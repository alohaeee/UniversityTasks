#pragma once
#include <iostream>

namespace SPLAY{


struct node{
    int key;
    //int size;
    struct node *left;
    struct node *right;
    struct node *parent;
    node () = default;
    explicit node(node *parent,int key) : key(key) 
    {
        left=right=nullptr;
        this->parent=parent;
        //size=1;
    };  
};

class SplayTree
{
private:
    node *root;
    ////bin tree
    void clean_help(node* tree);
    node* add_help(node *tree, int key);
    void inorder_help(node *tree);
    void print_vis(node *tree, int count);
    node* search_help(node* cur, node* prev, int key);
    node* del_help(node *cur);
    void chainGrandParent(node *gp, node *p, node *ch);
    node* rightRotate(node *p);
    node* leftRotate(node *p);
    /////splay
    bool isZigZag(node *cur);
    void zigZag(node* cur);
    void zigZig(node* cur);
    void zig(node* cur);
    void splay(node* cur);
public:
    static size_t counter_cmp;
    SplayTree() : root(nullptr) {};
    ~SplayTree()
    {
        clean_help(root);
    }
    void PrintInorder()
    {
        inorder_help(root);
        std::cout << std::endl;
    }
    void add_node(int key)
    {
        if(root==nullptr){
            node* parent=nullptr;
            root=new node(parent,key);
        }
        splay(add_help(root,key));
    }
    node *search(int key)
    {
        node* prev = nullptr;
        node* res= search_help(root, prev, key);

        if(res){
            splay(res);
            return root;
        }
        if(prev)
            splay(prev);
        return nullptr;
    }
    bool del_node(int key)
    {
        node* prev=nullptr;
        node* res = search_help(root, prev, key);

        if(res)
            splay(del_help(res));
        else if(prev)
            splay(prev);
        
        return res ? true : false;
    }
    void Print()
    {
        int counter=0;
        print_vis(root, counter);
    }

};
}