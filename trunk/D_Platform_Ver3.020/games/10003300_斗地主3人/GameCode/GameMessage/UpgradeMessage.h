#pragma once

//同楼 普通版/视频版 编译  release/视频版  ，提牌器编译提牌器版

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

//文件名字定义
#define GAMENAME						TEXT("斗地主")

#ifdef SSYJ //谁是赢家
#ifdef VIDEO
#define NAME_ID							10000305								//名字 ID
#else
#define NAME_ID							10000300								//名字 ID
#endif
#else
#ifdef VIDEO
#define NAME_ID							10003305								//名字 ID
#else
#define NAME_ID							10003300								//名字 ID
#endif
#endif


//版本定义
#define GAME_MAX_VER					1								//现在最高版本
#define GAME_LESS_VER					1								//现在最低版本
#define GAME_CHANGE_VER					0								//修改版本

//支持类型
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
//游戏信息

#define PLAY_COUNT						3								//游戏人数


//游戏内部开发版本号
#define DEV_HEIGHT_VERSION				2				//内部开发高版本号(每修正一次LOW_VERSIONG+1)
#define DEV_LOW_VERSION					0				//内部开发低版本号

//#define SKIN_FOLDER						TEXT("ddz")	//图片文件夹
//#define SKIN							TEXT("cardskin1")	//两套图片中用一套
#define SKIN_CARD						TEXT(".\\image\\cardskin")		//共用图片文件夹
static TCHAR szTempStr[MAX_PATH] = {0};//暂存字符串，用来获取 dll_name 等的时候使用
#define GET_CLIENT_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".ico"))
#define GET_SERVER_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".dll"))

#define GET_CLIENT_BCF_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".bcf"))

//游戏状态定义
#define GS_WAIT_SETGAME					0				//等待东家设置状态
#define GS_WAIT_ARGEE					1				//等待同意设置
#define GS_SEND_CARD					20				//发牌状态
#define GS_WAIT_BACK					21				//等待扣压底牌
#define GS_PLAY_GAME					22				//游戏中状态
#define GS_WAIT_NEXT					23				//等待下一盘开始 

#define GS_FLAG_NORMAL					0				//正常情况
#define GS_FLAG_CALL_SCORE				1				//叫分
#define GS_FLAG_ROB_NT					2				//抢地主
#define GS_FLAG_ADD_DOUBLE				3				//加棒
#define GS_FLAG_SHOW_CARD				4				//亮牌
/********************************************************************************/
//游戏数据包

/********************************************************************************/
//用户出牌数据包 （发向服务器）
struct OutCardStruct
{
	int					iCardCount;						//扑克数目
	BYTE				iCardList[45];					//扑克信息
};

//代替玩家出牌
struct ReplaceOutCardStruct
{
	BYTE				bDeskStation;					//代替出牌的位置
	int					iCardCount;						//扑克数目
	BYTE				iCardList[45];					//扑克信息
};

//用户出牌数据包 （发向客户端）
struct OutCardMsg
{
	int					iNextDeskStation;				//下一出牌者
	BYTE				iCardCount;						//扑克数目
	BYTE				bDeskStation;					//当前出牌者	
	BYTE				iCardList[45];					//扑克信息
};
//新一轮
struct NewTurnStruct
{
	BYTE				bDeskStation;					//坐号
	BYTE				bReserve;						//保留
};
//游戏状态数据包	（ 等待东家设置状态 ）
struct GameStation_1
{
	//游戏版本
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	//游戏信息
};

//游戏状态数据包	（ 等待其他玩家开始 ）
struct GameStation_2
{
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	//游戏信息
	BYTE				iPlayCard;						//扑克数目
	UINT				iPlayCount;						//使用的牌数(54,108,162,216,324)
	BYTE				iBackCount;						//底牌数
	BYTE				iBeginNt;						//开始位置
	BYTE				iEndNt;							//结束位置
	BOOL				bTwoIsNt;						//2是否为常主
	BOOL				bHaveKing;						//是否有王
	BOOL				bKingCanReplace;				//王是否可当
	DWORD				iCardShape;						//牌型设置
	//辅助
	BYTE				iBeginTime;						//开始准备时间
	BYTE				iThinkTime;						//出牌思考时间
	BYTE				iGiveBackTime;					//留底时间
	BYTE				iCallScoreTime;					//叫分计时
	BYTE				iAddDoubleTime;					//加棒时间
	BYTE				iPlayLimit;						//游戏轮数
	//游戏倍数
	UINT				iDeskBasePoint;					//桌面基础分
	UINT				iRoomBasePoint;					//房间倍数
	__int64				iRunPublish;					//逃跑扣分
	bool				bTurnRule;						//打牌顺序
};


