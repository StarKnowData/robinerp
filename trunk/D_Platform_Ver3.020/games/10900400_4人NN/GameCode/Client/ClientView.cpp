#include "StdAfx.h"
#include "ClientView.h"
#include "ClientGameDlg.h"
//宏定义
#define BT_WIDTH							32						//按钮宽度
#define BT_HEIGHT							32						//按钮高度
#define SMALL_NUM_WIDTH						16						//小图片宽
#define SMALL_NUM_HEIGHT					12						//小图片高
#define NUM_WIDTH							30						//标准图片宽
#define NUM_HEIGHT							21						//标准图片高
#define GREEN_NUM_WIDTH						30						//绿图片宽
#define GREEN_NUM_HEIGHT					19						//绿图片高
#define JETON_WIDTH							41						//筹码
#define JETON_HEIGHT						37				

#define FACE_WIDTH							83						//人像头面框
#define FACE_HEIGHT							78						//人物头像框

#define WIDTH_NEW_MAN						112						//新头像人物宽
#define HEIGHT_NEW_MAN						130						//新头像人物高
//CBitmap				CClientPlayView::m_Back_Center;
//CBitmap				CClientPlayView::m_Bitmap_Num;
//BITMAP				CClientPlayView::m_Back_Center_Info;

#define ZHUANG_HEIGHT						30
#define ZHUANG_WIDTH						30
BEGIN_MESSAGE_MAP(CClientPlayView, CUsingSkinClass)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BEGIN,OnHitBegin)
	ON_BN_CLICKED(IDC_CONTINUE, OnHitContinue)
	ON_BN_CLICKED(IDC_HAVE_THING, OnHitThing)
	ON_BN_CLICKED(IDC_STOP, OnHitStop)
    ON_BN_CLICKED (IDC_NOTE,OnNote )    //下注
	ON_BN_CLICKED (IDC_GIVEUP,OnOver )  //弃

	ON_BN_CLICKED (IDC_RESET,OnReset )  //重排
	ON_BN_CLICKED (IDC_OPEN,OnOpen )    //开牌
	ON_BN_CLICKED (IDC_BULL,OnBull )    //牛
	ON_BN_CLICKED (IDC_CHANGE_SHIN,OnChangeShin)  //换肤

	ON_BN_CLICKED(IDC_LEAVE,OnHitLeave)
	ON_BN_CLICKED(IDC_AUTO,OnHitAuto)

	ON_COMMAND_RANGE(IDC_CALL_SCORE_PASS,IDC_CALL_SCORE_1,OnHitCallScore)//叫庄

	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/*******************************************************************************************************/
//构造函数
CClientPlayView::CClientPlayView(void)//:m_SysBackCard(true) //:m_GameSet(this),m_GameInfo(this)//,m_GameEndView(this)
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	TCHAR szName[MAX_PATH];
	wsprintf(szName,".\\image\\bg.bmp");
	m_PicGameViewLogo.SetLoadInfo(szName,true);
	memset(m_bAuto,0,sizeof(m_bAuto));
	memset(m_iNotePoint,0,sizeof(m_iNotePoint));
	memset(m_iThisTurnNote,0,sizeof(m_iThisTurnNote));
	memset(m_iPass,0,sizeof(m_iPass));
	memset(m_bMing,0,sizeof(m_bMing));
	memset(m_bOpenCard,false, sizeof(m_bOpenCard));
	m_iGamePoint=0;
	m_iNoteTotalPoint=0;					//本轮总注
	m_iNoteLimit=0;							//本轮上限
	m_iBaseNote=0;
	m_iMingLImit=0;
	m_iAnLImit=0;
	m_bMeSide=-1;
	m_bDraw=false;
	m_bWait = false;
	m_GameType = 0;
	memset(m_iGetPoint,0,sizeof(m_iGetPoint));
	memset(m_iShape,-1,sizeof(m_iShape));
	memset(m_iGetPointSplit,0,sizeof(m_iGetPointSplit));
	SetNameColor(RGB(255,255,0));			//设置默认用户名颜色
	//本轮添加筹码数
//	m_iThisTurnAddNote=0;
	//中间筹码堆数
	m_iNoteJeontTimes=0;
	m_nPowerOfGold = 0;


	m_iGameNoteSetType = 0;
	memset(m_bIsSendCard,0,sizeof(m_bIsSendCard));
	memset(m_bIsNote,0,sizeof(m_bIsNote));
	m_bClass3DInfo = false;
	//AfxSetResourceHandle(GetModuleHandle(NULL));

	CString fpath = CBcfFile::GetAppPath();
	CBcfFile file( fpath + SKIN_FOLDER +".BCF");
	CString firstKey(TEXT("config"));
	m_bShowLogo			= file.GetKeyVal(firstKey,TEXT("ShowLogo"),0);
	m_NameFont_Height	= file.GetKeyVal(firstKey,TEXT("NameFontHeight"),14);
	m_NameFont_Width	= file.GetKeyVal(firstKey,TEXT("NameFontWidth"),0);
	m_NameTextOffset_Height	= file.GetKeyVal(firstKey,TEXT("NameTextOffset_Height"),0);
	m_NameTextOffset_Width	= file.GetKeyVal(firstKey,TEXT("NameTextOffset_Width"),0);
	m_JinBiFont_Height	= file.GetKeyVal(firstKey,TEXT("JinBiFontHeight"),14);
	m_JinBiFont_Width	= file.GetKeyVal(firstKey,TEXT("JinBiFontWidth"),0);
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

	CString strDeskClass  = ""; 
	CBcfFile  f("GameOption.bcf"); 
	strDeskClass = f.GetKeyVal("DESK", "Class", "2d");

	if(strDeskClass == "3d")
	{
		m_bClass3DInfo = true ; 
	}
	else
	{
		m_bClass3DInfo = false ; 
	}

	::memset(m_pImgBackground,NULL,sizeof(m_pImgBackground));
	m_iCurrentBG = 0;								//当前背景图片
	::memset(&m_ViFinish,0,sizeof(m_ViFinish));		//结算数据
	m_bShowResult = false;							//是否显示结算;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	m_ShapeName[0] = TEXT("牛破");
	m_ShapeName[1] = TEXT("牛一");
	m_ShapeName[2] = TEXT("牛二");
	m_ShapeName[3] = TEXT("牛三");
	m_ShapeName[4] = TEXT("牛四");
	m_ShapeName[5] = TEXT("牛五");
	m_ShapeName[6] = TEXT("牛六");
	m_ShapeName[7] = TEXT("牛七");
	m_ShapeName[8] = TEXT("牛八");
	m_ShapeName[9] = TEXT("牛九");
	m_ShapeName[10] = TEXT("牛牛");
	m_ShapeName[11] = TEXT("银牛");
	m_ShapeName[12] = TEXT("金牛");
	m_ShapeName[13] = TEXT("五小");
	m_ShapeName[14] = TEXT("炸弹");

	return;
}

//析构函数
CClientPlayView::~CClientPlayView(void)
{
	GdiplusShutdown(m_gdiplusToken);
}

//更新用户资料
void CClientPlayView::UpdateUserInfo(BYTE bViewStation)
{
	UpdateViewFace(NULL);
	return;
}

//绘画界面函数
void CClientPlayView::DrawViewFace(CDC * pDC, int iWidth, int iHeight)
{
	pDC->FillSolidRect(0,0,iWidth,iHeight,m_Background.GetPixel(0,0));

	CRect rect;
	GetClientRect(&rect);

	DrawBk(pDC,m_pImgBackground[m_iCurrentBG],iWidth,iHeight);
#ifndef	SAO_YANG
	CGameImageHelper bg(&m_Background);

	//贴大图片
	int x=(rect.right-bg.GetWidth())/2;
	int y=((rect.bottom)-bg.GetHeight())/2;
	bg.BitBlt(pDC->GetSafeHdc(),x,y);

	//贴logo
	DrawGameTitle(pDC,iWidth,iHeight);
#endif

	//绘画用户
	pDC->SetTextColor(m_NameColor);		//用户昵称颜色
	CFont Font,*OldFont;  
	Font.CreateFont(12,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体")); 
	OldFont = pDC->SelectObject(&Font);
	TCHAR sz[100];

#ifdef VIDEO
	pDC->SetTextColor(m_NameColor);
	for (int i=0;i<PLAY_COUNT;i++)
	{
		if (m_pUserItem[i] != NULL)
		{
			UserInfoStruct * pUserInfo = &m_pUserItem[i]->GameUserInfo;
			POINT offsetLogo={0,0};
			POINT offsetAgree={0,0};
			RECT  rectName;  ///昵称和剩余牌数的框	

			offsetLogo.x	= m_rectVideoFrame[i].left + 40;
			offsetLogo.y	= m_rectVideoFrame[i].top +30;
			
			rectName.left	= m_rectVideoFrame[i].left + 5;
			rectName.top	= m_rectVideoFrame[i].top +  2;
			rectName.right	= rectName.left + 160;
			rectName.bottom	= rectName.top + 20;

			if(i!=0)
			{
				offsetAgree.x	= m_rectVideoFrame[i].left;
				offsetAgree.y	= m_rectVideoFrame[i].top -12;	
				if (i == 3)
				{
					offsetAgree.x	= m_rectVideoFrame[i].left+160;
				}
				if (i == 1)
				{
					offsetAgree.x	= m_rectVideoFrame[i].left-12;
				}
			}
			else
			{
				offsetAgree.x	= m_rectVideoFrame[i].left;
				offsetAgree.y	= m_rectVideoFrame[i].bottom + 5;
			}
			
			////////////////////////
			///视频底图
			CGameImageHelper bg(&m_pVideoFrame);
			CDC dc;
			dc.CreateCompatibleDC(pDC);
			dc.SelectObject(bg);
			::TransparentBlt(pDC->GetSafeHdc(),m_rectVideoFrame[i].left,m_rectVideoFrame[i].top,bg.GetWidth(),bg.GetHeight(),dc.GetSafeHdc(),0,0,m_pVideoFrame.GetWidth(),m_pVideoFrame.GetHeight(),dc.GetPixel(0,0));
                        dc.DeleteDC();
			//昵称
			wsprintf(sz,"%s",m_pUserItem[i]->GameUserInfo.nickName); 
			pDC->DrawText(sz,lstrlen(sz),&rectName,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
																		 
			//用户头像
			DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,offsetLogo.x,offsetLogo.y,m_pUserItem[i]->GameUserInfo.bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
			//计时器
			if (m_uTime[i]!=0)
				DrawTimer(pDC,m_PtTime[i].x,m_PtTime[i].y,m_uTime[i]);
			//同意标识
			if (m_pUserItem[i]->GameUserInfo.bUserState==USER_ARGEE)
				DrawArgeeFlag(pDC,offsetAgree.x, offsetAgree.y);
		}
	}
#else

	for (int i=0;i<PLAY_COUNT;i++)
	{
		if(m_bShowLogo)
		{
			if (m_pUserItem[i]!=NULL)
			{
				//绘制框架
				//DrawLogoFrame(pDC,m_PtLogo[i].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2,m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2);
#ifndef	TWO_NN
				if (i == 1)
				{
					int x = m_PtLogo[i].x -(m_iUserFrame.GetWidth() + 140)/2;
					int y = m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT + 65)/2;
	#ifdef SAO_YANG
						if(!m_bClass3DInfo)
						{
							x = x + 5;
							y = y + 8;
						}

	#endif
					//绘制头像框
					DrawLogoBJ( i ,pDC,x,y);
				}
				else
				{
					int x = m_PtLogo[i].x -(m_iUserFrame.GetWidth() + LOGO_WIDTH - 75)/2;
					int y = m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT + 65)/2;
	#ifdef SAO_YANG
						if(!m_bClass3DInfo)
						{
							x = x+5;
							y = y + 13;
						}
	#endif					
						//绘制头像框
					DrawLogoBJ(i ,pDC,x,y );
				}
#else
				//绘制头像框
				DrawLogoBJ(i ,pDC,m_PtLogo[i].x -(m_iUserFrame.GetWidth() + LOGO_WIDTH - 75)/2,m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT + 65)/2);
#endif
				

				UserInfoStruct * pUserInfo=&m_pUserItem[i]->GameUserInfo;
				//昵称
				CString str=(pUserInfo->nickName);
				wsprintf(sz,"%s",str);//.Left(10));

				rect.left=m_PtName[i].x-13;
				rect.right=rect.left+110;
				rect.top=m_PtName[i].y - 10;
				rect.bottom=rect.top+20;
				pDC->DrawText(sz,lstrlen(sz),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				pDC->SetTextColor(RGB(255,255,255));		//用户昵称颜色

				CString strMoney;
				GetNumString(pUserInfo->i64Money,strMoney,m_nPowerOfGold);
				wsprintf(sz,"%s",/*m_strMoneyType,*/strMoney);
				rect.left=m_PtName[i].x-13;
				rect.right=rect.left+80;
				rect.top=m_PtName[i].y+15;
				rect.bottom=rect.top+20;
				pDC->DrawText(sz,lstrlen(sz),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				pDC->SetTextColor(m_NameColor);		//用户昵称颜色
			
				if(m_bClass3DInfo)
				{
				#ifdef SAO_YANG
					if(i == 0 || i == 2)
						DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x-65,m_PtLogo[i].y-52,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
					else if(i == 1)
						DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x-5,m_PtLogo[i].y-105,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
					else
						DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x+15,m_PtLogo[i].y-105,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
				#else
					DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x + 10,m_PtLogo[i].y - 80,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
				#endif
				}
				else
				{
					DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x-3,m_PtLogo[i].y,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
				}
				
				if (m_uTime[i]!=0)
					DrawTimer(pDC,m_PtTime[i].x,m_PtTime[i].y,m_uTime[i]);

				if (pUserInfo->bUserState==USER_ARGEE)
					DrawArgeeFlag(pDC,m_PtAgree[i].x,m_PtAgree[i].y);
			}
		}
		else
		{
			if (m_pUserItem[i]!=NULL)
			{
#ifndef	TWO_NN
				if(i == 1)
				{

					int x = m_PtLogo[i].x -(m_iUserFrame.GetWidth() + 140)/2;
					int y = m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT + 65)/2;
#ifdef SAO_YANG
					if(m_bClass3DInfo)
					{
						x = x + 5;
						y = y + 8;
					}
#endif						//绘制头像框
					DrawLogoBJ( i ,pDC,x,y);
				}
				else
				{
					int x = m_PtLogo[i].x -(m_iUserFrame.GetWidth() + 140)/2;
					int y = m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT + 65)/2;
#ifdef SAO_YANG	
					if(m_bClass3DInfo)
					{
						x = x+5;
						y = y + 13;
					}
#endif	
					//绘制头像框
					DrawLogoBJ(i ,pDC,x,y );
				}
#else
				//绘制头像框
				DrawLogoBJ(i ,pDC,m_PtLogo[i].x -(m_iUserFrame.GetWidth() + LOGO_WIDTH - 170)/2,m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT - 60)/2);
#endif

				UserInfoStruct * pUserInfo=&m_pUserItem[i]->GameUserInfo;

				//昵称
				CString str=(pUserInfo->nickName);
				wsprintf(sz,"%s",str);//.Left(10));

				rect.left=m_PtName[i].x-13+m_UserNameOffset_x[i];
				rect.right=rect.left+100+m_NameTextOffset_Width;
				rect.top=m_PtName[i].y+m_UserNameOffset_y[i] - 8;
				rect.bottom=rect.top+20+m_NameTextOffset_Height;

				CFont nameFont;
				nameFont.CreateFont(m_NameFont_Height,m_NameFont_Width,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
				CFont* oldFont = pDC->SelectObject(&nameFont);

				pDC->SetTextColor(m_NameColor);		//用户昵称颜色
				pDC->DrawText(sz,lstrlen(sz),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				
				CString strMoney;
				GetNumString(pUserInfo->i64Money,strMoney,m_nPowerOfGold);
				wsprintf(sz,"%s",strMoney);
				rect.left=m_PtName[i].x-13+m_JinBiOffset_x[i];
				rect.right=rect.left+80+m_JinBiTextOffset_Width;
				rect.top=m_PtName[i].y+15+m_JinBiOffset_y[i];
				rect.bottom=rect.top+20+m_JinBiTextOffset_Height;

				CFont Font;
				Font.CreateFont(m_JinBiFont_Height,m_JinBiFont_Width,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
				pDC->SelectObject(&Font);

				pDC->SetTextColor(RGB(255,255,255));		//金币颜色
				pDC->DrawText(sz,lstrlen(sz),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);				

				pDC->SelectObject(oldFont);
				
				if (m_bClass3DInfo)
				{
					DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x + 10,m_PtLogo[i].y - 80,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
				}
				else
				{
					DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x-3,m_PtLogo[i].y,pUserInfo->bUserState==USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
				}

				if (m_uTime[i]!=0)
					DrawTimer(pDC,m_PtTime[i].x,m_PtTime[i].y,m_uTime[i]);

				if (pUserInfo->bUserState==USER_ARGEE) 
					DrawArgeeFlag(pDC,m_PtAgree[i].x,m_PtAgree[i].y);
			}
		}
	}
#endif
	
	DrawPass(pDC);

	DrawNt(pDC);

//GIF 动画
#ifdef TWO_NN
	if( m_iGifDeskStation >=0 && m_iGifDeskStation<2 )
		DrawGif(pDC,m_PtGif[m_iGifDeskStation].x,m_PtGif[m_iGifDeskStation].y);
#else
	DrawGif(pDC,m_PtGif[m_iGifDeskStation].x,m_PtGif[m_iGifDeskStation].y);
#endif
	

	DrawWait(pDC,iWidth,iHeight);

	DrawMoney(pDC);

	DrawNoteBt(pDC);


	DrawOpenCard(pDC);

	pDC->SelectObject(OldFont);
	return;
}
//绘制头像框
void CClientPlayView::DrawLogoBJ( int iView , CDC *pDC,int iXPos,int iYPos)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	if (m_bClass3DInfo)
	{
		CGameImageHelper help3(&m_PeopleBk3);
		dc.SelectObject(help3);
		::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,help3.GetWidth(),help3.GetHeight(),dc.GetSafeHdc(),0,0,help3.GetWidth(),help3.GetHeight(),RGB(255,0,255));
	}
	else
	{
		int iMyView = -1;
#ifndef TWO_NN
		iMyView = 1; 

		if(iMyView == iView)
		{ 
			CGameImageHelper help1(&m_PeopleBk1);
			dc.SelectObject(help1);
			::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,help1.GetWidth(),help1.GetHeight(),dc.GetSafeHdc(),0,0,help1.GetWidth(),help1.GetHeight(),RGB(255,0,255));
		}
		else
		{
			CGameImageHelper help2(&m_PeopleBk2);
			dc.SelectObject(help2);
			::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,help2.GetWidth(),help2.GetHeight(),dc.GetSafeHdc(),0,0,help2.GetWidth(),help2.GetHeight(),RGB(255,0,255));
		}
#else
		CGameImageHelper help2(&m_PeopleBk2);
		dc.SelectObject(help2);
		::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,help2.GetWidth(),help2.GetHeight(),dc.GetSafeHdc(),0,0,help2.GetWidth(),help2.GetHeight(),RGB(255,0,255));
#endif	
	}
	dc.DeleteDC();
}

//绘制游戏背面小图
void CClientPlayView::DrawBk(CDC *pDC,Image *pImage,int iWidth, int iHeight)
{

#ifdef SAO_YANG
	if(NULL == pImage)
	{
		return;
	}

	Graphics GDIDC(pDC->GetSafeHdc());	

	if(m_iCurrentBG == 0)
	{
		GDIDC.DrawImage(pImage,Rect(1, 1, iWidth, iHeight));
	}
	else
	{
		GDIDC.DrawImage(m_pImgBackground[0],Rect(1, 1, iWidth, iHeight));
		GDIDC.DrawImage(pImage,Rect(1, 186, iWidth, iHeight-186));
	}
#else
	CGameImageHelper bg(&m_bit_background);
	if(m_bit_background.GetHeight()>0)
	{
		for(int i = 0; i < iHeight; i += m_bit_background.GetHeight())
		{
			for(int j = 0; j < iWidth; j += m_bit_background.GetWidth())
			{	
				bg.BitBlt(pDC->GetSafeHdc(), j ,i);	
			}	
		}
	
	}
#endif	

}

