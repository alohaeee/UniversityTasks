#include "writeworker.h"


#include <QDebug>
#include <random>
#include <QApplication>
#include "mainwindow.h"
#include <QTextStream>


int WriteWorker::countNumbers() const
{
    return m_countNumbers;
}

void WriteWorker::setCountNumbers(int countNumbers)
{
    m_countNumbers = countNumbers;
}

QFile &WriteWorker::fileOut()
{
    return m_fileOut;
}

bool WriteWorker::openFile(const QString &fileName)
{
    if(m_fileOut.isOpen())
        m_fileOut.close();

    m_fileOut.setFileName(fileName);

    return m_fileOut.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
}

WriteWorker::WriteWorker(QObject *parent) : QObject(parent)
{

}

WriteWorker::~WriteWorker()
{
    if(m_fileOut.isOpen())
        m_fileOut.close();
}

void WriteWorker::generationFile()
{
    std::random_device rDevice;
    std::mt19937 rGenerator(rDevice());
    std::normal_distribution<double> distribution{5,2};

    QTextStream textStream(&m_fileOut);

    int i;
    QTime currentTime = QTime::currentTime();
    currentTime.start();
    for(i = 0 ; i < m_countNumbers; i++)
    {
        if(this->thread()->isInterruptionRequested())
        {
            break;
        }
        int num = static_cast<int>(std::round((distribution(rGenerator))));

        MainWindow::mutexLocker()->lock();

        textStream << QString::number(num) + "\n";
        textStream.flush();

        MainWindow::queueData()->enqueue(num);
        MainWindow::waitCondition()->wakeAll();
        MainWindow::mutexLocker()->unlock();

        if(i % 1000 == 0)
            writeNumber(i , currentTime);

    }
    writeNumber(i, currentTime);

    moveToThread(QApplication::instance()->thread());
    finishedGeneration();
}


