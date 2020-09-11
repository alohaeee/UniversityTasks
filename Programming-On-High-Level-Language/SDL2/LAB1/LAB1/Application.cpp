#include "Application.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Widgets.h"

RectRender* rect;
Label* versionLabel;
Label* nameLabel;

Application::Application(const char* title, int w, int h)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) SetState(ErrorLog::BAD_INIT);
	if (TTF_Init() == -1) SetState(ErrorLog::BAD_INIT);

	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (_window) std::cerr << "Ok Window" << std::endl;
	else SetState(ErrorLog::BAD_WINDOW);

	_renderer = SDL_CreateRenderer(_window, -1, NULL);
	if (_renderer) std::cerr << "Ok Renderer" << std::endl;
	else SetState(ErrorLog::BAD_RENDERER);
	

}

Application::~Application()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
	TTF_Quit();
}


SDL_Renderer* Application::GetRender()
{
	return _renderer;
}

void Application::init()
{
	if (_currentState == ErrorLog::OKAY) _isRunning = true;
	rect = new RectRender(this);
	versionLabel = new Label(this);
	nameLabel = new Label(this);
	

	versionLabel->SetFont("myfont.ttf", 30);
	SDL_version linked;
	SDL_GetVersion(&linked);
	std::string linkedText = "SDL: " + std::to_string(linked.major) + '.' + std::to_string(linked.minor)+ '.' + std::to_string(linked.patch);

	versionLabel->SetText(linkedText, { 255,255,0 });
	versionLabel->SetPosition(0, 160);

	nameLabel->SetFont("myfont.ttf", 20);
	nameLabel->SetText("Дубровский Владислав.", {0, 255, 0} );
	nameLabel->SetPosition(0, 300);


	rect->SetRect(200, 50, 120, 120);
}

void Application::SetState(ErrorLog e)
{
	_currentState = e;
	destroy();
}


void Application::render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	rect->render();
	nameLabel->render();
	versionLabel->render();

	SDL_RenderPresent(_renderer);
}

void Application::eventUpdate()
{
	SDL_WaitEvent(&_events);
	switch (_events.type)
	{
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			break;
	};
}

void Application::destroy()
{
	_isRunning = false;
	delete versionLabel;
	delete nameLabel;
	delete rect;
	//exit(_currentState);
}
int Application::run()
{
	init();
	render();
	while (_isRunning)
	{
		eventUpdate();
	}
	destroy();

	return _currentState;
}

