#pragma once
#include "afxwin.h"


// CUserUpdateBox �Ի���

class CUserUpdateBox : public CDialogEx
{
	DECLARE_DYNAMIC(CUserUpdateBox)

public:
	CUserUpdateBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserUpdateBox();

// �Ի�������
	enum { IDD = IDD_USERUPDATE_BOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString str_userName;
	CString str_password;
	CEdit userNameText;
	CEdit passwordText;
	CButton button;
	afx_msg void OnBnClickedButton1();
};
