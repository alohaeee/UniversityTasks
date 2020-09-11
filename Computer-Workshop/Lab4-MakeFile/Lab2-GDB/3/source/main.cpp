#include "ioFunc.h"
#include <vector>

int main()
{
    std::cout << "Input line: " << std::endl;
    std::string str = inputStr();
    std::vector<std::string> result;
    {
        std::string temp;
        std::string parsingTask = ".,:;!? ";
        for(auto &c : str)
        {
            if(parsingTask.find(c) != parsingTask.npos)
            {
                if(temp.empty()) continue;
                result.push_back(temp);
                temp.clear();
            }
            else temp.push_back(c);
        }
    }
    std::cout << "Words:" << std::endl;
    for(auto &s : result)
    {
        outputStr(s);
    }
    return 0;
}