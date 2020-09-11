#include "splay_tree.h"

size_t SPLAY::SplayTree::counter_cmp;


void SPLAY::SplayTree::clean_help(node *tree)
{
    if(tree==nullptr) return;
    clean_help(tree->left);
    clean_help(tree->right);
    delete tree;
}

SPLAY::node* SPLAY::SplayTree::add_help(node *tree, int key)
{
    if(tree->key == key)
        return tree;
    node* tmp;

    if(tree->key > key){
        if(tree->left)
            tmp = add_help(tree->left, key);
        else
            tmp = tree->left = new node(tree,key);
    }
    else if(tree-> key < key){
        if(tree->right)
            tmp = add_help(tree->right, key);
        else
            tmp = tree->right=new node(tree, key);
    }
    else{
        tmp=tree;
    }

    return tmp;
}

void SPLAY::SplayTree::inorder_help(node *tree)
{
    if(tree == nullptr) return;
    inorder_help(tree->left);
    std::cout << tree->key << '\t';
    inorder_help(tree->right);
}

void SPLAY::SplayTree::print_vis(node *tree, int count)
{
   if(tree==nullptr) return;
    print_vis(tree->right, count+1);
    for(size_t i=0; i<=count; i++) std::cout << "   ";
    std::cout << tree->key << std::endl;
    print_vis(tree->left, count+1);
}



SPLAY::node* SPLAY::SplayTree::search_help(node* cur, node* prev, int key)
{
    while(cur)
    {
        counter_cmp++;
        if(cur->key == key)
            return cur;
        else{
            prev=cur;
            cur=(cur->key > key ? cur->left : cur->right);
        }
        
    }
    return nullptr;
}

SPLAY::node* SPLAY::SplayTree::del_help(node* cur)
{
    
    node * removedNode = nullptr, *p=nullptr;;
    if(cur->left && cur->right)
    {
        node *prev=nullptr;
        node* higherClosest = search_help(cur,prev, cur->key+1);
        if(higherClosest==nullptr){
            higherClosest=prev;
            p=prev->parent;
        }
        else{
            p=prev;
        }
        cur->key = higherClosest->key; // swap

        if(higherClosest == p->left)
            p->left = higherClosest->right; //higherclosest always is have't left son, here just up right son;
        else
            p->right = higherClosest->right;
        
        if(higherClosest->right)
            higherClosest->right->parent = p;
        removedNode = higherClosest;
    } else{
        p = cur->parent;
        node *ch = cur->left ? cur->left : cur->right;
        if(p==nullptr)
            root = ch;
        else {
            if(p->left == cur)
                p->left = ch;
            else 
                p->right =ch;
        }
        if(ch)
            ch->parent = p;
        removedNode = cur;
    }
    delete removedNode;
    return p;
}

void SPLAY::SplayTree::chainGrandParent(node* gp, node* p, node* ch)
{
    if(gp->left == p)
        gp->left = ch;
    else
        gp->right = ch;   
}

SPLAY::node* SPLAY::SplayTree::rightRotate(node *p)
{
    node* ch = p->left;
    p->left=ch->right;
    if(ch->right)
        ch->right->parent = p;
    ch->parent = p->parent;

    if(p->parent)
        chainGrandParent(p->parent, p, ch);
    else
        root = ch;
    
    ch->right=p; p->parent = ch;
    return ch;
}

SPLAY::node* SPLAY::SplayTree::leftRotate(node *p)
{
    node *ch = p->right;
    p->right = ch->left;
    if(ch->left)
        ch->left->parent=p;
    ch->parent= p->parent;

    if(p->parent)
        chainGrandParent(p->parent, p, ch);
    else
        root = ch;

    ch->left = p; p->parent = ch;
    return ch;
}

bool SPLAY::SplayTree::isZigZag(node *cur)
{
    node* p = cur->parent, *gp=p->parent;

    return (p->right == cur && gp->left == p) ||
    (p->left == cur && gp->right == p);
}

void SPLAY::SplayTree::zigZag(node *cur)
{
    node* p= cur->parent;
    if(p->right == cur && p->parent->left == p)
        rightRotate(leftRotate(p)->parent);
    else
        leftRotate(rightRotate(p)->parent);
}

void SPLAY::SplayTree::zigZig(node *cur)
{
    node* p = cur->parent;
    if(p->left == cur && p->parent->left == p)
        rightRotate(rightRotate(p->parent));
    else
        leftRotate(leftRotate(p->parent));
}

void SPLAY::SplayTree::zig(node *cur)
{
    node* p = cur->parent;
    if(p->left == cur)
        rightRotate(p);
    else
        leftRotate(p);
}

void SPLAY::SplayTree::splay(node* cur)
{
    if(cur == nullptr)
        return;
    
    while(cur->parent)
    {
        if(cur->parent->parent)
            if(isZigZag(cur))
                zigZag(cur);
            else 
                zigZig(cur);
        else
            zig(cur);
    }
}

