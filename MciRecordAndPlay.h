// MciRecordAndPlay.h : main header file for the MCIRECORDANDPLAY application
//

#if !defined(AFX_MCIRECORDANDPLAY_H__7DDEC1BD_7789_43CC_902B_94C2D859399A__INCLUDED_)
#define AFX_MCIRECORDANDPLAY_H__7DDEC1BD_7789_43CC_902B_94C2D859399A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMciRecordAndPlayApp:
// See MciRecordAndPlay.cpp for the implementation of this class
//

class CMciRecordAndPlayApp : public CWinApp
{
public:
	CMciRecordAndPlayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMciRecordAndPlayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMciRecordAndPlayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCIRECORDANDPLAY_H__7DDEC1BD_7789_43CC_902B_94C2D859399A__INCLUDED_)
