
// ossGui.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CossGuiApp:
// �йش����ʵ�֣������ ossGui.cpp
//

class CossGuiApp : public CWinApp
{
public:
	CossGuiApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CossGuiApp theApp;