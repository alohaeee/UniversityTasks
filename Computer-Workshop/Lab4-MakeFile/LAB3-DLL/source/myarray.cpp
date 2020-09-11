#include "myarray.h"
#include <random>
#include <iostream>




void fillRandomArray(int* array, int N,int x, int y)
{
    std::mt19937 mt_seed(time(NULL));
    std::uniform_int_distribution<int> uid(x,y);

    for(int i=0; i<N; i++)
    {
        array[i] = uid(mt_seed);
        std::cout << array[i] << "  ";
    }
    std::cout << std::endl;
}


int countArray(int* array, int N, int num)
{
    int counter = 0;
    for(int i=0; i<N; i++)
    {
        if(array[i] % num == 0)
        {
            counter++;
        }
    }
    return counter;
}