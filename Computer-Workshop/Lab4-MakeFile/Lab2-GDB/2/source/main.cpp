#include <iostream>
#include <string>
#include <vector>

std::string inputStr()
{
    std::string str;
    std::getline(std::cin, str);

    std::cin.clear();

    return str;
}

void outputStr(std::string str)
{
    std::cout << str << std::endl;
}

int main()
{
    std::cout << "Input first string: ";
    std::string str1 = inputStr();
    
    std::cout << "Input second string: ";
    std::string str2 = inputStr();

    if(str1.back()!=' ') str1.push_back(' ');
    str1 += str2;
    if(str1.back()!='.') str1 += '.'; 

    outputStr(str1);
    return 0;
}