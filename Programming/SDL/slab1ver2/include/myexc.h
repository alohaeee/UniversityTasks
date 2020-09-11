#include <exception>
#include <string>



class Myexception : public std::exception
{
private:
    std::string errName;
    int errValue;
public:
    Myexception(std::string mess, int i)
    {
        this->errName=mess;
        this->errValue=i;
    };
    int GetValue(void) { return errValue; }
    std::string GetErrM(void) { return errName; }
};