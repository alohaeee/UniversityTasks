#include "dialogshow.h"
#include "ui_dialogshow.h"

DialogShow::DialogShow(QWidget *parent, int bottom, int top) :
    QDialog(parent), ui(new Ui::DialogShow),
    m_bottom(bottom), m_top(top)
{
    ui->setupUi(this);

    ui->errorLabel->setStyleSheet("QLabel { color: red; }");
    ui->buttonShow->setDisabled(true);

    connect(ui->buttonShow, &QPushButton::clicked, this, &DialogShow::onShow);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &DialogShow::onCancel);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &DialogShow::onLineEditChange);
}

DialogShow::~DialogShow()
{
    delete ui;
}

void DialogShow::setLabel(const QString &text)
{
    ui->label->setText(text);
}

void DialogShow::onShow()
{
    this->close();
    showed(ui->lineEdit->text().toInt());
}

void DialogShow::onCancel()
{
    this->close();
}

void DialogShow::onLineEditChange(const QString &text)
{
    if(text.contains(QRegExp("(\\D)")))
    {
        ui->errorLabel->setText("Edit line contains may contain only digits");
        ui->buttonShow->setDisabled(true);
        return;
    }

    bool isOkay = true;
    int value = text.toInt(&isOkay);
    if(!isOkay && !text.length())
    {
        ui->errorLabel->setText("Can't parse to number");
        ui->buttonShow->setDisabled(true);
        return;
    }
    else if(value <= m_bottom)
    {
        ui->errorLabel->setText("Value must be bigger then: " + QString(m_bottom));
        ui->buttonShow->setDisabled(true);
        return;
    }
    else if(value >= m_top)
    {
        ui->errorLabel->setText("Value must be less then: " + QString(m_top));
        ui->buttonShow->setDisabled(true);
        return;
    }

    ui->errorLabel->setText("");
    ui->buttonShow->setDisabled(false);
}