//游戏状态数据包	（ 等待扣押底牌状态 ）
struct GameStation_3
{
	BYTE				iVersion;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号
	BYTE				iPlayCard;						//扑克数目	
	BYTE				iBackCount;						//底牌数
	BYTE				iBeginNt;						//开始位置
	BYTE				iEndNt;							//结束位置
	BOOL				bTwoIsNt;						//2是否为常主
	BOOL				bHaveKing;						//是否有王
	BOOL				bKingCanReplace;				//王是否可当
	BYTE				iBeginTime;						//开始准备时间
	BYTE				iThinkTime;						//出牌思考时间
	BYTE				iGiveBackTime;					//留底时间
	BYTE				iCallScoreTime;					//叫分计时
	BYTE				iAddDoubleTime;					//加棒时间
	BYTE				iPlayLimit;						//游戏轮数
	BYTE				iBeenPlayGame;					//已经游戏的局数
	BYTE				iCallScorePeople;				//当前叫分人
	BYTE				iGameFlag;						//叫分标记
	BYTE				iCallScoreResult;				//所叫的分
	
	int					iUpGradePeople;					//庄家位置
	int					iBase;							//当前炸弹个数
	__int64				iRunPublish;					//逃跑扣分
	
	UINT				iDeskBasePoint;					//桌面基础分
	UINT				iRoomBasePoint;					//房间倍数
	UINT				iPlayCount;						//使用的牌数(54,108,162,216,324)
	DWORD				iCardShape;						//牌型设置

	bool				bAuto[PLAY_COUNT];				//托管情况
	bool				bCanleave[PLAY_COUNT];			//能否点退出

	BYTE				iCallScore[PLAY_COUNT];			//几家叫分情况
	BYTE				iRobNT[PLAY_COUNT];				//抢地主
	BYTE				iUserCardCount[PLAY_COUNT];		//用户手上扑克数目
	BYTE				iUserCardList[195];				//用户手上的扑克
	BYTE				byUserChui[PLAY_COUNT];			//记录玩家是否加锤 1:未知状态,0:不锤,2:锤
	bool				bTurnRule;						//打牌顺序
};

//游戏状态数据包	（ 游戏中状态 ）
struct GameStation_4	
{
	
	bool				bIsLastCard;						//是否有上轮数据
	
	BOOL				bTwoIsNt;							//2是否为常主
	BOOL				bHaveKing;							//是否有王
	BOOL				bKingCanReplace;					//王是否可当

	BYTE				iVersion;							//游戏版本号
	BYTE				iVersion2;							//游戏版本号
	BYTE				iPlayCard;							//扑克数目
	BYTE				iBackCount;							//底牌数
	BYTE				iBeginNt;							//开始位置
	BYTE				iEndNt;								//结束位置
	BYTE				iBeginTime;							//开始准备时间
	BYTE				iThinkTime;							//出牌思考时间
	BYTE				iGiveBackTime;						//留底时间
	BYTE				iCallScoreTime;						//叫分计时
	BYTE				iAddDoubleTime;						//加棒时间
	BYTE				iBeenPlayGame;						//已经游戏的局数
	BYTE				iPlayLimit;							//游戏轮数
	BYTE				iBaseOutCount;						//出牌的数目
	BYTE				bIsPass;							//是否不出

	int					iRunPublish;						//逃跑扣分	
	int					iBase;								//当前炸弹个数
	int					iUpGradePeople;						//庄家位置
	int					iBackCardCount;						//底牌数量
	int 				iCallScoreResult;					//叫分结果
	int					iOutCardPeople;						//现在出牌用户
	int					iFirstOutPeople;					//先出牌的用户
	int					iBigOutPeople;						//先出牌的用户

	UINT				iDeskBasePoint;						//桌面基础分
	UINT				iRoomBasePoint;						//房间倍数
	UINT				iPlayCount;							//使用的牌数(54,108,162,216,324)
	
