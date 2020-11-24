#include "OrderModel.h"

#include "FinishModel.h"
OrderModel::OrderModel(QObject *parent) : QAbstractTableModel(parent)
{
}

QVariant OrderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Номер заказа");
            case 1:
                return QString("Id клиента");
            case 2:
                return QString("Время ожидания");
            case 3:
                return QString("Id блюд");
            case 4:
                return QString("Время приготовления");
            }
        }
    }
    return QVariant();
}

int OrderModel::rowCount(const QModelIndex &parent) const
{
    return m_orders.size();
}

int OrderModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant OrderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    auto order = m_orders[index.row()];
    switch (index.column())
    {
    case 0:
        return order.id;
    case 1:
        return order.client.id;
    case 2:
        return FromMSToString(order.client.currentTime) + '/' + FromMSToString(order.client.maxQueueTimeWait);
    case 3: {
        return order.orderStringed;
    }
    case 4:
        return FromMSToString(order.currentTime) + '/' + FromMSToString(order.goalTime);
    }

    return QVariant();
}

void OrderModel::OnChangeTime(FinishModel &finishModel, FinishModel &notWaitingModel)
{
    beginResetModel();
    QList<int> toDelete;
    for (int i = 0; i < m_orders.size(); i++)
    {
        if (!m_orders[i].client.AddSec())
        {
            toDelete.append(i);
        }
    }
    for (int i = toDelete.size() - 1; i >= 0; i--)
    {
        auto order = std::move(m_orders[toDelete[i]]);
        notWaitingModel.AddOrderWithRating(std::move(order), -1);
        m_orders.removeAt(toDelete[i]);
    }
    toDelete.clear();

    for (int i = 0; i < m_orders.size(); i++)
    {
        if (m_orders[i].AddSec())
        {
            toDelete.append(i);
        }
    }
    for (int i = toDelete.size() - 1; i >= 0; i--)
    {
        auto order = std::move(m_orders[toDelete[i]]);
        finishModel.AddOrderWithRating(std::move(order), Simulator::RandRating());
        m_orders.removeAt(toDelete[i]);
    }
    endResetModel();
}

void OrderModel::CreateOrderWithClient(Client &&client)
{
    beginResetModel();
    AppendOrder(Order{client});
    endResetModel();
}

void OrderModel::AppendOrder(Order &&order)
{
    m_orders.push_back(order);
}
