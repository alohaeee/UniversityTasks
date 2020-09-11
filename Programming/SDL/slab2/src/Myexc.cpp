#include "Myexc.h"


Myexception::Myexception(string errName, int errValue)
{
    this->errName = errName;
    this->errValue = errValue;
}

int Myexception::GetValue(void) { return errValue; }

string Myexception::GetErrM(void) { return errName; }