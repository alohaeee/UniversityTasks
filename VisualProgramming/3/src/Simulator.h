#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QDebug>
#include <random>

#include "Client.h"
#include "Food.h"
#include <array>
class Simulator
{
public:
    static void Init();
    static void RandDishLists(int n);
    using Range = std::uniform_int_distribution<int>;
    static int Random(Range range);
    static bool IsTimeToCreateNewClient();
    static Client RandClient();
    static OrderList RandOrderList();
    static int RandRating();

    inline static int chanceOfNewClient = 5;
    inline static Range clientTimeRange = Range(10000, 15 * 60 * 1000);
    inline static std::random_device rd;
    inline static std::mt19937 mt;
    inline static int clinetId = 0;
    inline static int orderId = 0;

    inline static int clientOrderInSameTime = 5;
    inline static int secTime = 1000;
    inline static int clientsOnStart = 10;
};

#endif // SIMULATOR_H
