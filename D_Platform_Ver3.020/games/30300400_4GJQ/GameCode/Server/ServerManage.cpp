#include "StdAfx.h"
#include "ServerManage.h"

/**
 * 获取游戏状态信息
 */
bool CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{
	switch (m_bGameStation)
	{
	case GS_WAIT_SETGAME:		//游戏没有开始状态
		{
			GameStation_1 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			GameStation.iMainVersion=MAIN_VERSION;
			GameStation.iLessVersion=ASS_VERSION;
			GameStation.uRunPublish=m_pDataManage->m_InitData.uRunPublish;
			GameStation.basepoint=m_pDataManage->m_InitData.uBasePoint;
			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));

			MessageStruct Mess;
			ZeroMemory(Mess.Message,200);
			lstrcpy(Mess.Message,"欢迎您参加四国军棋游戏，祝您玩得开心！");
			SendGameData(bDeskStation,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);

			return TRUE;
		}
	case GS_WAIT_ARGEE:			//等待玩家开始状态
		{
			GameStation_2 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			GameStation.iPlayCount=m_iLessCount;
			GameStation.iMainVersion=MAIN_VERSION;
			GameStation.iLessVersion=ASS_VERSION;
			GameStation.uRunPublish=m_pDataManage->m_InitData.uRunPublish;
			GameStation.basepoint=m_pDataManage->m_InitData.uBasePoint;
			for(int i=0;i<MAX_I;i++)
		      for(int j=0;j<MAX_J;j++)
	        GameStation.mBoard[i][j]=m_Logic.mBoard[i][j];

			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	case GS_BUZHEN:		//发牌状态(还未发牌)
	case GS_PLAY_GAME:	//游戏中状态
		{
			GameStation_3 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			GameStation.iPlayCount=m_iLessCount;
			GameStation.iTimerCount = m_iTimerCount ; 
			GameStation.iPunishPoint=m_PunishPoint[bDeskStation];
			GameStation.iBeenPlayGame=m_iBeenPlayGame;
			GameStation.m_iNowOutPeople=m_Logic.m_iNowOutPeople;	

			GameStation.m_iStartI=m_Logic.m_iStartI;
			GameStation.m_iStartJ=m_Logic.m_iStartJ;
			GameStation.m_iEndI=m_Logic.m_iEndI;
			GameStation.m_iEndJ=m_Logic.m_iEndJ;
			GameStation.uRunPublish=m_pDataManage->m_InitData.uRunPublish;
			GameStation.basepoint=m_pDataManage->m_InitData.uBasePoint;
			for(int i=0;i<MAX_I;i++)
		      for(int j=0;j<MAX_J;j++)
	        GameStation.mBoard[i][j]=m_Logic.mBoard[i][j];


			int iSendSize=sizeof(GameStation);
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,iSendSize);
			return TRUE;
		}

	case GS_WAIT_NEXT:		//等待下一盘游戏开始
		{
			GameStation_5 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			GameStation.iPlayCount=m_iLessCount;
			GameStation.iPunishPoint=m_PunishPoint[bDeskStation];			
			GameStation.iBeenPlayGame=m_iBeenPlayGame;		
			GameStation.uRunPublish=m_pDataManage->m_InitData.uRunPublish;
			GameStation.basepoint=m_pDataManage->m_InitData.uBasePoint;
			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	}
	return false;
}

bool CServerGameDesk::H021_UserPass(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	//发送开始消息
	m_Logic.m_iNowOutPeople=m_Logic.GetNextStation (bDeskStation);
	tagNextStep s;
	s.station=m_Logic.m_iNowOutPeople;
	for (int i=0;i<4;i++) SendGameData(i,&s,sizeof(s),MDM_GM_GAME_NOTIFY,ASS_NEXT_STEP,0);
	SendWatchData(m_bMaxPeople,&s,sizeof(s),MDM_GM_GAME_NOTIFY,ASS_NEXT_STEP,0);

	KillTimer(TIME_USER_OUT_CARD) ; 

	m_iTimerCount = m_iLessCount + 3 ; 
	SetTimer(TIME_USER_OUT_CARD ,1000) ;  
	
	return true;
}

