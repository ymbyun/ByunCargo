// ImageButton.cpp : implementation file
//

#include "stdafx.h"
#include "ByunCargo.h"
#include "ImageButton.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageButton

CImageButton::CImageButton()
{
//	m_bShow = TRUE;
//	m_nX = -1;
//	m_nY = -1;
	m_ptPoint = CPoint(-1, -1);
//	m_bAreaInclusion = FALSE;
//	m_ptRegionStart = CPoint(1, 1);
//	m_ptRegionEnd = CPoint(RES_X, RES_Y);
	m_rtInclusion = CRect(1, 1, RES_X, RES_Y);
	m_nNumOfBlackPixels = -1;
	m_szParticle = CSize(-1, -1);

	InitializeParticleArray();
	InitializeIntensityArray();
}

CImageButton::~CImageButton()
{
}


BEGIN_MESSAGE_MAP(CImageButton, CButton)
	//{{AFX_MSG_MAP(CImageButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageButton message handlers

void CImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item

	CDC		dc;
	CRect	rcButton;

	dc.Attach(lpDrawItemStruct->hDC);		// Get device context object
	m_rcButton = lpDrawItemStruct->rcItem;	// Get button rect

//	TRACE("Width:%d, Height:%d\n", rcButton.Width(), rcButton.Height());
	
	ShowFrame(lpDrawItemStruct);
	ShowParticle(lpDrawItemStruct);
	ShowInformation(lpDrawItemStruct);
	ShowIncludedArea(lpDrawItemStruct);
	ShowExcludedAreas(lpDrawItemStruct);
	ShowId(lpDrawItemStruct);
/*
	x = rcButton.left + 160 - 5;
	y = rcButton.top + 120 + 60;
	cx = TEMPLATE_WIDTH;
	cy = TEMPLATE_HEIGHT;
	dc.FillSolidRect(x, y, cx, cy, RGB(255, 0, 0));
*/
	dc.Detach();
}

void CImageButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	CString strPoint;
//	strPoint.Format("(%d,%d)", point.x, point.y);
//	AfxMessageBox(strPoint);
//	TRACE("(%d,%d)\n", point.x, point.y);
	if(m_ptPoint.x < 0)
	{
		m_ptPoint = point;
	}
	else
	{
		m_ptPoint = CPoint(-1, -1);
	}

	// Count the number of black pixels in the working area and calculate the size of the particle
	int		i, j;
	int		nXi, nXf, nYi, nYf;
	int		nMinX, nMaxX, nMinY, nMaxY;
	CPoint	ptTopLeft, ptBottomRight;
	ptTopLeft		= m_rtInclusion.TopLeft();
	ptBottomRight	= m_rtInclusion.BottomRight();
	if(m_bGray == TRUE && m_bAreaInclusion == TRUE)
	{
		if(ptBottomRight.x >= 0)
		{
			nXi = ptTopLeft.x;
			nXf = ptBottomRight.x;
			nYi = ptTopLeft.y;
			nYf = ptBottomRight.y;

			nMinX = nXf;
			nMaxX = nXi;
			nMinY = nYf;
			nMaxY = nYi;
			m_nNumOfBlackPixels = 0;
			for(i = nXi; i < nXf; i++)
			{
				for(j = nYi; j < nYf; j++)
				{
					if(m_byteIntensity[i][j] == COLOR_BLACK)
					{
						m_nNumOfBlackPixels++;
						
						if(i > nMaxX)	nMaxX = i;
						if(i < nMinX)	nMinX = i;
						if(j > nMaxY)	nMaxY = j;
						if(j < nMinY)	nMinY = j;
					}
				}
			}

			m_szParticle = CSize(nMaxX - nMinX, nMaxY - nMinY);
		}
	}

	// Add an exclued area to an array
	CRect	rtExclusion;
	int		nLastIndex = -1;
	if(m_bGray == TRUE && m_bAreaExclusion == TRUE)
	{
		for(i = (EXCLUDED_AREAS_MAX - 1); i >= 0; i--)
		{
			rtExclusion = m_rtExclusionArray[i];
			ptTopLeft = rtExclusion.TopLeft();
			ptBottomRight = rtExclusion.BottomRight();

			if(ptTopLeft.x >= 0)
			{
				nLastIndex = i;
				break;
			}
		}

		if(nLastIndex < 0)
			m_rtExclusionArray[0] = CRect(point, CPoint(-1, -1));
		else
		{
			if(ptBottomRight.x < 0)
				m_rtExclusionArray[nLastIndex] = CRect(ptTopLeft, point);
			else
				if(nLastIndex < (EXCLUDED_AREAS_MAX - 1))
					m_rtExclusionArray[nLastIndex + 1] = CRect(point, CPoint(-1, -1));
		}
	}

	CButton::OnLButtonDown(nFlags, point);
}

