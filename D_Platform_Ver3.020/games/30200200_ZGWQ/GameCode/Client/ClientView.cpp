#include "StdAfx.h"
#include "ClientView.h"
#include "ClientGameDlg.h"

BEGIN_MESSAGE_MAP(CClientPlayView, CUsingSkinClass)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(IDC_GAME_BEGIN,IDC_HAVE_THING,OnHitButton)
END_MESSAGE_MAP()

/*******************************************************************************************************/

//构造函数
CClientPlayView::CClientPlayView(void) :m_GameSet(this),m_GameInfo(this)//,m_GameEndView(this)
{
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	AfxSetResourceHandle(GetModuleHandle(NULL));
	return;
}

//析构函数
CClientPlayView::~CClientPlayView(void)
{
}

//更新用户资料
void CClientPlayView::UpdateUserInfo(BYTE bViewStation)
{
	byte medesk = ((CClientGameDlg*)GetParent())->GetMeUserInfo()->bDeskStation;
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		if(m_pUserItem[i] == NULL)
		{
			m_MeCard.SetUserInfo(NULL,0);
			continue;
		}
		if(m_pUserItem[i]->GameUserInfo.bDeskStation == medesk)
		{
			m_MeCard.SetUserInfo(m_pUserItem[i],1);
		}
		else
			m_MeCard.SetUserInfo(m_pUserItem[i],0);
	}
	UpdateViewFace(NULL);
	m_MeCard.InvalidateRect(NULL);
	return;
}

//绘画界面函数
void CClientPlayView::DrawViewFace(CDC * pDC, int iWidth, int iHeight)
{
	CGameImageHelper LogoHandle(&m_PicGameView);
	pDC->FillSolidRect(0,0,iWidth,iHeight,LogoHandle.GetPixel(0,0));
	CDC *dc=m_MeCard.GetDC();
	DrawGif(dc,m_PtGif[m_iGifDeskStation].x,m_PtGif[m_iGifDeskStation].y);
	if (m_iFrameCount%3==0)
	{
		m_MeCard.Invalidate(false);
	}
	return ;
}

//透明绘制
void CClientPlayView::TransparentBlt2( HDC hdcDest,      // 目标DC
					int nXOriginDest,   // 目标X偏移
					int nYOriginDest,   // 目标Y偏移
					int nWidthDest,     // 目标宽度
					int nHeightDest,    // 目标高度
					HDC hdcSrc,         // 源DC
					int nXOriginSrc,    // 源X起点
					int nYOriginSrc,    // 源Y起点
					int nWidthSrc,      // 源宽度
					int nHeightSrc,     // 源高度
					UINT crTransparent  // 透明色,COLORREF类型
					)
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);

	// 将源DC中的位图拷贝到临时DC中
//	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
//	else
//		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
//					hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// 设置透明色
	SetBkColor(hImageDC, crTransparent);

	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(255,255,255));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	// 清理、恢复	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
}

//建立消息
int CClientPlayView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CUsingSkinClass::OnCreate(lpCreateStruct) == -1)
		return -1;
	//建立控件
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	
	TCHAR path[MAX_PATH] = {0};
#ifdef	VIDEO
	wsprintf(path,TEXT(".\\image\\VideoFrame.bmp"),SKIN_FOLDER);
	m_pVideoFrame.SetLoadInfo(path,false);
#endif


	//创建按钮
	m_btContinue.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,CRect(0,0,80,25),this,IDC_GAME_BEGIN);
	m_btLeave.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_LEAVE);
	m_btRegretChess.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_REGRET_CHESS);
	m_btStop.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_STOP);
	m_btAdmitDefeat.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_ADMIT_DEFEAT);
	m_btFinishDianMu.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_FINISH_DIAN_MU);
	m_btChessManual.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_CHESS_MANUAL);
	m_btThing.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_HAVE_THING);

	m_GameNoteView.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,50,NULL);
	m_GameNoteView.AutoSize();
	//结算
	m_Result.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,51,NULL);


	m_msgbox.Create(IDD_MSGBOX,this);
	//设置按钮背景图
	CGameImage m_bk;
	HRGN hRgn;
	TCHAR szName[MAX_PATH];
	//加载图片
	wsprintf(szName,".\\image\\%s\\board.bmp",SKIN_FOLDER);	//开始按钮
	m_PicGameView.SetLoadInfo(szName,CGameImageLink::m_bAutoLock);

	//加载按钮
	wsprintf(szName,".\\image\\%s\\start_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btContinue.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btContinue.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\%s\\havething_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btThing.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btThing.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\%s\\heqi_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btStop.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btStop.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\%s\\admit_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btAdmitDefeat.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btAdmitDefeat.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\%s\\Regret_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btRegretChess.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btRegretChess.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\%s\\DianMu_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btChessManual.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btChessManual.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\%s\\finish_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btFinishDianMu.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btFinishDianMu.SetWindowRgn(hRgn,true);

	wsprintf(szName,".\\image\\%s\\leave_bt.bmp",SKIN_FOLDER);	//开始按钮
	m_btLeave.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btLeave.SetWindowRgn(hRgn,true);

	//棋盘
	m_MeCard.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,25,NULL);
	m_MeCard.InitGameCard(GetParent());

	m_GameSetDlg.m_pParent = this;
	m_GameSetDlg.Create(IDD_GAME_SET,this);
	
	//(CClientGameDlg*)GetParent()->m_GameSet = &m_GameSetDlg;

	AfxSetResourceHandle(GetModuleHandle(NULL));

	return 0;
}

