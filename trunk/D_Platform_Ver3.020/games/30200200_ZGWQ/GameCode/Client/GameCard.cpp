#include "Stdafx.h"
#include "Resource.h"
#include "GameCard.h"
#include "ClientGameDlg.h"
#include ".\gamecard.h"
//#include "..\..\游戏开发开发库\include\服务器组件\Common\writelog.h"

BEGIN_MESSAGE_MAP(CUpGradeGameCard, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
//	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

//构造函数
CUpGradeGameCard::CUpGradeGameCard()
{
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	if (GetSystemMetrics(SM_CXSCREEN)>=1024)
	{
		m_iQZiWidth = 43;
		
		TCHAR path[MAX_PATH] = {0};
		wsprintf(path,TEXT(".\\image\\%s\\board.bmp"),SKIN_FOLDER);
		m_BoardPic.SetLoadInfo(path,true);		
		wsprintf(path,TEXT(".\\image\\%s\\wqfocus.bmp"),SKIN_FOLDER);
		m_bitFocus.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\curblack.bmp"),SKIN_FOLDER);
		m_bitCurBlack.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\wqcurWhite.BMP"),SKIN_FOLDER);
		m_bitCurWhite.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\heiqi.bmp"),SKIN_FOLDER);
		m_bitBlack.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\baiqi.bmp"),SKIN_FOLDER);
		m_bitWhite.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\heiguan.bmp"),SKIN_FOLDER);
		m_bitHeiGuan.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\baiguan.bmp"),SKIN_FOLDER);
		m_bitBaiGuan.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\bcross.bmp"),SKIN_FOLDER);
		m_bitBCross.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\wcross.bmp"),SKIN_FOLDER);
		m_bitWCross.SetLoadInfo(path,true);
	}
	else
	{
		m_iQZiWidth = 43;
		TCHAR path[MAX_PATH] = {0};
		wsprintf(path,TEXT(".\\image\\%s\\board.bmp"),SKIN_FOLDER);
		m_BoardPic.SetLoadInfo(path,true);		
		wsprintf(path,TEXT(".\\image\\%s\\wqfocus.bmp"),SKIN_FOLDER);
		m_bitFocus.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\curblack.bmp"),SKIN_FOLDER);
		m_bitCurBlack.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\wqcurWhite.BMP"),SKIN_FOLDER);
		m_bitCurWhite.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\heiqi.bmp"),SKIN_FOLDER);
		m_bitBlack.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\baiqi.bmp"),SKIN_FOLDER);
		m_bitWhite.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\heiguan.bmp"),SKIN_FOLDER);
		m_bitHeiGuan.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\baiguan.bmp"),SKIN_FOLDER);
		m_bitBaiGuan.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\bcross.bmp"),SKIN_FOLDER);
		m_bitBCross.SetLoadInfo(path,true);
		wsprintf(path,TEXT(".\\image\\%s\\wcross.bmp"),SKIN_FOLDER);
		m_bitWCross.SetLoadInfo(path,true);
	}


	m_iMeFlag = -1;
	m_iCurPlay = -1;
	m_iBoardWidth = 0;
	m_iBoardHeight = 0;
	m_bInitBoard = TRUE;
	m_bIsPlay = FALSE;
	m_iEndI = m_iEndJ = -1;
	m_iStartI = m_iStartJ = -1;

	::memset(m_iBoard,0,sizeof(m_iBoard));
	::memset(m_iTiZiNum,0,sizeof(m_iTiZiNum));

	m_iFocusX = -1;
	m_iFocusY = -1;
	m_bUseMouseFlag = false;
	m_bIsFinish = false;
	m_strFinishMessage.Empty();

	m_iJuMin = 0;
	m_iJuSec = 0;
	m_iBuMin = 0;
	m_iBuSec = 0;
	m_iDuMin = 0;
	m_iDuSec = 0;
	
	m_iTopJuUseTime = 0;
	m_iTopBuUseTime = 0;
	m_iTopDuUseTime = 0;
	m_iBotJuUseTime = 0;
	m_iBotBuUseTime = 0;
	m_iBotDuUseTime = 0;

	

//	m_iCardUpSpace=19;
	m_pHandleWnd=NULL;
//	m_bHorzLook=true;
//	m_bShowCard=false;
	m_bUseMouse=false;
//	m_bHotHitCard=255;
	m_PtBasePoint.SetPoint(0,0);
	m_XShowMode=XShowMode::SWX_MODE_CENTER;
	m_YShowMode=YShowMode::SWY_MODE_CENTER;
	memset(m_pUserInfo,0,sizeof(m_pUserInfo));
	AfxSetResourceHandle(GetModuleHandle(NULL));
}

//析构函数
CUpGradeGameCard::~CUpGradeGameCard()
{
}

//初始化函数
bool CUpGradeGameCard::InitGameCard(CWnd * pHandleWnd)
{
	m_pHandleWnd=pHandleWnd;
	return true;
}

//设置扑克参数
void CUpGradeGameCard::SetCardParameter(int iHSpace, int iVSpace, int iUpSpace)
{

	return;
}

//获取大小函数
bool CUpGradeGameCard::GetCardSize(CSize & Size)
{
	return true;
}

//设置基准点函数
void CUpGradeGameCard::SetBasePoint(CPoint & BasePoint, XShowMode XShowMode, YShowMode YShowMode)
{
	m_PtBasePoint=BasePoint;
	m_iBoardWidth = m_BoardPic.GetWidth();
	m_iBoardHeight = m_BoardPic.GetHeight();
	//FixCardControl();
	return;
}


//设置使用鼠标
void CUpGradeGameCard::SetUseMouse(bool bUserMouse)
{
	m_bUseMouse=bUserMouse;
	return;
}


//设置棋盘
void CUpGradeGameCard::SetBoard(CDC &memDC)
{
	CPaintDC dc(this);
	CRect rect;
	CBitmap bitBuffer;
	GetClientRect(&rect);
	memDC.CreateCompatibleDC(&dc);
	bitBuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	memDC.SelectObject(&bitBuffer);
	CGameImageHelper BoardHandle(&m_BoardPic);
	BoardHandle.BitBlt(memDC.GetSafeHdc(),0,0,SRCCOPY);
	
	#ifdef	VIDEO
	CString  strVideoCfg=CINIFile::GetAppPath()+TEXT("VideoCfg.ini");
	CINIFile iniFile(strVideoCfg);
	int	 m_heightVideo=0,m_widthVideo=0;
	m_widthVideo
		=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("WidthVideoWQ"), 0);
	m_heightVideo
		=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("HeightVideoWQ"), 0);


	m_PtVideo[0].x = 3;
	m_PtVideo[0].y = XQ_UPPEOPLE_LOG_Y - 5;
	
	m_PtVideo[1].x = 3;
	m_PtVideo[1].y = XQ_DOWNPEOPLE_LOG_Y - 5;
	
	///视频底图
	CGameImageHelper bg(&m_pVideoFrame);
	if(NULL != m_pUserInfo[0])
	{
		CDC dc;
		dc.CreateCompatibleDC(&memDC);
		dc.SelectObject(bg);
		::TransparentBlt(memDC,m_PtVideo[0].x, m_PtVideo[0].y,m_widthVideo, m_heightVideo,dc.GetSafeHdc(),\
			0,0,m_widthVideo, m_heightVideo,dc.GetPixel(0,0));
		dc.DeleteDC();
		//bg.BitBlt(memDC.GetSafeHdc(), m_PtVideo[0].x, m_PtVideo[0].y, m_widthVideo, m_heightVideo,0,0, SRCCOPY);
	}
	if(NULL != m_pUserInfo[1])
	{
		CDC dc;
		dc.CreateCompatibleDC(&memDC);
		dc.SelectObject(bg);
		::TransparentBlt(memDC,m_PtVideo[1].x, m_PtVideo[1].y,m_widthVideo, m_heightVideo,dc.GetSafeHdc(),\
			0,0,m_pVideoFrame.GetWidth(),m_pVideoFrame.GetHeight(),dc.GetPixel(0,0));
		dc.DeleteDC();
		//bg.BitBlt(memDC.GetSafeHdc(), m_PtVideo[1].x, m_PtVideo[1].y, m_widthVideo, m_heightVideo, 0,0,SRCCOPY);
	}
