#include <windows.h>
#include "resource.h"

HINSTANCE hInst;
LRESULT CALLBACK WindProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX  WndCls;
	static const wchar_t szAppName[] =L"ExoBrush";
	MSG         Msg;

	hInst = hInstance;
	WndCls.cbSize = sizeof(WndCls);
	WndCls.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	WndCls.lpfnWndProc = WindProcedure;
	WndCls.cbClsExtra = 0;
	WndCls.cbWndExtra = 0;
	WndCls.hInstance = hInst;
	WndCls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndCls.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndCls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndCls.lpszMenuName = NULL;
	WndCls.lpszClassName = szAppName;
	WndCls.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	RegisterClassEx(&WndCls);

	CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		szAppName, L"Pattern Brushes",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 240,
		NULL, NULL, hInstance, NULL);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return static_cast<int>(Msg.wParam);
}

LRESULT CALLBACK WindProcedure(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	HDC         hDC;
	PAINTSTRUCT Ps;
	HBITMAP     BmpBrush;
	HBRUSH		brPattern;
	HPEN        hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	switch (Msg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &Ps);

		BmpBrush = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		brPattern = CreatePatternBrush(BmpBrush);

		SelectObject(hDC, hPen);
		SelectObject(hDC, brPattern);

		Rectangle(hDC, 5, 3, 380, 280);

		DeleteObject(hPen);
		DeleteObject(BmpBrush);

		EndPaint(hWnd, &Ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}