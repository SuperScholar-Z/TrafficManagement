#pragma once


// CUpdatePassword 对话框

class CUpdatePassword : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdatePassword)

public:
	CUpdatePassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdatePassword();

// 对话框数据
	enum { IDD = IDD_UPDATEPASSWORDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString userName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