#endif



	return;
}


//设置棋子
void CUpGradeGameCard::SetQiZi(int i,int j, int type, CDC *memDC)
{
	if (i < 0 || i > WQ_MAX_I || j < 0 || j > WQ_MAX_J) return;
	if (!memDC) return;
	int x = WQ_BOARD_X + (j - 1) * WQ_RECT_W - WQ_QIZI_R/2;
	int y = WQ_BOARD_Y + (i - 1) * WQ_RECT_W - WQ_QIZI_R/2;
	if (type == WQ_FLAG_BLACK_CROSS || type == WQ_FLAG_WHITE_CROSS)
	{
		x = WQ_BOARD_X + (j - 1) * WQ_RECT_W - 9/2 - 1;
		y = WQ_BOARD_Y + (i - 1) * WQ_RECT_W - 9/2 - 1;

	}

	ShowQiZi(x,y,type,memDC);
	return;
}


//显示棋子
void CUpGradeGameCard::ShowQiZi(int iDestX, int iDestY, int type, CDC *memDC)
{
	if (!memDC) return;
	int sx = 0, sy = 0;
	int w,h;
	w = WQ_QIZI_R;
	h = WQ_QIZI_R;
	
	CGameImage *bit = NULL;
	switch (type)
	{
	
	case WQ_FLAG_BLACK:
		bit = &m_bitBlack;
		break;

	case WQ_FLAG_WHITE:
		bit = &m_bitWhite;
		break;

	case WQ_FLAG_CUR_BLACK:
		bit = &m_bitCurBlack;
		break;

	case WQ_FLAG_CUR_WHITE:
		bit = &m_bitCurWhite;
		break;

	case WQ_FLAG_BLACK_CROSS:
		bit = &m_bitBCross;
		break;

	case WQ_FLAG_WHITE_CROSS:
		bit = &m_bitWCross;
		break;
	}
	
	if (bit)
	{
		CDC mdc;
		mdc.CreateCompatibleDC(memDC);
		CGameImageHelper handle(bit);
		mdc.SelectObject(handle);
		w = bit->GetWidth();
		h = bit->GetHeight();
		this->TransparentBlt(memDC,iDestX,iDestY,w,h,&mdc,sx,sy,w,h,mdc.GetPixel(0,0));
		mdc.DeleteDC();
	}
	return;
}


