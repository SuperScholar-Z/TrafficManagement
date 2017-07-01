// Auto.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "OrdinaryUserDlg.h"
#include "Auto.h"
#include "afxdialogex.h"


// CAuto �Ի���

IMPLEMENT_DYNAMIC(CAuto, CDialogEx)

CAuto::CAuto(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuto::IDD, pParent)
	, strPathName(_T(""))
{

}

CAuto::~CAuto()
{
}

void CAuto::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAuto, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAuto::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAuto::OnBnClickedButton2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAuto ��Ϣ�������


void CAuto::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, (CString)"jpg", (CString)"*.jpg", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)"JPEG�ļ�(*.jpg)|*.jpg|GIF�ļ�(*.gif)|*.gif|bmp�ļ�(*.bmp)|*.bmp|", NULL);
	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		ShowImage(strPathName);
	}
	//ʶ���㷨
	//��strPathName��ͼƬ��ַ
	//ʶ��ɹ�ʱ������һ���ַ����������ݿ�
	CString str = (CString)"��A12345";
	theApp.pdatabase.Add("SELECT * FROM Tra_info", "����", "123456", (_variant_t)str, 0);
	//ʶ��ʧ��ʱ������ʧ�ܵ�ͼƬ·��
	theApp.pdatabase.Add("SELECT * FROM Tra_fail",(_variant_t)strPathName);
	//������ʾ��
	INT_PTR nRes;
	nRes = MessageBox(_T("ʶ��ʧ�ܣ���ת�˹�ʶ��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION);
	if (IDCANCEL == nRes)
	{
		return;
	}
	//ת��tab��
	COrdinaryUserDlg *parent = (COrdinaryUserDlg*)GetParent()->GetParent();
	parent->m_auto.ShowWindow(false);
	parent->m_tab.SetCurSel(1);
	parent->m_manual.strPathName = strPathName;
	parent->m_manual.ShowWindow(true);
}


void CAuto::OnBnClickedButton2()
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

BOOL CAuto::ShowImage(CString str)
{
	CFile file;
	file.Open(str, CFile::modeRead);
	DWORD dwDataLen = (DWORD)file.GetLength();
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
	CWnd *pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetClientRect(&rect);
	CDC *pDC = pWnd->GetDC();
	image.Draw(pDC->m_hDC, rect);
	ReleaseDC(pDC);

	return TRUE;
}

void CAuto::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	if (strPathName != "")
		ShowImage(strPathName);

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
