#include "GUI_API_Media.h"

#include "GUI_API_ErrorLoger.h"

namespace GUI_API
{
	namespace Media
	{
		std::map<std::string, TTF_Font*> Fonts::_fonts;

		void Fonts::loadFont(std::string path, int size, std::string key)
		{
			TTF_Font* font = TTF_OpenFont(path.c_str(), size);
			if (font == nullptr) throw ErrorLoger(TTF_GetError(), ErrorValue::BAD_LOAD);
			_fonts.insert(std::make_pair(key, font));
		}

		TTF_Font* Fonts::getFont(std::string key)
		{
			return _fonts.at(key);
		}

		void Fonts::clearFonts()
		{
			for (auto& p : _fonts)
			{
				TTF_CloseFont(p.second);
			}
			_fonts.clear();
		}

		void Fonts::eraseFont(std::string key)
		{
			_fonts.erase(key);
		}
	}
}
