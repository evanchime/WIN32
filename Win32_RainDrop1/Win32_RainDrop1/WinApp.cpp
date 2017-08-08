#include "WinApp.h"
#include "resource.h"

//---------------------------------------------------------------------------
WApplication::WApplication()
{
}

void WApplication::Create(HINSTANCE hInst, const wchar_t *ClsName,
	WNDPROC WndPrc, LPCTSTR MenuName)
{
	// Initializing the application using the application member variable
	_WndClsEx.cbSize = sizeof(WNDCLASSEX);
	_WndClsEx.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	_WndClsEx.lpfnWndProc = WndPrc;
	_WndClsEx.cbClsExtra = 0;
	_WndClsEx.cbWndExtra = 0;
	_WndClsEx.hInstance = hInst;
	_WndClsEx.hIcon = static_cast<HICON>(LoadImage(hInst,
		MAKEINTRESOURCE(IDI_RAINDROP),
		IMAGE_ICON,
		32,
		32,
		LR_DEFAULTSIZE));
	_WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClsEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	_WndClsEx.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	_WndClsEx.lpszClassName = ClsName;
	_WndClsEx.hIconSm = static_cast<HICON>(LoadImage(hInst,
		MAKEINTRESOURCE(IDI_RAINDROP),
		IMAGE_ICON,
		16,
		16,
		LR_DEFAULTSIZE));
}
//---------------------------------------------------------------------------
void WApplication::Register()
{
	RegisterClassEx(&_WndClsEx);
}
//---------------------------------------------------------------------------