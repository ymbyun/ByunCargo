// ByunCargoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ByunCargo.h"
#include "ByunCargoDlg.h"

#include "math.h"
#include "SaveOptionDlg.h"

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
// CByunCargoDlg dialog

CByunCargoDlg::CByunCargoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CByunCargoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CByunCargoDlg)
	m_nBoundary = 170;
	m_strFramePos = _T("");
	m_bShow = TRUE;
	m_nNumOfParticles = 0;
	m_nTargetFrame = 0;
	m_nRodLength = 10;
	m_nCropStart = 0;
	m_nCropEnd = 0;
	m_bAreaExclusion = FALSE;
	m_bAreaInclusion = FALSE;
	m_bMultiple = FALSE;
	m_strPrefixInput = _T("In_");
	m_strPrefixOutput = _T("Out_");
	m_nInputEnd = 10;
	m_nInputStart = 1;
	m_nVideoHeight = 240;
	m_bFindSingle = FALSE;
	m_nMaxDistance = 10;
	m_dIMax = 7.0;
	m_dIMin = 3.5;
	m_nPixelMax = 0;
	m_nPixelMin = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nTemplateSize = 0;
	m_nCurrFrame = 0;
	m_strFramePos = "0/0";
	m_nNumOfFrames = 0;
	m_nParticleType = TYPE_ROD;
	m_nSaveOption = SAVE_ALL_WO_MP;
	m_nIdMax = 0;
	m_strMultipleFileDir = "";

	m_btnImageReal.m_bGray			= FALSE;
	m_btnImageReal.m_bAreaInclusion	= FALSE;
	m_btnImageReal.m_bAreaExclusion	= FALSE;
	m_btnImageReal.m_nParticleType	= TYPE_ROD;

	m_btnImageGray.m_bGray			= TRUE;
	m_btnImageGray.m_bAreaInclusion	= FALSE;
	m_btnImageGray.m_bAreaExclusion	= FALSE;
	m_btnImageGray.m_nParticleType	= TYPE_ROD;

	InitializeParticleArray();
	InitializeIntensityArray();
	InitializeTemplateArray();
}

void CByunCargoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CByunCargoDlg)
	DDX_Control(pDX, IDC_PRG_STATUS, m_prgStatus);
	DDX_Control(pDX, IDC_BTN_IMAGEREAL, m_btnImageReal);
	DDX_Control(pDX, IDC_BTN_IMAGEGRAY, m_btnImageGray);
	DDX_Text(pDX, IDC_EDT_BOUNDARY, m_nBoundary);
	DDV_MinMaxUInt(pDX, m_nBoundary, 0, 255);
	DDX_Text(pDX, IDC_EDT_FRAMEPOS, m_strFramePos);
	DDX_Check(pDX, IDC_CHK_SHOW, m_bShow);
	DDX_Text(pDX, IDC_EDT_NUMOFCARGOES, m_nNumOfParticles);
	DDX_Text(pDX, IDC_EDT_TARGETFRAME, m_nTargetFrame);
	DDX_Text(pDX, IDC_EDT_RODLENGTH, m_nRodLength);
	DDX_Text(pDX, IDC_EDT_CROP_START, m_nCropStart);
	DDX_Text(pDX, IDC_EDT_CROP_END, m_nCropEnd);
	DDX_Check(pDX, IDC_CHK_AREA_EXCLUSION, m_bAreaExclusion);
	DDX_Check(pDX, IDC_CHK_AREA_INCLUSION, m_bAreaInclusion);
	DDX_Check(pDX, IDC_CHK_MULTIPLE, m_bMultiple);
	DDX_Text(pDX, IDC_EDT_PREFIX_INPUT, m_strPrefixInput);
	DDX_Text(pDX, IDC_EDT_PREFIX_OUTPUT, m_strPrefixOutput);
	DDX_Text(pDX, IDC_EDT_INPUT_END, m_nInputEnd);
	DDX_Text(pDX, IDC_EDT_INPUT_START, m_nInputStart);
	DDX_Text(pDX, IDC_EDT_VIDEOHEIGHT, m_nVideoHeight);
	DDX_Check(pDX, IDC_CHK_FIND_SINGLE, m_bFindSingle);
	DDX_Text(pDX, IDC_EDT_MAX_DISTANCE, m_nMaxDistance);
	DDX_Text(pDX, IDC_EDT_I_MAX, m_dIMax);
	DDX_Text(pDX, IDC_EDT_I_MIN, m_dIMin);
	DDX_Text(pDX, IDC_EDT_PIXEL_MAX, m_nPixelMax);
	DDX_Text(pDX, IDC_EDT_PIXEL_MIN, m_nPixelMin);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CByunCargoDlg, CDialog)
	//{{AFX_MSG_MAP(CByunCargoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_APPLY, OnBtnApply)
	ON_BN_CLICKED(IDC_BTN_PREV, OnBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, OnBtnNext)
	ON_BN_CLICKED(IDC_BTN_OPEN_TEMPLATE, OnBtnOpenTemplate)
	ON_BN_CLICKED(IDC_CHK_SHOW, OnChkShow)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_GOTO, OnBtnGoto)
	ON_BN_CLICKED(IDC_BTN_FIND, OnBtnFind)
	ON_BN_CLICKED(IDC_BTN_CROP, OnBtnCrop)
	ON_BN_CLICKED(IDC_RAD_ROD, OnRadRod)
	ON_BN_CLICKED(IDC_RAD_ROD_CARGO, OnRadRodCargo)
	ON_BN_CLICKED(IDC_BTN_OPEN_VIDEO, OnBtnOpenVideo)
	ON_BN_CLICKED(IDC_CHK_AREA_INCLUSION, OnChkAreaInclusion)
	ON_BN_CLICKED(IDC_CHK_AREA_EXCLUSION, OnChkAreaExclusion)
	ON_BN_CLICKED(IDC_BTN_CLEAR_ALL_EXCLUDED_AREAS, OnBtnClearAllExcludedAreas)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LAST_EXCLUDED_AREA, OnBtnClearLastExcludedArea)
	ON_BN_CLICKED(IDC_RAD_SPHERE, OnRadSphere)
	ON_BN_CLICKED(IDC_BTN_MANUAL_DATA, OnBtnManualData)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CByunCargoDlg message handlers

