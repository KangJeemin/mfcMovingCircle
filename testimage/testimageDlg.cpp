
// testimageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "testimage.h"
#include "testimageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestimageDlg 대화 상자



CtestimageDlg::CtestimageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTIMAGE_DIALOG, pParent)
	, m_e3(0)
	, m_e1(0)
	, m_e2(0)
	, m_e4(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestimageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_e3);
	DDX_Text(pDX, IDC_EDIT1, m_e1);
	DDX_Text(pDX, IDC_EDIT2, m_e2);
	DDX_Text(pDX, IDC_EDIT4, m_e4);
}

BEGIN_MESSAGE_MAP(CtestimageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_draw, &CtestimageDlg::OnBnClickeddraw)
	
	ON_BN_CLICKED(IDC_SAVEBTN, &CtestimageDlg::OnBnClickedSavebtn)
	ON_BN_CLICKED(IDC_LOADBTN, &CtestimageDlg::OnBnClickedLoadbtn)
	
	ON_BN_CLICKED(IDC_ACTIONBTN, &CtestimageDlg::OnBnClickedActionbtn)
END_MESSAGE_MAP()


// CtestimageDlg 메시지 처리기

BOOL CtestimageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CtestimageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CtestimageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CtestimageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestimageDlg::OnBnClickeddraw()
{
	int nWidth = 640; // 가로폭
	int nHeight = 480; // 세로폭	
	int nBpp = 8; // gray level
	srand((unsigned)time(NULL)); // 난수 생성을 위한 시드 초기화

	ranRadius = rand() % 100;

	UpdateData(true);
	

	// 이미지 생성
	m_image.Create(nWidth, -nHeight, nBpp); //

	

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits(); //

	

	memset(fm, 0xff, nWidth * nHeight);

	
	drawCircle(fm, m_e1, m_e2, ranRadius, 0);
	UpdateDisplay();

}


CString g_strFIleImage = _T("c:\\image\\save.bmp");
void CtestimageDlg::OnBnClickedSavebtn()
{
	m_image.Save(g_strFIleImage);
}

void CtestimageDlg::OnBnClickedLoadbtn()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}
	CClientDC dc(this);

	CFileDialog dlg(TRUE, _T("bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Bitmap Files (*.bmp)|*.bmp||"));

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		if (m_image)
		{
			m_image.Destroy();
		}

		HRESULT hr = m_image.Load(filePath);

		if (FAILED(hr))
		{
			AfxMessageBox(_T("이미지 로드 실패"));
			return;
		}

		int width = m_image.GetWidth();
		int height = m_image.GetHeight();
		int pitch = m_image.GetPitch();
		unsigned char* bits = (unsigned char*)m_image.GetBits();

		int centerX = 0, centerY = 0;
		int blackPixelCount = 0;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned char pixel = bits[y * pitch + x]; // 8-bit gray pixel
				if (pixel == 0) { // 검은색 픽셀(0값으로 표현됨)
					centerX += x;
					centerY += y;
					blackPixelCount++;
				}
			}
		}

		if (blackPixelCount == 0) {
			AfxMessageBox(_T("검은색 원이 감지되지 않았습니다."));
			return;
		}

		// 중심점 계산
		centerX /= blackPixelCount;
		centerY /= blackPixelCount;

		// 중심에 X 표시
		for (int i = -5; i <= 5; i++) {
			// 그리기 X 방향(대각선 왼쪽 상단에서 오른쪽 하단)
			if (centerX + i >= 0 && centerX + i < width && centerY + i >= 0 && centerY + i < height) {
				bits[(centerY + i) * pitch + (centerX + i)] = 255; // X 표시를 흰색으로 설정
			}

			// 그리기 X 방향(대각선 오른쪽 상단에서 왼쪽 하단)
			if (centerX + i >= 0 && centerX + i < width && centerY - i >= 0 && centerY - i < height) {
				bits[(centerY - i) * pitch + (centerX + i)] = 255; // X 표시를 흰색으로 설정
			}
		}



		CString message;
		message.Format(_T("원 중심 좌표: (%d, %d)"), centerX, centerY);
		AfxMessageBox(message);


		// Show the image with the marked X
		UpdateDisplay();
	}
}




void CtestimageDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0); // 그리기
}

void CtestimageDlg::moveRect()
{
	static double nStartX = m_e1;
	static double nStartY = m_e2;
	int nGray = 0;
	int nWidth = m_image.GetWidth(); // 가로폭
	int nHeight = m_image.GetHeight(); // 세로폭    
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 이동 거리 계산
	double deltaX = (m_e3 - m_e1) / 300.0;
	double deltaY = (m_e4 - m_e2) / 300.0;

	// 경계 조건 검사 전: 새 위치 계산
	double newX = nStartX + deltaX;
	double newY = nStartY + deltaY;

	// 경계 조건 검사: 화면 범위를 벗어나면 이동 중단
	if ((newX - ranRadius < 0 && deltaX < 0) || (newX + ranRadius*2 > nWidth && deltaX > 0) ||
		(newY - ranRadius < 0 && deltaY < 0) || (newY + ranRadius*2 > nHeight && deltaY > 0))
	{
		return; // 이동 중단
	}

	// 이전 화면 초기화
	memset(fm, 0xff, nWidth * nHeight);

	// 새 위치에 원 그리기
	drawCircle(fm, (int)newX, (int)newY, ranRadius, nGray);

	// 현재 위치 갱신
	nStartX = newX;	
	nStartY = newY;

	// 화면 갱신
	UpdateDisplay();
	CString strFile;
	strFile.Format(_T("C:\\image\\image%d.bmp"), nStartX);
	m_image.Save(strFile);
}






void CtestimageDlg::OnBnClickedActionbtn()
{
	for (int i = 0;i < 300;i++) {
		moveRect();
		Sleep(5);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


bool CtestimageDlg::validimgPos(int x,int y)
{
	int nWidth = m_image.GetWidth(); // 가로폭
	int nHeight = m_image.GetHeight(); // 세로폭
	
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x,y));


}

void CtestimageDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		if (j < 0 || j >= m_image.GetHeight()) continue; // 세로 경계 검사

		for (int i = x; i < x + nRadius * 2; i++) {
			if (i < 0 || i >= m_image.GetWidth()) continue; // 가로 경계 검사

			if (inCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}

}

bool CtestimageDlg::inCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) return true;
	return false;
}