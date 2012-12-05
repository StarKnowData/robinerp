#include "StdAfx.h"	
#include "ClientGameDlg.h"
#include "GameSet.h"
#include "playcardsound.h"
#include ".\clientgamedlg.h"

static void Msg(const char *lpszFormat, ...)
{
	va_list pArg;
	va_start(pArg, lpszFormat);
	char szMessage[1024] = { 0 };
#ifdef WIN32
	_vsnprintf(szMessage, 1023, lpszFormat, pArg);
#else
	vsnprintf(szMessage, 1023, lpszFormat, pArg);
#endif
	va_end(pArg);
	OutputDebugString(szMessage);
}

BEGIN_MESSAGE_MAP(CClientGameDlg, CLoveSendClassInExe)
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(IDM_BEGIN,OnHitBegin)
	//ON_MESSAGE(IDM_USER_NT,OnHitNt)
	ON_MESSAGE(IDM_LEFT_HITCARD,OnHitCard)
	ON_MESSAGE(IDM_MOUSE_MOVE,OnMouseMove)
	ON_MESSAGE(IDM_MOUSE_LEFT,OnMouseLeft)
	//ON_MESSAGE(IDM_GIVE_BACK,OnHitBackCard)
	//ON_MESSAGE(IDM_OUT_CARD,OnHitOutCard)
	//ON_MESSAGE(IDM_LOOK_LAST,OnHitLastTurn)
	//ON_MESSAGE(IDM_BACK_CARD,OnHitLookBack)
	ON_MESSAGE(IDM_HAVE_THING,OnHitHaveThing)
	ON_MESSAGE(IDM_SEND_THING,OnSendHaveThing)
	ON_MESSAGE(IDM_ARGEE_LEAVE,OnArgeeUserLeft)
	ON_MESSAGE(IDM_CALL_SCORE,OnCallScore)				//叫分
	//ON_MESSAGE(IDM_RIGHT_HITCARD,OnRightHitCard)
	ON_MESSAGE(IDM_STOP,OnStop)
	ON_MESSAGE(IDM_STOP_THING,OnStopThing)			//发送提前结束事件
	ON_MESSAGE(IDM_ARGEE_STOP,OnAgreeStop)			//同意提前结束事件
	ON_MESSAGE(IDM_AUTO,OnHitAuto)				//托管
	//ON_MESSAGE(IDM_PASS,OnHitPass)
	//	ON_MESSAGE(IDM_USER_NT,OnHitNt)
	ON_MESSAGE(IDM_ACTIVE_RESULT,OnHitActiveResult)//用户处理结果
	ON_MESSAGE(IDM_SHOW_NOTE,OnShowNote)			//用户下注加注具体数
	ON_MESSAGE(IDM_SELECT_NOTE_NUM,OnSelectNote)		//用户选择下注
	ON_MESSAGE(WM_SENDCARD_SHOWCARD,SendCardShowCard)
	//	ON_MESSAGE(WM_SETMESSAGE,OnSetMessage)
	ON_WM_TIMER()
	//	ON_WM_CLOSE()
END_MESSAGE_MAP()

//构造函数
CClientGameDlg::CClientGameDlg() : CLoveSendClassInExe(&m_PlayView)
{
	m_iVersion=DEV_HEIGHT_VERSION;
	m_iVersion2=DEV_LOW_VERSION;
	m_iThinkTime=0;
	m_iCardCount=0;
	m_iNowOutPeople=0;
	m_iFirstOutPeople = 0;
	m_PlayView.SetNTStation();
	m_bTimeOutCount=0;
	m_bCurrentOperationStation = 255;//当前叫分者
#ifdef SUPER_VERSION
	m_SetCard = NULL;
#endif
	
	//系统牌清零
	//m_iSysCardCount=28;
	m_iNowBigNote=0;				//当前最大押注数
	m_iThisTurnLimit=0;				//本轮限注
	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));
	::memset(m_iUpBullCard,1,sizeof(m_iUpBullCard));
	::memset(m_UserCard,0,sizeof(m_UserCard));
	m_bBgSound=true;
	m_hMciWnd1=NULL;
	m_hMciWnd2=NULL;
	m_iAfterWaitAction = 0;
	//	WriteProfileInt(TEXT("ShowPicture"),GameSetDlg.m_bRightPower?1:0);
	m_iSendAnimaCardPos = 255 ;
	m_iSendCardTotle = 0 ;
	m_bIsSuper       = FALSE;
	m_bPlayer        = FALSE;

}

//析构函数
CClientGameDlg::~CClientGameDlg()
{
	if(m_hMciWnd1)
	{
		MCIWndStop(m_hMciWnd1);
		MCIWndDestroy(m_hMciWnd1);
		m_hMciWnd1=NULL;
	}

	if(m_hMciWnd2)
	{
		MCIWndStop(m_hMciWnd2);
		MCIWndDestroy(m_hMciWnd2);
		m_hMciWnd2=NULL;
	}
#ifdef SUPER_VERSION
	if (m_SetCard)
	{
		delete m_SetCard;
		m_SetCard = NULL;
	}
#endif

}

//数据绑定函数
void CClientGameDlg::DoDataExchange(CDataExchange * pDX)
{
	CLoveSendClassInExe::DoDataExchange(pDX);
	DoDataExchangeWebVirFace(pDX);
}

//初始化函数
BOOL CClientGameDlg::OnInitDialog()
{
	CLoveSendClassInExe::OnInitDialog();
	m_PlayView.m_nPowerOfGold = Glb().m_nPowerOfGold;

	//更新标题
	SetDialogIcon(LoadIcon(GetModuleHandle(CLIENT_DLL_NAME),MAKEINTRESOURCE(IDI_CLIENT_ROOM)),TRUE);

	m_PlayView.m_bRightPower=TRUE;//GetProfileInt(TEXT("RightPower"),FALSE);
	m_pGameInfo->bEnableSound=true;

	CString s = CBcfFile::GetAppPath();
	CString fpath;
	fpath = s+SKIN_FOLDER+".bcf";
	if (CBcfFile::IsFileExist(fpath))
	{
		CBcfFile f(fpath);
		m_iAfterWaitAction = f.GetKeyVal(_T("config"), _T("AfterWaitAction"), 2);
		m_PlayView.m_strMoneyType.Format("%s", f.GetKeyVal("config", "moneytype", "金币"));
		if (m_iAfterWaitAction != 1 && m_iAfterWaitAction != 2)
		{
			m_iAfterWaitAction = 2;
		}
		m_bAutoBull =  f.GetKeyVal(_T("config"), _T("AutoBull"), 1);
	}

	return TRUE;
}

//设置游戏状态
bool CClientGameDlg::SetGameStation(void * pStationData, UINT uDataSize)
{
	Msg("Test:Step: %d",GetStationParameter());
	//m_PlayView.SetShape(2, 0);

#ifdef SAO_YANG
	m_PlayView.m_btChangeShin.ShowWindow(SW_SHOW);
	m_PlayView.m_btChangeShin.EnableWindow(TRUE);
#endif

	switch (GetStationParameter())
	{
	case GS_WAIT_SETGAME:	//游戏没有开始状态
	case GS_WAIT_ARGEE:	//等待同意状态
		{	
			GameStation_2 * pGameStation=(GameStation_2 *)pStationData;
			m_Logic.SetCardShape(pGameStation->iCardShape);
			//设置数据
			m_iThinkTime=pGameStation->iThinkTime;
			m_iBeginTime=pGameStation->iBeginTime;
			m_iPalyCardCount=pGameStation->iAllCardCount;
			m_iCallScoreTime = pGameStation->iCallScoreTime;
			m_iXiaZhuTime = pGameStation->iXiaZhuTime;
			m_PlayView.m_GameType = pGameStation->bGameType;
			m_PlayView.m_iGameNoteSetType = pGameStation->iGameNoteSetType;
			//函数调用
			CheckVersion(pGameStation->iVersion,pGameStation->iVersion2);	
			m_iRoomBasePoint = pGameStation->iRoomBasePoint ;//房间倍数
			m_iRunPublish = pGameStation->iRunPublish ;		//逃跑扣分
			m_bIsSuper    = pGameStation->bIsSuper;
		
			//正式发行版不允许旁观
			/*	if(m_bWatchMode&&m_pGameInfo->pMeUserInfo->GameUserInfo.bGameMaster!=MAST_PEOPLE)
			{
			PostMessage(WM_CLOSE,0,0);
			return true;
			}*/
			::CopyMemory(m_iLimitNote,&pGameStation->iLimitNote,sizeof(pGameStation->iLimitNote));	//最大注
			m_iBaseNote=pGameStation->iBaseNote;			//底注
			m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetShowCard(!m_bWatchMode||m_bWatchOther);//20090414旁观看牌设置zht

			if(!m_bWatchMode)
			{
// 				m_PlayView.m_btContinue.ShowWindow(!m_bWatchMode);
// 				m_PlayView.m_btLeave.ShowWindow(!m_bWatchMode);	
// 				m_PlayView.m_btContinue.SetFocus();
// 				SetGameTimer(GetMeUserInfo()->bDeskStation,m_iThinkTime,ID_BEGIN_TIME);
				if (!IsQueueGameRoom()) 
				{ 
					m_PlayView.m_btContinue.ShowWindow(!m_bWatchMode);
					if(m_PlayView.m_btLeave.m_hWnd)
						m_PlayView.m_btLeave.ShowWindow(!m_bWatchMode);
					//m_PlayView.m_btContinue.SetFocus();
				
					SetGameTimer(GetMeUserInfo()->bDeskStation,m_iBeginTime,ID_BEGIN_TIME);
				} 
				else
				{
					ResetGameStation(RS_GAME_BEGIN);
				}
			}

			return TRUE;
		}
	case GS_SEND_CARD:	//发牌状态
		{
			GameStation_3 * pGameStation=(GameStation_3 *)pStationData;
			//函数调用
			CheckVersion(pGameStation->iVersion,pGameStation->iVersion2);
			m_Logic.SetCardShape(pGameStation->iCardShape);
			m_PlayView.m_btLeave.ShowWindow(SW_HIDE);	
			m_PlayView.m_btContinue.ShowWindow(SW_HIDE);
			m_PlayView.m_GameType = pGameStation->bGameType;
			m_PlayView.m_iGameNoteSetType = pGameStation->iGameNoteSetType;

			//设置数据
			m_iThinkTime=pGameStation->iThinkTime;
			m_iBeginTime=pGameStation->iBeginTime;
			m_iPalyCardCount=pGameStation->iAllCardCount;
			m_iRoomBasePoint = pGameStation->iRoomBasePoint ;//房间倍数
			m_iRunPublish = pGameStation->iRunPublish ;		//逃跑扣分
			m_iCallScoreTime = pGameStation->iCallScoreTime;
			m_iXiaZhuTime = pGameStation->iXiaZhuTime;
			::CopyMemory(m_iLimitNote,&pGameStation->iLimitNote,sizeof(pGameStation->iLimitNote));	//最大注
			m_iBaseNote=pGameStation->iBaseNote;			//底注
			m_PlayView.m_btContinue.ShowWindow(SW_HIDE);
			m_iUpGradePeople = pGameStation->iUpGradePeople;
			m_bIsSuper    = pGameStation->bIsSuper;
			m_bPlayer     = pGameStation->bPlayer;

			//Msg("zhtlog:m_bPlayer=%d",m_bPlayer);
			//			::CopyMemory(m_iDeskCardCount,pGameStation->iUserCardCount,sizeof(pGameStation->iUserCardCount));
			BYTE iView = 2;
#ifndef TWO_NN
			iView = 2;
#else
			iView = 1;
#endif
			for (int i=0;i<PLAY_COUNT;i++)
			{	
				//设置各家手中牌
				int desk=ViewStation(i);
				//桌面牌数
				m_iDeskCardCount[desk]=pGameStation->iUserCardCount[i];
				::CopyMemory(m_UserCard[desk],pGameStation->iUserCard[i],sizeof(BYTE)*m_iDeskCardCount[desk]);
				if (desk == iView)
					::CopyMemory(m_DeskCard[desk],pGameStation->iUserCard[i],sizeof(BYTE)*m_iDeskCardCount[desk]);
				else 
					memset(m_DeskCard[desk],0,sizeof(m_DeskCard[desk]));
				m_PlayView.m_UserCard[desk].SetShowCard(!m_bWatchMode||m_bWatchOther);//20090414旁观看牌设置zht
				m_PlayView.m_UserCard[desk].SetCard(m_DeskCard[desk],NULL,m_iDeskCardCount[desk]);

				//设置各家手中押注情况
				m_PlayView.SetNotePoint(desk,pGameStation->iTotalNote[i]);
				//系统管理员显示各家底牌
				/*if(m_pGameInfo->pMeUserInfo->GameUserInfo.bGameMaster==MAST_PEOPLE)
					m_PlayView.m_UserCard[desk].SetCard(m_UserCard[desk],NULL,m_iDeskCardCount[desk]);*/
#ifdef SUPER_VERSION
				m_PlayView.m_UserCard[desk].SetCard(m_UserCard[desk],NULL,m_iDeskCardCount[desk]);

#endif
			}
			m_iThisTurnLimit=m_iLimitNote[GetMeUserInfo()->bDeskStation];

			//设置押注上限
			m_PlayView.SetLimitNote(0,m_iThisTurnLimit,m_iBaseNote);

			Msg("jiaofen2:【1】m_iUpGradePeople = %d", m_iUpGradePeople);

			//设置庄家
// 			if (m_iUpGradePeople != -1)
// 				m_PlayView.SetNTStation(ViewStation(m_iUpGradePeople));
			
			//设置押注上限
			m_PlayView.SetLimitNote(0,m_iLimitNote[GetMeUserInfo()->bDeskStation],m_iBaseNote);
			//设置总押注情况
//			m_PlayView.SetTotalNote(0, pGameStation->tag.iTotalNote);
			m_iNowOutPeople=pGameStation->tag.iOutPeople;
			//设置时间
			//SetGameTimer(GetMeUserInfo()->bDeskStation,m_iThinkTime,ID_OUT_CARD);
			//是否为当前押注者
			if (!m_bWatchMode&&m_iUpGradePeople!=GetMeUserInfo()->bDeskStation && pGameStation->iGameFlag == GS_NOTE &&m_bPlayer)
			{
				if (pGameStation->iTotalNote[ GetMeUserInfo()->bDeskStation ] <= 0)
				{
					m_PlayView.SetDrawNote(true);
					FlashWindowEx(FLASHW_TIMERNOFG|FLASHW_TRAY, 1, 0);
				}
			}
			if (!m_bWatchMode&&m_iNowOutPeople ==GetMeUserInfo()->bDeskStation && pGameStation->iGameFlag ==GS_FLAG_CALL_SCORE && m_bPlayer)
			{
				m_PlayView.m_btCallScore1.ShowWindow(SW_SHOW);
				m_PlayView.m_btCallScorePass.ShowWindow(SW_SHOW);
				m_PlayView.m_btCallScore1.EnableWindow(TRUE);
				m_PlayView.m_btCallScorePass.EnableWindow(TRUE);
				FlashWindowEx(FLASHW_TIMERNOFG|FLASHW_TRAY, 1, 0);
			}

			if (pGameStation->iGameFlag ==GS_FLAG_CALL_SCORE)
			{
				Msg("Test: Client Runing GS_FLAG_CALL_SCORE");
				SetGameTimer(m_iNowOutPeople,m_iCallScoreTime,ID_CALL_SCORE_TIME);
			}
			else if (pGameStation->iGameFlag == GS_NOTE)
			{
				SetGameTimer(GetMeUserInfo()->bDeskStation,m_iXiaZhuTime,ID_NOTE);
				if (GetMeUserInfo()->bDeskStation == m_iUpGradePeople)
				{
					m_PlayView.SetWait(true);//绘等待贴图
				}
			}

			return TRUE;
		}
	case GS_PLAY_GAME:	//游戏进行中
		{
			GameStation_4 * pGameStation=(GameStation_4 *)pStationData;
			m_PlayView.m_GameType = pGameStation->bGameType;
			m_PlayView.m_iGameNoteSetType = pGameStation->iGameNoteSetType;
			//函数调用
			CheckVersion(pGameStation->iVersion,pGameStation->iVersion2);
			m_Logic.SetCardShape(pGameStation->iCardShape);
			m_PlayView.m_btContinue.ShowWindow(SW_HIDE);
			m_PlayView.m_btLeave.ShowWindow(SW_HIDE);	
			m_bIsSuper    = pGameStation->bIsSuper;
			m_bPlayer     = pGameStation->bPlayer;

			BYTE iView = 2;
#ifndef TWO_NN
			iView = 2;
#else
			iView = 1;
#endif
			//设置数据
			m_iThinkTime=pGameStation->iThinkTime;
			m_iBeginTime=pGameStation->iBeginTime;
			m_iPalyCardCount=pGameStation->iAllCardCount;
			m_iRoomBasePoint = pGameStation->iRoomBasePoint ;//房间倍数
			m_iRunPublish = pGameStation->iRunPublish ;		//逃跑扣分
			::CopyMemory(m_iLimitNote,&pGameStation->iLimitNote,sizeof(pGameStation->iLimitNote));	//最大注
			m_iBaseNote=pGameStation->iBaseNote;			//底注
			m_PlayView.m_btContinue.ShowWindow(SW_HIDE);

			m_iXiaZhuTime = pGameStation->iXiaZhuTime;
			m_iCallScoreTime = pGameStation->iCallScoreTime;
			m_iNowOutPeople=pGameStation->iOutCardPeople;
			m_iFirstOutPeople=pGameStation->iFirstOutPeople;
			m_iUpGradePeople = pGameStation->iUpGradePeople;
			//保存当前用户下注总额
			::CopyMemory(m_iThisGameNote,pGameStation->iTotalNote,sizeof(pGameStation->iTotalNote));
			::CopyMemory(m_iThisGameNote,pGameStation->iThisGameNote,sizeof(pGameStation->iThisGameNote));
			::CopyMemory(m_iTotalGameNote,pGameStation->iTotalGameNote,sizeof(pGameStation->iTotalGameNote));
			m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetShowCard(!m_bWatchMode||m_bWatchOther);//20090414旁观看牌设置zht
			
			for (int i=0;i<PLAY_COUNT;i++)
			{	
				//设置各家手中牌
				int desk=ViewStation(i);
				//桌面牌数
				m_iDeskCardCount[desk]=pGameStation->iUserCardCount[i];
				::CopyMemory(m_UserCard[desk],pGameStation->iUserCard[i],sizeof(BYTE)*m_iDeskCardCount[desk]);
				if (desk == iView)
					::CopyMemory(m_DeskCard[desk],pGameStation->iUserCard[i],sizeof(BYTE)*m_iDeskCardCount[desk]);
				else 
					memset(m_DeskCard[desk],0,sizeof(m_DeskCard[desk]));
				m_PlayView.m_UserCard[desk].SetCard(m_DeskCard[desk],NULL,m_iDeskCardCount[desk]);
				//设置各家手中押注情况
				m_PlayView.SetNotePoint(desk,pGameStation->iTotalNote[i]);
				m_PlayView.m_bOpenCard[desk] = pGameStation->iUserStation[i];

				//系统管理员显示各家底牌
				/*if(m_pGameInfo->pMeUserInfo->GameUserInfo.bGameMaster==MAST_PEOPLE)
					m_PlayView.m_UserCard[desk].SetCard(m_UserCard[desk],NULL,m_iDeskCardCount[desk]);*/
#ifdef SUPER_VERSION
				m_PlayView.m_UserCard[desk].SetCard(m_UserCard[desk],NULL,m_iDeskCardCount[desk]);

#endif
			}

			m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetUseMouse(!m_bWatchMode);

			m_iThisTurnLimit=m_iLimitNote[GetMeUserInfo()->bDeskStation];

			//设置庄家
			if (m_iUpGradePeople != -1)
				m_PlayView.SetNTStation(ViewStation(m_iUpGradePeople));

			//设置押注上限
			m_PlayView.SetLimitNote(0,m_iLimitNote[GetMeUserInfo()->bDeskStation],m_iBaseNote);
			m_iNowBigNote=pGameStation->tag.iNowBigNote;
			//设置总押注情况
//			m_PlayView.SetTotalNote(0, pGameStation->tag.iTotalNote);
				
			//设置时间
			if (m_iNowOutPeople != -1) 
				SetGameTimer(GetMeUserInfo()->bDeskStation,m_iThinkTime,ID_OUT_CARD);
			//是否为当前押注者
			if (!m_bWatchMode && pGameStation->iUserStation[GetMeUserInfo()->bDeskStation] != TYPE_GIVE_UP&&m_bPlayer)
			{	
				//if (!m_PlayView.m_bRightPower)
				m_PlayView.m_btBull.ShowWindow(SW_SHOW);
				m_PlayView.m_btOpen.ShowWindow(SW_SHOW);
				m_PlayView.m_btReset.ShowWindow(SW_SHOW);
				m_PlayView.m_btBull.EnableWindow(TRUE);
				m_PlayView.m_btOpen.EnableWindow(TRUE);
				m_PlayView.m_btReset.EnableWindow(TRUE);//小于21点才能要牌

				FlashWindowEx(FLASHW_TIMERNOFG|FLASHW_TRAY, 1, 0);

			}

			// 已经分了牌
			if (pGameStation->bSplit)
			{
				KillGameTimer(ID_OUT_CARD);
				m_PlayView.m_btBull.ShowWindow(SW_HIDE);
				m_PlayView.m_btOpen.ShowWindow(SW_HIDE);

				BYTE card[10];
				::CopyMemory(m_iUpBullCard[iView], pGameStation->bBullCard, sizeof(m_iUpBullCard[iView]));
				::CopyMemory(card,&m_UserCard[iView],sizeof(m_UserCard[iView]));
				m_Logic.RemoveCard(m_iUpBullCard[iView], 3, card, 5);
				if (m_Logic.GetShape(m_UserCard[iView], 5, m_iUpBullCard[iView]) > UG_NO_POINT)
				{
				m_PlayView.m_UserCard[iView].SetCard(m_iUpBullCard[iView], NULL, 3);
				m_PlayView.m_UserBull[iView].SetCard(card, NULL, 2);
				}
				else
				{
					m_PlayView.m_UserCard[iView].SetCard(m_UserCard[iView], NULL,5);
					m_PlayView.m_UserBull[iView].SetCard(NULL, NULL, 0);
				}
				m_PlayView.m_UserCard[iView].SetUseMouse();
				m_PlayView.m_UserBull[iView].SetShowCard(!m_bWatchMode||m_bWatchOther);
				m_PlayView.m_UserCard[iView].SetShowCard(!m_bWatchMode||m_bWatchOther);


				//FlashWindowEx(FLASHW_TIMERNOFG|FLASHW_TRAY, 1, 0);
			}

			return TRUE;
		}
	case GS_WAIT_NEXT:		//等待下一盘开始
		{
			GameStation_5 * pGameStation=(GameStation_5 *)pStationData;
			//函数调用
			CheckVersion(pGameStation->iVersion,pGameStation->iVersion2);
			m_Logic.SetCardShape(pGameStation->iCardShape);
			m_PlayView.m_GameType = pGameStation->bGameType;
			m_PlayView.m_iGameNoteSetType = pGameStation->iGameNoteSetType;
			//设置数据
			m_iThinkTime=pGameStation->iThinkTime;
			m_iBeginTime=pGameStation->iBeginTime;
			m_iPalyCardCount=pGameStation->iAllCardCount;
			m_iRoomBasePoint = pGameStation->iRoomBasePoint ;//房间倍数
			m_iRunPublish = pGameStation->iRunPublish ;		//逃跑扣分
			m_iCallScoreTime = pGameStation->iCallScoreTime;
			m_iXiaZhuTime = pGameStation->iXiaZhuTime;
			m_iUpGradePeople = pGameStation->iUpGradePeople;
			m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetShowCard(!m_bWatchMode||m_bWatchOther);//20090414旁观看牌设置zht
			
			m_PlayView.m_btContinue.ShowWindow(SW_HIDE);
			m_PlayView.m_btLeave.ShowWindow(SW_HIDE);
			m_bIsSuper    = pGameStation->bIsSuper;

			//显示开始按钮 
			if (GetMeUserInfo()->bUserState != USER_ARGEE)
			{
				if (m_bWatchMode == false)
				{
// 					m_PlayView.m_btContinue.ShowWindow(SW_SHOW);
// 					m_PlayView.m_btLeave.ShowWindow(SW_SHOW);
// 					m_PlayView.m_btContinue.SetFocus();
					if (!IsQueueGameRoom()) 
					{ 
						m_PlayView.m_btContinue.ShowWindow(!m_bWatchMode);
						if(m_PlayView.m_btLeave.m_hWnd)
							m_PlayView.m_btLeave.ShowWindow(!m_bWatchMode);
						m_PlayView.m_btContinue.SetFocus();
						SetGameTimer(GetMeUserInfo()->bDeskStation,m_iBeginTime,ID_BEGIN_TIME);
					} 
					else
					{
						ResetGameStation(RS_GAME_BEGIN);
					}
				}

				 
// 				SetGameTimer(GetMeUserInfo()->bDeskStation,m_iBeginTime,ID_BEGIN_TIME);
			}
			return TRUE;
		}
	}
	return false;
}

