#include "exception.h"




Exception::Exception(const QString& errorMessage,const int& state) : m_errorMessage(errorMessage), m_state(state)
{

}

Exception::Exception(const int &state) : m_errorMessage(QString()), m_state(state)
{

}

QString Exception::message() const
{
    return m_errorMessage;
}
int Exception::state() const
{
    return m_state;
}




