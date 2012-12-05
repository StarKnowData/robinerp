#pragma once

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

//#define	VIDEO

#ifdef	VIDEO
		//文件名字定义
		#define GAMENAME						TEXT("围棋视频版")
		#define NAME_ID							30200205							//名字 ID
#else
		//文件名字定义
		#define GAMENAME						TEXT("围棋")
		#define NAME_ID							30200200							//名字 ID
#endif

//版本定义
#define GAME_MAX_VER					1								//现在最高版本
#define GAME_LESS_VER					1								//现在最低版本
#define GAME_CHANGE_VER					0								//修改版本

//支持类型
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
#define GAME_TABLE_NAME					"WQ"
//游戏信息

#define PLAY_COUNT						2								//游戏人数

#define MAIN_VERSION					704						 //主版本号,?年?月
#define ASS_VERSION						21				//辅助版本号,?号

//游戏内部开发版本号
#define DEV_HEIGHT_VERSION				1				//内部开发高版本号(每修正一次LOW_VERSIONG+1)
#define DEV_LOW_VERSION					1				//内部开发低版本号


//游戏状态定义
#define GS_WAIT_SETGAME					0				//等待东家设置状态
#define GS_WAIT_ARGEE					1				//等待同意设置
#define GS_PLAY_GAME					22				//游戏中状态
#define GS_WAIT_NEXT					23				//等待下一盘开始 

#define ASS_GAME_READY					63				//游戏准备工作

//#define SKIN_FOLDER						TEXT("wq")	//图片文件夹
//#define SKIN							TEXT("cardskin1")	//两套图片中用一套
//#define SKIN_CARD						TEXT("wq")		//共用图片文件夹

#define GET_STRING(NUM)                 #NUM
#define INT_TO_STR(NUM)                 GET_STRING(NUM)
#define CLIENT_DLL_NAME                 TEXT(INT_TO_STR(NAME_ID)##".ico")        // 客户端ico名字
#define SKIN_FOLDER                     TEXT("") //TEXT(INT_TO_STR(NAME_ID))     // 客户端目录
#define GET_NAME_ID                     TEXT(INT_TO_STR(NAME_ID))                // 游戏ID
#define MUSIC_FOLDER					TEXT("wq")	//图片文件夹


/********************************************************************************/

//游戏数据包

/********************************************************************************/
//游戏中使用了的时间信息 jph100127
struct UsedTimeInfo
{
	int m_iJuUseTime[2];
	int	m_iBuUseTime[2];
	int	m_iDuUseTime[2];
	UsedTimeInfo()
	{
		memset(m_iJuUseTime,0,sizeof(m_iJuUseTime));
		memset(m_iBuUseTime,0,sizeof(m_iBuUseTime));
		memset(m_iDuUseTime,0,sizeof(m_iDuUseTime));
	}
};

//游戏状态数据包	（ 等待东家设置状态 ）
struct GameStation_1
{
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	//游戏倍数
	UINT				iDeskBasePoint;					//桌面基础分
	UINT				iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分
	int					iRunPublishMoney;				//逃跑金币
};

//游戏状态数据包	（ 等待其他玩家开始 ）
struct GameStation_2
{
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	//游戏倍数
	UINT				iDeskBasePoint;					//桌面基础分
	UINT				iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分
	int					iRunPublishMoney;				//逃跑金币

	int					iJuTimeMinute;					//局时分
	int					iJuTimeSecond;					//局时秒
	int					iBuTimeMinute;					//步时分
	int					iBuTimeSecond;					//步时秒
	int					iDuMiaoMinute;					//读秒分
	int					iDuMiaoSecond;					//读秒秒
};


//游戏状态数据包(游戏中)	


//游戏状态数据包	（ 游戏中状态 ）
struct GameStation_4	
{
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	//游戏倍数
	UINT				iDeskBasePoint;					//桌面基础分
	UINT				iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分
	int					iRunPublishMoney;				//逃跑金币
	//游戏信息
	int					iJuTimeMinute;					//局时分
	int					iJuTimeSecond;					//局时秒
	int					iBuTimeMinute;					//步时分
	int					iBuTimeSecond;					//步时秒
	int					iDuMiaoMinute;					//读秒分
	int					iDuMiaoSecond;					//读秒秒

	BYTE				iPlayCount;						//游戏盘数
	BYTE				iBeenPlayGame;					//已经游戏的局数
	int					iOutCardPeople;					//现在出牌用户
	int					iFirstOutPeople;				//先出牌的用户
	int					m_iLastDeskStation;				//最后出牌的用户
	int					iQiZi[21][21];
	int					iTiZiNum[2];
	int					iQiZiNum[2];						//已下棋子数
	int					iEndI;
	int					iEndJ;
	int                isHitAgreedianmu;                  //是否点击了同意点目
	UsedTimeInfo		m_stUsedTimeInfo;					//使用过的时间

	bool				bIsInHuiquStation[2];			//是否处理悔棋状态
	bool				bChessingInHuiQi[2];
};

//游戏状态数据包	（ 等待下盘开始状态  ）
struct GameStation_5
{
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	//游戏倍数
	UINT				iDeskBasePoint;					//桌面基础分
	UINT				iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分
	int					iRunPublishMoney;				//逃跑金币
	//游戏信息
	BYTE				iBeginStation;					//开始位置
	BYTE				iEndStation;					//结束位置
	BYTE				iPlayCount;						//游戏盘数
	BYTE				iCardCount;						//扑克数目

	//运行状态变量
	int					iWinPoint;						//游戏积分
	int					iPunishPoint;					//用户罚分
	int					iUpGradePeople;					//庄家位置
	BYTE				iPlayNTNum[2];					//各玩家的主牌数目
	BYTE				iBeenPlayGame;					//已经游戏的局数
};

