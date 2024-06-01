#include "pch.h"
#include "framework.h"
#include "Except1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CExcept1App, CWinApp)
END_MESSAGE_MAP()

CExcept1App::CExcept1App() 
{
    ptrWnd = NULL;
    ptrDat = NULL;
}

void CExcept1App::PutMessage(UINT ID_Message) const 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    HINSTANCE hInstance = GetModuleHandleA(NULL);
    char str[1024];
    int ret = LoadStringA(hInstance, ID_Message, str, sizeof(str));

    if (ptrWnd) 
    {
        ptrWnd->SendMessage(WM_DIS_MSG, (WPARAM)str, (LPARAM)ptrDat);
    } 
    else if (!ptrWnd && str[0] == 'E') 
    {
        CString sstr(str);
        AfxMessageBox(sstr);
        UINT uExitCode = 0;
        HANDLE hHandle = GetCurrentProcess();
        TerminateProcess(GetCurrentProcess(), uExitCode);
    }
}

void CExcept1App::ClearOutWnd() const 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if (ptrWnd) 
    {
        ptrWnd->SendMessage(WM_CLEAR_OUTPUT, 0, 0);
    }
}

CExcept1App theApp;

BOOL CExcept1App::InitInstance() 
{
    CWinApp::InitInstance();

    return TRUE;
}

extern "C" EXCEPT1_API CExcept1App * PASCAL EXPORT GetExceptPtr() 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return &theApp;
}