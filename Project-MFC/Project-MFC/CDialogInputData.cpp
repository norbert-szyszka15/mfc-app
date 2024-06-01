#include "pch.h"
#include "Project-MFC.h"
#include "afxdialogex.h"
#include "CDialogInputData.h"

IMPLEMENT_DYNAMIC(CDialogInputData, CDialogEx)

CDialogInputData::CDialogInputData(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUT_DATA, pParent)
	, mX(0), mY(0), mColor(0)
{
	pDocum = pDoc;
	memset((void*)&lvi, 0, sizeof(LVITEMA));
	pDat = pDocum->pDat;
}

CDialogInputData::~CDialogInputData() {}

void CDialogInputData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRL, mListCtrl);
	DDX_Text(pDX, IDC_EDIT_NAME, mName);
	DDX_Text(pDX, IDC_EDIT_X, mX);
	DDX_Text(pDX, IDC_EDIT_Y, mY);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_POINT_COLOR, mColorButton);
	DDX_Control(pDX, IDC_COLOR_BOX, mStaticColor);
}

BEGIN_MESSAGE_MAP(CDialogInputData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDialogInputData::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDialogInputData::OnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDialogInputData::OnClickedButtonDelete)
	ON_BN_CLICKED(IDOK, &CDialogInputData::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_CTRL, &CDialogInputData::OnItemchangingListCtrl)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON_POINT_COLOR, &CDialogInputData::OnBnClickedMfccolorbuttonPointColor)
END_MESSAGE_MAP()

BOOL CDialogInputData::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	CString name, strX, strY, color;

	lvi.mask = LVIF_TEXT;
	lvi.state = 0;
	lvi.stateMask = 0;
	lvi.iImage = 0;

	HICON hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ProjectMFCTYPE));

	mSmallImageList.Create(16, 16, FALSE, 1, 0);
	mSmallImageList.Add(hIcon);
	mListCtrl.SetImageList(&mSmallImageList, LVSIL_SMALL);

	CRect rectListCtrl;
	memset(rectListCtrl, 0, sizeof(rectListCtrl));
	mListCtrl.GetClientRect(&rectListCtrl);

	int listCtrlWidth = rectListCtrl.right - rectListCtrl.left;
	int columnWidth = listCtrlWidth / 3;

	int ret;
	int nFormat = LVCFMT_LEFT;
	ret = mListCtrl.InsertColumn(0, "Name", nFormat, columnWidth, 0);
	ret = mListCtrl.InsertColumn(1, "X", nFormat, columnWidth, 1);
	ret = mListCtrl.InsertColumn(2, "Y", nFormat, columnWidth, 2);
	ret = mListCtrl.InsertColumn(3, "Color", nFormat, columnWidth, 3);

	ASSERT(pDat);
	int noItem = pDat->Size();

	lvi.iSubItem = 0;
	mListCtrl.SetItemCount(noItem);

	for (int i = 0; i < noItem; i++)
	{
		MyPoint pt = (*pDat)[i];
		lvi.iItem = i;
		name = pt.name;
		strX.Format("%le", pt.x);
		size_t len = strlen(strX);
		strY.Format("%le", pt.y);
		len += strlen(strY);
		color.Format("%d", pt.color);
		len += strlen(color);

		lvi.pszText = " ";
		lvi.cchTextMax = (int)len;
		ret = mListCtrl.InsertItem(&lvi);
		mListCtrl.SetItemText(lvi.iItem, 0, name);
		mListCtrl.SetItemText(lvi.iItem, 1, strX);
		mListCtrl.SetItemText(lvi.iItem, 2, strY);
		mListCtrl.SetItemText(lvi.iItem, 3, color);
	}

	mColorButton.SetColor(RGB(0, 0, 0));

	return TRUE;
}

void CDialogInputData::ModifyData()
{
	char st[512];
	BOOL ret(0);
	MyPoint tmp;

	UpdateData(TRUE);
	const int noIt(mListCtrl.GetItemCount());

	if (pDat) { delete pDat; }
	pDocum->pDat = pDat = new MyData(noIt);

	for (int nItem = 0; nItem < noIt; ++nItem)
	{
		ret = mListCtrl.GetItemText(nItem, 0, st, sizeof(st));
		tmp.name = st;
		ret = mListCtrl.GetItemText(nItem, 1, st, sizeof(st));
		tmp.x = atof(st);
		ret = mListCtrl.GetItemText(nItem, 2, st, sizeof(st));
		tmp.y = atof(st);
		ret = mListCtrl.GetItemText(nItem, 3, st, sizeof(st));
		int colorInt = atoi(st); 
		tmp.color = static_cast<COLORREF>(colorInt); 

		pDat->Push(tmp);
	}

	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}
 
double ColorToDouble(COLORREF color)
{
	return (double)((GetRValue(color) << 16) | (GetGValue(color) << 8) | GetBValue(color));
}

