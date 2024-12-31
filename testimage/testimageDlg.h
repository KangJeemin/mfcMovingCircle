
// testimageDlg.h: 헤더 파일
//

#pragma once


// CtestimageDlg 대화 상자
class CtestimageDlg : public CDialogEx
{
private:
	CImage m_image;
	bool validimgPos(int x, int y);
	int ranRadius;

// 생성입니다.
public:
	CtestimageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickeddraw();
	
	afx_msg void OnBnClickedSavebtn();
	afx_msg void OnBnClickedLoadbtn();
	void UpdateDisplay();
	void moveRect();
	void drawCircle(unsigned char* fm, int i,int j, int nRadius, int nGray);
	bool inCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	
	afx_msg void OnBnClickedActionbtn();
	double m_e3;
	double m_e1;
	double m_e2;
	double m_e4;
};
