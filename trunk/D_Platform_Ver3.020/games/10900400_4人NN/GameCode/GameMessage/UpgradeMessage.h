#pragma once

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

//文件名字定义
#ifdef VIDEO
#define GAMENAME						TEXT("牛牛")
#define NAME_ID							10900405							//名字 ID
#define PLAY_COUNT						4								//游戏人数
#else
#ifdef TWO_NN
#define GAMENAME						TEXT("牛牛(VIP)")
#define NAME_ID							10900200							//名字 ID
#define PLAY_COUNT						2								//游戏人数
#else
#define GAMENAME						TEXT("牛牛")
#define NAME_ID							10900400							//名字 ID
#define PLAY_COUNT						4								//游戏人数
#endif
#endif
//版本定义
#define GAME_MAX_VER					1								//现在最高版本
#define GAME_LESS_VER					1								//现在最低版本
#define GAME_CHANGE_VER					0								//修改版本

//支持类型
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
#define GAME_TABLE_NAME					"MatchTable"
//游戏信息



//#define SKIN_FOLDER						TEXT("nn")	//图片文件夹
//#define SKIN							TEXT("cardskin1")	//两套图片中用一套
//#define SKIN_CARD						TEXT("card")		//共用图片文件夹

#define GET_STRING(NUM)                 #NUM
#define INT_TO_STR(NUM)                 GET_STRING(NUM)
#define CLIENT_DLL_NAME                 TEXT(INT_TO_STR(NAME_ID)##".ico")        // 客户端ico名字
#define SKIN_FOLDER                     TEXT(INT_TO_STR(NAME_ID))                // 客户端目录
#define SKIN_CARD						TEXT("CardSkin")		                 // 共用图片文件夹


//游戏开发版本
#define DEV_HEIGHT_VERSION				3								//内部开发高版本号
#define DEV_LOW_VERSION					10 								//内部开发低版本号

//游戏状态定义
#define GS_WAIT_SETGAME					0				//等待东家设置状态
#define GS_WAIT_ARGEE					1				//等待同意设置
#define GS_SEND_CARD					20				//发牌状态
#define GS_WAIT_BACK					21				//等待扣压底牌
#define GS_PLAY_GAME					22				//游戏中状态
#define GS_WAIT_NEXT					23				//等待下一盘开始 
#define GS_FLAG_CALL_SCORE              24              //叫分
#define GS_NOTE                         25              //下底注

//按注类型
#define TYPE_GIVE_UP					0x00			//放弃
#define TYPE_RESET                      0x01            //要牌
#define TYPE_OPEN                       0x02            //开牌
#define TYPE_BULL						0x03			//牛
#define TYPE_PLAY_GAME                  0x04            //是玩家
#define TYPE_NOTE						0x06			//下注

#define MAX_SHAPE_COUNT                 15              //所有牌型种类
/********************************************************************************/

//游戏数据包
//#define SUPER_VERSION
/********************************************************************************/

//发送用户结果
struct tagUserResult
{
	//	BOOL bShowOnly;				//仅显示
	//BOOL bAddFlag;				//加倍标记
	BYTE bCountNotePeople;		//当前未放弃玩家数
	BYTE bAddTime;				//押注次数
	BYTE iNowBigNoteStyle;		//下注类型
	BYTE iNowBigPeople;
	BYTE iOutPeople;			//下注者
	BYTE iSplitStation;         //分牌位置
	int iNowBigNote;			//当前下注
	int iTotalNote;				//总下注
    int iUserStation[PLAY_COUNT] ;//玩家下注类型
	int iFirstOutPeople;         //第一位置玩家
	int iUserNote[PLAY_COUNT];   //用户本轮下注
	bool bSplit;                 //是否分牌

	
	//	int iCurNote;		//当前下注数
};
//看牌数据
struct ControlWinStruct
{
  BYTE     bWinStation;
  BYTE     bLoseStation;
 //  bool  ming[PLAY_COUNT];
};
//游戏状态数据包	（ 等待东家设置状态 ）

struct GameStation_1
{

	//游戏版本
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	
};

//游戏状态数据包	（ 等待其他玩家开始 ）
struct GameStation_2
{
	//游戏版本
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	//游戏信息
	//	BYTE				iBeginStation;					//开始位置
	//	BYTE				iEndStation;					//结束位置
	BYTE				iThinkTime;						//游戏盘数
	BYTE				iBeginTime;						//游戏盘数
	BYTE				iCallScoreTime;						//叫分计时
	BYTE				iXiaZhuTime;						//下注时间
	BYTE				iAllCardCount;						//扑克数目
	int					iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分
	__int64					iLimitNote[PLAY_COUNT];						//最高注
	int					iBaseNote;						//底注
	DWORD				iCardShape;						//牌型设置
	BYTE                bGameType;                      //游戏种类。1为同喜乐的，同喜乐下注为100整数
	BYTE                iGameNoteSetType;                //游戏筹码设置类型
	BOOL                bIsSuper;                        //是否可以使用配置器
};

