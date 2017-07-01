#pragma once


// CManual 对话框

class CManual : public CDialogEx
{
	DECLARE_DYNAMIC(CManual)

public:
	CManual(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManual();

// 对话框数据
	enum { IDD = IDD_MANUAL_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString strPathName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	BOOL ShowImage(CString str);
//	afx_msg void OnPaint();
	afx_msg void OnPaint();
};
