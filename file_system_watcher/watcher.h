#pragma once

#ifndef TESTWATCHER_H
#define TESTWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfoList>

#include "catgenerator.h"
#include "listHandler.h"
#include "tablehandler.h"

class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = nullptr);
    void setItemsPtr(QVector<Item>* mPaths){
        this->mPaths=mPaths;
    }
    void setTableHandler(TableHandler* ptr){
        this->mtableHandler=ptr;
    }
    ~Watcher(){
        gen.wait();
    }
signals:

public slots:
    void startMonitoring();
    void stopMonitoring();

private slots:
    void folderEvent(const QString&);
    void fileEvent(const QString&);

private:
    QVector<Item>* mPaths = nullptr;
    QFileSystemWatcher* folderWatcher;
    QFileSystemWatcher* fileWatcher;
    QHash<QString, QFileInfoList> currFolderList;
    QVector<QString> folderPaths;
    QVector<QString> filePaths;
    CatGenerator gen;
    TableHandler* mtableHandler;

    void generateAllPaths();
    void generateFilePaths(QString path);
    void addFolder(QString path);
};

#endif // TESTWATCHER_H
