#include "graph.h"

///////////////////////
////////////
//////////////////////
/////////////////////
////////////
////////////////////

MatrixNeoGraph::MatrixNeoGraph(size_t n) : Graph(n)
{
	weight = new weight_t*[nodes_s];
	transfer = new bool* [nodes_s];
	re_path = new size_t* [nodes_s];
	for (size_t i = 0; i < nodes_s; i++)
	{
		weight[i] = new weight_t[nodes_s];
		transfer[i] = new bool[nodes_s];
		re_path[i] = new size_t[nodes_s];
		for (size_t j = 0; j < nodes_s; j++)
		{
			if (i == j) weight[i][j] = 0;
			else weight[i][j] = WEIGHT_INF;
			transfer[i][j] = false;
		}
	}
}

MatrixNeoGraph::~MatrixNeoGraph()
{
	for (int i = 0; i < nodes_s; i++)
	{
		delete[] weight[i];
		delete[] transfer[i];
		delete[] re_path[i];
	}
	delete[] weight;
	delete[] transfer;
	delete[] re_path;
}

void MatrixNeoGraph::add_path(size_t from, weight_t path, size_t to)
{
	try {
		if (from == to) throw Myexception("Attention!Path from one town to them!", 4);
		if (from > nodes_s || to > nodes_s) throw Myexception("From or To more then size of graph", 4);
	}
	catch (Myexception & e)
	{
		throw;
	};
	weight[from][to] = path;
	weight[to][from] = path;
}

void MatrixNeoGraph::add_path(size_t from, weight_t path, size_t to, int)
{
	try {
		if (from == to) throw Myexception("Attention!Path from one town to them!", 4);
		if (from > nodes_s || to > nodes_s) throw Myexception("From or To more then size of graph", 4);
	}
	catch (Myexception & e)
	{
		throw;
	};
	if (weight[from][to] > path) //if weight from second type of road is smaller then add in matrix
	{
		weight[from][to] = path;
		weight[to][from] = path;
		transfer[from][to] = true;
		transfer[to][from] = true;
	}
}

void MatrixNeoGraph::print_d(void)
{
	cout << "\t GRAPH:" << endl;
	cout << " ";
	cout << static_cast<char>(-77);
	for (int i = 1; i <= nodes_s; i++)
		cout << i << '\t';
	cout << endl;
	cout << static_cast<char>(-60);
	cout << static_cast<char>(-59);
	int temp = (nodes_s) * 7;
	for (int i = 0; i <= temp; i++)
		cout << static_cast<char>(-60);
	cout << endl;
	for (int i = 0; i < nodes_s; i++)
	{
		cout << i + 1 << static_cast<char>(-77);
		for (int j = 0; j < nodes_s; j++)
		{
			print_w(weight[i][j]);
			cout << '\t';
		}
		cout << endl;
	}
}

void MatrixNeoGraph::floyd_find()
{
	// Floyd-Warshall algorithm.
	for (size_t i = 0; i < nodes_s; i++) {  //init re_path matrix
		for (size_t j = 0; j < nodes_s; j++) {
			if (weight[i][j] == WEIGHT_INF || i == j)
				re_path[i][j] = SIZE_INF;
			else
				re_path[i][j] = i;
		}
	}	
	for (size_t k = 0; k < nodes_s; k++)
	{
		for(size_t i = 0 ; i< nodes_s; i++)
			for (size_t j = 0; j < nodes_s; j++)
			{
				if (weight[i][k] + weight[k][j] < weight[i][j])
				{
					weight[i][j] = weight[i][k] + weight[k][j];
					re_path[i][j] = re_path[k][i];
				}
			}
	}	
}

