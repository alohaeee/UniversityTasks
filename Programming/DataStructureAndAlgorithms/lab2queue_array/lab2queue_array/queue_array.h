#pragma once
#include "myexception.h"

typedef struct
{
	double c, e; // coeffients
}DataType;

class Queue
{
private:
	int front, rear;
	DataType *data;
	int maxlenght;
public:
	Queue(int i = 10) : maxlenght(i)
	{
		data = new DataType[maxlenght];
		front = 0;
		rear = maxlenght - 1;
	};
	~Queue() { delete data; }
	bool Empty(void);
	bool Full(void);
	int push(DataType x);
	DataType pop(void);
	DataType read(void);	
};
