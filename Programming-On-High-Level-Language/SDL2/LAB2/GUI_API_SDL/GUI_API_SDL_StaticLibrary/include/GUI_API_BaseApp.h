#pragma once
#include <vector>
#include <functional>
#include <iostream>


#define signals public
#define slots /*nothing*/
#define signalEmiters /*nothing*/


namespace GUI_API
{
	using SlotParametr = void*;
	using CallBackFunction = std::function<void(SlotParametr)>;
	using Slot = std::pair<CallBackFunction, int>;
	using Slots = std::vector<Slot>;

	/* ******
	Signal class.
	Store pointer of functions that need to invoke.
	****** */
	class Signal
	{
	public:
		Slots _slots;

		void invoke(void* argument)
		{
			for (auto& s : _slots)
			{
				s.first(argument);
			}
		}
	};

	/* ******
	Base App class.
	Base part of each element of application.
	Include ID Methods, common Interface, several signals and self state.
	****** */
	class BaseApp
	{
	private:
		static int getUniqueID();
	protected:
		int _id;
		bool _isActive = true;
	public:
		explicit BaseApp();
		virtual ~BaseApp() {};


		int getID() const;

		bool isActive() const;


		virtual void initialization() = 0;
		virtual void update() = 0;
		virtual void render() = 0;


	signals:
		Signal OnChangeActive;
		Signal OnDestroy;

	public signalEmiters:
		void setActive(bool active);
		virtual void destroy();
	public slots:


	};
}

