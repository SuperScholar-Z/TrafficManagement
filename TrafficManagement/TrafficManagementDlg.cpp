
// TrafficManagementDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "TrafficManagementDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTrafficManagementDlg �Ի���



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


// CTrafficManagementDlg ��Ϣ�������

BOOL CTrafficManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_tab.InsertItem(0, _T("�߼��û�"));  //��Ӹ߼��û�ѡ� 
	m_tab.InsertItem(1, _T("��ͨ�û�"));  //�����ͨ�û�ѡ� 

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
	//GetDlgItem(IDC_STATIC2)->SetFont(f);//���ñ�ǩ�ؼ������С

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTrafficManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTrafficManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrafficManagementDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (m_tab.GetCurSel() == 0)
		GetDlgItem(IDC_SIGNUP)->ShowWindow(false);
	else
		GetDlgItem(IDC_SIGNUP)->ShowWindow(true);

	*pResult = 0;
}


void CTrafficManagementDlg::OnBnClickedSignin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//Database database1;
	int now = m_tab.GetCurSel();//��ȡѡ��tab��״̬
	CString userName1, password1;
	vector<CString> rowRecords;
	GetDlgItem(IDC_USERNAME)->GetWindowText(userName1);
	GetDlgItem(IDC_PASSWORD)->GetWindowText(password1);//��ȡ�༭����û���������

	if ("" == userName1)
		AfxMessageBox(_T("�������û�����"));
	else if ("" == password1)
		AfxMessageBox(_T("���������룡"));
	else
	{
		//MessageBox(userName);
		if (-1 == theApp.pdatabase.GetRow("SELECT * FROM Tra_user", (_variant_t)"userName", (_variant_t)userName1, rowRecords))//�ж��û����Ƿ���ȷ
			AfxMessageBox(_T("�û������������������û���"));
		else
		{
			if (password1 != rowRecords[1])//�ж������Ƿ���ȷ
				AfxMessageBox(_T("���������������������"));
			else
			{
				if (now == 0)//�߼��û���¼
				{
					//AfxMessageBox(_T("�߼��û���¼"));

					if ("-1" == rowRecords[2])
					{
						AfxMessageBox(_T("�߼��û���¼"));
						//��ת���߼��û����ڲ���
						if (pAdministratorDlg.m_hWnd == NULL)
						{
							pAdministratorDlg.aUserName = userName1;
							pAdministratorDlg.Create(IDD_ADMINISTRATOR_DLG);
						}
						pAdministratorDlg.ShowWindow(true);

						this->ShowWindow(false);
						//this->DestroyWindow();//���ٵ�¼ע�ᴰ��
					}
					else
						AfxMessageBox(_T("������ͨ�û���û�е�¼Ȩ�ޣ�"));
				}
				else//��ͨ�û���¼
				{
					if ("0" == rowRecords[2])
					{
						AfxMessageBox(_T("��ͨ�û���¼"));
						//��ת����ͨ�û����ڲ���
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
						AfxMessageBox(_T("���Ǹ߼��û������Ʋ��߼��û���¼����"));
				}
			}
		}
	}
}


void CTrafficManagementDlg::OnBnClickedSignup()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int now = m_tab.GetCurSel();//��ȡѡ��tab��״̬
	if (now == 0)
		AfxMessageBox(_T("�߼��û�û��ע��Ȩ�ޣ�"));
	else
	{
		MessageBox(_T("��ͨ�û�ע��"));
		//CDlg dlg1;
		dlg1.DoModal();
		//dlg1.Create(IDD_SIGNUPDIALOG);
		//dlg1.ShowWindow(SW_SHOW);
	}
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


HBRUSH CTrafficManagementDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetBkColor(RGB(255, 255, 255));
	default:
		break;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
