#include "QueueModel.h"

QueueModel::QueueModel()
{
}

bool QueueModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}

int QueueModel::rowCount(const QModelIndex &parent) const
{
    return m_queue.size();
}

int QueueModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant QueueModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        auto client = m_queue[index.row()];
        if (index.column() == 0)
        {
            return client.id;
        }
        else
        {
            // return client.
        }
    }
    return QVariant();
}
