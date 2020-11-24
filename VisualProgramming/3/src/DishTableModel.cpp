#include "DishTableModel.h"

#include <QDebug>

QVariant DishTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Имя");
            case 1:
                return QString("Цена");
            case 2:
                return QString("Профит");
            case 3:
                return QString("Время приготовления");
            }
        }
    }
    return QVariant();
}

int DishTableModel::rowCount(const QModelIndex &parent) const
{
    return DishManager::GetCategory(m_type).Size();
}

int DishTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant DishTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    auto &category = DishManager::GetCategory(m_type);
    auto dish = category.GetDish(index.row());

    switch (index.column())
    {
    case 0:
        return dish.name;
    case 1:
        return dish.price;
    case 2:
        return dish.profit;
    case 3:
        return FromMSToString(dish.cookTime);
    }
    return QVariant();
}

Qt::ItemFlags DishTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}
