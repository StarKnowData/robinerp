#include "stdafx.h"
#include "StopMessage.h"
#include "ClientGameDlg.h"
#include ".\stopmessage.h"


BEGIN_MESSAGE_MAP(CStopMessage, CGameFaceGo)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/**
 * 构造函数
 */
CStopMessage::CStopMessage(CWnd * pParent) : CGameFaceGo(CStopMessage::IDD)
{
	m_pParent = pParent;
}

/**
 * 析构函数
 */
CStopMessage::~CStopMessage()
{
}

/**
 * DDX/DDV 支持
 */
void CStopMessage::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

/**
 * 取消函数
 */
void CStopMessage::OnCancel()
{
	m_pParent = GetParent();		
	if(m_pParent)
		m_pParent->SendMessage(IDM_ARGEE_STOP,0,0);
	//if(m_pParent)
	//	::g_pCClientGameDlg->SendMessage(IDM_ARGEE_STOP,0,0);
	CGameFaceGo::OnCancel();
}

/**
 * 确定函数
 */
void CStopMessage::OnOK()
{
	m_pParent = GetParent();
	if(m_pParent)
		m_pParent->SendMessage(IDM_ARGEE_STOP,1,1);
	//if(m_pParent)
	//	::g_pCClientGameDlg->SendMessage(IDM_ARGEE_STOP,1,1);
	CGameFaceGo::OnOK();
}


void CStopMessage::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CGameImageHelper	help(&m_bk);	
	help.BitBlt(dc.GetSafeHdc(),0,0);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.SelectObject(&CGameImageLink::m_HFont);
	dc.TextOut(40,55,"您的对家认为分数已经拣够了，因此");
	dc.TextOut(40,75,"提议提前结束本局，您是否同意？");
}

/**
 * 初始化函数
 */
BOOL CStopMessage::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();

	CGameImage m_bk_Temp;
	HRGN hRgn;

	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT(".\\image\\agree_bt.bmp"));
	m_btOk.LoadButtonBitmap(path,false);
	/*m_bk_Temp.SetLoadInfo(path,true);
	hRgn=AFCBmpToRgn(m_bk_Temp,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btOk.SetWindowRgn(hRgn,true);*/

	wsprintf(path,TEXT(".\\image\\oppose.bmp"));
	m_btCancel.LoadButtonBitmap(path,false);
	/*m_bk_Temp.SetLoadInfo(path,true);
	hRgn=AFCBmpToRgn(m_bk_Temp,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCancel.SetWindowRgn(hRgn,true);*/

	wsprintf(path,TEXT("image\\msgboxbk.bmp"));	
	m_bk.SetLoadInfo(path,true);

	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	//MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight());
	//CenterWindow(GetParent());

	CRect tempRect;
	int iWidth = 0, iHeight = 0;
	m_btCancel.GetClientRect(&tempRect);
	iWidth = tempRect.Width();
	iHeight = tempRect.Height();

	if(m_btOk.GetSafeHwnd())
	{
		m_btOk.MoveWindow(68, 158, iWidth, iHeight, false);
		m_btCancel.MoveWindow(204,158, iWidth, iHeight, false);
	}
	return TRUE;
}

/*
//自动调整大小
void CStopMessage::AutoSize()
{	
	CRect rect,clientrect;
	int cx,cy,csx,csy,x,y;
	((CClientGameDlg*)m_pParent)->m_PlayView.GetClientRect(&rect);
	cx=rect.Width();
	cy=rect.Height();
	csx = (GetSystemMetrics(SM_CXSCREEN)>1024?1024:GetSystemMetrics(SM_CXSCREEN));
	csy = (GetSystemMetrics(SM_CYSCREEN)>768?768:GetSystemMetrics(SM_CYSCREEN));
	GetClientRect(clientrect);
	//x = clientrect.Width();
	x=m_bk.GetWidth();
	//y = clientrect.Height();
	y=m_bk.GetHeight();
	MoveWindow((csx-cx)/2 + (cx-x),(csy-cy)/2 +(cy-y)/2,x,y);
}
*/

/**
 * 自动调整大小
 */
void CStopMessage::AutoSize(int xValue,int yValue)
{
	MoveWindow(xValue,yValue-20,m_bk.GetWidth(),m_bk.GetHeight());
	Invalidate();
	UpdateWindow();
}

void CStopMessage::OnLButtonDown(UINT nFlags,CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}