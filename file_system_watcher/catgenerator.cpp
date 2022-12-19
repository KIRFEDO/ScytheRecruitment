#include "catgenerator.h"
#include <QFile>
#include <QPixmap>
#include <QNetworkProxyFactory>

void CatGenerator::getCat(QFileInfo fInfo){
    fileInfo = fInfo;
    nam = new QNetworkAccessManager(this);
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    connect(nam, &QNetworkAccessManager::finished, this, &CatGenerator::downloadFinished);
    nam->get(QNetworkRequest(QUrl("http://cataas.com/cat/says/hello%20world!")));
    lock.lockForRead();
}

void CatGenerator::downloadFinished(QNetworkReply *reply){
    QPixmap pm;
    pm.loadFromData(reply->readAll());
    QString catPath = fileInfo.absoluteFilePath();
    catPath = catPath.left(catPath.length()-(fileInfo.suffix().length()+1));
    catPath+=".png";
    QFile file(catPath);
    file.open(QIODevice::WriteOnly);
    pm.save(&file, "PNG");
    file.close();
    lock.unlock();
}
