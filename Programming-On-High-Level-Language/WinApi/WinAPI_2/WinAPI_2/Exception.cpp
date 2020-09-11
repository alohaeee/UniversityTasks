#include "Exception.h"


namespace winapi
{
	Exception::Exception(DWORD errorCode) : std::exception(nullptr), m_errorCode(errorCode)
	{
	}
	Exception::Exception(DWORD errorCode, std::wstring additionalMessage) : std::exception(nullptr), m_errorCode(errorCode), m_additionalMessage(additionalMessage)
	{
	}
	Exception::~Exception()
	{
	}
	DWORD Exception::GetErrorCode() const
	{
		return m_errorCode;
	}
	LPCWSTR Exception::ConvertErrorMessage()
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
	LPCWSTR Exception::GetAdditionalMessage() const
	{
		if (m_additionalMessage.empty()) return nullptr;
		return m_additionalMessage.c_str();
	}
	void WinFastThrow()
	{
		throw Exception(GetLastError());
	}
	void COMThrowOnFail(HRESULT hResult)
	{
		if (FAILED(hResult))
		{
			throw _com_error(hResult);
		}
	}
}
