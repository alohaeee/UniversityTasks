#include "QueueModel.h"

#include "FinishModel.h"
#include "OrderModel.h"

void QueueModel::OnChangeTime(FinishModel &notWaitingModel)
{
    beginResetModel();
    QList<int> toDelete;
    for (int i = 0; i < m_queue.size(); i++)
    {
        if (!m_queue[i].AddSec())
        {
            toDelete.append(i);
        }
    }
    for (int i = toDelete.size() - 1; i >= 0; i--)
    {
        auto order = std::move(m_queue[toDelete[i]]);
        notWaitingModel.AddOrderWithRating(std::move(order), -1);
        m_queue.removeAt(toDelete[i]);
    }
    endResetModel();
}

void QueueModel::AddClient(const Client &client)
{
    beginResetModel();
    m_queue.append(client);
    endResetModel();
    // S dataChanged(index(0, rowCount() - 1), index(1, rowCount() - 1));
}

Client QueueModel::PopUpClient()
{
    beginResetModel();
    auto front = m_queue.front();
    m_queue.removeFirst();
    endResetModel();

    return front;
}

int QueueModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_queue.size();
}

int QueueModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 2;
}

QVariant QueueModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        auto client = m_queue[index.row()];
        if (index.column() == 0)
        {
            return client.id;
        }
        else
        {
            return client.StringedTime();
        }
    }
    return QVariant();
}

QVariant QueueModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 0)
            {
                return QString("Id");
            }
            else
            {
                return QString("Время ожидания в очереди");
            }
        }
    }
    return QVariant();
}
