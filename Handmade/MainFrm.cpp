#include "framework.h"
#include "Handmade.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
END_MESSAGE_MAP()

//======================================================================================================
CMainFrame::CMainFrame() noexcept
{
}
//======================================================================================================
CMainFrame::~CMainFrame()
{
}
//======================================================================================================
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{	
	//Help with window styles:
	//https://coding-examples.com/c/mfc/fixed-mfc-sdi-window-using-createstruct-precreatewindow/

	if (!CFrameWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}

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
//======================================================================================================
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
//======================================================================================================
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

//======================================================================================================
//CMainFrame message handlers
//======================================================================================================