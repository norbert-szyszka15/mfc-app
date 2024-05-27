// MyData.cpp : Defines the initialization routines for the DLL.
//
#include "pch.h"
#include "framework.h"
#include "MyData.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CMyDataApp

BEGIN_MESSAGE_MAP(CMyDataApp, CWinApp)
END_MESSAGE_MAP()


// CMyDataApp construction

CMyDataApp::CMyDataApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMyDataApp object

CMyDataApp theApp;


// CMyDataApp initialization

BOOL CMyDataApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

MyPoint* MyData::allocTab(MyPoint* pTab, int n)
{
	try
	{
		if (!pTab)
		{
			pTab = new MyPoint[n];
			capacity = n;
			return pTab;
		}
	}
	catch (std::bad_alloc)
	{
	}
}

MyData::MyData(int noIt)
{
	pTab = NULL;
	Init(noIt);
}

MyData::MyData(const MyData& ob)
{
	capacity = ob.capacity;
	last = ob.last;
	pTab = NULL;
	pTab = allocTab(pTab, capacity);
	if (pTab)
	{
		std::copy(ob.pTab, ob.pTab + last, pTab);
	}
}

void MyData::Init(int noIt)
{
	capacity = noIt;
	last = 0;
	pTab = allocTab(pTab, capacity);
}

//modyfikacja pat
void MyData::Push(const MyPoint& tmp)
{
	if (last >= capacity)
	{
		int delta = last - capacity;
		int newCapacity = (delta > capacity) ? (capacity + delta) : (2 * capacity);
		int oldCapacity(capacity);
		MyPoint* newTab(NULL);
		newTab = allocTab(newTab, newCapacity);
		std::copy(pTab, pTab + oldCapacity, newTab);
		delete[] pTab;
		pTab = newTab;
		capacity = newCapacity;
	}

	pTab[last++] = tmp;
}


void MyData::GetMinMaxCoords(double& maxX, double& minX, double& maxY, double& minY)
{
	maxX = minX = maxY = minY = 0;

	if (pTab && last)
	{
		maxX = minX = pTab[0].x;
		maxY = minY = pTab[0].y;

		for (int i = 1; i < last; ++i)
		{
			if (pTab[i].x > maxX) { maxX = pTab[i].x; }
			if (pTab[i].y > maxY) { maxY = pTab[i].y; }
			if (pTab[i].x < minX) { minX = pTab[i].x; }
			if (pTab[i].y < minY) { minY = pTab[i].y; }
		}
	}
}