//坐标调整
void CClientPlayView::FixControlSize(int cx,int cy)
{

#ifdef	VIDEO
	///设置视频窗口位置 
	//if(NULL!=CPlayVideo::CreatePlayVideo())
	//	CPlayVideo::CreatePlayVideo()->SetUserPos();  

	///以下临时用下，以后移到脚本中或者动态语言中
	CString  strVideoCfg=CINIFile::GetAppPath()+TEXT("VideoCfg.ini");
	
	CINIFile iniFile(strVideoCfg);
	int	 m_heightVideo=0,m_widthVideo=0;
	m_widthVideo
		=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("WidthVideoWQ"), 122);
	m_heightVideo
		=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("HeightVideoWQ"), 136);

#endif


	int iMidLine = cx / 2;
	int iBaseLine = cy / 2;
	m_MeCard.SetBasePoint(CPoint(0,0),
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
	
	int boardw = m_PicGameView.GetWidth(),boardh = m_PicGameView.GetHeight();

	m_MeCard.MoveWindow((cx-boardw)/2,(cy-boardh)/2,boardw,boardh,true);
	m_PtLogo[0].x = (cx-boardw)/2 + XQ_UPPEOPLE_LOG_X;
	m_PtLogo[0].y = (cy-boardh)/2 + XQ_UPPEOPLE_LOG_Y;

#ifdef	VIDEO
	m_RtVideo[0].left = 3;
	m_RtVideo[0].top =  XQ_UPPEOPLE_LOG_Y - 5;
	m_RtVideo[0].right = m_RtVideo[0].left + m_widthVideo;
	m_RtVideo[0].bottom = m_RtVideo[0].top + m_heightVideo;
#endif

	m_PtLogo[1].x = (cx-boardw)/2 + XQ_DOWNPEOPLE_LOG_X;
	m_PtLogo[1].y = (cy-boardh)/2 + XQ_DOWNPEOPLE_LOG_Y;

#ifdef	VIDEO
	m_RtVideo[1].left = 3;
	m_RtVideo[1].top = XQ_DOWNPEOPLE_LOG_Y - 5;
	m_RtVideo[1].right = m_RtVideo[1].left + m_widthVideo;
	m_RtVideo[1].bottom = m_RtVideo[1].top + m_heightVideo;

	///设置视频窗口位置 
	//if(NULL!=CPlayVideo::CreatePlayVideo())
	//	CPlayVideo::CreatePlayVideo()->SetUserPos();  
#endif

	//移动信息视图
	CRect ContronRect;
	m_GameNoteView.GetClientRect(&ContronRect);
	m_GameNoteView.MoveWindow((cx-ContronRect.Width()) / 2+50,((cy-150)-ContronRect.Height()) / 2+20,
						ContronRect.Width(),ContronRect.Height(),FALSE);
	//积分榜
	m_showcoredlg.GetClientRect(&ContronRect);
	m_showcoredlg.SetWindowPos(NULL,cx - ContronRect.Width() - 30,- m_showcoredlg.m_showh,0,0,SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOSIZE);
	//
	m_msgbox.CenterWindow(this);
	
	//移动信息视图
	m_Result.GetClientRect(&ContronRect);
	//m_Result.AutoSize(iMidLine - ContronRect.Width() / 2,iBaseLine - ContronRect.Height() / 2 - 30);
	m_Result.CenterWindow(this);
	
	//移动控件
	int x,y,xw,w,h;
	x = (cx - boardw) / 2 + 20;
	y = (cy - boardh) / 2 + 635;
	xw = (boardw - 20) / 8;

	m_btContinue.GetClientRect(&ContronRect);
	w = ContronRect.Width();
	h = ContronRect.Height();

	CGameImage btImage;
	TCHAR szName[200];
	wsprintf(szName,".\\image\\%s\\start_bt.bmp",SKIN_FOLDER);
	btImage.SetLoadInfo(szName,true);
	w = btImage.GetWidth()/4;
	h = btImage.GetHeight();

	m_btContinue.MoveWindow(x + xw*0,y,w,h);
	m_btLeave.MoveWindow(x + xw*1,y,w,h);
	m_btRegretChess.MoveWindow(x + xw*2,y,w,h);
	m_btStop.MoveWindow(x + xw*3,y,w,h);
	m_btAdmitDefeat.MoveWindow(x + xw*4,y,w,h);
	m_btChessManual.MoveWindow(x + xw*5,y,w,h);
	m_btFinishDianMu.MoveWindow(x + xw*6,y,w,h);
	m_btThing.MoveWindow(x + xw*7,y,w,h);

	CString s = CINIFile::GetAppPath ();/////本地路径
	DWORD cfgHandle;
#ifdef	VIDEO
	cfgHandle=cfgOpenFile(s +"30200205.bcf");
#else
	cfgHandle=cfgOpenFile(s +"30200200.bcf");
#endif
	if(cfgHandle<0x10)
	{
		return;
	}
	CBcfFile f( "30100200.bcf");
	//CINIFile f1( s +TEXT("image\\")+SKIN_FOLDER+TEXT("\\")+GET_NAME_ID +".ini");

	CString key1 = TEXT("config");

	m_PtGif[0].x = XQ_UPPEOPLE_LOG_X + f.GetKeyVal(key1,TEXT("flower0x"),0);
	m_PtGif[0].y = XQ_UPPEOPLE_LOG_Y + f.GetKeyVal(key1,TEXT("flower0y"),120);
	m_PtGif[1].x = XQ_DOWNPEOPLE_LOG_X + f.GetKeyVal(key1,TEXT("flower1x"),0);
	m_PtGif[1].y = XQ_DOWNPEOPLE_LOG_Y + f.GetKeyVal(key1,TEXT("flower1y"),120);
	
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);

