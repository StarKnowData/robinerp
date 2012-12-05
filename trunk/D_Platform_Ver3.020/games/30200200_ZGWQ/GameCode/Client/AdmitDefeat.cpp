#include "StdAfx.h"
#include "ClientGameDlg.h"
#include ".\admitdefeat.h"

CAdmitDefeat::CAdmitDefeat():CGameFaceGo(CAdmitDefeat::IDD)
{
	m_pParnet=NULL;
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\renshu.bmp"),SKIN_FOLDER);
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
}

CAdmitDefeat::~CAdmitDefeat(void)
{
}

BOOL CAdmitDefeat::OnInitDialog()
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
	return TRUE;
}
BEGIN_MESSAGE_MAP(CAdmitDefeat, CGameFaceGo)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CAdmitDefeat::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper handle(&m_bk);

	handle.BitBlt(dc,0,0);
}

void CAdmitDefeat::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CGameFaceGo::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

void CAdmitDefeat::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CGameFaceGo::OnCancel();
}

void CAdmitDefeat::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pParnet = GetParent();
	if(m_pParnet)
		m_pParnet->SendMessage(IDM_SEND_REN_SHU,0,0);
	CGameFaceGo::OnOK();

}
