#ifndef FOOD_H
#define FOOD_H

#include <QMap>
#include <QString>
#include <QTime>
#include <QVector>
#include <array>
#include <cstdint>

//"Картошка:200,30;30;Main";

class Dish
{
public:
    using PriceType = float;

    Dish() = default;

    enum DishType
    {
        Main,
        Drinks,
        Snacks,
        Garnirshs,
        Size
    };

    QString name;
    PriceType price;
    PriceType profit;
    QTime timeMade;
    // DishType type;
};

using IdType = uint32_t;
class DishList
{
public:
public:
    IdType AddDish(const Dish &dish)
    {
        m_dishList.push_back(dish);
        return m_dishList.size() - 1;
    }
    IdType AddDish(Dish &&dish)
    {
        m_dishList.push_back(dish);
        return m_dishList.size() - 1;
    }
    Dish &GetDish(IdType id)
    {
        return m_dishList[id];
    }
    bool IsValidId(IdType id)
    {
        return id < IdType(m_dishList.size());
    }
    const QVector<Dish> &GetList()
    {
        return m_dishList;
    }

private:
    QVector<Dish> m_dishList;
};

class DishManager
{
public:
    inline DishList &GetCategory(Dish::DishType i)
    {
        return list[i];
    }

private:
    inline static std::array<DishList, Dish::Size> list{};
};

#endif // FOOD_H
