#pragma once
#pragma once
#include <vector>
#include <memory>
#include "Application.h"
class SDLWidget
{

protected:
	Application* _parent;

public:
	SDLWidget(Application* parent) : _parent(parent) {};
	virtual ~SDLWidget() {};
	virtual void update() = 0;
	virtual void render() = 0;
};


