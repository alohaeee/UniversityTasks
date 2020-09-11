#include "tablegroupmodel.h"

#include "tablemodel.h"
#include <QDebug>


void TableGroupModel::sharedData(TableModel *refModel, int groupPeople, int minPoint)
{
    // Clear labels and vertical headers coz new groupPeople will be change them anyway.
    m_groupLabels.clear();
    m_verticalHeaders.clear();

    m_dataGroup.clear();

    m_groupPeopleCount = groupPeople;
    int rowCount = refModel->rowCount();

    for(int i = rowCount - 1; i > 0 ; i--)
    {
        if(refModel->m_data[i][m_columnCount-1].toInt() > minPoint)
        {
            rowCount = i;
            break;
        }
    }


    // Set groupCountR
    int groupCount = rowCount / m_groupPeopleCount + 1;

    QVector<QVector<QString*>> groupedFormat;

    groupedFormat.resize(groupCount);

    for(int j = 0, k = rowCount-1, g=0; j <= k; j++, k--,g++)
    {
        if(g >= groupCount)
        {
            g=0;
        }
        groupedFormat[g].append(refModel->m_data[j].data());
        groupedFormat[g].append(refModel->m_data[k].data());
    }
   // m_groupPeopleCount = groupedFormat[0].size();


    // Index of column which will be sorting
    int index = m_columnCount - 1;
    // GroupCounter
    int i = 1;

    this->beginResetModel();

    for(auto& g: groupedFormat)
    {
        std::sort(g.begin(),g.end(),[index](const auto& a,const auto& b)
        {
            return a[index].toInt() > b[index].toInt();
        });

        // Create group line and move it to groupLabels.
        createGroupLine(i);
        // Add group line at begin of each group.
        g.push_front(m_groupLabels.back().data());

        // Middle point of each group.
        double middlePoint = 0;
        int peopleNum = 0;
        foreach(const auto& row, g)
        {
            middlePoint += row[index].toDouble();
            // Append group row ref to data vector. Do this way for data acsess in Table View methods.
            m_dataGroup.append(row);
            // Fill vertical headers with nums of student row.
            m_verticalHeaders.append(peopleNum);
            peopleNum++;
        }
        // Convert midde points to a row and append it
        QVector<QString> middleLine;

        middleLine.resize(m_columnCount);
        middleLine[0] = "Средний общий балл: " + QString::number(middlePoint/(g.size()-1),'f',2);
        m_groupLabels.append(std::move(middleLine));
        // Also append ref to data.
        m_dataGroup.append(m_groupLabels.back().data());

        m_verticalHeaders.append(0);

        // Create separator and append it.
        QVector<QString> separatorLine;

        separatorLine.fill("",m_columnCount);
        m_groupLabels.append(std::move(separatorLine));
        m_dataGroup.append(m_groupLabels.back().data());
        m_verticalHeaders.append(0);


        i++;
    }
    // Change row count after all manipulation.
    m_rowCount=m_dataGroup.size();

    this->endResetModel();
}

void TableGroupModel::sharedHeaderData(TableModel *refModel)
{
    m_sharedHeaders = refModel->m_horizontalHeaderData.data();
}

void TableGroupModel::setColumnCount(int columnCount)
{
    m_columnCount = columnCount;
}

int TableGroupModel::groupPeopleCount() const
{
    return m_groupPeopleCount;
}

const QVector<QString>& TableGroupModel::createGroupLine(int index)
{
    QVector<QString> line;

    line.fill("*****************", columnCount());
    line[0] = "************ *Группа " + QString::number(index) + "* ************";
    m_groupLabels.append(std::move(line));

    return m_groupLabels.back();
}

TableGroupModel::TableGroupModel(QObject *parent,int groupPeopleCount) : QAbstractTableModel(parent) ,
    m_rowCount(0), m_columnCount(0), m_groupPeopleCount(groupPeopleCount)
{

}



int TableGroupModel::rowCount(const QModelIndex &) const
{
    return m_rowCount;
}

int TableGroupModel::columnCount(const QModelIndex &) const
{
    return m_columnCount;
}

QVariant TableGroupModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    switch(role)
    {
    case Qt::DisplayRole:
    {
        return m_dataGroup[index.row()][index.column()];
    }
    default:
        return QVariant();
    }
}




QVariant TableGroupModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation==Qt::Horizontal)
        {
            return m_sharedHeaders[section];
        }
        else if(orientation==Qt::Vertical)
        {
            if(m_verticalHeaders.at(section) == 0)
                return QVariant();
            return m_verticalHeaders.at(section);

        }
    }
    return QVariant();
}
