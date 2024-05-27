// Except1.h : main header file for the Except1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

class MyData;

#include "resource.h"      // main symbols
#include "MyData.h"

// CExcept1App
// See Except1.cpp for the implementation of this class
//

#ifdef EXCEPT1_EXPORT
#define EXCEPT1_API __declspec(dllexport)
#else
#define EXCEPT1_API __declspec(dllimport)
#endif

#define APP_START_MESSAGE WM_USER+100

enum ITS_APP_MESSAGE {
    WM_START = APP_START_MESSAGE,
    WM_DIS_MSG,
    WM_CLEAR_OUTPUT,
    WM_DIS_TOTALMES
};

class CExcept1App : public CWinApp {
public:
    CWnd* ptrWnd;
    MyData* ptrDat;

public:
    CExcept1App();
    void SetWnd(CWnd* ptrwnd, MyData* pdat) { ptrWnd = ptrwnd; ptrDat = pdat; }
    void ResetData(MyData* pdat) { ptrDat = pdat; }
    EXCEPT1_API void PutMessage(UINT ID_Message); // Ensure export for DLL
    EXCEPT1_API void ClearOutWnd(); // Ensure export for DLL

    // Overrides
public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};

extern "C" EXCEPT1_API CExcept1App * PASCAL EXPORT GetExceptPtr();