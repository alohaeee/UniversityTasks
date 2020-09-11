#include "CoordinateField.h"

#include "MainWindow.h"
#include "Point2D.h"
#include "GridLine.h"

#include "Exception.h"

#include <sstream>
#include <algorithm>

#include <windowsx.h>

namespace winapi
{
	void CoordinateField::DrawCreatedPoint(D2D1::ColorF color)
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hWnd, &ps);

		m_d2d1RenderTarget->BeginDraw();
		m_d2d1SolidBrush->SetColor(color);
		m_createdPoint->Draw(this);

		COMThrowOnFail(m_d2d1RenderTarget->EndDraw());

		EndPaint(m_hWnd, &ps);
	}
	void CoordinateField::DrawSelectedPoint(D2D1::ColorF color)
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hWnd, &ps);
		m_d2d1RenderTarget->BeginDraw();

		m_d2d1SolidBrush->SetColor(color);
		m_selectedPoint->Draw(this);

		COMThrowOnFail(m_d2d1RenderTarget->EndDraw());

		EndPaint(m_hWnd, &ps);
	}
	LRESULT CoordinateField::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_CREATE:
			OnCreate();
			break;
		case WM_PAINT:
			OnPaint();
			break;
		case WM_DESTROY:
			OnDestroy();
			break;
		case WM_KEYDOWN:
			OnKeyDown(wParam);
			break;
		case WM_LBUTTONDBLCLK:
			OnDBLClick(D2D1::Point2F(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			break;
		case WM_LBUTTONDOWN:
			OnLClick(D2D1::Point2F(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			break;
		case WM_MOUSEMOVE:
		{
			POINT mousePoint = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

			if (DragDetect(m_hWnd, mousePoint))
			{
				POINT translationPoint = { m_lastPoint.x - mousePoint.x   , mousePoint.y - m_lastPoint.y };

				TranslateView(translationPoint);

				SendMessage(m_hWnd, WM_PAINT, NULL, NULL);
			}
			m_lastPoint = mousePoint;
			break;
		}
		case WM_MOUSEWHEEL:
		{
			float delta = GET_WHEEL_DELTA_WPARAM(wParam);

			ScalingCartesian(delta);
			SendMessage(m_hWnd, WM_PAINT, NULL, NULL);
			break;
		}
		default:
			return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		}
		return 0;
	}
	void CoordinateField::OnCreate()
	{
		CreateGraphicResources();
		CalculateAxisScreenScale();

		m_gridLine = new GridLine(this);
		m_gridLine->SetAxisPosition();
		m_gridLine->d2d1ColorAxis = D2D1::ColorF(D2D1::ColorF::Aqua);
		m_gridLine->d2d1ColorGrid = D2D1::ColorF(D2D1::ColorF::Black);		
	}

	void CoordinateField::OnPaint()
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hWnd, &ps);

		m_d2d1RenderTarget->BeginDraw();

		m_d2d1RenderTarget->Clear(m_d2d1ColorBG);

		m_gridLine->Draw();

		m_d2d1SolidBrush->SetColor(GetPointColor());

		m_visiblePointVector.clear();
		for (auto& p : m_uniquePointVector)
		{
			if (p->IsWithin(m_d2d1CartesianRect))
			{
				p->Draw(this);
				m_visiblePointVector.push_back(p.get());
			}
		}
		if (m_createdPoint)
		{
			m_d2d1SolidBrush->SetColor(GetCreatedPointColor());
			m_createdPoint->Draw(this);
		}
		if (m_selectedPoint)
		{
			m_d2d1SolidBrush->SetColor(GetSelectedPointColor());
			m_selectedPoint->Draw(this);
		}
		
		COMThrowOnFail(m_d2d1RenderTarget->EndDraw());

		EndPaint(m_hWnd, &ps);
	}

	void CoordinateField::OnDestroy()
	{
		DiscardGraphicResources();

		delete m_gridLine;
	}

	void CoordinateField::CreateGraphicResources()
	{
		RECT rc;
		GetClientRect(m_hWnd, &rc);

		auto size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	

		COMThrowOnFail(MainWindow::GetD2D1Factory()->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hWnd, size),
			&m_d2d1RenderTarget));
		

		COMThrowOnFail(m_d2d1RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_d2d1SolidBrush));

		COMThrowOnFail(MainWindow::GetDWriteFactory()->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
			12, L"Russia", &m_dwTextFormatX));
		m_dwTextFormatX->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_dwTextFormatX->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

		COMThrowOnFail(MainWindow::GetDWriteFactory()->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
			12, L"Russia", &m_dwTextFormatY));
		m_dwTextFormatY->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		m_dwTextFormatY->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	void CoordinateField::DiscardGraphicResources()
	{
		safeRelease(m_d2d1SolidBrush);
		safeRelease(m_d2d1RenderTarget);
		safeRelease(m_dwTextFormatX);
		safeRelease(m_dwTextFormatY);
	}

	void CoordinateField::OnLClick(D2D1_POINT_2F point)
	{
		auto cartesianPoint = FromScreenToCartesian(point);
		point = FromCartesianToScreen(cartesianPoint);

		std::wstring position;

		auto finded = std::find_if(m_visiblePointVector.begin(), m_visiblePointVector.end(), [point](Point2D* element)
			{
				return element->IsInclude(point);
			});


		if (finded != m_visiblePointVector.end())
		{
			position += L"Click on point: (";
			
			if (m_selectedPoint) DrawSelectedPoint(GetPointColor());

			m_selectedPoint = *finded;
			DrawSelectedPoint(GetSelectedPointColor());

			if (m_createdPoint && m_createdPoint != m_selectedPoint)
			{
				DrawCreatedPoint(GetPointColor());
				m_createdPoint = nullptr;
			}
		}
		else
		{
			if (m_selectedPoint)
			{
				DrawSelectedPoint(GetPointColor());
				m_selectedPoint = nullptr;
			}

			if (m_createdPoint)
			{
				DrawCreatedPoint(GetPointColor());
				m_createdPoint = nullptr;
			}
			
			position += L"Left click: (";
		}
		
		position+=std::to_wstring(cartesianPoint.x) + L" ; " + std::to_wstring(cartesianPoint.y) + L")";
		MainWindow::GetStatusBar()->SendEventMessage(position.c_str());
	}

	void CoordinateField::OnDBLClick(D2D1_POINT_2F point)
	{
		auto cartesianPoint = FromScreenToCartesian(point);
		point = FromCartesianToScreen(cartesianPoint);

		if (std::find_if(m_visiblePointVector.begin(), m_visiblePointVector.end(), [point](Point2D* element)
			{
				return element->IsInclude(point);
			}) != m_visiblePointVector.end()) return;

		if (m_uniquePointVector.size() > GetMaxCountPoints())
		{
			std::wstring limit = L"Get limit of points - " + std::to_wstring(GetMaxCountPoints()) + L"!";
			MainWindow::GetStatusBar()->SendEventMessage(limit.c_str());
			return;
		}

		Point2D* point2D = new Point2D();
		std::unique_ptr<Point2D> uPtr{ point2D };

		uPtr->SetCartesianPoint(cartesianPoint);
		uPtr->setSize(5);

		m_uniquePointVector.emplace_back(std::move(uPtr));
		m_visiblePointVector.push_back(point2D);

		m_createdPoint = point2D;

		std::wstring position = L"Point create on : (" + std::to_wstring(cartesianPoint.x) + L" ; " + std::to_wstring(cartesianPoint.y) + L")";
		MainWindow::GetStatusBar()->SendEventMessage(position.c_str());

		DrawCreatedPoint(GetCreatedPointColor());
		if (m_selectedPoint)
		{
			DrawSelectedPoint(GetPointColor());
			m_selectedPoint = nullptr;
		}
	}

	void CoordinateField::OnKeyDown(int keyCode)
	{
		if (keyCode == VK_BACK)
		{
			if (m_selectedPoint)
			{
				auto cartesianPoint = m_selectedPoint->GetCartesianPoint();
				m_visiblePointVector.erase(std::remove_if(m_visiblePointVector.begin(), m_visiblePointVector.end(), [this](auto& point)
					{
						return m_selectedPoint == point;
					}),m_visiblePointVector.end());
				m_uniquePointVector.erase(std::remove_if(m_uniquePointVector.begin(), m_uniquePointVector.end(), [this](std::unique_ptr<Point2D>& point)
					{
						return m_selectedPoint == point.get();
					}), m_uniquePointVector.end());

				m_selectedPoint = nullptr;

				std::wstring position = L"Point deleted on : (" + std::to_wstring(cartesianPoint.x) + L" ; " + std::to_wstring(cartesianPoint.y) + L")";
				MainWindow::GetStatusBar()->SendEventMessage(position.c_str());

				SendMessage(m_hWnd, WM_PAINT, NULL, NULL);
			}
		}
	}

	void CoordinateField::CalculateAxisScreenScale()
	{
		auto renderTargetSize = m_d2d1RenderTarget->GetSize();
		
		m_d2d1ScaleAxis.x = renderTargetSize.width / (m_d2d1CartesianRect.right - m_d2d1CartesianRect.left);
		m_d2d1ScaleAxis.y = -renderTargetSize.height / (m_d2d1CartesianRect.top - m_d2d1CartesianRect.bottom);
	}
	CoordinateField::CoordinateField() 
	{

	}
	CoordinateField::~CoordinateField()
	{

	}
	

	void CoordinateField::TranslateView(POINT translationPoint)
	{
		auto length = CalculateCartesianLength();
		// Make translation above 
		auto xAxisTranslation = length.x / k_translationMultiplier;
		auto yAxisTranslation = length.y / k_translationMultiplier;
		
		auto normalizer = [](int value)
		{
			if (value > 0)
				return 1;
			else if (value < 0)
				return -1;
			return 0;
		};
		
		// Normalize and multiply by axis translation.
		xAxisTranslation *= normalizer(translationPoint.x);
		yAxisTranslation *= normalizer(translationPoint.y);
		
		auto lastRect = m_d2d1CartesianRect;
		// Add translation to View.
		m_d2d1CartesianRect.left += xAxisTranslation;
		m_d2d1CartesianRect.right += xAxisTranslation;
		m_d2d1CartesianRect.bottom += yAxisTranslation;
		m_d2d1CartesianRect.top += yAxisTranslation;
		

		std::wstring message = L"Translate on (" + std::to_wstring(xAxisTranslation) + L" ; " + std::to_wstring(yAxisTranslation) + L")";
		MainWindow::GetStatusBar()->SendEventMessage(message.c_str());

		// Apply changes to grid.
		CalculateAxisScreenScale();
		m_gridLine->SetAxisPosition();
		
	}
	void CoordinateField::ScalingCartesian(float direction)
	{
		if (direction > 0)
		{
			direction = -1;
		}
		else
		{
			direction = 1;
		}

		auto length = CalculateCartesianLength();
		if (length.x <= k_minCartesianLength && direction < 0) return;
		else if (length.x >= k_maxCartesianLength && direction > 0) return;
		if (length.y <= k_minCartesianLength && direction < 0) return;
		else if (length.y >= k_maxCartesianLength && direction > 0) return;

		auto markStep = m_gridLine->CalculateMarkStep();

		auto delta = D2D1::Point2F(direction * markStep.x / 2, direction * markStep.y / 2);
		
		m_d2d1CartesianRect.left -= delta.x;
		m_d2d1CartesianRect.right += delta.x;
		m_d2d1CartesianRect.bottom -= delta.x;
		m_d2d1CartesianRect.top += delta.x;

		std::wstring message = L"Zoom on (" + ToWStringPrecision(delta.x,length) + L" ; " + ToWStringPrecision(delta.y, length) + L")";
		MainWindow::GetStatusBar()->SendEventMessage(message.c_str());

		CalculateAxisScreenScale();
		m_gridLine->SetAxisPosition();
	}
	void CoordinateField::SetColorBG(D2D1::ColorF colorBackGround)
	{
		m_d2d1ColorBG = colorBackGround;
	}

	D2D1_POINT_2F CoordinateField::FromCartesianToScreen(D2D1_POINT_2F point)
	{
		D2D1_POINT_2F screenPoint;
		
		screenPoint.x = (point.x - m_d2d1CartesianRect.left) * m_d2d1ScaleAxis.x;
		screenPoint.y = (point.y - m_d2d1CartesianRect.top) * m_d2d1ScaleAxis.y;
	
		return screenPoint;
	}

	D2D1_POINT_2F CoordinateField::FromCartesianToScreenFixed(D2D1_POINT_2F point)
	{
		auto screenPoint = FromCartesianToScreen(point);
		
		auto size = m_d2d1RenderTarget->GetSize();

		if (screenPoint.x < 0) screenPoint.x = 0;
		else if (screenPoint.x > size.width) screenPoint.x = size.width;

		if (screenPoint.y < 1) screenPoint.y = 0;
		else if (screenPoint.y > size.height) screenPoint.y = size.height;

		return screenPoint;
	}

	D2D1_POINT_2F CoordinateField::FromScreenToCartesian(D2D1_POINT_2F screenPoint)
	{
		D2D1_POINT_2F cartesianPoint;
		
		
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		auto length = CalculateCartesianLength();

		cartesianPoint.x = screenPoint.x * length.x / rc.right+ m_d2d1CartesianRect.left;
		cartesianPoint.y = -screenPoint.y * length.y / rc.bottom + m_d2d1CartesianRect.top;

		return cartesianPoint;
	}

	D2D1_RECT_F CoordinateField::GetCartesianRect() const
	{
		return m_d2d1CartesianRect;
	}

	D2D1_POINT_2F CoordinateField::CalculateCartesianLength()
	{
		auto scale = D2D1::Point2F(m_d2d1CartesianRect.right - m_d2d1CartesianRect.left, m_d2d1CartesianRect.top - m_d2d1CartesianRect.bottom);
		return scale;
	}


	void CoordinateField::AddPointVector(std::vector<D2D1_POINT_2F> cartesianPoints)
	{
		m_visiblePointVector.clear();
		m_uniquePointVector.clear();

		std::array<D2D1_POINT_2F, 4> edgesPoints;
		std::fill(edgesPoints.begin(), edgesPoints.end(), cartesianPoints[0]);

		D2D1_RECT_F cartesianRect = D2D1::RectF(cartesianPoints[0].x, cartesianPoints[0].y, cartesianPoints[0].x, cartesianPoints[0].y);

		for (auto& cP : cartesianPoints)
		{
			if (m_uniquePointVector.size() >= GetMaxCountPoints()) break;

			//if (cartesianRect.left > cP.x) cartesianRect.left = cP.x;
			//if (cartesianRect.top < cP.y) cartesianRect.top = cP.y;
			//if (cartesianRect.right < cP.x) cartesianRect.right = cP.x;
			//if (cartesianRect.bottom > cP.y) cartesianRect.bottom = cP.y;

			Point2D* point2D = new Point2D();
			std::unique_ptr<Point2D> uPtr{ point2D };

			uPtr->SetCartesianPoint(cP);
			uPtr->setSize(5);

			m_uniquePointVector.emplace_back(std::move(uPtr));
		}
		
	/*	
		m_d2d1CartesianRect = cartesianRect;
		
		CalculateAxisScreenScale();
		m_gridLine->SetAxisPosition();*/
		SendMessage(m_hWnd, WM_PAINT, NULL, NULL);
	}

	std::vector<D2D1_POINT_2F> CoordinateField::GetCartesianPoints()
	{
		std::vector<D2D1_POINT_2F> cartesianPoints;

		for (auto& p : m_uniquePointVector)
		{
			cartesianPoints.push_back(p->GetCartesianPoint());
		}
		return cartesianPoints;
	}

	ID2D1HwndRenderTarget* CoordinateField::GetRenderTarget()
	{
		return m_d2d1RenderTarget;
	}

	ID2D1SolidColorBrush* CoordinateField::GetSolidBrush()
	{
		return m_d2d1SolidBrush;
	}

	IDWriteTextFormat* CoordinateField::GetTextFormatX()
	{
		return m_dwTextFormatX;
	}

	IDWriteTextFormat* CoordinateField::GetTextFormatY()
	{
		return m_dwTextFormatY;
	}



	std::wstring ToWStringPrecision(float value, D2D1_POINT_2F cartesianLenght)
	{
		std::wstringstream sstream;
		if (abs(value) > 1000)
		{
			sstream << std::scientific;
			sstream.precision(1);
		}
		else if (cartesianLenght.x < 0.1)
		{
			sstream << std::scientific;
			sstream.precision(1);
		}
		else if (cartesianLenght.x < 1)
		{
			sstream << std::fixed;
			sstream.precision(2);
		}
		else if (cartesianLenght.x < 10)
		{
			sstream << std::fixed;
			sstream.precision(1);
		}
		else
		{
			sstream << std::fixed;
			sstream.precision(0);
		}

		sstream << value;
		std::wstring str;
		sstream >> str;
		return str;
	}

}