void MatrixNeoGraph::restore(size_t from, size_t to)
{	
	if (from > to)
	{
		size_t temp = to;
		to = from;
		from = temp;
	}
	if (re_path[from][to] == SIZE_INF)
	{
		cout << "Path is not exist" << endl;
		return;
	}
	cout << "\tPATH:\n";
	size_t quit = from;
	bool flag = re_path[quit][to]!= quit ? transfer[quit][re_path[quit][to]] : transfer[quit][to];
	cout << (flag == true ? "H:" : "R:") <<from + 1 << "-(" << (re_path[quit][to]!=quit ? weight[quit][re_path[quit][to]] : weight[quit][to]) << ")->";
	while (re_path[quit][to] != quit)
	{
		if (transfer[quit][re_path[quit][to]] != flag)
		{
			cout << "(Transfer from " << ((flag == true) ? "Highway to Railway)->\nR:" : "Railway to Highway)->\nH:");
			flag = transfer[quit][re_path[quit][to]];
		}
		cout << re_path[quit][to] + 1;
		quit = re_path[quit][to];	
		cout << "-(" << (quit != re_path[quit][to] ? weight[quit][re_path[quit][to]] : weight[quit][to])<< ")->";
	}
	cout << to+1 << " reached.\n";
	cout << "Sum path:" << weight[from][to] << endl;
}




///////////////////////
////////////
//////////////////////
/////////////////////
////////////
////////////////////

TriangleMatrixNeoGraph::TriangleMatrixNeoGraph(size_t n) : Graph(n)
{
	weight = new weight_t*[nodes_s];
	transfer = new bool*[nodes_s];
	re_path = new size_t*[nodes_s];
	for (size_t i = 0; i < nodes_s ; i++) {
		weight[i] = new weight_t[i+1];
		transfer[i] = new bool[i+1];
		re_path[i] = new size_t[i+1];
		for (size_t j = 0; j <= i; j++) {
			if (i == j) 
				weight[i][j] = 0;
			else weight[i][j] = WEIGHT_INF;
			transfer[i][j] = false;
		}
	}
}

TriangleMatrixNeoGraph::~TriangleMatrixNeoGraph()
{
	for (int i=0; i<nodes_s; i++)
	{
		delete[] weight[i];
		delete[] transfer[i];
		delete[] re_path[i];
	}
	delete[] weight;
	delete[] transfer;
	delete[] re_path;
}

void TriangleMatrixNeoGraph::add_path(size_t from, weight_t path, size_t to)
{
	try {
		if (from == to) throw Myexception("Attention!Path from one town to them!", 4);
		if (from > nodes_s || to > nodes_s) throw Myexception("From or To more then size of graph", 4);
	}
	catch (Myexception & e)
	{
		throw;
	}
	if (from < to) 
	{
		weight[to][from] = path;
	}
	else
	{
		weight[from][to] = path;
	}
}
void TriangleMatrixNeoGraph::add_path(size_t from, weight_t path, size_t to, int)
{	
	try {
		if (from == to) throw Myexception("Attention!Path from one town to them!", 4);
		if (from > nodes_s || to > nodes_s) throw Myexception("From or To more then size of graph", 4);
	}
	catch (Myexception &e)
	{
		throw;
	};
	
	if (from < to) {
		if (weight[to][from] > path) {
			weight[to][from] = path;
			transfer[to][from] = true;
		}
	}
	else {
		if (weight[from][to] > path) {
			weight[from][to] = path;
			transfer[from][to] = true;
		}
	}
}

void TriangleMatrixNeoGraph::print_d(void)
{
	cout << "\t GRAPH:" << endl;
	cout << " ";
	cout << static_cast<char>(-77);
	for (int i = 1; i <= nodes_s; i++)
		cout << i << '\t';
	cout << endl;
	cout << static_cast<char>(-60);
	cout << static_cast<char>(-59);
	int temp = (nodes_s) * 7;
	for (int i = 0; i <= temp; i++)
		cout << static_cast<char>(-60);
	cout << endl;
	for (int i = 0 ; i< nodes_s; i++)
	{
		cout << i + 1 << static_cast<char>(-77);
		for (int j = 0; j <= i; j++)
		{
			print_w(weight[i][j]);
			cout << '\t';
		}
		cout << endl;
	}
}

