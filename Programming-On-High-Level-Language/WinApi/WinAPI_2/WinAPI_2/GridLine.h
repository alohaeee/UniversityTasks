#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <functional>

namespace winapi
{
	using NumericPositionSetter = std::pair<std::function<D2D1_RECT_F(D2D1_POINT_2F)>, std::function<D2D1_RECT_F(D2D1_POINT_2F)>>;
	class CoordinateField;

	class GridLine
	{
	private:
		CoordinateField* m_coordinateField = nullptr;


		D2D1_POINT_2F m_d2d1BeginXAxisPoint = D2D1::Point2F();
		D2D1_POINT_2F m_d2d1EndXAxisPoint = D2D1::Point2F();

		D2D1_POINT_2F m_d2d1BeginYAxisPoint = D2D1::Point2F();
		D2D1_POINT_2F m_d2d1EndYAxisPoint = D2D1::Point2F();

		D2D1_POINT_2F m_d2d1GridScale = D2D1::Point2F();

		// Additional space beetwen marks and text.
		int m_deltaTextDraw = 10;
		// Using for indicate layout text height and width.
		int m_layoutLenght = 100;

		// AXIS stroke size
		int m_strokeAxis = 2;
		int m_strokeGrid = 1;
		
		/// <summary>
		/// Create pair of two functions that returns text rect of mark's text layout.
		/// </summary>
		/// <returns></returns>
		NumericPositionSetter CreateNumericSetter();
		
	
		int m_marksSize = 10;
		float m_drawStep = 2;

		D2D1_POINT_2F m_d2d1MarkStep = D2D1::Point2F(2,2);
		D2D1_POINT_2U m_d2d1MaxMarkCount = D2D1::Point2U(12,12);
		D2D1_POINT_2U m_d2d1MinMarkCount = D2D1::Point2U(6, 6);

		/// <summary>
		/// Drawing marks on xAxis and yAxis with grid and val of each mark.
		/// </summary>
		void DrawMarks();
	public:
		GridLine() = delete;
		explicit GridLine(CoordinateField* coordinateField);
		~GridLine();

		
		
		D2D1_POINT_2F CalculateMarkStep();
		D2D1_POINT_2F GetMarkStep() const;
		
		
		float& GetDrawStep();

		void Draw();
		void SetScale(D2D1_POINT_2F scale);
		/// <summary>
		/// Set position of line's axis points by translate 
		/// begin of coordinates(0,0) to screen.
		/// </summary>
		void SetAxisPosition();
		
		D2D1::ColorF d2d1ColorAxis = D2D1::ColorF(D2D1::ColorF::Black);
		D2D1::ColorF d2d1ColorGrid = D2D1::ColorF(D2D1::ColorF::Black);
		
	};
}