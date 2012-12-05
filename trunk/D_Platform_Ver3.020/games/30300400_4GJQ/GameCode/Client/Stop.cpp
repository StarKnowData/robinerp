#include "Stdafx.h"
#include "HaveThing.h"
#include "ClientGameDlg.h"
#include ".\Stop.h"

//IMPLEMENT_DYNAMIC(CHaveThing, CAFCBaseDialog)

BEGIN_MESSAGE_MAP(CStop, CGameFaceGo)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/**
 * 构造函数
 */
CStop::CStop(CWnd * pParent) : CGameFaceGo(CStop::IDD)
{
	m_pParnet=pParent;
}

/**
 * 析构函数
 */
CStop::~CStop()
{
}

/**
 * DDX/DDV 支持
 */
void CStop::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

/**
 * 初始化函数
 */
BOOL CStop::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT(".\\image\\ok_bt.bmp"));
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT(".\\image\\cancel_bt.bmp"));
	m_btCancel.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT(".\\image\\msgboxbk.bmp"));
	m_bk.SetLoadInfo(path,true);

	//SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight());
	CenterWindow(GetParent());

	CRect tempRect;
	int iWidth = 0, iHeight = 0;
	m_btCancel.GetClientRect(&tempRect);
	iWidth = tempRect.Width();
	iHeight = tempRect.Height();

	if(m_btOk.GetSafeHwnd())
	{
		m_btOk.MoveWindow(68, 158, iWidth, iHeight, false);
		m_btCancel.MoveWindow(190,158, iWidth, iHeight, false);
	}
	return TRUE;
}

/**
 * 取消函数
 */
void CStop::OnCancel()
{
//	CGameFaceGo::OnClose();
	CGameFaceGo::OnCancel();
}

/**
 * 确定函数
 */
void CStop::OnOK()
{
	m_pParnet = GetParent();
	if(m_pParnet)
		m_pParnet->SendMessage(IDM_STOP_THING,0,0);
	//if(m_pParnet)
	//	::g_pCClientGameDlg->SendMessage(IDM_STOP_THING,0,0);
	CGameFaceGo::OnOK();
}

void CStop::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CGameImageHelper	help(&m_bk);	
	help.BitBlt(dc.GetSafeHdc(),0,0);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));
	dc.SelectObject(&CGameImageLink::m_HFont);
	dc.TextOut(40,55,"如果您认为已方本局的分已拣够，提");
	dc.TextOut(40,75,"出这个请求询问对家意见，若对家也");
	dc.TextOut(40,95,"同意此提议，本局将提前结束");
}

/**
 * 自动调整大小
 */
void CStop::AutoSize()
{	
	CRect rect,clientrect;
	int cx,cy,csx,csy,x,y;
	((CClientGameDlg*)m_pParnet)->m_PlayView.GetClientRect(&rect);
	cx=rect.Width();
	cy=rect.Height();
	csx = (GetSystemMetrics(SM_CXSCREEN)>1024?1024:GetSystemMetrics(SM_CXSCREEN));
	csy = (GetSystemMetrics(SM_CYSCREEN)>768?768:GetSystemMetrics(SM_CYSCREEN));
	GetClientRect(clientrect);	
	x=m_bk.GetWidth();	
	y=m_bk.GetHeight();
	MoveWindow((csx-cx)/2 + (cx-x),(csy-cy)/2 +(cy-y)/2,x,y);
}

void CStop::OnLButtonDown(UINT nFlags,CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}