//游戏消息处理函数
bool CClientGameDlg::HandleGameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	if (pNetHead->bMainID==MDM_GM_GAME_NOTIFY)
	{
		switch (pNetHead->bAssistantID)
		{
			//換底牌
		case ASS_GM_SUPERCLIENT:
			{
				if (uDataSize!=sizeof(ChangeBackStruct))
					return FALSE;
				ChangeBackStruct * pBack=(ChangeBackStruct *)pNetData;

				return ChangeBackCardResult(ViewStation(pBack->bDeskStation ),pBack->bSourceCard ,pBack->bResultCard,pBack->bExtVal);				
			}
		case ASS_UG_USER_SET:		//用户设置牌局
			{
				/*			if (uDataSize!=sizeof(UserArgeeGame))
				return FALSE;
				SetStationParameter(GS_WAIT_ARGEE);
				UserArgeeGame * pGameSet=(UserArgeeGame *)pNetData;

				//设置数据
				m_iThinkTime=pGameSet->iPlayCount=30;
				m_iBeginStation=pGameSet->iBeginStation;
				m_iEndStation=pGameSet->iEndStation;
				m_iPalyCardCount=pGameSet->iCardCount;

				//显示界面
				m_PlayView.m_StationView.SetShowMessage(TRUE);

				m_PlayView.m_StationView.SetPlayInfo(1,m_iThinkTime);
				if ((m_bWatchMode==FALSE)&&(GetMeUserInfo()->bDeskStation!=0))
				{
				m_PlayView.m_GameNoteView.SetMessage(NULL);
				m_PlayView.m_GameInfo.SetGameSetInfo(m_iPalyCardCount,m_iThinkTime,m_iBeginStation,m_iEndStation);
				}
				else m_PlayView.m_GameNoteView.SetMessage(TEXT("正在等待其他玩家开始游戏"));
				*/					
				return TRUE;
			}
		case ASS_BEGIN_UPGRADE:		//游戏开始
			{
				if (uDataSize!=sizeof(BeginUpgradeStruct))
					return FALSE;

				m_PlayView.m_GameNoteView.SetMessage(NULL);
				//设置开始动画起始位置
				//设置游戏状态
				SetStationParameter(GS_SEND_CARD);
				m_bTimeOutCount=0;	
				
				BeginUpgradeStruct * pBegin=(BeginUpgradeStruct *)pNetData;
				::CopyMemory(m_iLimitNote,&pBegin->iLimitNote,sizeof(pBegin->iLimitNote));	//最大注
				m_iBaseNote = pBegin->iBaseNote;
				m_iUpGradePeople = pBegin->iNt;                    //庄家
				m_iThisTurnLimit=m_iLimitNote[GetMeUserInfo()->bDeskStation];

				//m_bPlayer        = TRUE;
				m_PlayView.SetNTStation(ViewStation(m_iUpGradePeople));
				memset(m_PlayView.m_bOpenCard,false, sizeof(m_PlayView.m_bOpenCard));

				if (GetMeUserInfo()->bDeskStation == m_iUpGradePeople || m_bWatchMode || !m_bPlayer)
				{
					m_PlayView.SetWait(true);//绘等待贴图
					if (m_bPlayer)
						SetGameTimer(GetMeUserInfo()->bDeskStation,m_iXiaZhuTime,ID_NOTE );
				}
				else 
				{
					m_PlayView.m_btBull.EnableWindow(FALSE);
					m_PlayView.m_btOpen.EnableWindow(FALSE);
					m_PlayView.m_btReset.EnableWindow(FALSE);
//					m_PlayView.m_btSplit.EnableWindow(FALSE);

					m_PlayView.SetDrawNote(true);
					//闲家30秒下注时间
					SetGameTimer(GetMeUserInfo()->bDeskStation,m_iXiaZhuTime,ID_NOTE);
					FlashWindowEx(FLASHW_TIMERNOFG|FLASHW_TRAY, 1, 0);
				}
				if (m_bWatchMode==TRUE) 
				{
					KillAllTimer();
					
					ResetGameStation(RS_GAME_BEGIN);
				}
				m_PlayView.SetLimitNote(-1,m_iLimitNote[GetMeUserInfo()->bDeskStation],m_iBaseNote);

				return TRUE;
			}
		case ASS_SEND_CARD:			//服务器发牌
			{
				if(uDataSize != sizeof(SendAllCardStruct))
				{
					return FALSE;
				}
				SendAllCardStruct *pAllCard = (SendAllCardStruct *)pNetData ;

				for(int i = 0 ; i < PLAY_COUNT; i++)
				{
					BYTE bDesk = ViewStation(i);

					m_iDeskCardCount[bDesk] = pAllCard->iUserCardCount[i];	
			
					memcpy(&m_UserCard[bDesk],&pAllCard->iUserCard[i],sizeof(BYTE)*m_iDeskCardCount[bDesk]);

				}

			
				m_iSendCardTotle = 0;
				m_iSendAnimaCardPos = pAllCard->iStartPos;
				
				m_PlayView.SendCard(ViewStation(m_iSendAnimaCardPos),150);		

				SetTimer(ID_SEND_CARD_ANIMAL+ViewStation(m_iSendAnimaCardPos),150,NULL);

				if(m_pGameInfo->bEnableSound)
				{
					SetPlaySound(SOUND_SEND_CARD);
				}

				return TRUE;


			}
		case ASS_SEND_FINISH:		//发牌完成
			{				
				KillAllTimer();

				m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetUseMouse(!m_bWatchMode);
				BYTE bDesk = ViewStation(GetMeUserInfo()->bDeskStation);

				memcpy(&m_DeskCard,&m_UserCard,sizeof(m_UserCard));

				m_Logic.SortCard(m_DeskCard[bDesk],NULL,m_iDeskCardCount[bDesk]);
				m_PlayView.m_UserCard[bDesk].SetCard(m_DeskCard[bDesk],NULL,m_iDeskCardCount[bDesk]);
#ifdef SUPER_VERSION
				m_PlayView.m_UserCard[bDesk].SetCard(m_UserCard[bDesk],NULL,m_iDeskCardCount[bDesk]);
#endif
				

				if (m_bWatchMode)
					m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetShowCard(m_bWatchOther);				
		
				for(int i = 0; i < PLAY_COUNT; i++)
				{
					m_PlayView.m_SendCardAnimal[i].ShowWindow(SW_HIDE);
				}
				return TRUE;
			}
		case ASS_COLLECT_JETON://收集筹码
			{
				if (uDataSize != sizeof(CollectJetonStruct)) 
					return FALSE;	

				CollectJetonStruct * pCollectJeton=(CollectJetonStruct *)pNetData;

				BYTE desk=ViewStation(pCollectJeton->bDeskStation);
				//目前显示动画
				m_PlayView.SetCollectJetonStart();//设置收集筹码起始位置
				m_bShowAnimalStation=desk;						//设置当前动画位置
				m_iNowBigNote=0;

				////本輪下注清零
				//for(int i=0;i<PLAY_COUNT;i++)
				//	m_PlayView.SetThisTurnNotePoint(i,0);
				//设置起始坐标
				m_PlayView.SetCollectJetonStart();
				m_PlayView.CollectJetonAnimal();					//开始运行动画	
				SetTimer(ID_COLLECT_JETON_ANIMAL,50,0);

				return TRUE;
			}
		case ASS_SEND_A_CARD:
			{
				if (uDataSize != sizeof(SendCardStruct)) 
					return FALSE;	
				SendCardStruct * pSendCard=(SendCardStruct *)pNetData;
				int desk=ViewStation(pSendCard->bDeskStatin);
				m_DeskCard[desk][m_iDeskCardCount[desk]]=pSendCard->iCard;			//用户桌面上的牌
				if (desk == 2) //自已牌就显示
					m_UserCard[desk][m_iDeskCardCount[desk]++]=pSendCard->iCard;		//用户手中牌
				else
					m_UserCard[desk][m_iDeskCardCount[desk]++]=0x00;		//用户手中牌
				m_PlayView.m_UserCard[desk].SetCard(m_DeskCard[desk],NULL,m_iDeskCardCount[desk]);//显示桌面牌情形
				
			
				BYTE Rev[1];
				Rev[0]=pSendCard->iCard;
				/*for(int i=0;i<PLAY_COUNT;i++)
				m_PlayView.SetThisTurnNotePoint(i,0);*/
				//游戏开始音效设置
				if(m_pGameInfo->bEnableSound)
					SetPlaySound(SOUND_SEND_CARD);
				return true;
			}

		case ASS_GAME_PLAY:		//开始游戏
			{
				if (uDataSize!=sizeof(BeginPlayStruct)) 
					return FALSE;

				//设置游戏状态
				SetStationParameter(GS_PLAY_GAME);
				m_PlayView.m_GameNoteView.SetMessage(NULL);

				BeginPlayStruct * pBeginInfo=(BeginPlayStruct *)pNetData;

				m_bTimeOutCount=0;					//超时次数设置

				m_iNowOutPeople=m_iFirstOutPeople=pBeginInfo->iOutDeskStation;
				m_iNowBigNote=0;							//当前最大押注数
				m_iThisTurnLimit=m_iLimitNote[GetMeUserInfo()->bDeskStation];//m_iLimitNote/32*(1<<1)/m_iBaseNote*m_iBaseNote;

				//设置时间
				if (m_bPlayer)
					SetGameTimer(GetMeUserInfo()->bDeskStation,m_iThinkTime,ID_OUT_CARD);
#ifndef TWO_NN
				if ( !m_bWatchMode && m_iDeskCardCount[2]==5)
#else
				if( !m_bWatchMode && m_iDeskCardCount[1] == 5 )
#endif
				{
					m_PlayView.m_btBull.ShowWindow(SW_SHOW);

                    //yl add 20120817/
					///m_PlayView.m_btOpen.ShowWindow(SW_SHOW);
					///m_PlayView.m_btReset.ShowWindow(TRUE);//
					m_PlayView.m_btBull.EnableWindow(TRUE);
					///m_PlayView.m_btOpen.EnableWindow(TRUE);
					///m_PlayView.m_btReset.EnableWindow(TRUE);//
					//加入要牌按钮
					FlashWindowEx(FLASHW_TIMERNOFG|FLASHW_TRAY, 1, 0);
				}
				return TRUE;
			}
		case ASS_NOTE:								//玩家押注情况
			{
				if (uDataSize != sizeof(tagUserResult)) 
					return FALSE;
				tagUserResult *pResult = (tagUserResult *) pNetData;
				//用户下注用来显示下注动画,暂不赋值
				m_iNowOutPeople = pResult->iOutPeople;		//当前加注者
				m_iThisTurnLimit=m_iLimitNote[GetMeUserInfo()->bDeskStation];
				//系统给他下注次数

				if (m_iNowOutPeople == GetMeUserInfo()->bDeskStation && !m_bWatchMode && m_bPlayer)
				{
					m_PlayView.m_btBull.EnableWindow(TRUE);
					m_PlayView.m_btOpen.EnableWindow(TRUE);
					//加入要牌等的按钮            
					FlashWindowEx(FLASHW_TIMERNOFG|FLASHW_TRAY, 1, 0);
				}
				//设置时间
				if (m_iNowOutPeople!=-1 && (m_bPlayer)) 
					SetGameTimer(GetMeUserInfo()->bDeskStation,m_iThinkTime,ID_OUT_CARD);
				return true;
			}
		case ASS_NOTE_RESULT:											//押注结果
			{
				if (uDataSize != sizeof(NoteResult)) 
					return FALSE;


				NoteResult *noteresult=(NoteResult*)pNetData;
				
				m_iNowOutPeople=noteresult->iOutPeople;
				int iViewStation = ViewStation(noteresult->iOutPeople);
				m_PlayView.SetWait(false);//取消绘等待贴图

				if (GetMeUserInfo()->bDeskStation == noteresult->iOutPeople)
				{
					m_PlayView.SetDrawNote();
				}


				//如果是放弃则不再显示牌面
				switch(noteresult->bAddStyle)
				{
				case TYPE_GIVE_UP://放弃
					{
						if (GetStationParameter()!=GS_PLAY_GAME)
							m_PlayView.SetPass(iViewStation,1);
						memset(m_UserCard[iViewStation],0,m_iDeskCardCount[iViewStation]);
						memset(m_DeskCard[iViewStation],0,m_iDeskCardCount[iViewStation]);
						m_PlayView.m_UserCard[iViewStation].SetCard(m_DeskCard[iViewStation],NULL,m_iDeskCardCount[iViewStation]);//显示桌面牌情形
						if(GetMeUserInfo()->bDeskStation==noteresult->iOutPeople)
						{
							m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetUseMouse(false);
						}
						break;
					}

				case TYPE_OPEN://停牌(不要牌)
					{
						
		
						break;
					}
				/*case TYPE_RESET:
					{

						break;
					}*/
				case TYPE_NOTE:
					//更新下注
					{
						
						m_PlayView.SetNotePoint(iViewStation,noteresult->iCurNote);
						//设置某一个人下注总额
						m_iThisGameNote[noteresult->iOutPeople]+=noteresult->iCurNote;
						//用来显示用户桌面上下注情况
						//m_PlayView.SetAddNote(noteresult->iCurNote);

					//	Msg("zhtlog:noteresult->iCurNote=%I64d",noteresult->iCurNote);

						m_PlayView.SetNotePointStart(ViewStation(noteresult->iOutPeople));
						//目前显示动画

						if(m_pGameInfo->bEnableSound)
						{
							SetPlaySound(SOUND_USER_CHIP);	
						}
	
					}
					break;
				}
				return true;
			}
		case ASS_CALL_SCORE:			//叫分
			{	
				CallScoreStruct *score=(CallScoreStruct *)pNetData;	

				if (m_bWatchMode) 
				{
 					//int iViewStation = ViewStation(score->bDeskStation);
 					//m_PlayView.SetNTStation(iViewStation);

					KillAllTimer();
					ResetGameStation(RS_GAME_BEGIN);
				}

				if(m_pGameInfo->bEnableSound)
				{
					SetPlaySound(SOUND_START_DEF);
				}

				SetStationParameter(GS_SEND_CARD);
				
				m_bPlayer = score->bPlayer;
				m_bCurrentOperationStation = score->bDeskStation;
				m_PlayView.m_GameNoteView.SetMessage(NULL);
				if(m_bCurrentOperationStation != 255)
				{
					SetGameTimer(m_bCurrentOperationStation,m_iCallScoreTime,ID_CALL_SCORE_TIME);
				}

				//Msg("zhtlog11:m_bPlayer=%d",m_bPlayer);

				if(!m_bWatchMode && GetMeUserInfo()->bDeskStation == score->bDeskStation && m_bPlayer)
				{
					ShowCallScoreBt(score->iValue);
#ifdef AI_MACHINE
					int result = rand()%4;
					if(result > score->iCallScore && result > 0 && result <= 3)
						;
					else 
						result = 0;
					OnCallScore(result,result);
#endif 
				}
				return true;
			}
		case ASS_CALL_SCORE_RESULT:			//叫分结果
			{
				if (uDataSize != sizeof(CallScoreStruct)) 
					return FALSE;
				KillTimer(ID_CALL_SCORE_TIME);
				HideButton();

				return true;
			}
		case ASS_CALL_SCORE_FINISH:
			{
				if (uDataSize != sizeof(CallScoreStruct)) 
					return FALSE;

				KillTimer(ID_CALL_SCORE_TIME);
				HideButton();
				m_bCurrentOperationStation = 255;
				CallScoreStruct *score=(CallScoreStruct*)pNetData;

				int iViewStation = ViewStation(score->bDeskStation);
				m_PlayView.SetNTStation(iViewStation);

				return true;
			}

		case ASS_SALE_END:	//游戏安全结束
			{
				if (uDataSize!=sizeof(GameCutStruct)) 
					return FALSE;
				GameCutStruct * pGameEnd=(GameCutStruct *)pNetData;
				KillGameTimer(0);
				
				SetStationParameter(GS_WAIT_ARGEE);	
				KillAllTimer();
				ResetGameStation(RS_GAME_CUT);
				//是否为比赛场
				if(!m_bWatchMode)
				{
					m_PlayView.m_btContinue.ShowWindow(!m_bWatchMode);
					m_PlayView.m_btLeave.ShowWindow(!m_bWatchMode);
					m_PlayView.m_btContinue.SetFocus();

					SetGameTimer(GetMeUserInfo()->bDeskStation,m_iBeginTime,ID_BEGIN_TIME);
					
				}
				return TRUE;
			}
		case ASS_CUT_END:	//用户强行离开
			{
				if (uDataSize!=sizeof(GameCutStruct))
					return FALSE;
				GameCutStruct * pGameEnd=(GameCutStruct *)pNetData;
				KillGameTimer(0);
				//处理非空
				GameFinishNotify CutNotify;
				::memset(&CutNotify,0,sizeof(CutNotify));
				if(pGameEnd->bDeskStation != GetMeUserInfo()->bDeskStation&&m_pUserInfo[pGameEnd->bDeskStation]!=NULL)
				{
					//显示信息
					TCHAR szMessage[100];
					if (pNetHead->bAssistantID==ASS_CUT_END)
						wsprintf(szMessage,TEXT("由于〖 %s 〗强行退出，游戏结束。"),m_pUserInfo[pGameEnd->bDeskStation]->GameUserInfo.nickName);
					else 
						wsprintf(szMessage,TEXT("由于〖 %s 〗离开，游戏结束。"),m_pUserInfo[pGameEnd->bDeskStation]->GameUserInfo.nickName);
					//					m_PlayView.m_StationView.CleanAllInfo(TRUE);
					//设置结束显示信息
					for(int i=0;i<PLAY_COUNT;i++)
					{
						if(m_pUserInfo[i]!=NULL)
						{
							wsprintf(CutNotify.name[i],"%s",m_pUserInfo[i]->GameUserInfo.nickName);
							CutNotify.iWardPoint[i]=pGameEnd->iTurePoint[i];
							//	CutNotify.iTotalPoint[i]=m_pUserInfo[i]->GameUserInfo.dwPoint+pGameEnd->iTurePoint[i];
							CutNotify.iMoney[i]=pGameEnd->iChangeMoney[i];//m_pUserInfo[i]->GameUserInfo.dwMoney;
						}
						else
						{
							memset(CutNotify.name[i],0,sizeof(CutNotify.name[i]));
							CutNotify.iWardPoint[i]=0;
							//CutNotify.iTotalPoint[i]=0;
							CutNotify.iMoney[i]=0;
						}
					}

					m_MessageHandle.InsertNormalMessage(szMessage);
					//if(m_pGameInfo->bEnableSound)
					//	SetSenceSound(SOUND_USER_RUNAWARY,m_pUserInfo[GetMeUserInfo()->bDeskStation]->GameUserInfo.bBoy);

				}
				SetStationParameter(GS_WAIT_ARGEE);
				KillAllTimer();

				//m_bShowLast=FALSE;
				//m_iLastCardCount=0;
				ResetGameStation(RS_GAME_CUT);
				//				m_PlayView.m_Result.ShowWindow(SW_SHOW);

				//设置牌局
				if (m_bWatchMode==FALSE)
				{
					m_PlayView.m_btContinue.ShowWindow(!m_bWatchMode);
					m_PlayView.m_btLeave.ShowWindow(!m_bWatchMode);
					///m_PlayView.m_btContinue.SetFocus();	//yl add 20121015/
					SetGameTimer(GetMeUserInfo()->bDeskStation,m_iBeginTime,ID_BEGIN_TIME);
				}
				return TRUE;
			}
		case ASS_CONTINUE_END:	//游戏结束
		case ASS_NO_CONTINUE_END:
			{
				if (uDataSize!=sizeof(GameEndStruct)) 
					return FALSE;
				GameEndStruct * pGameEnd=(GameEndStruct *)pNetData;
				KillGameTimer(0);
				//设置分数 
				//m_PlayView.m_StationView.SetTurePoint(pGameEnd->iTurePoint[GetMeUserInfo()->bDeskStation]);

				//设置分数 
				CString stime;
				stime.Format("%d",CTime::GetCurrentTime());
				int curtime=atoi(stime);
				CString str;
				m_MessageHandle.InsertNormalMessage(TEXT("本局游戏结果："));
				m_MessageHandle.InsertNormalMessage(TEXT("－－－－－－－－－－－－"));
				GameFinishNotify finishnotify;
				::memset(&finishnotify,0,sizeof(finishnotify));
				int iUserInfoNull = 0;
				
				for (int i=0;i<PLAY_COUNT;i++)
				{
					if(m_pUserInfo[i] == NULL||pGameEnd->iUserState[i]==-1)
					{
						finishnotify.iCardShape[i] = 100;
						iUserInfoNull++;
						continue;
					}
					::CopyMemory(m_UserCard[ViewStation(i)],&pGameEnd->iCardList[i],sizeof(m_UserCard[i]));
					if(pGameEnd->iUserState[GetMeUserInfo()->bDeskStation] && pGameEnd->iUserState[i])
					{
						//OutputDebugString("zhtout:11");
						if (pGameEnd->iCardShape[i] != UG_NO_POINT && pGameEnd->iCardShape[i] < UG_BULL_SILVER)
						{
								
							
							m_Logic.RemoveCard(pGameEnd->iUpBullCard[i],3,m_UserCard[ViewStation(i)],5);
							m_iDeskCardCount[ViewStation(i)]-=3;

							m_PlayView.m_UserBull[ViewStation(i)].SetShowCard(true);
							m_PlayView.m_UserBull[ViewStation(i)].SetCard(m_UserCard[ViewStation(i)],NULL,2);

							m_PlayView.m_UserCard[ViewStation(i)].SetShowCard(true);
							m_PlayView.m_UserCard[ViewStation(i)].SetCard(pGameEnd->iUpBullCard[i],NULL,3);
						
						}
						else //处理三张方块2
						{
							m_Logic.SortCard(m_UserCard[ViewStation(i)],NULL,m_iDeskCardCount[ViewStation(i)]);

							m_PlayView.m_UserBull[ViewStation(i)].SetUseMouse(false);
							m_PlayView.m_UserBull[ViewStation(i)].SetCard(NULL,NULL,0);

							m_PlayView.m_UserCard[ViewStation(i)].SetShowCard(true);
							m_PlayView.m_UserCard[ViewStation(i)].SetCard(m_UserCard[ViewStation(i)],NULL,5);

						}

						//m_PlayView.m_CardShape[i].ShowCardShape(pGameEnd->iCardShape[i]);
						//m_PlayView.SetNotePoint(ViewStation(i),pGameEnd->iChangeMoney[i]);

						m_PlayView.m_UserCard[ViewStation(i)].Invalidate();
						m_PlayView.m_UserCard[ViewStation(i)].UpdateWindow();
						m_PlayView.m_UserBull[ViewStation(i)].Invalidate();
						m_PlayView.m_UserBull[ViewStation(i)].UpdateWindow();

						m_PlayView.SetShape(ViewStation(i),pGameEnd->iCardShape[i]);
					}
					CString strMoney;
					m_PlayView.GetNumString(pGameEnd->iChangeMoney[i],strMoney,Glb().m_nPowerOfGold);
					//设置结束显示信息
					str.Format(TEXT("%s 得分 %I64d %s %I64d"),m_pUserInfo[i]->GameUserInfo.nickName,pGameEnd->iTurePoint[i],m_PlayView.m_strMoneyType,pGameEnd->iChangeMoney[i]);
					//双倍
					if(m_pUserInfo[i]->GameUserInfo.iDoublePointTime>curtime && pGameEnd->iTurePoint[i]>0)
					{
						pGameEnd->iTurePoint[i]*=2;
						str.Format(TEXT("%s : 得分%I64d(双倍积分卡效果）%s %s"),
							m_pUserInfo[i]->GameUserInfo.nickName,pGameEnd->iTurePoint[i],m_PlayView.m_strMoneyType,strMoney/*pGameEnd->iChangeMoney[i]*/);							
					}
					else
					{
						str.Format(TEXT("%s : 得分 %I64d %s %s"),
							m_pUserInfo[i]->GameUserInfo.nickName,pGameEnd->iTurePoint[i],m_PlayView.m_strMoneyType,strMoney/*pGameEnd->iChangeMoney[i]*/);								
					}

					m_MessageHandle.InsertNormalMessage(str.GetBuffer(MAX_PATH));
					wsprintf(finishnotify.name[i],"%s",m_pUserInfo[i]->GameUserInfo.nickName);
					finishnotify.iWardPoint[i]=pGameEnd->iTurePoint[i];
					finishnotify.iMoney[i]=pGameEnd->iChangeMoney[i];
					finishnotify.iCardShape[i]=pGameEnd->iCardShape[i];
				}
				//一局结算时,传递分数给对话框
				for(int i=0;i<PLAY_COUNT;i++)
					m_PlayView.m_showcoredlg.SetUserScore(ViewStation(i)/*viewstation*/,pGameEnd->iTurePoint[i]/*改变的分数*/,pGameEnd->iChangeMoney[i]);

				finishnotify.iBasePoint=m_iBaseNote;
				finishnotify.iStyle=1;


				m_PlayView.m_Result.SetMessage(finishnotify,GetMeUserInfo()->bDeskStation, Glb().m_nPowerOfGold);
				//玩家刚回来，指针为空，会造成结算框上什么都不显示，如果这样，就不显示结算框了
				if (iUserInfoNull != PLAY_COUNT)
				{
					m_PlayView.m_Result.ShowWindow(SW_SHOW);
				}
	
				SetStationParameter((pNetHead->bAssistantID==ASS_CONTINUE_END)?GS_WAIT_NEXT:GS_WAIT_ARGEE);

				ResetGameStation(RS_GAME_END);
				if (!m_bWatchMode)
				{
					m_PlayView.m_btContinue.ShowWindow(!m_bWatchMode);
					m_PlayView.m_btLeave.ShowWindow(!m_bWatchMode);
					//m_PlayView.m_btContinue.SetFocus();
					SetGameTimer(GetMeUserInfo()->bDeskStation,m_iBeginTime,ID_BEGIN_TIME);
				}

				if(m_pGameInfo->bEnableSound)
				{
					if (pGameEnd->iTurePoint[GetMeUserInfo()->bDeskStation] > 0||pGameEnd->iChangeMoney[GetMeUserInfo()->bDeskStation]>0)
						SetPlaySound(SOUND_WIN);
					else
						SetPlaySound(SOUND_LOSE);
				}
				return TRUE;
			}
		case ASS_HAVE_THING:	//用户请求离开
			{
				//HaveThingStruct * pThing=(HaveThingStruct *)pNetData;
				//if (m_PlayView.m_ThingMessage.GetSafeHwnd()==NULL) 
				//{
				//m_PlayView.m_ThingMessage.Create(IDD_THING_MESSAGE,this);
				//m_PlayView.m_ThingMessage.m_pParent=this;
				//}
				//m_PlayView.m_ThingMessage.SetLeaveMessage(pThing->szMessage,m_pUserInfo[pThing->pos]->GameUserInfo.nickName);
				//m_PlayView.m_ThingMessage.ShowWindow(SW_SHOW);

				return TRUE;
			}
		case ASS_LEFT_RESULT:	//请求离开结果 
			{
				//if (uDataSize!=sizeof(LeaveResultStruct)) 
				//	return FALSE;
				//LeaveResultStruct * pLeftResult=(LeaveResultStruct *)pNetData;
				//CString strBuffer;
				//if (!pLeftResult->bArgeeLeave) 
				//{
				//	strBuffer.Format(TEXT("玩家 %s 不同意游戏结束。但本局结束后，申请离开者可以离开。"),m_pUserInfo[pLeftResult->bDeskStation]->GameUserInfo.nickName);
				//	m_MessageHandle.InsertNormalMessage(strBuffer.GetBuffer(MAX_PATH));
				//}
				//else
				//{
				//	if(pLeftResult->bArgeeLeave&&GetMeUserInfo()->bDeskStation==pLeftResult->bDeskStation&&!m_bWatchMode)
				//		OnCancel();
				//}
				return TRUE;
			}
		case ASS_MESSAGE:
			{
				if (uDataSize!=sizeof(MessageStruct))
				{
					return FALSE;
				}
				MessageStruct *pMessage=(MessageStruct*)pNetData;
				m_MessageHandle.InsertSystemMessage(pMessage->Message);
				return true;
			}
		case ASS_STOP_THING://对家请求提前结束
			{
				//if (m_PlayView.m_StopMessage.GetSafeHwnd()==NULL) 
				//{
				//m_PlayView.m_StopMessage.Create(IDD_STOP_MESSAGE,this);
				//m_PlayView.m_StopMessage.m_pParent=this;
				//}
				//m_PlayView.m_StopMessage.ShowWindow(SW_SHOW);
				//				
				//
				return true;
			}
		case ASS_AGREE_STOP://请求提前结束结果
			{
				//if (uDataSize!=sizeof(StopResultStruct))return FALSE;
				//StopResultStruct *pStop=(StopResultStruct*)pNetData;
				//if (pStop->bArgee) 
				//{
				//	m_MessageHandle.InsertNormalMessage("对家同意提前结束。");
				//}
				//else 
				//{
				//	m_MessageHandle.InsertNormalMessage("对家不同意提前结束。");
				//}
				return true;
			}
		case ASS_NOMONEY:
			{
				ResetGameStation(RS_ALL_VIEW);
				OnCancel();
				AfxMessageBox("所有玩家中没有达到庄家要求,游戏将重新开始");
				//m_MessageHandle.InsertNormalMessage("【系统消息】:所有玩家中都没有达到做庄家要求,游戏将重新开始");
				return true;



			}
		case ASS_TAN_PAI:		//摊牌
			{
				if (m_pGameInfo->bEnableSound)
				{
					SetPlaySound(SOUND_TAN_PAI);
				}
				return true;
			}

		}
	}

	return __super::HandleGameMessage(pNetHead,pNetData,uDataSize/*,pClientSocket*/);
}

