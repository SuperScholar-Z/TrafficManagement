#ifndef DATABASE_H
#define DATABASE_H

#include "resource.h"
#include <vector>

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
using namespace std;

class Database
{
private:
	_ConnectionPtr pConnection;
	_RecordsetPtr pRecordset;
public:
	Database();	//��ʼ�����ݿ�����
	~Database();	//�ر�����
	
	//***************�����ݿ��ض��������һ�μ�¼************************
	void Add(const _variant_t &Text, const _variant_t &userName, const _variant_t &password, const _variant_t &advancedUser);	//�û���Ϣ��
	void Add(const _variant_t &Text, const _variant_t &pname, const _variant_t &pid, const _variant_t &pcid, const _variant_t &pmark);	//������Ϣ��
	void Add(const _variant_t &Text, const _variant_t &value);	//�ڳ���δʶ��ͼƬ��Ϣ��
	//*********************************************************************
	//*******************************ɾ�����ݿ��е�һ�μ�¼******************************************
	void Delete(const _variant_t &Text, int row);	//���кż���ɾ��
	int Delete(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value);	//���ؼ��ּ���ɾ��
	//***********************************************************************************************
	
	int Find(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value);	//�������ݿ��е�ĳһ�μ�¼������������
	int Update(const _variant_t &Text, const _variant_t &keyField, const _variant_t &keyValue, const _variant_t &Field, const _variant_t &Value);	//���ؼ��ּ������ݿ���һ�μ�¼���޸��ض��ֶ�
	
	//****************��ȡ���ݿ�ĳ������ĳһ�е���Ϣ*********************
	void GetRow(const _variant_t &Text, int row, vector<CString>&strRow);	//����������
	int GetRow(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value, vector<CString>&strRow);	//���ؼ��ֶ�����
	//*******************************************************************
	
	void GetAll(const _variant_t &Text, const _variant_t &Field, vector<CString>&strAll);	//��ȡ���ݿ�ĳ������ĳ���ֶε�������Ϣ
};

#endif
