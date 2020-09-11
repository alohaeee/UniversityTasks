#include "GUI_API_BaseApp.h"

#include "GUI_API_Window.h"



namespace GUI_API
{
	int BaseApp::getUniqueID()
	{
		static int lastID = 0;
		return lastID++;
	}
	BaseApp::BaseApp()
	{
		_id = getUniqueID();
	}


	int BaseApp::getID() const
	{
		return _id;
	}

	bool BaseApp::isActive() const
	{
		return _isActive;
	}

	void BaseApp::setActive(bool active)
	{
		_isActive = active;
		OnChangeActive.invoke(&active);
	}

	void BaseApp::destroy()
	{
		OnDestroy.invoke(&_id);
	}


}