//游戏状态数据包	（ 游戏正在发牌状态 ）
struct GameStation_3
{
	//游戏版本
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号

	//游戏信息
	BYTE				iThinkTime;						//游戏盘数
	BYTE				iBeginTime;						//游戏盘数
	BYTE				iAllCardCount;						//扑克数目
	BYTE				iBeenPlayGame;					//已经游戏的局数
	BYTE				iCallScoreTime;						//叫分计时
	BYTE				iXiaZhuTime;						//下注时间
	BYTE				iSysCardCount;					//还剩下牌数量
	//状态信息
	BYTE				iUserCardCount[PLAY_COUNT];				//用户手上的牌数
	BYTE				iUserCard[PLAY_COUNT][10];				//用户手上的牌
	BYTE				iUserCardCountSplit[PLAY_COUNT];				//用户手上的牌数
	BYTE				iUserCardSplit[PLAY_COUNT][10];				//用户手上的牌
	BYTE                iGameFlag;
	tagUserResult		tag;
	
	//运行状态变量

	int					iUpGradePeople;					//庄家位置
	int					iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分
	__int64					iLimitNote[PLAY_COUNT];						//最高注
	int					iBaseNote;						//底注

	__int64					iTotalNote[PLAY_COUNT];					//用户当前下注
	DWORD				iCardShape;						//牌型设置
	BYTE                bGameType;                      //游戏种类。1为同喜乐的，同喜乐下注为100整数
	BYTE                iGameNoteSetType;                //游戏筹码设置类型
	BOOL                bIsSuper;                        //是否可以使用配置器
	BOOL                bPlayer;                         //是否玩家
	
};

//游戏状态数据包	（ 游戏中状态 ）
struct GameStation_4	
{
	//游戏版本
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号

	//游戏信息
	//	BYTE				iBeginStation;					//开始位置

	BYTE				iThinkTime;						//游戏盘数
	BYTE				iBeginTime;						//游戏盘数
	BYTE				iAllCardCount;						//扑克数目
	BYTE				iBeenPlayGame;					//已经游戏的局数
	BYTE				SysCard[28];					//还剩下的牌
	BYTE				iSysCardCount;					//还剩下牌数量
	BYTE				iCallScoreTime;						//叫分计时
	BYTE				iXiaZhuTime;						//下注时间
	__int64					iLimitNote[PLAY_COUNT];						//最高注
	int					iBaseNote;						//底注
	int					iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分
	//运行状态变量
	int					iUpGradePeople;					//下注位置
	int					iOutCardPeople;					//现在出牌用户
	int					iFirstOutPeople;				//先出牌的用户
	__int64					iTotalNote[PLAY_COUNT];					//用户当前下注
	int                 iThisGameNote[PLAY_COUNT];			//本局游戏下注数(明注)
	int					iTotalGameNote[PLAY_COUNT];
	int					iUserStation[PLAY_COUNT];				//记录用户状态
	bool                bSplit;                      //是否有分牌
	BYTE                iSplitStation;               //所处牌的位置(分牌)
   //状态信息

	//	int					iIngNote;						//当前下注用户
	//	int					iIngPlayStatus;					//正在游戏的动作
	//	int					iUserNote[4];					//用户本轮下注总数
	//	int					iTotalNote;						//所下总注
	tagUserResult		tag;
	BYTE				iUserCardCount[PLAY_COUNT];				//用户手上的牌数
	BYTE				iUserCard[PLAY_COUNT][10];				//用户手上的牌
	BYTE				bBullCard[3];							//用户牛牌
	BYTE				iUserCardCountSplit[PLAY_COUNT];				//用户手上的牌数
	BYTE				iUserCardSplit[PLAY_COUNT][10];				//用户手上的牌
	DWORD				iCardShape;						//牌型设置
	BYTE                bGameType;                      //游戏种类。1为同喜乐的，同喜乐下注为100整数
	BYTE                iGameNoteSetType;                //游戏筹码设置类型
	BOOL                bIsSuper;                        //是否可以使用配置器
	BOOL                bPlayer;                         //是否玩家
	//	tagButtonStatus		ButtonPara;						//按钮状态
};

//游戏状态数据包	（ 等待下盘开始状态  ）
struct GameStation_5
{
	//游戏版本
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	int					iRoomBasePoint;					//房间倍数
	int					iRunPublish;					//逃跑扣分

