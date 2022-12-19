#pragma once

#ifndef CATGENERATOR_H
#define CATGENERATOR_H

#include <QThread>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QList>
#include <QFileInfo>
#include <QReadWriteLock>

class CatGenerator : public QThread
{
    Q_OBJECT
public:
    CatGenerator(QObject *parent = nullptr) : QThread(parent)
    {
    };

    void run() override {
       getCat(fileInfo);
       lock.lockForRead();
       lock.unlock();
    }

private slots:
    void downloadFinished(QNetworkReply *reply);

public:
    void getCat(QFileInfo path);
private:
    QFileInfo fileInfo;
    QNetworkAccessManager *nam;
    QReadWriteLock lock;
};

#endif // CATGENERATOR_H
