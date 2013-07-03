// stdafx.cpp : �ȥ]�t�з� Include �ɪ���l�{����
// Gen_Iso_Tool.pch �|��������sĶ���Y��
// stdafx.obj �|�]�t����sĶ���O��T

#include "stdafx.h"

/********************************************************************/
/*																	*/
/* Function name : BrowseForFolder									*/		
/* Description   : Browse for folder using SHBrowseForFolder.		*/
/*																	*/
/********************************************************************/
CString BrowseForFolder(HWND hWnd, LPCTSTR lpszTitle, UINT nFlags)
{
	// We're going to use the shell to display a 
	// "Choose Directory" dialog box for the user.
	CString strResult = _T("");

	LPMALLOC lpMalloc;

	if (::SHGetMalloc(&lpMalloc) != NOERROR)
	{
		// failed to get allocator  
		return strResult; 
	}

	LPITEMIDLIST pidlRoot=NULL;
	SHGetFolderLocation(hWnd, CSIDL_DESKTOP, NULL, NULL, &pidlRoot);


	TCHAR szBuffer[_MAX_PATH];
	TCHAR szDisplayName[_MAX_PATH];

	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = hWnd;
	// set root at Desktop
	browseInfo.pidlRoot = pidlRoot; 
	browseInfo.pszDisplayName = szDisplayName;
	browseInfo.lpszTitle = lpszTitle;
	browseInfo.ulFlags = nFlags;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;

	LPITEMIDLIST lpItemIDList;

	if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
	{
		// Get the path of the selected folder from the item ID list.
		if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
		{
			// At this point, szBuffer contains the path the user chose.
			if (szBuffer[0] == _T('\0'))
			{
				// SHGetPathFromIDList failed, or SHBrowseForFolder failed.
				AfxMessageBox(_T("Failed to get directory"), MB_ICONSTOP|MB_OK);
				return strResult;
			}

			// We have a path in szBuffer!
			strResult = szBuffer;
			return strResult;
		}
		else
		{
			// The thing referred to by lpItemIDList 
			// might not have been a file system object.
			// For whatever reason, SHGetPathFromIDList didn't work!
			AfxMessageBox(_T("Failed to get directory"), MB_ICONSTOP|MB_OK);
			return strResult; // strResult is empty 
		}
		lpMalloc->Free(lpItemIDList);
	}

	if (pidlRoot)
	{
		lpMalloc->Free(pidlRoot);
	}

	lpMalloc->Release();

	return strResult;
}

