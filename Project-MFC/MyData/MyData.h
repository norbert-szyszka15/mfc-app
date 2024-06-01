#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		

#ifdef MYDATA_EXPORTS
#define MYDATA_API __declspec(dllexport)
#else
#define MYDATA_API __declspec(dllimport)
#endif

class CMyDataApp : public CWinApp
{
public:
	CMyDataApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#pragma pack(push, 1)
class CExcept1App;

class MYDATA_API MyPoint 
{
public:
	CString name;
	double x, y;
	COLORREF color;

public:
	MyPoint();
	MyPoint(CString n, double xx, double yy, COLORREF c);
	~MyPoint();
	void set(CString n, double xx, double yy, COLORREF c);
	MyPoint get() const;
};

class MYDATA_API MyData 
{
protected:
	MyPoint* pTab;
	int capacity;
	int last;

public:
	CExcept1App* pExcept;

public:
	MyData(int noIt);
	MyData(const MyData& ob);
	~MyData();
	int Size() const;
	void Free();
	void Init(int noIt);
	void Push(const MyPoint& tmp);
	void Clear();
	void GetMinMaxCoords(double& maxX, double& minX, double& maxY, double& minY);

public:
	MyPoint& operator[] (const int i) const;

private:
	MyPoint* allocTab(MyPoint* pTab, int n);
};

#pragma pack(pop)