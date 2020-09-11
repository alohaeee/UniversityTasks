#include <iostream>

int main()
{
    int n;
    std::cout << "Input n: ";
    std::cin >> n;
    if(n < 1 || std::cin.fail()) return -1;
    int fib1 = 1;
    int fib2 = 2;
    while(fib2 < n)
    {
        int temp = fib2;
        fib2 = fib1 + fib2;
        fib1 = temp;
    }
    int result = n-fib1 > fib2 - n ? fib2 : fib1;
    std::cout << result << std::endl;
    return 0;
}