	//游戏信息
	//	BYTE				iBeginStation;					//开始位置
	//	BYTE				iEndStation;					//结束位置
	BYTE				iThinkTime;						//游戏盘数
	BYTE				iBeginTime;						//游戏盘数
	BYTE				iAllCardCount;						//扑克数目
	BYTE				iCallScoreTime;						//叫分计时
	BYTE				iXiaZhuTime;						//下注时间
	//运行状态变量
	int					iUpGradePeople;					//庄家位置

	BYTE				iBeenPlayGame;					//已经游戏的局数
	DWORD				iCardShape;						//牌型设置
	BYTE                bGameType;                      //游戏种类。1为同喜乐的，同喜乐下注为100整数
	BYTE                iGameNoteSetType;                //游戏筹码设置类型
	BOOL                bIsSuper;                        //是否可以使用配置器
};

//用户同意游戏
struct UserArgeeGame
{
	BYTE				iBeginStation;					//开始位置
	BYTE				iEndStation;					//结束位置
	BYTE				iPlayCount;						//游戏盘数
	BYTE				iCardCount;						//扑克数目
};

//游戏开始
struct BeginUpgradeStruct
{
	BYTE				AllCardCount;					//一共使用的牌数
	int					iBaseNote;						//底注	
	__int64				iLimitNote[PLAY_COUNT];						//最大注数
	BYTE				SysCard[52];					//当前牌
	int                 iNt;                            //庄家

	//BYTE				iNtStation;						//现在的主牌
	//BYTE				iStation[2];					//主牌的位置
};
//收集筹码动画
struct CollectJetonStruct
{
	int JetonTotal;
	BYTE bDeskStation;
};
//发牌数据包
struct SendCardStruct
{
	BYTE				iCard;									//牌标号
	BYTE				bDeskStatin;							//新一轮出牌者
	bool                bIsSplit;                               //是否在分牌位置上发牌
	//	BYTE				bAddTime;								//押注次数
	//	BOOL				bEndFlag;								//结束标志
	//	SendCardStruct()
	//	{
	//		iOutPeople = 0;
	//		memset(iCard,0,sizeof(iCard));
	//		bAddTime=0;
	//		bEndFlag=FALSE;
	//	}
};
/// 发牌数据包，一次将扑克全部发给客户端
struct SendAllCardStruct
{
	BYTE      iStartPos;                  //发牌起始位置
	BYTE      iUserCard[PLAY_COUNT][5];   //用户扑克
	BYTE      iUserCardCount[PLAY_COUNT];

	SendAllCardStruct()
	{
		memset(iUserCard,0,sizeof(iUserCard));
		memset(iUserCardCount,0,sizeof(iUserCardCount));
		iStartPos = 255;
	}
};
/*
struct SendCardStruct
{
BYTE				iCard[4][2];							//牌标号
BYTE				iOutPeople;								//新一轮出牌者
BYTE				bAddTime;								//押注次数
BOOL				bEndFlag;								//结束标志
SendCardStruct()
{
iOutPeople = 0;
memset(iCard,0,sizeof(iCard));
bAddTime=0;
bEndFlag=FALSE;
}
};
*/

//游戏开始数据包
struct BeginPlayStruct
{
	BYTE				iOutDeskStation;				//出牌的位置
};

//用户出牌数据包 （发向服务器）
struct OutCardStruct
{
	int					iCardCount;						//扑克数目
	BYTE				iCardList[39];					//扑克信息
};



//用户出牌数据包 （发向客户端）
struct OutCardMsg
{
	int					iNextDeskStation;				//下一出牌者
	BYTE				iCardCount;						//扑克数目
	BYTE				bDeskStation;					//当前出牌者
	BYTE				iCardList[39];					//扑克信息
};



//游戏结束统计数据包
struct GameEndStruct
{
	int					iUserState[PLAY_COUNT];					//四家状态(提前放弃,还是梭)

	BYTE				iCardShape[PLAY_COUNT];
	__int64				iTurePoint[PLAY_COUNT];					//庄家得分
	__int64				iChangeMoney[8];
	BYTE				iUpGradeStation;				//庄家位置
	BYTE                iUpBullCard[PLAY_COUNT][3];      //升起的牌
	BYTE				iCardList[PLAY_COUNT][10];					//扑克信息
//	BYTE				iBackList[8];					//底牌扑克
};

