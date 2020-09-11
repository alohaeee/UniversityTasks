#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include <memory>
#include <queue>

#include "GUI_API_BaseApp.h"


namespace GUI_API
{
	class Window;
	
	using WindowsUniqueVector = std::vector<std::unique_ptr<Window>>;

	class Application : public BaseApp
	{
	private:
		// Invoke update method from each Window.
		void windowsUpdate();
		// Invoke render method from each Window.
		void windowsRender();
		// Queue of !SDL! IDs of windows that need to delete. 
		std::queue<int> _erasingWindowQueue;
		// Invoke widgetsErasing method of each Window and check erasingWidgetQueue for new IDs.
		void windowsErasing();
	protected:
		WindowsUniqueVector _windows;
		static SDL_Event* _events;

		// Running state of application
		bool _isRunning = true;

		/*Application's Interace */

		// INTERFACE
		// Initialization method of application.
		// Calls one time in start of Application.
		virtual void initialization() = 0;
		// INTERFACE
		// Update method of application.
		// Additional update method.
		virtual void update() = 0;
		// INTERFACE
		// Update render of application.
		// Additional render method.
		virtual void render() = 0;


		// Create Window of type T.
		// Arguments throw forward to constructor of Window.
		// Calling baseInitialization and initialization methods of new Window.
		// return -> Casted pointer to window.
		template<class T = Window, class ...TArgs>
		T* createWindow(TArgs&& ... mArgs)
		{
			T* window(new T(std::forward<TArgs>(mArgs)...));

			std::unique_ptr<Window> uPtr{ window };


			uPtr->baseInitialization();
			uPtr->initialization();

			_windows.emplace_back(std::move(uPtr));

			return window;
		}


		protected signalEmiters:
		void destroy() override;

	public:
		explicit Application();
		virtual ~Application();


		// Main application method.
		// Invoking update, render, event methods while application state is Running.
		int run();

		// Return pointer to application's data of events.
		static SDL_Event* getEvents();


	public slots:
		void closeWindow(SlotParametr id);
		void onQuit(SlotParametr nothing);
	};
}
