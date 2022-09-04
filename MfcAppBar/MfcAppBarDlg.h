#pragma once

class CMfcAppBarDlg : public CDialogEx
{
public:
	CMfcAppBarDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPBAR_DIALOG };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	void RegisterAppBar(HWND hWnd);
	void UnRegisterAppBar(HWND hWnd);
public:
	afx_msg void OnDestroy();
};
