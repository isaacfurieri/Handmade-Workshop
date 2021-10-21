#include "framework.h"
#include "MainFrm.h"

//================================================================================================
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
//================================================================================================
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()
//================================================================================================
int CMainFrame::OnCreate(LPCREATESTRUCT createStruct)
{
	if (CFrameWnd::OnCreate(createStruct) == -1)
	{
		return -1;
	}

	if (!m_statusBar.Create(this))
	{
		return -1;
	}

	m_statusBar.GetStatusBarCtrl().SetSimple();
	return 0;
}
//================================================================================================
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& createStruct)
{
	//Help with window styles:
	//https://coding-examples.com/c/mfc/fixed-mfc-sdi-window-using-createstruct-precreatewindow/

	if (!CFrameWnd::PreCreateWindow(createStruct))
	{
		return FALSE;
	}

	//This removes the 'blank spot' when removing the thick border
	//using 'ModifyStyleEx(WS_EX_CLIENTEDGE, 0)' in the OnCreate()
	//function inside the 'View' class. 
	createStruct.dwExStyle = 0;

	//Modify the Window class or styles here by modifying the 
	//CREATESTRUCT cs and make sure to do this AFTER the call above 

	//EXAMPLE:
	/*cs.style |= WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_MAXIMIZE;*/

	 //Use cs.style |= STYLE to add a style
	 //Use cs.style &= ~STYLE to remove a style
	 //Use cs.style = STYLE to create new styles from scratch

	return TRUE;
}
//================================================================================================
void CMainFrame::SetStatusBarText(const std::string& text)
{
	m_statusBar.GetStatusBarCtrl().SetText(std::wstring(text.begin(),
		text.end()).c_str(), 255, 0);
}