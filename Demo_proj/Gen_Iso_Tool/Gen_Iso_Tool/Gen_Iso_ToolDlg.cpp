// Gen_Iso_ToolDlg.cpp : ��@��
//

#include "stdafx.h"
#include "Gen_Iso_Tool.h"
#include "Gen_Iso_ToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CDROM_ISO		_T("cdrom.iso")
#define ISO_OFFICIAL_NAME	_T("9615-cdp-iso-image.yaffs2")
#define MKYAFFS2_NAME		_T("mkyaffs2image.exe")

// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGen_Iso_ToolDlg ��ܤ��

CGen_Iso_ToolDlg::CGen_Iso_ToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGen_Iso_ToolDlg::IDD, pParent)
	, bIsReady(FALSE)
	, m_PageSize(_T(""))
	, m_SpareSize(_T(""))
	, strMessage(_T(""))
	, m_strCur(_T(""))
	, strIsoOut(_T(""))
	, strIsoSrc(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGen_Iso_ToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_IsoSrcPath);
	DDX_Text(pDX, IDC_EDIT1, strIsoSrc);
	DDX_Control(pDX, IDC_EDIT2, m_IsoOutPath);
	DDX_Text(pDX, IDC_EDIT2, strIsoOut);
	DDX_Control(pDX, IDC_RADIO_2K, m_ctrlRadio_2K);
}

BEGIN_MESSAGE_MAP(CGen_Iso_ToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CGen_Iso_ToolDlg::OnBnClickedSrcIso)
	ON_BN_CLICKED(IDC_BUTTON2, &CGen_Iso_ToolDlg::OnBnClickedOutIso)
	ON_BN_CLICKED(IDC_BUTTON3, &CGen_Iso_ToolDlg::OnBnClickedGenIso)
	ON_BN_CLICKED(IDC_RADIO_2K, &CGen_Iso_ToolDlg::OnBnClickedRadio2k)
	ON_BN_CLICKED(IDC_RADIO_4K, &CGen_Iso_ToolDlg::OnBnClickedRadio4k)
END_MESSAGE_MAP()


// CGen_Iso_ToolDlg �T���B�z�`��

BOOL CGen_Iso_ToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	m_strCur = Get_Curr_Path();
	if ( !CheckMkyaffs2ImageExist() )
	{
		strMessage.Format(_T("%s not exist"), MKYAFFS2_NAME);
		AfxMessageBox(strMessage, MB_ICONEXCLAMATION);
	}

	// Default for 2K
	CButton* radio_2K = (CButton*)GetDlgItem(IDC_RADIO_2K);
	radio_2K->SetCheck(BST_CHECKED);
	SettingLayout(SET_2K);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CGen_Iso_ToolDlg::SettingLayout(E_SETTING e_Setting)
{
	switch (e_Setting)
	{
	case SET_2K:
		m_PageSize = _T("2048");
		m_SpareSize = _T("64");
		break;
	case SET_4K:
		m_PageSize = _T("4096");
		m_SpareSize = _T("224");
		break;
	default:
		m_PageSize = _T("2048");
		m_SpareSize = _T("64");
		break;
	}
}

void CGen_Iso_ToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CGen_Iso_ToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CGen_Iso_ToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGen_Iso_ToolDlg::OnBnClickedSrcIso()
{
	bIsReady = FALSE;
	CString strTmp_SrcIso = _T("");

	strTmp_SrcIso = BrowseForFolder(m_hWnd, _T("Select a directory included source firmware files:"), 
		BIF_USENEWUI | BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON);

	if (strTmp_SrcIso.GetLength() > 0)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE          hFind;
		CString         strImgFileList, strYaffs2FileList, strFileName;

		// Find .img boot file
		strImgFileList.Format(_T("%s\\*.iso"), strTmp_SrcIso);
		hFind = ::FindFirstFile(strImgFileList, &FindFileData);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				CString strFileName(FindFileData.cFileName);
				if (strFileName.Compare(CDROM_ISO) == NULL)
				{
					bIsReady = TRUE;
				}
			} while ( ::FindNextFile(hFind, &FindFileData) );
			::FindClose(hFind);
		}
		
		if (bIsReady)
		{
			strIsoSrc = strTmp_SrcIso;
			UpdateData(FALSE);
		}
		else
		{
			strMessage.Format(_T("Cannot found %s under %s"), CDROM_ISO, strTmp_SrcIso);
			AfxMessageBox(strMessage, MB_ICONEXCLAMATION);
		}
	}
}

