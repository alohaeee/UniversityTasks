#include "GUI_API_Window.h"


#include "GUI_API_BaseApp.h"
#include "GUI_API_Widget.h"
#include "GUI_API_Application.h"

#include "GUI_API_ErrorLoger.h"
#include "GUI_API_CallBack.h"

#include "GUI_API_Colors.h"

namespace GUI_API
{

	void Window::widgetErasing()
	{
		while (!_erasingWidgetQueue.empty())
		{
			auto id = _erasingWidgetQueue.front();
			_widgets.erase(std::remove_if(_widgets.begin(), _widgets.end(),
				[id](auto& widget)
				{
					return widget->getID() == id;
				}
			));

			_erasingWidgetQueue.pop();
		}

	}

	Window::Window(std::string title, int xScreenPosition, int yScreenPosition, int width, int height, bool isFullScreen, Application* app) : _application(app)
	{
		_window = SDL_CreateWindow(title.c_str(), xScreenPosition, yScreenPosition, width, height, isFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
		if (_window == nullptr) throw  ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);

		_renderer = SDL_CreateRenderer(_window, -1, NULL);
		if (_renderer == nullptr) throw ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);
	}

	Window::Window(std::string title, int width, int height, Application* app) : _application(app)
	{
		_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if (_window == nullptr) throw  ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);

		_renderer = SDL_CreateRenderer(_window, -1, NULL);
		if (_renderer == nullptr) throw ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);
	}

	Window::Window(std::string title, int xScreenPosition, int yScreenPosition, int width, int height, Application* app) : _application(app)
	{
		_window = SDL_CreateWindow(title.c_str(), xScreenPosition, yScreenPosition, width, height, SDL_WINDOW_SHOWN);
		if (_window == nullptr) throw  ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);

		_renderer = SDL_CreateRenderer(_window, -1, NULL);
		if (_renderer == nullptr) throw ErrorLoger(SDL_GetError(), ErrorValue::BAD_INIT);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(_window);
		SDL_DestroyRenderer(_renderer);
	}

	void Window::baseInitialization()
	{
		CallBack::setCallBack<Application>(_application, &Application::closeWindow, OnCloseWindow);
		CallBack::setCallBack<Application>(_application, &Application::closeWindow, OnDestroy);
	}

	void Window::widgetRender()
	{
		SDL_RenderClear(_renderer);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(_renderer, nullptr);
		for (auto& w : _widgets)
		{
			if (w->isActive())
				w->render();
		}
		SDL_RenderPresent(_renderer);
	}

	void Window::widgetUpdate()
	{
		for (auto& w : _widgets)
		{
			if (w->isActive())
				w->update();
		}

		onCloseWindow();
	}

	SDL_Renderer* Window::getRenderer()
	{
		return _renderer;
	}

	int Window::getWindowID() const
	{
		return SDL_GetWindowID(_window);
	}

	void Window::eraseChildOnDestroy(SlotParametr childID)
	{
		auto castedID = *static_cast<int*>(childID);

		_erasingWidgetQueue.push(castedID);
	}

	void Window::onCloseWindow()
	{
		if (Application::getEvents()->window.event == SDL_WINDOWEVENT_CLOSE)
		{
			int ID = Application::getEvents()->window.windowID;
			OnCloseWindow.invoke(&ID);
		}
	}
}