	DWORD				iCardShape;							//牌型设置
	bool				bAuto[PLAY_COUNT];					//托管情况
	bool				bCanleave[PLAY_COUNT];				//能否点退出
	BYTE				iUserCardCount[PLAY_COUNT];			//用户手上扑克数目
	BYTE				iDeskCardCount[PLAY_COUNT];			//桌面扑克的数目
	BYTE				iAwardPoint[PLAY_COUNT];			//奖分
	BYTE				iPeopleBase[PLAY_COUNT];			//加棒
	BYTE				iRobNT[PLAY_COUNT];					//抢地主
	BYTE				iLastCardCount[PLAY_COUNT];			//上轮扑克的数目
	BYTE				iLastOutCard[PLAY_COUNT][45];		//上轮的扑克
	BYTE				iUserCardList[195];					//用户手上的扑克
	int                 iHistroyInfoData[20] ;              ///历史出牌信息
	BYTE				byUserChui[PLAY_COUNT];				//记录玩家是否加锤 1:未知状态,0:不锤,2:锤
	bool				bTurnRule;						//打牌顺序
};

//游戏状态数据包	（ 等待下盘开始状态  ）
struct GameStation_5
{
	BYTE				iVersion;							//游戏版本号
	BYTE				iVersion2;							//游戏版本号
	//游戏信息
	BYTE				iPlayCard;							//扑克数目
	UINT				iPlayCount;							//使用的牌数(54,108,162,216,324)
	BYTE				iBackCount;							//底牌数
	BYTE				iBeginNt;							//开始位置
	BYTE				iEndNt;								//结束位置
	bool				bTwoIsNt;							//2是否为常主
	bool				bHaveKing;							//是否有王
	DWORD				iCardShape;							//牌型设置
	//辅助
	BYTE				iBeginTime;							//开始准备时间
	BYTE				iThinkTime;							//出牌思考时间
	BYTE				iGiveBackTime;						//留底时间
	BYTE				iCallScoreTime;						//叫分计时
	BYTE				iAddDoubleTime;						//加棒时间
	BYTE				iPlayLimit;							//游戏轮数
	//游戏倍数
	UINT				iDeskBasePoint;						//桌面基础分
	UINT				iRoomBasePoint;						//房间倍数
	__int64				iRunPublish;						//逃跑扣分
	bool				bTurnRule;							//打牌顺序
};

//用户同意游戏
struct UserArgeeGame
{
	BYTE				iPlayCount;							//游戏盘数
	BYTE				iCardCount;							//扑克数目
};

//游戏开始
struct BeginUpgradeStruct
{
	BYTE				iUpgradeStation;					//庄家位置
	BYTE				iPlayLimit;							//游戏总局数
	BYTE				iBeenPlayGame;						//已经玩了多少局

};
//游戏准备数据包
struct PrepareStruct
{
	BYTE				bCard;								//明牌
	BOOL                bUserVip ;                          ///玩家是否为Vip   
};
//发牌数据包
struct SendCardStruct
{
	BYTE				bDeskStation;							//玩家
	BYTE				bCard;									//牌标号
};

//發送所有牌數據
struct SendAllStruct
{
	BYTE iUserCardCount[PLAY_COUNT];										//发牌数量
	BYTE iUserCardList[108];									//发牌队例
};
//发牌结束
struct SendCardFinishStruct
{
	BYTE		bReserve;									
};


//底牌数据包
struct BackCardStruct
{
	BYTE				bDeskStation;					//庄家位置
	BYTE				iBackCardCount;					//扑克数目
	BYTE				iBackCard[12];					//底牌数据
};

//底牌数据包
struct BackCardExStruct
{
	BYTE				iGiveBackPeople;				//底牌玩家
	BYTE				iBackCardCount;					//扑克数目
	BYTE				iBackCard[12];					//底牌数据
};


//游戏开始数据包
struct BeginPlayStruct
{
	BYTE				iOutDeskStation;				//出牌的位置
};


//用户甩牌失败数据包 （发向客户端）
struct OutShowCardStruct
{
	BYTE				iCardCount;						//扑克数目
	BYTE				bDeskStation;					//当前出牌者
	BYTE				iResultCount;					//结果扑克数目
	BYTE				iCardList[78];					//扑克信息
};

