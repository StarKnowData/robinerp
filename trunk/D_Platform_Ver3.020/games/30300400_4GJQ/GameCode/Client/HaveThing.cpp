#include "Stdafx.h"
#include "HaveThing.h"
#include "ClientGameDlg.h"
#include ".\havething.h"

//IMPLEMENT_DYNAMIC(CHaveThing, CAFCBaseDialog)

BEGIN_MESSAGE_MAP(CHaveThing, CGameFaceGo)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_EN_SETFOCUS(IDC_THING,&CHaveThing::OnEnSetfocusEdit)
END_MESSAGE_MAP()

/**
 * 构造函数
 */
CHaveThing::CHaveThing() : CGameFaceGo(CHaveThing::IDD)
{
	m_pParnet=NULL;
//	TCHAR path[MAX_PATH];
//	wsprintf(path,".\\image\\havething.bmp");
//	m_bk.SetLoadInfo(path,true);
}

/**
 * 析构函数
 */
CHaveThing::~CHaveThing()
{
}

/**
 * DDX/DDV 支持
 */
void CHaveThing::DoDataExchange(CDataExchange* pDX)
{
	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

/**
 * 初始化函数
 */
BOOL CHaveThing::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	TCHAR path[MAX_PATH];
	wsprintf(path,TEXT(".\\image\\havething.bmp"));
	m_bk.SetLoadInfo(path,true);
	

	CGameImageHelper imgHelper(&m_bk);
	HRGN hRgn=AFCBmpToRgn(imgHelper,m_bk.GetPixel(0,0),RGB(1,1,1));
	if (hRgn!=NULL)
	{
		SetWindowRgn(hRgn,TRUE);
	}

	((CEdit *)GetDlgItem(IDC_THING))->LimitText(60);
	MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight());
	//SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	//CenterWindow(GetParent());
//	TCHAR path[MAX_PATH];
	wsprintf(path,TEXT(".\\image\\send.bmp"));
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT(".\\image\\cancel.bmp"));
	m_btCancel.LoadButtonBitmap(path,false);
	if(m_btOk.GetSafeHwnd())
	{
		m_btOk.MoveWindow(88,158,46,20,false);
		m_btCancel.MoveWindow(186,158,46,20,false);
		GetDlgItem(IDC_THING)->MoveWindow(19,67,282,59);
	}
	return TRUE;
}

/**
 * 取消函数
 */
void CHaveThing::OnCancel()
{
//	CGameFaceGo::OnClose();
	CGameFaceGo::OnCancel();
}

/**
 * 确定函数
 */
void CHaveThing::OnOK()
{
	char szBuffer[61];
	int iCount=GetDlgItem(IDC_THING)->GetWindowText(szBuffer,sizeof(szBuffer));
	if (iCount==0||!isclick)
	{
		MessageBox(TEXT("请在输入框中输入离开的理由！"),"系统提示",MB_ICONQUESTION);
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
	CPaintDC dc(this);	
	CGameImageHelper	help(&m_bk);
	help.BitBlt(dc.GetSafeHdc(),0,0);
	/*CDC srcDC;
	srcDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBmp = srcDC.SelectObject(help);*/
	/*::TransparentBlt(dc.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),
		srcDC.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),srcDC.GetPixel(0,0));
	srcDC.SelectObject(pOldBmp);
	srcDC.DeleteDC();*/
}

void CHaveThing::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

void CHaveThing::OnEnSetfocusEdit()
{
	if(isclick==false)
	{
		isclick=true;
		((CEdit *)GetDlgItem(IDC_THING))->SetWindowText("");
	}
}

BOOL CHaveThing::ShowWindow(int nCmdShow)
{
	//CenterWindow(GetParent());
	return __super::ShowWindow(nCmdShow);
}
