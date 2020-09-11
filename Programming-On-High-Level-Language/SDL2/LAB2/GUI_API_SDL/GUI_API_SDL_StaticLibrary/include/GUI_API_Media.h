#pragma once
#include <string>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

namespace GUI_API
{
	namespace Media
	{

		class Fonts
		{
		private:
			static std::map<std::string, TTF_Font*> _fonts;
		public:

			static void loadFont(std::string path, int size, std::string key);
			static TTF_Font* getFont(std::string key);

			static void clearFonts();

			static void eraseFont(std::string key);
		};
	}
}