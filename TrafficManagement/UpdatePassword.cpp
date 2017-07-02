// UpdatePassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "UpdatePassword.h"
#include "afxdialogex.h"


// CUpdatePassword �Ի���

IMPLEMENT_DYNAMIC(CUpdatePassword, CDialogEx)

CUpdatePassword::CUpdatePassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdatePassword::IDD, pParent)
	, userName(_T(""))
{

}

CUpdatePassword::~CUpdatePassword()
{
}

void CUpdatePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUpdatePassword, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdatePassword::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUpdatePassword::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUpdatePassword ��Ϣ�������


BOOL CUpdatePassword::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUpdatePassword::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString oldPassword, newPassword1, newPassword2;
	vector<CString> v;
	GetDlgItemText(IDC_OLD, oldPassword);
	GetDlgItemText(IDC_NEW1, newPassword1);
	GetDlgItemText(IDC_NEW2, newPassword2);//�ֱ��ȡԭ���롢�����롢ȷ���������Ӧ�ı༭�������

	if ("" == oldPassword)
		AfxMessageBox(_T("������ԭ���룡"));
	else if ("" == newPassword1)
		AfxMessageBox(_T("�����������룡"));
	else if ("" == newPassword2)
		AfxMessageBox(_T("���ٴ����������룡"));
	else
	{
		if (newPassword2 != newPassword1)
			AfxMessageBox(_T("�ڶ��������������͵�һ������������벻һ�£�����������"));
		else
		{
			theApp.pdatabase.GetRow((_variant_t)"SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName, v);//��ȡ�û�����Ӧ�ļ�¼
			if (oldPassword != v[1])
				AfxMessageBox(_T("ԭ�����������������ԭ����"));
			else
			{
				theApp.pdatabase.Update((_variant_t)"SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName, (_variant_t)"passWord", (_variant_t)newPassword1);
				MessageBox(_T("�޸�����ɹ�"));
				//CDialogEx::OnOK();
				this->DestroyWindow();//�����޸����봰��
			}
		}
	}
}


void CUpdatePassword::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
