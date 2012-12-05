#include "StdAfx.h"
#include "ClientView.h"
#include "ClientGameDlg.h"

//CBitmap				CClientPlayView::m_Bitmap_Num;

extern void MyMsgBox(const char *lpszFormat, ...);


BEGIN_MESSAGE_MAP(CClientPlayView, CUsingSkinClass)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CONTINUE, OnHitContinue)
	ON_BN_CLICKED(IDC_STARTDISPLAY, OnHitBeginDisplayCards)
	ON_BN_CLICKED(IDC_LEAVE, OnHitLeave)

	ON_BN_CLICKED(IDC_HAVE_THING, OnHitThing)
	ON_BN_CLICKED(IDC_AUTOCARD, OnHitAuto)
	ON_BN_CLICKED(IDC_SORT_CARD,OnHitSort)
	ON_BN_CLICKED(IDC_LAST_CARD,OnHitLastTurn)	

	ON_BN_CLICKED(IDC_OUT_CARD,OnHitOutCard)
	ON_BN_CLICKED(IDC_CUE,OnCue)
	ON_BN_CLICKED(IDC_PASS,OnHitPass)

	ON_COMMAND_RANGE(IDC_CALL_SCORE_PASS,IDC_CALL_SCORE_3,OnHitCallScore)
	//加棒抢地主
	ON_BN_CLICKED(IDC_ROB_NT,OnHitRobNT)	
	ON_BN_CLICKED(IDC_ROB_NT_2,OnHitRobNT2)	

	ON_BN_CLICKED(IDC_ADD_DOUBLE,OnHitAddDouble)	
	ON_BN_CLICKED(IDC_ADD_DOUBLE_2,OnHitAddDouble2)	

	ON_BN_CLICKED(IDC_SHOW_CARD,OnHitShowCard)	
	ON_BN_CLICKED(IDC_SHOW_CARD_2,OnHitShowCard2)	

	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

/*******************************************************************************************************/

//构造函数
CClientPlayView::CClientPlayView(void) //:m_GameSet(this),m_GameInfo(this)//,m_GameEndView(this)
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	SetNameColor(RGB(255,255,0));			//设置默认用户名颜色

	memset(m_iPass,0,sizeof(m_iPass));

	m_iCurOrientation=-1;	//出牌方向

	m_iRoomMultiple=0;

	m_iGameMultiple=0;

	m_iNtStation=-1;

	m_iCallScoreResult = -1;

	m_iCueType = 3;

	m_bFirstGame = true;		//090310a1 JJ 
	::memset(m_iCallScore,-1,sizeof(m_iCallScore));
	::memset(m_iPeopleMul,1,sizeof(m_iPeopleMul));
	::memset(m_bLaiCardList,0,sizeof(m_bLaiCardList));
	m_bInit = false;
	m_bIsFakeBomb = FALSE;//是否为软炸
	//AfxSetResourceHandle(GetModuleHandle(NULL));

	CString fpath = CINIFile::GetAppPath();
	CString fName ; 

	fName.Format("%d.bcf" , NAME_ID) ; 
	fpath +=  fName;

	CBcfFile file(fpath);
	CString firstKey(TEXT("Config"));

	m_bShowLogo = file.GetKeyVal(firstKey , "ShowLogo" , 0 )  ; 
	m_bShowMoney = file.GetKeyVal(firstKey , "ShowMoney" , 0) ; 
	m_strCoinName = file.GetKeyVal(firstKey , "CoinName" , "金币")  ; 
	
	return;
}

