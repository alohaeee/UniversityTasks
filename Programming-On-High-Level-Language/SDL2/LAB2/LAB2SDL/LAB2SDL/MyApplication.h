#pragma once
#include "GUI_API_Application.h"


class MainWindow;
 
class MyApplication : public GUI_API::Application
{
private:
	MainWindow* _window1 = nullptr;
	MainWindow* _window2 = nullptr;
public:
	MyApplication();
	~MyApplication();

	void initialization() override;
	void update() override;
	void render() override;
};