#ifndef COUNTERWORKER_
#define COUNTERWORKER_H

#include <QObject>
#include <QFile>
#include <QThread>
#include <QTime>


class CountWorker : public QObject
{
    Q_OBJECT
private:

    QFile m_fileIn;


    bool m_waitForData=true;
public:
    CountWorker(QObject* parent = nullptr);
    ~CountWorker();


    void readFromFile();

    bool openFile(const QString& fileName);


signals:
    void finishedCount();
    void countNumber(int count,const QTime& startTime,double average, double standart);
public slots:
    void countFile();
    void stopWaiting();
};

#endif // COUNTERWORKER_H
