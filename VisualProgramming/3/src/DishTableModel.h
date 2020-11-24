#ifndef DISHTABLEMODEL_H
#define DISHTABLEMODEL_H

#include <QAbstractTableModel>

#include "Food.h"

class DishTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    DishTableModel(Dish::DishType type, QObject *parent = nullptr) : QAbstractTableModel{parent}, m_type{type}
    {
    }

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    Dish::DishType m_type;
};

#endif // DISHTABLEMODEL_H