/**
 * 同意用户离开
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::H0011_UserBuZhen(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	///if(bWatchUser)				return true;
	tagBuZhen * bz=(tagBuZhen *)pData;

	m_Logic.UserBuZhen (*bz);
	m_bBuzhen[bDeskStation]=true;
	for (int i=0;i<4;i++) SendGameData(i,bz,sizeof(*bz),MDM_GM_GAME_NOTIFY,ASS_BUZHEN,0);
	SendWatchData(m_bMaxPeople,bz,sizeof(*bz),MDM_GM_GAME_NOTIFY,ASS_BUZHEN,0);

	if(m_Logic.GetBuzhenCount() >= GetPlayerCount()&&GS_BUZHEN==m_bGameStation)
	{
		m_bGameStation=GS_PLAY_GAME;

		//发送开始消息
		tagNextStep s;

		s.station=m_Logic.m_iNowOutPeople;
		
		for (int i=0;i<4;i++) SendGameData(i,&s,sizeof(s),MDM_GM_GAME_NOTIFY,ASS_NEXT_STEP,0);
		SendWatchData(m_bMaxPeople,&s,sizeof(s),MDM_GM_GAME_NOTIFY,ASS_NEXT_STEP,0);

		KillTimer(TIME_USER_OUT_CARD) ;

		m_iTimerCount = m_iLessCount + 3 ; 
		SetTimer(TIME_USER_OUT_CARD ,1000) ;  
	}

	return true;
}

int CServerGameDesk::GetPlayerCount()
{
	int count=0;
	for(int i=0;i<m_bMaxPeople;i++)
	{
		if(m_pUserInfo[i])
			count++;
	}
	return count;
}

int CServerGameDesk::GetPlayerStation()
{
	for(int i=0;i<m_bMaxPeople;i++)
	{
		if(m_pUserInfo[i])
			return i;
	}
	return -1;
}

/**
 * 用户出牌
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::H020_UserOutCard(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	//GameFinish(bDeskStation,GF_NORMAL);//*shingo*
	//return true;
	if (bWatchUser) return FALSE;
	if(m_bGameStation!=GS_PLAY_GAME)
		return true;
	if (uSize!=sizeof(tagMove)) return FALSE;
	if(bDeskStation!=m_Logic.m_iNowOutPeople)
		return false;
	tagMove * pOutCard=(tagMove *)pData;
	tagMoveResult   m;
	memset(m.cPath, 255, sizeof(m.cPath));
	/*if(pOutCard->m_iStartI==-1)
	{//有玩家无子可下了
	m.station=bDeskStation;
	m.loseColor=m_Logic.GetColorFromStation(bDeskStation);
	m.m_iStartI=-1;
	m_Logic.ClearColorAllQiZi(m.loseColor);
	int *p=new int;
	*p=bDeskStation;
	bool cor[4];
	m_Logic.GetDeadPeople(cor);
	m_Logic.mLoseStationList.AddTail(p);
	for(int i=0; i<4; i++)
	{

	if(i == *p)
	continue;
	if(!cor[i])
	{
	TCHAR sz[100];
	wsprintf(sz,"lose color %d",i);
	Testlog(sz);
	int *p1=new int;
	*p1=bDeskStation;
	m_Logic.mLoseStationList.AddTail(p1);
	}
	}
	m.nextstation=m_Logic.GetNextStation(m.station);
	}
	else
	{*/
	m.station=bDeskStation;
	m_Logic.UserMove(*pOutCard,m);
	//}
	if(m_Logic.IsFinish())
		m.nextstation=-1;
	m_Logic.m_iNowOutPeople=m.nextstation;
	m.iStep = pOutCard->iStep;
	memcpy(m.cPath, pOutCard->cPath, sizeof(m.cPath));

	for (int i=0;i<m_bMaxPeople;i++) 
		SendGameData(i,&m,sizeof(m),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);
	SendWatchData(m_bMaxPeople,&m,sizeof(m),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);

	KillTimer(TIME_USER_OUT_CARD) ;

	m_iTimerCount = m_iLessCount + 3 ; 
	SetTimer(TIME_USER_OUT_CARD ,1000) ;

	if(m.loseColor >= 0)//m_Logic.IsStationLose(bDeskStation))
	{
		tagNextStep N;
		if(pOutCard->m_iStartI==-1)
			N.station =bDeskStation;
		else
			N.station=m_Logic.GetStationFromColor(m.loseColor);
		N.station2=m_Logic.GetStationFromColor(m.loseColor2);
		for (int i=0;i<4;i++) 
			SendGameData(i,&N,sizeof(N),MDM_GM_GAME_NOTIFY,ASS_LOSE,0);
		SendWatchData(m_bMaxPeople,&N,sizeof(N),MDM_GM_GAME_NOTIFY,ASS_LOSE,0);
	}

	if(m_Logic.IsFinish())
	{
		m_bGameStation=GS_PLAY_GAME;
		SetTimer(TIME_GAME_FINISH,2000);
	}
	return true;
}

