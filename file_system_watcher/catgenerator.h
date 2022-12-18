#ifndef CATGENERATOR_H
#define CATGENERATOR_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QList>
#include <QFileInfo>

class CatGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CatGenerator(QObject *parent = nullptr);

signals:

public slots:
private slots:
    void downloadFinished(QNetworkReply *reply);
    void sslErros(QNetworkReply *reply, const QList<QSslError> &errors);

public:
    void getCat(QFileInfo path);
private:
    QFileInfo fileInfo;
    QNetworkAccessManager *nam;
};

#endif // CATGENERATOR_H
