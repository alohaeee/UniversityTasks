#include "tablemodel.h"
#include <QDebug>
#include <QFile>
#include "exception.h"




QChar TableModel::getSeparator() const
{
    return m_separator;
}

void TableModel::setSeparator(const QChar &separator)
{
    m_separator = separator;
}

bool TableModel::setCompareFunctionGetter(int index, CompareFunctionGetter compareFunctionGetter)
{
    if(index < 0 || index >= m_columnCount)
        return false;
    m_compareFunctionGetters.replace(index,compareFunctionGetter);
    return true;
}

bool TableModel::countColumnValues(int from, int to, int move, int divide)
{
    bool isOkay = true;
    int i = 0;
    foreach (const TableRow& row, m_data)
    {
        double value = 0;

        for(int j = from; j < to; j++)
        {
            value += row.at(j).toInt(&isOkay);
        }
        value /= divide;

        if(m_data[i].size() != m_columnCount) m_data[i].resize(m_columnCount);
        m_data[i].replace(move, (divide == 1 ? QString::number(value) : QString::number(value,'f',1)));

        i++;
    }
    return isOkay;
}

const TableModelData& TableModel::getDataList() const
{
    return m_data;
}


void TableModel::setColumnCount(int columnCount)
{
    m_columnCount = columnCount;
    m_horizontalHeaderData.resize(m_columnCount);
    m_compareFunctionGetters.resize(m_columnCount);

    setCompareFunctionGetter(0,CompString);
    for(int i = 1;i < columnCount; i++)
    {
        setCompareFunctionGetter(i,CompInt);
    }

}

TableModel::TableModel(const QChar &separator, const int &columCount, QObject *parent) :
    QAbstractTableModel(parent),m_columnCount(columCount), m_separator(separator)
{
    onCreate();
}

int TableModel::rowCount(const QModelIndex &) const
{
    return m_data.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return m_columnCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    switch(role)
    {
    case Qt::DisplayRole:
        return m_data[index.row()][index.column()];
    default:
        return QVariant();
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {
        return false;
    }
    switch (role)
    {
    case Qt::EditRole:
        m_data[index.row()].replace(index.column(),value.toString());
        return true;
    default:
        return false;
    }
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void TableModel::sort(int column, Qt::SortOrder order)
{
    if(m_data.size() == 0) return;

    CompareFunction comp = m_compareFunctionGetters.at(column)(column,order);

    this->beginResetModel();

    std::sort(m_data.begin(),m_data.end(),comp);

    this->endResetModel();

}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation==Qt::Horizontal)
        {
            return m_horizontalHeaderData.at(section);
        }
        else if(orientation==Qt::Vertical)
        {
            return section+1;
        }
    }
    return QVariant();
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role == Qt::EditRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section >= 0 && section < m_columnCount)
            {
                m_horizontalHeaderData.replace(section,value.toString());
                return true;
            }
        }
    }
    return false;
}

void TableModel::readFromFile(const QString& filePath, int countLineElements)
{
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        throw Exception(file.errorString(),Exception::Critical);

    // Make signal of begin reset whole data.
    this->beginResetModel();

    TableModelData bufData = m_data;
    m_data.clear();

    QString line = file.readLine();
    {
        for(int i = 0; i < countLineElements-1; i++)
            {
                QString value = line.section(m_separator,i,i);

                if(value.isNull())
                {
                    // Return old data.
                    m_data = bufData;
                    throw Exception("Bad File", Exception::Warning);
                }

                m_horizontalHeaderData[i] = value;
            }
            // Chop '\n' from last section.
            auto lastValue = line.section(m_separator,-1);
            lastValue.chop(1);
            m_horizontalHeaderData[countLineElements-1] = lastValue;
    }
    line = file.readLine();
    while(!line.isNull())
    {
        m_data.append(TableRow());

        for(int i = 0; i < countLineElements-1; i++)
        {
            QString value = line.section(m_separator,i,i);

            if(value.isNull())
            {
                // Return old data.
                m_data = bufData;
                throw Exception("Bad File", Exception::Warning);
            }

            m_data.back().append(std::move(value));
        }
        // Chop '\n' from last section.
        auto lastValue = line.section(m_separator,-1);
        lastValue.chop(1);
        m_data.back().append(std::move(lastValue));

        line = file.readLine();
    }
    // Make signal of end reset whole data.
    this->endResetModel();

    file.close();
}

void TableModel::onCreate()
{
    m_horizontalHeaderData.resize(m_columnCount);
    m_compareFunctionGetters.resize(m_columnCount);

    created();
}

void TableModel::clearData()
{
    this->beginResetModel();
    m_data.clear();
    this->endResetModel();
}




CompareFunction CompInt(int column, Qt::SortOrder order)
{
    if(order == Qt::SortOrder::DescendingOrder)
        return [column](const TableRow& a, const TableRow& b)
                {
                    return a.at(column).toInt() < b.at(column).toInt();
                };
    else
        return [column](const TableRow& a, const TableRow& b)
                {
                    return a.at(column).toInt() > b.at(column).toInt();
                };
}

CompareFunction CompLowerString(int column, Qt::SortOrder order)
{
    if(order == Qt::SortOrder::DescendingOrder)
        return [column](const TableRow& a, const TableRow& b)
                {
                    return a.at(column).toLower() < b.at(column).toLower();
                };
    else
        return [column](const TableRow& a, const TableRow& b)
                {
                    return a.at(column).toLower() > b.at(column).toLower();
                };
}

CompareFunction CompString(int column, Qt::SortOrder order)
{
    if(order == Qt::SortOrder::DescendingOrder)
        return [column](const TableRow& a, const TableRow& b)
                {
                    return a.at(column) < b.at(column);
                };
    else
        return [column](const TableRow& a, const TableRow& b)
                {
                    return a.at(column) > b.at(column);
                };
}
