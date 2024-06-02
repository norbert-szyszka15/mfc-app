#pragma once

#include "MyData.h"
#include "Except1.h"


class CProjectMFCDoc : public CDocument
{
protected:
	CProjectMFCDoc() noexcept;
	DECLARE_DYNCREATE(CProjectMFCDoc)

public:
	MyData* pDat;
	CExcept1App* pExcept;

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif

public:
	virtual ~CProjectMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif
};
