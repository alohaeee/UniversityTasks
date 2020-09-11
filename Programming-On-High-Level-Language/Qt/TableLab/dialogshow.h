#ifndef DIALOGSHOW_H
#define DIALOGSHOW_H

#include <QDialog>

namespace Ui {
class DialogShow;
}

class DialogShow : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogShow *ui;
    int m_bottom;
    int m_top;

public:
    DialogShow(QWidget *parent = nullptr, int bottom = 0, int top = 0);
    ~DialogShow();

    void setLabel(const QString& text);
signals:
    void showed(int m_countWorker);
public slots:
    void onShow();
    void onCancel();
    void onLineEditChange(const QString &text);

};

#endif // DIALOGSHOW_H
