#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#ifdef __BORLANDC__
#pragma argsused
#endif

#include "resource.h"

//---------------------------------------------------------------------------
HWND hWnd;
HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	DialogBox(hInst, MAKEINTRESOURCE(IDD_CONTROLS_DLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	HWND hWndScroller;
	SCROLLINFO si;
	int CurPos;
	wchar_t strPosition[20];

	hWndScroller = GetDlgItem(hWndDlg, IDC_SCROLLER);

	switch (Msg)
	{
	case WM_INITDIALOG:
		CurPos = 0;

		SecureZeroMemory(&si, sizeof(si));
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		si.nMin = 0;
		si.nMax = 240;
		si.nPage = 10;
		si.nPos = 54;
		SetScrollInfo(hWndScroller, SB_CTL, &si, TRUE);

		// safe form of wsprintf
		StringCchPrintfExW(strPosition, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"%d", si.nPos); 

		SetDlgItemText(hWndDlg, IDC_LABEL, strPosition);

		return TRUE;

	case WM_VSCROLL:
		SecureZeroMemory(&si, sizeof(si));
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;

		if (!GetScrollInfo(hWndScroller, SB_CTL, &si))
			break;
		CurPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_TOP:
			CurPos = 0;
			break;

		case SB_LINEUP:
			if (CurPos > 0)
				CurPos--;
			break;

		case SB_THUMBPOSITION:
			CurPos = HIWORD(wParam);
			break;

		case SB_THUMBTRACK:
			CurPos = HIWORD(wParam);
			break;

		case SB_LINEDOWN:
			if (CurPos < 240)
				CurPos++;
			break;

		case SB_BOTTOM:
			CurPos = 240;
			break;

		case SB_ENDSCROLL:
			break;
		}

		SecureZeroMemory(&si, sizeof(si));
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		si.nMin = 0;
		si.nMax = 240;
		si.nPage = 10;
		si.nPos = CurPos;
		SetScrollInfo(hWndScroller, SB_CTL, &si, TRUE);

		// safe form of wsprintf
		StringCchPrintfExW(strPosition, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"%d", CurPos);

		SetDlgItemText(hWndDlg, IDC_LABEL, strPosition);

		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_CLOSE_BTN:
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
	
