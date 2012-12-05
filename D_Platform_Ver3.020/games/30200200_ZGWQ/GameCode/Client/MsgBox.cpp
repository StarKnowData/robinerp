// MsgBox.cpp : 实现文件
//

#include "stdafx.h"
#include "MsgBox.h"
#include "ClientGameDlg.h"
// CMsgBox 对话框

IMPLEMENT_DYNAMIC(CMsgBox, CDialog)

CMsgBox::CMsgBox(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgBox::IDD, pParent)
{
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\msgboxbk.bmp"),SKIN_FOLDER);
	m_bkImg.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	m_Time=0;
	m_msg="";
}

CMsgBox::~CMsgBox()
{
}

void CMsgBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDOK, m_btleave);
}


BEGIN_MESSAGE_MAP(CMsgBox, CDialog)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CMsgBox::OnBnClickedOk)
END_MESSAGE_MAP()


// CMsgBox 消息处理程序

void CMsgBox::ShowMsg(TCHAR  szMsg[], int time,bool Showleave)
{
	Showleave=true;
	m_msg=szMsg;
	m_Time=time;
	SetTimer(IDR_HIDE,1000,NULL);
	TCHAR sz[100];
	wsprintf(sz,"确定(%d)",m_Time);
	m_btcancel.SetWindowText(sz);
	CRect rect;
	m_btcancel.GetClientRect(&rect);
	m_btcancel.MapWindowPoints(this,(LPPOINT)&rect,2);
	if(Showleave)
	{
		m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-140)/2,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
		m_btleave.SetWindowPos(NULL,(m_bkImg.GetWidth()-140)/2+70,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	}
	else
		m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-70)/2,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	m_btleave.ShowWindow(Showleave);
	Invalidate();
	ShowWindow(SW_SHOW);
}

void CMsgBox::OnTimer(UINT_PTR nIDEvent)
{
	if(IDR_HIDE == nIDEvent)
	{
		m_Time--;
		if(m_Time<=0)
		{
			KillTimer(IDR_HIDE);
			ShowWindow(FALSE);
		}
		else
		{
			TCHAR sz[100];
			wsprintf(sz,"确定(%d)",m_Time);
			m_btcancel.SetWindowText(sz);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CMsgBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	//CDialog::OnLButtonDown(nFlags, point);
}

void CMsgBox::OnPaint()
{
	CPaintDC dc(this);
	CFont Font;
	Font.CreateFont(-13,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	dc.SelectObject(Font);
	dc.SetBkMode(TRANSPARENT);
	CGameImageHelper img(&m_bkImg);
	img.BitBlt(dc.GetSafeHdc(),0,0);
	CRect rect;
	GetClientRect(&rect);
	rect.top+=23;
	rect.bottom-=34;
	dc.DrawText(m_msg,m_msg.GetLength(),rect,DT_CENTER);
}

BOOL CMsgBox::OnInitDialog()
{
	CDialog::OnInitDialog();
	CGameImage bt;
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\msgboxbt.bmp"),SKIN_FOLDER);
	bt.SetLoadInfo(path,true);
	wsprintf(path,TEXT("image\\%s\\msgboxbt.bmp"),SKIN_FOLDER);
	m_btcancel.LoadButtonBitmap(path,false);
	m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-140)/2,m_bkImg.GetHeight()-17-bt.GetHeight()/2,bt.GetWidth()/4,bt.GetHeight(),SWP_NOZORDER);
	wsprintf(path,TEXT("image\\%s\\msgboxbt.bmp"),SKIN_FOLDER);
	bt.SetLoadInfo(path,true);
	wsprintf(path,TEXT("image\\%s\\msgboxbt.bmp"),SKIN_FOLDER);
	m_btleave.LoadButtonBitmap(path,false);
	m_btleave.SetWindowPos(NULL,(m_bkImg.GetWidth()-140)/2+70,m_bkImg.GetHeight()-17-bt.GetHeight()/2,bt.GetWidth()/4,bt.GetHeight(),SWP_NOZORDER);
	SetWindowPos(NULL,0,0,m_bkImg.GetWidth(),m_bkImg.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	return TRUE; 
}

void CMsgBox::OnBnClickedOk()
{
	CWnd *p=GetParent();
	CWnd *pClientGameDlg;
	if(p)
		pClientGameDlg=p->GetParent();
	if(pClientGameDlg)
		pClientGameDlg->SendMessage(WM_CLOSE,0,0);
	//OnOK();
}
