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
END_MESSAGE_MAP()


// CAdministratorDlg 消息处理程序


BOOL CAdministratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	AdministratorTab.InsertItem(0, _T("管理车主"));
	AdministratorTab.InsertItem(1, _T("管理用户"));

	pDriverTab.Create(IDD_DRIVER_TAB, GetDlgItem(IDC_TAB1));
	pUserTab.Create(IDD_USER_TAB, GetDlgItem(IDC_TAB1));

	CRect rect;
	AdministratorTab.GetClientRect(&rect);
	rect.top += 22;
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
