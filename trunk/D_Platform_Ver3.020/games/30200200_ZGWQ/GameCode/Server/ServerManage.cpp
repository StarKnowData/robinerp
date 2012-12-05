#include "StdAfx.h"
#include "ServerManage.h"


//构造函数
CServerGameDesk::CServerGameDesk(void):CGameDesk(FULL_BEGIN)
{
	for (int i=0;i<PLAY_COUNT;i++)
	{
		m_bUserNetCut[i]=false;
	}
	m_bAgreeDianmuFinish=-1;
	m_iJuTimeMinute = 10;
	m_iJuTimeSecond = 30;
	m_iBuTimeMinute = 1;
	m_iBuTimeSecond = 30;
	m_iDuMiaoMinute = 1;
	m_iDuMiaoSecond = 30;
	m_Endi=m_Endj=-1;
//	m_bQueryQuit=false;
	m_iEnableWatch=0;
	m_iLeaveArgee=0;
//	m_iNtCardCount=0;
	m_iLessCount=0;
	m_iPlayCardCount=0;
	m_iBeginStation=0;
	m_iEndStation=0;
//	m_iBaseOutCount=0;
//	m_iNtPeople=-1;
//	m_iFirstOutPeople=-1;
	m_iOutCardPeople=-1;
	m_iUpGradePeople=-1;
	m_iBeenPlayGame=0;
//	m_iGamePoint=0;
	m_bGameStation=GS_WAIT_SETGAME;
//	m_CardCount=PLAY_TWO_CARD;
	//::memset(&m_PunishPoint,0,sizeof(m_PunishPoint));
	::memset(m_iPlayNTNum,0,sizeof(m_iPlayNTNum));
}

//析构函数
CServerGameDesk::~CServerGameDesk(void)
{
}

//定时器消息
bool CServerGameDesk::OnTimer(UINT uTimerID)
{
	if (uTimerID==TIME_GAME_FINISH)	//结束定时器
	{
		KillTimer(TIME_GAME_FINISH);

		if (m_bGameStation==GS_PLAY_GAME) 
			GameFinish(0,GF_NORMAL);
	}

	return __super::OnTimer(uTimerID);
}

