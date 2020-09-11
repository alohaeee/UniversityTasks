#ifndef QTABLEMODEL_H
#define QTABLEMODEL_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QArrayData>

#include <QAbstractTableModel>
#include <QTableWidget>
#include <QAbstractItemModel>

using TableModelData = QList<QVector<QString>>;
using TableRow = QVector<QString>;
using CompareFunction = std::function<bool(const TableRow& a, TableRow& b)>;
using CompareFunctionGetter = std::function<CompareFunction(int,Qt::SortOrder)>;

class TableSharedModel;
class TableGroupModel;

class TableModel : public QAbstractTableModel
{
private:
    Q_OBJECT
    
    TableModelData m_data;

    int m_columnCount = 0;


    QChar m_separator;
    QVector<QString> m_horizontalHeaderData;

    QVector<CompareFunctionGetter> m_compareFunctionGetters;

public:
    friend TableSharedModel;
    friend TableGroupModel;

    TableModel(const QChar& separator, const int& columCount, QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;


    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    void readFromFile(const QString& filePath, int countLineElements);
    QChar getSeparator() const;
    void setSeparator(const QChar &separator);

    bool setCompareFunctionGetter(int index, CompareFunctionGetter comparePair);

    bool countColumnValues(int from, int to, int move, int divide);

    const TableModelData& getDataList() const;




    void setColumnCount(int columnCount);

signals:
    void created();
protected slots:

    void onCreate();
public slots:
    void clearData();

};

CompareFunction CompInt(int column, Qt::SortOrder order);
CompareFunction CompLowerString(int column, Qt::SortOrder order);
CompareFunction CompString(int column, Qt::SortOrder order);


#endif // QTABLEMODEL_H
