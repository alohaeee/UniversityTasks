#pragma once
#include "Myexception.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

typedef unsigned int weight_t;
//constexpr auto WEIGHT_INF = std::numeric_limits<weight_t>::max();
constexpr auto WEIGHT_INF = 100000;
constexpr auto SIZE_INF = std::numeric_limits<size_t>::max();




class Graph
{
protected:	
	const size_t nodes_s;
	explicit Graph(const size_t n) : nodes_s(n) {}
public:
	virtual ~Graph() = default;

	/*add node from first type of road*/
	virtual void add_path(size_t from ,weight_t path, size_t to) = 0;
	
	/*add node from second type of road
	last arg is just stub to differ two overload functions*/
	virtual void add_path(size_t from, weight_t path, size_t to, int) = 0;

	/*print whole Graph*/
	virtual void print_d(void) = 0;

	/*weight - weight of node
	just make printing weight visual better*/
	static void print_w(weight_t weight)
	{
		if (weight == WEIGHT_INF) {
			std::cout << "NONE";
		}
		else {
			std::cout << weight;
		}
	}

	/*return count of nodes*/
	size_t size()
	{
		return nodes_s;
	};
};
//////////////////////
/////////////
/////////////////////
class MatrixNeoGraph :public Graph
{
private:
	weight_t** weight;
	bool** transfer;
	size_t** re_path;
public:
	MatrixNeoGraph(size_t n);
	~MatrixNeoGraph();

	void add_path(size_t from, weight_t path, size_t to);
	void add_path(size_t from, weight_t path, size_t to, int);
	void print_d(void);

	/*floyd warshall algorithm
	will find shorted pathes for all nodes in matrix*/
	void floyd_find(void);

	/*restore path from A town to B*/
	void restore(size_t from, size_t to);
};
//////////////////////
/////////////
/////////////////////

class TriangleMatrixNeoGraph:public Graph
{
private:
	weight_t **weight;
	bool **transfer;
	size_t** re_path;
public:
	TriangleMatrixNeoGraph(size_t n);
	~TriangleMatrixNeoGraph();

	void add_path(size_t from, weight_t path, size_t to);
	void add_path(size_t from, weight_t path, size_t to, int);
	void print_d(void);

	/*floyd warshall algorithm
	will find shorted pathes for all nodes in matrix*/
	void floyd_find();

	/*restore path from A town to B*/
	void restore(size_t from, size_t to);
};
//////////////////////
/////////////
/////////////////////

 

/*data list*/
template <class Type>
struct ListData {
	Type data;
	struct ListData* next;
	ListData() = default;
	explicit ListData(const Type value) : data(value) {};
};


template <class Type>
class AdjancecyList
{
private:
	ListData<Type>* front;
	ListData<Type>* back;
public:
	explicit AdjancecyList() : front(nullptr), back(nullptr) {};
	AdjancecyList(const AdjancecyList<Type> &obj)
	{
		ListData<Type>* iter = obj.pbegin();
		while (iter != nullptr)
		{
			this.push_back(iter->data);
			iter = iter->next;
		}
	};
	~AdjancecyList()
	{
		ListData<Type>* temp;
		while (front != back)
		{
			temp = front;
			front = front->next;
			delete temp;
		}
		delete front;
	};
	ListData<Type>* pbegin(void) const { return front; };
	ListData<Type>* pend(void) const { return back; };
	const bool empty() const {
		return front == nullptr;
	};
	void push_front(const Type value);
	void push_back(const Type value);
	void insert(ListData<Type>* pos, const Type value);
	void pop_front(void);
};

template<class Type>
void AdjancecyList<Type>::push_front(const Type value)
{
	ListData<Type>* temp = new ListData<Type>(value);
	if (front == nullptr)
	{
		temp->next = nullptr;
		front = back = temp;
		return;
	}
	temp->next = front;
	front = temp;
}

template<class Type>
void AdjancecyList<Type>::push_back(const Type value)
{
	ListData<Type>* temp = new ListData<Type>(value);
	temp->next = nullptr;
	if (front == nullptr)
	{
		front = back = temp;
		return;
	}
	back->next = temp;
	back = temp;
}



template<class Type>
void AdjancecyList<Type>::insert(ListData<Type> * pos, Type value)
{
	ListData<Type>* temp = new ListData<Type>(value);
	ListData<Type>* temp2;
	temp2 = pos->next;
	pos->next = temp;
	temp->next = temp2;
}

template<class Type>
void AdjancecyList<Type>::pop_front(void)
{
	ListData<Type>* temp;
	temp = front;
	front = front->next;
	delete temp;
}

/*priority queue for dijkstra algorithm*/
template<class Type, typename cmp_T>
class my_priority_queue
{
private:
	vector<Type> data;
	cmp_T cmp ;
	void sift_up(size_t pos);
	void sift_down(size_t pos);
public:
	explicit my_priority_queue() = default;
	explicit my_priority_queue(cmp_T* c) : cmp(c) {};
	const Type top() const {
		return data[0];
	}
	const bool empty() const{
		return data.size() == 0;
	}
	void pop()
	{
		swap(data[0], data.back());
		data.pop_back();
		sift_down(0);
	};
	void push(const Type& value)
	{
		data.push_back(value);
		sift_up(data.size() - 1);
	};		
};


template<class Type, class cmp_T>
void my_priority_queue<Type, cmp_T>::sift_up(size_t pos)
{
	size_t parent_pos = pos / 2;
	if (!cmp(data[pos], data[parent_pos])) {
		swap(data[pos], data[parent_pos]);
		if(pos !=parent_pos)
			sift_up(parent_pos);
	}
}

template<class Type, class cmp_T>
void my_priority_queue<Type, cmp_T>::sift_down(size_t pos)
{
	size_t cmp_pos = pos;
	if (2 * pos < data.size() && !cmp(data[2 * pos], data[cmp_pos])) {
		cmp_pos = 2 * pos;
	}
	if (2 * pos + 1 < data.size() && !cmp(data[2 * pos + 1], data[cmp_pos])) {
		cmp_pos = 2 * pos + 1;
	}
	if (cmp_pos != pos) {
		swap(data[cmp_pos], data[pos]);
		sift_down(cmp_pos);
	}
}

struct NodeData {
	size_t to;
	weight_t weight;
	bool road_type;
};

struct cmp_weight {
	bool operator ()(const NodeData& f, const NodeData& s)
	{
		return f.weight > s.weight;
	};
};

class ListNeoGraph : public Graph
{
private:
	AdjancecyList<NodeData> *weight_list;
	pair<size_t,bool>* re_path;
public:
	explicit ListNeoGraph(size_t num) : Graph(num) {
		weight_list = new AdjancecyList<NodeData>[nodes_s];
		re_path = new pair<size_t,bool>[nodes_s];
	};
	~ListNeoGraph()
	{
		delete[] weight_list;
	};
	void add_path(size_t from, weight_t path, size_t to);
	void add_path(size_t from, weight_t path, size_t to, int);

	/*dijkstra algorithm*/
	void dijkstra_find(size_t from);

	/*restore path from A town to B*/
	void restore(size_t from, size_t to);

	void print_d(void);
};
