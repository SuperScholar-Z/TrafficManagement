// UserTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "UserTab.h"
#include "afxdialogex.h"


// CUserTab �Ի���

IMPLEMENT_DYNAMIC(CUserTab, CDialogEx)

CUserTab::CUserTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserTab::IDD, pParent)
{

}

CUserTab::~CUserTab()
{
}

void CUserTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, fieldText);
	//  DDX_Control(pDX, IDC_EDIT1, filedValue);
	DDX_Control(pDX, IDC_LIST2, UserList);
	DDX_Control(pDX, IDC_EDIT1, fieldValue);
}


BEGIN_MESSAGE_MAP(CUserTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserTab::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserTab::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserTab::OnBnClickedButton4)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUserTab::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CUserTab ��Ϣ�������


BOOL CUserTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//�б�ؼ���ʼ��
	CRect rect;
	UserList.GetClientRect(&rect);
	UserList.SetExtendedStyle(UserList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	UserList.InsertColumn(1, _T("�û���"), LVCFMT_CENTER, rect.Width() / 2);
	UserList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 2);
	//�����б���ʼ��
	fieldText.InsertString(0, _T("ȫ����Ϣ"));
	fieldText.InsertString(1, _T("�û���"));
	fieldText.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUserTab::OnBnClickedButton1()
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
	if (strFieldText == (CString)"�û���")
		strFieldVariant = "userName";
	else
		strFieldVariant = "";

	//��ʾ���ҵĽ��
	if (strFieldText == "ȫ����Ϣ")
	{
		UserList.DeleteAllItems();	//��֮ǰ�ļ�¼ȫ��ɾ��

		vector<CString>str_userName;	//�����û��û���
		vector<CString>str_password;	//�����û�����
		vector<CString>str_advancedUser;	//�����û�����
		theApp.pdatabase.GetAll("SELECT * FROM Tra_user", "userName", str_userName);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_user", "password", str_password);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_user", "advancedUser", str_advancedUser);

		int num = str_userName.size();
		for (int i = 0; i < num; i++)
		{
			if (str_advancedUser[i] != "0")
			{
				str_userName.erase(str_userName.begin() + i);
				str_password.erase(str_password.begin() + i);
				str_advancedUser.erase(str_advancedUser.begin() + i);
				num--;
				i--;
			}
		}
		//��ʾ���н��
		for (int i = 0; i < num; i++)
		{
			UserList.InsertItem(i, _T(""));
			UserList.SetItemText(i, 0, str_userName[i]);
			UserList.SetItemText(i, 1, str_password[i]);
		}

		str_userName.clear();
		str_password.clear();
	}
	else if (strFieldValue == "")
		MessageBoxW(_T("���ڱ༭��������Ҫ���ҵ���Ϣ��"), _T("��ʾ"));
	else
	{
		UserList.DeleteAllItems();	//��֮ǰ�ļ�¼ȫ��ɾ��

		vector<CString>strValue;
		int result = theApp.pdatabase.GetRow("SELECT * FROM Tra_user", strFieldVariant, (_variant_t)strFieldValue, strValue);
		if (result == -1 || strValue[2] != "0")
			MessageBoxW(_T("δ�ҵ�ƥ����!"), _T("�������"));
		else
		{
			UserList.InsertItem(0, _T(""));
			UserList.SetItemText(0, 0, strValue[0]);
			UserList.SetItemText(0, 1, strValue[1]);
		}
	}
}


void CUserTab::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pUserUpdateBox.m_hWnd == NULL)
		pUserUpdateBox.Create(IDD_USERUPDATE_BOX);
	pUserUpdateBox.ShowWindow(true);
	pUserUpdateBox.button.SetWindowTextW(_T("���"));

	pUserUpdateBox.userNameText.SetWindowTextW(_T(""));
	pUserUpdateBox.passwordText.SetWindowTextW(_T(""));

	UserList.SetSelectionMark(-1);
}


void CUserTab::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int row = UserList.GetSelectionMark();	//��ȡ�б�ؼ���ѡ����
	if (row >= 0)
	{
		if (pUserUpdateBox.m_hWnd == NULL)
			pUserUpdateBox.Create(IDD_USERUPDATE_BOX);
		pUserUpdateBox.ShowWindow(true);
		pUserUpdateBox.button.SetWindowTextW(_T("�޸�"));
		//��ʾ����Ϣ�ڱ༭����
		pUserUpdateBox.str_userName = UserList.GetItemText(row, 0);
		pUserUpdateBox.str_password = UserList.GetItemText(row, 1);
		pUserUpdateBox.userNameText.SetWindowTextW(pUserUpdateBox.str_userName);
		pUserUpdateBox.passwordText.SetWindowTextW(pUserUpdateBox.str_password);

		UserList.SetSelectionMark(-1);
	}
	else
		MessageBoxW(_T("�����б��ѡ��Ҫ�޸ĵ��û���Ϣ!"), _T("��ʾ"));
}


void CUserTab::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int row = UserList.GetSelectionMark();
	if (row >= 0)
	{
		INT_PTR nRes;
		nRes = MessageBoxW(_T("ȷ��Ҫɾ��������¼��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION);
		if (IDCANCEL == nRes)
		{
			return;
		}

		theApp.pdatabase.Delete("SELECT * FROM Tra_user", "userName", (_variant_t)UserList.GetItemText(row, 0));
		UserList.DeleteItem(row);
	}
	else
		MessageBoxW(_T("�����б��ѡ��Ҫɾ�����û���Ϣ!"), _T("��ʾ"));
}


void CUserTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CUserTab::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (fieldText.GetCurSel() == 0)
	{
		fieldValue.SetWindowTextW((CString)"");
		fieldValue.SetReadOnly(true);
	}
	else
		fieldValue.SetReadOnly(false);
}