//获取游戏状态信息
bool CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{
	switch (m_bGameStation)
	{
	case GS_WAIT_SETGAME:		//游戏没有开始状态
		{
			GameStation_1 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;				//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;				//低版本
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();		//桌子倍数
			GameStation.iRoomBasePoint = GetRoomBasePoint();		//房间倍数
			GameStation.iRunPublish = GetRunPublish();				//逃跑扣分
			GameStation.iRunPublishMoney = GetRunPublishMoney();	//逃跑金币
			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	case GS_WAIT_ARGEE:			//等待玩家开始状态
		{
			GameStation_2 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;				//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;				//低版本
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();		//桌子倍数
			GameStation.iRoomBasePoint = GetRoomBasePoint();		//房间倍数
			GameStation.iRunPublish = GetRunPublish();				//逃跑扣分
			GameStation.iRunPublishMoney = GetRunPublishMoney();	//逃跑金币

			GameStation.iJuTimeMinute = m_iJuTimeMinute;
			GameStation.iJuTimeSecond = m_iJuTimeSecond;
			GameStation.iBuTimeMinute = m_iBuTimeMinute;
			GameStation.iBuTimeSecond = m_iBuTimeSecond;
			GameStation.iDuMiaoMinute = m_iDuMiaoMinute;
			GameStation.iDuMiaoSecond = m_iDuMiaoSecond;

			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	case GS_PLAY_GAME:	//游戏中状态
		{
			GameStation_4 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;				//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;				//低版本
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();		//桌子倍数
			GameStation.iRoomBasePoint = GetRoomBasePoint();		//房间倍数
			GameStation.iRunPublish = GetRunPublish();				//逃跑扣分
			GameStation.iRunPublishMoney = GetRunPublishMoney();	//逃跑金币

			GameStation.iJuTimeMinute = m_iJuTimeMinute;
			GameStation.iJuTimeSecond = m_iJuTimeSecond;
			GameStation.iBuTimeMinute = m_iBuTimeMinute;
			GameStation.iBuTimeSecond = m_iBuTimeSecond;
			GameStation.iDuMiaoMinute = m_iDuMiaoMinute;
			GameStation.iDuMiaoSecond = m_iDuMiaoSecond;
			GameStation.iEndI=m_Endi;
			GameStation.iEndJ=m_Endj;
			GameStation.m_iLastDeskStation = m_iLastDeskStation;
//			GameStation.iFirstOutPeople = m_iFirstOutPeople;
			GameStation.iOutCardPeople=m_iOutCardPeople;
			GameStation.isHitAgreedianmu=m_bAgreeDianmuFinish;
			GameStation.m_stUsedTimeInfo=m_stUsedTimeInfo;

			memcpy(GameStation.bIsInHuiquStation, m_bIsInHuiquStation, sizeof(m_bIsInHuiquStation));
			memcpy(GameStation.bChessingInHuiQi, m_bChessingInHuiQi, sizeof(m_bChessingInHuiQi));

			//发送数据
			::CopyMemory(GameStation.iTiZiNum,m_iTiZiNum,sizeof(m_iTiZiNum));
			::CopyMemory(GameStation.iQiZiNum,m_iQiZiNum,sizeof(m_iQiZiNum));

			::CopyMemory(GameStation.iQiZi,m_iBoard,sizeof(m_iBoard));
			int iSendSize=sizeof(GameStation);
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,iSendSize);

			return TRUE;	
		}
	case GS_WAIT_NEXT:		//等待下一盘游戏开始
		{
			GameStation_5 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;				//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;				//低版本
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();		//桌子倍数
			GameStation.iRoomBasePoint = GetRoomBasePoint();		//房间倍数
			GameStation.iRunPublish = GetRunPublish();				//逃跑扣分
			GameStation.iRunPublishMoney = GetRunPublishMoney();	//逃跑金币

			GameStation.iPlayCount=m_iLessCount;
			GameStation.iCardCount=m_iPlayCardCount;
			GameStation.iBeginStation=m_iBeginStation;
			GameStation.iEndStation=m_iEndStation;
			GameStation.iWinPoint=0;//m_iPlayNTNum[bDeskStation%2]-m_iBeginStation;			
			GameStation.iPunishPoint=0;//m_PunishPoint[bDeskStation];			
			GameStation.iUpGradePeople=m_iUpGradePeople;		
			GameStation.iPlayNTNum[0]=m_iPlayNTNum[0];		
			GameStation.iPlayNTNum[1]=m_iPlayNTNum[1];		
			GameStation.iBeenPlayGame=m_iBeenPlayGame;		

			//发送数据
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	}
	return false;
}

//游戏数据包处理函数
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	switch (pNetHead->bAssistantID)
	{
	case ASS_SYNC_TIME:
		{
			SyncTimeStruct *pMes = (SyncTimeStruct *)pData;
			m_stUsedTimeInfo.m_iJuUseTime[bDeskStation] = pMes->iBotJuUseTime;
			m_stUsedTimeInfo.m_iBuUseTime[bDeskStation] = pMes->iBotBuUseTime;
			m_stUsedTimeInfo.m_iDuUseTime[bDeskStation] = pMes->iBotDuUseTime;
		}
		return true;
	case ASS_GM_AGREE_GAME:		//用户同意游戏
		{
			if (bWatchUser)
				return FALSE;

			if (m_bGameStation == GS_WAIT_SETGAME)	//第一个坐下玩家设置
			{
				if (uSize!=sizeof(UserArgeeGame))
					return FALSE;
				UserArgeeGame * pGameSet=(UserArgeeGame *)pData;
				if (!UserSetGame(pGameSet,bDeskStation))
					return FALSE;
				__super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
				return TRUE;
			}
			//其他玩家
			if ((m_bGameStation != GS_WAIT_ARGEE)&&(m_bGameStation != GS_WAIT_NEXT)) 
				return TRUE;
			return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
		}
	case ASS_OUT_CARD:		//用户出牌
		{
			if(bWatchUser)
				return false;
			if(m_bGameStation == GS_WAIT_NEXT 
				|| m_bGameStation == GS_WAIT_ARGEE 
				|| m_bGameStation == GS_WAIT_SETGAME)
				return true;
			if (uSize != sizeof(PlayChessMsg))
				return false;
			PlayChessMsg * pPlayChessInfo =(PlayChessMsg *)pData;

			UserOutCard(bDeskStation,pPlayChessInfo->iChessArray,pPlayChessInfo->iPlayFlag,pPlayChessInfo->iEndI,pPlayChessInfo->iEndJ);
			return true;
		}

	case ASS_REN_SHU://认输
		{
			if (bWatchUser)
				return false;
			if(m_bGameStation == GS_WAIT_NEXT 
				|| m_bGameStation == GS_WAIT_ARGEE 
				|| m_bGameStation == GS_WAIT_SETGAME)
				return true;
			if (uSize != sizeof(LoserStruct))
				return false;
			LoserStruct * pLoser = (LoserStruct*)pData;
			m_iWinFlag = (pLoser->bDeskStation + 1) % PLAY_COUNT;
			GameFinish(bDeskStation,GF_LOSER);
			return true;			
		}
	case ASS_SUPER_TIMER://超时当成认输
		{
			if (bWatchUser)
				return false;
			if(m_bGameStation == GS_WAIT_NEXT 
				|| m_bGameStation == GS_WAIT_ARGEE 
				|| m_bGameStation == GS_WAIT_SETGAME)
				return true;
			if (uSize != sizeof(SuperTimerStruct))
				return false;
			SuperTimerStruct * pSuper = (SuperTimerStruct*)pData;
			m_iWinFlag = (pSuper->bDeskStation + 1) % PLAY_COUNT;
			GameFinish(bDeskStation,GF_SUPER_TIMER);
			return true;
		}
	case ASS_HUI_QI://悔棋
		{
			SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_HUI_QI,0);
			m_bIsInHuiquStation[bDeskStation] = true;
			return true;
		}
	case ASS_AGREE_HUI_QI://悔棋
		{
			int iflag = (int)pNetHead->bHandleCode;
			m_bIsInHuiquStation[(bDeskStation+1)%2] = false;
			m_bChessingInHuiQi[(bDeskStation+1)%2] = true;

			if (iflag == 0)	//不同意悔棋
			{
				SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,iflag);
				return true;
			}

			RegretChessMsg regretInfo;

			m_iOutCardPeople = m_iLastDeskStation;
			regretInfo.iLastDeskStation = m_iLastDeskStation;
			::CopyMemory(regretInfo.iLastTiZiNum,m_iLastTiZiNum,sizeof(m_iLastTiZiNum));
			::CopyMemory(regretInfo.iLastChessArray,m_iLastBoard,sizeof(m_iLastBoard));

			for (int i = 0;i < 2;i++)
				SendGameData(i,&regretInfo,sizeof(regretInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,1);

			SendWatchData(m_bMaxPeople,&regretInfo,sizeof(regretInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,1);

			::CopyMemory(m_iBoard,m_iLastBoard,sizeof(m_iLastBoard));
			::CopyMemory(m_iTiZiNum,m_iLastTiZiNum,sizeof(m_iLastTiZiNum));

			return true;
		}


	case ASS_DIAN_MU://点目
		{   
			m_bAgreeDianmuFinish=1;//需要点击点目
			CString CST;
			CST.Format("wyshdebug m_iOutCardPeople===%d,m_iLastDeskStation===%d",m_iOutCardPeople,m_iLastDeskStation);
			OutputDebugString(CST);
			SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU,0);

			return true;
		}

	case ASS_AGREE_DIAN_MU://同意点目
		{
			if (uSize != sizeof(DianMuResultStruct)) return false;
			DianMuResultStruct *dianMuResult = (DianMuResultStruct *) pData;

			m_bAgreeDianmuFinish=0;
			CString CST;
			CST.Format("wyshdebug 当前同意点目的人%d，应该下子的人%d",bDeskStation,(bDeskStation+1)%2);
			OutputDebugString(CST);
		      
			if (dianMuResult->bAgree&&m_bUserNetCut[(bDeskStation+1)%2]==false)
			{	
				DianMuResultStruct dianMuInfo;
				dianMuInfo.bAgree = true;
				for (int i = 0;i < 2;i++)
					SendGameData(i,&dianMuInfo,sizeof(dianMuInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_DIAN_MU,0);
				SendWatchData(m_bMaxPeople,&dianMuInfo,sizeof(dianMuInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_DIAN_MU,0);
			}
			else
			{
				DianMuResultStruct dianMuInfo;
				dianMuInfo.bAgree = false;
				SendGameData((bDeskStation+1)%2,&dianMuInfo,sizeof(dianMuInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_DIAN_MU,0);
			}
			return true;
		}

	case ASS_NUMBER_ZI://强制数子
		{
			struct DianMu *p=(struct DianMu *)pData;
			if(m_iFinishNumCnt==0)
				::memcpy(m_idianmu,m_iBoard,sizeof(m_iBoard));
			for(int i=1;i<20;i++)
			{
				for(int j=1;j<20;j++)
				{
					if((p->qi[i][j])==3)
						m_idianmu[i][j]=0;
				}
			}
			m_iFinishNumCnt++;
			if (m_iFinishNumCnt == 2)
			{
				m_iFinishNumCnt=0;
				int j;
				ForceNumberZi(j,m_dianmumsg);
				if (j == -1) 
						m_bQiuHe = true;
					else 
						m_iWinFlag = j;

				FinishDianMu finishdm;
				lstrcpy(finishdm.msg,(LPTSTR)(LPCTSTR) m_dianmumsg);
				::memcpy(finishdm.qi,m_idianmu,sizeof(m_idianmu));
				for (int i = 0; i < 2;i++) SendGameData(i,&finishdm,sizeof(finishdm),MDM_GM_GAME_NOTIFY,ASS_NUMBER_ZI,0);
				SendWatchData(m_bMaxPeople,&finishdm,sizeof(finishdm),MDM_GM_GAME_NOTIFY,ASS_NUMBER_ZI,0);
			}
			return true;
		}

	case ASS_DIAN_MU_RESULT://对点目结果处理（同意，继续点目，继续走棋）
		{
			m_bAgreeDianmuFinish=-1;  //同意点目已经结束
			int flag = (int) pNetHead->bHandleCode;
			if (flag == 1)//同意点目结果
			{
				m_iDianMuResult++;

				if (m_iDianMuResult == 2)//都同意结果
				{
				//	int i;
				//	CString s;
				//	ForceNumberZi(i,s);
					MessageStruct mess;
					lstrcpy(mess.Message,(LPTSTR)(LPCTSTR) m_dianmumsg);
					for (int j = 0; j < PLAY_COUNT;j++) 
						SendGameData(j,&mess,sizeof(mess),MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
					SendWatchData(m_bMaxPeople,&mess,sizeof(mess),MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);

				//	if (i == -1) 
				//		m_bQiuHe = true;
				//	else 
				//		m_iWinFlag = i;
					GameFinish(0,GF_NORMAL);
				}
				//AfxMessageBox("同意点目结果");
			}
			else if (flag == 2)//继续点目
			{
				m_iFinishNumCnt = 0;
				m_iDianMuResult = 0;

				for (int i = 0; i < 2;i++) SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
				SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
				//AfxMessageBox("继续点目");
			}
			else if (flag == 3)//继续走棋
			{
				m_iFinishNumCnt = 0;
				m_iDianMuResult = 0;

				for (int i = 0; i < PLAY_COUNT;i++) 
					SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
				SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
				//AfxMessageBox("继续走棋");
			}

			return true;
		}
	case ASS_HAVE_THING:	//有事请求离开
		{
			if(bWatchUser)
				return false;
			HaveThingStruct * pThing =( HaveThingStruct *)pData;
			 UserHaveThing(bDeskStation,pThing->szMessage);
			return true;
		}
	case ASS_LEFT_RESULT: //同意用户离开
		{
			if(bWatchUser)
				return false;
			LeaveResultStruct * pLeave=(LeaveResultStruct *)pData;
			ArgeeUserLeft(bDeskStation,pLeave->bArgeeLeave);
			return true;
		}
	case ASS_STOP_THING:
		{
			if(bWatchUser)
				return false;
			SendGameData((bDeskStation + 1) % PLAY_COUNT,MDM_GM_GAME_NOTIFY,ASS_STOP_THING,0);
			return true;
		}
	case ASS_GET_GAME_USED_TIME:
		{
			m_stUsedTimeInfo=*((UsedTimeInfo*)pData);
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
				SendGameData((bDeskStation+1)%2,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);

				MessageStruct Mess;

				memset(&Mess,0,sizeof(Mess));
				lstrcpy(Mess.Message,"您的对家提议提前结束本局！");
				SendWatchData(m_bMaxPeople,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);
				//结束游戏
				if (m_bGameStation==GS_PLAY_GAME) 
				{
					m_bQiuHe = true;
					GameFinish(0,GF_NORMAL);
				}
			}
			else
			{
				StopResultStruct stop;
				stop.bArgee=false;
				SendGameData((bDeskStation+1)%2,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);
			}
			return true;
		}
	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}

//清理计时器
void CServerGameDesk::KillAllTimer()
{
	KillTimer(TIME_SEND_CARD);
	KillTimer(TIME_WAIT_NT);
	KillTimer(TIME_GAME_FINISH);
}
//玩家断线处理
bool CServerGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	CString CST;
	CST.Format("wyshdebug UserNetCut bDeskStation===%d",bDeskStation);
    OutputDebugString(CST);

	m_bUserNetCut[bDeskStation]=true;

	return __super::UserNetCut(bDeskStation,  pLostUserInfo);
}
//用户重新进入游戏
bool CServerGameDesk::UserReCome(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(i==bDeskStation)
			continue;
		SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_GET_GAME_USED_TIME,0);
	}
	m_bUserNetCut[bDeskStation]=false;

	return __super::UserReCome(bDeskStation,pLostUserInfo);

}
//重置游戏状态
bool CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	KillAllTimer();

	m_Endi = m_Endj = -1;
	if ((bLastStation == GFF_FORCE_FINISH)||(bLastStation == GF_SALE))
	{
		m_iLessCount = 0;
		m_iPlayCardCount = 0;
		m_iBeginStation = 0;
		m_iEndStation = 0;
		m_iBeenPlayGame = 0;
		m_iUpGradePeople = -1;
		::memset(m_iPlayNTNum,0,sizeof(m_iPlayNTNum));
	}

//	m_bQueryQuit=false;
	m_iLeaveArgee = 0;
//	m_iGamePoint = 0;
//	m_iBaseOutCount = 0;
//	m_iFirstOutPeople = -1;
	m_iOutCardPeople = -1;
//	m_iNtPeople = -1;
//	m_iNtCardCount = 0;
//	m_iSendCardPos = 0;
	return TRUE;
}
//用户设置游戏
BOOL CServerGameDesk::UserSetGame(UserArgeeGame * pGameSet,BYTE desk)
{
	//效验数据
	if (m_bGameStation != GS_WAIT_SETGAME)
		return FALSE;

	m_bFirstRed = true;
	m_iBeenPlayGame = 0;
	m_bGameStation = GS_WAIT_ARGEE;

	m_iJuTimeMinute = pGameSet->iJuTimeMinute;
	m_iJuTimeSecond = pGameSet->iJuTimeSecond;
	m_iBuTimeMinute = pGameSet->iBuTimeMinute;
	m_iBuTimeSecond = pGameSet->iBuTimeSecond;
	m_iDuMiaoMinute = pGameSet->iDuMiaoMinute;
	m_iDuMiaoSecond = pGameSet->iDuMiaoSecond;

	//发送消息
	UserArgeeGame Agree;
	Agree.iJuTimeMinute = pGameSet->iJuTimeMinute;
	Agree.iJuTimeSecond = pGameSet->iJuTimeSecond;
	Agree.iBuTimeMinute = pGameSet->iBuTimeMinute;
	Agree.iBuTimeSecond = pGameSet->iBuTimeSecond;
	Agree.iDuMiaoMinute = pGameSet->iDuMiaoMinute;
	Agree.iDuMiaoSecond = pGameSet->iDuMiaoSecond;
	for (int i = 0; i < PLAY_COUNT; i ++)
		if(i != desk)//还有另外玩家在坐
			SendGameData(i,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);
	SendWatchData(m_bMaxPeople,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);

	return TRUE;
}
//游戏开始
bool CServerGameDesk::GameBegin(BYTE bBeginFlag)
{
	if (__super::GameBegin(bBeginFlag)==false) 
		return false;

	memset(m_bIsInHuiquStation, false, sizeof(m_bIsInHuiquStation));
	memset(m_bChessingInHuiQi, false, sizeof(m_bChessingInHuiQi));
	
	for (int i=0;i<PLAY_COUNT;i++)
	{
		m_bUserNetCut[i]=false;
	}
	//设置状态
	m_bQiuHe = false;
//	m_bQueryQuit = false;
//	m_iNtPeople = -1;
//	m_iNtCardCount = 0;
//	m_iSendCardPos = 0;
	m_bAgreeDianmuFinish=-1; //同意点目完成标示
	m_iBeenPlayGame ++;

	m_iFinishNumCnt = 0;
	m_iDianMuResult = 0;
	//清盘
	for (int i = 0; i < WQ_MAX_I; i ++)
		for (int j = 0;j < WQ_MAX_J;j++)
		{
			if (i == 0 || j == 0 || i == WQ_MAX_I - 1 || j == WQ_MAX_J - 1)
			{
				m_iBoard[i][j] = WQ_FLAG_SIDE;
				continue;
			}
			else 
				m_iBoard[i][j] = WQ_FLAG_NONE;

		}

		::memset(m_iQiZiNum,0,sizeof(m_iQiZiNum));
		::memset(m_iQiZiLastNum,0,sizeof(m_iQiZiLastNum));
		::memset(m_iTiZiNum,0,sizeof(m_iTiZiNum));

		::memset(m_iLastBoard,0,sizeof(m_iLastBoard));
		::memset(m_iLastTiZiNum,0,sizeof(m_iLastTiZiNum));
	
		BeginPlay();
		return TRUE;
}

