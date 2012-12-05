#include "Stdafx.h"
#include "HaveThing.h"
#include "ClientGameDlg.h"
#include ".\havething.h"

//IMPLEMENT_DYNAMIC(CHaveThing, CAFCBaseDialog)

BEGIN_MESSAGE_MAP(CHaveThing, CGameFaceGo)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//构造函数
CHaveThing::CHaveThing() : CGameFaceGo(CHaveThing::IDD)
{
	m_pParnet=NULL;
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT(".\\image\\%s\\havething.bmp"),SKIN_FOLDER);
	m_bk.SetLoadInfo(path,true);
}

//析构函数
CHaveThing::~CHaveThing()
{
}

// DDX/DDV 支持
void CHaveThing::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

//初始化函数
BOOL CHaveThing::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	((CEdit *)GetDlgItem(IDC_THING))->LimitText(60);
	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\send.bmp"),SKIN_FOLDER);
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\%s\\cancel.bmp"),SKIN_FOLDER);
	m_btCancel.LoadButtonBitmap(path,false);
	if(m_btOk.GetSafeHwnd())
	{
		m_btOk.MoveWindow(88,158,46,20,false);
		m_btCancel.MoveWindow(186,158,46,20,false);
		GetDlgItem(IDC_THING)->MoveWindow(19,67,282,59);
	}	
	return TRUE;
}

//取消函数
void CHaveThing::OnCancel()
{
//	CGameFaceGo::OnClose();
	CGameFaceGo::OnCancel();
}

//确定函数
void CHaveThing::OnOK()
{
	char szBuffer[61];
	int iCount=GetDlgItem(IDC_THING)->GetWindowText(szBuffer,sizeof(szBuffer));
	if (iCount==0)
	{
		MessageBox(TEXT("请在输入框中输入离开的原因！"),"提示",MB_ICONQUESTION);
		GetDlgItem(IDC_THING)->SetFocus();
		return;
	}
	m_pParnet = GetParent();
	if(m_pParnet)
		m_pParnet->SendMessage(IDM_SEND_THING,(WPARAM)szBuffer,(LPARAM)szBuffer);
	CGameFaceGo::OnOK();
}

void CHaveThing::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.SetBkMode(TRANSPARENT);
	CRect ClientRect;
	GetClientRect(&ClientRect);	
	CGameImageHelper	help(&m_bk);	
	help.BitBlt(dc.GetSafeHdc(),0,0);
}

LRESULT CHaveThing::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
		SetTextColor((HDC)wParam, RGB(0,0,0)) ;
		SetBkColor((HDC)wParam, m_bk.GetPixel(30,30));
		return (LRESULT)CreateSolidBrush(m_bk.GetPixel(30,30));
	}
	return __super::WindowProc(message, wParam, lParam);
}
