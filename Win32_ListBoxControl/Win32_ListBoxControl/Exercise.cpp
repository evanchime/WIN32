#include <windows.h>
#include <Windowsx.h>
#include "Resource.h"

//---------------------------------------------------------------------------
HWND hWnd;
HINSTANCE hInstGlobal;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInstGlobal = hInstance;

	DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_PRIMARYFAMILY_DLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND lbxPrimaryFamily;

	lbxPrimaryFamily = GetDlgItem(hWndDlg, IDC_PRIMARYFAMILY_LB);

	switch (msg)
	{
	case WM_INITDIALOG:
		/*CreateWindowEx(0,
			L"LISTBOX",
			TEXT("FamilyListing"),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			10, 10, 140, 120,
			hWndDlg,
			NULL,
			hInstGlobal,
			NULL);*/
		ListBox_AddString(lbxPrimaryFamily, L"Father");
		ListBox_AddString(lbxPrimaryFamily, L"Mother");
		SendMessage(lbxPrimaryFamily, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)L"Daughter");
		SendMessage(lbxPrimaryFamily, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)TEXT("Son"));
		SendMessage(lbxPrimaryFamily, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)TEXT("Bother"));
		SendMessage(lbxPrimaryFamily, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)TEXT("Sister"));

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDC_PRIMARYFAMILY_LB:
			{	
				switch (HIWORD(wParam))
				{
				case LBN_DBLCLK:
					int iSelectedIndex;
					TCHAR strSelectedItem[32];
					iSelectedIndex = ListBox_GetCurSel(lbxPrimaryFamily);
					ListBox_GetText(lbxPrimaryFamily, iSelectedIndex, (LPCTSTR)strSelectedItem);
					MessageBox(NULL, strSelectedItem, L"Exercise", MB_OK);
					// Deleting the item that was double-clicked
					ListBox_DeleteString(lbxPrimaryFamily, iSelectedIndex);
					return TRUE;
				}
			}
			return TRUE;

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