BOOL CByunCargoDlg::OnInitDialog()
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
	CButton* pParticleType = (CButton*)GetDlgItem(IDC_RAD_ROD);
	pParticleType->SetCheck(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CByunCargoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CByunCargoDlg::OnPaint() 
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
HCURSOR CByunCargoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CByunCargoDlg::OnBtnApply() 
{
	// TODO: Add your control notification handler code here
	int	nHeightOld;
	int	nHeightNew;
	
	nHeightOld = m_nVideoHeight;
	UpdateData(TRUE);				// For the boundary and height
	nHeightNew = m_nVideoHeight;

//	TRACE("Old:%d, New:%d\n", nHeightOld, nHeightNew);

	if(nHeightNew != nHeightOld)
	{
		InitializeParticleArray();
		InitializeIntensityArray();

		m_nCurrFrame = 1;
		m_nNumOfFrames = ReadVideo(1, TRUE);
		m_strFramePos.Format("%d/%d", m_nCurrFrame, m_nNumOfFrames);
		m_nCropStart = 1;
		m_nCropEnd = m_nNumOfFrames;

		UpdateData(FALSE);	
	}

	InvalidateFrame();
/*
	UpdateIntensityGray();
	for(int i = 0; i < RES_X; i++)
	{
		for(int j = 0; j < RES_Y; j++)
		{
			m_btnImageGray.m_byteIntensity[i][j] = m_byteIntensityGray[i][j];
		}
	}
	m_btnImageReal.m_nRodLength = m_nRodLength;
	m_btnImageGray.m_nRodLength = m_nRodLength;

	m_btnImageReal.Invalidate();
	m_btnImageGray.Invalidate();
*/
/*
	FindParticleInFile();
	InvalidateFrame();
*/
//	CString strTemp;
//	strTemp.Format("%d", m_nBoundary);
//	AfxMessageBox(strTemp);
}

void CByunCargoDlg::UpdateIntensityGray()
{
	for(int i = 0; i < RES_X; i++)
	{
		for(int j = 0; j < RES_Y; j++)
		{
			if(m_byteIntensityReal[i][j] <= (BYTE)m_nBoundary)
				m_byteIntensityGray[i][j] = COLOR_BLACK;
			else
				m_byteIntensityGray[i][j] = COLOR_WHITE;
		}
	}
}

void CByunCargoDlg::OnBtnPrev() 
{
	// TODO: Add your control notification handler code here
	if(m_nCurrFrame <= 1)
		return;

	m_nCurrFrame--;
	ReadVideo(m_nCurrFrame, FALSE);

	m_strFramePos.Format("%d/%d", m_nCurrFrame, m_nNumOfFrames);
	UpdateData(FALSE);		// For the number of frames

	InvalidateFrame();
}

void CByunCargoDlg::OnBtnNext() 
{
	// TODO: Add your control notification handler code here
	if(m_nCurrFrame >= m_nNumOfFrames)
		return;

	m_nCurrFrame++;
	ReadVideo(m_nCurrFrame, FALSE);

	m_strFramePos.Format("%d/%d", m_nCurrFrame, m_nNumOfFrames);
	UpdateData(FALSE);		// For the number of frames

	InvalidateFrame();	
}


int CByunCargoDlg::ReadVideo(int nFrame, BOOL bNumOfFrames)
{
	FILE*		fIn;
	char		szLine[RES_X*5];	// Why not 4? I don't know. :-(
	char*		p;
	int			nX = 1;
	int			nY = 1;
	int			nLine = 1;
	CWaitCursor	waitCursor;   // display wait cursor

	if((fIn = fopen(LPCTSTR(m_strVideoPathName), "r")) != NULL)
	{
		while(!feof(fIn))
		{
			fgets(szLine, sizeof(szLine), fIn);

			if(nLine > m_nVideoHeight * (nFrame-1) && nLine <= m_nVideoHeight * nFrame)
			{
				nX = 2;
				nY = nLine - m_nVideoHeight * (nFrame-1);
				p = strtok(szLine, ",");
				m_byteIntensityReal[0][nY-1] = (BYTE)atoi(p);
				while((p = strtok(NULL, ",")) != NULL)
				{
					m_byteIntensityReal[nX-1][nY-1] = (BYTE)atoi(p);
					nX++;
				}

				if(nLine == 1  && bNumOfFrames == TRUE)
					m_nVideoWidth = nX - 1;
			}

			nLine++;

			if(bNumOfFrames == FALSE && nY >= m_nVideoHeight)
				break;
		}

		fclose(fIn);
		UpdateIntensityGray();
	}

	if(bNumOfFrames == TRUE)
		return (nLine / m_nVideoHeight);
	else
		return -1;
}

void CByunCargoDlg::InvalidateFrame()
{
	int i, j;
	int nParticles = 0;

	// Frame
	UpdateIntensityGray();
	for(i = 0; i < RES_X; i++)
	{
		for(j = 0; j < RES_Y; j++)
		{
			m_btnImageReal.m_byteIntensity[i][j] = m_byteIntensityReal[i][j];
			m_btnImageGray.m_byteIntensity[i][j] = m_byteIntensityGray[i][j];
		}
	}

	// Particle
	for(i = 0; i < PARTICLE_NUMBER_MAX; i++)
	{
		m_btnImageReal.m_particleArray[i].x			= m_particleArray[m_nCurrFrame-1][i].x;
		m_btnImageReal.m_particleArray[i].y			= m_particleArray[m_nCurrFrame-1][i].y;
		m_btnImageReal.m_particleArray[i].angle		= m_particleArray[m_nCurrFrame-1][i].angle;
		m_btnImageReal.m_particleArray[i].i_ratio	= m_particleArray[m_nCurrFrame-1][i].i_ratio;
		m_btnImageReal.m_particleArray[i].id		= m_particleArray[m_nCurrFrame-1][i].id;

		m_btnImageGray.m_particleArray[i].x			= m_particleArray[m_nCurrFrame-1][i].x;
		m_btnImageGray.m_particleArray[i].y			= m_particleArray[m_nCurrFrame-1][i].y;
		m_btnImageGray.m_particleArray[i].angle		= m_particleArray[m_nCurrFrame-1][i].angle;
		m_btnImageGray.m_particleArray[i].i_ratio	= m_particleArray[m_nCurrFrame-1][i].i_ratio;
		m_btnImageGray.m_particleArray[i].id		= m_particleArray[m_nCurrFrame-1][i].id;
	}

	// Template size
	m_btnImageReal.m_nTemplateSize = m_nTemplateSize;
	m_btnImageGray.m_nTemplateSize = m_nTemplateSize;

	// Rod length
	m_btnImageReal.m_nRodLength = m_nRodLength;
	m_btnImageGray.m_nRodLength = m_nRodLength;

	// Current frame
	m_btnImageReal.m_nCurrFrame = m_nCurrFrame;
	m_btnImageGray.m_nCurrFrame = m_nCurrFrame;

	// Redraw a frame
	m_btnImageReal.Invalidate();
	m_btnImageGray.Invalidate();

	// The number of particles in a frame
	for(i = 0; i < PARTICLE_NUMBER_MAX; i++)
	{
		if(m_particleArray[m_nCurrFrame-1][i].x >= 0.0)
			nParticles++;
	}
	m_nNumOfParticles = nParticles;
	UpdateData(FALSE);
}

void CByunCargoDlg::OnBtnOpenTemplate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szFilter[] = _T("Text Files (*.txt)|*.txt||");
	CFileDialog dlg(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter);

//	dlg.m_ofn.lpstrTitle = _T("Open file...");
	if(dlg.DoModal() == IDOK)
	{
		InitializeTemplateArray();

		m_strTemplatePathName = dlg.GetPathName();
		m_nTemplateSize = ReadTemplate();
	}
}

int CByunCargoDlg::ReadTemplate()
{
	FILE*		fIn;
	char		szLine[TEMPLATE_SIZE_MAX*4];
	char*		p;
	int			nX = 1;
	int			nY = 1;
	int			nTemplateSize = 0;
	CWaitCursor	waitCursor;   // display wait cursor

	if((fIn = fopen(LPCTSTR(m_strTemplatePathName), "r")) != NULL)
	{
		while(!feof(fIn))
		{
			fgets(szLine, sizeof(szLine), fIn);

			nX = 2;
			p = strtok(szLine, ",");
			m_byteTemplate[0][nY-1] = (BYTE)atoi(p);
			while((p = strtok(NULL, ",")) != NULL)
			{
				m_byteTemplate[nX-1][nY-1] = (BYTE)atoi(p);
				nX++;
			}

			if(nY == 1)
				nTemplateSize = nX-1;

			nY++;
		}

		fclose(fIn);
	}

	return nTemplateSize;
/*
	CString strTemplate;
	CString strNumber;

	for(int i = 0; i < TEMPLATE_SIZE_MAX; i++)
	{
		for(int j = 0; j < TEMPLATE_SIZE_MAX; j++)
		{
			strNumber.Format("%d,", (int)m_byteTemplate[i][j]);
			strTemplate += strNumber;
		}
		strTemplate += CString("\n");
	}

	AfxMessageBox(strTemplate);
*/
}

