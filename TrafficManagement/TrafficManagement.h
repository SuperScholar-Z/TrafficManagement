
// TrafficManagement.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Database.h"

// CTrafficManagementApp: 
// �йش����ʵ�֣������ TrafficManagement.cpp
//

class CTrafficManagementApp : public CWinApp
{
public:
	CTrafficManagementApp();

// ��д
public:
	virtual BOOL InitInstance();

	Database pdatabase;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrafficManagementApp theApp;