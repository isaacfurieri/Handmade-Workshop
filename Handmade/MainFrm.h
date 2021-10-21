#pragma once

/*===================================================================#
| 'MainFrm' source files last updated on 21 October 2021             |
#===================================================================*/

#include <string>

class CMainFrame : public CFrameWnd
{

public:

	CMainFrame() {}
	virtual ~CMainFrame() {}
	void SetStatusBarText(const std::string& text);

private:

	afx_msg int OnCreate(LPCREATESTRUCT createStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& createStruct);

	CStatusBar m_statusBar;

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CMainFrame)

};