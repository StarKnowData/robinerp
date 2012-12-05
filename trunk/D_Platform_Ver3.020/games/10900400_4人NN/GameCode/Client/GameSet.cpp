#include "Stdafx.h"
#include "GameSet.h"
#include "ClientGameDlg.h"


BEGIN_MESSAGE_MAP(CGameSet, CCoolView)
ON_WM_PAINT()
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
	//DDX_Control(pDX, IDC_RIGHT_POWER, m_check_4);
}

//确定按钮
void CGameSet::OnOK()
{
	m_bSound=(m_check_1.GetCheck()==BST_CHECKED);
	m_bShowUser=(m_check_2.GetCheck()==BST_CHECKED);
	m_bEnableWatch=(m_check_3.GetCheck()==BST_CHECKED);
	//m_bRightPower=(m_check_4.GetCheck()==BST_CHECKED);
	CCoolView::OnOK();
}

//初始化对话框
BOOL CGameSet::OnInitDialog()
{
	CCoolView::OnInitDialog();
	TCHAR szName[MAX_PATH];
	wsprintf(szName,".\\image\\ok_bt.bmp");
	m_Ok.LoadButtonBitmap(szName,false);

	wsprintf(szName,".\\image\\cancel_bt.bmp");
	m_Cancel.LoadButtonBitmap(szName,false);

	wsprintf(szName,".\\image\\game_set.bmp");
	m_bk.SetLoadInfo(szName,true);


	if (m_bSound) m_check_1.SetCheck(BST_CHECKED);
	if (m_bShowUser) m_check_2.SetCheck(BST_CHECKED);
	if (m_bEnableWatch) m_check_3.SetCheck(BST_CHECKED);
	//if (m_bRightPower) m_check_4.SetCheck(BST_CHECKED);
	//HBITMAP
	
//	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
//	LoadDialogBitmap(GetModuleHandle(CLIENT_DLL_NAME),IDB_BITMAP_SETUP,RGB(255,0,255),RGB(1,1,1));
//	AfxSetResourceHandle(GetModuleHandle(NULL));

	/*CRect rect;
	((CClientGameDlg*)m_pParent)->m_PlayView.GetClientRect(rect);
	int cx=rect.Width();
	int cy=rect.Height();
	GetClientRect(rect);
	MoveWindow((cx-rect.Width())/2,(cy-rect.Height())/2-110,rect.Width(),rect.Height());*/
	//MoveWindow((cx)/2-20,(cy)/2-80,rect.Width(),rect.Height());
	MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight());
	CenterWindow(GetParent());

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
		HBRUSH hBrush=(HBRUSH)::GetStockObject(NULL_BRUSH);
		SetBkMode((HDC)wParam,TRANSPARENT);
		SetTextColor((HDC)wParam, RGB(0,0,0)) ;
		SetBkColor((HDC)wParam,m_bk.GetPixel(10,10));//RGB(187,104,2));
		//return (LRESULT)CreateSolidBrush(m_bk.GetPixel(10,10));//RGB(187,104,2));
		return (LRESULT)hBrush;
	}
	return CCoolView::WindowProc(message, wParam, lParam);
}

void CGameSet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect ClientRect;
	GetClientRect(&ClientRect);
	//this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	//this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	help.BitBlt(dc.GetSafeHdc(),0,0);
}
