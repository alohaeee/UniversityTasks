#pragma once

template<class Temp>
class mystack
{
	struct list{
		Temp data;
		struct list *next;
	}*end;
public:
	mystack();
	~mystack();
	int push(Temp);
	Temp pop(void);
	Temp read(void); 
	const bool Empty(void);

};


///////////////////
//////////
///////////////////
template<class Temp>
mystack<Temp>::mystack()
{
	end = nullptr;
}

template<class Temp>
mystack<Temp>::~mystack()
{
	struct list *temp;
	while (end)
	{
		temp = end;
		end = end->next;
		delete temp;
	}
}

template<class Temp>
int mystack<Temp>::push(Temp x)
{
	struct list *help = new (std::nothrow) struct list;
	if (help == nullptr)
		return 0;
	help->next = end;
	help->data = x;
	end = help;
	return 1;
}

template<class Temp>
Temp mystack<Temp>::pop(void)
{
	struct list *help = end;
	Temp data = help->data;
	end = end->next;
	delete help;
	return data;
}

template<class Temp>
Temp mystack<Temp>::read(void)
{
	return end->data;
}

template<class Temp>
const bool mystack<Temp>::Empty(void)
{
	return end == nullptr;
}

