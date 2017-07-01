#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "UserUpdateBox.h"


// CUserTab 对话框

class CUserTab : public CDialogEx
{
	DECLARE_DYNAMIC(CUserTab)

public:
	CUserTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserTab();

// 对话框数据
	enum { IDD = IDD_USER_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox fieldText;
//	CEdit filedValue;
	CListCtrl UserList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CUserUpdateBox pUserUpdateBox;
	CEdit fieldValue;
};
