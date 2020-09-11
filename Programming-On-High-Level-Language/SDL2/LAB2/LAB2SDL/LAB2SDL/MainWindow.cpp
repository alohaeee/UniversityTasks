#include "MainWindow.h"

#include "GUI_API_Widgets.h"
#include "GUI_API_Application.h"
#include "GUI_API_CallBack.h"
#include "GUI_API_Media.h"
#include "GUI_API_Colors.h"



MainWindow::MainWindow(std::string title, int width, int height, GUI_API::Application* app) : GUI_API::Window(title, width, height, app)
{
}

MainWindow::MainWindow(std::string title, int screenXPosition, int screenYPosition, int width, int height, GUI_API::Application* app) : GUI_API::Window(title, screenXPosition, screenYPosition, width, height, app)
{
}



void MainWindow::onChangeMousePosition()
{
	if (GUI_API::Application::getEvents()->type == SDL_MOUSEMOTION)
	{
		bool isMouseInsideWindow = GUI_API::Application::getEvents()->window.windowID == getWindowID();
		if (isMouseInsideWindow)
		{
			SDL_Rect point;
			point.x = GUI_API::Application::getEvents()->motion.x;
			point.y = GUI_API::Application::getEvents()->motion.y;
			OnChangeMousePosition.invoke(&point);
		}
	}	
}

void MainWindow::dragButtonOnRightClick(GUI_API::SlotParametr buttonID)
{
	auto castedID = *static_cast<int*>(buttonID);
	if (castedID == SDL_BUTTON_RIGHT)
	{
		int x;
		int y;
		SDL_GetMouseState(&x, &y);
		SDL_Rect lateRect = _button->getRect();
		_button->setPositionCentered(x, y);

		int w;
		int h;
		SDL_GetWindowSize(_window, &w, &h);

		SDL_Rect buttonRect = _button->getRect();
		if (buttonRect.x < 0 || buttonRect.y < 0 ||
			buttonRect.x + buttonRect.w > w || buttonRect.y + buttonRect.h > h)
			_button->setPosition(lateRect.x, lateRect.y);
	}
}

void MainWindow::setLabelMousePosition(GUI_API::SlotParametr position)
{
	auto point = *static_cast<SDL_Rect*>(position);
	_mousePositionLabel->setTextUTF8(std::to_string(point.x) + " : " + std::to_string(point.y));
}

void MainWindow::changeStateOfSending(GUI_API::SlotParametr buttonID)
{
	auto castedID = *static_cast<int*>(buttonID);
	if (castedID == SDL_BUTTON_LEFT)
	{
		isSendingMousePosition = !isSendingMousePosition;
		isSendingMousePosition ? _StatusLabel->setTextUTF8("On", GUI_API::Color::Green) : _StatusLabel->setTextUTF8("Off", GUI_API::Color::Red);
	}
}


void MainWindow::baseInitialization()
{

}

void MainWindow::initialization()
{
	GUI_API::CallBack::setCallBack<GUI_API::Application>(_application, &GUI_API::Application::onQuit, OnCloseWindow);
	
	_mousePositionLabel = createWidget<GUI_API::Label>(this);

	_mousePositionLabel->setPosition(0, 0);
	_mousePositionLabel->setFont(GUI_API::Media::Fonts::getFont("Pixel30"));
	_mousePositionLabel->setTextUTF8("privet", GUI_API::Color::Red);
	
	_button = createWidget<GUI_API::Button>(this);
	
	_button->setSize(60, 60);
	_button->ButtonText->setFont(GUI_API::Media::Fonts::getFont("Pixel30"));
	_button->ButtonText->setTextUTF8("click", GUI_API::Color::White);
	_button->setPosition(120, 120);
	
	GUI_API::CallBack::setCallBack<MainWindow>(this, &MainWindow::changeStateOfSending, _button->OnClick);
	GUI_API::CallBack::setCallBack<MainWindow>(this, &MainWindow::dragButtonOnRightClick, _button->OnDrag);

	_StatusLabel = createWidget<GUI_API::Label>(this);
	_StatusLabel->setPosition(320, 320);
	_StatusLabel->setFont(GUI_API::Media::Fonts::getFont("Pixel30"));
	_StatusLabel->setTextUTF8("On", GUI_API::Color::Green);
}

void MainWindow::update()
{
	if (isSendingMousePosition)
	{
		onChangeMousePosition();
	}
	
}