void CImageButton::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bGray && m_bAreaInclusion)
	{
//		TRACE("(%d,%d)\n", point.x, point.y);
		CPoint ptTopLeft, ptBottomRight;

		ptTopLeft		= m_rtInclusion.TopLeft();
		ptBottomRight	= m_rtInclusion.BottomRight();
		
		if(ptBottomRight.x < 0)
		{
//			m_ptRegionEnd.x = point.x;
//			m_ptRegionEnd.y = point.y;
			
			m_rtInclusion = CRect(ptTopLeft, point);
		}
		else
		{
//			m_ptRegionStart.x = point.x;
//			m_ptRegionStart.y = point.y;

//			m_ptRegionEnd.x = -1;
//			m_ptRegionEnd.y = -1;

			m_rtInclusion = CRect(point, CPoint(-1, -1));
		}
		Invalidate();
	}

	CButton::OnRButtonDown(nFlags, point);
}

void CImageButton::ShowFrame(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		dc;
	CRect	rcButton;
	int		x, y;
	int		cx, cy;
	int		nIntensity;
	int		i, j;

	dc.Attach(lpDrawItemStruct->hDC);		// Get device context object
	rcButton = lpDrawItemStruct->rcItem;	// Get button rect

//	TRACE("Width:%d, Height:%d\n", rcButton.Width(), rcButton.Height());

	// Draw a frame image
	cx = 1;
	cy = 1;
	for(i = 0; i < RES_X; i++)
	{
		for(j = 0; j < RES_Y; j++)
		{
			// Coordinates
			x = rcButton.left + cx * i;
			y = rcButton.top  + cy * j;
			nIntensity = m_byteIntensity[i][j];

			dc.FillSolidRect(x, y, cx, cy, RGB(nIntensity, nIntensity, nIntensity));
		}
	}

	dc.Detach();
}

