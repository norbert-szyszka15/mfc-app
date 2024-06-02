#pragma once
#include "afxdialogex.h"
#include "MyData.h"
#include "Project-MFCDoc.h"

class CDialogInputData : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogInputData)

public:
	CDialogInputData(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);
	virtual ~CDialogInputData();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	void ModifyData();

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl mListCtrl;
	LV_ITEM lvi;
	CImageList mSmallImageList;
	MyData* pDat;
	CProjectMFCDoc* pDocum;
	int mSelItem;

	double mX;
	double mY;
	int mColor;
	CString mName;

	CBrush mBrushColor;
	CMFCColorButton mColorButton;
	CStatic mStaticColor;

	afx_msg void OnClickedButtonAdd();
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnBnClickedMfccolorbuttonPointColor();
	afx_msg void OnBnClickedOk();
	afx_msg void OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
