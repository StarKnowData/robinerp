#include "stdafx.h"
#include "LeaveMessage.h"
#include "ClientGameDlg.h"


BEGIN_MESSAGE_MAP(CLeaveMessage, CGameFaceGo)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

//构造函数
CLeaveMessage::CLeaveMessage() : CGameFaceGo(CLeaveMessage::IDD)
{
	m_pParent=NULL;
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT(".\\image\\%s\\thingmsg.bmp"),SKIN_FOLDER);
	m_bk.SetLoadInfo(path,true);
}

//析构函数
CLeaveMessage::~CLeaveMessage()
{
}

//DDX/DDV 支持
void CLeaveMessage::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

//取消函数
void CLeaveMessage::OnCancel()
{
	m_pParent = GetParent();
	if(m_pParent)
		m_pParent->SendMessage(IDM_ARGEE_LEAVE,0,0);
	CGameFaceGo::OnCancel();
}

//确定函数
void CLeaveMessage::OnOK()
{
	m_pParent = GetParent();
	if(m_pParent)
		m_pParent->SendMessage(IDM_ARGEE_LEAVE,1,1);
	CGameFaceGo::OnOK();
}

//设置信息
void CLeaveMessage::SetLeaveMessage(TCHAR * szMessage, TCHAR * szUserName)
{
//	if (GetSafeHwnd())
//	{
		GetDlgItem(IDC_LEFT_USER)->SetWindowText(szUserName);
		GetDlgItem(IDC_LEAVE_MSG)->SetWindowText(szMessage);
//	}
	return;
}


LRESULT CLeaveMessage::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	//case WM_CTLCOLORSCROLLBAR :
	//case WM_CTLCOLORBTN:
	//case WM_CTLCOLORMSGBOX:
	//case WM_CTLCOLOREDIT:
	//case WM_CTLCOLORLISTBOX:
	//case WM_CTLCOLORDLG:
	case WM_CTLCOLORSTATIC :
		SetTextColor((HDC)wParam, RGB(0,0,0)) ;
		SetBkColor((HDC)wParam, m_bk.GetPixel(50,50));
		return (LRESULT)CreateSolidBrush(m_bk.GetPixel(50,50));
	}
	return __super::WindowProc(message, wParam, lParam);
}

void CLeaveMessage::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper	help(&m_bk);
	help.BitBlt(dc.GetSafeHdc(),0,0);
}


BOOL CLeaveMessage::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\agree_bt.bmp"),SKIN_FOLDER);
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\%s\\oppose.bmp"),SKIN_FOLDER);
	m_btCancel.LoadButtonBitmap(path,false);
	if(m_btOk.GetSafeHwnd())
	{
		GetDlgItem(IDC_LEFT_USER)->MoveWindow(19,47,100,13,false);
		GetDlgItem(IDC_LEAVE_MSG)->MoveWindow(19,67,282,59,false);
		m_btOk.MoveWindow(88,151,46,20,false);
		m_btCancel.MoveWindow(186,151,46,20,false);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CLeaveMessage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	return hbr;
}