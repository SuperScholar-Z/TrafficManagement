
// TrafficManagementDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "TrafficManagementDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTrafficManagementDlg 对话框



CTrafficManagementDlg::CTrafficManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrafficManagementDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrafficManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CTrafficManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CTrafficManagementDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTrafficManagementDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_SIGNIN, &CTrafficManagementDlg::OnBnClickedSignin)
	ON_BN_CLICKED(IDC_SIGNUP, &CTrafficManagementDlg::OnBnClickedSignup)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTrafficManagementDlg 消息处理程序

BOOL CTrafficManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_tab.InsertItem(0, _T("高级用户"));  //添加高级用户选项卡 
	m_tab.InsertItem(1, _T("普通用户"));  //添加普通用户选项卡 

	//CFont * f;
	//f = new CFont;
	//f->CreateFont(16,            // nHeight 
	//	0,           // nWidth 
	//	0,           // nEscapement 
	//	0,           // nOrientation 
	//	FW_BOLD,     // nWeight 
	//	FALSE,        // bItalic 
	//	FALSE,       // bUnderline 
	//	0,           // cStrikeOut 
	//	ANSI_CHARSET,              // nCharSet 
	//	OUT_DEFAULT_PRECIS,        // nOutPrecision 
	//	CLIP_DEFAULT_PRECIS,       // nClipPrecision 
	//	DEFAULT_QUALITY,           // nQuality 
	//	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
	//	_T("Arial"));              // lpszFac

	//GetDlgItem(IDC_STATIC1)->SetFont(f);
	//GetDlgItem(IDC_STATIC2)->SetFont(f);//设置标签控件字体大小

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTrafficManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTrafficManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTrafficManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrafficManagementDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码

	if (m_tab.GetCurSel() == 0)
		GetDlgItem(IDC_SIGNUP)->ShowWindow(false);
	else
		GetDlgItem(IDC_SIGNUP)->ShowWindow(true);

	*pResult = 0;
}


void CTrafficManagementDlg::OnBnClickedSignin()
{
	// TODO:  在此添加控件通知处理程序代码
	//Database database1;
	int now = m_tab.GetCurSel();//获取选中tab栏状态
	CString userName1, password1;
	vector<CString> rowRecords;
	GetDlgItem(IDC_USERNAME)->GetWindowText(userName1);
	GetDlgItem(IDC_PASSWORD)->GetWindowText(password1);//获取编辑框的用户名和密码

	if ("" == userName1)
		AfxMessageBox(_T("请输入用户名！"));
	else if ("" == password1)
		AfxMessageBox(_T("请输入密码！"));
	else
	{
		//MessageBox(userName);
		if (-1 == theApp.pdatabase.GetRow("SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName1, rowRecords))//判断用户名是否正确
			AfxMessageBox(_T("用户名错误！请重新输入用户名"));
		else
		{
			if (password1 != rowRecords[1])//判断密码是否正确
				AfxMessageBox(_T("密码错误！请重新输入密码"));
			else
			{
				if (now == 0)//高级用户登录
				{
					//AfxMessageBox(_T("高级用户登录"));

					if ("-1" == rowRecords[2])
					{
						AfxMessageBox(_T("高级用户登录"));
						//跳转到高级用户窗口操作
						if (pAdministratorDlg.m_hWnd == NULL)
						{
							pAdministratorDlg.aUserName = userName1;
							pAdministratorDlg.Create(IDD_ADMINISTRATOR_DLG);
						}
						pAdministratorDlg.ShowWindow(true);

						this->ShowWindow(false);
						//this->DestroyWindow();//销毁登录注册窗口
					}
					else
						AfxMessageBox(_T("你是普通用户，没有登录权限！"));
				}
				else//普通用户登录
				{
					if ("0" == rowRecords[2])
					{
						AfxMessageBox(_T("普通用户登录"));
						//跳转到普通用户窗口操作
						if (pOrdinaryUserDlg.m_hWnd == NULL)
						{
							pOrdinaryUserDlg.oUserName = userName1;
							pOrdinaryUserDlg.Create(IDD_ORDINARYUSER_DIALOG);
						}
						pOrdinaryUserDlg.ShowWindow(true);

						this->ShowWindow(false);
						//this->DestroyWindow();
					}
					else
						AfxMessageBox(_T("你是高级用户！请移步高级用户登录界面"));
				}
			}
		}
	}
}


void CTrafficManagementDlg::OnBnClickedSignup()
{
	// TODO:  在此添加控件通知处理程序代码
	int now = m_tab.GetCurSel();//获取选中tab栏状态
	if (now == 0)
		AfxMessageBox(_T("高级用户没有注册权限！"));
	else
	{
		MessageBox(_T("普通用户注册"));
		//CDlg dlg1;
		dlg1.DoModal();
		//dlg1.Create(IDD_SIGNUPDIALOG);
		//dlg1.ShowWindow(SW_SHOW);
	}
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


HBRUSH CTrafficManagementDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetBkColor(RGB(255, 255, 255));
	default:
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
