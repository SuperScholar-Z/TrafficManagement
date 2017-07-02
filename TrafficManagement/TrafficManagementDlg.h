
// TrafficManagementDlg.h : 头文件
//

#pragma once
#include "AdministratorDlg.h"
#include "afxcmn.h"
#include "Dlg.h"
#include "OrdinaryUserDlg.h"


// CTrafficManagementDlg 对话框
class CTrafficManagementDlg : public CDialogEx
{
// 构造
public:
	CTrafficManagementDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TRAFFICMANAGEMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