void TriangleMatrixNeoGraph::floyd_find()
{
	for (size_t i = 0; i < nodes_s; i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			if (weight[i][j] == WEIGHT_INF || i==j)
				re_path[i][j] = SIZE_INF;
			else
				re_path[i][j] = 0;
		}
	}
	for (size_t k = 0; k < nodes_s; k++)
	{
		for (size_t i = 0; i < nodes_s; i++)
		{
			for (size_t j = 0; j <= i ; j++)	
			{
				weight_t a = k > i ?
					weight[k][i] : weight[i][k];
				weight_t b = k > j ?
					weight[k][j] : weight[j][k];
				if (weight[i][j] > a + b)
				{
					weight[i][j] = a + b;
					re_path[i][j] = k+1;
				}
			}
		}
	}
}

void TriangleMatrixNeoGraph::restore(size_t from, size_t to)
{
	string s1;
	string s2;
	bool reached;
	if (from < to)
	{
		size_t temp = to;
		to = from;
		from = temp;
		s1 = "-(";
		s2 = ")->";
		reached = true;
	}
	else
	{
		s1 = "<-(";
		s2 = ")-";
		reached = false;
	}
	stack<size_t> path_way;
	size_t quit = from;
	size_t part;
	path_way.push(from + 1);
	while (re_path[quit][to] != 0)
	{
		path_way.push(re_path[quit][to]);
		quit = re_path[quit][to] - 1;
	}
	part = path_way.top();
	path_way.push(to + 1);
	quit = path_way.top();
	bool flag = quit > part ? transfer[quit - 1][part - 1] : transfer[part - 1][quit - 1];
	cout << (reached == true ? "|BEGIN| " : "|reached| ");
	cout << (flag == true ? "H: " : "R: ");
	while (quit != from + 1)
	{
		
		path_way.pop();
		part = path_way.top();
		if (flag != quit > part ? transfer[quit - 1][part - 1] : transfer[part - 1][quit - 1]) {
			cout << s1 << "Transfer from " << (flag  == true ?
				"Highway to Railway" + s2 + "\nR: " : "Railway to Highway" + s2 + "\nH: ");
			flag = quit > part ? transfer[quit - 1][part - 1] : transfer[part - 1][quit - 1];
		}
		cout << quit << s1 << (quit > part ? weight[quit-1][part-1] : weight[part-1][quit-1]) << s2;
		quit = part;
	}
	cout << quit << (reached == true ? " |reached|" : " |BEGIN|") << endl;
}


///////////////////////
////////////
//////////////////////
/////////////////////
////////////
////////////////////




void ListNeoGraph::add_path(size_t from, weight_t path, size_t to)
{
	try {
		if (from == to) throw Myexception("Attention!Path from one town to them!", 4);
		if (from > nodes_s || to > nodes_s) throw Myexception("From or To more then size of graph", 4);
	}
	catch (Myexception & e)
	{
		throw;
	};
	NodeData value;
	value.to = to; value.weight = path; value.road_type = false;
	weight_list[from].push_back(value);
	value.to = from;
	weight_list[to].push_back(value);
}

void ListNeoGraph::add_path(size_t from, weight_t path, size_t to, int)
{
	try {
		if (from == to) throw Myexception("Attention!Path from one town to them!", 4);
		if (from > nodes_s || to > nodes_s) throw Myexception("From or To more then size of graph", 4);
	}
	catch (Myexception & e)
	{
		throw;
	};
	NodeData value;
	value.weight = path; value.road_type = true;
	ListData<NodeData>* iter = weight_list[from].pbegin();
	ListData<NodeData>* iter2 = weight_list[to].pbegin();
	while (iter != nullptr)
	{
		if (iter->data.to == to && iter->data.weight > path)
		{
			value.to = to;
			iter->data = value;
		}
		iter = iter->next;
	}
	
	while (iter && iter2 != nullptr)
	{
		if (iter2->data.to == from && iter2->data.weight > path)
		{
			value.to = from;
			iter2->data = value;
		}
		iter2 = iter2->next;
	}
	if (!iter && !iter2)
	{
		value.to = to;
		weight_list[from].push_back(value);
		value.to = from;
		weight_list[to].push_back(value);
	}
}

