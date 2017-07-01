#pragma once
#include "afxwin.h"


// CUserUpdateBox 对话框

class CUserUpdateBox : public CDialogEx
{
	DECLARE_DYNAMIC(CUserUpdateBox)

public:
	CUserUpdateBox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserUpdateBox();

// 对话框数据
	enum { IDD = IDD_USERUPDATE_BOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString str_userName;
	CString str_password;
	CEdit userNameText;
	CEdit passwordText;
	CButton button;
	afx_msg void OnBnClickedButton1();
};