//设置棋局
void CUpGradeGameCard::SetChess(int iMeFlag, int iCurPlay, int qi[][21], BOOL initBoard)
{	
	
	m_iMeFlag = iMeFlag;
	m_iCurPlay = iCurPlay;
	m_bInitBoard = initBoard;
	::CopyMemory(m_iBoard,qi,sizeof(m_iBoard));
	
	Invalidate(FALSE);
	return;
}


//get init time string
void CUpGradeGameCard::GetInitTimeString(int iMinute, int iSec, CString &str)
{
	str.Empty();

	CString s;
	s.Format("%d",iMinute);
	if (iMinute < 10) s = TEXT("0") + s;
	str = s + TEXT("分");
	s.Format("%d",iSec);
	if (iSec < 10) s = TEXT("0") + s;
	s += TEXT("秒");

	str += s;
	return;
}

//get time string 
void CUpGradeGameCard::GetTimeString(int iSec, CString &str)
{
	if (iSec < 0) iSec = 0;
	str.Empty();

	int second = iSec % 60,
		minute = iSec / 60;
	CString s;
	
	s.Format("%d",minute);
	if (minute < 10) s = TEXT("0") + s;
	str = s + TEXT(":");
	s.Format("%d",second);
	if (second < 10) s = TEXT("0") + s;
	str += s;

	return;
}

void CUpGradeGameCard::SetFinishMessage(CString strMessage, bool bIsFinish)
{
	m_bIsFinish = bIsFinish;
	if (!strMessage.IsEmpty()) 
		m_strFinishMessage = strMessage;
	Invalidate(FALSE);
	return;
}


