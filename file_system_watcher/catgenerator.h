#ifndef CATGENERATOR_H
#define CATGENERATOR_H

#include <QObject>

class CatGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CatGenerator(QObject *parent = nullptr);

signals:

};

#endif // CATGENERATOR_H
