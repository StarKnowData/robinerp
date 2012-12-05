#include "StdAfx.h"
#include "ClientView.h"
#include "ClientGameDlg.h"

/// 宏定义
#define BT_WIDTH							32						///< 按钮宽度
#define BT_HEIGHT							32						///< 按钮高度

#define ID_CHECK_TIMER      23

CBitmap				CClientPlayView::m_Bitmap_Num;

void CClientPlayView::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == ID_CHECK_TIMER)
	{
		m_imaxelaspse -= 1000;
		UpdateViewFace(NULL);
		if(m_imaxelaspse <= 0)
		{
			KillCheckTimer();
			OnHitFinishDiaoDu();
		}
	}
}

void CClientPlayView::SetCheckTimer(int maxelaspse)
{
	m_imaxelaspse=maxelaspse;
	SetTimer(ID_CHECK_TIMER,1000,NULL);
}

void CClientPlayView::KillCheckTimer()
{
	m_imaxelaspse=0;
	KillTimer(ID_CHECK_TIMER);
}


BEGIN_MESSAGE_MAP(CClientPlayView, CUsingSkinClass)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BEGIN,OnHitBegin)

	ON_BN_CLICKED(IDC_FINISH_DIAODU,OnHitFinishDiaoDu) 
	ON_BN_CLICKED(IDC_SAVE_BUZHEN,OnHitSaveBuZhen) 
	ON_BN_CLICKED(IDC_LOAD_BUZHEN,OnHitLoadBuZhen) 

	ON_BN_CLICKED(IDC_CONTINUE, OnHitContinue)
	ON_BN_CLICKED(IDC_LEAVE, OnHitLeave)
	ON_BN_CLICKED(IDC_HAVE_THING, OnHitThing)
	ON_BN_CLICKED(IDC_STOP, OnHitStop)

	ON_WM_TIMER()

	ON_WM_RBUTTONUP()

	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CClientPlayView::OnHitFinishDiaoDu()
{
	m_Logic.m_bICanMove = false;
	KillCheckTimer();
	m_btFinishDiaoDu.ShowWindow (SW_HIDE);
	m_btLoadBuZhen.ShowWindow (SW_HIDE);
	m_btSaveBuZhen.ShowWindow (SW_HIDE);
	m_Logic.FinishBuZhen ();	
}

void CClientPlayView::OnHitSaveBuZhen()
{
	m_Logic.SaveBuZhen ();
	
	
}

void CClientPlayView::OnHitLoadBuZhen()
{
	m_Logic.LoadBuZhen ();
	UpdateViewFace(NULL);
	
}

/**
 * 建立消息
 */
int CClientPlayView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CUsingSkinClass::OnCreate(lpCreateStruct) == -1)	return -1;

	
	//建立控件
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	TCHAR path[MAX_PATH] = {0};
#ifdef	VIDEO
	wsprintf(path,TEXT(".\\image\\VideoFrame.bmp"));
	m_pVideoFrame.SetLoadInfo(path,false);
#endif

	m_btContinue.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_CONTINUE);
	m_btThing.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_HAVE_THING);
	m_btStop.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_STOP);
	
	m_btFinishDiaoDu.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_FINISH_DIAODU);
	m_btLoadBuZhen.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_LOAD_BUZHEN);
	m_btSaveBuZhen.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_SAVE_BUZHEN);
	//m_btleave.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_LEAVE);

	m_GameNoteView.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,50,NULL);
	m_GameNoteView.AutoSize();

	m_msgbox.Create(IDD_MSGBOX,this);
	m_Result.Create(IDD_MSGBOX_RESULT,this);

	m_StopThing.Create(IDD_STOP, this);
	m_StopMessage.Create(IDD_STOP_MESSAGE, this);


	m_btThing.SetFont(&CGameImageLink::m_HFont);

	m_btContinue.SetFont(&CGameImageLink::m_HFont);

	m_btFinishDiaoDu.SetFont(&CGameImageLink::m_HFont);
	m_btLoadBuZhen.SetFont(&CGameImageLink::m_HFont);
	m_btSaveBuZhen.SetFont(&CGameImageLink::m_HFont);

	AfxSetResourceHandle(GetModuleHandle(NULL));
	m_btFinishDiaoDu.ShowWindow(false);
	m_btLoadBuZhen.ShowWindow(false);
	m_btSaveBuZhen.ShowWindow(false);

	wsprintf(path,TEXT("image\\start.bmp"));
	m_btContinue.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\finish.bmp"));
	m_btFinishDiaoDu.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\load.bmp"));
	m_btLoadBuZhen.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\save.bmp"));
	m_btSaveBuZhen.LoadButtonBitmap(path,false);

	wsprintf(path,TEXT("image\\have.bmp"));
	m_btThing.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\stop.bmp"));
	m_btStop.LoadButtonBitmap(path,false);
	//m_btleave.LoadButtonBitmap("image\\jq\\leave.bmp",false);

	if(m_iUserFrame.GetWidth() <= 0)
	{
		_stprintf_s(path, sizeof(path), TEXT(".\\image\\logoframe.bmp"));
		SetFrameImage(path);
	}	

	return 0;
}

