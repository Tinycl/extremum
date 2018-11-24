#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "emd.h"
#include "cubic.h"
#include "WriteReadTxt.h"

int Max_size;    //����ֵ��Сֵ��ĸ���
int Min_size;
void findpeak(double *x,double *y,double *x1,double *y1,double *x2,double *y2)
{
	int i,j=1,k=1;
	x1[0]=x[0];//�˵�ֵ
	y1[0]=y[0];
	x2[0]=x[0];
	y2[0]=y[0];
	Max_size=0;
	Min_size=0;
	
	ARRAYstruct arystruct;
	arystruct = ArrayGetMaxMinAndIndex(&y[0], EMDN);
	/*************�ź�ȫ�Ǵ���0�����********************/
	if (arystruct.darymin > 0)
	{
		for(i=0;i<EMDN-2;i++)
		{
			if(y[i+1]>=y[i]&&y[i+1]>y[i+2])
			{
				x1[j]=x[i+1];
				y1[j]=y[i+1];
				j++;
			}
			Max_size=j;
			if(y[i+1]<=y[i]&&y[i+1]<y[i+2])
			{
				x2[k]=x[i+1];
				y2[k]=y[i+1];
				k++;
			}
			Min_size=k;
		}
	}else/*************�źŹ��������***********************/
	{
		for(i=0;i<EMDN-2;i++)
		{
			if(y[i+1]>=y[i]&&y[i+1]>y[i+2])
			{
				if (y[i+1] > 0)
				{
					x1[j]=x[i+1];
					y1[j]=y[i+1];
					j++;
				}
			}
			Max_size=j;
			if(y[i+1]<=y[i]&&y[i+1]<y[i+2])
			{
				if (y[i+1] < 0)
				{
					x2[k]=x[i+1];
					y2[k]=y[i+1];
					k++;
				}
			}
			Min_size=k;
		}
	}
	
	x1[Max_size]=x[EMDN-1];//�˵�ֵ
	y1[Max_size]=y[EMDN-1];
	x2[Min_size]=x[EMDN-1];
	y2[Min_size]=y[EMDN-1];
}

void splineemd(coefficient *coe,double *xx,double *yy,int M,double *ss)
{

    double a[EMDN/2][EMDN/2]={0.0};
	double temp,t=0;
	int i,j;
	double *h = new double[M];
	double *f = new double[M];
	double *m = new double[M+1];
	double *s = new double[EMDN + 1];
	for(i=0;i<M;i++)
	{
		h[i]=xx[i+1]-xx[i];
		f[i]=(yy[i+1]-yy[i])/h[i];
	}
	for(i=0;i<M-1;i++)
	{
		coe[i].lamda=h[i+1]/(h[i]+h[i+1]);
		coe[i].u=1-coe[i].lamda;
		coe[i].c=3*((coe[i].lamda)*f[i]+(coe[i].u)*f[i+1]);
	}
	/****��ʼ������ϵ��****/
	for(i=1;i<M;i++)
	{
		a[i][M+1]=coe[i-1].c;
	}
	a[0][M+1]=3*f[0];
	a[M][M+1]=3*f[M-1];
	a[0][0]=2;
	a[0][1]=1;
	a[M+1][M-1]=1;
	a[M][M]=2;
	for(i=1;i<M;i++)
	{
		a[i][i-1]=coe[i-1].lamda;
		a[i][i]=2;
		a[i][i+1]=coe[i-1].u;
	}
	/******��˹��Ԫ*******/
	/******��Ԫ����Ϊ��������******/
	for(i=1;i<M+1;i++)
	{
		for(j=0;j<M+2;j++)
		{
			a[i][j]=a[i][j]-a[i-1][j]/a[i-1][i-1]*a[i][i-1];
		}
	}
	m[i-1]=a[i-1][j-1]/a[i-1][j-2];//������һ��m��ֵ
	/*******�ش�����������mֵ*******/
	for(i=M-1;i>=0;i--)
	{
		for(j=i+1;j<=M;j++)
		{
			temp=0;
			temp=temp+m[j]*a[i][j];
		}
		m[i]=(a[i][M+1]-temp)/a[i][i];
	}
	/****������������ֵ****/
	j=0;
	t=0;
	for(i=0;i<M+1;i++)
	{
		for(;t<=xx[i+1];t=t+1.0)    //1Ϊ�źŵĲ�������,ԭʼ�źź��������1
		{
			s[j++]=(h[i]+2*(t-xx[i]))*pow((t-xx[i+1]),2)*yy[i]/pow(h[i],3)
				+(h[i]-2*(t-xx[i+1]))*pow((t-xx[i]),2)*yy[i+1]/pow(h[i],3)
				+(t-xx[i])*pow((t-xx[i+1]),2)*m[i]/pow(h[i],2)
				+(t-xx[i+1])*pow((t-xx[i]),2)*m[i+1]/pow(h[i],2);
		}
	}
	s[EMDN-1]=yy[M];

	for (int kk = 0; kk < EMDN; kk ++)
	{
		ss[kk] = s[kk];
	}


	
	delete[] s;
	delete[] h;
	delete[] f;
	delete[] m;
}

