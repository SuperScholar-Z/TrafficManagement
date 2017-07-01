// Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "Dlg.h"
#include "afxdialogex.h"


// CDlg 对话框

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


// CDlg 消息处理程序


void CDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString userName2, password2;
	GetDlgItem(IDC_USERNAME2)->GetWindowText(userName2);
	GetDlgItem(IDC_PASSWORD2)->GetWindowText(password2);//获取编辑框的用户名和密码

	if ("" == userName2)
		AfxMessageBox(_T("请输入用户名！"));
	else if ("" == password2)
	{
		AfxMessageBox(_T("请输入密码！"));
	}
	else
	{

		//注意SQL语句完整性
		if (-1 == theApp.pdatabase.Find((_variant_t)"SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName2))
		{
			//AfxMessageBox(_T("用户名已存在！"));
			theApp.pdatabase.Add((_variant_t)"SELECT * FROM Tra_user", (_variant_t)userName2, (_variant_t)password2, 0);//添加普通用户记录
			MessageBox(_T("注册成功"));
			CDialogEx::OnOK();
			//this->DestroyWindow();//销毁子窗口
		}
		else
		{
			AfxMessageBox(_T("用户名已存在！请重新注册"));
		}
	}
}
