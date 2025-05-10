#if !defined(AFX_SAVEOPTIONDLG_H__E87A6C9A_A51A_43C7_A39E_2822BD8EEA9B__INCLUDED_)
#define AFX_SAVEOPTIONDLG_H__E87A6C9A_A51A_43C7_A39E_2822BD8EEA9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Define.h"

// SaveOptionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveOptionDlg dialog

class CSaveOptionDlg : public CDialog
{
// Construction
public:
	CSaveOptionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveOptionDlg)
	enum { IDD = IDD_SAVE_OPTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveOptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Attributes
public:
	int	m_nSaveOption;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveOptionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadSaveDist();
	afx_msg void OnRadSaveAllWMp();
	afx_msg void OnRadSaveAllWoMp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEOPTIONDLG_H__E87A6C9A_A51A_43C7_A39E_2822BD8EEA9B__INCLUDED_)