void CUpGradeGameCard::ShowFinishMessage(CDC *memDC)
{
	if (!memDC) return;
	if (!m_strFinishMessage.IsEmpty())
	{
		CFont font;
		font.CreateFont(-50,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
		CFont *pOldFont = memDC->SelectObject(&font);
		memDC->SetTextColor(RGB(125,221,180));
		memDC->SetBkMode(TRANSPARENT);
		memDC->TextOut(245,160,m_strFinishMessage);
		memDC->SelectObject(pOldFont);
		font.DeleteObject();
	}
	return;
}

//启动定时器
void CUpGradeGameCard::SetTimerCount()
{
	SetTimer(1,1000,NULL);
	return;
}


//set init time
void CUpGradeGameCard::SetPlayTime(int iJuMin, int iJuSec, int iBuMin, int iBuSec, int iDuMin, int iDuSec)
{
	m_iJuMin = iJuMin;
	m_iJuSec = iJuSec;
	m_iBuMin = iBuMin;
	m_iBuSec = iBuSec;
	m_iDuMin = iDuMin;
	m_iDuSec = iDuSec;

	return;
}

//set init info
void CUpGradeGameCard::SetInitInfo(CDC *memDC, bool bFlag)
{
	if (!memDC) return;

	int	iLeftRangZiX = XQ_UPPEOPLE_X,
		iLeftRangZiY = XQ_UP_RANGZI_Y,

		iLeftTiZiX	 = XQ_UPPEOPLE_X,
		iLeftTiZiY	 = XQ_UP_TIZI_Y,
		
		iRightTieMuX = XQ_UPPEOPLE_X,
		iRightTieMuY = XQ_DOWN_RANGZI_Y,

		iRightTiZiX  = XQ_UPPEOPLE_X,
		iRightTiZiY  = XQ_DOWN_TIZI_Y;

	CString s;
	s = TEXT("0");
	
	CFont font;
	font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	CFont *pOldFont = memDC->SelectObject(&font);
	memDC->SetBkMode(TRANSPARENT);

	if (bFlag)
		memDC->TextOut(iLeftRangZiX,iLeftRangZiY,s);
	s=TEXT("0");
	if (bFlag)
		memDC->TextOut(iLeftTiZiX,iLeftTiZiY,s);
	memDC->TextOut(iRightTiZiX,iRightTiZiY,s);

	if(m_iMeFlag==1)
		s = TEXT("0");
	else
		s = TEXT("3又3/4");
	memDC->TextOut(iRightTieMuX,iRightTieMuY,s);

	memDC->SelectObject(pOldFont);
	font.DeleteObject();
}


//set time display
void CUpGradeGameCard::SetTimeDisplay(int iDestX, int iDestY, CString &str, CDC *memDC, COLORREF crColor)
{
	if (!memDC) return;
	CFont Font;
	Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	CFont *pOldFont = memDC->SelectObject(&Font);
	memDC->SetTextColor(crColor);
	memDC->SetBkMode(TRANSPARENT);

	memDC->TextOut(iDestX,iDestY,str);
	
	memDC->SelectObject(pOldFont);
	Font.DeleteObject();
	return;
}

//显示走子标志
void CUpGradeGameCard::ShowPlayFlag(CDC *memDC)
{
	if (!memDC || m_iFocusX < 0 || m_iFocusY < 0) return;
	
	if ((m_iFocusX > 0 || m_iFocusY > 0) && m_bUseMouse)
	{
		CDC mdc;
		int w,h;
		w = m_bitFocus.GetWidth();
		h = m_bitFocus.GetHeight();
		mdc.CreateCompatibleDC(memDC);
		CGameImageHelper handle(&m_bitFocus);
		mdc.SelectObject(handle);
		this->TransparentBlt(memDC,m_iFocusX,m_iFocusY,w,h,&mdc,0,0,w,h,RGB(255,255,255));
		mdc.DeleteDC();
	}
	return ;
}


//设置走棋标志
void CUpGradeGameCard::SetPlayFlag(int iStartI, int iStartJ, int iEndI, int iEndJ, BOOL bIsPlay)
{
	return;
}


//显示该谁走
void CUpGradeGameCard::ShowGeneralFlag(CDC *memDC)
{
	if (!memDC)
		return;
	if (m_pUserInfo[0] == NULL && m_iCurPlay != m_iMeFlag) 
		return;
	CDC mdc;
	mdc.CreateCompatibleDC(memDC);
	CGameImage *bit = NULL;
	int iDestX,iDestY;
	int w,h;
	if (m_iCurPlay != m_iMeFlag)
	{
		iDestX = XQ_UP_FLAG_X;
		iDestY = XQ_UP_FLAG_Y;
	}
	else if (m_iCurPlay == m_iMeFlag)
	{		
		iDestX = XQ_DOWN_FLAG_X;
		iDestY = XQ_DOWN_FLAG_Y;
	}
	if(m_iCurPlay==WQ_PLAY_FLAG_BLACK)
		bit = &m_bitHeiGuan;
	else if(m_iCurPlay==WQ_PLAY_FLAG_WHITE)
		bit = &m_bitBaiGuan;
	if (bit)
	{
		CGameImageHelper handle(bit);
		mdc.SelectObject(handle);
		w = bit->GetWidth();
		h = bit->GetHeight();
		this->TransparentBlt(memDC,iDestX,iDestY,w,h,&mdc,0,0,w,h,mdc.GetPixel(0,0));
	}
	
	mdc.DeleteDC();
	return;
}


//设置提子数
void CUpGradeGameCard::SetTiZiNum(int iNum[])
{
	m_iTiZiNum[WQ_PLAY_FLAG_BLACK] = iNum[WQ_PLAY_FLAG_BLACK];
	m_iTiZiNum[WQ_PLAY_FLAG_WHITE] = iNum[WQ_PLAY_FLAG_WHITE];
	Invalidate(FALSE);
	return;
}

//显示提子数
void CUpGradeGameCard::ShowTiZiNum(CDC *memDC)
{
	if (!memDC) return;

	int	iLeftRangZiX = XQ_UPPEOPLE_X,
		iLeftRangZiY = XQ_UP_RANGZI_Y,

		iLeftTiZiX	 = XQ_UPPEOPLE_X,
		iLeftTiZiY	 = XQ_UP_TIZI_Y,
		
		iRightTieMuX = XQ_UPPEOPLE_X,
		iRightTieMuY = XQ_DOWN_RANGZI_Y,

		iRightTiZiX  = XQ_UPPEOPLE_X,
		iRightTiZiY  = XQ_DOWN_TIZI_Y;

	CFont font;
	font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	CFont *pOldFont = memDC->SelectObject(&font);
	memDC->SetBkMode(TRANSPARENT);
	
	CString s;
	
	if(m_iMeFlag==0)
		s = TEXT("0");
	else
		s = TEXT("3又3/4");
	if (m_pUserInfo[0]!=NULL)
		memDC->TextOut(iLeftRangZiX,iLeftRangZiY,s);
	
	if(m_iMeFlag==1)
		s = TEXT("0");
	else
		s = TEXT("3又3/4");
	memDC->TextOut(iRightTieMuX,iRightTieMuY,s);

	s.Format("%d",TEXT(m_iTiZiNum[WQ_PLAY_FLAG_BLACK]));
	memDC->TextOut(iRightTiZiX,iRightTiZiY,s);
		
	s.Format("%d",TEXT(m_iTiZiNum[WQ_PLAY_FLAG_WHITE]));
	if (m_pUserInfo[0]!=NULL)
		memDC->TextOut(iLeftTiZiX,iLeftTiZiY,s);	
	
	memDC->SelectObject(pOldFont);
	font.DeleteObject();
	return;
}
//设置用户信息
void CUpGradeGameCard::SetUserInfo(UserItemStruct *m_UserInfo, int iStation)
{
	m_pUserInfo[iStation]=m_UserInfo;
	return;
}

//调整窗口位置
void CUpGradeGameCard::FixCardControl()
{
	MoveWindow(m_PtBasePoint.x,m_PtBasePoint.y,m_iBoardWidth,m_iBoardHeight);
	return;
}

//建立消息
int CUpGradeGameCard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	TCHAR path[MAX_PATH] = {0};
#ifdef	VIDEO
	wsprintf(path,TEXT(".\\image\\VideoFrame.bmp"),SKIN_FOLDER);
	m_pVideoFrame.SetLoadInfo(path,false);
#endif


	if (CWnd::OnCreate(lpCreateStruct)==-1) return -1;
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);
	return 0;
}

