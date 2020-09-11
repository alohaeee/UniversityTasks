#pragma once
#include "SDLWidget.h"
#include <string>
#include <SDL_ttf.h>
#include <SDL.h>
#include <iostream>


class Label : SDLWidget
{
private:
	TTF_Font* _font;
	SDL_Texture* _texture;
	SDL_Rect _destinationRect;
	std::string _text;
	
public:
	Label(Application* app) : SDLWidget(app) 
	{

	}
	~Label()
	{
		SDL_DestroyTexture(_texture);
		TTF_CloseFont(_font);
	}

	void render() override
	{
		if(SDL_RenderCopy(_parent->GetRender(), _texture, nullptr, &_destinationRect) == -1) std::cerr << SDL_GetError() << std::endl;
	}
	void update() override
	{

	}
	void SetText(std::string text, SDL_Color color)
	{
		
		SDL_DestroyTexture(_texture);
		_text = text;
		SDL_Surface* temp = TTF_RenderUTF8_Solid(_font, _text.c_str(), color);
		_texture = SDL_CreateTextureFromSurface(_parent->GetRender(), temp);
		SDL_FreeSurface(temp);
		SDL_QueryTexture(_texture, nullptr, nullptr, &_destinationRect.w, &_destinationRect.h);
		

	}
	void SetFont(std::string path, int size)
	{
		_font = TTF_OpenFont(path.c_str(), size);
		if (_font == nullptr)
		{
			std::cerr << TTF_GetError() << std::endl;
			_parent->SetState(ErrorLog::BAD_FONT);
		}
	}
	void SetPosition(int x, int y)
	{
		_destinationRect.x = x;
		_destinationRect.y = y;

	}
};

