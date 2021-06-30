#pragma once

/*===================================================================#
| 'MainFrm' source files last updated on 30 June 2021                |
#===================================================================*/

class CMainFrame : public CFrameWnd
{

protected: 

	//Create from serialization only
	CMainFrame() noexcept;
	virtual ~CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

};