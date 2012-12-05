#pragma once

#include "../../../../sdk/include/ServerCommon/GameDesk.h"
#include "../GameMessage/UpGradeLogic.h"

// 服务器开启太多的定时器，会影响性能，故此作出优化，只开一个定时器，所有使用到的定时器都由这个定时器来触发，在触发中加以判断

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
#define MY_ELAPSE					250				// 定时器间隔
#define TIMER_COUNT					11				// 用到的定时器数目

// 下列为游戏中使用到的定时器，由上面的TIME_MY_TIMER计数进行统一处理

#define TIME_SEND_CARD				30				//发牌定时器
#define TIME_WAIT_NT				31				//等待反牌
#define TIME_GAME_FINISH			32				//游戏结束定时器
#define TIME_SEND_A_CARD			33				//发送一张牌
#define TIME_BEGIN_ANIMAL			34				//游戏开始动画
#define TIME_COLLECT_JETON			35				//收集动画
#define TIMER_SEND_END              36
#define TIME_BIPAI					37				//比牌动画定时器
#define TIME_CUT_AI                 38              //托管定时器

#define TIMER_WAIT_NOTE             39				// 
#define TIMER_FINISH_COMPARE        40              // 游戏结束收筹码计时器

#define DEFAULT_WAIT_FREQUENCE      1000            //一秒中检测一次

/*
//游戏配置信息
#define PLAY_MAX_NOTE				500			//最大下注
#define PLAY_BASE_NOTE				5				//底注
#define THINK_TIME					30				//游戏思考时间
#define PLAY_CARD_COUNT				1				//扑克副数

*/#define ALL_CARD_COUNT				52				//一共使用的牌数
//游戏结束标志定义
#define GF_NORMAL					10				//游戏正常结束
#define GF_SALE						11				//游戏安全结束

//#define SEND_CARD_TIME				1000			//发牌时间设置测试用10毫秒,正常用1000
#define  TIMER_CUT_AI_LONG                  1000


// 用来方便地加锁和解锁的类
class BZWLockForCriticalSection
{
	CRITICAL_SECTION *m_pSection;
	BZWLockForCriticalSection();
public:
	BZWLockForCriticalSection(CRITICAL_SECTION *pSection)
	{
		m_pSection = pSection;
		EnterCriticalSection(m_pSection);
	}
	~BZWLockForCriticalSection()
	{
		LeaveCriticalSection(m_pSection);
	}
};


//游戏桌类
class CServerGameDesk : public CGameDesk
{

	//std::list<TimerStruct>	m_lstTimer;
	TimerStruct		m_arTimer[TIMER_COUNT];
	// 杀死定时器标志
	void KillMyTimer(UINT nTimeID);
	int SetMyTimer(UINT nTimeID, int uElapse);
	bool OnMyTimer(UINT uTimerID);
	CRITICAL_SECTION m_csForIPCMessage;

protected:
	enum 
	{
		FINISH_TYPE_UNFINISH = 0,     //没有结束		
		FINISH_TYPE_FISH = 1,         //其他结束      
		FINISH_TYPE_REACH_LIMITE_SELF = 2,  //达到上限，结束
		FINISH_TYPE_REACH_LIMITE_NEXT = 3   //下一家跟注就会超过限制
	};
	//运行状态变量
	//	int						m_PunishPoint[4];					//用户罚分
	BYTE					m_iNtPeople;                          //赢家

	int						m_iUpGradePeople;					//庄家位置
	BYTE					m_iBeenPlayGame;					//已经游戏的局数
	BYTE					m_iLeaveArgee;						//离开同意标志
	BYTE					m_iHaveThingPeople;					//有事要走玩家

	//状态信息
	BYTE					m_iUserCardCount[PLAY_COUNT];				//用户手上扑克数目
	BYTE					m_iUserCard[PLAY_COUNT][5];					//用户手上的扑克
	BOOL                    m_Ming[PLAY_COUNT];                         //明牌

