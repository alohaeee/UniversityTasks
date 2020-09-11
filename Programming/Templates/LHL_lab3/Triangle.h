#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class Triangle
{
private:
	/*struct sides {
		double a;
		double b;
		double c;
		sides(double a=0, double b=0, double c=0) : a(a), b(b), c(c)
		{};
	}sides;*/
	double a;
	double b;
	double c;
public:
	Triangle() 
	{
		cout << "����� ������������ �� ���������" << endl;
	};

	Triangle(double a, double b, double c) : a(a), b(b), c(c)
	{
		cout << "����� ������������ � �����������" << endl;
	};
	
	Triangle(const Triangle &copy) : a(copy.a), b(copy.b), c(copy.c)
	{
		cout << "����� ������������ �����������" << endl;
	};
	~Triangle()
	{
		cout << "����� �����������" << endl;
	};
	
	double area(void);
	double Rin(void);
	double Rout(void);
	const bool check(void);
	string type(void);
	

	friend istream &operator >> (istream &stream, Triangle &p);
	friend ostream &operator << (ostream &stream, const Triangle &p);
	const bool &operator == (const Triangle &right);
	friend const bool &operator == (const Triangle &left, const Triangle &right);
};

