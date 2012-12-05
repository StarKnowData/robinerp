#include "StdAfx.h"
#include "ServerManage.h"

//游戏扩展配置
BYTE CServerGameDesk:: m_iAllCardCount;
int CServerGameDesk:: m_iSendCardTime;
BYTE CServerGameDesk:: m_iThinkTime;
BYTE CServerGameDesk:: m_iBeginTime;
BYTE CServerGameDesk:: m_iCallScoreTime;
BYTE CServerGameDesk:: m_iXiaZhuTime;
BOOL CServerGameDesk:: m_bTurnRule;		//顺时针还是逆时针
//构造函数
CServerGameDesk::CServerGameDesk(void):CGameDesk(ALL_ARGEE)
{
	m_iLeaveArgee     = 0;								//同意离开
	m_iFirstOutPeople = -1;							//第一个加注者
	m_iOutCardPeople  = -1;
	m_iLastOutPeople  = -1;
	m_iNtPeople       = -1;
	m_iUpGradePeople  = -1;						
	m_iBeenPlayGame   = 0;								//已经玩过的局数
	m_iPrepareNT      = 255;
	m_bSuperSet       = FALSE;
	memset(m_bIsSuper,0,sizeof(m_bIsSuper));
	::memset(m_iCallScore,-1,sizeof(m_iCallScore));		//叫分
	m_bGameStation=GS_WAIT_ARGEE;//GS_WAIT_SETGAME;		//游戏状态
	memset(m_iTotalCard,0,sizeof(m_iTotalCard));
	
	for(int i=0; i<PLAY_COUNT; i++)
		memset(m_bBullCard[i],0,sizeof(m_bBullCard[i]));
	
	memset(m_bAdd,0,sizeof(m_bAdd));
	memset(m_bIsCut,0,sizeof(m_bIsCut));
#ifdef SUPER_VERSION
	for(int i = 0; i < 8; i++)
	{
		m_iSuperCardCount[i] = 0;
		::memset(m_bSuperCardList[i],0,sizeof(m_bSuperCardList[i]));
	}
	m_bSuperStation = -1;
#endif
	m_bControlWin = 255;
	m_bControlLost = 255;
	m_iFirstJiao  = 255;

}
//加载ini配置文件
BOOL CServerGameDesk::LoadIni()
{
	CString s = CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s +SKIN_FOLDER +"_s.ini");
	CString key = TEXT("game");
	m_iAllCardCount = f.GetKeyVal(key,"cardcount",54);

	m_iCardShape &=0x00000000;
	m_iCardShape |= (f.GetKeyVal(key,"Yn",0)&0xFFFFFFFF);//银牛
	m_iCardShape |= ((f.GetKeyVal(key,"Jn",0)<<1)&0xFFFFFFFF);//金牛
	m_iCardShape |= ((f.GetKeyVal(key,"Bomb",0)<<2)&0xFFFFFFFF);//炸弹
	m_iCardShape |= ((f.GetKeyVal(key,"Five",0)<<3)&0xFFFFFFFF);//五小

	m_GameType =  f.GetKeyVal(key,"GameType",0);
	m_iGameNoteSetType = f.GetKeyVal(key,"GameNoteSetType",0);

	m_iGoodCard        =  f.GetKeyVal(key,"iGoodCard",80);
	m_bHaveKing        = f.GetKeyVal(key,"HaveKing",1);//是否有王
	
	m_Logic.SetCardShape(m_iCardShape);

	CString keyName;
	int base = 0;
	for (int i=0; i<MAX_SHAPE_COUNT; i++)
	{
		keyName.Format("CardShape%d",i);
		if (i < 6)
		{
			base = 1;
		}
		else if(i < 10)
		{
			base = i - 5;
		}
		else if (i == 10)
		{
			base = 5;
		}
		else if(i == 11)
		{
			base = 6;
		}
		else if(i == 12)
		{
			base = 7;
		}
		else if(i > 12)
		{
			base = 8;
		}
		m_bCardShapeBase[i] = f.GetKeyVal(key,keyName,base);
	}


	key=TEXT("other");
	m_iSendCardTime = f.GetKeyVal(key,"sendcardtime",120);
	m_iBeginTime = f.GetKeyVal(key,"begintime",30);
	m_iThinkTime = f.GetKeyVal(key,"thinktime",30);
	m_iCallScoreTime = f.GetKeyVal(key,"CallScoretime",15);
	m_iXiaZhuTime = f.GetKeyVal(key,"XiaZhutime",15);
	m_bTurnRule = f.GetKeyVal(key,"TurnRule",0);
	
	
	//	m_iGiveBackTime = f.GetKeyVal(key,"givebacktime",30);
	return true;
}
//加载限注
BOOL CServerGameDesk::LoadExtIni()
{
	CString s = CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s +SKIN_FOLDER +"_s.ini");
	CString key = TEXT("game");
	m_iBaseNote = f.GetKeyVal(key,"basenote",10);
	return TRUE;
}
//根据房间ID加载配置文件
BOOL CServerGameDesk::LoadExtIni(int iRoomID)
{
	TCHAR szKey[20];
	wsprintf(szKey,"%s_%d",SKIN_FOLDER,iRoomID);

	CString s = CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s +SKIN_FOLDER +"_s.ini");
	CString key = szKey;
	//	m_iLimitNote = f.GetKeyVal(key,"limitnote",m_iLimitNote);
	m_iBaseNote = f.GetKeyVal(key,"basenote",m_iBaseNote);
	m_iGameNoteSetType = f.GetKeyVal(key,"GameNoteSetType",m_iGameNoteSetType);
	m_iGoodCard        =  f.GetKeyVal(key,"iGoodCard",m_iGoodCard);
	m_bHaveKing        = f.GetKeyVal(key,"HaveKing",m_bHaveKing);//是否有王
	return TRUE;
}
//析构函数
CServerGameDesk::~CServerGameDesk(void)
{
}

//初始化
bool CServerGameDesk::InitDeskGameStation()
{

	/*if(m_pDataManage->m_InitData.uMaxPeople>50)
	{
		CString sfile;
		sfile.Format("ErrRoom_%d.log",m_pDataManage->m_InitData.uRoomID);
		CFile f;
		f.Open(sfile,CFile::modeCreate|CFile::modeNoInherit|CFile::modeReadWrite);
		sfile.Format("[%s] 房间 %d 人数配置：%d，超过50！",CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"),
			m_pDataManage->m_InitData.uRoomID,m_pDataManage->m_InitData.uMaxPeople);
		f.Write(sfile,sfile.GetLength());
		f.Close();
		typedef struct{int a;}_tag;
		_tag *ta=NULL;
		ta->a=0;
		return false;
	}
	*/
	//加载配置文件
	LoadIni();
	//加载通用限注
	LoadExtIni();

	//重新加载配置文件里面的
	LoadExtIni(m_pDataManage->m_InitData.uRoomID);
	return true;
}
//定时器消息
bool CServerGameDesk::OnTimer(UINT uTimerID)
{
	if(TIME_BEGIN_ANIMAL==uTimerID)
	{
		if (m_bGameStation==GS_SEND_CARD) 
		{	
			KillTimer(TIME_BEGIN_ANIMAL);
			SetTimer(TIME_SEND_CARD,m_iSendCardTime);
		}else
			KillTimer(TIME_BEGIN_ANIMAL);

		return true;
	}
	if (uTimerID==TIME_SEND_CARD)	//发牌定时器
	{
		if (m_bGameStation==GS_SEND_CARD) 
			SendCard();
		else KillTimer(TIME_SEND_CARD);
		return TRUE;
	}
	if(uTimerID==TIME_COLLECT_JETON)
	{
		if (m_bGameStation==GS_PLAY_GAME)
			CollectJeton();
		else KillTimer(TIME_COLLECT_JETON);
		return TRUE;
	}
	if(uTimerID==TIME_SEND_A_CARD)
	{
		if (m_bGameStation==GS_PLAY_GAME)
			SendACard();
		else KillTimer(TIME_SEND_A_CARD);
		return TRUE;
	}
	if (uTimerID==TIME_GAME_FINISH)	//结束定时器
	{
		KillTimer(TIME_GAME_FINISH);
		if (m_bGameStation==GS_PLAY_GAME || m_bGameStation == GS_SEND_CARD) 
			GameFinish(0,GF_NORMAL);
		return TRUE;
	}
	if (uTimerID==TIME_NOTE)
	{
		KillTimer(TIME_NOTE);
		if (m_iGameFlag == GS_NOTE && m_bGameStation == GS_SEND_CARD)
		{
			for (int i=0; i<PLAY_COUNT; i++)
			{
				if (m_pUserInfo[i] != NULL && m_iUserStation[i] == TYPE_PLAY_GAME && i!= m_iUpGradePeople)
				{
					m_iUserStation[i] = TYPE_GIVE_UP;
				}
			}
			if (CountNotePeople() == 1)
			{
				GameFinish(0,GF_SALE);
				return TRUE;
			}
			m_iSendCardPos = 0;
			SetTimer(TIME_SEND_CARD,m_iSendCardTime);
		}
		return TRUE;

	}
	if (uTimerID==TIME_CALL_NT)
	{
		KillTimer(TIME_CALL_NT);
		if (m_iGameFlag == GS_FLAG_CALL_SCORE && m_bGameStation == GS_SEND_CARD)
		{
			UserCallScore(m_bCurrentCallScore, 1);
		}
		return TRUE;
	}
	if (uTimerID==TIME_CUTLINE_AUTO)	//断线自动摆牛
	{
		KillTimer(TIME_CUTLINE_AUTO);

		// 摆牛前断线（如庄家在其他玩家没下注前断线），系统自动帮其摆牛，
		for (BYTE i=0; i<PLAY_COUNT; i++)
		{
			if (NULL!=m_pUserInfo[i] && m_iUserStation[i] != -1 && m_iUserStation[i] != TYPE_OPEN/*&& m_bIsCut[i]*/)
			{
				BYTE bResult[3];
				memset(bResult, 0, sizeof(bResult));
				tagUserProcess Verb;
				Verb.iVrebType = TYPE_OPEN;

				if (m_Logic.GetBull(m_iUserCard[i], 5, bResult))
				{
					::CopyMemory(m_bBullCard[i], bResult, sizeof(bResult));
				}
				else
				{
					memset(m_bBullCard[i], 0, sizeof(m_bBullCard[i]));
					m_bBullCard[i][0] = m_iUserCard[i][0];
					m_bBullCard[i][1] = m_iUserCard[i][1];
					m_bBullCard[i][2] = m_iUserCard[i][2];
				}

				UserActiveResult(i, Verb.iVrebType, 0);
			}
		}

		CheckFinish();
	}
	return __super::OnTimer(uTimerID);
}

