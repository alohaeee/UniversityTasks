#pragma once
#include <d2d1.h>
#include <dwrite.h>

#include "BaseWindow.h"
#include "DebugLogger.h"

#include <vector>
#include <memory>
#include <string>
#include <array>

namespace winapi
{
	class Point2D;
	class GridLine;

	// Convert to wstring with precision.
	std::wstring ToWStringPrecision(float value, D2D1_POINT_2F cartesianLenght);

	
	using UniquePointVector = std::vector<std::unique_ptr<Point2D>>;
	using VisiblePointVector = std::vector<Point2D*>;

	class CoordinateField : public BaseWindow
	{
	private:
		D2D1::ColorF m_d2d1ColorBG = D2D1::ColorF(D2D1::ColorF::Black);

		D2D1_POINT_2F m_d2d1ScaleAxis = D2D1::Point2F();
		D2D1_RECT_F m_d2d1CartesianRect = D2D1::RectF(-10,10,10,-10);

		const float k_translationMultiplier = 100;

		UniquePointVector m_uniquePointVector;
		VisiblePointVector m_visiblePointVector;
		constexpr int GetMaxCountPoints() { return 35; }
		inline D2D1::ColorF GetPointColor() { return D2D1::ColorF(D2D1::ColorF::Red); }

		Point2D* m_createdPoint = nullptr;
		inline D2D1::ColorF GetCreatedPointColor() { return D2D1::ColorF(D2D1::ColorF::GreenYellow); }
		Point2D* m_selectedPoint = nullptr;
		inline D2D1::ColorF GetSelectedPointColor() { return D2D1::ColorF(D2D1::ColorF::Blue); }

		void DrawCreatedPoint(D2D1::ColorF color);
		void DrawSelectedPoint(D2D1::ColorF color);

		GridLine* m_gridLine;

		const double k_minCartesianLength = 0.2;
		const double k_maxCartesianLength = 99999;
		
		POINT m_lastPoint = {};

		
		ID2D1HwndRenderTarget* m_d2d1RenderTarget;
		ID2D1SolidColorBrush* m_d2d1SolidBrush;
		IDWriteTextFormat* m_dwTextFormatX;
		IDWriteTextFormat* m_dwTextFormatY;

		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		void OnCreate();
		void OnPaint();
		void OnDestroy();

		void CreateGraphicResources();
		void DiscardGraphicResources();
		
		void OnLClick(D2D1_POINT_2F point);
		void OnDBLClick(D2D1_POINT_2F point);
		void OnKeyDown(int keyCode);

		void CalculateAxisScreenScale();

		/// <summary>
		/// Trivial method to translate view.
		/// Using for draging cartesian view.
		/// </summary>
		/// <param name="translationPoint">
		/// translate point where:
		///  x - translate for left and right in Cartesian View rectangle.
		///	 y - translate for top and bottom in Cartesian View rectangle.
		/// </param>
		void TranslateView(POINT translationPoint);

		void ScalingCartesian(float direction);
	public:
		CoordinateField();
		~CoordinateField();		



		

		void SetColorBG(D2D1::ColorF colorBackGround);
		D2D1_POINT_2F FromCartesianToScreen(D2D1_POINT_2F point);
		D2D1_POINT_2F FromCartesianToScreenFixed(D2D1_POINT_2F point);
		D2D1_POINT_2F FromScreenToCartesian(D2D1_POINT_2F point);
		D2D1_RECT_F GetCartesianRect() const;

		D2D1_POINT_2F CalculateCartesianLength();
		

		void AddPointVector(std::vector<D2D1_POINT_2F> cartesianPoints);
		std::vector<D2D1_POINT_2F> GetCartesianPoints();

		ID2D1HwndRenderTarget* GetRenderTarget();

		ID2D1SolidColorBrush* GetSolidBrush();
		IDWriteTextFormat* GetTextFormatX();
		IDWriteTextFormat* GetTextFormatY();
	};
}