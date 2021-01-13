#ifndef FINISHMODEL_H
#define FINISHMODEL_H

#include "OrderModel.h"

struct Rating
{
    static constexpr int MAX_RATING = 5;
    Rating(int rating)
    {
        if (rating > MAX_RATING)
        {
            this->rating = MAX_RATING;
        }
        else if (rating < 0)
        {
            this->rating = -1;
        }
        else
        {
            this->rating = rating;
        }
    }
    QString ToString() const
    {
        if (rating == -1)
        {
            return "Не дождался";
        }
        return QString("%1/%2").arg(rating).arg(MAX_RATING);
    }
    int rating;
};
class FinishModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FinishModel();
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void AddOrderWithRating(Order &&order, Rating &&rating);
    void Reset()
    {
        beginResetModel();

        m_rating.clear();
        m_orderModel.Reset();

        endResetModel();
    }

private:
    OrderModel m_orderModel{};
    QVector<Rating> m_rating{};
};

#endif // FINISHMODEL_H
