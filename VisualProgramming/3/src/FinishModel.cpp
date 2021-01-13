#include "FinishModel.h"

FinishModel::FinishModel()
{
}

QVariant FinishModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 5)
            {
                return "Рейтинг";
            }
            else
            {
                return m_orderModel.headerData(section, orientation, role);
            }
        }
    }
    return QVariant();
}

int FinishModel::columnCount(const QModelIndex &parent) const
{
    return m_orderModel.columnCount() + 1;
}

int FinishModel::rowCount(const QModelIndex &parent) const
{
    return m_orderModel.rowCount();
}

QVariant FinishModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    if (index.column() == 5)
    {
        return m_rating[index.row()].ToString();
    }
    return m_orderModel.data(index, role);
}

void FinishModel::AddOrderWithRating(Order &&order, Rating &&rating)
{
    beginResetModel();
    m_orderModel.AppendOrder(std::move(order));
    m_rating.push_back(rating);
    endResetModel();
}
