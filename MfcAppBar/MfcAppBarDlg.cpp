#include "pch.h"
#include "framework.h"
#include "MfcAppBar.h"
#include "MfcAppBarDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMfcAppBarDlg::CMfcAppBarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPBAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcAppBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcAppBarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CMfcAppBarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	int sx = ::GetSystemMetrics(SM_CXSCREEN);
	int sy = ::GetSystemMetrics(SM_CYSCREEN);
	int w = 50, h = sy;
	this->SetWindowPos(&CWnd::wndTopMost, sx - w, 0, w, h, SWP_SHOWWINDOW);

	LONG style = ::GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE);
	style ^= WS_EX_APPWINDOW;
	style |= WS_EX_TOOLWINDOW;
	::SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, style);

	this->RegisterAppBar(this->GetSafeHwnd());

	return TRUE;
}

void CMfcAppBarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	if (this->GetSafeHwnd())
	{
		CDC* pDC = this->GetDC();
		CRect rc;
		this->GetClientRect(rc);
		pDC->FillSolidRect(rc, RGB(0, 0, 0));
		this->ReleaseDC(pDC);
	}
}

HCURSOR CMfcAppBarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMfcAppBarDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	this->UnRegisterAppBar(this->GetSafeHwnd());
}

void CMfcAppBarDlg::RegisterAppBar(HWND hWnd)
{
	APPBARDATA data;
	data.cbSize = sizeof(APPBARDATA);
	data.hWnd = hWnd;
	::SHAppBarMessage(ABM_NEW, &data);

	data.uEdge = ABE_RIGHT;
	::GetWindowRect(hWnd, &data.rc);
	::SHAppBarMessage(ABM_QUERYPOS, &data);
	::SHAppBarMessage(ABM_SETPOS, &data);
}

void CMfcAppBarDlg::UnRegisterAppBar(HWND hWnd)
{
	APPBARDATA data;
	data.cbSize = sizeof(APPBARDATA);
	data.hWnd = hWnd;
	::SHAppBarMessage(ABM_REMOVE, &data);
}