int CByunCargoDlg::FindParticleInFile(CString strFilePath, int nFile)
{
	FILE*		fIn;
	char		szLine[RES_X*5];	// Why not 4? I don't know. :-(
	char*		p;
	int			nX = 1;
	int			nY = 1;
	int			nLine = 1;
	int			nFrame = 1;
	int			nCoincidence = 0;
	BYTE		byteIntensityReal[RES_X][RES_Y];
	CWaitCursor	waitCursor;			// display wait cursor
	int			i, j;

	// Initialize the particle array
	InitializeParticleArray();

	// Fill the intensity array with black
	for(i = 0; i < RES_X; i++)
	{
		for(j = 0; j < RES_Y; j++)
		{
			byteIntensityReal[i][j] = 0;	// Black
		}
	}

	// Open a video file
	if((fIn = fopen(LPCTSTR(strFilePath), "r")) != NULL)
	{
		m_prgStatus.SetRange((short)0, (short)m_nNumOfFrames);

		while(!feof(fIn))
		{
			// Read a file line by line
			fgets(szLine, sizeof(szLine), fIn);

			nFrame = (nLine - 1) / m_nVideoHeight + 1;		// Fixed a small bug
			nX = 2;
			nY = nLine - m_nVideoHeight * (nFrame-1);
			p = strtok(szLine, ",");
			byteIntensityReal[0][nY-1] = (BYTE)atoi(p);
			while((p = strtok(NULL, ",")) != NULL)
			{
				byteIntensityReal[nX-1][nY-1] = (BYTE)atoi(p);
				nX++;
			}
			nLine++;

			// Find particles in a complete frame
			if((nLine % m_nVideoHeight) == 0)
			{
				if(nFrame >= m_nCurrFrame)
				{
					if(m_nParticleType == TYPE_ROD_CARGO)
						FindRodWithCargoInFrame(byteIntensityReal, nFrame);
					else if(m_nParticleType == TYPE_ROD)
						FindRodInFrame(byteIntensityReal, nFrame, nFile);
					else if(m_nParticleType == TYPE_SPHERE)
						FindRodInFrame(byteIntensityReal, nFrame, nFile);

					m_prgStatus.SetPos(nLine / m_nVideoHeight);

					// Fill the intensity array with black
					for(i = 0; i < RES_X; i++)
					{
						for(j = 0; j < RES_Y; j++)
						{
							byteIntensityReal[i][j] = 0;	// Black
						}
					}
				}
			}
		}

		fclose(fIn);
	}

	// Give each particle its own ID
	CalcIdOfParticle();

	// The number of frames in a video file
	return (nLine / m_nVideoHeight);
}

int CByunCargoDlg::FindRodWithCargoInFrame(BYTE byteIntensityReal[][RES_Y], int nFrame)
{
	int		i, j, k, l;
	int		nParticle = 0;
	int		nBlack = 0;
	int		nWhite = 0;
	double	dDistance;
	BOOL	bOverlap;
	BYTE	byteIntensityGray[RES_X][RES_Y];
	int		nXi, nXf, nYi, nYf;
	CPoint	ptTopLeft, ptBottomRight;

	// Real (0 ~ 255) => black or white
	for(i = 0; i < RES_X; i++)
	{
		for(j = 0; j < RES_Y; j++)
		{
			if(byteIntensityReal[i][j] <= (BYTE)m_nBoundary)
				byteIntensityGray[i][j] = INTENSITY_BLACK;
			else
				byteIntensityGray[i][j] = INTENSITY_WHITE;
		}
	}

	// Compare a retangular region in a frame with a template
	if(m_bAreaInclusion)
	{
/*
		nXi = m_btnImageGray.m_ptRegionStart.x;
		nXf = m_btnImageGray.m_ptRegionEnd.x - m_nRodLength;
		nYi = m_btnImageGray.m_ptRegionStart.y;
		nYf = m_btnImageGray.m_ptRegionEnd.y - m_nRodLength;
*/
		ptTopLeft		= m_btnImageGray.m_rtInclusion.TopLeft();
		ptBottomRight	= m_btnImageGray.m_rtInclusion.BottomRight();

		nXi = ptTopLeft.x;
		nXf = ptBottomRight.x - m_nRodLength;
		nYi = ptTopLeft.y;
		nYf = ptBottomRight.y - m_nRodLength;
	}
	else
	{
		nXi = (int)m_nRodLength;
		nXf = (int)(RES_X - m_nRodLength);
		nYi = (int)m_nRodLength;
		nYf = (int)(RES_Y - m_nRodLength);
	}
	for(i = nXi; i < nXf; i++)
	{
		for(j = nYi; j < nYf; j++)
		{
			// Count the number of coincidence in black and white
			nBlack = 0;
			nWhite = 0;
			for(k = 0; k < m_nTemplateSize; k++)
			{
				for(l = 0; l < m_nTemplateSize; l++)
				{
					if(byteIntensityGray[i+k][j+l] == m_byteTemplate[k][l])
					{
						if		(byteIntensityGray[i+k][j+l] == INTENSITY_BLACK)	nBlack++;
						else if	(byteIntensityGray[i+k][j+l] == INTENSITY_WHITE)	nWhite++;
					}
				}
			}
			
			// Decide whether to add the cargo to the array or not
//			if(nBlack >= (int)m_nNumOfBlack && nWhite >= (int)m_nNumOfWhite)
			if(nBlack >= m_nPixelMin && nBlack <= m_nPixelMax)
			{
				// Check if a new cargo overlaps with an old one
				bOverlap = FALSE;
				for(k = 0; k < nParticle; k++)
				{
					dDistance = sqrt(pow(i - m_particleArray[nFrame-1][k].x, 2.0) + pow(j - m_particleArray[nFrame-1][k].y, 2.0));
					if(dDistance <= (double)m_nTemplateSize)
					{
						bOverlap = TRUE;
//						if((nBlack + nWhite) > (m_particleArray[nFrame-1][k].black + m_particleArray[nFrame-1][k].white))
						if(nBlack > m_particleArray[nFrame-1][k].pixel)
						{
							// Replace an old cargo with a new one
							m_particleArray[nFrame-1][k].x		= (float)i;
							m_particleArray[nFrame-1][k].y		= (float)j;
//							m_particleArray[nFrame-1][k].black	= (short)nBlack;
//							m_particleArray[nFrame-1][k].white	= (short)nWhite;
							m_particleArray[nFrame-1][k].pixel	= (short)nBlack;
							m_particleArray[nFrame-1][k].angle	= CalcOriOfRodWithCargo(byteIntensityGray, i, j);
						}
						break;
					}
				}

				// No overlap => Add the cargo to the end of the array
				if(bOverlap == FALSE)
				{
					m_particleArray[nFrame-1][nParticle].x		= (float)i;
					m_particleArray[nFrame-1][nParticle].y		= (float)j;
//					m_particleArray[nFrame-1][nParticle].black	= (short)nBlack;
//					m_particleArray[nFrame-1][nParticle].white	= (short)nWhite;
					m_particleArray[nFrame-1][nParticle].pixel	= (short)nBlack;
					m_particleArray[nFrame-1][nParticle].angle	= CalcOriOfRodWithCargo(byteIntensityGray, i, j);

					nParticle++;
				}
			}
		}
	}

	return nParticle;
}

