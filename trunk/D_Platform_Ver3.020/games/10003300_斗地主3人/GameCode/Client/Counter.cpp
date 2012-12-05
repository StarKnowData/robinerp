// Counter.cpp : 实现文件
//

#include "stdafx.h"
#include "Counter.h"


// CCounter
#define  ID_CLOSE_BT            2007
#define  ID_LEAVE_BT            2008
#define  ID_HAVE_BT             2009

IMPLEMENT_DYNAMIC(CCounter, CWnd)

CCounter::CCounter()
{
	memset(m_iHistoryCard , 0 , sizeof(m_iHistoryCard)) ;
		 
	m_bShowLeaveNum = true ; 
}

CCounter::~CCounter()
{
}

BEGIN_MESSAGE_MAP(CCounter, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_CLOSE_BT,OnLookClose)
	ON_BN_CLICKED(ID_LEAVE_BT,OnLeaveNum)
	ON_BN_CLICKED(ID_HAVE_BT,OnHaveNum)
END_MESSAGE_MAP()

// CCounter 消息处理程序
void CCounter::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	return ;
	//CWnd::OnLButtonDown(nFlags, point);
}
///创建
int CCounter::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	TCHAR szName[MAX_PATH];

	wsprintf(szName,".\\image\\Look_bg.bmp");
	m_bglook.SetLoadInfo(szName,false);

	// TODO:  在此添加您专用的创建代码
	CGameImageHelper help(&m_bglook);
	HRGN hRgn=AFCBmpToRgn(help,RGB(255,0,255),RGB(1,1,1));     //过滤掉RGB(255,0,255)的颜色区域
	if (hRgn!=NULL)
	{
		SetWindowRgn(hRgn,TRUE);        //设置为没有过滤掉的区域
	}
	CRect rect;
	GetClientRect(&rect);
	this->MoveWindow(0,0,help.GetWidth(),help.GetHeight());

	m_btnLookclose.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,ID_CLOSE_BT);
	m_btnleaveNum.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,ID_LEAVE_BT);
	m_btnHaveNum.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,ID_HAVE_BT);
	
	HRGN hRgnt = NULL;
	CGameImage imgTemp;
	wsprintf(szName,".\\image\\game_close_bt.bmp");
	m_btnLookclose.LoadButtonBitmap(szName,false);
	imgTemp.SetLoadInfo(szName,false);
	hRgnt = AFCBmpToRgn(imgTemp,RGB(255,0,255),RGB(1,1,1));
	if (hRgnt !=NULL )
	{
		m_btnLookclose.SetWindowRgn(hRgnt,true);
	}

	wsprintf(szName,".\\image\\HaveNum_bt.bmp");
	m_btnleaveNum.LoadButtonBitmap(szName,false);
	imgTemp.SetLoadInfo(szName,false);
	hRgnt = AFCBmpToRgn(imgTemp,RGB(255,0,255),RGB(1,1,1));
	if (hRgnt !=NULL )
	{
		m_btnleaveNum.SetWindowRgn(hRgnt,true);
	}

	wsprintf(szName,".\\image\\LeaveNum_bt.bmp");
	m_btnHaveNum.LoadButtonBitmap(szName,false);
	imgTemp.SetLoadInfo(szName,false);
	hRgnt = AFCBmpToRgn(imgTemp,RGB(255,0,255),RGB(1,1,1));
	if (hRgnt !=NULL )
	{
		m_btnHaveNum.SetWindowRgn(hRgnt,true);
	}

	m_btnLookclose.ShowWindow(SW_SHOW);
	m_btnLookclose.GetWindowRect(&rect);
	m_btnLookclose.MoveWindow(432,5,rect.Width(),rect.Height());

	m_btnleaveNum.ShowWindow(SW_SHOW);
	m_btnleaveNum.GetWindowRect(&rect);
	m_btnleaveNum.MoveWindow(5,60,rect.Width(),rect.Height());

	m_btnHaveNum.ShowWindow(SW_HIDE);
	m_btnHaveNum.GetWindowRect(&rect);
	m_btnHaveNum.MoveWindow(5,60,rect.Width(),rect.Height());

	// TODO:  在此添加您专用的创建代码

	return 0;
}
///
void CCounter::DrawHistoryInfo(CDC *pDC)
{
	CString strNum ; 
	int iCount = 0 ; 

	CFont Newfont ; 
	CFont *Oldfont ; 
	Newfont.CreateFont(14,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	Oldfont = pDC->SelectObject(&Newfont) ;
	pDC->SetTextColor(RGB(255,0,0));

	for(int i = 3 ; i< 18 ; i++)
	{
		if(m_bShowLeaveNum)
		{
			strNum.Format("%d" , m_iHistoryCard[i]) ; 
		}
		else
		{
			if(i >15) ///
			{
				strNum.Format("%d" , 1 -m_iHistoryCard[i]) ; 
			}
			else
			{
				strNum.Format("%d" , 4-m_iHistoryCard[i]) ; 
			}
		}

		pDC->TextOutA(iCount*26 + 90,65,strNum) ;

		iCount ++ ; 
	}

	Newfont.DeleteObject() ; 

	pDC->SelectObject(&Oldfont) ;
	
	return ; 
}

void CCounter::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectWindow;
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(&dc);

	CBitmap BufferBmp;
	GetWindowRect(&rectWindow);
	BufferBmp.CreateCompatibleBitmap(&dc,rectWindow.Width(),rectWindow.Height());
	CBitmap * pOldBmp=BufferDC.SelectObject(&BufferBmp);
	
	CDC srcdc;
	CGameImageHelper help(&m_bglook);
	help.BitBlt(BufferDC.GetSafeHdc(),0,0);
	dc.SetBkMode(TRANSPARENT);
	BufferDC.SetBkMode(TRANSPARENT);	 

	m_bglook.BitBlt(BufferDC.GetSafeHdc(),0,0);
	DrawHistoryInfo(&BufferDC);  
	BufferDC.SetBkMode(TRANSPARENT); 
	dc.BitBlt(0,0,rectWindow.Width(),rectWindow.Height(),&BufferDC,0,0,SRCCOPY);
	srcdc.DeleteDC();
	BufferDC.DeleteDC();
	BufferBmp.DeleteObject();
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
}
void CCounter::OnLookClose()
{
      ShowWindow(SW_HIDE);
	//SendMessage(WM_CLOSE,0,0);
}
///剩余牌张数
void CCounter::OnHaveNum()
{
	m_bShowLeaveNum = !m_bShowLeaveNum ;

	if(m_bShowLeaveNum)
	{
		m_btnleaveNum.ShowWindow(SW_SHOW);
		m_btnHaveNum.ShowWindow(SW_HIDE);
	}
	else
	{
		m_btnleaveNum.ShowWindow(SW_HIDE);
		m_btnHaveNum.ShowWindow(SW_SHOW);
	}

	Invalidate() ; 

	return ; 
}
///已出牌张数
void CCounter::OnLeaveNum()
{
	m_bShowLeaveNum = !m_bShowLeaveNum ;

	if(m_bShowLeaveNum)
	{
		m_btnleaveNum.ShowWindow(SW_SHOW);
		m_btnHaveNum.ShowWindow(SW_HIDE);
	}
	else
	{
		m_btnleaveNum.ShowWindow(SW_HIDE);
		m_btnHaveNum.ShowWindow(SW_SHOW);
	}

	Invalidate() ; 

	return ; 
}
///重新设置游戏中的数据
void CCounter::ReSetDlg()
{
	ShowWindow(SW_HIDE);
	memset(m_iHistoryCard , 0 , sizeof(m_iHistoryCard));
}
