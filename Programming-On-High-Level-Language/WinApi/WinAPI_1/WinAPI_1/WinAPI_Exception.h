#pragma once

#include <exception>
#include <string>
#include <Windows.h>

namespace winapi 
{
	class Exception : private std::exception
	{
	private:
		std::wstring m_additionalMessage;
		DWORD m_errorCode = 0;
	public:
		Exception() = delete;
		explicit Exception(std::wstring additionalMessage);
		explicit Exception(DWORD errorCode);
	    Exception(DWORD errorCode, std::wstring additionalMessage);
		~Exception();

		DWORD getErrorCode() const;
		LPCWSTR convertErrorMessage();
		LPCWSTR getAdditionalMessage() const;
		

	};
	void FastThrow();
}


