#pragma once

///#include "..\..\消息文件\mj.h"

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

#ifdef	VIDEO
		//文件名字定义
		#define GAMENAME						TEXT("四国军棋视频版")
		#define NAME_ID							30300405								///< 名字 ID
#else
		#define GAMENAME						TEXT("四国军棋")
		#define NAME_ID							30300400								///< 名字 ID
#endif

/// 版本定义
#define GAME_MAX_VER					1												///< 现在最高版本
#define GAME_LESS_VER					1												///< 现在最低版本
#define GAME_CHANGE_VER					0												///< 修改版本

/// 支持类型
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
#define GAME_TABLE_NAME					"MatchTable_JQ"
/// 游戏信息

#define PLAY_COUNT						4												///< 游戏人数

#define	VERSION							3
#define MAIN_VERSION					707												///< 主版本号,?年?月
#define ASS_VERSION						VERSION											///< 辅助版本号,?号

static TCHAR szTempStr[MAX_PATH] = {0};//暂存字符串，用来获取 dll_name 等的时候使用
#define GET_CLIENT_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".ico"))
#define GET_SERVER_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".dll"))       

#ifdef TWO_PEOPLE
#define CLIENT_DLL_NAME					TEXT("JQ2.ico")
#define SERVER_DLL_NAME					TEXT("JQ2Srv.DLL")
#define NAME_ID							51												///< 名字 ID
#define PLAY_COUNT						2												///< 游戏人数
#define MAIN_VERSION					707												///< 主版本号,?年?月
#define ASS_VERSION						(VERSION*10+1)									///< 辅助版本号,?号
#endif

//#define SKIN_FOLDER					TEXT("jq")										///< 图片文件夹
//#define SKIN							TEXT("cardskin1")								///< 两套图片中用一套
//#define SKIN_CARD						TEXT("card")									///< 共用图片文件夹

#define GET_STRING(NUM)                 #NUM
#define INT_TO_STR(NUM)                 GET_STRING(NUM)
#define CLIENT_DLL_NAME                 TEXT(INT_TO_STR(NAME_ID)##".ico")				///<  客户端ico名字
#define SKIN_FOLDER                     TEXT("")//TEXT(INT_TO_STR(NAME_ID))             ///<  客户端目录
#define SKIN_FOLDER1                    TEXT(INT_TO_STR(NAME_ID))						///<  客户端目录

/// 游戏状态定义
#define GS_WAIT_SETGAME					0												///< 等待东家设置状态
#define GS_WAIT_ARGEE					1												///< 等待同意设置
#define GS_BUZHEN						20												///< 发牌状态
//wushuqun  2009.6.16
#define GS_PLAY_GAME					21												///< 游戏中状态
#define GS_WAIT_NEXT					23												///< 等待下一盘开始 

/********************************************************************************/

struct tagBuZhen
{
	int station;
	int Count;										///< 各家的扑克数目
	int CardArr[40];								///< 自己的扑克信息

	tagBuZhen()
	{
		station=-1;
		Count=0;
		memset(CardArr,0,40);
	}
};

/// 游戏结束统计数据包
struct tagNextStep
{
	int					station;					///< 退出位置
	int					station2;					///< 失败的第二个玩家
};

struct tagMove
{
	int					m_iStartI,m_iStartJ,m_iEndI,m_iEndJ;
	int					iStep;
	BYTE				cPath[17][17];
};

struct tagMoveResult
{
	int	m_iStartI,m_iStartJ,m_iEndI,m_iEndJ;	
	int station,nextstation;
	int ToJq,FromJq;
	int loseColor;
	int loseColor2;									///< 第二个失败玩家
	int iStep;
	BYTE cPath[17][17];						///< 所有路径
};

typedef struct tagPATHMSG
{
	bool bContinueInsertPos[17][17];
	int iCurStep;
	POINT FrontPath;
	POINT BackPath;
	POINT CurPath;
	tagMoveResult PathMsg;

	void Init()
	{
		iCurStep = 0;
		FrontPath.x = FrontPath.y = 255;
		BackPath.x = BackPath.y = 255;
		CurPath.x = CurPath.y = 255;		
		memset(&PathMsg, 0, sizeof(PathMsg));
		memset(bContinueInsertPos, 0, sizeof(bContinueInsertPos));
	}

	void tagMoveResult()
	{
		Init();
	}
}_PathMsg;

#define JJ_TEST
#ifdef JJ_TEST
//#define JJ_TEST_DEAD
#endif





















/*





struct tagMjPai
{
	int					 Count;						//各家的扑克数目
	int				 CardArr[40];					//自己的扑克信息

	tagMjPai()
	{
		Count=0;
		memset(CardArr,0,40);
	}
};



struct tagUserMjPai
{
	int station;
	tagMjPai   MjPai	;	
	tagUserMjPai(){station=-1;}
};


struct tagUserZhuaPai
{
	int station;
	int iStartIndex;
	int iEndIndex;
	tagMjPai   MjPai	;	
	tagUserZhuaPai(){station=iStartIndex=iEndIndex=-1;}
};



//用户出牌数据包 （发向服务器）
struct ChuPaiStruct
{
	int ChuPaiType;
	int station;
	int					iCardCount;						//扑克数目
//	ARRUSERMJ				iCardList;					//扑克信息

	int m_iF1;

	ChuPaiStruct &operator =(ChuPaiStruct& from)
	{
		ChuPaiType=from.ChuPaiType;
		station=from.station;
		iCardCount=from.iCardCount;
		//for(int i=0;i<iCardCount;i++)
//			iCardList[i]=from.iCardList[i];
		return * this;
	}
	void Clear(){ChuPaiType = station =m_iF1=-1;iCardCount = 0;}
};


*/

