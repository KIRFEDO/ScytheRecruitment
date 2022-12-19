#include "watcher.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QDateTime>
#include <QtConcurrent>

#include "catgenerator.h"

Watcher::Watcher(QObject *parent)
    : QObject{parent}
{
}

void Watcher::startMonitoring(){
    generateAllPaths();
    folderWatcher = new QFileSystemWatcher(this);
    fileWatcher = new QFileSystemWatcher(this);
    for(const auto path : folderPaths){
        qDebug()<<path;
        folderWatcher->addPath(path);
    }
    for(const auto path : filePaths){
        fileWatcher->addPath(path);
    }
    disconnect(folderWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(folderEvent(QString)));
    disconnect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(fileEvent(QString)));
    for(const auto path : folderPaths){
        QDir dir(path);
        dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
        currFolderList[path] = dir.entryInfoList();
    }
    connect(folderWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(folderEvent(QString)));
    connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(fileEvent(QString)));
}

void Watcher::stopMonitoring(){
    disconnect(folderWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(folderEvent(QString)));
    disconnect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(fileEvent(QString)));
}

void Watcher::folderEvent(const QString& path){
    QDir dir(path);
    qint64 qiTimestamp=QDateTime::currentMSecsSinceEpoch();
    QDateTime dt;
    auto timestamp = dt.currentDateTime().toString("dd.MM.yyyy hh:mm");
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    auto oldFolderList = dir.entryInfoList();
    std::swap(currFolderList[path], oldFolderList);
    if(currFolderList[path].size() > oldFolderList.size()){
        for(auto fileInfo: currFolderList[path]){
            if(!oldFolderList.contains(fileInfo)){
                if(fileInfo.isFile())fileWatcher->addPath(fileInfo.absoluteFilePath());
                folderWatcher->addPath(fileInfo.absoluteFilePath());
                mtableHandler->appendRow(
                    *(new FolderEventStruct("Created", fileInfo.absoluteFilePath(), timestamp, fileInfo.isDir()))
                );
                break;
            }
        }
    }
    else if(currFolderList[path].size() < oldFolderList.size()){
        for(auto fileInfo: oldFolderList){
            if(!currFolderList[path].contains(fileInfo)){
                if(fileInfo.isFile())fileWatcher->removePath(fileInfo.absoluteFilePath());
                folderWatcher->removePath(fileInfo.absoluteFilePath());
                mtableHandler->appendRow(
                    *(new FolderEventStruct("Removed", fileInfo.absoluteFilePath(), timestamp, fileInfo.isDir()))
                );
                if(fileInfo.isFile()){
                    gen.getCat(fileInfo);
                }
            }
        }
    } else {

    }
}

void Watcher::fileEvent(const QString& path){
    qint64 qiTimestamp=QDateTime::currentMSecsSinceEpoch();
    QDateTime dt;
    auto timestamp = dt.currentDateTime().toString("dd.MM.yyyy hh:mm");
    mtableHandler->appendRow(
        *(new FolderEventStruct("Edited", path, timestamp, false))
    );
}

void Watcher::generateAllPaths(){
    auto& paths = *mPaths;
    folderPaths.clear();
    filePaths.clear();
    for(auto path : paths){
        addFolder(path.path);
        generateFilePaths(path.path);
    }
}

void Watcher::generateFilePaths(QString path) {
    QDir dir(path);
    QDirIterator fileIt(path, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(fileIt.hasNext()){
        dir = fileIt.next();
        filePaths.append(dir.path());
    };
}

void Watcher::addFolder(QString path) {
    folderPaths.append(path);
    QDir dir(path);
    QDirIterator fileIt(path, QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(fileIt.hasNext()){
        dir = fileIt.next();
        folderPaths.append(dir.path());
    };
}
