#pragma once 
#include <iostream>
#include <fstream>
#include <string>
#include "Myexception.h"

namespace SORT{
class Sort_test
{
private:
    int N;
    std::ifstream unsorted;
    std::ifstream resorted;
    std::string name_un;
    std::string name_re;
    static size_t counter_key;
    static size_t counter_index;
    static void Sift(int *array, int Left, int Right);
public:
    int* array=nullptr;
    
    
    explicit Sort_test(int N, const char* name_un, const char* name_re) : N(N) , name_un(name_un), name_re(name_re)
    {
        try{
            unsorted.open(this->name_un,std::ios::in|std::ios::binary);
            resorted.open(this->name_re,std::ios::in|std::ios::binary);
            if(unsorted.fail() || resorted.fail()) throw Myexception("Could't to open file!", 1);
            std::cout << "Files were successfully open!\n";
            array = new (std::nothrow) int[this->N];
            if(array == nullptr) throw Myexception("Bad alloc!", 2);
         }catch(Myexception & e){
            throw e;
        };
    };
    ~Sort_test()
    {
        unsorted.close();
        resorted.close();
        delete[] array;
    };
    void init(int left, int right);
    void read(int N)
    {   
        unsorted.read((char*)array,N*sizeof(int));
        unsorted.seekg(std::ios::beg);
    };
    void read(int N, int)
    {
        resorted.read((char*)array,N*sizeof(int));
        resorted.seekg(std::ios_base::beg);
    };
    static void PrintArray(int *array, int N);
    static void StraightInsertion(int *array, int N);
    static void BinaryInsertion(int *array, int N);
    static void HeapSort(int *array, int N);
    static void QuickSort(int *array, int N);
    static size_t get_counter();
    static void init_counter(size_t x);
    static size_t get_counter(int) ;
    static void init_counter(size_t x, int);     
};
}

