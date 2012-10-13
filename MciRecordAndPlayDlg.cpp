// MciRecordAndPlayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MciRecordAndPlay.h"
#include "MciRecordAndPlayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMciRecordAndPlayDlg dialog

CMciRecordAndPlayDlg::CMciRecordAndPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMciRecordAndPlayDlg::IDD, pParent)
	, m_mciDeviceID(0)
	, m_mciPlay(0)
{
	//{{AFX_DATA_INIT(CMciRecordAndPlayDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMciRecordAndPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMciRecordAndPlayDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMciRecordAndPlayDlg, CDialog)
	//{{AFX_MSG_MAP(CMciRecordAndPlayDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RECSTART, OnRecordStart)
	ON_BN_CLICKED(IDC_BUTTON_RECSTOP, OnRecordStop)
	ON_BN_CLICKED(IDC_BUTTON_RECCLOSE, OnRecordClose)
	ON_BN_CLICKED(IDC_BUTTON_RECPAUSE, OnRecordPause)
	ON_BN_CLICKED(IDC_BUTTON_RECRESUME, OnRecordResume)
	ON_BN_CLICKED(IDC_BUTTON_RECSAVE, OnRecordSave)
	ON_BN_CLICKED(IDC_BUTTON_RECPLAY, OnRecordPlay)
	ON_BN_CLICKED(IDC_BUTTON_RECPLAYSTOP, OnRecordPlayStop)
	ON_BN_CLICKED(IDC_BUTTON_RECPLAYCLOSE, OnButtonRecordPlayClose)
	ON_BN_CLICKED(IDC_BUTTON_RECPLAYPAUSE, OnRecordPlayPause)
	ON_BN_CLICKED(IDC_BUTTON_RECPLAYRESUME, OnRecordPlayResume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMciRecordAndPlayDlg message handlers

BOOL CMciRecordAndPlayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMciRecordAndPlayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMciRecordAndPlayDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMciRecordAndPlayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMciRecordAndPlayDlg::OnRecordStart() 
{
	/// Open the wave audio device
	MCI_OPEN_PARMS openParams;
	openParams.lpstrDeviceType	= _T("waveaudio");
	openParams.lpstrElementName	= _T("");
	DWORD dwRet = mciSendCommand( NULL, MCI_OPEN,
		MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&openParams );
	if ( dwRet != 0 )	// Error
	{
		DisplayErrorMessage( dwRet );
	} 
	else			// Open succeed
	{
		m_mciDeviceID = openParams.wDeviceID;	// save the device id

		MCI_RECORD_PARMS recordParams;
		recordParams.dwFrom	= 0;
		recordParams.dwTo	= 0;
		dwRet = mciSendCommand( m_mciDeviceID, MCI_RECORD, NULL,(DWORD)(LPVOID)&recordParams );
		DisplayErrorMessage( dwRet );
	}
}

void CMciRecordAndPlayDlg::OnRecordStop() 
{
	if ( m_mciDeviceID == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciDeviceID, MCI_STOP, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
}

void CMciRecordAndPlayDlg::OnRecordClose() 
{
	if ( m_mciDeviceID == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciDeviceID, MCI_CLOSE, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
	m_mciDeviceID = 0;
}

void CMciRecordAndPlayDlg::OnRecordPause() 
{
	if ( m_mciDeviceID == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciDeviceID, MCI_PAUSE, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
}

void CMciRecordAndPlayDlg::OnRecordResume() 
{
	if ( m_mciDeviceID == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciDeviceID, MCI_RESUME, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
}

void CMciRecordAndPlayDlg::DisplayErrorMessage(DWORD dwRet)
{
	if ( dwRet != 0 )	// Error
	{
		TCHAR szError[MAXERRORLENGTH];
		if ( ! mciGetErrorString(dwRet, szError, sizeof(szError) ) )
			_tcscpy( szError, _T("Unknown Error!") );
		AfxMessageBox(szError);
	}
}

void CMciRecordAndPlayDlg::OnRecordSave() 
{
	CFileDialog saveDialog(FALSE, _T("wav"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("声音文件(*.wav)|*.wav"), this );
	if ( saveDialog.DoModal() == IDOK )
	{
		CString fileName = saveDialog.GetPathName();

		MCI_SAVE_PARMS saveParams;
		saveParams.lpfilename	= fileName;
		DWORD dwRet = mciSendCommand(m_mciDeviceID, MCI_SAVE, MCI_SAVE_FILE|MCI_WAIT, (DWORD)(LPMCI_SAVE_PARMS)&saveParams );
		DisplayErrorMessage(dwRet);
		if ( m_mciDeviceID != 0 )
		{
			OnRecordStop();		//stop first
			DWORD dwRet = mciSendCommand(m_mciDeviceID, MCI_CLOSE, MCI_WAIT, NULL );
			DisplayErrorMessage( dwRet );
		}
	}
}

void CMciRecordAndPlayDlg::OnRecordPlay() 
{
	CFileDialog openFileDlg(TRUE,_T("wav"),NULL,OFN_HIDEREADONLY,
		_T("声音文件(*.wav)|*.wav"), this );
	if (openFileDlg.DoModal() != IDOK )
		return;
	CString fileName = openFileDlg.GetPathName();
	MCI_OPEN_PARMS openParams;
	openParams.lpstrDeviceType	= _T("waveaudio");
	openParams.lpstrElementName	= fileName;
	DWORD dwRet = mciSendCommand(NULL,MCI_OPEN,MCI_WAIT|MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,
		(DWORD)(LPVOID)&openParams );
	if ( dwRet != 0 )
		DisplayErrorMessage(dwRet);
	else
	{
		m_mciPlay = openParams.wDeviceID;

		MCI_PLAY_PARMS playParams;
		playParams.dwFrom	= 0;
		playParams.dwTo		= 0;
		dwRet = mciSendCommand(m_mciPlay, MCI_PLAY, MCI_FROM,(DWORD)(LPVOID)&playParams);
		DisplayErrorMessage(dwRet);
	}
}

void CMciRecordAndPlayDlg::OnRecordPlayStop() 
{
	if ( m_mciPlay == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciPlay, MCI_STOP, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
}

void CMciRecordAndPlayDlg::OnButtonRecordPlayClose() 
{
	if ( m_mciPlay == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciPlay, MCI_CLOSE, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
	m_mciPlay = 0;
}

void CMciRecordAndPlayDlg::OnRecordPlayPause() 
{
	if ( m_mciPlay == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciPlay, MCI_PAUSE, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
}

void CMciRecordAndPlayDlg::OnRecordPlayResume() 
{
	if ( m_mciPlay == 0 )
		return;
	DWORD dwRet = mciSendCommand(m_mciPlay, MCI_RESUME, MCI_WAIT, NULL );
	DisplayErrorMessage( dwRet );
}
