#include "Triangle.h"
#include <iostream>
#include <conio.h>
#include <locale.h>
#include <vector>
using namespace std;

void menu_vector(void);
void menu_triangle(void);
void clear_enter(void);


int main()
{
	setlocale(LC_ALL, "Rus");
	vector<Triangle> list;
	bool quit = true;
	int c = -1;
	int i;
	do {
		menu_vector();
		while ((c < '0' || c > '6') && (c = _getch()));
		if (c == '0') break;
		system("cls");

		switch (c)
		{
		case '1': {
			for (i=0; i<list.size(); i++)
			{
				cout << i+1 << ".\t" << list[i] << endl;
			}
			if (i == 0) cout << "Empty!" << endl;
			break;
		}
		case '2': {
			Triangle temp;
			bool flag=true;
			while (!temp.check()) {
				while (!(cin >> temp)) {
					cout << "Incorrect enter!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			list.push_back(temp);
			break;
		}

		case '3': {
			if (list.size() == 0) {
				cout << "Empty";
				break;
			}
			int num=-1;
			cout << "Enter num of triangle: ";
			
			while (!(cin >> num) || (num > list.size() || num < 1)) {
				cout << "Incorrect num" << endl;
				cout << "Enter num of triangle: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			auto iter = list.begin();
			advance(iter, num-1);
			list.erase(iter);
			break;
		}
		case '4': {
			if (list.size() < 2) {
				cout << "Not enough triangles";
				break;
			}
			int num = -1;
			
			cout << "Enter num of first triangle: ";
			while (!(cin >> num) || (num > list.size() || num < 1)) {
				cout << "Incorrect num" << endl;
				cout << "Enter num of triangle: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			num--;

			int num2 = -1;
			cout << "Enter num of second triangle: ";
			while (!(cin >> num2) || (num2 > list.size() || num2 < 1)) {
				cout << "Incorrect num" << endl;
				cout << "Enter num of triangle: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			num2--;

			if (list[num] == list[num2]) cout << "Equal" << endl;
			else cout << "Not equal" << endl;
			break;
		}
		case '5': {
			
			int num;
			cout << "Enter num of triangle: ";
			while (!(cin >> num) || (num > list.size() || num < 1)) {
				cout << "Incorrect num" << endl;
				cout << "Enter num of triangle: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			num--;
			do {
				cout << list[num];

				menu_triangle();
				c = -1;
				while ((c = _getch()) && (c < '1' || c>'4') && (c!=13));
				if (c == 13) break;
				system("cls");
				switch (c)
				{
				case '1':
					cout << list[num].area() << endl;
					break;
				case '2':
					cout << list[num].Rin() << endl;
					break;
				case '3':
					cout << list[num].Rout() << endl;
					break;
				case '4':
					cout << list[num].type().c_str() << endl;

				}
			} while (true);
			break;
		}
		case '6':
			double a, b, c;
			cout << "Enter a, b, c" << endl;
			do {
				while (!(cin >> a >> b >> c))
				{
					cout << "Incorrect num" << endl;
					cout << "Enter a, b, c" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				Triangle temp(a, b, c);
				if (temp.check()) {
					list.push_back(temp);
					break;
				}	
				else {
					cout << "Incorrect triangle" << endl;
				}
			} while (true);
		}
		clear_enter();
		c = -1;
	} while (true);
	return 0;
}


void menu_vector(void)
{
	cout << "1. Show list of triangles" << "\n"
		<< "2. Add triangle in list with \"<<\"" << "\n"
		<< "3. Delete triangle from list" << "\n"
		<< "4. Compare on equal of two triangles" << "\n"
		<< "5. Operations with triangle" << "\n"
		<< "6. Add with param" << "\n"
		<< "0. Exit " << endl;
}
void menu_triangle(void)
{
	cout << "1. Compute area of triangle" << "\n"
		<< "2. Find radius of incircle" << "\n"
		<< "3. Find radius of circumcircle" << "\n"
		<< "4. Type of triangle" << endl;
}

void clear_enter(void)
{
	while (_getch() != 13);
	system("cls");
}