void CByunCargoDlg::OnChkShow() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_btnImageReal.m_bShow = m_bShow;
	m_btnImageGray.m_bShow = m_bShow;

	m_btnImageReal.Invalidate();
	m_btnImageGray.Invalidate();
}

void CByunCargoDlg::InitializeParticleArray()
{
	for(int i = 0; i < FRAME_NUMBER_MAX; i++)
	{
		for(int j = 0; j < PARTICLE_NUMBER_MAX; j++)
		{
			m_particleArray[i][j].x			= -1.0;
			m_particleArray[i][j].y			= -1.0;
			m_particleArray[i][j].angle		= -1.0;
			m_particleArray[i][j].i_ratio	= -1.0;
//			m_particleArray[i][j].black		= -1;
//			m_particleArray[i][j].white		= -1;
			m_particleArray[i][j].pixel		= -1;
			m_particleArray[i][j].id		= -1;
		}
	}
}

void CByunCargoDlg::InitializeIntensityArray()
{
	for(int i = 0; i < RES_X; i++)
	{
		for(int j = 0; j < RES_Y; j++)
		{
			m_byteIntensityReal[i][j] = (BYTE)COLOR_BLACK;
			m_byteIntensityGray[i][j] = (BYTE)COLOR_BLACK;
		}
	}
}

void CByunCargoDlg::InitializeTemplateArray()
{
	for(int i = 0; i < TEMPLATE_SIZE_MAX; i++)
	{
		for(int j = 0; j < TEMPLATE_SIZE_MAX; j++)
		{
			m_byteTemplate[i][j] = (BYTE)9;
		}
	}
}


void CByunCargoDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	char			szFilter[] = _T("Text Files (*.txt)|*.txt||");
	CFileDialog		dlgFile(FALSE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter);
	CString			strPath;
	CSaveOptionDlg	dlgSaveOption;

	dlgSaveOption.DoModal();
	m_nSaveOption = dlgSaveOption.m_nSaveOption;

//	dlg.m_ofn.lpstrTitle = _T("Open file...");
	if(dlgFile.DoModal() == IDOK)
	{
		strPath = dlgFile.GetPathName();
		WriteData(strPath);
	}
}

void CByunCargoDlg::WriteData(CString strPath)
{
	FILE*		fOut;
	int			i, j, k;
	float		fX, fY;
	int			nNumOfPartAtAng[180];
	float		fAngle;
	float		fIratio;
	CWaitCursor	waitCursor;   // display wait cursor

//	if(m_particleArray[0][0].x < 0)
//		return;

	if((fOut = fopen(LPCTSTR(strPath), "w")) != NULL)
	{
		if(m_nSaveOption == SAVE_ALL_W_MP)
		{
//			fprintf(fOut, "Particle, Frame, X, Y, Angle\n");

			for(i = 0; i < PARTICLE_NUMBER_MAX; i++)
			{
				for(j = 0; j < (int)m_nNumOfFrames; j++)
				{
					if(m_nParticleType == TYPE_ROD_CARGO)
					{
						fX		= (m_particleArray[j][i].x + (float)m_nTemplateSize / 2) * (float)PIXEL_X;
						fY		= ((float)RES_Y - (m_particleArray[j][i].y + (float)m_nTemplateSize / 2)) * (float)PIXEL_Y;
						fAngle	= (float)360.0 - m_particleArray[j][i].angle;
					}
					else if(m_nParticleType == TYPE_ROD)
					{
						fX		= (m_particleArray[j][i].x) * (float)PIXEL_X;
						fY		= ((float)RES_Y - m_particleArray[j][i].y) * (float)PIXEL_Y;
						fAngle	= (float)180.0 - m_particleArray[j][i].angle;
					}
					else if(m_nParticleType == TYPE_SPHERE)
					{
						fX		= (m_particleArray[j][i].x) * (float)PIXEL_X;
						fY		= ((float)RES_Y - m_particleArray[j][i].y) * (float)PIXEL_Y;
						fAngle	= 0.0;
					}

					fIratio = m_particleArray[j][i].i_ratio;
					fprintf(fOut, "%3d %4d %14.8f %14.8f %14.8f %14.8f\n", i+1, j+1, fX, fY, fIratio, fAngle);
				}

				if(m_particleArray[0][i+1].x < 0.0)
					break;
			}
		}
		else if(m_nSaveOption == SAVE_ALL_WO_MP)
		{
//			PARTICLE m_particleArray[FRAME_NUMBER_MAX][PARTICLE_NUMBER_MAX];
//			fprintf(fOut, "Particle, Frame, X, Y, Angle\n");

			for(i = 1; i <= m_nIdMax; i++)
			{
				for(j = 0; j < (int)m_nNumOfFrames; j++)
				{
					for(k = 0; k < PARTICLE_NUMBER_MAX; k++)
					{
						if(m_particleArray[j][k].x < 0.0)
							break;

						if(m_particleArray[j][k].id == i)
						{
							if(m_nParticleType == TYPE_ROD_CARGO)
							{
								fX		= (m_particleArray[j][k].x + (float)m_nTemplateSize / 2) * (float)PIXEL_X;
								fY		= ((float)m_nVideoHeight - (m_particleArray[j][k].y + (float)m_nTemplateSize / 2)) * (float)PIXEL_Y;
								fAngle	= (float)360.0 - m_particleArray[j][k].angle;
							}
							else if(m_nParticleType == TYPE_ROD)
							{
								fX		= (m_particleArray[j][k].x) * (float)PIXEL_X;
								fY		= ((float)m_nVideoHeight - m_particleArray[j][k].y) * (float)PIXEL_Y;
								fAngle	= (float)180.0 - m_particleArray[j][k].angle;
							}
							else if(m_nParticleType == TYPE_SPHERE)
							{
								fX		= (m_particleArray[j][k].x) * (float)PIXEL_X;
								fY		= ((float)m_nVideoHeight - m_particleArray[j][k].y) * (float)PIXEL_Y;
								fAngle	= 0.0;
							}

							fIratio = m_particleArray[j][k].i_ratio;
							fprintf(fOut, "%3d %4d %14.8f %14.8f %14.8f %14.8f\n", i, j+1, fX, fY, fIratio, fAngle);

							break;
						}
					}
				}
			}
		}
		else if(m_nSaveOption == SAVE_DIST)
		{
			for(i = 0; i < 180; i++)
				nNumOfPartAtAng[i] = 0;

			for(i = 0; i < (int)m_nNumOfFrames; i++)
			{
				for(j = 0; j < PARTICLE_NUMBER_MAX; j++)
				{
					fAngle = m_particleArray[i][j].angle;

					if(fAngle < 0.0)
						break;
					else
						nNumOfPartAtAng[(int)fAngle]++;
				}
			}

			fprintf(fOut, "Angle, # of Particles\n");
			for(i = 91; i < 180; i++)
				fprintf(fOut, "%4d, %6d\n", i - 180, nNumOfPartAtAng[i]);
			for(i = 0; i <= 90; i++)
				fprintf(fOut, "%4d, %6d\n", i, nNumOfPartAtAng[i]);
		}

		fclose(fOut);
	}
}

