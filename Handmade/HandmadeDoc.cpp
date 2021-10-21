#include "framework.h"
#include "HandmadeDoc.h"

//================================================================================================
IMPLEMENT_DYNCREATE(CHandmadeDoc, CDocument)
//================================================================================================
BEGIN_MESSAGE_MAP(CHandmadeDoc, CDocument)
END_MESSAGE_MAP()
//================================================================================================
BOOL CHandmadeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	return TRUE;
}