#pragma once


// CUpdatePassword �Ի���

class CUpdatePassword : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdatePassword)

public:
	CUpdatePassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdatePassword();

// �Ի�������
	enum { IDD = IDD_UPDATEPASSWORDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString userName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
