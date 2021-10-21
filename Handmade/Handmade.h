#pragma once

/*===================================================================#
| 'Handmade' source files last updated on 21 October 2021            |
#===================================================================*/

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"      

class CHandmadeApp : public CWinApp
{

public:

	CHandmadeApp();
	virtual BOOL InitInstance();
	virtual int ExitInstance();

private:

	UINT m_nAppLook;
	DECLARE_MESSAGE_MAP()

};

extern CHandmadeApp theApp;