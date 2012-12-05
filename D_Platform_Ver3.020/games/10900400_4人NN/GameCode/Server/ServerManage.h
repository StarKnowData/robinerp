#pragma once

#include "StdAfx.h"
#include"..\GameMessage\UpgradeLogic.h"

//定时器 ID
#define TIME_SEND_CARD				30				//发牌定时器
#define TIME_CALL_NT				31				//叫庄
#define TIME_GAME_FINISH			32				//游戏结束定时器
#define TIME_SEND_A_CARD			33				//发送一张牌
#define TIME_BEGIN_ANIMAL			34				//游戏开始动画
#define TIME_COLLECT_JETON			35				//收集动画
#define TIME_CUTLINE_AUTO			36				//断线自动摆牛
#define TIME_NOTE                   37              //下注计时器
/*
//游戏配置信息
#define PLAY_MAX_NOTE				500			//最大下注
#define PLAY_BASE_NOTE				5				//底注
#define THINK_TIME					30				//游戏思考时间
#define PLAY_CARD_COUNT				1				//扑克副数

*/

//游戏结束标志定义
#define GF_NORMAL					10				//游戏正常结束
#define GF_SALE						11				//游戏安全结束

//
#define SH_USER_CARD                5               //牌的张数


//#define SEND_CARD_TIME				1000			//发牌时间设置测试用10毫秒,正常用1000

//游戏桌类
class CServerGameDesk : public CGameDesk
{
protected:
	//运行状态变量
	int						m_iNtPeople;                          //赢家
	int						m_iUpGradePeople;					//庄家位置
	BYTE					m_iBeenPlayGame;					//已经游戏的局数
	BYTE					m_iLeaveArgee;						//离开同意标志
	BYTE					m_iHaveThingPeople;					//有事要走玩家
	//状态信息
	BYTE					m_iUserCardCount[PLAY_COUNT];				//用户手上扑克数目
	BYTE					m_iUserCard[PLAY_COUNT][10];					//用户手上的扑克
	int						m_iCallScore[PLAY_COUNT];                     //叫庄状况
	//运行信息
	int						m_iOutCardPeople;					//现在出牌用户
	int						m_iFirstOutPeople;					//先出牌的用户
	//发牌数据
	BYTE					m_iTotalCard[52];					//总的牌
	BYTE					m_iSendCardPos;						//发牌位置
	BYTE                    m_bBullCard[PLAY_COUNT][3];                        //玩家摆的牛牌

	CUpGradeGameLogic		m_Logic;							//游戏逻辑
	int						m_iGameStation;						//游戏状态
	int						m_iLastOutPeople;
    int                     m_MaxPlayer;                        //下注闲家的数量;
	int						m_iUserStation[PLAY_COUNT];				//记录用户状态
	__int64						m_iPerJuTotalNote[PLAY_COUNT];			//用户每局压总注
	//int						m_iInsuranceNote[PLAY_COUNT];					//当前保险金
	//__int64					m_iTotalNote;					//总注
	bool                    m_bAdd[PLAY_COUNT];                //是否加倍
	bool                    m_bIsCut[PLAY_COUNT];              //是否掉线了主要为机器人设置
	BYTE					m_iIngPlayNote;					//当前下注者（给旁观）
	BYTE					m_iLastShuttle;					//上一梭了者
	BYTE					m_iSendPos;				//新一轮发牌开始位置
	BYTE                    m_iPrepareNT;              //预备庄家
	BYTE					m_bCurrentCallScore;					//当前叫分者
	BYTE                    m_iFirstJiao;
	BYTE                    m_iGameFlag;             //当前游戏分状态
	BOOL                    m_bIsSuper[PLAY_COUNT];   //是否可以使用发牌
	BOOL                    m_bSuperSet;              //是否启动了发牌
	BYTE                    m_bControlWin;             //控制输赢位置
	BYTE                    m_bControlLost;             //控制输赢位置


private:
	static BYTE m_iAllCardCount;	//游戏所用的牌数
	__int64 m_iLimitNote[PLAY_COUNT];	//上限
	int m_iBaseNote;		//底注
	//=============扩展
	static 	int m_iSendCardTime;//游戏思考时间
	static 	BYTE m_iThinkTime;//游戏思考时间
	static 	BYTE m_iBeginTime;//游戏开始时间
	static 	BYTE m_iCallScoreTime;
	static 	BYTE m_iXiaZhuTime;
	static  BOOL m_bTurnRule;	//游戏顺序
	DWORD m_iCardShape;	//牌型
	BYTE  m_GameType;
	/// 牌型倍率2010-08-03
	BYTE m_bCardShapeBase[MAX_SHAPE_COUNT];//0-10代表无牛到牛牛间的倍率
    BYTE  m_iGameNoteSetType;         //是否启用牛牛中所有的牌型的最大值 
	int  m_iGoodCard;//发大牌机率牛七以上
	bool m_bHaveKing;//是否有王
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
	//函数定义
public:
	//构造函数
	CServerGameDesk(); 
	//析构函数
	virtual ~CServerGameDesk();