void CImageButton::ShowParticle(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		dc;
	CRect	rcButton;
	int		x, y;
	int		cx, cy;
	int		dx, dy;
	int		nRx, nRy;
	double	dRx, dRy;
	int		nTempX, nTempY;
	int		i;
	double	dAngRad;
	CPen	myPen, *pOldPen;
	CBrush	myBrush, *pOldBrush;

	dc.Attach(lpDrawItemStruct->hDC);		// Get device context object
	rcButton = lpDrawItemStruct->rcItem;	// Get button rect
	
	myPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	myBrush.CreateSolidBrush(RGB(255, 0, 0));

	pOldPen = dc.SelectObject(&myPen);
	pOldBrush = dc.SelectObject(&myBrush);

	// Show the findings to check to see if they are consistent with real data
	if(m_bShow)
	{
		if(m_nParticleType == TYPE_ROD_CARGO)
		{
			for(i = 0; i < PARTICLE_NUMBER_MAX; i++)
			{
				if(m_particleArray[i].x >= 0.0)
				{
					x = rcButton.left + (int)m_particleArray[i].x;
					y = rcButton.top  + (int)m_particleArray[i].y;
					cx = m_nTemplateSize;
					cy = m_nTemplateSize;
//					dc.FillSolidRect(x, y, cx, cy, RGB(255, 0, 0));
					dc.Ellipse(x, y, x + cx, y + cy);

					dAngRad = PI / 180.0 * (double)m_particleArray[i].angle;
					dx = (int)((double)(m_nTemplateSize + m_nRodLength) * cos(dAngRad));
					dy = (int)((double)(m_nTemplateSize + m_nRodLength) * sin(dAngRad));
					dc.MoveTo(x + cx / 2, y + cy / 2);
					dc.LineTo(x + cx / 2 + dx, y + cy / 2 + dy);	// Caution!
				}
			}
		}
		else if(m_nParticleType == TYPE_ROD)
		{
			for(i = 0; i < PARTICLE_NUMBER_MAX; i++)
			{
				if(m_particleArray[i].x >= 0.0)
				{

					nTempX = (int)m_particleArray[i].x;
					nTempY = (int)m_particleArray[i].y;
					dRx = m_particleArray[i].x - (double)nTempX;
					dRy = m_particleArray[i].y - (double)nTempY;
					if(dRx < 0.5)	nRx = 0;
					else			nRx = 1;
					if(dRy < 0.5)	nRy = 0;
					else			nRy = 1;

					x = rcButton.left + (int)m_particleArray[i].x + nRx;
					y = rcButton.top  + (int)m_particleArray[i].y + nRy;
					dAngRad = PI / 180.0 * (double)m_particleArray[i].angle;
					dx = (int)((double)(m_nRodLength / 2) * cos(dAngRad));
					dy = (int)((double)(m_nRodLength / 2) * sin(dAngRad));
					dc.MoveTo(x + dx, y + dy);	// Caution!
					dc.LineTo(x - dx, y - dy);	// Caution!
				}
			}		
		}
		else if(m_nParticleType == TYPE_SPHERE)
		{
			for(i = 0; i < PARTICLE_NUMBER_MAX; i++)
			{
				if(m_particleArray[i].x >= 0.0)
				{
					x = rcButton.left + (int)m_particleArray[i].x - m_nRodLength / 2;
					y = rcButton.top  + (int)m_particleArray[i].y - m_nRodLength / 2;
					cx = m_nRodLength;
					cy = m_nRodLength;
//					dc.FillSolidRect(x, y, cx, cy, RGB(255, 0, 0));
					dc.Ellipse(x, y, x + cx, y + cy);
				}
			}		
		}
	}

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	myPen.DeleteObject();
	myBrush.DeleteObject();

	dc.Detach();
}

void CImageButton::ShowInformation(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		dc;
	CRect	rcButton;
	int		x, y;
	int		cx, cy;
	CString	strInfo;
	CRect	rcInfo;

	dc.Attach(lpDrawItemStruct->hDC);		// Get device context object
	rcButton = lpDrawItemStruct->rcItem;	// Get button rect

	// Show XY coordinates
	if(m_bAreaExclusion == FALSE && m_ptPoint.x >= 0)
	{
		// Point
		x = rcButton.left + m_ptPoint.x - 1;
		y = rcButton.top  + m_ptPoint.y - 1;
		cx = 3;
		cy = 3;
		dc.FillSolidRect(x, y, cx, cy, RGB(0, 0, 255));

		// Coordinates
		rcInfo = CRect(rcButton.left + 5, rcButton.top + 5, rcButton.left + 200, rcButton.top + 20);
		strInfo.Format("Coordinates: (%d, %d)", m_ptPoint.x, (int)RES_Y - m_ptPoint.y);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(0, 0, 255));
		dc.DrawText(strInfo, rcInfo, DT_LEFT/*|DT_CENTER|DT_VCENTER|*/|DT_SINGLELINE);

		// Number of black pixels in a working region and the size of the particle
		if(m_bGray == TRUE && m_bAreaInclusion == TRUE)
		{
			rcInfo = CRect(rcButton.left + 5, rcButton.top + 25, rcButton.left + 200, rcButton.top + 40);
			strInfo.Format("Number of black pixels: %d", m_nNumOfBlackPixels);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(0, 0, 255));
			dc.DrawText(strInfo, rcInfo, DT_LEFT/*|DT_CENTER|DT_VCENTER|*/|DT_SINGLELINE);

			rcInfo = CRect(rcButton.left + 5, rcButton.top + 45, rcButton.left + 200, rcButton.top + 60);
			strInfo.Format("Size of the particle: %d x %d", m_szParticle.cx, m_szParticle.cy);
			dc.DrawText(strInfo, rcInfo, DT_LEFT/*|DT_CENTER|DT_VCENTER|*/|DT_SINGLELINE);
		}
	}

	dc.Detach();
}