//重画函数
void CUpGradeGameCard::OnPaint()
{
	CPaintDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	CFont Font, *OldFont;
	Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));	
	CClientGameDlg *pClientGameDlg = (CClientGameDlg *)(GetParent()->GetParent());

	CDC BufferDC;	
	SetBoard(BufferDC);	
	OldFont = BufferDC.SelectObject(&Font);
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(RGB(255,255,255));

	if (!m_bInitBoard)
	{
		for (int i = 0;i < 21;i++)
			for (int j = 0;j < 21;j++)
			{
				int type = m_iBoard[i][j];
				if (type == WQ_FLAG_NONE || type == WQ_FLAG_SIDE) 
					continue;
				SetQiZi(i,j,type,&BufferDC);
			}
		CString str;
		GetInitTimeString(m_iJuMin,m_iJuSec,str);
		SetTimeDisplay(XQ_INIT_SET_JU_TIME_X,XQ_INIT_SET_JU_TIME_Y,str,&BufferDC,RGB(255,255,255));
			
		GetInitTimeString(m_iBuMin,m_iBuSec,str);
		SetTimeDisplay(XQ_INIT_SET_BU_TIME_X,XQ_INIT_SET_BU_TIME_Y,str,&BufferDC,RGB(255,255,255));	
		
		ShowTiZiNum(&BufferDC);
		ShowPlayFlag(&BufferDC);	
		ShowGeneralFlag(&BufferDC);

		if (m_bIsFinish)
			ShowFinishMessage(&BufferDC);
	
		//显示走子时间
		CString s;
		///下方
		GetTimeString(m_iBotJuUseTime,s);
		SetTimeDisplay(XQ_SET_BOT_JU_TIME_X,XQ_SET_BOT_JU_TIME_Y,s,&BufferDC,RGB(255,255,255));
				
		GetTimeString(m_iBotBuUseTime,s);
		SetTimeDisplay(XQ_SET_BOT_BU_TIME_X,XQ_SET_BOT_BU_TIME_Y,s,&BufferDC,RGB(255,255,255));

		///上方
		GetTimeString(m_iTopJuUseTime,s);
		if (m_pUserInfo[0]!=NULL)//----------------用户不存在时，不显示时间等信息----------------
			SetTimeDisplay(XQ_SET_TOP_JU_TIME_X,XQ_SET_TOP_JU_TIME_Y,s,&BufferDC,RGB(255,255,255));

		GetTimeString(m_iTopBuUseTime,s);
		if (m_pUserInfo[0]!=NULL)//----------------用户不存在时，不显示时间等信息----------------
			SetTimeDisplay(XQ_SET_TOP_BU_TIME_X,XQ_SET_TOP_BU_TIME_Y,s,&BufferDC,RGB(255,255,255));
	
		TCHAR sz[100];
		if (m_pUserInfo[0]!=NULL)//----------------用户不存在时，不显示时间等信息----------------
			BufferDC.TextOut(XQ_UPPEOPLE_X,XQ_UP_MUSU_Y,sz,wsprintf(sz,"%d",m_iQiZiNum[(m_iMeFlag+1)%2]));
		BufferDC.TextOut(XQ_DOWNPEOPLE_X,XQ_DOWN_MUSU_Y,sz,wsprintf(sz,"%d",m_iQiZiNum[m_iMeFlag]));
		//用户头像与名称
		TCHAR nickname[100],m_szUserName[100];		
		if(m_pUserInfo[0]!=NULL)
		{
			memset(nickname,'\0',sizeof(nickname));
			lstrcpy(m_szUserName,m_pUserInfo[0]->GameUserInfo.nickName);
			strncpy(nickname,m_szUserName,lstrlen(m_szUserName)<11?lstrlen(m_szUserName):10);
			s.Format("%s",nickname);
			BufferDC.TextOut(XQ_UPPEOPLE_X,XQ_UPPEOPLE_Y,s);	
			pClientGameDlg->m_PlayView.DrawLogo(&BufferDC,m_pUserInfo[0]->GameUserInfo.bLogoID,XQ_UPPEOPLE_LOG_X,XQ_UPPEOPLE_LOG_Y,m_pUserInfo[0]->GameUserInfo.bUserState==USER_CUT_GAME,m_pUserInfo[0]->GameUserInfo.dwUserID,false,false);
		}
		if(m_pUserInfo[1]!=NULL)
		{
			memset(nickname,'\0',sizeof(nickname));
			lstrcpy(m_szUserName,m_pUserInfo[1]->GameUserInfo.nickName);
			strncpy(nickname,m_szUserName,lstrlen(m_szUserName)<11?lstrlen(m_szUserName):10);
			s.Format("%s",nickname);
			BufferDC.TextOut(XQ_DOWNPEOPLE_X,XQ_DOWNPEOPLE_Y,s);
			pClientGameDlg->m_PlayView.DrawLogo(&BufferDC,m_pUserInfo[1]->GameUserInfo.bLogoID,XQ_UPPEOPLE_LOG_X,XQ_DOWNPEOPLE_LOG_Y,m_pUserInfo[1]->GameUserInfo.bUserState==USER_CUT_GAME,m_pUserInfo[1]->GameUserInfo.dwUserID,false,false);
		}
	}
	else if (m_bInitBoard)
	{
		//用户头像与名称
		TCHAR nickname[100],m_szUserName[100];
		CString s;	
		if(m_pUserInfo[0]!=NULL)
		{
			memset(nickname,'\0',sizeof(nickname));
			lstrcpy(m_szUserName,m_pUserInfo[0]->GameUserInfo.nickName);
			strncpy(nickname,m_szUserName,lstrlen(m_szUserName)<11?lstrlen(m_szUserName):10);
			s.Format("%s",nickname);
			BufferDC.TextOut(XQ_UPPEOPLE_X,XQ_UPPEOPLE_Y,s);		
			pClientGameDlg->m_PlayView.DrawLogo(&BufferDC,m_pUserInfo[0]->GameUserInfo.bLogoID,XQ_UPPEOPLE_LOG_X,XQ_UPPEOPLE_LOG_Y,m_pUserInfo[0]->GameUserInfo.bUserState==USER_CUT_GAME,m_pUserInfo[0]->GameUserInfo.dwUserID,false,false);
		}
		if(m_pUserInfo[1]!=NULL)
		{
			memset(nickname,'\0',sizeof(nickname));
			lstrcpy(m_szUserName,m_pUserInfo[1]->GameUserInfo.nickName);
			strncpy(nickname,m_szUserName,lstrlen(m_szUserName)<11?lstrlen(m_szUserName):10);
			s.Format("%s",nickname);
			BufferDC.TextOut(XQ_DOWNPEOPLE_X,XQ_DOWNPEOPLE_Y,s);		
			pClientGameDlg->m_PlayView.DrawLogo(&BufferDC,m_pUserInfo[1]->GameUserInfo.bLogoID,XQ_UPPEOPLE_LOG_X,XQ_DOWNPEOPLE_LOG_Y,m_pUserInfo[1]->GameUserInfo.bUserState==USER_CUT_GAME,m_pUserInfo[1]->GameUserInfo.dwUserID,false,false);
		}		
	}

	if (m_pUserInfo[0]!=NULL)
	{
		if (m_pUserInfo[0]->GameUserInfo.bUserState==USER_ARGEE)		
			pClientGameDlg->m_PlayView.DrawArgeeFlag(&BufferDC,XQ_UPPEOPLE_X+50+15,XQ_UPPEOPLE_Y); 		
	}
	if (m_pUserInfo[1]!=NULL)
	{
		if (m_pUserInfo[1]->GameUserInfo.bUserState==USER_ARGEE)		
			pClientGameDlg->m_PlayView.DrawArgeeFlag(&BufferDC,XQ_DOWNPEOPLE_X+50+15,XQ_DOWNPEOPLE_Y);		
	}
	dc.BitBlt(0,0,m_iBoardWidth,m_iBoardHeight,&BufferDC,0,0,SRCCOPY);
	BufferDC.SelectObject(OldFont);
	BufferDC.DeleteDC();
	Font.DeleteObject();
	return;
}