//游戏开始
BOOL CServerGameDesk::BeginPlay()
{
	//设置数据
	//黑子先下
/*	if(m_iUpGradePeople == -1)
		m_iUpGradePeople = rand() % PLAY_COUNT;
	else
		m_iUpGradePeople = (m_iUpGradePeople + 1) % PLAY_COUNT;//交换先后手
*/	
	if(-1 == m_iUpGradePeople)
		m_iUpGradePeople= WQ_PLAY_FLAG_BLACK;
	else
	{
		if(m_iUpGradePeople == WQ_PLAY_FLAG_BLACK)		//轮流先后手
			m_iUpGradePeople = WQ_PLAY_FLAG_WHITE;
		else if(m_iUpGradePeople == WQ_PLAY_FLAG_WHITE)
			m_iUpGradePeople = WQ_PLAY_FLAG_BLACK;
	}
	
	m_Qiflag[m_iUpGradePeople] = WQ_PLAY_FLAG_BLACK;
	m_Qiflag[(m_iUpGradePeople + 1) % PLAY_COUNT] = WQ_PLAY_FLAG_WHITE;
	m_bGameStation = GS_PLAY_GAME;
    //设置谁先手，若不设，客户端会出现信息框中的用户名为空BUG
	m_iOutCardPeople = m_iUpGradePeople;
	//先手消息
	PrepareStruct stPrepare;
	stPrepare.bDeskStation = m_iOutCardPeople;

	for (int i = 0; i < m_bMaxPeople; i ++) 
	{
		SendGameData(i,&stPrepare,sizeof(stPrepare),MDM_GM_GAME_NOTIFY,ASS_GAME_PREPARE,0);
	}
	SendWatchData(m_bMaxPeople,&stPrepare,sizeof(stPrepare),MDM_GM_GAME_NOTIFY,ASS_GAME_PREPARE,0);


	m_iOutCardPeople = m_iUpGradePeople;
	//发送游戏开始消息
	BeginPlayStruct Begin;
	Begin.bDeskStation = m_iOutCardPeople;
	for (int i = 0; i < m_bMaxPeople; i ++) 
	{
		SendGameData(i,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);
	}
	SendWatchData(m_bMaxPeople,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);

	GameReady();

	return TRUE;
}

