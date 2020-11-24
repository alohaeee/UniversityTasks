#ifndef QUEUEMODEL_H
#define QUEUEMODEL_H

#include <QAbstractListModel>
#include <QQueue>

#include "Client.h"

class FinishModel;
class QueueModel : public QAbstractTableModel
{
public:
    explicit QueueModel(QObject *parent = nullptr) : QAbstractTableModel(parent)
    {
    }

    // bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void OnChangeTime(FinishModel &notWaitingModel);
    void AddClient(const Client &client);
    Client PopUpClient();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void Reset()
    {
        beginResetModel();
        m_queue.clear();
        endResetModel();
    }

private:
    QQueue<Client> m_queue;
};

#endif // QUEUEMODEL_H
