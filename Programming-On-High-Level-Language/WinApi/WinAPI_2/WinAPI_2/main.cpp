// Linker flags
#pragma comment(lib,"d2d1")
#pragma comment(lib,"dwrite")
#pragma comment(lib,"COMCTL32")




#include "MainWindow.h"
#include "CoordinateField.h"
#include "Exception.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



	winapi::MainWindow mainWindow;

	std::wstring regularWindowClass = L"regularWindowClass";

	try
	{

		winapi::RegistererClass(regularWindowClass.c_str());
		mainWindow.CreateWindowBW(regularWindowClass.c_str(), L"WinAPI 2", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 0, 
			CW_USEDEFAULT, CW_USEDEFAULT, 800,900);
		
		ShowWindow(mainWindow.GetWindow(), nCmdShow);
		
		return mainWindow.MessageRoutine();;
	}
	catch (winapi::Exception& e)
	{
		std::wstring errorString;
		if (e.GetAdditionalMessage())
		{
			errorString.append(e.GetAdditionalMessage());
		}
		errorString.append(L"Error: ");

		errorString.append(e.ConvertErrorMessage());
		errorString.append(L"Error code: " + std::to_wstring(e.GetErrorCode()));

		MessageBox(mainWindow.GetWindow(),errorString.c_str(), L"Error", MB_ICONWARNING);

		return e.GetErrorCode();

	}
	catch (_com_error& e)
	{
		std::wstring errorString = L"Error code: " + std::to_wstring(e.Error()) + L"ErrorMessage: " + e.ErrorMessage();

		MessageBox(mainWindow.GetWindow(), errorString.c_str(), L"Error", MB_ICONWARNING);
		
		return e.Error();
	}

	return 0;
}