#include <iostream>
#include <fstream>
#include "binary_search_tree.h"
#include "splay_tree.h"
#include <vector>
#include <random> 
#include <set>
#include <algorithm>
#include <map>

int main() {
    SPLAY::SplayTree::counter_cmp = 0;
    BinarySearchTree::counter_cmp = 0;
    
    auto splay_tree = new SPLAY::SplayTree();
    auto bin_tree = new BinarySearchTree();

    std::ifstream file("unsorted.dat", std::ios::binary);
    if(file.bad()){
        std::cerr << "Couldn't open file!" << std::endl;
        std::cin.get();
        return 1;
    }
    

    
    std::vector<int> keys_search;
    std::cout << "Init data of keys" << std::endl;
{
    std::uniform_int_distribution uid_chance(1,4);
    std::uniform_int_distribution uid_repeat(1,7);

    int min=100000000;
    int max=0;
    std::set<int> existing_keys;
    int exist,smaller,bigger,inside_range;
    std::mt19937 mt_rand(time(NULL));
    {
        {
            std::uniform_int_distribution uid_exist(30,50);
            exist = uid_exist(mt_rand);
            std::uniform_int_distribution uid_smaller(exist+10, exist+20);
            smaller = uid_smaller(mt_rand);
            std::uniform_int_distribution uid_bigger(smaller+10, smaller+20);
            bigger = uid_bigger(mt_rand);
            inside_range=99;
        }
        /*std::cout << inside_range-bigger << std::endl << bigger-smaller << std::endl 
        << smaller-exist << std::endl << exist << std::endl;
        std:: cout << "OAP\n" << exist << '\t' << smaller << '\t' << bigger << std::endl;*/
    }

    for(size_t i=0; !file.eof(); i++)
    {
        int key;
        file.read((char*) &key, sizeof(int));
        
        if(min>key)
            min=key;
        if(max<key)
            max=key;
        
        existing_keys.insert(key);
        splay_tree->add_node(key);
        bin_tree->add_node(key);
    }
    //std::cout << min << '\t' << max << std::endl;
    {   
        int rep;
        std::uniform_int_distribution uid_inside(min,max);
        while(keys_search.size()<exist)
        {   
            int key = uid_inside(mt_rand);
            if(existing_keys.find(key)!=existing_keys.end()){
                if(uid_chance(mt_rand)==1){
                    rep = uid_repeat(mt_rand);
                    for(int i=0; i < rep && keys_search.size()<exist; i++)
                        keys_search.push_back(key);
                }
                else keys_search.push_back(key);
            }
        }
        
        std::uniform_int_distribution uid_smaller(10000000, min);
        while(keys_search.size()<smaller)
        {
            if(uid_chance(mt_rand)==1){
                rep=uid_repeat(mt_rand);
                for(int i=0; i<rep && keys_search.size()<smaller; i++)
                    keys_search.push_back(uid_smaller(mt_rand));
            }
            else keys_search.push_back(uid_smaller(mt_rand));
        }
        std::uniform_int_distribution uid_bigger(max,99999999);
        while(keys_search.size()<bigger)
        {
            if(uid_chance(mt_rand)==1){
                rep=uid_repeat(mt_rand);
                for(int i=0; i<rep && keys_search.size()<bigger; i++)
                keys_search.push_back(uid_bigger(mt_rand));
            }
            else keys_search.push_back(uid_bigger(mt_rand));
        }
        
        while(keys_search.size() < 100)
        {
            int key = uid_inside(mt_rand);
            if(existing_keys.find(key)==existing_keys.end()){
                if(uid_chance(mt_rand)==1){
                    rep=uid_repeat(mt_rand);
                    for(int i=0; i<rep && keys_search.size()<100; i++)
                        keys_search.push_back(key);
                }
                else keys_search.push_back(key);
                
            }
            
        }
    }

}
    std::cout << "KEYS FOR SEARCH" << std::endl;
    for(size_t i=0; i<keys_search.size(); i++)
        std::cout << keys_search[i] << std::endl;
    {
        std::mt19937 mt_rand(time(NULL));
        std::shuffle(keys_search.begin(), keys_search.end(),mt_rand);
    }
    
    int found=0;
    SPLAY::SplayTree::counter_cmp = 0;
    BinarySearchTree::counter_cmp = 0;
    size_t sum1=0;
    size_t sum2=0;
    
    std::cout << "\tSearching 100 keys:" << std::endl;
    std::map<int,size_t> repeated; 

    for(size_t i=0; i<keys_search.size(); i++)
    {
        int key = keys_search[i];
        bool flag = false;
        if(splay_tree->search(key)) { 
            found++;
            flag = true;
        }
        bin_tree->search(key);


        std::cout << i << ". Key:" << key;
        auto rep = repeated.find(key);
        if(rep != repeated.end())
        {
            std::cout << "(REP^" << rep->second << ')';
            rep->second = i;
        }
        else repeated.insert(std::make_pair(key,i));
        std::cout << " - ";

        if(flag) std::cout << "Found" << std::endl;
        else std::cout << "Not found" << std::endl;
        std::cout << "Count of comparing keys in SplayTree: " << SPLAY::SplayTree::counter_cmp << std::endl;
        std::cout << "Count of comparing keys int non Balanced Binary Tree: " << BinarySearchTree::counter_cmp << std::endl;
        

        sum1+=SPLAY::SplayTree::counter_cmp;
        sum2+=BinarySearchTree::counter_cmp;
        std::cout << '\n';
        std::cout << "////////////////////////" << std::endl;
        std::cout << '\n';
        SPLAY::SplayTree::counter_cmp=0;
        BinarySearchTree::counter_cmp=0;
    }
    std::cout << "////////////////////////" << std::endl;
    std::cout << "//////////////////" << std::endl;
    std::cout << "////////////////////////" << std::endl;
    std::cout << "Count of found keys: " << found << std::endl;
    std::cout << "Wasn't found:" << keys_search.size() - found << std::endl;

    std::cout << "Sum of cmp in SplayTree: " << sum1 << std::endl;
    std::cout << "Sum of cmp in non Balanced Binary Tree: " << sum2 << std::endl;
    

    file.close();
    std::cin.get();
    return 0;
}