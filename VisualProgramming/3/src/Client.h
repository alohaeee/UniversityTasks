#ifndef CLIENT_H
#define CLIENT_H

#include "Food.h"

#include <array>

#include <QTime>

using OrderList = std::array<QVector<IdType>, Dish::Size>;
class Client
{

public:
    // return false when client gets andgry and want go out
    bool AddSec()
    {
        currentTime += 1000;
        if (currentTime >= maxQueueTimeWait)
        {
            return false;
        }
        return true;
    }

    QString StringedTime()
    {
        return QString("%1/%2")
            .arg(QTime(0, 0, 0).addMSecs(currentTime).toString("hh:mm:ss"))
            .arg(QTime(0, 0, 0).addMSecs(maxQueueTimeWait).toString("hh:mm:ss"));
    }
    Client(IdType id, OrderList list, int maxTime) : id(id), maxQueueTimeWait(maxTime), order{list}
    {
    }

public:
    IdType id;
    OrderList order;
    int maxQueueTimeWait;
    int currentTime = 0;
};

#endif // CLIENT_H
