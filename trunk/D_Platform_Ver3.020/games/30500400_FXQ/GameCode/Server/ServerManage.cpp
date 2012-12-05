#include "StdAfx.h"
#include "ServerManage.h"
#include "../../../../sdk/include/Common/writelog.h"
#include <math.h>

//游戏扩展配置
BOOL CServerGameDesk:: m_bTurnRule = TRUE;		//顺时针还是逆时针
BOOL CServerGameDesk:: m_bIskinescope = FALSE;


void DebugPrintf(int uRoomID,const char *p, ...)
{
	//return;	// 发布时不做任何事	By Zxd 20090727
	char szFilename[256];
	CString strPath = CINIFile::GetAppPath() +"\\GameLog\\";

	SHCreateDirectoryEx(NULL, strPath, NULL);

	wsprintf( szFilename, "%s%d_%d_Server.txt",strPath ,  NAME_ID,uRoomID);
	FILE *fp = fopen( szFilename, "a" );
	if (NULL == fp)
	{
		return;
	}
	va_list arg;
	va_start( arg, p );
	vfprintf(fp, p, arg );
	fprintf(fp,"\n");
	fclose(fp);
}
void MsgPrint(const char *lpszFormat, ...)
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

//构造函数
CServerGameDesk::CServerGameDesk(void):CGameDesk(FULL_BEGIN)
{
	m_iTimerCount = 0; 
	m_iGameBasePoint =  1 ; 
	m_iLimitPlayGame = 0; 
	m_iBeenPlayGame = 0 ; 
	m_cbOperater = 255 ;

	m_cbDiceValue = 0 ;

	m_cbWinPlayer = 255 ; 

	m_cbPropDiceValue = 0 ;
	
	m_bFlying = false ;

	m_bUserProp = false ; 

	memset(m_bPlayerReady , 0 , sizeof(m_bPlayerReady)) ; 

	memset(m_bAuto , 0 , sizeof(m_bAuto)) ; 

	memset(m_bUserNetCut , 0 , sizeof(m_bUserNetCut)) ; 

	memset(m_bDiceAniFinish , false , sizeof(m_bDiceAniFinish)) ; 

	memset(m_cbPropDiceCount , 0 , sizeof(m_cbPropDiceCount)) ; 

	memset(&m_ActiveData , 0 ,sizeof(m_ActiveData)) ; 

	m_bGameStation = GS_WAIT_SETGAME;

	LoadStaticIni();
}
//析构函数
CServerGameDesk::~CServerGameDesk(void)
{
	KillTimer(TIME_MY_TIMER);
}
///加载静态变量配置项
BOOL CServerGameDesk::LoadStaticIni()
{
	CString strName;
	CString fileName ; 
	CString s = CINIFile::GetAppPath();/////本地路径
	strName.Format("%d",NAME_ID);	
	fileName.Format("%s%s_s.ini",s,strName) ; 

	CINIFile f( fileName );
	CString key ="game" ; 

	m_bTurnRule      = f.GetKeyVal(key,"TurnRule", 0 );
	m_bIskinescope   = f.GetKeyVal(key, "Kinesscope" , 0) ; 

	return  true  ;
}

//加载局数限制
BOOL CServerGameDesk::LoadExtIni()
{
	CString strName;
	CString fileName ; 
	strName.Format("%d",NAME_ID);

	CString s = CINIFile::GetAppPath();/////本地路径
	fileName.Format("%s%s_s.ini",s,strName) ; 

	CINIFile f( fileName );
	CString key ="game" ; 
	m_iDiceTime  = f.GetKeyVal(key , "DiceTime" , 10) ; 
	m_iBeginTime     = f.GetKeyVal(key,"BeginTime", 10);
	m_iThinkTime     = f.GetKeyVal(key,"ThinkTime", 15);

	m_iGameBasePoint = f.GetKeyVal(key , "GameBasePoint" , 1) ; 

	return TRUE;
}
//根据房间ID加载配置文件
BOOL CServerGameDesk::LoadExtIni(int iRoomID)
{
	CString strName;
	CString fileName ; 
	strName.Format("%d",NAME_ID);
	CString s = CINIFile::GetAppPath();/////本地路径

	fileName.Format("%s%s_s.ini",s,strName) ; 

	CINIFile f( fileName );
	CString key ;
	key.Format("%d_%d",NAME_ID,iRoomID) ; 

	m_iBeginTime     = f.GetKeyVal(key,"BeginTime", m_iBeginTime);
	m_iDiceTime      = f.GetKeyVal(key , "DiceTime" , m_iDiceTime) ;      
	m_iThinkTime     = f.GetKeyVal(key,"ThinkTime", m_iThinkTime);

	m_iGameBasePoint = f.GetKeyVal(key , "GameBasePoint" , m_iGameBasePoint) ; 

	return TRUE;
}
///房间配置文件加载
bool CServerGameDesk::InitDeskGameStation()
{
	LoadExtIni();
	LoadExtIni(m_pDataManage->m_InitData.uRoomID);
	return true;
}
//清所有计时器
void CServerGameDesk::KillAllTimer()
{
	memset(m_arTimer, 0, sizeof(m_arTimer));
}
///游戏开始前初始一些数据
bool CServerGameDesk::IniBeginData()
{
	m_bFlying = false ;  

	m_bUserProp = false ; 

	m_cbDiceValue = 0 ;

	m_cbPropDiceValue = 0 ;

	m_cbWinPlayer = 255 ;  

	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		m_cbPropDiceCount[i] = 1 ;
	}

	m_cbPropDiceValue = 0 ;

	memset(m_bPlayerReady , 0 , sizeof(m_bPlayerReady)) ; 

	memset(m_bUserNetCut , 0 , sizeof(m_bUserNetCut)) ; 

	memset(m_bAuto,0,sizeof(m_bAuto)) ; 

	memset(m_bDiceAniFinish , false , sizeof(m_bDiceAniFinish)) ; 

	memset(&m_ActiveData , 0 ,sizeof(m_ActiveData)) ; 

	m_Logic.InitServerData() ; 

	return true ; 
}