void CClientPlayView::FixControlSize(int cx,int cy)
{
	if ((cx==0)||(cy==0)) return;

	CString s = CINIFile::GetAppPath ();/////本地路径
	CString key = TEXT("UISet");
	CString key1 = TEXT("VideoUISet");

	CGameImageHelper LogoHandle(&m_PicGameViewLogo);	

#ifdef	VIDEO
	CBcfFile f( "30300405.bcf");
#else
	CBcfFile f( "30300400.bcf");
#endif
	

#ifdef	VIDEO		

	int	 m_heightVideo=0,m_widthVideo=0;	
	m_widthVideo = f.GetKeyVal(key1,TEXT("iWidthVideo"), 160);
	m_heightVideo = f.GetKeyVal(key1,TEXT("iHeightVideo"), 152);
	
	int m_iVideoFrameX0 = f.GetKeyVal(key1, TEXT("VideoFrame0x"), -140);
	int m_iVideoFramey0 = f.GetKeyVal(key1, TEXT("VideoFrame0y"), -120);
	int m_iVideoFrameX1 = f.GetKeyVal(key1, TEXT("VideoFrame1x"), -40);
	int m_iVideoFramey1 = f.GetKeyVal(key1, TEXT("VideoFrame1y"), -120);
	int m_iVideoFrameX2 = f.GetKeyVal(key1, TEXT("VideoFrame3x"), 120);
	int m_iVideoFramey2 = f.GetKeyVal(key1, TEXT("VideoFrame2y"), 20);
	int m_iVideoFrameX3 = f.GetKeyVal(key1, TEXT("VideoFrame3x"), -140);
	int m_iVideoFramey3 = f.GetKeyVal(key1, TEXT("VideoFrame3y"), 20);		

	m_rectVideoFrame[0].top = cy/2-m_heightVideo + m_iVideoFramey0;
	m_rectVideoFrame[0].left = cx/2-m_widthVideo + m_iVideoFrameX0;
	m_rectVideoFrame[0].bottom = m_rectVideoFrame[0].top+m_heightVideo;
	m_rectVideoFrame[0].right = m_rectVideoFrame[0].left+m_widthVideo;
	 
	m_rectVideoFrame[1].top= cy/2-m_heightVideo+m_iVideoFramey1;
	m_rectVideoFrame[1].left= cx/2+ m_widthVideo+m_iVideoFrameX1;
	m_rectVideoFrame[1].bottom=m_rectVideoFrame[1].top+m_heightVideo;
	m_rectVideoFrame[1].right=m_rectVideoFrame[1].left+m_widthVideo;
	
	m_rectVideoFrame[2].top= cy/2 + m_heightVideo+m_iVideoFramey2;
	m_rectVideoFrame[2].left=cx/2+m_iVideoFrameX2;
	m_rectVideoFrame[2].bottom=m_rectVideoFrame[2].top+m_heightVideo;
	m_rectVideoFrame[2].right=m_rectVideoFrame[2].left+m_widthVideo;
	
	m_rectVideoFrame[3].top= cy/2+m_heightVideo+m_iVideoFramey3;
	m_rectVideoFrame[3].left= cx/2-m_widthVideo+m_iVideoFrameX3;
	m_rectVideoFrame[3].bottom=m_rectVideoFrame[3].top + m_heightVideo;
	m_rectVideoFrame[3].right=m_rectVideoFrame[3].left + m_widthVideo;
	
	///设置视频窗口位置 
	if(NULL!=CPlayVideo::CreatePlayVideo())
		CPlayVideo::CreatePlayVideo()->SetUserPos(); 

	m_PtLogo[1].x=m_rectVideoFrame[1].left + (m_rectVideoFrame[1].Width()/2 - 77/2);
	m_PtLogo[1].y=m_rectVideoFrame[1].top + 25 + ((m_rectVideoFrame[1].Height()-40)/2 -97/2) ;
	m_PtName[1].x=m_rectVideoFrame[1].left+10;
	m_PtName[1].y=m_rectVideoFrame[1].top+5;
	m_PtAgree[1].x=m_rectVideoFrame[1].left + (m_widthVideo - 20)/2;
	m_PtAgree[1].y=m_rectVideoFrame[1].top - 20;
	m_PtTime[1]=m_PtAgree[1];

	m_PtLogo[2].x=m_rectVideoFrame[2].left + (m_rectVideoFrame[2].Width()/2 - 77/2);
	m_PtLogo[2].y=m_rectVideoFrame[2].top + 25 + ((m_rectVideoFrame[2].Height()-40)/2 -97/2) ;
	m_PtName[2].x=m_rectVideoFrame[2].left+10;
	m_PtName[2].y=m_rectVideoFrame[2].top+5;;
	m_PtAgree[2].x=m_rectVideoFrame[2].left + (m_widthVideo - 20)/2;
	m_PtAgree[2].y=m_rectVideoFrame[2].top - 20;
	m_PtTime[2]=m_PtAgree[2];

	m_PtLogo[3].x=m_rectVideoFrame[3].left + (m_rectVideoFrame[3].Width()/2 - 77/2);
	m_PtLogo[3].y=m_rectVideoFrame[3].top + 25 + ((m_rectVideoFrame[3].Height()-40)/2 -97/2) ;
	m_PtName[3].x=m_rectVideoFrame[3].left+10;
	m_PtName[3].y=m_rectVideoFrame[3].top+5;;
	m_PtAgree[3].x=m_rectVideoFrame[3].right+5;
	m_PtAgree[3].y=m_rectVideoFrame[3].top;

	int iAgreeX3 = f.GetKeyVal(key,TEXT("iVideoAgreeX3"), 6);
	int iAgreeY3 = f.GetKeyVal(key,TEXT("iVideoAgreeY3"), -178);

	m_PtAgree[3].x=m_rectVideoFrame[3].left + (m_widthVideo - 20)/2+iAgreeX3;
	m_PtAgree[3].y=m_rectVideoFrame[3].bottom + 5+iAgreeY3;
	m_PtTime[3]=m_PtAgree[3];

	m_PtLogo[0].x=m_rectVideoFrame[0].left + (m_rectVideoFrame[0].Width()/2 - 77/2);;
	m_PtLogo[0].y=m_rectVideoFrame[0].top + 25 + ((m_rectVideoFrame[0].Height()-40)/2 -97/2) ;
	m_PtName[0].x=m_rectVideoFrame[0].left+10;
	m_PtName[0].y=m_rectVideoFrame[0].top+5;

	int iAgreeX0 = f.GetKeyVal(key,TEXT("iVideoAgreeX0"), 107);
	int iAgreeY0 = f.GetKeyVal(key,TEXT("iVideoAgreeY0"), -20);
	m_PtAgree[0].x=m_rectVideoFrame[0].left-30+iAgreeX0;
	m_PtAgree[0].y=m_rectVideoFrame[0].top+iAgreeY0;
	m_PtTime[0]=m_PtAgree[0];
	
#else
	m_PtLogo[1].x=cx/2 + f.GetKeyVal(key,TEXT("logo1x"),207);
	m_PtLogo[1].y=cy/2 - f.GetKeyVal(key,TEXT("logo1y"),116);

	m_PtName[1].x=m_PtLogo[1].x+ f.GetKeyVal(key,TEXT("name1x"),176);
	m_PtName[1].y=m_PtLogo[1].y+ f.GetKeyVal(key,TEXT("name1y"),147);

	m_PtAgree[1].x=m_PtLogo[1].x + f.GetKeyVal(key,TEXT("agree1x"),236);
	m_PtAgree[1].y=m_PtLogo[1].y+ f.GetKeyVal(key,TEXT("agree1y"),172);
	m_PtTime[1]=m_PtAgree[1];

	m_PtLogo[2].x=cx/2 +  f.GetKeyVal(key,TEXT("logo2x"),188);
	m_PtLogo[2].y=cy/2 + f.GetKeyVal(key,TEXT("logo2y"),200);

	m_PtName[2].x=m_PtLogo[2].x +  f.GetKeyVal(key,TEXT("name2x"),5);
	m_PtName[2].y=m_PtLogo[2].y+ f.GetKeyVal(key,TEXT("name2y"),5);

	m_PtAgree[2].x=m_PtLogo[2].x + f.GetKeyVal(key,TEXT("agree2x"),183);
	m_PtAgree[2].y=m_PtLogo[2].y+ f.GetKeyVal(key,TEXT("agree2y"),182);

	m_PtTime[2]=m_PtAgree[2];

	m_PtLogo[3].x=cx/2 - f.GetKeyVal(key,TEXT("logo3x"),285);
	m_PtLogo[3].y=cy/2 + f.GetKeyVal(key,TEXT("logo3y"),32);

	m_PtName[3].x = m_PtLogo[3].x + f.GetKeyVal(key,TEXT("name3x"),5);
	m_PtName[3].y = m_PtLogo[3].y + f.GetKeyVal(key,TEXT("name3y"),5);

	m_PtAgree[3].x=m_PtLogo[3].x + f.GetKeyVal(key,TEXT("agree3x"),256);
	m_PtAgree[3].y=m_PtLogo[3].y + f.GetKeyVal(key,TEXT("agree3y"),157);
	m_PtTime[3]=m_PtAgree[3];

	m_PtLogo[0].x=cx/2 - f.GetKeyVal(key,TEXT("logo0x"),232);
	m_PtLogo[0].y=cy/2 - f.GetKeyVal(key,TEXT("logo0y"),46);

	m_PtName[0].x = m_PtLogo[0].x + f.GetKeyVal(key,TEXT("name0x"),15);
	m_PtName[0].y = m_PtLogo[0].y + f.GetKeyVal(key,TEXT("name0y"),15);

	m_PtAgree[0].x=m_PtLogo[0].x + f.GetKeyVal(key,TEXT("agree0x"),303);
	m_PtAgree[0].y=m_PtLogo[0].y+f.GetKeyVal(key,TEXT("agree0y"),10);

	m_PtTime[0]=m_PtAgree[0];
	
	if (!m_bShowLogo)
	{
		CString MyKey = TEXT("UISet");
		m_PtAgree[0].x += f.GetKeyVal(MyKey,TEXT("Agreeoffset0x"),0);
		m_PtAgree[0].y += f.GetKeyVal(MyKey,TEXT("Agreeoffset0y"),0);	
		m_PtAgree[1].x += f.GetKeyVal(MyKey,TEXT("Agreeoffset1x"),0);
		m_PtAgree[1].y += f.GetKeyVal(MyKey,TEXT("Agreeoffset1y"),0);
		m_PtAgree[2].x += f.GetKeyVal(MyKey,TEXT("Agreeoffset2x"),0);
		m_PtAgree[2].y += f.GetKeyVal(MyKey,TEXT("Agreeoffset2y"),0);
		m_PtAgree[3].x += f.GetKeyVal(MyKey,TEXT("Agreeoffset3x"),0);
		m_PtAgree[3].y += f.GetKeyVal(MyKey,TEXT("Agreeoffset3y"),0);
		m_PtTime[0] = m_PtAgree[0];
		m_PtTime[1] = m_PtAgree[1];
		m_PtTime[2] = m_PtAgree[2];
		m_PtTime[3] = m_PtAgree[3];
	}
#endif

	//移动信息视图
	CRect ContronRect;
	m_GameNoteView.GetClientRect(&ContronRect);
	m_GameNoteView.MoveWindow((cx-ContronRect.Width())/2,((cy-150)-ContronRect.Height())/2,	ContronRect.Width(),ContronRect.Height(),FALSE);
	CRect rect;
	m_showcoredlg.GetClientRect(&rect);

	m_showcoredlg.SetWindowPos(NULL,cx-rect.Width()-30,-m_showcoredlg.m_showh,0,0,SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOSIZE);
	//m_showcoredlg.ShowWindow(SW_HIDE);
	m_msgbox.CenterWindow(this);
	m_Result.CenterWindow(this);
	//m_StopThing.CenterWindow(this);
	//m_StopMessage.CenterWindow(this);
	//移动按钮
	
	//m_btleave.MoveWindow(cx-250,cy-70,90,34);
	int x,y,w,h;
	x=cx-90;
	y=cy-120;
	w=90;
	h=34;
	
	m_btFinishDiaoDu.MoveWindow(x,y-80 - 15,w,h);
	m_btLoadBuZhen.MoveWindow(x,y-40 - 15,w,h);
	m_btSaveBuZhen.MoveWindow(x,y - 15,w,h);

	m_btContinue.MoveWindow(cx-90,cy-120 - 15,90,34);
	m_btStop.MoveWindow(cx-90,cy-80 - 15,90,34);
	m_btThing.MoveWindow(cx-90,cy-40 - 15,90,34);
	
#ifdef VIDEO	
	m_PtGif[0].x = m_PtLogo[0].x+5;
	m_PtGif[0].y = m_PtLogo[0].y+m_heightVideo;

	m_PtGif[1].x = m_PtLogo[1].x+-130;
	m_PtGif[1].y = m_PtLogo[1].y+0;

	m_PtGif[2].x = m_PtLogo[2].x+0;
	m_PtGif[2].y = m_PtLogo[2].y-150;

	m_PtGif[3].x = m_PtLogo[3].x+m_widthVideo;
	m_PtGif[3].y = m_PtLogo[3].y+0;
	
	m_PtGif[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("flower0x"),0);
	m_PtGif[0].y = m_PtLogo[0].y+f.GetKeyVal(key,TEXT("flower0y"),0);

	m_PtGif[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("flower1x"),0);
	m_PtGif[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("flower1y"),0);

	m_PtGif[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("flower2x"),0);
	m_PtGif[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("flower2y"),0);

	m_PtGif[3].x = m_PtLogo[3].x+f.GetKeyVal(key,TEXT("flower3x"),0);
	m_PtGif[3].y = m_PtLogo[3].y+f.GetKeyVal(key,TEXT("flower3y"),0);
#else

	m_PtGif[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("flower0x"),0);
	m_PtGif[0].y = m_PtLogo[0].y+f.GetKeyVal(key,TEXT("flower0y"),0);

	m_PtGif[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("flower1x"),0);
	m_PtGif[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("flower1y"),0);

	m_PtGif[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("flower2x"),0);
	m_PtGif[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("flower2y"),0);

	m_PtGif[3].x = m_PtLogo[3].x+f.GetKeyVal(key,TEXT("flower3x"),0);
	m_PtGif[3].y = m_PtLogo[3].y+f.GetKeyVal(key,TEXT("flower3y"),0);
#endif

		m_bUpdateScoreboard=true;

	//end;
}

