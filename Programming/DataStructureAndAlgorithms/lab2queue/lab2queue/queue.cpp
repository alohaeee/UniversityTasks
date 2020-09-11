#include "queue.h"

Queue::~Queue()
{
	element *temp;
	while (begin)
	{
		temp = begin;
		begin = begin->next;
		delete temp;
	}
}

int Queue::Empty(void)
{
	return begin == nullptr; // ïî ñóòè âñòàâëÿåì bool âûğàæåíèå
}

double Queue::check(void)
{
	return end->num.e;
}

int Queue::Full(void)
{
	element *temp;
	temp = new (nothrow) element; // âûäåëÿåì ïàìÿòü ñ êîíñòîíñòàíòîé nothrow äëÿ ñàìîñòîÿòåëüíîé îáğàáîòêè èñêëş÷åíèÿ.
	if (temp == nullptr) return 1;
	delete temp;
	return 0;

}

void Queue::push(DataType nums)
{
	element *temp = new (nothrow) element;
	if (temp == nullptr) throw Myexception("Îøèáêà âûäåëåíèÿ ïàìÿòè", 2);
	temp->num = nums;
	temp->next = nullptr;
	if(Empty())
		begin = end = temp;
	else 
	{
		end->next = temp;
		end = end->next;
	}
}

DataType Queue::pop(void)
{
	DataType temp = begin->num;
	element *temp1 = begin;
	begin = begin->next;
	delete temp1;
	return temp;
}

DataType Queue::read(void)
{
	return begin->num;
}