void CImageButton::ShowIncludedArea(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		dc;
	CRect	rcButton;
	int		x, y;
	int		cx, cy;
	CBrush	myBrush, *pOldBrush;
	CPoint	ptTopLeft, ptBottomRight;

	dc.Attach(lpDrawItemStruct->hDC);		// Get device context object
	rcButton = lpDrawItemStruct->rcItem;	// Get button rect

	myBrush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = dc.SelectObject(&myBrush);

	ptTopLeft		= m_rtInclusion.TopLeft();
	ptBottomRight	= m_rtInclusion.BottomRight();

	// Show the working area where particles are supposed to be traced
	if(m_bGray == TRUE && m_bAreaInclusion == TRUE)
	{
		if(ptBottomRight.x >= 0)
			dc.FrameRect(m_rtInclusion, &myBrush);
		else
		{
			x = rcButton.left + ptTopLeft.x - 1;
			y = rcButton.top  + ptTopLeft.y - 1;
			cx = 3;
			cy = 3;
			dc.FillSolidRect(x, y, cx, cy, RGB(255, 0, 0));		
		}
	}

	dc.SelectObject(pOldBrush);
	myBrush.DeleteObject();

	dc.Detach();
}

void CImageButton::InitializeParticleArray()
{
	for(int i = 0; i < PARTICLE_NUMBER_MAX; i++)
	{
		m_particleArray[i].x		= -1.0;
		m_particleArray[i].y		= -1.0;
		m_particleArray[i].angle	= -1.0;
		m_particleArray[i].i_ratio	= -1.0;
//		m_particleArray[i].black	= -1;
//		m_particleArray[i].white	= -1;
		m_particleArray[i].pixel	= -1;
		m_particleArray[i].id		= -1;
	}
}

void CImageButton::InitializeIntensityArray()
{
	for(int i = 0; i < RES_X; i++)
	{
		for(int j = 0; j < RES_Y; j++)
		{
			m_byteIntensity[i][j] = (BYTE)COLOR_BLACK;
		}
	}
}

void CImageButton::InitializeExcludedAreas()
{
	for(int i = 0; i < EXCLUDED_AREAS_MAX; i++)
	{
		m_rtExclusionArray[i] = CRect(-1, -1, -1, -1);
	}
}

void CImageButton::DeleteLastExcludedArea()
{
	CRect	rtExclusion;
	CPoint	ptTopLeft;
	int		nLastIndex = -1;

	for(int i = (EXCLUDED_AREAS_MAX - 1); i >= 0; i--)
	{
		rtExclusion = m_rtExclusionArray[i];
		ptTopLeft = rtExclusion.TopLeft();

		if(ptTopLeft.x >= 0)
		{
			nLastIndex = i;
			break;
		}
	}

	if(nLastIndex >= 0)
		m_rtExclusionArray[nLastIndex] = CRect(-1, -1, -1, -1);
}