// (x, y) = top-left corner point
float CByunCargoDlg::CalcOriOfRodWithCargo(BYTE byteIntensityGray[][RES_Y], int x, int y)
{
	int		i, j;
	int		nMinX, nMaxX;
	int		nMinY, nMaxY;
	CPoint	ptRod[ROD_LENGTH_MAX*5];
	double	dAngRad, dAngDeg;
	int		nNumberOfPoints = 0;
	double	dMeanX, dMeanY;
	int		nSumX, nSumY;

	nMinX = x - m_nRodLength;
	nMaxX = x + m_nTemplateSize + m_nRodLength;
	nMinY = y - m_nRodLength;
	nMaxY = y + m_nTemplateSize + m_nRodLength;

	if(nMinX < 0)		nMinX = 0;
	if(nMaxX > RES_X)	nMaxX = RES_X;
	if(nMinY < 0)		nMinY = 0;
	if(nMaxY > RES_Y)	nMaxY = RES_Y;

	// Initialize a rod array
	for(i = 0; i < ROD_LENGTH_MAX*5; i++)
	{
		ptRod[i] = CPoint(-1, -1);
	}

	// Find rod pixels
	for(i = nMinX; i < nMaxX; i++)
	{
		for(j = nMinY; j < nMaxY; j++)
		{
			// This part needs to be corrected due to the points at four corners
			if((i >= (x-1) && i <= (x + m_nTemplateSize)) && (j >= (y-1) && j <= (y + m_nTemplateSize)))
				;
			else
			{
				if(byteIntensityGray[i][j] == INTENSITY_BLACK)
				{
					ptRod[nNumberOfPoints] = CPoint(i, j);
					nNumberOfPoints++;
				}
			}
		}
	}

	// In case no rod is found
	if(nNumberOfPoints == 0)
		return -1.0;

	// Find the orientation of the rod
	nSumX = 0;
	nSumY = 0;
	for(i = 0; i < ROD_LENGTH_MAX*5; i++)
	{
		if(ptRod[i].x >= 0)
		{
			nSumX += ptRod[i].x - (x + m_nTemplateSize/2);
			nSumY += ptRod[i].y - (y + m_nTemplateSize/2);
		}
	}	
	dMeanX = (double)nSumX / (double)nNumberOfPoints;
	dMeanY = (double)nSumY / (double)nNumberOfPoints;
	dAngRad = atan2(dMeanY, dMeanX);		// Caution!
	if(dAngRad >= 0.0)
		dAngDeg = dAngRad * 180.0 / PI;
	else
		dAngDeg = (2.0 * PI + dAngRad) * 180.0 / PI;

	// I got it!
	return (float)dAngDeg;	// 0.0 ~ 360.0
}

void CByunCargoDlg::OnBtnGoto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);				// For the target frame

	if(m_nTargetFrame < 0 || m_nTargetFrame > m_nNumOfFrames)
	{
		AfxMessageBox("Are you kidding?");
		return;
	}

	m_nCurrFrame = m_nTargetFrame;
	ReadVideo(m_nCurrFrame, FALSE);

	m_strFramePos.Format("%d/%d", m_nCurrFrame, m_nNumOfFrames);
	UpdateData(FALSE);		// For the position of the frame
	
	InvalidateFrame();
}

void CByunCargoDlg::OnBtnFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);				// For the boundary, the rod length and many more

	if(m_bFindSingle == TRUE && m_bAreaInclusion == FALSE)
	{
		AfxMessageBox("In order to track a sinlge particle, you should set a region in which the particle is.");
	}
	else
	{
		if(m_bMultiple == TRUE)
		{
			int		i;
			CString strNumber;
			CString strInputFilePath;
			CString strOutputFilePath;

			for(i = m_nInputStart; i <= m_nInputEnd; i++)
			{
				if(i <= 9)						strNumber.Format("00%d", i);
				else if(i >= 10 && i <= 99)		strNumber.Format("0%d", i);
				else							strNumber.Format("%d", i);

				strInputFilePath.Format( "%s\\%s%s.txt", m_strMultipleFileDir, m_strPrefixInput,  strNumber);
				strOutputFilePath.Format("%s\\%s%s.txt", m_strMultipleFileDir, m_strPrefixOutput, strNumber);

				FindParticleInFile(strInputFilePath, i);
				
				WriteData(strOutputFilePath);
			}
		}
		else
		{
			FindParticleInFile(m_strVideoPathName, 0);
			InvalidateFrame();
		}
	}
}

void CByunCargoDlg::OnBtnCrop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

//	CString strTemp;
//	strTemp.Format("%d, %d", m_nCropStart, m_nCropEnd);
//	AfxMessageBox(strTemp);

	char szFilter[] = _T("Text Files (*.txt)|*.txt||");
	CFileDialog dlg(FALSE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter);

//	dlg.m_ofn.lpstrTitle = _T("Open file...");
	if(dlg.DoModal() == IDOK)
	{
		FILE*		fIn;
		FILE*		fOut;
		char		szLine[RES_X*5];	// Why not 4? I don't know. :-(
		int			nLine = 1;
		int			nFrame = 1;
		CWaitCursor	waitCursor;   // display wait cursor

		// Open a cargo file to write
		fOut = fopen(LPCTSTR(dlg.GetPathName()), "w");
		if(fOut == NULL) return;

		// Open a cargo file to read
		if((fIn = fopen(LPCTSTR(m_strVideoPathName), "r")) != NULL)
		{
			while(!feof(fIn))
			{
				// Read a file line by line
				fgets(szLine, sizeof(szLine), fIn);
//				nFrame = (nLine - 1) / RES_Y + 1;
				nFrame = (nLine - 1) / m_nVideoHeight + 1;
				nLine++;

				// Write a file
				if(nFrame >= (int)m_nCropStart && nFrame <= (int)m_nCropEnd)
				{
					fputs(szLine, fOut);
				}
			}

			fclose(fIn);
		}

		fclose(fOut);
	}	
}



