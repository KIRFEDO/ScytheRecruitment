#include "listHandler.h"
#include <QDebug>

ListHandler::ListHandler(QObject *parent)
    : QObject{parent}
{
}

void ListHandler::appendItem(QString path){
    emit preItemAppended();
    QString pathModified = path.left(4)=="file" ? path.right(path.length()-8) : path;
    paths.append(*(new Item(paths.size(), pathModified, uniqueId++)));
    idMap[uniqueId-1]=paths.size()-1;
    emit postItemAppended();
}

void ListHandler::removeItem(int id){
    emit preItemRemoved(idMap[id]);
    paths.removeAt(idMap[id]);
    for(int i=0;i<paths.size();i++){
        idMap[paths[i].id]=i;
        paths[i].color = i % 2 == 0 ? "white" : "#D3D3D3";
    }
    emit postItemRemoved();
}

int ListHandler::getRealPos(int id){
    return idMap[id];
}
