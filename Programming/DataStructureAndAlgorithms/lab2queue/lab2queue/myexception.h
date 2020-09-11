#pragma once
#include <string>
#include <exception>
class Myexception : public std::exception
{ 
private:
	int errValue;
	std::string errName;
public:
	Myexception(std::string j, int i)
	{
		this->errName = j;
		this->errValue = i;
	}
	int GetValue(void) { return errValue; }
	std::string GetErr(void) { return errName; }
};
