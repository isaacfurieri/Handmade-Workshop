#pragma once

/*===================================================================#
| 'framework' source files last updated on 21 October 2021           |
#===================================================================*/

//Exclude rarely-used stuff from Windows headers
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      
#define _AFX_ALL_WARNINGS

#include <afxcontrolbars.h>     //MFC support for ribbons and control bars
#include <afxext.h>             //MFC extensions
#include <afxwin.h>             //MFC core and standard components

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           //MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             //MFC support for Windows Common Controls
#endif 

//This code usually resides in the 'stdafx.h' file and 
//sets the manifest so that the modern Windows controls 
//are used. If this is missing dialog boxes will look old
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif