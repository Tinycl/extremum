#ifndef __EMD_H__
#define __EMD_H__
#define EMDN 5000
#include "cubic.h"

typedef struct			//定义一个系数结构体，用来存放方程组中的系数值
{
	double lamda;
	double u;
	double c;
}coefficient;

extern void findpeak(double *x,double *y,double *x1,double *y1,double *x2,double *y2);
extern void splineemd(coefficient *coe,double *xx,double *yy,int M,double *ss);
extern void imf(double *x,double *h,double *x1,double *y1,double *x2,double *y2,double *outh);
extern void emd(double* pInputnum, int numLength);
#endif