#include "stdafx.h"
#include "StopMessage.h"
#include "ClientGameDlg.h"
#include ".\stopmessage.h"


BEGIN_MESSAGE_MAP(CStopMessage, CGameFaceGo)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//构造函数
CStopMessage::CStopMessage() : CGameFaceGo(CStopMessage::IDD)
{
	m_pParent=NULL;
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\stopmsg.bmp"),SKIN_FOLDER);
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
}

//析构函数
CStopMessage::~CStopMessage()
{
}

//DDX/DDV 支持
void CStopMessage::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

//取消函数
void CStopMessage::OnCancel()
{
	if(m_pParent)
		m_pParent->SendMessage(IDM_ARGEE_STOP,0,0);
	CGameFaceGo::OnCancel();
}

//确定函数
void CStopMessage::OnOK()
{
	m_pParent = GetParent();
	if(m_pParent)
		m_pParent->SendMessage(IDM_ARGEE_STOP,1,1);
	CGameFaceGo::OnOK();
}

void CStopMessage::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper handle(&m_bk);
	handle.BitBlt(dc,0,0);
}

BOOL CStopMessage::OnInitDialog()
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