COLORREF DoubleToColor(double color)
{
	int intColor = (int)color;
	return RGB((intColor >> 16) & 0xFF, (intColor >> 8) & 0xFF, intColor & 0xFF);
}


void CDialogInputData::OnClickedButtonAdd()
{
	int nItem = mListCtrl.GetItemCount();
	int ret = -1;
	MyPoint tmp;
	CString strName, strX, strY, strColor;

	UpdateData(TRUE);

	COLORREF selectedColor = mColorButton.GetColor();
	mColor = selectedColor; 

	TRACE("Selected Color (COLORREF): R=%d, G=%d, B=%d\n", GetRValue(selectedColor), GetGValue(selectedColor), GetBValue(selectedColor));

	tmp.x = mX;
	tmp.y = mY;
	tmp.color = mColor;
	tmp.name = mName;

	pDat->Push(tmp);

	strName = mName;
	strX.Format("%le", mX);
	strY.Format("%le", mY);
	strColor.Format("%d", selectedColor); 

	lvi.iItem = nItem;
	lvi.pszText = _T("");
	lvi.cchTextMax = 0;
	ret = mListCtrl.InsertItem(&lvi);
	mListCtrl.SetItemText(lvi.iItem, 0, strName);
	mListCtrl.SetItemText(lvi.iItem, 1, strX);
	mListCtrl.SetItemText(lvi.iItem, 2, strY);
	mListCtrl.SetItemText(lvi.iItem, 3, strColor);

	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}

void CDialogInputData::OnClickedButtonModify()
{
	int ret = -1;
	int noItem = mListCtrl.GetItemCount();

	if (mSelItem < 0 || mSelItem >= noItem) { return; }

	MyPoint tmp;
	CString strName, strX, strY, strColor;
	int nItem = mSelItem;

	UpdateData(TRUE);

	COLORREF selectedColor = mColorButton.GetColor();
	mColor = selectedColor;

	TRACE("Selected Color (COLORREF): R=%d, G=%d, B=%d\n", GetRValue(selectedColor), GetGValue(selectedColor), GetBValue(selectedColor));

	tmp.name = mName;
	tmp.x = mX;
	tmp.y = mY;
	tmp.color = mColor;

	(*pDat)[nItem] = tmp;

	strName = mName;
	strX.Format("%le", mX);
	strY.Format("%le", mY);
	strColor.Format("%d", selectedColor);

	lvi.iItem = nItem;
	mListCtrl.SetItemText(lvi.iItem, 0, strName);
	mListCtrl.SetItemText(lvi.iItem, 1, strX);
	mListCtrl.SetItemText(lvi.iItem, 2, strY);
	mListCtrl.SetItemText(lvi.iItem, 3, strColor);

	UpdateData(FALSE);

	ModifyData();
}


void CDialogInputData::OnClickedButtonDelete() 
{
	int ret = -1;
	UpdateData(TRUE);

	int noItem = mListCtrl.GetItemCount();

	if (mSelItem < 0 || mSelItem >= noItem) { return; }

	mListCtrl.DeleteItem(mSelItem);
	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}

void CDialogInputData::OnBnClickedOk()
{
	CDialogEx::OnOK();

	ModifyData();
}

//zmiany pat
void CDialogInputData::OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	UpdateData(TRUE);

	int nItem = mSelItem = pNMLV->iItem;
	int noItem = mListCtrl.GetItemCount();

	if (mSelItem < 0 || mSelItem >= noItem) { return; }

	int nCol = 0;
	char st[512];
	BOOL ret = mListCtrl.GetItemText(nItem, nCol, st, sizeof(st));

	mName = st;
	nCol = 1;
	ret = mListCtrl.GetItemText(nItem, nCol, st, sizeof(st));

	mX = atof(st);
	nCol = 2;
	ret = mListCtrl.GetItemText(nItem, nCol, st, sizeof(st));

	mY = atof(st);
	nCol = 3;
	ret = mListCtrl.GetItemText(nItem, nCol, st, sizeof(st));

	int r, g, b;
	if (sscanf_s(st, "R=%d, G=%d, B=%d", &r, &g, &b) == 3)
	{
		mColor = RGB(r, g, b);
	}
	else
	{
		mColor = atol(st);
	}

	mColorButton.SetColor(mColor);

	mBrushColor.DeleteObject();
	mBrushColor.CreateSolidBrush(mColorButton.GetColor());
	mStaticColor.Invalidate();
	mStaticColor.UpdateWindow();

	UpdateData(FALSE);
}

HBRUSH CDialogInputData::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_COLOR_BOX) { hbr = mBrushColor; }

	return hbr;
}

void CDialogInputData::OnBnClickedMfccolorbuttonPointColor() 
{
	mBrushColor.DeleteObject();
	mBrushColor.CreateSolidBrush(mColorButton.GetColor());
	mStaticColor.Invalidate();
	mStaticColor.UpdateWindow();
}
