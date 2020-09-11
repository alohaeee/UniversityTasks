#pragma once
#include <d2d1.h>
#include <dwrite.h>

#include "BaseWindow.h"
#include "StatusBar.h"
#include "DebugLogger.h"

// Debug leak
#include <crtdbg.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

namespace winapi
{
	template<class T>
	void safeRelease(T*& unknown)
	{
		if (unknown)
		{
			unknown->Release();
			unknown = nullptr;
		}
	};

	class CoordinateField;

	class MainWindow : public BaseWindow
	{
	private:
		static ID2D1Factory* m_d2d1Factory;
		static IDWriteFactory* m_dwFactory;

		static StatusBar* m_statusBar;
		CoordinateField* m_coordinateField = nullptr;


		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		HMENU m_menuFile;
		HMENU m_menu;
	
		bool m_isOpened = false;

		WCHAR m_fileName[250] = { 0 };

		void OnCreate();
		void OnPaint();
		void OnDestroy();
		void OnCommand(int menuID);
		void OnOpen();
		void OnSave();

		void CreateMenuBar();
		void CreateStatusBar();
		
	public:
		MainWindow();
		~MainWindow();

		int MessageRoutine();

		static ID2D1Factory* GetD2D1Factory();
		static IDWriteFactory* GetDWriteFactory();
		static StatusBar* GetStatusBar();
	};

	bool string_to_double(const std::string& str, double& value);
	
}