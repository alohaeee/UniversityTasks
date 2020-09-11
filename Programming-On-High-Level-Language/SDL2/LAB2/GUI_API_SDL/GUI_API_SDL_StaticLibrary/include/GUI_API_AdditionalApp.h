#pragma once


namespace GUI_API
{
	class AdditionalApp
	{
	public:
		virtual void baseUpdate() = 0;
		virtual void baseRender() = 0;
		virtual void baseInitialization() = 0;
	};
}