//重置游戏状态
bool CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	KillAllTimer();

	m_bFlying = false ; 

	return true;
}

//游戏开始
bool CServerGameDesk::GameBegin(BYTE bBeginFlag)
{
	if (__super::GameBegin(bBeginFlag)==false) 
	{
		return false;
	}

	IniBeginData() ; 

	SetTimer(TIME_MY_TIMER, MY_ELAPSE);

	//设置数据
	m_bGameStation = GS_PLAY_GAME;

	///随机一个人投色子
	srand( (unsigned)time(NULL) + 3333) ; 
	m_cbOperater = rand()%PLAY_COUNT ;

	BeginUpgradeStruct BeginData  ;
	memset(&BeginData , 0 , sizeof(BeginData)) ;

	BeginData.iBeenPlayGame = m_iBeenPlayGame ; 
	BeginData.iPlayLimit  = m_iLimitPlayGame ;

	for (int i = 0; i < PLAY_COUNT; i ++) 
	{
		SendGameDataSaveFile(i,&BeginData,sizeof(BeginData),MDM_GM_GAME_NOTIFY,ASS_GAME_BEGIN,0);
	}
	SendWatchData(m_bMaxPeople,&BeginData,sizeof(BeginData),MDM_GM_GAME_NOTIFY,ASS_GAME_BEGIN,0);

	SetMyTimer(TIME_APPLY_DICE , m_iDiceTime *1000) ;

	OnNotifyClentApplyDice(m_cbOperater) ; 

	return TRUE;
}

//拦截玩家强退消息f
bool CServerGameDesk::HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if (bDeskStation>=PLAY_COUNT)
	{
		return true;
	}

	bool  bForceQuitAsAuto = true ; 
	
	ASSERT(pNetHead->bMainID==MDM_GM_GAME_FRAME);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_FORCE_QUIT:
		{
			///查找上层路径
			CString szAppPath = CINIFile::GetAppPath();

			CString strBCFFile  ; 
			strBCFFile.Format("%s\\SpecialRule.bcf",szAppPath) ; 

			CBcfFile File(strBCFFile) ;

			if (File.IsFileExist(strBCFFile))
			{
				bForceQuitAsAuto = File.GetKeyVal("ForceQuitAsAuto","30500400" ,1) ; 
			}

			if(bForceQuitAsAuto == true)
			{
				return true ; 
			}

			break;
		}
		break;
	default:
		break;
	}
	return __super::HandleFrameMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}


//游戏数据包处理函数
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if (bDeskStation>=PLAY_COUNT)
	{
		return true;
	}	

	switch (pNetHead->bAssistantID)
	{
	case ASS_SUPER_MSG://超级客户端
		{		
			return true;
		}
	case ASS_GM_AGREE_GAME:		//用户同意游戏
		{
			if (bWatchUser) 
			{
				return true;
			}
			if(m_bGameStation != GS_WAIT_ARGEE)
			{
				m_bGameStation = GS_WAIT_ARGEE;	
			}

			m_bPlayerReady[bDeskStation] = true ; 

			return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
		}	
	case  ASS_APPLY_DICE:
		{
			if(bWatchUser)
			{
				return true ; 
			}

			OnCSNotifyDiceMessage(bDeskStation) ; 
			return true ; 
		}
	case  ASS_NOTIFY_DICE_FINISH:
		{
			if(bWatchUser)
			{
				return true ; 
			}

			if(bDeskStation != m_cbOperater)
			{
				return true ; 
			}

			KillMyTimer(TIME_PLAYER_DICE) ; 

			if(!CheckPlaneCanFly(m_cbOperater))
			{
				m_cbOperater = GetNextDeskStation(m_cbOperater) ; 
				OnNotifyClentApplyDice(m_cbOperater) ; 

				if(m_bUserNetCut[m_cbOperater] == true)
				{
					SetMyTimer(TIME_APPLY_DICE , 1000) ; 
				}
				else
				{
					SetMyTimer(TIME_APPLY_DICE , m_iDiceTime*1000) ; 
				}

			}
			return true ; 
		}
	case ASS_PLAYER_CHOISE_PLANE:
		{
			if(bWatchUser)
			{
				return true ; 
			}
			if(uSize != sizeof(PlayerChoiseStruct))
			{
				return false ; 
			}
			PlayerChoiseStruct *pChoiseData = (PlayerChoiseStruct *)pData ; 

			OnCSNotifyFlyMessage(bDeskStation ,pChoiseData->inDexPlane ) ; 

			return true ; 
		}
	case  ASS_DICE_PROP:
		{
			if(bWatchUser)
			{
				return true ; 
			}
			if(uSize != sizeof(PropDiceStruct))
			{
				return false ; 
			}

			PropDiceStruct *pDiceData = (PropDiceStruct *)pData ; 

			OnCSPropDiceMessage(bDeskStation , pDiceData->cbIndex) ;

			return true ; 
		}
	case  ASS_PLANE_FLY_FINISH:
		{
			if(bWatchUser)
			{
				return true ; 
			}

			OnUserAniFinish(bDeskStation) ; 
			return true ; 
		}
	case ASS_AUTO:			//托管
		{
			if ((bWatchUser)||(uSize!=sizeof(AutoStruct))) 
				return FALSE;
			AutoStruct * pAuto = (AutoStruct*)pData;
			UserSetAuto(bDeskStation,pAuto->bAuto);
			return true;
		}
	default: 
		{
			break;
		}
	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}
