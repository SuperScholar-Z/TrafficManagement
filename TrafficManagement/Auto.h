#pragma once

// CAuto �Ի���

class CAuto : public CDialogEx
{
	DECLARE_DYNAMIC(CAuto)

public:
	CAuto(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAuto();

// �Ի�������
	enum { IDD = IDD_AUTO_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
