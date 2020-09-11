#include "countworker.h"

#include <QApplication>
#include <QVector>
#include <QDebug>

#include <mainwindow.h>

void CountWorker::readFromFile()
{

}

CountWorker::CountWorker(QObject *parent) : QObject(parent)
{

}

CountWorker::~CountWorker()
{
    if(m_fileIn.isOpen())
        m_fileIn.close();
}


bool CountWorker::openFile(const QString &fileName)
{
    if(m_fileIn.isOpen())
        m_fileIn.close();

    m_fileIn.setFileName(fileName);

    return m_fileIn.open(QIODevice::ReadOnly);
}

void CountWorker::countFile()
{
    MainWindow::waitForData = true;
    int count = 0;
    double sumError = 0;
    double standartError = 0;
    double averageError = 0;
    QString line;
    QTime currentTime = QTime::currentTime();

    currentTime.start();


    forever
    {
        if(this->thread()->isInterruptionRequested())
        {
            break;
        }
        MainWindow::mutexLocker()->lock();
        if(MainWindow::queueData()->isEmpty())
        {
            if(MainWindow::waitForData)
            {

                MainWindow::waitCondition()->wait(MainWindow::mutexLocker());
                MainWindow::mutexLocker()->unlock();
                continue;
            }   
            else
            {
                MainWindow::mutexLocker()->unlock();
                break;
            }

        }
        else
        {
            auto data = MainWindow::queueData()->dequeue();

            line = m_fileIn.readLine();

            MainWindow::mutexLocker()->unlock();
            //line.chop(line.size()-1);
            int num = line.toInt();
            if(data != num)
            {
                qDebug() << data << " ade " << num;
            }

            count++;
            sumError += num;

            double lastAverage = averageError;
            averageError = sumError/count;

            standartError += ((num - averageError)*(num - lastAverage)-standartError*standartError)/count;
            //standartError /= count;

            //standartError = pow(standartError,0.5);

            if(count%1000 == 0)
                countNumber(count, currentTime, averageError, standartError);


         }
    }
    //qDebug()
    countNumber(count,currentTime,averageError, standartError);


    moveToThread(QApplication::instance()->thread());

    finishedCount();
}


void CountWorker::stopWaiting()
{
    m_waitForData = false;
}