//框架消息处理函数
bool CServerGameDesk::HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	switch(pNetHead->bAssistantID)
	{
	case ASS_GM_FORCE_QUIT:		//强行退出//安全退出
		{
			
			UserFourceQuit(bDeskStation);

			char cKey[10];
			CString sPath=CBcfFile::GetAppPath();
			int iResult = 1;
			if (CBcfFile::IsFileExist(sPath + "SpecialRule.bcf"))
			{
				CBcfFile fsr( sPath + "SpecialRule.bcf");
				sprintf(cKey, "%d", NAME_ID);
				iResult = fsr.GetKeyVal (_T("ForceQuitAsAuto"), cKey, 0);
			}

			if (iResult == 0)
			{
				return __super::HandleFrameMessage( bDeskStation,  pNetHead,  pData,  uSize,  uSocketID,  bWatchUser); 
			}
			return true;
		}
	}
	return __super::HandleFrameMessage( bDeskStation,  pNetHead,  pData,  uSize,  uSocketID,  bWatchUser);
}

//游戏数据包处理函数
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	CString aa;
	aa.Format("Test: Server Msg %d", pNetHead->bAssistantID);
	OutputDebugString(aa);

	switch (pNetHead->bAssistantID)
	{
#ifdef SUPER_VERSION
		case 79://超级客户端
			{
				if(bWatchUser)
					return FALSE;
				if(m_bGameStation == GS_PLAY_GAME)
					return true;
				SetCardStruct * pCard = (SetCardStruct*)pData;

				m_bSuperSet = TRUE;
				//默认方式(当前设置玩家)
				m_bSuperStation = bDeskStation ;
				if(pCard->paicount[0] > 0)//仅设置自家
				{
					m_iSuperCardCount[m_bSuperStation] = pCard->paicount[0];
					::CopyMemory(m_bSuperCardList[m_bSuperStation],pCard->pai[0],m_iSuperCardCount[m_bSuperStation]);

				}else//设置多家0位置给默认
				{
					for(int i = 1; i < 8; i ++)
					{
						m_iSuperCardCount[i-1] = pCard->paicount[i];
						::CopyMemory(m_bSuperCardList[i-1],pCard->pai[i],sizeof(BYTE)*m_iSuperCardCount[i-1]);
					}
				}
				return TRUE;
			}
#endif
			//換底牌
		case ASS_GM_SUPERCLIENT:
			{
				if (bWatchUser)
					return FALSE;
				if(uSize!=sizeof(ChangeBackStruct))
					return FALSE;
				ChangeBackStruct * pChangeCard=(ChangeBackStruct *)pData;
				return ChangeBackCard(pChangeCard->bDeskStation,pChangeCard->bSourceCard,pChangeCard->bResultCard);
			}
		case ASS_GM_AGREE_GAME:		//用户同意游戏
			{
				if (bWatchUser)
					return TRUE;
				/*		if ((bDeskStation==0)&&(m_bGameStation==GS_WAIT_SETGAME))	//东家设置
				{
				if (uSize!=sizeof(UserArgeeGame)) return FALSE;
				UserArgeeGame * pGameSet=(UserArgeeGame *)pData;
				if (!UserSetGame(pGameSet)) return FALSE;
				__super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
				return TRUE;
				}
				*/	
				//OutputDebugString("zhtlog:用户同意游戏");
				//其他玩家
				if ((m_bGameStation!=GS_WAIT_ARGEE)&&(m_bGameStation!=GS_WAIT_NEXT)) 
					return TRUE;
					
				if(m_bGameStation!=GS_WAIT_NEXT)
				{
					m_bGameStation=GS_WAIT_ARGEE;
					//GameFinish(0,GF_SALE);
				}
				return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
			}

		case ASS_HAVE_THING:	//有事请求离开
			{
				if(bWatchUser)
					return false;
				HaveThingStruct * pThing=(HaveThingStruct *)pData;
				return UserHaveThing(bDeskStation,pThing->szMessage);
			}
		case ASS_LEFT_RESULT: //同意用户离开
			{
				if(bWatchUser)
					return false;
				LeaveResultStruct * pLeave=(LeaveResultStruct *)pData;
				return ArgeeUserLeft(bDeskStation,pLeave->bArgeeLeave);
			}
		case ASS_STOP_THING:
			{
				if(bWatchUser)
					return false;
				SendGameData((bDeskStation+2)%PLAY_COUNT,MDM_GM_GAME_NOTIFY,ASS_STOP_THING,0);
				return true;
			}
		case ASS_AGREE_STOP:
			{
				if(bWatchUser)
					return false;
				StopResultStruct * pStop=(StopResultStruct *)pData;
				if(pStop->bArgee==1)
				{
					//同意
					StopResultStruct stop;
					stop.bArgee=true;
					SendGameData((bDeskStation+2)%PLAY_COUNT,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);

					MessageStruct Mess;
					memset(&Mess,0,sizeof(Mess));
					lstrcpy(Mess.Message,"敌家经过商量，提前结束了本局！");
					SendGameData((bDeskStation+1)%PLAY_COUNT,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);
					SendGameData((bDeskStation+3)%PLAY_COUNT,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);

					memset(&Mess,0,sizeof(Mess));
					lstrcpy(Mess.Message,"敌家经过商量，提前结束了本局！");
					SendWatchData(m_bMaxPeople,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);
					//结束游戏
					if (m_bGameStation==GS_PLAY_GAME) 
						GameFinish(0,GF_NORMAL);
				}
				else
				{
					StopResultStruct stop;
					stop.bArgee=false;
					SendGameData((bDeskStation+2)%PLAY_COUNT,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);
				}
				return true;
			}

		case ASS_BEGIN_UPGRADE:
			{
				//OutputDebugString("zhtlog:下注11，");
				if(bWatchUser)
					return true;
				if (m_iPerJuTotalNote[bDeskStation]!=0 || m_iUserStation[bDeskStation] == TYPE_GIVE_UP)
				{
					//OutputDebugString("zhtlog:下注22，");
					return true;
				}
				if (m_iUserStation[bDeskStation] == -1)
				{
					//OutputDebugString("zhtlog:下注失败，");
					return true;
				}

				tagUserProcess *pVerb = (tagUserProcess *) pData;
				return UserNoteResult(bDeskStation,pVerb->iVrebType,pVerb->iNote);

				return TRUE;
			}

		case ASS_VREB_CHECK:		//用户处理
			{
				if(bWatchUser)
					return true;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				if (m_iUserStation[bDeskStation] == -1)
				{
					return true;
				}

				tagUserProcess *pVerb = (tagUserProcess *) pData;
				if (pVerb->iVrebType == TYPE_OPEN)
				{
					::CopyMemory(m_bBullCard[bDeskStation],pVerb->bUpCard,sizeof(pVerb->bUpCard));
					for(int i = 0;i < PLAY_COUNT; ++i)
					{
						if(i != bDeskStation)
						{
							SendGameData(i,NULL,0,MDM_GM_GAME_NOTIFY,ASS_TAN_PAI,0);
						}
					}
				}
				//else
				return UserActiveResult(bDeskStation,pVerb->iVrebType,pVerb->iNote);

				if (CheckFinish())
					return true;
				return true;
			}
		case ASS_CALL_SCORE:
			{
				if ((bWatchUser)
					||(uSize!=sizeof(CallScoreStruct))) 
					return true;
				if (m_iUserStation[bDeskStation] == -1)
				{
					return true;
				}
				CallScoreStruct * pCallScore=(CallScoreStruct *)pData;
				UserCallScore(bDeskStation,pCallScore->iValue);
				return true;
			}
		case ASS_REPLACE_CALL_SCORE:
			{
				/*	if (uSize!=sizeof(ReplaceCallScoreStruct)) 
				return FALSE;
				ReplaceCallScoreStruct * pReplace=(ReplaceCallScoreStruct *)pData;
				UserCallScore(pReplace->bDeskStation,pReplace->CallScore);
				return true;*/
			}
		case ASS_SUPERSEDE_VREB_CHECK://代替用户处理
			{
				return true;
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				SupersedeUserNote *pUserNote = (SupersedeUserNote *) pData;
				if (m_bGameStation == GS_PLAY_GAME)
					return UserActiveResult(pUserNote->bDeskStation ,pUserNote->iVrebType,pUserNote->iNote);
				else
					if (m_iGameFlag == GS_FLAG_CALL_SCORE)
						return UserCallScore(pUserNote->bDeskStation,pUserNote->iVrebType);
				return UserNoteResult(pUserNote->bDeskStation ,pUserNote->iVrebType,pUserNote->iNote);
			}

		case ASS_CONTROL_WIN:
			{

				//m_bSuperSet = TRUE;
				ControlWinStruct * pControl = (ControlWinStruct *) pData;

				if (m_bIsSuper[bDeskStation])
				{
					m_bControlWin = pControl->bWinStation;
					m_bControlLost = pControl->bLoseStation;
				}
				
				return TRUE;
			}
	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}

