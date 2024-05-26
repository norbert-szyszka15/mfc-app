
// Project-MFCView.h : interface of the CProjectMFCView class
//

#pragma once


class CProjectMFCView : public CView
{
protected: // create from serialization only
	CProjectMFCView() noexcept;
	DECLARE_DYNCREATE(CProjectMFCView)

// Attributes
public:
	CFont font;
	LOGFONT lf;

	double mScaleX;
	double mScaleY;
	int pointRad;

	struct DCOORD
	{
		double x;
		double y;
		DCOORD(double xx, double yy) : x(xx), y(yy) {}
	};

// Operations
public:
	CProjectMFCDoc* GetDocument() const;
	CPoint GetScreenCoord(DCOORD Coord, DCOORD min, DCOORD max, SIZE size, SIZE marg, int hsbpos, int vsbpos);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CProjectMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOperateInputData();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in Project-MFCView.cpp
inline CProjectMFCDoc* CProjectMFCView::GetDocument() const
   { return reinterpret_cast<CProjectMFCDoc*>(m_pDocument); }
#endif

