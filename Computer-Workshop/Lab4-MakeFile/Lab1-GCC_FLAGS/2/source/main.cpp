#include <iostream>

#include "ioArray.h"
#include "funArray.h"


const constexpr auto N = 15;

int main()
{
    int array[N];
    inputArrayBorders(array, N);
    std::cout << "SUM = " << countSum(array, N) << std::endl;
    return 0;
}