//代替开始
struct ReplaceAgreeStruct
{
	BYTE bDeskStation;									
};

//叫分数据包
struct CallScoreStruct
{	
	BYTE				bDeskStation;							//当前叫分者
	int					iValue;									//叫分类型
	bool 				bCallScoreflag;							//叫分标记								
};
//抢地主
struct RobNTStruct
{
	BYTE bDeskStation;										//抢地主坐号
	int iValue;												//抢地主情况
};

//明牌
struct ShowCardStruct
{
	BYTE bDeskStation;										//坐号
	BYTE iCardList[54];					//扑克信息
	BYTE iCardCount;						//扑克数目
	int iValue;											//保留
	int iBase;												//倍数 20081204
};

//代替亮牌
struct ReplaceShowCardStruct
{
	BYTE bDeskStation;										//坐号
	BYTE bRepDeskStation;									//代替位置
	int iValue;												//保留
};
//加棒
struct AddDoubleStruct
{
	BYTE bDeskStation;										//加棒位置
	int iValue;												//加棒情况
};

//代替叫分数据包
struct ReplaceCallScoreStruct
{	
	BYTE		bDeskStation;								//代替叫分者
	int		    NowCallScorePeople;							//当前叫分者
	int			CallScore;									//叫分类型
	bool 		CallScoreFlag;								//叫分标记								
};

//奖分
struct AwardPointStruct
{
	BYTE	iAwardPoint;									//奖分
	BYTE	bDeskStation;									//坐号
	int		iBase;											//倍数
};

//托管数据结构
struct AutoStruct
{
	BYTE bDeskStation;
	bool bAuto;
};
///玩家是否为Vip
struct VipDataStruct
{
	BYTE  bDeskStation ; 
	BOOL  bVipUser ; 
};
//机器人托管
struct UseAIStation
{
	BYTE bDeskStation;					//坐号
	BOOL bState;						//状态
};

//冠军结果
struct ChampionStruct
{
	BYTE bDeskStation ;
};

//用户出牌数据包 （发向客户端）
struct BatchOutCardMsg
{
	BYTE				iCardCount;						//扑克数目
	BYTE				iCardList[156];					//扑克信息
};

////道俱
//struct PropStruct
//{
//	BYTE				sendDeskStation;				//发放位置
//	BYTE				recvDeskStation;				//接收位置
//	int					iValue;
//};
//游戏结束统计数据包
struct GameEndStruct
{
	int					iBasePoint;						//游戏倍数
	__int64				iTurePoint[PLAY_COUNT];			//玩家得分
	__int64				iInitScore[PLAY_COUNT];			//未经过系统加分后的得分
	__int64				iChangeMoney[8];				//玩家金币
	BYTE				iUpGradeStation;				//庄家位置
	BYTE				iCallScore;						//庄家叫分
	BYTE				iRobMul;						//抢地主亮牌倍数
	BYTE				iOutCardMul;					//出牌加倍
	BYTE				iBombMul;						//炸弹加倍
	BYTE				iTotalMul;						//总倍数

	BYTE			    iUserCardCount[PLAY_COUNT];	    //用户手上扑克数目
	BYTE			    iUserCard[PLAY_COUNT][45];		//用户手上的扑克

};

//游戏结束统计数据包
struct GameCutStruct
{
	int					iRoomBasePoint;					//倍数
	int					iDeskBasePoint;					//桌面倍数
	int					iHumanBasePoint;				//人头倍数

	int					bDeskStation;					//退出位置
	__int64				iChangeMoney[8];				//玩家金币
	__int64				iTurePoint[PLAY_COUNT];			//庄家得分

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

//游戏结算
struct GameFinishNotify
{
	TCHAR name[PLAY_COUNT][61];
	//	int	iBasePoint;
	BYTE iStyle;			//游戏类型是否为强退,还是正常结束
	int	iBasePoint;			//系统基数
	int	iDeskBasePoint;		//桌面基础分
	int iUpGradePeople;		//莊家
	int iGrade2;			//莊家盟友
	__int64	iWardPoint[PLAY_COUNT];
	__int64 iAwardPoint[PLAY_COUNT];	//讨赏
	__int64 iTotalScore[PLAY_COUNT];	//总积分
	__int64 iMoney[PLAY_COUNT];			//比赛所留钱数
	BYTE iGameStyle;					//游戏类型
};
struct UserleftDesk
{
	BYTE bDeskStation;                //断线玩家
};

//锤消息
struct ChuiStruct
{
	BYTE bDeskStation;				//锤位置
	bool bIsChui;					//是否锤
	int	 iFee;						//锤一锤费用

