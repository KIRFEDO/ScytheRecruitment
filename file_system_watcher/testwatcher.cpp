#include "testwatcher.h"
#include <QDebug>
#include <QDir>
TestWatcher::TestWatcher(QObject *parent)
    : QObject{parent}
{
}

void TestWatcher::startMonitoring(){
    auto& paths = *mPaths;
//    for(const auto& path : paths){
//        qDebug()<<path.path<<"\n";
//    }
    if(watcher)
        delete watcher;

    watcher = new QFileSystemWatcher(this);
    watcher->addPath(paths[0].path);

    disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(folderEvent(QString)));
    disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(fileEvent(QString)));

    QDir dir(paths[0].path);

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    QFileInfoList list = dir.entryInfoList();

    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(folderEvent(QString)));
    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileEvent(QString)));

}

void TestWatcher::folderEvent(QString& path){
    qDebug()<<"folder"<<"\n";
}

void TestWatcher::fileEvent(QString& path){
    qDebug()<<"file"<<"\n";
}
