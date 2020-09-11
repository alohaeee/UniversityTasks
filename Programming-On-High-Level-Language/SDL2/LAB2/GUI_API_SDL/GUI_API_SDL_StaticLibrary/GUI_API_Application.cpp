#include "GUI_API_Application.h"

#include "GUI_API_Window.h"
#include "GUI_API_ErrorLoger.h"
#include "GUI_API_Media.h"

#include <iostream>
#include <algorithm>

namespace GUI_API
{
	SDL_Event* Application::_events = new SDL_Event();

	Application::Application()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throw ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);
		if (TTF_Init() == 1)
			throw ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);
	}

	Application::~Application()
	{
	}

	int Application::run()
	{
		try {
			initialization();
			while (_isRunning)
			{
				SDL_WaitEvent(_events);
				windowsUpdate();
				update();
				windowsRender();
				windowsErasing();
			}
			destroy();

			return 0;
		}
		catch (ErrorLoger& e)
		{
			std::cerr << e.what() << std::endl;
			destroy();
			return e.getErrorCode();
		};

	}

	SDL_Event* Application::getEvents()
	{
		return _events;
	}

	void Application::closeWindow(SlotParametr id)
	{
		auto idCasted = *static_cast<int*>(id);

		_erasingWindowQueue.push(idCasted);

	}


	void Application::windowsUpdate()
	{
		for (auto& w : _windows)
		{
			if (w->isActive())
			{
				w->widgetUpdate();
				w->update();
			}
		}
	}

	void Application::windowsRender()
	{
		for (auto& w : _windows)
		{
			if (w->isActive())
			{
				w->widgetRender();
			}
		}
	}

	void Application::windowsErasing()
	{
		for (auto& w : _windows)
		{
			w->widgetErasing();
		}

		while (!_erasingWindowQueue.empty())
		{
			auto id = _erasingWindowQueue.front();

			_windows.erase(std::remove_if(_windows.begin(), _windows.end(),
				[id](auto& w)
				{
					if (w->getWindowID() == id)
					{
						w->destroy();
						return true;
					}
					return false;
				}));
			_erasingWindowQueue.pop();
		}
		if (_windows.size() <= 0) _isRunning = false;
	}

	void Application::onQuit(SlotParametr nothing)
	{
		_isRunning = false;
	}

	void Application::destroy()
	{
		OnDestroy.invoke(nullptr);
		Media::Fonts::clearFonts();
		TTF_Quit();
		SDL_Quit();
	}

}