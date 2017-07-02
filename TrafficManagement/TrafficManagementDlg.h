
// TrafficManagementDlg.h : ͷ�ļ�
//

#pragma once
#include "AdministratorDlg.h"
#include "afxcmn.h"
#include "Dlg.h"
#include "OrdinaryUserDlg.h"


// CTrafficManagementDlg �Ի���
class CTrafficManagementDlg : public CDialogEx
{
// ����
public:
	CTrafficManagementDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRAFFICMANAGEMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButton1();
	CAdministratorDlg pAdministratorDlg;
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSignin();
	afx_msg void OnBnClickedSignup();
	CDlg dlg1;
	COrdinaryUserDlg pOrdinaryUserDlg;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
