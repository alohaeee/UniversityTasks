#include "GUI_API_Button.h"

#include "GUI_API_Window.h"
#include "GUI_API_Label.h"
#include "GUI_API_Application.h"


namespace GUI_API
{
	void Button::mouseCollision()
	{
		if (Application::getEvents()->motion.type == SDL_MOUSEMOTION)
		{
			int xMousePosition;
			int yMousePosition;
			SDL_GetMouseState(&xMousePosition, &yMousePosition);
			bool onBottomXRange = _rect.x <= xMousePosition && xMousePosition <= _rect.x + _rect.w;
			bool onBottomYRange = _rect.y <= yMousePosition && yMousePosition <= _rect.y + _rect.h;
			bool isMouseInsideWindow = Application::getEvents()->window.windowID == _parent->getWindowID();

			_isMouseInside = onBottomXRange && onBottomYRange && isMouseInsideWindow;
		}

	}
	void Button::mouseEvents()
	{
		if (_isMouseInside)
		{
			if (Application::getEvents()->button.state == SDL_PRESSED && Application::getEvents()->button.type == SDL_MOUSEBUTTONDOWN)
			{
				if (!_isDraging)
				{
					int mouseBottomID = Application::getEvents()->button.button;
					OnClick.invoke(&mouseBottomID);
					_lastButtonID = mouseBottomID;
					_isDraging = true;
				}
			}
			else if (Application::getEvents()->button.state == SDL_RELEASED && Application::getEvents()->button.type == SDL_MOUSEBUTTONUP)
			{
				_isDraging = false;
			}

			if (_isDraging)
			{
				OnDrag.invoke(&_lastButtonID);
			}

		}
		else _isDraging = false;
	}


	void Button::onInside()
	{
		bool isInside = _isMouseInside;

		OnInside.invoke(&isInside);
	}

	Button::Button(Window* parent) : Widget(parent)
	{
		ButtonText = new Label(parent);
	}

	Button::~Button()
	{
	}

	void Button::initialization()
	{
		ButtonText->initialization();
	}

	void Button::update()
	{
		mouseCollision();
		mouseEvents();
		onInside();
		ButtonText->update();



	}

	void Button::render()
	{
		ButtonText->render();

		SDL_SetRenderDrawColor(_parent->getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(_parent->getRenderer(), &_rect);

	}

	void Button::setPosition(int x, int y)
	{
		_rect.x = x;
		_rect.y = y;

		auto textRect = ButtonText->getRect();

		int textXCentre = _rect.x + _rect.w / 2;
		int xText = textXCentre - textRect.w / 2;
		int yText = _rect.y + _rect.h / 2 - textRect.h / 2;

		ButtonText->setPosition(xText, yText);

		OnSetPosition.invoke(&_rect);
	}

	void Button::setPositionCentered(int x, int y)
	{
		_rect.x = x - _rect.w / 2;
		_rect.y = y - _rect.h / 2;

		auto textRect = ButtonText->getRect();

		int textXCentre = _rect.x + _rect.w / 2;
		int xText = textXCentre - textRect.w / 2;
		int yText = _rect.y + _rect.h / 2 - textRect.h / 2;

		ButtonText->setPosition(xText, yText);

		OnSetPosition.invoke(&_rect);
	}
}