/**
 * 绘画界面函数
 */
void CClientPlayView::DrawViewFace(CDC * pDC, int iWidth, int iHeight)
{
	//绘画界面	
	pDC->SetBkMode(TRANSPARENT);
	CFont newFont, newFont1, *OldFont, *OldFont1; 	
	newFont.CreateFont(m_NameFont_Height,m_NameFont_Width,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	newFont1.CreateFont(m_JinBiFont_Height,m_JinBiFont_Width,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	OldFont = pDC->SelectObject(&newFont);

	CGameImageHelper BackHandle(&m_PicGameView);
	CGameImageHelper LogoHandle(&m_PicGameViewLogo);

	if(BackHandle.GetWidth() > 0 && BackHandle.GetHeight()>0)
	for(int i=0;i<iWidth;i+=BackHandle.GetWidth())
		for(int j=0;j<iHeight;j+=BackHandle.GetHeight())
			BackHandle.BitBlt(pDC->GetSafeHdc(),i,j);
	int x=(iWidth-LogoHandle.GetWidth())/2,
		y=(iHeight - LogoHandle.GetHeight())/2;

	LogoHandle.BitBlt(pDC->GetSafeHdc(),x,y);
	if (m_imaxelaspse> 0)
		DrawTimer(pDC,m_PtTime[2].x ,m_PtTime[2].y ,m_imaxelaspse / 1000);

	m_Logic.m_ptBoardStartCenter.x = x + 11;
	m_Logic.m_ptBoardStartCenter.y = y + 13;

	CRect tempRect;		
	int iAlign = 0x01;
	//绘画用户
	pDC->SetTextColor(RGB(255,255,0));
	for (int i=0;i<PLAY_COUNT;i++)
	{
		if (m_pUserItem[i]!=NULL)
		{

#ifdef	VIDEO
			OutputDebugString("----------进入画视频底图----------");
			///视频底图
			CGameImageHelper bg(&m_pVideoFrame);
			CDC srcdc;
			CBitmap *OldBmp;
			srcdc.CreateCompatibleDC(pDC);
			OldBmp = srcdc.SelectObject(bg);			
			TransparentBlt(pDC->GetSafeHdc(), m_rectVideoFrame[i].left, m_rectVideoFrame[i].top, m_rectVideoFrame[i].Width(), m_rectVideoFrame[i].Height(), 
							srcdc.GetSafeHdc(),0,0,bg.GetWidth(),bg.GetHeight(),srcdc.GetPixel(0,0));
			srcdc.SelectObject(OldBmp);
			srcdc.DeleteDC();		
			//动画坐标
			//m_PtGif[0].x = m_PtLogo[0].x;
			//m_PtGif[0].y = m_PtLogo[0].y;
			//m_PtGif[1].x = m_PtLogo[1].x;
			//m_PtGif[1].y = m_PtLogo[1].y;	
			//m_PtGif[2].x = m_PtLogo[2].x;
			//m_PtGif[2].y = m_PtLogo[2].y;	//计时器
#endif
			//m_PtGif[0].x = m_PtLogo[0].x - m_widthVideo/4;
			//m_PtGif[0].y = m_PtLogo[0].y - m_heightVideo;

			//m_PtGif[1].x = m_PtLogo[1].x + m_widthVideo/4;
			//m_PtGif[1].y = m_PtLogo[1].y - m_heightVideo/2;	

			//m_PtGif[2].x = m_PtLogo[2].x + m_widthVideo/4;
			//m_PtGif[2].y = m_PtLogo[2].y - m_heightVideo/2;	//计时器
			UserInfoStruct * pUserInfo=&m_pUserItem[i]->GameUserInfo;
			
			TCHAR szText[_MAX_PATH]={0};
			POINT offsetLogo={0,0};
			offsetLogo.x = -15;
			offsetLogo.y = -5;			
			
#ifndef VIDEO
			if (m_bShowLogo)
			{
				DrawLogoFrame(pDC, m_PtLogo[i].x + offsetLogo.x, m_PtLogo[i].y + offsetLogo.y);//头像背景框				
				tempRect.left = m_PtName[i].x;
				tempRect.top = m_PtName[i].y;
				tempRect.right = tempRect.left + 100;
				tempRect.bottom = tempRect.top + 30;
			}
			else
			{
				tempRect.left = m_PtName[i].x+m_UserNameOffset_x[i];
				tempRect.top = m_PtName[i].y+m_UserNameOffset_y[i]+m_NameTextOffset_Height;
				tempRect.right = tempRect.left + +m_iUserFrame.GetWidth()+m_NameTextOffset_Width;
				tempRect.bottom = tempRect.top + 20;
			}			
#else			
			tempRect.left = m_rectVideoFrame[i].left;
			tempRect.top = m_rectVideoFrame[i].top+2;
			tempRect.right = tempRect.left + 160;
			tempRect.bottom = tempRect.top + 20;
#endif	  
		
			if (m_bShowLogo)
			{	
				pDC->DrawText(pUserInfo->nickName,lstrlen(pUserInfo->nickName), &tempRect,iAlign|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);//画玩家名					
				DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x,m_PtLogo[i].y,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);				
			}	
			else
			{	
				pDC->DrawText(pUserInfo->nickName,lstrlen(pUserInfo->nickName), &tempRect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);//画玩家名				

				CString str1;
				str1.Format("金币:%d",m_pUserItem[i]->GameUserInfo.i64Money);	
				tempRect.left = m_PtName[i].x+m_UserNameOffset_x[i]+m_JinBiOffset_x[i];
				tempRect.right = tempRect.left+m_JinBiTextOffset_Width;
				tempRect.top=m_PtName[i].y+m_JinBiOffset_y[i]+35;
				tempRect.bottom=tempRect.top+m_JinBiTextOffset_Height+20;
				
				OldFont1 = pDC->SelectObject(&newFont1);
				pDC->DrawText(str1,lstrlen(str1),&tempRect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				pDC->SelectObject(OldFont1);							
			}		
#ifdef TWENTY
			if (i == 2)
			{
				CFont Font, *oldfont;
				Font.CreateFont(12,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体")); 
				oldfont = pDC->SelectObject(&Font);
				TCHAR sz[100];
				wsprintf(sz,TEXT("红宝石场：%d/20  蓝宝石场: %d/20"),m_pUserItem[i]->GameUserInfo.iRedDiamondGameCnt,m_pUserItem[i]->GameUserInfo.iBlueDiamondGameCnt);
				tempRect.left=tempRect.left-50;
				tempRect.right=tempRect.left+200;
				tempRect.top=tempRect.top+20;
				tempRect.bottom=tempRect.top+20;
				pDC->DrawText(sz,lstrlen(sz),&tempRect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				pDC->SelectObject(oldfont);
				Font.DeleteObject();
			}
#endif	

			if (m_uTime[i]!=0&&m_imaxelaspse<=0)
				DrawTimer(pDC,m_PtTime[i].x,m_PtTime[i].y,m_uTime[i]);
			if (pUserInfo->bUserState==USER_ARGEE)				
				DrawArgeeFlag(pDC,m_PtAgree[i].x,m_PtAgree[i].y);
		}
	}
	DrawUserMj( pDC,  iWidth, iHeight);
	DrawGif(pDC,m_PtGif[m_iGifDeskStation].x,m_PtGif[m_iGifDeskStation].y);

	DeleteObject(pDC->SelectObject(OldFont));
	newFont1.DeleteObject();
	return;
}

/**
 * 绘画界面函数
 */
void CClientPlayView::DrawUserMj(CDC * pDC, int iClientWidth, int iClientHeight)
{
	if (m_bFirstGame)	//是否是新进桌子
		Init();
	m_Logic.OnPaint (pDC);
}

/**
 * 鼠标消息
 */
void CClientPlayView::OnRButtonUp(UINT nFlags, CPoint Point)
{
//	if(g_MjImg.ButtenPara.ChuEnable)
			//	m_Logic.OnMjBtnClick(BUTTON_CHU);
}

void CClientPlayView::Init()
{
	m_imaxelaspse=0;
	KillCheckTimer();
	m_Logic.Init ();
	m_Logic.InitPath();
	m_msgbox.ShowWindow(false);
	m_Result.ShowWindow(false);

	m_StopMessage.ShowWindow(false);
	m_StopThing.ShowWindow(false);
	UpdateViewFace(NULL);
}

/**
 * 鼠标消息
 */
void CClientPlayView::OnLButtonUp(UINT nFlags, CPoint Point)
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_SET_FLASH_CHESS,0,0);

	m_Logic.OnLBUp(Point);
	UpdateViewFace(NULL);
}


/*******************************************************************************************************/

/**
 * 构造函数
 */
CClientPlayView::CClientPlayView(void) :m_GameSet(this),m_GameInfo(this)//,m_GameEndView(this)
{
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\bakc.bmp"));
	m_PicGameView.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	wsprintf(path,TEXT("image\\back.bmp"));
	m_PicGameViewLogo.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	AfxSetResourceHandle(GetModuleHandle(NULL));
	m_bUpdateScoreboard=true;

	m_imaxelaspse = 0;

	CString fpath = CBcfFile::GetAppPath();	

#ifdef	VIDEO
		fpath += "30300405.bcf";
#else
		fpath += "30300400.bcf";
#endif
	
	CBcfFile file(fpath);
	CString firstKey(TEXT("UISet"));
	m_bShowLogo			= file.GetKeyVal(firstKey,TEXT("ShowLogo"),1);
	m_NameFont_Height	= file.GetKeyVal(firstKey,TEXT("NameFontHeight"),14);
	m_NameFont_Width	= file.GetKeyVal(firstKey,TEXT("NameFontWidth"),7);
	m_NameTextOffset_Height	= file.GetKeyVal(firstKey,TEXT("NameTextOffset_Height"),0);
	m_NameTextOffset_Width	= file.GetKeyVal(firstKey,TEXT("NameTextOffset_Width"),0);
	m_JinBiFont_Height	= file.GetKeyVal(firstKey,TEXT("JinBiFontHeight"),14);
	m_JinBiFont_Width	= file.GetKeyVal(firstKey,TEXT("JinBiFontWidth"),7);
	m_JinBiTextOffset_Height = file.GetKeyVal(firstKey,TEXT("JinBiTextOffset_Height"),0);
	m_JinBiTextOffset_Width	 = file.GetKeyVal(firstKey,TEXT("JinBiTextOffset_Width"),0);	

	CString secKey;
	for (int i=0; i<PLAY_COUNT; i++)
	{
		secKey.Format("UserNameOffset%d_x",i);
		m_UserNameOffset_x[i] = file.GetKeyVal(firstKey,secKey,0);
		secKey.Format("UserNameOffset%d_y",i);
		m_UserNameOffset_y[i] = file.GetKeyVal(firstKey,secKey,0);
		secKey.Format("JinBiOffset%d_x",i);
		m_JinBiOffset_x[i] = file.GetKeyVal(firstKey,secKey,0);
		secKey.Format("JinBiOffset%d_y",i);
		m_JinBiOffset_y[i] = file.GetKeyVal(firstKey,secKey,0);
	}

	m_bFirstGame = false;
	return;
}

/**
 * 析构函数
 */
CClientPlayView::~CClientPlayView(void)
{
}

/**
 * 更新用户资料
 */
void CClientPlayView::UpdateUserInfo(BYTE bViewStation)
{
	UpdateViewFace(NULL);
	return;
}

/**
 * 开始按钮
 */
void CClientPlayView::OnHitBegin()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_BEGIN,0,0);
	return;
}

