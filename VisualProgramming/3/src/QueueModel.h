#ifndef QUEUEMODEL_H
#define QUEUEMODEL_H

#include <QAbstractListModel>
#include <QQueue>

#include "Client.h"
class QueueModel : public QAbstractTableModel
{
public:
    QueueModel();

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QQueue<Client> m_queue;
};

#endif // QUEUEMODEL_H
