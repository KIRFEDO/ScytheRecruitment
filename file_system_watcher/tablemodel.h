#pragma once

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "tablehandler.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(TableHandler *handler READ handler WRITE setHandler)
    enum {
        Color,
        Value,
        Size,
        isLeft
    };
public:
    explicit TableModel(QObject *parent = nullptr);
    TableHandler* handler() const;
    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(QModelIndex const& idx) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void setHandler(TableHandler* handler);
private:
    TableHandler* tableHandler;
};

#endif // TABLEMODEL_H
