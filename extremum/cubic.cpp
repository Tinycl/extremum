/*=======================================================================*/  
#include <stdio.h> 
#include "stdafx.h"
#include "cubic.h" 
#include <math.h>
#include "WriteReadTxt.h"
  
/*=============================================================================== 
*** �������ƣ� Spline3() 
*** ����˵���� �������������ֵ������ʹ��׷�Ϸ����M���� 
*** ��ڲ����� (pSPLINE)pLine  �����ṹ��ָ��pLine�е�x[],y[],num,begin_k1,end_k1 
*** ���ڲ����� (pSPLINE)pLine  �����ṹ��ָ��pLine�еĺ������� 
*** ���ز����� ���س���ִ�н����״̬TRUE or FALSE 
================================================================================*/  
RESULT Spline3(pSPLINE pLine)  
{  
	float H[MAXNUM] = {0};     //С����Ĳ���  
	float Fi[MAXNUM] = {0};     //�м���  
	float U[MAXNUM+1] = {0};    //�м���  
	float A[MAXNUM+1] = {0};    //�м���  
	float D[MAXNUM+1] = {0};    //�м���  
	float M[MAXNUM+1] = {0};    //M����  
	float B[MAXNUM+1] = {0};    //׷�Ϸ��м���  
	float Y[MAXNUM+1] = {0};    //׷�Ϸ��м����  
	int i = 0;  
	////////////////////////////////////////�����м����  
	if((pLine->point_num < 3) || (pLine->point_num > MAXNUM + 1))  
	{  
		return ERR;       //�������ݵ����̫�ٻ�̫��  
	}  
	for(i = 0;i <= pLine->point_num-2 ;i++)  
	{          //��H[i]  
		H[i] = pLine->x[i+1] - pLine->x[i];  
		Fi[i] = (pLine->y[i+1] - pLine->y[i]) / H[i]; //��F[x(i),x(i+1)]  
	}  
	for(i = 1;i <= pLine->point_num - 2;i++)  
	{          //��U[i]��A[i]��D[i]  
		U[i] = H[i-1] / (H[i-1] + H[i]);  
		A[i] = H[i] / (H[i-1] + H[i]);  
		D[i] = 6 * (Fi[i] - Fi[i-1]) / (H[i-1] + H[i]);  
	}  
	//���߽�����Ϊ1����������  
	U[i] = 1;  
	A[0] = 1;  
	D[0] = 6 * (Fi[0] - pLine->begin_k1) / H[0];  
	D[i] = 6 * (pLine->end_k1 - Fi[i-1]) / H[i-1];  
	//���߽�����Ϊ2����������  
	//U[i] = 0;  
	//A[0] = 0;  
	//D[0] = 2 * begin_k2;  
	//D[i] = 2 * end_k2;  
	/////////////////////////////////////////׷�Ϸ����M����  
	B[0] = A[0] / 2;  
	for(i = 1;i <= pLine->point_num - 2;i++)  
	{  
		B[i] = A[i] / (2 - U[i] * B[i-1]);  
	}  
	Y[0] = D[0] / 2;  
	for(i = 1;i <= pLine->point_num-1 ;i++)  
	{  
		Y[i] = (D[i] - U[i] * Y[i-1]) / (2 - U[i] * B[i-1]);  
	}  
	M[pLine->point_num - 1] = Y[pLine->point_num - 1];  
	for(i = pLine->point_num ;i > 0;i--)  
	{  
		M[i-1] = Y[i-1] - B[i-1] * M[i];  
	}  
	//////////////////////////////////////////���㷽�������ս��  
	for(i = 0;i <= pLine->point_num-2 ;i++)  
	{  
		pLine->a3[i] = M[i] / (6 * H[i]);  
		pLine->a1[i] = (pLine->y[i] - M[i] * H[i] * H[i] / 6) / H[i];  
		pLine->b3[i] = M[i+1] / (6 * H[i]);  
		pLine->b1[i] = (pLine->y[i+1] - M[i+1] * H[i] * H[i] / 6) /H[i];  
	}  
	return TRUE;  
}
/*****************************************************************
ʹ��ʱ�����µ�����
������Ĵ�С= (ԭ�����GetSize()-1) * (m_iInsertCount + 1) + 1)��
********************************************************/
//////////////////////////////////////////////////////////////////////////////////  
int CubicInsertFun(double *pAfterInsert,double *pBeforeInsert,int BeforeInLength,int InsertCount )  
{   
	    SPLINE line1;  
	    pSPLINE pLine1 = &line1;
		line1.point_num = BeforeInLength; 
		//�洢ԭʼ��X��Y
		for (int kk = 0; kk < line1.point_num; kk++)
		{
			line1.x[kk] = kk;  
			line1.y[kk] = pBeforeInsert[kk];  
		}
		 
		line1.begin_k1 = 0;  
		line1.end_k1 = 0;  
		Spline3(pLine1); 
		//����֮������鳤��Ӧ��Ϊ(line1.point_num-1)*(InsertCount+1)
 		for (int i=0;i<=(line1.point_num-1)*(InsertCount+1);i++)
 		{
 			line1.x3[i]=i;
 		}
		//����������
		int iIndex=0;//����ȥ����֮��ԭʼ���ݶ�Ӧ���±�
		for (int i=0;i<=(line1.point_num-1)*(InsertCount+1);i+=InsertCount+1)
		{   
			line1.y3[i]=line1.y[iIndex];//ԭʼ����
			for (int m=1;m<=InsertCount;m++)
			{
				double d=iIndex+((m*1.0)/(InsertCount*1.0+1.0));
				line1.y3[iIndex*(InsertCount+1)+m]=line1.a3[iIndex]*(line1.x[iIndex+1]-d)*(line1.x[iIndex+1]-d)*(line1.x[iIndex+1]-d)+
					line1.a1[iIndex]*(line1.x[iIndex+1]-d)+line1.b3[iIndex]*(d-line1.x[iIndex])*(d-line1.x[iIndex])*(d-line1.x[iIndex])+
					line1.b1[iIndex]*(d-line1.x[iIndex]);//��ֵ�������
				
			}
			iIndex++;
		
		}
		
		/////////////////////////////////////////////
		for (int i=0;i<=(line1.point_num-1)*(InsertCount+1);i++)
		{
			pAfterInsert[i]=line1.y3[i];
		}
		
		return 0;  
} 