//鼠标消息(下棋子)
void CUpGradeGameCard::OnLButtonDown(UINT nFlags, CPoint Point)
{
	if(!m_bUseMouse)
		return ;
	int ii = -1,jj = -1;
	for (int i = 0;i < WQ_MAX_I - 2;i++)
	{	
		bool bFind = false;
		for (int j = 0;j < WQ_MAX_J - 2;j++)
		{
			int dx = WQ_BOARD_ORG_X + j * WQ_RECT_W - Point.x;
			int dy = WQ_BOARD_ORG_Y + i * WQ_RECT_W - Point.y;
			int dr = dx * dx + dy * dy;
			if (dr <= (WQ_QIZI_R * WQ_QIZI_R) / 4)
			{
				ii = i;
				jj = j;
				bFind = true;
				break;
			}
		}
		if (bFind) break;
	}


	if(ii < 0 || ii > WQ_MAX_I - 2 || jj < 0 || jj > WQ_MAX_J - 2)	return;
		
	int iCurI = ii + 1;
	int iCurJ = jj + 1;
		
	///m_iCurI = ii;
	//m_iCurJ = jj;

	if (m_pHandleWnd != NULL)
		m_pHandleWnd->SendMessage(IDM_LEFT_HITCARD,iCurI,iCurJ);

	return;
}