//析构函数
CClientPlayView::~CClientPlayView(void)
{
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
	DrawBk(pDC,iWidth,iHeight);

	CGameImageHelper yichunxs_bg(&m_Background);				//背景图和LOGO
	CRect rect;
	GetClientRect(&rect);		
	int x=(rect.right-yichunxs_bg.GetWidth())/2;
	int y=((rect.bottom)-yichunxs_bg.GetHeight())/2+30;
	yichunxs_bg.BitBlt(pDC->GetSafeHdc(),x,y);
	//贴logo
	DrawGameTitle(pDC);


	CFont Font,*OldFont;
	Font.CreateFont(12,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	OldFont=pDC->SelectObject(&Font);
	TCHAR sz[100];
	
#ifdef VIDEO
	for (int i=0;i<PLAY_COUNT;i++)
	{
		if (m_pUserItem[i]!=NULL)
		{
			UserInfoStruct * pUserInfo=&m_pUserItem[i]->GameUserInfo;
			pDC->SetTextColor(GetNameColor(&(m_pUserItem[i]->GameUserInfo)));		//用户昵称颜色

			POINT offsetLogo={0,0};
			POINT offsetAgree={0,0};
			RECT  rectName,rectcars;  ///昵称和剩余牌数的框	

			offsetLogo.x	= m_rectVideoFrame[i].left + (160-LOGO_WIDTH)/2;
			offsetLogo.y	= m_rectVideoFrame[i].top + 30;

			rectName.left	= m_rectVideoFrame[i].left + 0;
			rectName.top	= m_rectVideoFrame[i].top +  2;
			rectName.right	= rectName.left + 160;
			rectName.bottom	= rectName.top + 20;

			rectcars.left	= m_rectVideoFrame[i].left + 25;
			rectcars.top	= m_rectVideoFrame[i].bottom + 25 ;
			rectcars.right	= rectcars.left +47;
			rectcars.bottom	= rectcars.top + 20;

			if(i!=0)
			{
				offsetAgree.x	= m_rectVideoFrame[i].left;
				offsetAgree.y	= m_rectVideoFrame[i].top -12;	
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
#ifdef MY_TWO
			if(i!=1) 
			{
				CGameImageHelper Num(&m_Num);
				CDC NumDC;
				NumDC.CreateCompatibleDC(pDC);
				NumDC.SelectObject(Num);
				int iNumWidth = 25,iNumHeight = 28;
				//加上剩余牌数
				wsprintf(sz,_T("剩余牌数:"),m_HandCard[i].GetCardCount()); 
				pDC->DrawText(sz,lstrlen(sz),&rectcars,DT_SINGLELINE);
				int num1 =m_HandCard[i].GetCardCount()/10 ,num2 = m_HandCard[i].GetCardCount()%10;
				if(m_HandCard[i].GetCardCount() >= 10 )
				{
					::TransparentBlt(pDC->GetSafeHdc(),rectcars.right,rectcars.top-iNumHeight/3,iNumWidth,iNumHeight,NumDC.GetSafeHdc(),num1*iNumWidth,0,iNumWidth,iNumHeight,RGB(255,0,255));
					::TransparentBlt(pDC->GetSafeHdc(),rectcars.right+iNumWidth,rectcars.top-iNumHeight/3,iNumWidth,iNumHeight,NumDC.GetSafeHdc(),num2*iNumWidth,0,iNumWidth,iNumHeight,RGB(255,0,255));
				}else 
				{
					::TransparentBlt(pDC->GetSafeHdc(),rectcars.right,rectcars.top-iNumHeight/3,iNumWidth,iNumHeight,NumDC.GetSafeHdc(),num2*iNumWidth,0,iNumWidth,iNumHeight,RGB(255,0,255));
				}
				NumDc.DeleteDC();
			} 
#endif

			//昵称
			wsprintf(sz,"%s",m_pUserItem[i]->GameUserInfo.nickName); 
			pDC->DrawText(sz,lstrlen(sz),&rectName,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

			//====用户头像
			if(m_bShowLogo)
			{
				DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,offsetLogo.x - 10,offsetLogo.y - 13,m_pUserItem[i]->GameUserInfo.bUserState==USER_CUT_GAME,
					m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
			}
			
			//===读秒
			//计时器
			if (m_uTime[i]!=0)
			{
				if (!m_bFirstGame)//090310a1 JJ 添加当进入新桌子的时候倒计时放到中间
				{
					DrawTimer(pDC,m_PtTime[i].x,m_PtTime[i].y,m_uTime[i]);
				}
				else
				{
					DrawTimer(pDC, iWidth/2-15, iHeight/2-11, m_uTime[i]);
				}
			}
			//同意标识
			if (m_pUserItem[i]->GameUserInfo.bUserState==USER_ARGEE)
				DrawArgeeFlag(pDC,m_PtAgree[i].x, m_PtAgree[i].y);

		}
	}
#else

	for (int i = 0; i < PLAY_COUNT; i ++)
	{
		if (m_pUserItem[i] == NULL)
			continue;
		pDC->SetTextColor(GetNameColor(&(m_pUserItem[i]->GameUserInfo)));		//用户昵称颜色
		//绘制框架
		//DrawLogoFrame(pDC,m_PtLogo[i].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2,m_PtLogo[i].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2);

		if(m_bShowLogo)
		{
			DrawLogo(pDC,m_pUserItem[i]->GameUserInfo.bLogoID,m_PtLogo[i].x,m_PtLogo[i].y,m_pUserItem[i]->GameUserInfo.bUserState == USER_CUT_GAME,m_pUserItem[i]->GameUserInfo.dwUserID,false,false);
		}

		UserInfoStruct * pUserInfo = &m_pUserItem[i]->GameUserInfo;
		wsprintf(sz,TEXT("昵称:%s"),pUserInfo->nickName);
		rect.left = m_PtName[i].x - 10;
		rect.right = rect.left+LOGO_WIDTH+60;
		rect.top = m_PtName[i].y - 28;
		rect.bottom = rect.top+20;
		pDC->DrawText(sz,lstrlen(sz),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		if(m_bShowMoney)
		{
			rect.left = m_PtName[i].x - 10;
			rect.right = rect.left+LOGO_WIDTH+60;
			rect.top = m_PtName[i].y;
			rect.bottom = rect.top+20;

			CString strMoneyInfo ;
			strMoneyInfo.Format("%s:%I64d", m_strCoinName , pUserInfo->i64Money) ; 
			pDC->DrawText(strMoneyInfo,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		}

		if (m_uTime[i] != 0) 
		{
			if (!m_bFirstGame)//090310a1 JJ 添加当进入新桌子的时候倒计时放到中间
			{
				DrawTimer(pDC,m_PtTime[i].x,m_PtTime[i].y,m_uTime[i]);
			}
			else
			{
				DrawTimer(pDC, iWidth/2-15, iHeight/2-11, m_uTime[i]);
			}
		}

		if (pUserInfo->bUserState == USER_ARGEE)
			DrawArgeeFlag(pDC,m_PtAgree[i].x,m_PtAgree[i].y);
	}
#endif

	//绘画庄家位置
	if (m_iNtStation != -1) 
	{
		DrawNt(pDC,m_PtNt[m_iNtStation].x,m_PtNt[m_iNtStation].y);		
		DrawFarmer(pDC,m_PtNt[(m_iNtStation+1)%PLAY_COUNT].x,m_PtNt[(m_iNtStation+1)%PLAY_COUNT].y);
		DrawFarmer(pDC,m_PtNt[(m_iNtStation+2)%PLAY_COUNT].x,m_PtNt[(m_iNtStation+2)%PLAY_COUNT].y);
	}
	//画赖子
	DrawLai(pDC);
	//叫分提示信息
	DrawShowMsg(pDC);
	//叫分结果	
	DrawCallScoreResult(pDC);
	//倍率
	DrawRoomMultiple(pDC);
	//叫分
	DrawFen(pDC);
	//不出
	DrawPass(pDC);
	//托管
	DrawAuto(pDC);
	//奖分
	DrawAwardPoint(pDC);
	//绘制出牌指示方向
	DrawOrientation(pDC);
	//加棒
	DrawPeopleMultiple(pDC);
	//GIF动画
	DrawGif(pDC,m_PtGif[m_iGifDeskStation].x,m_PtGif[m_iGifDeskStation].y);
	//结果动画(地主输,地主赢)
	m_AnimalResult.DrawAnimal(pDC, iWidth/2, iHeight/2);
	//小炸弹动画
	m_AnimalBomb[0].DrawAnimal(pDC, iWidth/2, iHeight/2);
	m_AnimalBomb[1].DrawAnimal(pDC, iWidth/2, iHeight/2);
	m_AnimalBomb[2].DrawAnimal(pDC, iWidth/2, iHeight/2);
	//大炸弹动画
	m_AnimalBigBomb.DrawAnimal(pDC, iWidth/2, iHeight/2);
	
	
	DeleteObject(pDC->SelectObject(OldFont));
	return;
}
//绘制游戏背面小图
void CClientPlayView::DrawBk(CDC *pDC,int iWidth, int iHeight)
{
	CGameImageHelper bg(&m_bit_background);
	if(m_bit_background.GetHeight()>0)
		for(int i = 0; i < iHeight; i += m_bit_background.GetHeight())
		{
			for(int j = 0; j < iWidth; j += m_bit_background.GetWidth())
			{	
				bg.BitBlt(pDC->GetSafeHdc(), j ,i);	
			}	
		}
		return ;
}

//绘制游戏名称logo
void CClientPlayView::DrawGameTitle(CDC *pDC)
{
	CGameImageHelper bg(&m_GameTitleLogo);

	bg.BitBlt(pDC->GetSafeHdc(),m_PtGameTitle.x,m_PtGameTitle.y);	
	return ;
}

//透明自理
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
	//	SetTextColor(hImageDC,RGB(255,255,255));
	// 生成透明区域为白色，其它区域为黑色的掩码位图(s|~b)
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));//(s&b)
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(255,255,255));
	SetTextColor(hdcDest,RGB(0,0,0));//(s&b)
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

	//加载所有图片
	TCHAR path[MAX_PATH];

	wsprintf(path,TEXT(".\\image\\%s\\cardnum.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_Num.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
#ifdef VIDEO
	wsprintf(path, (".\\image\\%s\\VideoFrame.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_pVideoFrame.SetLoadInfo(path,false);
#else
	if(m_iUserFrame.GetWidth() <= 0)
	{
		wsprintf(path,TEXT(".\\image\\%s\\logoframe.bmp"),GET_SKIN_FOLDER(szTempStr));
		SetFrameImage(path);
	}
#endif

	wsprintf(path,TEXT(".\\image\\%s\\BackColorOnly.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_bit_background.SetLoadInfo(path,CGameImageLink::m_bAutoLock);				//小贴图背景

	wsprintf(path,TEXT(".\\image\\%s\\centerlogo.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_Background.SetLoadInfo(path,CGameImageLink::m_bAutoLock);		//中心图片

	wsprintf(path,TEXT(".\\image\\%s\\Nt.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_NT.SetLoadInfo(path, false);

	wsprintf(path,TEXT(".\\image\\%s\\nm.bmp"),GET_SKIN_FOLDER(szTempStr)); 
	m_NT2.SetLoadInfo(path,false);						

	wsprintf(path,TEXT(".\\image\\%s\\AwardPoint.bmp"),GET_SKIN_FOLDER(szTempStr)); //囧 后面又重设路径了
	m_AwardPint.SetLoadInfo(path,true);						

	wsprintf(path,TEXT(".\\image\\%s\\CallScore2_pass.bmp"),GET_SKIN_FOLDER(szTempStr)); //囧
	m_CallScore.SetLoadInfo(path,false);					

	wsprintf(path,TEXT(".\\image\\%s\\tuoguan.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_AutoLogo.SetLoadInfo(path,true);	

	wsprintf(path,TEXT(".\\image\\%s\\pass.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_Pass.SetLoadInfo(path,false);							

	wsprintf(path,TEXT(".\\image\\%s\\lastcardflag.bmp"),GET_SKIN_FOLDER(szTempStr));// 囧
	m_LastCardFlag.SetLoadInfo(path,false);						

	//方向
	wsprintf(path,TEXT(".\\image\\%s\\CurOutCard.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_ImgFangXiang.SetLoadInfo(path,false);						

	//玩家倍数
	wsprintf(path,TEXT(".\\image\\%s\\ban.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_PeopleMul.SetLoadInfo(path,false);						

	//叫分倍率
	wsprintf(path,TEXT(".\\image\\%s\\showmsg.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_ShowMsg.SetLoadInfo(path,false);

	 //赖子框
	wsprintf(path,TEXT(".\\image\\%s\\laizi.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_LaiZhi.SetLoadInfo(path,false);
	
	 //赖子牌
	wsprintf(path,TEXT("image\\%s\\Game_Card_LaiZi.bmp"),SKIN_CARD);
	m_ImgCard.SetLoadInfo(path,false);
	
	//小癞子
	wsprintf(path,TEXT("image\\%s\\laizipai.bmp"),SKIN_CARD);
	m_ImgSmlLaiz.SetLoadInfo(path,false);

	m_btOutCard.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,56,26),this,IDC_OUT_CARD);
	m_btPass.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,56,26),this,IDC_PASS);
	m_btCue.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,56,26),this,IDC_CUE);

	m_btContinue.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,56,26),this,IDC_CONTINUE);
	//m_btStartDisplayCards.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,56,26),this,IDC_STARTDISPLAY); //明牌开始按钮
	m_btLeave.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|BS_OWNERDRAW,CRect(0,0,56,26),this,IDC_LEAVE);

	m_btLastTurn.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,56,26),this,IDC_LAST_CARD);
	m_btThing.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,56,26),this,IDC_HAVE_THING);
	m_btAuto.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,56,26),this,IDC_AUTOCARD);
	m_btSortCard.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,56,26),this,IDC_SORT_CARD);

	m_GameNoteView.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,50,NULL);
	m_Result.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,51,NULL);
	m_SelectLaiZhi.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,52,NULL);

	m_btCallScorePass.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_CALL_SCORE_PASS);
	m_btCallScore1.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_CALL_SCORE_1);
	m_btCallScore2.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_CALL_SCORE_2);
	m_btCallScore3.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_CALL_SCORE_3);
	//加棒抢地主
	m_btRobNT.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_ROB_NT);
	m_btRobNT2.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_ROB_NT_2);

	m_btAddDouble.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_ADD_DOUBLE);
	m_btAddDouble2.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_ADD_DOUBLE_2);

	m_btShowCard.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_SHOW_CARD);
	m_btShowCard2.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_SHOW_CARD_2);

	//不要聊天框了....
	//for(int i = 0;i< PLAY_COUNT;i++)
	//{
	//	m_dlgDisTalk[i].m_viewid = i;
	//	m_dlgDisTalk[i].Create(IDD_DISPLAY_TALK,this);  //创建聊天信息框
	//	m_dlgDisTalk[i].ShowWindow(SW_HIDE);             //创建后隐藏
	//}
	m_ToolTip.Create(this);

	m_ToolTip.AddTool((CWnd*)&m_btThing,TEXT("有事要走"));
	m_ToolTip.AddTool((CWnd*)&m_btAuto,TEXT("托管"));
	m_ToolTip.AddTool((CWnd*)&m_btSortCard,TEXT("排列"));
	m_ToolTip.AddTool((CWnd*)&m_btLeave,TEXT("离开"));

	CGameImage m_bk;
	HRGN hRgn;
	TCHAR szName[MAX_PATH];
	wsprintf(szName,TEXT(".\\image\\%s\\start_bt.bmp"),GET_SKIN_FOLDER(szTempStr));	//开始按钮
	m_btContinue.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btContinue.SetWindowRgn(hRgn,true);

	//wsprintf(szName,TEXT(".\\image\\%s\\btStartDisplay.bmp"),GET_SKIN_FOLDER(szTempStr));	//明牌开始按钮????
	//m_btStartDisplayCards.LoadButtonBitmap(szName,false);	
	//m_bk.SetLoadInfo(szName,true);
	//hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	//if(hRgn)
	//	m_btStartDisplayCards.SetWindowRgn(hRgn,true);

	wsprintf(szName,TEXT(".\\image\\%s\\OutCard_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//出牌按钮
	m_btOutCard.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btOutCard.SetWindowRgn(hRgn,true);

	wsprintf(szName,TEXT(".\\image\\%s\\Pass_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//Pass按钮
	m_btPass.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btPass.SetWindowRgn(hRgn,true);

	wsprintf(szName,TEXT(".\\image\\%s\\Cue_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//提示按钮
	m_btCue.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCue.SetWindowRgn(hRgn,true);

	wsprintf(szName,TEXT(".\\image\\%s\\auto_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//托管按钮
	m_btAuto.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btAuto.SetWindowRgn(hRgn,true);

	wsprintf(szName,TEXT(".\\image\\%s\\havething_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//有事要走按钮
	m_btThing.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btThing.SetWindowRgn(hRgn,true);

	wsprintf(szName,TEXT(".\\image\\%s\\sort_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//排序按钮
	m_btSortCard.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btSortCard.SetWindowRgn(hRgn,true);



	wsprintf(szName,TEXT(".\\image\\%s\\leave_bt.bmp"),GET_SKIN_FOLDER(szTempStr));	//离开按钮		
	m_btLeave.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btLeave.SetWindowRgn(hRgn,true);

    


	//上一轮
	wsprintf(szName,TEXT(".\\image\\%s\\Lastturn_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btLastTurn.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btLastTurn.SetWindowRgn(hRgn,true);	

	//抢地主
	wsprintf(szName,TEXT(".\\image\\%s\\RobNt_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btRobNT.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btRobNT.SetWindowRgn(hRgn,true);
	//不抢地主
	wsprintf(szName,TEXT(".\\image\\%s\\RobNt2_bt.bmp"),GET_SKIN_FOLDER(szTempStr));		
	m_btRobNT2.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btRobNT2.SetWindowRgn(hRgn,true);	
	//加棒
	wsprintf(szName,TEXT(".\\image\\%s\\AddDouble_bt.bmp"),GET_SKIN_FOLDER(szTempStr));		
	m_btAddDouble.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btAddDouble.SetWindowRgn(hRgn,true);
	//不加棒
	wsprintf(szName,TEXT(".\\image\\%s\\AddDouble2_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btAddDouble2.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btAddDouble2.SetWindowRgn(hRgn,true);	

	//亮牌
	wsprintf(szName,TEXT(".\\image\\%s\\ShowCard_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btShowCard.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btShowCard.SetWindowRgn(hRgn,true);
	//不亮
	wsprintf(szName,TEXT(".\\image\\%s\\ShowCard2_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btShowCard2.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btShowCard2.SetWindowRgn(hRgn,true);	

	//叫分1按钮
	wsprintf(szName,TEXT(".\\image\\%s\\jiaofen1_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btCallScore1.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCallScore1.SetWindowRgn(hRgn,true);

	//叫分2按钮
	wsprintf(szName,TEXT(".\\image\\%s\\jiaofen2_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btCallScore2.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCallScore2.SetWindowRgn(hRgn,true);

	//叫分3按钮
	wsprintf(szName,TEXT(".\\image\\%s\\jiaofen3_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btCallScore3.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCallScore3.SetWindowRgn(hRgn,true);

	//不叫按钮
	wsprintf(szName,TEXT(".\\image\\%s\\jiaofen_pass.bmp"),GET_SKIN_FOLDER(szTempStr));			
	m_btCallScorePass.LoadButtonBitmap(szName,false);	
	m_bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCallScorePass.SetWindowRgn(hRgn,true);

	//设置动画对象(090329a1 JJ)
	wsprintf(szName,TEXT(".\\image\\%s\\Animal\\dzk.bmp"), GET_SKIN_FOLDER(szTempStr));	
	m_ImgAnimalDZLose.SetLoadInfo(szName,true);
	wsprintf(szName,TEXT(".\\image\\%s\\Animal\\dzx.bmp"), GET_SKIN_FOLDER(szTempStr));	
	m_ImgAnimalDZWin.SetLoadInfo(szName,true);
	wsprintf(szName,TEXT(".\\image\\%s\\Animal\\xzd.bmp"), GET_SKIN_FOLDER(szTempStr));	
	m_ImgAnimalSmallBomb.SetLoadInfo(szName,true);
	wsprintf(szName,TEXT(".\\image\\%s\\Animal\\hy.bmp"), GET_SKIN_FOLDER(szTempStr));	
	m_ImgAnimalBBFire.SetLoadInfo(szName,true);
	wsprintf(szName,TEXT(".\\image\\%s\\game_CARD.bmp"), SKIN_CARD);	
	m_ImgAnimalBBCardNormal.SetLoadInfo(szName,true);
	wsprintf(szName,TEXT(".\\image\\%s\\game_CARD_BACK.bmp"), SKIN_CARD);	
	m_ImgAnimalBBCardBack.SetLoadInfo(szName,true);
	wsprintf(szName,TEXT(".\\image\\%s\\Animal\\hh.bmp"), GET_SKIN_FOLDER(szTempStr));	
	m_ImgAnimalBBStar.SetLoadInfo(szName,true);
	//end

	//建立客户扑克
	for (int i = 0; i < PLAY_COUNT; i ++)
	{
		m_UserCard[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,20+i,NULL);
		m_UserCard[i].SetShowCard(true);
		m_UserCard[i].InitGameCard(GetParent());

#ifdef MY_TWO
		m_HandCard[i].Create(NULL,NULL,WS_CHILD|/*WS_VISIBLE|*/WS_CLIPSIBLINGS,CRect(0,0,0,0),this,24+i,NULL);
#else

		m_HandCard[i].Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,24+i,NULL);
#endif
		m_HandCard[i].SetShowCard(false);
		m_HandCard[i].SetCardParameter(15,15,20);
		m_HandCard[i].SetCardShowNum(1);
		m_HandCard[i].InitGameCard(GetParent());
	}
	m_MeCard.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,30,NULL);
	m_MeCard.InitGameCard(GetParent());
	m_MeBackCard.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,31,NULL);
	m_MeBackCard.InitGameCard(GetParent());
	m_MeBackCard.SetCardParameter(70,0,0);
	m_MeBackCard.SetShowCard(false);
	m_MeBackCard.SetUseMouse(false);
	m_MeBackCard.ShowWindow(SW_HIDE);

	m_btOutCard.ShowWindow(SW_HIDE);
	m_btPass.ShowWindow(SW_HIDE);
	m_btCue.ShowWindow(SW_HIDE);

#ifdef MY_TWO
	m_ThreeCard.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,CRect(0,0,0,0),this,32,NULL);
	m_ThreeCard.InitGameCard(GetParent());
	m_ThreeCard.SetShowCard(false);
	m_ThreeCard.SetCardParameter(15,15,20);
	m_ThreeCard.SetCardShowNum(1);
#endif

	//AfxSetResourceHandle(GetModuleHandle(NULL));

	m_bInit = true;
	return 0;
}

void CClientPlayView::FixControlSize(int cx,int cy)
{
	if(!m_bInit)
		return ;
	if ((cx==0)||(cy==0))
		return;

	//部分坐标
	m_PtDeskTempPoint.x = 30;
	m_PtDeskTempPoint.y = 60;

	m_PtDeskMultiple.x = 30;
	m_PtDeskMultiple.y = 30;

	m_PtGameMultiple.x = 60;
	m_PtGameMultiple.y = 25;

	m_PtRoomMultiple.x = 60;
	m_PtRoomMultiple.y = 55;

	m_PtCallScoreResult.x = 30;
	m_PtCallScoreResult.y = 30;

	m_PtCallScoreNT.x = 30;
	m_PtCallScoreNT.y = 50;

	m_PtGameTitle.x = 0;
	m_PtGameTitle.y = 0;

	m_PtLaiZhi.x    = 20;
	m_PtLaiZhi.y    = 22;
	//移动坐标
	int iMidLine = cx/2;			//x中间线
	int iBaseLine = cy/2;		    //y中间线
	m_PtDeskCue.x = iMidLine;
	m_PtDeskCue.y = iBaseLine;	

	//使用坐标
	LoadSkinIni(cx,cy);
	//计时器居中
	/*m_PtTime[0].x=iMidLine-TIME_WIDTH/2;
	m_PtTime[0].y=iBaseLine-TIME_HEIGHT/2;
	m_PtTime[2] = m_PtTime[1] = m_PtTime[0];*/

	POINT	spt;
	CGameImage img;
	TCHAR name[MAX_PATH];
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		int viewid = i;
		wsprintf(name,TEXT(".\\image\\%s\\usertalk%d.BMP"),GET_SKIN_FOLDER(szTempStr),viewid + 1); //囧
		img.SetLoadInfo(name,true);
		switch(viewid)
		{
		case 0://减去头像和消息框宽度
			//	spt.x = m_PtLogo[0].x - img.GetWidth();
			//	spt.y = m_PtLogo[0].y + LOGO_WIDTH+2;
			//	break;
			//case 1:
			spt.x = m_PtLogo[0].x - img.GetWidth();
			spt.y = m_PtLogo[0].y;
			break;
		case 1:
			{
				spt.x = m_PtLogo[1].x + LOGO_WIDTH;
				spt.y = m_PtLogo[1].y - img.GetHeight() + 30;
			}
			break;
		case 2:
			{
				spt.x = m_PtLogo[2].x + LOGO_WIDTH;
				spt.y = m_PtLogo[2].y;
			}
			break;
		default:
			break ;
		}
		CRect rectDisplay(spt.x,spt.y,spt.x+img.GetWidth(),spt.y+img.GetHeight());
//		m_dlgDisTalk[i].MoveWindow(&rectDisplay);
	}

	//移动一些固定坐标值
	MoveScreen(cx,cy);
	return;
}

//根据加载坐标移动
void CClientPlayView::MoveScreen(int cx,int cy)
{

	int iMidLine = cx/2;
	int iBaseLine = cy/2;
	int y_Card = 95;
	//移动扑克
	m_HandCard[0].SetBasePoint(CPoint(ptHandCard[0].x,ptHandCard[0].y),
		CUpGradeGameCard::XShowMode::SWX_MODE_RIGHT,CUpGradeGameCard::YShowMode::SWY_MODE_CENTER);
	m_HandCard[0].SetLookMode(false);
#ifdef MY_TWO
	m_ThreeCard.SetBasePoint(CPoint(80,iBaseLine-70),
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_CENTER);
	m_ThreeCard.SetLookMode(false);

	m_HandCard[0].SetLookMode(true);
#endif

	m_HandCard[1].SetBasePoint(CPoint(ptHandCard[1].x,ptHandCard[1].y),
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);
	m_HandCard[1].ShowWindow(SW_HIDE);

	m_HandCard[2].SetBasePoint(CPoint(ptHandCard[2].x,ptHandCard[2].y),
		CUpGradeGameCard::XShowMode::SWX_MODE_LEFT,CUpGradeGameCard::YShowMode::SWY_MODE_CENTER);
	m_HandCard[2].SetLookMode(false);

	//移动扑克
	m_UserCard[0].SetBasePoint(CPoint(ptCardPoint[0].x,ptCardPoint[0].y),
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_CENTER);
	m_UserCard[1].SetBasePoint(CPoint(ptCardPoint[1].x,ptCardPoint[1].y),
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_CENTER);
	m_UserCard[2].SetBasePoint(CPoint(ptCardPoint[2].x,ptCardPoint[2].y),
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_CENTER);

	m_MeCard.SetBasePoint(CPoint(ptHandCard[1].x,ptHandCard[1].y),
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

	//底牌位置
	m_MeBackCard.SetBasePoint(CPoint(ptBackCard.x,ptBackCard.y),								//底牌
		CUpGradeGameCard::XShowMode::SWX_MODE_CENTER,CUpGradeGameCard::YShowMode::SWY_MODE_TOP);

	//移动反牌视图
	CRect ContronRect;
	//移动信息视图
	m_GameNoteView.GetClientRect(&ContronRect);

	m_GameNoteView.MoveWindow(iMidLine-ContronRect.Width() / 2,iBaseLine-ContronRect.Height() / 2,
		ContronRect.Width(),ContronRect.Height(),FALSE);
	m_GameNoteView.AutoSize(iMidLine-ContronRect.Width() / 2,iBaseLine-ContronRect.Height() / 2);

	//移动信息视图
	m_Result.GetClientRect(&ContronRect);
	m_Result.AutoSize(iMidLine - ContronRect.Width() / 2,iBaseLine - ContronRect.Height() / 2 - 30);

//移动信息视图
	m_SelectLaiZhi.GetClientRect(&ContronRect);
	m_SelectLaiZhi.AutoSize(iMidLine - ContronRect.Width() / 2,iBaseLine - ContronRect.Height() / 2 - 30);

	//移动控件
	m_btOutCard.GetClientRect(&ContronRect);
	int btWidth = ContronRect.Width(),btHeight = ContronRect.Height();
	//出牌
	m_btOutCard.MoveWindow(iMidLine-2*ContronRect.Width(),m_Bt2HeightSpace-20,btWidth,btHeight);
	m_btPass.MoveWindow(iMidLine-ContronRect.Width()/2,m_Bt2HeightSpace-20,btWidth,btHeight);
	m_btCue.MoveWindow(iMidLine+ContronRect.Width(),m_Bt2HeightSpace-20,btWidth,btHeight);

	//叫分
	m_btCallScore1.GetClientRect(&ContronRect);
	btWidth = ContronRect.Width(),btHeight = ContronRect.Height();
	m_btCallScore1.MoveWindow(iMidLine-ContronRect.right*2 - 40,m_Bt2HeightSpace,btWidth,btHeight);
	m_btCallScore2.MoveWindow(iMidLine-ContronRect.right - 20,m_Bt2HeightSpace,btWidth,btHeight);
	m_btCallScore3.MoveWindow(iMidLine,m_Bt2HeightSpace,btWidth,btHeight);		
	m_btCallScorePass.MoveWindow(iMidLine+ContronRect.right + 20,m_Bt2HeightSpace,btWidth,btHeight);		

	//抢地主不抢地主
	m_btRobNT.MoveWindow(iMidLine-2*ContronRect.Width(),m_Bt2HeightSpace,btWidth,btHeight);
	m_btRobNT2.MoveWindow(iMidLine+ContronRect.Width(),m_Bt2HeightSpace,btWidth,btHeight);
	//加棒不加棒
	m_btAddDouble.MoveWindow(iMidLine-2*ContronRect.Width(),m_Bt2HeightSpace,btWidth,btHeight);
	m_btAddDouble2.MoveWindow(iMidLine+ContronRect.Width(),m_Bt2HeightSpace,btWidth,btHeight);
	//亮牌,不亮
	m_btShowCard.MoveWindow(iMidLine-2*ContronRect.Width(),m_Bt2HeightSpace,btWidth,btHeight);
	m_btShowCard2.MoveWindow(iMidLine+ContronRect.Width(),m_Bt2HeightSpace,btWidth,btHeight);
	//开始
	m_btContinue.GetClientRect(&ContronRect);
	//m_btContinue.MoveWindow(iMidLine - 110,m_Bt2HeightSpace,ContronRect.Width(),ContronRect.Height());
	//离开
	//m_btLeave.MoveWindow(iMidLine - 110+ ContronRect.Width() * 2 + 40,m_Bt2HeightSpace,ContronRect.Width(),ContronRect.Height());

	m_btContinue.MoveWindow(iMidLine+20, iBaseLine+150, ContronRect.Width(), ContronRect.Height());
	m_btLeave.MoveWindow(iMidLine-20-ContronRect.Width(), iBaseLine+150, ContronRect.Width(), ContronRect.Height());

	//明牌开始按钮
	//m_btStartDisplayCards.GetClientRect(&ContronRect);
	//m_btStartDisplayCards.MoveWindow(iMidLine -110 + ContronRect.Width() + 20 , m_Bt2HeightSpace, ContronRect.Width(), ContronRect.Height());

	//托管
	m_btAuto.GetClientRect(&ContronRect);
	m_btThing.MoveWindow(cx-ContronRect.Width() -m_Bt1WidthSpace,cy-(ContronRect.Height()+m_Bt1HeightSpace),ContronRect.Width(),ContronRect.Height());
	m_btSortCard.MoveWindow(cx-ContronRect.Width() -m_Bt1WidthSpace,cy-(ContronRect.Height()+m_Bt1HeightSpace)*2,ContronRect.Width(),ContronRect.Height());
	m_btAuto.MoveWindow(cx-ContronRect.Width() -m_Bt1WidthSpace,cy-(ContronRect.Height()+m_Bt1HeightSpace)*3,ContronRect.Width(),ContronRect.Height());
	m_btLastTurn.MoveWindow(cx-ContronRect.Width() -m_Bt1WidthSpace,cy-(ContronRect.Height()+m_Bt1HeightSpace)*4,ContronRect.Width(),ContronRect.Height());

	//改变积分榜,x坐标
	CRect rect;
	m_showcoredlg.GetClientRect(&rect);
	m_showcoredlg.SetWindowPos(NULL,iMidLine,-m_showcoredlg.m_showh,0,0,SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOSIZE);
	return ;
}

//根据游戏加载坐标
void CClientPlayView::LoadSkinIni(int cx,int cy)
{
#ifdef VIDEO
	//////////////////////////////////视频///////////////////////////
	///以下临时用下，以后移到脚本中或者动态语言中
	CString  strVideoCfg=CINIFile::GetAppPath()+TEXT("VideoCfg.ini");
	if(!CINIFile::IsFileExist(strVideoCfg))
	{

		AfxMessageBox("未找到视频配置文件: ");
		return  ;
	}
	CINIFile iniFile(strVideoCfg);
	int	 m_heightVideo=0,m_widthVideo=0;
	m_widthVideo
		=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("WidthVideo"), 160);
	m_heightVideo
		=iniFile.GetKeyVal(TEXT("VedioCfg"),TEXT("HeightVideo"), 152);
	//////////////////////////////////////////////////////////////////
#endif
	int iMidLine = cx/2;			//x中间线
	int iBaseLine = cy/2;		    //y中间线
	int x_Card = 70;				//牌宽
	int y_Card = 95;				//牌高

	
	CString s = CBcfFile::GetAppPath ();/////本地路径
	CBcfFile f( s +SKIN_FOLDER +".bcf");
	//CBcfFile f( s +"\\" + strTemp +".bcf");
	CString key;
#ifdef VIDEO
	key = TEXT("videoUISet");
#else
	key = TEXT("UISet");
#endif

	//1号位置
	//手中牌
	ptHandCard[0].x = cx - LOGO_WIDTH +f.GetKeyVal(key,TEXT("handcard0x"),-100);
	ptHandCard[0].y =iBaseLine + f.GetKeyVal(key,TEXT("handcard0y"), -y_Card/2);
	//桌面上牌
	ptCardPoint[0].x =3*iMidLine/2+f.GetKeyVal(key,TEXT("deskcard0x"),-x_Card)-20;
	ptCardPoint[0].y =iBaseLine + f.GetKeyVal(key,TEXT("deskcard0y"),- y_Card/2-20);
#ifdef VIDEO
	//头像
	m_PtLogo[0].x =cx-m_widthVideo + f.GetKeyVal(key,TEXT("logo0x"),-0);
	m_PtLogo[0].y =iBaseLine-m_heightVideo/2+ f.GetKeyVal(key,TEXT("logo0y"),-10);
	//头像显示区
	//	m_UserRect[0].SetRect(m_PtLogo[0].x,m_PtLogo[0].y,m_PtLogo[0].x+m_widthVideo,m_PtLogo[0].y+m_heightVideo);

	//计时器
	m_PtTime[0].x =m_PtLogo[0].x+ f.GetKeyVal(key,TEXT("time0x"),-35);
	m_PtTime[0].y =m_PtLogo[0].y+ f.GetKeyVal(key,TEXT("time0y"),5);
	//庄图标
	m_PtNt[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("nt0x"),50);
	m_PtNt[0].y =m_PtLogo[0].y+f.GetKeyVal(key,TEXT("nt0y"),-40);
	//托管
	m_PtAuto[0].x =m_PtLogo[0].x+ f.GetKeyVal(key,TEXT("auto0x"),0);
	m_PtAuto[0].y =m_PtLogo[0].y+ f.GetKeyVal(key,TEXT("auto0y"),-35);

	ptHandCard[0].x = cx - m_widthVideo +f.GetKeyVal(key,TEXT("handcard0x"),-5);
	ptHandCard[0].y =iBaseLine + f.GetKeyVal(key,TEXT("handcard0y"), -y_Card/2);

	//加棒位置
	m_PtPeopleMul[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("peopleMul0x"),100);;
	m_PtPeopleMul[0].y = m_PtLogo[0].y+f.GetKeyVal(key,TEXT("peopleMul0y"),-40);

	//奖分
	m_PtAwardPoint[0].x =m_PtLogo[0].x+ f.GetKeyVal(key,TEXT("awardpoint0x"),m_widthVideo-30);
	m_PtAwardPoint[0].y = m_PtLogo[0].y+m_heightVideo+f.GetKeyVal(key,TEXT("awardpoint0y"),0);

#else
	//头像
	m_PtLogo[0].x =cx-LOGO_WIDTH + f.GetKeyVal(key,TEXT("logo0x"),-33);
	m_PtLogo[0].y =iBaseLine-LOGO_HEIGHT/2+ f.GetKeyVal(key,TEXT("logo0y"),-28);
	//头像显示区
	//m_UserRect[0].SetRect(m_PtLogo[0].x,m_PtLogo[0].y,m_PtLogo[0].x+LOGO_WIDTH,m_PtLogo[0].y+LOGO_HEIGHT);

	//计时器
	m_PtTime[0].x =m_PtLogo[0].x+ f.GetKeyVal(key,TEXT("time0x"),-35);
	m_PtTime[0].y =m_PtLogo[0].y+ f.GetKeyVal(key,TEXT("time0y"),5);
	//庄图标
	m_PtNt[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("nt0x"),+30);
	m_PtNt[0].y =m_PtLogo[0].y+LOGO_HEIGHT +f.GetKeyVal(key,TEXT("nt0y"),+35);
	//托管
	m_PtAuto[0].x =m_PtLogo[0].x+ f.GetKeyVal(key,TEXT("auto0x"),-10);
	m_PtAuto[0].y =m_PtLogo[0].y+LOGO_HEIGHT+ f.GetKeyVal(key,TEXT("auto0y"),35);

	//加棒位置
	m_PtPeopleMul[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("peopleMul0x"),40);;
	m_PtPeopleMul[0].y = m_PtLogo[0].y+LOGO_HEIGHT+f.GetKeyVal(key,TEXT("peopleMul0y"),35);

	//奖分
	m_PtAwardPoint[0].x =m_PtLogo[0].x+f.GetKeyVal(key,TEXT("awardpoint0x"),-30);
	m_PtAwardPoint[0].y = m_PtLogo[0].y+f.GetKeyVal(key,TEXT("awardpoint0y"),-35);

#endif
	m_PtGif[0].x = m_PtLogo[0].x+f.GetKeyVal(key,TEXT("flower0x"),0);
	m_PtGif[0].y = m_PtLogo[0].y+f.GetKeyVal(key,TEXT("flower0y"),0);
	//昵称
	m_PtName[0].x =m_PtLogo[0].x+f.GetKeyVal(key,TEXT("name0x"),0);
	m_PtName[0].y =m_PtLogo[0].y+LOGO_HEIGHT+f.GetKeyVal(key,TEXT("name0y"),15);
	//举手
	m_PtAgree[0].x =m_PtLogo[0].x+ f.GetKeyVal(key,TEXT("agree0x"),-35);
	m_PtAgree[0].y =m_PtLogo[0].y+ f.GetKeyVal(key,TEXT("agree0y"),5);
	//过
	m_PtPass[0].x =ptCardPoint[0].x+ f.GetKeyVal(key,TEXT("pass0x"),-50);
	m_PtPass[0].y = ptCardPoint[0].y+f.GetKeyVal(key,TEXT("pass0y"),-30);
	//叫分
	m_PtCallScore[0].x = ptCardPoint[0].x+f.GetKeyVal(key,TEXT("CallScore0x"),-50);
	m_PtCallScore[0].y = ptCardPoint[0].y+f.GetKeyVal(key,TEXT("CallScore0y"),-30);
	//指示器方向
	m_PtCurOrientation[0].x = iMidLine+f.GetKeyVal(key,TEXT("Orientation0x"),15);
	m_PtCurOrientation[0].y = iBaseLine+f.GetKeyVal(key,TEXT("Orientation0y"),-20);
	//2号位置
	//手中牌
	ptHandCard[1].x =iMidLine+f.GetKeyVal(key,TEXT("handcard1x"),0);
	ptHandCard[1].y =cy+f.GetKeyVal(key,TEXT("handcard1y"),-y_Card-y_Card+45);
	//桌面上牌
	ptCardPoint[1].x =iMidLine+f.GetKeyVal(key,TEXT("deskcard1x"),0);
	ptCardPoint[1].y =cy+f.GetKeyVal(key,TEXT("deskcard1y"),-y_Card-y_Card-y_Card-y_Card/2+50);
#ifdef VIDEO
	//头像
	m_PtLogo[1].x = cx  - f.GetKeyVal(key,TEXT("logo1x"),cx );
	m_PtLogo[1].y = cy-m_heightVideo+f.GetKeyVal(key,TEXT("logo1y"),-30);
	//头像显示区
	//	m_UserRect[1].SetRect(m_PtLogo[1].x,m_PtLogo[1].y,m_PtLogo[1].x+m_widthVideo,m_PtLogo[1].y+m_heightVideo);
	//计时器
	m_PtTime[1].x =m_PtLogo[1].x+m_widthVideo+ f.GetKeyVal(key,TEXT("time1x"),-30);
	m_PtTime[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("time1y"),-30);
	//庄图标
	m_PtNt[1].x =m_PtLogo[1].x+ f.GetKeyVal(key,TEXT("nt1x"),50);
	m_PtNt[1].y =m_PtLogo[1].y+ f.GetKeyVal(key,TEXT("nt1y"),-40);
	//托管
	m_PtAuto[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("auto1x"),0);
	m_PtAuto[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("auto1y"),-35);

	//加棒位置
	m_PtPeopleMul[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("peopleMul1x"),100);
	m_PtPeopleMul[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("peopleMul1y"),-40);

	//奖分
	m_PtAwardPoint[1].x =m_PtLogo[1].x+ f.GetKeyVal(key,TEXT("awardpoint1x"),m_widthVideo-30);
	m_PtAwardPoint[1].y = m_PtLogo[1].y+m_heightVideo+f.GetKeyVal(key,TEXT("awardpoint1y"),0);

#else
	//头像
	m_PtLogo[1].x = iMidLine  - f.GetKeyVal(key,TEXT("logo1x"),280);
	m_PtLogo[1].y = cy-LOGO_HEIGHT+f.GetKeyVal(key,TEXT("logo1y"),-43);
	//头像显示区
	//m_UserRect[1].SetRect(m_PtLogo[1].x,m_PtLogo[1].y,m_PtLogo[1].x+LOGO_WIDTH,m_PtLogo[1].y+LOGO_HEIGHT);
	//计时器
	m_PtTime[1].x =m_PtLogo[1].x+LOGO_WIDTH+ f.GetKeyVal(key,TEXT("time1x"),10);
	m_PtTime[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("time1y"),15);
	//庄图标
	m_PtNt[1].x =m_PtLogo[1].x+ f.GetKeyVal(key,TEXT("nt1x"),-60);
	m_PtNt[1].y =m_PtLogo[1].y+ f.GetKeyVal(key,TEXT("nt1y"),20);
	//托管
	m_PtAuto[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("auto1x"),-60);
	m_PtAuto[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("auto1y"),70);

	//加棒位置
	m_PtPeopleMul[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("peopleMul1x"),-60);;
	m_PtPeopleMul[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("peopleMul1y"),20);;

	//奖分
	m_PtAwardPoint[1].x =m_PtLogo[1].x+ f.GetKeyVal(key,TEXT("awardpoint1x"),0);
	m_PtAwardPoint[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("awardpoint1y"),-35);

#endif

	m_PtGif[1].x = m_PtLogo[1].x+f.GetKeyVal(key,TEXT("flower1x"),0);
	m_PtGif[1].y = m_PtLogo[1].y+f.GetKeyVal(key,TEXT("flower1y"),0);
	//昵称
	m_PtName[1].x =m_PtLogo[1].x+f.GetKeyVal(key,TEXT("name1x"),0);
	m_PtName[1].y =m_PtLogo[1].y+LOGO_HEIGHT+f.GetKeyVal(key,TEXT("name1y"),10);
	//举手
	m_PtAgree[1].x =m_PtLogo[1].x+LOGO_WIDTH+ f.GetKeyVal(key,TEXT("agree1x"),10);
	m_PtAgree[1].y =m_PtLogo[1].y+ f.GetKeyVal(key,TEXT("agree1y"),5);
	//过
	m_PtPass[1].x =ptCardPoint[1].x+ f.GetKeyVal(key,TEXT("pass1x"),-30);
	m_PtPass[1].y =ptCardPoint[1].y+ f.GetKeyVal(key,TEXT("pass1y"),y_Card/2+50);
	//叫分
	m_PtCallScore[1].x = ptCardPoint[1].x+f.GetKeyVal(key,TEXT("CallScore1x"),-30);
	m_PtCallScore[1].y =ptCardPoint[1].y+ f.GetKeyVal(key,TEXT("CallScore1y"),y_Card/2+50);
	//指示器方向
	m_PtCurOrientation[1].x =iMidLine+ f.GetKeyVal(key,TEXT("Orientation1x"),-15);
	m_PtCurOrientation[1].y =iBaseLine + f.GetKeyVal(key,TEXT("Orientation1y"),5);


	//3号位置
	//手中牌
	ptHandCard[2].x =LOGO_WIDTH+f.GetKeyVal(key,TEXT("handcard2x"),80);
	ptHandCard[2].y =iBaseLine+f.GetKeyVal(key,TEXT("handcard2y"),-y_Card/2);
	//桌面上牌
	ptCardPoint[2].x =iMidLine/2+f.GetKeyVal(key,TEXT("deskcard2x"),x_Card);
	ptCardPoint[2].y =iBaseLine+f.GetKeyVal(key,TEXT("deskcard2y"),-y_Card/2-20);
#ifdef VIDEO
	//头像
	m_PtLogo[2].x = f.GetKeyVal(key,TEXT("logo2x"),0);
	m_PtLogo[2].y =iBaseLine-m_heightVideo/2+ f.GetKeyVal(key,TEXT("logo2y"),-10);
	//头像显示区
	//	m_UserRect[2].SetRect(m_PtLogo[2].x,m_PtLogo[2].y,m_PtLogo[2].x+m_widthVideo,m_PtLogo[2].y+m_heightVideo);
	//计时器
	m_PtTime[2].x =m_PtLogo[2].x+m_widthVideo+ f.GetKeyVal(key,TEXT("time2x"),-30);
	m_PtTime[2].y =m_PtLogo[2].y+ f.GetKeyVal(key,TEXT("time2y"),-30);
	//庄图标
	m_PtNt[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("nt2x"),50);
	m_PtNt[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("nt2y"),-40);
	//托管
	m_PtAuto[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("auto2x"),0);
	m_PtAuto[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("auto2y"),-35);

	//手中牌
	ptHandCard[2].x =m_widthVideo+f.GetKeyVal(key,TEXT("handcard2x"),5);
	ptHandCard[2].y =iBaseLine+f.GetKeyVal(key,TEXT("handcard2y"),-y_Card/2);
	//桌面上牌
	ptCardPoint[2].x =iMidLine/2+f.GetKeyVal(key,TEXT("deskcard2x"),x_Card);
	ptCardPoint[2].y =iBaseLine+f.GetKeyVal(key,TEXT("deskcard2y"),-y_Card/2-20);

	//加棒位置
	m_PtPeopleMul[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("peopleMul2x"),100);
	m_PtPeopleMul[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("peopleMul2y"),-40);

	//奖分
	m_PtAwardPoint[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("awardpoint2x"),m_widthVideo-30);
	m_PtAwardPoint[2].y = m_PtLogo[2].y+m_heightVideo-f.GetKeyVal(key,TEXT("awardpoint2y"),0);

#else
	//头像
	m_PtLogo[2].x = f.GetKeyVal(key,TEXT("logo2x"),28);
	m_PtLogo[2].y =iBaseLine-LOGO_WIDTH/2+ f.GetKeyVal(key,TEXT("logo2y"),-48);
	//头像显示区
	//m_UserRect[2].SetRect(m_PtLogo[2].x,m_PtLogo[2].y,m_PtLogo[2].x+LOGO_WIDTH,m_PtLogo[2].y+LOGO_HEIGHT);
	//计时器
	m_PtTime[2].x =m_PtLogo[2].x+LOGO_WIDTH+ f.GetKeyVal(key,TEXT("time2x"),10);
	m_PtTime[2].y =m_PtLogo[2].y+ f.GetKeyVal(key,TEXT("time2y"),5);
	//庄图标
	m_PtNt[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("nt2x"),40);
	m_PtNt[2].y = m_PtLogo[2].y+LOGO_HEIGHT+f.GetKeyVal(key,TEXT("nt2y"),35);
	//托管
	m_PtAuto[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("auto2x"),-10);
	m_PtAuto[2].y = m_PtLogo[2].y+LOGO_HEIGHT+f.GetKeyVal(key,TEXT("auto2y"),35);

	//加棒位置
	m_PtPeopleMul[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("peopleMul2x"),50);;
	m_PtPeopleMul[2].y = m_PtLogo[2].y+LOGO_HEIGHT+f.GetKeyVal(key,TEXT("peopleMul2y"),35);;

	//奖分
	m_PtAwardPoint[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("awardpoint2x"),10);
	m_PtAwardPoint[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("awardpoint2y"),-35);

#endif

	m_PtGif[2].x = m_PtLogo[2].x+f.GetKeyVal(key,TEXT("flower2x"),0);
	m_PtGif[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("flower2y"),0);
	//昵称
	m_PtName[2].x =m_PtLogo[2].x+f.GetKeyVal(key,TEXT("name2x"),0);
	m_PtName[2].y =m_PtLogo[2].y+LOGO_HEIGHT+f.GetKeyVal(key,TEXT("name2y"),15);
	//举手
	m_PtAgree[2].x =m_PtLogo[2].x+LOGO_WIDTH+ f.GetKeyVal(key,TEXT("agree2x"),10);
	m_PtAgree[2].y = m_PtLogo[2].y+f.GetKeyVal(key,TEXT("agree2y"),5);
	//过
	m_PtPass[2].x = ptCardPoint[2].x+f.GetKeyVal(key,TEXT("pass2x"),-20);
	m_PtPass[2].y =m_PtLogo[2].y+ f.GetKeyVal(key,TEXT("pass2y"),-30);
	//叫分
	m_PtCallScore[2].x =  ptCardPoint[2].x+f.GetKeyVal(key,TEXT("CallScore2x"),-20);
	m_PtCallScore[2].y =  ptCardPoint[2].y+f.GetKeyVal(key,TEXT("CallScore2y"),-30);
	//指示器方向
	m_PtCurOrientation[2].x =iMidLine+ f.GetKeyVal(key,TEXT("Orientation2x"),-45);
	m_PtCurOrientation[2].y =iBaseLine+ f.GetKeyVal(key,TEXT("Orientation2y"),-20);

	//底牌
	ptBackCard.x=iMidLine+ f.GetKeyVal(key,TEXT("backcardx"),0);
	ptBackCard.y=f.GetKeyVal(key,TEXT("backcardy"),40);
	//底分提示
	m_PtBottomCue.x = iMidLine+ f.GetKeyVal(key,TEXT("bottonx"),0);
	m_PtBottomCue.y = cy+f.GetKeyVal(key,TEXT("bottony"),-10);
	//右边按钮级
	m_Bt1WidthSpace=f.GetKeyVal(key,TEXT("WidthSpace1"),10);
	m_Bt1HeightSpace=f.GetKeyVal(key,TEXT("HeightSpace1"),10);
	//叫分按钮级
	m_Bt2WidthSpace=f.GetKeyVal(key,TEXT("WidthSpace2"),10);
	m_Bt2HeightSpace=iBaseLine+f.GetKeyVal(key,TEXT("HeightSpace2"),3*y_Card/2-20+30);
	//
	m_PtShowMsg.x = f.GetKeyVal(key,TEXT("showmsgx"),30);
	m_PtShowMsg.y = f.GetKeyVal(key,TEXT("showmsgy"),80);

	//小炸弹
	m_PtSBomb[0].x = 60;	
	m_PtSBomb[0].y = -100;	
	m_PtSBomb[1].x = 0;	
	m_PtSBomb[1].y = 120;	
	m_PtSBomb[2].x = -60;	
	m_PtSBomb[2].y = -100;	

#ifdef VIDEO
	m_PtLogo[0].x = cx - m_widthVideo- 2;
	m_PtLogo[0].y = iBaseLine - m_heightVideo/2 - 32;
	m_PtLogo[1].x = 2;
	m_PtLogo[1].y = cy - m_heightVideo - 30;
	m_PtLogo[2].x = 2;
	m_PtLogo[2].y = iBaseLine - m_heightVideo/2 - 32;
	//视频的坐标出
	m_rectVideoFrame[2].top=m_PtLogo[2].y;// cy-m_heightVideo;
	m_rectVideoFrame[2].left=m_PtLogo[2].x;//10;
	m_rectVideoFrame[2].bottom=m_rectVideoFrame[2].top+m_heightVideo;
	m_rectVideoFrame[2].right=m_rectVideoFrame[2].left+m_widthVideo;
	m_rectVideoFrame[3].top=m_PtLogo[3].y;//249;
	m_rectVideoFrame[3].left=m_PtLogo[3].x;//10;
	m_rectVideoFrame[3].bottom=m_rectVideoFrame[3].top+m_heightVideo;
	m_rectVideoFrame[3].right=m_rectVideoFrame[3].left+m_widthVideo;

	m_rectVideoFrame[0].top=m_PtLogo[0].y;//0;
	m_rectVideoFrame[0].left=m_PtLogo[0].x;//220;
	m_rectVideoFrame[0].bottom=m_rectVideoFrame[0].top+m_heightVideo;
	m_rectVideoFrame[0].right=m_rectVideoFrame[0].left+m_widthVideo;
	m_rectVideoFrame[1].top=m_PtLogo[1].y;//242;
	m_rectVideoFrame[1].left=m_PtLogo[1].x;//cx-m_widthVideo+5;
	m_rectVideoFrame[1].bottom=m_rectVideoFrame[1].top+m_heightVideo;
	m_rectVideoFrame[1].right=m_rectVideoFrame[1].left+m_widthVideo; 

	m_PtAgree[0].x = m_PtLogo[0].x + 0;
	m_PtAgree[0].y = m_PtLogo[0].y + - 13 - 2;
	m_PtAgree[1].x = m_PtLogo[1].x + m_widthVideo - 13;
	m_PtAgree[1].y = m_PtLogo[1].y + - 13 - 2;
	m_PtAgree[2].x = m_PtLogo[2].x + m_widthVideo - 13;
	m_PtAgree[2].y = m_PtLogo[2].y + - 13 - 2;

	m_PtAuto[0].x = m_PtLogo[0].x + m_widthVideo - 35;
	m_PtAuto[0].y = m_PtLogo[0].y + - 35 - 2;
	m_PtAuto[1].x = m_PtLogo[1].x + 0;
	m_PtAuto[1].y = m_PtLogo[1].y + - 35 - 2;
	m_PtAuto[2].x = m_PtLogo[2].x + 0;
	m_PtAuto[2].y = m_PtLogo[2].y + - 35 - 2;

	m_PtNt[0].x = m_PtLogo[0].x + (m_widthVideo-45)/2;
	m_PtNt[0].y = m_PtLogo[0].y + - 35 - 2;
	m_PtNt[1].x = m_PtLogo[1].x + (m_widthVideo-45)/2;
	m_PtNt[1].y = m_PtLogo[1].y + - 35 - 2;
	m_PtNt[2].x = m_PtLogo[2].x + (m_widthVideo-45)/2;
	m_PtNt[2].y = m_PtLogo[2].y + - 35 - 2;

	m_PtName[0].x = m_PtLogo[0].x + (m_widthVideo-LOGO_WIDTH)/2;
	m_PtName[0].y = m_PtLogo[0].y + 4;
	m_PtName[1].x = m_PtLogo[1].x + (m_widthVideo-LOGO_WIDTH)/2;
	m_PtName[1].y = m_PtLogo[1].y + 4;
	m_PtName[2].x = m_PtLogo[2].x + (m_widthVideo-LOGO_WIDTH)/2;
	m_PtName[2].y = m_PtLogo[2].y + 4;

	m_PtTime[0].x = m_PtLogo[0].x + 0;
	m_PtTime[0].y = m_PtLogo[0].y + - 21 - 2;
	m_PtTime[1].x = m_PtLogo[1].x + m_widthVideo - 30;
	m_PtTime[1].y = m_PtLogo[1].y + - 21 -2;
	m_PtTime[2].x = m_PtLogo[2].x + m_widthVideo - 30;
	m_PtTime[2].y = m_PtLogo[2].y + - 21 - 2;

	m_PtAwardPoint[0].x = m_PtLogo[0].x + 0;
	m_PtAwardPoint[0].y = m_PtLogo[0].y + m_heightVideo;
	m_PtAwardPoint[1].x = m_PtLogo[1].x + 0;
	m_PtAwardPoint[1].y = m_PtLogo[1].y + m_heightVideo;
	m_PtAwardPoint[2].x = m_PtLogo[2].x + 0;
	m_PtAwardPoint[2].y = m_PtLogo[2].y + m_heightVideo;

	//ptCardPoint[0].x = m_PtLogo[0].x + 0;
	ptCardPoint[0].y = m_PtLogo[0].y + m_heightVideo/2 - 11;
	//ptCardPoint[1].x = m_PtLogo[1].x + 0;
	ptCardPoint[1].y += 20;
	//ptCardPoint[2].x = m_PtLogo[2].x + 0;
	ptCardPoint[2].y = m_PtLogo[2].y + m_heightVideo/2 - 11;

	m_PtPass[0].x = ptCardPoint[0].x + -5;
	m_PtPass[0].y = ptCardPoint[0].y + 0;
	m_PtPass[1].x = ptCardPoint[1].x + 0;
	m_PtPass[1].y = ptCardPoint[1].y + 5;
	m_PtPass[2].x = ptCardPoint[2].x + 5;
	m_PtPass[2].y = ptCardPoint[2].y + 0;
	for (int i = 0; i < PLAY_COUNT; i++)
	{
		m_PtPass[i].x -= 30;
		m_PtPass[i].y -= 15;
	}

	m_PtGif[0].x = m_PtLogo[0].x + 0;
	m_PtGif[0].y = m_PtLogo[0].y + -120;
	m_PtGif[1].x = m_PtLogo[1].x + m_widthVideo;
	m_PtGif[1].y = m_PtLogo[1].y + -50;
	m_PtGif[2].x = m_PtLogo[2].x + 0;
	m_PtGif[2].y = m_PtLogo[2].y + -120;
	
	///设置视频窗口位置
	if(NULL!=CPlayVideo::CreatePlayVideo())
	{
		CPlayVideo::CreatePlayVideo()->SetUserPos();  
	}

	/////////////////////////////////////////////////////////////
#else
	//此处重算举手位置 托管位置 
	m_PtAgree[0].x = m_PtLogo[0].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("agree0x"),-25);
	m_PtAgree[0].y = m_PtLogo[0].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("agree0y"),-63);
	m_PtAgree[1].x = m_PtLogo[1].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("agree1x"),-25);
	m_PtAgree[1].y = m_PtLogo[1].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("agree1y"),-63);
	m_PtAgree[2].x = m_PtLogo[2].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("agree2x"),-25);
	m_PtAgree[2].y = m_PtLogo[2].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("agree2y"),-63);

	m_PtAuto[0].x = m_PtLogo[0].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("auto0x"),25);
	m_PtAuto[0].y = m_PtLogo[0].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("auto0y"),-m_AutoLogo.GetHeight()+50);
	m_PtAuto[1].x = m_PtLogo[1].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("auto1x"),25);
	m_PtAuto[1].y = m_PtLogo[1].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("auto1y"),-m_AutoLogo.GetHeight()+50);
	m_PtAuto[2].x = m_PtLogo[2].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("auto2x"),25);
	m_PtAuto[2].y = m_PtLogo[2].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("auto2y"),-m_AutoLogo.GetHeight()+50);

	//m_PtAwardPoint[0].x = m_PtLogo[0].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("awardpoint0x"),m_AutoLogo.GetWidth()+3);
	//m_PtAwardPoint[0].y = m_PtLogo[0].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("awardpoint0y"),-m_AwardPint.GetHeight());
	//m_PtAwardPoint[1].x = m_PtLogo[1].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("awardpoint1x"),m_AutoLogo.GetWidth()+3);
	//m_PtAwardPoint[1].y = m_PtLogo[1].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("awardpoint1y"),-m_AwardPint.GetHeight());
	//m_PtAwardPoint[2].x = m_PtLogo[2].x -(m_iUserFrame.GetWidth() - LOGO_WIDTH)/2 + f.GetKeyVal(key,_T("awardpoint2x"),m_AutoLogo.GetWidth()+3);
	//m_PtAwardPoint[2].y = m_PtLogo[2].y - (m_iUserFrame.GetHeight() - LOGO_HEIGHT)/2 + f.GetKeyVal(key,_T("awardpoint2y"),-m_AwardPint.GetHeight());

	m_PtGif[0].x = m_PtLogo[0].x+f.GetKeyVal(key, _T("flower0x"), -15);
	m_PtGif[0].y = m_PtLogo[0].y+f.GetKeyVal(key, _T("flower0y"), 126);
	m_PtGif[1].x = m_PtLogo[1].x+f.GetKeyVal(key, _T("flower1x"), -121);
	m_PtGif[1].y = m_PtLogo[1].y+f.GetKeyVal(key, _T("flower1y"), 0);
	m_PtGif[2].x = m_PtLogo[2].x+f.GetKeyVal(key, _T("flower2x"), 0);
	m_PtGif[2].y = m_PtLogo[2].y+f.GetKeyVal(key, _T("flower2y"), 126);
#endif
}


//开始按钮
void CClientPlayView::OnHitBegin()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_BEGIN,0,0);
	return;
}

//明牌开始按钮
void CClientPlayView::OnHitBeginDisplayCards()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_BEGINDISPLAY,0,0);
	return;
}


//离开按钮
void CClientPlayView::OnHitLeave()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(WM_CLOSE,0,0);
	return;
}
//出牌按钮
void CClientPlayView::OnHitOutCard()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_OUT_CARD,1,1);
	return;
}

//继续按钮
void CClientPlayView::OnHitContinue()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_BEGIN,0,0);
	return;
}


//有事要走
void CClientPlayView::OnHitThing()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_HAVE_THING,0,0);
	return;
}



