#ifndef CLIENT_H
#define CLIENT_H

#include "Food.h"

#include <array>

#include <QTime>

class Client
{
    using OrderList = std::array<QVector<IdType>, Dish::Size>;

public:
    // return false when client gets andgry and want go out
    bool ApplyDelta(QTime deltaTime)
    {
        auto delta = QTime(startTimeWait.elapsed());
        if (delta > maxQueueTimeWait)
        {
            return false;
        }
        return true;
    }

public:
    IdType id;
    OrderList order;
    QTime maxQueueTimeWait;
    QTime startTimeWait;
};

#endif // CLIENT_H
