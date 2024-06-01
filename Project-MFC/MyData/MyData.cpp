#include "pch.h"
#include "framework.h"
#include "MyData.h"
#include <iostream>
#include "Except1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMyDataApp, CWinApp)
END_MESSAGE_MAP()

CMyDataApp::CMyDataApp() {}

CMyDataApp theApp;

BOOL CMyDataApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

MyPoint::MyPoint() : name(_T("point")), x(0), y(0), color(RGB(0, 0, 0)) {}

MyPoint::MyPoint(CString n, double xx, double yy, COLORREF c) : name(n), x(xx), y(yy), color(c) {}

MyPoint::~MyPoint() {}

void MyPoint::set(CString n, double xx, double yy, COLORREF c) 
{
	name = n;
	x = xx;
	y = yy;
	color = c;
}

MyPoint MyPoint::get() const 
{
	return *this;
}

MyData::MyData(int noIt)
{
	pExcept = GetExceptPtr();
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

MyData::~MyData() 
{ 
	Free(); 
}

int MyData::Size() const 
{
	return last;
}

void MyData::Free() 
{ 
	if (pTab) { delete[] pTab; }
	pTab = NULL;
}

void MyData::Init(int noIt)
{
	capacity = noIt;
	last = 0;
	pTab = allocTab(pTab, capacity);
}

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

void MyData::Clear() 
{ 
	last = 0;
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

MyPoint& MyData::operator[](const int i) const 
{
	return pTab[i];
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
		CExcept1App* pExcp = (CExcept1App*)pExcept;
		pExcept->PutMessage(1002);
	}
}