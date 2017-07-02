// DriverUpdateBox.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "DriverUpdateBox.h"
#include "afxdialogex.h"


// CDriverUpdateBox 对话框

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


// CDriverUpdateBox 消息处理程序


BOOL CDriverUpdateBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDriverUpdateBox::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strButton;
	button.GetWindowTextW(strButton);

	if (strButton == "添加")	//添加车主信息
	{
		//使用临时变量记录编辑框信息
		CString pname, pid, pcid;
		pnameText.GetWindowTextW(pname);
		pidText.GetWindowTextW(pid);
		pcidText.GetWindowTextW(pcid);
		int pmark = pmarkCheck.GetCheck();

		if (pname == "" || pid == "" || pcid == "")
			MessageBoxW(_T("信息不能为空，请输入完整信息!"), _T("提示"));
		else if (theApp.pdatabase.Find("SELECT * FROM Tra_info", "pid", (_variant_t)pid) == -1)
		{
			theApp.pdatabase.Add("SELECT * FROM Tra_info", (_variant_t)pname, (_variant_t)pid, (_variant_t)pcid, (_variant_t)pmark);
			if (MessageBoxW(_T("添加成功!"), _T("提示")) == IDOK)
				this->DestroyWindow();
		}
		else
			MessageBoxW(_T("已存在该记录，请重新核对信息!"), _T("提示"));
	}
	else if (strButton == "修改")	//修改车主信息
	{
		//使用临时变量记录编辑框信息
		CString pname, pid, pcid;
		pnameText.GetWindowTextW(pname);
		pidText.GetWindowTextW(pid);
		pcidText.GetWindowTextW(pcid);
		int pmark = pmarkCheck.GetCheck();

		if (pname == "" || pid == "" || pcid == "")
			MessageBoxW(_T("信息不能为空，请输入完整信息!"), _T("提示"));
		else if (pname == str_pname && pid == str_pid && pcid == str_pcid && pmark == check_pmark)
			MessageBoxW(_T("新信息不能与原信息相同，请重新输入!"), _T("提示"));
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
			if (MessageBoxW(_T("修改成功!"), _T("提示")) == IDOK)
				this->DestroyWindow();
		}
		else
			MessageBoxW(_T("该身份证号已存在，请重新核对输入!"), _T("提示"));
	}
}
