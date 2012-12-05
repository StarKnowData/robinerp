#pragma once

#include "GameDesk.h"
#include "AsaveAndReadfile.h"
#include "..\GameMessage\UpGradeLogic.h"

// 定时器所用结构
struct TimerStruct 
{
	UINT nId;			//定时器标志号
	int nTickCount;		//已经经过了次
	int nTriggerCount;	// 经过多少次后触发事件
	TimerStruct(UINT nTimerID, int uElapse) : nId(nTimerID),nTickCount(0), nTriggerCount(uElapse)
	{
	}
	TimerStruct(): nId(0),nTickCount(0), nTriggerCount(0){}
};
//定时器 ID
#define TIME_MY_TIMER				20				//公用定时器，只有这个定时器是实际定时器，其余都是从这个定时器经过判断来的
#define MY_ELAPSE					500				// 定时器间隔
#define TIMER_COUNT					10		// 用到的定时器数目

// 下列为游戏中使用到的定时器，由上面的TIME_MY_TIMER计数进行统一处理
#define TIME_SEND_CARD				30				//发牌定时器
#define TIME_APPLY_DICE             31             ///玩家申请打色子
#define TIME_PLAYER_DICE            32             ///玩家打色子
#define TIME_PLANE_FLY              33             ///飞机起飞定时器
#define TIME_PLANE_FLY_INTEVAL      34             ///飞机起飞时间间隔


//游戏结束标志定义
#define GF_NORMAL					10				//游戏正常结束
#define GF_SAFE						11				//游戏安全结束
#define GF_TERMINATE				14				//意外停止游戏
#define GF_AHEAD_END				15				//提前结束


///游戏桌类
class CServerGameDesk : public CGameDesk
{
private:
	///定时器操作及变量
	TimerStruct		       m_arTimer[TIMER_COUNT];
	void                   KillMyTimer(UINT nTimeID);
	int                    SetMyTimer(UINT nTimeID, int uElapse);
	bool                   OnMyTimer(UINT uTimerID);
	void                   KillAllMyTimer() ; 
	int				       m_iTimerCount;	/// 定时器计数

	//静态变量
private:

	static                 BOOL m_bTurnRule;	       ///游戏顺序	
	static                 BOOL m_bIskinescope;        /// 是否录像默认不录
	//=============扩展
	BYTE                   m_iBeginTime;               ///游戏开始时间
	BYTE                   m_iDiceTime ;               ///打色子时间
	BYTE                   m_iThinkTime;               ///游戏思考时间
	int                    m_iGameBasePoint ;          ///基本底注

protected:
	///游戏逻辑
	CUpGradeGameLogic		m_Logic;
	///录像存储
	CAsaveAndReadfile       m_saveFile;
	///至少打完多少局
	UINT	                m_iLimitPlayGame;	
	///已经游戏的局数
	BYTE					m_iBeenPlayGame;
 
public:

	BYTE                    m_cbOperater ;  ///当前操作的人    
	BYTE                    m_cbDiceValue ;  ///当前色子的点数
	BYTE                    m_cbWinPlayer ;  //胜利的玩家


	BYTE                    m_cbPropDiceValue ;  ///玩家要求打的色子

	BYTE                    m_cbPropDiceCount[PLAY_COUNT] ; 

	bool                    m_bPlayerReady[PLAY_COUNT] ; 

	///托管设置
	bool					m_bAuto[PLAY_COUNT];	

	bool                    m_bUserNetCut[PLAY_COUNT] ; 

	bool                    m_bDiceAniFinish[PLAY_COUNT] ; 


	PlayerActiveStruct      m_ActiveData ;  ///这个数据要保存起来校对客户端的飞机数据

	bool                    m_bFlying  ;       ///飞机正在飞行过程中

	bool                    m_bUserProp ;    //是否使用道具

	//函数定义
public:
	//构造函数
	CServerGameDesk(); 
	//析构函数
	virtual ~CServerGameDesk();
	//重载函数
public:
	//游戏开始
	virtual bool GameBegin(BYTE bBeginFlag);
	//游戏结束
	virtual bool GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	//判断是否正在游戏
	virtual bool IsPlayGame(BYTE bDeskStation);
	//游戏数据包处理函数
	virtual bool HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//用户离开游戏桌
	virtual BYTE UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	virtual bool HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//用户同意开始
	virtual bool UserAgreeGame(BYTE bDeskStation);
	//获取游戏状态信息
	virtual bool OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	//重置游戏状态
	virtual bool ReSetGameState(BYTE bLastStation);
	//定时器消息
	virtual bool OnTimer(UINT uTimerID);
	//配置INI文件
	virtual bool InitDeskGameStation();	
	//玩家断线处理
	virtual bool UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);
	//用户断线重来
	virtual bool UserReCome(BYTE bDeskStation, CGameUserInfo * pNewUserInfo);
	//用户坐到游戏桌
	virtual BYTE UserSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo);

public:
	///加载静态项的配置
	static BOOL LoadStaticIni();
    ///初始化开始数据
	bool IniBeginData() ; 
	///加载一般项的配置
	BOOL LoadExtIni();
	//根据房间ID加载底注和上限
	BOOL LoadExtIni(int iRoomID);
	//游戏开始
	BOOL BeginPlay();
	//殺所有計時器
	void KillAllTimer();
	//逃跑扣分
	int  GetRunPublish();
	//逃跑扣分
	int  GetRunPublish(BYTE bDeskStation);
	//非强退玩家得分
	int  GetRunAwayOtherGetPoint(BYTE bDeskStation,BYTE bRunDeskStation);
	//获取下一个玩家位置
	BYTE GetNextDeskStation(BYTE bDeskStation);
	///检测飞机起飞状况
	bool CheckPlaneCanFly(BYTE bDeskStation) ;  
	///通知客户端更新打色子界面
	bool OnNotifyClentApplyDice(BYTE bDeskStation ) ;  
	///处理客户端发来的消息
	bool OnCSNotifyDiceMessage(BYTE bDeskStation) ;
	///处理客户端发来的玩家选择完飞机起飞消息
	bool  OnCSNotifyFlyMessage(BYTE bDeskStation ,int inDex) ; 
	///处理客户端发来的道具消息
	bool  OnCSPropDiceMessage(BYTE  bDeskStation , BYTE cbDicevalue) ; 
	///处理客户端发来的玩家动画播放完毕
	bool  OnUserAniFinish(BYTE bDeskStation ) ; 
	///用户设置托管
	bool  UserSetAuto(BYTE bDeskStation, bool bAutoCard) ;

public:

	///发送数据函数 （发送消息给游戏者）并且存盘
	bool SendGameDataSaveFile(BYTE bDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode,bool bSingle = true );
	/// 发送数据函数 （发送消息给游戏者）并且存盘
	bool SendGameDataSaveFile(BYTE bDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode,bool bSingle = true);
	///日志记录接口
	void  SrvTestlog(TCHAR *pMessage);	
};

/******************************************************************************************************/
