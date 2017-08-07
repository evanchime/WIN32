#include <windows.h>
#include "Resource.h"

#ifdef __BORLANDC__
#pragma argsused
#endif
//---------------------------------------------------------------------------
HINSTANCE hInst;
const wchar_t *ClsName = L"CallingDlg";
const wchar_t *WndName = L"Calling a Dialog Box From an SDI";
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG        Msg;
	HWND       hWnd;
	WNDCLASSEX WndClsEx;

	// Create the application window
	WndClsEx.cbSize = sizeof(WNDCLASSEX);
	WndClsEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc = WndProcedure;
	WndClsEx.cbClsExtra = 0;
	WndClsEx.cbWndExtra = 0;
	WndClsEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClsEx.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	WndClsEx.lpszClassName = ClsName;
	WndClsEx.hInstance = hInstance;
	WndClsEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register the application
	RegisterClassEx(&WndClsEx);
	hInst = hInstance;

	// Create the window object
	hWnd = CreateWindowEx(0,
		ClsName,
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

	// Find out if the window was created
	if (!hWnd) // If the window was not created,
		return 0; // stop the application

				  // Display the window to the user
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// Decode and treat the messages
	// as long as the application is running
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_FILE_EXIT:
			PostQuitMessage(WM_QUIT);
			break;
		case IDM_HELP_ABOUT:
			DialogBox(hInst,
				MAKEINTRESOURCE(IDD_ABOUTDLGBOX),
				hWnd,
				reinterpret_cast<DLGPROC>(DlgProc));
			break;
		}
		return 0;

		// If the user wants to close the application
	case WM_DESTROY:
		// then close it
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
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
//---------------------------------------------------------------------------