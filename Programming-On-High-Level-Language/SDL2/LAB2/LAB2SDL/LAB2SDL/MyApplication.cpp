#include "MyApplication.h"

#include "GUI_API_Media.h"
#include "GUI_API_CallBack.h"

#include "MainWindow.h"

MyApplication::MyApplication()
{
}

MyApplication::~MyApplication()
{
}

void MyApplication::initialization()
{
	GUI_API::Media::Fonts::loadFont("myfont.ttf", 30, "Pixel30");
	_window1 = createWindow<MainWindow>("Window 1", 200, SDL_WINDOWPOS_CENTERED, 400, 400, this);
	_window2 = createWindow<MainWindow>("Window 2", 800, SDL_WINDOWPOS_CENTERED, 400, 400, this);

	GUI_API::CallBack::setCallBack<MainWindow>(_window1, &MainWindow::setLabelMousePosition, _window2->OnChangeMousePosition);
	GUI_API::CallBack::setCallBack<MainWindow>(_window2, &MainWindow::setLabelMousePosition, _window1->OnChangeMousePosition);
}

void MyApplication::update()
{
	
}

void MyApplication::render()
{
}
