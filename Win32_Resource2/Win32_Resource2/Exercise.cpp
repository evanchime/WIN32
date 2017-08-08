//---------------------------------------------------------------------------
#include <windows.h>
#include <CommCtrl.h>
#include "resource.h"


//---------------------------------------------------------------------------
wchar_t AppCaption[40];
HINSTANCE hInst;
//const int NUMBUTTONS = 7;
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG        Msg;
	HWND       hWnd;
	WNDCLASSEX WndClsEx;
	LPCTSTR ClsName = L"ResFund";
	//LPCTSTR WndName = L"Resources Fundamentals";

	LoadString(hInstance, IDS_APP_NAME, AppCaption, 40);

	hInst = hInstance;

	// Create the application window
	WndClsEx.cbSize = sizeof(WNDCLASSEX);
	WndClsEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc = WndProcedure;
	WndClsEx.cbClsExtra = 0;
	WndClsEx.cbWndExtra = 0;
	WndClsEx.hIcon = LoadIcon(hInstance,
		MAKEINTRESOURCE(IDI_RESFUND2));
	WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClsEx.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);
	WndClsEx.lpszClassName = ClsName;
	WndClsEx.hInstance = /*hInstance*/ hInst;
	WndClsEx.hIconSm = LoadIcon(hInstance,
		MAKEINTRESOURCE(IDI_RESFUND2));

	// Register the application
	RegisterClassEx(&WndClsEx);

	// Create the window object
	hWnd = CreateWindowEx(0,
		ClsName,
		/*WndName*/AppCaption,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// Find out if the window was created
	if (!hWnd) // If the window was not created,
		return FALSE; // stop the application

	TBADDBITMAP tbAddBitmap;
	tbAddBitmap.hInst = hInstance;
	tbAddBitmap.nID = IDB_BITMAP2;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hWnd, NULL, hInst, NULL);

	if (hWndToolbar == NULL)
		return NULL;

	const int numButtons = 7;

	int stdidx = SendMessage(hWndToolbar, TB_ADDBITMAP, numButtons, (LPARAM)&tbAddBitmap);


	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);

	
	TBBUTTON tbrButtons[numButtons] =
	{
		{ stdidx + 0, IDM_FILE_NEW, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 1, IDM_FILE_OPEN, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 2, IDM_ARROW, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 3, IDM_DRAW_LINE, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 4, IDM_DRAW_RECTANGLE, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 5, IDM_DRAW_ELLIPSE, TBSTATE_ENABLED, BTNS_BUTTON },
		{ stdidx + 6, 0, TBSTATE_ENABLED, BTNS_SEP },
	};


	// Add buttons.
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)tbrButtons);

	// Resize the toolbar, and then show it.
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Decode and treat the messages
	// as long as the application is running
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

		return Msg.wParam;
	//return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	default:
		// Process the left-over messages
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	// If something was not done, let it go
	return 0;
}
//---------------------------------------------------------------------------