//重新设置界面
void CClientGameDlg::ResetGameFrame()
{
	m_PlayView.m_Result.ShowWindow(SW_HIDE);
	m_bTimeOutCount=0;

	m_iNowOutPeople=-1;

	m_iFirstOutPeople=-1;

	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));

	//界面重置
	for (int i=0;i<PLAY_COUNT;i++)
	{
		m_PlayView.m_UserCard[i].SetUseMouse(false);
		m_PlayView.m_UserCard[i].SetCard(NULL,NULL,0);
		m_PlayView.m_UserBull[i].SetUseMouse(false);
		m_PlayView.m_UserBull[i].SetCard(NULL,NULL,0);
	}
	m_PlayView.m_GameNoteView.SetMessage(NULL);
	//	if (m_PlayView.m_GameInfo.GetSafeHwnd()) m_PlayView.m_GameInfo.DestroyWindow();
	//	if (m_PlayView.m_BackCardDlg.GetSafeHwnd()) m_PlayView.m_BackCardDlg.DestroyWindow();
	//	if (m_PlayView.m_HaveThing.GetSafeHwnd()) m_PlayView.m_HaveThing.DestroyWindow();
	//	if (m_PlayView.m_ThingMessage.GetSafeHwnd()) m_PlayView.m_ThingMessage.DestroyWindow();
	//	if (m_PlayView.m_GameSet.GetSafeHwnd()) m_PlayView.m_GameSet.DestroyWindow();
	//	if (m_PlayView.m_GameEndView.GetSafeHwnd()) m_PlayView.m_GameEndView.DestroyWindow();
	return __super::ResetGameFrame();
}

