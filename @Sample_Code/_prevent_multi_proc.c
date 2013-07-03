// �o�q�d�ҵ{���Q��²�檺 named kernel object �F��
// ����P�ɦ���ӬۦP�� instalnces ���檺���p

#include "stdafx.h"
#include <windows.h>
int _tmain(int argc, _TCHAR* argv[])
{
	// �����n,�A���t�Τ���n���H�ϥ� Baby �o�ӦW�r,
	// �̦n����k�O�ϥ� GUID(Globally Unique Identifier) �ӷ�@�W��
	// ���� GUID ����k: �ϥ� VS ���u�� UUIDGEN.EXE
	HANDLE h = CreateEvent(NULL,FALSE,FALSE,"Baby");

   if (GetLastError( )==ERROR_ALREADY_EXISTS) {
      MessageBox(NULL,"�t�Τ��w�g�����ƪ��{�����b����","Error",MB_OK);
      return(0);
   }
   getchar();
   // Before exiting, close the object.
   CloseHandle(h);
   return(0);
}

// ============ �t�~����k ============  
/* http://www.codeguru.com/Cpp/W-P/system/misc/article.php/c5663/
This is a very simple way to detect the running instance of an application. It can be achieved by declaring a data variable in the compiler's own data section called shared.

#pragma data_seg("Shared")
LONG g_Counter = -1;
#pragma data_seg()

After this, the Linker will be noticed to make the Shared section readable, writable, and shared.


#pragma comment(linker, "/section:Shared, rws")
Now, whenever the application runs, the data variable declared in the compiler's data section will be incremented by 1 and until or unless the application gets closed, the data variable's value will not be decremented. Now, at this point, if we start the application again, it will check for the value of the variable declared in the data section of the compiler. If it's greater than 1, splash message of duplicate instance; else, start the application.

The value in the data variable of the compiler's data section is incremented or decremented by the functions declared in winbase.h; these are InterLockedIncrement and InterLockedDecrement. Just pass the address of the variable and the rest will be performed by the function.






*/

