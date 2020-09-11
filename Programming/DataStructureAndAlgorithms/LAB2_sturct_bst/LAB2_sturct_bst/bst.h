#pragma once
#include "Myexception.h"
#include <iostream>
#include <queue>

template<class Type>
struct node {
	Type data;
	struct node* left;
	struct node* right;
	node() = default;
	explicit node(const Type x) : data(x) {
		left = right = nullptr;
	};
};

template<class Type>
class bst
{
private:
	node<Type> *root;
	void sub_add(node<Type> *&sub, const Type &value);
	void distruct_help(node<Type>* sub);
	void inorder_help(node<Type>* sub);
	void preorder_help(node<Type>* sub);
	void postorder_help(node<Type>* sub);
	void print_tree(node<Type>* sub, size_t level);
	void copy_help(node<Type>*& sub_this, node<Type>* sub_copy);
	void del_help(node<Type>*& sub, const Type& value);
	void minimum(node<Type>* min, node<Type>* cur);
	bool check(node<Type>* sub, int &height);
	
public:
	explicit bst()
	{
		root = nullptr;
	};
	~bst()
	{
		if (root)
		{
			distruct_help(root);
		}
	};
	bst(const bst& copy)
	{
		if (copy.root)
		{
			copy_help(root, copy.root);
		}
	};
	const bool empty (void) const
	{
		return root==nullptr;
	};
	void add_node(const Type &value)
	{
		if (root == nullptr)
			root = new node<Type>(value);
		else 
			sub_add(root, value );
	};
	void print_inorder()
	{
		if (root) {
			inorder_help(root);
			std::cout << std::endl;
		} else std::cout << "empty" << std::endl;
	};
	void print_preorder()
	{
		if (root) {
			preorder_help(root);
			std::cout << std::endl;
		} else std::cout << "empty" << std::endl;
	};
	void print_postorder()
	{
		if (root) {
			postorder_help(root);
			std::cout << std::endl;
		} else std::cout << "empty" << std::endl;
	};
	void print_onlevel();
	void print_visual()
	{
		print_tree(root, 0);
	};
	bool balanced()
	{
		int h;
		return check(root, h);
		
	};
	void del_node(const Type& value)
	{
		del_help(root, value);
	};
};


template<class Type>
void bst<Type>::sub_add(node<Type> *&sub, const Type &value)
{
	if (sub->data > value)
	{
		if (sub->left)
			sub_add(sub->left, value);
		else
			sub->left = new node<Type>(value);
	}
	else
	{
		if (sub->right)
			sub_add(sub->right, value);
		else
			sub->right = new node<Type>(value);
	}	
}
template<class Type>
void bst<Type>::distruct_help(node<Type>* sub)
{
	if (sub->left)
		distruct_help(sub->left);
	if (sub->right)
		distruct_help(sub->right);
	delete sub;
}

template<class Type>
void bst<Type>::inorder_help(node<Type>* sub)
{
	if(sub->left)
		inorder_help(sub->left);
	std::cout << sub->data << ' ';
	if(sub->right)
		inorder_help(sub->right);
}

template<class Type>
void bst<Type>::preorder_help(node<Type>* sub)
{
	std::cout << sub->data << ' ';
	if (sub->left)
		preorder_help(sub->left);
	if (sub->right)
		preorder_help(sub->right);
}
template<class Type>
void bst<Type>::postorder_help(node<Type>* sub)
{
	if (sub->left)
		postorder_help(sub->left);
	if(sub->right)
		postorder_help(sub->right);
	std::cout << sub->data << ' ';
}

template<class Type>
void bst<Type>::print_tree(node<Type>* sub, size_t level)
{
	if (sub)
	{
		print_tree(sub->right, level + 1);
		for (size_t i = 0; i <= level; i++) std::cout << "   ";
		std::cout << sub->data << std::endl;
		print_tree(sub->left, level + 1);
	}
}



template<class Type>
void bst<Type>::copy_help(node<Type>*& sub_this, node<Type>* sub_copy)
{
	sub_this = new node<Type>(sub_copy->data);
	if(sub_copy->left) copy_help(sub_this->left, sub_copy->left);
	if(sub_copy->right) copy_help(sub_this->right, sub_copy->right);
}

template<class Type>
void bst<Type>::del_help(node<Type>*& sub, const Type& value)
{
	if (sub)
	{
		if (value < sub.data)
			del_help(sub->left, value);
		else if (value > sub.data)
			del_help(sub->right, value);
		else
		{
			node<Type> temp = sub;
			if (sub->left == nullptr)
				sub = sub->right;
			else if (sub->right == nullptr)
				sub = sub->left;
			else 
				
			delete temp;
		}
	}
}

template<class Type>
void bst<Type>::minimum(node<Type>* min, node<Type>* cur)
{
	if (min->left)
		minimum(min->left);
	else
	{
		cur->data = min->data;
		cur = min;
		min = min->right;
	}
}

template<class Type>
bool bst<Type>::check(node<Type>* sub,int &height)
{
	if (sub == nullptr)
	{
		height = 0;
		return true;
	}
	int left=0;
	int right=0;
	bool flag_left = check(sub->left, left);
	bool flag_right = check(sub->right, right);
	height = (left > right ? left : right) + 1;
	if (std::abs(left - right) > 1)
		return false;
	return flag_left && flag_right;

}

template<class Type>
void bst<Type>::print_onlevel()
{
	std::queue<node<Type> *> q;
	q.push(root);
	while (!q.empty())
	{	
		node<Type> *temp = q.front();
		q.pop();
		std::cout << temp->data << ' ';
		if (temp->left)
			q.push(temp->left);
		if (temp->right)
			q.push(temp->right);
	}
	std::cout << std::endl;
}