//开始按钮函数
LRESULT	CClientGameDlg::OnHitBegin(WPARAM wparam, LPARAM lparam)
{
	if (m_pGameInfo->bEnableSound)
	{
		SetPlaySound(SOUND_HIT_BEGIN);
	}
	OnControlHitBegin();
	return 0;
}

bool CClientGameDlg::OnControlHitBegin()
{
	m_PlayView.m_btContinue.ShowWindow(SW_HIDE);		//隐藏
	m_PlayView.m_btLeave.ShowWindow(SW_HIDE);		//隐藏
	//SetSenceSound(SOUND_READY,m_pUserInfo[GetMeUserInfo()->bDeskStation]->GameUserInfo.bBoy);
	if (NULL != m_PlayView.m_GameNoteView.GetSafeHwnd())
	{
		m_PlayView.m_GameNoteView.SetMessage(TEXT("正在等待其他玩家开始游戏!"));		//以此来启动Waiting图像
	}

	if ((GetStationParameter()==GS_WAIT_SETGAME||GetStationParameter()==GS_WAIT_NEXT||GetStationParameter()==GS_WAIT_ARGEE)&&!m_bWatchMode)
	{
		SendGameData(MDM_GM_GAME_NOTIFY,ASS_GM_AGREE_GAME,0);
	}
	KillAllTimer();
	//	m_PlayView.m_StationView.CleanAllInfo(FALSE);
	//	m_PlayView.m_StationView.m_iTurePoint=0;
	ResetGameStation(RS_GAME_BEGIN);

	//旁观玩家关闭界面元素		//yl add 20121015/
	for (int i = 0; i < PLAY_COUNT; i++)
	{
		m_PlayView.m_CardShape[i].ShowWindow(SW_HIDE);
	}

	return true;
}

//清除所有定时器
void CClientGameDlg::KillAllTimer()
{
	KillTimer(ID_BEGIN_TIME);
	KillTimer(ID_OUT_CARD);
	KillTimer(ID_LOOK_BACK);
	KillTimer(ID_NOTE);
	KillTimer(ID_CALL_SCORE_TIME);
	KillTimer(ID_BEGIN_ANIMAL);
	//	KillTimer(ID_END_ANIMAL);
	KillTimer(ID_NOTE_ANIMAL_ZERO);
	KillTimer(ID_NOTE_ANIMAL_ONE);
	KillTimer(ID_NOTE_ANIMAL_TWO);
	KillTimer(ID_NOTE_ANIMAL_THREE);	
	KillTimer(ID_COLLECT_JETON_ANIMAL);
	for(int i = 0 ;i<PLAY_COUNT ;i++)
	{
		KillTimer(ID_SEND_CARD_ANIMAL+i);
	}
	memset(m_PlayView.m_uTime,0,sizeof(m_PlayView.m_uTime));
	m_PlayView.m_uTime[2]=0;
	return;
}

//定时器消息
bool CClientGameDlg::OnGameTimer(BYTE bDeskStation, UINT uTimeID, UINT uTimeCount)
{
	switch (uTimeID)
	{
	case ID_BEGIN_TIME:	//继续游戏定时器
		{
			if (uTimeCount<=0)
			{
				//时间到了
				if (!m_bWatchMode)
				{
					if (1 == m_iAfterWaitAction)
					{
						OnHitBegin(0,0);
					}
					else
					{
						OnCancel();
					}
					
				}
				return true;
			}
			if (uTimeCount<=5) 
			{
				if(m_pGameInfo->bEnableSound)
					SetPlaySound(SOUND_WARNING_0 - uTimeCount);	
			}

			return true;
		}
	case ID_NOTE:
		{
			if (uTimeCount<=0)
			{
				KillAllTimer();
				if (GetMeUserInfo()->bDeskStation != m_iUpGradePeople)
				{
					m_PlayView.SetDrawNote();
					if (!m_bWatchMode)
					{
						m_PlayView.OnNote(4);
					}
				}

				OnHitActiveResult(0,0);
			}
			if (uTimeCount<=5) 
			{
				if(m_pGameInfo->bEnableSound)
					SetPlaySound(SOUND_WARNING_0 - uTimeCount);	
					//PlaySound(TEXT("WARNING"),GetModuleHandle(CLIENT_DLL_NAME),SND_RESOURCE|SND_NOSTOP|SND_ASYNC|SND_NODEFAULT|SND_NOWAIT);
			}
			return true;

		}
	case ID_CALL_SCORE_TIME:
		{
			if (uTimeCount<=0)	//时间到了
			{
				KillAllTimer();
				//断线
				/*if(USER_CUT_GAME == m_pUserInfo[m_bCurrentOperationStation]->GameUserInfo.bUserState )
				{
					UserSupersedeNote(m_bCurrentOperationStation);
				
					return true;
					}*/
				if (!m_bWatchMode)
					OnCallScore(0,0);

			}
			if (uTimeCount<=5) 
			{
				if(m_pGameInfo->bEnableSound)
					SetPlaySound(SOUND_WARNING_0 - uTimeCount);	
					//PlaySound(TEXT("WARNING"),GetModuleHandle(CLIENT_DLL_NAME),SND_RESOURCE|SND_NOSTOP|SND_ASYNC|SND_NODEFAULT|SND_NOWAIT);
			}
			return true;

		}

	case ID_OUT_CARD:	//出牌
		{
			int iViewStation=ViewStation(bDeskStation);
			if (uTimeCount<=0)	//时间到了
			{

				//断线
				//for (int i = 0; i < PLAY_COUNT; i++)
				//{
				//	if (!m_pUserInfo[i])
				//		continue;
				//	if(m_pUserInfo[i]->GameUserInfo.bUserState==USER_CUT_GAME)

				//		UserSupersedeNote(i);
				////	return true;
				//}
				
				//OnHitActiveResult(TYPE_OPEN,0);
				//判断超时
				if(/*(m_iNowOutPeople==GetMeUserInfo()->bDeskStation) && */(m_bWatchMode==FALSE))
					m_bTimeOutCount++;
				if (m_bTimeOutCount>3 && (m_iNowOutPeople==GetMeUserInfo()->bDeskStation) && (m_bWatchMode==FALSE))
				{
					KillGameTimer(0);
					SendGameData(MDM_GM_GAME_FRAME,ASS_GM_FORCE_QUIT,0);
					SendGameData(MDM_GR_USER_ACTION,ASS_GR_USER_UP,0);
					AFCMessageBox(TEXT("超时次数太多，游戏结束！"),m_pGameInfo->szGameName,AFC_CONFIRM);//,this);
					PostMessage(WM_CLOSE,0,0);
					return false;
				}
				else if(/*m_iNowOutPeople==GetMeUserInfo()->bDeskStation && */!m_bWatchMode)
				{
					CString str;
					//					str.Format("请注意，您已经超时 %d 次了，超时三次会当做逃跑处理。",m_bTimeOutCount);
					//str.Format("请注意，您已经超时，系统自动为您摊牌。");
					m_MessageHandle.InsertNormalMessage("请注意，您已经超时，系统自动为您摊牌。");
					OnHitActiveResult(TYPE_OPEN,0);
				}

				
				return true;
			}
			if ((uTimeCount<=5)&&(m_bWatchMode==FALSE)&&(iViewStation==2)) 
			{
				if(m_pGameInfo->bEnableSound)
					SetPlaySound(SOUND_WARNING_0 - uTimeCount);	
				//					PlaySound(TEXT("WARNING"),GetModuleHandle(CLIENT_DLL_NAME),SND_RESOURCE|SND_NOSTOP|SND_ASYNC|SND_NODEFAULT|SND_NOWAIT);
			}
			return true;
		}
	}
	return true;
}

