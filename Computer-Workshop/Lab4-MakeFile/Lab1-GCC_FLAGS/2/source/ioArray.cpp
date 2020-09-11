#include "ioArray.h"
#include <iostream>

void inputArray(int *arr, int N)
{
    for(int i=0; i < N; i++)
    {
        std::cout << i+1 << ": ";
        std::cin >> arr[i];
    }
}

void inputArrayBorders(int *arr, int N)
{
    int X=0, Y=10;
    std::cout << "Input borders:" << std::endl;
    std::cout << "X = "; std::cin >> X;
    std::cout << "Y = "; std::cin >> Y;
    for(int i=0; i < N; i++)
    {
        std::cout << i+1 << ": ";
        int temp;
        std::cin >> temp;
        while(std::cin.fail() || temp < X || temp > Y)
        {
            std::cin.clear();
            std::cin.ignore(255, '\n');
            std::cin >> temp;
        }
        arr[i] = temp;
    }
}

void outputArray(int *arr, int N)
{
    for(int i=0; i < N ; i++)
    {
        std::cout << "Array[" << i << "] = " << arr[i] << std::endl;
    }
}