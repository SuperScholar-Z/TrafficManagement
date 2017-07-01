// UserUpdateBox.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "UserUpdateBox.h"
#include "afxdialogex.h"


// CUserUpdateBox 对话框

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


// CUserUpdateBox 消息处理程序


void CUserUpdateBox::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strButton;
	button.GetWindowTextW(strButton);

	if (strButton == "添加")	//添加车主信息
	{
		CString userName, password;
		userNameText.GetWindowTextW(userName);
		passwordText.GetWindowTextW(password);

		if (userName == "" || password == "")
			MessageBoxW(_T("用户名和密码不能为空!"), _T("提示"));
		else if (theApp.pdatabase.Find("SELECT * FROM Tra_user", "userName", (_variant_t)userName) == -1)
		{
			theApp.pdatabase.Add("SELECT * FROM Tra_user", (_variant_t)userName, (_variant_t)password, 0);
			MessageBoxW(_T("添加成功!"), _T("提示"));
		}
		else
			MessageBoxW(_T("已存在该用户名，请重新输入!"), _T("提示"));

		OnClose();
	}
	else if (strButton == "修改")	//修改车主信息
	{
		CString userName, password;
		userNameText.GetWindowTextW(userName);
		passwordText.GetWindowTextW(password);

		if (userName == "" || password == "")
			MessageBoxW(_T("用户名和密码不能为空!"), _T("提示"));
		else if (userName == str_userName && password == str_password)
			MessageBoxW(_T("新信息不能与原信息相同，请重新输入!"), _T("提示"));
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
			MessageBoxW(_T("修改成功!"), _T("提示"));
		}
		else
			MessageBoxW(_T("该用户名已存在，请重新输入!"), _T("提示"));

		OnClose();
	}
}
