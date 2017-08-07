#include <windows.h>
#ifdef __BORLANDC__
#pragma argsused
#endif

#include "resource.h"
#include <commctrl.h>
//---------------------------------------------------------------------------
HWND hWnd;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_CONTROLSDLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_PROGRESS_CLASS;
	InitCommonControlsEx(&InitCtrlEx);

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HWND hWndMonthCal;

	hWndMonthCal = GetDlgItem(hWndDlg, IDC_MONTHCALENDAR);

	switch (Msg)
	{
	case WM_INITDIALOG:
		SendMessage(hWndMonthCal, MCM_SETCOLOR, MCSC_TITLEBK, RGB(205, 50, 5));
		MonthCal_SetColor(hWndMonthCal, MCSC_TITLETEXT, RGB(255, 250, 5));
		MonthCal_SetColor(hWndMonthCal, MCSC_TEXT, RGB(128, 0, 5));
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDCANCEL:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
//---------------------------------------------------------------------------