///通知玩家打色子界面
bool CServerGameDesk::OnNotifyClentApplyDice(BYTE bDeskStation )
{
	m_bFlying = false ; 

	m_bUserProp = false ; 

	for(int i = 0 ; i<PLAY_COUNT ; i++) 
	{
		if(true == m_Logic.CheckGameFinish(i))  ///结束这里判断的(此处玩家的动画结束)
		{
			m_cbWinPlayer = i ;
			GameFinish(i ,GF_NORMAL) ; 
			return true ; 
		}
	}

	memset(m_bDiceAniFinish , false ,sizeof(m_bDiceAniFinish)) ; 

	WaitDiceStruct uData ; 
	uData.cbDeskStation = bDeskStation ; 

	for(int  i = 0 ; i<PLAY_COUNT ; i++)
	{
		if(NULL != m_pUserInfo[i])
		{
			SendGameDataSaveFile(i , &uData , sizeof(uData) , MDM_GM_GAME_NOTIFY , ASS_APPLY_DICE ,0 ) ; 
		}
	}
	SendWatchData(m_bMaxPeople, &uData , sizeof(uData) , MDM_GM_GAME_NOTIFY , ASS_APPLY_DICE ,0 ) ; 
	return true ; 
}
///玩家道具色子
bool CServerGameDesk::OnCSPropDiceMessage(BYTE  bDeskStation , BYTE cbDicevalue) 
{
	if(bDeskStation != m_cbOperater)
	{
		return true ; 
	}

	if(cbDicevalue <1 ||cbDicevalue >6)
	{
		return true ; 
	}
#ifdef  TEST_VERSION
	m_cbPropDiceCount[bDeskStation] = 2; ///测试版永远有道具
#else 
	if(m_cbPropDiceCount[bDeskStation]<1)
	{
		return true ; 
	}
	
#endif

	m_bUserProp = true ; 

	m_cbPropDiceValue = cbDicevalue ; 

	m_cbPropDiceCount[bDeskStation] --  ; 

	OnCSNotifyDiceMessage(bDeskStation) ;

	return true ; 

}
///处理客户端发过来的消息,通知玩家打色子
bool  CServerGameDesk::OnCSNotifyDiceMessage(BYTE bDeskStation) 
{
	KillMyTimer(TIME_APPLY_DICE) ; 

	if(m_bGameStation != GS_PLAY_GAME)
	{
		return true ; 
	}
	if(bDeskStation !=  m_cbOperater)
	{
		return true ; 
	}

	srand((unsigned)time(NULL) + 1111) ;
	m_cbDiceValue = rand()%6 + 1 ; 

	if(m_cbPropDiceValue >0 &&m_cbPropDiceValue <7 )
	{
		m_cbDiceValue = m_cbPropDiceValue ; 

		m_cbPropDiceValue = 0 ; 
	}

	NotifyDiceStruct NotifyData ;
	NotifyData.cbDeskStation = bDeskStation ; 
	NotifyData.cbDiceValue = m_cbDiceValue ; 
	NotifyData.cbPropCount = m_cbPropDiceCount[bDeskStation] ; 

	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		if(NULL != m_pUserInfo[i])
		{
			SendGameDataSaveFile( i ,&NotifyData,sizeof(NotifyData),MDM_GM_GAME_NOTIFY,ASS_NOTIFY_DICE ,0) ; 
		}
	}

	SetMyTimer(TIME_PLAYER_DICE,3000) ; 

	return true ; 
}
///处理客户端发来的飞机起飞消息
bool CServerGameDesk::OnCSNotifyFlyMessage(BYTE bDeskStation,int inDex)
{
	if(bDeskStation != m_cbOperater)
	{
		DebugPrintf(m_pDataManage->m_InitData.uRoomID , "不是正确的人处理了消息") ;

		return true ; 
	}
	if(0 >inDex ||inDex>=PLAYER_PLANE_NUM )
	{
		DebugPrintf(m_pDataManage->m_InitData.uRoomID , "没有找到正确的飞机啊") ;

		return true  ; 
	}

	if( !m_Logic.IsCanMove(bDeskStation , inDex , m_cbDiceValue))  //不符合飞行逻辑
	{
		return true ; 
	}

	if(m_bFlying)   ///防止客户端多次点击
	{
		return true ; 
	}

	m_bFlying = true ; 

	KillMyTimer(TIME_PLANE_FLY) ;

	memset(&m_ActiveData , 0 ,sizeof(m_ActiveData)) ; 

	///服务端根据当前的点数走棋
	int  bActivePlane = m_Logic.PlayerPlaneFly(bDeskStation ,m_cbDiceValue ,inDex ,m_ActiveData.PlaneActive) ;

	MsgPrint("wysoutfxqinfo::玩家的飞机开始飞行 飞行的点数==%d " ,m_ActiveData.PlaneActive[0].cbStepCount); 

	PlayerActiveStruct uActiveData ; 

	uActiveData = m_ActiveData ; 

	uActiveData.iPlaneCount = bActivePlane ;  

	uActiveData.cbDeskStation = bDeskStation ; 

	uActiveData.cbDiceValue = m_cbDiceValue ; 

	memcpy(uActiveData.iPlayerfight , m_Logic.m_iPlayerfight , sizeof(m_Logic.m_iPlayerfight)) ; 
	

	if(0 == bActivePlane)
	{
		DebugPrintf(m_pDataManage->m_InitData.uRoomID ,"游戏飞行有问题 ,一个飞机都没动");
	}

	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		if(NULL != m_pUserInfo[i])
		{
			continue; 
		}
		SendGameDataSaveFile(i, &uActiveData ,sizeof(uActiveData) , MDM_GM_GAME_NOTIFY ,ASS_PLANE_FLY_ANI ,0) ; 
	}

	SendGameDataSaveFile(m_bMaxPeople , &uActiveData ,sizeof(uActiveData) , MDM_GM_GAME_NOTIFY ,ASS_PLANE_FLY_ANI ,0) ;


	SetMyTimer(TIME_PLANE_FLY_INTEVAL ,15*1000) ;
	

	return true ; 
}

