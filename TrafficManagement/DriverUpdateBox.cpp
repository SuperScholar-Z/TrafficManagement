// DriverUpdateBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "DriverUpdateBox.h"
#include "afxdialogex.h"


// CDriverUpdateBox �Ի���

IMPLEMENT_DYNAMIC(CDriverUpdateBox, CDialogEx)

CDriverUpdateBox::CDriverUpdateBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDriverUpdateBox::IDD, pParent)
	, str_pname(_T(""))
	, str_pid(_T(""))
	, str_pcid(_T(""))
	, check_pmark(0)
{

}

CDriverUpdateBox::~CDriverUpdateBox()
{
}

void CDriverUpdateBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, pnameText);
	DDX_Control(pDX, IDC_EDIT2, pidText);
	DDX_Control(pDX, IDC_EDIT3, pcidText);
	DDX_Control(pDX, IDC_CHECK1, pmarkCheck);
	DDX_Control(pDX, IDC_BUTTON1, button);
}


BEGIN_MESSAGE_MAP(CDriverUpdateBox, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDriverUpdateBox::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDriverUpdateBox ��Ϣ�������


BOOL CDriverUpdateBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDriverUpdateBox::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strButton;
	button.GetWindowTextW(strButton);

	if (strButton == "���")	//��ӳ�����Ϣ
	{
		//ʹ����ʱ������¼�༭����Ϣ
		CString pname, pid, pcid;
		pnameText.GetWindowTextW(pname);
		pidText.GetWindowTextW(pid);
		pcidText.GetWindowTextW(pcid);
		int pmark = pmarkCheck.GetCheck();

		if (pname == "" || pid == "" || pcid == "")
			MessageBoxW(_T("��Ϣ����Ϊ�գ�������������Ϣ!"), _T("��ʾ"));
		else if (theApp.pdatabase.Find("SELECT * FROM Tra_info", "pid", (_variant_t)pid) == -1)
		{
			theApp.pdatabase.Add("SELECT * FROM Tra_info", (_variant_t)pname, (_variant_t)pid, (_variant_t)pcid, (_variant_t)pmark);
			if (MessageBoxW(_T("��ӳɹ�!"), _T("��ʾ")) == IDOK)
				this->DestroyWindow();
		}
		else
			MessageBoxW(_T("�Ѵ��ڸü�¼�������º˶���Ϣ!"), _T("��ʾ"));
	}
	else if (strButton == "�޸�")	//�޸ĳ�����Ϣ
	{
		//ʹ����ʱ������¼�༭����Ϣ
		CString pname, pid, pcid;
		pnameText.GetWindowTextW(pname);
		pidText.GetWindowTextW(pid);
		pcidText.GetWindowTextW(pcid);
		int pmark = pmarkCheck.GetCheck();

		if (pname == "" || pid == "" || pcid == "")
			MessageBoxW(_T("��Ϣ����Ϊ�գ�������������Ϣ!"), _T("��ʾ"));
		else if (pname == str_pname && pid == str_pid && pcid == str_pcid && pmark == check_pmark)
			MessageBoxW(_T("����Ϣ������ԭ��Ϣ��ͬ������������!"), _T("��ʾ"));
		else if (pid == str_pid || theApp.pdatabase.Find("SELECT * FROM Tra_info", "pid", (_variant_t)pid) == -1)
		{
			if (pid != str_pid)
			{
				theApp.pdatabase.Update("SELECT * FROM Tra_info", "pid", (_variant_t)str_pid, "pid", (_variant_t)pid);
				str_pid = pid;
			}
			if (pname != str_pname)
			{
				theApp.pdatabase.Update("SELECT * FROM Tra_info", "pid", (_variant_t)str_pid, "pname", (_variant_t)pname);
				str_pname = pname;
			}
			if (pcid != str_pcid)
			{
				theApp.pdatabase.Update("SELECT * FROM Tra_info", "pid", (_variant_t)str_pid, "pcid", (_variant_t)pcid);
				str_pcid = pcid;
			}
			if (pmark != check_pmark)
			{
				theApp.pdatabase.Update("SELECT * FROM Tra_info", "pid", (_variant_t)str_pid, "pmark", (_variant_t)pmark);
				check_pmark = pmark;
			}
			if (MessageBoxW(_T("�޸ĳɹ�!"), _T("��ʾ")) == IDOK)
				this->DestroyWindow();
		}
		else
			MessageBoxW(_T("�����֤���Ѵ��ڣ������º˶�����!"), _T("��ʾ"));
	}
}
