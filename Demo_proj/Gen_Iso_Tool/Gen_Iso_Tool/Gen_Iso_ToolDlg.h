// Gen_Iso_ToolDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"

typedef enum
{
	SET_2K = 0,
	SET_4K,
	SET_MAX
} E_SETTING;

// CGen_Iso_ToolDlg ��ܤ��
class CGen_Iso_ToolDlg : public CDialog
{
// �غc
public:
	CGen_Iso_ToolDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_GEN_ISO_TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩

// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedSrcIso();
	afx_msg void OnBnClickedOutIso();
	afx_msg void OnBnClickedGenIso();
	afx_msg void OnBnClickedRadio2k();
	afx_msg void OnBnClickedRadio4k();

	BOOL ExeCommand();
	CString Get_Curr_Path();
	BOOL CheckMkyaffs2ImageExist();
	void SettingLayout(E_SETTING e_Setting);

	BOOL bIsReady;
	CEdit m_IsoSrcPath;
	CEdit m_IsoOutPath;	
	CString strIsoSrc;
	CString strIsoOut;
	CString m_strCur;
	CString strMessage;	
	CString m_PageSize;
	CString m_SpareSize;
	E_SETTING m_eSetting;
	CButton m_ctrlRadio_2K;	
};
