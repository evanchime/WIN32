//---------------------------------------------------------------------------
#include <windows.h>

//---------------------------------------------------------------------------

LPCTSTR Caption = L"Application Programming Interface";

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL,
		L"Welcome to Win32 Application Development\n"
		L"You will learn about functions, classes, "
		L"communication, and other cool stuff\n"
		L"Are you ready to rumble!!!!!!!!!!!!!!",
		Caption,
		MB_YESNOCANCEL | MB_ICONQUESTION);

	return 0;
}
//---------------------------------------------------------------------------