	//重载函数
public:
	//初始化游戏逻辑
	virtual bool InitDeskGameStation();
	//游戏开始
	virtual bool GameBegin(BYTE bBeginFlag);
	//游戏结束
	virtual bool GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	//判断是否正在游戏
	virtual bool IsPlayGame(BYTE bDeskStation);
	//框架消息处理函数
	virtual bool HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//游戏数据包处理函数
	virtual bool HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//用户离开游戏桌
	virtual BYTE UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	//
	virtual bool UserNetCut(BYTE bDeskStation, CGameUserInfo *pLostUserInfo);
	//用户断线重来
	virtual bool UserReCome(BYTE bDeskStation, CGameUserInfo * pNewUserInfo);

	//重载纯虚函数
public:
	//获取游戏状态信息
	virtual bool OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	//重置游戏状态
	virtual bool ReSetGameState(BYTE bLastStation);
	//定时器消息
	virtual bool OnTimer(UINT uTimerID);
	//处理函数
public:
	//读取静态变量
	BOOL LoadIni();	//准备发牌工作
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
	//计算升级
	int	GetUpGrade(int iGamePoint, int iPlayCardCount);
	//处理用户结果
	BOOL UserActiveResult(BYTE bDeskStation, BYTE iVerbType,int iNoteVal=0);
	//处理用户下注结果
	BOOL UserNoteResult(BYTE bDeskStation, BYTE iVerbType,__int64 iNoteVal=0);
	//检测是否结束
	BOOL CheckFinish();
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
	//查找设置牌
	BOOL SuperSetCard();
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
	//找庄家
	BOOL FindNt();
	//计算各家分数
	int ComputePoint(BYTE DeskStation);
	//得到最大牌和最小牌,win值为1时得到最大,其它为最小
	BYTE GetIndex(int win);
	//判断胜家
	BOOL JudgeWiner();
	//判断输家
	BOOL JudgeLoser();
	//换牌
	BOOL ChangeCard(BYTE bDestStation,BYTE bWinStation);
	//叫庄
	BOOL UserCallScore(BYTE bDeskStation, int iVal);
	//获取下一个玩家位置
	BYTE GetNextDeskStation(BYTE bDeskStation);
	//发送给第一个叫分
	BOOL SendCallScore(BYTE bDeskStation);
	//叫分结束
	BOOL CallScoreFinish();
	//用户下注
	BOOL UserNote();
	//算出玩家投注最大上限
	__int64 GetLimit(int bDeskStation);
	//统计掉线玩家
	BYTE CountCutPlayer();
	//玩家AI设置
	BOOL UserAI(BYTE bDeskStation,BYTE bCutType,bool bNet);
	//玩家强退
	BOOL UserFourceQuit(BYTE bDeskStation);
	//清理强退玩家
	void ClearQuitPlayer();
	///清理所有计时器
	void KillAllTimer();;

	///获取当前牌中最大的牌型，
	int GetMaxCardShape(BYTE iCard[], int iCardCount);
};

/******************************************************************************************************/