	ChuiStruct()
	{
		memset(this,0,sizeof(ChuiStruct));
	}
};
/********************************************************************************/

// 数据包处理辅助标识
//warning:79号ID预留给超级客户端,永不使用
/********************************************************************************/
#define ASS_UG_USER_SET					50				//设置游戏
#define ASS_GAME_BEGIN					51				//游戏开始
#define ASS_GAME_PREPARE				52				//准备工作

#define ASS_SEND_CARD					53				//发牌信息
#define ASS_SEND_CARD_MSG				54				//发牌过程中处理消息
#define ASS_SEND_ALL_CARD				55				//发送所有牌(一下发放全部)
#define ASS_SEND_FINISH					56				//发牌完成

#define ASS_CALL_SCORE					57				//叫分
#define ASS_CALL_SCORE_RESULT			58				//叫分结果
#define ASS_CALL_SCORE_FINISH			59				//叫分结束
#define ASS_REPLACE_CALL_SCORE			60				//代替叫分

#define ASS_ROB_NT						61				//抢地主
#define ASS_ROB_NT_RESULT				62				//抢地主结果
#define ASS_REPLACE_ROB_NT				63				//代替抢地主
#define ASS_GAME_MULTIPLE				64				//游戏倍数(抢地主后会加倍)
#define ASS_ROB_NT_FINISH				65				//抢地主结果


#define ASS_BACK_CARD					66				//底牌数据
#define ASS_BACK_CARD_EX				67				//扩展底牌数据(其他玩家可见)

#define ASS_ADD_DOUBLE					68				//加棒
#define ASS_ADD_DOUBLE_RESULT			69				//加棒结果
#define ASS_REPLACE_ADD_DOUBLE			70				//代替加棒
#define ASS_ADD_DOUBLE_FINISH			71				//加棒结束

#define ASS_SHOW_CARD					72				//亮牌
#define ASS_SHOW_CARD_RESULT			73				//亮牌结果
#define ASS_REPLACE_SHOW_CARD			74				//代替亮牌
#define ASS_SHOW_CARD_FINISH			75				//亮牌结束

#define ASS_GAME_PLAY					76				//开始游戏
#define ASS_OUT_CARD					77				//用户出牌
#define ASS_OUT_CARD_RESULT				78				//出牌結果
#define ASS_REPLACE_OUT_CARD			80				//代替出牌(79留给超级客户端发牌器)

#define ASS_ONE_TURN_OVER				81				//一轮完成(使客户端上一轮可用)
#define ASS_NEW_TURN					82				//新一轮开始
#define ASS_AWARD_POINT					83				//奖分(炸弹火箭)


#define ASS_CONTINUE_END				84				//游戏结束
#define ASS_NO_CONTINUE_END				85				//游戏结束
#define ASS_NO_CALL_SCORE_END			86				//无人叫分
#define ASS_CUT_END						87				//用户强行离开
#define ASS_SAFE_END					88				//游戏安全结束
#define ASS_TERMINATE_END				89				//意外结束
#define ASS_AHEAD_END					90				//提前结束

#define ASS_AUTO						91				//用户托管
#define ASS_HAVE_THING					92				//有事
#define ASS_LEFT_RESULT					93				//有事离开结果
#define ASS_MESSAGE						94				//文字消息
#define ASS_AI_STATION					95				//机器人托管(断线户用)
#define ASS_REPLACE_GM_AGREE_GAME		96				//代替玩家开始
#define ASS_USER_LEFTDESK               97               //玩家离开桌子或断线
#define ASS_USER_VIP_VERTIFY            98             ///玩家是否是VIP验证
#define ASS_CHUI						99				//锤
#define ASS_CHUI_RESULT					100				//锤结果

//#define ASS_PROP						200				//道俱

/********************************************************************************/
#endif
