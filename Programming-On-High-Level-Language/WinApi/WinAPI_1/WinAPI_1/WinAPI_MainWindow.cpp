#include "WinAPI_MainWindow.h"
#include "WinAPI_Exception.h"


// Disabling deprecated error.
#pragma warning(disable : 4996)

namespace winapi
{
	LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_SIZE:
		{
			resize();
			break;
		}
		case WM_CREATE:
		{
			onCreate();
			break;
		}
		case WM_PAINT:
		{
			onPaint();
			break;
		}
		case WM_DESTROY:
			discardGraphicsResources();
			if (m_D2D1Factory) m_D2D1Factory->Release();
			if (m_DWFactory) m_DWFactory->Release();
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			m_isEllipseTime = !m_isEllipseTime;
			onPaint();
			break;
		default:
			return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		}
		return 0;
	}
	MainWindow::MainWindow()
	{
	}
	MainWindow::~MainWindow()
	{
	}
	void MainWindow::onCreate()
	{
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_D2D1Factory))) FastThrow();

		if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_DWFactory), reinterpret_cast<IUnknown * *>(&m_DWFactory)))) FastThrow();

		if (FAILED(m_DWFactory->CreateTextFormat(L"Arial", NULL,
			DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 40, L"Russia", &m_DWTextFormat))) FastThrow();
		m_DWTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_DWTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		auto dwVersion = GetVersion();

		auto dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
		auto dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
		m_versionText = L"WinApi Version: " + std::to_wstring(dwMajorVersion) + L"." + std::to_wstring(dwMinorVersion);
		
	}
	void MainWindow::messageRoutine()
	{
		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	void MainWindow::createGraphicsResources()
	{
		if (m_D2D1WindowRenderTarget == NULL)
		{
			RECT rc;
			GetClientRect(m_hWnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			auto hResult = m_D2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hWnd, size), &m_D2D1WindowRenderTarget);
			if (FAILED(hResult)) FastThrow();
			else
			{
				const D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Red);
				hResult = m_D2D1WindowRenderTarget->CreateSolidColorBrush(color, &m_D2D1Brush);

				if (FAILED(hResult)) FastThrow();
				calculateLayout();
			}
		}

	}
	void MainWindow::calculateLayout()
	{
		if (m_D2D1WindowRenderTarget != NULL)
		{
			D2D1_SIZE_F size = m_D2D1WindowRenderTarget->GetSize();
			const float x = size.width / 2;
			const float y = size.height / 2;

			m_rectF = D2D1::RectF(size.width * 0.1, size.height * 0.1, size.width * 0.9, size.height * 0.9);
			m_ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), size.width * 0.4f, size.height * 0.4f);
		}
	}
	void MainWindow::resize()
	{
		if (m_D2D1WindowRenderTarget != NULL)
		{
			RECT rc;
			GetClientRect(m_hWnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			m_D2D1WindowRenderTarget->Resize(size);
			calculateLayout();
			InvalidateRect(m_hWnd, NULL, FALSE);
		}
	}
	void MainWindow::onPaint()
	{
		createGraphicsResources();

		PAINTSTRUCT ps;
	
		BeginPaint(m_hWnd, &ps);

		m_D2D1WindowRenderTarget->BeginDraw();

		
		m_D2D1WindowRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
		
		if (m_isEllipseTime)
		{
			m_D2D1Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Aqua));
			m_D2D1WindowRenderTarget->FillEllipse(m_ellipse, m_D2D1Brush);
		}
		else
		{
			m_D2D1Brush->SetColor(D2D1::ColorF(D2D1::ColorF::PaleGreen));
			m_D2D1WindowRenderTarget->FillRectangle(m_rectF, m_D2D1Brush);
		}
		

		

		m_D2D1Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		m_D2D1WindowRenderTarget->DrawText(m_versionText.c_str(), m_versionText.length(), m_DWTextFormat, 
			D2D1::RectF(m_rectF.left, m_rectF.top, m_rectF.right, m_rectF.bottom/2), m_D2D1Brush);
		m_D2D1WindowRenderTarget->DrawText(L"Дубровский Владислав", ARRAYSIZE(L"Дубровский Владислав"), m_DWTextFormat,
			D2D1::RectF(m_rectF.left, m_rectF.bottom/2, m_rectF.right, m_rectF.bottom), m_D2D1Brush);
		
		
	
		auto hResult = m_D2D1WindowRenderTarget->EndDraw();
		if (FAILED(hResult) || hResult == D2DERR_RECREATE_TARGET)
		{
			discardGraphicsResources();
		}
		EndPaint(m_hWnd, &ps);
	}
	void MainWindow::discardGraphicsResources()
	{
		if (m_D2D1WindowRenderTarget) m_D2D1WindowRenderTarget->Release();
		if (m_D2D1Brush) m_D2D1Brush->Release();
		
	}
}