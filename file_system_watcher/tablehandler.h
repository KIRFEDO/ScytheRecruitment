#pragma once

#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QObject>
#include <QVector>
#include "folderEventStruct.h"

class TableHandler : public QObject
{
    Q_OBJECT
public:
    explicit TableHandler(QObject *parent = nullptr);
    QVector<FolderEventStruct>& getRowsRef(){
        return rows;
    }

signals:
void postRowAppended();
void postReInit();

public slots:
    void appendRow(FolderEventStruct& folderEvent);
    void initTable();
private:
    QVector<FolderEventStruct> rows;
};

#endif // TABLEHANDLER_H
