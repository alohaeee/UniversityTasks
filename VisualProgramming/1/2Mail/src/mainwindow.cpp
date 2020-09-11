#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CreateMenu();

    this->layout = new QGridLayout(this);
    ui->centralwidget->setLayout(layout);

    // this->layout->

    CreateTree();
    CreateList();
    CreateGroupBox();
    CreateTextEdit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateMenu()
{
    auto bar = ui->menubar;

    auto menu = bar->addMenu("Меню");

    menu->addAction("Прочитанные");
    menu->addAction("Непрочитанные");
    menu->addAction("Черновики");

    menu->addSeparator();
    auto exitAction = menu->addAction("Выход");

    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::CreateTree()
{
    auto treeWidget = new QTreeWidget();
    this->layout->addWidget(treeWidget, 0, 0, 3, 1);

    treeWidget->setColumnCount(1);
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);

    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
    {
        items.append(new QTreeWidgetItem(QStringList(QString("pochta%1@mail").arg(i))));

        QList<QTreeWidgetItem *> menus;
        menus.append(new QTreeWidgetItem(QStringList("Работа")));
        menus.append(new QTreeWidgetItem(QStringList("Вуз")));

        if (i % 3 == 0)
        {
            menus.append(new QTreeWidgetItem(QStringList("Бизнес")));
        }

        items.back()->addChildren(std::move(menus));
    }
    treeWidget->insertTopLevelItems(0, items);
}

void MainWindow::CreateList()
{
    auto listWidget = new QListWidget();
    this->layout->addWidget(listWidget, 0, 1);

    listWidget->addItem("Сообщение");
    for (int i = 0; i < 200; i++)
    {
        listWidget->addItem("Спам");
    }
}

void MainWindow::CreateTextEdit()
{
    auto textEdit = new QTextEdit();
    this->layout->addWidget(textEdit, 2, 1);

    textEdit->setPlaceholderText("Введите текст");
}

void MainWindow::CreateGroupBox()
{
    auto groupBox = new QGroupBox("Управление сообщениями");
    this->layout->addWidget(groupBox, 1, 1);

    QLayout *layout = new QHBoxLayout(groupBox);
    groupBox->setLayout(layout);

    layout->addWidget(new QPushButton("Отправить"));
    layout->addWidget(new QPushButton("Удалить"));
    layout->addWidget(new QPushButton("Спам"));
}
