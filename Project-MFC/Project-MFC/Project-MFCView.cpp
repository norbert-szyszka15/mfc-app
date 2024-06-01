#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "Project-MFC.h"
#endif

#include "Project-MFCDoc.h"
#include "Project-MFCView.h"
#include "CDialogInputData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CProjectMFCView, CView)

BEGIN_MESSAGE_MAP(CProjectMFCView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProjectMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OPERATE_INPUT_DATA, &CProjectMFCView::OnOperateInputData)
END_MESSAGE_MAP()

CProjectMFCView::CProjectMFCView() noexcept
{
	mScaleX = mScaleY = 1.0;
	pointRad = 8;

	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 12;
	strcpy_s(lf.lfFaceName, "Arial");
}

CProjectMFCView::~CProjectMFCView() {}

void CProjectMFCView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CWnd* ptrWnd = this->GetActiveWindow();
	CProjectMFCDoc* pDoc = GetDocument();
	
	if (pDoc && pDoc->pDat)
	{
		MyData* pdat = pDoc->pDat;
		pDoc->pExcept->SetWnd(ptrWnd, pdat);
		pDoc->pExcept->ClearOutWnd();
	}
}

BOOL CProjectMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

CPoint CProjectMFCView::GetScreenCoord(DCOORD Coord, DCOORD min, DCOORD max, SIZE size, SIZE marg, int hsbpos, int vsbpos) 
{
	CPoint scr;
	const double eps = 1e-40;

	if (fabs(min.y - max.y) < eps)
	{
		scr.y = size.cy / 2;
	} 
	else
	{
		scr.y = (long)(marg.cy + (Coord.y - max.y) / (min.y - max.y) * (size.cy - 2 * marg.cy));
	}

	if (fabs(min.x - max.x) < eps)
	{
		scr.x = size.cx / 2;
	}
	else
	{
		scr.x = (long)(marg.cx + (Coord.x - min.x) / (max.x - min.x) * (size.cx - 2 * marg.cx));
	}

	scr.x -= hsbpos * size.cx / 100;
	scr.y -= vsbpos * size.cy / 100;

	return scr;
}

void CProjectMFCView::OnDraw(CDC* pDC)
{
	CProjectMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) { return; }

	pDC->SetMapMode(MM_TEXT);
	pDC->SetGraphicsMode(GM_ADVANCED);

	CString str;
	TEXTMETRIC tm;

	CPen newPen;
	CPen* oldPen;
	CBrush newBrush;
	CBrush* oldBrush;

	CPoint scr;
	SIZE size1;
	SIZE marg = { 80,80 };

	VERIFY(font.CreateFontIndirect(&lf));
	CFont* defFont = pDC->SelectObject(&font);

	pDC->GetOutputTextMetrics(&tm);

	CRect rect;
	this->GetClientRect(&rect);

	double maxX, minX, maxY, minY;
	pDoc->pDat->GetMinMaxCoords(maxX, minX, maxY, minY);

	size1.cx = (long)(mScaleX * (rect.right - rect.left));
	size1.cy = (long)(mScaleY * (rect.bottom - rect.top));

	newBrush.CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = pDC->SelectObject(&newBrush);
	pDC->Rectangle(0, 0, (rect.right - rect.left), (rect.bottom - rect.top));
	pDC->SelectObject(oldBrush);
	newBrush.DeleteObject();

	DCOORD Coord(0, 0), mmin(minX, minY), mmax(maxX, maxY);

	const int nPoints = pDoc->pDat->Size();

	newPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oldPen = pDC->SelectObject(&newPen);

	for (int iPoint = 0; iPoint < nPoints; ++iPoint)
	{
		Coord.x = (*pDoc->pDat)[iPoint].x;
		Coord.y = (*pDoc->pDat)[iPoint].y;
		scr = GetScreenCoord(Coord, mmin, mmax, size1, marg, 1, 1);
		MyPoint point = (*pDoc->pDat)[iPoint];
		COLORREF pointColor = point.color;

		TRACE("Drawing Point: X=%lf, Y=%lf, Color: R=%d, G=%d, B=%d\n",
			point.x, point.y, GetRValue(pointColor), GetGValue(pointColor), GetBValue(pointColor));

		newBrush.CreateSolidBrush(pointColor);
		oldBrush = pDC->SelectObject(&newBrush);
		pDC->Ellipse(scr.x + pointRad, scr.y + pointRad, scr.x - pointRad, scr.y - pointRad);
		pDC->SelectObject(oldBrush);
		newBrush.DeleteObject();

		pDC->SelectObject(oldPen);
		newPen.DeleteObject();
		newPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		oldPen = pDC->SelectObject(&newPen);

		if (iPoint == 0)
		{
			pDC->MoveTo(scr);
		}
		else
		{
			pDC->LineTo(scr);
		}

		pDC->SelectObject(oldPen);
		newPen.DeleteObject();

		str.Format("%s", point.name);
		pDC->TextOut(scr.x + pointRad + 2, scr.y, str);
	}

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

	pDC->SelectObject(defFont);
	font.DeleteObject();
}

void CProjectMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProjectMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CProjectMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {}

void CProjectMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {}

void CProjectMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProjectMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

#ifdef _DEBUG
void CProjectMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CProjectMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProjectMFCDoc* CProjectMFCView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectMFCDoc)));
	return (CProjectMFCDoc*)m_pDocument;
}
#endif

void CProjectMFCView::OnOperateInputData() 
{
	CProjectMFCDoc* pDoc = GetDocument();
	CDialogInputData dlg(pDoc);
	dlg.DoModal();
}