#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QDebug>
#include <QTime>

#include "DishTableModel.h"
#include "FinishModel.h"
#include "OrderModel.h"
#include "QueueModel.h"
#include "Simulator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Симулятор фуд трака");
    Simulator::Init();
    {
        Simulator::RandDishLists(50);

        auto tab = new QTabWidget();
        ui->dishListDock->setWidget(tab);
        tab->setLayout(new QGridLayout());
        for (int i = 0; i < Dish::Size; i++)
        {
            auto view = new QTableView();
            tab->addTab(view, Dish::typeToString(Dish::DishType(i)));
            view->setModel(new DishTableModel(Dish::DishType(i)));
            view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }

    QueueModel *queueModel = new QueueModel();

    for (int i = 0; i < Simulator::clientsOnStart; i++)
    {
        queueModel->AddClient(Simulator::RandClient());
    }

    ui->queueView->setModel(queueModel);
    ui->queueView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->queueView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    auto tableViewSet = [](QTableView *view) {
        view->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        view->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    };

    OrderModel *orderModel = new OrderModel();
    ui->orderView->setModel(orderModel);
    tableViewSet(ui->orderView);

    FinishModel *finishModel = new FinishModel();
    ui->finishView->setModel(finishModel);
    tableViewSet(ui->finishView);

    FinishModel *notWaitingModel = new FinishModel();
    ui->notWaitingView->setModel(notWaitingModel);
    tableViewSet(ui->notWaitingView);

    connect(&timer, &QTimer::timeout, [queueModel, notWaitingModel]() {
        queueModel->OnChangeTime(*notWaitingModel);
        if (Simulator::IsTimeToCreateNewClient())
        {
            queueModel->AddClient(Simulator::RandClient());
        }
    });
    connect(&timer, &QTimer::timeout, [orderModel, queueModel, finishModel, notWaitingModel]() {
        orderModel->OnChangeTime(*finishModel, *notWaitingModel);
        while (orderModel->rowCount() < Simulator::clientOrderInSameTime && queueModel->rowCount() > 0)
        {
            orderModel->CreateOrderWithClient(queueModel->PopUpClient());
        }
    });

    timer.start(Simulator::secTime);

    // connections
    connect(ui->timerSlider, &QSlider::valueChanged, [this](int value) {
        Simulator::secTime = value;
        timer.stop();
        timer.start(Simulator::secTime);
    });
    connect(ui->restartButton, &QPushButton::pressed, [finishModel, queueModel, notWaitingModel, orderModel, this]() {
        timer.stop();
        queueModel->Reset();
        orderModel->Reset();
        finishModel->Reset();
        notWaitingModel->Reset();

        Simulator::clinetId = 0;
        Simulator::orderId = 0;

        for (int i = 0; i < Simulator::clientsOnStart; i++)
        {
            queueModel->AddClient(Simulator::RandClient());
        }
        timer.start(Simulator::secTime);
    });
    auto isLastNum = [](const QString &str) {
        auto back = str.back();
        if (back >= '0' && back <= '9')
        {
            return true;
        }
        return false;
    };
    auto notApply = [](QLineEdit *edit) {
        QString textRef = edit->text();
        textRef.resize(textRef.size() - 1);
        edit->setText(textRef);
    };
    connect(ui->countLine, &QLineEdit::textChanged, [&](const QString &text) {
        if (text.size() && !isLastNum(text))
        {
            notApply(ui->countLine);
        }
    });
    connect(ui->countLine, &QLineEdit::editingFinished, [&]() {
        auto text = ui->countLine->text();
        if (text.size())
        {
            auto num = ui->startInQueueLine->text().toInt();
            if (num > 99)
                num = 99;
            Simulator::clientOrderInSameTime = num;
        }
    });
    connect(ui->chanceLine, &QLineEdit::textChanged, [&](const QString &text) {
        if (text.size() && !isLastNum(text))
        {
            notApply(ui->chanceLine);
        }
    });
    connect(ui->chanceLine, &QLineEdit::editingFinished, [&]() {
        auto text = ui->chanceLine->text();
        if (text.size())
        {
            auto chance = ui->chanceLine->text().toInt();
            if (chance > 99)
                chance = 99;
            Simulator::chanceOfNewClient = chance;
        }
    });
    connect(ui->startInQueueLine, &QLineEdit::textChanged, [&](const QString &text) {
        if (text.size() && !isLastNum(text))
        {
            notApply(ui->startInQueueLine);
        }
    });
    connect(ui->startInQueueLine, &QLineEdit::editingFinished, [&]() {
        auto text = ui->startInQueueLine->text();
        if (text.size())
        {
            auto num = ui->startInQueueLine->text().toInt();
            if (num > 99)
                num = 99;
            Simulator::clientsOnStart = num;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
