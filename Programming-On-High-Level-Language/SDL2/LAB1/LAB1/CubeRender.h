#pragma once
#include "SDLWidget.h"
class RectRender : SDLWidget
{
private:
	SDL_Rect _rect;
public:
	RectRender(Application* app) : SDLWidget(app)
	{
		SetRect(0, 0, 0, 0);
	}
	void SetRect(int x, int y, int w, int h)
	{
		_rect.x = x;
		_rect.y = y;
		_rect.w = w;
		_rect.h = h;
	}
	void SetColor(int r, int g, int b)
	{
		SDL_SetRenderDrawColor(_parent->GetRender(), r, g, b,SDL_ALPHA_OPAQUE);
	}
	void update() override
	{

	}
	void render() override
	{
		SetColor(255, 0, 0);
		SDL_RenderFillRect(_parent->GetRender(), &_rect);
	}
};

