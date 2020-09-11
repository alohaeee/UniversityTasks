#include "MainWindow.h"

#include <QApplication>

#include <chrono>
#include <ctime>
#include <iostream>

#include <QDebug>
#include <QTime>

int main(int argc, char *argv[])
{
    //    QTime t = QTime::currentTime();
    //    QTime d = QTime::currentTime();
    //    auto v = QTime::fromString("10.23", "m.s");
    //    qDebug() << QTime().currentTime();
    //    qDebug() << v;
    //    auto ff = std::chrono::system_clock::now();

    //    auto vv = ff + std::chrono::system_clock::now();
    //    vv.count();
    //    QTime t;
    //    t.start();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
