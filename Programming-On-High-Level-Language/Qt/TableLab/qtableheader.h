#ifndef QTABLEHEADER_H
#define QTABLEHEADER_H

#include <QHeaderView>
#include <QObject>

class QTableHeader : QHeaderView
{
public:
    explicit QTableHeader(QWidget* parent = nullptr);
};

#endif // QTABLEHEADER_H
