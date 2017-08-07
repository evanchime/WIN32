#include <windows.h>
#ifdef __BORLANDC__
#pragma argsused
#endif
//---------------------------------------------------------------------------
const wchar_t *ClsName = L"WndProperties";
const wchar_t *WndName = L"Popup Window";
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG        Msg;
	HWND       hWnd;
	WNDCLASSEX WndClsEx;

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
	WndClsEx.hInstance = hInstance;
	WndClsEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register the application
	RegisterClassEx(&WndClsEx);

	// Create the window object
	hWnd = CreateWindowEx(WS_EX_TOOLWINDOW,
		ClsName, WndName,
		WS_POPUPWINDOW | WS_CAPTION,
		200, 120, 200, 320,
		NULL, NULL, hInstance, NULL);

	// Find out if the window was created
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
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		// If the user wants to close the application
	case WM_DESTROY:
		// then close it
		PostQuitMessage(WM_QUIT);
		break;
	default:
		// Process the left-over messages
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	// If something was not done, let it go
	return 0;
}
//---------------------------------------------------------------------------
