#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setProperty("geometry", {0, 4, 2, 1});
}

MainWindow::~MainWindow()
{
    delete ui;
}
