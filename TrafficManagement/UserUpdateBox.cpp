// UserUpdateBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "UserUpdateBox.h"
#include "afxdialogex.h"


// CUserUpdateBox �Ի���

IMPLEMENT_DYNAMIC(CUserUpdateBox, CDialogEx)

CUserUpdateBox::CUserUpdateBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserUpdateBox::IDD, pParent)
	, str_userName(_T(""))
	, str_password(_T(""))
{

}

CUserUpdateBox::~CUserUpdateBox()
{
}

void CUserUpdateBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, userNameText);
	DDX_Control(pDX, IDC_EDIT2, passwordText);
	DDX_Control(pDX, IDC_BUTTON1, button);
}


BEGIN_MESSAGE_MAP(CUserUpdateBox, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserUpdateBox::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUserUpdateBox ��Ϣ�������


void CUserUpdateBox::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strButton;
	button.GetWindowTextW(strButton);

	if (strButton == "���")	//��ӳ�����Ϣ
	{
		CString userName, password;
		userNameText.GetWindowTextW(userName);
		passwordText.GetWindowTextW(password);

		if (userName == "" || password == "")
			MessageBoxW(_T("�û��������벻��Ϊ��!"), _T("��ʾ"));
		else if (theApp.pdatabase.Find("SELECT * FROM Tra_user", "userName", (_variant_t)userName) == -1)
		{
			theApp.pdatabase.Add("SELECT * FROM Tra_user", (_variant_t)userName, (_variant_t)password, 0);
			MessageBoxW(_T("��ӳɹ�!"), _T("��ʾ"));
		}
		else
			MessageBoxW(_T("�Ѵ��ڸ��û���������������!"), _T("��ʾ"));

		OnClose();
	}
	else if (strButton == "�޸�")	//�޸ĳ�����Ϣ
	{
		CString userName, password;
		userNameText.GetWindowTextW(userName);
		passwordText.GetWindowTextW(password);

		if (userName == "" || password == "")
			MessageBoxW(_T("�û��������벻��Ϊ��!"), _T("��ʾ"));
		else if (userName == str_userName && password == str_password)
			MessageBoxW(_T("����Ϣ������ԭ��Ϣ��ͬ������������!"), _T("��ʾ"));
		else if (userName == str_userName || theApp.pdatabase.Find("SELECT * FROM Tra_user", "userName", (_variant_t)userName) == -1)
		{
			if (userName != str_userName)
			{
				theApp.pdatabase.Update("SELECT * FROM Tra_user", "userName", (_variant_t)str_userName, "userName", (_variant_t)userName);
				str_userName = userName;
			}
			if (password != str_password)
			{
				theApp.pdatabase.Update("SELECT * FROM Tra_user", "userName", (_variant_t)str_userName, "password", (_variant_t)password);
				str_password = password;
			}
			MessageBoxW(_T("�޸ĳɹ�!"), _T("��ʾ"));
		}
		else
			MessageBoxW(_T("���û����Ѵ��ڣ�����������!"), _T("��ʾ"));

		OnClose();
	}
}
