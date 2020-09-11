#pragma once
#include <iostream>


struct node{
    int key;
    struct node *left;
    struct node *right;
    explicit node(int key) : key(key)
    {
        left=right=nullptr;
    }
    node() = default;
};

class BinarySearchTree
{
private:
    node *root;
    void clean_help(node *tree);
    void add_help(node *tree,int key);
    node* search_help(node *tree, int key);
    void min_del(node *min, node *cur);
    void inorder_help(node *tree);
    void print_vis(node *treem, int count);
public:
    static size_t counter_cmp;
    static size_t counter_help;
    BinarySearchTree() : root(nullptr) {};
    ~BinarySearchTree()
    {
        clean_help(root);
    };
    void add_node(int key)
    {
        if(root == nullptr)
            root = new node(key);
        else add_help(root, key);
    };
    node* search(int key)
    {
        return search_help(root,key);
    };
    bool del_node(int key);
    void PrintInorder()
    {
        inorder_help(root);
        std::cout << std::endl;
    }
    void Print()
    {
        int counter=0;
        print_vis(root,counter);
    }
};

