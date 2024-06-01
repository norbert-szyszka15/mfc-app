#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "Project-MFC.h"
#endif

#include "Project-MFCDoc.h"

#include <propkey.h>

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CProjectMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CProjectMFCDoc, CDocument)
END_MESSAGE_MAP()

CProjectMFCDoc::CProjectMFCDoc() noexcept
{
	pDat = NULL;
	pExcept = GetExceptPtr();
}

CProjectMFCDoc::~CProjectMFCDoc()
{
	if (pDat)
	{
		delete pDat;
	}
	pDat = NULL;
}

BOOL CProjectMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) 
	{ 
		return FALSE; 
	}

	if (pDat)
	{
		delete pDat;
	}

	try
	{
		pDat = new MyData(1);
		pExcept->ResetData(pDat);
	}
	catch (std::bad_alloc)
	{
		pExcept->PutMessage(1002);
	}

	return TRUE;
}

void CProjectMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		if (pDat)
		{
			MyPoint tmp;
			const int noIt(pDat->Size());

			ar << noIt;
			for (int i = 0; i < noIt; ++i)
			{
				tmp = (*pDat)[i].get();
				ar << tmp.x << tmp.y << tmp.color << tmp.name;
			}
		}
	}
	else
	{
		if (pDat) { delete pDat; }

		int noIt(0);
		ar >> noIt;

		if (noIt)
		{
			try
			{
				pDat = new MyData(noIt);
				pExcept->ResetData(pDat);
			}
			catch (std::bad_alloc)
			{
				pExcept->PutMessage(1002);
			}

			MyPoint tmp;

			for (int i = 0; i < noIt; ++i)
			{
				ar >> tmp.x >> tmp.y >> tmp.color >> tmp.name;
				pDat->Push(tmp);
			}
		}
		pExcept->PutMessage(1001);
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CProjectMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CProjectMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CProjectMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CProjectMFCDoc diagnostics

#ifdef _DEBUG
void CProjectMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProjectMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif