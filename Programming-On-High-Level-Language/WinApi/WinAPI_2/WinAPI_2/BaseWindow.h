#pragma once
#include <Windows.h>


namespace winapi
{
	void RegistererClass(LPCWSTR className, UINT style = 0, HBRUSH background = 0, HICON icon = 0, LPCWSTR menuName = nullptr, HCURSOR cursor = 0);
	class BaseWindow
	{
	protected:
		HWND m_hWnd = nullptr;

		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	public:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BaseWindow();
		virtual ~BaseWindow();

		void CreateWindowBW(LPCWSTR windowClass, LPCWSTR windowName, DWORD style, DWORD exStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
			int width = CW_USEDEFAULT, int height = CW_USEDEFAULT, HWND hWndParent = 0, HMENU m_menu = 0);

		HWND GetWindow() const;
	};

}




