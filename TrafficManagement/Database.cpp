#include "stdafx.h"
#include "Database.h"

Database::Database()	//初始化数据库连接
{
	AfxEnableControlContainer();	//初始化
	AfxOleInit();

	pConnection.CreateInstance(__uuidof(Connection));	//数据库连接指针初始化

	//连接数据库
	try
	{
		//打开本地Access库
		_bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=TrafficManagement.mdb";
		pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("数据库连接失败"), MB_OKCANCEL | MB_ICONQUESTION);
		return;
	}

	//连接指针实例化
	pRecordset.CreateInstance(__uuidof(Recordset));
}

Database::~Database()
{
	if (pConnection->GetState() == adStateOpen)
	{
		pConnection->Close();
	}
	if (pConnection)
	{
		pConnection.Release();
		pConnection = NULL;
	}

	if (pRecordset->GetState() == adStateOpen)
	{
		pRecordset->Close();
	}
	if (pRecordset)
	{
		pRecordset.Release();
		pRecordset = NULL;
	}
}

//*****************向数据库特定表单中添加一段记录*****************************
void Database::Add(const _variant_t &Text, const _variant_t &userName, const _variant_t &password, const _variant_t &advancedUser)	//用户信息表单
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	pRecordset->AddNew();
	pRecordset->PutCollect("userName", userName);
	pRecordset->PutCollect("password", password);
	pRecordset->PutCollect("advancedUser", advancedUser);
	pRecordset->Update();

	pRecordset->Close();
}
void Database::Add(const _variant_t &Text, const _variant_t &pname, const _variant_t &pid, const _variant_t &pcid, const _variant_t &pmark)	//车主信息表单
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	pRecordset->AddNew();
	pRecordset->PutCollect("pname", pname);
	pRecordset->PutCollect("pid", pid);
	pRecordset->PutCollect("pcid", pcid);
	pRecordset->PutCollect("pmark", pmark);
	pRecordset->Update();

	pRecordset->Close();
}
void Database::Add(const _variant_t &Text, const _variant_t &value)	//黑车或未识别图片信息表单
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	pRecordset->AddNew();
	if (Text == (_variant_t)"SELECT * FROM Tra_uCar")
	{
		pRecordset->PutCollect("pcid", value);
	}
	else if (Text == (_variant_t)"SELECT * FROM Tra_fail")
	{
		pRecordset->PutCollect("path", value);
	}
	pRecordset->Update();

	pRecordset->Close();
}
//****************************************************************************

//*******************************删除数据库中的一段记录******************************************
void Database::Delete(const _variant_t &Text, int row)	//按行号检索删除
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	pRecordset->Move(row);
	pRecordset->Delete(adAffectCurrent);
	pRecordset->Update();

	pRecordset->Close();
}
int Database::Delete(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value)	//按关键字检索删除
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int success = 0;	//是否成功找到记录并删除
	while (!pRecordset->adoEOF)	//遍历数据库
	{
		if (pRecordset->GetCollect(Field) == Value)
		{
			pRecordset->Delete(adAffectCurrent);
			pRecordset->Update();
			success = 1;
			break;
		}
		pRecordset->MoveNext();
	}
	
	pRecordset->Close();
	if (success == 0)
		return -1;
	else
		return 0;
}
//***********************************************************************************************


int Database::Find(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value)	//查找数据库中的某一段记录，并返回行数
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int row = 0;	//记录所在数据库中的行数
	int success = 0;	//是否成功找到记录并删除
	while (!pRecordset->adoEOF)	//遍历数据库
	{
		if (pRecordset->GetCollect(Field) == Value)
		{
			success = 1;
			break;
		}
		row++;
		pRecordset->MoveNext();
	}

	pRecordset->Close();
	if (success == 0)
		return -1;
	else
		return row;
}

int Database::Update(const _variant_t &Text, const _variant_t &keyField, const _variant_t &keyValue, const _variant_t &Field, const _variant_t &Value)	//修改数据库中一段记录的特定字段
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int success = 0;	//是否成功找到记录并更新
	while (!pRecordset->adoEOF)	//遍历数据库
	{
		if (pRecordset->GetCollect(keyField) == keyValue)
		{
			pRecordset->PutCollect(Field, Value);
			pRecordset->Update();
			success = 1;
			break;
		}
		pRecordset->MoveNext();
	}

	pRecordset->Close();
	if (success == 0)
		return -1;
	else
		return 0;
}


//****************获取数据库某个表中某一行的信息*********************
void Database::GetRow(const _variant_t &Text, int row, vector<CString>&strRow)	//按行数搜索
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	pRecordset->Move(row);
	if (Text == (_variant_t)"SELECT * FROM Tra_user")
	{
		strRow.push_back((CString)pRecordset->GetCollect("userName"));
		strRow.push_back((CString)pRecordset->GetCollect("password"));
		strRow.push_back((CString)pRecordset->GetCollect("advancedUser"));
	}
	else if (Text == (_variant_t)"SELECT * FROM Tra_info")
	{
		strRow.push_back((CString)pRecordset->GetCollect("pname"));
		strRow.push_back((CString)pRecordset->GetCollect("pid"));
		strRow.push_back((CString)pRecordset->GetCollect("pcid"));
		strRow.push_back((CString)pRecordset->GetCollect("pmark"));
	}
	else if (Text == (_variant_t)"SELECT * FROM Tra_uCar")
	{
		strRow.push_back((CString)pRecordset->GetCollect("pcid"));
	}
	else if (Text == (_variant_t)"SELECT * FROM Tra_fail")
	{
		strRow.push_back((CString)pRecordset->GetCollect("path"));
	}

	pRecordset->Close();
}
int Database::GetRow(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value, vector<CString>&strRow)	//按关键字段搜索
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int success = 0;	//是否成功找到关键字所在行
	while (!pRecordset->adoEOF)	//遍历数据库
	{
		if (pRecordset->GetCollect(Field) == Value)
		{
			success = 1;
			break;
		}
		pRecordset->MoveNext();
	}

	if (success == 0)
	{
		pRecordset->Close();
		return -1;
	}
	else
	{
		if (Text == (_variant_t)"SELECT * FROM Tra_user")
		{
			strRow.push_back((CString)pRecordset->GetCollect("userName"));
			strRow.push_back((CString)pRecordset->GetCollect("password"));
			strRow.push_back((CString)pRecordset->GetCollect("advancedUser"));
		}
		else if (Text == (_variant_t)"SELECT * FROM Tra_info")
		{
			strRow.push_back((CString)pRecordset->GetCollect("pname"));
			strRow.push_back((CString)pRecordset->GetCollect("pid"));
			strRow.push_back((CString)pRecordset->GetCollect("pcid"));
			strRow.push_back((CString)pRecordset->GetCollect("pmark"));
		}
		else if (Text == (_variant_t)"SELECT * FROM Tra_uCar")
		{
			strRow.push_back((CString)pRecordset->GetCollect("pcid"));
		}
		else if (Text == (_variant_t)"SELECT * FROM Tra_fail")
		{
			strRow.push_back((CString)pRecordset->GetCollect("path"));
		}
		pRecordset->Close();
		return 0;
	}
}
//*******************************************************************

void Database::GetAll(const _variant_t &Text, const _variant_t &Field, vector<CString>&strAll)	//获取数据库某个表中某个字段的所有信息
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	while (!pRecordset->adoEOF)	//遍历数据库
	{
		strAll.push_back((CString)pRecordset->GetCollect(Field));

		pRecordset->MoveNext();
	}

	pRecordset->Close();
}