/**
 * 定时器消息
 */
bool CServerGameDesk::OnTimer(UINT uTimerID)
{
	if (uTimerID==TIME_GAME_FINISH)	//结束定时器
	{
		KillTimer(TIME_GAME_FINISH);
		if (m_bGameStation==GS_PLAY_GAME) GameFinish(0,GF_NORMAL);
	}
	else if(uTimerID == TIME_USER_OUT_CARD)
	{
		m_iTimerCount --;

		if(m_iTimerCount < 0 )
		{
			KillTimer(TIME_USER_OUT_CARD) ; 

			if(m_bGameStation == GS_PLAY_GAME)
			{
				H021_UserPass(m_Logic.m_iNowOutPeople ,NULL ,NULL ,0,0,false) ;
			}
		}

		return true ;
	}
	return __super::OnTimer(uTimerID);
}

/**
 * 游戏数据包处理函数
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::H000_UserAgreeGame(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	//用户同意游戏
	if (bWatchUser) return FALSE;
	if ((bDeskStation==0)&&(m_bGameStation==GS_WAIT_SETGAME))	//东家设置
	{
		if (uSize!=sizeof(UserArgeeGame)) return FALSE;
		UserArgeeGame * pGameSet=(UserArgeeGame *)pData;
		if (!UserSetGame(pGameSet)) return FALSE;
		__super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
		return TRUE;
	}
	//其他玩家
	if ((m_bGameStation!=GS_WAIT_ARGEE)&&(m_bGameStation!=GS_WAIT_NEXT)) 
		return TRUE;
	int count=0;
	for(int i=0;i<m_bMaxPeople;i++)
	{
		if(!m_pUserInfo[i])
			continue;
		if(m_pUserInfo[i]->m_UserData.bUserState==USER_ARGEE)
			count++;
	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}

/**
 * 游戏结束
 * @param bDeskStation 玩家ID
 * @param bCloseFlag 结束类型
 */
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	KillTimer(TIME_USER_OUT_CARD) ; 
	//得到最小数的金币
	long m_dwMaxPoint=0;
	bool bSetMaxMoney=false;
	/*for (BYTE i=0;i<m_bMaxPeople;i++)
	{
		if (m_pUserInfo[i]!=NULL)
		{
			if (bSetMaxMoney==false)
			{
				bSetMaxMoney=true;
				m_dwMaxPoint=(long int)m_pUserInfo[i]->m_UserData.dwPoint-1;
			}
			else 
				m_dwMaxPoint=__min(m_dwMaxPoint,(long int)m_pUserInfo[i]->m_UserData.dwPoint-1);
		}
	}
	if(m_pDataManage->m_InitData.uComType!=TY_NORMAL_GAME && m_dwMaxPoint<0)
	{
		TRACE("出现错误，四国军棋金币或比赛游戏中，玩家的金币数为负数．");
		return false;
	}*/

	//编写代码
	switch (bCloseFlag)
	{
	case GF_PREEND:     //提前结束
	case GF_NORMAL:		//游戏正常结束
		{
			int iBasePoint=m_pDataManage->m_InitData.uBasePoint;//倍数
			//计算得分
			//游戏结束
			GameEndStruct GameEnd;
			::memset(&GameEnd,0,sizeof(GameEnd));
            
			m_Logic.CountFen(GameEnd.iTurePoint);

			if (GF_PREEND == bCloseFlag)//提前结束
			{
				GameEnd.iTurePoint[bDeskStation] = GameEnd.iTurePoint[(bDeskStation+2)%4] = -2;//提出提前结束的一方
				GameEnd.iTurePoint[(bDeskStation+1)%4] = GameEnd.iTurePoint[(bDeskStation+3)%4] = 2;//另一方
			}


			//设置基本分begin
			m_pDataManage->m_InitData.uBasePoint = 1;
			int base=-1;
			int temp;
			for(int i=1;i<m_bMaxPeople;i++)
			{
				if (m_pUserInfo[i]==NULL)
					continue;
				temp=m_Logic.GetBaseFen(m_pUserInfo[i]->m_UserData.dwPoint);
				if(base>temp||-1==base)
					base=temp;
			}

			for(int i=0; i<m_bMaxPeople; i++)
			{
				if(NULL == m_pUserInfo[i])
				{
					GameEnd.iTurePoint[i] = 0;
					continue;
				}
				GameEnd.iTurePoint[i]*=base;					
			}
			//设置基本分end
			//设置数据 
				m_bGameStation=GS_WAIT_ARGEE;
				for (int i=0;i<m_bMaxPeople;i++)
				{
					if (m_pUserInfo[i]!=NULL) 
						m_pUserInfo[i]->m_UserData.bUserState=USER_SITTING;
				}
				/*if (m_pDataManage->m_InitData.uComType!=TY_NORMAL_GAME)
				{
					GameEnd.iTurePoint[0]*=iBasePoint;
					GameEnd.iTurePoint[1]*=iBasePoint;
					GameEnd.iTurePoint[2]*=iBasePoint;
					GameEnd.iTurePoint[3]*=iBasePoint;
					for (BYTE i=0;i<m_bMaxPeople;i++)
					{
						if(GameEnd.iTurePoint[i]>0)
							GameEnd.iTurePoint[i]=__min(m_dwMaxPoint,GameEnd.iTurePoint[i]);
						if(GameEnd.iTurePoint[i]<0)
							GameEnd.iTurePoint[i]=__max(-m_dwMaxPoint,GameEnd.iTurePoint[i]);
						if (GameEnd.iTurePoint[i]>=100)
						{
							if(m_pDataManage->m_InitData.uComType!=SUP_MATCH_GAME)
								GameEnd.iTurePoint[i]=GameEnd.iTurePoint[i]*49L/50L;
						}
					}
				}*/
			
				//写入数据库				
			/*	bool temp_cut[PLAY_COUNT];
				memset(temp_cut,0,sizeof(temp_cut));
				ChangeUserPoint(GameEnd.iTurePoint, temp_cut);
				__super::RecoderGameInfo(GameEnd.iChangeMoney);*/
			//写入数据库				
				bool temp_cut[4];
				memset(temp_cut,0,sizeof(temp_cut));
				ChangeUserPoint(GameEnd.iTurePoint, temp_cut);
				__super::RecoderGameInfo(GameEnd.iChangeMoney);
				GameEnd.iDoublePointEffect = GetDoublePointEffect();//20081125

				bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// 金币场不扣积分    add by wys 2010-11-1
				if (true == bNotCostPoint)
				{
					memset(GameEnd.iTurePoint,0,sizeof(GameEnd.iTurePoint));
				}
				//发送数据
				for (int i=0;i<m_bMaxPeople;i++) 
					SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);
				SendWatchData(m_bMaxPeople,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);

				
				ReSetGameState(bCloseFlag);
				__super::GameFinish(bDeskStation,GF_SALE);
				return true;



		}
	case GF_SALE:			//游戏安全结束
	case GFF_FORCE_FINISH:		//用户断线离开
		{
			int iBasePoint=m_pDataManage->m_InitData.uBasePoint;//倍数
			//计算得分
//			int iTurePoint=GetUpGrade(m_iGamePoint,m_iPlayCardCount);
			//设置数据
			m_bGameStation=GS_WAIT_ARGEE;

			for (int i=0;i<m_bMaxPeople;i++)
			{
				if (m_pUserInfo[i]!=NULL) 
					m_pUserInfo[i]->m_UserData.bUserState=USER_SITTING;
			}
			GameCutStruct CutEnd;
			CutEnd.bDeskStation=bDeskStation;
			if(bCloseFlag==GF_SALE)
			{
				CutEnd.iTurePoint[bDeskStation]=0;
				CutEnd.iTurePoint[(bDeskStation+1)%4]=0;
				CutEnd.iTurePoint[(bDeskStation+2)%4]=0;
				CutEnd.iTurePoint[(bDeskStation+3)%4]=0;
			}
			else
			{
				//设置分数
				CutEnd.iTurePoint[bDeskStation]=0-m_pDataManage->m_InitData.uRunPublish;;
				CutEnd.iTurePoint[(bDeskStation+1)%4]=0;
				CutEnd.iTurePoint[(bDeskStation+2)%4]=0;
				CutEnd.iTurePoint[(bDeskStation+3)%4]=0;

			}

			//发送信息
			if (bCloseFlag==GF_SALE)
			{
				for (int i=0;i<m_bMaxPeople;i++) SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);
				SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);
			}
			else
			{
				//计算金币类和比赛类的实得分
				/*if (m_pDataManage->m_InitData.uComType!=TY_NORMAL_GAME)
				{
					CutEnd.iTurePoint[0]*=iBasePoint;
					CutEnd.iTurePoint[1]*=iBasePoint;
					CutEnd.iTurePoint[2]*=iBasePoint;
					CutEnd.iTurePoint[3]*=iBasePoint;
					for (BYTE i=0;i<m_bMaxPeople;i++)
					{
						if(CutEnd.iTurePoint[i]>0)
							CutEnd.iTurePoint[i]=__min(m_dwMaxPoint,CutEnd.iTurePoint[i]);
						if(CutEnd.iTurePoint[i]<0)
							CutEnd.iTurePoint[i]=__max(-m_dwMaxPoint,CutEnd.iTurePoint[i]);
						if (CutEnd.iTurePoint[i]>=100)
						{
							if(m_pDataManage->m_InitData.uComType!=SUP_MATCH_GAME)
								CutEnd.iTurePoint[i]=CutEnd.iTurePoint[i]*49L/50L;
						}
					}
				}*/
				
			/*	bool temp_cut[PLAY_COUNT];
				memset(temp_cut,0,sizeof(temp_cut));
				for (int i=0;i<PLAY_COUNT;i++)
				{
					temp_cut[i]=(bDeskStation==i && CutEnd.iTurePoint[i]<0);
				}
				ChangeUserPoint(CutEnd.iTurePoint, temp_cut);
				__super::RecoderGameInfo(CutEnd.iChangeMoney);*/
				//写入数据库				
				bool temp_cut[4];
				memset(temp_cut,0,sizeof(temp_cut));
				for (int i=0;i<m_bMaxPeople;i++)
				{
					temp_cut[i]=(bDeskStation==i && CutEnd.iTurePoint[i]<0);
				}
				ChangeUserPoint(CutEnd.iTurePoint, temp_cut);
				__super::RecoderGameInfo(CutEnd.iChangeMoney);

				bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// 金币场不扣积分    add by wys 2010-11-1
				if (true == bNotCostPoint)
				{
					memset(CutEnd.iTurePoint,0,sizeof(CutEnd.iTurePoint));
				}

				for (int i=0;i<m_bMaxPeople;i++)
					SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);
				SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);
			}

			bCloseFlag=GFF_FORCE_FINISH;

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

