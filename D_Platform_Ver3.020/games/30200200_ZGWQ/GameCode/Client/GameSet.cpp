#include "Stdafx.h"
#include "GameSet.h"
#include "ClientGameDlg.h"


BEGIN_MESSAGE_MAP(CGameSet, CCoolView)
END_MESSAGE_MAP()

//构造函数
CGameSet::CGameSet(CWnd * pParent) : CCoolView(CGameSet::IDD,pParent)
{
	m_bSound=TRUE;
	m_bShowUser=TRUE;
	m_bEnableWatch=TRUE;
	m_pParent=pParent;
}

//析构函数
CGameSet::~CGameSet()
{
}

//DDX/DDV 支持
void CGameSet::DoDataExchange(CDataExchange* pDX)
{
	CCoolView::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Control(pDX, IDC_SOUND, m_check_1);
	DDX_Control(pDX, IDC_USER_MESSAGE, m_check_2);
	DDX_Control(pDX, IDC_WATCH, m_check_3);
	DDX_Control(pDX, IDC_RIGHT_POWER, m_check_4);
}

//确定按钮
void CGameSet::OnOK()
{
	m_bSound=(m_check_1.GetCheck()==BST_CHECKED);
	m_bShowUser=(m_check_2.GetCheck()==BST_CHECKED);
	m_bEnableWatch=(m_check_3.GetCheck()==BST_CHECKED);
	m_bRightPower=(m_check_4.GetCheck()==BST_CHECKED);
	m_pParent->GetParent()->SendMessage(IDM_GAMESETTING_OK,0,0);
	CCoolView::OnOK();
}

//初始化对话框
BOOL CGameSet::OnInitDialog()
{
	CCoolView::OnInitDialog();

	if (m_bSound) m_check_1.SetCheck(BST_CHECKED);
	if (m_bShowUser) m_check_2.SetCheck(BST_CHECKED);
	if (m_bEnableWatch) m_check_3.SetCheck(BST_CHECKED);
	if (m_bRightPower) m_check_4.SetCheck(BST_CHECKED);
	//HBITMAP
	
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT(".\\image\\%s\\game_set.bmp"),SKIN_FOLDER);
	LoadDialogBitmap(path,RGB(255,0,255),RGB(1,1,1));
	AfxSetResourceHandle(GetModuleHandle(NULL));
	wsprintf(path,TEXT(".\\image\\%s\\set_ok_btn.bmp"),SKIN_FOLDER);
	m_Ok.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT(".\\image\\%s\\set_cancel_btn.bmp"),SKIN_FOLDER);
	m_Cancel.LoadButtonBitmap(path,false);
	/*wsprintf(path,TEXT(".\\image\\%s\\set_ok.bmp"),SKIN_FOLDER);
	m_Ok.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT(".\\image\\%s\\set_cancel.bmp"),SKIN_FOLDER);
	m_Cancel.LoadButtonBitmap(path,false);*/

	/*m_pParent = GetParent();
	this->CenterWindow(m_pParent);*/
	CRect rect;
	((CClientGameDlg*)m_pParent)->m_PlayView.GetClientRect(rect);
	m_pParent->GetClientRect(rect);
	int cx=rect.Width();
	int cy=rect.Height();
	GetClientRect(rect);	
	MoveWindow((cx-m_BackBitmap.GetWidth())/2,(cy-m_BackBitmap.GetHeight())/2,m_BackBitmap.GetWidth(),m_BackBitmap.GetHeight());
	return TRUE; 
}


LRESULT CGameSet::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
