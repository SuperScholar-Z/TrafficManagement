#pragma once


// CManual �Ի���

class CManual : public CDialogEx
{
	DECLARE_DYNAMIC(CManual)

public:
	CManual(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManual();

// �Ի�������
	enum { IDD = IDD_MANUAL_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString strPathName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	BOOL ShowImage(CString str);
//	afx_msg void OnPaint();
	afx_msg void OnPaint();
};
