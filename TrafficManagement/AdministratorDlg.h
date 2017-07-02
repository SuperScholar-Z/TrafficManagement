#pragma once
#include "afxcmn.h"
#include "DriverTab.h"
#include "UserTab.h"
#include "afxwin.h"
#include "UpdatePassword.h"


// CAdministratorDlg 对话框

class CAdministratorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdministratorDlg)

public:
	CAdministratorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdministratorDlg();

// 对话框数据
	enum { IDD = IDD_ADMINISTRATOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