int Sin_Interpolation(double *pResult, double *origin_data, int sampleNum, int insertNum)
{
	int n, m, k;
	k = 0;
	double sin_parameter , sin_ratio , temp , sin_value = 0;
	int i;
	// ��ԭ����ֵ �ŵ���ֵ���еĺ���λ��
	for(n=0, i=0; n < sampleNum; n++)
	{
		pResult[i] = origin_data[n];
		i += (insertNum + 1);
	}

	// ������ѭ�������ÿ��������֮��Ĳ�ֵ����
	// ����һ�㣺ԭʼ�������� sampleNum ��Ϊѭ������
	// �м�һ�㣺��������֮�����ĵ��� insertNum ��Ϊѭ����������ʱinsertNumΪ����ֵ�����ɱ䣬��������1��insertNum��sampleNum-1
	// ����һ�㣺����ʱ���õ��Ĳ������� k ��Ϊѭ������(�ɱ�)��0��k��
	for (n = 0; n < sampleNum - 1; n++)				// �ӵ�0�������� �� ��sampleNum-1��������֮�� ��Ҫ���в�ֵ 
	{
		for (m = 1; m <= insertNum; m++)			// ÿ����������֮�����insertNum����
		{
			pResult[n * (insertNum + 1) + m] = 0;

			for (k = 0; k < sampleNum; k++)			// ÿ����ֵ���� sampleNum ��������������õ�
			{
				sin_parameter = (double)(m * 1.0 / (insertNum + 1)) + n - k;		// ����������������Ϊ����
				sin_parameter *= PI;
				sin_ratio = sin(sin_parameter) / sin_parameter;			// �������ֵϵ��
				temp = origin_data[k] * sin_ratio;						// �������
				pResult[n * (insertNum + 1) + m] += temp;				// ���
			}// end of for1
		}// end of for2
	}// end of for3

	return TRUE;
}// end of int Sin_Interpolation
void SmoothFilter(double* p, int num, double* ptemp, int SFnum)
{

	for (int i = 0; i < num; i++)
	{
		if (i <= num -1 - SFnum && i >= SFnum)
		{
			double temp = 0;
			for (int j = -SFnum; j <= SFnum; j++)
				temp += p[i+j];
			ptemp[i] = /*static_cast<int>*/(temp/(2.0*SFnum+1.0));
		}
		if (i<SFnum)
		{
			double temp = 0;
			for (int j = -i; j <= SFnum;j++)
				temp += p[i+j];
			ptemp[i] = /*static_cast<int>*/(temp/((i + SFnum +1.0)*1.0));
		}

		if (i> num - SFnum)
		{
			double temp = 0;
			for (int j = -SFnum; j <= num - 1 - i;j++)
				temp += p[i+j];
			ptemp[i] = /*static_cast<int>*/(temp/(1.0*(num-i +SFnum +1)));
		}
	}
	//for(int i = 0;i<num;i++)
	//{
	//	p[i] = ptemp[i];
	//}
}

double Format2valuable(double dtemp)
{
	int itemp = dtemp;
	int itemp1 = dtemp * 100;
	int itempback2 = itemp1 % 10; 
	int itemp2 =itemp1 / 10;
	int itempback1 = itemp2 % 10;
	int itemp3 = itemp2 / 10;
	if (itempback2 == 0)
	{
		itempback2 = 0 ;
	}
	double itempformat = itempback2 * 0.01 + itempback1 * 0.1 + itemp;
	return itempformat;
}

ARRAYstruct ArrayGetMaxMinAndIndex(double *pin, int length)
{
	ARRAYstruct arystruct;
	double dmax = -10000.0, dmin = 10000.0;
	int imaxindex = 0, iminindex = 0;
	for (int kk = 0; kk < length; kk ++)
	{
		if (pin[kk] > dmax)
		{
			dmax = pin[kk];
			imaxindex = kk;
		}
		if (pin[kk] < dmin)
		{
			dmin = pin[kk];
			iminindex = kk;
		}
	}
	arystruct.darymax = dmax;
	arystruct.darymin = dmin;
	arystruct.maxindex = imaxindex;
	arystruct.minindex = iminindex;
	return arystruct;
}