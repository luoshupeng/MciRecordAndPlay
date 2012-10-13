// MciRecordAndPlayDlg.h : header file
//

#if !defined(AFX_MCIRECORDANDPLAYDLG_H__658A6371_845A_4DE8_912C_D1BF234558A7__INCLUDED_)
#define AFX_MCIRECORDANDPLAYDLG_H__658A6371_845A_4DE8_912C_D1BF234558A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMciRecordAndPlayDlg dialog

class CMciRecordAndPlayDlg : public CDialog
{
// Construction
public:
	CMciRecordAndPlayDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMciRecordAndPlayDlg)
	enum { IDD = IDD_MCIRECORDANDPLAY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMciRecordAndPlayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	inline void DisplayErrorMessage(DWORD dwRet);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMciRecordAndPlayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRecordStart();
	afx_msg void OnRecordStop();
	afx_msg void OnRecordClose();
	afx_msg void OnRecordPause();
	afx_msg void OnRecordResume();
	afx_msg void OnRecordSave();
	afx_msg void OnRecordPlay();
	afx_msg void OnRecordPlayStop();
	afx_msg void OnButtonRecordPlayClose();
	afx_msg void OnRecordPlayPause();
	afx_msg void OnRecordPlayResume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	MCIDEVICEID m_mciPlay;
	MCIDEVICEID m_mciDeviceID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCIRECORDANDPLAYDLG_H__658A6371_845A_4DE8_912C_D1BF234558A7__INCLUDED_)