/**
 * 游戏开始
 */
bool CServerGameDesk::H001_GameBegin(BYTE bBeginFlag)
{
	if (__super::GameBegin(bBeginFlag)==false) 
		return false;
	//设置状态
	m_bQueryQuit=false;
	m_iBeenPlayGame++;
	m_bGameStation=GS_BUZHEN;
	//发送开始消息
	BeginGameStruct BeginMessage;
	BeginMessage.iPlayCount=m_iBeenPlayGame;	
	for (int i=0;i<4;i++) SendGameData(i,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_BEGIN_UPGRADE,0);
	SendWatchData(m_bMaxPeople,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_BEGIN_UPGRADE,0);
	return TRUE;
}

/**
 * 游戏开始
 */
BOOL CServerGameDesk::BeginPlayUpGrade()
{
	//设置数据
	m_bGameStation=GS_PLAY_GAME;
//	m_iBaseOutCount=0;
//	m_Logic.m_iOutCardPeople=m_Logic.m_iUpGradePeople;
//	m_iFirstOutPeople=m_Logic.m_iUpGradePeople;
//	m_iGamePoint=0;
//	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));

	//排列扑克
	///for (int i=0;i<4;i++) m_Logic.SortCard(m_iUserCard[i],NULL,m_iUserCardCount[i]);

	//发送游戏开始消息
	BeginPlayStruct Begin;
//	Begin.iOutDeskStation=m_Logic.m_iOutCardPeople;
	for (int i=0;i<m_bMaxPeople;i++) SendGameData(i,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);
	SendWatchData(m_bMaxPeople,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);

	return TRUE;
}