///玩家动画播放完毕
bool CServerGameDesk::OnUserAniFinish(BYTE bDeskStation )
{
	m_bDiceAniFinish[bDeskStation] = true ; 
	int  iAniFinishCount = 0 ; 
	for(int i = 0 ; i <PLAY_COUNT ; i++)
	{
		if(m_bDiceAniFinish[i] == true||m_bUserNetCut[i])
		{
			iAniFinishCount ++ ; 
		}
	}

	if(iAniFinishCount  == PLAY_COUNT)
	{
		KillMyTimer(TIME_PLANE_FLY_INTEVAL) ;


		ScenceChangeStruct pScenceData ;

		for(int i = 0 ; i<PLAY_COUNT ; i++)
		{
			for(int j = 0 ;  j <PLAYER_PLANE_NUM ; j++)
			{
				pScenceData.PlaneData[i][j] = m_Logic.m_PlayerSerInfo[i].Plane[j] ; 
			}
		}

		for(int i = 0 ; i<PLAY_COUNT ; i++)
		{
			SendGameDataSaveFile(i , &pScenceData ,sizeof(pScenceData) ,MDM_GM_GAME_NOTIFY ,ASS_PLANE_FLY_FINISH ,0) ; 
		}

		SendWatchData(m_bMaxPeople ,&pScenceData ,sizeof(pScenceData) ,MDM_GM_GAME_NOTIFY ,ASS_PLANE_FLY_FINISH ,0) ; 

		if(m_cbDiceValue != 6 ||true == m_bUserProp)
		{
			m_cbOperater = GetNextDeskStation(m_cbOperater) ; 
		}

		OnNotifyClentApplyDice(m_cbOperater) ; 

		if(m_bUserNetCut[m_cbOperater] == true)
		{
			SetMyTimer(TIME_APPLY_DICE , 1000) ; 
		}
		else
		{
			SetMyTimer(TIME_APPLY_DICE , m_iDiceTime*1000) ; 
		}
	}

	return true ; 
}
//托管设置
bool CServerGameDesk::UserSetAuto(BYTE bDeskStation, bool bAutoCard)
{
	if (bDeskStation>=PLAY_COUNT)
	{
		return false;
	}
	m_bAuto[bDeskStation] = bAutoCard;

	AutoStruct autoset;
	autoset.bAuto = bAutoCard;
	autoset.bDeskStation = bDeskStation;

	for(int i = 0; i < PLAY_COUNT; i ++)
		SendGameDataSaveFile(i,&autoset,sizeof(autoset),MDM_GM_GAME_NOTIFY,ASS_AUTO,0);
	SendWatchData(m_bMaxPeople,&autoset,sizeof(autoset),MDM_GM_GAME_NOTIFY,ASS_AUTO,0);
	return true;
}
// 删除游戏内部计时器
void CServerGameDesk::KillMyTimer(UINT nTimeID)
{
	int nIdx = nTimeID-TIME_SEND_CARD;
	if (nIdx<0 || nIdx>TIMER_COUNT-1)
	{
		return;
	}
	memset(&m_arTimer[nIdx], 0, sizeof(TimerStruct));
}
///删除我其他的定时器
void CServerGameDesk::KillAllMyTimer()
{
	for(int i = 0 ; i<TIMER_COUNT ; i++)
	{
		KillMyTimer(i +TIME_SEND_CARD) ;
	}

	return ; 
}
// 创建游戏内部计时器
int CServerGameDesk::SetMyTimer(UINT nTimeID, int uElapse)
{
	int nElapse = uElapse/MY_ELAPSE;
	if (nElapse<1)
	{
		nElapse = 1;
	}
	int nIdx = nTimeID-TIME_SEND_CARD;
	if (nIdx<0 || nIdx>TIMER_COUNT-1)
	{
		DebugPrintf(m_pDataManage->m_InitData.uRoomID,"定时器[%d]创建不成功", nTimeID);
		return -1;
	}

	char mess[200];
	wsprintf (mess, "SetMyTimer  m_arTimer 长度=%d 实际值%d nTimeID=%d",17,nIdx,nTimeID);
	SrvTestlog(mess);

	m_arTimer[nIdx].nId = nTimeID;
	m_arTimer[nIdx].nTriggerCount = nElapse;
	return 0;
}
bool CServerGameDesk::OnTimer(UINT uTimerID)
{	
	if (uTimerID != TIME_MY_TIMER)
	{
		return __super::OnTimer(uTimerID);
	}
	for (int i=0; i<TIMER_COUNT; ++i)
	{
		if (m_arTimer[i].nId == 0)
		{
			continue;
		}
		++m_arTimer[i].nTickCount;
		if (m_arTimer[i].nTickCount >= m_arTimer[i].nTriggerCount)
		{
			m_arTimer[i].nTickCount = 0;
			OnMyTimer(m_arTimer[i].nId);
		}
	}

	return true;
}
//定时器消息
bool CServerGameDesk::OnMyTimer(UINT uTimerID)
{
	switch(uTimerID)
	{
	case TIME_APPLY_DICE:
		{
			KillMyTimer(TIME_APPLY_DICE) ; 
			OnCSNotifyDiceMessage(m_cbOperater) ;  
			break;
		}
	case  TIME_PLAYER_DICE:
		{
			KillMyTimer(TIME_PLAYER_DICE) ; 

			if(!CheckPlaneCanFly(m_cbOperater))
			{
				m_cbOperater = GetNextDeskStation(m_cbOperater) ; 
				OnNotifyClentApplyDice(m_cbOperater) ; 

				if(m_bUserNetCut[m_cbOperater] == true)
				{
					SetMyTimer(TIME_APPLY_DICE , 1000) ; 
				}
				else
				{
					SetMyTimer(TIME_APPLY_DICE , m_iDiceTime*1000) ; 
				}

			}
			break;
		}
	case  TIME_PLANE_FLY:
		{
			KillMyTimer(TIME_PLANE_FLY) ; 

			int iPlaneIndex = m_Logic.FindOnePlaneToFly(m_cbOperater ,m_cbDiceValue) ; 

			MsgPrint("wysoutfxqinfo::iPlaneIndex==%d ,m_cbDiceValue==%d ,m_cbOperater==%d" ,iPlaneIndex , m_cbDiceValue ,m_cbOperater) ;

			OnCSNotifyFlyMessage(m_cbOperater ,iPlaneIndex ) ; 

			break;
		}
	case TIME_PLANE_FLY_INTEVAL:
		{
			KillMyTimer(TIME_PLANE_FLY_INTEVAL) ;


			ScenceChangeStruct pScenceData ;

			for(int i = 0 ; i<PLAY_COUNT ; i++)
			{
				for(int j = 0 ;  j <PLAYER_PLANE_NUM ; j++)
				{
					pScenceData.PlaneData[i][j] = m_Logic.m_PlayerSerInfo[i].Plane[j] ; 
				}
			}

			for(int i = 0 ; i<PLAY_COUNT ; i++)
			{
				SendGameDataSaveFile(i , &pScenceData ,sizeof(pScenceData) ,MDM_GM_GAME_NOTIFY ,ASS_PLANE_FLY_FINISH ,0) ; 
			}

			SendWatchData(m_bMaxPeople ,&pScenceData ,sizeof(pScenceData) ,MDM_GM_GAME_NOTIFY ,ASS_PLANE_FLY_FINISH ,0) ; 

			if(m_cbDiceValue != 6 ||true == m_bUserProp)
			{
				m_cbOperater = GetNextDeskStation(m_cbOperater) ; 
			}

			OnNotifyClentApplyDice(m_cbOperater) ;
			if(m_bUserNetCut[m_cbOperater] == true)
			{
				SetMyTimer(TIME_APPLY_DICE , 1000) ; 
			}
			else
			{
				SetMyTimer(TIME_APPLY_DICE , m_iDiceTime*1000) ; 
			}
			break;
		}
	default:
		{
			break;
		}
	}
	return __super::OnTimer(uTimerID);
}
//获取游戏状态信息
bool CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{	
	switch (m_bGameStation)
	{
	case GS_WAIT_SETGAME:		//游戏没有开始状态
	case GS_WAIT_ARGEE:			//等待玩家开始状态
		{
			GameBaseStation GameStation ;
			::memset(&GameStation,0,sizeof(GameStation)) ; 

			GameStation.iVersion1 = DEV_HEIGHT_VERSION ; 
			GameStation.iVersion2 = DEV_LOW_VERSION ;

			memcpy(GameStation.bUserReady ,m_bPlayerReady , sizeof(m_bPlayerReady)) ;
			memcpy(GameStation.bUserAuto , m_bAuto , sizeof(m_bAuto)) ; 

			GameStation.cbBeginTime = m_iBeginTime ; 
			GameStation.cbDiceTime  = m_iDiceTime ; 
			GameStation.cbThinkTime = m_iThinkTime ; 

			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));

			return TRUE;
		}
	case GS_SEND_CARD:		//发牌状态
		{		
			return TRUE;
		}
	case GS_PLAY_GAME:	//游戏中状态
		{
			PlayingGameStation GameStation;		
			::memset(&GameStation,0,sizeof(GameStation));

			GameStation.cbBeginTime = m_iBeginTime ; 
			GameStation.cbDiceTime  = m_iDiceTime ; 
			GameStation.cbThinkTime = m_iThinkTime ; 

			GameStation.iVersion1 = DEV_HEIGHT_VERSION ; 
			GameStation.iVersion2 = DEV_LOW_VERSION ; 

			GameStation.cbOperater = m_cbOperater ; 

			memcpy(GameStation.bUserAuto , m_bAuto , sizeof(m_bAuto)) ; 

			memcpy(GameStation.cbPropCount , m_cbPropDiceCount , sizeof(GameStation.cbPropCount)) ; 
			memcpy(GameStation.iPlayerfight , m_Logic.m_iPlayerfight , sizeof(GameStation.iPlayerfight)) ; 

			for(int i = 0 ; i<PLAY_COUNT ; i++)
			{
				for(int j = 0 ;  j <PLAYER_PLANE_NUM ; j++)
				{
					GameStation.PlaneData[i][j] = m_Logic.m_PlayerSerInfo[i].Plane[j] ; 
				}
			}

			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	case GS_WAIT_NEXT:		//等待下一盘游戏开始
		{		
			WaitNextGameStation GameStation;
			::memset(&GameStation,0,sizeof(GameStation));

			GameStation.iVersion1 = DEV_HEIGHT_VERSION ; 
			GameStation.iVersion2 = DEV_LOW_VERSION ; 

			GameStation.cbBeginTime = m_iBeginTime ; 
			GameStation.cbDiceTime  = m_iDiceTime ; 
			GameStation.cbThinkTime = m_iThinkTime ; 

			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}

	default:
		break;
	}
	return false;
}

