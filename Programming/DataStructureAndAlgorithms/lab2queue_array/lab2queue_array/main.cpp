#include "queue_array.h"
#include <iostream>
#include <locale.h>
#include <conio.h>

using namespace std;

int main()
{
try {
	setlocale(LC_ALL, "rus");

	char c=0;
	cout << "Init/ESC to exit";
	Queue obj;

	do
	{
		c = _getch();
		if (c == 27) break;

		int n;
		double flag;
		cout.unsetf(cout.showpos);

		cout << "\nВведите количество членов многочленна: ";
		if (!(cin >> n)) throw Myexception("Ошибка ввода", 1);
		if (n <= 0) continue;
		if (n >= 10)
		{
			cout << "mNoGo" << endl;
			n = 9;
		}
		for (int i = 1; i <= n; i++)
		{
			DataType temp;
			cout << "x" << i << ":" << "c" << i << " = ";
			if (!(cin >> temp.c)) throw Myexception("Ошибка ввода", 1);

			cout << "   e" << i << " = ";
			if (!(cin >> temp.e)) throw Myexception("Ошибка ввода", 1);

			if (obj.Empty()) {
				while (temp.e < 0)
				{
					cout << "Степень не соотвествует условию e1>e2>...en>=0" << endl;
					cout << "   e" << i << " = ";
					if (!(cin >> temp.e)) throw Myexception("Ошибка ввода", 1);
				}
			}
			else {
				while (temp.e < 0 || temp.e >= flag)
				{
					cout << "Степень не соотвествует условию e1>e2>...en>=0" << endl;
					cout << "   e" << i << " = ";
					if (!(cin >> temp.e)) throw Myexception("Ошибка ввода", 1);

					
				}
			}
			obj.push(temp);
			
			flag = temp.e;
			if (temp.e == 0) break;


		}
		cout << "P(x)' = ";
		bool flag1 = true;
		for (int i = 1; !obj.Empty(); i++)
		{
			DataType temp = obj.pop();
			if (temp.e == 0 || temp.c == 0);
			else if (temp.e == 1)
			{
				cout << temp.c*temp.e;
			}
			else
			{
				if (temp.e == 2) cout << temp.c*temp.e << "*x";
				else {
					cout << temp.c*temp.e << "*x" << "^";
					cout.unsetf(cout.showpos);
					cout << temp.e - 1;
					cout.setf(cout.showpos);
				}
			}
			if (i == 1) cout.setf(cout.showpos);
			 
		}
	} while (true);
	cout << "\nВышли";
	_getch();
	return 0;
}
catch (Myexception &e) {
	cout << "Error: " << e.GetErr() << endl;
	_getch();
	return e.GetValue();
}
}