//获取游戏状态信息
bool CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{
	if (!bWatchUser)
		SuperSetCard();
	switch (m_bGameStation)
	{
	case GS_WAIT_SETGAME:		//游戏没有开始状态

	case GS_WAIT_ARGEE:			//等待玩家开始状态
		{
			GameStation_2 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//游戏版本号
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iXiaZhuTime = m_iXiaZhuTime;
			//游戏基础信息设置
			::CopyMemory(GameStation.iLimitNote,&m_iLimitNote,sizeof(m_iLimitNote));
			GameStation.iBaseNote=m_iBaseNote;							//底注
			GameStation.iBeginTime=m_iBeginTime;
			GameStation.iThinkTime=m_iThinkTime;
			GameStation.iAllCardCount=m_iAllCardCount;
			GameStation.iCardShape = m_iCardShape;
			GameStation.bGameType = m_GameType;
			GameStation.iGameNoteSetType = m_iGameNoteSetType;
			GameStation.bIsSuper = m_bIsSuper[bDeskStation];

			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	case GS_SEND_CARD:		//发牌状态
		{
			GameStation_3 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//游戏版本号
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iXiaZhuTime = m_iXiaZhuTime;
			GameStation.iGameFlag = m_iGameFlag;
			//游戏基本内容设置
			GameStation.iBeginTime=m_iBeginTime;								//最高注
			GameStation.iBaseNote=m_iBaseNote;//PLAY_BASE_NOTE;							//底注
			::CopyMemory(GameStation.iLimitNote,&m_iLimitNote,sizeof(m_iLimitNote));
			GameStation.iThinkTime=m_iThinkTime;
			GameStation.iAllCardCount=m_iAllCardCount;
			GameStation.iUpGradePeople=m_iUpGradePeople;		
			GameStation.iBeenPlayGame=m_iBeenPlayGame;	

			GameStation.tag.bCountNotePeople=CountNotePeople();
			GameStation.tag.iOutPeople=m_bCurrentCallScore;					//当前叫分
//			GameStation.tag.iTotalNote=m_iTotalNote;						//当前总注
			GameStation.iCardShape = m_iCardShape;
			GameStation.bGameType = m_GameType;              //游戏种类。0为普通。1为同喜乐
			GameStation.iGameNoteSetType = m_iGameNoteSetType;
			GameStation.bIsSuper = m_bIsSuper[bDeskStation];
			GameStation.bPlayer  = m_iUserStation[bDeskStation]!=-1?TRUE:FALSE;                         //是否玩家
			//用户手中牌
			::CopyMemory(GameStation.iUserCardCount,m_iUserCardCount,sizeof(m_iUserCardCount));
			::CopyMemory(GameStation.iUserCard,m_iUserCard,sizeof(m_iUserCard));
			//系统牌数
			GameStation.iSysCardCount=m_iAllCardCount-m_iSendCardPos;
			::CopyMemory(GameStation.iTotalNote,m_iPerJuTotalNote,sizeof(m_iPerJuTotalNote));
			//发送数据
			int iSendSize=sizeof(GameStation);//-sizeof(GameStation.iUserCard)+sizeof(BYTE)*m_iUserCardCount[bDeskStation];
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,iSendSize);
			return TRUE;
		}
	case GS_PLAY_GAME:	//游戏中状态
		{
			GameStation_4 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//游戏版本号
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iXiaZhuTime = m_iXiaZhuTime;

			::CopyMemory(GameStation.iLimitNote,&m_iLimitNote,sizeof(m_iLimitNote));
			GameStation.iBaseNote=m_iBaseNote;//PLAY_BASE_NOTE;							//底注
			GameStation.iBeginTime=m_iBeginTime;
			GameStation.iThinkTime=m_iThinkTime;
			GameStation.iAllCardCount=m_iAllCardCount;
			GameStation.iUpGradePeople=m_iUpGradePeople;	
			GameStation.iBeenPlayGame=m_iBeenPlayGame;		
			GameStation.iOutCardPeople=m_iOutCardPeople;
			GameStation.iFirstOutPeople=m_iFirstOutPeople;

			GameStation.tag.bCountNotePeople=CountNotePeople();
			GameStation.tag.iOutPeople=m_iOutCardPeople;					//当前押注者
//			GameStation.tag.iTotalNote=m_iTotalNote;						//当前总注
			GameStation.iCardShape = m_iCardShape;
			GameStation.bGameType = m_GameType;              //游戏种类。0为普通。1为同喜乐
			GameStation.iGameNoteSetType = m_iGameNoteSetType;
			GameStation.bSplit=false;
			GameStation.bIsSuper = m_bIsSuper[bDeskStation];
			GameStation.bPlayer  = m_iUserStation[bDeskStation]!=-1?TRUE:FALSE;                         //是否玩家
			memcpy(GameStation.iUserStation, m_iUserStation, sizeof(GameStation.iUserStation));


			if (m_iUserStation[bDeskStation]==TYPE_OPEN)
			{
				GameStation.bSplit=true;
				memcpy(GameStation.bBullCard, m_bBullCard[bDeskStation], sizeof(GameStation.bBullCard));
			}

			//用户手中牌
			::CopyMemory(GameStation.iUserCardCount,m_iUserCardCount,sizeof(m_iUserCardCount));
			::CopyMemory(GameStation.iUserCard,m_iUserCard,sizeof(m_iUserCard));
			//当前各用户下注总数
			::CopyMemory(GameStation.iTotalNote,m_iPerJuTotalNote,sizeof(m_iPerJuTotalNote));
			//发送数据
			int iSendSize=sizeof(GameStation);//-sizeof(GameStation.iUserCardList)+sizeof(BYTE)*iPos;
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,iSendSize);
			return TRUE;
		}
	case GS_WAIT_NEXT:		//等待下一盘游戏开始
		{
			GameStation_5 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//游戏版本号
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();
			GameStation.iBeginTime=m_iBeginTime;
			GameStation.iThinkTime=m_iThinkTime;
			GameStation.iAllCardCount=m_iAllCardCount;
			GameStation.iUpGradePeople=m_iUpGradePeople;		
			GameStation.iBeenPlayGame=m_iBeenPlayGame;		
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iXiaZhuTime = m_iXiaZhuTime;
			GameStation.iCardShape = m_iCardShape;
			GameStation.bGameType = m_GameType;              //游戏种类。0为普通。1为同喜乐
			GameStation.iGameNoteSetType = m_iGameNoteSetType;
			GameStation.bIsSuper = m_bIsSuper[bDeskStation];
			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	}
	return false;
}

//重置游戏状态
bool CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	for(int i=0; i<PLAY_COUNT; i++)
		memset(m_bBullCard[i],0,sizeof(m_bBullCard[i]));
	KillTimer(TIME_SEND_CARD);
	//	KillTimer(TIME_WAIT_NT);
	KillTimer(TIME_GAME_FINISH);
	KillTimer(TIME_BEGIN_ANIMAL);
	KillTimer(TIME_SEND_A_CARD);
	KillTimer(TIME_COLLECT_JETON);
	KillTimer(TIME_CUTLINE_AUTO);

	if ((bLastStation==GFF_FORCE_FINISH)||(bLastStation==GF_SALE))
	{
		m_iBeenPlayGame=0;
		m_iNtPeople=-1;	

	}
	m_bControlWin = 255;
	m_bControlLost = 255;
	//	m_iUpGradePeople=-1;
	m_iLeaveArgee=0;
	m_iFirstOutPeople=-1;
	m_iOutCardPeople=-1;
	m_iLastOutPeople=-1;
	m_iSendCardPos=0;
	//m_iUpGradePeople=-1;
	m_iPrepareNT = 255;
	m_bSuperSet       = FALSE;
	::memset(m_iCallScore,-1,sizeof(m_iCallScore));		//叫分
	//m_Logic.SetNTHuaKind(UG_ERROR_HUA);
	//memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));
	memset(m_iUserCardCount, 0, sizeof(m_iUserCardCount));
	memset(m_bAdd, 0, sizeof(m_bAdd));
	memset(m_bIsCut, 0, sizeof(m_bIsCut));
#ifdef SUPER_VERSION
	for(int i = 0; i < 8; i++)
	{
		m_iSuperCardCount[i] = 0;
		::memset(m_bSuperCardList[i],0,sizeof(m_bSuperCardList[i]));
	}
	m_bSuperStation = -1;
#endif
	return TRUE;
}

//游戏开始
bool CServerGameDesk::GameBegin(BYTE bBeginFlag)
{
	if (__super::GameBegin(bBeginFlag)==false) 
	{
		GameFinish(0,GF_SALE);
		return false;
	}
	//设置状态
	//	m_bQueryQuit=false;							//有玩家请求离开
	m_iSendCardPos=0;							//发牌位置
	m_iBeenPlayGame++;							//已经玩的局数
//	m_iTotalNote = 0;	
	//桌面总注数
	//	m_iCurPlayStatus = -1;
	m_iGameStation = -1;
	m_iIngPlayNote = -1;
	m_iLastShuttle = -1;
	m_bGameStation = GS_SEND_CARD;				//游戏状态
	::memset(m_iUserCardCount,0,sizeof(m_iUserCardCount));		//用户手中牌数
	for (int i = 0; i < m_bMaxPeople; i++) 
	{
		m_iUserStation[i] = -1;
		m_iPerJuTotalNote[i] = 0;
		if (m_pUserInfo[i])
		{
			m_iUserStation[i] = TYPE_PLAY_GAME;
		}
//		m_iInsuranceNote[i] = 0;
	}
	//分发扑克
	m_Logic.RandCard(m_iTotalCard,m_iAllCardCount,m_bHaveKing);
	int temp = rand()%100;
	CString str;
	str.Format("zhtlog: temp=%d m_iGoodCard=%d",temp,m_iGoodCard);
	OutputDebugString(str);
	//洗到好牌
	if (temp < m_iGoodCard)
	{
		for (int i=0; i<20; i++)
		{

			if (GetMaxCardShape(m_iTotalCard,m_iAllCardCount) > UG_BULL_SEVEN)
			{
				OutputDebugString("zhtlog:洗到好牌");
				break;
			}
			else
			{
				OutputDebugString("zhtlog:没洗到好牌");
			}
			m_Logic.RandCard(m_iTotalCard,m_iAllCardCount,m_bHaveKing);
		}
	}
	//服务端发牌测试
	//	SuperSetCard(m_iTotalCard,ALL_CARD_COUNT);
	//发送开始消息
	//if (!FindNt())
	//{
	//	GameFinish(0,GF_SALE);
	//	for (int i=0;i<m_bMaxPeople;i++) 
	//	{
	//		
	//		if(m_pUserInfo[i])
	//			SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_NOMONEY,0);
	//		else
	//			continue;
	//	}
	//	SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_NOMONEY,0);
	//	return TRUE;
	//}
	srand(GetTickCount());
	//m_iFirstJiao= rand()%PLAY_COUNT;
#ifdef SUPER_VERSION
	for(int j = 0; j < PLAY_COUNT; j++)
	{
		for(int i = 0; i < m_iSuperCardCount[j]; i ++)
		{
			//仅适应一副牌
			int temp = m_Logic.GetSerialBySpecifyCard(m_iTotalCard,0,m_iAllCardCount,m_bSuperCardList[j][i]);
			if(temp != -1)
			{	
				BYTE t = m_iTotalCard[i + j * 5];
				m_iTotalCard[i + j * 5] = m_iTotalCard[temp];
				m_iTotalCard[temp] = t;

			}
		}
	}
#endif
	m_bGameStation = GS_SEND_CARD;

	if (m_iFirstJiao != 255)
	{
		m_iFirstJiao = GetNextDeskStation(m_iFirstJiao);
		//OutputDebugString("zhtlog:");
	}
	else
	{
		m_iFirstJiao = GetNextDeskStation(rand()%PLAY_COUNT);
		//OutputDebugString("zhtlogelse:");
	}
	

	/*CString str;
	str.Format("zhtlog:m_iFirstJiao=%d",m_iFirstJiao);
	OutputDebugString(str);*/
	SendCallScore(m_iFirstJiao);
	//随机第一个叫庄的人
	/*for (int i = 0; i<PLAY_COUNT; i++)
	{
		m_iFirstJiao = m_iFirstJiao%PLAY_COUNT;
		if(!m_pUserInfo[m_iFirstJiao])
		{
			m_iFirstJiao++;
		}
		else
		{
			SendCallScore(m_iFirstJiao);

			return true;
		}
	}*/

	return true;
}
//用户下注
BOOL CServerGameDesk::UserNote()
{
	m_iGameFlag = GS_NOTE;
	m_iUpGradePeople = m_iPrepareNT;
	for (int i=0; i<PLAY_COUNT; i++)
	{
		if (i==m_iUpGradePeople || !m_pUserInfo[i])
			continue;
		m_iLimitNote[i] = GetLimit(i);
	}

	BeginUpgradeStruct BeginMessage;
	memset(&BeginMessage,0,sizeof(BeginMessage));
	BeginMessage.AllCardCount=m_iAllCardCount;
	::CopyMemory(BeginMessage.iLimitNote,m_iLimitNote,sizeof(m_iLimitNote));
	BeginMessage.iBaseNote=m_iBaseNote;//PLAY_BASE_NOTE;			//底注最大注的百分之一
	::CopyMemory (BeginMessage.SysCard,m_iTotalCard,sizeof(BYTE)*m_iAllCardCount);
	m_MaxPlayer = CountNotePeople() - 1;//闲家的数量为所有未放弃玩家的数量减去一个庄家
	BeginMessage.iNt = m_iUpGradePeople;	 

	for (int i=0;i<m_bMaxPeople;i++) 
	{
		if(m_pUserInfo[i]&&m_iUserStation[i]!=TYPE_GIVE_UP)
			SendGameData(i,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_BEGIN_UPGRADE,0);
		else
			continue;
	}
	SendWatchData(m_bMaxPeople,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_BEGIN_UPGRADE,0);

	SetTimer(TIME_NOTE,(m_iXiaZhuTime+2)*1000);
	m_iSendPos=0;
	return TRUE;
}

