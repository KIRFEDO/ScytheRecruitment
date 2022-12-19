#include "listModel.h"

ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return mList->getPaths().size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const auto item = mList->getPaths().at(index.row());
    switch(role){
        case Color:
            return QVariant(item.color);
        case Path:
            return QVariant(item.path);
        case Id:
            return QVariant(item.id);
        default:
            return QVariant();
    }
}

bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   return false;
}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Color] = "color";
    names[Path] = "path";
    names[Id] = "id";
    return names;
}

ListHandler* ListModel::list() const
{
    return mList;
}

void ListModel::setList(ListHandler *list){
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &ListHandler::preItemAppended, this, [=]() {
            const int index = mList->getPaths().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &ListHandler::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &ListHandler::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &ListHandler::postItemRemoved, this, [=]() {
            beginResetModel();
            endRemoveRows();
            endResetModel();
        });
    }

    endResetModel();
}
