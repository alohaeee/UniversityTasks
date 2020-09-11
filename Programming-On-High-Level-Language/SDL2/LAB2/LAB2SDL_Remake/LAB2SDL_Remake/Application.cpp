#include "Application.h"
#include <iostream>
#include <SDL_ttf.h>
#include "EventFilter.h"
#include <exception>

Application::Application(const char* title, int w, int h)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) std::exception(static_cast<const char*>(SDL_GetError()));
	if (TTF_Init() == -1) throw std::exception(static_cast<const char*>(TTF_GetError()));

	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (_window) std::cerr << "Ok Window" << std::endl;
	else std::exception(static_cast<const char*>(SDL_GetError()));

	_renderer = SDL_CreateRenderer(_window, -1, NULL);
	if (_renderer) std::cerr << "Ok Renderer" << std::endl;
	else std::exception(static_cast<const char*>(SDL_GetError()));
	

}

Application::~Application()
{

}

void Application::destroy()
{
	SDL_RemoveTimer(repeatOnceFunctionTimer);
	SDL_RemoveTimer(customEventFunctionTimer);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
	TTF_Quit();
}



void Application::init()
{
	_isRunning = true;
}



void Application::render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	SDL_RenderPresent(_renderer);
}




int Application::run()
{
	SDL_SetEventFilter(eventFilter, nullptr);

	if (!(customEventFunctionTimer = SDL_AddTimer(2000 /* 2 sec */, customEventFunction, _window))) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create custom event timer. See the log for more info.", _window);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create custom event timer, error: %s", SDL_GetError());
	}

	if (!(repeatOnceFunctionTimer = SDL_AddTimer(10000 /* 10 sec */, repeatOnceFunction, _window))) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create repeat once timer. See the log for more info.", _window);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create repeat once timer, error: %s", SDL_GetError());
	}

	SDL_WaitEvent(NULL);
	

	destroy();
	return 0;
}