//重置界面函数
void CClientPlayView::ResetGameView()
{
	CUsingSkinClass::ResetGameView();

	return;
}

//绘画 NT 标志
void CClientPlayView::DrawNt(CDC * pDC, int x, int y)
{
	CGameImageHelper	nt(&m_NT);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(nt);
	::TransparentBlt(pDC->GetSafeHdc(),x,y,nt.GetWidth(),nt.GetHeight(),dc.GetSafeHdc(),0,0,nt.GetWidth(),nt.GetHeight(),dc.GetPixel(0,0));
	dc.DeleteDC();
	return;
}

//绘画农民标志
void CClientPlayView::DrawFarmer(CDC * pDC, int x, int y)
{
	CGameImageHelper	nt(&m_NT2);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(nt);
	::TransparentBlt(pDC->GetSafeHdc(),x,y,nt.GetWidth(),nt.GetHeight(),dc.GetSafeHdc(),0,0,nt.GetWidth(),nt.GetHeight(),dc.GetPixel(0,0));
	dc.DeleteDC();
	return;
}


//设置庄家的位置
void CClientPlayView::SetNTStation(int iViewStation)
{
	m_iNtStation = iViewStation;
	UpdateViewFace(NULL);
	return;
}



//设置背景色
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

/*******************************************************************************************************/