#ifdef _USE_VIDEO
	p->RefreshAllVideoPanel();
#endif

	return;
}


//按钮消息
void CClientPlayView::OnHitButton(UINT uID)
{
	UINT msg;
	switch(uID - IDC_GAME_BEGIN)
	{
	case 0://开始
		msg = IDM_BEGIN;
		break;
	case 1://离开
		msg = WM_CLOSE;
		break;	
	case 2://悔棋
		msg = IDM_REGRET_CHESS;
		break;
	case 3://求和
		msg = IDM_STOP;
		break;
	case 4://认输
		msg = IDM_ADMIT_DEFEAT;
		break;	
	case 5://点目
		msg = IDM_CHESS_MANUAL;
		break;
	case 6://完成点目
		msg = IDM_FINISH_DIAN_MU;
		break;
	case 7://有事要走
		msg = IDM_HAVE_THING;
		break;
	default:
		break;
	}
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(msg,0,0);
	return ;
}

//重置界面函数
void CClientPlayView::ResetGameView()
{
	CUsingSkinClass::ResetGameView();
	return;
}


///将此昵称的玩家视频窗口矩形写入参数rect,并返回TRUE;没找到返回falst
#ifdef	VIDEO
BOOL	CClientPlayView::GetVideoRect(CString  strNickname, RECT& rect, CString& pic)
{
	CString strLocalName;

	for(int iCount=0; iCount<MAX_PEOPLE; iCount++)
	{
		if(m_pUserItem[iCount])
		{    
			strLocalName=m_pUserItem[iCount]->GameUserInfo.nickName;
			
			if(strLocalName == strNickname)
			{
				rect=m_RtVideo[iCount];
				m_MeCard.ClientToScreen(&rect);
				ScreenToClient(&rect);

				//rect=m_RtVideo[iCount];
				CString logopathstr;
				
				logopathstr.Format("image\\log\\gamelog%d.bmp", m_pUserItem[iCount]->GameUserInfo.bLogoID);
				
				CString  tempstr = CINIFile::GetAppPath()+logopathstr;
				
				pic = tempstr;
				return true;
			}
		}
	
	}	 
	return false; //没找到
}
#endif