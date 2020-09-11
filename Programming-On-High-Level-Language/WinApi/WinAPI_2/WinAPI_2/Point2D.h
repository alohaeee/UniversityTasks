#pragma once

#include <d2d1.h>

namespace winapi
{
	class CoordinateField;
	class Point2D
	{
	private:
		D2D1_ELLIPSE m_d2d1Ellipse = D2D1::Ellipse(D2D1::Point2F(),0.0f,0.0f);
		
		D2D1_POINT_2F m_d2d1CartesianPoint = D2D1::Point2F();
		
	public:
		Point2D();
		~Point2D();
		
		bool IsInclude(D2D1_POINT_2F point);
		bool IsWithin(D2D1_RECT_F outsideRect);
		void Draw(CoordinateField* coordinateField);

		D2D1_POINT_2F GetScreenPoint() const;
		D2D1_POINT_2F GetCartesianPoint() const;
		void SetCartesianPoint(D2D1_POINT_2F point);
		void SetCartesianPoint(float x, float y);
		
		void setSize(float radius);
		
	};
}
