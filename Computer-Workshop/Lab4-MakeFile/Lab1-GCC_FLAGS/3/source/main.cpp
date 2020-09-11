#include <iostream>

#include "funArray2.h"
#include "ioArray.h"

auto N = 15;

int main()
{
    int* array = new int(N);
    inputArray(array, N);
    int result = eraseFirstNegative(array, N);
    std::cout << (result == 0 ? "Not found" : "First negative: " + std::to_string(result)) << std::endl;
    outputArray(array, N);
    delete array;
    return 0;
}