#pragma once

#ifndef LISTWATCHEDPATH_H
#define LISTWATCHEDPATH_H

#include <QObject>
#include <QVector>
#include <QHash>

struct Item{
    QString color;
    QString path;
    int id;
    void updateItem(size_t currentSize, int id){
        this->color = currentSize % 2 == 0 ? "white" : "#D3D3D3";
        this->id=id;
    }
    Item(size_t currentSize, QString path, int id){
        this->color = currentSize % 2 == 0 ? "white" : "#D3D3D3";
        this->path = path;
        this->id=id;
    }
};

class ListHandler : public QObject
{
    Q_OBJECT
public:
    explicit ListHandler(QObject *parent = nullptr);
    const QVector<Item>& getPaths() const {
        return paths;
    }

    QVector<Item>* getPathsPtr() {
        return &paths;
    }

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem(QString path);
    void removeItem(int id);
    int getRealPos(int id);
private:
    QVector<Item> paths;
    int uniqueId=0;
    QHash<int, int> idMap;
};

#endif // LISTWATCHEDPATH_H
