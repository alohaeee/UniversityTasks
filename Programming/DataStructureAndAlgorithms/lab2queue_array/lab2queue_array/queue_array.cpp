#include "queue_array.h"

bool Queue::Empty(void)
{
	return (rear + 1) % maxlenght == front;
}

bool Queue::Full(void)
{
	return (rear + 2) % maxlenght == front;
}

int Queue::push(DataType x)
{
	if(Full()) return 0;
	rear = (rear + 1) % maxlenght;
	data[rear] = x;
	return 1;
}

DataType Queue::pop(void)
{
	int temp = front;
	front = (front + 1) % maxlenght;
	return data[temp];
}

DataType Queue::read(void)
{
	return data[front];
}