int CByunCargoDlg::FindRodInFrame(BYTE byteIntensityReal[][RES_Y], int nFrame, int nFile)
{
	int		i, j, k, l;
	int		nRod = 0;
	int		nBlack = 0;
	int		nWhite = 0;
	double	dDistance;
	BOOL	bOverlap;
	BYTE	byteIntensityGray[RES_X][RES_Y];
	int		nXi, nXf, nYi, nYf;
	FPOINT	fptCenter;
	INERTIA	mI;
	CPoint	ptTopLeft, ptBottomRight;
	BOOL	bKeepGoing, bTemp;
	BOOL	bGoodParticle;
//	int		nCMX, nCMY;

	// Real (0 ~ 255) => black or white
	for(i = 0; i < RES_X; i++)
	{
		for(j = 0; j < RES_Y; j++)
		{
			if(byteIntensityReal[i][j] <= (BYTE)m_nBoundary)
				byteIntensityGray[i][j] = INTENSITY_BLACK;
			else
				byteIntensityGray[i][j] = INTENSITY_WHITE;
		}
	}

	// Try to find a rod in a square region
	if(m_bFindSingle == TRUE)
	{
		if(m_bMultiple == TRUE)
		{
			if((nFile == m_nInputStart) && (nFrame == m_nCurrFrame))
			{
				ptTopLeft		= m_btnImageGray.m_rtInclusion.TopLeft();
				ptBottomRight	= m_btnImageGray.m_rtInclusion.BottomRight();

				nXi = ptTopLeft.x;
				nXf = ptBottomRight.x - m_nRodLength;
				nYi = ptTopLeft.y;
				nYf = ptBottomRight.y - m_nRodLength;			
			}
			else
			{
				nXi = m_nCMX - m_nRodLength / 2 - m_nMaxDistance;
				nXf = m_nCMX + m_nRodLength / 2 + m_nMaxDistance;
				nYi = m_nCMY - m_nRodLength / 2 - m_nMaxDistance;
				nYf = m_nCMY + m_nRodLength / 2 + m_nMaxDistance;
			}
		}
		else
		{
			if(nFrame == m_nCurrFrame)
			{
				ptTopLeft		= m_btnImageGray.m_rtInclusion.TopLeft();
				ptBottomRight	= m_btnImageGray.m_rtInclusion.BottomRight();

				nXi = ptTopLeft.x;
				nXf = ptBottomRight.x - m_nRodLength;
				nYi = ptTopLeft.y;
				nYf = ptBottomRight.y - m_nRodLength;
			}
			else
			{
				nXi = m_nCMX - m_nRodLength / 2 - m_nMaxDistance;
				nXf = m_nCMX + m_nRodLength / 2 + m_nMaxDistance;
				nYi = m_nCMY - m_nRodLength / 2 - m_nMaxDistance;
				nYf = m_nCMY + m_nRodLength / 2 + m_nMaxDistance;
			}
		}

		if(nXi < 0)									nXi = 0;
		if(nXf > (m_nVideoWidth	 - m_nRodLength))	nXf = m_nVideoWidth  - m_nRodLength;
		if(nYi < 0)									nYi = 0;
		if(nYf > (m_nVideoHeight - m_nRodLength))	nYf = m_nVideoHeight - m_nRodLength;
	}
	else	// Find multiple particles at the same time
	{
		if(m_bAreaInclusion == TRUE)
		{
			ptTopLeft		= m_btnImageGray.m_rtInclusion.TopLeft();
			ptBottomRight	= m_btnImageGray.m_rtInclusion.BottomRight();

			nXi = ptTopLeft.x;
			nXf = ptBottomRight.x - m_nRodLength;
			nYi = ptTopLeft.y;
			nYf = ptBottomRight.y - m_nRodLength;
		}
		else
		{
			nXi = (int)0;
			nXf = (int)(m_nVideoWidth  - m_nRodLength);
			nYi = (int)0;
			nYf = (int)(m_nVideoHeight - m_nRodLength);
		}		
	}

	for(i = nXi; i < nXf; i++)
	{
		for(j = nYi; j < nYf; j++)
		{
			// Check if we have to skip a point (i, j)
			bKeepGoing = TRUE;
			if(m_bAreaExclusion)
			{
				for(k = 0; k < EXCLUDED_AREAS_MAX; k++)
				{
					bTemp = m_btnImageGray.m_rtExclusionArray[k].PtInRect(CPoint(i, j));
					if(bTemp == TRUE)
					{
						bKeepGoing = FALSE;
						break;
					}
				}
			}

			if(bKeepGoing == TRUE)
			{
				// Count the number of black and white pixels in a circle
				nBlack = 0;
				nWhite = 0;
				for(k = 0; k < m_nRodLength; k++)
				{
					for(l = 0; l < m_nRodLength; l++)
					{
//						dDistance = sqrt(pow((double)k - (double)m_nRodLength / 2.0, 2.0) + pow((double)l - (double)m_nRodLength / 2.0, 2.0));

//						if(dDistance <= (double)m_nRodLength / 2.0)
//						{
							if		(byteIntensityGray[i+k][j+l] == INTENSITY_BLACK)	nBlack++;
							else if	(byteIntensityGray[i+k][j+l] == INTENSITY_WHITE)	nWhite++;
//						}
					}
				}

//				TRACE("frame:%4d, i:%4d, j:%4d, B:%4d, W:%4d\n", nFrame, i, j, nBlack, nWhite);

				// Decide whether to add the particle to the array or not
//				if(nBlack >= m_nNumOfBlack && nWhite >= m_nNumOfWhite)
				if(nBlack >= m_nPixelMin && nBlack <= m_nPixelMax)
				{
					// Check if a new particle overlaps with an old one					
					fptCenter	= CalcPosOfRod(byteIntensityReal, byteIntensityGray, i, j);
					mI			= CalcOriOfRod(byteIntensityReal, byteIntensityGray, i, j, fptCenter.x, fptCenter.y);

					bGoodParticle = TRUE;

//					if( fptCenter.x < m_nRodLength * 1 || fptCenter.x > (m_nVideoWidth	- m_nRodLength * 1) ||
//						fptCenter.y < m_nRodLength * 1 || fptCenter.y > (m_nVideoHeight - m_nRodLength * 1) )
//						bGoodParticle = FALSE;

					if(m_nParticleType == TYPE_ROD)
					{
//						if(mI.i_ratio < m_dIMin || mI.i_ratio > m_dIMax)
//							bGoodParticle = FALSE;

						if(m_bFindSingle == TRUE)
						{
							if(mI.i_ratio < m_dIMin || mI.i_ratio > m_dIMax)
								bGoodParticle = FALSE;

							if(nFrame > m_nCurrFrame)
							{
								dDistance = sqrt(pow(fptCenter.x - (double)m_nCMX, 2.0) + pow(fptCenter.y - (double)m_nCMY, 2.0));
								if(dDistance > (double)m_nMaxDistance)
									bGoodParticle = FALSE;
							}
						}

//						if(byteIntensityGray[(int)fptCenter.x][(int)fptCenter.y] == INTENSITY_WHITE)
//							bGoodParticle = FALSE;
					}

					if(bGoodParticle == TRUE)
					{
						bOverlap = FALSE;
						for(k = 0; k < PARTICLE_NUMBER_MAX; k++)
						{
							if(m_particleArray[nFrame-1][k].x > 0.0)
							{
								dDistance = sqrt(pow(fptCenter.x - m_particleArray[nFrame-1][k].x, 2.0) + pow(fptCenter.y - m_particleArray[nFrame-1][k].y, 2.0));
								if(dDistance <= (double)m_nRodLength)
								{
									bOverlap = TRUE;
									if((short)nBlack >= m_particleArray[nFrame-1][k].pixel)
									{
										// Replace an old particle with a new one
										m_particleArray[nFrame-1][k].x			= fptCenter.x;
										m_particleArray[nFrame-1][k].y			= fptCenter.y;
//										m_particleArray[nFrame-1][k].black		= (short)nBlack;
//										m_particleArray[nFrame-1][k].white		= (short)nWhite;
										m_particleArray[nFrame-1][k].pixel		= (short)nBlack;
										m_particleArray[nFrame-1][k].angle		= mI.angle;
										m_particleArray[nFrame-1][k].i_ratio	= mI.i_ratio;

										m_nCMX = (int)fptCenter.x;
										m_nCMY = (int)fptCenter.y;
									}
								}
							}
						}

						// No overlap => Add the particle to the end of the array
						if(bOverlap == FALSE)
						{
							m_particleArray[nFrame-1][nRod].x		= fptCenter.x;
							m_particleArray[nFrame-1][nRod].y		= fptCenter.y;
//							m_particleArray[nFrame-1][nRod].black	= (short)nBlack;
//							m_particleArray[nFrame-1][nRod].white	= (short)nWhite;
							m_particleArray[nFrame-1][nRod].pixel	= (short)nBlack;
							m_particleArray[nFrame-1][nRod].angle	= mI.angle;
							m_particleArray[nFrame-1][nRod].i_ratio	= mI.i_ratio;

							m_nCMX = (int)fptCenter.x;
							m_nCMY = (int)fptCenter.y;

							nRod++;
						}
					}	// bGoodParticle
				}
			} // bKeepGoing
		}
	}

	return nRod;
}

