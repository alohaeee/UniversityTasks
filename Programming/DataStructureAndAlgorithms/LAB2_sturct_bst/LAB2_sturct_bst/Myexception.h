#pragma once
#include <exception>
#include <string>

class Myexception : public std::exception
{
private:
	std::string errName;
	int errValue;
public:
	Myexception(std::string str, int val) : errName(str), errValue(val)
	{};
	std::string GetName(void) { return errName; };
	int GetVal(void) { return errValue; };
};


