#include "Stdafx.h"
#include "HaveThing.h"
#include "ClientGameDlg.h"

//IMPLEMENT_DYNAMIC(CHaveThing, CAFCBaseDialog)

BEGIN_MESSAGE_MAP(CHaveThing, CGameFaceGo)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_EN_SETFOCUS(IDC_THING,&CHaveThing::OnEnSetfocusEdit)
END_MESSAGE_MAP()

//构造函数
CHaveThing::CHaveThing() : CGameFaceGo(CHaveThing::IDD)
{
	isclick = false;
	m_pParnet=NULL;

	//	TCHAR path[MAX_PATH];
	//	wsprintf(path,".\\image\\havething.bmp",SKIN_CARD);
	//	m_bk.SetLoadInfo(path,true);
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
//初始化函数
BOOL CHaveThing::OnInitDialog()
{

	CGameFaceGo::OnInitDialog();

	TCHAR path[MAX_PATH];
	wsprintf(path,TEXT(".\\image\\havething.bmp"));
	m_bk.SetLoadInfo(path,true);

	((CEdit *)GetDlgItem(IDC_THING))->LimitText(60);
	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	//	TCHAR path[MAX_PATH];
	wsprintf(path,TEXT(".\\image\\send.bmp"));
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT(".\\image\\cancel.bmp"));
	m_btCancel.LoadButtonBitmap(path,false);
	if(m_btOk.GetSafeHwnd())
	{
		CGameImage OkTmp;
		OkTmp.SetLoadInfo(TEXT(".\\image\\send.bmp"), true);
		m_btOk.MoveWindow(88,158, OkTmp.GetWidth()/4, OkTmp.GetHeight(), false);
		OkTmp.SetLoadInfo(TEXT(".\\image\\cancel.bmp"), true);
		m_btCancel.MoveWindow(186,158, OkTmp.GetWidth()/4, OkTmp.GetHeight(), false);
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
	if (iCount==0||!isclick)
	{
		AFCMessageBox(TEXT("请在输入框中输入离开的原因！"));
		GetDlgItem(IDC_THING)->SetFocus();
		return;
	}
	if(m_pParnet)
		m_pParnet->SendMessage(IDM_SEND_THING,(WPARAM)szBuffer,(LPARAM)szBuffer);
	CGameFaceGo::OnOK();
}

void CHaveThing::OnPaint()
{	
	CPaintDC dc(this);
	CRect ClientRect;
	GetClientRect(&ClientRect);
	//this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	//this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	help.BitBlt(dc.GetSafeHdc(),0,0);
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
