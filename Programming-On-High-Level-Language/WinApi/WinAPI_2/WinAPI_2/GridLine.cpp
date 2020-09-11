#include "GridLine.h"

#include "MainWindow.h"
#include "CoordinateField.h"

#include <string>
#include <sstream>

namespace winapi
{

	NumericPositionSetter GridLine::CreateNumericSetter()
	{
		auto fontSize = m_coordinateField->GetTextFormatX()->GetFontSize();
		auto fontHeightCheck = fontSize * 2;
		auto size = m_coordinateField->GetRenderTarget()->GetPixelSize();

		
		NumericPositionSetter numericSetter;
		
		if (m_d2d1BeginYAxisPoint.y + fontHeightCheck > size.height)
		{
			m_coordinateField->GetTextFormatY()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			numericSetter.first = [this](D2D1_POINT_2F point)
			{
				return D2D1::RectF(point.x, point.y - m_marksSize - m_deltaTextDraw, point.x + m_layoutLenght, point.y - m_marksSize);
			};
		}
		else
		{
			m_coordinateField->GetTextFormatY()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			numericSetter.first = [this,fontSize](D2D1_POINT_2F point)
			{
				
				return D2D1::RectF(point.x-m_deltaTextDraw, point.y - m_layoutLenght, point.x + m_layoutLenght, point.y + m_deltaTextDraw + m_marksSize+fontSize);
			};
		}

		if (m_d2d1BeginXAxisPoint.x - fontHeightCheck < 0)
		{
			m_coordinateField->GetTextFormatY()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
			numericSetter.second = [this](D2D1_POINT_2F point)
			{
				return D2D1::RectF(point.x + m_marksSize + m_deltaTextDraw, point.y + m_deltaTextDraw, point.x + m_marksSize + m_deltaTextDraw + m_layoutLenght,
					point.y);
			};
		}
		else
		{
			m_coordinateField->GetTextFormatY()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			numericSetter.second = [this](D2D1_POINT_2F point)
			{
				return D2D1::RectF(point.x - m_layoutLenght, point.y + m_deltaTextDraw, point.x - m_marksSize - m_deltaTextDraw , point.y);
			};
		}
		return numericSetter;
	}

	void GridLine::DrawMarks()
	{
		auto cartesianRect = m_coordinateField->GetCartesianRect();
		auto cartesianLength = m_coordinateField->CalculateCartesianLength();
		auto screenSize = m_coordinateField->GetRenderTarget()->GetPixelSize();

		// Comparators for identify end of drawing.
		auto compLess = [](int x, int y) { return x <= y; };
		auto compBigger = [](int x, int y) { return x >= y; };


		auto numericPositionSetter = CreateNumericSetter();
		
		auto xDrawer = [this,numericPositionSetter,cartesianLength,screenSize](float from, float to, float step, std::function<bool(float,float)> comparator)
		{
			for (;comparator(from,to); from+=step)
			{
				
				if (from != 0)
				{
					auto point = m_coordinateField->FromCartesianToScreen(D2D1::Point2F(from, 0));
					// Dump marks if Axis is dump.
					if (point.y < 0) point.y = 0;
					if (point.y > screenSize.height) point.y = screenSize.height;

					// Draw Grid.
					m_coordinateField->GetSolidBrush()->SetColor(d2d1ColorGrid);
					m_coordinateField->GetRenderTarget()->DrawLine(D2D1::Point2F(point.x, 0), D2D1::Point2F(point.x, screenSize.height), 
						m_coordinateField->GetSolidBrush(), m_strokeGrid);

					// Draw Mark.
					m_coordinateField->GetSolidBrush()->SetColor(d2d1ColorAxis);	
					m_coordinateField->GetRenderTarget()->DrawLine(D2D1::Point2F(point.x, point.y + m_marksSize), D2D1::Point2F(point.x, point.y - m_marksSize),
						m_coordinateField->GetSolidBrush(), m_strokeAxis);

					// Draw Text.
					auto layoutRect = numericPositionSetter.first(point);
					auto valueString = ToWStringPrecision(from, cartesianLength);
					
					m_coordinateField->GetRenderTarget()->DrawTextW(valueString.c_str(), valueString.size(), m_coordinateField->GetTextFormatX(), layoutRect, 
						m_coordinateField->GetSolidBrush());
				}
			}	
		};

		auto yDrawer = [this,numericPositionSetter, cartesianLength, screenSize](float from, float to, float step, std::function<bool(float, float)> comparator)
		{
			for (; comparator(from, to); from += step)
			{
				auto point = m_coordinateField->FromCartesianToScreen(D2D1::Point2F(0, from));

				if (from != 0)
				{
					// Dump marks if Axis is dump.
					if (point.x < 0) point.x = 0;
					if (point.x > screenSize.width) point.x = screenSize.width;
					// Draw Grid.
					m_coordinateField->GetSolidBrush()->SetColor(d2d1ColorGrid);
					m_coordinateField->GetRenderTarget()->DrawLine(D2D1::Point2F(0, point.y), D2D1::Point2F(screenSize.width, point.y), 
						m_coordinateField->GetSolidBrush(), m_strokeGrid);

					// Draw Mark.
					m_coordinateField->GetSolidBrush()->SetColor(d2d1ColorAxis);
					m_coordinateField->GetRenderTarget()->DrawLine(D2D1::Point2F(point.x + m_marksSize, point.y), D2D1::Point2F(point.x - m_marksSize, point.y),
						m_coordinateField->GetSolidBrush(), m_strokeAxis);

					// Draw Text.
					auto layoutRect = numericPositionSetter.second(point);
					auto valueString = ToWStringPrecision(from,cartesianLength);

					m_coordinateField->GetRenderTarget()->DrawTextW(valueString.c_str(), valueString.size(), m_coordinateField->GetTextFormatY(), layoutRect,
						m_coordinateField->GetSolidBrush());
				}
				
			}
		};
		

		// Aproximate begin point.
		auto toAproxValue = [](float value, float del)
		{
			return std::trunc(value / del) * del;
		};

		auto beginAprox = D2D1::Point2F();
		if (cartesianRect.left > 0)
		{
			beginAprox.x = toAproxValue(cartesianRect.left, cartesianLength.x);
		}
		else if (cartesianRect.right < 0)
		{
			beginAprox.x = toAproxValue(cartesianRect.right, cartesianLength.x);
		}
		if (cartesianRect.top < 0)
		{
			beginAprox.y = toAproxValue(cartesianRect.top, cartesianLength.y);
		}
		else if (cartesianRect.bottom > 0)
		{
			beginAprox.y = toAproxValue(cartesianRect.bottom, cartesianLength.y);
		}
		
		// Draw.
		xDrawer(beginAprox.x, cartesianRect.right, m_d2d1MarkStep.x, compLess);
		xDrawer(beginAprox.x, cartesianRect.left, -m_d2d1MarkStep.x, compBigger);
		yDrawer(beginAprox.y, cartesianRect.top, m_d2d1MarkStep.x, compLess);
		yDrawer(beginAprox.y, cartesianRect.bottom, -m_d2d1MarkStep.x, compBigger);
		
	}

