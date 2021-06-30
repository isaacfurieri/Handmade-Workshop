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
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	//TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	//Make sure to do this AFTER the call above and append settings with |=

	/*cs.style |= WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_MAXIMIZE;*/

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