//按动扑克
LRESULT CClientGameDlg::OnHitCard(WPARAM wparam, LPARAM lparam)
{
	if (GetStationParameter()==GS_PLAY_GAME && !m_bWatchMode)
	{//验证出牌信息
		BYTE iUpCard[39];
		BYTE bView=1;
#ifndef TWO_NN
		bView = 2;
		int iCardCount=m_PlayView.m_UserCard[2].GetUpCard(iUpCard);
#else 
		bView = 1;
		int iCardCount = m_PlayView.m_UserCard[1].GetUpCard(iUpCard);
#endif
		if (m_pGameInfo->bEnableSound)
		{
			SetPlaySound(SOUND_HIT_CARD);
		}

		//出牌数目判断
		if (iCardCount!=3 && iCardCount!=2)
		{
			//m_PlayView.m_btBull.EnableWindow(FALSE);
			return 0;
		}
		//if (!m_PlayView.m_bRightPower && iCardCount!=3)
		//{
		//	//m_PlayView.m_btBull.EnableWindow(FALSE);
		//	return 0;
		//}

		//验证是否可以出这样的扑克
		//if (!m_PlayView.m_bRightPower)
			//m_PlayView.m_btBull.EnableWindow(m_Logic.IsBull(iUpCard,iCardCount));

		if (m_PlayView.m_bRightPower)
		{
			Msg("Test: 从 If 中 Into");

			BYTE card[10];	
			if (iCardCount == 2)
			{
							
				::CopyMemory(card,&m_UserCard[bView],sizeof(m_UserCard[bView]));
				m_Logic.RemoveCard(iUpCard,iCardCount,card,5);

				if (m_Logic.IsBull(card,3))
				{	
					for (int i=0; i<3; i++)
					{
						m_iUpBullCard[bView][i]=card[i];
					}

					OnHitActiveResult(TYPE_BULL, 1);
				}

				m_PlayView.SetShape(bView, m_Logic.GetShape(m_UserCard[bView],5,card));
				m_PlayView.m_btBull.ShowWindow(SW_SHOW);
				m_PlayView.m_btOpen.ShowWindow(SW_SHOW);
				m_PlayView.m_btReset.ShowWindow(SW_SHOW);
				m_PlayView.m_btBull.EnableWindow(TRUE);
				m_PlayView.m_btOpen.EnableWindow(TRUE);
				m_PlayView.m_btReset.EnableWindow(TRUE);

				//if(m_pGameInfo->bEnableSound && m_Logic.GetShape(m_UserCard[bView],5,card) == UG_BULL_BULL)
					//SetNoteSound(TYPE_NN,m_pUserInfo[ViewStation(GetMeUserInfo()->bDeskStation)]->GameUserInfo.bBoy);					//押注声音
			}

			if (iCardCount == 3)
			{
				m_PlayView.SetShape(bView,m_Logic.GetShape(m_UserCard[bView],5,iUpCard));
				if (m_Logic.IsBull(iUpCard,iCardCount))
					OnHitActiveResult(TYPE_BULL, 1);
				m_PlayView.m_btBull.ShowWindow(SW_SHOW);
				m_PlayView.m_btOpen.ShowWindow(SW_SHOW);
				m_PlayView.m_btReset.ShowWindow(SW_SHOW);
				m_PlayView.m_btBull.EnableWindow(TRUE);
				m_PlayView.m_btOpen.EnableWindow(TRUE);
				m_PlayView.m_btReset.EnableWindow(TRUE);

				//if(m_pGameInfo->bEnableSound && NULL!=m_pUserInfo[bView] && m_Logic.GetShape(m_UserCard[bView],5,iUpCard)==UG_BULL_BULL)
					//SetNoteSound(TYPE_NN,m_pUserInfo[bView]->GameUserInfo.bBoy);					//押注声音

			}
		}
		else
		{
			Msg("Test: 从 else 中 Into");
			//m_PlayView.SetShape(bView, m_Logic.GetShape(m_UserCard[bView], 5, iUpCard));
			//if(m_pGameInfo->bEnableSound && NULL!=m_pUserInfo[bView] && m_Logic.GetShape(m_UserCard[bView], 5, iUpCard)==UG_BULL_BULL)
				//SetNoteSound(TYPE_NN, m_pUserInfo[bView]->GameUserInfo.bBoy);					//押注声音

		}

	}
	
	return 0L;
}

//按动扑克
LRESULT CClientGameDlg::OnMouseMove(WPARAM wparam, LPARAM lparam)
{
	//if (GetStationParameter() == GS_PLAY_GAME/*&&m_Ming[GetMeUserInfo()->bDeskStation]*/)
	//{
	//	/*BYTE iCard[5];
	//	int iCount = m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].GetUpCard(iCard);
	//	if (iCount == 0) 
	//	return 0L;
	//	for (int i = 0;i < iCount;i++)
	//	if (m_Logic.GetCardNum(iCard[i]) != 1) 
	//	return 0L;*/
	//	//	SetGameTimer(NULL,3000,ID_LOOK_BACK);
	//	SetTimer(ID_LOOK_BACK,3000,NULL);

	//	m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetCard(m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)],NULL,m_iDeskCardCount[ViewStation(GetMeUserInfo()->bDeskStation)]);
	//}
	return TRUE;;
}
//按动扑克
LRESULT CClientGameDlg::OnMouseLeft(WPARAM wparam, LPARAM lparam)
{
	//if (GetStationParameter() == GS_PLAY_GAME /*&&m_Ming[GetMeUserInfo()->bDeskStation]*/)
	//{
	//	/*BYTE iCard[5];
	//	int iCount = m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].GetUpCard(iCard);
	//	if (iCount == 0) 
	//	return 0L;
	//	for (int i = 0;i < iCount;i++)
	//	if (m_Logic.GetCardNum(iCard[i]) != 1) 
	//	return 0L;*/
	//	//	SetGameTimer(NULL,3000,ID_LOOK_BACK);
	//	SetTimer(ID_LOOK_BACK,3000,NULL);

	//	m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetCard(m_DeskCard[ViewStation(GetMeUserInfo()->bDeskStation)],NULL,m_iDeskCardCount[ViewStation(GetMeUserInfo()->bDeskStation)]);
	//}
	return TRUE;	
}

//用户处理结果
LRESULT CClientGameDlg::OnHitActiveResult(WPARAM wparam, LPARAM lparam)
{
	if (GetStationParameter() == GS_PLAY_GAME)
	{
		int ret = (int) wparam;
		m_PlayView.SetDrawNote();
        
		switch(wparam)
		{
		case TYPE_RESET:	//重排
			if (m_pGameInfo->bEnableSound)
			{
				SetPlaySound(SOUND_CHONG_PAI);
			}
			//m_PlayView.m_btBull.ShowWindow(SW_SHOW&&!m_PlayView.m_bRightPower);
			m_PlayView.m_btBull.ShowWindow(SW_SHOW);
#ifndef TWO_NN
			memset(m_iUpBullCard[2],1,sizeof(m_iUpBullCard));
			m_PlayView.SetShape(2,-1);
			m_PlayView.m_btOpen.ShowWindow(SW_HIDE);    //yl alter/
			m_PlayView.m_btReset.ShowWindow(SW_HIDE);   //yl alter/
			m_PlayView.m_btBull.EnableWindow(TRUE);
			m_PlayView.m_btOpen.EnableWindow(FALSE);    //yl alter/
			m_PlayView.m_btReset.EnableWindow(FALSE);   //yl alter/
			m_PlayView.m_UserCard[2].SetCard(m_DeskCard[2],NULL,m_iDeskCardCount[2]);
			m_PlayView.m_UserBull[2].SetCard(NULL,NULL,0);
			m_PlayView.m_UserCard[2].SetUseMouse(true);
#else
			memset(m_iUpBullCard[1],1,sizeof(m_iUpBullCard));
			m_PlayView.SetShape(1,-1);
			m_PlayView.m_btOpen.ShowWindow(SW_SHOW);
			m_PlayView.m_btBull.EnableWindow(TRUE);
			m_PlayView.m_btOpen.EnableWindow(TRUE);
			m_PlayView.m_btReset.ShowWindow(SW_SHOW);
			m_PlayView.m_btReset.EnableWindow(TRUE);
			m_PlayView.m_UserCard[1].SetCard(m_DeskCard[1],NULL,m_iDeskCardCount[1]);
			m_PlayView.m_UserCard[1].SetUseMouse(true);
			m_PlayView.m_UserBull[1].SetCard(NULL,NULL,0);
			m_PlayView.m_UserCard[1].SetUseMouse(true);
#endif
			break;
		case TYPE_OPEN:	//摊牌
			{
				KillAllTimer();
				m_PlayView.m_btOpen.ShowWindow(SW_HIDE);
				m_PlayView.m_btOpen.EnableWindow(FALSE);
				m_PlayView.m_btBull.ShowWindow(SW_HIDE);
				m_PlayView.m_btBull.EnableWindow(FALSE);
				m_PlayView.m_btReset.ShowWindow(SW_HIDE);
                m_PlayView.m_btReset.EnableWindow(FALSE);///
				

				tagUserProcess process;
				process.iVrebType = TYPE_OPEN;				//类型
				if (m_bAutoBull && m_PlayView.m_UserBull[ViewStation(GetMeUserInfo()->bDeskStation)].GetCardCount() == 0)
				{
					OnHitActiveResult(TYPE_BULL,0);
				}
#ifndef TWO_NN
				::CopyMemory(process.bUpCard,m_iUpBullCard[2],sizeof(m_iUpBullCard[2]));		
#else
				::CopyMemory(process.bUpCard,m_iUpBullCard[1],sizeof(m_iUpBullCard[1]));
#endif
				int itemp = m_Logic.GetShape(m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)],5,m_iUpBullCard[ViewStation(GetMeUserInfo()->bDeskStation)]);

				m_PlayView.SetShape(ViewStation(GetMeUserInfo()->bDeskStation),itemp);
				if (m_pGameInfo->bEnableSound&&itemp>=0)
				{
					SetNoteSound(itemp+SOUND_NO_POINT,GetMeUserInfo()->bBoy);

                    if (itemp == 0)
                    {
                        m_PlayView.m_btOpen.ShowWindow(SW_HIDE);
                        m_PlayView.m_btOpen.EnableWindow(FALSE);
                        m_PlayView.m_btReset.ShowWindow(SW_HIDE);
                        m_PlayView.m_btReset.EnableWindow(FALSE);
                    }
				}
				SendGameData(&process,sizeof(process),MDM_GM_GAME_NOTIFY,ASS_VREB_CHECK,0);
			}
			break;
		case TYPE_BULL:		//提示
			{
				if (m_pGameInfo->bEnableSound)
				{
					SetPlaySound(SOUND_USER_CUE);
				}
				int iView=2;

#ifndef TWO_NN
				iView = 2;
#else
				iView = 1;
#endif

			   // 弹起牛牌
				BYTE card[10],cardBuf[5];
				if (lparam != 1)
				{
					
					if ( !m_Logic.GetBull(m_UserCard[iView], 5, m_iUpBullCard[iView]) )
					{
					
						m_PlayView.SetShape(iView,0);
						m_PlayView.m_btBull.EnableWindow(FALSE);
                        m_PlayView.m_btBull.ShowWindow(SW_HIDE);

                        //yl add 20120817/
                        m_PlayView.m_btOpen.ShowWindow(SW_SHOW);
                        m_PlayView.m_btOpen.EnableWindow(TRUE);
                        m_PlayView.m_btReset.ShowWindow(SW_SHOW);
                        m_PlayView.m_btReset.EnableWindow(TRUE);

						return 0;
					}
					
				}
				else
				{
					int iUpCount = m_PlayView.m_UserCard[iView].GetUpCard(cardBuf);
					::CopyMemory(m_iUpBullCard[iView], cardBuf,sizeof(m_iUpBullCard[iView]));

					if (3==iUpCount)
					{
						;
					}
					else if (2==iUpCount)
					{
						::CopyMemory(card, &m_UserCard[iView], sizeof(m_UserCard[iView]));
						m_Logic.RemoveCard(m_iUpBullCard[iView], 2, card, 5);
						::CopyMemory(m_iUpBullCard[iView], card, sizeof(m_iUpBullCard[iView]));
					}
					else
						return 0;
				}

				if ( !m_Logic.IsBull(m_iUpBullCard[iView], 3) )
					return 0;

				if(1 != lparam)
				{
					OutputDebugString("zhtlog:555");
					m_PlayView.SetShape(iView, m_Logic.GetShape(m_UserCard[iView],5,m_iUpBullCard[iView]));
					//if (m_pGameInfo->bEnableSound && NULL!=m_pUserInfo[iView] && m_Logic.GetShape(m_UserCard[iView],5,m_iUpBullCard[iView])==UG_BULL_BULL)
						//SetNoteSound(TYPE_NN,m_pUserInfo[iView]->GameUserInfo.bBoy);
				}

				::CopyMemory(card,&m_UserCard[iView],sizeof(m_UserCard[iView]));				
				m_PlayView.m_UserBull[iView].SetShowCard(true);
				m_Logic.RemoveCard(m_iUpBullCard[iView], 3, card, 5);
				m_PlayView.m_UserCard[iView].SetCard(m_iUpBullCard[iView], NULL, 3);
				m_PlayView.m_UserBull[iView].SetCard(card, NULL, 2);
				m_PlayView.m_UserCard[iView].SetUseMouse();

				m_PlayView.m_btBull.ShowWindow(SW_HIDE);
				m_PlayView.m_btBull.EnableWindow(FALSE);

                //yl add 20120817/
                m_PlayView.m_btOpen.ShowWindow(SW_SHOW);
                m_PlayView.m_btOpen.EnableWindow(TRUE);
                m_PlayView.m_btReset.ShowWindow(SW_SHOW);
                m_PlayView.m_btReset.EnableWindow(TRUE);
	
				
			}
			break;
		}

	}
	return 0L;
}

//托管
LRESULT CClientGameDlg::OnHitAuto(WPARAM wparam,LPARAM lparam)
{
	return 0;
}
//按动有事按钮函数
LRESULT	CClientGameDlg::OnHitHaveThing(WPARAM wparam, LPARAM lparam)
{
	/*	if (m_PlayView.m_HaveThing.GetSafeHwnd()==NULL) 
	{
	m_PlayView.m_HaveThing.Create(IDD_THING,this);
	m_PlayView.m_HaveThing.m_pParnet=this;
	}
	m_PlayView.m_HaveThing.ShowWindow(SW_SHOW);
	m_PlayView.m_HaveThing.SetFocus();*/
	return 0;
}

//提前结束
LRESULT	CClientGameDlg::OnStop(WPARAM wparam, LPARAM lparam)
{
	/*	if(m_PlayView.m_bMeSide && m_PlayView.m_iGamePoint>=80 && !m_bWatchMode)
	{
	if (m_PlayView.m_StopThing.GetSafeHwnd()==NULL) 
	{
	m_PlayView.m_StopThing.Create(IDD_STOP,this);
	m_PlayView.m_StopThing.m_pParnet=this;
	}
	m_PlayView.m_StopThing.ShowWindow(SW_SHOW);
	m_PlayView.m_StopThing.SetFocus();
	}*/
	return 0;
}

//发送提前结束
LRESULT	CClientGameDlg::OnStopThing(WPARAM wparam, LPARAM lparam)
{
	/*	if(!m_bWatchMode && GetStationParameter()!=GS_WAIT_SETGAME && m_PlayView.m_bMeSide && m_PlayView.m_iGamePoint>=80)
	{
	SendGameData(MDM_GM_GAME_NOTIFY,ASS_STOP_THING,0);
	}*/
	return 0;
}

//同意提前结束
LRESULT	CClientGameDlg::OnAgreeStop(WPARAM wparam, LPARAM lparam)
{
	/*	if(!m_bWatchMode && GetStationParameter()!=GS_WAIT_SETGAME)
	{
	StopResultStruct Stop;
	Stop.bArgee=(BYTE)wparam;
	SendGameData(&Stop,sizeof(Stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);
	}
	*/	return 0;
}


//发送离开请求函数
LRESULT	CClientGameDlg::OnSendHaveThing(WPARAM wparam, LPARAM lparam)
{
	/*	if(!m_bWatchMode && GetStationParameter()!=GS_WAIT_SETGAME)
	{
	m_PlayView.m_btThing.EnableWindow(FALSE);
	HaveThingStruct HaveThing;
	HaveThing.pos=0;
	::strcpy(HaveThing.szMessage,(char *)wparam);
	SendGameData(&HaveThing,sizeof(HaveThing),MDM_GM_GAME_NOTIFY,ASS_HAVE_THING,0);
	}*/
	return 0;
}

//用户请求离开
LRESULT	CClientGameDlg::OnArgeeUserLeft(WPARAM wparam, LPARAM lparam)
{
	/*	LeaveResultStruct Leave;
	Leave.bDeskStation=GetMeUserInfo()->bDeskStation;
	Leave.bArgeeLeave=(BYTE)wparam;
	SendGameData(&Leave,sizeof(Leave),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	*/	return 0;
}



