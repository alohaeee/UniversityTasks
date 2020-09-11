#include "Point2D.h"

#include "CoordinateField.h"


namespace winapi
{
	Point2D::Point2D()
	{
	}

	Point2D::~Point2D()
	{
	}
	bool Point2D::IsInclude(D2D1_POINT_2F point)
	{
		D2D1_RECT_F rectF = D2D1::RectF(m_d2d1Ellipse.point.x - m_d2d1Ellipse.radiusX, m_d2d1Ellipse.point.y - m_d2d1Ellipse.radiusY,
			m_d2d1Ellipse.point.x + m_d2d1Ellipse.radiusX, m_d2d1Ellipse.point.y + m_d2d1Ellipse.radiusY);

		if (rectF.left < point.x && point.x < rectF.right)
		{
			if (rectF.top < point.y && point.y < rectF.bottom)
			{
				return true;
			}
		}

		return false;
	}

	bool Point2D::IsWithin(D2D1_RECT_F outsideRect)
	{
		if (outsideRect.left < m_d2d1CartesianPoint.x && outsideRect.top > m_d2d1CartesianPoint.y)
		{
			if (outsideRect.right > m_d2d1CartesianPoint.x && outsideRect.bottom < m_d2d1CartesianPoint.y)
			{
				return true;
			}
		}
		return false;
	}

	void Point2D::Draw(CoordinateField* coordinateField)
	{
		m_d2d1Ellipse.point = coordinateField->FromCartesianToScreen(m_d2d1CartesianPoint);
		
		coordinateField->GetRenderTarget()->FillEllipse(m_d2d1Ellipse, coordinateField->GetSolidBrush());
	}

	D2D1_POINT_2F Point2D::GetScreenPoint() const
	{
		return m_d2d1Ellipse.point;
	}

	D2D1_POINT_2F Point2D::GetCartesianPoint() const
	{
		return m_d2d1CartesianPoint;
	}

	void Point2D::SetCartesianPoint(D2D1_POINT_2F point)
	{
		m_d2d1CartesianPoint = point;
	}

	void Point2D::SetCartesianPoint(float x, float y)
	{
		m_d2d1CartesianPoint = D2D1::Point2F(x, y);
	}
	
	void Point2D::setSize(float radius)
	{
		m_d2d1Ellipse.radiusX = radius;
		m_d2d1Ellipse.radiusY = radius;
	} 
}

