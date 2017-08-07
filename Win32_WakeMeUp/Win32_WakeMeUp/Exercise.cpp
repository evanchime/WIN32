#include <windows.h>
#include <CommCtrl.h>
#include <Mmsystem.h>
#include <stdio.h>
#ifdef __BORLANDC__
#pragma argsused
#endif

#include "resource.h"

//---------------------------------------------------------------------------
HWND hWnd;
HINSTANCE hInst;
int DialogWidth;
int DialogHeight;
SYSTEMTIME tmeSet;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	DialogBox(hInst, MAKEINTRESOURCE(IDD_WAKEMEUP_DLG),
		hWnd, (DLGPROC)DlgProc);

	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_DATE_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM /*lParam*/)
{
	HDC hdc;
	HWND hWndDateTimePicker, hWndOK;

	LONG ptrStyles = GetWindowLongPtr(hWndDlg, GWL_STYLE);
	// This will represent the dimensions of the whole screen
	RECT rctClient;

	// Create a black brush
	HBRUSH BlackBrush;
	// Select the black brush
	HBRUSH oldBrush = NULL;

	hWndDateTimePicker = GetDlgItem(hWndDlg, IDC_TIMETOWAKEUP);
	hWndOK = GetDlgItem(hWndDlg, IDOK);

	SYSTEMTIME tmeCurrent;

	switch (Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDCANCEL:
			EndDialog(hWndDlg, 0);
			return TRUE;

		case IDC_SET_BTN:
			// Get the time that the user had set and store it
			// in the tmeSet variable
			DateTime_GetSystemtime(hWndDateTimePicker, &tmeSet);

			hdc = GetDC(hWndDlg);
			BlackBrush = CreateSolidBrush(RGB(0, 0, 0));

			SelectObject(hdc, BlackBrush);
			// TODO: Add your control notification handler code here
			// Get the screen dimensions
			DialogWidth = GetSystemMetrics(SM_CXSCREEN);
			DialogHeight = GetSystemMetrics(SM_CYSCREEN);

			// When sets the clock CD, remove the title bar and the borders
			ptrStyles &= ~WS_TILEDWINDOW;
			SetWindowLongPtr(hWndDlg, GWL_STYLE, ptrStyles);

			// Occupy the whole screen
			SetWindowPos(hWndDlg, HWND_TOPMOST, 0, 0, DialogWidth, DialogHeight, SWP_SHOWWINDOW);

			// Get the dimension of the current dialog box
			GetWindowRect(hWndDlg, &rctClient);

			// Paint the dialog box in black
			Rectangle(hdc, rctClient.left, rctClient.top, rctClient.right, rctClient.bottom);

			// Restore the original brush
			SelectObject(hdc, oldBrush);
			
			// Start the timer control
			SetTimer(hWndDlg, IDC_CHECKTIME, 2000, 0);
			
			// We don't need to see the cursor
			ShowCursor(FALSE);
			
			//release device context
			ReleaseDC(hWndDlg, hdc);


			return TRUE;
		}
		break;

	case WM_TIMER:
		// Get the current time on the computer
		GetLocalTime(&tmeCurrent);

		// Compare the current time with the time the user had set
		// If they are the same, then start playing the CD
		if ((tmeCurrent.wYear == tmeSet.wYear) &&
			(tmeCurrent.wMonth == tmeSet.wMonth) &&
			//(tmeCurrent.wDayOfWeek == tmeSet.wDayOfWeek) &&
			(tmeCurrent.wDay == tmeSet.wDay) &&
			(tmeCurrent.wHour == tmeSet.wHour) &&
			(tmeCurrent.wMinute == tmeSet.wMinute) /* &&
												   (tmeCurrent.wSecond == tmeSet.wSecond) &&
												   (tmeCurrent.wMilliseconds == tmeSet.wMilliseconds) */)
		{
			mciSendString(L"play cdaudio", NULL, 0, NULL);
		}
		break;

	case WM_CLOSE:
		PostQuitMessage(WM_QUIT);
		break;

	case WM_DESTROY:
		// However the user decides to close the dialog box,
		// stop playing the CD
		mciSendString(L"stop cdaudio", NULL, 0, NULL);
		KillTimer(hWndDlg, IDC_CHECKTIME);
		break;
	}

	return FALSE;
}
//---------------------------------------------------------------------------