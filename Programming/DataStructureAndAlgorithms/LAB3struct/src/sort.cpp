#include "sort.h"
#include <vector>
#include <algorithm>
#include <random>
size_t SORT::Sort_test::counter_key;
size_t SORT::Sort_test::counter_index;

void SORT::Sort_test::init(int left, int right)
{
    try{
        std::mt19937 rand_mer(time(NULL));
        std::uniform_int_distribution<int> uid(left,right);

        std::ofstream temp_stream(name_un);
        if(temp_stream.fail()) throw Myexception("Could't create file!", 1);

        std::vector<int> uns;
        std::uniform_int_distribution<int> uid_chance(1,5);
        for(int i=0; i<N;i++)
        {   
            int temp;
            if(uid_chance(rand_mer) == 1){
                std::uniform_int_distribution<int> uid_repeat(0,i-1);
                temp = uns[uid_repeat(rand_mer)];
            }
            else
                temp=uid(rand_mer);
                
            temp_stream.write((char*) &temp, sizeof(int));
            uns.push_back(temp);
        }
        temp_stream.close();

        temp_stream.open(name_re);
        if(temp_stream.fail()) throw Myexception("Could't create file!", 1);
        std::sort(uns.begin(), uns.end(), std::greater<int>());
        temp_stream.write((char*) uns.data(), sizeof(int)*N);
        temp_stream.close();
    }
    catch(Myexception &e)
    {
        throw e;
    }
}

void SORT::Sort_test::PrintArray(int *array, int N)
{
    std::cout << "Array:" << std::endl;
    /*for(int i=0; i < 4; i++)
        std::cout << array[i] << std::endl;

    std::cout << "..." << std::endl;
    for(int i=N/2-2; i<N/2+2; i++)
        std::cout << array[i] << std::endl;
    
    std::cout << "..." << std::endl;std::cout << " . . . " << std::endl;
    for(int i=N-4; i<N; i++)
        std::cout << array[i] << std::endl;*/
    for(int i=0; i<N/1000; i++)
    {
        int step=i*1000;
        for(int j = step; j<step+10;j++)
        {
            std::cout << array[j] << std::endl;
        }
        std::cout << " . . . " << std::endl;
    }
}

void SORT::Sort_test::StraightInsertion(int *array, int N)
{
    for(int i=1; (counter_index++,i < N); i++)
    {
        int cur=array[i];
        int j;
        for(j=i; j && (counter_key++,cur < array[j-1]) ; j--)
        {
            array[j]=array[j-1];
        }
        array[j]=cur;
    }

}

void SORT::Sort_test::BinaryInsertion(int *array, int N)
{
    for(int i=1; (counter_index++,i < N); i++)
    {
        int cur = array[i];
        int left = 0, right = i;
        while((counter_index++,left < right))
        {
            int mid = (right+left)/2;
            if(array[mid] <= cur)
                left = mid + 1;
            else
                right=mid; 
            counter_key++;  
        }
        for (int j=i; (counter_index++,j>right); array[j--]=array[j-1]);
        array[right]=cur;
    }
}

void SORT::Sort_test::Sift(int *array, int Left, int N)
{
    int parent = Left;
    int son = Left*2+1;
    int cur=array[Left];
    if((counter_index++,son < N) && (counter_key++,array[son+1] > array[son])){
        son++;
    }
    while((counter_index++,son < N) && (counter_key++,array[son] > cur))
    {
        array[parent] = array[son];
        parent=son;
        son=son*2+1;
        if((counter_index++,son < N) && (counter_key++,array[son+1] > array[son])){
            son++;
        }
    }
    array[parent]=cur;
}



void SORT::Sort_test::HeapSort(int *array, int N)
{
    int Begin = N/2;
    int End = N-1;
    while((counter_index++,Begin>0)){
        Sift(array,--Begin,End);
    }
    while((counter_index++,End>0))
    {
        std::swap(array[0], array[End]);
        Sift(array,Begin,--End);
    }
}

void SORT::Sort_test::QuickSort(int *array, int N)
{
    int piv = array[N/2];
    int begin=0, end=N-1;
    do{
        while((counter_key++,array[begin]<piv)) begin++;
        while((counter_key++,piv<array[end])) end--;
        if((counter_index++,begin<=end))
        {
            std::swap(array[begin], array[end]);
            begin++; end--;
        }
    }while((counter_index++,begin<end));
    if((counter_index++,end>0))
        QuickSort(array, end+1);
    if((counter_index++,begin<N-1))
        QuickSort(array+begin, N-begin);

}

 size_t SORT::Sort_test::get_counter() { return counter_key; };
 void SORT::Sort_test::init_counter(size_t x) { counter_key=x; };  
  size_t SORT::Sort_test::get_counter(int) {return counter_index; };
 void SORT::Sort_test::init_counter(size_t x, int) { counter_index = x; };  
