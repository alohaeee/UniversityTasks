#include "queue.h"
#include <locale>
#include <conio.h>

/*Errors log:
1-������������ ����
2-������ ��������� ������*/
 
int main()
{ 
try {
	setlocale(LC_ALL, "Rus");

	Queue obj;
	int n;
	bool flag = false;
	
	cout << "Init/������� ���������� ������ �����������: ";
	if (!(cin >> n)) throw Myexception("������ �����", 1);
	for (int i = 1; i <= n; i++)
	{
		DataType temp;
		cout << "x" << i << ":" << "c" << i << " = ";
		if (!(cin >> temp.c)) throw Myexception("������ �����", 1);

		cout << "   e" << i << " = ";
		if (!(cin >> temp.e)) throw Myexception("������ �����", 1);

		if (obj.Empty()) {
			while (temp.e < 0)
			{
				cout << "������� �� ������������ ������� e1>e2>...en>=0" << endl;
				cout << "   e" << i << " = ";
				if (!(cin >> temp.e)) throw Myexception("������ �����", 1);
			}
		}
		else {
			while (temp.e < 0 || temp.e >= obj.check())
			{
				cout << "������� �� ������������ ������� e1>e2>...en>=0" << endl;
				cout << "   e" << i << " = ";
				if (!(cin >> temp.e)) throw Myexception("������ �����", 1);

			}
		}
		obj.push(temp);

	}
	cout << "P(x) = ";
	for (int i = 1; !obj.Empty(); i++)
	{
		DataType temp = obj.pop();
		cout << temp.c*temp.e << "*x" << i << "^" << temp.e-1;
		if (!obj.Empty()) cout << " + ";
	}
	_getch();
	return 0;

}
catch (Myexception &e) {
	cout << "Error: " << e.GetErr() << endl;
	_getch();
	return e.GetValue();
}
}