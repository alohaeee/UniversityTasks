#include "binary_search_tree.h"

size_t BinarySearchTree::counter_cmp;

void BinarySearchTree::clean_help(node *tree)
{
    if(tree==nullptr) return;
    clean_help(tree->left);
    clean_help(tree->right);
    delete tree;
}

void BinarySearchTree::add_help(node *tree, int key)
{
    if(tree->key > key)
    {
        if(tree->left)
            add_help(tree->left, key);
        else tree->left = new node(key);
        
    }
    else if(tree->key < key)
    {
        if(tree->right)
            add_help(tree->right, key);
        else tree->right = new node(key);
    }
    else {
        //do smth
        return;
    }
}

node *BinarySearchTree::search_help(node *tree, int key)
{
    counter_cmp++;
    if(tree == nullptr || tree->key==key)
        return tree;
    else if(tree->key>key)
        return search_help(tree->left,key);
    else 
        return search_help(tree->right,key);
}

void BinarySearchTree::min_del(node *min, node *cur)
{
    if(min->left)
        min_del(min->left, cur);
    else
    {
        cur->key=min->key; //swap
        cur=min; 
        min = min->right;
    }
}

bool BinarySearchTree::del_node(int key)
{
    node* del=search_help(root,key);
    if(del)
    {
        node* temp=del;
        if(del->left==nullptr)
            del=del->right;
        else if(del->right==nullptr)
            del=del->left;
        else
            min_del(del->right, temp);
        delete temp;
        return true;
    }
    return false;
}

void BinarySearchTree::inorder_help(node *tree)
{
    if(tree == nullptr) return;
    inorder_help(tree->left);
    std::cout << tree->key << '\t';
    inorder_help(tree->right);
}

void BinarySearchTree::print_vis(node *tree, int count)
{
    if(tree==nullptr) return;
    print_vis(tree->right, count+1);
    for(size_t i=0; i<=count; i++) std::cout << "   ";
    std::cout << tree->key << std::endl;
    print_vis(tree->left, count+1);
}