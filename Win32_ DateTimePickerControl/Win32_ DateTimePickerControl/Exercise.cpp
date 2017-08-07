#include <windows.h>
#include "Resource.h"
#include <CommCtrl.h>

//---------------------------------------------------------------------------
HWND hWnd;
HINSTANCE hInstGlobal;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInstGlobal = hInstance;

	DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_EXERCISE_DLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(icex);
	icex.dwICC = ICC_DATE_CLASSES;

	InitCommonControlsEx(&icex);
	switch (msg)
	{
	case WM_INITDIALOG:
		/*CreateWindowEx(0,
			DATETIMEPICK_CLASS,
			TEXT("DateTime"),
			WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHOWNONE,
			10, 10, 220, 20,
			hWndDlg,
			NULL,
			hInstGlobal,
			NULL);*/
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;

	case WM_CLOSE:
		PostQuitMessage(WM_QUIT);
		break;
	}

	return FALSE;
}
//---------------------------------------------------------------------------