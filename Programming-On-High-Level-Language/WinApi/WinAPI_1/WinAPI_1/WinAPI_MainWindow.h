#pragma once
#include "WinAPI_BaseWindow.h"
#include <d2d1.h>
#include <dwrite.h>
#include <string>

namespace winapi
{
	class MainWindow : public winapi::BaseWindow
	{
	private:
		ID2D1Factory* m_D2D1Factory = nullptr;
		ID2D1HwndRenderTarget* m_D2D1WindowRenderTarget = nullptr;
		ID2D1SolidColorBrush* m_D2D1Brush = nullptr;

		
		D2D1_ELLIPSE m_ellipse;
		D2D1_RECT_F m_rectF;
		bool m_isEllipseTime = true;

		IDWriteFactory* m_DWFactory;
		IDWriteTextFormat* m_DWTextFormat;
		

		std::wstring m_versionText;

		


		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	public:
		MainWindow();
		~MainWindow();
		void onCreate();
		void messageRoutine();
		void createGraphicsResources();
		void calculateLayout();
		void resize();
		void onPaint();
		void discardGraphicsResources();

	};
}