//游戏数据包

/********************************************************************************/

//游戏状态数据包	（ 等待东家设置状态 ）
struct GameStation_1
{

	//游戏信息
	BYTE				iCardCount;						//扑克数目
	int			        iMainVersion;
	int			        iLessVersion;
	int					uRunPublish;	//扣分
	int					basepoint;		//倍数
};

//游戏状态数据包	（ 等待其他玩家开始 ）
struct GameStation_2
{
	//游戏信息
	BYTE				iPlayCount;						//游戏盘数
	BYTE				iCardCount;						//扑克数目
	int			iMainVersion;
	int			iLessVersion;
	int					uRunPublish;	//扣分
	int					basepoint;		//倍数
	int mBoard[17][17];
};

//游戏状态数据包	（ 游戏正在发牌状态 ）
//游戏状态数据包	（ 等待扣押底牌状态 ）
struct GameStation_3
{
	//游戏信息
	
	BYTE				iPlayCount;						//游戏盘数
	int                 iTimerCount ; 
	int					iWinPoint;						//游戏积分
	int					iPunishPoint;					//用户罚分
	BYTE				iBeenPlayGame;					//已经游戏的局数
	int					uRunPublish;	//扣分
	int					basepoint;		//倍数
	int					m_iNowOutPeople;	
	int mBoard[17][17];
	int m_iStartI,m_iStartJ,m_iEndI,m_iEndJ;
};

/*

//游戏状态数据包	（ 游戏中状态 ）
struct GameStation_4	:public GameStation_3
{
	int					iOutCardPeople;					//现在出牌用户
};
*/
//游戏状态数据包	（ 等待下盘开始状态  ）
struct GameStation_5
{
	
	BYTE				iPlayCount;						//游戏盘数
	BYTE				iCardCount;						//扑克数目

	//运行状态变量
	int					iWinPoint;						//游戏积分
	int					iPunishPoint;					//用户罚分
	int					iUpGradePeople;					//庄家位置
	BYTE				iBeenPlayGame;					//已经游戏的局数
	int					uRunPublish;	//扣分
	int					basepoint;		//倍数
};

//用户同意游戏
struct UserArgeeGame
{
	BYTE				iPlayCount;						//游戏盘数
	BYTE				iCardCount;						//扑克数目
};

//游戏开始
struct BeginGameStruct
{
	BYTE				iPlayCount;						//游戏回合
};

//发牌数据包
struct SendCardStruct
{
	int					iCardCount[4];						//各家的扑克数目
	int iStartIndex;
	int iEndIndex;
};

//游戏开始数据包
struct BeginPlayStruct
{
	BYTE				iOutDeskStation;				//出牌的位置
};

/*
struct PassOutCkeckStruct
{
	int bDeskStation;
};



//玩家的分数据包
struct GamePointStruct
{
	bool				bAdd;
	int					iPoint;							//得分数目
	int station;
};
*/
//游戏结束统计数据包
struct GameEndStruct
{
	int					iTurePoint[4];					//庄家得分
	__int64					iChangeMoney[4];				//金币
	BYTE				iDoublePointEffect;				//双倍积分卡效果；20081125	
};

//游戏结束统计数据包
typedef struct tagGameResult
{
	int					iWardPoint[PLAY_COUNT];					//庄家得分
	int					iMoney[PLAY_COUNT];				//金币
	TCHAR               name[PLAY_COUNT][60];
	tagGameResult()
	{
        memset(this, 0, sizeof(tagGameResult));
	}
}GameResult;

//游戏结束统计数据包
struct GameCutStruct
{
	int					bDeskStation;					//退出位置
	__int64					iChangeMoney[4];				//金币
	int					iTurePoint[4];					//庄家得分
};

struct HaveThingStruct
{
	BYTE pos;
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

struct StopResultStruct
{
	bool bArgee;
};

/*
struct CastSeZiStruct
{
	int step;////抛色子次数
	int sezi1Dian,
		sezi2Dian;

	CastSeZiStruct(){step =sezi1Dian =sezi2Dian=0;}
};

*/
/********************************************************************************/

// 数据包处理辅助标识

/********************************************************************************/
#define ASS_UG_USER_SET					50				//用户设置游戏
#define ASS_BEGIN_UPGRADE				51				//升级游戏开始
#define ASS_BUZHEN					52				//发牌信息

///#define ASS_SEND_FINISH					54				//发牌完成
#define ASS_GAME_PLAY					59				//开始游戏
#define ASS_OUT_CARD					60				//用户出牌
#define ASS_GAME_POINT					63				//用户分数
///#define ASS_NEW_TURN					64				//新一轮开始
#define ASS_CONTINUE_END				65				//游戏结束
#define ASS_NO_CONTINUE_END				66				//游戏结束
#define ASS_CUT_END						67				//用户强行离开
#define ASS_SALE_END					68				//游戏安全结束
#define ASS_HAVE_THING					69
#define ASS_LEFT_RESULT					70
#define ASS_MESSAGE						71
#define ASS_STOP_THING					72
#define ASS_AGREE_STOP					73

#define ASS_NEXT_STEP					74				//新一轮开始

#define ASS_LOSE                        75
#define ASS_PASS                        76


/********************************************************************************/
#endif
