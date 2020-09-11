#pragma once
#include <SDL.h>

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "GUI_API_BaseApp.h"
#include "GUI_API_CallBack.h"





namespace GUI_API
{
	class Widget;
	class Application;

	using WidgetUniqueVector = std::vector<std::unique_ptr<Widget>>;

	class Window : public BaseApp
	{
	protected:
		SDL_Window* _window = nullptr;
		SDL_Renderer* _renderer = nullptr;
		// Pointer to Application object, root of program tree.
		Application* _application = nullptr;

		WidgetUniqueVector _widgets;
		// Queue of IDs of widgets that need to delete. 
		std::queue<int> _erasingWidgetQueue;

		public signalEmiters:
		void onCloseWindow();
	public:
		Window() = delete;
		explicit Window(std::string title, int xScreenPosition, int yScreenPosition, int width, int height, bool isFullScreen, Application* app);
		explicit Window(std::string title, int width, int height, Application* app);
		explicit Window(std::string title, int xScreenPosition, int yScreenPosition, int width, int height, Application* app);
		virtual ~Window();

		// Makes callback with application. Maybe override to change behaviour of window and application.
		virtual void baseInitialization();

		// Invoke render method from each widget.
		// Basically calling in Application windowsRender method.
		void widgetRender();
		// Invoke update method from each Widget.
		// Basically calling in Application windowsUpdate method.
		void widgetUpdate();
		// Check erasingWidgetQueue for new IDs.
		// Basically calling in Application windowsErasing method.
		void widgetErasing();

		// INTERFACE
		// Common method for initialization and creating logic of windows after them creating.
		virtual void initialization() = 0;
		// Additional update method.
		virtual void update() = 0;
		// Additional render method.
		virtual void render() = 0;

		// Return pointer to Renderer of current window.
		SDL_Renderer* getRenderer();


		// Return SDL Window ID.
		int getWindowID() const;


		// Create Widget of type T.
		// Arguments throw forward to constructor of Widget.
		// Calling initialization method of new Widget.
		// return -> Casted pointer to widget.
		template<class T = Widget, class ...TArgs>
		T* createWidget(TArgs&& ... mArgs)
		{
			T* widget(new T(std::forward<TArgs>(mArgs)...));

			std::unique_ptr<Widget> uPtr{ widget };
			uPtr->initialization();

			CallBack::setCallBack<Window>(this, &Window::eraseChildOnDestroy, uPtr->OnDestroy);

			_widgets.emplace_back(std::move(uPtr));

			return widget;
		}

	signals:
		Signal OnCloseWindow;

	public slots:
		void eraseChildOnDestroy(SlotParametr childID);
	};
}
