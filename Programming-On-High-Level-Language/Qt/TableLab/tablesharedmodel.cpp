#include "tablesharedmodel.h"

#include <QDebug>

#include "tablemodel.h"
TableSharedModel::TableSharedModel(QObject* parent) : QAbstractTableModel(parent)
{
    m_sharedHeaders = nullptr;
}

int TableSharedModel::rowCount(const QModelIndex &) const
{
    return m_sharedData.size();
}

int TableSharedModel::columnCount(const QModelIndex &) const
{
    return m_columns.size();
}

QVariant TableSharedModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    switch(role)
    {
    case Qt::DisplayRole:
        return m_sharedData[index.row()][m_columns[index.column()]];
    default:
        return QVariant();
    }
}

Qt::ItemFlags TableSharedModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TableSharedModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation==Qt::Horizontal)
        {
            return m_sharedHeaders[m_columns[section]];
        }
        else if(orientation==Qt::Vertical)
        {
            return section+1;
        }
    }
    return QVariant();
}

void TableSharedModel::sharedData(TableModel *refModel,int rowCount)
{
    this->beginResetModel();
    if(rowCount > refModel->rowCount() || m_columns.size() > refModel->columnCount())
        return;

    m_sharedData.resize(rowCount);


    for(int i = 0; i<rowCount; i++)
    {
        m_sharedData[i] = refModel->m_data[i].data();
    }

    this->endResetModel();
}

void TableSharedModel::setColumnList(const QList<int> &columnList)
{
    m_columns = columnList;
}

void TableSharedModel::sharedHeaderData(TableModel *refModel)
{
    m_sharedHeaders = refModel->m_horizontalHeaderData.data();
}