//重置游戏
void CClientGameDlg::ResetGameStation(int iGameStation)
{
	KillAllTimer();
	//数据重置
	m_iNowOutPeople=-1;
	m_iFirstOutPeople=-1;
	m_PlayView.SetWait(false);//取消绘等待贴图
	//界面重置
//	m_PlayView.m_btAuto.EnableWindow(FALSE);
//	m_PlayView.m_btThing.EnableWindow(FALSE);
	m_PlayView.SetDrawNote();
//	m_PlayView.m_btNote.ShowWindow(SW_HIDE);
//	m_PlayView.m_btOver.ShowWindow(SW_HIDE);
	m_PlayView.m_btBull.ShowWindow(SW_HIDE);
	m_PlayView.m_btOpen.ShowWindow(SW_HIDE);
	m_PlayView.m_btReset.ShowWindow(SW_HIDE);
	m_PlayView.m_NtList.ShowWindow(SW_HIDE);

//	m_PlayView.m_btNote.EnableWindow(FALSE);
//	m_PlayView.m_btOver.EnableWindow(FALSE);
	m_PlayView.m_btBull.EnableWindow(FALSE);
	m_PlayView.m_btOpen.EnableWindow(FALSE);
//	m_PlayView.m_btReset.EnableWindow(FALSE);
//	m_PlayView.m_btSplit.EnableWindow(FALSE);
	
	HideButton();
	DelShowThis();
	::memset(m_iUpBullCard,1,sizeof(m_iUpBullCard));
	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));	
	::memset(m_UserCard,0,sizeof(m_UserCard));
	//	m_PlayView.m_ShowNote.ShowWindow(SW_HIDE);

	
	for(int i=0;i<PLAY_COUNT;i++)
	{
		m_PlayView.m_SendCardAnimal[i].SetCard(NULL,0,NULL);
	}

	//for (int i = 0; i < PLAY_COUNT; i++)
	//{
	//	m_PlayView.m_CardShape[i].ShowWindow(SW_HIDE);
	//}

	switch (iGameStation)
	{
	case RS_ALL_VIEW:
		//			KillAllTimer();

		for (int i=0;i<PLAY_COUNT;i++) 
		{

			m_PlayView.SetPass(i,0);
			m_PlayView.SetMing(i,0);
		}

		::memset(m_iTotalGameNote,0,sizeof(m_iTotalGameNote));
		::memset(m_iThisGameNote,0,sizeof(m_iThisGameNote));
		//		m_iThisNoteTimes=0;
		m_PlayView.m_Result.ShowWindow(SW_HIDE);
//		m_PlayView.SetAddNote(0);
		//下注动画所用的筹码数
//		m_PlayView.m_NoteAnimal.SetTotalJeton(0);
		//奖池所用的筹码数
//		for(int i=0;i<50;i++)
//			m_PlayView.m_NoteAll[i].SetTotalJeton(0);
		//设置奖池中筹码堆数
		m_PlayView.SetAddTimes(0);
		//设置各家下注动画初始值
//		for(int i=0;i<PLAY_COUNT;i++)
//			m_PlayView.m_NoteTotal[i].SetTotalJeton(0);
	case RS_GAME_CUT:
		{
			m_PlayView.SetNTStation();
			m_PlayView.m_GameNoteView.SetMessage(NULL);
			/*for (int i=0;i<PLAY_COUNT;i++)
			{
				m_PlayView.m_UserCard[i].SetUseMouse(false);
				m_PlayView.m_UserCard[i].SetCard(NULL,NULL,0);
			}*/
			//系统牌清零
			//m_iSysCardCount=28;
//			m_PlayView.m_SysBackCard.SetCard(NULL,0,NULL);
			//for(int i=0;i<PLAY_COUNT;i++)
			//	m_PlayView.m_SendCardAnimal[i].SetCard(NULL,0,NULL);
			//桌上牌情况
			::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));



			//初始化各玩家押注情况
			for(int i=0;i<PLAY_COUNT;i++)
			{
				m_PlayView.SetNotePoint(i,0);
				//m_PlayView.SetThisTurnNotePoint(i,0);
				m_PlayView.SetGetPoint(i, 0);
				m_PlayView.SetShape(i, -1);
				m_PlayView.SetGetPointSplit(i, 0);
			}
			//初始化总注
//			m_PlayView.SetTotalNote(0,0);
			//初始化本轮上限
			m_PlayView.SetLimitNote(0,0,0);
			m_PlayView.SetMingLImit(0);
			break;
		}
	case RS_GAME_END:
		{
			m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetUseMouse(false);
			memset(m_PlayView.m_bOpenCard,0,sizeof(m_PlayView.m_bOpenCard));
			//for (int i = 0;i < PLAY_COUNT;i++)		
			//{					
			//					m_PlayView.m_EndAnimal[i].ShowWindow(SW_HIDE);
			//					int iViewStation = ViewStation(i);
			//m_PlayView.m_UserCard[i].SetShowCard(true);
			//	m_PlayView.m_UserCard[i].SetCard(m_UserCard[i],NULL,m_iDeskCardCount[i]);
			//}
			//显示系统底
			//				m_PlayView.m_SysBackCard.SetShowCard(true);
			//				m_PlayView.m_SysBackCard.SetCard(m_SysCard,0,m_iSysCardCount);
			//设置各家下注动画初始值
//			for(int i=0;i<PLAY_COUNT;i++)
//				m_PlayView.m_NoteTotal[i].SetTotalJeton(0);
			m_PlayView.m_GameNoteView.SetMessage(NULL);
			break;
		}
	case RS_GAME_BEGIN:
		{
			Msg("jiaofen3: 【4】");

			//m_PlayView.SetNTStation();	//yl alter/修改旁观玩家无庄图标
			m_PlayView.SetDrawNote();
			for (int i=0;i<PLAY_COUNT;i++) 
			{
				
				m_PlayView.m_UserCard[i].SetUseMouse(false);
				m_PlayView.m_UserCard[i].SetCard(NULL,NULL,0);
				m_PlayView.m_UserBull[i].SetUseMouse(false);
				m_PlayView.m_UserBull[i].SetCard(NULL,NULL,0);
				m_PlayView.SetPass(i,0);
				m_PlayView.SetGetPoint(i, 0);
				m_PlayView.SetShape(i, -1);

				if (m_bWatchMode) 
				{
					m_PlayView.m_CardShape[i].ShowWindow(SW_HIDE);
				}
			}
			//清除发牌标记
			memset(m_PlayView.m_bIsSendCard,0,sizeof(m_PlayView.m_bIsSendCard));
			memset(m_PlayView.m_bIsNote,0,sizeof(m_PlayView.m_bIsNote));
			memset(m_PlayView.m_bOpenCard,0,sizeof(m_PlayView.m_bOpenCard));
			
			//桌上牌情况
			::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));
			::memset(m_iThisGameNote,0,sizeof(m_iThisGameNote));
			::memset(m_iTotalGameNote,0,sizeof(m_iTotalGameNote));
			m_PlayView.m_Result.ShowWindow(SW_HIDE);
//			m_PlayView.SetAddNote(0);
			//下注动画所用的筹码数
//			m_PlayView.m_NoteAnimal.SetTotalJeton(0);
			//奖池所用的筹码数
//			for(int i=0;i<50;i++)
//				m_PlayView.m_NoteAll[i].SetTotalJeton(0);
			//设置奖池中筹码堆数
			m_PlayView.SetAddTimes(0);
			//设置各家下注动画初始值
//			for(int i=0;i<PLAY_COUNT;i++)
//				m_PlayView.m_NoteTotal[i].SetTotalJeton(0);
			//初始化各玩家押注情况
			for(int i=0;i<PLAY_COUNT;i++)
			{
				m_PlayView.SetNotePoint(i,0);
				//m_PlayView.SetThisTurnNotePoint(i,0);
			}
			//初始化总注
//			m_PlayView.SetTotalNote(0,0);
			//初始化本轮上限
			m_PlayView.SetLimitNote(0,0,0);
			m_PlayView.SetMingLImit(0);

			//			if (m_PlayView.m_GameSet.GetSafeHwnd()) m_PlayView.m_GameSet.DestroyWindow();
			//			if (m_PlayView.m_GameEndView.GetSafeHwnd()) m_PlayView.m_GameEndView.DestroyWindow();
			break;
		}
	}
	return;
}

void CClientGameDlg::OnGameSetting()
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
#ifdef SUPER_VERSION
	AfxSetResourceHandle(GetModuleHandle("DllForGame.dll"));
	if (m_bIsSuper)
	{
		if (m_Control.GetSafeHwnd() == NULL)
		{
			m_Control.Create(IDD_CONTROLWIN,this);
			m_Control.SetParentWnd(this);
		}
		m_Control.ShowWindow(SW_SHOW);
		m_Control.CenterWindow();
		AfxSetResourceHandle(NULL);
		return;
	}
#endif
#ifdef SENDCARD_VERSION
	AfxSetResourceHandle(GetModuleHandle("DllForGame.dll"));
	{

		if (m_SetCard == NULL)
		{
			m_SetCard = new CCardSet();
			m_SetCard->Create(IDD_CARD_SET,this);
			m_SetCard->CenterWindow();
			m_SetCard->ShowWindow(SW_SHOW);
		}
		else
		{
			m_SetCard->UpdateComboBox();
			m_SetCard->ShowWindow(SW_SHOW);
		}

		//dlg->DoModal();
	}
	

	AfxSetResourceHandle(NULL);
	return ;
#endif
	
	CGameSet GameSetDlg(this);
	GameSetDlg.m_bSound=m_pGameInfo->bEnableSound;
	GameSetDlg.m_bShowUser=m_pGameInfo->bShowUserInfo;	
	GameSetDlg.m_bEnableWatch=m_pGameInfo->bEnableWatch;
	GameSetDlg.m_bRightPower=TRUE;//GetProfileInt(TEXT("RightPower"),FALSE);
	
	//if (GameSetDlg.DoModal()==IDOK)
	int reval =  GameSetDlg.DoModal();

	if (reval == IDOK)
	{
		//定义参数
		bool bSendWatch=((m_bWatchMode==false)&&(m_pGameInfo->bEnableWatch!=GameSetDlg.m_bEnableWatch));

		//保存数据
		m_pGameInfo->bShowUserInfo=GameSetDlg.m_bShowUser;
		m_pGameInfo->bEnableWatch=GameSetDlg.m_bEnableWatch;
		m_pGameInfo->bEnableSound=GameSetDlg.m_bSound;
		WriteProfileInt(TEXT("RightPower"),GameSetDlg.m_bRightPower?1:0);
		m_PlayView.m_bRightPower=GameSetDlg.m_bRightPower;

		//发送数据
		if (bSendWatch==true)
		{
			MSG_GM_WatchSet WatchSet;			
			memset(&WatchSet,0,sizeof(WatchSet));
			WatchSet.dwUserID=0;
			SendGameData(&WatchSet,sizeof(WatchSet),MDM_GM_GAME_FRAME,ASS_GM_WATCH_SET,GameSetDlg.m_bEnableWatch?TRUE:FALSE);
		}
	}
	//AfxSetResourceHandle(GetModuleHandle(NULL));
	return;
}

void CClientGameDlg::OnWatchSetChange(void)
{
	if (m_bWatchMode==true)
	{
		m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetShowCard(m_bWatchOther?TRUE:FALSE);//20090414旁观看牌设置zht
		if (m_bWatchOther)	m_MessageHandle.InsertNormalMessage(TEXT("玩家允许您旁观他游戏"));
		else m_MessageHandle.InsertNormalMessage(TEXT("玩家不允许您旁观他游戏"));
	}
}

//用户离开
bool CClientGameDlg::GameUserLeft(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser)
{
	/*	if ((bWatchUser==false)&&(pUserItem!=NULL)&&(bDeskStation==0))
	{
	if (GetStationParameter()==GS_WAIT_ARGEE)
	{
	for (int i=0;i<4;i++)
	{
	if (m_pUserInfo[i]!=NULL) 
	{
	m_pUserInfo[i]->GameUserInfo.bUserState=USER_SITTING;
	m_UserListDlg.UpdateGameUser(m_pUserInfo[i]);
	}
	}
	if (m_PlayView.m_GameInfo.GetSafeHwnd()) m_PlayView.m_GameInfo.DestroyWindow();
	m_PlayView.m_GameNoteView.SetMessage(TEXT("正在等待东家设置牌局"));
	m_PlayView.UpdateViewFace(NULL);
	}
	}*/
	//	if ((bWatchUser==false)&&(pUserItem!=NULL)&&(bDeskStation==0))		//如果是东家离开
	//	{
	/*if (GetStationParameter()>GS_WAIT_ARGEE)
	{
		for (int i=0;i<PLAY_COUNT;i++)
		{
			if (m_pUserInfo[i]!=NULL) 
			{
				m_pUserInfo[i]->GameUserInfo.bUserState=USER_SITTING;
				m_UserListDlg.UpdateGameUser(m_pUserInfo[i]);
			}
		}
		m_PlayView.UpdateViewFace(NULL);
	}*/
	//m_PlayView.SetNTStation();

	//m_PlayView.m_UserCard[ViewStation(bDeskStation)].ShowWindow(SW_HIDE);
	//	}
	//当前玩家离开看此玩家牌的玩家也随之离开房间
	if(GetMeUserInfo()->bDeskStation==bDeskStation&&pUserItem!=NULL&&!bWatchUser==TRUE)
	{
		//	MessageBox("您观看的玩家,已经退出.","系统提示",MB_ICONQUESTION);
		OnCancel();
		//PostMessage(WM_CLOSE,0,0);
	}

	if(m_pGameInfo->bEnableSound)	//离开音效
	{
		SetPlaySound(SOUND_USER_LEAVE);
	}
	return __super::GameUserLeft(bDeskStation,pUserItem,bWatchUser);
}

void CClientGameDlg::OnTimer(UINT nIDEvent)
{
	int iAllCount = 0 ;
	for(int i = 0 ; i<PLAY_COUNT ;i++)
	{
		if(NULL != m_pUserInfo[i] && m_iDeskCardCount[ViewStation(i)] == 5)
		{
			iAllCount ++ ; 
		}
		CString str;
		str.Format("wysm_iDeskCardCount[%d]=%d,i=%d",ViewStation(i),m_iDeskCardCount[ViewStation(i)],i);
		OutputDebugString(str);
	}
	CString strr;
	strr.Format("wys423定时器处理::当前定时器===%d",nIDEvent);
	OutputDebugString(strr);
	
	if ((nIDEvent>=ID_SEND_CARD_ANIMAL) && (nIDEvent<(ID_SEND_CARD_ANIMAL+PLAY_COUNT)))
	{
		CString str;
		str.Format("wys423::Ontimer::iAllCount===%d,m_iSendAnimaCardPos==%d，m_iSendCardTotle==%d",iAllCount,m_iSendAnimaCardPos,m_iSendCardTotle);
		OutputDebugString(str);
		
		
		KillTimer(nIDEvent);		
		int desk = nIDEvent-ID_SEND_CARD_ANIMAL;
		
		m_DeskCard[desk][(m_iSendCardTotle/iAllCount)%5] = (ViewStation(GetMeUserInfo()->bDeskStation)==desk)?m_UserCard[desk][(m_iSendCardTotle/iAllCount)%5]:0;
		m_PlayView.m_SendCardAnimal[desk].StopMove();
		m_PlayView.m_SendCardAnimal[desk].ShowWindow(SW_HIDE);
		Msg("qlog%d: view %d", GetMeUserInfo()->bDeskStation, desk);
		m_PlayView.m_UserCard[desk].SetCard(m_DeskCard[desk],NULL,(m_iSendCardTotle/iAllCount)%5+1);

		if(m_pGameInfo->bEnableSound)
		{
			SetPlaySound(SOUND_SEND_CARD);
		}

		m_iSendCardTotle ++;

		if(m_iSendCardTotle<iAllCount *5)
		{			
			//m_iSendAnimaCardPos = GetNetUserPos(m_iSendAnimaCardPos);
			m_iSendAnimaCardPos = (m_iSendAnimaCardPos+1)%PLAY_COUNT;
			while(NULL == m_pUserInfo[m_iSendAnimaCardPos]||m_iDeskCardCount[ViewStation(m_iSendAnimaCardPos)]==0)
			{
				m_iSendAnimaCardPos = (m_iSendAnimaCardPos+1)%PLAY_COUNT;
			}

			m_PlayView.SendCard(ViewStation(m_iSendAnimaCardPos),150);		

			SetTimer(ID_SEND_CARD_ANIMAL+ViewStation(m_iSendAnimaCardPos),150,NULL);
		}

		return ;

	}
	switch(nIDEvent)
	{
	case ID_LOOK_BACK:
		m_PlayView.m_UserCard[ViewStation(GetMeUserInfo()->bDeskStation)].SetCard(m_DeskCard[ViewStation(GetMeUserInfo()->bDeskStation)],NULL,m_iDeskCardCount[ViewStation(GetMeUserInfo()->bDeskStation)]);
		KillTimer(ID_LOOK_BACK);
		break;
	case ID_BEGIN_ANIMAL:
		m_PlayView.BeginAnimal();
		break;
	case  ID_NOTE_ANIMAL_ZERO:							//下注动画
		{
			m_PlayView.NoteAnimal(0);
			break;
		}
	case ID_NOTE_ANIMAL_ONE:							//下注动画
		{
			m_PlayView.NoteAnimal(1);
			break;
		}
	case ID_NOTE_ANIMAL_TWO:								//下注动画
		{
			m_PlayView.NoteAnimal(2);
			break;
		}
	case ID_NOTE_ANIMAL_THREE://下注动画
		{
			//			m_PlayView.m_NoteAnimal.ShowWindow(SW_SHOW);
			m_PlayView.NoteAnimal(3);
			break;
		}
	case ID_COLLECT_JETON_ANIMAL://收集筹码动画
		{
			//			m_PlayView.m_NoteAnimal.ShowWindow(SW_SHOW);
			m_PlayView.CollectJetonAnimal();

			break;
		}
	//case ID_SEND_CARD_ANIMAL:
	//	{
	//		m_PlayView.SendCardAnimal(m_bShowAnimalStation);
	//		break;
	//	}

	default:
		break;
	}
	CLoveSendClassInExe::OnTimer(nIDEvent);
}