//用户同意游戏
struct UserArgeeGame
{
	
	int			iJuTimeMinute;//局时分
	int			iJuTimeSecond;//局时秒
	int			iBuTimeMinute;//步时分
	int			iBuTimeSecond;//步时秒
	int			iDuMiaoMinute;//读秒分
	int			iDuMiaoSecond;//读秒秒
};

struct PrepareStruct
{
	BYTE			bDeskStation;					//选手位置
};

//游戏开始
struct BeginUpgradeStruct
{
	BYTE				bDeskStation;				//庄家位置
	BYTE				iPlayCount;						//游戏回合
};


//游戏开始数据包
struct BeginPlayStruct
{
	BYTE				bDeskStation;				//出牌的位置
};

//游戏准备,先手位置,白手位置
struct GameReadyStruct
{
	BYTE				iBlackStation;					//先手位置
	BYTE				iWhiteStation;					//白手位置
};

//游戏结束统计数据包
struct GameEndStruct
{
	//BYTE				bDeskStation;						//庄家位置
	BYTE				bDeskStation;						//玩家位置
	BYTE				iDoublePointEffect;					//双倍积分卡有效性 20081125
	__int64				iTurePoint[PLAY_COUNT];					//庄家得分
	__int64				iChangeMoney[PLAY_COUNT];				//金币
	char				szNickName[PLAY_COUNT][61];
};

////游戏结算
//struct GameFinishNotify
//{
//	TCHAR name[PLAY_COUNT][21];
//	BYTE iStyle;								//游戏类型是否为强退,还是正常结束
//	int	iScore1;								//点子数
//	int	iScore2;								//点子数二
//	int	iTurePoint[PLAY_COUNT];					//认输求和
//	int iChangeMoney[PLAY_COUNT];				//比赛所留钱数
//};

//游戏结算
struct GameFinishNotify
{
	int	 iUpGradePeople;
	int iGrade2;
	TCHAR name[4][21];
	BYTE iStyle;			//游戏类型是否为强退,还是正常结束
	int	iWardPoint[4];
	__int64	iTurePoint[PLAY_COUNT];				//认输求和
	int	iScore1;								//点子数
	int	iScore2;								//点子数二
	int iChangeMoney[PLAY_COUNT];				//比赛所留钱数
	__int64 iMoney[4];
};

struct HaveThingStruct
{
	BYTE bDeskStation;
	char szMessage[61];
};

struct LeaveResultStruct
{
	BYTE bDeskStation;
	int bArgeeLeave;
};

struct MessageStruct	//客户端到服务器
{
	char Message[200];
};
//
struct StopResultStruct
{
	bool bArgee;
};
//数据包(认输)
struct LoserStruct 
{
	BYTE	bDeskStation;
	BYTE	bReserver;
};
//数据包(超时,认输)
struct SuperTimerStruct 
{
	BYTE	bDeskStation;
	BYTE	bReserver;
};
///棋子数据包（发向客户端）
struct PlayChessMsg
{	
	BYTE				bDeskStation;		//当前下子者
	int					iEndI;
	int					iEndJ;
	int					iPlayFlag;
	int					iTiZiNum[2];//提子数
	int					iChessArray[21][21];
//	int					iNextPlayStation;
	int					iQiZiNum[2];
};
//下子者
struct PlayChessStruct
{
	BYTE				bDeskStation;
};
//
struct DianMu
{
	int qi[21][21];
};
//
struct FinishDianMu
{
	int qi[21][21];
	char msg[50];
};
//悔棋数据包(发向客户端)
struct RegretChessMsg
{
	int					iLastChessArray[21][21];//记录上步棋局
	int					iLastTiZiNum[2];//记录上步提子数
	int					iLastDeskStation;//走棋者的位置
};

struct DianMuResultStruct	//点目
{
	bool bAgree;
};

/**
* @brief 同步时间数据包
*/
struct SyncTimeStruct
{
	int					iBotJuUseTime;
	int					iBotBuUseTime;
	int					iBotDuUseTime;
};


/********************************************************************************/

// 数据包处理辅助标识

/********************************************************************************/

#define ASS_UG_USER_SET					50				//用户设置游戏
#define ASS_BEGIN_UPGRADE				51				//升级游戏开始
#define ASS_GAME_PREPARE				52				//先手
#define ASS_GAME_PLAY					51				//开始游戏

#define ASS_OUT_CARD_RESULT				60				//用户出牌结果
#define ASS_OUT_CARD					61				//下一出牌者
#define ASS_SYNC_TIME					63				///< 同步用时

#define ASS_SUPER_TIMER					71				//超时处理
#define ASS_REN_SHU						72				//认输
#define ASS_HUI_QI						73				//悔棋
#define ASS_AGREE_HUI_QI				74				//同意悔棋

#define ASS_DIAN_MU						75			//点目
#define ASS_AGREE_DIAN_MU				76			//同意点目
#define ASS_NUMBER_ZI					77			//强制数子
#define ASS_DIAN_MU_RESULT				78			//点目结果处理

#define ASS_CONTINUE_END				80				//游戏结束
#define ASS_SUPER_TIMER_END				81				//超时结束
#define ASS_LOSER_END					82				//认输结束
#define ASS_NO_CONTINUE_END				83				//游戏结束
#define ASS_CUT_END						84				//用户强行离开
#define ASS_SALE_END					85				//游戏安全结束

#define ASS_HAVE_THING					90
#define ASS_LEFT_RESULT					91
#define ASS_MESSAGE						92
#define ASS_STOP_THING					93
#define ASS_AGREE_STOP					94

#define ASS_GET_GAME_USED_TIME			95				//获取使用时间	

/********************************************************************************/
#endif
