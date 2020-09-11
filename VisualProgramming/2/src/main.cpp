#include "mainwindow.h"

#include "Core/customuiloader.h"
#include <QApplication>
#include <QDebug>

#include <QAbstractItemView>
#include <QFile>
#include <QGridLayout>
#include <QMetaObject>
#include <QMetaProperty>
#include <QTextStream>
#include <QTreeWidget>
#include <filesystem>

#include <QObject>

void printer(int level, const QObjectList &obj)
{
    if (obj.size())
    {
        QString r = "";
        for (int i = 0; i < level; i++)
        {
            r += ' ';
        }
        qDebug() << r << obj;

        for (auto &c : obj)
        {
            printer(level + 1, c->children());
        }
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString content;
    std::unique_ptr<QMainWindow *> ptr;
    try
    {

        content = OpenFileAndReadAll("windowFrom1Laba.ui");
        CustomUILoader loader(std::move(content));
        auto widget = loader.VisitForWidget();
        auto w = dynamic_cast<QMainWindow *>(widget);

        w->show();
        qDebug() << w->children();
        // printer(0, w->children());

        //        auto widget2 = loader.VisitForWidget();
        //        w->setMenuBar(dynamic_cast<QMenuBar *>(widget2));

        //        auto widget3 = loader.VisitForWidget();
        //        w->setStatusBar(dynamic_cast<QStatusBar *>(widget3));

        //        auto widget3 = loader.Visit();

        // printer(0, widget2->children());
    }
    catch (std::invalid_argument &e)
    {
        qFatal(e.what());
        return -1;
    }

    catch (std::exception &e)
    {
        qFatal(e.what());
        return -1;
    }

    //    MainWindow w;
    //    w.show();
    return a.exec();
}