BOOL CServerGameDesk::SuperSetCard()
{
	CString s = CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s +SKIN_FOLDER +"_s.ini");
	CString key = TEXT("Super");
	int count = f.GetKeyVal(key,"count",0);
	if(count <= 0 )					//无胜者
		return FALSE;
	TCHAR szName[21];
	BYTE  bFind = 255;				//胜者座号
	int probability = 0;
	CString szNickName;
	memset(m_bIsSuper,0,sizeof(m_bIsSuper));
	for (int j = 0; j < PLAY_COUNT; j++)
	{
		if(m_pUserInfo[j] == NULL)
			continue;

		for(int i = 0; i < count; i ++)
		{
			wsprintf(szName,"nickname%d",i);
			szNickName = f.GetKeyVal(key,szName,"wing");

			if(strcmp(m_pUserInfo[j]->m_UserData.nickName,szNickName) != 0)
				continue;
		
			m_bIsSuper[j] = TRUE;
			break;
		}

	}
	return true;
}

//计算得分
int	CServerGameDesk::GetUpGrade(int iGamePoint, int iPlayCardCount)
{
	/**********************************************
	赢家的局最大分，放弃者输掉所下的总注，其他人输掉
	局最大分
	**********************************************/

	/*	int fen[4] = {0,0,0,0},total = 0;

	int iWiner = GetCardGreater();
	if (iWiner >= 0) 
	fen[iWiner] = PLAY_MAX_NOTE;

	for (int i = 0;i < 4;i++)
	{
	total += m_iPerJuTotalNote[i];
	if (i == iWiner) continue;
	if (m_iUserStation[i] == BUTTON_TYPE_GIVEUP)
	{
	if (m_iPerJuTotalNote[i] > PLAY_MAX_NOTE) fen[i] = -(PLAY_MAX_NOTE);
	else fen[i] = -(m_iPerJuTotalNote[i]);
	continue;
	}
	fen[i] = -m_iPerJuTotalNote[i];//-(PLAY_MAX_NOTE);
	}
	fen[iWiner] = total;

	for (int i = 0;i < 4;i++)
	{
	int flag = 1;
	long ul = fen[i];
	if (ul < 0)
	{
	ul = -ul;
	flag = -1;
	}
	ul = ul / 100;
	m_iTurePoint[i] = flag * ul;
	}*/
	return 0;
}

//用户设置游戏
BOOL CServerGameDesk::UserSetGame(UserArgeeGame * pGameSet)
{
	/*	//效验数据
	if (m_bGameStation!=GS_WAIT_SETGAME) return FALSE;

	//效验数据
	if (((pGameSet->iPlayCount<=0)||(pGameSet->iPlayCount>99))||
	(pGameSet->iBeginStation<2)||(pGameSet->iEndStation>14)||
	(pGameSet->iBeginStation>pGameSet->iEndStation)) 
	return FALSE;
	if ((m_CardCount & pGameSet->iCardCount)==0) return FALSE;

	//设置数据
	m_iThinkTime=pGameSet->iPlayCount;
	m_iPlayCardCount=(pGameSet->iCardCount&1)?2:3;
	m_iBeginStation=pGameSet->iBeginStation;
	m_iEndStation=pGameSet->iEndStation;
	m_iBeenPlayGame=0;


	m_bGameStation=GS_WAIT_ARGEE;

	//发送消息
	UserArgeeGame Agree;
	Agree.iBeginStation=m_iBeginStation;
	Agree.iEndStation=m_iEndStation;
	Agree.iPlayCount=m_iThinkTime;
	Agree.iCardCount=m_iPlayCardCount;
	for (int i=0;i<4;i++) SendGameData(i,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);
	SendWatchData(m_bMaxPeople,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);
	*/
	return TRUE;
}

//发送扑克给用户
BOOL CServerGameDesk::SendCard()
{
	KillTimer(TIME_SEND_CARD);

	int QuitCardCount = 0;
	for (int i=0; i < PLAY_COUNT; i++)
	{
		if(!m_pUserInfo[i] && m_iUserCardCount[i] > 0)
			QuitCardCount += m_iUserCardCount[i];
	}
	if (/*m_iSendCardPos == CountNotePeople()*5 + QuitCardCount*/m_iSendCardPos>0)//发牌位置到了最后一个玩家发完2张时结束发牌
	{
		KillTimer(TIME_SEND_CARD);

		SendCardFinish();
		return TRUE;
	}
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if( m_iUserStation[i] == TYPE_GIVE_UP)
			continue;
		if(m_pUserInfo[i] && CanSendCard(i) )//如果用户非空,且手中牌数最少
		{
			m_iSendPos = i;
			break;
		}
	}
	//
	SendAllCardStruct  pAllCard;
	pAllCard.iStartPos = m_iUpGradePeople;

	for(int j = 0 ; j<5 ;j++)
	{
		for(int i = 0 ;i<PLAY_COUNT;i++)
		{
			if( NULL == m_pUserInfo[i] || m_iUserStation[i] == -1)
			{
				m_iUserCardCount[i] = 0;
				continue;
			}
			else
			{
				m_iUserCard[i][j] =  m_iTotalCard[i*5+j];	
				
			}			
		}
	}
	for(int i = 0 ;i<PLAY_COUNT;i++)
	{
		if(NULL == m_pUserInfo[i]|| m_iUserStation[i] == -1)
		{
			m_iUserCardCount[i] = 0;
			pAllCard.iUserCardCount[i] = 0;
			continue;
		}
		else
		{
			m_iUserCardCount[i] = 5;
			memcpy(&pAllCard.iUserCard[i],&m_iUserCard[i],sizeof(BYTE)*m_iUserCardCount[i]);			
			pAllCard.iUserCardCount[i] = m_iUserCardCount[i] ;
		}
	}	
	for(int j=0;j<m_bMaxPeople;j++)
	{
		if(m_pUserInfo[j])
			SendGameData(j,&pAllCard,sizeof(pAllCard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD,0);
		
	}	
	SendWatchData(m_bMaxPeople,&pAllCard,sizeof(pAllCard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD,0);

	///发牌时间写死，与客户端一致150*5
	SetTimer(TIME_SEND_CARD,/*6*m_iSendCardTime*/CountNotePeople()*750+500);

	m_iSendCardPos++;



	for(int i = 0 ; i<PLAY_COUNT;i++)
	{
		for(int j = 0 ;j<5 ;j++)
		{
			CString str;
			str.Format("wys423sever::m_iUserCard[%d][%d]=%d",i,j,m_iUserCard[i][j]);
			OutputDebugString(str);

		}
	}

	return TRUE;

 //   SendCardStruct SendCard;
	//SendCard.bDeskStatin=m_iSendPos;//m_iSendCardPos%m_bMaxPeople; 
	////改成所有牌都设置好的
	//BYTE bCard = m_iTotalCard[m_iSendPos * 5 + m_iUserCardCount[ m_iSendPos ]];
	//m_iUserCard[m_iSendPos][m_iUserCardCount[m_iSendPos]++] = bCard;
	//SendCard.iCard = bCard;//m_iUserCard[m_iSendCardPos%4][m_iSendCardPos/m_bMaxPeople];

	//for(int j=0;j<m_bMaxPeople;j++)
	//{
	//	if(m_pUserInfo[j])
	//		SendGameData(j,&SendCard,sizeof(SendCard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD,0);
	//}
	//SendWatchData(m_bMaxPeople,&SendCard,sizeof(SendCard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD,0);
	//m_iSendCardPos++;
	//return TRUE;
}

//发牌结束
BOOL CServerGameDesk::SendCardFinish()
{
	for (int i=0;i<m_bMaxPeople;i++) 
	{
		if(m_pUserInfo[i])
			SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_SEND_FINISH,0);
	}
	SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_SEND_FINISH,0);

	//	SetTimer(TIME_GAME_FINISH,2000);

	BeginPlayUpGrade();
	return true;
}

//是否增加发牌
BOOL CServerGameDesk::CanSendCard(BYTE bDeskStation)
{
	int min=99;
	for(int i=0;i<m_bMaxPeople;i++)
	{
		if(m_iUserCardCount[i]<min&&m_pUserInfo[i]&&m_iUserStation[i] != TYPE_GIVE_UP&&m_iUserStation[i] != -1)
			min=m_iUserCardCount[i];
	}
	if(m_iUserCardCount[bDeskStation]==min)
		return true;
	return false;
}

//统计玩游戏玩家
BYTE CServerGameDesk::CountPlayer()
{
	BYTE count=0;
	for(int i=0;i<m_bMaxPeople;i++)
	{
		if(m_pUserInfo[i] && m_iUserStation[i] != -1)
			count++;
	}
	return count;
}

//游戏开始
BOOL CServerGameDesk::BeginPlayUpGrade()
{
	//设置数据
	m_bGameStation=GS_PLAY_GAME;

	//	m_iOutCardPeople=(m_iUpGradePeople + 1)%PLAY_COUNT;
	for (int i = m_iOutCardPeople;;i=(i+1) % PLAY_COUNT)
	{
		if(!m_pUserInfo[i] || m_iUserStation[i] == TYPE_GIVE_UP || i == m_iUpGradePeople)
			continue;
		else
		{
			m_iOutCardPeople = i;
			break;
		}
	}
	//发送游戏开始消息
	BeginPlayStruct Begin;
	Begin.iOutDeskStation=m_iOutCardPeople;
	for (int i=0;i<m_bMaxPeople;i++)
		SendGameData(i,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);
	SendWatchData(m_bMaxPeople,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);

	// 倒计时摆牛
	SetTimer(TIME_CUTLINE_AUTO, (m_iThinkTime+2)*1000);
	return TRUE;
}
//用户下注
BOOL CServerGameDesk::UserNoteResult(BYTE bDeskStation, BYTE iVerbType,__int64 iNoteVal)
{
	if (m_iPerJuTotalNote[bDeskStation]!=0 || m_iUserStation[bDeskStation] == TYPE_GIVE_UP)
		return true;
	if (m_iLimitNote[bDeskStation] < iNoteVal || 0 > iNoteVal)//2011-03-03 添加iNoteVal < 0判断，防止玩家修改数据包下负数
	{
		return true;
	}
	m_iPerJuTotalNote[bDeskStation] = iNoteVal;
	m_iUserStation[bDeskStation] = iVerbType;
	//m_iGameStation = iVerbType;

	CString aa;
	aa.Format("Test: Server 用户状态 %d-》%d", bDeskStation, m_iUserStation[bDeskStation]);
	OutputDebugString(aa);

	m_MaxPlayer--;
	if (CountNotePeople() == 1)
	{
		GameFinish(0,GF_SALE);
		return TRUE;
	}
	NoteResult noteresult;					
	noteresult.bAddStyle=iVerbType;										//下注类型
	noteresult.iOutPeople = bDeskStation;								//本次下注者
	noteresult.iCurNote =  iNoteVal;
	for (int i = 0; i < m_bMaxPeople; i++)
	{
		if(m_pUserInfo[i])
		{
			SendGameData(i,&noteresult,sizeof(noteresult),MDM_GM_GAME_NOTIFY,ASS_NOTE_RESULT,0);
		}		
	}
	SendWatchData(m_bMaxPeople,&noteresult,sizeof(noteresult),MDM_GM_GAME_NOTIFY,ASS_NOTE_RESULT,0);

	if (m_MaxPlayer <= 0)
		//发牌消息
	{
		m_iGameFlag = GS_SEND_CARD;
		KillTimer(TIME_NOTE);
		if (!m_bSuperSet)//没有超端配置的情况下才处理控制输赢
		{
			JudgeLoser();
			JudgeWiner();
		}
		

		if (m_bControlWin != 255)
		{
			BYTE bDest = GetIndex(1);
			
			if (bDest != m_bControlWin)
				ChangeCard(m_bControlWin,bDest);

		}
		if (m_bControlLost != 255)
		{

			BYTE bDest = GetIndex(0);
			if (bDest != m_bControlLost)
				ChangeCard(m_bControlLost,bDest);
		}
		m_iSendCardPos = 0;
		SetTimer(TIME_SEND_CARD,m_iSendCardTime);
		return TRUE;

	}
	if (CheckFinish())
	{
		return TRUE;
	}
	return TRUE;

}

