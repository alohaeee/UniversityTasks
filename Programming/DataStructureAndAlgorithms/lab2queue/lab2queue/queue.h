#pragma once
#include <iostream>
#include "myexception.h"

using namespace std;
typedef struct element element;

typedef struct
{
	double c; // ����������
	double e; // ����������
} DataType;

class Queue
{
private:
	struct element{
		DataType num;// ����������� ��� ����� � ���������� ��������
		struct element *next;
	}*begin, *end;

public:
	Queue() { begin = end = nullptr; };
	~Queue();
	void push(DataType nums); // ����������
	DataType pop(void); // ��������
	DataType read(void); // ������������� ������ � ������
	int Full(void); // �������� �� �������
	int Empty(void); // �������
	double check(void); //������ � ����� ��� �������� �������������� �������.
};  

