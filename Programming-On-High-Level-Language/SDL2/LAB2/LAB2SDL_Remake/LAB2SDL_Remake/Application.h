#pragma once
#include<SDL.h>
#include<memory>
#include<vector>


class Application
{
private:
	
	bool _isRunning = false;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	SDL_Event _events;

	SDL_TimerID repeatOnceFunctionTimer;
	SDL_TimerID customEventFunctionTimer;

	void init();
	void render();
	void setTimer(SDL_TimerID timer, SDL_TimerCallback callback, void* param);
public:
	Application() = delete;
	explicit Application(const char* title, int w, int h);
	~Application();
	void destroy();
	int run();

};

