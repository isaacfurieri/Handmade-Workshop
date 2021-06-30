#pragma once

/*===================================================================#
| 'HandmadeDoc' source files last updated on 30 June 2021            |
#===================================================================*/

class CHandmadeDoc : public CDocument
{

protected:

	//Create from serialization only
	CHandmadeDoc() noexcept;
	virtual ~CHandmadeDoc();
	DECLARE_DYNCREATE(CHandmadeDoc)

public:

	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

};