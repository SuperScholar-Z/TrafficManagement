#include "stdafx.h"
#include "Database.h"

Database::Database()	//��ʼ�����ݿ�����
{
	AfxEnableControlContainer();	//��ʼ��
	AfxOleInit();

	pConnection.CreateInstance(__uuidof(Connection));	//���ݿ�����ָ���ʼ��

	//�������ݿ�
	try
	{
		//�򿪱���Access��
		_bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=TrafficManagement.mdb";
		pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"), MB_OKCANCEL | MB_ICONQUESTION);
		return;
	}

	//����ָ��ʵ����
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

//*****************�����ݿ��ض��������һ�μ�¼*****************************
void Database::Add(const _variant_t &Text, const _variant_t &userName, const _variant_t &password, const _variant_t &advancedUser)	//�û���Ϣ��
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	pRecordset->AddNew();
	pRecordset->PutCollect("userName", userName);
	pRecordset->PutCollect("password", password);
	pRecordset->PutCollect("advancedUser", advancedUser);
	pRecordset->Update();

	pRecordset->Close();
}
void Database::Add(const _variant_t &Text, const _variant_t &pname, const _variant_t &pid, const _variant_t &pcid, const _variant_t &pmark)	//������Ϣ��
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
void Database::Add(const _variant_t &Text, const _variant_t &value)	//�ڳ���δʶ��ͼƬ��Ϣ��
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

//*******************************ɾ�����ݿ��е�һ�μ�¼******************************************
void Database::Delete(const _variant_t &Text, int row)	//���кż���ɾ��
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	pRecordset->Move(row);
	pRecordset->Delete(adAffectCurrent);
	pRecordset->Update();

	pRecordset->Close();
}
int Database::Delete(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value)	//���ؼ��ּ���ɾ��
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int success = 0;	//�Ƿ�ɹ��ҵ���¼��ɾ��
	while (!pRecordset->adoEOF)	//�������ݿ�
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


int Database::Find(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value)	//�������ݿ��е�ĳһ�μ�¼������������
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int row = 0;	//��¼�������ݿ��е�����
	int success = 0;	//�Ƿ�ɹ��ҵ���¼��ɾ��
	while (!pRecordset->adoEOF)	//�������ݿ�
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

int Database::Update(const _variant_t &Text, const _variant_t &keyField, const _variant_t &keyValue, const _variant_t &Field, const _variant_t &Value)	//�޸����ݿ���һ�μ�¼���ض��ֶ�
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int success = 0;	//�Ƿ�ɹ��ҵ���¼������
	while (!pRecordset->adoEOF)	//�������ݿ�
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


//****************��ȡ���ݿ�ĳ������ĳһ�е���Ϣ*********************
void Database::GetRow(const _variant_t &Text, int row, vector<CString>&strRow)	//����������
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
int Database::GetRow(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value, vector<CString>&strRow)	//���ؼ��ֶ�����
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	int success = 0;	//�Ƿ�ɹ��ҵ��ؼ���������
	while (!pRecordset->adoEOF)	//�������ݿ�
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

void Database::GetAll(const _variant_t &Text, const _variant_t &Field, vector<CString>&strAll)	//��ȡ���ݿ�ĳ������ĳ���ֶε�������Ϣ
{
	pRecordset->Open(Text, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

	while (!pRecordset->adoEOF)	//�������ݿ�
	{
		strAll.push_back((CString)pRecordset->GetCollect(Field));

		pRecordset->MoveNext();
	}

	pRecordset->Close();
}