/**
 * 有事请求离开
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::H040_UserHaveThing(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if(bWatchUser)				return false;
	HaveThingStruct * pThing=(HaveThingStruct *)pData;
	return H041_UserHaveThing(bDeskStation,pThing->szMessage);
}

/**
 * 同意用户离开
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::H043_ArgeeUserLeft(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if(bWatchUser)				return false;
	LeaveResultStruct * pLeave=(LeaveResultStruct *)pData;
	return H044_ArgeeUserLeft(bDeskStation,pLeave->bArgeeLeave);
}

/**
 * 游戏数据包处理函数
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	switch (pNetHead->bAssistantID)
	{

	case ASS_PASS:		//用户同意游戏
		{
			return H021_UserPass(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
		}
		case ASS_BUZHEN:		//用户同意游戏
		{
			return H0011_UserBuZhen(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
		}
	


	case ASS_GM_AGREE_GAME:		//用户同意游戏
		{
			return H000_UserAgreeGame(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
		}
	

	case ASS_OUT_CARD:		//用户出牌
		{
			return H020_UserOutCard(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
			
		}
	case ASS_HAVE_THING:	//有事请求离开
		{
			return H040_UserHaveThing(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
		}
	case ASS_LEFT_RESULT: //同意用户离开
		{
			return H043_ArgeeUserLeft(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
			
		}
	case ASS_STOP_THING:
		{
			return H046_StopThing(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
			
		}
	case ASS_AGREE_STOP:
		{
			return H048_ArgeeStopThing(bDeskStation, pNetHead, pData, uSize, uSocketID,  bWatchUser);
			
		}
	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}

/**
 * 同意用户离开
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::H048_ArgeeStopThing(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
			if(bWatchUser)
				return false;
			StopResultStruct * pStop=(StopResultStruct *)pData;
			if(pStop->bArgee==1)
			{
				//同意
				StopResultStruct stop;
				stop.bArgee=true;
				SendGameData((bDeskStation+2)%4,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);

				MessageStruct Mess;
				memset(&Mess,0,sizeof(Mess));
				lstrcpy(Mess.Message,"敌家经过商量，提前结束了本局！");
				SendGameData((bDeskStation+1)%4,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);
				SendGameData((bDeskStation+3)%4,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);

				memset(&Mess,0,sizeof(Mess));
				lstrcpy(Mess.Message,"拣分的双方经过商量，提前结束了本局！");
				SendWatchData(m_bMaxPeople,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);
				//结束游戏
				if (m_bGameStation==GS_PLAY_GAME) 
					GameFinish(bDeskStation, GF_PREEND);//提前结束
			}
			else
			{
				StopResultStruct stop;
				stop.bArgee=false;
				SendGameData((bDeskStation+2)%4,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);
			}
			return true;
}

/**
 * 同意用户离开
 * @param bDeskStation 玩家ID
 * @param pNetHead 参数基类
 * @param pData 网络数据包
 * @param uSize 数据包大小
 * @param uSocketID 参数基类
 * @param bWatchUser 是否旁观
 */
