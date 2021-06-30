
// Handmade.h : main header file for the Handmade application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHandmadeApp:
// See Handmade.cpp for the implementation of this class
//

class CHandmadeApp : public CWinApp
{
public:
	CHandmadeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHandmadeApp theApp;
