#pragma once
#include<SDL.h>
#include<memory>
#include<vector>
enum ErrorLog
{
	OKAY, BAD_WINDOW, BAD_RENDERER, BAD_INIT, BAD_FONT
};

class Application
{
private:
	ErrorLog _currentState = ErrorLog::OKAY;
	bool _isRunning = false;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _events;

protected:
	void init();
	void render();
	void eventUpdate();
	void destroy();
public:
	
	Application(const char* title, int w, int h);
	~Application();
	int run();
	SDL_Renderer* GetRender();
	void SetState(ErrorLog e);

};

