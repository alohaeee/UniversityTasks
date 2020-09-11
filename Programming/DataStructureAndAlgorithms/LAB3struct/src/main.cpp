#include <iostream>
#include <string>
#include "Myexception.h"
#include "sort.h"

using namespace SORT;

constexpr int N[4] = { 15000, 40000, 80000, 150000};
constexpr auto LEFT = 10000000; // 10^7 
constexpr auto RIGHT = 99999999;
constexpr auto UNSORTED_FILE="unsorted.dat";
constexpr auto RESORTED_FILE="resorted.dat";


int main() {
try{
    Sort_test sorting(N[3],UNSORTED_FILE,RESORTED_FILE);
    {
        char answer;
        std::cout << "Want reinit files for new rand?(y/n)" << std::endl;
        std::cin >> answer;
        while(!std::cin && !(answer == 'y' || answer == 'n' || answer == 'Y' || answer == 'N'))
        {
            std::cout << "Wrong input!Try again" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            std::cin >> answer;
        }
        if(answer == 'y' || answer == 'Y')
        {
            sorting.init(LEFT+1000, RIGHT-1000);
        }
    }
    void (*sort_list[4])(int *, int) = { Sort_test::StraightInsertion, Sort_test::BinaryInsertion,
                                            Sort_test::HeapSort, Sort_test::QuickSort };
    std::string sort_name[4] = { "StraightInsertion", "BinaryInsertion",
                                            "HeapSort", "QuickSort" };
    
    for(size_t i=0; i<4; i++)
    {
        std::cout << "\tElements: " << N[i] << '\n' << std::endl;
        for(size_t j=0; j<4; j++)
        {
            std::cout << '*' << sort_name[j] << '*' << std::endl;

            std::cout << "  Non sorted array:" << std::endl;
            sorting.read(N[i]);
            Sort_test::init_counter(0); 
            Sort_test::init_counter(0,1);   
            sort_list[j](sorting.array, N[i]);
            std::cout << "Count of comparison keys:" << Sort_test::get_counter() <<  std::endl;
            std::cout << "\tIndex:" << Sort_test::get_counter(1) << std::endl;
            
            std::cout << "  Sorted array:" << std::endl;
            Sort_test::init_counter(0);
            Sort_test::init_counter(0,1); 
            sort_list[j](sorting.array, N[i]);
            std::cout << "Count of comparison:" << Sort_test::get_counter()  << std::endl;
            std::cout << "\tIndex:" << Sort_test::get_counter(1) << std::endl;

            std::cout << "  Sorted in another direction array:" << std::endl;
            sorting.read(N[i], 1);
            Sort_test::init_counter(0); 
            Sort_test::init_counter(0,1);
            sort_list[j](sorting.array, N[i]);
            std::cout << "Count of comparison:" << Sort_test::get_counter() << std::endl;
            std::cout << "\tIndex:" << Sort_test::get_counter(1) << std::endl;

            std::cout << "\n";
        }
        std::cout << "//////////////////////\n////////\n//////////////////////" << std::endl;
    }
    
    std::cin.get();
    return 0;
}
catch(Myexception &e)
{
    std::cerr << e.GetErr() << std::endl;
    std::cin.get();
    return e.GetVal();
};
}