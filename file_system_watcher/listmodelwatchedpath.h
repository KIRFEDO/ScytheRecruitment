#ifndef LISTMODELWATCHEDPATH_H
#define LISTMODELWATCHEDPATH_H

#include <QAbstractListModel>

#include "listwatchedpath.h"

class ListModelWatchedPath : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ListWatchedPath *list READ list WRITE setList)

public:
    explicit ListModelWatchedPath(QObject *parent = nullptr);

    enum {
        Color,
        Path,
        Id
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;
    ListWatchedPath* list() const;
    void setList(ListWatchedPath *list);

private:
    ListWatchedPath *mList;
};

#endif // LISTMODELWATCHEDPATH_H