	bool                    m_bOpenLoser[PLAY_COUNT];                    //比牌失败
	bool                    m_bIsGiveUp[PLAY_COUNT];                     //是否放弃

    int                     m_iNowBigPeople;
	//运行信息
	//	int						m_iGamePoint;						//用户游戏分数
	int						m_iOutCardPeople;					//现在出牌用户
	int						m_iFirstOutPeople;					//先出牌的用户
	bool                    m_bFirstNote;                       //是否为第一次下注

	BYTE					m_bReachLimitPlayer;				// 第一个达到上限的玩家座位号
	
	//发牌数据
	BYTE					m_iTotalCard[52];					//总的牌
	BYTE					m_iSendCardPos;						//发牌位置

	CUpGradeGameLogic		m_Logic;     						//游戏逻辑
	//	bool					m_bQueryQuit;						//有玩家请求退出

	int						m_iLastOutPeople;
	int						m_iUserStation[PLAY_COUNT];				//记录用户状态
	
	__int64						m_iUserNote[PLAY_COUNT];	       //用户每轮押注，就是本次下注额	
	
	
	__int64						m_iPerJuTotalNote[PLAY_COUNT];      //用户每局压总注	
	__int64						m_iNowNote[PLAY_COUNT];			    //当前押注数
	__int64						m_iTotalNote;					    //总注
	__int64                     m_iFrontNote;                      //前家押注
	
	__int64                     m_iThisGameNote[PLAY_COUNT];	    //当局总注(判断是否达到上限)
	__int64                     m_iTotalGameNote[PLAY_COUNT];
	
	__int64                     m_iMaxNote;                     //最大注(每局)按明注算
	int                     m_ihelp[PLAY_COUNT];
	BYTE					m_iIngPlayNote;					//当前下注者（给旁观）
	BYTE					m_iLastShuttle;					//上一梭了者
	int					    m_bAddNoteTime;					//下注次数，用来给客户端判断是否可以比牌

	BYTE					m_iSendPos;				//新一轮发牌开始位置

	//Add By JianGK.20100720
	int						m_dwAIBalanceMoney;						//机器人持有金币量稳定值
	BYTE					m_iAIWinProb[2];						//机器人胜率表

#ifdef SUPER_VERSION
	BYTE					m_bSuperCardList[8][54];				//超级客户端
	int						m_iSuperCardCount[8];					//
	int						m_bSuperStation;						//超级客户端位置
	struct SetCardStruct	//客户端到服务器
	{
		BYTE pai[8][54];
		int	paicount[8];
	};
#endif

private:
	static BYTE m_iAllCardCount;	//游戏所用的牌数
	__int64 m_iLimitNote;	            //上限            
	int m_iBaseNote;		//底注       
	int m_iGuoDi;           //锅底值
	__int64 m_iLimitePerNote;   //单注上限  暗注的，但显示为明注的

	//bool m_bCanOpen;         //判断是否可以开牌

	int      m_iTimerCount;   //记录玩家时间
	int      m_iAddressIndex[PLAY_COUNT]; 

	//玩家的索引
	int     m_iMaxSuperPeople;
	CString  m_strCityTextInDex[50];
	CString  m_strUserIDTextInDex[50];

	bool     m_bSuperUser[PLAY_COUNT];

	//=============扩展
	static 	BYTE m_iSendCardTime;//游戏思考时间
	static 	BYTE m_iThinkTime;//游戏思考时间
	static 	BYTE m_iBeginTime;//游戏开始时间	//函数定义

