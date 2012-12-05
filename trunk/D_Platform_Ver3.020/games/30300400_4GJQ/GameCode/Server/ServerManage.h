#pragma once

#include "StdAfx.h"

#include "jqlogic.h"
/// 定时器 ID
///#define TIME_SEND_CARD			30							///< 发牌定时器
#define TIME_GAME_FINISH			32							///< 游戏结束定时器

#define TIME_USER_OUT_CARD          33                          //玩家走棋定时器
/// 扑克数目定义
#define PLAY_TWO_CARD				1							///< 两副扑克
#define PLAY_THREE_CARD				2							///< 三副扑克

/// 游戏结束标志定义
#define GF_NORMAL					10							///< 游戏正常结束
#define GF_SALE						11							///< 游戏安全结束
#define GF_PREEND                   12							///< 提前结束

/// 游戏桌类 H021_UserPass
class CServerGameDesk : public CGameDesk
{
	bool H021_UserPass(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	CJqLogic m_Logic;
	bool H0011_UserBuZhen(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	
	int m_Counter;
	///void H004_SendCard();
	bool H001_GameBegin(BYTE bBeginFlag);
    bool H048_ArgeeStopThing(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
    bool H046_StopThing(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
    bool H043_ArgeeUserLeft(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	bool H040_UserHaveThing(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	bool H020_UserOutCard(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	bool H000_UserAgreeGame(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);

protected:
	/// 玩家设置数据
	BYTE					m_iLessCount;						///< 最少游戏局数
	BYTE					m_iEnableWatch;						///< 是否允许旁观

	//运行状态变量
	int						m_PunishPoint[4];					///< 用户罚分
	BYTE					m_iBeenPlayGame;					///< 已经游戏的局数
	BYTE					m_iLeaveArgee;						///< 离开同意标志
	int                     m_iTimerCount ;                     ///当前的定时器
	
	bool					m_bQueryQuit;						///< 有玩家请求退出
	int						m_bdesk;							///< 请求退出的玩家
	bool					m_bBuzhen[4];						///< 玩家是否已布阵
	/// 函数定义
public:
	/// 构造函数
	CServerGameDesk(); 
	/// 析构函数
	virtual ~CServerGameDesk();

	/// 重载函数
public:
	/// 游戏开始
	int GetPlayerCount();
	/// 得到第一个有玩家的位置
	int GetPlayerStation();
	virtual bool GameBegin(BYTE bBeginFlag)
	{
		m_Logic.m_maxPeople=m_bMaxPeople;
		m_Logic.m_iPlayerCount=GetPlayerCount();
		m_Logic.m_iStation=GetPlayerStation();
		m_Counter = 0;
		return H001_GameBegin(bBeginFlag);
	}
	/// 游戏结束
	virtual bool GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	/// 判断是否正在游戏
	virtual bool IsPlayGame(BYTE bDeskStation);
	/// 游戏数据包处理函数
	virtual bool HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	/// 用户离开游戏桌
	virtual BYTE UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);

	/// 重载纯虚函数
public:
	/// 获取游戏状态信息
	virtual bool OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	/// 重置游戏状态
	virtual bool ReSetGameState(BYTE bLastStation);
	/// 定时器消息
	virtual bool OnTimer(UINT uTimerID);
	/// 处理函数
public:
	/// 用户设置游戏
	BOOL UserSetGame(UserArgeeGame * pGameSet);
	/// 发送扑克给用户
	/// /BOOL SendCard();
	/// 游戏开始
	BOOL BeginPlayUpGrade();	
	/// 新一轮开始
	BOOL NewPlayTurn(int iWiner);
	/// 用户请求离开
	BOOL H041_UserHaveThing(BYTE bDeskStation, char * szMessage);
	/// 同意用户离开
	BOOL H044_ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee);
};
































