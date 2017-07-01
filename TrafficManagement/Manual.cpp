// Manual.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "Manual.h"
#include "afxdialogex.h"


// CManual �Ի���

IMPLEMENT_DYNAMIC(CManual, CDialogEx)

CManual::CManual(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManual::IDD, pParent)
	, strPathName(_T(""))
{

}

CManual::~CManual()
{
}

void CManual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CManual::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CManual::OnBnClickedButton2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CManual ��Ϣ�������


void CManual::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	vector<CString>strRow;
	theApp.pdatabase.GetRow("SELECT * FROM Tra_fail", 0, strRow);
	strPathName = strRow[0];
	ShowImage(strPathName);
}


void CManual::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);

	//��info���Ƚ��ж��Ƿ��Ǻڳ�
	if (theApp.pdatabase.Find("SELECT * FROM Tra_info", "pcid", (_variant_t)str) == -1)
	{
		if (theApp.pdatabase.Find("SELECT * FROM Tra_uCar", "pcid", (_variant_t)str) == -1)
		{
			theApp.pdatabase.Add("SELECT * FROM Tra_uCar", (_variant_t)str);
			AfxMessageBox(_T("�ó��Ǻڳ����ѱ���"));
		}
		else
		{
			AfxMessageBox(_T("�ó��Ǻڳ����뿪ʼ�ж�������"));
		}
	}
	else
	{
		theApp.pdatabase.Update("SELECT * FROM Tra_info", "pcid", (_variant_t)str, "pmark", -1);
	}
}


BOOL CManual::ShowImage(CString str)
{
	CFile file;
	file.Open(str, CFile::modeRead);
	DWORD dwDataLen = file.GetLength();
	BYTE *buf = new BYTE[dwDataLen];
	memset(buf, 0x00, dwDataLen);
	file.Read(buf, dwDataLen);
	file.Close();

	CFile tempfile(_T("temp.jpg"), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&tempfile, CArchive::store);
	ar.Close();
	tempfile.Close();

	CImage image;
	COleStreamFile osf;
	osf.CreateMemoryStream(NULL);
	osf.Write((void*)buf, dwDataLen);
	osf.SeekToBegin();
	image.Load(osf.GetStream());

	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_STATIC2);
	pWnd->GetClientRect(&rect);
	CDC *pDC = pWnd->GetDC();
	image.Draw(pDC->m_hDC, rect);
	ReleaseDC(pDC);

	return TRUE;
}

void CManual::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	if (strPathName != "")
		ShowImage(strPathName);

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
