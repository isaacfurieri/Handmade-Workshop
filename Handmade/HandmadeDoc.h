#pragma once

/*===================================================================#
| 'HandmadeDoc' source files last updated on 21 October 2021         |
#===================================================================*/

class CHandmadeDoc : public CDocument
{

public:

	CHandmadeDoc() {}
	virtual ~CHandmadeDoc() {}
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& archive) {}

private:

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CHandmadeDoc)

};