void CClientPlayView::DrawFen(CDC * pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	TCHAR path[MAX_PATH];
	for(int i = 0 ; i < PLAY_COUNT; i ++)
	{
		if(m_iCallScore[i]==-1||m_iCallScore[i]==255 || m_iCallScore[i] == 30)
			continue;
		else
		{
		
			switch(m_iCallScore[i])
			{
				
			case 0:
				wsprintf(path,TEXT(".\\image\\%s\\jiaofen2_pass.bmp"),GET_SKIN_FOLDER(szTempStr));// 囧
				break;
			case 10:
				wsprintf(path,TEXT(".\\image\\%s\\jiaofen1.bmp"),GET_SKIN_FOLDER(szTempStr)); // 囧
				break;
			case 20:
				wsprintf(path,TEXT(".\\image\\%s\\jiaofen2.bmp"),GET_SKIN_FOLDER(szTempStr)); // 囧
				break;
			default:
				break;
			}
		}
		m_CallScore.SetLoadInfo(path,true);						//游戏logo标志
		CGameImageHelper	help(&m_CallScore);
		dc.SelectObject(help);
		/*	if (m_iCallScore[i]!=0)
		::TransparentBlt(pDC->GetSafeHdc(),m_PtCallScore[i].x,m_PtCallScore[i].y,help.GetWidth()/4,help.GetHeight(),dc.GetSafeHdc(),0,0,m_CallScore.GetWidth()/4,m_CallScore.GetHeight(),dc.GetPixel(0,0));
		else*/
		::TransparentBlt(pDC->GetSafeHdc(),m_PtCallScore[i].x,m_PtCallScore[i].y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,m_CallScore.GetWidth(),m_CallScore.GetHeight(),dc.GetPixel(0,0));

	}
	dc.DeleteDC();
	return ;
}

