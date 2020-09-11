#ifndef TABLEGROUPMODEL_H
#define TABLEGROUPMODEL_H


#include <QAbstractTableModel>
#include <QVector>
#include <QString>
#include "tablesharedmodel.h"


class TableGroupModel : public QAbstractTableModel
{
private:
    int m_rowCount;
    int m_columnCount;

    int m_groupPeopleCount;


    QVector<QVector<QString>> m_groupLabels;




    QVector<QString*> m_dataGroup;
    QVector<int> m_verticalHeaders;
    QString* m_sharedHeaders;

    const QVector<QString>& createGroupLine(int index);
public:


    TableGroupModel(QObject* parent = nullptr, int groupPeopleCount = 30);


    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void sharedData(TableModel *refModel,int groupPeopleCount, int minPoint);
    void sharedHeaderData(TableModel *refModel);
    void setGroups(int groupCount);
    void setColumnCount(int columnCount);
    int groupPeopleCount() const;
};

#endif // TABLEGROUPMODEL_H
