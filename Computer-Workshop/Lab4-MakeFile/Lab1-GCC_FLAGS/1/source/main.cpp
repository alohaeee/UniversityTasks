#include <iostream>

int main()
{
    int x;
    std::cout << "Input natural nubmer: ";
    std::cin >> x;
    while(std::cin.fail() || x < 0)
    {
        std::cout << "Wrong input!" << std::endl;
        std::cin.clear();
        std::cin.ignore(255, '\n');
        std::cout << "Input natural nubmer: ";
        std::cin >> x;
    }
    int temp = x / 2 + 1;
    std::cout << "List of natural dividers:" << std::endl;
    for(int i=1; i<temp;i++)
    {
        if(x%i == 0)
            std::cout << i << std::endl;
    }
    std::cout << x << std::endl;
    return 0;
}