//绘制游戏名称logo
void CClientPlayView::DrawGameTitle(CDC *pDC,int iWidth, int iHeight)
{
	CGameImageHelper bg(&m_GameTitleLogo);

	bg.BitBlt(pDC->GetSafeHdc(),m_PtGameTitle.x,m_PtGameTitle.y);

	//20100803zht绘制积分规则图，同喜乐
	CGameImageHelper Rule(&m_imgScoreRule);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(Rule);
	::TransparentBlt(pDC->GetSafeHdc(),iWidth-m_imgScoreRule.GetWidth(),0,Rule.GetWidth(),Rule.GetHeight(),dc.GetSafeHdc(),0,0,Rule.GetWidth(),Rule.GetHeight(),dc.GetPixel(0,0));
	dc.DeleteDC();

	return ;
}

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
	if (CUsingSkinClass::OnCreate(lpCreateStruct) == -1)	return -1;

	//建立控件
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	//	m_StationView.Create(this,100);
	//for(int i=0;i<MAX_NOTEJEONT;i++)
	//	m_NoteAll[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,56+i,NULL);
	//建立中心提示栏 090311a1 JJ
	m_GameNoteView.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this, NOTEVIEW,NULL);
	m_GameNoteView.AutoSize();
	m_GameNoteView.ShowWindow(SW_HIDE);

	m_NtList.Create(IDD_EASY_LIST,this);
//	m_ShowNote.Create(IDD_SHOW_NOTE,this);
    m_btContinue.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_CONTINUE);
	m_btLeave.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_LEAVE);
	m_btContinue.ShowWindow(SW_HIDE);
	m_btLeave.ShowWindow(SW_HIDE);

	for (BYTE i = 0; i < PLAY_COUNT; i++)
	{
		m_CardShape[i].Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS, CRect(0,0,0,0), this, 0, NULL);
		m_CardShape[i].ShowWindow(SW_HIDE);
	}

	//m_btNote.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_NOTE);
	//m_btOver.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_GIVEUP);

	m_btCallScorePass.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_CALL_SCORE_PASS);
	m_btCallScorePass.ShowWindow(SW_HIDE);

	m_btCallScore1.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_CALL_SCORE_1);
	m_btCallScore1.ShowWindow(SW_HIDE);

	m_btReset.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_RESET);
	m_btReset.ShowWindow(SW_HIDE);

	m_btOpen.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_OPEN);
	m_btOpen.ShowWindow(SW_HIDE);

	m_btBull.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_BULL);
	m_btBull.ShowWindow(SW_HIDE);

	m_btChangeShin.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_CHANGE_SHIN);
	m_btChangeShin.ShowWindow(SW_HIDE);

	/*m_btSplit.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_SPLIT);
	m_btInsurance.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,80,25),this,IDC_INSURANCE);*/

	CString strTemp = "";
	for(int i = 0; i < 4; ++i)
	{
		strTemp.Format(".\\image\\Background%d.png",i);
		m_pImgBackground[i] = Image::FromFile(CA2W(strTemp));	//加载图片
	}

	//加载所有图片
	TCHAR path[MAX_PATH];
#ifdef VIDEO
	wsprintf(path, _T(".\\image\\VideoFrame.bmp"));
	m_pVideoFrame.SetLoadInfo(path,false);
