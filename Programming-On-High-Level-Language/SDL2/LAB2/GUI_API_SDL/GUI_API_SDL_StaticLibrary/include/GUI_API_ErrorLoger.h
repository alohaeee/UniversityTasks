#pragma once
#include <exception>
#include <string>

enum ErrorValue
{
	BAD_INIT = 1,
	BAD_LOAD = 2
};

class ErrorLoger : public std::exception
{
private:
	ErrorValue _errorCode;
public:
	ErrorLoger(std::string message, ErrorValue errorValue) : std::exception(message.c_str()), _errorCode(errorValue)
	{
	}
	ErrorValue getErrorCode()
	{
		return _errorCode;
	}
};