//处理用户结果
BOOL CServerGameDesk::UserActiveResult(BYTE bDeskStation, BYTE iVerbType,int iNoteVal)
{
	CString aa;
	aa.Format("Test: Server UserActiveResult %d %d %d", bDeskStation, iVerbType, iNoteVal);
	OutputDebugString(aa);

	//if (bDeskStation != m_iOutCardPeople)
	//	return true;
	//BYTE TempStation;//停牌的临时位置
	switch (iVerbType)
	{
		//放弃
	case TYPE_GIVE_UP:
		{
			break;
		}
		//加倍
	case TYPE_BULL:
		{

			break;
		}
		//开牌
	case TYPE_OPEN:
		{
			m_iGameStation = TYPE_OPEN;
			m_iUserStation[bDeskStation] = TYPE_OPEN;
			if (CheckFinish())
			{
				return TRUE;
			}

		}
	}
	NoteResult noteresult;					
	noteresult.bAddStyle=iVerbType;										//下注类型
	noteresult.iOutPeople = bDeskStation;								//本次下注者
	//	noteresult.NoHitStation = TempStation;
	noteresult.iCurNote = m_iPerJuTotalNote[bDeskStation] / 2;
	for (int i = 0; i < m_bMaxPeople; i++)
	{
		if(m_pUserInfo[i])
			SendGameData(i,&noteresult,sizeof(noteresult),MDM_GM_GAME_NOTIFY,ASS_NOTE_RESULT,0);
	}
	SendWatchData(m_bMaxPeople,&noteresult,sizeof(noteresult),MDM_GM_GAME_NOTIFY,ASS_NOTE_RESULT,0);
	if (CheckFinish())															//是否结束
		return TRUE;
	////下一位要牌者//当前玩家不要牌的情况下才计算下一要牌者
	//if ((!m_bIsHit[m_iOutCardPeople][0] && !m_bIsHit[m_iOutCardPeople][1]) || (!m_bIsHit[m_iOutCardPeople][0] && !m_bSplit[bDeskStation]))
	//{
	//	m_iOutCardPeople=(m_iOutCardPeople + 1)%PLAY_COUNT;
	//	for (int i = m_iOutCardPeople;;i=(i+1) % PLAY_COUNT)
	//	{
	//		if(!m_pUserInfo[i] || m_iUserStation[i] == TYPE_GIVE_UP /*|| i == m_iUpGradePeople*/)
	//			continue;
	//		else
	//		{
	//			m_iOutCardPeople = i;
	//			break;
	//		}
	//	}
	//}
	//tagUserResult result;
	//result.iOutPeople = m_iOutCardPeople;
	//result.bCountNotePeople = CountNotePeople();
	//result.bSplit = m_bSplit[m_iOutCardPeople];
	//result.iSplitStation = (m_bIsHit[m_iOutCardPeople][0]?0:1);

	//for (int i = 0;i < PLAY_COUNT;i++)
	//{
	//	if(m_pUserInfo[i])
	//	{
	//		SendGameData(i,&result,sizeof(result),MDM_GM_GAME_NOTIFY,ASS_NOTE,0);
	//	}
	//}
	//SendWatchData(m_bMaxPeople,&result,sizeof(result),MDM_GM_GAME_NOTIFY,ASS_NOTE,0);

	return TRUE;
}


BYTE CServerGameDesk::CountNotePeople()
{
	int iCount=0;
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(!m_pUserInfo[i])		
			continue;
		if(m_iUserStation[i]!=TYPE_GIVE_UP && m_iUserStation[i]!=-1)
			iCount++;
	}
	return iCount;
}
//检测是否结束
BOOL CServerGameDesk::CheckFinish()
{
	//检查是否结束
	/*******************
	结束条件：
	*******************/
	//	bool bFinish = false;

	int iShuttle = 0,iGiveUp = 0;
	for (int i = 0;i < PLAY_COUNT;i++)
	{
		if(!m_pUserInfo[i])
			continue;

		if (m_iUserStation[i] == TYPE_GIVE_UP)
		{
			iGiveUp++;
			continue;
		}
		if (m_iUserStation[i] == TYPE_OPEN)
		{
			iShuttle++;
			continue;
		}
	}
	//	//	if (((iShuttle + iGiveUp) == CountPlayer())&&!bFinish || (iGiveUp ==  CountPlayer()-1))			//有三家放弃,或者牌已经发完且放弃的和扎金花的玩家为游戏人数
	if((iGiveUp  ==  CountPlayer()-1)||(iShuttle + iGiveUp) == CountPlayer())			//有三家放弃,或者牌已经发完且放弃的和扎金花的玩家为游戏人数
	{
		//结束
		SetTimer(TIME_GAME_FINISH,2000);
		return true;
	}
	if (iShuttle == CountNotePeople())
	{
		//结束
		SetTimer(TIME_GAME_FINISH,2000);
		return true;
	}

	return FALSE;
}
BOOL CServerGameDesk::CollectJeton(BOOL bOnly)
{
	KillTimer(TIME_COLLECT_JETON);
	CollectJetonStruct jeton;
	for (int i = 0;i < PLAY_COUNT;i++) 
		SendGameData(i,&jeton,sizeof(jeton),MDM_GM_GAME_NOTIFY,ASS_COLLECT_JETON,0);
	SendWatchData(m_bMaxPeople,&jeton,sizeof(jeton),MDM_GM_GAME_NOTIFY,ASS_COLLECT_JETON,0);
	if(!bOnly)
		NewPlayTurn(m_iOutCardPeople);
	return TRUE;
}

//新一轮开始
BOOL CServerGameDesk::NewPlayTurn(BYTE bDeskStation)
{/*
 //	if (m_iNowBigPeople < 0)//new turn
 //	{
 m_bAddNoteTime++;
 m_iNowBigPeople=-1;

 //每人发一张牌
 bool bIs5Card = false;
 for (int i = 0;i < PLAY_COUNT;i++)
 {
 if(!m_pUserInfo[i])
 continue;
 if (m_iUserCardCount[i] != 5)
 continue;
 bIs5Card = true;
 }
 if (bIs5Card) 
 {
 SetTimer(TIME_GAME_FINISH,2000);
 return TRUE;
 }
 m_iOutCardPeople = GetCardGreater(false);//iGreater;
 //开始发牌位置
 m_iSendPos=0;
 SetTimer(TIME_SEND_A_CARD,SEND_CARD_TIME);

 //		SendACard(m_iOutCardPeople);	
 //第三轮就全部梭哈,发最后一张牌就比较大小
 //	}*/
	//if(m_Ming[m_iNowBigPeople])
	//	m_iMaxNote+=m_iUserNote[m_iNowBigPeople];
	//else
	//	m_iMaxNote+=m_iUserNote[m_iNowBigPeople]*2;
	//m_iNowBigPeople=-1;
	//m_iOutCardPeople=-1;
	//for(int i=0;i<PLAY_COUNT;i++)
	//	m_iUserNote[i]=0;
	SendUserNote();
	return TRUE;
}

BOOL CServerGameDesk::SendACard()
{
	if(m_iSendPos>=PLAY_COUNT)//未放弃者每人发了一张牌
	{
		KillTimer(TIME_SEND_A_CARD);
		SendUserNote();
		return true;
	}
	//发一张牌
	SendCardStruct SendCard;
	int pos=m_iOutCardPeople;		//开始发牌位置

	m_iUserCard[pos][m_iUserCardCount[pos]] = m_iTotalCard[m_iSendCardPos];
	SendCard.iCard = m_iUserCard[pos][m_iUserCardCount[pos]];
	m_iUserCardCount[pos]++;
	SendCard.bIsSplit = false;

	SendCard.bDeskStatin=pos;												//发送牌位置
	for (int i = 0;i < PLAY_COUNT;i++) 
		SendGameData(i,&SendCard,sizeof(SendCard),MDM_GM_GAME_NOTIFY,ASS_SEND_A_CARD,0);
	SendWatchData(m_bMaxPeople,&SendCard,sizeof(SendCard),MDM_GM_GAME_NOTIFY,ASS_SEND_A_CARD,0);

	m_iSendCardPos++;
	KillTimer(TIME_SEND_A_CARD);
	//SendUserNote();

	return TRUE;
}

BOOL CServerGameDesk::SendUserNote()
{
	//检查是否可以结束(在任一轮都可以梭的情况下进行分析)本游戏规则可以省
	//		if(CheckFinish())
	//		{
	//			return true;
	//		}
	//下注者
	tagUserResult result;
	result.iOutPeople = m_iOutCardPeople;
	result.bCountNotePeople=CountNotePeople();
	::CopyMemory(result.iUserStation,&m_iUserStation,sizeof(m_iUserStation));
	for (int i = 0;i < PLAY_COUNT;i++)
	{
		if(m_pUserInfo[i])
			SendGameData(i,&result,sizeof(result),MDM_GM_GAME_NOTIFY,ASS_NOTE,0);
	}
	SendWatchData(m_bMaxPeople,&result,sizeof(result),MDM_GM_GAME_NOTIFY,ASS_NOTE,0);

	return TRUE;
}

//更新用户所下注
void CServerGameDesk::ModifyPlayNote(BYTE bDeskStation)
{
	/*	m_iIngPlayNote = bDeskStation;

	tagUserResult result;
	result.iOutPeople = bDeskStation;
	result.iTotalNote = m_iTotalNote;
	CopyMemory(result.iCurNote,m_iUserNote,sizeof(m_iUserNote));

	for (int i = 0;i < 4;i++)
	SendGameData(i,&result,sizeof(result),MDM_GM_GAME_NOTIFY,ASS_MODIFY_PLAY_NOTE,0);
	SendWatchData(m_bMaxPeople,&result,sizeof(result),MDM_GM_GAME_NOTIFY,ASS_MODIFY_PLAY_NOTE,0);
	*/	return;
}