void CImageButton::ShowExcludedAreas(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		dc;
	CRect	rcButton;
	int		i;
	int		nIncompleteIndex = -1;
	int		x, y;
	int		cx, cy;
	CBrush	myBrush, *pOldBrush;
	CPoint	ptTopLeft, ptBottomRight;

	dc.Attach(lpDrawItemStruct->hDC);		// Get device context object
	rcButton = lpDrawItemStruct->rcItem;	// Get button rect

	myBrush.CreateSolidBrush(RGB(0, 255, 0));
	pOldBrush = dc.SelectObject(&myBrush);

	// Show areas where particles are not supposed to be traced
	if(m_bGray == TRUE && m_bAreaExclusion == TRUE)
	{
		for(i = 0; i < EXCLUDED_AREAS_MAX; i++)
		{
			dc.FrameRect(m_rtExclusionArray[i], &myBrush);

			ptTopLeft		= m_rtExclusionArray[i].TopLeft();
			ptBottomRight	= m_rtExclusionArray[i].BottomRight();

			if(ptTopLeft.x >= 0 && ptBottomRight.x < 0)
				nIncompleteIndex = i;
		}

		if(nIncompleteIndex >= 0)
		{
			ptTopLeft = m_rtExclusionArray[nIncompleteIndex].TopLeft();
			x = rcButton.left + ptTopLeft.x - 1;
			y = rcButton.top  + ptTopLeft.y - 1;
			cx = 3;
			cy = 3;
			dc.FillSolidRect(x, y, cx, cy, RGB(0, 255, 0));		
		}
	}

	dc.SelectObject(pOldBrush);
	myBrush.DeleteObject();

	dc.Detach();
}

void CImageButton::ShowId(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		dc;
	CRect	rcButton;
	int		x, y;
	int		cx, cy;
	int		i;
	CString	strId;
	CRect	rcId;

	dc.Attach(lpDrawItemStruct->hDC);		// Get device context object
	rcButton = lpDrawItemStruct->rcItem;	// Get button rect
	
	if(m_bShow)
	{
		for(i = 0; i < PARTICLE_NUMBER_MAX; i++)
		{
			if(m_particleArray[i].x >= 0.0)
			{
				x = rcButton.left + (int)m_particleArray[i].x - m_nRodLength / 2;
				y = rcButton.top  + (int)m_particleArray[i].y - m_nRodLength / 2 + m_nRodLength;
				cx = 45;
				cy = 15;

				// Coordinates
				rcId = CRect(x, y, x + cx, y + cy);
				strId.Format("%d (%4.1f)", m_particleArray[i].id, m_particleArray[i].i_ratio);
				dc.SetBkMode(TRANSPARENT);
				dc.SetTextColor(RGB(255, 0, 0));
				dc.DrawText(strId, rcId, DT_LEFT/*|DT_CENTER|DT_VCENTER|*/|DT_SINGLELINE);

			}
		}
	}

	dc.Detach();
}

void CImageButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CRect	rcInval;
	BOOL	bInval = FALSE;
	FILE*	fOut;

	if(m_ptPoint.x >= 0)
	{
		if(nChar == 'D')
		{
			m_ptPoint.x ++;
			bInval = TRUE;
		}
		else if(nChar =='A')
		{
			m_ptPoint.x --;
			bInval = TRUE;		
		}
		else if(nChar =='W')
		{
			m_ptPoint.y --;
			bInval = TRUE;		
		}
		else if(nChar =='S')
		{
			m_ptPoint.y ++;
			bInval = TRUE;		
		}
		else if(nChar =='P')
		{
			if(m_strManualPathName.IsEmpty() == TRUE)
			{
				AfxMessageBox("You have to input the file path by using the Manual tracking... button above.");
			}
			else
			{
				if((fOut = fopen(LPCTSTR(m_strManualPathName), "a")) != NULL)
				{
					fprintf(fOut, "%4d, %3d, %3d\n", m_nCurrFrame, m_ptPoint.x, (int)RES_Y - m_ptPoint.y);
				}
				fclose(fOut);
			}
		}

		if(bInval == TRUE)
		{
			// Invalidate the point
			rcInval = CRect(m_rcButton.left + m_ptPoint.x - 3,
							m_rcButton.top	+ m_ptPoint.y - 3,
							m_rcButton.left + m_ptPoint.x + 3,
							m_rcButton.top	+ m_ptPoint.y + 3);
			InvalidateRect(rcInval);

			// Invalidate the coordinates of the point
			rcInval = CRect(m_rcButton.left + 5,
							m_rcButton.top  + 5,
							m_rcButton.left + 200,
							m_rcButton.top  + 20);
			InvalidateRect(rcInval);
		}
	}

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}
