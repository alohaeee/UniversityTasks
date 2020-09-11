#include "funArray.h"
#include <malloc.h>

int countSum(int* arr, int N)
{
    int sum = 0;
    for(int i = 0; i < N; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int deleteFirstNegative(int* arr, int& N)
{
    for(int i = 0 ; i < N; i++)
    {
        if(arr[i] < 0)
        {
            int re = arr[i];
            for(int j=N-1;  j > i; j--)
                arr[j-1] = arr[j];
            N--;
            arr = (int*)realloc(arr,sizeof(int)*(N));
            if(arr == nullptr) return -1;
            return re;
        }
    }
    return 0;
}