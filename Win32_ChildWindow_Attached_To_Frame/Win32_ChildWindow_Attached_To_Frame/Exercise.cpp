#include <windows.h>
#include "resource.h"

HINSTANCE hInst;
LPTSTR strAppName = L"WndFrame";
LPTSTR WndName = L"Attaching a child window to an application's frame";
LPTSTR strToolbox = L"WndFloater";

HWND   hWndMainFrame, hWndToolbox;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ToolboxProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG   msg;
	RECT rect;
	WNDCLASSEX  WndClsEx;

	WndClsEx.cbSize = sizeof(WNDCLASSEX);
	WndClsEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc = MainWndProc;
	WndClsEx.cbClsExtra = 0;
	WndClsEx.cbWndExtra = 0;
	WndClsEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndClsEx.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	WndClsEx.lpszClassName = strAppName;
	WndClsEx.hInstance = hInstance;
	WndClsEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WndClsEx))
		return (FALSE);

	hInst = hInstance;

	hWndMainFrame = CreateWindowEx(0,
		strAppName,
		WndName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWndMainFrame)
		return (FALSE);


	// Create a child window based on the available dialog box
	hWndToolbox = CreateDialog(hInst,
		MAKEINTRESOURCE(IDD_TOOLBOX_DLG),
		hWndMainFrame,
		(DLGPROC)ToolboxProc);

	ShowWindow(hWndToolbox, SW_SHOW);
	ShowWindow(hWndMainFrame, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK ToolboxProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu;
	RECT rctMainWnd, rctToolbox;
	UINT ToolboxMenuState;
	MENUITEMINFO MenuItem;

	switch (Msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_VIEW_TOOLBOX:
			hMenu = GetMenu(hWndMainFrame);
			ToolboxMenuState = GetMenuState(hMenu, IDM_VIEW_TOOLBOX, MF_BYCOMMAND);
			if (LOBYTE(ToolboxMenuState) & MF_CHECKED)
			{
				MENUITEMINFO MenuItem = { sizeof(MENUITEMINFO), MIIM_STATE, 0, MFS_UNCHECKED, 0,
												NULL, NULL, NULL, 0, NULL, 0, NULL };
				SetMenuItemInfo(hMenu, IDM_VIEW_TOOLBOX, false, &MenuItem);
				//CheckMenuItem(hMenu, IDM_VIEW_TOOLBOX, MF_BYCOMMAND | MF_UNCHECKED);
				ShowWindow(hWndToolbox, SW_HIDE);
			}
			else
			{
				MENUITEMINFO MenuItem = { sizeof(MENUITEMINFO), MIIM_STATE, 0, MFS_CHECKED, 0,
												NULL, NULL, NULL, 0, NULL, 0, NULL };
				SetMenuItemInfo(hMenu, IDM_VIEW_TOOLBOX, false, &MenuItem);
				//CheckMenuItem(hMenu, IDM_VIEW_TOOLBOX, MF_BYCOMMAND | MF_CHECKED);
				ShowWindow(hWndToolbox, SW_SHOW);
			}
			break;

		case IDM_FILE_EXIT:
			PostQuitMessage(WM_QUIT);
			return 0;
		};
		break;

	case WM_SIZE:
		GetClientRect(hWndMainFrame, &rctMainWnd);
		GetWindowRect(hWndToolbox, &rctToolbox);

		SetWindowPos(hWndToolbox,
			HWND_TOP,
			rctMainWnd.left,
			rctMainWnd.top,
			rctToolbox.right - rctToolbox.left,
			rctMainWnd.bottom,
			SWP_NOACTIVATE | SWP_NOOWNERZORDER);

		break;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}
//---------------------------------------------------------------------------