void CClientPlayView::OnCue(void)		//提示
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_CUE,0,0);
	return;
}

void CClientPlayView::OnHitAuto(void)		//托管
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_AUTOCARD,0,0);
	return;
}
//设置各家叫分
void CClientPlayView::SetCallScoreValue(BYTE bViewStation, int iCallScore)
{
	m_iCallScore[bViewStation] = iCallScore;

	UpdateViewFace(NULL);
}

//設置叫分結果
void CClientPlayView::SetCallScoreResult(int iCardCount)	//叫分结果
{
	m_iCallScoreResult=iCardCount;

	UpdateViewFace(NULL);
}

//不出
void CClientPlayView::OnHitPass()		//200
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_PASS,1,1);
	return;
}
void CClientPlayView::OnHitSort()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_SORT,1,1);
	return;
}

void CClientPlayView::OnHitCallScore(UINT uID)		
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_CALL_SCORE,(uID - IDC_CALL_SCORE_PASS)*10,(uID -IDC_CALL_SCORE_PASS)*10);
	return;
}

//抢地主，加棒
void CClientPlayView::OnHitRobNT()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_ROB_NT,1,1);
	return;
}

//抢地主，加棒
void CClientPlayView::OnHitRobNT2()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_ROB_NT,0,0);
	return;
}