//获取下一个玩家位置
BYTE CServerGameDesk::GetNextDeskStation(BYTE bDeskStation)
{
	if (bDeskStation>=PLAY_COUNT)
	{
		return 0;
	}
	if(FALSE == m_bTurnRule )//顺时针
	{
		return (bDeskStation + 1 ) % PLAY_COUNT;
	}

	return 	(bDeskStation + (PLAY_COUNT - 1)) % PLAY_COUNT;
}
///检测飞机起飞
bool  CServerGameDesk::CheckPlaneCanFly(BYTE bDeskStation)
{
	int  iActiveCount  = m_Logic.FindActivePlaneCount(bDeskStation) ;

	int  iFinishCount = m_Logic.FindPlaneFinishCount(bDeskStation) ; 

	MsgPrint("wysoutfxqinfo::iActiveCount ===%d , iFinishCount==%d ,m_cbDiceValue==%d" , iActiveCount , iFinishCount ,m_cbDiceValue) ;

	if(m_cbDiceValue == 6)  ///当前的骰子点数为6的话
	{
		if(iFinishCount == PLAYER_PLANE_NUM - 1)  ///已经有三架飞机完成飞行任务
		{
			SetMyTimer(TIME_PLANE_FLY ,20 ) ;
		}
		else
		{
			if(true == m_bUserNetCut[bDeskStation])
			{
				SetMyTimer(TIME_PLANE_FLY , 20);
			}
			else
			{
				SetMyTimer(TIME_PLANE_FLY , (m_iThinkTime + 3)*1000);
			}
			

			NotifyChoisePlane   pChoiseData ; 
			pChoiseData.cbDeskStation = bDeskStation ; 

			SendGameDataSaveFile(bDeskStation ,&pChoiseData , sizeof(pChoiseData),MDM_GM_GAME_NOTIFY ,ASS_NOTIFY_CHOISE_PLANE ,0) ;
		}
		return true ; 
	}

	if(iActiveCount >0)
	{
		if(iActiveCount  == 1 )  ///只有一架的时候直接起飞
		{
			SetMyTimer(TIME_PLANE_FLY , 20) ;
		}
		else ///需要玩家点击哪一个飞机起飞操作
		{
			if(true == m_bUserNetCut[bDeskStation])
			{
				SetMyTimer(TIME_PLANE_FLY , 20);
			}
			else
			{
				SetMyTimer(TIME_PLANE_FLY , (m_iThinkTime + 3)*1000);
			}

			NotifyChoisePlane   pChoiseData ; 
			pChoiseData.cbDeskStation = bDeskStation ; 

			for(int i = 0 ; i<PLAY_COUNT ; i++)
			{
				SendGameDataSaveFile(bDeskStation ,&pChoiseData , sizeof(pChoiseData),MDM_GM_GAME_NOTIFY ,ASS_NOTIFY_CHOISE_PLANE ,0) ;
			}
			SendWatchData(m_bMaxPeople ,&pChoiseData , sizeof(pChoiseData),MDM_GM_GAME_NOTIFY ,ASS_NOTIFY_CHOISE_PLANE ,0) ;
		}
		return true ; 
	}

	return false ;  //下个玩家继续打色子
}
//游戏结束
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	if (bDeskStation>=PLAY_COUNT)
	{
		return TRUE;
	}	
	KillAllMyTimer() ; 
	KillTimer(TIME_MY_TIMER);
	//编写代码
	switch (bCloseFlag)
	{
	case GF_NORMAL:		//游戏正常结束
		{
			//DebugPrintf(m_pDataManage->m_InitData.uRoomID,"游戏结束");
			//设置数据 
			m_bGameStation = GS_WAIT_ARGEE;
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}

			//游戏结束
			GameEndStruct GameEnd;
			::memset(&GameEnd,0,sizeof(GameEnd));

			///获取游戏中的倍数
			int  iPoint = 0; 

			if(m_Logic.m_iPlayerfight[m_cbWinPlayer%2] >m_Logic.m_iPlayerfight[(m_cbWinPlayer+1)%2])
			{
				iPoint = 3 ; 
			}
			else if(m_Logic.m_iPlayerfight[m_cbWinPlayer%2] == m_Logic.m_iPlayerfight[(m_cbWinPlayer+1)%2])
			{
				iPoint = 2 ; 
			}
			else
			{
				iPoint = 1 ; 
			}

			for(int i = 0 ; i<PLAY_COUNT ; i ++ )
			{
				if(i == m_cbWinPlayer || i == (m_cbWinPlayer + 2 )%PLAY_COUNT)
				{
					GameEnd.iTurePoint[i] = m_iGameBasePoint *iPoint  ; 
				}
				else
				{
					GameEnd.iTurePoint[i] =-m_iGameBasePoint *iPoint ; 
				}
			}

			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));

			ChangeUserPointint64(GameEnd.iTurePoint,temp_cut);
			__super::RecoderGameInfo(GameEnd.iChangeMoney);

			m_bGameStation = GS_WAIT_ARGEE;

			for (int i = 0; i < PLAY_COUNT; i ++) 
			{
				SendGameDataSaveFile(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_NO_CONTINUE_END,0);
			}

			SendWatchData(m_bMaxPeople,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_NO_CONTINUE_END,0);

			bCloseFlag = GFF_FORCE_FINISH;
			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);

			return true;
		}
	case GFF_SAFE_FINISH:
	case GF_SAFE:			//游戏安全结束
		{
			//设置数据
			m_bGameStation = GS_WAIT_ARGEE;//GS_WAIT_SETGAME;

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			GameCutStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));

			for (int i = 0; i < PLAY_COUNT; i ++) 
				SendGameDataSaveFile(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SAFE_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SAFE_END,0);

			bCloseFlag = GFF_FORCE_FINISH;

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GFF_FORCE_FINISH:		//用户断线离开
		{
			m_bGameStation = GS_WAIT_ARGEE;

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING ;
			}
			GameCutStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));
			CutEnd.bDeskStation = bDeskStation;

			int  iArriveCount[PLAY_COUNT] ; 
			memset(iArriveCount , 0 , sizeof(iArriveCount)) ; 

			for(int  i = 0 ; i<PLAY_COUNT ; i++)
			{
				iArriveCount[i] = m_Logic.FindPlaneFinishCount(i) ;
			}

			if(iArriveCount[bDeskStation]+iArriveCount[(bDeskStation + 2)%PLAY_COUNT]>iArriveCount[(bDeskStation + 1)%PLAY_COUNT]+iArriveCount[(bDeskStation + 3)%PLAY_COUNT])
			{
				CutEnd.iTurePoint[bDeskStation] = - 4*(8 -iArriveCount[bDeskStation]-iArriveCount[(bDeskStation + 2)%PLAY_COUNT])*m_iGameBasePoint ;

				CutEnd.iTurePoint[(bDeskStation+2)%PLAY_COUNT] = 2*(8 -iArriveCount[bDeskStation]-iArriveCount[(bDeskStation + 2)%PLAY_COUNT])*m_iGameBasePoint ;
			}
			else
			{
				int iPoint1 = 0 ;  ///逃跑倍率
				int iPoint2 = 0 ;  /// 未逃跑倍率
				if(m_Logic.m_iPlayerfight[bDeskStation] +m_Logic.m_iPlayerfight[(bDeskStation+2)%PLAY_COUNT]< m_Logic.m_iPlayerfight[(bDeskStation+1)%PLAY_COUNT] +m_Logic.m_iPlayerfight[(bDeskStation+3)%PLAY_COUNT])
				{
					iPoint1 = 6 ; 
					iPoint2 = 3 ;
				}
				else if(m_Logic.m_iPlayerfight[bDeskStation] +m_Logic.m_iPlayerfight[(bDeskStation+2)%PLAY_COUNT]==m_Logic.m_iPlayerfight[(bDeskStation+1)%PLAY_COUNT] +m_Logic.m_iPlayerfight[(bDeskStation+3)%PLAY_COUNT])
				{
					iPoint1 = 4 ; 
					iPoint2 = 2; 
				}
				else
				{
					iPoint1 = 3 ; 
					iPoint2 = 1 ;
				}
				CutEnd.iTurePoint[bDeskStation] = -iPoint1 *8*m_iGameBasePoint ; 
				CutEnd.iTurePoint[(bDeskStation + 1)%PLAY_COUNT] = iPoint2 *m_iGameBasePoint *(8 - iArriveCount[bDeskStation] - iArriveCount[(bDeskStation + 2)%PLAY_COUNT])/2 ;
				CutEnd.iTurePoint[(bDeskStation + 3)%PLAY_COUNT] = iPoint2 *m_iGameBasePoint *(8 - iArriveCount[bDeskStation] - iArriveCount[(bDeskStation + 2)%PLAY_COUNT])/2 ;
			}


			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				temp_cut[i] = (bDeskStation == i && CutEnd.iTurePoint[i] < 0);
			}

			ChangeUserPointint64(CutEnd.iTurePoint, temp_cut);
			__super::RecoderGameInfo(CutEnd.iChangeMoney);

			for (int i = 0; i < PLAY_COUNT; i ++)
				SendGameDataSaveFile(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);

			bCloseFlag = GFF_FORCE_FINISH;

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);

			return TRUE;
		}
	}
	//重置数据
	ReSetGameState(bCloseFlag);
	__super::GameFinish(bDeskStation,bCloseFlag);

	return true;
}