//光标消息
BOOL CUpGradeGameCard::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message)
{
	if (m_bUseMouse==true && m_bUseMouseFlag == true)
	{
		//JMod-载入本地光标-20090505
		SetCursor(LoadCursor(GetModuleHandle(CLIENT_DLL_NAME),MAKEINTRESOURCE(IDC_HAND)));
		//SetCursor(CGameImageLink::m_hHandCursor);
		return TRUE;
	}
	else if (m_bUseMouse == false && m_bUseMouseFlag == true)
	{
		SetCursor(LoadCursor(GetModuleHandle(CLIENT_DLL_NAME),MAKEINTRESOURCE(IDC_DIS)));
		//SetCursor(CGameImageLink::m_SplitResource.m_hDisableCur);
		return TRUE;
	}
	return __super::OnSetCursor(pWnd,nHitTest,message);
}


//透明贴图
void CUpGradeGameCard::TransparentBlt(CDC *pDestDC, int iDestX, int iDestY, int iDestWidth, int iDestHeight,
									  CDC *pSrcDC, int iSrcX, int iSrcY, int iSrcWidth, int iSrcHeight, COLORREF transparentColor)
{
	SetStretchBltMode(pDestDC->GetSafeHdc(),COLORONCOLOR);

	::TransparentBlt(pDestDC->GetSafeHdc(),iDestX,iDestY,iDestWidth,iDestHeight,
					 pSrcDC->GetSafeHdc(),iSrcX,iSrcY,iSrcWidth,iSrcHeight,transparentColor);

	return;
}

void CUpGradeGameCard::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//int flg = m_iMeFlag * m_iCurPlay;

	if ( m_iMeFlag == m_iCurPlay)	//该我走
	{
		if (m_iBotJuUseTime < (m_iJuSec + m_iJuMin * 60))
		{
			m_iBotJuUseTime++;
			m_iBotBuUseTime++;

			if (0 == m_iBotBuUseTime%15)
			{
				/// 发送同步时间消息
				SyncTimeStruct	sMess;
				sMess.iBotJuUseTime = m_iBotJuUseTime;
				sMess.iBotBuUseTime = m_iBotBuUseTime;
				sMess.iBotDuUseTime = m_iBotDuUseTime;

				CClientPlayView *p = CONTAINING_RECORD(this, CClientPlayView, m_MeCard);
				((CClientGameDlg *)(p->GetParent()))->SendGameData(&sMess, sizeof(sMess), MDM_GM_GAME_NOTIFY, ASS_SYNC_TIME, 0);
			}
		}
		if (m_iBotJuUseTime >= (m_iJuSec + m_iJuMin * 60)) 
		{
			m_iBotDuUseTime++;	//局时超时开始读秒

			if (0 == m_iBotDuUseTime%15)
			{
				/// 发送同步时间消息
				SyncTimeStruct	sMess;
				sMess.iBotJuUseTime = m_iBotJuUseTime;
				sMess.iBotBuUseTime = m_iBotBuUseTime;
				sMess.iBotDuUseTime = m_iBotDuUseTime;

				CClientPlayView *p = CONTAINING_RECORD(this, CClientPlayView, m_MeCard);
				((CClientGameDlg *)(p->GetParent()))->SendGameData(&sMess, sizeof(sMess), MDM_GM_GAME_NOTIFY, ASS_SYNC_TIME, 0);
			}
		}

		if (m_iBotBuUseTime >= (m_iBuSec + m_iBuMin * 60) ||
			((m_iBotDuUseTime > 0) && (m_iBotDuUseTime > (m_iDuSec + m_iDuMin * 60)))
			)	//步时或读秒超时
		{
			if (m_pHandleWnd!=NULL) m_pHandleWnd->SendMessage(IDM_SUPER_TIMER);
			KillTimer(nIDEvent);
			
			m_iTopJuUseTime = 0;
			m_iTopBuUseTime = 0;
			m_iTopDuUseTime = 0;
			m_iBotJuUseTime = 0;
			m_iBotBuUseTime = 0;
			m_iBotDuUseTime = 0;
			return;
		}
		m_iTopBuUseTime = 0;
		m_iTopDuUseTime = 0;

	}

	else
	{
		if (m_iTopJuUseTime < (m_iJuSec + m_iJuMin * 60))
		{
			m_iTopJuUseTime++;
			m_iTopBuUseTime++;
		}
		if (m_iTopJuUseTime >= (m_iJuSec + m_iJuMin * 60)) m_iTopDuUseTime++;

		if (m_iTopBuUseTime >= (m_iBuSec + m_iBuMin * 60) ||
			((m_iTopDuUseTime > 0) && (m_iTopDuUseTime > (m_iDuSec + m_iDuMin * 60)))
			)	//步时或读秒超时
		{
			//if (m_pHandleWnd!=NULL) m_pHandleWnd->SendMessage(IDM_SUPER_TIMER);
			KillTimer(nIDEvent);

			m_iTopJuUseTime = 0;
			m_iTopBuUseTime = 0;
			m_iTopDuUseTime = 0;
			m_iBotJuUseTime = 0;
			m_iBotBuUseTime = 0;
			m_iBotDuUseTime = 0;
			return;
		}

		m_iBotBuUseTime = 0;
		m_iBotDuUseTime = 0;
	}
	
	this->Invalidate(FALSE);

	CWnd::OnTimer(nIDEvent);
}

