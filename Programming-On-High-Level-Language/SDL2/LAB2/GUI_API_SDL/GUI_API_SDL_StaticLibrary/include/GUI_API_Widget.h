#pragma once
#include <SDL.h>

#include "GUI_API_BaseApp.h"

#include <string>



namespace GUI_API
{
	class Window;
	class Widget : public BaseApp
	{
	protected:
		Window* _parent = nullptr;
		SDL_Rect _rect;
	public:
		Widget() = delete;
		explicit Widget(Window* parent);
		virtual ~Widget();

		virtual void initialization() = 0;
		virtual void update() = 0;
		virtual void render() = 0;

		SDL_Rect getRect();
		SDL_Rect& getRefRect();
		void setRect(SDL_Rect rect);

		public signalEmiters:
		virtual void setPosition(int x, int y);
		virtual void setPositionCentered(int x, int y);
		virtual void setSize(int w, int h);
	signals:
		Signal OnSetPosition;
		Signal OnSetSize;
	};
}
