#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "UserUpdateBox.h"


// CUserTab �Ի���

class CUserTab : public CDialogEx
{
	DECLARE_DYNAMIC(CUserTab)

public:
	CUserTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserTab();

// �Ի�������
	enum { IDD = IDD_USER_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