//玩家逃跑其他玩家得分
int CServerGameDesk::GetRunAwayOtherGetPoint(BYTE bDeskStation,BYTE bRunDeskStation )
{
	return 0;
}

//逃跑扣分
int CServerGameDesk::GetRunPublish()
{
	return m_pDataManage->m_InitData.uRunPublish;
}
//逃跑扣分
int CServerGameDesk::GetRunPublish(BYTE bDeskStation)
{
	return m_pDataManage->m_InitData.uRunPublish;
}
//用户同意开始
bool CServerGameDesk::UserAgreeGame(BYTE bDeskStation)
{
	return  __super::UserAgreeGame(bDeskStation);	
}
//判断是否正在游戏
bool CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	if((m_bGameStation >= GS_SEND_CARD && m_bGameStation < GS_WAIT_NEXT))
		return true;
	return false;
}
//用户离开游戏桌
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	if (bDeskStation>=PLAY_COUNT)
	{
		return 0;
	}	

	m_bPlayerReady[bDeskStation] = false ; 

	return __super::UserLeftDesk(bDeskStation,pUserInfo);
}

//用户断线离开
bool CServerGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	m_bUserNetCut[bDeskStation] = true ; 
	return  __super::UserNetCut(bDeskStation,  pLostUserInfo);
}

