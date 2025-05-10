#if !defined(AFX_IMAGEBUTTON_H__F2F874D4_6089_4AC7_93D5_1E7EF4A71F63__INCLUDED_)
#define AFX_IMAGEBUTTON_H__F2F874D4_6089_4AC7_93D5_1E7EF4A71F63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageButton.h : header file
//

#include "Define.h"

/////////////////////////////////////////////////////////////////////////////
// CImageButton window

class CImageButton : public CButton
{
// Construction
public:
	CImageButton();

// Attributes
public:
	BYTE		m_byteIntensity[RES_X][RES_Y];
//	CPoint		m_ptCargo[PARTICLE_NUMBER_MAX];
	PARTICLE	m_particleArray[PARTICLE_NUMBER_MAX];
	int			m_nTemplateSize;
	BOOL		m_bShow;
//	int			m_nX;
//	int			m_nY;
	CPoint		m_ptPoint;
	int			m_nRodLength;
	BOOL		m_bAreaInclusion;
//	CPoint		m_ptRegionStart;
//	CPoint		m_ptRegionEnd;
	CRect		m_rtInclusion;
	CRect		m_rtExclusionArray[EXCLUDED_AREAS_MAX];
	BOOL		m_bGray;
	BOOL		m_bAreaExclusion;
	int			m_nParticleType;
	int			m_nNumOfBlackPixels;
	CRect		m_rcButton;
	UINT		m_nCurrFrame;
	CString		m_strManualPathName;
	CSize		m_szParticle;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowId(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DeleteLastExcludedArea();
	void InitializeExcludedAreas();
	void InitializeIntensityArray();
	void InitializeParticleArray();
	void ShowExcludedAreas(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ShowIncludedArea(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ShowInformation(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ShowParticle(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ShowFrame(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CImageButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBUTTON_H__F2F874D4_6089_4AC7_93D5_1E7EF4A71F63__INCLUDED_)
