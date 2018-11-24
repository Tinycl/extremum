#ifndef __CUBIC_H__
#define __CUBIC_H__

#define  MAXNUM  6000   //����������������������Ϊ5000��  
#define PI 3.1415926
typedef struct SPLINE    //���������ṹ�壬���ڴ洢һ��������������Ϣ  
{ //��ʼ����������  
	float x[MAXNUM+1];    //�洢�����ϵĵ��x���꣬���5001����  
	float y[MAXNUM+1];    //�洢�����ϵĵ��y���꣬���5001���� 
	float x3[MAXNUM*3];
	float y3[MAXNUM*3];
	unsigned int point_num;   //�洢�����ϵ�ʵ�ʵ� �� �ĸ���  
	float begin_k1;     //��ʼ���һ�׵�����Ϣ  
	float end_k1;     //��ֹ���һ�׵�����Ϣ  
	//float begin_k2;    //��ʼ��Ķ��׵�����Ϣ  
	//float end_k2;     //��ֹ��Ķ��׵�����Ϣ  
	//�������õ���������S(x)  
	float k1[MAXNUM+1];    //���е��һ�׵�����Ϣ  
	float k2[MAXNUM+1];    //���е�Ķ��׵�����Ϣ  
	//51����֮����50���Σ�func[]�洢ÿ�εĺ���ϵ��  
	float a3[MAXNUM],a1[MAXNUM];      
	float b3[MAXNUM],b1[MAXNUM];  
	//�ֶκ�������ʽΪ Si(x) = a3[i] * {x(i+1) - x}^3  + a1[i] * {x(i+1) - x} +  
	//        b3[i] * {x - x(i)}^3 + b1[i] * {x - x(i)}  
	//xiΪx[i]��ֵ��xi_1Ϊx[i+1]��ֵ   
	//i��ԭʼ�����±�Ҳ�ǲ�ֵ���ã�����������ԭʼ���ݣ�x���ǲ���
}SPLINE,*pSPLINE;  
typedef int RESULT;      //���غ���ִ�еĽ��״̬������Ϊ����ķ���ѡ��  
#ifndef TRUE  
#define TRUE 1  
#endif  
#ifndef FALSE  
#define FALSE -1  
#endif  
#ifndef NULL  
#define NULL 0  
#endif  
#ifndef ERR  
#define ERR  -2  
#endif 

typedef struct
{
	double darymax;
	int maxindex;
	double darymin;
	int minindex;
}ARRAYstruct;
RESULT Spline3(pSPLINE pLine) ;
extern int CubicInsertFun(double *pAfterInsert,double *pBeforeInsert,int BeforeInsertCount,int InsertCount ) ;
extern int Sin_Interpolation(double *pResult, double *origin_data, int sampleNum, int insertNum);
extern void SmoothFilter(double* p, int num, double* ptemp, int SFnum);
extern double Format2valuable(double dtemp);
extern ARRAYstruct ArrayGetMaxMinAndIndex(double *pin, int length);
#endif