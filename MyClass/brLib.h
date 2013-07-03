// brLib.h : brLib DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�

#define BRLIB_SUCCESS 1
#define BRLIB_ERROR 0

// CbrLibApp
// �o�����O����@�аѾ\ brLib.cpp
//

class CbrLibApp : public CWinApp
{
public:
	CbrLibApp();

// �мg
public:
	virtual BOOL InitInstance();	
	DECLARE_MESSAGE_MAP()

public:
	/* Convert Use */
	__declspec(dllexport) int UnicodeToAnsi(TCHAR *unicode, char* ansi);
	__declspec(dllexport) int AnsiToUnicode(char* ansi, TCHAR* unicode);
	__declspec(dllexport) int CStringToChar(CString strsrc, char* dest);
	__declspec(dllexport) int CharToCString(char* source, CString* dest);
	/* Debug Use */
	__declspec(dllexport) int DbgPrint(char* chString, CString strData=NULL);
	/* General Use */
	__declspec(dllexport) BOOL CheckFileExist(char* path);
};