void imf(double *x,double *h,double *x1,double *y1,double *x2,double *y2,double *outh)
{
	/*    ����˵��:s1,s2��ʾ�źŵ����°���
	**             r[N]�������
	**             m[N]���°���ľ�ֵ
	**			   
	**/
	int i,count=1;
	int hcount = 0;
	long double SD = 0.0;
	double *r = new double[EMDN];
	coefficient coef[EMDN/2];
	double *m = new double[EMDN];
	double *temp = new double[EMDN];
	double *s1 = new double[EMDN+1];
	double *s2 = new double[EMDN+1];
	double outhtemp[EMDN];
	for (i = 0; i < EMDN; i++)
	{
		r[i]=0.0;
		m[i]=0.0;
		temp[i]=0.0;
		outh[i]=0.0;
		outhtemp[i] = 0;
	}
	for (i = 0; i < EMDN+1; i++)
	{
		s1[i]=0.0;
		s2[i]=0.0;
	}

	/*��ʼ��r[N]*/
	for(i=0;i<EMDN;i++)
	{
		r[i]=h[i];
	}

	/*����ģ��������ֵ�ź�*/ 
	for (int imfcount = 0; imfcount <2; imfcount ++)
	{
		
		/**��һ����imf��ԭʼ�ź�y[t]*******************/
		do
		{
				findpeak(x,h,x1,y1,x2,y2);              //��ֵ�㣬y1��ż���ֵ��y2��ż�Сֵ
				splineemd(coef,x1,y1,Max_size,s1);          //����ֵ����
				splineemd(coef,x2,y2,Min_size,s2);          //��Сֵ����
				for(i=0;i<EMDN;i++)
				{
					m[i]=(s1[i]+s2[i])/2;
				}
				for(i=0;i<EMDN;i++)
				{
					temp[i]=h[i];
					h[i]=h[i]-m[i];
				}
		
				for(i=0;i<EMDN;i++)
				{
					SD += h[i];
				}
				SD = SD/EMDN;

		  } while(abs(SD) > 0.01);//�����һ��imf
		    SD = 0.0;
			/*����������*/
			for(i=0;i<EMDN;i++)             //���������ȥ����Ƶ�����Ĳ�ֵ�ź�r(t)
			{
				r[i]=r[i]-h[i];
			}
			/***********���ÿ�μ�����ı�������,Ȼ���ۼ����ڼ������ԭʼ�ź�**************/
			for (i = 0; i < EMDN; i ++)
			{
				outhtemp[i] += h[i];
			}
			/***********������Ҫ�ò�ֵ�źż�����imf,���¸�h��ֵ������ѭ��*************************/
			/*if (imfcount == 0)
			{
				WriteToTxt(_T("IMF00"),h,N);
				WriteToTxt(_T("H00"),r,N);
			}
            if (imfcount == 1)
            {
				WriteToTxt(_T("IMF01"),h,N);
				WriteToTxt(_T("H01"),r,N);
            }*/
			for (i=0;i<EMDN;i++)
			{
				h[i] = r[i];
			}
	} 
	for (i = 0; i < EMDN; i ++)
	{
       outh[i] = outhtemp[i]; 
	}

	/***********ԭʼ�ź� = sum(imf) + r(last)**********/

	delete[] r;
	delete[] m;
	delete[] temp;
	delete[] s1;
	delete[] s2;
}

void emd(double* pInputnum, int numLength)
{

	double *x = new double[EMDN];//ԭʼ�źź�����
	double *y = new double[EMDN];//ԭʼ�ź�ֵ
	double *x1 = new double[EMDN/2];//����ֵ������
	double *y1 = new double[EMDN/2];//����ֵ
	double *x2 = new double[EMDN/2];//��Сֵ������
	double *y2 = new double[EMDN/2];//��Сֵ
	//x2����źż�Сֵ���ĺ�����ֵ��y2����źż�Сֵ
    /******ԭʼ�źŴ���EMD���Ⱦͽ�ȡ��С��EMD���ȾͲ���*************/
	if (numLength >= EMDN)
	{
		for (int kk = 0; kk < EMDN; kk ++)
		{
			x[kk] = kk * 1.0;
			y[kk] = pInputnum[kk];
		}
	}
	else 
	{
		for (int kk = 0; kk < numLength; kk ++)
		{
			x[kk] = kk * 1.0;
			y[kk] = pInputnum[kk];
		}
		for (int kk = numLength ; kk < EMDN; kk ++)
		{
			x[kk] = kk * 1.0;
			y[kk] = 0.0;
		}

	}
	/*********************EMD��������END******************/
	/* rΪ�ֽ��ı���ģ����*/
	double outhf[EMDN];
	imf(x,y,x1,y1,x2,y2,outhf);
	WriteToTxt(_T("�ۼ�IMF"),outhf,EMDN);
		
	delete[] x;
	delete[] y;
	delete[] x1;
	delete[] y1;
	delete[] x2;
	delete[] y2;
	//delete[] outhf;
}