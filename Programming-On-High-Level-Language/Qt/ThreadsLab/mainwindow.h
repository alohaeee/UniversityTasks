#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QFile>
#include <QThread>
#include <QTime>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QReadWriteLock>

class WriteWorker;
class CountWorker;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    CountWorker* m_countWorker;
    WriteWorker* m_writeWorker;

    static QMutex* s_readWriteLocker;
    static QWaitCondition* s_waitCondition;
    static QQueue<int>* s_queueData;


    QString m_fileName;

    int m_countRunningThreads = 0;


protected:
    void closeEvent( QCloseEvent *__e );

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QMutex *mutexLocker();

    static QWaitCondition *waitCondition();

    static QQueue<int>* queueData();
    static bool waitForData;

signals:




public slots:
    void onOpenFile();
    void onStartGeneration(int m_countWorker);

    void onEnterCount();

    void disableGenerationButton();
    void disableCountButton();

    void onWriteNumber(int num, const QTime& startTime);
    void onCountNumber(int count,const QTime& startTime,double average, double standart);
    static void stopWaiting();

    void onCloseThread();



};
#endif // MAINWINDOW_H
