#include "IGameImpl.h"
#include "..\GameMessage\UpGradeLogic.h"
#include "PlaneMoveAni.h"

#include <irrKlang.h>

using namespace irrklang;


const  int  TIME_GAME_BEGIN    = 200 ;    ///游戏开始定时器
const  int  TIME_PLAYER_DICE   = 201 ;   ///玩家打骰子
const  int  TIME_DICE_FINISH   = 202 ;  ///玩家打色子动画结束
const  int  TIME_PLAYER_CHOISE = 203 ; ///玩家选择飞机
const  int  TIME_AIM_AT_PLANE  = 204 ; //指向飞机的动画
const  int  TIME_PLANE_FLY     = 205 ;  ///飞机起飞动画
const  int  TIME_CURSOR_ANI    = 300 ;    //玩家光标旋转定时器

const  int   MAX_ANI_PLANE     = 8 ;  ///最多8架飞机



///游戏中的音效ID
const   int   PLANE_ARRIVE   = 0x10 ;  //飞机到达
const   int   BOMB_SOUND     = 0x11 ;  //飞机爆炸
const   int   DICE_ROLL      = 0x12 ;  //色子滚动
const   int   PLANE_FLY      = 0x13 ; //飞机飞行
const   int   PLANE_TAKEOFF  = 0x14 ;  //飞机起飞
const   int   TIME_OUT       = 0x15 ; ///时间到
const   int   WIND_SOUND     = 0x16 ;  //风
const   int   AIM_AT_PLANE   = 0x17 ; //瞄准 
const   int   ARRIVE_HOME    = 0x18 ; //成功回家

const   int   SOUND_WIN      = 0x20 ; // 胜利
const   int   SOUND_LOST     = 0x21 ; ///失败

const   int   GAME_BG_SOUND  = 0x30 ; //游戏背景音效


#define GetControlNode(A ,IControl , IControlID ) \
	IControl *A=  dynamic_cast<IControl *>(m_pUI->GetIControlbyID(IControlID)); \
	if (NULL != A) \
	A


interface IGameFrame;
interface IUserInterface;
class CNewGameClient : public IGameImpl
{
public:
    CNewGameClient(IGameFrame *pGameFrame, IUserInterface *pUI);
    virtual ~CNewGameClient();
private:
    CNewGameClient(const CNewGameClient &other);
    CNewGameClient &operator = (const CNewGameClient &other);

private:
	///框架游戏指针
	IGameFrame            *m_pGameFrame;
	///界面游戏指针
	IUserInterface        *m_pUI;

	ISoundEngine           *m_SoundEngine;               ///游戏音效

	ISoundEngine           *m_SoundEnginBg ;              ///背景音效
public: 


	CUpGradeGameLogic      m_ClientLogic ;                 ///客户端逻辑类
	BYTE                   m_bGameStation ;                ///当前的游戏状态

	int                    m_iMyDeskStation ;              ///玩家自己的游戏位子
	BYTE                   m_cbOperater ;                 ///当前操作的人
	BYTE                   m_cbCurrentStation ;             ///当前的游戏状态
	BYTE                   m_cbDiceFrame ;               ///当前骰子滚动到了那一帧
  
	///时间列表
	BYTE					m_iBeginTime;		           ///游戏开始时间
	BYTE                    m_iDiceTime ;                 ///游戏中打色子时间
	BYTE					m_iThinkTime;		           ///最少游戏盘数

	PATH                    m_BasePath ;                  ///游戏基本路径

	CPoint                  m_ptBasePoint ;               ///游戏基准点

	CPlaneMoveAni           m_planeAni[8] ;               ///飞机动画(最多八架飞机一起有动画)

	CPlaneMoveAni           m_bombAni ;                   ///瞄准动画

	BYTE                    m_cbDiceValue ;                ///当前色子的点数

	GameScence              m_GameScene ;                  ///游戏场景

	BYTE                    m_iPropCount[PLAY_COUNT] ;    ///玩家巧借东风数量

	int                     m_iPlayerfight[2] ;  ///玩家战绩

	int                     m_iAniPlaneCount ;        ///动画飞机的个数

	bool                    m_bReady[PLAY_COUNT] ;   ///显示玩家准备图标

	bool                    m_bAutoOutCard[PLAY_COUNT];              ///是否为托管出牌 ,只在客户端做托管   

	BYTE                    m_bAutoOutTime ;           ///玩家超时次数

	bool                    m_bSoundPlay ;  //是否可以播放声音

	bool                    m_bSoundBgPlay ;  //背景音效

	bool                    m_bAllowWatch ; // 是否允许旁观

	CString                 m_strCoinName ;   ///游戏中的金币

