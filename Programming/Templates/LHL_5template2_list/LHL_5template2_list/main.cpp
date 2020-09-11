#include <iostream>
#include <conio.h>
#include "mystack.h"
#include <string>


using namespace std;

template <class T>
void menu_func(string type)
{
	
	mystack<T> *ptr = new mystack<T>;
	int c=-1;
	do {
		system("cls");
		cout << "\tMenu stack+<" << type << '>' << endl
			<< "1 - push" << endl
			<< "2 - pop" << endl
			<< "3 - read" << endl
			<< "0 - exit" << endl;
		while ((c<'0' || c>'4') && (c = _getch()));
		if (c == '0') break;

		switch (c)
		{
		case '1': {
			T temp;
			cout << "Enter data: ";
			while (!(cin >> temp))
			{
				cout << "Incorrect input!" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter data: ";
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(!ptr->push(temp)) cout << "Stack is full";
			break;
		}
		case '2':
			if (ptr->Empty()) {
				cout << "Empty" << endl;
				break;
			}
			cout << "pop:" << ptr->pop() << endl;
			break;
		case '3':
			if (ptr->Empty()) {
				cout << "Empty" << endl;
				break;
			}
			cout << "read:" << ptr->read() << endl;
			break;
		}
		while (_getch() != 13);
		c = -1;
	} while (true);
	delete ptr;
}

int main()
{
	int c=-1;
	while (true)
	{
		cout << "List of datatypes:" << endl
			<< "1 - float" << endl
			<< "2 - double" << endl
			<< "3 - int" << endl
			<< "4 - unsigned int" << endl
			<< "5 - char" << endl
			<< "6 - string" << endl
			<< "0 - exit" << endl;
		cout << "Press num of datatype";
		while ((c<'0' || c>'6') && (c = _getch()));
		if (c == '0') break;
		switch (c)
		{
		case '1': 
			menu_func<float>("float");
			break;
		
		case '2': 
			menu_func<double>("double");
			break;
		
		case '3': 
			menu_func<int>("int");
			break;
		
		case '4': 
			menu_func<unsigned int>("unsigned int");
			break;
		
		case '5': 
			menu_func<char>("char");
			break;
		
		case '6':
			menu_func<string>("string");
		}
		c = -1;
		system("cls");
		
	}
	return 0;
}