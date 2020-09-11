#pragma once
#include <iostream>
#include "myexception.h"

using namespace std;
typedef struct element element;

typedef struct
{
	double c; // коэффицент
	double e; // показатель
} DataType;

class Queue
{
private:
	struct element{
		DataType num;// коэффиценты при члене и показатели степеней
		struct element *next;
	}*begin, *end;

public:
	Queue() { begin = end = nullptr; };
	~Queue();
	void push(DataType nums); // добавление
	DataType pop(void); // удаление
	DataType read(void); // неразрушающие чтение с головы
	int Full(void); // проверка на полноту
	int Empty(void); // пустоту
	double check(void); //чтение с конца для проверки удовлетворения условия.
};  