bool CServerGameDesk::H046_StopThing(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if(bWatchUser)
		return false;
	SendGameData((bDeskStation+2)%4,MDM_GM_GAME_NOTIFY,ASS_STOP_THING,0);
	return true;
}

/**
 * 构造函数
 */
CServerGameDesk::CServerGameDesk(void):CGameDesk(FULL_BEGIN)
{
	m_bQueryQuit=false;
	m_iEnableWatch=0;
	m_iLeaveArgee=0;
	m_iLessCount=45;
	m_iTimerCount = 0 ; 
	m_iBeenPlayGame=0;
	m_bGameStation=GS_WAIT_ARGEE;
	::memset(&m_PunishPoint,0,sizeof(m_PunishPoint));
}

/**
 * 析构函数
 */
CServerGameDesk::~CServerGameDesk(void)
{
}

/**
 * 重置游戏状态
 */
bool CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	KillTimer(TIME_GAME_FINISH);
	if ((bLastStation==GFF_FORCE_FINISH)||(bLastStation==GF_SALE))
	{
		m_iBeenPlayGame=0;
		::memset(m_PunishPoint,0,sizeof(m_PunishPoint));
	}
	m_bQueryQuit=false;
	m_iLeaveArgee=0;
	m_Logic.Init ();

	return TRUE;
}

