// AdministratorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "TrafficManagementDlg.h"
#include "AdministratorDlg.h"
#include "afxdialogex.h"


// CAdministratorDlg 对话框

IMPLEMENT_DYNAMIC(CAdministratorDlg, CDialogEx)

CAdministratorDlg::CAdministratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdministratorDlg::IDD, pParent)
	, aUserName(_T(""))
{

}

CAdministratorDlg::~CAdministratorDlg()
{
}

void CAdministratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, AdministratorTab);
}


BEGIN_MESSAGE_MAP(CAdministratorDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CAdministratorDlg::OnTcnSelchangeTab1)
	ON_WM_SYSKEYDOWN()
	ON_WM_CLOSE()
//	ON_WM_CTLCOLOR()
ON_COMMAND(ID_32771, &CAdministratorDlg::OnAUpdatePassword)
ON_COMMAND(ID_32772, &CAdministratorDlg::On32772)
END_MESSAGE_MAP()


// CAdministratorDlg 消息处理程序


BOOL CAdministratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//加载显示用户名的菜单
	m_aMenu.LoadMenuW(IDR_MENU);
	SetMenu(&m_aMenu);
	m_aMenu.ModifyMenu(0, MF_BYPOSITION, -1, aUserName);

	//初始化Tab栏
	AdministratorTab.InsertItem(0, _T("管理车主"));
	AdministratorTab.InsertItem(1, _T("管理用户"));

	pDriverTab.Create(IDD_DRIVER_TAB, GetDlgItem(IDC_TAB1));
	pUserTab.Create(IDD_USER_TAB, GetDlgItem(IDC_TAB1));

	CRect rect;
	AdministratorTab.GetClientRect(&rect);
	rect.left += 1;
	rect.top += 22;
	rect.right -= 2;
	rect.bottom -= 1;
	pDriverTab.MoveWindow(&rect);
	pUserTab.MoveWindow(&rect);

	pDriverTab.ShowWindow(true);
	pUserTab.ShowWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAdministratorDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	int CurSel = AdministratorTab.GetCurSel();
	switch (CurSel)
	{
	case 0:
		pDriverTab.ShowWindow(true);
		pUserTab.ShowWindow(false);
		break;
	case 1:
		pDriverTab.ShowWindow(false);
		pUserTab.ShowWindow(true);
		break;
	}

	*pResult = 0;
}


void CAdministratorDlg::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnSysKeyDown(nChar, nRepCnt, nFlags);
}


void CAdministratorDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CTrafficManagementDlg *parent = (CTrafficManagementDlg*)GetParent();
	parent->DestroyWindow();

	CDialogEx::OnClose();
}

void CAdministratorDlg::OnAUpdatePassword()
{
	// TODO:  在此添加命令处理程序代码
	uPsd2.userName = aUserName;
	if (uPsd2.m_hWnd == NULL)
		uPsd2.Create(IDD_UPDATEPASSWORDDLG);
	uPsd2.ShowWindow(TRUE);
}


void CAdministratorDlg::On32772()
{
	// TODO:  在此添加命令处理程序代码
	CTrafficManagementDlg *parent = (CTrafficManagementDlg*)GetParent();
	parent->ShowWindow(TRUE);
	parent->SetDlgItemTextW(IDC_USERNAME, _T(""));
	parent->SetDlgItemTextW(IDC_PASSWORD, _T(""));

	m_aMenu.DestroyMenu();//销毁菜单

	this->DestroyWindow();
}
