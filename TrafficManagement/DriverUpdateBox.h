#pragma once
#include "afxwin.h"


// CDriverUpdateBox 对话框

class CDriverUpdateBox : public CDialogEx
{
	DECLARE_DYNAMIC(CDriverUpdateBox)

public:
	CDriverUpdateBox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDriverUpdateBox();

// 对话框数据
	enum { IDD = IDD_DRIVERUPDATE_BOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString str_pname;
	CString str_pid;
	CString str_pcid;
	int check_pmark;
	CEdit pnameText;
	CEdit pidText;
	CEdit pcidText;
	CButton pmarkCheck;
	CButton button;
	afx_msg void OnBnClickedButton1();
};
