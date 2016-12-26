// ChLP.h : main header file for the CHLP application
//

#if !defined(AFX_CHLP_H__CFB7E39A_F8A0_430F_BBE5_4706C74E4BA9__INCLUDED_)
#define AFX_CHLP_H__CFB7E39A_F8A0_430F_BBE5_4706C74E4BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChLPApp:
// See ChLP.cpp for the implementation of this class
//

class CChLPApp : public CWinApp
{
public:
	CChLPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChLPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CChLPApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHLP_H__CFB7E39A_F8A0_430F_BBE5_4706C74E4BA9__INCLUDED_)
