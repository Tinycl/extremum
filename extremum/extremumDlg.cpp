
// extremumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "extremum.h"
#include "extremumDlg.h"
#include "WriteReadTxt.h"
#include "emd.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CextremumDlg dialog




CextremumDlg::CextremumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CextremumDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CextremumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CextremumDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CextremumDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CextremumDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CextremumDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CextremumDlg message handlers

BOOL CextremumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	AfxOleInit();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CextremumDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CextremumDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CextremumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CextremumDlg::OnBnClickedButton1()
{
		
	ReadFromTxt(m_ary_allData);
	
	// TODO: Add your control notification handler code here
}

void CextremumDlg::OnBnClickedButton2()
{
	double dFistResponseWaveMax=-10000,dFirstResponseWaveMin=10000,
		   dSecondResponseWaveMax=0,dSecondResponseWaveMin=0;
	int dFistResponseWaveMax_Index=0,dFirstResponseWaveMin_Index=0,
		dSecondResponseWaveMax_Index=0,dSecondResponseWaveMin_Index=0;
	//求首次回波的最值
   for(int kk = 0;kk < m_ary_allData.GetSize();kk++ )
   {
	   
	   if (m_ary_allData[kk] > dFistResponseWaveMax)
	   {
		   dFistResponseWaveMax = m_ary_allData[kk];
		   dFistResponseWaveMax_Index = kk;
	   }
	  
	   if (m_ary_allData[kk] < dFirstResponseWaveMin)
	   {
		   dFirstResponseWaveMin = m_ary_allData[kk];
		   dFirstResponseWaveMin_Index = kk;
	   }
	}
   //周期NS
   double d_Tperiod = abs(dFistResponseWaveMax_Index - dFirstResponseWaveMin_Index)*1000/200;
   //给正数组
    for (int kk = 0;kk < m_ary_allData.GetSize();kk++)
    {
		m_ary_allData_Positive.Add(m_ary_allData[kk]);
    }
    for(int kk = 0;kk < m_ary_allData_Positive.GetSize();kk++ )
	{
	
		if (m_ary_allData_Positive[kk] < 0.0)
		{
			m_ary_allData_Positive[kk] = 0.0-m_ary_allData_Positive[kk];
		}
	}
   //判断极值点
	for(int kk = 3;kk < m_ary_allData_Positive.GetSize()-3;kk++ )
	{   
	   
	   if ((m_ary_allData_Positive[kk-3] < m_ary_allData_Positive[kk])&&(m_ary_allData_Positive[kk-2] < m_ary_allData_Positive[kk]) && (m_ary_allData_Positive[kk-1] < m_ary_allData_Positive[kk])
		   && (m_ary_allData_Positive[kk] > m_ary_allData_Positive[kk+1]) && (m_ary_allData_Positive[kk] > m_ary_allData_Positive[kk+2])&& (m_ary_allData_Positive[kk] > m_ary_allData_Positive[kk+3])
		  )
	   {
		  //方便存TXT
		   m_dVec_Externum.push_back(m_ary_allData_Positive[kk]);
		   m_iVec_Externum_Index.push_back(kk);
		   //存极值数组
		   m_ary_Data_Extrenum.Add(m_ary_allData_Positive[kk]);
		   m_ary_Data_Extrenum_Index.Add(kk);


	   }
    }
	//找极值最大值点和下标
    double dExtrenumMax = -10000.0;
	int iExtrenumIndex = 0;
	for (int kk = 0;kk < m_ary_Data_Extrenum.GetSize();kk++)
	{
		if (m_ary_Data_Extrenum[kk] > dExtrenumMax)
		{
			dExtrenumMax = m_ary_Data_Extrenum[kk];
			iExtrenumIndex = m_ary_Data_Extrenum_Index[kk];

		}

	}
	//找极值点的平滑区
	//找极值点首次过目标线
	double dExtrenumError = dExtrenumMax/15.0;
	int iRightIndex = 0;
	int iBigErrorIndex1 = 0,iSmallErrorIndex1 = 0;
	double dBigNum1 = 0.0,dSmallNum1 = 0.0;
	for (int kk = dExtrenumMax; kk < m_ary_Data_Extrenum.GetSize();kk++ )
	{
		if (m_ary_Data_Extrenum[kk] >= dExtrenumError && m_ary_Data_Extrenum[kk+1] <= dExtrenumError)
		{
			iBigErrorIndex1 = m_ary_Data_Extrenum_Index[kk];
			iSmallErrorIndex1 = m_ary_Data_Extrenum_Index[kk+1];
			dBigNum1 = m_ary_Data_Extrenum[kk];
			dSmallNum1 = m_ary_Data_Extrenum[kk+1] ;
			break;
		}
	}
	//在首次过目标线的点往后扫苗 8个周期，是否有大于此值的点（正）,第二次
	int iBigErrorIndex2 = 0,iSmallErrorIndex2 = 0;
	double dBigNum2 = 0.0,dSmallNum2 = 0.0;
   for (int kk = iBigErrorIndex1 + 1; kk < dBigNum1 + 9; kk++)
   {
		if (m_ary_Data_Extrenum[kk] >= dBigNum1)
		{
			dBigNum2 = m_ary_Data_Extrenum[kk];
			iBigErrorIndex2 = m_ary_Data_Extrenum_Index[kk];
			break;
		}
		else iRightIndex = iBigErrorIndex1;
   }
   //如果第二次,找到则继续向后扫描过目标线的点
   int iBigErrorIndex3 = 0,iSmallErrorIndex3 = 0;
   double dBigNum3 = 0.0,dSmallNum3 = 0.0;
   if (iBigErrorIndex2 != 0)
   {
	   for (int kk = iBigErrorIndex2; kk < iBigErrorIndex2 + 8;kk++ )
	   {
		   if (m_ary_Data_Extrenum[kk] >= dExtrenumError && m_ary_Data_Extrenum[kk+1] <= dExtrenumError)
		   {
			   iBigErrorIndex3 = m_ary_Data_Extrenum_Index[kk];
			   iSmallErrorIndex3 = m_ary_Data_Extrenum_Index[kk+1];
			   dBigNum3 = m_ary_Data_Extrenum[kk];
			   dSmallNum3 = m_ary_Data_Extrenum[kk+1] ;
			   break;
		   }
		   else iRightIndex = iBigErrorIndex2;
	   }
   }
//如果第三次找到，再往后找
   int iBigErrorIndex4 = 0,iSmallErrorIndex4 = 0;
   double dBigNum4 = 0.0,dSmallNum4 = 0.0;
   if (iBigErrorIndex3 != 0)
   {
	   for (int kk = iBigErrorIndex3+1; kk < iBigErrorIndex3 + 9;kk++ )
	   {
		   if (m_ary_Data_Extrenum[kk] >= dExtrenumError && m_ary_Data_Extrenum[kk+1] <= dExtrenumError)
		   {
			   iBigErrorIndex4 = m_ary_Data_Extrenum_Index[kk];
			   iSmallErrorIndex4 = m_ary_Data_Extrenum_Index[kk+1];
			   dBigNum4 = m_ary_Data_Extrenum[kk];
			   dSmallNum4 = m_ary_Data_Extrenum[kk+1] ;
			   break;
		   }
		   else iRightIndex = iBigErrorIndex3;
	   }
   }
   /**********************保存所截得数据**********************************/
	WriteToTxt(_T("包络线"),&m_ary_Data_Extrenum[0],m_ary_Data_Extrenum.GetSize());
	/*****************************保存文件******************************/
   

}

void CextremumDlg::OnBnClickedButton3()
{
	emd(&m_ary_allData[0],m_ary_allData.GetSize());
	// TODO: Add your control notification handler code here
}