//抢地主，加棒
void CClientPlayView::OnHitAddDouble()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_ADD_DOUBLE,1,1);
	return;
}
//抢地主，加棒
void CClientPlayView::OnHitAddDouble2()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_ADD_DOUBLE,0,0);
	return;
}

//抢地主，亮牌
void CClientPlayView::OnHitShowCard()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_SHOW_CARD,1,1);
	return;
}

//抢地主，不亮
void CClientPlayView::OnHitShowCard2()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_SHOW_CARD,0,0);
	return;
}

//上一轮
void CClientPlayView::OnHitLastTurn()
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_LOOK_LAST,0,0);
	return;
}

//設置托管
void CClientPlayView::SetAuto(int bDeskStation,bool Trusteeship)
{
	m_bAuto[bDeskStation]=Trusteeship;
	CRect rect;
	rect.SetRect(m_PtAuto[bDeskStation].x,m_PtAuto[bDeskStation].y,m_PtAuto[bDeskStation].x+35,m_PtAuto[bDeskStation].y+35);
	UpdateViewFace(rect);	

	TCHAR szName[200];
	if(1 == bDeskStation)
	{
		if(m_bAuto[bDeskStation] )
			wsprintf(szName,TEXT(".\\image\\%s\\auto_less.bmp"),GET_SKIN_FOLDER(szTempStr));			
		else
			wsprintf(szName,TEXT(".\\image\\%s\\auto_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			
		m_btAuto.LoadButtonBitmap(szName,false);	
	}
}

//绘制托管
BOOL CClientPlayView::DrawAuto(CDC * pDC)
{
	CGameImageHelper	AutoLogo(&m_AutoLogo);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(AutoLogo);
	for(int i = 0;i < PLAY_COUNT;i++)
	{
		if(m_bAuto[i])
			::TransparentBlt(pDC->GetSafeHdc(),m_PtAuto[i].x,m_PtAuto[i].y,AutoLogo.GetWidth(),AutoLogo.GetHeight(),dc.GetSafeHdc(),0,0,AutoLogo.GetWidth(),AutoLogo.GetHeight(),dc.GetPixel(0,0));
	}
	dc.DeleteDC();
	return true;
}

//鼠标消息
void CClientPlayView::OnLButtonUp(UINT nFlags, CPoint Point)
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	//	p->SendMessage(IDM_OUT_CARD,0,0);
}

//鼠标消息
void CClientPlayView::OnRButtonUp(UINT nFlags, CPoint Point)
{
	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	p->SendMessage(IDM_OUT_CARD,1,1);
}

//设置奖分情况
void CClientPlayView::SetAwardPoint(BYTE bDeskStation,BYTE iAwardPoint)
{
	m_iAwardPoint[bDeskStation] = iAwardPoint;
	UpdateViewFace(NULL);
}

//绘制奖分
void CClientPlayView::DrawAwardPoint(CDC * pDC)
{
	TCHAR szName[MAX_PATH];

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	
	for(int k= 0;k < PLAY_COUNT;k ++)
	{
		if(m_iAwardPoint[k] == 0 )
			continue;
		BYTE temp = m_iAwardPoint[k];
		for(int i = 0; i < temp; i ++)
		{
			if(temp >= 10)
			{
				temp -= 9;
				wsprintf(szName,TEXT(".\\image\\%s\\AwardPoint3.bmp"),GET_SKIN_FOLDER(szTempStr)); // 囧
				m_AwardPint.SetLoadInfo(szName,true);
			}
			else if(temp >= 5)
			{
				temp -= 4;
				wsprintf(szName,TEXT(".\\image\\%s\\AwardPoint2.bmp"),GET_SKIN_FOLDER(szTempStr)); // 囧 
				m_AwardPint.SetLoadInfo(szName,true);
			}
			else
			{	
				wsprintf(szName,TEXT(".\\image\\%s\\AwardPoint.bmp"),GET_SKIN_FOLDER(szTempStr)); // 囧
				m_AwardPint.SetLoadInfo(szName,true);
			}
			CGameImageHelper	AwardPint(&m_AwardPint);
			dc.SelectObject(AwardPint);
			if (1==k)
			{
				::TransparentBlt(pDC->GetSafeHdc(),m_PtAwardPoint[k].x+i*30,m_PtAwardPoint[k].y+10,AwardPint.GetWidth(),AwardPint.GetHeight(),dc.GetSafeHdc(),0,0,AwardPint.GetWidth(),AwardPint.GetHeight(),dc.GetPixel(0,0));
			}
			else
			{
				::TransparentBlt(pDC->GetSafeHdc(),m_PtAwardPoint[k].x,m_PtAwardPoint[k].y+i*30,AwardPint.GetWidth(),AwardPint.GetHeight(),dc.GetSafeHdc(),0,0,AwardPint.GetWidth(),AwardPint.GetHeight(),dc.GetPixel(0,0));
			}
			
		}
	}
	dc.DeleteDC();
	return;
}

//设置不出
void CClientPlayView::SetPass(BYTE iViewStation,int iGiveup)
{
	m_iPass[iViewStation]=iGiveup;
	UpdateViewFace(NULL);
	return ;
}

//绘制过
void CClientPlayView::DrawPass(CDC *pDC)
{
	CGameImageHelper	AutoLogo(&m_Pass);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(AutoLogo);
	for(int i=0;i < PLAY_COUNT;i++)
	{
		if(m_iPass[i] != 0)
			::TransparentBlt(pDC->GetSafeHdc(),m_PtPass[i].x,m_PtPass[i].y,AutoLogo.GetWidth(),AutoLogo.GetHeight(),dc.GetSafeHdc(),0,0,m_Pass.GetWidth(),m_Pass.GetHeight(),dc.GetPixel(0,0));
	}
	dc.DeleteDC();
	return ;
}


//聊天框
void CClientPlayView::DisplayTalkMsg(int Viewstation,TCHAR * szCharString)
{ 
//	m_dlgDisTalk[Viewstation].DisplayTalkText(szCharString);
}

//提示文字
BOOL CClientPlayView::PreTranslateMessage(MSG * pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	return __super::PreTranslateMessage(pMsg);
}

//设置方向
void CClientPlayView::SetOrientation(BYTE bDeskStation)
{
	m_iCurOrientation = bDeskStation ;

	UpdateViewFace(NULL);
	return ;
}

//绘制方向
BOOL CClientPlayView::DrawOrientation(CDC *pDC)
{
	if(m_iCurOrientation >= 0 && m_iCurOrientation < PLAY_COUNT)	//指示现在出牌人
	{
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		CGameImageHelper img(&m_ImgFangXiang);
		dc.SelectObject(img);
#ifdef MY_TWO
		TransparentBlt(pDC->GetSafeHdc(),m_PtCurOrientation[m_iCurOrientation].x,m_PtCurOrientation[m_iCurOrientation].y,
			img.GetWidth()/8,img.GetHeight(),dc.GetSafeHdc(),(m_iCurOrientation*2 )*img.GetWidth()/8,0,
			img.GetWidth()/8,img.GetHeight(),RGB(255,0,255));
#else

		TransparentBlt(pDC->GetSafeHdc(),m_PtCurOrientation[m_iCurOrientation].x,m_PtCurOrientation[m_iCurOrientation].y,
			img.GetWidth()/8,img.GetHeight(),dc.GetSafeHdc(),(m_iCurOrientation + 1)*img.GetWidth()/8,0,
			img.GetWidth()/8,img.GetHeight(),RGB(255,0,255));
#endif
		dc.DeleteDC();
	}
	return TRUE;
}

//聊天框初始化
void CClientPlayView::Init()
{
	//隐藏窗口
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
//		m_dlgDisTalk[i].ShowWindow(SW_HIDE);             //创建后隐藏
	}
}

