#include "tablehandler.h"

TableHandler::TableHandler(QObject *parent)
    : QObject{parent}
{
    initTable();
}

void TableHandler::appendRow(FolderEventStruct& folderEvent){
    rows.append(folderEvent);
    emit postRowAppended();
}

void TableHandler::initTable()
{
    rows.clear();
    rows.append(*(new FolderEventStruct("1", "1", "1", false)));
    emit postReInit();
}