void CByunCargoDlg::OnRadRod() 
{
	// TODO: Add your control notification handler code here
	m_nParticleType = TYPE_ROD;

	m_btnImageReal.m_nParticleType = TYPE_ROD;
	m_btnImageGray.m_nParticleType = TYPE_ROD;
}

void CByunCargoDlg::OnRadRodCargo() 
{
	// TODO: Add your control notification handler code here
	m_nParticleType = TYPE_ROD_CARGO;

	m_btnImageReal.m_nParticleType = TYPE_ROD_CARGO;
	m_btnImageGray.m_nParticleType = TYPE_ROD_CARGO;	
}


// Find the slope of the best fit line. Now, I don't use this any more.
double CByunCargoDlg::LinearFit(CPoint ptArray[], int nNumber)
{
	int i = 0;
	int nSumX = 0;
	int nSumY = 0;
	double dMeanX = 0.0;
	double dMeanY = 0.0;
	double dSx = 0.0;
	double dSy = 0.0;
	double dSxy = 0.0;

	// Find sums
	for(i = 0; i < nNumber; i++)
	{
		nSumX += ptArray[i].x;
		nSumY += ptArray[i].y;
	}

	// Find mean values
	dMeanX = nSumX / (double)nNumber;
	dMeanY = nSumY / (double)nNumber;

	// Find Sx, Sy, Sxy
	for(i = 0; i < nNumber; i++)
	{
		dSx		+= ((double)ptArray[i].x - dMeanX) * ((double)ptArray[i].x - dMeanX);
		dSy		+= ((double)ptArray[i].y - dMeanY) * ((double)ptArray[i].y - dMeanY);
		dSxy	+= ((double)ptArray[i].x - dMeanX) * ((double)ptArray[i].y - dMeanY);
	}

	return dSxy / dSx;
}

// (x, y) = top left corner point
FPOINT CByunCargoDlg::CalcPosOfRod(BYTE byteIntensityReal[][RES_Y], BYTE byteIntensityGray[][RES_Y], int x, int y)
{
	int		i, j;
	int		nXi, nXf, nYi, nYf;
	int		nNumberOfPoints;
	CPoint	ptRod[ROD_LENGTH_MAX*ROD_LENGTH_MAX];
	int		nMass[ROD_LENGTH_MAX*ROD_LENGTH_MAX];
	double	dSumMX, dSumMY;		// Sum of mass x coordinates
	double	dSumM;				// Sum of mass
//	float	fCMX, fCMY;			// Center of mass
	FPOINT	fptCM;
//	double	dDistance;

	nXi = x;
	nXf = x + m_nRodLength;
	nYi = y;
	nYf = y + m_nRodLength;

	// This should not happen.
	if(nXi < 0)		nXi = 0;
	if(nXf > RES_X)	nXf = RES_X;
	if(nYi < 0)		nYi = 0;
	if(nYf > RES_Y)	nYf = RES_Y;

	// Initialize the rod and mass arrays
	for(i = 0; i < ROD_LENGTH_MAX*ROD_LENGTH_MAX; i++)
	{
		ptRod[i] = CPoint(-1, -1);
		nMass[i] = 0;
	}

	// Find rod points
	nNumberOfPoints = 0;
	for(i = nXi; i < nXf; i++)
	{
		for(j = nYi; j < nYf; j++)
		{
//			dDistance = sqrt(pow((double)i - ((double)nXi + (double)m_nRodLength / 2.0), 2.0) + pow((double)j - ((double)nYi + (double)m_nRodLength / 2.0), 2.0));

//			if(dDistance <= (double)m_nRodLength / 2.0)
//			{
				if(byteIntensityGray[i][j] == INTENSITY_BLACK)
				{
					ptRod[nNumberOfPoints] = CPoint(i, j);
					nMass[nNumberOfPoints] = (255 - byteIntensityReal[i][j]) - (255 - m_nBoundary) + 1;

					nNumberOfPoints++;
				}
//			}
		}
	}

	// In case no rod point is found
	if(nNumberOfPoints == 0)
	{
		fptCM.x = -1.0;
		fptCM.y = -1.0;
		return fptCM;
	}

	// Calculate the mean value of the rod points
	dSumMX = dSumMY	= dSumM	= 0.0;
	for(i = 0; i < nNumberOfPoints; i++)
	{
		dSumMX	+= (double)(nMass[i] * ptRod[i].x);
		dSumMY	+= (double)(nMass[i] * ptRod[i].y);
		dSumM	+= (double)(nMass[i]);
	}	
	fptCM.x = (float)(dSumMX / dSumM);
	fptCM.y = (float)(dSumMY / dSumM);

	return fptCM;
}

// (x, y) = the top left of the box
// (cmx, cmy) = the center of mass of a rod
INERTIA CByunCargoDlg::CalcOriOfRod(BYTE byteIntensityReal[][RES_Y], BYTE byteIntensityGray[][RES_Y], int x, int y, double cmx, double cmy)
{
	int		i, j;
	int		nXi, nXf, nYi, nYf;
	int		nNumberOfPoints = 0;
	CPoint	ptRod[ROD_LENGTH_MAX*ROD_LENGTH_MAX];
//	FPOINT	ptRod[ROD_LENGTH_MAX*ROD_LENGTH_MAX];
	int		nMass[ROD_LENGTH_MAX*ROD_LENGTH_MAX];
	double	dSlope;
	double	dAngRad, dAngDeg;
	double	Ixx, Ixy, Iyy, I1, I2;
	double	a, b, c;
	INERTIA	mI;
//	double	dDistance;

	// Set up the working region.
	nXi = x;
	nXf = x + m_nRodLength;
	nYi = y;
	nYf = y + m_nRodLength;
//	nXi = (int)(x - (float)m_nRodLength / 2.0) - 1;
//	nXf = (int)(x + (float)m_nRodLength / 2.0) + 1;
//	nYi = (int)(y - (float)m_nRodLength / 2.0) - 1;
//	nYf = (int)(y + (float)m_nRodLength / 2.0) + 1;

	// This should not happen.
	if(nXi < 0)		nXi = 0;
	if(nXf > RES_X)	nXf = RES_X;
	if(nYi < 0)		nYi = 0;
	if(nYf > RES_Y)	nYf = RES_Y;

	// Initialize the rod and mass arrays
	for(i = 0; i < ROD_LENGTH_MAX*ROD_LENGTH_MAX; i++)
	{
		ptRod[i] = CPoint(-1, -1);
//		ptRod[i] = -1.0;
//		ptRod[i] = -1.0;
		nMass[i] = 0;
	}

	// Find rod points
	for(i = nXi; i < nXf; i++)
	{
		for(j = nYi; j < nYf; j++)
		{
//			dDistance = sqrt(pow((double)i - cmx, 2.0) + pow((double)j - cmy, 2.0));

//			if(dDistance <= (double)m_nRodLength / 2.0)
//			{
				if(byteIntensityGray[i][j] == INTENSITY_BLACK)
				{
					ptRod[nNumberOfPoints] = CPoint(i, j);
					nMass[nNumberOfPoints] = (255 - byteIntensityReal[i][j]) - (255 - m_nBoundary) + 1;

					nNumberOfPoints++;
				}
//			}
		}
	}

	// In case no rod point is found
	if(nNumberOfPoints == 0)
	{
		mI.angle	= -1.0;
		mI.i_ratio	= -1.0;

		return mI;
	}

	// Find the principal axis of rotation
	Ixx = Ixy = Iyy = 0.0;
	for(i = 0; i < nNumberOfPoints; i++)
	{
		Ixx += (double)nMass[i] * pow(((double)ptRod[i].y - cmy) * ((double)PIXEL_X), 2.0);
		Ixy += (double)nMass[i] * ((double)ptRod[i].x - cmx) * ((double)ptRod[i].y - cmy) * ((double)PIXEL_X) * ((double)PIXEL_Y) * (-1.0);
		Iyy += (double)nMass[i] * pow(((double)ptRod[i].x - cmx) * ((double)PIXEL_Y), 2.0);
	}
	a	= 1.0;
	b	= -(Ixx + Iyy);
	c	= Ixx * Iyy - Ixy * Ixy;
	I1	= (-1.0 * b + sqrt(pow(b, 2.0) - 4.0 * a * c)) / (2.0 * a);
	I2	= (-1.0 * b - sqrt(pow(b, 2.0) - 4.0 * a * c)) / (2.0 * a);

	// Convert the slope to the angle
	if(Ixy == 0.0)
	{
		if(Ixx == I2)	dAngDeg = 0.0;
		if(Iyy == I2)	dAngDeg = 90.0;
	}
	else
	{
		dSlope = (I2 - Ixx) / Ixy;			// Caution!
		dAngRad = atan2(dSlope, 1.0);		// Caution!
		if(dAngRad >= 0.0)
			dAngDeg = dAngRad * 180.0 / PI;
		else
			dAngDeg = (1.0 * PI + dAngRad) * 180.0 / PI;
	}

	mI.angle	= (float)dAngDeg;								// 0.0 ~ 180.0
	mI.i_ratio	= (float)(I1 / I2);

//	TRACE("I - Ixx:%f, Ixy:%f\n", I - Ixx, Ixy);
//	TRACE("I1:%f, I2:%f, (I1-I2)/(I1+I2)*2:%f\n", I1, I2, fabs((I1-I2)/(I1+I2)*2.0));
//	TRACE("I1:%10.2f\tI2:%10.2f\tI2/I1:%10.2f%10.2f%10.2f\n", I1, I2, I2 / I1, (I1-Ixx)/Ixy, Ixy/(I1-Iyy));

	return mI;
}

