#include <windows.h>
#include "resource.h"

HINSTANCE hInst;
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG        Msg;
	HWND       hWnd;
	WNDCLASSEX WndClsEx;

	hInst = hInstance;

	const wchar_t *ClsName = L"MenuApplied";
	const wchar_t *WndName = L"Techniques of Using Menus";

	// Create the application window
	WndClsEx.cbSize = sizeof(WNDCLASSEX);
	WndClsEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc = WndProcedure;
	WndClsEx.cbClsExtra = 0;
	WndClsEx.cbWndExtra = 0;
	WndClsEx.hIcon = LoadIcon(NULL, IDI_WARNING);
	WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	WndClsEx.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	WndClsEx.lpszClassName = ClsName;
	WndClsEx.hInstance = hInstance;
	WndClsEx.hIconSm = LoadIcon(NULL, IDI_WARNING);

	RegisterClassEx(&WndClsEx);

	hWnd = CreateWindow(ClsName,
		WndName,
		WS_OVERLAPPEDWINDOW,
		200,
		160,
		460,
		320,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
		return 0;

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	// Handle to a menu. This will be used with the context-sensitive menu
	HMENU hMenu;
	// Handle to the system menu
	HMENU hSysMenu;
	// Handle to the context menu that will be created
	HMENU hMenuTrackPopup;

	switch (Msg)
	{
	case WM_CREATE:
		// To modify the system menu, first get a handle to it
		hSysMenu = GetSystemMenu(hWnd, FALSE);
		// This is how to add a separator to a menu
		InsertMenu(hSysMenu, 2, MF_SEPARATOR, 0, L"-");
		// This is how to add a menu item using a string
		AppendMenu(hSysMenu, MF_STRING, 1, L"Practical Techniques");
		// This is how to add a menu item using a defined identifier
		AppendMenu(hSysMenu, MF_STRING, IDM_HELP_ABOUT, L"About...");
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_LARGE:
			MessageBox(hWnd, L"Menu Item Selected = Large", L"Message", MB_OK);
			break;

		case IDM_FILE_EXIT:
			PostQuitMessage(WM_QUIT);
			break;
		}
		return 0;

	case WM_CONTEXTMENU:
		// Get a handle to the popup menu using its resource
		if ((hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_POPUP))) == NULL)
			return 0;

		// Get a handle to the first shortcut menu
		hMenuTrackPopup = GetSubMenu(hMenu, 0);

		// Display the popup menu when the user right-clicks
		TrackPopupMenu(hMenuTrackPopup,
			TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			LOWORD(lParam),
			HIWORD(lParam),
			0,
			hWnd,
			NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}