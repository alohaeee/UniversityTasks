#include "WinAPI_Exception.h"
#include <Windows.h>


namespace winapi
{
	Exception::Exception(std::wstring additionalMessage) : std::exception(nullptr), m_errorCode(0)
	{
	}
	Exception::Exception(DWORD errorCode) : std::exception(nullptr), m_errorCode(errorCode)
	{
	}
	Exception::Exception(DWORD errorCode, std::wstring additionalMessage) : std::exception(nullptr), m_errorCode(errorCode), m_additionalMessage(additionalMessage)
	{
	}
	Exception::~Exception()
	{
	}
	DWORD Exception::getErrorCode() const
	{
		return m_errorCode;
	}
	LPCWSTR Exception::convertErrorMessage()
	{
		LPVOID lpMsgBuf;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			m_errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)& lpMsgBuf,
			0, NULL);
		return (LPCWSTR)lpMsgBuf;
	}
	LPCWSTR Exception::getAdditionalMessage() const
	{
		if (m_additionalMessage.empty()) return nullptr;
		return m_additionalMessage.c_str();
	}
	void FastThrow()
	{
		throw Exception(GetLastError());
	}
}