void CByunCargoDlg::OnBtnOpenVideo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szFilter[] = _T("Text Files (*.txt)|*.txt||");
	CFileDialog dlg(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter);

//	dlg.m_ofn.lpstrTitle = _T("Open file...");
	if(dlg.DoModal() == IDOK)
	{
		InitializeParticleArray();
		InitializeIntensityArray();

		m_strVideoPathName = dlg.GetPathName();
		m_nCurrFrame = 1;
//		ReadVideo(1, FALSE);
//		m_nNumOfFrames = FindParticleInFile();
		m_nNumOfFrames = ReadVideo(1, TRUE);
//		m_nNumOfFrames = FindParticleInFile();
		m_strFramePos.Format("%d/%d", m_nCurrFrame, m_nNumOfFrames);
		m_nCropStart = 1;
		m_nCropEnd = m_nNumOfFrames;

		UpdateData(FALSE);
		InvalidateFrame();
	}
}


void CByunCargoDlg::OnChkAreaInclusion() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_btnImageGray.m_bAreaInclusion = m_bAreaInclusion;
	m_btnImageGray.Invalidate();
}

void CByunCargoDlg::OnChkAreaExclusion() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_btnImageGray.m_bAreaExclusion = m_bAreaExclusion;
	m_btnImageGray.Invalidate();
}

void CByunCargoDlg::OnBtnClearAllExcludedAreas() 
{
	// TODO: Add your control notification handler code here
	m_btnImageGray.InitializeExcludedAreas();
	m_btnImageGray.Invalidate();	
}

void CByunCargoDlg::OnBtnClearLastExcludedArea() 
{
	// TODO: Add your control notification handler code here
	m_btnImageGray.DeleteLastExcludedArea();
	m_btnImageGray.Invalidate();	
}

void CByunCargoDlg::OnRadSphere() 
{
	// TODO: Add your control notification handler code here
	m_nParticleType = TYPE_SPHERE;

	m_btnImageReal.m_nParticleType = TYPE_SPHERE;
	m_btnImageGray.m_nParticleType = TYPE_SPHERE;	
}

void CByunCargoDlg::CalcIdOfParticle()
{
	int		i, j, k;
	int		nIdMax = 1;
	int		nIdTemp;
	double	dX1, dY1, dX2, dY2;
	double	dDistance;
	double	dDistanceMin;

//	PARTICLE m_particleArray[FRAME_NUMBER_MAX][PARTICLE_NUMBER_MAX];
	for(i = 0; i < (int)m_nNumOfFrames; i++)
	{
		for(j = 0; j < PARTICLE_NUMBER_MAX; j++)
		{
			if(m_particleArray[i][j].x > 0.0)
			{
				if(i == 0)
				{
					m_particleArray[i][j].id = nIdMax;
					nIdMax++;
				}
				else
				{
					nIdTemp = -1;
					dDistanceMin = 10000.0;
					dX1 = m_particleArray[i][j].x;
					dY1 = m_particleArray[i][j].y;

					for(k = 0; k < PARTICLE_NUMBER_MAX; k++)
					{
						dX2 = m_particleArray[i-1][k].x;
						dY2 = m_particleArray[i-1][k].y;

						if(dX2 > 0.0)
						{
							dDistance = sqrt(pow(dX1 - dX2, 2.0) + pow(dY1 - dY2, 2.0));
							if(dDistance < dDistanceMin)
							{
								nIdTemp = m_particleArray[i-1][k].id;
								dDistanceMin = dDistance;
							}
						}
					}

					if(nIdTemp < 0)
					{
						m_particleArray[i][j].id = nIdMax;
						nIdMax++;
					}
					else
					{
						if(dDistanceMin > (double)m_nRodLength * (double)PARTICLE_DIST_MAX)
						{
							m_particleArray[i][j].id = nIdMax;
							nIdMax++;
						}
						else
						{
							m_particleArray[i][j].id = nIdTemp;
						}
					}
				}
			}
		}
	}

	m_nIdMax = nIdMax;
}



void CByunCargoDlg::OnBtnManualData() 
{
	// TODO: Add your control notification handler code here
	char szFilter[] = _T("Text Files (*.txt)|*.txt||");
	CFileDialog dlg(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter);

//	dlg.m_ofn.lpstrTitle = _T("Open file...");
	if(dlg.DoModal() == IDOK)
	{
		m_btnImageReal.m_strManualPathName = dlg.GetPathName();
		m_btnImageGray.m_strManualPathName = dlg.GetPathName();
	}	
}

void CByunCargoDlg::OnBtnBrowse() 
{
	// TODO: Add your control notification handler code here
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = _T("Pick a Directory");
    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
    if ( pidl != 0 )
    {
        // get the name of the folder
        TCHAR path[MAX_PATH];
        if ( SHGetPathFromIDList ( pidl, path ) )
        {
//            _tprintf ( _T("Selected Folder: %s\n"), path );
			m_strMultipleFileDir = path;
        }

        // free memory used
        IMalloc * imalloc = 0;
        if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
        {
            imalloc->Free ( pidl );
            imalloc->Release ( );
        }
    }
	
}