//获取牌最大者
int CServerGameDesk::GetCardGreater(BOOL bExtVal)
{
	int iGreater =m_iOutCardPeople;// -1;
	//    if(m_iUserStation[iGreater]==TYPE_GIVE_UP)
	//         iGreater=-1;
	//for (int i = 0;i < m_bMaxPeople;i++)
	//{	
	//	if (m_iUserStation[i] == TYPE_GIVE_UP||!m_pUserInfo[i]) 
	//		continue;
	//	if (iGreater < 0)
	//	{
	//		iGreater = i; //i;
	//		continue;
	//	}
	//	if(i == m_iOutCardPeople)
	//		continue;
	//	int ret; 		
	//	if(!bExtVal)		//比较明牌
	//		ret = m_Logic.CompareCard(m_iUserCard[iGreater]+1,m_iUserCardCount[iGreater]-1,m_iUserCard[i]+1,m_iUserCardCount[i]-1);
	//	else				//比较所有牌
	//		ret= m_Logic.CompareCard(m_iUserCard[iGreater],m_iUserCardCount[iGreater],m_iUserCard[i],m_iUserCardCount[i]);
	//	if (ret > 0)
	//		continue;
	//	else iGreater = i;
	//}
	return iGreater;
}

//游戏结束
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	//得到最小数的金币
	long m_dwMaxPoint=0;
	bool bSetMaxMoney=false;
	KillTimer(TIME_CUTLINE_AUTO);
	KillAllTimer();


	//玩家人数异常，直接算安全结束
	if (CountPlayer() <= 1)
	{
		bCloseFlag = GF_SALE;
	}
	switch (bCloseFlag)
	{
	case GF_NORMAL:		//游戏正常结束
		{
			//设置数据 
			m_bGameStation=GS_WAIT_NEXT;

			for (int i=0;i<PLAY_COUNT;i++)
			{
				if (m_pUserInfo[i]!=NULL) 
					m_pUserInfo[i]->m_UserData.bUserState=USER_SITTING;
			}	

			//游戏结束
			GameEndStruct GameEnd;
			::memset(&GameEnd,0,sizeof(GameEnd));
			GameEnd.iUpGradeStation=m_iUpGradePeople;
			::CopyMemory(GameEnd.iUpBullCard,&m_bBullCard,sizeof(m_bBullCard));
			::CopyMemory(GameEnd.iCardList,&m_iUserCard,sizeof(m_iUserCard));
			//传给客户端当前牌型
			for (int i = 0;i < PLAY_COUNT;i++)
			{
				if (m_pUserInfo[i]==NULL) 
					continue;
				//牌型处理
				if(m_iUserStation[i]!=TYPE_GIVE_UP)
				{
					GameEnd.iUserState[i] = m_iUserStation[i];
					GameEnd.iCardShape[i] = m_Logic.GetShape(m_iUserCard[i],m_iUserCardCount[i],m_bBullCard[i]);
				}
			}
			__int64 iNtPoint = 0; //庄家输的钱（算上赢部分闲家）
			double  iNtLoseMoney = 0;//庄家输的钱。（不算赢部分闲家的）
			for (int i = 0;i < PLAY_COUNT;i++)
			{
				if (m_pUserInfo[i]==NULL) 
					continue;
				if(i != m_iUpGradePeople)//得到各闲家的得分点
				{
					
					GameEnd.iTurePoint[i] = ComputePoint(i)*m_iPerJuTotalNote[i];
					
					//20100802 zht 同喜乐客户修改了输赢结算闲家不够钱
					if (GameEnd.iTurePoint[i] + m_pUserInfo[i]->m_UserData.i64Money < 0)
					{
                         GameEnd.iTurePoint[i] = -m_pUserInfo[i]->m_UserData.i64Money;    
					}
					if (GameEnd.iTurePoint[i] > 0)
					{
						iNtLoseMoney+=GameEnd.iTurePoint[i];
					}
					iNtPoint += GameEnd.iTurePoint[i];
					//CString str;
					//str.Format("zhtout:iNtPoint=%d iNtLoseMoney=%lf GameEnd.iTurePoint[%d]=%d",iNtPoint,iNtLoseMoney,i,GameEnd.iTurePoint[i]);
					//OutputDebugString(str);
					//GameEnd.iTurePoint[m_iUpGradePeople] -= 
				}
			}
			//20100802 zht 同喜乐客户修改了输赢结算
			if (m_pUserInfo[m_iUpGradePeople] != NULL)
			{

				__int64 dwNtMoney = m_pUserInfo[m_iUpGradePeople]->m_UserData.i64Money;
				if (iNtPoint > dwNtMoney)//不够钱赔
				{

					for (int i = 0;i < PLAY_COUNT;i++)
					{
						if (m_pUserInfo[i]==NULL) 
							continue;
						if(i != m_iUpGradePeople && GameEnd.iTurePoint[i] > 0)//得到各闲家的得分点
						{
							GameEnd.iTurePoint[i] = (dwNtMoney+(iNtLoseMoney-iNtPoint)) *(GameEnd.iTurePoint[i]/iNtLoseMoney);
						}
					}
					GameEnd.iTurePoint[m_iUpGradePeople] = -m_pUserInfo[m_iUpGradePeople]->m_UserData.i64Money; 

				}
				else
				{
					GameEnd.iTurePoint[m_iUpGradePeople] = -iNtPoint;
				}
			}

			//写入数据库				
			int temp_point[PLAY_COUNT];
			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			for (int i=0;i<PLAY_COUNT;i++)
			{
				temp_point[i]=GameEnd.iTurePoint[i];//+m_iAwardPoint[i];
				GameEnd.iChangeMoney[i]=GameEnd.iTurePoint[i];
				CString str;
			
			}
			
			ChangeUserPointint64(/*temp_point*/GameEnd.iTurePoint, temp_cut);
			__super::RecoderGameInfo(GameEnd.iChangeMoney);

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// 金币场不扣积分    add by wys 2010-11-1
			if (true == bNotCostPoint)
			{
				memset(GameEnd.iTurePoint,0,sizeof(GameEnd.iTurePoint));
			}
			//发送数据

			for (int i=0; i < PLAY_COUNT; i++) 
			{
				if (m_pUserInfo[i]!=NULL) 
					SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);
			}
			SendWatchData(m_bMaxPeople,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);

			ClearQuitPlayer();
			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GF_SALE:			//游戏安全结束
	case GFF_SAFE_FINISH:
		{
			m_bGameStation = GS_WAIT_ARGEE;//GS_WAIT_SETGAME;
			for (int i = 0; i < m_bMaxPeople; i++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			GameCutStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));
			CutEnd.bDeskStation=bDeskStation;
			for (int i = 0; i < m_bMaxPeople; i++)
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);
			bCloseFlag = GFF_SAFE_FINISH;

			ClearQuitPlayer();
			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;

		}
	case GFF_FORCE_FINISH:		//用户断线离开
		{
			//设置数据
			m_bGameStation=GS_WAIT_ARGEE;//GS_WAIT_SETGAME;

			for (int i=0;i<m_bMaxPeople;i++)
			{
				if (m_pUserInfo[i]!=NULL) 
					m_pUserInfo[i]->m_UserData.bUserState=USER_SITTING;
			}
			GameCutStruct CutEnd;
			memset(&CutEnd,0,sizeof(CutEnd));
			CutEnd.bDeskStation=bDeskStation;
			int total = 0;
			for (int i=0; i<PLAY_COUNT; i++)
			{
				total+=m_iPerJuTotalNote[i];
			}

			if (bDeskStation == m_iUpGradePeople)
			{
				CutEnd.iTurePoint[bDeskStation]= -total*5;;
			}
			else
			{
				CutEnd.iTurePoint[bDeskStation]= -m_iPerJuTotalNote[bDeskStation]*5;;//m_iTotalNote;			//扣除强退玩家全部下注
			}
			//CutEnd.iTurePoint[(bDeskStation+1)%PLAY_COUNT]=(m_iTotalNote-m_iBaseNote)/(CountPlayer()-1);
			//CutEnd.iTurePoint[(bDeskStation+2)%PLAY_COUNT]=(m_iTotalNote-m_iBaseNote)/(CountPlayer()-1);
			//CutEnd.iTurePoint[(bDeskStation+3)%PLAY_COUNT]=(m_iTotalNote-m_iBaseNote)/(CountPlayer()-1);
			////CutEnd.iTurePoint[(bDeskStation+4)%PLAY_COUNT]=(m_iTotalNote-m_iBaseNote)/(CountPlayer()-1);
			//CutEnd.iTurePoint[(bDeskStation+5)%PLAY_COUNT]=(m_iTotalNote-m_iBaseNote)/(CountPlayer()-1);

			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			int i=0;
			for (i=0; i<PLAY_COUNT; ++i) 
			{ 
				temp_cut[i] = (bDeskStation == i)?true:false; 
			} 


			ChangeUserPointint64(CutEnd.iTurePoint, temp_cut);
			//__super::RecoderGameInfo(CutEnd.iChangeMoney);

			__super::RecoderGameInfo(CutEnd.iChangeMoney);
			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// 金币场不扣积分    add by wys 2010-11-1
			if (true == bNotCostPoint)
			{
				memset(CutEnd.iTurePoint,0,sizeof(CutEnd.iTurePoint));
			}

			for (int i=0;i<m_bMaxPeople;i++)
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);

			bCloseFlag=GFF_FORCE_FINISH;

			ClearQuitPlayer();
			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	}

	//重置数据
	ReSetGameState(bCloseFlag);
	__super::GameFinish(bDeskStation,bCloseFlag);

	return true;
}

bool CServerGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo *pLostUserInfo)
{
	UserAI(bDeskStation, 1, true);
	return __super:: UserNetCut(bDeskStation, pLostUserInfo);
}

//用户断线重来
bool CServerGameDesk::UserReCome(BYTE bDeskStation, CGameUserInfo * pNewUserInfo)
{
	UserAI(bDeskStation, 1, false);
	return __super:: UserReCome(bDeskStation, pNewUserInfo);
}

//玩家AI设置
BOOL CServerGameDesk::UserAI(BYTE bDeskStation,BYTE bCutType,bool bNet)
{
	m_bIsCut[bDeskStation] = bNet;

	if(CountCutPlayer() == CountPlayer())	
	{
		GameFinish(0,GF_SALE);

		return FALSE;
	}
	if(1 == CountPlayer())	//仅1人
	{
		GameFinish(0,GF_SALE);

		return FALSE;
	}
	return TRUE;
}
//统计玩游戏玩家
BYTE CServerGameDesk::CountCutPlayer()
{
	BYTE count = 0;
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		if(m_pUserInfo[i] == NULL)
			continue;

		if(m_bIsCut[i])
		{	
			count ++;
		}
	}
	return count;
}
//判断是否正在游戏
bool CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	/*CString str;
	str.Format("zhtlog:bDeskStation=%d",bDeskStation);
	OutputDebugString(str);*/
	
	if (m_iUserStation[bDeskStation] == -1)
	{
		OutputDebugString("zhtlog:判断是否正在游戏");
		return false;
	}
	if(m_bGameStation>=GS_SEND_CARD&&m_bGameStation<GS_WAIT_NEXT)
		return true;
	else
		return false;
	//return __super::IsPlayGame(bDeskStation);
}

