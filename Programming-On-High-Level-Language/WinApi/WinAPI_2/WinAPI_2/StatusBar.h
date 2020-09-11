#pragma once



#include "BaseWindow.h"
#include <commctrl.h>

namespace winapi
{
	class StatusBar : public BaseWindow
	{
	private:
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	public:
		StatusBar();
		~StatusBar();
		int GetEventID();
		int GetFileID();
		void SendEventMessage(LPCWSTR message);
		void SendFileMessage(LPCWSTR message);
		
		
	};
}