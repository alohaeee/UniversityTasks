#pragma once
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GUI_API_Widget.h"



namespace GUI_API
{
	class Label : public Widget
	{
	protected:
		TTF_Font* _font = nullptr;
		std::string _text;
		SDL_Texture* _texture = nullptr;
		SDL_Color _color = { 0,0,0 };

		void setTextureUTF8();
	public:
		Label() = delete;
		explicit Label(Window* parent);
		~Label();

		void setFont(TTF_Font* font);

		void setTextUTF8(std::string text, SDL_Color color);
		void setTextUTF8(std::string text);
		void setTextUTF8(SDL_Color color);


		void initialization() override;
		void update() override;
		void render() override;

	};
}