//用户离开游戏桌
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	/*	if ((m_pUserInfo[bDeskStation]!=NULL)&&(m_bGameStation==GS_WAIT_ARGEE)&&(bDeskStation==0))
	{
	//更改数据
	m_bGameStation=GS_WAIT_SETGAME;
	for (int i=0;i<m_bMaxPeople;i++)
	{
	if (m_pUserInfo[i]!=NULL) m_pUserInfo[i]->m_UserData.bUserState=USER_SITTING;
	}
	}
	else if(m_bGameStation==GS_WAIT_SETGAME && (m_pUserInfo[bDeskStation]!=NULL) && m_iBeenPlayGame>0)
	{
	GameFinish(0,GF_SALE);
	}*/
	SuperSetCard();
	if (m_iUserStation[bDeskStation] == -1)
	{
		return __super::UserLeftDesk(bDeskStation,pUserInfo);
	}
	if(m_bGameStation>GS_WAIT_ARGEE)
	{
		GameFinish(0,GF_SALE);
	}
	return __super::UserLeftDesk(bDeskStation,pUserInfo);
}
//用户请求离开
BOOL CServerGameDesk::UserHaveThing(BYTE bDeskStation, char * szMessage)
{
	if (m_bGameStation<GS_SEND_CARD)
		return TRUE;
	m_iHaveThingPeople=bDeskStation;
	m_iLeaveArgee|=1<<bDeskStation;
	if (m_iLeaveArgee!=15)
	{
		HaveThingStruct HaveThing;
		HaveThing.pos=bDeskStation;
		::CopyMemory(HaveThing.szMessage,szMessage,60*sizeof(char));
		for (int i=0;i<m_bMaxPeople;i++)
			if (i!=bDeskStation) SendGameData(i,&HaveThing,sizeof(HaveThing),MDM_GM_GAME_NOTIFY,ASS_HAVE_THING,0);
	}
	else GameFinish(bDeskStation,GF_SALE);

	return TRUE;
}

