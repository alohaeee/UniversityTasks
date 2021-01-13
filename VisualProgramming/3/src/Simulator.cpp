#include "Simulator.h"

#include "FinishModel.h"
void Simulator::Init()
{
    mt.seed(rd());
}

void Simulator::RandDishLists(int n)
{

    std::uniform_int_distribution<int> time(10000, 600000);
    std::uniform_int_distribution<Dish::PriceType> priceRange(30, 1000);

    std::uniform_int_distribution<int> type(0, Dish::Size - 1);

    for (int i = 0; i < n; i++)
    {
        auto index = type(mt);

        auto &list = DishManager::GetCategory(Dish::DishType(index));
        auto price = priceRange(mt);
        auto profit = std::uniform_int_distribution<Dish::PriceType>(-100, price)(mt);
        list.AddDish(Dish{QString("SomeFoodName%1").arg(list.Size()), price, profit, time(mt)});
    }
}

int Simulator::Random(Simulator::Range range)
{
    return range(mt);
}

bool Simulator::IsTimeToCreateNewClient()
{
    static Range r = Range(0, 100);
    auto chance = Random(r);
    if (chance <= chanceOfNewClient)
    {
        return true;
    }
    return false;
}

Client Simulator::RandClient()
{
    return Client(clinetId++, RandOrderList(), clientTimeRange(mt));
}

OrderList Simulator::RandOrderList()
{
    OrderList orderList;
    int i = 0;
    for (auto &list : DishManager::GetLists())
    {
        QVector<IdType> dishes;
        auto foodCount = Random(Range(1, 3));
        if (list.Size())
        {
            auto range = Range(0, list.Size() - 1);
            for (int i = 0; i < foodCount; i++)
            {
                auto randomDish = Random(range);
                dishes.push_back(randomDish);
            }
        }
        orderList[i++] = std::move(dishes);
    }
    return orderList;
}

int Simulator::RandRating()
{
    return Random(Range(0, Rating::MAX_RATING));
}