	//------------------------------与托管相关的功能------------------
	bool m_arybCutUser[PLAY_COUNT];     //玩家是否掉线
	void InitAIData();
	virtual bool OnBeginUserNetCutAI(BYTE bDeskStation);  //重载触发托管函数
    void ExcutNetCutAI();  //执行托管操作
	void SuperUserIDJudge();
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
	//框架消息处理函数
	virtual bool HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//用户离开游戏桌
	virtual BYTE UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	//用户断线
	virtual bool UserNetCut(BYTE bDeskStation, CGameUserInfo * pUserInfo);
virtual bool InitDeskGameStation();
	//重载纯虚函数
public:
	//获取游戏状态信息
	virtual bool OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	//重置游戏状态
	virtual bool ReSetGameState(BYTE bLastStation);
	//定时器消息
	virtual bool OnTimer(UINT uTimerID);

public:
	inline int GetLimit() {return (m_iLimitePerNote < m_iLimitNote ? m_iLimitePerNote : m_iLimitNote);}
	//处理函数
public:
	//读取静态变量
	static BOOL LoadIni();	//准备发牌工作
	//加载限注
	BOOL LoadExtIni();
	//根据房间ID加载底注和上限
	BOOL LoadExtIni(int iRoomID);
	//用户设置游戏
	BOOL UserSetGame(UserArgeeGame * pGameSet);
	//发送扑克给用户
	BOOL SendCard();
	//发牌结束
	BOOL SendCardFinish();
	//游戏开始
	BOOL BeginPlayUpGrade();

	//新一轮开始
	BOOL NewPlayTurn(BYTE bDeskStation);
	//发一张新牌
	BOOL SendACard ();
	//发送用户下注
	BOOL SendUserNote();
	//用户请求离开
	BOOL UserHaveThing(BYTE bDeskStation, char * szMessage);
	//同意用户离开
	BOOL ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee);
	//处理用户结果
	BOOL UserActiveResult(BYTE bDeskStation, BYTE iVerbType,int iNoteVal=0,BYTE bComparedStation=255);
    //比牌结果
	BOOL BiPaiActiveResult();
	//检测是否结束
	UINT CheckFinish();   //修改检测结束返回值
	//更新用户所下注
	void ModifyPlayNote(BYTE bDeskStation);
	//获取牌最大的位置(bExtVal表示比较明牌还是比较全部牌)
	int GetCardGreater(BOOL bExtVal=FALSE);
	//发牌位置
	BOOL CanSendCard(BYTE bDeskStation);
	//统计游戏人数
	BYTE CountPlayer();
	//收集筹码
	BOOL CollectJeton(BOOL bOnly=false);
	//设置牌
	BOOL SuperSetCard(BYTE iTotalCard[],int iCardCount);
	//換牌
	BOOL ChangeBackCard(BYTE bDeskStation,BYTE bSourceCard,BYTE bResultCard);
	//隊例中是否有某牌是否替換成功
	BOOL ReplaceCard(BYTE iTotalCard[],int iSendCardPos,int iEndPos,BYTE bSourceCard,BYTE bResultCard);
	//统计当前未放弃玩家
	BYTE CountNotePeople();
	//统计倍数(人头)
	int GetHumanBasePoint();
	//桌面倍数
	int GetDeskBasePoint();
	//房间倍数
	int GetRoomBasePoint();
	//逃跑扣分
	int GetRunPublish();
	//得到下一个出牌玩家的位置
	BYTE GetNextNoteStation(BYTE bCurDeskStation);

	void FinishCompare();                          //游戏结束前的比牌过程 

	//------------------------------------------
	//----控制输赢--------
	BOOL JudgeWiner();															//判断胜家	
	BOOL JudgeLoser();															//判断输家
	BOOL ChangeCard(BYTE bDestStation,BYTE bWinStation);						//换牌	
	BYTE GetWiner();														//得到赢家
	BYTE GetLoser();                                                         //得到输家
	bool SetUserCard();			// 读取配置文件，用于调试发牌	Add by zxd 20090803
	BYTE m_bCutLastPeoPle;


	//add by ljl 
	/**
	*
	*
	* @return 返回最小金币玩家的金币
	*/
	__int64 GetMinMoney();


	BYTE m_byWin[PLAY_COUNT];

	BOOL m_bIsShowIdOrPlay;
};

/******************************************************************************************************/