//用户出牌
BOOL CServerGameDesk::UserOutCard(BYTE bDeskStation, int iPlayQi[][21], int iPlayFlag, int iEndI, int iEndJ)
{
	if (bDeskStation != m_iOutCardPeople)
		return FALSE;

	m_bChessingInHuiQi[bDeskStation] = false;
	//保存当前棋局
	m_iLastDeskStation = bDeskStation;
	::CopyMemory(m_iLastBoard,m_iBoard,sizeof(m_iBoard));
	::CopyMemory(m_iLastTiZiNum,m_iTiZiNum,sizeof(m_iTiZiNum));
	m_Endi = iEndI;
	m_Endj = iEndJ;
	m_iLastDeskStation = bDeskStation;

	::CopyMemory(m_iBoard,iPlayQi,sizeof(m_iBoard));

	::memset(m_iQiZiNum,0,sizeof(m_iQiZiNum));

	//统计所下棋子
	for (int i = 1; i < WQ_MAX_I - 1; i ++)
		for (int j = 1; j < WQ_MAX_J - 1; j ++)
		{
			if (m_iBoard[i][j] == WQ_FLAG_BLACK || m_iBoard[i][j] == WQ_FLAG_CUR_BLACK)
			{
				m_iQiZiNum[WQ_PLAY_FLAG_BLACK] ++;
				continue;
			}
			if (m_iBoard[i][j] == WQ_FLAG_WHITE || m_iBoard[i][j] == WQ_FLAG_CUR_WHITE)
			{
				m_iQiZiNum[WQ_PLAY_FLAG_WHITE]++;
				continue;
			}
		}

		//统计提子数
		PlayChessMsg playChessInfo;
		::memset(&playChessInfo,0,sizeof(playChessInfo));
		playChessInfo.bDeskStation = bDeskStation;

		///::memset(m_iTiZiNum,0,sizeof(m_iTiZiNum));
		int iCnt;
		if (m_Qiflag[bDeskStation] == WQ_PLAY_FLAG_BLACK)//黑方下子统计所提白方的子
		{
			iCnt = m_iQiZiLastNum[WQ_PLAY_FLAG_WHITE] - m_iQiZiNum[WQ_PLAY_FLAG_WHITE];
			if (iCnt < 0) iCnt = 0;
			m_iTiZiNum[WQ_PLAY_FLAG_BLACK] += iCnt;
			playChessInfo.iTiZiNum[WQ_PLAY_FLAG_BLACK] = m_iTiZiNum[WQ_PLAY_FLAG_BLACK];
			playChessInfo.iTiZiNum[WQ_PLAY_FLAG_WHITE] = m_iTiZiNum[WQ_PLAY_FLAG_WHITE];
		}
		else if (m_Qiflag[bDeskStation] == WQ_PLAY_FLAG_WHITE)//白方下子统计所提黑方的子
		{
			iCnt = m_iQiZiLastNum[WQ_PLAY_FLAG_BLACK] - m_iQiZiNum[WQ_PLAY_FLAG_BLACK];
			if (iCnt < 0) iCnt = 0;
			m_iTiZiNum[WQ_PLAY_FLAG_WHITE] += iCnt;
			playChessInfo.iTiZiNum[WQ_PLAY_FLAG_WHITE] = m_iTiZiNum[WQ_PLAY_FLAG_WHITE];
			playChessInfo.iTiZiNum[WQ_PLAY_FLAG_BLACK] = m_iTiZiNum[WQ_PLAY_FLAG_BLACK];
		}
		playChessInfo.iEndI = iEndI;
		playChessInfo.iEndJ = iEndJ;
		//playChessInfo.iNextPlayStation = m_iOutCardPeople;
		playChessInfo.iPlayFlag = bDeskStation;
		::CopyMemory(playChessInfo.iQiZiNum,m_iQiZiNum,sizeof(m_iQiZiNum));
		::CopyMemory(playChessInfo.iChessArray,iPlayQi,sizeof(playChessInfo.iChessArray));

		for(int i = 0; i < PLAY_COUNT; i ++) 
			SendGameData(i,&playChessInfo,sizeof(playChessInfo),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD_RESULT,0);

		SendWatchData(m_bMaxPeople,&playChessInfo,sizeof(playChessInfo),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD_RESULT,0);
		//int iNextPlayFlag = iPlayFlag;
		::CopyMemory(m_iQiZiLastNum,m_iQiZiNum,sizeof(m_iQiZiNum));

		///下一走棋者
		m_iOutCardPeople = (bDeskStation + 1) % PLAY_COUNT;

		PlayChessStruct play;
		play.bDeskStation = m_iOutCardPeople;
		for(int i = 0; i < PLAY_COUNT; i ++)
		{
			SendGameData(i,&play,sizeof(play),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);
			SendWatchData(m_bMaxPeople,&play,sizeof(play),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);
		}
		return TRUE;
}

