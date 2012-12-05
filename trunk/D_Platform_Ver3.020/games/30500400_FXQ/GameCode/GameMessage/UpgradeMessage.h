#pragma once

//同楼 普通版/视频版 编译  release/视频版  ，提牌器编译提牌器版

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

//文件名字定义
#define GAMENAME						TEXT("飞行棋")
//名字 ID
#define NAME_ID							30500400			
//支持类型
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
//游戏人数
#define PLAY_COUNT						4								
//版本定义
#define GAME_MAX_VER					1								//现在最高版本
#define GAME_LESS_VER					1								//现在最低版本
#define GAME_CHANGE_VER					0								//修改版本
//游戏内部开发版本号
#define DEV_HEIGHT_VERSION				1				//内部开发高版本号(每修正一次LOW_VERSIONG+1)
#define DEV_LOW_VERSION					0				//内部开发低版本号

static TCHAR szTempStr[MAX_PATH] = {0};//暂存字符串，用来获取 dll_name 等的时候使用
#define GET_CLIENT_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".ico"))
#define GET_SERVER_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".dll"))
#define GET_CLIENT_BCF_NAME(A)          (sprintf(A,"%d",NAME_ID),strcat(A,".bcf"))    

//游戏状态定义
#define GS_WAIT_SETGAME					0				//等待东家设置状态
#define GS_WAIT_ARGEE					1				//等待同意设置
#define GS_SEND_CARD					20				//发牌状态
#define GS_PLAY_GAME					22				//游戏中状态
#define GS_WAIT_NEXT					23				//等待下一盘开始 


///客户端和服务端的几种状态
#define     WAIT_PLAYER_DICE           50             ///等待玩家打色子                  
#define     WAIT_DICE_ANI              51             ///等待玩家色子动画
#define     WAIT_PLAYER_CHOISE         52             ///等待玩家选择走棋
#define     WAIT_PLANE_FLY_ANI         53             ///等待棋子飞行动画

const  int  PLAYER_PLANE_NUM  =  4 ;    /// 每个人有四架飞机
const  int  MAX_MAGIC_NUM     =  1 ;    ///玩家道具的最大种类（供以后扩展）
const  int  PUBLIC_PATH_STEP  =  52;    ///公共路径
const  int  PRIVATE_PATH_STEP =  6 ;    ///私有的位置
const  int  FINISH_PATH_STEP  =  56 ;   ///完成整个路径需要的步数
const  int  STEP_INTEVAL      =  13 ;   ///两家飞机之间的间隔
const  int  SHORTCUT_STEP_VALUE = 17 ;  ///玩家走捷径时的路径值 
const  int  SHORTCUT_OTHER_STEP  = 29 ; //飞行棋的另一边的位置
const  int  STEP_TAKEOFF        = 254 ; ///起飞位置定义
const  int  STEP_HOME           = 255 ; ///家的位置   
///定义棋子的几个方位
enum  enumSide
{
	emGreen = 0 ,       ///绿方
	emRed  = 1 ,        ///红方
	emYellow = 2 ,      ///黄方
	emBlue =  3 ,       ///蓝方
	emInvalidate = 255  ///不属于任何一方
};
///飞机的几种状态
enum enumPlaneState
{
	emStandby = 0,	     //在飞机场
	emTakeoff = 1,	     //起飞，在起飞的那个圈中
	emFlying = 2,	     //在飞
	emLanding = 3,	     //着陆，是指在最后的那五步棋上
	emStop = 4	,	     //飞机已停到中央
	emError = 255        //错误的状态
};
///魔法种类（暂时只有巧借东风）
enum  enumMagicType
{
	emWindMagic   = 1 ,    ///巧借东风
	emErrorMagic  = 255    ///错误的道具
};
///游戏中飞机的方向
enum enumDirection
{
	emLeft     = 0,    
	emLeftUp   = 1 ,
	emUp       = 2 , 
	emUpRight  = 3 ,
	emRight    = 4 ,
	emRightDown= 5 , 
	emDown     = 6,
	emDownLeft = 7 ,
	emErrorDir = 255   
};
///玩家飞机动作
enum  ActiveType
{
	emTakeOfFActive = 10 , // 起飞
	emFlyingActive  = 11 , //飞行
	emShortCutActive= 12 , //走了捷径
	emBackActive    = 13 , //后退
	emBackTakeOff   = 14 , //回到起飞状态
	emHomeActive    = 15 , //返回
	emArriveHome    = 16 , //完成任务 
	emMutiPlane     = 16 , //与别人的飞机迭机
	emErrorActive   = 255 
};
///飞机的数据
struct PLANE
{
	BYTE            emSide;		    //飞机属于哪一方的
	BYTE            emPlaneState;	//飞机状态
	BYTE            cbStep;		    //飞机所处的位置 (包括在着陆区的位置,是否在）									着陆区由cbPlaneState决定,着陆区只有四个值										01234)
	BYTE            cbAirPortPos;	//飞机在机场的位置(此位置初始化后不会变)
	BYTE            cbLandPos;		//着陆的位置
	PLANE()
	{
		memset(this , 0, sizeof(PLANE)) ; 
	}
	void Reset()
	{
		memset(this , 0 , sizeof(PLANE)) ;  
	}
};
///魔法的数据
struct MAGIC
{
	BYTE cbMagic;  ///魔法
	BYTE cbCount;  ///魔法的个数
};
// 每个棋子
struct STEP 
{
	enumDirection enPlaneDt;	        // 飞机在此格移动时的方向
	BYTE          cbSide;				// 属于哪一方的格子	`
	BYTE          cbMagic;				// 格子拥有什么样的魔法
	CPoint        ptPathPos ;          //格子的位置

