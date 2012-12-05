#include "StdAfx.h"
#include "ClientGameDlg.h"
#include ".\regretchess.h"

CRegretChess::CRegretChess():CGameFaceGo(CAdmitDefeat::IDD)
{
	m_pParnet=NULL;
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\huiqi.bmp"),SKIN_FOLDER);
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
}

CRegretChess::~CRegretChess(void)
{
}

void CRegretChess::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);

	
}

BOOL CRegretChess::OnInitDialog()
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
BEGIN_MESSAGE_MAP(CRegretChess, CGameFaceGo)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CRegretChess::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper handle(&m_bk);
	handle.BitBlt(dc,0,0);
}

void CRegretChess::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	if(m_pParnet)
		m_pParnet->SendMessage(IDM_AGREE_REGRET,1,1);

	CGameFaceGo::OnOK();
}

void CRegretChess::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	if(m_pParnet)
		m_pParnet->SendMessage(IDM_AGREE_REGRET,0,0);

	CGameFaceGo::OnCancel();
}