//游戏结束
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	// 平台断线与步时可能会冲突导致结束两次, 因此这里判断
	if (m_bGameStation != GS_PLAY_GAME)
		return true;

	//编写代码
	switch (bCloseFlag)
	{
	case GF_LOSER://认输
		{
			//继续下一盘
			m_bGameStation = GS_WAIT_ARGEE;
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			GameEndStruct loser;
			::memset(&loser,0,sizeof(loser));
			loser.bDeskStation = bDeskStation;

			strcpy(loser.szNickName[bDeskStation],m_pUserInfo[bDeskStation]->m_UserData.nickName);
			strcpy(loser.szNickName[(bDeskStation+1)%2],m_pUserInfo[(bDeskStation+1)%2]->m_UserData.nickName);
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if(i == bDeskStation)
					 loser.iTurePoint[i] = - BASE_SCORE;
					else
					 loser.iTurePoint[i] = BASE_SCORE;
			}
			//写入数据库				
			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			ChangeUserPointint64(loser.iTurePoint, temp_cut);
			__super::RecoderGameInfo(loser.iChangeMoney);
			loser.iDoublePointEffect = GetDoublePointEffect();//20081125

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0;//金币场不扣积分add by xqm 2010-12-14
			if (true == bNotCostPoint)
			{
				memset(loser.iTurePoint,0,sizeof(loser.iTurePoint));
			}
			//发送数据
			for (int i = 0; i < m_bMaxPeople; i ++)
				SendGameData(i, &loser, sizeof(loser), MDM_GM_GAME_NOTIFY, ASS_LOSER_END, 0);
			SendWatchData(m_bMaxPeople, &loser, sizeof(loser), MDM_GM_GAME_NOTIFY, ASS_LOSER_END, 0);
			__super::GameFinish(bDeskStation,GF_SALE);
			ReSetGameState(bCloseFlag); 
			return true;
		}
	case GF_SUPER_TIMER://超时结束
		{
			//继续下一盘
			m_bGameStation = GS_WAIT_ARGEE;
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			GameEndStruct supertimer;
			::memset(&supertimer,0,sizeof(supertimer));
			supertimer.bDeskStation = bDeskStation;
			strcpy(supertimer.szNickName[bDeskStation],m_pUserInfo[bDeskStation]->m_UserData.nickName);
			strcpy(supertimer.szNickName[(bDeskStation+1)%2],m_pUserInfo[(bDeskStation+1)%2]->m_UserData.nickName);

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if(i == bDeskStation)
					 supertimer.iTurePoint[i] = -BASE_SCORE;
					else
					 supertimer.iTurePoint[i] = BASE_SCORE;
			}
			//写入数据库				
			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			ChangeUserPointint64(supertimer.iTurePoint, temp_cut);
			__super::RecoderGameInfo(supertimer.iChangeMoney);
			supertimer.iDoublePointEffect = GetDoublePointEffect();//20081125

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0;//金币场不扣积分add by xqm 2010-12-14
			if (true == bNotCostPoint)
			{
				memset(supertimer.iTurePoint,0,sizeof(supertimer.iTurePoint));
			}
			//发送数据
			for (int i = 0; i < m_bMaxPeople; i ++)
				SendGameData(i,&supertimer,sizeof(supertimer),MDM_GM_GAME_NOTIFY,ASS_SUPER_TIMER_END,0);
			SendWatchData(m_bMaxPeople,&supertimer,sizeof(supertimer),MDM_GM_GAME_NOTIFY,ASS_SUPER_TIMER_END,0);
			__super::GameFinish(bDeskStation,GF_SALE);
			ReSetGameState(bCloseFlag);
			return true;
		}
	case GF_NORMAL:		//游戏正常结束
		{
			//继续下一盘
			m_bGameStation = GS_WAIT_NEXT;
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;				
			}
			int iBasePoint = GetRoomBasePoint();
			//游戏结束
		//	GetUpGrade(0,m_iPlayCardCount);
			GameEndStruct GameEnd;
			::memset(&GameEnd,0,sizeof(GameEnd));
			GameEnd.bDeskStation = m_iUpGradePeople; 
			///计算得分
			GetUpGrade(0,m_iPlayCardCount);

			for (int i=0; i<PLAY_COUNT; ++i)
			{
				if (NULL != m_pUserInfo[i])
				{
					sprintf(GameEnd.szNickName[i], "%s", m_pUserInfo[i]->m_UserData.nickName );
				}				
			}
			if(!m_bQiuHe)//add 20081127  ;求和都不扣分,不是求和继续算分
			{
				if (m_iWinFlag == 0)
				{
					//黑方胜
					GameEnd.iTurePoint[m_iBlackStation] = BASE_SCORE;
					GameEnd.iTurePoint[m_iWhiteStation] = - BASE_SCORE;
				}
				else if (m_iWinFlag == 1)
				{
					//白方胜

					GameEnd.iTurePoint[m_iWhiteStation] = BASE_SCORE;
					GameEnd.iTurePoint[m_iBlackStation] = - BASE_SCORE;
				}
				else
				{
					GameEnd.iTurePoint[0] = 0; 
					GameEnd.iTurePoint[1] = 0;
				}
			}
			//写入数据库				
			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			ChangeUserPointint64(GameEnd.iTurePoint, temp_cut);
			__super::RecoderGameInfo(GameEnd.iChangeMoney);
			GameEnd.iDoublePointEffect = GetDoublePointEffect();//20081125

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0;//金币场不扣积分add by xqm 2010-12-14
			if (true == bNotCostPoint)
			{
				memset(GameEnd.iTurePoint,0,sizeof(GameEnd.iTurePoint));
			}
			//发送数据
			for (int i = 0; i < m_bMaxPeople; i ++)
				SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);
			SendWatchData(m_bMaxPeople,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);

			__super::GameFinish(bDeskStation,GF_SALE);
			ReSetGameState(bCloseFlag);
			return true;
		}
	case GF_SALE:			//游戏安全结束
		{
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}	
			int iBasePoint = GetRoomBasePoint();//倍数
			m_bGameStation = GS_WAIT_ARGEE;
			GameEndStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));
			CutEnd.bDeskStation = bDeskStation;
			
			for (int i = 0; i < PLAY_COUNT; i ++) 
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);
				SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);

			bCloseFlag = GFF_FORCE_FINISH;

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GFF_FORCE_FINISH:		//用户断线离开----------(用户强退)
		{
			int iBasePoint = GetRoomBasePoint();//倍数

			m_bGameStation = GS_WAIT_ARGEE;

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}

			GameEndStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));

			CutEnd.bDeskStation = bDeskStation;
			strcpy(CutEnd.szNickName[bDeskStation],m_pUserInfo[bDeskStation]->m_UserData.nickName);
			strcpy(CutEnd.szNickName[(bDeskStation+1)%2],m_pUserInfo[(bDeskStation+1)%2]->m_UserData.nickName);

			CutEnd.iTurePoint[bDeskStation] =  - GetRunPublish();
			CutEnd.iTurePoint[(bDeskStation + 1) % PLAY_COUNT] = GetRunPublish();

			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			
			/*for (int i = 0; i < PLAY_COUNT; i ++)
			{
				temp_cut[i] = (bDeskStation == i && CutEnd.iTurePoint[i] < 0);
			}			
			ChangeUserPoint(CutEnd.iTurePoint, temp_cut);*/

			for (int i=0; i<PLAY_COUNT; ++i) 
			{ 
				temp_cut[i] = (bDeskStation == i)?true:false; 
			}

			ChangeUserPointint64(CutEnd.iTurePoint, temp_cut);//,CutEnd.iChangeMoney,false);
			__super::RecoderGameInfo(CutEnd.iChangeMoney);
			CutEnd.iDoublePointEffect = GetDoublePointEffect();//20081125

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0;//金币场不扣积分add by xqm 2010-12-14
			if (true == bNotCostPoint)
			{
				memset(CutEnd.iTurePoint,0,sizeof(CutEnd.iTurePoint));
			}
			
			for (int i = 0; i < PLAY_COUNT; i ++) 
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);
			bCloseFlag = GFF_FORCE_FINISH;

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

