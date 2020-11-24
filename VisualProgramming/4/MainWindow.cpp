#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QColor>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene();
    ui->graphicsView->setScene(m_scene);

    CreateText();
    CreateCapibara();
    auto spinBox = CreateSpinBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}
