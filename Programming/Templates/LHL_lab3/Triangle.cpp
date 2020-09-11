#include "Triangle.h"



double Triangle::area(void)
{
	cout << "Площадь треугольника" << endl;
	double p = (a + b + c) / 2;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

double Triangle::Rin(void)
{
	cout << "Радиус вписанной окружности" << endl;
	return (area() * 2) / (a + b + c);
}

double Triangle::Rout(void)
{
	cout << "Радиус описанной окружности" << endl;
	return a*b*c / (4 * area());
}

const bool Triangle::check(void)
{
	cout << "Вызов проверки, существует ли такой треугольник." << endl;
	if (a <= 0 || b <= 0 || c <= 0) return false;
	return a + b > c && b + c > a && c + a > b;
}

std::string Triangle::type(void)
{
	cout << "Определение типа треугольника" << endl;
	if (a*a == b*b + c*c || b*b == c*c + a*a ||
		c*c == a*a + b*b) return "Right triangle";
	else if (a*a > b*b + c*c || b*b > c*c + a*a ||
		c*c > a*a + b*b) return "Obtuse triangle";
	else return "Acute triangle";
}

const bool & Triangle::operator==(const Triangle & right)
{
	return this->a == right.a && this->b == right.b && this->c == right.c;
}

/////////////////////
////friend func/////
///////////////////

istream &operator >> (istream &stream, Triangle &p)
{
	cout << "a = "; stream >> p.a;
	cout << "b = "; stream >> p.b;
	cout << "c = "; stream >> p.c;
	return stream;
}
ostream &operator << (ostream &stream, const Triangle &p)
{
	stream << "a = " << p.a << "\t" 
		<< "b = " << p.b << "\t" 
	    << "c = " << p.c << endl;
	return stream;
}

const bool &operator==(const Triangle &left, const Triangle &right)
{
	return left.a == right.a && left.b == right.b && left.c == left.c;
}