//同意用户离开
BOOL CServerGameDesk::ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee)
{
	if (bArgee) m_iLeaveArgee|=1<<bDeskStation;
	else m_iLeaveArgee&=~1<<bDeskStation;
	if (m_iLeaveArgee!=15)
	{
		//		m_bQueryQuit=true;
		LeaveResultStruct Leave;
		Leave.bDeskStation=bDeskStation;
		Leave.bArgeeLeave=bArgee;
		for (int i=0;i<m_bMaxPeople;i++) 
			if (i!=bDeskStation) SendGameData(i,&Leave,sizeof(Leave),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}
	else
	{
		GameFinish(bDeskStation,GF_SALE);
		//		GameFinish(m_iHaveThingPeople/*bDeskStation*/,GF_SALE);
		LeaveResultStruct Leave1;
		Leave1.bDeskStation=m_iHaveThingPeople;
		Leave1.bArgeeLeave=true;
		SendGameData(m_iHaveThingPeople,&Leave1,sizeof(Leave1),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}
	return TRUE;
}

//換底牌
BOOL CServerGameDesk::ChangeBackCard(BYTE bDeskStation,BYTE bSourceCard,BYTE bResultCard)
{
	ChangeBackStruct back;

	if(ReplaceCard(m_iTotalCard,m_iSendCardPos,28,bSourceCard,bResultCard))
	{
		m_iUserCard[bDeskStation][0]=bResultCard;
		back.bExtVal=true;
	}else
		back.bExtVal=false;

	back.bDeskStation=bDeskStation;
	back.bSourceCard=bSourceCard;
	back.bResultCard=bResultCard;
	for(int i=0;i<PLAY_COUNT;i++)
		SendGameData(i,&back,sizeof(back),MDM_GM_GAME_NOTIFY,ASS_GM_SUPERCLIENT,0);
	return true;
}
//系統底牌中是否有某張牌
BOOL CServerGameDesk::ReplaceCard(BYTE iTotalCard[],int iSendCardPos,int iEndPos,BYTE bSourceCard,BYTE bResultCard)
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

//逃跑扣分
int CServerGameDesk::GetRunPublish()
{
	return 15;//return m_pDataManage->m_InitData.uRunPublish;
}
//游戲基礎倍數
int CServerGameDesk::GetRoomBasePoint()
{
	int iBasePoint = m_pDataManage->m_InitData.uBasePoint;//倍数
	return (iBasePoint>0?iBasePoint:1);
}

//桌子倍数
int CServerGameDesk::GetDeskBasePoint()
{
	return 1;//GetTableBasePoint();
}
//统计倍数
int CServerGameDesk::GetHumanBasePoint()
{
	//金币场不进行比分换算
	//	if(m_pDataManage->m_InitData.uComType == TY_MONEY_GAME)

	__int64 minval=m_pUserInfo[0]->m_UserData.dwPoint;
	for(int i=1;i<PLAY_COUNT;i++)
	{
		minval=min(minval,m_pUserInfo[i]->m_UserData.dwPoint);
	}

	__int64 uBasePoint[22]=
	{
		0,10,30,60,
		100,200,400,640,
		920,1240,2140,4640,
		7390,10390,13640,20640,
		35640,51640,68640,86640,
		108640,138640
	};
	int BasePoint[22]=
	{
		1,2,3,4,
		5,10,12,14,
		16,18,50,55,
		60,65,70,150,
		160,170,180,190,
		200,210
	};
	for (int i=0;i<22;i++)	
		if (minval<uBasePoint[i]) 
			return BasePoint[i];
	return BasePoint[21];
}
//找庄家
BOOL CServerGameDesk::FindNt()
{
	/*if (m_iUpGradePeople == -1)
	{

	for (int i = 0; i < PLAY_COUNT; i++)
	{
	if (m_pUserInfo[i] != NULL && m_pUserInfo[i]->m_UserData.dwMoney > m_iLimitNote * 20)
	{
	m_iUpGradePeople = i;
	return TRUE;
	}
	}
	return FALSE;


	}
	else 
	{
	m_iUpGradePeople = (m_iUpGradePeople + 1) % PLAY_COUNT;
	for (int i = m_iUpGradePeople;;i=(i+1) % PLAY_COUNT)
	{
	if(!m_pUserInfo[i])
	continue;
	if (m_pUserInfo[i] != NULL && m_pUserInfo[i]->m_UserData.dwMoney > m_iLimitNote * 20)
	{
	m_iUpGradePeople = i;
	return TRUE;
	}
	if (i == (m_iUpGradePeople + (PLAY_COUNT-1)) % PLAY_COUNT)
	return FALSE;
	}

	}*/
	return true;

}
//计算各家分数
int CServerGameDesk::ComputePoint(BYTE DeskStation)
{

	int Shape;
	int Point = 0;
	int winer = -1;
	if( m_Logic.CompareCard(m_iUserCard[DeskStation], m_iUserCardCount[DeskStation], m_bBullCard[DeskStation],
		m_iUserCard[m_iUpGradePeople],m_iUserCardCount[m_iUpGradePeople],m_bBullCard[m_iUpGradePeople]) == 1)
	{
		winer = DeskStation;
		Point = 1;
	}
	else
	{
		winer = m_iUpGradePeople;
		Point = -1;
	}
	Shape = m_Logic.GetShape(m_iUserCard[winer],m_iUserCardCount[winer],m_bBullCard[winer]);
	Point = Point * m_bCardShapeBase[Shape];
	//switch(Shape)
	//{
	//case UG_FIVE_SMALL://五小

	//	Point = Point * 8;
	//	break;
	//case UG_BULL_BOMB://炸弹
	//	Point = Point * 8;
	//	break;
	//case UG_BULL_GOLD://金牛
	//	Point = Point * 7;
	//	break;
	//case UG_BULL_SILVER://银牛
	//	Point = Point * 6;
	//	break;
	//case UG_BULL_BULL:
	//	Point = Point * 5;
	//	break;
	//case UG_BULL_NINE:
	//	Point = Point * 4;
	//	break;
	//case UG_BULL_EIGHT:
	//	Point = Point * 3;
	//	break;
	//case UG_BULL_SEVEN:
	//	Point = Point * 2;
	//	break;
	//default:
	//	break;



	//}
	return Point;
}
BYTE CServerGameDesk::GetIndex(int win)
{
	BYTE Max = 0, Mix = 0;
	for (int i=1; i<PLAY_COUNT; i++)
	{
		if (m_Logic.CompareCard(&m_iTotalCard[Max*SH_USER_CARD],SH_USER_CARD,
			&m_iTotalCard[i*SH_USER_CARD],SH_USER_CARD)==-1)
			Max = i;
		if (m_Logic.CompareCard(&m_iTotalCard[Mix*SH_USER_CARD],SH_USER_CARD,
			&m_iTotalCard[i*SH_USER_CARD],SH_USER_CARD)==1)
			Mix = i;
	}
	if (win == 1)
		return Max;
	else 
		return Mix;

}
//判断负者
BOOL CServerGameDesk::JudgeLoser()
{
	try
	{
		//CString s = CINIFile::GetAppPath ();/////本地路径
		//CINIFile f( s +"userlist.ini");
		CString s = CINIFile::GetAppPath ();/////本地路径
		CINIFile f( s +SKIN_FOLDER +"_s.ini");
		CString key = TEXT("loser");
		int count = f.GetKeyVal(key,"count",0);
		if(count <= 0 )					//无胜者
			return FALSE;
		TCHAR szName[21];
		BYTE  bFind = 255;				//胜者座号
		int probability = 0;
		CString szNickName;
		for (int j = 0; j < PLAY_COUNT; j++)
		{
			if(m_pUserInfo[j] == NULL)
				continue;

			for(int i = 0; i < count; i ++)
			{
				wsprintf(szName,"nickname%d",i);
				szNickName = f.GetKeyVal(key,szName,"wing");

				if(strcmp(m_pUserInfo[j]->m_UserData.nickName,szNickName) != 0)
					continue;
				//优先胜率(仅只处理一个)
				wsprintf(szName,"prob%d",i);
				probability = f.GetKeyVal(key,szName,0);
				bFind = j;
				break;
			}

		}
		//当前玩家中无负者
		if(bFind == 255)
			return FALSE;

		BYTE bDest = GetIndex(0);
		srand(GetTickCount()); 
		if((rand() % 100) + 1 <= probability)	//一定得输
		{
			if(bFind != bDest)
				ChangeCard(bFind,bDest);
		}
		//else								//一定得胜 将胜家留给胜利受控人
		//{
		//	if(bFind != bDest)
		//		ChangeCard(bFind,bDest);
		//}
		return TRUE;
	}
	catch(...)
	{
		return TRUE;
	}
	return FALSE;
}

//判断胜者
BOOL CServerGameDesk::JudgeWiner()
{
	try
	{
		//CString s = CINIFile::GetAppPath ();/////本地路径
		//CINIFile f( s +"userlist.ini");
		CString s = CINIFile::GetAppPath ();/////本地路径
		CINIFile f( s +SKIN_FOLDER +"_s.ini");
		CString key = TEXT("winer");
		int count = f.GetKeyVal(key,"count",0);

		if(count <= 0 )					//无胜者
			return FALSE;

		TCHAR szName[21];
		BYTE  bFind = 255;				//胜者座号
		int probability = 0;
		CString szNickName;
		for (int j = 0; j < PLAY_COUNT; j++)
		{
			if(m_pUserInfo[j] == NULL)
				continue;
			for(int i = 0; i < count; i ++)
			{
				wsprintf(szName,"nickname%d",i);
				szNickName = f.GetKeyVal(key,szName,"wing");

				if(strcmp(m_pUserInfo[j]->m_UserData.nickName,szNickName) != 0)
					continue;
				//优先胜率(仅只处理一个)
				wsprintf(szName,"prob%d",i);
				probability = f.GetKeyVal(key,szName,0);
				bFind = j;
				break;
			}
			if(bFind != 255)
				break;
		}

		//当前玩家中无胜者
		if(bFind == 255)
			return FALSE;
		BYTE bDest = GetIndex(1);
		srand(GetTickCount()); 
		if((rand() % 100) + 1 <= probability)//产生胜者
		{
			if(bFind != bDest)
				ChangeCard(bFind,bDest);
		}
		//else	//一定得输
		//{
		//	if(bFind == bDest)
		//		ChangeCard(bFind,(bDest + 1) % PLAY_COUNT);
		//}
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
	return FALSE;
}
//换牌
BOOL CServerGameDesk::ChangeCard(BYTE bDestStation,BYTE bWinStation)
{
	for(int i = 0; i < SH_USER_CARD; i ++)
	{
		BYTE bTemp = m_iTotalCard[bDestStation * SH_USER_CARD + i];
		m_iTotalCard[bDestStation * SH_USER_CARD + i ] = m_iTotalCard[bWinStation * SH_USER_CARD + i];
		m_iTotalCard[bWinStation * SH_USER_CARD + i] = bTemp;
	}
	return TRUE;
}
//叫庄
BOOL CServerGameDesk::UserCallScore(BYTE bDeskStation, int iVal)
{
	if(bDeskStation != m_bCurrentCallScore)
		return true;
	KillTimer(TIME_CALL_NT);
	if(iVal == 0)
	{	
		m_iCallScore[bDeskStation] = 0;		//====某位置不叫分
	}
	else
	{
		m_iPrepareNT = bDeskStation;				//最后叫分者
		goto NT;
	}
	CallScoreStruct callscore;
	callscore.bDeskStation = bDeskStation;
	callscore.bCallScoreflag = FALSE;					
	callscore.iValue = m_iCallScore[bDeskStation];		//当前叫分类型保存

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&callscore,sizeof(callscore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_RESULT,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&callscore,sizeof(callscore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_RESULT,0);

	int iNextPeople = GetNextDeskStation(bDeskStation);

	if(m_iCallScore[iNextPeople] == 0)
	{
		m_iPrepareNT=m_iFirstJiao;
		m_iCallScore[m_iFirstJiao]=1;
		goto NT;
	}

	if(m_iCallScore[iNextPeople] == -1)
	{
		SendCallScore(iNextPeople);
		return TRUE;
	}

NT:		
	CallScoreFinish();
	return true;
}
//获取下一个玩家位置
BYTE CServerGameDesk::GetNextDeskStation(BYTE bDeskStation)
{
	if(!m_bTurnRule)//顺时针
	{
		int i=1;
		for (;i<PLAY_COUNT; i++)
		{
			if (m_pUserInfo[(bDeskStation + i ) % PLAY_COUNT] && m_iUserStation[(bDeskStation + i ) % PLAY_COUNT] != -1)
				break;
		}

		return (bDeskStation + i ) % PLAY_COUNT;
	}
	//逆时针
	int i=3;
	for (;i>=1; i--)
	{
		if (m_pUserInfo[(bDeskStation + i ) % PLAY_COUNT] &&  m_iUserStation[(bDeskStation + i ) % PLAY_COUNT] != -1)
			break;
	}
	return 	(bDeskStation + i) % PLAY_COUNT;
}
//叫分结束
BOOL CServerGameDesk::CallScoreFinish()
{
	if (m_iPrepareNT == 255 )	//没有人叫分.重新发牌
	{
		GameFinish(0,GF_SALE);
		return true;
	}
	if (m_iCallScore[m_iPrepareNT] == 0 )	//没有人叫分.重新发牌
	{
		GameFinish(0,GF_SALE);
		return true;
	}
	//用于抢地主位置结束控制
	m_iNtPeople = m_iPrepareNT;

	CallScoreStruct scoreresult;
	scoreresult.iValue = m_iCallScore[m_iPrepareNT];
	scoreresult.bDeskStation  = m_iPrepareNT;
	scoreresult.bCallScoreflag = false;

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&scoreresult,sizeof(scoreresult),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_FINISH,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&scoreresult,sizeof(scoreresult),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_FINISH,0);

	UserNote();
	//直接进入游戏
	//SendBackCard();
	return TRUE;
}
//发送给第一个叫分
BOOL CServerGameDesk::SendCallScore(BYTE bDeskStation)
{
	//m_bGameStation = GS_WAIT_BACK;
	m_iGameFlag = GS_FLAG_CALL_SCORE;																	

	CallScoreStruct CallScore;
	CallScore.iValue = (m_iPrepareNT == 255) ? -1 : m_iCallScore[m_iPrepareNT];
	CallScore.bDeskStation = bDeskStation;						
	CallScore.bCallScoreflag = true;	


	m_bCurrentCallScore = bDeskStation ;

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		CallScore.bPlayer = m_iUserStation[i] == -1?false:true;
		SendGameData(i,&CallScore,sizeof(CallScore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE,0);
	}

	SendWatchData(m_bMaxPeople,&CallScore,sizeof(CallScore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE,0);
	SetTimer(TIME_CALL_NT,(m_iCallScoreTime+2)*1000);
	return TRUE;
}
//得到玩家的下注上限
__int64 CServerGameDesk::GetLimit(int bDeskStation)
{
	if (m_pUserInfo[m_iUpGradePeople]!= NULL && m_pUserInfo[bDeskStation]!=NULL&&CountPlayer()>1)
	{

		__int64 NtNote = m_pUserInfo[m_iUpGradePeople]->m_UserData.i64Money;
		__int64 StationNote = m_pUserInfo[bDeskStation]->m_UserData.i64Money;

		//2011-7-25 程序设定不能超过十亿，超过十亿以十亿显示
		/*if (NtNote > 1000000000)
		{
		NtNote = 1000000000;
		}*/
		double TempBase = 0;
		double temp = 1;
		int MaxBase = 1; //游戏最大倍率
		int iCardShapeCount = MAX_SHAPE_COUNT;
		if (m_iGameNoteSetType>0)
		{
			iCardShapeCount = 11;
		}
		for (int i=0; i<iCardShapeCount; i++)
		{
			if (m_bCardShapeBase[i] > MaxBase)
			{
				MaxBase = m_bCardShapeBase[i];
			}
		}
		if (m_GameType == 1)
		{
			TempBase = 0.125;
		}
		else
		{
			if (NtNote > StationNote)
			{
				TempBase = temp/MaxBase/(CountPlayer()-1);
			}
			else
			{
				TempBase = temp/MaxBase/(CountPlayer()-1);
			}
		}
		/*CString CST;
		CST.Format("wyslog::MaxBase===%d,m_GameType==%d",MaxBase,m_GameType);
		OutputDebugString(CST);*/
		if (NtNote > StationNote)
		{
			return StationNote*TempBase;//StationNote/5/(CountPlayer()-1); //20100802 zht 同喜乐客户修改了输赢结算
		}
		else
		{
			return NtNote*TempBase;//NtNote/5/(CountPlayer()-1); //20100802 zht 同喜乐客户修改了输赢结算
		}
	}
	else
	{
		return 0;
	}
}

//玩家强退
BOOL CServerGameDesk::UserFourceQuit(BYTE bDeskStation)
{
	/*CString aa;
	aa.Format("AAAAA:HandleGameMessage %d, %d, %d",m_iUserStation[bDeskStation],m_iGameStation,m_bGameStation);*/

	// 可以摆牛了，这时玩家强退。系统自动帮其摆牛
	if ((TYPE_OPEN==m_iGameStation || TYPE_NOTE==m_iGameStation || TYPE_BULL==m_iGameStation))
	{
		BYTE bResult[3];
		memset(bResult, 0, sizeof(bResult));
		tagUserProcess Verb;
		Verb.iVrebType = TYPE_OPEN;
		
		if (m_Logic.GetBull(m_iUserCard[bDeskStation], 5, bResult))
		{
			::CopyMemory(m_bBullCard[bDeskStation], bResult, sizeof(bResult));
		}
		else
		{
			memset(m_bBullCard[bDeskStation], 0, sizeof(m_bBullCard[bDeskStation]));
			m_bBullCard[bDeskStation][0] = m_iUserCard[bDeskStation][0];
			m_bBullCard[bDeskStation][1] = m_iUserCard[bDeskStation][1];
			m_bBullCard[bDeskStation][2] = m_iUserCard[bDeskStation][2];
		}
		
		UserActiveResult(bDeskStation, Verb.iVrebType, 0);
		CheckFinish();
	}
	else
	{
		// 没有叫庄、下庄时强退只扣掉强退玩家分给系统。游戏结束
		//GameFinish(bDeskStation, GFF_FORCE_FINISH);
	}

	//CleanCutGameInfo(bDeskStation);

	//游戏结束
	if(IsPlayingByGameStation())
	{	
		if(!UserAI(bDeskStation, 2, true))
			return TRUE;
	}
	else
	{
		return TRUE;
	}

	return TRUE;
}

//清理强退玩家
void CServerGameDesk::ClearQuitPlayer()
{
	return;
	//广播踢出所有断线玩家
	for (BYTE i=0; i<PLAY_COUNT; i++)
	{
		if (m_bIsCut[i])
		{
			MakeUserOffLine(i);
		}
	}
}
///清理所有计时器
void CServerGameDesk::KillAllTimer()
{
	KillTimer(TIME_SEND_CARD);			//发牌定时器
	KillTimer(TIME_CALL_NT);				//叫庄
	KillTimer(TIME_GAME_FINISH);			//游戏结束定时器
	KillTimer(TIME_SEND_A_CARD);				//发送一张牌
	KillTimer(TIME_BEGIN_ANIMAL);				//游戏开始动画
	KillTimer(TIME_COLLECT_JETON);				//收集动画
	KillTimer(TIME_CUTLINE_AUTO);				//断线自动摆牛
	KillTimer(TIME_NOTE);             //下注计时器
}

int CServerGameDesk::GetMaxCardShape(BYTE iCard[], int iCardCount)
{
	if (iCardCount < SH_USER_CARD*PLAY_COUNT)
	{
		return 0;
	}
	int shape = 0;
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		if (m_pUserInfo[i] && m_iUserStation[i]!=-1)
		{
			int temp = m_Logic.GetShape(&m_iTotalCard[i*SH_USER_CARD],SH_USER_CARD);
			if (shape < temp)
			{
				shape = temp;
			}
		}
		
	}
	return shape;
}