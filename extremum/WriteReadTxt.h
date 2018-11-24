#ifndef __WRITEREADTXT_H__
#define __WRITEREADTXT_H__
#include "stdafx.h"
#include "resource.h"
extern CString GetPath_sln(void);
extern CString GetCurrentData();
extern void WriteToTxt(CString filename, double *pInputnum,int numLength );
extern void ReadFromTxt(CArray<double,double&> &arydtemp);
#endif