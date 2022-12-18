#ifndef TESTWATCHER_H
#define TESTWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfoList>

#include "listwatchedpath.h"

class TestWatcher : public QObject
{
    Q_OBJECT
public:
    explicit TestWatcher(QObject *parent = nullptr);
    void setItemsPtr(QVector<Item>* mPaths){
        this->mPaths=mPaths;
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

    void generateAllPaths();
    void generateFilePaths(QString path);
    void addFolder(QString path);
};

#endif // TESTWATCHER_H
