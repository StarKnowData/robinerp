#include "StdAfx.h"
#include "GameFinishDlg.h"
#include "Resource.h"
#include "../../include/GameLaunchSdk/CommonDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CGameFinishDlg, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_MOVE()
END_MESSAGE_MAP()

//构造函数
CGameFinishDlg::CGameFinishDlg(void)// :CGameFaceGo(CGameFinishDlg::IDD)
{
	//C++ TEST
	::ZeroMemory(&m_iFinish,sizeof(m_iFinish));
	m_pParnet = NULL;
	m_nPowerOfGold=0;	

	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));


	//AfxSetResourceHandle(GetModuleHandle(NULL));
}
//
int CGameFinishDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	TCHAR szName[MAX_PATH];
	wsprintf(szName,TEXT(".\\image\\result.bmp"));
	m_bk.SetLoadInfo(szName,TRUE);

	wsprintf(szName,".\\image\\win.bmp");
	m_Flag.SetLoadInfo(szName,false);

	CRect ClientRect;
	GetClientRect(&ClientRect);
	//this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	HRGN hRgn=AFCBmpToRgn(help,RGB(255,0,255),RGB(1,0,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,help.GetWidth(),help.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
	}

	return 0;
}
//析构函数
CGameFinishDlg::~CGameFinishDlg(void)
{
}

//重画函数
void CGameFinishDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect ClientRect;
	GetClientRect(&ClientRect);
	//this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	//this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	//help.BitBlt(dc.GetSafeHdc(),0,0);
	CDC srcDC;
	srcDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBmp = srcDC.SelectObject(help);
	::TransparentBlt(dc.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),
		srcDC.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),srcDC.GetPixel(0,0));
	srcDC.SelectObject(pOldBmp);

	GetClientRect(&ClientRect);
	
	CRect rect;
	TCHAR sz[100];
	CFont Font;
	//TCHAR szMsg[50]="";
	//	Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	Font.CreateFont(14,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	CFont *OldFont=dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255,255,255));
	dc.SetBkMode(TRANSPARENT);

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		if(strlen(m_iFinish.name[i]) <= 0)
			continue;
		/*if(m_iViewStation==i)
		dc.SetTextColor(RGB(255,0,0));
		else
		dc.SetTextColor(RGB(0,0,0));*/
		if(m_iFinish.iWardPoint[i] > 0||m_iFinish.iMoney[i]>0)
		{
			dc.SetTextColor(RGB(255,0,0));
		}
		else
		{
			dc.SetTextColor(RGB(0,0,0));
		}

		//TCHAR ch[20];
		//GetChar(m_iFinish.name[i],ch,10);
		wsprintf(sz,"%s",m_iFinish.name[i]);
		rect.left=m_iGameEndX;
		rect.right=rect.left+80;
		rect.top=m_iGameEndY+m_iGameEndLineSpace*i;
		rect.bottom=rect.top+35;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		wsprintf(sz,"%I64d",m_iFinish.iWardPoint[i]);
		rect.left=225;
		rect.right=rect.left+70;
		rect.top=m_iGameEndY+m_iGameEndLineSpace*i;
		rect.bottom=rect.top+35;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		//wsprintf(sz,"%d",m_iFinish.iMoney[i]);
		//CString str="";
		//GetNumString(m_iFinish.iMoney[i],str,m_nPowerOfGold);
		char str[MAX_PATH] = {0};
		GlbGetNumString(str,m_iFinish.iMoney[i],m_nPowerOfGold,FALSE,"");
		rect.left=307;
		rect.right=rect.left+70;
		rect.top=m_iGameEndY+m_iGameEndLineSpace*i;
		rect.bottom=rect.top+35;
		dc.DrawText(str,lstrlen(str),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		//dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		if(m_iFinish.iWardPoint[i] > 0||m_iFinish.iMoney[i]>0)
			wsprintf(sz,".\\image\\win.bmp");
		else if(m_iFinish.iWardPoint[i] == 0&&m_iFinish.iMoney[i]==0)
			wsprintf(sz,".\\image\\equal.bmp");
		else
			wsprintf(sz,".\\image\\lost.bmp");
		m_Flag.SetLoadInfo(sz,false);
		CGameImageHelper flag(&m_Flag);
		//CDC srcDC;
		srcDC.CreateCompatibleDC(&dc);
		CBitmap *pOldBmp = srcDC.SelectObject(flag);
		//flag.BitBlt(dc.GetSafeHdc(),StartX,StartY+33*i,SRCCOPY);
		::TransparentBlt(dc.GetSafeHdc(),m_iGameEndWinLostX+5,m_iGameEndWinLostY+m_iGameEndLineSpace* i,flag.GetWidth(),flag.GetHeight(),
			srcDC.GetSafeHdc(),0,0,m_Flag.GetWidth(),m_Flag.GetHeight(),srcDC.GetPixel(0,0));
		srcDC.SelectObject(pOldBmp);
		srcDC.DeleteDC();
	}

	__super::OnPaint();
	return ;
}

