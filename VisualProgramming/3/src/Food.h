#ifndef FOOD_H
#define FOOD_H

#include <QMap>
#include <QString>
#include <QTime>
#include <QVector>
#include <array>
#include <cstdint>
#include <random>

class Dish
{
public:
    using PriceType = int;

    Dish() = default;

    enum DishType
    {
        Main,
        Drinks,
        Snacks,
        Garnirshs,
        Size
    };

    static QString typeToString(DishType type)
    {
        switch (type)
        {
        case Main:
            return "Основное";
        case Drinks:
            return "Напитки";
        case Snacks:
            return "Снеки";
        case Garnirshs:
            return "Гарнир";
        default:
            return "";
        }
    }

    QString name;
    PriceType price;
    PriceType profit;
    int cookTime;
};

inline QString FromMSToString(int ms)
{
    return QTime(0, 0, 0).addMSecs(ms).toString("hh:mm:ss");
}

using IdType = uint32_t;
class DishList
{
public:
    //    DishList(Dish::DishType type) : m_type{type}
    //    {}
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
    inline std::size_t Size() const
    {
        return m_dishList.size();
    }
    inline Dish::DishType GetType()
    {
        return m_type;
    }

private:
    Dish::DishType m_type;
    QVector<Dish> m_dishList;
};

class DishManager
{
public:
    static inline DishList &GetCategory(Dish::DishType i)
    {
        return list[i];
    }

    static std::size_t ListCount()
    {
        return Dish::Size;
    }
    static const std::array<DishList, Dish::Size> &GetLists()
    {
        return list;
    }

private:
    inline static std::array<DishList, Dish::Size> list{};
};

#endif // FOOD_H
