#pragma once
#include "GUI_API_Widget.h"


namespace GUI_API
{
	class Label;

	class Button : public Widget
	{
	private:
		bool _isMouseInside = false;
		bool _isDraging = false;
		int _lastButtonID = 0;

		void mouseCollision();

		private signalEmiters:
		void mouseEvents();
		void onInside();

	public:
		Label* ButtonText = nullptr;

		Button() = delete;
		explicit Button(Window* parent);
		~Button();

		void initialization() override;
		void update() override;
		void render() override;

		void setPosition(int x, int y) override;
		void setPositionCentered(int x, int y) override;


	signals:
		Signal OnClick;
		Signal OnDrag;
		Signal OnInside;
	};
}