void CClientGameDlg::OnCancel()
{

	/*if(GetComType() == TY_MONEY_GAME)
		wsprintf(sz,"现在退出将会被托管,您真的要退出吗?",m_iRunPublish,m_iRunPublish * m_iRoomBasePoint);
	else
		wsprintf(sz,"现在退出将会被扣所有下注X5，庄家则扣除所有闲家总注X5,您真的要退出吗?",m_iRunPublish);*/

	//char cKey[10];
	//CString sPath=CBcfFile::GetAppPath();
	//int iResult = 1;
	//if (CBcfFile::IsFileExist(/*sPath + */"..\\SpecialRule.bcf"))
	//{
	//	CBcfFile fsr( /*sPath + */"..\\SpecialRule.bcf");
	//	wsprintf(cKey, "%d", NAME_ID);
	//	iResult = fsr.GetKeyVal (_T("ForceQuitAsAuto"), cKey, 0);
	//}

	//if (iResult)
	//{

	//	wsprintf(sz,"现在退出将会被扣所有下注X5，庄家则扣除所有闲家总注X5,您真的要退出吗?");
	//}
	//else
	//{
	//	wsprintf(sz,"下注后退出将会被托管,您真的要退出吗");
	//}
	

	//查询状态
	if (!m_bWatchMode && GetStationParameter()>=GS_SEND_CARD&&GetStationParameter() < GS_WAIT_NEXT && m_bPlayer)
	{
		TCHAR sz[200];
		char cKey[10];
		//CString sPath=CBcfFile::GetAppPath();
		int iResult = 1;
		if (CBcfFile::IsFileExist( "..\\SpecialRule.bcf"))
		{
			CBcfFile fsr( "..\\SpecialRule.bcf");
			sprintf(cKey, "%d", NAME_ID);
			iResult = fsr.GetKeyVal (_T("ForceQuitAsAuto"), cKey, 0);
		}

		if (iResult)
			wsprintf(sz,TEXT("您正在游戏中，现在退出游戏自动托管.您真得要退出吗?"));

		else
		{
			if (m_pGameInfo->uComType == 1)
			{
				wsprintf(sz,TEXT("您正在游戏中，现在退出将会被扣积分，是否要退出游戏？"));
			}
			else
			{
				wsprintf(sz,TEXT("您正在游戏中，现在退出将会被扣金币，是否要退出游戏？"));
			}
		}


		if (IDOK!=AFCMessageBox(sz,m_pGameInfo->szGameName,AFC_YESNO)) //|MB_DEFBUTTON2|MB_ICONINFORMATION,this)) 
			return;
		SendGameData(MDM_GM_GAME_FRAME,ASS_GM_FORCE_QUIT,0);
	}

	m_bPlayer        = FALSE;
	KillAllTimer();
	AFCCloseFrame();
	//	if(hmciwnd)
	//		MCIWndDestroy(hmciwnd);
	__super::OnCancel();
}

//修改用户押注情况
BOOL CClientGameDlg::ModifyNote(BYTE iViewStation,int iCurNote,BOOL bExtVal)
{
	//追加本轮某方押注情况
	m_PlayView.AddNotePoint(iViewStation,iCurNote);
	//总注累加
//	m_PlayView.AddTotalNote(0,iCurNote);
	return true;
}

////用户押注声音
//BOOL CClientGameDlg::SetNoteSound(BYTE bNoteStyle,BOOL bIsBoy)
//{
//	TCHAR str[MAX_PATH+1]="";
//	TCHAR filename[MAX_PATH];//path[MAX_PATH];
//	CString s=CINIFile::GetAppPath ();/////本地路径
//	CINIFile f( s + "cardsound.ini");
//	CString key = TEXT("wznnnote");
//	//	TCHAR path[MAX_PATH];
//	CString folder,extendname,name;
//	folder=f.GetKeyVal(key,"folder","music\\cardwav\\wznn\\");
//	extendname=f.GetKeyVal(key,"extendname",".wav");
//	TCHAR Val[50];
//	srand(GetCurrentTime());
//	int count =f.GetKeyVal(key,"count",1);
//	switch(bNoteStyle)
//	{
//		/*case TYPE_OPENCARD:
//		{	
//		wsprintf(Val,"%c(open%d)",bIsBoy?'b':'g',rand()%count);
//		name = f.GetKeyVal(key,Val,Val);
//		break;
//		}
//		case TYPE_FOLLOW:
//		{
//		wsprintf(Val,"%c(follow%d)",bIsBoy?'b':'g',rand()%count);
//		name = f.GetKeyVal(key,Val,Val);
//		break;
//		}
//		case TYPE_BULL:
//		{
//		wsprintf(Val,"%c(add%d)",bIsBoy?'b':'g',rand()%count);
//		name = f.GetKeyVal(key,Val,Val);
//		break;
//		}*/
//	case TYPE_NOTE:
//		{
//			wsprintf(Val,"%c(note%d)",bIsBoy?'b':'g',rand()%count);
//			name = f.GetKeyVal(key,Val,Val);
//			break;
//		}
//	case TYPE_GIVE_UP:
//		{
//			wsprintf(Val,"%c(pass%d)",bIsBoy?'b':'g',rand()%count);
//			name = f.GetKeyVal(key,Val,Val);
//			break;
//		}	
//	default:
//		{
//			wsprintf(str,"%c(def)",bIsBoy?'b':'g');
//			name = f.GetKeyVal(key,Val,Val);
//			break;
//		}
//
//	}
//	wsprintf(filename,"%s%s%s",folder,name,extendname);
//	PlayOutCardType(filename,m_hMciWnd1);
//	return true;
//}
//
//BOOL CClientGameDlg::SetPlaySound(BYTE bSoundStyle,BOOL bExtVal)
//{
//	CString s=CINIFile::GetAppPath ();/////本地路径
//	CINIFile f( s + "cardsound.ini");
//	CString key = TEXT("system");
//	CString folder,filename;
//	folder=f.GetKeyVal(key,"folder","music\\cardwav\\");
//	TCHAR fi[MAX_PATH+1];
//	switch(bSoundStyle)
//	{
//	case SOUND_WARNING:
//		{
//			filename = f.GetKeyVal(key,"warning","warning");
//			break;
//		}
//	case SOUND_INVALIDATE:
//		{
//			filename = f.GetKeyVal(key,"invalidate","invalidate");
//			break;
//		}
//	case SOUND_SEND_CARD:
//		{
//			filename = f.GetKeyVal(key,"sendcard","sendcard");
//			break;
//		}
//	}
//	wsprintf(fi,"%s%s%s",folder,filename,".wav");
//	::PlaySound(fi,NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP|SND_NOWAIT|SND_NODEFAULT);
//	return true;
//}
//
////设置出牌牌型声音
//BOOL CClientGameDlg::SetOutCardTypeSound(BYTE iCardList[],int iCardCount,BOOL IsBoy)
//{
//	int cardshape = m_Logic.GetCardShape(iCardList,iCardCount);
//	//	int cardstart,cardend;
//	//	TCHAR filename[MAX_PATH],
//	TCHAR str[100]="";
//	TCHAR filename[MAX_PATH];//path[MAX_PATH];
//	CString s=CINIFile::GetAppPath ();/////本地路径
//	CINIFile f( s + "cardsound.ini");
//	CString key = TEXT("type0");
//	//	TCHAR path[MAX_PATH];
//	CString folder,extendname,name;
//	folder=f.GetKeyVal(key,"folder","music\\cardwav\\type0\\");
//	extendname=f.GetKeyVal(key,"extendname",".mp3");
//
//
//	if(IsBoy)
//	{
//		wsprintf(str,"b(def)");
//	}
//	else
//		wsprintf(str,"g(def)");
//
//	name=f.GetKeyVal(key,str,str);
//	wsprintf(filename,"%s%s%s",folder,name,extendname);
//
//	PlayOutCardType(filename,m_hMciWnd1);
//
//	//::PlaySound(filename,NULL,SND_FILENAME|SND_ASYNC|SND_NOWAIT|SND_NODEFAULT);
//
//	return TRUE;
//}
////播放场景声音
//BOOL CClientGameDlg::SetSenceSound(BYTE iSendSound,BOOL IsBoy,int iVal)
//{
//	TCHAR str[100]="";
//	TCHAR filename[MAX_PATH];//path[MAX_PATH];
//	CString s=CINIFile::GetAppPath ();/////本地路径
//	CINIFile f( s + "cardsound.ini");
//	CString key = TEXT("cardsence");
//	//	TCHAR path[MAX_PATH];
//	CString folder,extendname,name;
//	folder=f.GetKeyVal(key,"folder","music\\cardwav\\sence\\");
//	extendname=f.GetKeyVal(key,"extendname",".mp3");
//
//	//	TCHAR filename[MAX_PATH],str[100]="";
//	srand(GetCurrentTime());
//	int count;
//	switch(iSendSound)
//	{
//	case SOUND_WIN://胜利
//		if(IsBoy)
//		{	
//			count = f.GetKeyVal(key,"bwincount",10);
//			wsprintf(str,"b(win%d)",rand()%count);
//		}
//		else
//		{
//			count = f.GetKeyVal(key,"gwincount",10);
//			wsprintf(str,"g(win%d)",rand()%count);
//		}
//		break;
//	case SOUND_LOSE://失败
//		if(IsBoy)
//		{
//			count = f.GetKeyVal(key,"blosecount",10);
//			wsprintf(str,"b(lose%d)",rand()%count);
//		}
//		else
//		{
//			count = f.GetKeyVal(key,"glosecount",10);
//			wsprintf(str,"g(lose%d)",rand()%count);
//		}
//		break;
//	case SOUND_WAITING://等待
//		if(IsBoy)
//		{
//			count = f.GetKeyVal(key,"bwaitcount",10);
//			wsprintf(str,"b(wait%d)",rand()%count);
//		}
//		else
//		{
//			count = f.GetKeyVal(key,"gwaitcount",10);
//			wsprintf(str,"g(wait%d)",rand()%count);
//		}
//		break;
//	case SOUND_ERROR://出牌出错了
//		if(IsBoy)
//		{
//			count = f.GetKeyVal(key,"berrorcount",10);
//			wsprintf(str,"b(error%d)",rand()%count);
//		}
//		else
//		{
//			count = f.GetKeyVal(key,"gerrorcount",10);
//			wsprintf(str,"g(error%d)",rand()%count);
//		}
//		break;
//	case SOUND_READY://准备
//		if(IsBoy)
//		{
//			count = f.GetKeyVal(key,"breadycount",10);
//			wsprintf(str,"b(ready%d)",rand()%count);
//		}
//		else
//		{
//			count = f.GetKeyVal(key,"greadycount",10);
//			wsprintf(str,"g(ready%d)",rand()%count);
//		}
//		break;
//	case SOUND_START://开始游戏(随机)
//		if(IsBoy)
//		{
//			count = f.GetKeyVal(key,"bstartcount",10);
//			wsprintf(str,"b(start%d)",rand()%count);
//		}
//		else
//		{
//			count = f.GetKeyVal(key,"gstartcount",10);
//			wsprintf(str,"g(start%d)",rand()%count);
//		}
//		break;
//	case SOUND_JIAO_FEN://叫分
//		{
//			if(IsBoy)
//				wsprintf(str,"b(jiaofen%d)",iVal);
//			else
//				wsprintf(str,"g(jiaofen%d)",iVal);
//		}
//	case SOUND_OUT_CARD_FINISH://出完牌
//		{
//			if(IsBoy)
//			{
//				count = f.GetKeyVal(key,"boutcardfinishcount",10);
//				wsprintf(str,"b(outcardfinish%d)",rand()%count);
//			}
//			else
//			{
//				count = f.GetKeyVal(key,"goutcardfinishcount",10);
//				wsprintf(str,"g(outcardfinish%d)",rand()%count);
//			}
//			break;
//		}
//	case SOUND_FRIEND_APPEAR://盟友出現
//		{
//			if(IsBoy)
//			{
//				count = f.GetKeyVal(key,"bfriendcount",10);
//				wsprintf(str,"b(friend%d)",rand()%count);
//			}
//			else
//			{
//				count = f.GetKeyVal(key,"gfriendcount",10);
//				wsprintf(str,"g(friend%d)",rand()%count);
//			}
//			break;
//		}
//	case SOUND_USER_RUNAWARY:	//逃跑
//		{
//			if(IsBoy)
//			{
//				count = f.GetKeyVal(key,"brunawarycount",10);
//				wsprintf(str,"b(runawary%d)",rand()%count);
//			}
//			else
//			{
//				count = f.GetKeyVal(key,"grunawarycount",10);
//				wsprintf(str,"g(runawary%d)",rand()%count);
//			}
//			break;
//		}
//	case SOUND_USER_LEFT:	//有人离开
//		{
//			if(IsBoy)
//			{
//				count = f.GetKeyVal(key,"bleftcount",10);
//				wsprintf(str,"b(left%d)",rand()%count);
//			}
//			else
//			{
//				count = f.GetKeyVal(key,"gleftcount",10);
//				wsprintf(str,"g(left%d)",rand()%count);
//			}
//			break;
//		}
//	case SOUND_GIVE_BACK://埋底
//		{
//			if(IsBoy)
//			{
//				count = f.GetKeyVal(key,"bgivebackcount",10);
//				wsprintf(str,"b(giveback%d)",rand()%count);
//			}
//			else
//			{
//				count = f.GetKeyVal(key,"ggivebackcount",10);
//				wsprintf(str,"g(giveback%d)",rand()%count);
//			}
//			break;
//		}
//	default:
//		if(IsBoy)
//			wsprintf(str,"b(sence_0)");
//		else
//			wsprintf(str,"g(sence_0)");
//		break;
//	}
//	name=f.GetKeyVal(key,str,str);
//	wsprintf(filename,"%s%s%s",folder,name,extendname);
//	PlayOutCardType(filename,m_hMciWnd2);
//	return TRUE;
//}
////播放Mp3音乐
//BOOL CClientGameDlg::PlayOutCardType(TCHAR FileName[],HWND hmciwnd)
//{
//	if(hmciwnd)
//	{
//		MCIWndStop(hmciwnd);
//		MCIWndDestroy(hmciwnd);
//		hmciwnd=NULL;
//	}
//
//	//hmciwnd = MCIWndCreate(this->m_hWnd,AfxGetInstanceHandle(),WS_CHILD,FileName);
//
//	hmciwnd=MCIWndCreate(this->m_hWnd,AfxGetInstanceHandle(),WS_CHILD|MCIWNDF_NOMENU|MCIWNDF_NOOPEN|MCIWNDF_NOPLAYBAR|MCIWNDF_NOERRORDLG,FileName);
//	if(hmciwnd)
//		MCIWndPlay(hmciwnd);	
//	return true;
//}
////函数定义
BOOL CClientGameDlg::CheckVersion(BYTE iVersion,BYTE iVersion2)
{	
	TCHAR GameName[200];
	CString strBuffer;
	wsprintf(GameName,"您的 %s 游戏版本过旧,您要现在重新下载新版本吗?",m_pGameInfo->szGameName);
	if(iVersion!=m_iVersion || iVersion2!=m_iVersion2)
	{
		TCHAR sz[200];
		wsprintf(sz,"版本冲突:当前版本%d-%d,服务端版本%d-%d",m_iVersion,m_iVersion2,iVersion,iVersion2);
	}
	if(iVersion!=m_iVersion)
	{

		if (IDOK==AFCMessageBox(GameName,m_pGameInfo->szGameName,AFC_YESNO)) //|MB_DEFBUTTON1|MB_ICONINFORMATION,this)) 
		{
			strBuffer.Format(TEXT(Glb().m_CenterServerPara.m_strDownLoadSetupADDR),1,1);
			ShellExecute(NULL,TEXT("open"),strBuffer,NULL,NULL,SW_MAXIMIZE);
		}
		PostMessage(WM_CLOSE,0,0);
		return TRUE;
	}

	if(iVersion2!=m_iVersion2)
	{
		if (IDOK==AFCMessageBox(GameName,m_pGameInfo->szGameName,AFC_YESNO)) //|MB_DEFBUTTON1|MB_ICONINFORMATION,this)) 
		{
			strBuffer.Format(TEXT(Glb().m_CenterServerPara.m_strDownLoadSetupADDR),1,1);
			ShellExecute(NULL,TEXT("open"),strBuffer,NULL,NULL,SW_MAXIMIZE);
		}
		PostMessage(WM_CLOSE,0,0);
		return TRUE;
	}

	return TRUE;
}
//用户下注
LRESULT CClientGameDlg::OnShowNote(WPARAM wparam,LPARAM lparam)
{
	m_PlayView.m_NtList.ShowWindow(TRUE);
	m_PlayView.m_NtList.SetNumList(m_iThisTurnLimit, m_iBaseNote);				//更新下注数目
	return TRUE;
}
//用户选择下注数
LRESULT CClientGameDlg::OnSelectNote(WPARAM wparam,LPARAM lparam)
{
	int ret = (int)wparam;
	if ((int)lparam == 15 )
	{
		m_PlayView.m_NtList.ShowWindow(SW_HIDE);

		return true;
	}
	if(ret<=0)
		ret=0;
	m_PlayView.SetDrawNote();
	m_PlayView.m_NtList.ShowWindow(SW_HIDE);

	KillAllTimer();

	__int64 Num = 0;
	switch(ret)
	{
	case 1:
		if (m_PlayView.m_GameType == 1)              //游戏种类。0为普通。1为同喜乐
		{
			Num = m_PlayView.m_iNoteLimit/100*100;
		}
		else
		{
			Num = m_PlayView.m_iNoteLimit;
		}
		break;
	case 2:
		if (m_PlayView.m_GameType == 1)              //游戏种类。0为普通。1为同喜乐
		{
			Num = m_PlayView.m_iNoteLimit/125*100;
		}
		else
		{
			if (m_PlayView.m_iGameNoteSetType>0)
			{
				Num = m_PlayView.m_iNoteLimit/2;
			}
			else
			{
				Num = m_PlayView.m_iNoteLimit/1.25;
			}

		}
		break;
	case 3:

		if (m_PlayView.m_GameType == 1)              //游戏种类。0为普通。1为同喜乐
		{
			Num = m_PlayView.m_iNoteLimit/250*100;
		}
		else
		{
			if (m_PlayView.m_iGameNoteSetType>0)
			{
				Num = m_PlayView.m_iNoteLimit/4;
			}
			else
			{
				Num = m_PlayView.m_iNoteLimit/2.5;
			}

		}
		break;
	case 4:

		if (m_PlayView.m_GameType == 1)              //游戏种类。0为普通。1为同喜乐
		{
			Num = m_PlayView.m_iNoteLimit/500*100;
		}
		else
		{
			if (m_PlayView.m_iGameNoteSetType>0)
			{
				Num = m_PlayView.m_iNoteLimit/8;
			}
			else
			{
				Num =m_PlayView.m_iNoteLimit/5;
			}

		}
		break;
	}
	//Msg("zhtlog:Num=%I64d ret=%d m_PlayView.m_GameType =%d m_PlayView.m_iGameNoteSetType=%d",Num,ret,m_PlayView.m_GameType,m_PlayView.m_iGameNoteSetType );
	tagUserProcess process;
	process.iVrebType =(int)lparam;//ret;				//下注类型
	process.iNote=Num;						//下注数(只有下注和加注才设置此值)
	if (GetStationParameter() ==GS_PLAY_GAME)
		SendGameData(&process,sizeof(process),MDM_GM_GAME_NOTIFY,ASS_VREB_CHECK,0);
	SendGameData(&process,sizeof(process),MDM_GM_GAME_NOTIFY,ASS_BEGIN_UPGRADE,0);
	return TRUE;
}


