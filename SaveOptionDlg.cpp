// SaveOptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ByunCargo.h"
#include "SaveOptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SaveOptionDlg dialog

/////////////////////////////////////////////////////////////////////////////
// SaveOptionDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CSaveOptionDlg dialog


CSaveOptionDlg::CSaveOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveOptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveOptionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nSaveOption = SAVE_ALL_WO_MP;
}


void CSaveOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveOptionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveOptionDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveOptionDlg)
	ON_BN_CLICKED(IDC_RAD_SAVE_DIST, OnRadSaveDist)
	ON_BN_CLICKED(IDC_RAD_SAVE_ALL_W_MP, OnRadSaveAllWMp)
	ON_BN_CLICKED(IDC_RAD_SAVE_ALL_WO_MP, OnRadSaveAllWoMp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveOptionDlg message handlers

BOOL CSaveOptionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton* pSaveOption = (CButton*)GetDlgItem(IDC_RAD_SAVE_ALL_WO_MP);
	pSaveOption->SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveOptionDlg::OnRadSaveDist() 
{
	// TODO: Add your control notification handler code here
	m_nSaveOption = SAVE_DIST;
}

void CSaveOptionDlg::OnRadSaveAllWMp() 
{
	// TODO: Add your control notification handler code here
	m_nSaveOption = SAVE_ALL_W_MP;
}

void CSaveOptionDlg::OnRadSaveAllWoMp() 
{
	// TODO: Add your control notification handler code here
	m_nSaveOption = SAVE_ALL_WO_MP;
}