	STEP()
	{
		cbSide = emInvalidate;
		cbMagic = emErrorMagic;
		enPlaneDt =	emErrorDir;
		ptPathPos.SetPoint(0 , 0 ) ; 
	}
};

//游戏状态数据包	（ 等待东家设置状态 ）
struct GameBaseStation
{
	BYTE				iVersion1;						//游戏版本号
	BYTE				iVersion2;						//游戏版本号

	bool                bUserReady[PLAY_COUNT] ;    ///玩家是否有准备

	bool                bUserAuto[PLAY_COUNT] ; 

	BYTE                cbBeginTime ;                  //开始时间
	BYTE                cbDiceTime  ;                  //打色子时间
	BYTE                cbThinkTime ;                 //大色子时间
};
///游戏进行中数据包
struct PlayingGameStation: GameBaseStation
{
	BYTE   cbOperater ;  ///当前操作的人
	BYTE   cbPropCount[PLAY_COUNT] ;  ///玩家的道具
	int    iPlayerfight[2] ;  ///玩家打掉别人飞机的数量
	PLANE  PlaneData[PLAY_COUNT][PLAYER_PLANE_NUM] ;  ///玩家的飞机状态
};
///等待下一家数据包
struct WaitNextGameStation: GameBaseStation
{

};
//游戏开始
struct BeginUpgradeStruct
{
	BYTE				iBeenPlayGame;			//已经玩了多少局
	BYTE				iPlayLimit;				//游戏总局数
};
///通知玩家更新打色子界面
struct WaitDiceStruct
{
	BYTE  cbDeskStation ; 
};
///玩家要求掷骰子
struct NotifyDiceStruct
{
	BYTE    cbDeskStation ;             ///发出
	BYTE    cbDiceValue ;              ///骰子值
	BYTE    cbPropCount ; 
};
///通知玩家选择飞机飞行
struct NotifyChoisePlane
{
	BYTE  cbDeskStation ; 
};
///玩家选择飞机
struct PlayerChoiseStruct
{
	BYTE  cbDeskStation ; 
    int   inDexPlane ; 
};
///玩家动作飞行过程中的动作结构体
struct PlaneFlyStruct
{
	BYTE     cbSide ;  ///谁家的飞机
    BYTE     cbIndex  ;       ///飞机的索引
	BYTE     cbOperateType ;   ///飞机的动作
	BYTE     cbComeByStepIndex[20] ; ///玩家走过的轨迹
	int      cbStepCount ;          ///飞机走过点的数量

	PlaneFlyStruct()
	{
		memset(this , 255 ,sizeof(PlaneFlyStruct)) ; 
		cbStepCount = 0 ;
	}
};
///玩家飞机飞行数据
struct PlayerActiveStruct
{
	BYTE            cbDeskStation ;          ///当前操作的玩家
	BYTE            cbDiceValue ;           ///当前打的色子点数
	int             iPlaneCount ;            ///有动作的飞机的个数
	int             iPlayerfight[2];         ///记录双方的战绩
	PlaneFlyStruct  PlaneActive[8] ;        ///需要有动作的飞机（应该不会超过8架吧）  
};
///更新玩家的飞机状态（同服务端保持一致）
struct  ScenceChangeStruct
{
	BYTE   cbDeskStation ; 
	PLANE  PlaneData[PLAY_COUNT][PLAYER_PLANE_NUM] ; 
};
///玩家道具通知服务端打色子
struct PropDiceStruct
{
	BYTE    cbDeskStaion ;       //使用道具的玩家
	BYTE    cbIndex ;            //道具索引
};

//托管数据结构
struct AutoStruct
{
	BYTE bDeskStation;	// 位置
	bool bAuto;			// 是否托管
	BYTE byAutoCount;	// 已经托管次数
};

//游戏结束统计数据包
struct GameEndStruct
{
	__int64				   iTurePoint[PLAY_COUNT];	  	  ///玩家得分
    __int64				   iChangeMoney[8];				  ///玩家金币
};

//游戏结束统计数据包
struct GameCutStruct
{
	int					bDeskStation;					//退出位置
	__int64				iTurePoint[PLAY_COUNT];					//庄家得分
	__int64				iChangeMoney[8];				//玩家金币

};


/********************************************************************************/

// 数据包处理辅助标识
//warning:79号ID预留给超级客户端,永不使用
/********************************************************************************/

#define  ASS_UG_USER_SET				50				//设置游戏
#define  ASS_GAME_BEGIN					51				//游戏开始
#define  ASS_APPLY_DICE                 52               //客户端请求打色子
#define  ASS_NOTIFY_DICE                53              //通知玩家打骰子
#define  ASS_NOTIFY_DICE_FINISH         54              //玩家打色子结束
#define  ASS_NOTIFY_CHOISE_PLANE        55             ///通知玩家选择飞机飞行
#define  ASS_PLAYER_CHOISE_PLANE        56              ///玩家选择走棋
#define  ASS_PLANE_FLY_ANI              57              ///通知客户端进行飞行动画
#define  ASS_PLANE_FLY_FINISH           58             ///服务端更新客户端飞行动画了
#define  ASS_DICE_PROP                  59            ///玩家打色子道具
#define  ASS_AUTO                       60 

#define  ASS_SUPER_MSG                  79              ///玩家超端设置

#define  ASS_SAFE_END                   83
#define  ASS_CONTINUE_END				84				//游戏结束
#define  ASS_NO_CONTINUE_END            85              //游戏直接退出
#define  ASS_CUT_END					86				//用户强行离开


/********************************************************************************/
#endif
