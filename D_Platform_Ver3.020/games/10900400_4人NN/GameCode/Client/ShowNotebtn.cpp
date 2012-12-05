#include "Stdafx.h"
#include "ShowNoteBtn.h"
#include "ClientGameDlg.h"
#include "Resource.h"

BEGIN_MESSAGE_MAP(CShowNote, CDialog)
	ON_BN_CLICKED(IDC_NOTE, OnNote)
	ON_BN_CLICKED(IDC_BULL, OnAdd)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_BN_CLICKED(IDC_FOLLOW, OnFollow)//跟
	ON_BN_CLICKED(IDC_GIVEUP, OnGiveup)//弃
	ON_BN_CLICKED(IDC_LOOK, OnLook)//弃
	ON_WM_PAINT()	
	ON_WM_LBUTTONDOWN()
	//	ON_BN_CLICKED(IDC_NT, OnNT)
END_MESSAGE_MAP()

//构造函数
CShowNote::CShowNote(CWnd* pParent /*=NULL*/): CDialog(CShowNote::IDD, pParent)
{
	CGameImage bk;
	//m_BmNote.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_NOTE);
    //m_BmShow.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_SHOW);
    //m_BmAdd.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_BULL);
    //m_BmFollow.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_FOLLOW);
    //m_BmGiveup.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_GIVEUP);
    HRGN hRgn;
	TCHAR szName[MAX_PATH];
	wsprintf(szName,".\\image\\Note.bmp");	//开始按钮
	m_BmNote.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_BmNote.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\Show.bmp");	//开始按钮
	m_BmShow.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_BmShow.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\Add.bmp");	//开始按钮
	m_BmAdd.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_BmAdd.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\Follow.bmp");	//开始按钮
	m_BmFollow.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_BmFollow.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\Giveup.bmp");	//开始按钮
	m_BmGiveup.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_BmGiveup.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\look.bmp");	//开始按钮
	m_BmLook.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_BmLook.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\allbtn.bmp");	//开始按钮
	m_bk.SetLoadInfo(szName,CGameImageLink::m_bAutoLock);
	m_pParent=pParent;
}

//DDX 支持
void CShowNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTE, m_BmNote);
	DDX_Control(pDX, IDC_BULL, m_BmAdd);
	DDX_Control(pDX, IDC_SHOW, m_BmShow);
	DDX_Control(pDX, IDC_FOLLOW, m_BmFollow);
	DDX_Control(pDX, IDC_GIVEUP, m_BmGiveup);
	DDX_Control(pDX, IDC_LOOK, m_BmLook);
}

//初始化函数
BOOL CShowNote::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	m_BmShow.SizeToContent();
//	m_BmNote.SizeToContent();
//	m_BmAdd.SizeToContent();
//	m_BmFollow.SizeToContent();
//	m_BmGiveup.SizeToContent();

//	int iHide=0,iWide=0;
	CRect rect;
//	iWide=134;//rect.Width();
//	iHide=164;//rect.Height();
	m_BmShow.MoveWindow(146,38,42,33);
	m_BmNote.MoveWindow(12,73,42,33);
	m_BmAdd.GetWindowRect(&rect);
	m_BmAdd.MoveWindow(70,19,42,33);
	m_BmFollow.MoveWindow(30,40,42,33);
	m_BmGiveup.MoveWindow(113,17,42,33);
	m_BmLook.MoveWindow(165,73,42,33);

	CGameImageHelper ImageHandle(&m_bk);
	HRGN hRgn=AFCBmpToRgn(ImageHandle,RGB(255,0,255),RGB(1,0,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
		return true;
	}

//	GetWindowRect(&rect);
	MoveWindow(0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight());
//	AfxSetResourceHandle(GetModuleHandle(NULL));
	UpdateShowNoteBtn(1,1,1,1,1);			//更新下注按钮
	return TRUE;
}
//设置按钮可用状态
void CShowNote::UpdateShowNoteBtn(BOOL show,BOOL note,BOOL add,BOOL follow,BOOL giveup,BOOL look)
{
	m_BmShow.EnableWindow(show);
	m_BmNote.EnableWindow(note);
	m_BmAdd.EnableWindow(add);
	m_BmFollow.EnableWindow(follow);
	m_BmGiveup.EnableWindow(giveup);
	m_BmLook.EnableWindow(look);
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);
	return ;
}
//更新按钮可用状态
void CShowNote::SetShowNoteBtn(BOOL show,BOOL note,BOOL add,BOOL follow,BOOL giveup,BOOL look)
{
	m_BmShow.EnableWindow(show);
	m_BmNote.EnableWindow(note);
	m_BmAdd.EnableWindow(add);
	m_BmFollow.EnableWindow(follow);
	m_BmGiveup.EnableWindow(giveup);
	m_BmLook.EnableWindow(look);
	return ;
}

//按钮消息
void CShowNote::OnNote()   
{	
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_ShowNote);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_SHOW_NOTE,0,0); 
}
//按钮消息
void CShowNote::OnAdd()   
{	
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_ShowNote);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_SHOW_NOTE,1,1); 
}
//按钮消息
void CShowNote::OnShow()   
{	
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_ShowNote);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_ACTIVE_RESULT,4,4); 
}
//按钮消息
void CShowNote::OnFollow()   
{	
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_ShowNote);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_ACTIVE_RESULT,3,3); 
}
//按钮消息
void CShowNote::OnGiveup()   
{	
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_ShowNote);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_ACTIVE_RESULT,0,0); 
}
//看牌消息
void CShowNote::OnLook()  
{
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_ShowNote);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_ACTIVE_RESULT,6,6); 

}
void CShowNote::OnPaint()
{
	CPaintDC dc(this);
	DrawBk(&dc,0, 0);
	return ;
}
void CShowNote::DrawBk(CDC * pDC, int x, int y)
{
		CGameImageHelper ImageHandle(&m_bk);
		ImageHandle.BitBlt(pDC->GetSafeHdc(),0,0);
}

void CShowNote::OnLButtonDown(UINT nFlags, CPoint point)
{
//	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
//	Invalidate();
	return ;
}