//用户断线重来
bool CServerGameDesk::UserReCome(BYTE bDeskStation, CGameUserInfo * pNewUserInfo)
{	
	m_bUserNetCut[bDeskStation] = false ; 
	return __super::UserReCome(bDeskStation,pNewUserInfo);
}

//用户坐到游戏桌
BYTE CServerGameDesk::UserSitDesk(MSG_GR_S_UserSit* pUserSit, CGameUserInfo* pUserInfo)
{
	return __super::UserSitDesk(pUserSit,pUserInfo);
}
/**
* 发送数据函数 （发送消息给游戏者）并且存盘
*
* @param bDeskStation 发送给哪个玩家的逻辑号
*
* @param bMainID数据的类型
*
* @param bAssID数据的id
*
* @bSingle伴随值
*/
bool CServerGameDesk::SendGameDataSaveFile(BYTE bDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode,bool bSingle)
{
	if (m_bIskinescope )  //是否录像
	{
		if ( bMainID == MDM_GM_GAME_NOTIFY ) 
		{
			if ( !bSingle )
			{ 
				NetMessageHead NetHead;
				NetHead.bMainID      = bMainID;
				NetHead.bAssistantID = bAssID;
				m_saveFile.SaveFileMessage(&NetHead,NULL,0);

			}
			else
			{
				if ( bDeskStation == 0  )
				{
					NetMessageHead NetHead;
					NetHead.bMainID      = bMainID;
					NetHead.bAssistantID = bAssID;
					m_saveFile.SaveFileMessage(&NetHead,NULL,0);
				}
			}

		}
	}
	return SendGameData(bDeskStation,bMainID,bAssID,bHandleCode);
}

