// UpdatePassword.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "UpdatePassword.h"
#include "afxdialogex.h"


// CUpdatePassword 对话框

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


// CUpdatePassword 消息处理程序


BOOL CUpdatePassword::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CUpdatePassword::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString oldPassword, newPassword1, newPassword2;
	vector<CString> v;
	GetDlgItemText(IDC_OLD, oldPassword);
	GetDlgItemText(IDC_NEW1, newPassword1);
	GetDlgItemText(IDC_NEW2, newPassword2);//分别获取原密码、新密码、确认新密码对应的编辑框的内容

	if ("" == oldPassword)
		AfxMessageBox(_T("请输入原密码！"));
	else if ("" == newPassword1)
		AfxMessageBox(_T("请输入新密码！"));
	else if ("" == newPassword2)
		AfxMessageBox(_T("请再次输入新密码！"));
	else
	{
		if (newPassword2 != newPassword1)
			AfxMessageBox(_T("第二次输入的新密码和第一次输入的新密码不一致！请重新输入"));
		else
		{
			theApp.pdatabase.GetRow((_variant_t)"SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName, v);//获取用户名对应的记录
			if (oldPassword != v[1])
				AfxMessageBox(_T("原密码错误！请重新输入原密码"));
			else
			{
				theApp.pdatabase.Update((_variant_t)"SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName, (_variant_t)"passWord", (_variant_t)newPassword1);
				MessageBox(_T("修改密码成功"));
				//CDialogEx::OnOK();
				this->DestroyWindow();//销毁修改密码窗口
			}
		}
	}
}


void CUpdatePassword::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
