// Auto.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficManagement.h"
#include "OrdinaryUserDlg.h"
#include "Auto.h"
#include "afxdialogex.h"


// CAuto 对话框

IMPLEMENT_DYNAMIC(CAuto, CDialogEx)

CAuto::CAuto(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuto::IDD, pParent)
	, strPathName(_T(""))
{

}

CAuto::~CAuto()
{
}

void CAuto::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAuto, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAuto::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAuto::OnBnClickedButton2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAuto 消息处理程序


void CAuto::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, (CString)"jpg", (CString)"*.jpg", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)"JPEG文件(*.jpg)|*.jpg|GIF文件(*.gif)|*.gif|bmp文件(*.bmp)|*.bmp|", NULL);
	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		ShowImage(strPathName);
	}
	//识别算法
	//由strPathName传图片地址
	//识别成功时：生成一个字符串加入数据库
	CString str = (CString)"鄂A12345";
	theApp.pdatabase.Add("SELECT * FROM Tra_info", "张三", "123456", (_variant_t)str, 0);
	//识别失败时：存入失败的图片路径
	theApp.pdatabase.Add("SELECT * FROM Tra_fail",(_variant_t)strPathName);
	//弹出提示框：
	INT_PTR nRes;
	nRes = MessageBox(_T("识别失败，请转人工识别"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION);
	if (IDCANCEL == nRes)
	{
		return;
	}
	//转换tab栏
	COrdinaryUserDlg *parent = (COrdinaryUserDlg*)GetParent()->GetParent();
	parent->m_auto.ShowWindow(false);
	parent->m_tab.SetCurSel(1);
	parent->m_manual.strPathName = strPathName;
	parent->m_manual.ShowWindow(true);
}


void CAuto::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);

	//与info表单比较判断是否是黑车
	if (theApp.pdatabase.Find("SELECT * FROM Tra_info", "pcid", (_variant_t)str) == -1)
	{
		if (theApp.pdatabase.Find("SELECT * FROM Tra_uCar", "pcid", (_variant_t)str) == -1)
		{
			theApp.pdatabase.Add("SELECT * FROM Tra_uCar", (_variant_t)str);
			AfxMessageBox(_T("该车是黑车，已备案"));
		}
		else
		{
			AfxMessageBox(_T("该车是黑车，请开始行动！！！"));
		}
	}
	else
	{
		theApp.pdatabase.Update("SELECT * FROM Tra_info", "pcid", (_variant_t)str, "pmark", -1);
	}
}

BOOL CAuto::ShowImage(CString str)
{
	CFile file;
	file.Open(str, CFile::modeRead);
	DWORD dwDataLen = (DWORD)file.GetLength();
	BYTE *buf = new BYTE[dwDataLen];
	memset(buf, 0x00, dwDataLen);
	file.Read(buf, dwDataLen);
	file.Close();

	CFile tempfile(_T("temp.jpg"), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&tempfile, CArchive::store);
	ar.Close();
	tempfile.Close();

	CImage image;
	COleStreamFile osf;
	osf.CreateMemoryStream(NULL);
	osf.Write((void*)buf, dwDataLen);
	osf.SeekToBegin();
	image.Load(osf.GetStream());

	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetClientRect(&rect);
	CDC *pDC = pWnd->GetDC();
	image.Draw(pDC->m_hDC, rect);
	ReleaseDC(pDC);

	return TRUE;
}

void CAuto::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	if (strPathName != "")
		ShowImage(strPathName);

	// 不为绘图消息调用 CDialogEx::OnPaint()
}
