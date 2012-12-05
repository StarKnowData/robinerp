#pragma once

#include "StdAfx.h"
#include "logic.h"
//定时器 ID
#define TIME_SEND_CARD				30				//发牌定时器
#define TIME_WAIT_NT				31				//等待反牌
#define TIME_GAME_FINISH			32				//游戏结束定时器


//扑克数目定义
#define PLAY_TWO_CARD				1				//两副扑克
#define PLAY_THREE_CARD				2				//三副扑克

//游戏结束标志定义
#define GF_NORMAL					10				//游戏正常结束
#define GF_SALE						11				//游戏安全结束
#define GF_SUPER_TIMER		12				//超时结束
#define GF_LOSER					13				//认输

#define BASE_SCORE				10				//底分(基数)
//*****************************************************************************************

//游戏桌类
class CServerGameDesk : public CGameDesk
{
protected:
	//玩家设置数据
	BYTE					m_iLessCount;						//最少游戏局数
	BYTE					m_iPlayCardCount;					//游戏扑克数目
	BYTE					m_iBeginStation;					//游戏开始位置
	BYTE					m_iEndStation;						//游戏结束位置
	BYTE					m_iEnableWatch;						//是否允许旁观

	BYTE					m_iHaveThingPeople;						//有事要走玩家

	int						m_iJuTimeMinute,//局时
							m_iJuTimeSecond,
							m_iBuTimeMinute,//步时
							m_iBuTimeSecond,
							m_iDuMiaoMinute,//读秒
							m_iDuMiaoSecond;

	//运行状态变量
	int						m_iUpGradePeople;					//庄家位置
	BYTE					m_iPlayNTNum[PLAY_COUNT];					//各玩家的主牌数目
	BYTE					m_iBeenPlayGame;					//已经游戏的局数
	BYTE					m_iLeaveArgee;						//离开同意标志
	int						m_iOutCardPeople;					//现在出牌用户
	CUpGradeGameLogic		m_Logic;							//游戏逻辑

	int						m_iWinFlag;//获胜方
	int						m_iTurePoint[PLAY_COUNT];//真实得分

	bool					m_bFirstRed;
	bool					m_bQiuHe;
	
	//wq
	int						m_iBoard[21][21];
	int						m_idianmu[21][21];
	int						m_iQiZiNum[PLAY_COUNT];//统计黑白两方的下的棋子数（用于提子）
	int						m_iQiZiLastNum[PLAY_COUNT];//上手双方棋子数
	int						m_iTiZiNum[PLAY_COUNT];

	bool                    m_bUserNetCut[PLAY_COUNT];  //用户断线
	int                     m_bAgreeDianmuFinish;             //-1表示无人点击，0表示已回应点击点目，1表示没有回应点击

	//悔棋数据
	int						m_iLastDeskStation;//上步走棋者的位置
	int						m_iLastBoard[21][21];//上步棋局
	int						m_iLastTiZiNum[PLAY_COUNT];//上步提子数
	int						m_Endi;
	int						m_Endj;

	int						m_iFinishNumCnt;//完成点目
	int						m_iDianMuResult;//点目结果处理
	CString					m_dianmumsg;
	int						m_Qiflag[PLAY_COUNT];

	int						m_iBlackStation;			//先手位置
	int						m_iWhiteStation;			//白手位置

	UsedTimeInfo			m_stUsedTimeInfo;//已经使用的时间信息

	bool					m_bIsInHuiquStation[2];				///< 是否处于悔棋状态
	bool					m_bChessingInHuiQi[2];
	
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

	//重载纯虚函数
public:
	//获取游戏状态信息
	virtual bool OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	//重置游戏状态
	virtual bool ReSetGameState(BYTE bLastStation);
	//定时器消息
	virtual bool OnTimer(UINT uTimerID);
	//处理函数
	//玩家断线处理
	virtual bool UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);
   //用户重新进入游戏
	virtual  bool UserReCome(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);
public:
	//用户设置游戏
	BOOL UserSetGame(UserArgeeGame * pGameSet,BYTE desk);
	//游戏开始
	BOOL BeginPlay();
	//用户出牌
	BOOL UserOutCard(BYTE bDeskStation, int iPlayQi[][21], int iPlayFlag, int iEndI, int iEndJ);
	//用户请求离开
	BOOL UserHaveThing(BYTE bDeskStation, char * szMessage);
	//同意用户离开
	BOOL ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee);
	//计算升级
	int	GetUpGrade(int iGamePoint, int iPlayCardCount);

	//游戏准备工作
	BOOL GameReady();

	//强制数子
	void ForceNumberZi(int &iWinFlag, CString &strMessage);
public:
	//清理所有计时器
	void KillAllTimer();
	//桌面倍数
	int GetDeskBasePoint();
	//房间倍数
	int GetRoomBasePoint();
	//逃跑扣分
	int GetRunPublish();
	//逃跑扣分
	int GetRunPublishMoney();
};
