#pragma once
#include <windows.h>

//---------------------------------------------------------------------------
class WApplication
{
public:
	// This constructor will initialize the application
	WApplication();
	void Create(HINSTANCE hInst, const wchar_t *ClasName,
		WNDPROC WndPrc, LPCTSTR MenuName = NULL);

	// Class Registration
	void Register();

protected:
	// Global variable that holds the application
	WNDCLASSEX _WndClsEx;
};
//---------------------------------------------------------------------------
