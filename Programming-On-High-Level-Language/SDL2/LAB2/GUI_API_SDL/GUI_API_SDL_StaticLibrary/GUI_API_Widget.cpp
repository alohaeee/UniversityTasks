#include "GUI_API_Widget.h"

#include "GUI_API_Window.h"

namespace GUI_API
{

	Widget::Widget(Window* parent)
	{
		_parent = parent;
		_rect.x = _rect.y = 0;
		_rect.h = _rect.w = 0;
	}

	Widget::~Widget()
	{
	}

	void Widget::setPosition(int x, int y)
	{
		_rect.x = x;
		_rect.y = y;

		OnSetPosition.invoke(&_rect);
	}

	void Widget::setPositionCentered(int x, int y)
	{
		_rect.x = x - _rect.w / 2;
		_rect.y = y - _rect.h / 2;

		OnSetPosition.invoke(&_rect);
	}

	void Widget::setSize(int w, int h)
	{
		_rect.w = w;
		_rect.h = h;

		OnSetSize.invoke(&_rect);
	}

	SDL_Rect Widget::getRect()
	{
		return _rect;
	}

	SDL_Rect& Widget::getRefRect()
	{
		return _rect;
	}

	void Widget::setRect(SDL_Rect rect)
	{
		_rect = rect;
	}
}
