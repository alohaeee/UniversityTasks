#ifndef WRITERWORKER_H
#define WRITERWORKER_H

#include <QObject>
#include <QFile>
#include <QThread>
#include <QTime>



class WriteWorker : public QObject
{
    Q_OBJECT
private:
    int m_countNumbers;

    QFile m_fileOut;
public:
    WriteWorker(QObject* parent = nullptr);
    ~WriteWorker();

    int countNumbers() const;


    QFile& fileOut();
    bool openFile(const QString& fileName);

signals:
    void finishedGeneration();
    void writeNumber(int m_countWorker, const QTime& startTime);
    void succesWrite();

public slots:
    void generationFile();
    void setCountNumbers(int countNumbers);

};

#endif // WRITERWORKER_H
