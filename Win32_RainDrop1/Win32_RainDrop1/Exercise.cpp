#include <windows.h>
#include <CommCtrl.h>
#include "resource.h"

#include "Exercise.h"

// This is for Visual C++
#pragma comment(lib, "COMCTL32.lib")
Exercise Exo;

//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG   Msg;
	LPCTSTR ClsName = L"Win32OOP";
	LPCTSTR WndName = L"Object-Oriented Win32 Programming";

	Exo.hInst = hInstance;


	// Initialize the Common Controls
	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);

	// Initialize the application class
	Exo.WinApp.Create(Exo.hInst, ClsName, MainWndProc);
	Exo.WinApp.Register();

	// Create the main window
	Exo.Wnd.Create(Exo.hInst, ClsName, WndName);
	// Display the main winow
	Exo.Wnd.Show();

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
	HDC hDC;
	static BOOL IsDrawing = FALSE;
	static int StartX, StartY;
	static int EndX, EndY;
	//UINT iButtonState;
	switch (Msg)
	{
	case WM_CREATE:
		Exo.hWndToolbar = Exo.CreateStandardToolbar(hWnd, Exo.hInst);
		SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_ARROW, TBSTATE_CHECKED | TBSTATE_ENABLED);
		return 0;

	case WM_ACTIVATE:
		Exo.Wnd.SetText(L"RainDrop - Untitled");
		return 0;

	case WM_LBUTTONDOWN:
		hDC = GetDC(hWnd);

		StartX = LOWORD(lParam);
		StartY = HIWORD(lParam);

		EndX = LOWORD(lParam);
		EndY = HIWORD(lParam);

		// If the Line button is down, draw with it
		if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_LINE, 0) & TBSTATE_CHECKED)
		{
			SetROP2(hDC, R2_XORPEN);

			MoveToEx(hDC, StartX, StartY, NULL);
			LineTo(hDC, EndX, EndY);
		}
		else if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_FREEHAND, 0) & TBSTATE_CHECKED)
		{
			StartX = LOWORD(lParam);
			StartY = HIWORD(lParam);
		}
		else if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_POLYLINE, 0) & TBSTATE_CHECKED)
		{
			SetROP2(hDC, R2_XORPEN);

			MoveToEx(hDC, StartX, StartY, NULL);
			LineTo(hDC, EndX, EndY);
		}

		IsDrawing = TRUE;

		ReleaseDC(hWnd, hDC);

		return 0;


	case WM_MOUSEMOVE:
		hDC = GetDC(hWnd);

		if (IsDrawing == TRUE)
		{
			SetROP2(hDC, R2_NOTXORPEN);

			// Find out if the Line button is clicked
			if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_LINE, 0) & TBSTATE_CHECKED)
			{
				MoveToEx(hDC, StartX, StartY, NULL);
				LineTo(hDC, EndX, EndY);

				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);

				MoveToEx(hDC, StartX, StartY, NULL);
				LineTo(hDC, EndX, EndY);
			}
			// Find out if the Polyline button is clicked
			else if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_FREEHAND, 0) & TBSTATE_CHECKED)
			{
				MoveToEx(hDC, EndX, EndY, NULL);
				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);
				LineTo(hDC, EndX, EndY);
			}
			else if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_POLYLINE, 0) & TBSTATE_CHECKED)
			{
				MoveToEx(hDC, StartX, StartY, NULL);
				LineTo(hDC, EndX, EndY);

				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);

				MoveToEx(hDC, StartX, StartY, NULL);
				LineTo(hDC, EndX, EndY);
			}
		}

		ReleaseDC(hWnd, hDC);
		break;


	case WM_LBUTTONUP:
		hDC = GetDC(hWnd);

		EndX = LOWORD(lParam);
		EndY = HIWORD(lParam);

		SetROP2(hDC, R2_XORPEN);

		MoveToEx(hDC, StartX, StartY, NULL);
		LineTo(hDC, EndX, EndY);

		if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_LINE, 0) & TBSTATE_CHECKED)
		{
			IsDrawing = FALSE;
		}

		if (SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_FREEHAND, 0) & TBSTATE_CHECKED)
		{
			IsDrawing = FALSE;
		}

		ReleaseDC(hWnd, hDC);

		break;
	
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// If the user press Esc, may be he/she was drawing a polyline
			// In that case, stop drawing
			IsDrawing = FALSE;
			break;

		default:
			break;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_FILE_NEW:
			break;

		case IDM_FILE_OPEN:
			break;

		case IDM_FILE_SAVE:
			break;

		case IDM_FILE_SAVEAS:
			break;

		case IDM_FILE_EXIT:
			PostQuitMessage(WM_QUIT);
			break;

		case IDM_DRAW_ARROW:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_ARROW, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hWnd, IDC_ARROW);
			break;

		case IDM_DRAW_FREEHAND:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_FREEHAND, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hWnd, MAKEINTRESOURCE(IDC_FREEHAND));
			break;

		case IDM_DRAW_LINE:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_LINE, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hWnd, MAKEINTRESOURCE(IDC_LINE));
			break;

		case IDM_DRAW_POLYLINE:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_POLYLINE, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hWnd, MAKEINTRESOURCE(IDC_POLYLINE));
			break;

		};
		return 0;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		return 0;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
Exercise::Exercise()
{
}
//---------------------------------------------------------------------------
HWND Exercise::CreateStandardToolbar(HWND hParent, HINSTANCE hInst)
{
	TBADDBITMAP tbAddBitmap;
	tbAddBitmap.hInst = hInst;
	tbAddBitmap.nID = IDB_STANDARD;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hParent, NULL, hInst, NULL);

	if (hWndToolbar == NULL)
		return NULL;

	const int numButtons = 9;

	int stdidx = SendMessage(hWndToolbar, TB_ADDBITMAP, numButtons, (LPARAM)&tbAddBitmap);

	TBBUTTON tbrButtons[numButtons] =
	{
		{ stdidx + 0, IDM_FILE_NEW, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 1, IDM_FILE_OPEN, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 2, IDM_FILE_SAVE, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 3,  IDM_FILE_PRINT, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 4, IDM_DRAW_ARROW, TBSTATE_ENABLED, BTNS_BUTTON | BTNS_GROUP | BTNS_CHECK },
		{ stdidx + 5, IDM_DRAW_FREEHAND, TBSTATE_ENABLED, BTNS_BUTTON | BTNS_GROUP | BTNS_CHECK },
		{ stdidx + 6, IDM_DRAW_LINE, TBSTATE_ENABLED, BTNS_BUTTON | BTNS_GROUP | BTNS_CHECK },
		{ stdidx + 7, IDM_DRAW_POLYLINE, TBSTATE_ENABLED, BTNS_BUTTON | BTNS_GROUP | BTNS_CHECK },
		{ stdidx + 8, 0, TBSTATE_ENABLED, BTNS_SEP },
	};


	// Add buttons.
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)tbrButtons);

	// Resize the toolbar, and then show it.
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	

	if (hWndToolbar == NULL)
		return NULL;
	return hWndToolbar;
}
//---------------------------------------------------------------------------
void Exercise::ChangeCurrentCursor(HWND hWnd, LPCTSTR cursor)
{
	HCURSOR crsCross;

	crsCross = LoadCursor(hInst, cursor);
	SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG)crsCross);
}
//---------------------------------------------------------------------------