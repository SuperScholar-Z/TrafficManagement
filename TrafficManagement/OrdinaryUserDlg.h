#pragma once
#include "Auto.h"
#include "Manual.h"
#include "afxcmn.h"


// COrdinaryUserDlg 对话框

class COrdinaryUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COrdinaryUserDlg)

public:
	COrdinaryUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COrdinaryUserDlg();

// 对话框数据
	enum { IDD = IDD_ORDINARYUSER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CAuto m_auto;
	CManual m_manual;
	CTabCtrl m_tab;
	afx_msg void OnClose();
};
