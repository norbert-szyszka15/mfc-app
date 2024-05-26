#pragma once
#include "afxdialogex.h"
#include "MyData.h"
#include "Project-MFCDoc.h"




// CDialogInputData dialog

class CDialogInputData : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogInputData)

public:
	CDialogInputData(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogInputData();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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

	afx_msg void OnClickedButtonAdd();
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
	double mX;
	double mY;
	int mColor;
	afx_msg void OnBnClickedOk();
	afx_msg void OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	CBrush mBrushColor;
	CMFCColorButton mColorButton;
	CStatic mStaticColor;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnBnClickedMfccolorbuttonPointColor();
};
