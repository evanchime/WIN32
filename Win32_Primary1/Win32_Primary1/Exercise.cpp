#include <windows.h>
#include "Resource.h"

#ifdef __BORLANDC__
#pragma argsused
#endif
//---------------------------------------------------------------------------
HWND hWnd;
HINSTANCE hInst;
const char *ClsName = "CallingDlg";
const char *WndName = "Calling One Dialog Box From Another";
LRESULT CALLBACK DlgProcPrimary(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProcSecondary(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_PRIMARY_DLG),
		hWnd, (DLGPROC)DlgProcPrimary);

	hInst = hInstance;
	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProcPrimary(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_SECOND_BTN:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SECOND_DLG),
				hWnd, (DLGPROC)DlgProcSecondary);
			return FALSE;
		case IDCANCEL:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProcSecondary(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam)
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
		case IDCANCEL:
			EndDialog(hWndDlg, 0);
			return TRUE;

		}
		break;
	}

	return FALSE;
}
//---------------------------------------------------------------------------
