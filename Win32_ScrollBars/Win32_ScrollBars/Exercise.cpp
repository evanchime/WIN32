#include <windows.h>
#ifdef __BORLANDC__
#pragma argsused
#endif

const wchar_t *ClsName = L"CtrlExos";
const wchar_t *WndName = L"Controls Examples";
HINSTANCE hInst;

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG        Msg;
	HWND       hWnd;
	WNDCLASSEX WndClsEx;

	hInst = hInstance;

	// Create the application window
	WndClsEx.cbSize = sizeof(WNDCLASSEX);
	WndClsEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc = WndProcedure;
	WndClsEx.cbClsExtra = 0;
	WndClsEx.cbWndExtra = 0;
	WndClsEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClsEx.lpszMenuName = NULL;
	WndClsEx.lpszClassName = ClsName;
	WndClsEx.hInstance = hInst;
	WndClsEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register the application
	RegisterClassEx(&WndClsEx);

	// Create the window object
	hWnd = CreateWindowEx(0,
		ClsName,
		WndName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);

	// Find out if the window was created successfully
	if (!hWnd) // If the window was not created,
		return 0; // stop the application

				  // Display the window to the user
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// Decode and treat the messages
	// as long as the application is running
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	static HWND hWndEdit;

	switch (Msg)
	{
	case WM_CREATE:

		hWndEdit = CreateWindowEx(0,
			L"EDIT", // We are creating an Edit control
			NULL,   // Leave the control empty
			WS_CHILD | WS_VISIBLE | WS_HSCROLL |
			WS_VSCROLL | ES_LEFT | ES_MULTILINE |
			ES_AUTOHSCROLL | ES_AUTOVSCROLL,
			0, 0, 0, 0, // Let the WM_SIZE messge below take care of the size
			hWnd,
			0,
			hInst,
			NULL);

		return 0;

	case WM_SETFOCUS:
		SetFocus(hWndEdit);
		return 0;

	case WM_SIZE:
		MoveWindow(hWndEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;

	case WM_DESTROY:
		// If the user has finished, then close the window
		PostQuitMessage(WM_QUIT);
		break;
	default:
		// Process the left-over messages
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	// If something was not done, let it go
	return 0;
}
