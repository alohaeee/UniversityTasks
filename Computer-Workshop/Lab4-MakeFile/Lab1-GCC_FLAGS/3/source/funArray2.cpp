#include "funArray2.h"
#include <malloc.h>

int eraseFirstNegative(int* arr, int& N)
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