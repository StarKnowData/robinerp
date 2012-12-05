// MsgBox.cpp : 实现文件
//

#include "stdafx.h"
#include "MsgBox.h"
#include "ClientGameDlg.h"
// CMsgBox 对话框

IMPLEMENT_DYNAMIC(CMsgBox, CDialog)

CMsgBox::CMsgBox(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgBox::IDD, pParent)
{
	m_Time=0;
	m_msg="";
}

CMsgBox::~CMsgBox()
{
}

void CMsgBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDOK, m_btleave);
}


BEGIN_MESSAGE_MAP(CMsgBox, CDialog)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CMsgBox::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMsgBox 消息处理程序

void CMsgBox::ShowMsg(TCHAR  szMsg[], int time,bool Showleave, GameResult gameResult)
{
	m_iFinish = gameResult;
	m_msg=szMsg;
	m_Time=time;
	SetTimer(IDR_HIDE,1000,NULL);
	TCHAR sz[100];
	wsprintf(sz,"确定%d",m_Time);
	m_btcancel.SetWindowText(sz);
	m_btcancel.SetTextColor(RGB(255, 255, 0), true);
	m_btleave.SetTextColor(RGB(255, 255, 0), true);
	CRect rect;
	m_btcancel.GetClientRect(&rect);
	m_btcancel.MapWindowPoints(this,(LPPOINT)&rect,2);
	int iTemp = 5;
	if (!Showleave)
	{
		iTemp = 0;
	}
	if(Showleave)
	{
		m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-150)/2,rect.top + 5,0,0,SWP_NOSIZE|SWP_NOZORDER);
		m_btleave.SetWindowPos(NULL,(m_bkImg.GetWidth()-150)/2+100,rect.top + 5,0,0,SWP_NOSIZE|SWP_NOZORDER);
	}
	else
		m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-70)/2,rect.top+iTemp,0,0,SWP_NOSIZE|SWP_NOZORDER);
	m_btleave.ShowWindow(Showleave);

	Invalidate();
	ShowWindow(SW_SHOW);
}

void CMsgBox::OnTimer(UINT_PTR nIDEvent)
{
	if(IDR_HIDE == nIDEvent)
	{
		m_Time--;
		if(m_Time<=0)
		{
			KillTimer(IDR_HIDE);
			ShowWindow(FALSE);
		}
		else
		{
			TCHAR sz[100];
			wsprintf(sz,"确定%d",m_Time);
			//m_btcancel.SetTextColor(RGB(255, 255, 0));
			//m_btcancel.SetFont()
			m_btcancel.SetWindowText(sz);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CMsgBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	//CDialog::OnLButtonDown(nFlags, point);
}

void CMsgBox::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper help(&m_bkImg);
	CDC srcDC;
	srcDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBmp = srcDC.SelectObject(help);
	::TransparentBlt(dc.GetSafeHdc(),0,0,m_bkImg.GetWidth(),m_bkImg.GetHeight(),
		srcDC.GetSafeHdc(),0,0,m_bkImg.GetWidth(),m_bkImg.GetHeight(),srcDC.GetPixel(0,0));
	srcDC.SelectObject(pOldBmp);


	CRect ClientRect;
	GetClientRect(&ClientRect);
	
	CRect rect;
//	TCHAR sz[100];
	CFont Font;
	Font.CreateFont(14,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	CFont *OldFont=dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255,255,255));
	dc.SetBkMode(TRANSPARENT);

	ClientRect.top+=23;
	ClientRect.bottom-=34;
	dc.DrawText(m_msg, m_msg.GetLength(), ClientRect,DT_CENTER);

	dc.DeleteDC();
}

BOOL CMsgBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	CGameImage bt;
	TCHAR path[MAX_PATH] = {0};

	wsprintf(path,TEXT("image\\msgboxbt.bmp"));
	bt.SetLoadInfo(path,true);
	wsprintf(path,TEXT("image\\msgboxbt.bmp"));
	m_btcancel.LoadButtonBitmap(path,false);
	m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-140)/2,m_bkImg.GetHeight()-17-bt.GetHeight()/2,bt.GetWidth()/4,bt.GetHeight(),SWP_NOZORDER);
	wsprintf(path,TEXT("image\\msgboxbt.bmp"));
	bt.SetLoadInfo(path,true);
	wsprintf(path,TEXT("image\\msgboxbt.bmp"));
	m_btleave.LoadButtonBitmap(path,false);
	m_btleave.SetWindowPos(NULL,(m_bkImg.GetWidth()-140)/2+70,m_bkImg.GetHeight()-17-bt.GetHeight()/2,bt.GetWidth()/4,bt.GetHeight(),SWP_NOZORDER);
	SetWindowPos(NULL,0,0,m_bkImg.GetWidth(),m_bkImg.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	
	return TRUE; 
}

void CMsgBox::OnBnClickedOk()
{
	::g_pCClientGameDlg->SendMessage(WM_CLOSE,0,0);
	//OnOK();
}

/**
 * 自动调整大小
 */
void CMsgBox::AutoSize(int xValue,int yValue)
{
	MoveWindow(xValue,yValue-20,m_bkImg.GetWidth(),m_bkImg.GetHeight());
	Invalidate();
	UpdateWindow();
}


int CMsgBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	TCHAR szName[MAX_PATH];
     wsprintf(szName,TEXT("image\\msgboxbk.bmp"));
	m_bkImg.SetLoadInfo(szName,TRUE);

	CRect ClientRect;
	GetClientRect(&ClientRect);
	CGameImageHelper	help(&m_bkImg);
	MoveWindow(0,0,help.GetWidth(),help.GetHeight());
	HRGN hRgn=AFCBmpToRgn(help,RGB(255,0,255),RGB(1,0,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,help.GetWidth(),help.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
	}

	return 0;
}