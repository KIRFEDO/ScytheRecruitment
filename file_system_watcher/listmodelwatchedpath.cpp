#include "listmodelwatchedpath.h"

ListModelWatchedPath::ListModelWatchedPath(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ListModelWatchedPath::rowCount(const QModelIndex &parent) const
{
    return mList->getPaths().size();
}

QVariant ListModelWatchedPath::data(const QModelIndex &index, int role) const
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

bool ListModelWatchedPath::setData(const QModelIndex &index, const QVariant &value, int role)
{
   return false;
}

Qt::ItemFlags ListModelWatchedPath::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ListModelWatchedPath::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

bool ListModelWatchedPath::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> ListModelWatchedPath::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Color] = "color";
    names[Path] = "path";
    names[Id] = "id";
    return names;
}

ListWatchedPath* ListModelWatchedPath::list() const
{
    return mList;
}

void ListModelWatchedPath::setList(ListWatchedPath *list){
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &ListWatchedPath::preItemAppended, this, [=]() {
            const int index = mList->getPaths().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &ListWatchedPath::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &ListWatchedPath::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &ListWatchedPath::postItemRemoved, this, [=]() {
            beginResetModel();
            endRemoveRows();
            endResetModel();
        });
    }

    endResetModel();
}
