// DriverTab.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "DriverTab.h"
#include "afxdialogex.h"


// CDriverTab 对话框

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


// CDriverTab 消息处理程序


BOOL CDriverTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//列表控件初始化
	CRect rect;
	DriverList.GetClientRect(&rect);
	DriverList.SetExtendedStyle(DriverList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	DriverList.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, rect.Width() / 4);
	DriverList.InsertColumn(1, _T("身份证号"), LVCFMT_CENTER, rect.Width() / 4);
	DriverList.InsertColumn(2, _T("车牌号"), LVCFMT_CENTER, rect.Width() / 4);
	DriverList.InsertColumn(3, _T("违章标记"), LVCFMT_CENTER, rect.Width() / 4);
	//下拉列表框初始化
	fieldText.InsertString(0, _T("全部信息"));
	fieldText.InsertString(1, _T("姓名"));
	fieldText.InsertString(2, _T("身份证号"));
	fieldText.InsertString(3, _T("车牌号"));
	fieldText.InsertString(4, _T("违章标记"));
	fieldText.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDriverTab::OnBnClickedButton1()
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
	if (strFieldText == (CString)"姓名")
		strFieldVariant = "pname";
	else if (strFieldText == "身份证号")
		strFieldVariant = "pid";
	else if (strFieldText == "车牌号")
		strFieldVariant = "pcid";
	else if (strFieldText == "违章标记")
		strFieldVariant = "pmark";
	else
		strFieldVariant = "";

	//显示查找的结果
	if (strFieldText == "全部信息")
	{
		DriverList.DeleteAllItems();	//将之前的记录全部删除

		vector<CString>str_pname;	//所有车主姓名
		vector<CString>str_pid;		//所有车主身份证号
		vector<CString>str_pcid;	//所有车主车牌号
		vector<CString>str_pmark;	//所有车主违章标记
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pname", str_pname);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pid", str_pid);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pcid", str_pcid);
		theApp.pdatabase.GetAll("SELECT * FROM Tra_info", "pmark", str_pmark);

		int num = str_pname.size();
		//显示所有结果
		for (int i = 0; i < num; i++)
		{
			//将违规标记由-1转换为"√"
			if (str_pmark[i] != "0")
				str_pmark[i] = "√";
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
		MessageBoxW(_T("请在编辑框中输入要查找的信息！"), _T("提示"));
	}
	else
	{
		DriverList.DeleteAllItems();	//将之前的记录全部删除

		vector<CString>strValue;
		int result = theApp.pdatabase.GetRow("SELECT * FROM Tra_info", strFieldVariant, (_variant_t)strFieldValue, strValue);
		if (result == -1)
			MessageBoxW(_T("未找到匹配项!"), _T("搜索结果"));
		else
		{
			if (strValue[3] != "0")
				strValue[3] = "√";
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
	// TODO:  在此添加控件通知处理程序代码
	if (pDriverUpdateBox.m_hWnd == NULL)
		pDriverUpdateBox.Create(IDD_DRIVERUPDATE_BOX);
	pDriverUpdateBox.ShowWindow(true);
	pDriverUpdateBox.button.SetWindowTextW(_T("添加"));

	pDriverUpdateBox.pnameText.SetWindowTextW(_T(""));
	pDriverUpdateBox.pidText.SetWindowTextW(_T(""));
	pDriverUpdateBox.pcidText.SetWindowTextW(_T(""));
	pDriverUpdateBox.pmarkCheck.SetCheck(0);

	DriverList.SetSelectionMark(-1);
}


void CDriverTab::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	int row = DriverList.GetSelectionMark();	//获取列表控件的选中行
	if (row >= 0)
	{
		if (pDriverUpdateBox.m_hWnd == NULL)
			pDriverUpdateBox.Create(IDD_DRIVERUPDATE_BOX);
		pDriverUpdateBox.ShowWindow(true);
		pDriverUpdateBox.button.SetWindowTextW(_T("修改"));
		//显示旧信息在编辑框中
		pDriverUpdateBox.str_pname = DriverList.GetItemText(row, 0);
		pDriverUpdateBox.str_pid = DriverList.GetItemText(row, 1);
		pDriverUpdateBox.str_pcid = DriverList.GetItemText(row, 2);
		if (DriverList.GetItemText(row, 3) == "√")
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
		MessageBoxW(_T("请在列表框选中要修改的车主信息!"), _T("提示"));
}


void CDriverTab::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	int row = DriverList.GetSelectionMark();
	if (row >= 0)
	{
		theApp.pdatabase.Delete("SELECT * FROM Tra_info", "pid", (_variant_t)DriverList.GetItemText(row, 1));
		DriverList.DeleteItem(row);
	}
	else
		MessageBoxW(_T("请在列表框选中要删除的车主信息!"), _T("提示"));
}
