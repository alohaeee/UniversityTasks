#include "MainWindow.h"

#include <QApplication>

#include <chrono>
#include <ctime>
#include <iostream>

#include <QDebug>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