void CUpGradeGameCard::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if ((point.x > 127 && point.x < 742) && (point.y > 6 && point.y < 620) )//&& m_bUseMouse)
	{
		m_bUseMouseFlag = true;
		

		CPoint ptBegin;
		ptBegin.SetPoint(WQ_BOARD_ORG_X,WQ_BOARD_ORG_Y-1);
		
		int iDistanceX = abs(point.x - ptBegin.x),
			iDistanceY = abs(point.y - ptBegin.y);
		
		//修正坐标
		if (iDistanceX % WQ_RECT_W >= WQ_RECT_W / 2) iDistanceX =iDistanceX - iDistanceX % WQ_RECT_W + WQ_RECT_W;
		else iDistanceX =iDistanceX - iDistanceX % WQ_RECT_W;

		if (iDistanceY % WQ_RECT_W >= WQ_RECT_W / 2) iDistanceY =iDistanceY - iDistanceY % WQ_RECT_W +WQ_RECT_W;
		else  iDistanceY =iDistanceY - iDistanceY % WQ_RECT_W;

		int row = iDistanceX / WQ_RECT_W,//鼠标移动所在的行
			col = iDistanceY / WQ_RECT_W;//鼠标移动所在的列

		int x = abs(point.x - ptBegin.x - row * WQ_RECT_W),
			y = abs(point.y - ptBegin.y - col * WQ_RECT_W);

		//if ( x < WQ_QIZI_R /2 || y < WQ_QIZI_R / 2)
		{
			m_iFocusX = ptBegin.x + row * WQ_RECT_W - WQ_QIZI_R / 2 - 1;//+1;
			m_iFocusY = ptBegin.y + col * WQ_RECT_W - WQ_QIZI_R / 2 - 1;//+1;
			
		}

		
		//else
		{
			//m_iFocusX = -1;
			//m_iFocusY = -1;
		}

		if (m_pHandleWnd != NULL) m_pHandleWnd->SendMessage(IDM_MOVE_ONCARD,col+1,row+1);
					
	}
	else 
	{
		m_iFocusX = -1;
		m_iFocusY = -1;
		m_bUseMouseFlag = false;
		
	}

	CRect rect;
	GetClientRect(&rect);
	rect.left+=170;
	rect.bottom-=70;
	InvalidateRect(&rect,false);

	CWnd::OnMouseMove(nFlags, point);
}

void CUpGradeGameCard::Init(void)
{
	memset(m_iQiZiNum,0,sizeof(m_iQiZiNum));
	for (int i = 0;i < WQ_MAX_I;i++)
		for(int j = 0;j < WQ_MAX_J;j++)
		{
			if (i == 0 || i == WQ_MAX_I - 1 || j == 0 || j == WQ_MAX_J - 1)
				m_iBoard[i][j] = WQ_FLAG_SIDE;
			else m_iBoard[i][j] = WQ_FLAG_NONE;
		}
	SetUseMouse(false);
	KillTimer(1);
	m_iTopJuUseTime=m_iTopBuUseTime=m_iTopDuUseTime=0;
	m_iBotJuUseTime=m_iBotBuUseTime=m_iBotDuUseTime=0;

}
