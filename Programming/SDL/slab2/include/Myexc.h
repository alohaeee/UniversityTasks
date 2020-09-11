using namespace std;
#include <exception>
#include <string>

class Myexception :public exception
{
private:
    string errName;
    int errValue;
public:
    Myexception(string errName, int errValue);
    int GetValue(void);
    string GetErrM(void);
};