/**
* 发送数据函数 （发送消息给游戏者）并且存盘
*
* @param bDeskStation 发送给哪个玩家的逻辑号
*
* @param pData发送的数据包
*
* @param uSize发送的数据
*
* @param bMainID数据的类型
*
* @param bAssID数据的id
*
* @bSingle伴随值
*/
bool CServerGameDesk::SendGameDataSaveFile(BYTE bDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode,bool bSingle)
{
	return SendGameData(bDeskStation,pData,uSize,bMainID,bAssID,bHandleCode);
}
///名称：SrvTestlog
///描述：日志记录接口
///@param pMessage 日志信息
///@return 
void  CServerGameDesk::SrvTestlog(TCHAR *pMessage)
{
	return ;	// 发布出去不记录
	try
	{
		CString  tempstr = CINIFile::GetAppPath();
		SYSTEMTIME st;
		GetLocalTime(&st);
		TCHAR FileName[256];
		//wsprintf(FileName, TEXT("e:\\syslog%d.txt\0"),GetCurrentProcessId());
		//wsprintf(FileName, TEXT("ddz-L.txt"),tempstr,st.wYear,st.wMonth,st.wDay,st.wHour);
		wsprintf(FileName, TEXT("%d-%d-%d-ddz-L.txt"),st.wMonth,st.wDay,st.wHour);
		CFile syslog;
		syslog.Open(FileName,CFile::modeNoTruncate| CFile::modeCreate |CFile::modeReadWrite);
		TCHAR szDate[256];
		wsprintf(szDate, TEXT("%d-%d-%d %d-%d-%d.%d\t"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		syslog.SeekToEnd();
		syslog.Write(szDate,lstrlen(szDate));
		syslog.SeekToEnd();
		syslog.Write(pMessage,lstrlen(pMessage));
		TCHAR nextLine[] = TEXT("\r\n");
		syslog.SeekToEnd();
		syslog.Write(nextLine,lstrlen(nextLine));

		syslog.Close();
	}
	catch(CException *e)
	{
		//AfxMessageBox("some exception!");
		e->Delete();
		return ; 
	}
}
