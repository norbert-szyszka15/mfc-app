// InputDataDlg.cpp: plik implementacji
//

#include "pch.h"
#include "Project-MFC.h"
#include "afxdialogex.h"
#include "InputDataDlg.h"


// Okno dialogowe InputDataDlg

IMPLEMENT_DYNAMIC(InputDataDlg, CDialogEx)

InputDataDlg::InputDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

InputDataDlg::~InputDataDlg()
{
}

void InputDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputDataDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &InputDataDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &InputDataDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &InputDataDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT2, &InputDataDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// Procedury obsługi komunikatów InputDataDlg


void InputDataDlg::OnBnClickedButton2()
{
	// TODO: Dodaj tutaj swój kod procedury obsługi powiadamiania kontrolki
}


void InputDataDlg::OnBnClickedButton1()
{
	// TODO: Dodaj tutaj swój kod procedury obsługi powiadamiania kontrolki
}


void InputDataDlg::OnBnClickedButton3()
{
	// TODO: Dodaj tutaj swój kod procedury obsługi powiadamiania kontrolki
}


void InputDataDlg::OnEnChangeEdit2()
{
	// TODO:  Jeżeli to jest kontrolka RICHEDIT, to kontrolka nie będzie
	// wyślij to powiadomienie, chyba że przesłonisz element CDialogEx::OnInitDialog()
	// funkcja i wywołanie CRichEditCtrl().SetEventMask()
	// z flagą ENM_CHANGE zsumowaną logicznie z maską.

	// TODO:  Dodaj tutaj swój kod procedury obsługi powiadamiania kontrolki
}
