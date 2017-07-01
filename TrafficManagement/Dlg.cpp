// Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "Dlg.h"
#include "afxdialogex.h"


// CDlg �Ի���

IMPLEMENT_DYNAMIC(CDlg, CDialogEx)

CDlg::CDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg::IDD, pParent)
{

}

CDlg::~CDlg()
{
}

void CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg ��Ϣ�������


void CDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString userName2, password2;
	GetDlgItem(IDC_USERNAME2)->GetWindowText(userName2);
	GetDlgItem(IDC_PASSWORD2)->GetWindowText(password2);//��ȡ�༭����û���������

	if ("" == userName2)
		AfxMessageBox(_T("�������û�����"));
	else if ("" == password2)
	{
		AfxMessageBox(_T("���������룡"));
	}
	else
	{

		//ע��SQL���������
		if (-1 == theApp.pdatabase.Find((_variant_t)"SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName2))
		{
			//AfxMessageBox(_T("�û����Ѵ��ڣ�"));
			theApp.pdatabase.Add((_variant_t)"SELECT * FROM Tra_user", (_variant_t)userName2, (_variant_t)password2, 0);//�����ͨ�û���¼
			MessageBox(_T("ע��ɹ�"));
			CDialogEx::OnOK();
			//this->DestroyWindow();//�����Ӵ���
		}
		else
		{
			AfxMessageBox(_T("�û����Ѵ��ڣ�������ע��"));
		}
	}
}
