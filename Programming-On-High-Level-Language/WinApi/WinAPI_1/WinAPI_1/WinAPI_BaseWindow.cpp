#include "WinAPI_BaseWindow.h"
#include "WinAPI_Exception.h"

namespace winapi
{
	void RegistererClass(LPCWSTR className, UINT style, HBRUSH background, HICON icon, LPCWSTR menuName, HCURSOR cursor)
	{
		WNDCLASS wc = { 0 };

		wc.hInstance = GetModuleHandle(NULL);
		wc.hbrBackground = background;
		wc.hCursor = cursor;
		wc.hIcon = icon;
		wc.lpfnWndProc = BaseWindow::WindowProc;
		wc.lpszClassName = className;
		wc.style = style;
		wc.lpszMenuName = menuName;

		auto result = RegisterClass(&wc);

		if(result == FALSE) FastThrow();
	}

	LRESULT BaseWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		BaseWindow* pThis = NULL;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (BaseWindow*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hWnd = hwnd;
		}
		else
		{
			pThis = (BaseWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	BaseWindow::BaseWindow()
	{
	}

	BaseWindow::~BaseWindow()
	{
		if (m_hWnd) DestroyWindow(m_hWnd);
	}

	void BaseWindow::createWindow(LPCWSTR windowClass, LPCWSTR windowName, DWORD style, DWORD exStyle, int x, int y, int width, int height, 
		HWND hWndParent, HMENU hMenu)
	{
		m_hWnd = CreateWindowEx(exStyle, windowClass, windowName, style, x, y, width, height, hWndParent, hMenu, GetModuleHandle(NULL), this);

		if (m_hWnd == FALSE) FastThrow();
	}
	HWND BaseWindow::getWindow() const
	{
		return m_hWnd;
	}
}

