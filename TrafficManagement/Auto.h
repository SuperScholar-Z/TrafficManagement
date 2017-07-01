#pragma once

// CAuto 对话框

class CAuto : public CDialogEx
{
	DECLARE_DYNAMIC(CAuto)

public:
	CAuto(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAuto();

// 对话框数据
	enum { IDD = IDD_AUTO_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnPaint();
	BOOL ShowImage(CString str);
	CString strPathName;
//	COrdinaryUserDlg* pFather;
	afx_msg void OnPaint();
};
