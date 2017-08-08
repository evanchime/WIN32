#pragma once
#include "WinApp.h"
#include "MainWnd.h"
//---------------------------------------------------------------------------
class Exercise
{
public:
	Exercise();
	WWindow Wnd;
	HINSTANCE hInst;
	WApplication WinApp;
	TBADDBITMAP tbAddBitmap;
	HWND CreateStandardToolbar(HWND hParent, HINSTANCE hInst);
	HWND hWndToolbar;

public:
	void ChangeCurrentCursor(HWND hWnd, LPCTSTR cursor);
};
//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow);
//---------------------------------------------------------------------------
