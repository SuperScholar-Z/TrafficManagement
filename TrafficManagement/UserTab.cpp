// UserTab.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "UserTab.h"
#include "afxdialogex.h"


// CUserTab 对话框

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


// CUserTab 消息处理程序


BOOL CUserTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//列表控件初始化
	CRect rect;
	UserList.GetClientRect(&rect);
	UserList.SetExtendedStyle(UserList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	UserList.InsertColumn(1, _T("用户名"), LVCFMT_CENTER, rect.Width() / 2);
	UserList.InsertColumn(1, _T("密码"), LVCFMT_CENTER, rect.Width() / 2);
	//下拉列表框初始化
	fieldText.InsertString(0, _T("全部信息"));
	fieldText.InsertString(1, _T("用户名"));
	fieldText.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CUserTab::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strFieldValue;	//字段值
	CString strFieldText;	//字段类型
	_variant_t strFieldVariant;	//字段类型(数据库用)
	vector<CString>strDriver;	//查找所得结果

	//获取编辑框和列表框的值
	fieldValue.GetWindowTextW(strFieldValue);
	fieldText.GetLBText(fieldText.GetCurSel(), strFieldText);

	//根据列表框的字段类型生产数据库可用的字符串
	if (strFieldText == (CString)"用户名")
		strFieldVariant = "userName";
	else
		strFieldVariant = "";

	//显示查找的结果
	if (strFieldText == "全部信息")
	{
		UserList.DeleteAllItems();	//将之前的记录全部删除

		vector<CString>str_userName;	//所有用户用户名
		vector<CString>str_password;	//所有用户密码
		vector<CString>str_advancedUser;	//所有用户类型
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
		//显示所有结果
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
		MessageBoxW(_T("请在编辑框中输入要查找的信息！"), _T("提示"));
	else
	{
		UserList.DeleteAllItems();	//将之前的记录全部删除

		vector<CString>strValue;
		int result = theApp.pdatabase.GetRow("SELECT * FROM Tra_user", strFieldVariant, (_variant_t)strFieldValue, strValue);
		if (result == -1 || strValue[2] != "0")
			MessageBoxW(_T("未找到匹配项!"), _T("搜索结果"));
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
	// TODO:  在此添加控件通知处理程序代码
	if (pUserUpdateBox.m_hWnd == NULL)
		pUserUpdateBox.Create(IDD_USERUPDATE_BOX);
	pUserUpdateBox.ShowWindow(true);
	pUserUpdateBox.button.SetWindowTextW(_T("添加"));

	pUserUpdateBox.userNameText.SetWindowTextW(_T(""));
	pUserUpdateBox.passwordText.SetWindowTextW(_T(""));

	UserList.SetSelectionMark(-1);
}


void CUserTab::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	int row = UserList.GetSelectionMark();	//获取列表控件的选中行
	if (row >= 0)
	{
		if (pUserUpdateBox.m_hWnd == NULL)
			pUserUpdateBox.Create(IDD_USERUPDATE_BOX);
		pUserUpdateBox.ShowWindow(true);
		pUserUpdateBox.button.SetWindowTextW(_T("修改"));
		//显示旧信息在编辑框中
		pUserUpdateBox.str_userName = UserList.GetItemText(row, 0);
		pUserUpdateBox.str_password = UserList.GetItemText(row, 1);
		pUserUpdateBox.userNameText.SetWindowTextW(pUserUpdateBox.str_userName);
		pUserUpdateBox.passwordText.SetWindowTextW(pUserUpdateBox.str_password);

		UserList.SetSelectionMark(-1);
	}
	else
		MessageBoxW(_T("请在列表框选中要修改的用户信息!"), _T("提示"));
}


void CUserTab::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	int row = UserList.GetSelectionMark();
	if (row >= 0)
	{
		INT_PTR nRes;
		nRes = MessageBoxW(_T("确定要删除此条记录吗？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION);
		if (IDCANCEL == nRes)
		{
			return;
		}

		theApp.pdatabase.Delete("SELECT * FROM Tra_user", "userName", (_variant_t)UserList.GetItemText(row, 0));
		UserList.DeleteItem(row);
	}
	else
		MessageBoxW(_T("请在列表框选中要删除的用户信息!"), _T("提示"));
}


void CUserTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CUserTab::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (fieldText.GetCurSel() == 0)
	{
		fieldValue.SetWindowTextW((CString)"");
		fieldValue.SetReadOnly(true);
	}
	else
		fieldValue.SetReadOnly(false);
}