	bool                    m_bWatchStation;  ///是否是旁观状态


public:
    /// 初始化
    virtual int Initial();
    /// 初始化UI
    virtual int InitUI();
    /// 游戏消息
    virtual int HandleGameMessage(WORD nMainID,WORD nSubId,BYTE * buffer,int nLen);
    /// 界面消息
    virtual int OnUIMessage(TUIMessage* pMessage);
    /// 重新设置状态
    virtual int ResetGameFrame(void);
    /// 玩家进入
    virtual int GameUserCome(void);
    /// 玩家离开
    virtual int GameUserLeft(int nIndex);
    /// 玩家断线
    virtual int GameUserOffLine(void);
    // 是否正在游戏，由游戏实现
    // 旁观玩家返回false，游戏玩家正在游戏中返回true，其它状态返回false
    virtual bool IsPlayingGame();          
    /// 定时器消息
    virtual void OnTimer(int nTimerID);
    /// 置状态
    virtual void SetStationParameter(BYTE bGameStation);
    ///设置游戏状态
	virtual BYTE GetStationParameter();
	///游戏结束
	virtual bool OnGameQuiting();

public:
	///初始化数据
	void  ResetScenceData(void) ; 
	///玩家进入游戏
	void  SetGameStation(void * pBuffer,int nLen);
	///杀掉所有定时器
	void  KillAllGameTime(void) ; 
	///显示或隐藏开始倒计时时钟
	void  ShowOrHideUserTime(BYTE bDeskStation,int nShowMaxNum,int nShowMinNum,bool bFlag) ;

	///隐藏所有定时器
	void  HideAllTime(void) ;
	///设置游戏基本底图数据
	void  SetBaseImage(void) ; 
	///绘制当前的飞机情况
	void  DrawPlayerPlane(BYTE bDeskStation , bool bShow) ; 
	///绘制瞄准
	void  DrawAimBombAni(bool bShow) ; 
	///播放炸弹动画
	void  DrawBmobAni(bool bPlay) ; 
	///绘制飞机动画
	void  DrawPlaneAni(void) ; 
    ///设置当前的鼠标形状
	void  SetCurrentCursor(int iSrcPos);
	///处理服务端发过来的开始消息
	bool  OnSCBeginMessage(BeginUpgradeStruct *pBeginData); 
	///处理服务端发过来的更新玩家要求打色子界面
	bool  OnSCWaitDiceMessage(WaitDiceStruct *pWaiData) ;
	///处理服务端发过来的打色子信息
	bool  OnSCDiceMessage(NotifyDiceStruct *pDiceDate) ; 
	///处理服务端发来的处理选择飞机的消息
	bool  OnSCChoisePlaneMessage(NotifyChoisePlane *pChoiseData) ; 
	///处理服务端发来的
	bool  OnSCPlaneFlyMessage(PlayerActiveStruct *pActiveData) ; 
	///完成飞行任务（实际是和服务端校对数据）
	bool  OnSCPlaneFlyFinish(ScenceChangeStruct *pScenceChange) ; 
	///游戏结束
	bool  OnSCGameFinish(GameEndStruct *pGameEnd) ; 
    ///游戏强行结束
	bool  OnSCGameCutFinish(GameCutStruct *pCutEnd) ;
	///播放色子动画
	void  PlayDiceAni(BYTE bDeskStation , bool bPlay , bool  bShow) ; 
    ///播放区域高亮状态
	void  PlayHihtLightAni(bool bPlay ,bool bShow) ;
	///显示玩家准备图标
	void  ShowReadyLogo(bool bShow) ; 
	///显示玩家道具图标
	void  ShowPlayerPropLogo(bool bshow) ; 
	///显示目的地图片
	void  ShowDestineImg(int  cbStep  ,BYTE inDex , bool bShow) ; 
	///显示玩家的战绩
	void  ShowFightScore(bool bShow) ; 
	///显示游戏结束
	void  ShowGameFinish(bool  bShow) ;


	///显示托管标识
	void  ShowAutoOutCard(bool bShow) ;
   ///设置用户托管状态
	void  SetAutoStation(BYTE bDeskStation,bool bAtuoOrCancel)  ;
	///用户托管打色子
	void  UserAutoDice(void) ; 
	///用户托管选择棋子
	void  UserAutoChoisePlane(void) ;
	///玩家设置游戏信息
	int   UserSetGameInfo(bool bSoundEnable,bool bSoundBgEnable ,bool bWatchEnable,bool bShow) ;
	///游戏中的音效
	void  SetPlaySound(BYTE iDeskStation,int SoundID, bool bISLoop) ;
   ///游戏中的背景音效
	void  SetGameBgSound(int SoundID, bool bISLoop) ;

		 
};