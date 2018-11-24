#ifndef __CUBIC_H__
#define __CUBIC_H__

#define  MAXNUM  6000   //定义样条数据区间个数最多为5000个  
#define PI 3.1415926
typedef struct SPLINE    //定义样条结构体，用于存储一条样条的所有信息  
{ //初始化数据输入  
	float x[MAXNUM+1];    //存储样条上的点的x坐标，最多5001个点  
	float y[MAXNUM+1];    //存储样条上的点的y坐标，最多5001个点 
	float x3[MAXNUM*3];
	float y3[MAXNUM*3];
	unsigned int point_num;   //存储样条上的实际的 点 的个数  
	float begin_k1;     //开始点的一阶导数信息  
	float end_k1;     //终止点的一阶导数信息  
	//float begin_k2;    //开始点的二阶导数信息  
	//float end_k2;     //终止点的二阶导数信息  
	//计算所得的样条函数S(x)  
	float k1[MAXNUM+1];    //所有点的一阶导数信息  
	float k2[MAXNUM+1];    //所有点的二阶导数信息  
	//51个点之间有50个段，func[]存储每段的函数系数  
	float a3[MAXNUM],a1[MAXNUM];      
	float b3[MAXNUM],b1[MAXNUM];  
	//分段函数的形式为 Si(x) = a3[i] * {x(i+1) - x}^3  + a1[i] * {x(i+1) - x} +  
	//        b3[i] * {x - x(i)}^3 + b1[i] * {x - x(i)}  
	//xi为x[i]的值，xi_1为x[i+1]的值   
	//i是原始数据下标也是插值后变得，计算后面插点的原始数据，x就是插点后
}SPLINE,*pSPLINE;  
typedef int RESULT;      //返回函数执行的结果状态，下面为具体的返回选项  
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