#pragma once

/*===================================================================#
| 'Handmade' source files last updated on 30 June 2021               |
#===================================================================*/

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

class CHandmadeApp : public CWinApp
{

public:

	CHandmadeApp() noexcept;

public:

	virtual BOOL InitInstance();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

};

extern CHandmadeApp theApp;