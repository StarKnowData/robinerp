#include "Stdafx.h"
#include "HaveThing.h"
#include "ClientGameDlg.h"
#include ".\Stop.h"

//IMPLEMENT_DYNAMIC(CHaveThing, CAFCBaseDialog)

BEGIN_MESSAGE_MAP(CStop, CGameFaceGo)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//构造函数
CStop::CStop() : CGameFaceGo(CStop::IDD)
{
	m_pParnet=NULL;
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\stop.bmp"),SKIN_FOLDER);
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
}

//析构函数
CStop::~CStop()
{
}

// DDX/DDV 支持
void CStop::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

//初始化函数
BOOL CStop::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\ok.bmp"),SKIN_FOLDER);
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\%s\\cancel.bmp"),SKIN_FOLDER);
	m_btCancel.LoadButtonBitmap(path,false);
	if(m_btOk.GetSafeHwnd())
	{
		m_btOk.MoveWindow(54,100,46,20,false);
		m_btCancel.MoveWindow(143,100,46,20,false);
	}
	//jph 100127
	HRGN hRgn;
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
	{
		SetWindowRgn(hRgn,true);
	}
	return TRUE;
}

//取消函数
void CStop::OnCancel()
{
//	CGameFaceGo::OnClose();
	CGameFaceGo::OnCancel();
}

//确定函数
void CStop::OnOK()
{
	m_pParnet = GetParent();
	if(m_pParnet)
		m_pParnet->SendMessage(IDM_STOP_THING,0,0);
	CGameFaceGo::OnOK();
}

void CStop::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper handle(&m_bk);
	handle.BitBlt(dc,0,0);
}
