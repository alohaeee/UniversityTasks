#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "Client.h"
#include "Simulator.h"

struct Order
{
    Order(const Client &client) : client{client}
    {
        orderStringed = DoStringOrder();
        int maxTime = 0;
        int count = 0;
        int average = 0;
        int i = 0;
        for (auto &list : client.order)
        {
            auto category = DishManager::GetCategory(Dish::DishType(i));
            for (auto &index : list)
            {
                auto dish = category.GetDish(index);
                count++;
                average += dish.cookTime;
                if (maxTime < dish.cookTime)
                {
                    maxTime = dish.cookTime;
                }
            }
            i++;
        }
        average /= count;
        goalTime = average;
        id = Simulator::orderId++;
    }
    QString DoStringOrder()
    {
        QString buf;
        int i = 0;
        for (auto &list : client.order)
        {
            if (list.size())
            {
                buf.append(Dish::typeToString(Dish::DishType(i)));
                buf += ": ";
                for (auto &o : list)
                {
                    buf += QString::number(o) + ',';
                }
                buf.resize(buf.size() - 1);
                buf += ";\n";
            }
            i++;
        }
        return buf;
    }
    // return true when order is ready false otherwise
    bool AddSec()
    {
        currentTime += 1000;
        if (currentTime >= goalTime)
        {
            return true;
        }
        return false;
    }
    IdType id;
    Client client;
    QString orderStringed;
    int currentTime = 0;
    int goalTime;
};

class FinishModel;
class OrderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OrderModel(QObject *parent = nullptr);

    // Header:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void OnChangeTime(FinishModel &finishModel, FinishModel &notWaitingModel);
    void CreateOrderWithClient(Client &&client);
    void AppendOrder(Order &&order);

    void Reset()
    {
        beginResetModel();
        m_orders.clear();
        endResetModel();
    }

private:
    QVector<Order> m_orders;
};

#endif // ORDERMODEL_H
