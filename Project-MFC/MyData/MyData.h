// MyData.h : main header file for the MyData DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#ifdef MYDATA_EXPORTS
#define MYDATA_API __declspec(dllexport)
#else
#define MYDATA_API __declspec(dllimport)
#endif

// CMyDataApp
// See MyData.cpp for the implementation of this class
//

class CMyDataApp : public CWinApp
{
public:
	CMyDataApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#pragma pack(push, 1)
//modyfikacja pat
class MYDATA_API MyPoint
{
public:
	double x, y;
	COLORREF color;  // Przechowywanie koloru jako COLORREF

	MyPoint() : x(0), y(0), color(RGB(0, 0, 0)) {}
	MyPoint(double xx, double yy, COLORREF c) : x(xx), y(yy), color(c) {}
	~MyPoint() {}
	void set(double xx, double yy, COLORREF c) { x = xx; y = yy; color = c; }
	MyPoint get() { return *this; }
};

//modyfikacja pat
class MYDATA_API MyData
{
protected:
	MyPoint* pTab;
	int capacity;
	int last;

public:
	MyData(int noIt);
	MyData(const MyData& ob);
	~MyData() { Free(); }
	int Size() { return last; }
	void Free() { if (pTab) delete[] pTab; pTab = NULL; }
	void Init(int noIt);
	void Push(const MyPoint& tmp);
	void Clear() { last = 0; }
	void GetMinMaxCoords(double& maxX, double& minX, double& maxY, double& minY);

	// Overload of index operator
	MyPoint& operator[] (const int i) const { return pTab[i]; }

private:
	MyPoint* allocTab(MyPoint* pTab, int n);
};


#pragma pack(pop)