//游戏准备
BOOL CServerGameDesk::GameReady()
{
	/*
	if(-1 == m_iUpGradePeople)
		m_iUpGradePeople= WQ_PLAY_FLAG_BLACK;
	else
	{
		if(m_iUpGradePeople == WQ_PLAY_FLAG_BLACK)		//轮流先后手
			m_iUpGradePeople = WQ_PLAY_FLAG_WHITE;
		else if(m_iUpGradePeople == WQ_PLAY_FLAG_WHITE)
			m_iUpGradePeople = WQ_PLAY_FLAG_BLACK;
	}
*/
	//先手,后手位置
	m_iBlackStation = m_iUpGradePeople;
	m_iWhiteStation =(m_iUpGradePeople+1) % 2;
	GameReadyStruct GameReady;
	::memset(&GameReady,0,sizeof(GameReady));
	GameReady.iBlackStation=m_iBlackStation;
	GameReady.iWhiteStation=m_iWhiteStation;
	for (int i = 0; i < 2;i++) 
		SendGameData(i,&GameReady,sizeof(GameReady),MDM_GM_GAME_NOTIFY,ASS_GAME_READY,0);
	SendWatchData(m_bMaxPeople,&GameReady,sizeof(GameReady),MDM_GM_GAME_NOTIFY,ASS_GAME_READY,0);

	return TRUE;
}

