#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>
#include <QMessageBox>



class Exception : public QException
{
private:
    QString m_errorMessage;
    int m_state;
public:
    Exception(const QString& errorMessage = QString(),const int& state = Warning);
    explicit Exception(const int& state = Warning);

    QString message() const;
    int state() const;


    static const int Warning = 100;
    static const int Critical = 101;

};

#endif // EXCEPTION_H
