// ByunCargo.h : main header file for the BYUNCARGO application
//

#if !defined(AFX_BYUNCARGO_H__42A0308A_65CC_4055_8559_4FA87BF58547__INCLUDED_)
#define AFX_BYUNCARGO_H__42A0308A_65CC_4055_8559_4FA87BF58547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CByunCargoApp:
// See ByunCargo.cpp for the implementation of this class
//

class CByunCargoApp : public CWinApp
{
public:
	CByunCargoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CByunCargoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CByunCargoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BYUNCARGO_H__42A0308A_65CC_4055_8559_4FA87BF58547__INCLUDED_)
