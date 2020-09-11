#pragma once
#include "GUI_API_Window.h"

namespace GUI_API 
{
	class Label;
	class Button;
}


class MainWindow : public GUI_API::Window
{
protected:
	GUI_API::Label* _mousePositionLabel = nullptr;
	GUI_API::Button* _button = nullptr;
	GUI_API::Label* _StatusLabel = nullptr;
	bool isSendingMousePosition = true;

private signalEmiters:
	void onChangeMousePosition();

public:
	
	MainWindow() = delete;
	explicit MainWindow(std::string title, int width, int height, GUI_API::Application* app);
	explicit MainWindow(std::string title, int screenXPosition, int screenYPosition, int width, int height, GUI_API::Application* app);
	~MainWindow() {}

	void baseInitialization() override;
	void initialization() override;
	void update() override;

signals:
	GUI_API::Signal OnChangeMousePosition;

public slots:
	void dragButtonOnRightClick(GUI_API::SlotParametr buttonID);
	void setLabelMousePosition(GUI_API::SlotParametr position);
	void changeStateOfSending(GUI_API::SlotParametr buttonID);
};