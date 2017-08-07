#include <windows.h>
#include <cstdio>
#include <strsafe.h>
using namespace std;

#ifdef __BORLANDC__
#pragma argsused
#endif

#include "resource.h"
//---------------------------------------------------------------------------
HWND hWnd;
HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_CONTROLSDLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	hInst = hInstance;

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	wchar_t strMarkedPrice[20], strTaxRate[20], strTaxAmount[20], strNetPrice[20];
	HWND hWndMarkedPrice, hWndTaxRate, hWndTaxAmount, hWndNetPrice;
	double MarkedPrice, TaxRate, TaxAmount, NetPrice;

	hWndMarkedPrice = GetDlgItem(hWndDlg, IDC_MARKED_PRICE);
	hWndTaxRate = GetDlgItem(hWndDlg, IDC_TAX_RATE);
	hWndTaxAmount = GetDlgItem(hWndDlg, IDC_TAX_AMOUNT);
	hWndNetPrice = GetDlgItem(hWndDlg, IDC_NET_PRICE);

	switch (Msg)
	{
	case WM_INITDIALOG:
		SetWindowText(hWndMarkedPrice, L"0.00");
		SetWindowText(hWndTaxRate, L"5.75");
		SetWindowText(hWndTaxAmount, L"0.00");
		SetWindowText(hWndNetPrice, L"0.00");
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_CALCULATE_BTN:
			GetWindowText(hWndMarkedPrice, strMarkedPrice, 20);
			GetWindowText(hWndTaxRate, strTaxRate, 20);

			MarkedPrice = _wtof(strMarkedPrice); //_wtof: wide string atof
			TaxRate = _wtof(strTaxRate) / 100; //_wtof: wide string atof

			TaxAmount = MarkedPrice * TaxRate;
			NetPrice = MarkedPrice + TaxAmount;

			// safe form of wsprintf
			StringCchPrintfExW(strTaxAmount, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"$%.2f", TaxAmount);
			StringCchPrintfExW(strNetPrice, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"$%.2f", NetPrice);
			//sprintf(strTaxAmount, "%.2f", TaxAmount);
			//sprintf(strNetPrice, "%.2f", NetPrice);

			SetWindowText(hWndTaxAmount, strTaxAmount);
			SetWindowText(hWndNetPrice, strNetPrice);

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