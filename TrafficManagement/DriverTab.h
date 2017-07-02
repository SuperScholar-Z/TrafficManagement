#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DriverUpdateBox.h"


// CDriverTab 对话框

class CDriverTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDriverTab)

public:
	CDriverTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDriverTab();

// 对话框数据
	enum { IDD = IDD_DRIVER_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox fieldText;
	CEdit fieldValue;
	CListCtrl DriverList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CDriverUpdateBox pDriverUpdateBox;
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCombo1();
};