//判断是否正在游戏
bool CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	if(m_bGameStation > GS_WAIT_ARGEE&&m_bGameStation < GS_WAIT_NEXT)
		return true;
	else
		return false;
	//return __super::IsPlayGame(bDeskStation);
}

//用户离开游戏桌
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{	
	//-------------用户点目后，有玩家超时未点开始，重新进来游戏不能正常进行--------------
	/*if(m_pUserInfo[(bDeskStation + 1) % PLAY_COUNT] == NULL)	
		m_bGameStation = GS_WAIT_SETGAME;*/	
	//-------------------点目留下的问题，修改成以下后游戏能够正常进行--------------------
	if(m_pUserInfo[(bDeskStation+1)%2]==NULL)	
		m_bGameStation = GS_WAIT_SETGAME;	
	else
		m_bGameStation = GS_WAIT_ARGEE;

	if(m_bGameStation > GS_WAIT_ARGEE)
		GameFinish(bDeskStation,GF_SALE);

	return __super::UserLeftDesk(bDeskStation,pUserInfo);
}


//计算得分
int	CServerGameDesk::GetUpGrade(int iGamePoint, int iPlayCardCount)
{
	if (m_bQiuHe)
	{	
		m_iTurePoint[0] = 0;
		m_iTurePoint[1] = 0;
		return 0;
	}
	if(m_iWinFlag < 0)
		return 0;
	return 0;
}

