#include "stdafx.h"
#include "LeaveMessage.h"
#include "ClientGameDlg.h"


BEGIN_MESSAGE_MAP(CLeaveMessage, CGameFaceGo)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/**
 * 构造函数
 */
CLeaveMessage::CLeaveMessage() : CGameFaceGo(CLeaveMessage::IDD)
{
	m_pParent=NULL;
}

/**
 * 析构函数
 */
CLeaveMessage::~CLeaveMessage()
{
}

/**
 * 初始化函数
 */
BOOL CLeaveMessage::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	
	TCHAR path[MAX_PATH];
	wsprintf(path,TEXT(".\\image\\thingmsg.bmp"));
	m_bk.SetLoadInfo(path,true);


	CGameImage imgTemp;
	HRGN hRgn = NULL;

	CGameImageHelper imgHelper(&m_bk);
	hRgn=AFCBmpToRgn(imgHelper,m_bk.GetPixel(0,0),RGB(1,1,1));
	if (hRgn!=NULL)
	{
		SetWindowRgn(hRgn,TRUE);
	}


	//SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	//CenterWindow(GetParent());
	MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight());
	
	wsprintf(path,TEXT("image\\agree_bt.bmp"));
	m_btOk.LoadButtonBitmap(path,false);
/*   
	imgTemp.SetLoadInfo(path,true);
	hRgn=AFCBmpToRgn(imgTemp,m_bk.GetPixel(0,0),RGB(1,1,1));
	if (hRgn!=NULL)
	{
		SetWindowRgn(hRgn,TRUE);
	}
*/

	wsprintf(path,TEXT("image\\oppose.bmp"));
	m_btCancel.LoadButtonBitmap(path,false);
	/*imgTemp.SetLoadInfo(path,true);
	
	hRgn=AFCBmpToRgn(imgTemp,m_bk.GetPixel(0,0),RGB(1,1,1));
	if (hRgn!=NULL)
	{
		SetWindowRgn(hRgn,TRUE);
	}
*/
	if(m_btOk.GetSafeHwnd())
	{
		GetDlgItem(IDC_LEFT_USER)->MoveWindow(19,47,100,13,false);
		GetDlgItem(IDC_LEAVE_MSG)->MoveWindow(19,67,282,59,false);
		m_btOk.MoveWindow(88,151,46,20,false);
		m_btCancel.MoveWindow(186,151,46,20,false);
	}
	return TRUE;
}

/**
 * DDX/DDV 支持
 */
void CLeaveMessage::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
//	DDX_Control(pDX, IDC_LEFT_USER, m_Name);
}

void CLeaveMessage::OnPaint() 
{
	CPaintDC dc(this);

	CRect ClientRect;
	GetClientRect(&ClientRect);
	int x=20;
	int y=30;
	
	CGameImageHelper	help(&m_bk);
	help.BitBlt(dc.GetSafeHdc(),0,0);
	/*CDC srcDC;
	srcDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBmp = srcDC.SelectObject(help);
	::TransparentBlt(dc.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),
		srcDC.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),srcDC.GetPixel(0,0));
	srcDC.SelectObject(pOldBmp);*/

	CRect rect;
	TCHAR sz[100];
	CFont Font;
	Font.CreateFont(-12,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("新宋体"));
	CFont *OldFont=dc.SelectObject(&Font);
	dc.SetTextColor(RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);


	CString strTxt;
	GetDlgItem(IDC_LEFT_USER)->GetWindowText(strTxt);
	wsprintf(sz,"%s", strTxt.GetBuffer());
	rect.left=x;
	rect.right=rect.left+80;
	rect.top=y;
	rect.bottom=rect.top+33;
	dc.DrawText(sz,lstrlen(sz),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

	return;
}

/**
 * 取消函数
 */
void CLeaveMessage::OnCancel()
{
	m_pParent = GetParent();
	if(m_pParent)
	{
		m_pParent->SendMessage(IDM_ARGEE_LEAVE,0,0);
	}
	CGameFaceGo::OnCancel();
}

/**
 * 确定函数
 */
void CLeaveMessage::OnOK()
{
	m_pParent = GetParent();
	if(m_pParent)
	{
		m_pParent->SendMessage(IDM_ARGEE_LEAVE,1,1);
	}
	CGameFaceGo::OnOK();
}

/**
 * 设置信息
 */
void CLeaveMessage::SetLeaveMessage(TCHAR * szMessage, TCHAR * szUserName)
{
//	if (GetSafeHwnd())
//	{
		GetDlgItem(IDC_LEFT_USER)->SetWindowText(szUserName);
		GetDlgItem(IDC_LEAVE_MSG)->SetWindowText(szMessage);
//	}
	return;
}

void CLeaveMessage::OnLButtonDown(UINT nFlags,CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

HBRUSH CLeaveMessage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	/*
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
	return hbr;*/
	return 0;
}

BOOL CLeaveMessage::ShowWindow(int nCmdShow)
{
	//CenterWindow(GetParent());
	return __super::ShowWindow(nCmdShow);
}