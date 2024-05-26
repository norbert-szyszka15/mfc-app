#pragma once
#include "afxdialogex.h"


// Okno dialogowe InputDataDlg

class InputDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InputDataDlg)

public:
	InputDataDlg(CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~InputDataDlg();

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit2();
};
