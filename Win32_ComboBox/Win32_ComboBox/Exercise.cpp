#include <windows.h>
#ifdef __BORLANDC__
#pragma argsused
#endif

#include "resource.h"
//---------------------------------------------------------------------------
HWND hWnd;
HWND hWndComboBox;
HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_CONTROLSDLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	/*switch (Msg)
	{
	case WM_INITDIALOG:
		hWndComboBox = CreateWindowEx(0, L"COMBOBOX",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			60, 62, 136, 60,
			hWndDlg,
			NULL,
			hInst,
			NULL);

		if (!hWndComboBox)
		{
			MessageBox(hWndDlg,
				L"Could not create the combo box",
				L"Failed Control Creation",
				MB_OK);
			return FALSE;
		}
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

	return FALSE;*/
	HWND cboCountries;

	const wchar_t *Countries[] = { L"Sri Lanka", L"El Salvador", L"Botswana",
		L"France", L"Cuba", L"South Africa",
		L"Australia", L"Russia", L"Jamaica",
		L"Great Britain", L"Senegal", L"Bangla Desh" };

	switch (Msg)
	{
	case WM_INITDIALOG:
		cboCountries = GetDlgItem(hWndDlg, IDD_COUNTRIES_CBO);

		for (int Count = 0; Count < 12; Count++)
		{
			SendMessage(cboCountries,
				CB_ADDSTRING,
				0,
				reinterpret_cast<LPARAM>((LPCTSTR)Countries[Count]));
		}
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