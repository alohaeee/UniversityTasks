#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

#include "writeworker.h"
#include "countworker.h"
#include "dialogshow.h"


QMutex* MainWindow::s_readWriteLocker = new QMutex();

QWaitCondition* MainWindow::s_waitCondition = new QWaitCondition();
QQueue<int>* MainWindow::s_queueData = new QQueue<int>();
bool MainWindow::waitForData = true;

QMutex *MainWindow::mutexLocker()
{
    return s_readWriteLocker;
}

QWaitCondition *MainWindow::waitCondition()
{
    return s_waitCondition;
}

QQueue<int>* MainWindow::queueData()
{
    return s_queueData;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_writeWorker = new WriteWorker();
    connect(m_writeWorker, &WriteWorker::writeNumber, this, &MainWindow::onWriteNumber,Qt::QueuedConnection);

    m_countWorker = new CountWorker();
    connect(m_countWorker, &CountWorker::countNumber, this, &MainWindow::onCountNumber,Qt::QueuedConnection);


    ui->buttonStartGeneration->setEnabled(false);
    ui->buttonStopGeneration->setEnabled(false);
    ui->buttonStopCount->setEnabled(false);

    connect(ui->buttonStartGeneration, &QPushButton::clicked, this, &MainWindow::onEnterCount);

//    connect(this, &MainWindow::destroyed, this, &MainWindow::closeEvent);

    connect(ui->actionOpen, &QAction::triggered,this, &MainWindow::onOpenFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_writeWorker;
    delete m_countWorker;

    delete s_readWriteLocker;
    delete s_queueData;
    delete s_waitCondition;
}


void MainWindow::onOpenFile()
{
    m_fileName = QFileDialog::getOpenFileName(this, "Открыть файл", nullptr,"Text files (*.txt)");
    if(!m_fileName.isNull())
    {


        if(!ui->buttonStartGeneration->isEnabled())
            ui->buttonStartGeneration->setEnabled(true);
    }
}


void MainWindow::onStartGeneration(int count)
{
    if(!m_writeWorker->openFile(m_fileName) || !m_countWorker->openFile(m_fileName))
    {
        QMessageBox::warning(this, "Warning!", "Файл не был открыт!");
        return;
    }


    m_writeWorker->setCountNumbers(count);
    queueData()->clear();

    QThread* threadOut = new QThread();
    m_writeWorker->moveToThread(threadOut);

    connect(threadOut, &QThread::started, m_writeWorker, &WriteWorker::generationFile);

    connect(m_writeWorker, &WriteWorker::finishedGeneration, threadOut, &QThread::quit);
    connect(threadOut, &QThread::finished, threadOut, &QThread::deleteLater);
    connect(ui->buttonStopGeneration, &QPushButton::clicked, threadOut, &QThread::requestInterruption);
    connect(threadOut, &QThread::finished, this, &MainWindow::disableGenerationButton);


    connect(m_writeWorker, &WriteWorker::finishedGeneration, this, &MainWindow::stopWaiting,Qt::DirectConnection);



    QThread* threadIn = new QThread();
    m_countWorker->moveToThread(threadIn);

    connect(threadIn, &QThread::started, m_countWorker, &CountWorker::countFile);

    connect(m_countWorker, &CountWorker::finishedCount, threadIn, &QThread::quit);

    connect(threadIn, &QThread::finished, threadIn, &QThread::deleteLater);
    connect(threadIn, &QThread::finished, this, &MainWindow::disableCountButton);
    connect(ui->buttonStopCount, &QPushButton::clicked, threadIn, &QThread::requestInterruption);


    connect(threadIn, &QThread::finished, this, &MainWindow::onCloseThread);
    connect(threadOut, &QThread::finished, this, &MainWindow::onCloseThread);
    m_countRunningThreads = 2;

    threadOut->start(QThread::Priority::NormalPriority);
    threadIn->start(QThread::Priority::NormalPriority);

    ui->buttonStopGeneration->setEnabled(true);
    ui->buttonStopCount->setEnabled(true);
    ui->buttonStartGeneration->setEnabled(false);

}



void MainWindow::onEnterCount()
{
    DialogShow dialogShow(this,1,std::numeric_limits<int>::max());

    connect(&dialogShow,&DialogShow::showed,this,&MainWindow::onStartGeneration);


    dialogShow.setLabel("Введите кол-во чисел: ");
    dialogShow.setModal(true);
    dialogShow.exec();

    disconnect(&dialogShow,&DialogShow::showed,this,&MainWindow::onStartGeneration);

}

void MainWindow::disableGenerationButton()
{
     ui->buttonStopGeneration->setEnabled(false);
}

void MainWindow::disableCountButton()
{
    ui->buttonStopCount->setEnabled(false);
}

void MainWindow::onCountNumber(int count,const QTime& startTime,double average, double standart)
{
    ui->labelCount->setText("Время: " + QString::number(startTime.elapsed()) + " мс\nКоличество чисел:" + QString::number(count) +
                            "\nСреднее отклонение = " + QString::number(average,'f',2) +
                            "\nСреднеквадратичное = " + QString::number(standart, 'f', 4));
}

void MainWindow::stopWaiting()
{
    waitForData = false;
    MainWindow::waitCondition()->wakeAll();
}

void MainWindow::onCloseThread()
{
    m_countRunningThreads--;
    if(!m_countRunningThreads)
        ui->buttonStartGeneration->setEnabled(true);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    auto writeThread =  m_writeWorker->thread();
    auto countThread = m_countWorker->thread();
    if(writeThread != QApplication::instance()->thread())
    {
        if(writeThread->isRunning())
        {
            writeThread->requestInterruption();
        }
    }
    if(countThread != QApplication::instance()->thread())
    {

        if(countThread->isRunning())
        {

            countThread->requestInterruption();
        }

    }
    event->accept();
}


void MainWindow::onWriteNumber(int count, const QTime& startTime)
{
    ui->labelGeneration->setText("Время: " + QString::number(startTime.elapsed()) + " мс\nКоличество чисел:" + QString::number(count));
}


