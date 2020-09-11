#pragma once
#include <vector>
#include <functional>
#include <algorithm>

#include "GUI_API_BaseApp.h"





namespace GUI_API
{
	class CallBack
	{
	public:
		// Push back pointer of function to Signal.
		template<class T>
		static void setCallBack(BaseApp* slotObject, void(T::* slot)(void*), Signal& signal)
		{
			CallBackFunction callback = std::bind(slot, (T*)slotObject, std::placeholders::_1);
			signal._slots.push_back(std::make_pair(callback, slotObject->getID()));
		}
		// Erase pointer of function from Signal if it exist.
		template<class T>
		static void unsetCallBack(BaseApp* slotObject, void(T::* slot)(void*), Signal& signal)
		{
			CallBackFunction callback = std::bind(slot, (T*)slotObject, std::placeholders::_1);

			auto name = callback.target_type().name();
			auto objectId = slotObject->getID();

			signal._slots.erase(std::remove_if(signal._slots.begin(), signal._slots.end(),
				[name, objectId](Slot& slot)
				{
					return slot.second == objectId && slot.first.target_type().name() == name;
				}));
		}
	};
}