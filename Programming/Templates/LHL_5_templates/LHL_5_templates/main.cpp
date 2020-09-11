#include <iostream>
#include <conio.h>
#include <iterator>

using namespace std;

template<class T>
void array_changer(T *first, int size)
{
	int flag=-1;
	for (int i = 0; i < size; i++)
	{
		if (first[i] < 0 && flag < 0) {
			flag = i;
		}
		else if (flag >= 0 && first[i] >= 0)
		{
				T temp;
				for (int j = i; j > flag; j--)
				{
					temp = first[j - 1];
					first[j - 1] = first[j];
					first[j] = temp;
				}
				i-=flag+1;
				flag = -1;
		}
	}
}


int main()
{
	float *f;
	char *c;
	int s1, s2;

	cout << "Enter size of array float: ";
	while (!(cin >> s1) || s1<0)
	{
		cout << "Wrong input" << endl;
		cout << "Enter size of array float: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	f = new float[s1];
	for (int i = 0; i < s1; i++)
	{
		cout << "f[" << i+1 << "] = ";
		while (!(cin >> f[i]))
		{
			cout << "Wrong input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "f[" << i+1 << "] = ";
		}
	}
	array_changer(f, s1);
	for (int i = 0; i < s1; i++)
	{
		cout << f[i] << '\t';
	}
	cout << '\n';


	cout << "Enter size of array char: ";
	while (!(cin >> s2) || s2<0)
	{
		cout << "Wrong input" << endl;
		cout << "Enter size of array char: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	c = new char[s2];
	for (int i = 0; i < s2; i++)
	{
		int temp;
		cout << "c[" << i+1 << "] = ";
		while (!(cin >> temp))
		{
			cout << "Wrong input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "c[" << i+1 << "] = ";
		}
		c[i] = temp;
	}
	array_changer(c, s2);
	for (int i = 0; i < s2; i++)
	{
		cout << static_cast<int>(c[i]) << '\t';
	}

	_getch();
	return 0;
}