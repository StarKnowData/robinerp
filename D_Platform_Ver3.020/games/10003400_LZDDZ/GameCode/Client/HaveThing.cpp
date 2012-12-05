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

//构造函数
CHaveThing::CHaveThing() : CGameFaceGo(CHaveThing::IDD)
{
	m_pParnet=NULL;
//	TCHAR path[MAX_PATH];
//	wsprintf(path,".\\image\\%s\\havething.bmp",GET_SKIN_FOLDER(szTempStr));
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
	wsprintf(path,TEXT(".\\image\\%s\\havething.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_bk.SetLoadInfo(path,true);
	
	((CEdit *)GetDlgItem(IDC_THING))->LimitText(60);
	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	CenterWindow(GetParent());
//	TCHAR path[MAX_PATH];
	wsprintf(path,TEXT(".\\image\\%s\\send.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT(".\\image\\%s\\cancel.bmp"),GET_SKIN_FOLDER(szTempStr));
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
	if (iCount==0||!isclick)
	{
		MessageBox(TEXT("请在输入框中输入离开的原因！"),"系统提示",MB_ICONQUESTION);
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
	/*CRect ClientRect;
	GetClientRect(&ClientRect);
	this->MapWindowPoints(this->GetParent(),&ClientRect);*/
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

BOOL CHaveThing::ShowWindow(int nCmdShow)
{
	CenterWindow(GetParent());
	BringWindowToTop();
	return __super::ShowWindow(nCmdShow);
}