#endif
	wsprintf(path,".\\image\\BackColorOnly.bmp");
	m_bit_background.SetLoadInfo(path,CGameImageLink::m_bAutoLock);		//小贴图背景

	wsprintf(path,".\\image\\bg.bmp");
	m_Background.SetLoadInfo(path,CGameImageLink::m_bAutoLock);			//中心图片

	wsprintf(path,".\\image\\pass.bmp");
	m_Pass.SetLoadInfo(path,false);										//游戏pass标志	

	wsprintf(path,".\\image\\green_num.bmp");
	m_PicGreenNum.SetLoadInfo(path,false);

	wsprintf(path,".\\image\\PeopleBk1.bmp");							//人物背景1
	m_PeopleBk1.SetLoadInfo(path,false);

	wsprintf(path,".\\image\\PeopleBk2.bmp");							//人物背景2
	m_PeopleBk2.SetLoadInfo(path,false);

	wsprintf(path,".\\image\\PeopleBk3.bmp");							//人物背景3
	m_PeopleBk3.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\normal_num.bmp");
	m_PicNum.SetLoadInfo(path,CGameImageLink::m_bAutoLock);	

	wsprintf(path,".\\image\\small_num.bmp");
	m_PicSmallNum.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\showlimit.bmp");
	m_PicLeftLogo.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\score.bmp");
	m_PicScore.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\maxfen.bmp");
	m_HuangGuan.SetLoadInfo(path,false);	

	wsprintf(path,".\\image\\jeton.bmp");
	m_Jeton.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\waiting1.bmp");
	m_Waiting.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\kuan.bmp");
	m_NoteKuan.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\jeton.bmp");
	m_WinFen.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\jeton2.bmp");
	m_LossFen.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\niu.bmp");
	m_Niu.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\niu_n.bmp");
	m_Niu_n.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\nn.bmp");
	m_Nn.SetLoadInfo(path,false);

	wsprintf(path,".\\image\\jingniu.bmp");
	m_ImgJn.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\yinniu.bmp");
	m_ImgYn.SetLoadInfo(path,false);

	wsprintf(path,".\\image\\zhadan.bmp");
	m_ImgBomb.SetLoadInfo(path,false);

	wsprintf(path,".\\image\\5xiao.bmp");
	m_ImgFive.SetLoadInfo(path,false);

	wsprintf(path,".\\image\\jifenguizhe.bmp");
	m_imgScoreRule.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\green_num.bmp");
	m_Num.SetLoadInfo(path,false);
	
	wsprintf(path,".\\image\\nt.bmp");
	m_Nt.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\tanpai.bmp");
	m_imgOpenCard.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,".\\image\\logoframe.bmp");
	SetFrameImage(path);	
	
	//加载按钮
	CGameImage m_bk;
	HRGN hRgn;
	TCHAR szName[MAX_PATH];
	wsprintf(szName,".\\image\\start_bt.bmp");	//开始按钮
	m_btContinue.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btContinue.SetWindowRgn(hRgn,true);
	
	wsprintf(szName,".\\image\\leave_bt.bmp");	//开始按钮
	m_btLeave.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btLeave.SetWindowRgn(hRgn,true);

	//	wsprintf(szName,".\\image\\note_bt.bmp");	//下注
	////m_btNote.LoadButtonBitmap(szName,false);	
	//	m_bk.SetLoadInfo(szName,true);
	//	hRgn = AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	//	if (hRgn)
	//		m_btNote.SetWindowRgn(hRgn,true);

	//	wsprintf(szName, ".\\image\\giveup_bt.bmp", SKIN_FOLDER);	//弃牌
	//m_btOver.LoadButtonBitmap(szName,false);	
	//m_bk.SetLoadInfo(szName,true);
	//hRgn = AFCBmpToRgn(m_bk, RGB(255, 0, 255),RGB(1, 1, 1));
	//if (hRgn)
	//	m_btOver.SetWindowRgn(hRgn,true);

	wsprintf(szName, ".\\image\\Reset_bt.bmp", SKIN_FOLDER);	//重排
	m_btReset.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn = AFCBmpToRgn(m_bk, RGB(255, 0, 255),RGB(1, 1, 1));
	if (hRgn)
		m_btReset.SetWindowRgn(hRgn,true);

	wsprintf(szName, ".\\image\\Open_bt.bmp", SKIN_FOLDER);		//不要
	m_btOpen.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn = AFCBmpToRgn(m_bk, RGB(255, 0, 255),RGB(1, 1, 1));
	if (hRgn)
		m_btOpen.SetWindowRgn(hRgn,true);

	wsprintf(szName, ".\\image\\cue_bt.bmp", SKIN_FOLDER);		//加倍
	m_btBull.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn = AFCBmpToRgn(m_bk, RGB(255, 0, 255),RGB(1, 1, 1));
	if (hRgn)
		m_btBull.SetWindowRgn(hRgn,true);

	wsprintf(szName, ".\\image\\changeshin_bt.bmp", SKIN_FOLDER);//换肤
	m_btChangeShin.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn = AFCBmpToRgn(m_bk, RGB(255, 0, 255),RGB(1, 1, 1));
	if(hRgn)
		m_btChangeShin.SetWindowRgn(hRgn,true);

	//wsprintf(szName, ".\\image\\split_bt.bmp", SKIN_FOLDER);	//分牌
	//m_btSplit.LoadButtonBitmap(szName,false);	
	//m_bk.SetLoadInfo(szName,true);
	//hRgn = AFCBmpToRgn(m_bk, RGB(255, 0, 255),RGB(1, 1, 1));
	//if (hRgn)
	//	m_btSplit.SetWindowRgn(hRgn,true);

	//wsprintf(szName, ".\\image\\giveup_bt.bmp", SKIN_FOLDER);	//买保险
	//m_btInsurance.LoadButtonBitmap(szName,false);	
	//m_bk.SetLoadInfo(szName,true);
	//hRgn = AFCBmpToRgn(m_bk, RGB(255, 0, 255),RGB(1, 1, 1));
	//if (hRgn)
	//	m_btInsurance.SetWindowRgn(hRgn,true);

	//叫分1按钮
	wsprintf(szName,TEXT(".\\image\\JiaoNt_bt.bmp"));			
	m_btCallScore1.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCallScore1.SetWindowRgn(hRgn,true);

	//不叫按钮
	wsprintf(szName,TEXT(".\\image\\NoNt_bt.bmp"));			
	m_btCallScorePass.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCallScorePass.SetWindowRgn(hRgn,true);

	//建立客户扑克
	//int iCreateIndex[4]={2,1,3,0};
	for (int i = 0; i < PLAY_COUNT; i++)
	{
		m_UserBull[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,20+i,NULL);
		m_UserBull[i].InitGameCard(GetParent());
		m_UserBull[i].SetShowCard(true);
		m_UserBull[i].SetCardParameter(17,10,10);
		
		m_UserCard[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,30+i,NULL);
		m_UserCard[i].InitGameCard(GetParent());
		m_UserCard[i].SetShowCard(true);
		m_UserCard[i].SetCardParameter(17,10,10);
		m_UserBull[i].SetWindowPos(&m_UserCard[i],0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	}

	for (int i = 0; i < PLAY_COUNT; i++)	
	{
		m_SendCardAnimal[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,60+i,NULL);
		m_SendCardAnimal[i].InitGameCard(GetParent());
		m_SendCardAnimal[i].SetUseMouse(false);
		//m_SendCardAnimal[i].SetWindowPos(&wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	}

	//m_SysBackCard.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,25,NULL);
	//m_SysBackCard.InitGameCard(GetParent());
	//m_SysBackCard.SetShowCard(false);
	//m_SysBackCard.SetUseMouse(false);	
	//------------------------------------------------------------------------------------------
	//	m_FlashCard.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,26,NULL);
	//	m_FlashCard.InitGameCard(GetParent());
	//	m_FlashCard.SetShowCard(true);
	//	m_FlashCard.SetUseMouse(false);

	//for(int i=0;i<PLAY_COUNT;i++)
	////发牌动画
	//{
	//	m_SendCardAnimal[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,60+i,NULL);
	//	m_SendCardAnimal[i].InitGameCard(GetParent());
	////	m_SendCardAnimal.SetShowCard(true);
	//	m_SendCardAnimal[i].SetUseMouse(false);
	//	m_SendCardAnimal[i].SetWindowPos(&wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	//}

	//开始动画
	//m_BeginAnimal.Create(IDD_BEGIN_ANIMAL,this);
	//m_BeginAnimal.ShowWindow(SW_HIDE);

	//下注动画
	//m_NoteAnimal.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,50,NULL);
	//m_NoteAnimal.SetWindowPos(&wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);


	//下注后玩家显示动画
	/*for(int i=0;i<PLAY_COUNT;i++)
	{
		m_NoteTotal[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,50+i,NULL);
		m_NoteTotal[i].SetWindowPos(&wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	}*/
	m_Result.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,60,NULL);
	m_Result.SetWindowPos(&wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	//AfxSetResourceHandle(GetModuleHandle(NULL));

	return 0;
}

void CClientPlayView::FixControlSize(int cx,int cy)
{
	if (m_bClass3DInfo)
	{
#ifdef VIDEO
		///视频
		CString  strVideoCfg=CINIFile::GetAppPath()+TEXT("VideoCfg.ini");
		if(!CINIFile::IsFileExist(strVideoCfg))
		{
			/*	Writelog("未找到视频配置文件: ");*/
			return  ;
		}

		CINIFile iniFile(strVideoCfg);
		int	 m_heightVideo=0,m_widthVideo=0;
		m_widthVideo
			=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("WidthVideo"), 0);
		m_heightVideo
			=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("HeightVideo"), 0);
#endif
		///////////////////////////////////////////////////////////////
		if ((cx==0)||(cy==0))
			return;
		//	if(cx>1024)
		//		cx=1024;
		CString s = CINIFile::GetAppPath ();/////本地路径

		CBcfFile f( s + SKIN_FOLDER +".BCF");

		CString key = TEXT("UiSet");
		CRect m_ClientRect;
		GetClientRect(&m_ClientRect);

		CGameImageHelper help(&m_WinFen);
		//修正位置
		//	cy-=110;
		//	m_ClientRect.bottom-=110;

		//扑克索引
		POINT ptCardPoint[PLAY_COUNT];
		int x_Value;				//分辩率修正值
		int y_Value;
		int x_Card;					//牌宽
		int y_Card;					//牌高
		if (GetSystemMetrics(SM_CXSCREEN)>=1024)
		{
			x_Value=40;
			y_Value=100;
			x_Card=70;
			y_Card=95;
		}
		else
		{
			x_Value=40;
			y_Value=40;
			x_Card=54;
			y_Card=73;
		}	//移动坐标
		int iMidLine=cx/2;
		int iBaseLine=cy/2;

		m_PtGameTitle.x=0;
		m_PtGameTitle.y=0;

#ifdef VIDEO
		//头像
		m_PtLogo[0].x = cx/2-LOGO_WIDTH*2;//iMidLine-FACE_WIDTH + f.GetKeyVal(key,TEXT("logo0x"),-40);
		m_PtLogo[0].y = 30;

		ptCardPoint[0].x =m_PtLogo[0].x+m_widthVideo+74;
		ptCardPoint[0].y =m_PtLogo[0].y+m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[0].x = m_PtLogo[0].x- 35;
		m_PtTime[0].y = m_PtLogo[0].y+m_heightVideo-21;

		m_PtNt[0].x=m_PtLogo[0].x -43;
		m_PtNt[0].y=m_PtLogo[0].y;

		m_PtShape[0].x = m_PtLogo[0].x - 43;
		m_PtShape[0].y = m_PtLogo[0].y + m_heightVideo -62;
#else
		//玩家头像
		m_PtLogo[0].x=cx/2-LOGO_WIDTH*2 - 100;;		//x坐标-头像宽-修正x
		m_PtLogo[0].y=100;

		ptCardPoint[0].x=m_PtLogo[0].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[0].y=m_PtLogo[0].y+10;

		m_PtTime[0].x=m_PtLogo[0].x-50;		//计时器在头像左-20
		m_PtTime[0].y=m_PtLogo[0].y+45;

		//庄牌标志
		m_PtNt[0].x = m_PtLogo[0].x + 90;
		m_PtNt[0].y = m_PtLogo[0].y- 40;

		m_PtShape[0].x = m_PtLogo[0].x + 150;
		m_PtShape[0].y = m_PtLogo[0].y + 50;

#endif

		m_PtNote[0].x=cx/2-115;
		m_PtNote[0].y=15+VIEW_FRAME_TOP;

		//本局下注
		m_PtNoteTotal[0].x =iMidLine-50;//m_PtLogo[0].x + f.GetKeyVal(key,TEXT("notetotal0x"),0);
		m_PtNoteTotal[0].y =iBaseLine+80;

		//	m_PtFace[0].x=iMidLine-FACE_WIDTH*3/2;
		//	m_PtFace[0].y=iBaseLine-610/2-30;

		//====正中
		m_PtName[0].x=m_PtLogo[0].x+65;
		m_PtName[0].y=m_PtLogo[0].y+LOGO_HEIGHT - 68;

		m_PtAgree[0].x=m_PtLogo[0].x+LOGO_WIDTH+20;
		m_PtAgree[0].y=m_PtLogo[0].y+5;

		m_PtScore[0].x=iMidLine+WIDTH_NEW_MAN/2+10;//m_PtFace[0].x;
		m_PtScore[0].y=iBaseLine-545/2-HEIGHT_NEW_MAN/2+20;//m_PtFace[0].y+FACE_HEIGHT+30;

		m_PtNoteLimit[0].x=0;//iMidLine+LOGO_WIDTH/2+10;
		m_PtNoteLimit[0].y=0;//LOGO_HEIGHT/2;	

		m_PtPass[0].x=ptCardPoint[0].x-x_Card/2;
		m_PtPass[0].y=ptCardPoint[0].y+y_Card+y_Card/4;

		m_PtNoteAnimalStart[0].x=iMidLine ;
		m_PtNoteAnimalStart[0].y=iBaseLine-548/2;

		m_PtNoteAnimalEnd[0].x=iMidLine-41 ;
		m_PtNoteAnimalEnd[0].y=iBaseLine-FACE_HEIGHT-32;

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[0].x=iMidLine;
		m_PtSendCardAnimalStart[0].y=iBaseLine-100;

		m_PtSendCardAnimalEnd[0].x=ptCardPoint[0].x;
		m_PtSendCardAnimalEnd[0].y=ptCardPoint[0].y;

		m_PtSendCardAnimalEndSplit[0].x=ptCardPoint[0].x + x_Card * 2;
		m_PtSendCardAnimalEndSplit[0].y=ptCardPoint[0].y;

		//显分
		m_PtGetPoint[0].x = ptCardPoint[0].x - x_Card + 20;
		m_PtGetPoint[0].y = ptCardPoint[0].y + 15 + y_Card;

#ifdef VIDEO
		m_PtLogo[1].x=cx-m_widthVideo;		//x坐标-头像宽-修正x
		m_PtLogo[1].y=iBaseLine-m_heightVideo/2;

		//桌面上牌
		ptCardPoint[1].x =m_PtLogo[1].x-74;
		ptCardPoint[1].y =m_PtLogo[1].y+m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[1].x = m_PtLogo[1].x;
		m_PtTime[1].y = m_PtLogo[1].y  - 25;

		m_PtNt[1].x=m_PtLogo[1].x + m_widthVideo -43;
		m_PtNt[1].y=m_PtLogo[1].y  - 65;

		m_PtShape[1].x = m_PtLogo[1].x ;
		m_PtShape[1].y = m_PtLogo[1].y  - 65;
#else
		m_PtLogo[1].x=cx-LOGO_WIDTH-20;			//第一位置头像
		m_PtLogo[1].y=iBaseLine - LOGO_HEIGHT/2;//-cy/4+20;

#ifdef SAO_YANG
		m_PtLogo[1].x=cx-LOGO_WIDTH-10;			//第一位置头像
		m_PtLogo[1].y=iBaseLine - LOGO_HEIGHT/2;
#endif

		ptCardPoint[1].x=m_PtLogo[1].x-LOGO_WIDTH-28;		//用户出的牌正中
		ptCardPoint[1].y=m_PtLogo[1].y+10;

		m_PtTime[1].x=m_PtLogo[1].x - 30;		//计时器在头像左-20
		m_PtTime[1].y=m_PtLogo[1].y - 30;

		//庄牌标志
		m_PtNt[1].x=m_PtLogo[1].x - 60;
		m_PtNt[1].y=m_PtLogo[1].y - 40;

		m_PtShape[1].x = m_PtLogo[1].x  - 260;
		m_PtShape[1].y = m_PtLogo[1].y  + 50;
#endif

		m_PtNote[1].x=cx-x_Card/2-LOGO_WIDTH-30;
		m_PtNote[1].y=cx-x_Card/2-LOGO_WIDTH-cy/4+y_Card/2;

		m_PtNoteTotal[1].x=m_ClientRect.Width()/2;
		m_PtNoteTotal[1].y=m_ClientRect.Height()/2-cy/4+y_Card/2;

		m_PtName[1].x=m_PtLogo[1].x-10;
		m_PtName[1].y=m_PtLogo[1].y+LOGO_HEIGHT - 68;

		m_PtNoteLimit[1].x=cx-x_Card/2-LOGO_WIDTH;
		m_PtNoteLimit[1].y=iBaseLine-cy/4+y_Card/2;	

		m_PtAgree[1].x=m_PtLogo[1].x-38;
		m_PtAgree[1].y=m_PtLogo[1].y+5;

		m_PtScore[1].x=m_PtFace[1].x;
		m_PtScore[1].y=m_PtFace[1].y+FACE_HEIGHT+45-cy/4+y_Card/2;

		m_PtPass[1].x=ptCardPoint[1].x-x_Card/2;
		m_PtPass[1].y=ptCardPoint[1].y-y_Card/4;

		m_PtNoteAnimalStart[1].x=iMidLine+630/2;
		m_PtNoteAnimalStart[1].y=iBaseLine+15;//-cy/4+y_Card/2+30;

		m_PtNoteAnimalEnd[1].x=iMidLine+12;
		m_PtNoteAnimalEnd[1].y=iBaseLine-33/2;//-cy/4+y_Card/2+30;

#ifdef SAO_YANG
		m_PtNoteAnimalEnd[1].x=iMidLine+5;
		m_PtNoteAnimalEnd[1].y=iBaseLine-33/2;//-cy/4+y_Card/2+30;
#endif

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[1].x=iMidLine;
		m_PtSendCardAnimalStart[1].y=iBaseLine-100;//-cy/4+y_Card/2;

		m_PtSendCardAnimalEnd[1].x=ptCardPoint[1].x;
		m_PtSendCardAnimalEnd[1].y=ptCardPoint[1].y -y_Card/2 - 10;//-cy/4;

		m_PtSendCardAnimalEndSplit[1].x=ptCardPoint[1].x;
		m_PtSendCardAnimalEndSplit[1].y=ptCardPoint[1].y + y_Card/2;//-cy/4;

		//显分
		m_PtGetPoint[1].x = ptCardPoint[1].x - x_Card + 20;
		m_PtGetPoint[1].y = ptCardPoint[1].y - y_Card/2 - 22;// + y_Card;



#ifndef TWO_NN
#ifdef VIDEO
		m_PtLogo[2].x =cx/2-LOGO_WIDTH*2;		//x坐标-头像宽-修正x
		m_PtLogo[2].y=cy-LOGO_HEIGHT-y_Card/3 - 20;

		//桌面上牌
		ptCardPoint[2].x =m_PtLogo[2].x+m_widthVideo+74;
		ptCardPoint[2].y =m_PtLogo[2].y +m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[2].x = m_PtLogo[2].x ;
		m_PtTime[2].y = m_PtLogo[2].y  - 25;

		//庄标志
		m_PtNt[2].x=m_PtLogo[2].x - 43;
		m_PtNt[2].y=m_PtLogo[2].y;

		m_PtShape[2].x = m_PtLogo[2].x-43;
		m_PtShape[2].y = m_PtLogo[2].y + m_heightVideo -62;
#else
		m_PtLogo[2].x=cx/2-LOGO_WIDTH*2 - 100;		//头像x修正
		m_PtLogo[2].y=cy-LOGO_HEIGHT+10;	

		ptCardPoint[2].x=m_PtLogo[2].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[2].y=m_PtLogo[2].y + 10;

		m_PtTime[2].x=m_PtLogo[2].x + 350;		//
		m_PtTime[2].y=m_PtLogo[2].y - 50;

		//庄标志
		m_PtNt[2].x=m_PtLogo[2].x+90;
		m_PtNt[2].y=m_PtLogo[2].y-40;

		m_PtShape[2].x = m_PtLogo[2].x + 150;
		m_PtShape[2].y = m_PtLogo[2].y + 53;
#endif
		m_PtNote[2].x=cx/2-115;
		m_PtNote[2].y=cy-y_Card-LOGO_HEIGHT;

		m_PtNoteTotal[2].x=cx/2;
		m_PtNoteTotal[2].y=cy-y_Card-LOGO_HEIGHT;

		m_PtFace[2].x=iMidLine-FACE_WIDTH*3/2+15;
		m_PtFace[2].y=iBaseLine+610/2-FACE_HEIGHT*2;

		m_PtNoteLimit[2].x=iMidLine-LOGO_WIDTH/2+LOGO_WIDTH;							
		m_PtNoteLimit[2].y=cy-y_Card-LOGO_HEIGHT;

		m_PtName[2].x=m_PtLogo[2].x+65;
		m_PtName[2].y=m_PtLogo[2].y + LOGO_HEIGHT - 68;

		m_PtAgree[2].x=m_PtLogo[2].x+LOGO_WIDTH+20;
		m_PtAgree[2].y=m_PtLogo[2].y+5;

		m_PtScore[2].x=iMidLine-WIDTH_NEW_MAN/2;//m_PtFace[2].x;
		m_PtScore[2].y=cy;//+50;

		m_PtPass[2].x=ptCardPoint[2].x-x_Card/2;
		m_PtPass[2].y=ptCardPoint[2].y-y_Card/4;

		//下注动画起点
		m_PtNoteAnimalStart[2].x =m_PtLogo[2].x + LOGO_WIDTH * 2 + 30;
		m_PtNoteAnimalStart[2].y =m_PtLogo[2].y + LOGO_HEIGHT;

		//m_PtNoteAnimalEnd[2].x = m_PtLogo[2].x +  LOGO_WIDTH * 2 + 30;
		//m_PtNoteAnimalEnd[2].y = m_PtLogo[2].y  -60;

		m_PtNoteAnimalEnd[2].x = iMidLine - 41;
		m_PtNoteAnimalEnd[2].y = iBaseLine+120-m_WinFen.GetHeight();//m_PtLogo[2].y - LOGO_HEIGHT;

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[2].x=iMidLine;
		m_PtSendCardAnimalStart[2].y=iBaseLine-100;

		m_PtSendCardAnimalEnd[2].x=ptCardPoint[2].x;
		m_PtSendCardAnimalEnd[2].y=ptCardPoint[2].y;

		m_PtSendCardAnimalEndSplit[2].x=ptCardPoint[2].x + y_Card*2;
		m_PtSendCardAnimalEndSplit[2].y=ptCardPoint[2].y;

		m_PtGetPoint[2].x = ptCardPoint[2].x - x_Card + 20;
		m_PtGetPoint[2].y = ptCardPoint[2].y + 15 + y_Card;

#ifdef VIDEO
		m_PtLogo[3].x=0;
		m_PtLogo[3].y=iBaseLine-m_heightVideo/2;

		//桌面上牌
		ptCardPoint[3].x =m_PtLogo[3].x+m_widthVideo+74;
		ptCardPoint[3].y =m_PtLogo[3].y+m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[3].x = m_PtLogo[3].x + m_widthVideo -32;
		m_PtTime[3].y = m_PtLogo[3].y - 25;

		//庄标志
		m_PtNt[3].x=m_PtLogo[3].x  ;
		m_PtNt[3].y=m_PtLogo[3].y - 65;


		m_PtShape[3].x = m_PtLogo[3].x + m_widthVideo -40;
		m_PtShape[3].y = m_PtLogo[3].y  - 65;
#else
		m_PtLogo[3].x=5;
		m_PtLogo[3].y=iBaseLine - LOGO_HEIGHT/2;//-cy/4+20;

#ifdef SAO_YANG
		m_PtLogo[3].x=0;
		m_PtLogo[3].y=iBaseLine - LOGO_HEIGHT/2;;
#endif

		ptCardPoint[3].x=m_PtLogo[3].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[3].y=m_PtLogo[3].y+10;

		m_PtTime[3].x=m_PtLogo[3].x+LOGO_WIDTH + 60;		//计时器在头像左-20
		m_PtTime[3].y=m_PtLogo[3].y-30;

		//庄标志
		m_PtNt[3].x=m_PtLogo[3].x + 90;
		m_PtNt[3].y=m_PtLogo[3].y - 40;

		m_PtShape[3].x = m_PtLogo[3].x + 150;
		m_PtShape[3].y = m_PtLogo[3].y + 50;
#endif

		m_PtNote[3].x=ptCardPoint[3].x+LOGO_WIDTH+x_Card + 20;
		m_PtNote[3].y=iBaseLine-cy/4+y_Card/2;


		m_PtNoteTotal[3].x=ptCardPoint[3].x+LOGO_WIDTH+x_Card;
		m_PtNoteTotal[3].y=iBaseLine-cy/4+y_Card/2;

		m_PtFace[3].x=iMidLine-750/2-LOGO_WIDTH;
		m_PtFace[3].y=iBaseLine-FACE_HEIGHT-cy/4+y_Card/2;

		m_PtName[3].x=m_PtLogo[3].x + 65;
		m_PtName[3].y=m_PtLogo[3].y+LOGO_HEIGHT - 68;

		m_PtNoteLimit[3].x=LOGO_WIDTH+x_Card;
		m_PtNoteLimit[3].y=iBaseLine-cy/4+y_Card/2;

		m_PtAgree[3].x=m_PtLogo[3].x+LOGO_WIDTH+20;
		m_PtAgree[3].y=m_PtLogo[3].y+5;


		m_PtScore[3].x=m_PtFace[3].x+ptCardPoint[3].x;
		m_PtScore[3].y=m_PtFace[3].y+FACE_HEIGHT+50-cy/4+y_Card/2;

		m_PtPass[3].x=ptCardPoint[3].x-x_Card/2;
		m_PtPass[3].y=ptCardPoint[3].y-y_Card/4;

		m_PtNoteAnimalStart[3].x=LOGO_WIDTH;
		m_PtNoteAnimalStart[3].y=iBaseLine+15;//-cy/4+y_Card/2+30;

		m_PtNoteAnimalEnd[3].x=iMidLine-FACE_WIDTH-12;
		m_PtNoteAnimalEnd[3].y=iBaseLine-33/2;//-cy/4+y_Card/2+30;

#ifdef SAO_YANG
		m_PtNoteAnimalEnd[3].x=iMidLine-FACE_WIDTH-23;
		m_PtNoteAnimalEnd[3].y=iBaseLine-33/2;;
#endif

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[3].x=iMidLine;
		m_PtSendCardAnimalStart[3].y=iBaseLine-100;//-cy/4+y_Card/2;

		m_PtSendCardAnimalEnd[3].x=ptCardPoint[3].x;
		m_PtSendCardAnimalEnd[3].y=ptCardPoint[3].y - y_Card/2 - 10;;//-cy/4+y_Card/2;

		m_PtSendCardAnimalEndSplit[3].x=ptCardPoint[3].x;
		m_PtSendCardAnimalEndSplit[3].y=ptCardPoint[3].y + y_Card/2 ;

		m_PtGetPoint[3].x = ptCardPoint[3].x - x_Card + 20;
		m_PtGetPoint[3].y = ptCardPoint[3].y - y_Card/2 - 25;// + y_Card;
#endif	//end if of TWO_NN

#ifdef TWO_NN	//二人场，重构1号位置的坐标 zxj 2009-11-21
#ifdef VIDEO
		m_PtLogo[1].x =cx/2-LOGO_WIDTH*2;		//x坐标-头像宽-修正x
		m_PtLogo[1].y=cy-LOGO_HEIGHT-y_Card/3 - 20;

		//桌面上牌
		ptCardPoint[1].x =m_PtLogo[1].x+m_widthVideo+74;
		ptCardPoint[1].y =m_PtLogo[1].y +m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[1].x = m_PtLogo[1].x ;
		m_PtTime[1].y = m_PtLogo[1].y  - 25;

		//庄标志
		m_PtNt[1].x=m_PtLogo[1].x - 43;
		m_PtNt[1].y=m_PtLogo[1].y;

		m_PtShape[1].x = m_PtLogo[1].x-43;
		m_PtShape[1].y = m_PtLogo[1].y + m_heightVideo -62;
#else
		m_PtLogo[1].x=cx/2-LOGO_WIDTH*2 - 100;		//头像x修正
		m_PtLogo[1].y=cy-LOGO_HEIGHT + 10;	

		ptCardPoint[1].x=m_PtLogo[1].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[1].y=m_PtLogo[1].y + 10;

		m_PtTime[1].x=m_PtLogo[1].x + 350;		//
		m_PtTime[1].y=m_PtLogo[1].y - 50;

		//庄标志
		m_PtNt[1].x=m_PtLogo[1].x+90;
		m_PtNt[1].y=m_PtLogo[1].y -40;

		m_PtShape[1].x = m_PtLogo[1].x + 150;
		m_PtShape[1].y = m_PtLogo[1].y + 53;
#endif
		m_PtNote[1].x=cx/2-115;
		m_PtNote[1].y=cy-y_Card-LOGO_HEIGHT;

		m_PtNoteTotal[1].x=cx/2;
		m_PtNoteTotal[1].y=cy-y_Card-LOGO_HEIGHT;

		m_PtFace[1].x=iMidLine-FACE_WIDTH*3/2+15;
		m_PtFace[1].y=iBaseLine+610/2-FACE_HEIGHT*2;

		m_PtNoteLimit[1].x=iMidLine-LOGO_WIDTH/2+LOGO_WIDTH;							
		m_PtNoteLimit[1].y=cy-y_Card-LOGO_HEIGHT;

		m_PtName[1].x=m_PtLogo[1].x+65;
		m_PtName[1].y=m_PtLogo[1].y + LOGO_HEIGHT - 68;

		m_PtAgree[1].x=m_PtLogo[1].x+LOGO_WIDTH+20;
		m_PtAgree[1].y=m_PtLogo[1].y+5;

		m_PtScore[1].x=iMidLine-WIDTH_NEW_MAN/2;//m_PtFace[1].x;
		m_PtScore[1].y=cy;//+50;

		m_PtPass[1].x=ptCardPoint[1].x-x_Card/2;
		m_PtPass[1].y=ptCardPoint[1].y-y_Card/4;

		//下注动画起点
		m_PtNoteAnimalStart[1].x =m_PtLogo[1].x + LOGO_WIDTH * 2 + 30;
		m_PtNoteAnimalStart[1].y =m_PtLogo[1].y + LOGO_HEIGHT;

		//m_PtNoteAnimalEnd[1].x = m_PtLogo[1].x +  LOGO_WIDTH * 2 + 30;
		//m_PtNoteAnimalEnd[1].y = m_PtLogo[1].y  -60;

		m_PtNoteAnimalEnd[1].x = iMidLine - 41;
		m_PtNoteAnimalEnd[1].y = iBaseLine+120-m_WinFen.GetHeight();//m_PtLogo[1].y - LOGO_HEIGHT;

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[1].x=iMidLine;
		m_PtSendCardAnimalStart[1].y=iBaseLine-100;

		m_PtSendCardAnimalEnd[1].x=ptCardPoint[1].x;
		m_PtSendCardAnimalEnd[1].y=ptCardPoint[1].y;

		m_PtSendCardAnimalEndSplit[1].x=ptCardPoint[1].x + y_Card*2;
		m_PtSendCardAnimalEndSplit[1].y=ptCardPoint[1].y;

		m_PtGetPoint[1].x = ptCardPoint[1].x - x_Card + 20;
		m_PtGetPoint[1].y = ptCardPoint[1].y + 15 + y_Card;
#endif	//重构1号位置坐标结束 zxj 2009-11-21

		m_PtGif[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("flower0x"),0);
		m_PtGif[0].y = m_PtLogo[0].y+f.GetKeyVal(key,TEXT("flower0y"),0);
		m_PtGif[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("flower1x"),0);
		m_PtGif[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("flower1y"),0);

#ifndef TWO_NN
		m_PtGif[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("flower2x"),0);
		m_PtGif[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("flower2y"),0);
		m_PtGif[3].x = m_PtLogo[3].x+f.GetKeyVal(key,TEXT("flower3x"),0);
		m_PtGif[3].y = m_PtLogo[3].y+f.GetKeyVal(key,TEXT("flower3y"),0);
#endif

		m_BtnRect0.left = iMidLine - (4*82+3*10)/2;
		m_BtnRect0.top = cy - 250;
		m_BtnRect0.right = m_BtnRect0.left + help.GetWidth();
		m_BtnRect0.bottom = m_BtnRect0.top + help.GetHeight();

		m_BtnRect1.left = m_BtnRect0.right + 10;
		m_BtnRect1.top = m_BtnRect0.top;
		m_BtnRect1.right = m_BtnRect1.left + help.GetWidth();
		m_BtnRect1.bottom = m_BtnRect1.top + help.GetHeight();

		m_BtnRect2.left = m_BtnRect1.right + 10;
		m_BtnRect2.top = m_BtnRect0.top;
		m_BtnRect2.right = m_BtnRect2.left + help.GetWidth();
		m_BtnRect2.bottom = m_BtnRect2.top + help.GetHeight();

		m_BtnRect3.left = m_BtnRect2.right + 10;
		m_BtnRect3.top = m_BtnRect0.top;
		m_BtnRect3.right = m_BtnRect3.left + help.GetWidth();
		m_BtnRect3.bottom = m_BtnRect3.top + help.GetHeight();

		//用户下注上下限
		m_PtShowLimit.x=20;//iMidLine-567/2-100;
		m_PtShowLimit.y=0;
		//用户下注池
		m_PtNoteAll.x=iMidLine;
		m_PtNoteAll.y=iBaseLine;
		//用户下注动画起点
		m_PtBeginAnimalStart.x=iMidLine-460/2;
		m_PtBeginAnimalStart.y=iBaseLine/2;

		//用户下注动画终点
		m_PtBeginAnimalEnd.x=iMidLine-460/2;
		m_PtBeginAnimalEnd.y=iBaseLine;

		//设置奖池筹码数
		//	m_NoteAll[0].SetBasePoint(m_PtNoteAll);
		//移动扑克

#ifndef TWO_NN
		m_UserBull[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y - 95),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[1].SetBasePoint(CPoint(ptCardPoint[1].x - 80,ptCardPoint[1].y - 95),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[2].SetBasePoint(CPoint(ptCardPoint[2].x + 80,ptCardPoint[2].y - 95),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[3].SetBasePoint(CPoint(ptCardPoint[3].x + 80,ptCardPoint[3].y - 95),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
#else 
		m_UserBull[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y - 95),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[1].SetBasePoint(CPoint(ptCardPoint[1].x + 80,ptCardPoint[1].y - 95),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

#endif

#ifndef TWO_NN
		m_UserCard[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y - 60),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[1].SetBasePoint(CPoint(ptCardPoint[1].x - 80,ptCardPoint[1].y - 60),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[2].SetBasePoint(CPoint(ptCardPoint[2].x + 80,ptCardPoint[2].y - 60),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[3].SetBasePoint(CPoint(ptCardPoint[3].x + 80,ptCardPoint[3].y - 60),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		// 牌型的位置跟随牌控件移动
		m_CardShape[0].SetPoint(ptCardPoint[0].x, ptCardPoint[0].y - 30);
		m_CardShape[1].SetPoint(ptCardPoint[1].x - 160, ptCardPoint[1].y - 30);
		m_CardShape[2].SetPoint(ptCardPoint[2].x, ptCardPoint[2].y - 30);
		m_CardShape[3].SetPoint(ptCardPoint[3].x, ptCardPoint[3].y - 30);
#else

		m_UserCard[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y - 60),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[1].SetBasePoint(CPoint(ptCardPoint[1].x + 80,ptCardPoint[1].y - 60),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		// 牌型的位置跟随牌控件移动
		m_CardShape[0].SetPoint(ptCardPoint[0].x, ptCardPoint[0].y - 30);
		m_CardShape[1].SetPoint(ptCardPoint[1].x, ptCardPoint[1].y - 30);

#endif

#ifdef SAO_YANG
		m_UserBull[1].SetBasePoint(CPoint(ptCardPoint[1].x - 55,ptCardPoint[1].y - 5),


			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[3].SetBasePoint(CPoint(ptCardPoint[3].x + 55,ptCardPoint[3].y - 10),


			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		m_UserCard[1].SetBasePoint(CPoint(ptCardPoint[1].x - 55,ptCardPoint[1].y + 25),


			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[3].SetBasePoint(CPoint(ptCardPoint[3].x + 55,ptCardPoint[3].y + 25),


			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		// 牌型的位置跟随牌控件移动
		m_CardShape[1].SetPoint(ptCardPoint[1].x - 135, ptCardPoint[1].y + 50);
		m_CardShape[3].SetPoint(ptCardPoint[3].x-25, ptCardPoint[3].y + 50);
#endif

		for(int i=0;i<PLAY_COUNT;i++)
		{
			m_SendCardAnimal[i].SetBasePoint(CPoint(/*3*iMidLine/2,iBaseLine/2*/iMidLine,iBaseLine),CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		}

		//移动反牌视图
		CRect ContronRect;
		m_NtList.GetClientRect(&ContronRect);
		m_NtList.MoveWindow(iMidLine-ContronRect.Width()/2+30,iBaseLine+100,ContronRect.Width(),ContronRect.Height(),FALSE);

		//移动控件
		//移动信息视图
		m_GameNoteView.GetClientRect(&ContronRect);
		m_GameNoteView.MoveWindow(iMidLine-ContronRect.Width()/2,iBaseLine-ContronRect.Height()/2,
			ContronRect.Width(),ContronRect.Height(),FALSE);
		m_btContinue.GetClientRect(&ContronRect);
		//m_btContinue.MoveWindow(iMidLine - ContronRect.Width()/2,cy - 220,ContronRect.right,ContronRect.bottom);

		m_btContinue.MoveWindow(iMidLine+20,cy - 220 /*iBaseLine+140*/, ContronRect.Width(), ContronRect.Height());
		m_btLeave.MoveWindow(iMidLine-20-ContronRect.Width(), cy - 220/*iBaseLine+140*/, ContronRect.Width(), ContronRect.Height());

		m_Result.GetClientRect(&ContronRect);
		m_Result.MoveWindow((cx - ContronRect.Width())/2,(cy - ContronRect.Height())/2-30 ,ContronRect.right,ContronRect.bottom);

		m_btBull.GetClientRect(&ContronRect);
		//	m_btNote.MoveWindow(cx - 4*ContronRect.right+30, cy - 100, ContronRect.right,ContronRect.bottom);                        
		///m_btBull.MoveWindow(iMidLine-2*ContronRect.Width()+10, cy - 220, ContronRect.right,ContronRect.bottom);   
        m_btBull.MoveWindow(iMidLine-ContronRect.Width()/2 , cy - 220, ContronRect.right,ContronRect.bottom);
		m_btOpen.GetClientRect(&ContronRect);
		m_btOpen.MoveWindow(iMidLine+ContronRect.Width()-10,  cy - 220,ContronRect.right,ContronRect.bottom);                     
		m_btReset.GetClientRect(&ContronRect);
		///m_btReset.MoveWindow(iMidLine-ContronRect.Width()/2 , cy - 220, ContronRect.right,ContronRect.bottom);
        m_btReset.MoveWindow(iMidLine-2*ContronRect.Width()+10, cy - 220, ContronRect.right,ContronRect.bottom);

#ifdef SAO_YANG
		m_btChangeShin.GetClientRect(&ContronRect);	//换肤
		m_btChangeShin.MoveWindow(cx-ContronRect.Width()-10, cy-ContronRect.Height()-10, ContronRect.right,ContronRect.bottom); 
#endif

		//叫分
		m_btCallScore1.GetClientRect(&ContronRect);
		m_btCallScore1.MoveWindow(iMidLine-2*ContronRect.Width()+10, cy - 220,ContronRect.Width(),ContronRect.Height());
		m_btCallScorePass.MoveWindow(iMidLine+ContronRect.Width()-10,  cy - 220,ContronRect.Width(),ContronRect.Height());


#ifdef VIDEO
#ifndef TWO_NN 
		//视频的坐标出
		m_rectVideoFrame[2].top=m_PtLogo[2].y;// cy-m_heightVideo;
		m_rectVideoFrame[2].left=m_PtLogo[2].x;//10;
		m_rectVideoFrame[2].bottom=m_rectVideoFrame[2].top+m_heightVideo;
		m_rectVideoFrame[2].right=m_rectVideoFrame[2].left+m_widthVideo;
		m_rectVideoFrame[3].top=m_PtLogo[3].y;//249;
		m_rectVideoFrame[3].left=m_PtLogo[3].x;//10;
		m_rectVideoFrame[3].bottom=m_rectVideoFrame[3].top+m_heightVideo;
		m_rectVideoFrame[3].right=m_rectVideoFrame[3].left+m_widthVideo;
#endif	 
		m_rectVideoFrame[0].top=m_PtLogo[0].y;//0;
		m_rectVideoFrame[0].left=m_PtLogo[0].x;//220;
		m_rectVideoFrame[0].bottom=m_rectVideoFrame[0].top+m_heightVideo;
		m_rectVideoFrame[0].right=m_rectVideoFrame[0].left+m_widthVideo;
		m_rectVideoFrame[1].top=m_PtLogo[1].y;//242;
		m_rectVideoFrame[1].left=m_PtLogo[1].x;//cx-m_widthVideo+5;
		m_rectVideoFrame[1].bottom=m_rectVideoFrame[1].top+m_heightVideo;
		m_rectVideoFrame[1].right=m_rectVideoFrame[1].left+m_widthVideo; 

		///设置视频窗口位置 
		if(NULL!=CPlayVideo::CreatePlayVideo())
			CPlayVideo::CreatePlayVideo()->SetUserPos();  
#endif

		//改变积分榜,x坐标
		CRect rect;
		m_showcoredlg.GetClientRect(&rect);
		m_showcoredlg.SetWindowPos(NULL,cx-rect.Width()-m_imgScoreRule.GetWidth(),-m_showcoredlg.m_showh,0,0,SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOSIZE);

		m_PtOpenCard[0].SetPoint(ptCardPoint[0].x-40, ptCardPoint[0].y+110);
		m_PtOpenCard[1].SetPoint(ptCardPoint[1].x-30, ptCardPoint[1].y-27);
		m_PtOpenCard[2].SetPoint(ptCardPoint[2].x-30, ptCardPoint[2].y-27);
		m_PtOpenCard[3].SetPoint(ptCardPoint[3].x-30, ptCardPoint[3].y-27);
	}
	else
	{
#ifdef VIDEO
		///视频
		CString  strVideoCfg=CINIFile::GetAppPath()+TEXT("VideoCfg.ini");
		if(!CINIFile::IsFileExist(strVideoCfg))
		{

			/*	Writelog("未找到视频配置文件: ");*/
			return  ;
		}

		CINIFile iniFile(strVideoCfg);
		int	 m_heightVideo=0,m_widthVideo=0;
		m_widthVideo
			=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("WidthVideo"), 0);
		m_heightVideo
			=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("HeightVideo"), 0);
#endif
		///////////////////////////////////////////////////////////////
		if ((cx==0)||(cy==0))
			return;
		//	if(cx>1024)
		//		cx=1024;
		CString s = CINIFile::GetAppPath ();/////本地路径

		CBcfFile f( s + SKIN_FOLDER +".BCF");

		CString key = TEXT("UiSet");
		CRect m_ClientRect;
		GetClientRect(&m_ClientRect);

		CGameImageHelper help(&m_WinFen);
		//修正位置
		//	cy-=110;
		//	m_ClientRect.bottom-=110;

		//扑克索引
		POINT ptCardPoint[PLAY_COUNT];
		int x_Value;				//分辩率修正值
		int y_Value;
		int x_Card;					//牌宽
		int y_Card;					//牌高
		if (GetSystemMetrics(SM_CXSCREEN)>=1024)
		{
			x_Value=40;
			y_Value=100;
			x_Card=70;
			y_Card=95;
		}
		else
		{
			x_Value=40;
			y_Value=40;
			x_Card=54;
			y_Card=73;
		}	//移动坐标
		int iMidLine=cx/2;
		int iBaseLine=cy/2;

		m_PtGameTitle.x=0;
		m_PtGameTitle.y=0;

#ifdef VIDEO
		//头像
		m_PtLogo[0].x = cx/2-LOGO_WIDTH*2;//iMidLine-FACE_WIDTH + f.GetKeyVal(key,TEXT("logo0x"),-40);
		m_PtLogo[0].y = 30;

		ptCardPoint[0].x =m_PtLogo[0].x+m_widthVideo+74;
		ptCardPoint[0].y =m_PtLogo[0].y+m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[0].x = m_PtLogo[0].x- 35;
		m_PtTime[0].y = m_PtLogo[0].y+m_heightVideo-21;

		m_PtNt[0].x=m_PtLogo[0].x -43;
		m_PtNt[0].y=m_PtLogo[0].y;

		m_PtShape[0].x = m_PtLogo[0].x - 43;
		m_PtShape[0].y = m_PtLogo[0].y + m_heightVideo -62;
#else
		//玩家头像
		m_PtLogo[0].x=cx/2-LOGO_WIDTH*2 - 70;;		//x坐标-头像宽-修正x
		m_PtLogo[0].y=10;

		ptCardPoint[0].x=m_PtLogo[0].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[0].y=m_PtLogo[0].y+10;

		m_PtTime[0].x=m_PtLogo[0].x-50;		//计时器在头像左-20
		m_PtTime[0].y=m_PtLogo[0].y+93;

		//庄牌标志
		m_PtNt[0].x = m_PtLogo[0].x + 90;
		m_PtNt[0].y = m_PtLogo[0].y+15;

		m_PtShape[0].x = m_PtLogo[0].x + 150;
		m_PtShape[0].y = m_PtLogo[0].y + 50;

#endif

		m_PtNote[0].x=cx/2-115;
		m_PtNote[0].y=15+VIEW_FRAME_TOP;

		//本局下注
		m_PtNoteTotal[0].x =iMidLine-50;//m_PtLogo[0].x + f.GetKeyVal(key,TEXT("notetotal0x"),0);
		m_PtNoteTotal[0].y =iBaseLine+80;

		//	m_PtFace[0].x=iMidLine-FACE_WIDTH*3/2;
		//	m_PtFace[0].y=iBaseLine-610/2-30;

		//====正中
		m_PtName[0].x=m_PtLogo[0].x+65;
		m_PtName[0].y=m_PtLogo[0].y+LOGO_HEIGHT - 11;

		m_PtAgree[0].x=m_PtLogo[0].x+LOGO_WIDTH+20;
		m_PtAgree[0].y=m_PtLogo[0].y+5;

		m_PtScore[0].x=iMidLine+WIDTH_NEW_MAN/2+10;//m_PtFace[0].x;
		m_PtScore[0].y=iBaseLine-545/2-HEIGHT_NEW_MAN/2+20;//m_PtFace[0].y+FACE_HEIGHT+30;

		m_PtNoteLimit[0].x=0;//iMidLine+LOGO_WIDTH/2+10;
		m_PtNoteLimit[0].y=0;//LOGO_HEIGHT/2;	

		m_PtPass[0].x=ptCardPoint[0].x-x_Card/2;
		m_PtPass[0].y=ptCardPoint[0].y+y_Card+y_Card/4;

		m_PtNoteAnimalStart[0].x=iMidLine ;
		m_PtNoteAnimalStart[0].y=iBaseLine-548/2;

		m_PtNoteAnimalEnd[0].x=iMidLine-41 ;
		m_PtNoteAnimalEnd[0].y=iBaseLine-FACE_HEIGHT-32;

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[0].x=iMidLine;
		m_PtSendCardAnimalStart[0].y=iBaseLine-100;

		m_PtSendCardAnimalEnd[0].x=ptCardPoint[0].x;
		m_PtSendCardAnimalEnd[0].y=ptCardPoint[0].y;

		m_PtSendCardAnimalEndSplit[0].x=ptCardPoint[0].x + x_Card * 2;
		m_PtSendCardAnimalEndSplit[0].y=ptCardPoint[0].y;

		//显分
		m_PtGetPoint[0].x = ptCardPoint[0].x - x_Card + 20;
		m_PtGetPoint[0].y = ptCardPoint[0].y + 15 + y_Card;

#ifdef VIDEO
		m_PtLogo[1].x=cx-m_widthVideo;		//x坐标-头像宽-修正x
		m_PtLogo[1].y=iBaseLine-m_heightVideo/2;

		//桌面上牌
		ptCardPoint[1].x =m_PtLogo[1].x-74;
		ptCardPoint[1].y =m_PtLogo[1].y+m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[1].x = m_PtLogo[1].x;
		m_PtTime[1].y = m_PtLogo[1].y  - 25;

		m_PtNt[1].x=m_PtLogo[1].x + m_widthVideo -43;
		m_PtNt[1].y=m_PtLogo[1].y  - 65;

		m_PtShape[1].x = m_PtLogo[1].x ;
		m_PtShape[1].y = m_PtLogo[1].y  - 65;
#else
		m_PtLogo[1].x=cx-LOGO_WIDTH-20;			//第一位置头像
		m_PtLogo[1].y=iBaseLine - LOGO_HEIGHT/2;//-cy/4+20;

#ifdef SAO_YANG
		m_PtLogo[1].x=cx-LOGO_WIDTH+5;			//第一位置头像
		m_PtLogo[1].y=iBaseLine - LOGO_HEIGHT/2;
#endif

		ptCardPoint[1].x=m_PtLogo[1].x-LOGO_WIDTH-28;		//用户出的牌正中
		ptCardPoint[1].y=m_PtLogo[1].y+10;

		m_PtTime[1].x=m_PtLogo[1].x - 17;		//计时器在头像左-20
		m_PtTime[1].y=m_PtLogo[1].y - 30;

		//庄牌标志
		m_PtNt[1].x=m_PtLogo[1].x - 60;
		m_PtNt[1].y=m_PtLogo[1].y + 15;

		m_PtShape[1].x = m_PtLogo[1].x  - 260;
		m_PtShape[1].y = m_PtLogo[1].y  + 50;
#endif

		m_PtNote[1].x=cx-x_Card/2-LOGO_WIDTH-30;
		m_PtNote[1].y=cx-x_Card/2-LOGO_WIDTH-cy/4+y_Card/2;

		m_PtNoteTotal[1].x=m_ClientRect.Width()/2;
		m_PtNoteTotal[1].y=m_ClientRect.Height()/2-cy/4+y_Card/2;

		m_PtName[1].x=m_PtLogo[1].x-10;
		m_PtName[1].y=m_PtLogo[1].y+LOGO_HEIGHT - 11;

		m_PtNoteLimit[1].x=cx-x_Card/2-LOGO_WIDTH;
		m_PtNoteLimit[1].y=iBaseLine-cy/4+y_Card/2;	

		m_PtAgree[1].x=m_PtLogo[1].x-38;
		m_PtAgree[1].y=m_PtLogo[1].y+5;

		m_PtScore[1].x=m_PtFace[1].x;
		m_PtScore[1].y=m_PtFace[1].y+FACE_HEIGHT+45-cy/4+y_Card/2;

		m_PtPass[1].x=ptCardPoint[1].x-x_Card/2;
		m_PtPass[1].y=ptCardPoint[1].y-y_Card/4;

		m_PtNoteAnimalStart[1].x=iMidLine+630/2;
		m_PtNoteAnimalStart[1].y=iBaseLine+15;//-cy/4+y_Card/2+30;

		m_PtNoteAnimalEnd[1].x=iMidLine+12;
		m_PtNoteAnimalEnd[1].y=iBaseLine-33/2;//-cy/4+y_Card/2+30;

#ifdef SAO_YANG
		m_PtNoteAnimalEnd[1].x=iMidLine+5;
		m_PtNoteAnimalEnd[1].y=iBaseLine-33/2;//-cy/4+y_Card/2+30;
#endif

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[1].x=iMidLine;
		m_PtSendCardAnimalStart[1].y=iBaseLine-100;//-cy/4+y_Card/2;

		m_PtSendCardAnimalEnd[1].x=ptCardPoint[1].x;
		m_PtSendCardAnimalEnd[1].y=ptCardPoint[1].y -y_Card/2 - 10;//-cy/4;

		m_PtSendCardAnimalEndSplit[1].x=ptCardPoint[1].x;
		m_PtSendCardAnimalEndSplit[1].y=ptCardPoint[1].y + y_Card/2;//-cy/4;

		//显分
		m_PtGetPoint[1].x = ptCardPoint[1].x - x_Card + 20;
		m_PtGetPoint[1].y = ptCardPoint[1].y - y_Card/2 - 22;// + y_Card;



#ifndef TWO_NN
#ifdef VIDEO
		m_PtLogo[2].x =cx/2-LOGO_WIDTH*2;		//x坐标-头像宽-修正x
		m_PtLogo[2].y=cy-LOGO_HEIGHT-y_Card/3 - 20;

		//桌面上牌
		ptCardPoint[2].x =m_PtLogo[2].x+m_widthVideo+74;
		ptCardPoint[2].y =m_PtLogo[2].y +m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[2].x = m_PtLogo[2].x ;
		m_PtTime[2].y = m_PtLogo[2].y  - 25;

		//庄标志
		m_PtNt[2].x=m_PtLogo[2].x - 43;
		m_PtNt[2].y=m_PtLogo[2].y;

		m_PtShape[2].x = m_PtLogo[2].x-43;
		m_PtShape[2].y = m_PtLogo[2].y + m_heightVideo -62;
#else
		m_PtLogo[2].x=cx/2-LOGO_WIDTH*2 - 70;		//头像x修正
		m_PtLogo[2].y=cy-LOGO_HEIGHT-80;	

		ptCardPoint[2].x=m_PtLogo[2].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[2].y=m_PtLogo[2].y + 10;

		m_PtTime[2].x=m_PtLogo[2].x + 350;		//
		m_PtTime[2].y=m_PtLogo[2].y + 30;

		//庄标志
		m_PtNt[2].x=m_PtLogo[2].x+90;
		m_PtNt[2].y=m_PtLogo[2].y+15;

		m_PtShape[2].x = m_PtLogo[2].x + 150;
		m_PtShape[2].y = m_PtLogo[2].y + 53;
#endif
		m_PtNote[2].x=cx/2-115;
		m_PtNote[2].y=cy-y_Card-LOGO_HEIGHT;

		m_PtNoteTotal[2].x=cx/2;
		m_PtNoteTotal[2].y=cy-y_Card-LOGO_HEIGHT;

		m_PtFace[2].x=iMidLine-FACE_WIDTH*3/2+15;
		m_PtFace[2].y=iBaseLine+610/2-FACE_HEIGHT*2;

		m_PtNoteLimit[2].x=iMidLine-LOGO_WIDTH/2+LOGO_WIDTH;							
		m_PtNoteLimit[2].y=cy-y_Card-LOGO_HEIGHT;

		m_PtName[2].x=m_PtLogo[2].x+65;
		m_PtName[2].y=m_PtLogo[2].y + LOGO_HEIGHT - 11;

		m_PtAgree[2].x=m_PtLogo[2].x+LOGO_WIDTH+20;
		m_PtAgree[2].y=m_PtLogo[2].y+5;

		m_PtScore[2].x=iMidLine-WIDTH_NEW_MAN/2;//m_PtFace[2].x;
		m_PtScore[2].y=cy;//+50;

		m_PtPass[2].x=ptCardPoint[2].x-x_Card/2;
		m_PtPass[2].y=ptCardPoint[2].y-y_Card/4;

		//下注动画起点
		m_PtNoteAnimalStart[2].x =m_PtLogo[2].x + LOGO_WIDTH * 2 + 30;
		m_PtNoteAnimalStart[2].y =m_PtLogo[2].y + LOGO_HEIGHT;

		//m_PtNoteAnimalEnd[2].x = m_PtLogo[2].x +  LOGO_WIDTH * 2 + 30;
		//m_PtNoteAnimalEnd[2].y = m_PtLogo[2].y  -60;

		m_PtNoteAnimalEnd[2].x = iMidLine - 41;
		m_PtNoteAnimalEnd[2].y = iBaseLine+120-m_WinFen.GetHeight();//m_PtLogo[2].y - LOGO_HEIGHT;

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[2].x=iMidLine;
		m_PtSendCardAnimalStart[2].y=iBaseLine-100;

		m_PtSendCardAnimalEnd[2].x=ptCardPoint[2].x;
		m_PtSendCardAnimalEnd[2].y=ptCardPoint[2].y;

		m_PtSendCardAnimalEndSplit[2].x=ptCardPoint[2].x + y_Card*2;
		m_PtSendCardAnimalEndSplit[2].y=ptCardPoint[2].y;

		m_PtGetPoint[2].x = ptCardPoint[2].x - x_Card + 20;
		m_PtGetPoint[2].y = ptCardPoint[2].y + 15 + y_Card;

#ifdef VIDEO
		m_PtLogo[3].x=0;
		m_PtLogo[3].y=iBaseLine-m_heightVideo/2;

		//桌面上牌
		ptCardPoint[3].x =m_PtLogo[3].x+m_widthVideo+74;
		ptCardPoint[3].y =m_PtLogo[3].y+m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[3].x = m_PtLogo[3].x + m_widthVideo -32;
		m_PtTime[3].y = m_PtLogo[3].y - 25;

		//庄标志
		m_PtNt[3].x=m_PtLogo[3].x  ;
		m_PtNt[3].y=m_PtLogo[3].y - 65;


		m_PtShape[3].x = m_PtLogo[3].x + m_widthVideo -40;
		m_PtShape[3].y = m_PtLogo[3].y  - 65;
#else
		m_PtLogo[3].x=5;
		m_PtLogo[3].y=iBaseLine - LOGO_HEIGHT/2;//-cy/4+20;

#ifdef SAO_YANG
		m_PtLogo[3].x=0;
		m_PtLogo[3].y=iBaseLine - LOGO_HEIGHT/2;;
#endif

		ptCardPoint[3].x=m_PtLogo[3].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[3].y=m_PtLogo[3].y+10;

		m_PtTime[3].x=m_PtLogo[3].x+LOGO_WIDTH-15;		//计时器在头像左-20
		m_PtTime[3].y=m_PtLogo[3].y-30;

		//庄标志
		m_PtNt[3].x=m_PtLogo[3].x + 90;
		m_PtNt[3].y=m_PtLogo[3].y + 15;


		m_PtShape[3].x = m_PtLogo[3].x + 150;
		m_PtShape[3].y = m_PtLogo[3].y + 50;
#endif

		m_PtNote[3].x=ptCardPoint[3].x+LOGO_WIDTH+x_Card + 20;
		m_PtNote[3].y=iBaseLine-cy/4+y_Card/2;


		m_PtNoteTotal[3].x=ptCardPoint[3].x+LOGO_WIDTH+x_Card;
		m_PtNoteTotal[3].y=iBaseLine-cy/4+y_Card/2;

		m_PtFace[3].x=iMidLine-750/2-LOGO_WIDTH;
		m_PtFace[3].y=iBaseLine-FACE_HEIGHT-cy/4+y_Card/2;

		m_PtName[3].x=m_PtLogo[3].x + 65;
		m_PtName[3].y=m_PtLogo[3].y+LOGO_HEIGHT - 11;

		m_PtNoteLimit[3].x=LOGO_WIDTH+x_Card;
		m_PtNoteLimit[3].y=iBaseLine-cy/4+y_Card/2;

		m_PtAgree[3].x=m_PtLogo[3].x+LOGO_WIDTH+20;
		m_PtAgree[3].y=m_PtLogo[3].y+5;


		m_PtScore[3].x=m_PtFace[3].x+ptCardPoint[3].x;
		m_PtScore[3].y=m_PtFace[3].y+FACE_HEIGHT+50-cy/4+y_Card/2;

		m_PtPass[3].x=ptCardPoint[3].x-x_Card/2;
		m_PtPass[3].y=ptCardPoint[3].y-y_Card/4;

		m_PtNoteAnimalStart[3].x=LOGO_WIDTH;
		m_PtNoteAnimalStart[3].y=iBaseLine+15;//-cy/4+y_Card/2+30;

		m_PtNoteAnimalEnd[3].x=iMidLine-FACE_WIDTH-12;
		m_PtNoteAnimalEnd[3].y=iBaseLine-33/2;//-cy/4+y_Card/2+30;

#ifdef SAO_YANG
		m_PtNoteAnimalEnd[3].x=iMidLine-FACE_WIDTH-23;
		m_PtNoteAnimalEnd[3].y=iBaseLine-33/2;;
#endif

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[3].x=iMidLine;
		m_PtSendCardAnimalStart[3].y=iBaseLine-100;//-cy/4+y_Card/2;

		m_PtSendCardAnimalEnd[3].x=ptCardPoint[3].x;
		m_PtSendCardAnimalEnd[3].y=ptCardPoint[3].y - y_Card/2 - 10;;//-cy/4+y_Card/2;

		m_PtSendCardAnimalEndSplit[3].x=ptCardPoint[3].x;
		m_PtSendCardAnimalEndSplit[3].y=ptCardPoint[3].y + y_Card/2 ;

		m_PtGetPoint[3].x = ptCardPoint[3].x - x_Card + 20;
		m_PtGetPoint[3].y = ptCardPoint[3].y - y_Card/2 - 25;// + y_Card;
#endif	//end if of TWO_NN

#ifdef TWO_NN	//二人场，重构1号位置的坐标 zxj 2009-11-21
#ifdef VIDEO
		m_PtLogo[1].x =cx/2-LOGO_WIDTH*2;		//x坐标-头像宽-修正x
		m_PtLogo[1].y=cy-LOGO_HEIGHT-y_Card/3 - 20;

		//桌面上牌
		ptCardPoint[1].x =m_PtLogo[1].x+m_widthVideo+74;
		ptCardPoint[1].y =m_PtLogo[1].y +m_heightVideo-y_Card-11;
		//计时器
		m_PtTime[1].x = m_PtLogo[1].x ;
		m_PtTime[1].y = m_PtLogo[1].y  - 25;

		//庄标志
		m_PtNt[1].x=m_PtLogo[1].x - 43;
		m_PtNt[1].y=m_PtLogo[1].y;

		m_PtShape[1].x = m_PtLogo[1].x-43;
		m_PtShape[1].y = m_PtLogo[1].y + m_heightVideo -62;
#else
		m_PtLogo[1].x=cx/2-LOGO_WIDTH*2 - 70;		//头像x修正
		m_PtLogo[1].y=cy-LOGO_HEIGHT-80;	

		ptCardPoint[1].x=m_PtLogo[1].x+LOGO_WIDTH+93;		//用户出的牌正中
		ptCardPoint[1].y=m_PtLogo[1].y + 10;

		m_PtTime[1].x=m_PtLogo[1].x + 350;		//
		m_PtTime[1].y=m_PtLogo[1].y + 30;

		//庄标志
		m_PtNt[1].x=m_PtLogo[1].x+90;
		m_PtNt[1].y=m_PtLogo[1].y+15;

		m_PtShape[1].x = m_PtLogo[1].x + 150;
		m_PtShape[1].y = m_PtLogo[1].y + 53;
#endif
		m_PtNote[1].x=cx/2-115;
		m_PtNote[1].y=cy-y_Card-LOGO_HEIGHT;

		m_PtNoteTotal[1].x=cx/2;
		m_PtNoteTotal[1].y=cy-y_Card-LOGO_HEIGHT;

		m_PtFace[1].x=iMidLine-FACE_WIDTH*3/2+15;
		m_PtFace[1].y=iBaseLine+610/2-FACE_HEIGHT*2;

		m_PtNoteLimit[1].x=iMidLine-LOGO_WIDTH/2+LOGO_WIDTH;							
		m_PtNoteLimit[1].y=cy-y_Card-LOGO_HEIGHT;

		m_PtName[1].x=m_PtLogo[1].x+65;
		m_PtName[1].y=m_PtLogo[1].y + LOGO_HEIGHT - 11;

		m_PtAgree[1].x=m_PtLogo[1].x+LOGO_WIDTH+20;
		m_PtAgree[1].y=m_PtLogo[1].y+5;

		m_PtScore[1].x=iMidLine-WIDTH_NEW_MAN/2;//m_PtFace[1].x;
		m_PtScore[1].y=cy;//+50;

		m_PtPass[1].x=ptCardPoint[1].x-x_Card/2;
		m_PtPass[1].y=ptCardPoint[1].y-y_Card/4;

		//下注动画起点
		m_PtNoteAnimalStart[1].x =m_PtLogo[1].x + LOGO_WIDTH * 2 + 30;
		m_PtNoteAnimalStart[1].y =m_PtLogo[1].y + LOGO_HEIGHT;

		//m_PtNoteAnimalEnd[1].x = m_PtLogo[1].x +  LOGO_WIDTH * 2 + 30;
		//m_PtNoteAnimalEnd[1].y = m_PtLogo[1].y  -60;

		m_PtNoteAnimalEnd[1].x = iMidLine - 41;
		m_PtNoteAnimalEnd[1].y = iBaseLine+120-m_WinFen.GetHeight();//m_PtLogo[1].y - LOGO_HEIGHT;

		//发牌动画起始坐标和终点坐标
		m_PtSendCardAnimalStart[1].x=iMidLine;
		m_PtSendCardAnimalStart[1].y=iBaseLine-100;

		m_PtSendCardAnimalEnd[1].x=ptCardPoint[1].x;
		m_PtSendCardAnimalEnd[1].y=ptCardPoint[1].y;

		m_PtSendCardAnimalEndSplit[1].x=ptCardPoint[1].x + y_Card*2;
		m_PtSendCardAnimalEndSplit[1].y=ptCardPoint[1].y;

		m_PtGetPoint[1].x = ptCardPoint[1].x - x_Card + 20;
		m_PtGetPoint[1].y = ptCardPoint[1].y + 15 + y_Card;
#endif	//重构1号位置坐标结束 zxj 2009-11-21

		m_PtGif[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("flower0x"),0);
		m_PtGif[0].y = m_PtLogo[0].y+f.GetKeyVal(key,TEXT("flower0y"),0);
		m_PtGif[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("flower1x"),0);
		m_PtGif[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("flower1y"),0);

#ifndef TWO_NN
		m_PtGif[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("flower2x"),0);
		m_PtGif[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("flower2y"),0);
		m_PtGif[3].x = m_PtLogo[3].x+f.GetKeyVal(key,TEXT("flower3x"),0);
		m_PtGif[3].y = m_PtLogo[3].y+f.GetKeyVal(key,TEXT("flower3y"),0);
#endif

		m_BtnRect0.left = iMidLine - (4*82+3*10)/2;
		m_BtnRect0.top = cy - 250;
		m_BtnRect0.right = m_BtnRect0.left + help.GetWidth();
		m_BtnRect0.bottom = m_BtnRect0.top + help.GetHeight();

		m_BtnRect1.left = m_BtnRect0.right + 10;
		m_BtnRect1.top = m_BtnRect0.top;
		m_BtnRect1.right = m_BtnRect1.left + help.GetWidth();
		m_BtnRect1.bottom = m_BtnRect1.top + help.GetHeight();

		m_BtnRect2.left = m_BtnRect1.right + 10;
		m_BtnRect2.top = m_BtnRect0.top;
		m_BtnRect2.right = m_BtnRect2.left + help.GetWidth();
		m_BtnRect2.bottom = m_BtnRect2.top + help.GetHeight();

		m_BtnRect3.left = m_BtnRect2.right + 10;
		m_BtnRect3.top = m_BtnRect0.top;
		m_BtnRect3.right = m_BtnRect3.left + help.GetWidth();
		m_BtnRect3.bottom = m_BtnRect3.top + help.GetHeight();

		//用户下注上下限
		m_PtShowLimit.x=20;//iMidLine-567/2-100;
		m_PtShowLimit.y=0;
		//用户下注池
		m_PtNoteAll.x=iMidLine;
		m_PtNoteAll.y=iBaseLine;
		//用户下注动画起点
		m_PtBeginAnimalStart.x=iMidLine-460/2;
		m_PtBeginAnimalStart.y=iBaseLine/2;

		//用户下注动画终点
		m_PtBeginAnimalEnd.x=iMidLine-460/2;
		m_PtBeginAnimalEnd.y=iBaseLine;

		//设置奖池筹码数
		//	m_NoteAll[0].SetBasePoint(m_PtNoteAll);
		//移动扑克

#ifndef TWO_NN
		m_UserBull[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y - 5),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[1].SetBasePoint(CPoint(ptCardPoint[1].x - 80,ptCardPoint[1].y - 5),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[2].SetBasePoint(CPoint(ptCardPoint[2].x + 80,ptCardPoint[2].y - 10),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[3].SetBasePoint(CPoint(ptCardPoint[3].x + 80,ptCardPoint[3].y - 10),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
#else 
		m_UserBull[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y - 5),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[1].SetBasePoint(CPoint(ptCardPoint[1].x + 80,ptCardPoint[1].y - 5),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

#endif

#ifndef TWO_NN
		m_UserCard[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[1].SetBasePoint(CPoint(ptCardPoint[1].x - 80,ptCardPoint[1].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[2].SetBasePoint(CPoint(ptCardPoint[2].x + 80,ptCardPoint[2].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[3].SetBasePoint(CPoint(ptCardPoint[3].x + 80,ptCardPoint[3].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		// 牌型的位置跟随牌控件移动
		m_CardShape[0].SetPoint(ptCardPoint[0].x, ptCardPoint[0].y + 50);
		m_CardShape[1].SetPoint(ptCardPoint[1].x - 160, ptCardPoint[1].y + 50);
		m_CardShape[2].SetPoint(ptCardPoint[2].x, ptCardPoint[2].y + 50);
		m_CardShape[3].SetPoint(ptCardPoint[3].x, ptCardPoint[3].y + 50);
#else

		m_UserCard[0].SetBasePoint(CPoint(ptCardPoint[0].x + 80,ptCardPoint[0].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[1].SetBasePoint(CPoint(ptCardPoint[1].x + 80,ptCardPoint[1].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		// 牌型的位置跟随牌控件移动
		m_CardShape[0].SetPoint(ptCardPoint[0].x, ptCardPoint[0].y + 50);
		m_CardShape[1].SetPoint(ptCardPoint[1].x, ptCardPoint[1].y + 50);

#endif

#ifdef SAO_YANG
		m_UserBull[1].SetBasePoint(CPoint(ptCardPoint[1].x - 55,ptCardPoint[1].y - 5),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserBull[3].SetBasePoint(CPoint(ptCardPoint[3].x + 55,ptCardPoint[3].y - 10),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		m_UserCard[1].SetBasePoint(CPoint(ptCardPoint[1].x - 55,ptCardPoint[1].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		m_UserCard[3].SetBasePoint(CPoint(ptCardPoint[3].x + 55,ptCardPoint[3].y + 25),
			CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		// 牌型的位置跟随牌控件移动
		m_CardShape[1].SetPoint(ptCardPoint[1].x - 135, ptCardPoint[1].y + 50);
		m_CardShape[3].SetPoint(ptCardPoint[3].x-25, ptCardPoint[3].y + 50);
#endif

		for(int i=0;i<PLAY_COUNT;i++)
		{
			m_SendCardAnimal[i].SetBasePoint(CPoint(/*3*iMidLine/2,iBaseLine/2*/iMidLine,iBaseLine),CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		}

		//系统底牌
		//	m_SysBackCard.SetBasePoint(CPoint(3*iMidLine/2,iBaseLine/2),
		//		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		/*for(int i=0;i<PLAY_COUNT;i++)
		{
		m_SendCardAnimal[i].SetBasePoint(CPoint(3*iMidLine/2,iBaseLine/2),CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		}*/
		//筹码位置设定
		//	m_UserJeton[0].SetBasePoint(CPoint(m_PtJeton[0].x,m_PtJeton[0].y),
		//		CGameJeton::XShowMode::SWX_MODE_CENTER,CGameJeton::YShowMode::SWY_MODE_TOP);

		//	m_UserJeton[1].SetBasePoint(CPoint(m_PtJeton[1].x,m_PtJeton[1].y),
		//		CGameJeton::XShowMode::SWX_MODE_CENTER,CGameJeton::YShowMode::SWY_MODE_TOP);
		//	m_UserJeton[2].SetBasePoint(CPoint(m_PtJeton[2].x,m_PtJeton[2].y),
		//		CGameJeton::XShowMode::SWX_MODE_CENTER,CGameJeton::YShowMode::SWY_MODE_TOP);
		//	m_UserJeton[3].SetBasePoint(CPoint(m_PtJeton[3].x,m_PtJeton[3].y),
		//		CGameJeton::XShowMode::SWX_MODE_CENTER,CGameJeton::YShowMode::SWY_MODE_TOP);

		//m_MeCard.SetBasePoint(CPoint(cx/2,cy-170),
		//	CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
		//m_MeBackCard.SetBasePoint(CPoint(cx/2,cy-170),
		//	CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

		//移动反牌视图
		CRect ContronRect;
		m_NtList.GetClientRect(&ContronRect);
		m_NtList.MoveWindow(iMidLine-ContronRect.Width()/2+30,iBaseLine+100,ContronRect.Width(),ContronRect.Height(),FALSE);

		//	m_Result.GetClientRect(&ContronRect);
		//	m_Result.MoveWindow((cx -ContronRect.Width())/2,(cy- ContronRect.Height())/2-80,ContronRect.Width(),ContronRect.Height());


		//	//用户下注后筹码显示位置
		//	m_NoteTotal[0].SetLookMode(true);
		//	m_NoteTotal[0].SetBasePoint(m_PtNoteAnimalEnd[0]);
		//	m_NoteTotal[1].SetLookMode(false);
		//	m_NoteTotal[1].SetBasePoint(m_PtNoteAnimalEnd[1]);
		//
		//#ifndef TWO_NN
		//	m_NoteTotal[2].SetLookMode(true);
		//	m_NoteTotal[2].SetBasePoint(m_PtNoteAnimalEnd[2]);
		//	m_NoteTotal[3].SetLookMode(false);
		//	m_NoteTotal[3].SetBasePoint(m_PtNoteAnimalEnd[3]);
		//#endif
		//移动控件
		//移动信息视图
		m_GameNoteView.GetClientRect(&ContronRect);
		m_GameNoteView.MoveWindow(iMidLine-ContronRect.Width()/2,iBaseLine-ContronRect.Height()/2,
			ContronRect.Width(),ContronRect.Height(),FALSE);
		m_btContinue.GetClientRect(&ContronRect);
		//m_btContinue.MoveWindow(iMidLine - ContronRect.Width()/2,cy - 220,ContronRect.right,ContronRect.bottom);

		m_btContinue.MoveWindow(iMidLine+20,cy - 220 /*iBaseLine+140*/, ContronRect.Width(), ContronRect.Height());
		m_btLeave.MoveWindow(iMidLine-20-ContronRect.Width(), cy - 220/*iBaseLine+140*/, ContronRect.Width(), ContronRect.Height());

		m_Result.GetClientRect(&ContronRect);
		m_Result.MoveWindow((cx - ContronRect.Width())/2,(cy - ContronRect.Height())/2-30 ,ContronRect.right,ContronRect.bottom);

		m_btBull.GetClientRect(&ContronRect);
		//	m_btNote.MoveWindow(cx - 4*ContronRect.right+30, cy - 100, ContronRect.right,ContronRect.bottom);                        
		///m_btBull.MoveWindow(iMidLine-2*ContronRect.Width()+10, cy - 220, ContronRect.right,ContronRect.bottom);//yl alter 20120817/
        m_btBull.MoveWindow(iMidLine-ContronRect.Width()/2 , cy - 220, ContronRect.right,ContronRect.bottom);
		m_btOpen.GetClientRect(&ContronRect);
		m_btOpen.MoveWindow(iMidLine+ContronRect.Width()-10,  cy - 220,ContronRect.right,ContronRect.bottom);                     
		m_btReset.GetClientRect(&ContronRect);
		///m_btReset.MoveWindow(iMidLine-ContronRect.Width()/2 , cy - 220, ContronRect.right,ContronRect.bottom);//yl alter 20120817/
        m_btReset.MoveWindow(iMidLine-2*ContronRect.Width()+10, cy - 220, ContronRect.right,ContronRect.bottom); 

#ifdef SAO_YANG
		m_btChangeShin.GetClientRect(&ContronRect);	//换肤
		m_btChangeShin.MoveWindow(cx-ContronRect.Width()-10, cy-ContronRect.Height()-10, ContronRect.right,ContronRect.bottom); 
#endif
		//叫分
		m_btCallScore1.GetClientRect(&ContronRect);
		m_btCallScore1.MoveWindow(iMidLine-2*ContronRect.Width()+10, cy - 220,ContronRect.Width(),ContronRect.Height());
		m_btCallScorePass.MoveWindow(iMidLine+ContronRect.Width()-10,  cy - 220,ContronRect.Width(),ContronRect.Height());


#ifdef VIDEO
#ifndef TWO_NN 
		//视频的坐标出
		m_rectVideoFrame[2].top=m_PtLogo[2].y;// cy-m_heightVideo;
		m_rectVideoFrame[2].left=m_PtLogo[2].x;//10;
		m_rectVideoFrame[2].bottom=m_rectVideoFrame[2].top+m_heightVideo;
		m_rectVideoFrame[2].right=m_rectVideoFrame[2].left+m_widthVideo;
		m_rectVideoFrame[3].top=m_PtLogo[3].y;//249;
		m_rectVideoFrame[3].left=m_PtLogo[3].x;//10;
		m_rectVideoFrame[3].bottom=m_rectVideoFrame[3].top+m_heightVideo;
		m_rectVideoFrame[3].right=m_rectVideoFrame[3].left+m_widthVideo;
#endif	 
		m_rectVideoFrame[0].top=m_PtLogo[0].y;//0;
		m_rectVideoFrame[0].left=m_PtLogo[0].x;//220;
		m_rectVideoFrame[0].bottom=m_rectVideoFrame[0].top+m_heightVideo;
		m_rectVideoFrame[0].right=m_rectVideoFrame[0].left+m_widthVideo;
		m_rectVideoFrame[1].top=m_PtLogo[1].y;//242;
		m_rectVideoFrame[1].left=m_PtLogo[1].x;//cx-m_widthVideo+5;
		m_rectVideoFrame[1].bottom=m_rectVideoFrame[1].top+m_heightVideo;
		m_rectVideoFrame[1].right=m_rectVideoFrame[1].left+m_widthVideo; 

		///设置视频窗口位置 
		if(NULL!=CPlayVideo::CreatePlayVideo())
			CPlayVideo::CreatePlayVideo()->SetUserPos();  
#endif

		//改变积分榜,x坐标
		CRect rect;
		m_showcoredlg.GetClientRect(&rect);
		m_showcoredlg.SetWindowPos(NULL,cx-rect.Width()-m_imgScoreRule.GetWidth(),-m_showcoredlg.m_showh,0,0,SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOSIZE);

		m_PtOpenCard[0].SetPoint(ptCardPoint[0].x-40, ptCardPoint[0].y+110);
		m_PtOpenCard[1].SetPoint(ptCardPoint[1].x-30, ptCardPoint[1].y-27);
		m_PtOpenCard[2].SetPoint(ptCardPoint[2].x-30, ptCardPoint[2].y-27);
		m_PtOpenCard[3].SetPoint(ptCardPoint[3].x-30, ptCardPoint[3].y-27);
	}
	return;
}

//开始按钮
void CClientPlayView::OnHitBegin()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_BEGIN,0,0);
	return;
}
//离开按钮
void CClientPlayView::OnHitLeave()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(WM_CLOSE,0,0);
	return;
}


//托管
void CClientPlayView::OnHitAuto()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_SOUND,0,0);
	return;
}

//继续按钮
void CClientPlayView::OnHitContinue()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_BEGIN,0,0);

// 	for(int i = 0; i < PLAY_COUNT; i++)
// 	{
// 		if(m_pUserInfo[i] == NULL)//m_bWatchMode
// 		{
// 			m_CardShape[i].ShowWindow(SW_HIDE);
// 		}
// 	}

	return;
}


//有事要走
void CClientPlayView::OnHitThing()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_HAVE_THING,0,0);
	return;
}


//提前停止
void CClientPlayView::OnHitStop()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_STOP,0,0);
	return;
}
//下
void CClientPlayView::OnNote()
{
	CClientGameDlg *p = CONTAINING_RECORD(this, CClientGameDlg, m_PlayView);
	p->SendMessage(IDM_SHOW_NOTE, 0, 0);
	return;
}
//弃
void CClientPlayView::OnOver()
{
	CClientGameDlg *p = CONTAINING_RECORD(this, CClientGameDlg, m_PlayView);
	p->SendMessage(IDM_SELECT_NOTE_NUM, TYPE_GIVE_UP, 0);

	return;
}
//重排
void CClientPlayView::OnReset()
{
	CClientGameDlg *p = CONTAINING_RECORD(this, CClientGameDlg, m_PlayView);
	p->SendMessage(IDM_ACTIVE_RESULT, TYPE_RESET, 0);
}
//开牌
void CClientPlayView::OnOpen()
{
	CClientGameDlg *p = CONTAINING_RECORD(this, CClientGameDlg, m_PlayView);
	p->SendMessage(IDM_ACTIVE_RESULT, TYPE_OPEN, 0);
}

//加倍
void CClientPlayView::OnBull()
{
	CClientGameDlg *p = CONTAINING_RECORD(this, CClientGameDlg, m_PlayView);
	p->SendMessage(IDM_ACTIVE_RESULT, TYPE_BULL, 0);
}
void CClientPlayView::OnHitCallScore(UINT uID)		
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_CALL_SCORE,uID - IDC_CALL_SCORE_PASS,uID -IDC_CALL_SCORE_PASS);
	return;
}

//换肤
void CClientPlayView::OnChangeShin()
{
	m_iCurrentBG++;
	if(m_iCurrentBG >= 4)
	{
		m_iCurrentBG = 0;
	}
 
	//检查图片文件是否存在
	if(m_pImgBackground[m_iCurrentBG]->GetWidth() > 0)
	{
		UpdateViewFace(NULL);
	}
	else if(m_iCurrentBG != 0)	//图片不存在用默认图片
	{
		m_iCurrentBG = 0;
	}
}

//重置界面函数
void CClientPlayView::ResetGameView()
{
	CUsingSkinClass::ResetGameView();

	return;
}

//设置庄家的位置
void CClientPlayView::SetNTStation(int iViewStation)
{
	CString str;
	str.Format("jiaofen3: 【5】iViewStation = %d", iViewStation);
	OutputDebugString(str);

	m_iNtStation=iViewStation;
	UpdateViewFace(NULL);
	return;
}

//设置报主位置
void CClientPlayView::SetShowNtStation(int iViewStation, int iHuaKind)
{
	return;
}
//拖管设置
void CClientPlayView::SetAuto(int bDeskStation,bool bAuto)
{
	m_bAuto[bDeskStation]=bAuto;
	CRect rect;
	rect.SetRect(m_PtAuto[bDeskStation].x,m_PtAuto[bDeskStation].y,m_PtAuto[bDeskStation].x+33,m_PtAuto[bDeskStation].y+33);
	UpdateViewFace(rect);	
}
void CClientPlayView::DrawAutoLogo(CDC * pDC, int x, int y)
{
/*	CGameImageHelper	AutoLogo(&m_bAutoLogo);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(AutoLogo);
	::TransparentBlt(pDC->GetSafeHdc(),x,y,AutoLogo.GetWidth(),AutoLogo.GetHeight(),dc.GetSafeHdc(),0,0,AutoLogo.GetWidth(),AutoLogo.GetHeight(),dc.GetPixel(0,0));
*/	return ;
}
//绘制下注分显示
void CClientPlayView::DrawScore(CDC * pDC, int x, int y)
{
	CGameImageHelper	Score(&m_PicScore);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(Score);
	::TransparentBlt(pDC->GetSafeHdc(),x,y,Score.GetWidth(),Score.GetHeight(),dc.GetSafeHdc(),0,0,Score.GetWidth(),Score.GetHeight(),dc.GetPixel(0,0));
	dc.DeleteDC();
	return ;
}
/*//绘制下注界面
void CClientPlayView::DrawNoteBtn(CDC * pDC, int x, int y)
{
CGameImageHelper	btn(&m_PicBtn);
CDC dc;
dc.CreateCompatibleDC(pDC);
dc.SelectObject(btn);
::TransparentBlt(pDC->GetSafeHdc(),x,y,btn.GetWidth(),btn.GetHeight(),dc.GetSafeHdc(),0,0,btn.GetWidth(),btn.GetHeight(),dc.GetPixel(0,0));
return ;
}*/
//设置游戏分数
void CClientPlayView::SetGamePoint(int iGamePoint, int bMeSide)
{
	if ((iGamePoint==0)&&(bMeSide==-1))
	{
		bMeSide=-1;
		m_iGamePoint=0;
	}
	else if (iGamePoint==0) m_bMeSide=bMeSide;
	else m_iGamePoint+=iGamePoint;

	UpdateViewFace(NULL);

	return;
}

//设置背景色
void CClientPlayView::SetBackBmp(UINT uResourceID, TCHAR * szFileName, BOOL bResource)
{
	if(bResource)
	{
		CBitmap Temp;
		if(!Temp.LoadBitmap(uResourceID)) return;
		return;
	}
	else
	{
		if (szFileName==NULL) return;
	}
	return;
}
//void CClientPlayView::DrawNote(CDC *pDC)
//{
//	CFont Font;
//	CRect rect;
//	TCHAR szMsg[100];
//	Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
//	pDC->SelectObject(Font);
//	pDC->SetTextColor(RGB(255,255,0));
//	pDC->SetBkMode(TRANSPARENT);
//	//顶部贴图
//	//CGameImageHelper LogoLeftLogo(&m_PicLeftLogo);
//	//LogoLeftLogo.BitBlt(pDC->GetSafeHdc(),m_PtShowLimit.x,m_PtShowLimit.y);
//	////最大限注
//	//if(m_iNoteLimit!=0)
//	//{	
//	//	bool bThousand=(m_iNoteLimit>=100000);
//	//	UINT BasePoint=m_iBaseNote;//m_iNoteLimit/100;
//	//	DrawSmallNum(pDC,m_PtShowLimit.x+20,m_PtShowLimit.y+10,BasePoint,15,0,1,bThousand);
//	//	if(m_iNoteLimit>=10000)
//	//		bThousand=true;
//	//	DrawSmallNum(pDC,m_PtShowLimit.x+40,m_PtShowLimit.y+42,m_iNoteLimit,15,0,1,bThousand);
//	//}
//
//	////本局下注数
//	//for(int i=0;i<PLAY_COUNT;i++)
//	//{
//	//	//用户本轮下注数
//	//	//			DrawScore(pDC,m_PtScore[i].x,m_PtScore[i].y-24);
//	//	if(i!=2)
//	//		continue;
//	//	if(m_iNotePoint[i]!=0)
//	//	{
//	//		//用户当前下注数 
//	//		DrawScore(pDC,m_PtScore[i].x,m_PtScore[i].y-50);
//	//		bool bThousand=(m_iNotePoint[i]>=10000);
//	//		DrawSmallNum(pDC,m_PtScore[i].x+13 ,m_PtScore[i].y-44,m_iNotePoint[i],15,false,1,bThousand);
//	//	}
//	//}
//	if(m_iNoteTotalPoint!=0)
//	{
//		Font.CreateFont(18,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
//		pDC->SelectObject(Font);
//		pDC->SetTextColor(RGB(255,255,0));
//		pDC->SetBkMode(TRANSPARENT);
//		rect.left = m_PtNoteTotal[0].x;
//		rect.right = rect.left + 100;
//		rect.top = m_PtNoteTotal[0].y;
//		rect.bottom = rect.top + 24;
//		CGameImageHelper	help(&m_NoteKuan);
//		CDC dc;
//		dc.CreateCompatibleDC(pDC);
//		dc.SelectObject(help);
//		::TransparentBlt(pDC->GetSafeHdc(),m_PtNoteTotal[0].x,m_PtNoteTotal[0].y-2,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_NoteKuan.GetWidth(),m_NoteKuan.GetHeight(),dc.GetPixel(0,0));
//		wsprintf(szMsg,"%d",m_iNoteTotalPoint);
//		pDC->DrawText(szMsg,lstrlen(szMsg),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
//		dc.DeleteDC();
//	}
//	ShowAllNote();
//	
//	return ;
//}
//初始化清屏
void CClientPlayView::SetNotePoint(BYTE iViewStation,__int64 iNotePoint)
{
	m_iNotePoint[iViewStation]=iNotePoint;
	CRect rect;
	rect.SetRect(m_PtNote[iViewStation].x,m_PtNote[iViewStation].y,m_PtNote[iViewStation].x+35,m_PtNote[iViewStation].y+20);
	UpdateViewFace(rect);	
	UpdateViewFace(NULL);
	return ;
}
////初始化清屏
//void CClientPlayView::SetThisTurnNotePoint(BYTE iViewStation,int iThisTurnPoint)
//{
//	m_iThisTurnNote[iViewStation]=iThisTurnPoint;
//	CRect rect;
//	rect.SetRect(m_PtNote[iViewStation].x,m_PtNote[iViewStation].y+20,m_PtNote[iViewStation].x+35,m_PtNote[iViewStation].y+20+20);
//	//UpdateViewFace(rect);	
//	UpdateViewFace(NULL);
//	return ;
//}
////增加
//void CClientPlayView::AddThisTurnNotePoint(BYTE iViewStation,int iThisTurnPoint)
//{
//	
//	m_iThisTurnNote[iViewStation]+=iThisTurnPoint;
//	CRect rect;
//	rect.SetRect(m_PtNote[iViewStation].x,m_PtNote[iViewStation].y+20,m_PtNote[iViewStation].x+35,m_PtNote[iViewStation].y+20+20);
//	UpdateViewFace(rect);	
//	UpdateViewFace(NULL);
//	return ;
//}

//初始化总注
//void CClientPlayView::SetTotalNote(BYTE iViewStation,int iNoteTotal)
//{
//	m_iNoteTotalPoint=iNoteTotal;
//	CRect rect;
//	rect.SetRect(m_PtNoteTotal[iViewStation].x,m_PtNoteTotal[iViewStation].y,m_PtNoteTotal[iViewStation].x+35,m_PtNoteTotal[iViewStation].y+20);
////	UpdateViewFace(rect);
//	UpdateViewFace(NULL);
//	return ;
//}
//
void CClientPlayView::SetMingLImit(int limit,int an)
{
	m_iMingLImit=limit;
	m_iAnLImit=an;
	UpdateViewFace(NULL);
	return ;
}
//初始化下注上限
void CClientPlayView::SetLimitNote(BYTE iViewStation,__int64 iNoteLimit,__int64 iBaseNote)
{
	m_iBaseNote=iBaseNote;
	m_iNoteLimit=iNoteLimit;
	CRect rect;
	rect.SetRect(m_PtNoteLimit[iViewStation].x,m_PtNoteLimit[iViewStation].y,m_PtNoteLimit[iViewStation].x+35,m_PtNoteLimit[iViewStation].y+20);
	UpdateViewFace(rect);
	UpdateViewFace(NULL);
	return ;
}
//追加押注
void CClientPlayView::AddNotePoint(BYTE iViewStation,__int64 iNotePoint)
{
	m_iNotePoint[iViewStation]+=iNotePoint;
	CRect rect;
	rect.SetRect(m_PtNote[iViewStation].x,m_PtNote[iViewStation].y,m_PtNote[iViewStation].x+35,m_PtNote[iViewStation].y+20);
	UpdateViewFace(rect);	
	UpdateViewFace(NULL);
	return ;
}
//加注
//void CClientPlayView::AddTotalNote(BYTE iViewStation,int iNoteTotal)
//{
//	m_iNoteTotalPoint+=iNoteTotal;
//	CRect rect;
//	rect.SetRect(m_PtNoteTotal[iViewStation].x,m_PtNoteTotal[iViewStation].y,m_PtNoteTotal[iViewStation].x+35,m_PtNoteTotal[iViewStation].y+20);
//	UpdateViewFace(rect);
//	UpdateViewFace(NULL);
//	return ;
//}
void CClientPlayView::DrawInfo(CDC *pDC)
{
	/*	if (!m_StationView.m_bShowMessage) 
	return;

	CFont Font;
	CPaintDC dc(this);
	Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	//	dc.SelectObject(Font);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkMode(TRANSPARENT);

	//绘画信息
	TCHAR szBuffer[50];
	TCHAR * szUpGrade[]={TEXT("本方 -- 对家"),TEXT("敌方 -- 右家"),TEXT("本方 -- 自己"),TEXT("敌方 -- 左家")};
	TCHAR * szHua[]={TEXT("方块"),TEXT("梅花"),TEXT("红桃"),TEXT("黑桃")};
	TCHAR * szCard[13]={TEXT("2"),TEXT("3"),TEXT("4"),TEXT("5"),TEXT("6"),TEXT("7"),
	TEXT("8"),TEXT("9"),TEXT("10"),TEXT("J"),TEXT("Q"),TEXT("K"),
	TEXT("A")};*/
	/*
	pDC->TextOut(10+VIEW_FRAME_LEFT,5+VIEW_FRAME_TOP,TEXT("本方："));	
	pDC->TextOut(10+VIEW_FRAME_LEFT,20+VIEW_FRAME_TOP,TEXT("敌方："));
	pDC->TextOut(10+VIEW_FRAME_LEFT,35+VIEW_FRAME_TOP,TEXT("已打局数："));
	//	pDC->TextOut(10+VIEW_FRAME_LEFT,50+VIEW_FRAME_TOP,TEXT("分数："));
	//	pDC->TextOut(10+VIEW_FRAME_LEFT,65+VIEW_FRAME_TOP,TEXT("罚分："));
	pDC->TextOut(10+VIEW_FRAME_LEFT,50+VIEW_FRAME_TOP,TEXT("主牌："));
	*/
	/*
	pDC->TextOut(10+VIEW_FRAME_LEFT,750,TEXT("本方："));	
	pDC->TextOut(10+VIEW_FRAME_LEFT,20+VIEW_FRAME_TOP,TEXT("敌方："));
	pDC->TextOut(10+VIEW_FRAME_LEFT,35+VIEW_FRAME_TOP,TEXT("已打局数："));
	//	pDC->TextOut(10+VIEW_FRAME_LEFT,50+VIEW_FRAME_TOP,TEXT("分数："));
	//	pDC->TextOut(10+VIEW_FRAME_LEFT,65+VIEW_FRAME_TOP,TEXT("罚分："));
	pDC->TextOut(10+VIEW_FRAME_LEFT,50+VIEW_FRAME_TOP,TEXT("主牌："));
	if (m_StationView.m_iMeStation!=-1)
	{
	sprintf(szBuffer,TEXT("%s打到%s，现在打%s"),szCard[m_StationView.m_iBeginStation-2],szCard[m_StationView.m_iEndStation-2],szCard[m_StationView.m_iMeStation-2]);
	pDC->TextOut(50+VIEW_FRAME_LEFT,5+VIEW_FRAME_TOP,szBuffer,lstrlen(szBuffer));
	}
	if (m_StationView.m_iOtherStation!=-1)
	{
	sprintf(szBuffer,TEXT("%s打到%s，现在打%s"),szCard[m_StationView.m_iBeginStation-2],szCard[m_StationView.m_iEndStation-2],szCard[m_StationView.m_iOtherStation-2]);
	pDC->TextOut(50+VIEW_FRAME_LEFT,20+VIEW_FRAME_TOP,szBuffer,lstrlen(szBuffer));
	}

	if (m_StationView.m_iLessPlay!=-1)
	{
	//		sprintf(szBuffer,TEXT("%d （最少回合＝%d）"),m_StationView.m_iPlayCount,m_StationView.m_iLessPlay);
	sprintf(szBuffer,TEXT("%d"),m_StationView.m_iPlayCount);
	pDC->TextOut(80+VIEW_FRAME_LEFT,35+VIEW_FRAME_TOP,szBuffer,lstrlen(szBuffer));
	}

	//	sprintf(szBuffer,TEXT("%d"),m_StationView.m_iTurePoint);
	//	pDC->TextOut(50+VIEW_FRAME_LEFT,50+VIEW_FRAME_TOP,szBuffer,lstrlen(szBuffer));

	//if (m_StationView.m_iPunishPoint!=0)
	//{
	//	sprintf(szBuffer,TEXT("%d"),m_StationView.m_iPunishPoint);
	//	pDC->TextOut(50+VIEW_FRAME_LEFT,65+VIEW_FRAME_TOP,szBuffer,lstrlen(szBuffer));
	//}
	//else 
	//	pDC->TextOut(50+VIEW_FRAME_LEFT,65+VIEW_FRAME_TOP,TEXT("无"),2);

	if (m_StationView.m_iNTStation!=-1)
	{
	DrawNtLogo(pDC,50+VIEW_FRAME_LEFT,50+VIEW_FRAME_TOP,m_iHuaKind);
	sprintf(szBuffer,TEXT("%s %s"),szHua[m_StationView.m_iNTHua>>4],(m_StationView.m_iUpGrade==0 || m_StationView.m_iUpGrade==2)?szCard[m_StationView.m_iMeStation-2]:szCard[m_StationView.m_iOtherStation-2]);
	pDC->TextOut(50+VIEW_FRAME_LEFT+17,50+VIEW_FRAME_TOP,szBuffer,lstrlen(szBuffer));
	}
	*/
	return;
}
void CClientPlayView::DrawNum(CDC * pDC, int iXPos, int iYPos, UINT Num,int offset,BOOL bThousand)
{
	//	if ((Num!=0L)&&(Num<10000L))
	{
		UINT uFirst=Num/100000L,uSecond=(Num/10000)%10,uThree=(Num/1000)%10,uFour=(Num/100)%10,uFive=(Num/10)%10,uSix=Num%10;
		CGameImageHelper ImageHandle(&m_PicNum);
		CDC destdc;
		destdc.CreateCompatibleDC(pDC);
		destdc.SelectObject(ImageHandle);
		if(uFirst)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,NUM_HEIGHT/2,NUM_HEIGHT,destdc.GetSafeHdc(),uFirst*NUM_WIDTH/2,0,NUM_WIDTH/2,NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+offset,iYPos,NUM_HEIGHT/2,NUM_HEIGHT,destdc.GetSafeHdc(),uSecond*NUM_WIDTH/2,0,NUM_WIDTH/2,NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond||uThree)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+2*offset,iYPos,NUM_HEIGHT/2,NUM_HEIGHT,destdc.GetSafeHdc(),uThree*NUM_WIDTH/2,0,NUM_WIDTH/2,NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond||uThree||uFour)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+3*offset,iYPos,NUM_HEIGHT/2,NUM_HEIGHT,destdc.GetSafeHdc(),uFour*NUM_WIDTH/2,0,NUM_WIDTH/2,NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond||uThree||uFour||uFive)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+4*offset,iYPos,NUM_HEIGHT/2,NUM_HEIGHT,destdc.GetSafeHdc(),uFive*NUM_WIDTH/2,0,NUM_WIDTH/2,NUM_HEIGHT,RGB(0,0,0));
		::TransparentBlt(pDC->GetSafeHdc(),iXPos+5*offset,iYPos,NUM_HEIGHT/2,NUM_HEIGHT,destdc.GetSafeHdc(),uSix*NUM_WIDTH/2,0,NUM_WIDTH/2,NUM_HEIGHT,RGB(0,0,0));
		destdc.DeleteDC();
	}
	return;
}
void CClientPlayView::DrawSmallNum(CDC * pDC, int iXPos, int iYPos, int Num,int offset,BOOL bIsFourOrSix,BOOL bIsPlus,BOOL bThousand)
{
	CGameImageHelper ImageHandle(&m_PicSmallNum);
	CDC destdc;
	destdc.CreateCompatibleDC(pDC);
	destdc.SelectObject(ImageHandle);
	if(!bIsPlus)
	{
		::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),10*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		Num=abs(Num);
	}
	if(bThousand)
		Num/=1000;
	if (bIsFourOrSix)
	{
		UINT uFirst=Num/100000L,uSecond=(Num/10000)%10,uThree=(Num/1000)%10,uFour=Num/100%10,uFive=Num/10%10,uSix=Num%10;
		if(uFirst)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uFirst*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+2*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uSecond*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond||uThree)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+3*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uThree*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond||uThree||uFour)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+4*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uFour*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond||uThree||uFour||uFive)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+5*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uFive*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		::TransparentBlt(pDC->GetSafeHdc(),iXPos+6*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uSix*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(bThousand)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+7*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),11*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		//顯示港幣	
		::TransparentBlt(pDC->GetSafeHdc(),iXPos+8*offset,iYPos,25,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),13*8,0,25,SMALL_NUM_HEIGHT,RGB(0,0,0));
	}
	else
	{
		UINT uFirst=Num/1000L,uSecond=(Num/100)%10,uThree=(Num/10)%10,uFour=Num%10;
		if(uFirst)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uFirst*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+2*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uSecond*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(uFirst||uSecond||uThree)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+3*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uThree*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		::TransparentBlt(pDC->GetSafeHdc(),iXPos+4*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),uFour*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
		if(bThousand)
			::TransparentBlt(pDC->GetSafeHdc(),iXPos+5*offset,iYPos,SMALL_NUM_HEIGHT/2,SMALL_NUM_HEIGHT,destdc.GetSafeHdc(),11*SMALL_NUM_WIDTH/2,0,SMALL_NUM_WIDTH/2,SMALL_NUM_HEIGHT,RGB(0,0,0));
	}
	destdc.DeleteDC();
	return;
}

void CClientPlayView::DrawPass(CDC *pDC)
{
	CGameImageHelper	help(&m_Pass);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(help);
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(m_iPass[i] !=0)
			::TransparentBlt(pDC->GetSafeHdc(),m_PtPass[i].x,m_PtPass[i].y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_Pass.GetWidth(),m_Pass.GetHeight(),dc.GetPixel(0,0));
	}
	dc.DeleteDC();
	return ;
}
void CClientPlayView::DrawMing(CDC *pDC)
{
	CGameImageHelper	help(&m_Ming);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(help);
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(m_bMing[i])
			::TransparentBlt(pDC->GetSafeHdc(),m_PtNt[i].x,m_PtNt[i].y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_Ming.GetWidth(),m_Ming.GetHeight(),dc.GetPixel(0,0));
	}
	dc.DeleteDC();
	return ;
}
void  CClientPlayView::DrawWait(CDC *pDC,int iWidth,int iHeight)
{
	CGameImageHelper	help(&m_Waiting);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(help);
	if(m_bWait)
		::TransparentBlt(pDC->GetSafeHdc(),(iWidth - m_Waiting.GetWidth())/2,(iHeight - m_Waiting.GetHeight())/2,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_Waiting.GetWidth(),m_Waiting.GetHeight(),dc.GetPixel(0,0));
	dc.DeleteDC();
	return ;
}
//画庄家
void  CClientPlayView::DrawNt(CDC *pDC)
{
#ifdef SAO_YANG

	if(m_iNtStation!=-1)
	{
		Image* pImageNt = Image::FromFile(L".\\image\\nt.png");

		Graphics GDIDC(pDC->m_hDC);
		GDIDC.DrawImage(pImageNt,Rect(m_PtNt[m_iNtStation].x,m_PtNt[m_iNtStation].y,pImageNt->GetWidth(),pImageNt->GetHeight()));	
	}
#else
	CGameImageHelper	help(&m_Nt);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(help);
	if(m_iNtStation != -1)
		::TransparentBlt(pDC->GetSafeHdc(),m_PtNt[m_iNtStation].x,m_PtNt[m_iNtStation].y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_Nt.GetWidth(),m_Nt.GetHeight(),dc.GetPixel(0,0));
	dc.DeleteDC();
#endif
	return;
}
void CClientPlayView::SetDrawNote(bool draw)
{
	m_bDraw = draw;
	UpdateViewFace(NULL);
}
//下注按钮
void CClientPlayView::DrawNoteBt(CDC *pDC)
{
	if (m_bDraw)
	{
		CGameImageHelper	help(&m_WinFen);
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		dc.SelectObject(help);
		::TransparentBlt(pDC->GetSafeHdc(),m_BtnRect0.left,m_BtnRect0.top,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_WinFen.GetWidth(),m_WinFen.GetHeight(),dc.GetPixel(0,0));
		::TransparentBlt(pDC->GetSafeHdc(),m_BtnRect1.left,m_BtnRect1.top,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_WinFen.GetWidth(),m_WinFen.GetHeight(),dc.GetPixel(0,0));
		::TransparentBlt(pDC->GetSafeHdc(),m_BtnRect2.left,m_BtnRect2.top,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_WinFen.GetWidth(),m_WinFen.GetHeight(),dc.GetPixel(0,0));
		::TransparentBlt(pDC->GetSafeHdc(),m_BtnRect3.left,m_BtnRect3.top,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_WinFen.GetWidth(),m_WinFen.GetHeight(),dc.GetPixel(0,0));
		CFont Font, *OldFont;
		CHAR szMsg[50];
		int TempLen = 14;

		if (m_iNoteLimit > 99999999999)
			TempLen = 12;
		Font.CreateFont(TempLen,0,0,0,700,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
		OldFont=pDC->SelectObject(&Font);
		pDC->SetTextColor(RGB(0,19,43));
		pDC->SetBkMode(TRANSPARENT);
		CString strMoney;
		if (m_GameType == 1)              //游戏种类。0为普通。1为同喜乐
		{
			GetNumString(m_iNoteLimit/100*100,strMoney,m_nPowerOfGold);
			pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect0,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			GetNumString(m_iNoteLimit/125*100,strMoney,m_nPowerOfGold);
			pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect1,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			GetNumString(m_iNoteLimit/250*100,strMoney,m_nPowerOfGold);
			pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect2,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			GetNumString(m_iNoteLimit/500*100,strMoney,m_nPowerOfGold);
			pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect3,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		}
		else
		{
			if (m_iGameNoteSetType>0)
			{
				GetNumString(m_iNoteLimit,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect0,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				GetNumString(m_iNoteLimit/2,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect1,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				GetNumString(m_iNoteLimit/4,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect2,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				GetNumString(m_iNoteLimit/8,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect3,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			}
			else
			{
				GetNumString(m_iNoteLimit,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect0,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				GetNumString(m_iNoteLimit/1.25,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect1,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				GetNumString(m_iNoteLimit/2.5,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect2,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				GetNumString(m_iNoteLimit/5,strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&m_BtnRect3,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			}
			
		}
		//wsprintf(szMsg,"%d",m_iNoteLimit);
		//pDC->DrawText(szMsg,lstrlen(szMsg),&m_BtnRect0,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		/*
		wsprintf(szMsg,"%d",m_iNoteLimit/2);
		pDC->DrawText(szMsg,lstrlen(szMsg),&m_BtnRect1,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		wsprintf(szMsg,"%d",m_iNoteLimit/4);
		pDC->DrawText(szMsg,lstrlen(szMsg),&m_BtnRect2,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		wsprintf(szMsg,"%d",m_iNoteLimit/6);
		pDC->DrawText(szMsg,lstrlen(szMsg),&m_BtnRect3,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);*/
		dc.DeleteDC();
		pDC->SelectObject(OldFont);
	}
}

//画摊牌标识
void CClientPlayView::DrawOpenCard(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CGameImageHelper ImgOpenCard(&m_imgOpenCard);
	dc.SelectObject(ImgOpenCard);
	LONG lTmp=0;
	BYTE bView = 2;
#ifdef TWO_NN
	bView = 1;
#endif

	for (BYTE i=0; i<PLAY_COUNT; i++)
	{
		if (m_pUserItem[i]!=NULL && (m_bOpenCard[i]==TYPE_OPEN))
		{
			if (0<m_UserBull[bView].GetCardCount() && bView==i)
				lTmp = 33;
			else
				lTmp = 0;

			::TransparentBlt(pDC->GetSafeHdc(), m_PtOpenCard[i].x, \
				m_PtOpenCard[i].y-lTmp, \
				ImgOpenCard.GetWidth(), ImgOpenCard.GetHeight(), dc.GetSafeHdc(), \
				0, 0, m_imgOpenCard.GetWidth(), m_imgOpenCard.GetHeight(),dc.GetPixel(0,0));
		}
	}

	dc.DeleteDC();
}

//画牌型
void CClientPlayView::DrawShape(CDC *pDC,int x,int y,int shape)
{
	//CDC dc;
	//dc.CreateCompatibleDC(pDC);
	//CGameImageHelper help(&m_10Num);
	//dc.SelectObject(help);
	//dc.DeleteDC();
	
	//case 11:
	//	{
	//		CGameImageHelper	help(&m_ImgYn);
	//		dc.SelectObject(help);
	//		::TransparentBlt(pDC->GetSafeHdc(),x,y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_ImgYn.GetWidth(),m_ImgYn.GetHeight(),dc.GetPixel(0,0));
	//	}
	//	break;
	//case 12:
	//	{
	//		CGameImageHelper	help(&m_ImgJn);
	//		dc.SelectObject(help);
	//		::TransparentBlt(pDC->GetSafeHdc(),x,y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_ImgJn.GetWidth(),m_ImgJn.GetHeight(),dc.GetPixel(0,0));
	//	}
	//	break;
	//case 13:
	//	{
	//		CGameImageHelper	help(&m_ImgFive);
	//		dc.SelectObject(help);
	//		::TransparentBlt(pDC->GetSafeHdc(),x,y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_ImgFive.GetWidth(),m_ImgFive.GetHeight(),dc.GetPixel(0,0));

	//	}
	//	break;
	//case 14:
	//	{
	//		CGameImageHelper	help(&m_ImgBomb);
	//		dc.SelectObject(help);
	//		::TransparentBlt(pDC->GetSafeHdc(),x,y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_ImgBomb.GetWidth(),m_ImgBomb.GetHeight(),dc.GetPixel(0,0));

	//				}
	//	break;
	//default:
	//	break;
	//}
	
	return ;
}
//设置牌型
void CClientPlayView::SetShape(BYTE iViewStation,int Shape)
{	
	m_iShape[iViewStation] = Shape;
	m_CardShape[iViewStation].ShowCardShape(m_iShape[iViewStation]);

	//for (int i = 0; i < PLAY_COUNT; i++)
	//{
	//	if (m_iShape[i] != -1)
	//	{
	//		//DrawShape(pDC, m_PtShape[i].x, m_PtShape[i].y, m_iShape[i]);

	//		m_CardShape[iViewStation].ShowCardShape(m_iShape[iViewStation]);
	//	}
	//}

	//CRect rect;
	//rect.SetRect(m_PtShape[iViewStation].x - 10, m_PtShape[iViewStation].y - 10, 
	//	m_PtShape[iViewStation].x + 150, m_PtShape[iViewStation].y + 200);
	//UpdateViewFace(rect);
}

//绘制得分情况
BOOL CClientPlayView::DrawGetPoint(CDC *pDC)
{
	int tempMax = m_iGetPoint[0];
	CGameImageHelper	help(&m_HuangGuan);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(help);
	for (int i = 0; i < PLAY_COUNT; i++)
	{
		if (m_iGetPoint[i] > tempMax)
			tempMax = m_iGetPoint[i];
		if (m_iGetPointSplit[i] > tempMax)
			tempMax = m_iGetPointSplit[i];
	}
	for (int i = 0; i < PLAY_COUNT; i++)
	{
		if (m_iGetPoint[i] != 0)
		{
			if (m_iGetPoint[i] <22)
				DrawGreenNum(pDC, m_PtGetPoint[i].x + 5, m_PtGetPoint[i].y, m_iGetPoint[i], 15, 1, 1, 0);
			else
				::TransparentBlt(pDC->GetSafeHdc(), m_PtGetPoint[i].x + 5, m_PtGetPoint[i].y - 5, help.GetWidth(),help.GetHeight(), dc.GetSafeHdc(), 0, 0, m_HuangGuan.GetWidth(), m_HuangGuan.GetHeight(), dc.GetPixel(0,0));
		}
	}
	dc.DeleteDC();	
	return TRUE;
}

//设置得分
void CClientPlayView::SetGetPoint(BYTE iViewStation,int iGetPoint)
{
	m_iGetPoint[iViewStation] = iGetPoint;
	CRect rect;
	rect.SetRect(m_PtGetPoint[iViewStation].x - 10, m_PtGetPoint[iViewStation].y - 10, 
		m_PtGetPoint[iViewStation].x + 150, m_PtGetPoint[iViewStation].y + 200);
	UpdateViewFace(rect);
	/*UpdateViewFace(NULL);*/
}
//设置得分
void CClientPlayView::SetGetPointSplit(BYTE iViewStation,int iGetPoint)
{

	/*UpdateViewFace(NULL);*/
}
void CClientPlayView::DrawGreenNum(CDC * pDC, int iXPos, int iYPos, int Num,int offset,BOOL bIsFourOrSix,BOOL bIsPlus,BOOL bThousand)
{
	CGameImageHelper ImageHandle(&m_PicGreenNum);
	CDC destdc;
	destdc.CreateCompatibleDC(pDC);
	destdc.SelectObject(ImageHandle);
	if (!bIsPlus)
	{
		::TransparentBlt(pDC->GetSafeHdc(), iXPos+offset, iYPos, GREEN_NUM_WIDTH/2, GREEN_NUM_HEIGHT, destdc.GetSafeHdc(), 10*GREEN_NUM_WIDTH/2, 0, GREEN_NUM_WIDTH/2, GREEN_NUM_HEIGHT,RGB(255,0,255));
		Num = abs(Num);
	}
	if (bIsFourOrSix)
	{
		UINT uFirst = Num / 100, uSecond = (Num / 10) % 10,uThree = Num % 10;
		if(!bThousand)
		{
			int i = 1;
			if (uFirst)
				::TransparentBlt(pDC->GetSafeHdc(),iXPos+(i++)*offset,iYPos,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,destdc.GetSafeHdc(),uFirst*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
			if (uFirst || uSecond)
				::TransparentBlt(pDC->GetSafeHdc(),iXPos+(i++)*offset,iYPos,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,destdc.GetSafeHdc(),uSecond*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
			if (uFirst || uSecond || uThree)
				::TransparentBlt(pDC->GetSafeHdc(),iXPos+(i++)*offset,iYPos,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,destdc.GetSafeHdc(),uThree*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
		}
		else
		{
			int i = 2;
			::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,destdc.GetSafeHdc(),11*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
			if (uFirst)
				::TransparentBlt(pDC->GetSafeHdc(), iXPos+(i++)*offset, iYPos,GREEN_NUM_WIDTH/2, GREEN_NUM_HEIGHT, destdc.GetSafeHdc(),uFirst*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
			if (uFirst || uSecond)
				::TransparentBlt(pDC->GetSafeHdc(), iXPos+(i++)*offset, iYPos,GREEN_NUM_WIDTH/2, GREEN_NUM_HEIGHT, destdc.GetSafeHdc(),uSecond*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
			if (uFirst || uSecond || uThree)
				::TransparentBlt(pDC->GetSafeHdc(), iXPos+(i++)*offset, iYPos,GREEN_NUM_WIDTH/2, GREEN_NUM_HEIGHT, destdc.GetSafeHdc(),uThree*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
				::TransparentBlt(pDC->GetSafeHdc(), iXPos+(i++)*offset, iYPos, GREEN_NUM_WIDTH/2, GREEN_NUM_HEIGHT, destdc.GetSafeHdc(),12*GREEN_NUM_WIDTH/2,0,GREEN_NUM_WIDTH/2,GREEN_NUM_HEIGHT,RGB(255,0,255));
		}
	}
	destdc.DeleteDC();
	return;
}

void CClientPlayView::SetPass(BYTE iViewStation,int iGiveup)
{
	
	m_iPass[iViewStation]=iGiveup;
	//	CRect rect;
	//	rect.SetRect(m_PtPass[iViewStation].x,m_PtPass[iViewStation].y,m_PtPass[iViewStation].x+35,m_PtPass[iViewStation].y+20);
	//	UpdateViewFace(rect);	
	UpdateViewFace(NULL);
	return ;
}
void CClientPlayView::SetMing(BYTE iViewStation,BOOL iGiveup)
{
	m_bMing[iViewStation]=iGiveup;
	//	CRect rect;
	//	rect.SetRect(m_PtPass[iViewStation].x,m_PtPass[iViewStation].y,m_PtPass[iViewStation].x+35,m_PtPass[iViewStation].y+20);
	//	UpdateViewFace(rect);	
	UpdateViewFace(NULL);
	return ;
}
//
void CClientPlayView::SetWait(BOOL wait)
{
	m_bWait = wait;	
	UpdateViewFace(NULL);
	return ;
}
//设置开始起点
void CClientPlayView::SetBeginAnimalPos(void)
{
	m_PtBeginAnimal=m_PtBeginAnimalStart;
	return ;		
}
//开始动画
void CClientPlayView::BeginAnimal(void)
{

	//m_PtBeginAnimal.y+=20;
	//m_BeginAnimal.ShowWindow(SW_SHOW);
	//m_BeginAnimal.FixCardControl(m_PtBeginAnimal.x,m_PtBeginAnimal.y);
	//if (m_PtBeginAnimal.y>m_PtBeginAnimalEnd.y)
	//{
	//	Sleep(1000);
	//	this->GetParent()->KillTimer(ID_BEGIN_ANIMAL);
	//	m_BeginAnimal.ShowWindow(SW_HIDE);
	//}
	return ;
}
/*
//开始动画
void CClientPlayView::BeginAnimal(void)
{
	CRect rect;
	GetClientRect(&rect);
	int h = rect.Height() / 4, x = rect.Width() / 2-460/2;

	m_Animaly += 5;

	//	if ((m_Animaly >= h) && (!m_IsStop))
	//	{
	m_IsStop = true;
	//		m_Animaly -= 100;
	//	}
	m_BeginAnimal.FixCardControl(x,m_Animaly);
	if ((m_Animaly >= h) && (m_IsStop))
	{
		Sleep(500);
		this->GetParent()->SendMessage(WM_SETMESSAGE,(WPARAM)2,0);
		m_Animaly = 0;
		m_IsStop = false;
		this->GetParent()->KillTimer(ID_BEGIN_ANIMAL);
		m_BeginAnimal.ShowWindow(SW_HIDE);
		m_BeginAnimal.FixCardControl(x,m_Animaly);
	}
	return ;
}
*/
//初始化发牌动画起始坐标
void CClientPlayView::SetSendCardPointStart(BYTE iViewStation)
{
	m_iSendCardAnimalPointStart[iViewStation]=m_PtSendCardAnimalStart[iViewStation];
}
//发牌动画
void CClientPlayView::SendCardAnimal(BYTE iViewStation,bool split)
{
//	m_SendCardAnimal[iViewStation].ShowWindow(SW_SHOW);
//	for (m_flag = 0; m_flag < PLAY_COUNT; m_flag++)
//	{
//		if (m_bIsSendCard[m_flag])
//		{
//			iViewStation=m_flag;
//			break;
//		}
//	}
//	if (m_flag >= PLAY_COUNT)
//	{
//		m_SendCardAnimal[iViewStation].SetShowCard(false);
//		m_SendCardAnimal[iViewStation].ShowWindow(0);
//		this->GetParent()->KillTimer(ID_SEND_CARD_ANIMAL);
//		m_flag = 0;
//	}
//	switch(iViewStation)
//	{
//	case 0:
//		{
//			m_iSendCardAnimalPointStart[iViewStation].x-=15;		
//			m_iSendCardAnimalPointStart[iViewStation].y-=15;
//			break;
//		}
//	case 1:
//		{
//			m_iSendCardAnimalPointStart[iViewStation].x+=15;
//			m_iSendCardAnimalPointStart[iViewStation].y+=10;
//			break;
//		}
//#ifndef TWO_NN
//	case 2:
//		{
//			m_iSendCardAnimalPointStart[iViewStation].x-=20;
//			m_iSendCardAnimalPointStart[iViewStation].y+=40;
//			break;
//		}
//    case 3:
//		{
//			m_iSendCardAnimalPointStart[iViewStation].x-=40;
//			m_iSendCardAnimalPointStart[iViewStation].y+=20;
//			break;
//		}
//#endif	
//	default:
//		break;
//	}
//
//	m_SendCardAnimal[iViewStation].SetBasePoint(m_iSendCardAnimalPointStart[iViewStation],CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
//     CPoint CardEnd[PLAY_COUNT];
//	//如果分牌就发牌到分牌位置
//	if (split)
//	{
//		
//		::CopyMemory(CardEnd,&m_PtSendCardAnimalEndSplit,sizeof(m_PtSendCardAnimalEndSplit));
//
//	}
//	//否则就分牌到第一打牌位置
//	else
//	{
//		::CopyMemory(CardEnd,&m_PtSendCardAnimalEnd,sizeof(m_PtSendCardAnimalEnd));
//	}
//	switch(iViewStation)
//	{
//	case 0:
//		if(m_iSendCardAnimalPointStart[iViewStation].x<CardEnd[0].x
//			||m_iSendCardAnimalPointStart[iViewStation].y<CardEnd[0].y)
//		{
//			m_SendCardAnimal[0].SetCard(NULL,NULL,0);
//			m_SendCardAnimal[0].ShowWindow(SW_HIDE);
//			m_bIsSendCard[m_flag] = false;
//			this->GetParent()->SendMessage(WM_SENDCARD_SHOWCARD,0,0);
//		}
//		break;
//	case 1:
//		if(m_iSendCardAnimalPointStart[iViewStation].y>CardEnd[1].y
//			||m_iSendCardAnimalPointStart[iViewStation].x>CardEnd[1].x)
//		{
//		m_bIsSendCard[m_flag] = false;
//			m_SendCardAnimal[1].SetCard(NULL,NULL,0);
//			m_SendCardAnimal[1].ShowWindow(SW_HIDE);
//			this->GetParent()->SendMessage(WM_SENDCARD_SHOWCARD,1,1);
//		}
//		break;
//#ifndef TWO_NN	
//	case 2:
//		if(m_iSendCardAnimalPointStart[iViewStation].x<CardEnd[2].x
//			||m_iSendCardAnimalPointStart[iViewStation].y>CardEnd[2].y)
//		{
//			m_bIsSendCard[m_flag] = false;
//			m_SendCardAnimal[2].SetCard(NULL,NULL,0);
//			m_SendCardAnimal[2].ShowWindow(SW_HIDE);
//			this->GetParent()->SendMessage(WM_SENDCARD_SHOWCARD,2,2);
//		}
//		break;
//	
//	case 3:
//		if(m_iSendCardAnimalPointStart[iViewStation].x<CardEnd[3].x
//			||m_iSendCardAnimalPointStart[iViewStation].y>CardEnd[3].y)
//		{
//			m_bIsSendCard[m_flag] = false;
//			m_SendCardAnimal[3].SetCard(NULL,NULL,0);
//			m_SendCardAnimal[3].ShowWindow(SW_HIDE);
//			this->GetParent()->SendMessage(WM_SENDCARD_SHOWCARD,3,3);
//		}
//		break;
//#endif
//	default:
//		break;
//	}
	return ;
}
void CClientPlayView::SetAddTimes(int iTimes)
{
	m_iNoteJeontTimes=iTimes;
}
//收集到正中心筹码显示
void CClientPlayView::SetAddJeton(int iBaseNote)
{
	//int xoffset=0;
	//int yoffset=0;
	//srand(GetCurrentTime());
	//xoffset=rand()%25;
	//yoffset=rand()%25;
	//int ibase=(rand()%2)?1:-1;
	//xoffset*=ibase;
	//yoffset*=ibase;
	//m_NoteAllPoint[m_iNoteJeontTimes]=CPoint(xoffset,yoffset);
	//m_NoteAll[m_iNoteJeontTimes].SetBasePoint(CPoint(m_PtNoteAll.x+xoffset,m_PtNoteAll.y+yoffset));
	//m_NoteAll[m_iNoteJeontTimes].SetTotalJeton(iBaseNote);
	//Sleep(500);
	//m_iNoteJeontTimes++;
	//if(m_iNoteJeontTimes>49)
	//	m_iNoteJeontTimes=0;
	//
	
}
void CClientPlayView::ShowAllNote()
{
	//for(int i=0;i<m_iNoteJeontTimes;i++)
	//{
	//	m_NoteAll[i].SetBasePoint(CPoint(m_PtNoteAll.x+m_NoteAllPoint[i].x,m_PtNoteAll.y+m_NoteAllPoint[i].y));//.x+xoffset,m_PtNoteAll.y+yoffset));
	//}
}
//初始化系统收集筹码动画坐标
void CClientPlayView::SetCollectJetonStart()
{
	m_PtCollectJetonStart[0]=m_PtNoteAnimalEnd[0];
	m_PtCollectJetonStart[1]=m_PtNoteAnimalEnd[1];
#ifndef TWO_NN
	m_PtCollectJetonStart[2]=m_PtNoteAnimalEnd[2];
	m_PtCollectJetonStart[3]=m_PtNoteAnimalEnd[3];
#endif
}

//收集筹码动画
void CClientPlayView::CollectJetonAnimal()
{
//	m_PtCollectJetonStart[0].y+=20;
//	m_PtCollectJetonStart[1].x-=20;
//#ifndef TWO_NN
//	m_PtCollectJetonStart[2].y-=20;
//	m_PtCollectJetonStart[3].x+=20;
//#endif
//	m_NoteTotal[0].SetBasePoint(m_PtCollectJetonStart[0]);
//
//	m_NoteTotal[1].SetBasePoint(m_PtCollectJetonStart[1]);
//#ifdef TWO_NN
//	m_NoteTotal[2].SetBasePoint(m_PtCollectJetonStart[2]);
//
//	m_NoteTotal[3].SetBasePoint(m_PtCollectJetonStart[3]);
//#endif
//
//#ifdef TWO_NN
//	if(m_PtCollectJetonStart[0].y>m_PtNoteAll.y||m_PtCollectJetonStart[1].x<m_PtNoteAll.x )
//#else
//	if(m_PtCollectJetonStart[0].y>m_PtNoteAll.y||m_PtCollectJetonStart[1].x<m_PtNoteAll.x
//		||m_PtCollectJetonStart[2].y<m_PtNoteAll.y||m_PtCollectJetonStart[3].x>m_PtNoteAll.x)
//#endif
//	{
//		int xoffset=0;
//		int yoffset=0;
//		int ibase=1;
//		srand(GetCurrentTime());
//		xoffset=rand()%25;
//		yoffset=rand()%25;
//		ibase=(rand()%2)?1:-1;
//		xoffset*=ibase;
//		yoffset*=ibase;
//
//
//		//收集本轮下注筹码
//		m_NoteAll[m_iNoteJeontTimes].SetBasePoint(CPoint(m_PtNoteAll.x+xoffset,m_PtNoteAll.y+yoffset));
//		m_NoteAll[m_iNoteJeontTimes++].SetTotalJeton(m_NoteTotal[0].GetJeton());
//		if(m_iNoteJeontTimes>49)
//			m_iNoteJeontTimes=0;
//
//		xoffset=rand()%25;
//		yoffset=rand()%25;
//		ibase=(rand()%2)?1:-1;
//		xoffset*=ibase;
//		yoffset*=ibase;
//		m_NoteAll[m_iNoteJeontTimes].SetBasePoint(CPoint(m_PtNoteAll.x+xoffset,m_PtNoteAll.y+yoffset));
//		m_NoteAll[m_iNoteJeontTimes++].SetTotalJeton(m_NoteTotal[1].GetJeton());
//		if(m_iNoteJeontTimes>49)
//			m_iNoteJeontTimes=0;
//		xoffset=rand()%25;
//		yoffset=rand()%25;
//		ibase=(rand()%2)?1:-1;
//		xoffset*=ibase;
//		yoffset*=ibase;
//		m_NoteAll[m_iNoteJeontTimes].SetBasePoint(CPoint(m_PtNoteAll.x+xoffset,m_PtNoteAll.y+yoffset));
//		m_NoteAll[m_iNoteJeontTimes++].SetTotalJeton(m_NoteTotal[2].GetJeton());
//		if(m_iNoteJeontTimes>49)
//			m_iNoteJeontTimes=0;
//
//		xoffset=rand()%25;
//		yoffset=rand()%25;
//		ibase=(rand()%2)?1:-1;
//		xoffset*=ibase;
//		yoffset*=ibase;
//		m_NoteAll[m_iNoteJeontTimes].SetBasePoint(CPoint(m_PtNoteAll.x+xoffset,m_PtNoteAll.y+yoffset));
//		m_NoteAll[m_iNoteJeontTimes++].SetTotalJeton(m_NoteTotal[3].GetJeton());
//		if(m_iNoteJeontTimes>49)
//			m_iNoteJeontTimes=0;
//			if(m_iNoteJeontTimes>49)
//			m_iNoteJeontTimes=0;
//
//		//还原玩家本轮下注终点坐标
//		m_NoteTotal[0].SetBasePoint(m_PtNoteAnimalEnd[0]);
//		m_NoteTotal[1].SetBasePoint(m_PtNoteAnimalEnd[1]);
//#ifndef TWO_NN
//		m_NoteTotal[2].SetBasePoint(m_PtNoteAnimalEnd[2]);
//		m_NoteTotal[3].SetBasePoint(m_PtNoteAnimalEnd[3]);
//#endif
//		//清除玩家本轮下注
//		m_NoteTotal[0].SetTotalJeton(0);
//		m_NoteTotal[1].SetTotalJeton(0);
//#ifndef TWO_NN
//		m_NoteTotal[2].SetTotalJeton(0);
//		m_NoteTotal[3].SetTotalJeton(0);
//#endif
//		this->GetParent()->KillTimer(ID_COLLECT_JETON_ANIMAL);
//	}
	return ;
}

//初始化下注动画起始坐标
void CClientPlayView::SetNotePointStart(BYTE iViewStation)
{
	m_iNoteAnimalPointStart[iViewStation]=m_PtNoteAnimalStart[iViewStation];
}

//下注动画
void CClientPlayView::NoteAnimal(BYTE iViewStation)
{/*
	m_NoteAnimal.ShowWindow(SW_SHOW);
	switch(iViewStation)
	{
	case 0:
		m_NoteAnimal.SetLookMode(true);
		m_iNoteAnimalPointStart[iViewStation].y+=20;break;
	case 1:
		m_NoteAnimal.SetLookMode(false);
		m_iNoteAnimalPointStart[iViewStation].x-=20;break;
#ifndef TWO_NN
	case 2:
		m_NoteAnimal.SetLookMode(true);
		m_iNoteAnimalPointStart[iViewStation].y-=20;break;
	case 3:
		m_NoteAnimal.SetLookMode(false);
		m_iNoteAnimalPointStart[iViewStation].x+=20;break;
#endif
	default:
		break;
	}

	m_NoteAnimal.SetBasePoint(m_iNoteAnimalPointStart[iViewStation]);

	switch(iViewStation)
	{
	case 0:
		if(m_iNoteAnimalPointStart[iViewStation].y>m_PtNoteAnimalEnd[iViewStation].y)
		{
			m_NoteAnimal.SetTotalJeton(0);
			m_NoteTotal[0].SetTotalJeton(m_iThisTurnNote[0]);
			m_NoteTotal[0].ShowWindow(SW_SHOW);
			m_iThisTurnAddNote=0;
			this->GetParent()->KillTimer(ID_NOTE_ANIMAL_ZERO);
		}
		break;
	case 1:
		if(m_iNoteAnimalPointStart[iViewStation].x<m_PtNoteAnimalEnd[iViewStation].x)
		{
			m_NoteAnimal.SetTotalJeton(0);
			m_NoteTotal[1].SetTotalJeton(m_iThisTurnNote[1]);
			m_iThisTurnAddNote=0;
			this->GetParent()->KillTimer(ID_NOTE_ANIMAL_ONE);
		}
		break;
#ifndef TWO_NN
	case 2:
		if(m_iNoteAnimalPointStart[iViewStation].y<m_PtNoteAnimalEnd[iViewStation].y)
		{
			m_NoteAnimal.SetTotalJeton(0);
			m_NoteTotal[2].SetTotalJeton(m_iThisTurnNote[2]);
			m_iThisTurnAddNote=0;
			this->GetParent()->KillTimer(ID_NOTE_ANIMAL_TWO);
		}
		break;
	case 3:
		if(m_iNoteAnimalPointStart[iViewStation].x>m_PtNoteAnimalEnd[iViewStation].x)
		{
			m_NoteAnimal.SetTotalJeton(0);
			m_NoteTotal[3].SetTotalJeton(m_iThisTurnNote[3]);
			m_iThisTurnAddNote=0;
			this->GetParent()->KillTimer(ID_NOTE_ANIMAL_THREE);
		}
		break;
#endif
	default:
		break;
	}
	return ;*/
}
#ifdef VIDEO
///将此昵称的玩家视频窗口矩形写入参数rect,并返回TRUE;没找到返回falst
BOOL	CClientPlayView::GetVideoRect(CString  strNickname, RECT& rect, CString& pic)
{
 	CString strLocalName;
	CString logopathstr;
	for(int iCount=0; iCount<MAX_PEOPLE; iCount++)
	{
		if(m_pUserItem[iCount])
		{    
			strLocalName=m_pUserItem[iCount]->GameUserInfo.nickName;
			if(strLocalName == strNickname)
			{
				rect=m_rectVideoFrame[iCount];
				
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

void CClientPlayView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bDraw)
	{
		if(PtInRect(&m_BtnRect0,point))
		{
			OnNote(1);
			return ;
		}
		if(PtInRect(&m_BtnRect1,point))
		{
			OnNote(2);
			return ;
		}
		if(PtInRect(&m_BtnRect2,point))
		{
			OnNote(3);
			return ;
		}
		if(PtInRect(&m_BtnRect3,point))
		{
			OnNote(4);
			return ;
		}

	}
	//PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	return ;
	CUsingSkinClass::OnLButtonDown(nFlags, point);
	
}
void CClientPlayView::OnNote(int type)
{
	//int Num;
	CString str;
	str.Format("zhtlog:type=%d",type);
	OutputDebugString(str);
	 CClientGameDlg *pp=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	 pp->SendMessage(IDM_SELECT_NOTE_NUM,type,TYPE_NOTE); 
}

void CClientPlayView::DrawMoney(CDC *pDC)
{
	CGameImageHelper	help(&m_WinFen);
	CGameImageHelper	help1(&m_LossFen);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(help);
	CFont Font, *OldFont;
	CRect  rect;

	CHAR szMsg[50];
	int TempLen = 14;

	if (m_iNoteLimit > 99999999999)
		TempLen = 12;
	Font.CreateFont(TempLen,0,0,0,700,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	OldFont=pDC->SelectObject(&Font);
	pDC->SetBkMode(TRANSPARENT);
	LONG LX,LY;

	for (int i=0; i<PLAY_COUNT; i++)
	{
		if (m_iNotePoint[i] != 0)
		{
			LX = m_PtNoteAnimalEnd[i].x -(82-help.GetWidth())/2;
			LY = m_PtNoteAnimalEnd[i].y -(33-help.GetHeight())/2;

			rect.left = LX;
			rect.top = LY;
			rect.right = rect.left +help.GetWidth() ;
			rect.bottom = rect.top +help.GetHeight();
			if (m_iNotePoint[i]>0)
			{
				dc.SelectObject(help);
				::TransparentBlt(pDC->GetSafeHdc(),LX,LY,help.GetWidth(),\
					help.GetHeight(),dc.GetSafeHdc(),0,0,m_WinFen.GetWidth(),m_WinFen.GetHeight(),dc.GetPixel(0,0));
				
				pDC->SetTextColor(RGB(0,19,43));
				CString strMoney;
				GetNumString(m_iNotePoint[i],strMoney,m_nPowerOfGold);
				pDC->DrawText(strMoney,strMoney.GetLength(),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			}
			else
			{
				dc.SelectObject(help1);
				::TransparentBlt(pDC->GetSafeHdc(),LX,LY,help1.GetWidth(), \
					help1.GetHeight(),dc.GetSafeHdc(),0,0,m_LossFen.GetWidth(),m_LossFen.GetHeight(),dc.GetPixel(0,0));
				
				CString strMoney;
				GetNumString(m_iNotePoint[i],strMoney,m_nPowerOfGold);
				//wsprintf(szMsg,"%d",m_iNotePoint[i]);
				//pDC->SetTextColor(RGB(246,211,0));

				pDC->SetTextColor(RGB(229, 229, 229));
				pDC->DrawText(strMoney,strMoney.GetLength(),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				//pDC->DrawText(szMsg,lstrlen(szMsg),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			}

		}
	}
	dc.DeleteDC();
}
//colin090411发牌动画
void CClientPlayView::SendCard(BYTE byViewSeat, int iTime)
{
	BYTE byCardList[1]={0};	
	m_SendCardAnimal[byViewSeat].StopMove();
	m_SendCardAnimal[byViewSeat].SetCard(NULL, NULL, 0);
	m_SendCardAnimal[byViewSeat].MoveAnimal(m_PtSendCardAnimalStart[byViewSeat], m_PtSendCardAnimalEnd[byViewSeat], (long)iTime);
	m_SendCardAnimal[byViewSeat].SetCard(byCardList, NULL, 1);
}
///
///依当前金币倍率得到字符串
///@param [int] int nNum 要显示的数字
///@param [out] CString &Str 返回的字符串
///@param [int] int nPower 金币倍率
///@return void
///
void CClientPlayView::GetNumString(__int64 nNum, CString &Str, int nPower)
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
	wsprintf( strTmp, TEXT("%I64d"), nNum);
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
			//str[nDes++] = TEXT(' ');///牛牛不加空格
		//}
		str[nDes++] = strTmp[nSrc++];
	}
	str[nDes] = TEXT('\0');
	Str.Format("%s",str);
	return ;
}