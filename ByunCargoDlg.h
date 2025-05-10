// ByunCargoDlg.h : header file
//

#if !defined(AFX_BYUNCARGODLG_H__6D647D64_06EB_481B_966B_D518797FF6BB__INCLUDED_)
#define AFX_BYUNCARGODLG_H__6D647D64_06EB_481B_966B_D518797FF6BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Define.h"
#include "ImageButton.h"

/////////////////////////////////////////////////////////////////////////////
// CByunCargoDlg dialog

class CByunCargoDlg : public CDialog
{
// Construction
public:
	CByunCargoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CByunCargoDlg)
	enum { IDD = IDD_BYUNCARGO_DIALOG };
	CProgressCtrl	m_prgStatus;
	CImageButton	m_btnImageReal;
	CImageButton	m_btnImageGray;
	UINT	m_nBoundary;
	CString	m_strFramePos;
	BOOL	m_bShow;
	UINT	m_nNumOfParticles;
	int		m_nTargetFrame;
	int		m_nRodLength;
	UINT	m_nCropStart;
	UINT	m_nCropEnd;
	BOOL	m_bAreaExclusion;
	BOOL	m_bAreaInclusion;
	BOOL	m_bMultiple;
	CString	m_strPrefixInput;
	CString	m_strPrefixOutput;
	int		m_nInputEnd;
	int		m_nInputStart;
	int		m_nVideoHeight;
	BOOL	m_bFindSingle;
	int		m_nMaxDistance;
	double	m_dIMax;
	double	m_dIMin;
	int		m_nPixelMax;
	int		m_nPixelMin;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CByunCargoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Attributes
public:
	CString		m_strVideoPathName;
	CString		m_strTemplatePathName;
//	CByteArray	m_arrIntensity;
	BYTE		m_byteIntensityGray[RES_X][RES_Y];
	BYTE		m_byteIntensityReal[RES_X][RES_Y];
//	int			m_nNumOfFrames;
	int			m_nCurrFrame;
	BYTE		m_byteTemplate[TEMPLATE_SIZE_MAX][TEMPLATE_SIZE_MAX];
	int			m_nTemplateSize;
//	CPoint		m_ptCargo[FRAME_NUMBER_MAX][PARTICLE_NUMBER_MAX];
	PARTICLE	m_particleArray[FRAME_NUMBER_MAX][PARTICLE_NUMBER_MAX];
//	int			m_nXinFrame;
//	int			m_nYinFrame;
	int			m_nNumOfFrames;
	int			m_nParticleType;
	int			m_nSaveOption;
	int			m_nIdMax;
	CString		m_strMultipleFileDir;
	int			m_nVideoWidth;
	int			m_nCMX;
	int			m_nCMY;
//	int			m_nCurrFile;

// Operations
public:
	void CalcIdOfParticle();
	INERTIA CalcOriOfRod(BYTE byteIntensityReal[][RES_Y], BYTE byteIntensityGray[][RES_Y], int x, int y, double cmx, double cmy);
	FPOINT CalcPosOfRod(BYTE byteIntensityReal[][RES_Y], BYTE byteIntensityGray[][RES_Y], int x, int y);
	double LinearFit(CPoint ptArray[], int nNumber);
	int FindRodInFrame(BYTE byteIntensityReal[][RES_Y], int nFrame, int nFile);
	float CalcOriOfRodWithCargo(BYTE byteIntensityGray[][RES_Y], int x, int y);
	void WriteData(CString strPath);
	void InitializeTemplateArray();
	void InitializeIntensityArray();
	void InitializeParticleArray();
	int FindRodWithCargoInFrame(BYTE byteIntensityReal[][RES_Y], int nFrame);
	int FindParticleInFile(CString strFilePath, int nFile);
	int ReadTemplate();
	void InvalidateFrame();
	int ReadVideo(int nFrame, BOOL bNumOfFrames);
	void UpdateIntensityGray();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CByunCargoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnApply();
	afx_msg void OnBtnPrev();
	afx_msg void OnBtnNext();
	afx_msg void OnBtnOpenTemplate();
	afx_msg void OnChkShow();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnGoto();
	afx_msg void OnBtnFind();
	afx_msg void OnBtnCrop();
	afx_msg void OnRadRod();
	afx_msg void OnRadRodCargo();
	afx_msg void OnBtnOpenVideo();
	afx_msg void OnChkAreaInclusion();
	afx_msg void OnChkAreaExclusion();
	afx_msg void OnBtnClearAllExcludedAreas();
	afx_msg void OnBtnClearLastExcludedArea();
	afx_msg void OnRadSphere();
	afx_msg void OnBtnManualData();
	afx_msg void OnBtnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BYUNCARGODLG_H__6D647D64_06EB_481B_966B_D518797FF6BB__INCLUDED_)
