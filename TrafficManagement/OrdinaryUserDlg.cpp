// OrdinaryUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "TrafficManagementDlg.h"
#include "OrdinaryUserDlg.h"
#include "afxdialogex.h"


// COrdinaryUserDlg 对话框

IMPLEMENT_DYNAMIC(COrdinaryUserDlg, CDialogEx)

COrdinaryUserDlg::COrdinaryUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COrdinaryUserDlg::IDD, pParent)
	, oUserName(_T(""))
{

}

COrdinaryUserDlg::~COrdinaryUserDlg()
{
}

void COrdinaryUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(COrdinaryUserDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &COrdinaryUserDlg::OnTcnSelchangeTab1)
	ON_WM_CLOSE()
	ON_COMMAND(ID_32771, &COrdinaryUserDlg::OnOUpdatePassword)
	ON_COMMAND(ID_32772, &COrdinaryUserDlg::OnOSignOut)
END_MESSAGE_MAP()

BOOL COrdinaryUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//加载显示用户名的菜单
	m_oMenu.LoadMenuW(IDR_MENU);
	SetMenu(&m_oMenu);
	m_oMenu.ModifyMenu(0, MF_BYPOSITION, -1, oUserName);

	//初始化Tab栏
	CRect tabRect;
	m_tab.InsertItem(0, _T("自动识别"));
	m_tab.InsertItem(1, _T("人工识别"));
	m_auto.Create(IDD_AUTO_TAB, GetDlgItem(IDC_TAB1));
	m_manual.Create(IDD_MANUAL_TAB, GetDlgItem(IDC_TAB1));
	m_tab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 22;
	tabRect.bottom -= 1;
	m_auto.MoveWindow(&tabRect);
	m_manual .MoveWindow(&tabRect);

	m_auto.ShowWindow(true);
	m_manual.ShowWindow(false);

	//m_auto.changeToManual = &m_manual;
	//m_auto.toAuto = &m_auto;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

// COrdinaryUserDlg 消息处理程序

void COrdinaryUserDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	switch (m_tab.GetCurSel())
	{
	case 0:
		m_auto.ShowWindow(true);
		m_manual.ShowWindow(false);
		break;
	case 1:
		m_auto.ShowWindow(false);
		m_manual.ShowWindow(true);
		break;
	default:
		break;
	}

	*pResult = 0;
}


void COrdinaryUserDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CTrafficManagementDlg *parent = (CTrafficManagementDlg*)GetParent();
	parent->DestroyWindow();

	CDialogEx::OnClose();
}


void COrdinaryUserDlg::OnOUpdatePassword()
{
	// TODO:  在此添加命令处理程序代码
	uPsd1.userName = oUserName;
	if (uPsd1.m_hWnd == NULL)
		uPsd1.Create(IDD_UPDATEPASSWORDDLG);
	uPsd1.ShowWindow(TRUE);
}


void COrdinaryUserDlg::OnOSignOut()
{
	// TODO:  在此添加命令处理程序代码
	CTrafficManagementDlg *parent = (CTrafficManagementDlg*)GetParent();
	parent->ShowWindow(TRUE);
	parent->SetDlgItemTextW(IDC_USERNAME, _T(""));
	parent->SetDlgItemTextW(IDC_PASSWORD, _T(""));

	m_oMenu.DestroyMenu();//销毁菜单

	this->DestroyWindow();
}
