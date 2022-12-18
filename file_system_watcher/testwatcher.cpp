#include "testwatcher.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include "catgenerator.h"

TestWatcher::TestWatcher(QObject *parent)
    : QObject{parent}
{
}

void TestWatcher::startMonitoring(){
    generateAllPaths();
    folderWatcher = new QFileSystemWatcher(this);
    fileWatcher = new QFileSystemWatcher(this);
    for(const auto path : folderPaths){
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

void TestWatcher::stopMonitoring(){
    disconnect(folderWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(folderEvent(QString)));
    disconnect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(fileEvent(QString)));
}

void TestWatcher::folderEvent(const QString& path){
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    auto oldFolderList = dir.entryInfoList();
    std::swap(currFolderList[path], oldFolderList);
    if(currFolderList[path].size() > oldFolderList.size()){
        for(auto fileInfo: currFolderList[path]){
            if(!oldFolderList.contains(fileInfo)){
                qDebug()<<"new | "<<fileInfo.absoluteFilePath();
                break;
            }
        }
    }
    else if(currFolderList[path].size() < oldFolderList.size()){
        for(auto fileInfo: oldFolderList){
            if(!currFolderList[path].contains(fileInfo)){
                qDebug()<<"delete | "<<fileInfo.absoluteFilePath();
                if(fileInfo.isFile()){
                    gen.getCat(fileInfo);
                }
            }
        }
    } else {

    }
}

void TestWatcher::fileEvent(const QString& path){
    if(QFile::exists(path)){
        qDebug()<<"edit | "<<path;
    }
}

void TestWatcher::generateAllPaths(){
    auto& paths = *mPaths;
    folderPaths.clear();
    filePaths.clear();
    for(auto path : paths){
        qDebug()<<path.path;
        addFolder(path.path);
    }
}

void TestWatcher::generateFilePaths(QString path) {
    QDir dir(path);
    QDirIterator fileIt(path, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(fileIt.hasNext()){
        dir = fileIt.next();
        filePaths.append(dir.path());
    };
}

void TestWatcher::addFolder(QString path) {
    folderPaths.append(path);
    QDir dir(path);
    auto infoList = dir.entryInfoList();
    for(auto fileInfo : infoList){
        folderPaths.append(fileInfo.absoluteFilePath());
    }

    generateFilePaths(path);
}
