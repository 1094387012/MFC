// Gen_Iso_Tool.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CGen_Iso_ToolApp:
// �аѾ\��@�����O�� Gen_Iso_Tool.cpp
//

class CGen_Iso_ToolApp : public CWinApp
{
public:
	CGen_Iso_ToolApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CGen_Iso_ToolApp theApp;