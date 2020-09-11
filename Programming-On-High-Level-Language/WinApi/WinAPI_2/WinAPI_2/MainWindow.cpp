#include "MainWindow.h"

#include "Exception.h"
#include "CoordinateField.h"

#include <sstream>

namespace winapi
{
	ID2D1Factory* MainWindow::m_d2d1Factory = nullptr;
	IDWriteFactory* MainWindow::m_dwFactory = nullptr;
	StatusBar* MainWindow::m_statusBar = nullptr;

	constexpr auto MENU_FILE = 100;
	constexpr auto MENU_FILE_OPEN = 1000;
	constexpr auto MENU_FILE_SAVE = 1001;
	constexpr auto MENU_FILE_EXIT = 1002;
	
	
	LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CREATE:
			OnCreate();
			break;
		case WM_PAINT:
			OnPaint();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			OnDestroy();
			break;
		case WM_KEYDOWN:
			SendMessage(m_coordinateField->GetWindow(), WM_KEYDOWN, wParam, NULL);
			break;
		case WM_COMMAND:
			OnCommand(LOWORD(wParam));
			break;
		default:
			return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		}
		return 0;
	}

	void MainWindow::OnCreate()
	{	
		InitCommonControls();

		COMThrowOnFail(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2d1Factory));

		COMThrowOnFail(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_dwFactory), reinterpret_cast<IUnknown * *>(&m_dwFactory)));

		m_coordinateField = new CoordinateField();
		m_coordinateField->SetColorBG(D2D1::ColorF(D2D1::ColorF::Gray));
		RegistererClass(L"CoordinateFieldWindow", CS_DBLCLKS);
		m_coordinateField->CreateWindowBW(L"CoordinateFieldWindow", L"CoordinateField", WS_CHILDWINDOW| WS_VISIBLE , 0,
			0, 0, 800, 800, m_hWnd);

		CreateMenuBar();
		CreateStatusBar();
	}

	void MainWindow::OnPaint()
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hWnd, &ps);

		EndPaint(m_hWnd, &ps);
	}

	void MainWindow::OnDestroy()
	{
		delete m_coordinateField;
		delete m_statusBar;

		safeRelease(m_dwFactory);
		safeRelease(m_d2d1Factory);
	}

	void MainWindow::OnCommand(int menuID)
	{
		switch (menuID)
		{
		case MENU_FILE_OPEN:
			OnOpen();
			break;
		case MENU_FILE_SAVE:
			OnSave();
			break;
		case MENU_FILE_EXIT:
			SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
			break;
		default:
			break;
		}
	}

	void MainWindow::OnOpen()
	{
		OPENFILENAME openFileName = {};


		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = m_hWnd;
		openFileName.lpstrFile = m_fileName;
		openFileName.nMaxFile = sizeof(m_fileName);
		openFileName.lpstrFilter = L"Text\0*.TXT\0\0";
		openFileName.nFilterIndex = 1;
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = NULL;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&openFileName))
		{
			auto hFile = CreateFile(m_fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE == hFile)
			{
				WinFastThrow();
			}

			// Read from file.
			CHAR szMsg[500] = { 0 };
			DWORD nToRead;

			if (!ReadFile(hFile, szMsg, sizeof(szMsg), &nToRead, NULL)) WinFastThrow();

			std::string fileString = szMsg;
			std::vector<D2D1_POINT_2F> points;

			bool isBadFile = false;
			bool isXPoint = true;
			D2D1_POINT_2F curPoint = D2D1::Point2F();

			while (fileString.length())
			{
				double num;
				std::string curNum;
				size_t pos;

				if (isXPoint)
				{
					pos = fileString.find_first_of(" ");
					curNum = fileString.substr(0, pos);
				}
				else
				{
					pos = fileString.find_first_of("\n");
					curNum = fileString.substr(0, pos-1);
				}

				fileString = fileString.substr(pos + 1);

				if (!string_to_double(curNum, num))
				{
					isBadFile = true;
					break;
				}

				if (isXPoint)
				{
					curPoint.x = num;
				}
				else
				{
					curPoint.y = num;
					points.push_back(curPoint);

				}

				// Exit.
				if (pos == std::string::npos)
				{
					if (isXPoint)
					{
						isBadFile = true;
					}
					break;
				}

				isXPoint = !isXPoint;
			}

			// Message to status bar.
			std::wstring message = m_fileName;

			message = message.substr(message.find_last_of(L"\\") + 1);
			if (!isBadFile)
			{
				message = L"File: " + message;
			}
			else
			{
				message = L"Couldn't open file: " + message;
				GetStatusBar()->SendFileMessage(L"");
				MessageBox(m_hWnd, message.c_str(), L"Error", MB_ICONWARNING);
				return;
			}
			GetStatusBar()->SendFileMessage(message.c_str());

			CloseHandle(hFile);

			if (!m_isOpened)
			{
				ModifyMenu(m_menuFile, MENU_FILE_SAVE, MF_STRING | MF_ENABLED, MENU_FILE_SAVE, L"Save");
				DrawMenuBar(m_hWnd);
				m_isOpened = true;
			}

			m_coordinateField->AddPointVector(points);

			GetStatusBar()->SendEventMessage(L"File opened");
		}
	}

	void MainWindow::OnSave()
	{
		auto hFile = CreateFile(m_fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			WinFastThrow();
		}
		auto cartesianPoints = m_coordinateField->GetCartesianPoints();
		std::string buf;

		for (auto& cp : cartesianPoints)
		{
			buf.append(std::to_string(cp.x) + " " + std::to_string(cp.y) + "\r\n");
		}

		CHAR szMsg[500] = { 0 };
		DWORD nToRead;

		if (!WriteFile(hFile, buf.c_str(), buf.length(), &nToRead, NULL)) WinFastThrow();

		CloseHandle(hFile);

		GetStatusBar()->SendEventMessage(L"File saved");
	}

	void MainWindow::CreateMenuBar()
	{
		m_menu = CreateMenu();
		m_menuFile = CreatePopupMenu();

		AppendMenu(m_menu, MF_STRING | MF_POPUP, (UINT)m_menuFile, L"File");
		
		AppendMenu(m_menuFile, MF_STRING, MENU_FILE_OPEN, L"Open");
		AppendMenu(m_menuFile, MF_STRING | MF_GRAYED, MENU_FILE_SAVE, L"Save");
		AppendMenu(m_menuFile, MF_STRING, MENU_FILE_EXIT, L"Exit");

		SetMenu(m_hWnd, m_menu);
		
	}

	void MainWindow::CreateStatusBar()
	{
		m_statusBar = new StatusBar();
		m_statusBar->CreateWindowBW(STATUSCLASSNAME, NULL , WS_CHILDWINDOW | WS_VISIBLE | SBARS_SIZEGRIP, 0,
			0, 0, 0, 0, m_hWnd);

		RECT rect;
		GetClientRect(m_hWnd, &rect);

		int rightEdges[2];

		rightEdges[0] = rect.right / 2;
		rightEdges[1] = rect.right;

		// Tell the status bar to create the window parts.
		SendMessage(m_statusBar->GetWindow(), SB_SETPARTS, (WPARAM)2, (LPARAM)rightEdges);
	}

	MainWindow::MainWindow()
	{
		
	}
	MainWindow::~MainWindow()
	{
	}

	int MainWindow::MessageRoutine()
	{
		MSG msg = { };

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		return (int)msg.wParam;
	}

	ID2D1Factory* MainWindow::GetD2D1Factory()
	{
		return m_d2d1Factory;
	}

	IDWriteFactory* MainWindow::GetDWriteFactory()
	{
		return m_dwFactory;
	}

	StatusBar* MainWindow::GetStatusBar()
	{
		return m_statusBar;
	}
	
	bool string_to_double(const std::string& str, double& value)
	{
		std::istringstream i(str);
		if (!(i >> value))
			return false;
		return true;
	}

}

