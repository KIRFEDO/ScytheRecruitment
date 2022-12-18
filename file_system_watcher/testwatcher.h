#ifndef TESTWATCHER_H
#define TESTWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>

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
//    void stopMonitoring();

private slots:
    void folderEvent(QString&);
    void fileEvent(QString&);

private:
    QVector<Item>* mPaths = nullptr;
    QFileSystemWatcher* watcher;
};

#endif // TESTWATCHER_H
