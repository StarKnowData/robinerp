// MsgBox.cpp : 实现文件
//

#include "stdafx.h"
#include "MsgBox.h"
#include "ClientGameDlg.h"
extern void GetNumString(int nNum, CString &Str, int nPower,bool bIsBlank);
// CMsgBoxResult 对话框

IMPLEMENT_DYNAMIC(CMsgBoxResult, CDialog)

CMsgBoxResult::CMsgBoxResult(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgBoxResult::IDD, pParent)
{
	m_Time=0;
	m_msg="";
	m_nPowerOfGold=0;///20091231修改百亿
}

CMsgBoxResult::~CMsgBoxResult()
{
}

void CMsgBoxResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDOK, m_btleave);
}


BEGIN_MESSAGE_MAP(CMsgBoxResult, CDialog)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CMsgBoxResult::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


/**
 * CMsgBoxResult 消息处理程序
 */
void CMsgBoxResult::ShowMsg(TCHAR  szMsg[], int time,bool Showleave, GameResult gameResult, int nPowerOfGold)
{
	m_nPowerOfGold = nPowerOfGold;
	m_iFinish = gameResult;
	m_msg=szMsg;
	m_Time=time;

	// 2010-05-04 duanxiaohui
	/*SetTimer(IDR_HIDE,1000,NULL);
	TCHAR sz[100];
	wsprintf(sz,"确定%d",m_Time);
	m_btcancel.SetWindowText(sz);
	m_btcancel.SetTextColor(RGB(255, 255, 0), true);*/
	m_btcancel.ShowWindow(SW_HIDE);
	m_btleave.SetTextColor(RGB(255, 255, 0), true);
	CRect rect, clientRect;
	m_btcancel.GetClientRect(&rect);
	GetClientRect(&clientRect);
	m_btcancel.MapWindowPoints(this,(LPPOINT)&rect,2);

	if(Showleave)
	{
		m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-150)/2,clientRect.bottom - 28,0,0,SWP_NOSIZE|SWP_NOZORDER);
		m_btleave.SetWindowPos(NULL,(m_bkImg.GetWidth()-150)/2+100,clientRect.bottom - 28,0,0,SWP_NOSIZE|SWP_NOZORDER);
	}
	else
		m_btcancel.SetWindowPos(NULL,(m_bkImg.GetWidth()-70)/2,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	m_btleave.ShowWindow(Showleave);

	Invalidate();
	ShowWindow(SW_SHOW);
}

void CMsgBoxResult::OnTimer(UINT_PTR nIDEvent)
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

void CMsgBoxResult::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	//CDialog::OnLButtonDown(nFlags, point);
}

void CMsgBoxResult::OnPaint()
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
	//int x=24;//ClientRect.left+20;
	//int y=ClientRect.Height()/2 - 34;
	
	CRect rect;
	TCHAR sz[100];
	CFont Font;
	Font.CreateFont(14,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	CFont *OldFont=dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255,255,255));
	dc.SetBkMode(TRANSPARENT);

	//int StartX = 222;
	//int StartY = 78;
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		if(strlen(m_iFinish.name[i]) <= 0)
			continue;
		if(m_iFinish.iWardPoint[i] > 0||m_iFinish.iMoney[i]>0)
		{
			dc.SetTextColor(RGB(255,0,0));
		}
		else
		{
			dc.SetTextColor(RGB(0,0,0));
		}

		wsprintf(sz,"%s",m_iFinish.name[i]);
		rect.left=m_iGameEndX;
		rect.right=rect.left+80;
		rect.top=m_iGameEndY+33*i;
		rect.bottom=rect.top+33;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		wsprintf(sz,TEXT("%d"), m_iFinish.iWardPoint[i]);
		rect.left=225;
		rect.right=rect.left+70;
		rect.top=m_iGameEndY+33*i;
		rect.bottom=rect.top+33;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		CString strMoney;
		GetNumString(m_iFinish.iMoney[i],strMoney,m_nPowerOfGold,false);
		wsprintf(sz,TEXT("%s"),strMoney);

		rect.left=306;
		rect.right=rect.left+70;
		rect.top=m_iGameEndY+33*i;
		rect.bottom=rect.top+33;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		if(m_iFinish.iWardPoint[i] > 0||m_iFinish.iMoney[i]>0)
			wsprintf(sz,".\\image\\win.bmp");
		else if(m_iFinish.iWardPoint[i] == 0 && m_iFinish.iMoney[i] == 0)
			wsprintf(sz,".\\image\\equal.bmp");
		else
			wsprintf(sz,".\\image\\lost.bmp");
		m_Flag.SetLoadInfo(sz,false);
		CGameImageHelper flag(&m_Flag);
		CDC srcDC;
		srcDC.CreateCompatibleDC(&dc);
		srcDC.SelectObject(flag);
		//flag.BitBlt(dc.GetSafeHdc(),StartX,StartY+33*i,SRCCOPY);
		::TransparentBlt(dc.GetSafeHdc(),m_iGameEndWinLostX+6,m_iGameEndWinLostY+ 33* i,flag.GetWidth(),flag.GetHeight(),
			srcDC.GetSafeHdc(),0,0,m_Flag.GetWidth(),m_Flag.GetHeight(),srcDC.GetPixel(0,0));
	}


	dc.DeleteDC();
}

BOOL CMsgBoxResult::OnInitDialog()
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

void CMsgBoxResult::OnBnClickedOk()
{
	::g_pCClientGameDlg->SendMessage(WM_CLOSE,0,0);
	//OnOK();
}

/**
 * 自动调整大小
 */
void CMsgBoxResult::AutoSize(int xValue,int yValue)
{
	MoveWindow(xValue,yValue-20,m_bkImg.GetWidth(),m_bkImg.GetHeight());
	Invalidate();
	UpdateWindow();
}


int CMsgBoxResult::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	TCHAR szName[MAX_PATH];

	wsprintf(szName,TEXT("image\\result.bmp"));
	m_bkImg.SetLoadInfo(szName,TRUE);

	wsprintf(szName,".\\image\\win.bmp");
	m_Flag.SetLoadInfo(szName,false);

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
	
#ifdef	VIDEO
		CBcfFile f( "30300405.bcf");
#else
		CBcfFile f( "30300400.bcf");
#endif

	CString key = TEXT("UISet");
	m_iGameEndX = f.GetKeyVal(key,TEXT("GameEndX"), 22);
	m_iGameEndY = f.GetKeyVal(key,TEXT("GameEndY"), 76);
	m_iGameEndLineSpace = f.GetKeyVal(key,TEXT("GameEndLineSpace"), 35);

	m_iGameEndWinLostX = f.GetKeyVal(key,TEXT("GameEndWinLostX"),133);
	m_iGameEndWinLostY = f.GetKeyVal(key,TEXT("GameEndWinLostY"), 78);


	return 0;
}