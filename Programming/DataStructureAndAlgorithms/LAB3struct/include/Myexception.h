#pragma once
#include <exception>
#include <string>

class Myexception : public std::exception
{
private:
    std::string ErrName;
    int ErrVal;
public:
    Myexception(const char* name, const int val) : ErrName(name), ErrVal(val) {}
    std::string GetErr()
    {
        return ErrName;
    }
    int GetVal()
    {
        return ErrVal;
    }
    
};