void CGen_Iso_ToolDlg::OnBnClickedOutIso()
{
	CString strYaffs2Path = _T("");

	strYaffs2Path = BrowseForFolder(m_hWnd, _T("Select a directory included source firmware files:"), 
		BIF_USENEWUI | BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON);

	if (strYaffs2Path.GetLength() > 0)
	{
		strIsoOut = strYaffs2Path + _T("\\") + ISO_OFFICIAL_NAME;
		UpdateData(FALSE);
	}
}

void CGen_Iso_ToolDlg::OnBnClickedGenIso()
{
	// Check Path
	if (strIsoSrc.IsEmpty() || 
		strIsoOut.IsEmpty() ||
		m_strCur.IsEmpty()	)
	{
		AfxMessageBox(_T("Please check your path was specified"), MB_ICONEXCLAMATION);
		return;
	}

	if (m_ctrlRadio_2K.GetCheck() == BST_UNCHECKED)
	{
		SettingLayout(SET_4K);
	}
	else
	{
		SettingLayout(SET_2K);
	}

	if (!ExeCommand())
	{
		// Fail...
	}
	else
		AfxMessageBox(_T("Done"));
}

CString CGen_Iso_ToolDlg::Get_Curr_Path()
{
	CString strCurPath;
	TCHAR szCurDir[MAX_PATH];

	if (GetCurrentDirectory(MAX_PATH, szCurDir) != 0) 
	{
		strCurPath.Format(_T("%s"), szCurDir);
	}
	return strCurPath;	
}

BOOL CGen_Iso_ToolDlg::ExeCommand()
{	
	CString strExe = MKYAFFS2_NAME;
	CString strCmd = strExe + _T(" -c ") + m_PageSize + _T(" -s ") + m_SpareSize + _T(" ") + strIsoSrc + _T(" ") + strIsoOut;
	CString strFullCur = m_strCur + _T("\\") + strExe;

	PROCESS_INFORMATION processInfo		= {0};
	STARTUPINFO startupInfo             = {0};
	startupInfo.cb                      = sizeof(startupInfo);
	startupInfo.dwFlags					= STARTF_USESHOWWINDOW;
	startupInfo.hStdInput				= NULL;
	startupInfo.hStdOutput				= NULL;
	startupInfo.hStdError				= NULL;

	int nBuffer = strCmd.GetLength() + 30;

 	BOOL bRet = CreateProcess( strFullCur.GetBuffer(),
  							   strCmd.GetBuffer(nBuffer),
 							   NULL, NULL, TRUE, 
 							   NORMAL_PRIORITY_CLASS,
 							   NULL, NULL, &startupInfo, &processInfo );

	strFullCur.ReleaseBuffer();
	strCmd.ReleaseBuffer();
	return TRUE;
}

BOOL CGen_Iso_ToolDlg::CheckMkyaffs2ImageExist()
{
	CString strCur = m_strCur;
	CString strRet;

	strRet.Format(_T("%s\\%s"), strCur, MKYAFFS2_NAME);
	if (!strRet.IsEmpty())
	{
		CFileStatus fs;
		if ( ! CFile::GetStatus(strRet, fs) )
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}

void CGen_Iso_ToolDlg::OnBnClickedRadio2k()
{
// 	CButton* radio_2K = (CButton*)GetDlgItem(IDC_RADIO_2K);
// 	
// 	if (radio_2K->GetCheck() == BST_CHECKED)
// 	{
// 		CButton* radio_4K = (CButton*)GetDlgItem(IDC_RADIO_4K);
// 		radio_4K->SetCheck(BST_UNCHECKED);
// 	}
// 	SettingLayout(SET_2K);
}

void CGen_Iso_ToolDlg::OnBnClickedRadio4k()
{
// 	CButton* radio_4K = (CButton*)GetDlgItem(IDC_RADIO_4K);
// 
// 	if (radio_4K->GetCheck() == BST_CHECKED)
// 	{
// 		CButton* radio_2K = (CButton*)GetDlgItem(IDC_RADIO_2K);
// 		radio_2K->SetCheck(BST_UNCHECKED);
// 	}
// 	SettingLayout(SET_4K);
}
