#include <windows.h>
#include "Resource.h"
#include <CommCtrl.h>

//---------------------------------------------------------------------------
HWND hWnd, hProgress;
HINSTANCE hInst;
DWORD IDC_TIMER, nCounter;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	DialogBox(hInst, MAKEINTRESOURCE(IDD_CONTROLS_DLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_PROGRESS_CLASS;
	InitCommonControlsEx(&InitCtrlEx);

	switch (Msg)
	{
	case WM_INITDIALOG:
		hProgress = CreateWindowEx(0, PROGRESS_CLASS, NULL,
			WS_CHILD | WS_VISIBLE,
			20, 20, 260, 17,
			hWndDlg, NULL, hInst, NULL);
		SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 220));
		SendMessage(hProgress, PBM_SETSTEP, (WPARAM)10, 0);
		SetTimer(hWndDlg, IDC_TIMER, 220, 0);
		nCounter = 0;
		return TRUE;

	case WM_TIMER:
		nCounter++;
		SendMessage(hProgress, PBM_STEPIT, 0, 0);
		if (nCounter == 10)
		{
			KillTimer(hWndDlg, IDC_TIMER);
		}
		break;

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