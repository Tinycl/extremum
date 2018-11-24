
// extremumDlg.h : header file
//

#pragma once
#include <vector>
using namespace std;
// CextremumDlg dialog
class CextremumDlg : public CDialog
{
// Construction
public:
	CextremumDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EXTREMUM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

public:
	CArray<double,double&> m_ary_allData;		// �洢�������ݵ�����,ʹ������� [n] ���ĳλ�õ�Ԫ��ʱ������ֵ����ʱ����
	
	CArray<double,double&> m_ary_allData_Positive;
	CArray<double,double&> m_ary_Data_Extrenum;
	CArray<int,int&> m_ary_Data_Extrenum_Index;

	vector <double>  m_dVec_Externum;
	vector <int>  m_iVec_Externum_Index;
	
	int m_iDistanceTime;//��100mm��ʱ��

    vector <double> m_dVec_alldata;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
