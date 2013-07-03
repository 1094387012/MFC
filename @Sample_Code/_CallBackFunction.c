Callback function �d�ҵ{��
TouchAPI.h

#ifdef  TOUCHAPI_EXPORTS  
 #define TOUCH_API __declspec(dllexport)  
#else  
 #define TOUCH_API __declspec(dllimport)  
#endif  
  
// �w�qĲ���I��������T  
struct TouchPoint  
{  
 int X;   
 int Y;   
};  
  
// �w�qcallback function��prototype  
// CB_TOUCH_FUNC�O�@��pointer,���V�㦳�@��TouchPoint����,�B�^��void������?  
// �e������typedef,�ҥH�{�bCB_TOUCH_FUNC�O�o��������?�W  
typedef void (_stdcall *CB_TOUCH_FUNC) (TouchPoint);  
  
// �w�q�F�@��RegisterCBTouchFunc���禡,�i�ǤJ�@�Ө㦳CB_TOUCH_FUNC���O��callback function  
TOUCH_API void RegisterCBTouchFunc(CB_TOUCH_FUNC callback);  


TouchAPI.cpp
#include "stdafx.h"  
#include "TouchAPI.h"  
  
void DetectTouchFromSystem(CB_TOUCH_FUNC callback)  
{  
    // ��t�Ψ��otouch��Ʈ�,  
    // �N�|�I�s�@��pCB_TOUCH_FUNC�ѼƩҫ���function�@��  
    TouchPoint tp;  
    tp.X = 5;  
    tp.Y = 10;  
    callback(tp);  
}  
  
void RegisterCallbackTouchFunc(CB_TOUCH_FUNC callback)  
{  
 DetectTouchFromSystem(callback);  
}  
TouchPaint.cpp
#include "stdafx.h"  
#include "conio.h"  
#include "TouchAPI.h"  
   
// �w�q�F�@�ӦW��GetTouch���禡, �]�N�Ocallback�禡  
// ����prototype�����PTouchAPI��CB_TOUCH_FUNC�ŧi�@�P  
void _stdcall GetTouch(TouchPoint point)  
{  
 printf("x=%d, y=%d", point.X, point.Y);  
}  
   
int main(void)  
{  
    //���U�@��callback function  
    RegisterCBTouchFunc(GetTouch);  
    getch();  
    return 0 ;  
}; 


My Example:

In header:

DLOAD_API DoProcess(LPCTSTR fp=NULL, 
					LPCTSTR lpszPortNum=NULL,
					CB_PROG_FUNC NandPrg=NULL,
					E_JOB_TYPE e_Job_Type=JOB_UNKNOWN);
					
struct _CbMsg  
{  
	E_CB_STATE _cb_State;
	CString    _cb_TaskName;
	DWORD	   _cb_Percent;
};

typedef void (_stdcall *CB_PROG_FUNC) (_CbMsg);


In Cpp:
void _stdcall GetProg(_CbMsg nProg)
{
	// Do something;
}