//游戏结束统计数据包
struct GameCutStruct
{
	int					bDeskStation;					//退出位置
	__int64					iTurePoint[PLAY_COUNT];					//庄家得分
	__int64				iChangeMoney[8];
	BYTE                iQuitType;                     //退出类型
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
//叫分数据包
struct CallScoreStruct
{	
	BYTE				bDeskStation;							//当前叫分者
	int					iValue;									//叫分类型
	bool 				bCallScoreflag;								//叫分标记		
	bool               bPlayer;
};
/*
//按钮类型
enum BUTTON_TYPE
{
BUTTON_TYPE_NONE = -1,
BUTTON_TYPE_GIVEUP,//放弃
BUTTON_TYPE_100NOTE,//100注
BUTTON_TYPE_200NOTE,//200注
BUTTON_TYPE_400NOTE,//400注
BUTTON_TYPE_BULL,	//加注
BUTTON_TYPE_FOLLOW,//跟了
BUTTON_TYPE_SHUTTLE,//梭了
};*/

//用户处理信息
struct tagUserProcess
{
	BYTE iVrebType;//所处理的按钮
	__int64  iNote;		//下注数
	BYTE bUpCard[3];
};

//代替断线用户处理信息
struct SupersedeUserNote
{
	BYTE bDeskStation;//代替的位置
	BYTE iVrebType;//所处理的按钮
	int  iNote;		//下注数
};
//換底牌數據結果
struct ChangeBackStruct
{
	BYTE bDeskStation;//位置
	BYTE bSourceCard;//源牌
	BYTE bResultCard;//結果牌
	BOOL bExtVal;	//是否替換成功
};

//发送用户押注
struct NoteResult
{
	BYTE bAddStyle;		//下注类型
	BYTE iOutPeople;	//下注者
	__int64 iCurNote;		//当前玩家下注数
	BYTE NoHitStation;          //停牌位置
};
struct GameFinishNotify
{
	TCHAR name[PLAY_COUNT][21];
	int	iBasePoint;
	BYTE iStyle;			//游戏类型是否为强退,还是正常结束
	__int64	iWardPoint[PLAY_COUNT];
	//__int64 iTotalPoint[4];
	BYTE iCardShape[PLAY_COUNT];
	__int64 iMoney[PLAY_COUNT];
};
/*
//放弃结果数据
struct tagUserGiveUp
{
BOOL bShowOnly;		//仅显示
BOOL bAddFlag;	//加倍标记	
BYTE bAddTime;	//押注次数
BYTE bAddStyle;	//下注类型	
BYTE iGiveUpPeo;//放弃者
BYTE iOutPeople;//下注者
//	tagButtonStatus ButtonPara;//按钮参数
};
*/
/********************************************************************************/

// 数据包处理辅助标识

/********************************************************************************/

#define ASS_UG_USER_SET					50				//用户设置游戏
#define ASS_BEGIN_UPGRADE				51				//升级游戏开始
#define ASS_SEND_CARD					52				//发牌信息
#define ASS_SEND_FINISH					54				//发牌完成

#define ASS_CALL_SCORE					55				//叫分
#define ASS_CALL_SCORE_RESULT			56				//叫分结果
#define ASS_CALL_SCORE_FINISH			57				//叫分结束
#define ASS_REPLACE_CALL_SCORE			58				//代替叫分

#define ASS_GAME_PLAY					59				//开始游戏
#define ASS_SEND_ALLCARD				63				//发送所有的余牌
#define ASS_NEW_TURN					64				//新一轮开始
#define ASS_CONTINUE_END				65				//游戏结束
#define ASS_NO_CONTINUE_END				66				//游戏结束
#define ASS_CUT_END						67				//用户强行离开
#define ASS_SALE_END					68				//游戏安全结束
#define ASS_HAVE_THING					69
#define ASS_LEFT_RESULT					70
#define ASS_MESSAGE						71
#define ASS_STOP_THING					72
#define ASS_AGREE_STOP					73
#define ASS_NOMONEY                     75              //没有庄家.退出



#define ASS_SUPERSEDE_VREB_CHECK		78				//代替(断线)用户处理
#define ASS_VREB_CHECK					89				//用户处理

#define ASS_SHUTTLE						80				//梭了
#define ASS_FOLLOW						81				//跟了或不加
#define ASS_ADD_NOTE					82				//加注
#define ASS_SHOW_100					83				//押注100
#define ASS_SHOW_200					84				//押注200
#define ASS_SHOW_400					85				//押注400
#define ASS_GIVE_UP						86				//放弃
#define ASS_MODIFY_PLAY_NOTE			90				//更新用户所下注
#define ASS_NOTE						91				//下注
#define ASS_NOTE_RESULT					92				//下注结果
#define ASS_SEND_A_CARD					93				//新发一张牌
#define ASS_COLLECT_JETON				94				//收集筹码
#define ASS_CONTROL_WIN                 95              //控制输赢
#define ASS_GM_SUPERCLIENT				100				//超級客戶端
#define ASS_TAN_PAI						101				//摊牌消息发至客户端

/********************************************************************************/
#endif
