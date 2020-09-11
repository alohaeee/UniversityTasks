#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    auto p = property("geometry").type();

    //    auto g = QVariant(p);
    //    g.value<p>
    //    g.create(p, (void*)({1,2,3,4}));
    // g.create(p,QMetaType::create({1,2,3,4});

    // g.setValue<p>({1,2,3,4});
    // setProperty("geometry", setValue());
    // QVariant::fromValue({1,2,3,4});
}

MainWindow::~MainWindow()
{
    delete ui;
}
