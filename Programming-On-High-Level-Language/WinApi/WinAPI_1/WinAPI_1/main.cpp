#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#include "WinAPI_MainWindow.h"
#include "WinAPI_Exception.h"

#include <string>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	winapi::MainWindow mainWindow;
	std::wstring standartClass = L"StandartClass";
	try {

		winapi::RegistererClass(standartClass.c_str());
		mainWindow.createWindow(standartClass.c_str(), L"Test", WS_OVERLAPPEDWINDOW);

		ShowWindow(mainWindow.getWindow(), nCmdShow);
		mainWindow.messageRoutine();
		return 0;
	}
	catch (winapi::Exception& e)
	{
		std::wstring message(e.convertErrorMessage());
		message += L"Error code:" + std::to_wstring(e.getErrorCode()) + L'\r';
		if (e.getAdditionalMessage())
		{
			message += L"Where:";
			message += e.getAdditionalMessage();
		}
		MessageBox(mainWindow.getWindow(), message.c_str(), L"ERROR!", MB_ICONSTOP);
		return e.getErrorCode();
	}
}

