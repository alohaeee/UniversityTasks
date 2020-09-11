#include "GUI_API_Label.h"

#include "GUI_API_Window.h"
#include "GUI_API_Application.h"


namespace GUI_API
{


	inline void Label::setTextureUTF8()
	{
		SDL_DestroyTexture(_texture);
		SDL_Surface* surface = TTF_RenderUTF8_Solid(_font, _text.c_str(), _color);
		_texture = SDL_CreateTextureFromSurface(_parent->getRenderer(), surface);

		TTF_SizeText(_font, _text.c_str(), &_rect.w, &_rect.h);

		SDL_FreeSurface(surface);
	}

	Label::Label(Window* parent) : Widget(parent)
	{
	}

	Label::~Label()
	{
		SDL_DestroyTexture(_texture);
	}

	void Label::setFont(TTF_Font* font)
	{
		_font = font;
	}

	void Label::setTextUTF8(std::string text, SDL_Color color)
	{
		_text = text;
		_color = color;

		setTextureUTF8();
	}

	void Label::setTextUTF8(std::string text)
	{
		_text = text;

		setTextureUTF8();
	}

	void Label::setTextUTF8(SDL_Color color)
	{
		_color = color;

		setTextureUTF8();
	}

	void Label::initialization()
	{
	}

	void Label::update()
	{
	}

	void Label::render()
	{
		SDL_RenderCopy(_parent->getRenderer(), _texture, nullptr, &_rect);
	}
}