// SimpleMutex.cpp : Defines the entry point for the console application.
// ²�檺�D�n�u�@
// 1. �إ� Mutex
// 2. ���ͨ�� thread  A, B
//    A ���ͤ@�� radom number �s���줽�ΰO����Ϥ�
//    B �s��Ū�� 10 �����,��ܦb�ù��W
//    (�g�J�PŪ�������㦳�W�e��)

#include "stdafx.h"
#include "SimpleMutex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
using namespace std;

void ShowError();
UINT  WriteData(LPVOID LParam);       // ���_���g�J��� (�g�J�PŪ�����t�פ��P)
UINT  ReadData(LPVOID LParam);        // ���_���q�@�ΰO�����Ū�����

struct ShareInfo{
	HANDLE hMutex;                    // �P�B�Ϊ� kernel object
	int *ShareDataBuffer;             // �O���@�ΰO���骺��m
	int DataLength;
}Info1;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	// �@�ΰO����϶�
	int Size=10;
	int *DataBuffer=(int*)HeapAlloc(GetProcessHeap(),0,Size*sizeof(int));
	if(DataBuffer==NULL){
		ShowError();
	}
	
	cout << "�@�ΰO����t�m�֭�= "<<HeapSize(GetProcessHeap(),0,DataBuffer) <<" Bytes (�Ы����NŲ�~��)"<< endl;
    Info1.ShareDataBuffer=DataBuffer;
	Info1.DataLength=Size;
	getchar();

	// 1. �إ� Mutex: Initial ���A�� non-signal
       HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
	   Info1.hMutex=hMutex;

    // 2. �إ� A, B threads
	   AfxBeginThread(WriteData,(LPVOID)&Info1);
	   AfxBeginThread(ReadData,(LPVOID)&Info1);


    HANDLE hevent=CreateEvent(NULL,FALSE,FALSE,NULL);
	WaitForSingleObject(hevent,INFINITE);

	// �U�����{���û����|�Q����, �򥻤W,�o�O���|����{��
	HeapFree(GetProcessHeap(),NULL,DataBuffer);
	CloseHandle(hMutex);
	CloseHandle(hevent);
	return 0;
}

UINT  WriteData(LPVOID LParam){
	ShareInfo *pInfo1=(ShareInfo*) LParam;

	while(true){   // ���_���g�J���

		// Step 1: �o��s���\�i
			WaitForSingleObject(pInfo1->hMutex,INFINITE);
			cout << "============================= �g�J�{���o��\�i =============================" << endl;
		// Step 2: �g�J���
			srand( (unsigned)time( NULL ) );
			
			for(int i=0;i<pInfo1->DataLength;i++){
				int data=rand();
				pInfo1->ShareDataBuffer[i]=data;
				cout<<"�g�J: " << data << endl;
				Sleep(100);
			}

		// Step 3: ���}
			cout << "============================= �g�J�{�����} =============================" << endl;
			ReleaseMutex(pInfo1->hMutex);
	}

	return(0);	
}

UINT  ReadData(LPVOID LParam){
	ShareInfo *pInfo1=(ShareInfo*) LParam;

	while(true){   // ���_��Ū�����

		// Step 1: �o��s���\�i
			WaitForSingleObject(pInfo1->hMutex,INFINITE);
            cout << "============================= Ū���{���o��\�i =============================" << endl;
		// Step 2: �g�J���
			for(int i=0;i<pInfo1->DataLength;i++){
				int data=pInfo1->ShareDataBuffer[i];
				cout<<"Ū��: " << data << endl;
				Sleep(1000);
			}

		// Step 3: ���}
			cout << "============================= Ū���{�����} =============================" << endl;
			ReleaseMutex(pInfo1->hMutex);
			
	}

	return(0);	
}

// �Y�����󪺿��~, �A�i�H�I�s�U���o�� functin
// ���A�զX�X���~�T��
void ShowError(){
  LPVOID lpMsgBuf;

  /* ����T��
     FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,
		   NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		   (LPTSTR) &lpMsgBuf,0,NULL );
  */

   // �^��T�� (�����K�� Yahoo �d�O�H�p��ѨM)
   FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL,GetLastError(),MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), // Default language
		 (LPTSTR) &lpMsgBuf,0,NULL );
   MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
   LocalFree( lpMsgBuf );
}

