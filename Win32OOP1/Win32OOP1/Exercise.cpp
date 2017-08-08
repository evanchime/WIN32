#include <windows.h>
#include "WinApp.h"
#include "MainWnd.h"

//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG   Msg;
	LPCTSTR ClsName = L"Win32OOP";
	LPCTSTR WndName = L"Object-Oriented Win32 Programming";

	// Initialize the application class
	WApplication WinApp(hInstance, ClsName, MainWndProc);
	WinApp.Register();

	// Create the main window
	WWindow Wnd;
	Wnd.Create(hInstance, ClsName, WndName);
	// Display the main winow
	Wnd.Show();

	// Process the main window's messages
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		return 0;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
//---------------------------------------------------------------------------