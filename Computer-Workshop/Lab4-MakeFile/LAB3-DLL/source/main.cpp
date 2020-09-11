#include <iostream>

#include "load.h"

constexpr auto N = 57;

constexpr auto N1 = 5;
constexpr auto N2 = 7;

constexpr auto X = -50;
constexpr auto Y = 50;

constexpr auto NUM = 3;

#ifdef WIN32
#define LIBMATRIX "matrix.dll"
#define LIBARRAY "myarray.dll"
#else
#define LIBMATRIX "libmatrix.so"
#define LIBARRAY "libmyarray.so"
#endif

int main()
{
    std::cout << "Matrix(1) or Array(2)?" << std::endl;

    int answer = 0;
    void* library = nullptr;
    std::cin >> answer;
    if(answer == 1)
    {
        int** matrix;
        matrix = new int*[N1];
        for(int i = 0; i < N1; i++)
        {
            matrix[i] = new int[N2];
        }
        

        library = loadDLL(LIBMATRIX);

        while(answer != 3)
        {
            std::cout << "1. Fill Matrix\n" <<
            "2. Count\n"  << 
            "3. Exit" << std::endl;
            std::cin >> answer;
            if(answer == 1)
            {
                auto function = loadFunction<void (*)(int**,int,int,int,int)>(library, "fillRandomMatrix");
                if(function != nullptr) 
                {
                    function(matrix, N1, N2,X,Y);
                }
            }
            else if(answer == 2)
            {
                auto function = loadFunction<int (*)(int**,int,int,int)>(library, "countMatrix");
                if(function != nullptr)
                {
                    std::cout << function(matrix, N1, N2, NUM) << std::endl;
                }
                
            }

        }

        for(int i=0; i<N1; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        
    }
    else if(answer == 2)
    {
        int* array = new int[N];

        library = loadDLL(LIBARRAY);

        while(answer != 3)
        {
            std::cout << "1. Fill Array\n" <<
            "2. Count\n"  << 
            "3. Exit" << std::endl;
            std::cin >> answer;
            if(answer == 1)
            {
                auto function = loadFunction<void (*)(int *,int,int,int)>(library, "fillRandomArray");
                if(function != nullptr) 
                {
                    function(array, N,X,Y);
                }  
            }
            else if(answer == 2)
            {
                auto function = loadFunction<int (*)(int*,int,int)>(library, "countArray");
                if(function != nullptr)
                {
                    std::cout << function(array, N, NUM) << std::endl;
                }
                
            }
        }

        delete[] array;
    }

    closeDLL(library);


    return 0;
}