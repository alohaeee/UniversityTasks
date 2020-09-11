#include "ioFunc.h"

std::string inputStr()
{
    std::string temp;
    std::getline(std::cin,temp);
    return temp;
}

void outputStr(std::string str)
{
    std::cout << str << std::endl;
}
