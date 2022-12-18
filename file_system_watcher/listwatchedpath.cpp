#include "listwatchedpath.h"
#include <QDebug>

ListWatchedPath::ListWatchedPath(QObject *parent)
    : QObject{parent}
{
}

void ListWatchedPath::appendItem(QString path){
    emit preItemAppended();
    paths.append(*(new Item(paths.size(), path, uniqueId++)));
    idMap[uniqueId-1]=paths.size()-1;
    emit postItemAppended();
}

void ListWatchedPath::removeItem(int id){
    emit preItemRemoved(idMap[id]);
    paths.removeAt(idMap[id]);
    for(int i=0;i<paths.size();i++){
        idMap[paths[i].id]=i;
    }
    emit postItemRemoved();
}

int ListWatchedPath::getRealPos(int id){
    return idMap[id];
}