//自动调整大小
void CGameFinishDlg::AutoSize(int xValue,int yValue)
{
	MoveWindow(xValue,yValue,m_bk.GetWidth(),m_bk.GetHeight());
	Invalidate(FALSE);
	UpdateWindow();
}


void CGameFinishDlg::SetMessage(GameFinishNotify finishnotify,BYTE iViewStation,bool bInVideoRoom)
{	
	CString strMsg;


	m_iFinish=finishnotify;
	m_iViewStation=iViewStation;
	TCHAR szName[MAX_PATH];

	//wsprintf(szName,TEXT(".\\image\\result.bmp"),SKIN);
	CString s = CBcfFile::GetAppPath ();/////本地路径

	//CBcfFile f( "GameOption.bcf");
	CBcfFile f(GET_CLIENT_BCF_NAME(szTempStr));
	
	CString key = TEXT("UISet");
	if(bInVideoRoom)
		key="VideoUISet";

	CString sec = _T("");

	//sec.Format("ResultImg%d", m_iFinish.iGameStyle);
	//wsprintf(szName,f.GetKeyVal(key, sec, ""));


	m_iGameEndX = f.GetKeyVal(key,TEXT("GameEndX"), 22);
	m_iGameEndY = f.GetKeyVal(key,TEXT("GameEndY"), 76);
	m_iGameEndLineSpace = f.GetKeyVal(key,TEXT("GameEndLineSpace"), 35);

	m_iGameEndWinLostX = f.GetKeyVal(key,TEXT("GameEndWinLostX"), 133);
	m_iGameEndWinLostY = f.GetKeyVal(key,TEXT("GameEndWinLostY"), 78);


	//m_bk.SetLoadInfo(szName,TRUE);
	MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight(),TRUE);
	CenterWindow();

	//strMsg.Format("img1:%s; wid:%d,hei:%d",szName,m_bk.GetWidth(),m_bk.GetHeight());
	//OutputDebugString(strMsg);


	//Invalidate(TRUE);
	//UpdateWindow();
	return;
}

void CGameFinishDlg::OnLButtonDown(UINT nFags,CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	return ;
}


void CGameFinishDlg::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);
	InvalidateRect(NULL);
}
void CGameFinishDlg::GetNumString(int nNum, CString &Str, int nPower)
{
	if (0 == nNum)
	{
		Str.Format("0");
		return;
	}
	/// 暂存结果
	TCHAR strTmp[32];
	TCHAR str[50];
	/// 目前只处理大于0的情况，在正常字符串后面要加至少一个0
	wsprintf( strTmp, TEXT("%d"), nNum);
	for (int i=0; i<nPower; ++i)
	{
		_tcscat( strTmp, TEXT("0"));
	}
	/// 按位数每三位空一格显示
	int nLen = _tcslen(strTmp);	// 字符串长度
	int nTimes = nLen % 3;	// 这个字符串可以分成的节数，至少是1节

	int nSrc = 0;
	int nDes = 0;

	for (int i=0; i<nLen; ++i)
	{
		//if ((i>0)&&(i%3==nTimes))
		//{
		//	str[nDes++] = TEXT('');
		//}
		str[nDes++] = strTmp[nSrc++];
	}
	str[nDes] = TEXT('\0');
	Str.Format("%s",str);
	return ;
}