/**
 * 继续按钮
 */
void CClientPlayView::OnHitContinue()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_BEGIN,0,0);
	return;
}

/**
 * 继续按钮
 */
void CClientPlayView::OnHitLeave()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(WM_CLOSE,0,0);
	return;
}

/**
 * 有事要走
 */
void CClientPlayView::OnHitThing()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_HAVE_THING,0,0);
	return;
}

/**
 * 提前停止
 */
void CClientPlayView::OnHitStop()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_STOP,0,0);
	return;
}

/**
 * 重置界面函数
 */
void CClientPlayView::ResetGameView()
{
	CUsingSkinClass::ResetGameView();

	return;
}

/**
 * 绘画 NT 标志
 */
void CClientPlayView::DrawNt(CDC * pDC, int x, int y)
{
	CDC NtDC;
	BITMAP BmpInfo;
	m_NT.GetBitmap(&BmpInfo);
	NtDC.CreateCompatibleDC(pDC);
	NtDC.SelectObject(&m_NT);
	pDC->BitBlt(x,y,BmpInfo.bmWidth,BmpInfo.bmHeight,&NtDC,0,0,SRCCOPY);
	return;
}

/**
 * 设置庄家的位置
 */
void CClientPlayView::SetNTStation(int iViewStation)
{
	UpdateViewFace(NULL);
	return;
}