void ListNeoGraph::dijkstra_find(size_t from)
{
	weight_t *D = new weight_t[nodes_s];
	my_priority_queue<NodeData, cmp_weight> q;
	for (size_t i = 0; i < nodes_s; i++) //init 
	{
		D[i] = WEIGHT_INF;
		re_path[i].first = SIZE_INF;
		re_path[i].second = false;
	}
	D[from] = 0;
	ListData<NodeData>* iter = weight_list[from].pbegin();
	while (iter != nullptr) //pushing existing pathes from "FROM var" in queue
	{
		q.push(iter->data);
		D[iter->data.to] = iter->data.weight;
		re_path[iter->data.to].first = from;
		re_path[iter->data.to].second = iter->data.road_type;
		iter = iter->next;
	}
	while (!q.empty())
	{
		NodeData t=q.top();
		q.pop();
		/*if (t.weight > D[t.to]) //it happens really rarely
		{
			cout << "TAB " << endl;
			continue;
		}*/
		iter = weight_list[t.to].pbegin();
		while (iter != nullptr) //looking if path from queue's node is shorter then existing FROM pathes
		{
			if (D[iter->data.to] > D[t.to] + iter->data.weight)
			{
				D[iter->data.to] = D[t.to] + iter->data.weight;
				q.push(iter->data);
				re_path[iter->data.to].first = t.to;
				re_path[iter->data.to].second = iter->data.road_type;
			}
			iter = iter->next;
		}
	}
	cout << "\tAFTER ALGORITHM:" << endl; //print array D with shortest pathes
	for (size_t i = 1; i <= nodes_s; i++)
	{	
		cout << i << '\t';
	}
	cout << endl;
	size_t temp = (nodes_s) * 7;
	for (size_t i = 0; i <= temp; i++)
		cout << static_cast<char>(-60);
	cout << endl;
	for (size_t i = 0; i < nodes_s; i++)
	{
		print_w(D[i]); cout << '\t';
	}	
	cout << endl;

	/*for (size_t i = 0; i < nodes_s; i++)
	{
		cout << re_path[i].first << '\t';
	}
	cout << endl;*/
	//cout << "Sum weight from " << from+1 << " town to " << to+1 << " town = " << D[to] << endl;
}
void ListNeoGraph::restore(size_t from, size_t to)
{
	if (re_path[to].first == SIZE_INF)
	{
		cout << "Path is not exist" << endl;
		return;
	}
	stack<pair<size_t, bool>> st;
	size_t quit = to;
	while (re_path[quit].first != from)
	{
		st.push(re_path[quit]);
		quit = re_path[quit].first;
	}
	st.push(re_path[quit]);
	bool flag = st.top().second;
	cout << (flag == true ? "H: " : "R: ");
	while (!st.empty())
	{
		pair<size_t, bool> temp = st.top();
		cout << temp.first + 1 << "->";
		if (flag != temp.second)
		{
			cout << "Transfer from " << (flag == true ? "Highway to Railway->\nR: " : "Railway to Highway->\nH: ");
			flag = temp.second;
		}
		st.pop();
	}
	cout << to + 1 << " reached." << endl;
}

void ListNeoGraph::print_d(void)
{
	cout << '\t' << "LIST GRAPH:" << endl;
	cout << "F\tW\tT" << endl;
	for (size_t i = 0; i < nodes_s; i++) {
		ListData<NodeData>* iter = weight_list[i].pbegin();
		while (iter != nullptr)
		{
			cout << i+1 << '\t';
			print_w(iter->data.weight); cout << '\t' <<
				iter->data.to+1 << endl;
			iter = iter->next;
		}
	}
}