//发牌动画显示完毕后,显示各家牌
LRESULT CClientGameDlg::SendCardShowCard(WPARAM wparam,LPARAM lparam)
{
	BYTE iViewStation=(BYTE)wparam;
	//	m_PlayView.m_UserCard[m_PlayView.m_flag].SetCard(m_DeskCard[m_PlayView.m_flag],NULL,m_iDeskCardCount[m_PlayView.m_flag]);

	//系统管理员显示各家底牌
	/*if(m_pGameInfo->pMeUserInfo->GameUserInfo.bGameMaster==MAST_PEOPLE)
		m_PlayView.m_UserCard[iViewStation].SetCard(m_UserCard[iViewStation],NULL,m_iDeskCardCount[iViewStation]);*/
	return 0;
#ifdef SUPER_VERSION
	m_PlayView.m_UserCard[iViewStation].SetCard(m_UserCard[iViewStation],NULL,m_iDeskCardCount[iViewStation]);

#endif
}

//用戶換底牌
LRESULT CClientGameDlg::ChangeBackCard()
{
	if (GetStationParameter()==GS_PLAY_GAME&&!m_bWatchMode)
	{
		ChangeBackStruct change;
		change.bDeskStation=GetMeUserInfo()->bDeskStation ;
		change.bSourceCard=m_UserCard[GetMeUserInfo()->bDeskStation][0];
		change.bResultCard=0x3d;
		SendGameData(&change,sizeof(change),MDM_GM_GAME_NOTIFY,ASS_GM_SUPERCLIENT,0);
	}
	return 0;
}

//桌号换算到视图位置 zxj 2009-11-21 打开注释并修改内容
BYTE CClientGameDlg::ViewStation(BYTE bDeskStation)
{
	return __super::ViewStation(bDeskStation);	//抛弃原来注释掉的部分，添加此句按钮
//	BYTE bViewStation=m_pGameInfo->pMeUserInfo->GameUserInfo.bDeskStation;
//	int temp=((PLAY_COUNT/2)-bViewStation+bDeskStation);
//	if(temp>=0)
//		return temp%PLAY_COUNT;
//	else
//		return PLAY_COUNT-1;
//switch(bViewStation)
//	{
//	case 0: { 
//		if(bDeskStation==0)	
//			return 3;
//		if(bDeskStation==1)
//			return 4;
//		if(bDeskStation==2)
//			return 5;
//		if(bDeskStation==3)
//			return 0;
//		if(bDeskStation==4)
//			return 1;
//		if(bDeskStation==5)
//			return 2;
//		break;
//			}
//	case 1: {
//		if(bDeskStation==0)	
//			return 2;
//		if(bDeskStation==1)
//			return 3;
//		if(bDeskStation==2)
//			return 4;
//		if(bDeskStation==3)
//			return 5;
//		if(bDeskStation==4)
//			return 0;
//        if(bDeskStation==5)
//			return 1;
//		break;
//			}
//	case 2: { 
//		if(bDeskStation==0)	
//			return 1;
//		if(bDeskStation==1)
//			return 2;
//		if(bDeskStation==2)
//			return 3;
//		if(bDeskStation==3)
//			return 4;
//		if(bDeskStation==4)
//			return 5;
//		if(bDeskStation==5)
//			return 0;
//		break;
//			}
//	case 3: { 
//		if(bDeskStation==0)	
//			return 0;
//		if(bDeskStation==1)
//			return 1;
//		if(bDeskStation==2)
//			return 2;
//		if(bDeskStation==3)
//			return 3;
//		if(bDeskStation==4)
//			return 4;
//		if(bDeskStation==5)
//			return 5;
//		break;
//			}	
//	case 4: { 
//		if(bDeskStation==0)	
//			return 5;
//		if(bDeskStation==1)
//			return 0;
//		if(bDeskStation==2)
//			return 1;
//		if(bDeskStation==3)
//			return 2;
//		if(bDeskStation==4)
//			return 3;
//		if(bDeskStation==5)
//			return 4;
//		break;
//			}
//	case 5:
//		{
//		if(bDeskStation==0)	
//			return 4;
//		if(bDeskStation==1)
//			return 5;
//		if(bDeskStation==2)
//			return 0;
//		if(bDeskStation==3)
//			return 1;
//		if(bDeskStation==4)
//			return 2;
//		if(bDeskStation==5)
//			return 3;
//		break;
//		}
//	default:
//		break;
//    }
//	return 0;
}
//換底牌結果
BOOL CClientGameDlg::ChangeBackCardResult(BYTE bDeskStation,BYTE bSourceBackCard,BYTE bResultCard,BOOL bExtVal)
{
	if(!bExtVal)
		return true;
	m_UserCard[bDeskStation][0]=bResultCard;
	/*m_PlayView.m_UserCard[bDeskStation].SetCard(m_UserCard[bDeskStation],NULL,m_iDeskCardCount[bDeskStation]);
	ReplaceCard(m_SysCard,0,m_iSysCardCount,bSourceBackCard,bResultCard);

	m_PlayView.m_SysBackCard.SetCard(m_SysCard,NULL,m_iSysCardCount);*/
	return true;
}
//系統底牌中是否有某張牌
BOOL CClientGameDlg::ReplaceCard(BYTE iTotalCard[],int iSendCardPos,int iEndPos,BYTE bSourceCard,BYTE bResultCard)
{
	//換底牌
	for(int i=iSendCardPos;i<iEndPos;i++)
	{
		if(iTotalCard[i]==bResultCard)
		{
			iTotalCard[i]=bSourceCard;
			return true;
		}
	}
	return false;
}

//代替断线玩家下注
BOOL CClientGameDlg::UserSupersedeNote(BYTE bDeskStation)
{
	KillAllTimer();
	if (GetStationParameter() == GS_PLAY_GAME || GetStationParameter() == GS_SEND_CARD)
	{
		if (bDeskStation==GetMeUserInfo()->bDeskStation)
			return 0L;
		SupersedeUserNote supNote;
		supNote.bDeskStation = bDeskStation;	//代替下注位置
		supNote.iVrebType = 0;					//下注类型
		supNote.iNote = 0;						//下注数(只有下注和加注才设置此值)
		if (GetStationParameter() == GS_PLAY_GAME)
			supNote.iVrebType = TYPE_OPEN;
		SendGameData(&supNote,sizeof(supNote),MDM_GM_GAME_NOTIFY,ASS_SUPERSEDE_VREB_CHECK,0);
	}
	return TRUE;
}

void CClientGameDlg::DelShowThis()
{
	for (int i = 0; i < PLAY_COUNT; i++)
	{
		m_PlayView.m_UserCard[i].SetCardShowNum(0);
	}
}
//为视频模块重载此函数
#ifdef VIDEO
bool CClientGameDlg::GameUserCome(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser)
{
	if (! __super::GameUserCome(bDeskStation, pUserItem, bWatchUser))
	{
		return FALSE;
	}

	if( GetMeUserInfo()->dwUserID == pUserItem->GameUserInfo.dwUserID && bWatchUser )
	{
		m_PlayView.m_bWatch=bWatchUser;
	}
	if( GetMeUserInfo()->dwUserID == pUserItem->GameUserInfo.dwUserID && (!bWatchUser) )
	{    
		CPlayVideo *pPlayVideo=CPlayVideo::CreatePlayVideo();


		if(NULL!=pPlayVideo)
		{ 

			CString NickName=TEXT("");
			int    byteDeskNO=0;
			UserInfoStruct &UInfo=	pUserItem->GameUserInfo;
			NickName+=UInfo.nickName;
			byteDeskNO=UInfo.bDeskNO;
			UINT	uiRoomID = m_pGameInfo->uRoomID;
			UINT	uiBRRoomID =   uiRoomID * 1000 + byteDeskNO; 

			ST_INITVIDEO stInitVideo;
			stInitVideo.iRoomPassType = 0;
			stInitVideo.nRoomID		  = uiBRRoomID;
			stInitVideo.pParentWnd    = &m_PlayView;
			stInitVideo.strRoomPass   = _T("");
			stInitVideo.strUserName	  = NickName;
			stInitVideo.strUserPass   = _T("");
			if( pPlayVideo->Video_Initialize(stInitVideo) )
			{
				//			
				//sprintf(sz,"视频初始化成功!");
				//Writelog(sz,1);
				////连接视频服务器

				pPlayVideo->Connect();

			}
			else
			{
				pPlayVideo->Video_Release();
				/*	sprintf(sz,"视频初始化失败!");
				Writelog(sz,1);*/
				return 0;
			}


		} 
	}
	return TRUE;
}
bool CClientGameDlg::AFCCloseFrame()
{
	///释放视频资源 
	if( NULL != CPlayVideo::GetPlayVideo())
		CPlayVideo::GetPlayVideo()->Video_Release(); 
	return __super::AFCCloseFrame();
}
#endif
//隐藏叫庄按钮
BOOL CClientGameDlg::HideButton()
{
	m_PlayView.m_btCallScore1.ShowWindow(SW_HIDE);
	m_PlayView.m_btCallScorePass.ShowWindow(SW_HIDE);
	return true;
}
//叫分
void CClientGameDlg::ShowCallScoreBt(int CallScore,BOOL bExtVol)
{
	m_PlayView.m_btCallScore1.ShowWindow(SW_SHOW);
	m_PlayView.m_btCallScorePass.ShowWindow(SW_SHOW);
	m_PlayView.m_btCallScorePass.EnableWindow(1);
	m_PlayView.m_btCallScore1.EnableWindow(TRUE);
	return;
}
//叫分
LRESULT	CClientGameDlg::OnCallScore(WPARAM wparam, LPARAM lparam)
{

	KillTimer(ID_CALL_SCORE_TIME);
	HideButton();
	CallScoreStruct score;
	memset(&score,0,sizeof(score));
	score.iValue = (int)wparam;	
	if(m_pGameInfo->bEnableSound)
	{
		if(score.iValue == 0)	//放弃叫庄
		{
			SetPlaySound(SOUND_GIVEUP_NT);
		}
		else
		{
			SetPlaySound(SOUND_CALL_NT);
		}
	}
	score.bDeskStation = GetMeUserInfo()->bDeskStation;			
	score.bCallScoreflag = false;
	SendGameData(&score,sizeof(score),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE,0);

	return 0;
}

void CClientGameDlg::SetRecordView() 
{ 
	m_PlayView.m_btContinue.ShowWindow(SW_HIDE); 
	m_PlayView.m_btLeave.ShowWindow(SW_HIDE); 
	m_PlayView.m_btReset.ShowWindow(SW_HIDE); 
	m_PlayView.m_btOpen.ShowWindow(SW_HIDE);
	m_PlayView.m_btBull.ShowWindow(SW_HIDE);
	m_PlayView.m_btCallScorePass.ShowWindow(SW_HIDE); 
	m_PlayView.m_btCallScore1.ShowWindow(SW_HIDE); 

	m_PlayView.m_btContinue.EnableWindow(FALSE); 
	m_PlayView.m_btLeave.EnableWindow(FALSE); 
	m_PlayView.m_btReset.EnableWindow(FALSE); 
	m_PlayView.m_btOpen.EnableWindow(FALSE);
	m_PlayView.m_btBull.EnableWindow(FALSE);
	m_PlayView.m_btCallScorePass.EnableWindow(FALSE); 
	m_PlayView.m_btCallScore1.EnableWindow(FALSE); 
} 
BYTE CClientGameDlg::GetNetUserPos(BYTE iDesk)
{	
	for(int i = 0 ;i <PLAY_COUNT ;i++)
	{		
		BYTE iStation = (iDesk + 1);

		if(NULL != m_pUserInfo[iStation] &&m_iDeskCardCount[ViewStation(iStation)]>0)
		{
			return iStation;
		}
	}
	return 255;
}



