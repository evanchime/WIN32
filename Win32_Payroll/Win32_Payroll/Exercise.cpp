#include <windows.h>
#include <cstdio>
#include "resource.h"
#include <strsafe.h>

using namespace std;

#ifdef __BORLANDC__
#pragma argsused
#endif
HWND hWnd;
HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_CONTROLS_DLG),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	hInst = hInstance;

	return 0;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	wchar_t strHourlySalary[20], strMonday1[10], strTuesday1[10], strWednesday1[10],
		strThursday1[10], strFriday1[10], strSaturday1[10], strSunday1[10],
		strMonday2[10], strTuesday2[10], strWednesday2[10],
		strThursday2[10], strFriday2[10], strSaturday2[10], strSunday2[10];

	double monday1 = 0.00, tuesday1 = 0.00, wednesday1 = 0.00, thursday1 = 0.00,
		friday1 = 0.00, saturday1 = 0.00, sunday1 = 0.00,
		monday2 = 0.00, tuesday2 = 0.00, wednesday2 = 0.00, thursday2 = 0.00,
		friday2 = 0.00, saturday2 = 0.00, sunday2 = 0.00;

	HWND hWndHourlySalary, hWndMonday1, hWndTuesday1, hWndWednesday1,
		hWndThursday1, hWndFriday1, hWndSaturday1, hWndSunday1,
		hWndMonday2, hWndTuesday2, hWndWednesday2,
		hWndThursday2, hWndFriday2, hWndSaturday2, hWndSunday2,
		hWndRegularHours, hWndOvertimeHours,
		hWndRegularAmount, hWndOvertimeAmount,
		hWndNetPay;

	double totalHoursWeek1, totalHoursWeek2, ovtSalary;
	double regHours1 = 0.00, regHours2 = 0.00, ovtHours1 = 0.00, ovtHours2 = 0.00;
	double regAmount1 = 0.00, regAmount2 = 0.00, ovtAmount1 = 0.00, ovtAmount2 = 0.00;

	wchar_t   strRegularHours[20], strOvertimeHours[20];
	double regularHours, overtimeHours;
	wchar_t   strRegularAmount[20], strOvertimeAmount[20], strNetPay[20];
	double regularAmount, overtimeAmount, netPay;

	double hourlySalary = 0.00;

	hWndHourlySalary = GetDlgItem(hWndDlg, IDC_HOURLY_SALARY);
	hWndMonday1 = GetDlgItem(hWndDlg, IDC_MONDAY1);
	hWndTuesday1 = GetDlgItem(hWndDlg, IDC_TUESDAY1);
	hWndWednesday1 = GetDlgItem(hWndDlg, IDC_WEDNESDAY1);
	hWndThursday1 = GetDlgItem(hWndDlg, IDC_THURSDAY1);
	hWndFriday1 = GetDlgItem(hWndDlg, IDC_FRIDAY1);
	hWndSaturday1 = GetDlgItem(hWndDlg, IDC_SATURDAY1);
	hWndSunday1 = GetDlgItem(hWndDlg, IDC_SUNDAY1);

	hWndMonday2 = GetDlgItem(hWndDlg, IDC_MONDAY2);
	hWndTuesday2 = GetDlgItem(hWndDlg, IDC_TUESDAY2);
	hWndWednesday2 = GetDlgItem(hWndDlg, IDC_WEDNESDAY2);
	hWndThursday2 = GetDlgItem(hWndDlg, IDC_THURSDAY2);
	hWndFriday2 = GetDlgItem(hWndDlg, IDC_FRIDAY2);
	hWndSaturday2 = GetDlgItem(hWndDlg, IDC_SATURDAY2);
	hWndSunday2 = GetDlgItem(hWndDlg, IDC_SUNDAY2);

	hWndRegularHours = GetDlgItem(hWndDlg, IDC_REGULAR_HOURS);
	hWndOvertimeHours = GetDlgItem(hWndDlg, IDC_OVERTIME_HOURS);
	hWndRegularAmount = GetDlgItem(hWndDlg, IDC_REGULAR_AMOUNT);
	hWndOvertimeAmount = GetDlgItem(hWndDlg, IDC_OVERTIME_AMOUNT);
	hWndNetPay = GetDlgItem(hWndDlg, IDC_NET_PAY);

	switch (Msg)
	{
	case WM_INITDIALOG:
		SetWindowText(hWndHourlySalary, L"0.00");

		SetWindowText(hWndMonday1, L"0.00");
		SetWindowText(hWndTuesday1, L"0.00");
		SetWindowText(hWndWednesday1, L"0.00");
		SetWindowText(hWndThursday1, L"0.00");
		SetWindowText(hWndFriday1, L"0.00");
		SetWindowText(hWndSaturday1, L"0.00");
		SetWindowText(hWndSunday1, L"0.00");

		SetWindowText(hWndMonday2, L"0.00");
		SetWindowText(hWndTuesday2, L"0.00");
		SetWindowText(hWndWednesday2, L"0.00");
		SetWindowText(hWndThursday2, L"0.00");
		SetWindowText(hWndFriday2, L"0.00");
		SetWindowText(hWndSaturday2, L"0.00");
		SetWindowText(hWndSunday2, L"0.00");

		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_PROCESS_BTN:
			// Retrieve the hourly salary
			GetWindowText(hWndHourlySalary, strHourlySalary, 20);
			hourlySalary = _wtof(strHourlySalary); //_wtof: wide string atof

			// Get the time for each day
			GetWindowText(hWndMonday1, strMonday1, 10);
			monday1 = _wtof(strMonday1); //_wtof: wide string atof
			GetWindowText(hWndTuesday1, strTuesday1, 10);
			tuesday1 = _wtof(strTuesday1); //_wtof: wide string atof
			GetWindowText(hWndWednesday1, strWednesday1, 10);
			wednesday1 = _wtof(strWednesday1); //_wtof: wide string atof
			GetWindowText(hWndThursday1, strThursday1, 10);
			thursday1 = _wtof(strThursday1); //_wtof: wide string atof
			GetWindowText(hWndFriday1, strFriday1, 10);
			friday1 = _wtof(strFriday1); //_wtof: wide string atof
			GetWindowText(hWndSaturday1, strSaturday1, 10);
			saturday1 = _wtof(strSaturday1); //_wtof: wide string atof
			GetWindowText(hWndSunday1, strSunday1, 10);
			sunday1 = _wtof(strSunday1); //_wtof: wide string atof

			GetWindowText(hWndMonday2, strMonday2, 10);
			monday2 = _wtof(strMonday2); //_wtof: wide string atof
			GetWindowText(hWndTuesday2, strTuesday2, 10);
			tuesday2 = _wtof(strTuesday2); //_wtof: wide string atof
			GetWindowText(hWndWednesday2, strWednesday2, 10);
			wednesday2 = _wtof(strWednesday2); //_wtof: wide string atof
			GetWindowText(hWndThursday2, strThursday2, 10);
			thursday2 = _wtof(strThursday2); //_wtof: wide string atof
			GetWindowText(hWndFriday2, strFriday2, 10);
			friday2 = _wtof(strFriday2); //_wtof: wide string atof
			GetWindowText(hWndSaturday2, strSaturday2, 10);
			saturday2 = _wtof(strSaturday2); //_wtof: wide string atof
			GetWindowText(hWndSunday2, strSunday2, 10);
			sunday2 = _wtof(strSunday2); //_wtof: wide string atof

			// Calculate the total number of hours for each week
			totalHoursWeek1 = monday1 + tuesday1 + wednesday1 + thursday1 +
				friday1 + saturday1 + sunday1;
			totalHoursWeek2 = monday2 + tuesday2 + wednesday2 + thursday2 +
				friday2 + saturday2 + sunday2;

			// The overtime is paid time and half
			ovtSalary = hourlySalary * 1.5;

			// If the employee worked under 40 hours, there is no overtime
			if (totalHoursWeek1 < 40)
			{
				regHours1 = totalHoursWeek1;
				regAmount1 = hourlySalary * regHours1;
				ovtHours1 = 0.00;
				ovtAmount1 = 0.00;
			} // If the employee worked over 40 hours, calculate the overtime
			else if (totalHoursWeek1 >= 40)
			{
				regHours1 = 40;
				regAmount1 = hourlySalary * 40;
				ovtHours1 = totalHoursWeek1 - 40;
				ovtAmount1 = ovtHours1 * ovtSalary;
			}

			if (totalHoursWeek2 < 40)
			{
				regHours2 = totalHoursWeek2;
				regAmount2 = hourlySalary * regHours2;
				ovtHours2 = 0.00;
				ovtAmount2 = 0.00;
			}
			else if (totalHoursWeek2 >= 40)
			{
				regHours2 = 40;
				regAmount2 = hourlySalary * 40;
				ovtHours2 = totalHoursWeek2 - 40;
				ovtAmount2 = ovtHours2 * ovtSalary;
			}

			regularHours = regHours1 + regHours2;
			overtimeHours = ovtHours1 + ovtHours2;
			regularAmount = regAmount1 + regAmount2;
			overtimeAmount = ovtAmount1 + ovtAmount2;
			netPay = regularAmount + overtimeAmount;

			// safe form of wsprintf
			StringCchPrintfExW(strRegularHours, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"%.2f", regularHours);
			StringCchPrintfExW(strOvertimeHours, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"%.2f", overtimeHours);
			StringCchPrintfExW(strRegularAmount, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"$%.2f", regularAmount);
			StringCchPrintfExW(strOvertimeAmount, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"$%.2f", overtimeAmount);
			StringCchPrintfExW(strNetPay, 20, NULL, NULL, STRSAFE_NULL_ON_FAILURE, L"$%.2f", netPay);
			//sprintf(strRegularHours, "%.2f", regularHours);
			//sprintf(strOvertimeHours, "%.2f", overtimeHours);
			//sprintf(strRegularAmount, "%.2f", regularAmount);
			//sprintf(strOvertimeAmount, "%.2f", overtimeAmount);
			//sprintf(strNetPay, "%.2f", netPay);

			SetWindowText(hWndRegularHours, strRegularHours);
			SetWindowText(hWndRegularAmount, strRegularAmount);
			SetWindowText(hWndOvertimeHours, strOvertimeHours);
			SetWindowText(hWndOvertimeAmount, strOvertimeAmount);

			SetWindowText(hWndNetPay, strNetPay);

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