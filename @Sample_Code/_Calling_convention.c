In header

// DloadDll.h : DloadDll DLL ���D�n���Y��

#pragma once

#ifndef __AFXWIN_H__
#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�

// CDloadDllApp
#ifdef _BR_EXPORTS
#define DLOAD_API extern "C" void __declspec(dllexport) __stdcall
#else
#define DLOAD_API extern "C" void __declspec(dllimport) __stdcall
#endif

DLOAD_API DoProcess(LPCTSTR fp=NULL, 
					LPCTSTR lpszPortNum=NULL,
					CB_PROG_FUNC NandPrg=NULL,
					E_JOB_TYPE e_Job_Type=JOB_UNKNOWN);

In Cpp

DLOAD_API DoProcess(LPCTSTR fp,			/* =NULL */
						 LPCTSTR lpszPortNum,	/* =NULL */
						 CB_PROG_FUNC NandPrg,	/* =NULL */
						 E_JOB_TYPE e_Job_Type) /* =JOB_UNKNOWN */
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	// Calling Static Method
	CDloadDllApp::DloadFirmwareUpgrade(fp, 
									   lpszPortNum,
									   NandPrg, 
									   e_Job_Type);
}