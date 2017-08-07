#include <windows.h>
#include <cstdio>
#include <cmath>
#include "resource.h"
#include <strsafe.h>

//---------------------------------------------------------------------------
HWND hWnd;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN_DLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	// These variables will carry the values in the text boxes
	LPTSTR strPrincipal = new wchar_t[20],
		strInterest = new wchar_t[20], strPeriods = new wchar_t[20],
		strInterestEarned = new wchar_t[20], strAmountEarned = new wchar_t[20];
	// These are handled for the various controls
	HWND hWndPrincipal, hWndInterest, hWndPeriods, hWndCompound,
		hWndInterestEarned, hWndAmountEarned, hWndCalculate;

	double Principal, AnnualRate, InterestEarned;
	double FutureValue, RatePerPeriod;
	int    NumberOfPeriods, CompoundType;
	double i;
	int n;

	hWndPrincipal = GetDlgItem(hWndDlg, IDC_PRINCIPAL);
	hWndInterest = GetDlgItem(hWndDlg, IDC_ANNUAL_RATE);
	hWndPeriods = GetDlgItem(hWndDlg, IDC_NBR_OF_PERIODS);
	hWndCompound = GetDlgItem(hWndDlg, IDC_COMPOUND);
	hWndInterestEarned = GetDlgItem(hWndDlg, IDC_INTEREST_EARNED);
	hWndAmountEarned = GetDlgItem(hWndDlg, IDC_AMOUNT_EARNED);
	hWndCalculate = GetDlgItem(hWndDlg, IDC_CALCULATE_BTN);

	switch (Msg)
	{
	case WM_INITDIALOG:
		// Identify each control
		SetWindowText(hWndPrincipal, L"0.00");
		SetWindowText(hWndInterest, L"7.55");
		SetWindowText(hWndPeriods, L"0");
		SetWindowText(hWndInterestEarned, L"0.00");
		SetWindowText(hWndAmountEarned, L"0.00");

		CheckRadioButton(hWndDlg, IDC_COMPOUND, IDC_ANNUALLY, IDC_COMPOUND);
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_CALCULATE_BTN:
			GetWindowText(hWndPrincipal, strPrincipal, 20);
			GetWindowText(hWndInterest, strInterest, 10);
			GetWindowText(hWndPeriods, strPeriods, 8);

			Principal = _wtof(strPrincipal); //_wtof: wide string atof
			AnnualRate = _wtof(strInterest) / 100; //_wtof: wide string atof

			if (IsDlgButtonChecked(hWndDlg, IDC_COMPOUND) == BST_CHECKED)
				CompoundType = 12;
			else if (IsDlgButtonChecked(hWndDlg, IDC_QUATERLY) == BST_CHECKED)
				CompoundType = 4;
			else if (IsDlgButtonChecked(hWndDlg, IDC_SEMIANNUALLY) == BST_CHECKED)
				CompoundType = 2;
			else // if( IsDlgButtonChecked(hWndDlg, IDC_ANNUALLY) == BST_CHECKED )
				CompoundType = 1;

			NumberOfPeriods = _wtoi(strPeriods); //_wtoi: wide string atoi
			i = AnnualRate / CompoundType;
			n = CompoundType * NumberOfPeriods;

			RatePerPeriod = AnnualRate / NumberOfPeriods;
			FutureValue = Principal * pow(1 + i, n);
			InterestEarned = FutureValue - Principal;

			// safe form of wsprintf
			StringCchPrintfExW(strInterestEarned, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"$%.2f", InterestEarned);
			StringCchPrintfExW(strAmountEarned, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"$%.2f", FutureValue);
			/*wsprintf(strInterestEarned, L"$%.2f", InterestEarned);
			wsprintf(strAmountEarned, L"$%.2f", FutureValue);*/

			SetWindowText(hWndInterestEarned, strInterestEarned);
			SetWindowText(hWndAmountEarned, strAmountEarned);
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