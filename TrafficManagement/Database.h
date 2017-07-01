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
	Database();	//初始化数据库连接
	~Database();	//关闭连接
	
	//***************向数据库特定表单中添加一段记录************************
	void Add(const _variant_t &Text, const _variant_t &userName, const _variant_t &password, const _variant_t &advancedUser);	//用户信息表单
	void Add(const _variant_t &Text, const _variant_t &pname, const _variant_t &pid, const _variant_t &pcid, const _variant_t &pmark);	//车主信息表单
	void Add(const _variant_t &Text, const _variant_t &value);	//黑车或未识别图片信息表单
	//*********************************************************************
	//*******************************删除数据库中的一段记录******************************************
	void Delete(const _variant_t &Text, int row);	//按行号检索删除
	int Delete(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value);	//按关键字检索删除
	//***********************************************************************************************
	
	int Find(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value);	//查找数据库中的某一段记录，并返回行数
	int Update(const _variant_t &Text, const _variant_t &keyField, const _variant_t &keyValue, const _variant_t &Field, const _variant_t &Value);	//按关键字检索数据库中一段记录并修改特定字段
	
	//****************获取数据库某个表中某一行的信息*********************
	void GetRow(const _variant_t &Text, int row, vector<CString>&strRow);	//按行数搜索
	int GetRow(const _variant_t &Text, const _variant_t &Field, const _variant_t &Value, vector<CString>&strRow);	//按关键字段搜索
	//*******************************************************************
	
	void GetAll(const _variant_t &Text, const _variant_t &Field, vector<CString>&strAll);	//获取数据库某个表中某个字段的所有信息
};

#endif
