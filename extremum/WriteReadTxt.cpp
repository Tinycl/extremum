#include "WriteReadTxt.h"
#include "stdafx.h"
#include <stdio.h>
#include <vector>
using namespace std;
CString GetPath_sln(void)
{
	CString strPath;   
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);   
	strPath.ReleaseBuffer();   
	int nPos;   
	nPos = strPath.ReverseFind('\\');   
	strPath = strPath.Left(nPos); 

	nPos = strPath.ReverseFind('\\');   
	strPath = strPath.Left(nPos+1); 

	return strPath;  
}
CString GetCurrentData()
{
	CTime time = CTime::GetCurrentTime();
	CString strDate = time.Format("%Y%m%d %X");
	strDate.Delete(11);
	strDate.Delete(13);
	return strDate;
}
void WriteToTxt(CString filename, double* pInputnum,int numLength )
{
	/*******************ע����������÷�****************/
	double *ptemp = new double[numLength];
	for (int kk = 0; kk < numLength ; kk++)
	{
		ptemp[kk] = 0.0;
		ptemp[kk] = pInputnum[kk];
	}
	/*vector<double> dVectemp;
	dVectemp.clear();*/
	/*for (int kk = 0; kk < numLength ; kk++)
	{
		dVectemp.push_back(pInputnum[kk]);
	}*/
	FILE* fileHandle;
	CString strDate = GetCurrentData();
	CString strTXTFileName;
	CString strFolderName = GetPath_sln();
	strTXTFileName = filename + strDate + _T(".txt");
	CString m_strTxtFileName2Write =  strFolderName + strTXTFileName;
	USES_CONVERSION;
	fileHandle = fopen(T2A(m_strTxtFileName2Write), T2A(_T("wt")));		// �洢·��   ������ 
	if (fileHandle)
	{
		for (int kk = 0; kk < numLength; kk ++)
		{
			fprintf(fileHandle, "%.5f\n", ptemp[kk]);
		}
		/*for (int m = 0; m < dVectemp.size() ; m++)
		{
			fprintf(fileHandle, "%.5f\n", dVectemp.at(m));
		}  */
		fclose(fileHandle);
	}
	/***********************����ɾ��**************/
	delete[] ptemp;
}

void ReadFromTxt(CArray<double,double&> &arydtemp)
{
	CFileDialog fileDlg(TRUE, _T("TXT"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("*|*.txt", this));
	fileDlg.m_ofn.lpstrTitle = _T("�����ļ�ѡ��Ի���");;
	fileDlg.m_ofn.lpstrFilter = _T("BMP Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0");
	fileDlg.m_ofn.lpstrDefExt = _T("txt");
	arydtemp.RemoveAll();
	if (IDOK == fileDlg.DoModal())
	{
		CString strFilePath;
		CString strFileName;
		strFileName = fileDlg.GetFileName();
		strFilePath = fileDlg.GetPathName();	// �õ�ȫ·��


		{
			CStdioFile stdFile;
			CFileException fileException;
			CString strFileName = strFilePath;
			if (!stdFile.Open(strFileName, CFile::modeRead | CFile::typeText, &fileException))  // CFile::modeRead ֻ����ʽ��  // CFile::typeText ���óɶԻس����ж������⴦����ı�ģʽ���������������У�
			{
				TRACE( _T("�޷����ļ��� %s, ����ԭ�� = %u\n"), strFileName, fileException.m_cause );    // �ú�����ڳ����DEBUG�汾�г��֣���RELEASE��ʱ��ú����ȫ��ʧ;TRACE��Ϣ�����VC IDE�������������
			}

			CString strContent;
			LONG  iLinecount = 0;						// ������
			while (stdFile.ReadString(strContent))      // һ��һ�еĶ����ַ���
			{
				CString strGet;
				iLinecount++;
				strContent.Delete(strContent.GetLength()-1);   //ɾȥ �ַ���β���� ���з�



				double aaa = _tstof(strContent);										
				arydtemp.Add(aaa);


			}// end of while
			stdFile.Close();
		} // end of ��ȡTXT�ļ�
	}
}