	GridLine::GridLine(CoordinateField* coordinateField) : m_coordinateField(coordinateField)
	{
		auto size = m_coordinateField->GetRenderTarget()->GetPixelSize();

		m_d2d1BeginXAxisPoint.y = 0.0f;
		m_d2d1EndXAxisPoint.y = size.height;

		m_d2d1BeginYAxisPoint.x = 0.0f;
		m_d2d1EndYAxisPoint.x = size.width;
	}
	GridLine::~GridLine()
	{
	}

	D2D1_POINT_2F GridLine::CalculateMarkStep()
	{
		auto length = m_coordinateField->CalculateCartesianLength();

		if (length.x / m_d2d1MarkStep.x >= m_d2d1MaxMarkCount.x)
		{
			m_d2d1MarkStep.x = length.x / m_d2d1MinMarkCount.x;
		}
		else if (length.x / m_d2d1MarkStep.x <= m_d2d1MinMarkCount.x)
		{
			m_d2d1MarkStep.x = length.x / m_d2d1MaxMarkCount.x;
		}

		if (length.y / m_d2d1MarkStep.y >= m_d2d1MaxMarkCount.y)
		{
			m_d2d1MarkStep.y = length.y / m_d2d1MinMarkCount.y;
		}
		else if (length.y / m_d2d1MarkStep.y <= m_d2d1MinMarkCount.y)
		{
			m_d2d1MarkStep.y = length.y / m_d2d1MaxMarkCount.y;
		}

		return m_d2d1MarkStep;
	}

	D2D1_POINT_2F GridLine::GetMarkStep() const
	{
		return m_d2d1MarkStep;
	}

	float& GridLine::GetDrawStep()
	{
		return m_drawStep;
	}

	void GridLine::Draw()
	{
		m_coordinateField->GetSolidBrush()->SetColor(d2d1ColorAxis);
		

		m_coordinateField->GetRenderTarget()->DrawLine(m_d2d1BeginYAxisPoint, m_d2d1EndYAxisPoint, m_coordinateField->GetSolidBrush(), m_strokeAxis);
		m_coordinateField->GetRenderTarget()->DrawLine(m_d2d1BeginXAxisPoint, m_d2d1EndXAxisPoint, m_coordinateField->GetSolidBrush(), m_strokeAxis);
		
		DrawMarks();
	}
	void GridLine::SetScale(D2D1_POINT_2F scale)
	{
		auto multiplier = 100;
		m_d2d1GridScale.x = (1 / scale.x) * 100;
		m_d2d1GridScale.y = (1 / scale.y) * 100;
	}

	void GridLine::SetAxisPosition()
	{
		auto screenPoint = m_coordinateField->FromCartesianToScreenFixed	(D2D1::Point2F(0.0f, 0.0f));

		m_d2d1BeginXAxisPoint.x = screenPoint.x;
		m_d2d1EndXAxisPoint.x = screenPoint.x;

		m_d2d1BeginYAxisPoint.y = screenPoint.y;
		m_d2d1EndYAxisPoint.y = screenPoint.y;
	}

}