/**
 * 判断是否正在游戏
 */
bool CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	if(m_bGameStation>GS_WAIT_ARGEE&&m_bGameStation<GS_WAIT_NEXT)
		return true;
	else
		return false;
	return __super::IsPlayGame(bDeskStation);
}

/**
 * 用户离开游戏桌
 */
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	if(m_bGameStation>GS_WAIT_ARGEE &&m_bGameStation<GS_WAIT_NEXT)
		GameFinish(bDeskStation,GF_SALE);
	if(GS_WAIT_ARGEE==m_bGameStation)
	{//清理布局
		m_Logic.UserLeft(bDeskStation);
	}
	return __super::UserLeftDesk(bDeskStation,pUserInfo);
}

/**
 * 用户设置游戏
 */
BOOL CServerGameDesk::UserSetGame(UserArgeeGame * pGameSet)
{
	//效验数据
	if (m_bGameStation!=GS_WAIT_SETGAME) return FALSE;

	//效验数据
	if (((pGameSet->iPlayCount<=0)||(pGameSet->iPlayCount>99)))
		return FALSE;

	//设置数据
	m_iLessCount=pGameSet->iPlayCount;
//	m_iPlayCardCount=1;//(pGameSet->iCardCount&1)?1:2;//2:3;
	m_iBeenPlayGame=0;
	m_bGameStation=GS_WAIT_ARGEE;

	//发送消息
	UserArgeeGame Agree;
	Agree.iPlayCount=m_iLessCount;
//	Agree.iCardCount=m_iPlayCardCount;
	for (int i=0;i<4;i++) SendGameData(i,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);
	SendWatchData(m_bMaxPeople,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);

	return TRUE;
}

/**
 * 用户请求离开
 * @param bDeskStation 请求玩家ID
 * @param szMessage 请求消息内容
 */
BOOL CServerGameDesk::H041_UserHaveThing(BYTE bDeskStation, char * szMessage)
{
	if (m_bGameStation<GS_BUZHEN) return TRUE;
	m_bdesk=bDeskStation;
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

/**
 * 同意用户离开
 * @param bDeskStation 玩家ID
 * @param bArgee 是否同意
 */
BOOL CServerGameDesk::H044_ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee)
{
	if (bArgee) m_iLeaveArgee|=1<<bDeskStation;
	else //m_iLeaveArgee&=~1<<bDeskStation;
	{
		m_iLeaveArgee = 0;
	}
	if (m_iLeaveArgee!=15)
	{
		m_bQueryQuit=true;
		LeaveResultStruct Leave;
		Leave.bDeskStation=bDeskStation;
		Leave.bArgeeLeave=bArgee;
		for (int i=0;i<m_bMaxPeople;i++) 
			if (i!=bDeskStation) SendGameData(i,&Leave,sizeof(Leave),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}
	else GameFinish(m_bdesk,GF_SALE);

	return TRUE;
}