//設置基礎分顯示
BOOL CClientPlayView::SetRoomMultiple(int iRoomMultiple)
{
	m_iRoomMultiple=iRoomMultiple;

	UpdateViewFace(NULL);
	return true;
}

//繪製房间倍数
BOOL CClientPlayView::DrawRoomMultiple(CDC *pDC)
{
	CFont Font,*OldFont;
	TCHAR szMsg[50];
	Font.CreateFont(16,9,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->SetBkMode(TRANSPARENT);
	OldFont=pDC->SelectObject(&Font);

	CRect rect;
	SetRect(&rect,m_PtLaiZhi.x + 160,m_PtLaiZhi.y+31,m_PtLaiZhi.x+210,m_PtLaiZhi.y+47);

	wsprintf(szMsg,TEXT(" %d "),m_iRoomMultiple * m_iGameMultiple);
	//wsprintf(szMsg,TEXT(" %d "),m_iGameMultiple);
	pDC->DrawText(szMsg,lstrlen(szMsg),rect,DT_CENTER);
	DeleteObject(pDC->SelectObject(OldFont));
	return true;
}

//设置游戏倍数
BOOL CClientPlayView::SetGameMultiple(int iGameMultiple)
{
	m_iGameMultiple = iGameMultiple;
	UpdateViewFace(NULL);
	return true;
}

//繪製房间分(没用到)
BOOL CClientPlayView::DrawGameMultiple(CDC *pDC)
{
	if(m_iGameMultiple == 0)
		return true;
	CFont Font,*OldFont;
	TCHAR szMsg[50];
	Font.CreateFont(12,9,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->SetBkMode(TRANSPARENT);
	OldFont=pDC->SelectObject(&Font);

	CRect rect;
	SetRect(&rect,m_PtGameMultiple.x,m_PtGameMultiple.y,m_PtGameMultiple.x+60,m_PtGameMultiple.y+19);

	wsprintf(szMsg,TEXT(" %d "),m_iGameMultiple);
	pDC->DrawText(szMsg,lstrlen(szMsg),rect,DT_CENTER);
	DeleteObject(pDC->SelectObject(OldFont));
	return true;
}
//繪製房间底分
BOOL CClientPlayView::DrawCallScoreResult(CDC *pDC)
{
	if(m_iCallScoreResult <= 0 || m_iCallScoreResult >30)
		return true;
	CFont Font,*OldFont;
	TCHAR szMsg[50];
	Font.CreateFont(16,9,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->SetBkMode(TRANSPARENT);
	OldFont=pDC->SelectObject(&Font);

	CRect rect;
	SetRect(&rect,m_PtLaiZhi.x+160,m_PtLaiZhi.y+6,m_PtLaiZhi.x+210,m_PtLaiZhi.y+22);

	wsprintf(szMsg,TEXT(" %d "),m_iCallScoreResult);
	pDC->DrawText(szMsg,lstrlen(szMsg),rect,DT_CENTER);
	DeleteObject(pDC->SelectObject(OldFont));
	return true;
}

//設置桌面倍数
BOOL CClientPlayView::SetDeskMultiple(int iDeskMultiple)
{
	m_iDeskMultiple = iDeskMultiple;
	CRect rect;
	rect.SetRect(m_PtDeskMultiple.x,m_PtDeskMultiple.y,m_PtDeskMultiple.x+120,m_PtDeskMultiple.y+20);
	UpdateViewFace(rect);	

	return true;
}

//繪製桌面基礎分
BOOL CClientPlayView::DrawDeskMultiple(CDC *pDC)
{
	if(m_iDeskMultiple == 0)
		return true;
	CFont Font,*OldFont;
	TCHAR szMsg[50];
	Font.CreateFont(12,9,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->SetBkMode(TRANSPARENT);
	OldFont=pDC->SelectObject(&Font);

	wsprintf(szMsg,TEXT("台主设置: %d 倍"),m_iDeskMultiple);

	pDC->TextOutA(m_PtDeskMultiple.x,m_PtDeskMultiple.y,szMsg,lstrlen(szMsg));
	DeleteObject(pDC->SelectObject(OldFont));
	return true;
}

//设置玩家倍数
void CClientPlayView::SetPeopleMultiple(BYTE bViewStation,int iVal)
{
	m_iPeopleMul[bViewStation] = iVal;
	UpdateViewFace(NULL);	
	return ;
}

//绘制玩家倍数
void CClientPlayView::DrawPeopleMultiple(CDC *pDC)
{
	CGameImageHelper	help(&m_PeopleMul);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(help);
	for(int i = 0;i< PLAY_COUNT;i++)
	{
		if(m_iPeopleMul[i] == 2)
			::TransparentBlt(pDC->GetSafeHdc(),m_PtPeopleMul[i].x,m_PtPeopleMul[i].y,help.GetWidth(),help.GetHeight(),dc.GetSafeHdc(),0,0,help.GetWidth(),help.GetHeight(),dc.GetPixel(0,0));
	}
	dc.DeleteDC();
	return ;
}

//绘制玩家叫分结果和倍率背景图
void CClientPlayView::DrawShowMsg(CDC *pDC)
{
	CGameImageHelper help(&m_ShowMsg);
	help.BitBlt(pDC->GetSafeHdc(),m_PtShowMsg.x,m_PtShowMsg.y);	
	return ;
}
//设置赖子
void CClientPlayView::SetLai(BYTE iCard)
{
	int LaiCard = 0;
	if (iCard == 0x4e || iCard ==0x4f)
	{
		LaiCard = 3;

	}
	else if (((iCard&UG_VALUE_MASK)+1) == 14)
	{
		LaiCard = 2;
	}
	else
	{
		LaiCard = ((iCard&UG_VALUE_MASK)+1) + 1;
	}
	if (iCard == 255)
	{
		memset(m_bLaiCardList, 0, sizeof(m_bLaiCardList));
	}
	else
	{
		m_bLaiCardList[0] = (LaiCard - 1) | UG_FANG_KUAI;
		m_bLaiCardList[1] = (LaiCard - 1) | UG_MEI_HUA;
		m_bLaiCardList[2] = (LaiCard - 1) | UG_HONG_TAO;
		m_bLaiCardList[3] = (LaiCard - 1) | UG_HEI_TAO;
	}
	CRect rect;
	rect.SetRect(m_PtDeskMultiple.x,m_PtDeskMultiple.y,m_PtDeskMultiple.x+120,m_PtDeskMultiple.y+20);
	UpdateViewFace(rect);
}
//绘制赖子
void CClientPlayView::DrawLai(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CGameImageHelper   help(&m_ImgSmlLaiz);
	CGameImageHelper   help1(&m_LaiZhi);
	dc.SelectObject(help1);
 	::TransparentBlt(pDC->GetSafeHdc(),m_PtLaiZhi.x,m_PtLaiZhi.y,help1.GetWidth(),help1.GetHeight(),dc.GetSafeHdc(),0,0,help1.GetWidth(),help1.GetHeight(),RGB(255,0,255));
	
	if (m_bLaiCardList[0] !=0 && m_bLaiCardList[0]!= 255)
	{
		for (BYTE i=0;i<2;i++)
		{
			m_ImgSmlLaiz.BitBlt(pDC->GetSafeHdc(), m_PtLaiZhi.x+59+i*12, m_PtLaiZhi.y+5,32,41, GetCardXPos(m_bLaiCardList[i])*32, GetCardYPos(m_bLaiCardList[i])*41, SRCCOPY);
		}
	}
	dc.DeleteDC();
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
///20100105 添加双击鼠标将牌收起 zht
void CClientPlayView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	if (NULL != p)
	{
		m_MeCard.SetCard(p->m_iMeCardList,NULL,p->m_iMeCardCount);
	}
	CUsingSkinClass::OnLButtonDblClk(nFlags, point);
}