//force number qizi
void CServerGameDesk::ForceNumberZi(int &iWinFlag, CString &strMessage)
{
	float totalWhite = 0.00000,
		totalBlack = 0.00000;

	m_Logic.NumQiZi(&totalBlack,&totalWhite,m_idianmu);
	totalBlack -= WQ_BLACK_TIE_MU;
	totalWhite += WQ_BLACK_TIE_MU;

	float blackWinMu = totalBlack - totalWhite;
	int flag = (blackWinMu > 0.00000) ? 1 : ((blackWinMu == 0.00000) ? 0 : -1);
	blackWinMu = (flag > 0) ? blackWinMu : -blackWinMu;
	int count = (int) (blackWinMu);//整数部分
	int fraction = (int) ((blackWinMu - count) * 100);//小数部分
	int winFlag = 0;
	CString s;

	if (flag > 0)//黑方赢
	{
		winFlag = WQ_PLAY_FLAG_BLACK;
		s = TEXT("黑方赢");
		goto ret;
	}
	else if (flag < 0)//白方赢
	{
		winFlag = WQ_PLAY_FLAG_WHITE;
		s = TEXT("白方赢");
		goto ret;
	}
	else//平局
	{
		winFlag = -1;
		s = TEXT("此局为平局");
	}
ret:if (fraction != 0)
	{
		CString str;
		str.Format("%d",count);
		s += str;
		switch (fraction)
		{
		case 25:
			s += TEXT("又1/4子");
			break;

		case 50:
			s += TEXT("又1/2子");
			break;

		case 75:
			s += TEXT("又3/4子");
			break;
		}
	}
//此处判断玩家输赢时会出错，总是会判同一个人输
//修改 : wushuqun 2008.8.5

//	iWinFlag = m_Qiflag[winFlag];
	iWinFlag = winFlag;
	strMessage = s;
	return;
}


//用户请求离开
BOOL CServerGameDesk::UserHaveThing(BYTE bDeskStation, char * szMessage)
{
	if (m_bGameStation < GS_PLAY_GAME)
		return TRUE;

	m_iHaveThingPeople = bDeskStation;
	m_iLeaveArgee|=1<<bDeskStation;
	if (m_iLeaveArgee != 15)
	{
		HaveThingStruct HaveThing;
		HaveThing.bDeskStation = bDeskStation;
		::CopyMemory(HaveThing.szMessage,szMessage,60*sizeof(char));
		for (int i = 0; i < m_bMaxPeople; i ++)
			if (i != bDeskStation)
				SendGameData(i,&HaveThing,sizeof(HaveThing),MDM_GM_GAME_NOTIFY,ASS_HAVE_THING,0);
	}
	else GameFinish(bDeskStation,GF_SALE);

	return TRUE;
}

//同意用户离开
BOOL CServerGameDesk::ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee)
{
	if (!bArgee)
	{
//		m_bQueryQuit=true;
		LeaveResultStruct Leave;
		Leave.bDeskStation = bDeskStation;
		Leave.bArgeeLeave = bArgee;
		for (int i = 0; i < m_bMaxPeople; i ++) 
			if (i != bDeskStation)
				SendGameData(i,&Leave,sizeof(Leave),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}
	//else
	//	GameFinish((bDeskStation + 1) % PLAY_COUNT,GF_SALE);
	//
	else //JMod-自动离开-20090531
	{
		GameFinish(m_iHaveThingPeople,GF_SALE);
		LeaveResultStruct Leave1;
		Leave1.bDeskStation = m_iHaveThingPeople;
		Leave1.bArgeeLeave = true;
		SendGameData(m_iHaveThingPeople,&Leave1,sizeof(Leave1),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}

	return TRUE;
}


//逃跑扣分
int CServerGameDesk::GetRunPublishMoney()
{
	return m_pDataManage->m_InitData.uRunPublish;
	//return m_pDataManage->m_InitData.uRunPublishMoney;
}

//逃跑扣分
int CServerGameDesk::GetRunPublish()
{
	return m_pDataManage->m_InitData.uRunPublish;
}

//游戲基礎倍數
int CServerGameDesk::GetRoomBasePoint()
{
	int iBasePoint = m_pDataManage->m_InitData.uBasePoint;//倍数
	//	int iBasePoint = m_pDataManage->m_InitData.uScoreRate;//倍数
	return iBasePoint;
}

//桌子倍数
int CServerGameDesk::GetDeskBasePoint()
{
	return 1;
	//	return GetTableBasePoint();
}

