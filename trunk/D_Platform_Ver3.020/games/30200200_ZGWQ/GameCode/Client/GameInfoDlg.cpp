#include "Stdafx.h"
#include "GameInfoDlg.h"
#include "ClientGameDlg.h"
#include ".\gameinfodlg.h"


BEGIN_MESSAGE_MAP(CGameInfoDlg, CCoolView)
END_MESSAGE_MAP()

//构造函数
CGameInfoDlg::CGameInfoDlg(CWnd * pParent) : CCoolView(CGameInfoDlg::IDD,pParent)
{
	m_pPP = pParent;
}

//析够函数
CGameInfoDlg::~CGameInfoDlg()
{
}

// DDX/DDV 支持
void CGameInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CCoolView::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

//取消按钮
void CGameInfoDlg::OnCancel()
{
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_GameInfo);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	::PostMessage(pp->GetSafeHwnd(),WM_CLOSE,0,0); 
	CCoolView::OnClose();
}

//确定按钮
void CGameInfoDlg::OnOK()
{
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_GameInfo);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->PostMessage(IDM_BEGIN,0,0);
	CCoolView::OnClose();
	return;
}

//设置游戏设置
void CGameInfoDlg::SetGameSetInfo(int iJUMinute, int iJuSecond, int iBuMinute, int iBuSecond, int iDuMinute, int iDuSecond)
{
	if (GetSafeHwnd() == NULL)
		Create(IDD_GAME_INFO,m_pPP);

	SetDlgItemInt(IDC_EDIT_SET_JU_TIME_MINUTE,iJUMinute);
	SetDlgItemInt(IDC_EDIT_SET_JU_TIME_SECOND,iJuSecond);
	SetDlgItemInt(IDC_EDIT_SET_BU_TIME_MINUTE,iBuMinute);
	SetDlgItemInt(IDC_EDIT_SET_BU_TIME_SECOND,iBuSecond);
	SetDlgItemInt(IDC_EDIT_SET_DU_MIAO_MINUTE,iDuMinute);
	SetDlgItemInt(IDC_EDIT_SET_DU_MIAO_SECOND,iDuSecond);

	/*m_pPP = GetParent();
	this->CenterWindow(m_pPP);*/
	CRect rect;
	m_pPP->GetClientRect(rect);
	int cx=rect.Width();
	int cy=rect.Height();
	GetClientRect(rect);
	MoveWindow((cx-rect.Width())/2,(cy-rect.Height())/2,rect.Width(),rect.Height());

	//显示窗口
	ShowWindow(SW_SHOW);
	return;
}

BOOL CGameInfoDlg::OnInitDialog()
{
	CCoolView::OnInitDialog();

	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	TCHAR szPath[MAX_PATH];
	wsprintf(szPath,".\\image\\%s\\set_play.bmp",SKIN_FOLDER);
	LoadDialogBitmap(szPath,RGB(255,0,255),RGB(1,1,1));
	
	wsprintf(szPath,".\\image\\%s\\set_ok.bmp",SKIN_FOLDER);
	m_btOk.LoadButtonBitmap(szPath,false);
	wsprintf(szPath,".\\image\\%s\\set_cancel.bmp",SKIN_FOLDER);
	m_btCancel.LoadButtonBitmap(szPath,false);

	AfxSetResourceHandle(GetModuleHandle(NULL));
	return TRUE;
}

LRESULT CGameInfoDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
		SetBkMode((HDC)wParam,TRANSPARENT);
		HBRUSH brush = (HBRUSH)::GetStockObject(NULL_BRUSH);
		return (LRESULT)brush;
	}
	return CCoolView::WindowProc(message, wParam, lParam);
}