/**
 * 设置游戏分数
 */
void CClientPlayView::SetGamePoint(int iGamePoint, int bMeSide)
{
	if ((iGamePoint==0)&&(bMeSide==-1))
	{
		bMeSide=-1;
	}
	UpdateViewFace(NULL);
	
	return;
}

/**
 * 设置背景色
 */
void CClientPlayView::SetBackBmp(UINT uResourceID, TCHAR * szFileName, BOOL bResource)
{
	if (bResource)
	{
		CBitmap Temp;
		if (!Temp.LoadBitmap(uResourceID)) return;
		return;
	}
	else
	{
		if (szFileName==NULL) return;
	}
	return;
}

void CClientPlayView::DrawInfo(CDC *pDC)
{
//
//	CFont Font;
//	CPaintDC dc(this);
//	Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
//	pDC->SetTextColor(RGB(0,0,0));
//	pDC->SetBkMode(TRANSPARENT);
//
//	//绘画信息
////	TCHAR szBuffer[50];
//	TCHAR * szUpGrade[]={TEXT("本方 -- 对家"),TEXT("敌方 -- 右家"),TEXT("本方 -- 自己"),TEXT("敌方 -- 左家")};
//	TCHAR * szHua[]={TEXT("方块"),TEXT("梅花"),TEXT("红桃"),TEXT("黑桃")};
//	TCHAR * szCard[13]={TEXT("2"),TEXT("3"),TEXT("4"),TEXT("5"),TEXT("6"),TEXT("7"),
//						TEXT("8"),TEXT("9"),TEXT("10"),TEXT("J"),TEXT("Q"),TEXT("K"),
//						TEXT("A")};

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
				rect=m_rectVideoFrame[iCount];
				
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

//提示文字
BOOL CClientPlayView::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->hwnd==m_showcoredlg.m_hWnd && m_bUpdateScoreboard)
	{
		// 设置积分榜文本颜色	

#ifdef	VIDEO
		CBcfFile f( "30300405.bcf");
#else
		CBcfFile f( "30300400.bcf");
#endif
		
		CString key = TEXT("UISet");
		int uColorR = f.GetKeyVal(key,TEXT("ScorBarR"), 255);
		int uColorG = f.GetKeyVal(key,TEXT("ScorBarG"), 255);
		int uColorB = f.GetKeyVal(key,TEXT("ScorBarB"),255);
		m_showcoredlg.SetTextColor(RGB(uColorR, uColorG, uColorB));
		m_bUpdateScoreboard = false;
	}

//	m_ToolTip.RelayEvent(pMsg);
	return __super::PreTranslateMessage(pMsg);
}