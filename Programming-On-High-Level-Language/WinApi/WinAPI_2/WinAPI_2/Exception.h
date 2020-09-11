#pragma once

#include <exception>
#include <string>
#include <Windows.h>
#include <comdef.h>

namespace winapi
{
	class Exception : protected std::exception
	{
	private:
		std::wstring m_additionalMessage;
		DWORD m_errorCode = 0;
	public:
		Exception() = delete;
		explicit Exception(DWORD errorCode);
		Exception(DWORD errorCode, std::wstring additionalMessage);
		~Exception();

		DWORD GetErrorCode() const;
		LPCWSTR ConvertErrorMessage();
		LPCWSTR GetAdditionalMessage() const;


	};
	void WinFastThrow();
	void COMThrowOnFail(HRESULT hResult);
}

