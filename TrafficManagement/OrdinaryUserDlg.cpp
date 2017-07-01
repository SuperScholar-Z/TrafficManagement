// OrdinaryUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "TrafficManagementDlg.h"
#include "OrdinaryUserDlg.h"
#include "afxdialogex.h"


// COrdinaryUserDlg �Ի���

IMPLEMENT_DYNAMIC(COrdinaryUserDlg, CDialogEx)

COrdinaryUserDlg::COrdinaryUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COrdinaryUserDlg::IDD, pParent)
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
END_MESSAGE_MAP()

BOOL COrdinaryUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect tabRect;
	m_tab.InsertItem(0, _T("�Զ�ʶ��"));
	m_tab.InsertItem(1, _T("�˹�ʶ��"));
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
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// COrdinaryUserDlg ��Ϣ�������

void COrdinaryUserDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTrafficManagementDlg *parent = (CTrafficManagementDlg*)GetParent();
	parent->DestroyWindow();

	CDialogEx::OnClose();
}
