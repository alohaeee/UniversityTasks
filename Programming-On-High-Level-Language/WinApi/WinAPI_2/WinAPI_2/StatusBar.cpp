#include "StatusBar.h"

LRESULT winapi::StatusBar::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	
	default:
		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

winapi::StatusBar::StatusBar()
{
}

winapi::StatusBar::~StatusBar()
{
}

int winapi::StatusBar::GetEventID()
{
	return 0;
}

int winapi::StatusBar::GetFileID()
{
	return 1;
}

void winapi::StatusBar::SendEventMessage(LPCWSTR message)
{
	SendMessage(m_hWnd, SB_SETTEXT, (WPARAM)GetEventID(), LPARAM(message));
}

void winapi::StatusBar::SendFileMessage(LPCWSTR message)
{
	SendMessage(m_hWnd, SB_SETTEXT, (WPARAM)GetFileID(), LPARAM(message));
}
