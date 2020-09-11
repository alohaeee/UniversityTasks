#ifndef TABLEHIGHESTMODEL_H
#define TABLEHIGHESTMODEL_H

#include <QAbstractTableModel>
#include <QVector>


class TableModel;

class TableSharedModel : public QAbstractTableModel
{
protected:
    QVector<QString*> m_sharedData;
    QString* m_sharedHeaders;


    QList<int> m_columns;
public:

    TableSharedModel(QObject* parent);

    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex & = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual void sharedData(TableModel *refModel,int rowCount);
    void setColumnList(const QList<int>& columnList);
    void sharedHeaderData(TableModel *refModel);

};
#endif // TABLEHIGHESTMODEL_H
