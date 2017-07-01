// AdministratorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "TrafficManagementDlg.h"
#include "AdministratorDlg.h"
#include "afxdialogex.h"


// CAdministratorDlg �Ի���

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


// CAdministratorDlg ��Ϣ�������


BOOL CAdministratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	AdministratorTab.InsertItem(0, _T("������"));
	AdministratorTab.InsertItem(1, _T("�����û�"));

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
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAdministratorDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnSysKeyDown(nChar, nRepCnt, nFlags);
}


void CAdministratorDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTrafficManagementDlg *parent = (CTrafficManagementDlg*)GetParent();
	parent->DestroyWindow();

	CDialogEx::OnClose();
}
