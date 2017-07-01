// DriverTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "DriverTab.h"
#include "afxdialogex.h"


// CDriverTab �Ի���

IMPLEMENT_DYNAMIC(CDriverTab, CDialogEx)

CDriverTab::CDriverTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDriverTab::IDD, pParent)
{

}

CDriverTab::~CDriverTab()
{
}

void CDriverTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, fieldText);
	DDX_Control(pDX, IDC_EDIT1, fieldValue);
	DDX_Control(pDX, IDC_LIST2, DriverList);
}


BEGIN_MESSAGE_MAP(CDriverTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDriverTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDriverTab::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDriverTab::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDriverTab::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDriverTab ��Ϣ�������


BOOL CDriverTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//�б�ؼ���ʼ��
	CRect rect;
	DriverList.GetClientRect(&rect);
	DriverList.SetExtendedStyle(DriverList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	DriverList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 4);
	DriverList.InsertColumn(1, _T("���֤��"), LVCFMT_CENTER, rect.Width() / 4);
	DriverList.InsertColumn(2, _T("���ƺ�"), LVCFMT_CENTER, rect.Width() / 4);
	DriverList.InsertColumn(3, _T("Υ�±��"), LVCFMT_CENTER, rect.Width() / 4);
	//�����б���ʼ��
	fieldText.InsertString(0, _T("ȫ����Ϣ"));
	fieldText.InsertString(1, _T("����"));
	fieldText.InsertString(2, _T("���֤��"));
	fieldText.InsertString(3, _T("���ƺ�"));
	fieldText.InsertString(4, _T("Υ�±��"));
	fieldText.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDriverTab::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strFieldValue;	//�ֶ�ֵ
	CString strFieldText;	//�ֶ�����
	_variant_t strFieldVariant;	//�ֶ�����(���ݿ���)
	vector<CString>strDriver;	//�������ý��

	//��ȡ�༭����б���ֵ
	fieldValue.GetWindowTextW(strFieldValue);
	fieldText.GetLBText(fieldText.GetCurSel(), strFieldText);

	//�����б����ֶ������������ݿ���õ��ַ���
	if (strFieldText == (CString)"����")
		strFieldVariant = "pname";
	else if (strFieldText == "���֤��")
		strFieldVariant = "pid";
	else if (strFieldText == "���ƺ�")
		strFieldVariant = "pcid";
	else if (strFieldText == "Υ�±��")
		strFieldVariant = "pmark";
	else
		strFieldVariant = "";

	//��ʾ���ҵĽ��
	if (strFieldText == "ȫ����Ϣ")
	{
		DriverList.DeleteAllItems();	//��֮ǰ�ļ�¼ȫ��ɾ��

		vector<CString>str_pname;	//���г�������
		vector<CString>str_pid;		//���г������֤��
		vector<CString>str_pcid;	//���г������ƺ�
		vector<CString>str_pmark;	//���г���Υ�±��
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pname", str_pname);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pid", str_pid);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pcid", str_pcid);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pmark", str_pmark);

		int num = str_pname.size();
		//��ʾ���н��
		for (int i = 0; i < num; i++)
		{
			//��Υ������-1ת��Ϊ"��"
			if (str_pmark[i] != "0")
				str_pmark[i] = "��";
			else
				str_pmark[i] = "";

			DriverList.InsertItem(i, _T(""));
			DriverList.SetItemText(i, 0, str_pname[i]);
			DriverList.SetItemText(i, 1, str_pid[i]);
			DriverList.SetItemText(i, 2, str_pcid[i]);
			DriverList.SetItemText(i, 3, str_pmark[i]);
		}

		str_pname.clear();
		str_pid.clear();
		str_pcid.clear();
		str_pmark.clear();
	}
	else if (strFieldValue == "")
	{
		MessageBoxW(_T("���ڱ༭��������Ҫ���ҵ���Ϣ��"), _T("��ʾ"));
	}
	else
	{
		DriverList.DeleteAllItems();	//��֮ǰ�ļ�¼ȫ��ɾ��

		vector<CString>strValue;
		int result = theApp.pdatabase.GetRow("SELECT * FROM Tra_info", strFieldVariant, (_variant_t)strFieldValue, strValue);
		if (result == -1)
			MessageBoxW(_T("δ�ҵ�ƥ����!"), _T("�������"));
		else
		{
			if (strValue[3] != "0")
				strValue[3] = "��";
			else
				strValue[3] = "";

			DriverList.InsertItem(0, _T(""));
			DriverList.SetItemText(0, 0, strValue[0]);
			DriverList.SetItemText(0, 1, strValue[1]);
			DriverList.SetItemText(0, 2, strValue[2]);
			DriverList.SetItemText(0, 3, strValue[3]);
		}
	}
}


void CDriverTab::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pDriverUpdateBox.m_hWnd == NULL)
		pDriverUpdateBox.Create(IDD_DRIVERUPDATE_BOX);
	pDriverUpdateBox.ShowWindow(true);
	pDriverUpdateBox.button.SetWindowTextW(_T("���"));

	pDriverUpdateBox.pnameText.SetWindowTextW(_T(""));
	pDriverUpdateBox.pidText.SetWindowTextW(_T(""));
	pDriverUpdateBox.pcidText.SetWindowTextW(_T(""));
	pDriverUpdateBox.pmarkCheck.SetCheck(0);

	DriverList.SetSelectionMark(-1);
}


void CDriverTab::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int row = DriverList.GetSelectionMark();	//��ȡ�б�ؼ���ѡ����
	if (row >= 0)
	{
		if (pDriverUpdateBox.m_hWnd == NULL)
			pDriverUpdateBox.Create(IDD_DRIVERUPDATE_BOX);
		pDriverUpdateBox.ShowWindow(true);
		pDriverUpdateBox.button.SetWindowTextW(_T("�޸�"));
		//��ʾ����Ϣ�ڱ༭����
		pDriverUpdateBox.str_pname = DriverList.GetItemText(row, 0);
		pDriverUpdateBox.str_pid = DriverList.GetItemText(row, 1);
		pDriverUpdateBox.str_pcid = DriverList.GetItemText(row, 2);
		if (DriverList.GetItemText(row, 3) == "��")
		{
			pDriverUpdateBox.check_pmark = 1;
			pDriverUpdateBox.pmarkCheck.SetCheck(1);
		}
		else
		{
			pDriverUpdateBox.check_pmark = 0;
			pDriverUpdateBox.pmarkCheck.SetCheck(0);
		}
		pDriverUpdateBox.pnameText.SetWindowTextW(pDriverUpdateBox.str_pname);
		pDriverUpdateBox.pidText.SetWindowTextW(pDriverUpdateBox.str_pid);
		pDriverUpdateBox.pcidText.SetWindowTextW(pDriverUpdateBox.str_pcid);

		DriverList.SetSelectionMark(-1);
	}
	else
		MessageBoxW(_T("�����б��ѡ��Ҫ�޸ĵĳ�����Ϣ!"), _T("��ʾ"));
}


void CDriverTab::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int row = DriverList.GetSelectionMark();
	if (row >= 0)
	{
		theApp.pdatabase.Delete("SELECT * FROM Tra_info", "pid", (_variant_t)DriverList.GetItemText(row, 1));
		DriverList.DeleteItem(row);
	}
	else
		MessageBoxW(_T("�����б��ѡ��Ҫɾ���ĳ�����Ϣ!"), _T("��ʾ"));
}
