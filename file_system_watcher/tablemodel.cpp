#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableHandler* TableModel::handler() const
{
    return tableHandler;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return tableHandler->getRowsRef().size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    auto rows = tableHandler->getRowsRef();
    auto row = rows[index.row()];
    double arr[] = {0.2, 0.4, 0.1, 0.3};
    switch (role) {
        case Value:
            return row.getColValue(index.column(), index.row()==0);
        case Color:
            if(index.row()==0){
                return "grey";
            }else{
                return index.row() % 2 == 1 ? "white" : "#D3D3D3";
            }
        case Size:
            return arr[index.column()];
        case isLeft:
            return index.column()==0;
        default:
            break;
     }

     return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Color] = "color";
    names[Value] = "value";
    names[Size] = "size";
    names[isLeft] = "isLeft";
    return names;
}

void TableModel::setHandler(TableHandler *handler)
{
    beginResetModel();

    if (tableHandler)
        tableHandler->disconnect(this);

    tableHandler = handler;

    if (tableHandler) {
        connect(tableHandler, &TableHandler::postRowAppended, this, [=]() {
            beginResetModel();
            emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
            endResetModel();
        });
        connect(tableHandler, &TableHandler::postReInit, this, [=]() {
            beginResetModel();
            emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
            endResetModel();
        });
    }

    endResetModel();
}

Qt::ItemFlags TableModel::flags(QModelIndex const& idx) const
{
  if (false == idx.isValid())
  {
    return Qt::ItemIsEditable;
  }

  return QAbstractTableModel::flags(idx) | Qt::ItemIsEditable;
}
