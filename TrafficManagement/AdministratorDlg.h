#pragma once
#include "afxcmn.h"
#include "DriverTab.h"
#include "UserTab.h"
#include "afxwin.h"
#include "UpdatePassword.h"


// CAdministratorDlg �Ի���

class CAdministratorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdministratorDlg)

public:
	CAdministratorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdministratorDlg();

// �Ի�������
	enum { IDD = IDD_ADMINISTRATOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl AdministratorTab;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CDriverTab pDriverTab;
	CUserTab pUserTab;
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CMenu m_aMenu;
	CString aUserName;
	afx_msg void OnAUpdatePassword();
	afx_msg void On32772();
	CUpdatePassword uPsd2;
};
