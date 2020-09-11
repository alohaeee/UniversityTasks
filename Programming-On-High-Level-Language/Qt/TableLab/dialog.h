#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
    Ui::dialog *ui;

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void onShow();
    void onCancel();



};

#endif // DIALOG_H
