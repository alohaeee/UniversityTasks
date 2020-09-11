#include "matrix.h"
#include <random>
#include <iostream>

void fillRandomMatrix(int** matrix, int N1, int N2,int x, int y)
{
    std::mt19937 mt_seed(time(NULL));
    std::uniform_int_distribution<int> uid(x,y);

    for(int i=0; i<N1; i++)
    {
        for(int j=0; j<N2; j++)
        {
            matrix[i][j] = uid(mt_seed);
            printf("%6i\t", matrix[i][j]);
        } 
        std::cout << std::endl;
    }
}

int countMatrix(int** matrix, int N1, int N2, int num)
{
    int counter = 0;
    for(int i=0; i<N1; i++)
    {
        for(int j=0; j<N2; j++)
        {
            if(matrix[i][j]%num == 0) 
            {
                counter++;
            }
        }
    }
    return counter;
}