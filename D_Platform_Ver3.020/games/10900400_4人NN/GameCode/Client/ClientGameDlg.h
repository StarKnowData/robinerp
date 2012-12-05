#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "ClientView.h"
#include "LoveSendClassInExe.h"
#include "..\GameMessage\UpGradeLogic.h"
#ifdef SUPER_VERSION
#include "platform/CardSet.h"

#endif
#include "ControlWin.h"
//#include "MidiSample.h"

#define MAST_PEOPLE			-1							//是否为管理员
//消息定义
#define IDM_BEGIN			WM_USER+120					//开始按钮消息
//#define IDM_USER_NT		WM_USER+121					//用户反牌
//#define IDM_GIVE_BACK		WM_USER+123					//留底牌按钮
//#define IDM_OUT_CARD		WM_USER+124					//用户出牌
//#define IDM_LOOK_LAST		WM_USER+125					//看上轮扑克
//#define IDM_BACK_CARD		WM_USER+126					//底牌信息
#define IDM_HAVE_THING		WM_USER+127					//有事要走
#define IDM_SEND_THING		WM_USER+128					//发送离开请求
#define IDM_ARGEE_LEAVE		WM_USER+129					//同意离开消息
#define IDM_STOP			WM_USER+130					//提前结束按钮
#define IDM_STOP_THING		WM_USER+131					//发送提前结束
#define IDM_ARGEE_STOP		WM_USER+132					//同意提前结束

#define IDM_PASS			WM_USER+133					//不出按钮消息
#define IDM_CALL_SCORE		WM_USER+135					//叫分
#define IDM_AUTO			WM_USER+134					//托管消息
#define	IDM_ACTIVE_RESULT	WM_USER+136					//用户处理结果
#define IDM_SHOW_NOTE		WM_USER+137					//用户选择下注,加注
#define IDM_SELECT_NOTE_NUM	WM_USER+138					//用户下注
#define	IDM_SOUND			WM_USER+139					//用户设置声音
#define IDM_BGSOUND			WM_USER+140					//背景音乐
//定时器 ID
#define ID_BEGIN_TIME				100					//开始定时器
//#define ID_WAIT_ROB				101					//等待抢底牌
//#define ID_GIVE_BACK				102					//等待留底牌
#define ID_OUT_CARD					103					//出牌等待时间
#define ID_LOOK_BACK				105					//看暗牌
#define ID_CHANGE_MUSIC			    106					//换背景音乐
#define ID_NOTE                     110                 //等待闲家下注
#define ID_CALL_SCORE_TIME			107					//叫分定时器
//重置函数参数
#define RS_ALL_VIEW					1					//重置所有参数
#define RS_GAME_CUT					2					//用户离开重置
#define RS_GAME_END					3					//游戏结束重置
#define RS_GAME_BEGIN				4					//游戏开始重置


//游戏框架类 
class CClientGameDlg : public CLoveSendClassInExe//CLoveSendClassInExe//CGameFrameDlg
{
	//变量定义
public:
	//固定信息
	//=====================时间表信息===================
	BYTE					m_iThinkTime;				//最少游戏盘数
	BYTE					m_iBeginTime;				//游戏开始时间
	BYTE					m_iCallScoreTime;			//游戏开始时间
	BYTE					m_iXiaZhuTime;				//下注时间
	int						m_iRoomBasePoint;			//房间倍数
	int						m_iRunPublish;				//逃跑扣分
	int						m_iVersion;
	int						m_iVersion2;
	//	BYTE					m_iBeginStation;			//开始位置
	//	BYTE					m_iEndStation;				//结束位置
	BYTE					m_iCardCount;				//允许游戏的扑克数目
	BYTE					m_iPalyCardCount;			//游戏扑克数目
	__int64					m_iLimitNote[PLAY_COUNT];				//最大限额注
	__int64					m_iBaseNote;				//底注
	__int64					m_iThisTurnLimit;			//本轮限注
	//自己扑克数据
	//BYTE					m_iMeCardCount;				//自己扑克的数目
	//BYTE					m_iMeCardList[45];			//自己扑克列表
	//BYTE					m_iBackCard[8];				//底牌扑克
	//运行信息
	BYTE					m_DeskCard[PLAY_COUNT][10];			//每人桌面的扑克
	BYTE					m_iDeskCardCount[PLAY_COUNT];		//每人桌面扑克的数目
	BYTE					m_UserCard[PLAY_COUNT][10];			//用户扑克
	BYTE                    m_iUpBullCard[PLAY_COUNT][3];//升起的牛牌
	//运行信息
	BYTE				    	m_bCurrentOperationStation;		//現在叫分者
	BYTE						m_bTimeOutCount;			//超时
	BYTE						m_bShowAnimalStation;		//动画显示位置
	int					    	m_iNowOutPeople;			//现在出牌者
	int						    m_iFirstOutPeople;			//第一个出牌者
	int					    	m_iNowBigNote;				//当前最大押注数
	int						    m_iThisGameNote[PLAY_COUNT];			//本局游戏下注数(明注)
	int						    m_iTotalGameNote[PLAY_COUNT];			//本局游戏下注数(实际)
	int						    m_iUpGradePeople;					//庄家位置
	int                         m_iNote;                    //当前有效下注数即前位玩家有效下注数;
	BOOL						m_bBgSound;					//背景音乐
	int                         m_iAfterWaitAction;

	bool                        m_bAutoBull;                ///是否自动摆牛
	BYTE                        m_iSendAnimaCardPos;     ///发牌动画位置
	int                         m_iSendCardTotle;         ///发牌的张数
	BOOL                        m_bIsSuper;               ///是否超端
	CControlWin                 m_Control;
	BOOL                        m_bPlayer;                ///是否真实玩家，2011-8-17 因平台修改过程中玩家可以进入游戏所以中途坐上桌子的不算真实玩家
	//控件变量
public:
	CUpGradeGameLogic		m_Logic;					//升级逻辑
	CClientPlayView			m_PlayView;					//游戏视图
	//背景音乐
	HWND					m_hMciWnd1;						//背景音乐(出牌)
	HWND					m_hMciWnd2;						//背景音乐(场景)



#ifdef SUPER_VERSION
	CCardSet	*m_SetCard;
#endif
	//函数定义
public:
	//构造函数
	CClientGameDlg();
	//析构函数
	virtual ~CClientGameDlg();

	int GetGameStatus()
	{
		if(this)
			return GetStationParameter();
		else
			return 0;
	};

protected:
	//初始化函数
	virtual BOOL OnInitDialog();
	//数据绑定函数
	virtual void DoDataExchange(CDataExchange * pDX);
	virtual void OnWatchSetChange(void);
	virtual void OnGameSetting();
	//重载函数
public:
	//设置游戏状态
	virtual bool SetGameStation(void * pStationData, UINT uDataSize);
	//游戏消息处理函数
	virtual bool HandleGameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	//重新设置界面
	virtual void ResetGameFrame();
	//定时器消息
	virtual bool OnGameTimer(BYTE bDeskStation, UINT uTimeID, UINT uTimeCount);
	//清除所有定时器
	void KillAllTimer();
	//同意开始游戏 
	virtual bool OnControlHitBegin();
	//安全结束游戏
	virtual bool OnControlSafeFinish(){return false;};
	//用户离开
	virtual bool GameUserLeft(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);
     // 平台录影调用
	virtual void SetRecordView();

	BYTE GetNetUserPos(BYTE iDesk);

#ifdef VIDEO
	/// 为视频模块重载此函数
	virtual bool GameUserCome(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);
	virtual bool AFCCloseFrame();
#endif 

	//消息函数
public:
	//开始按钮函数
	LRESULT	OnHitBegin(WPARAM wparam, LPARAM lparam);

	//按动扑克按钮函数
	LRESULT	OnHitCard(WPARAM wparam, LPARAM lparam);
	//按动扑克按钮函数
	LRESULT	OnMouseMove(WPARAM wparam, LPARAM lparam);
	//按动扑克按钮函数
	LRESULT	OnMouseLeft(WPARAM wparam, LPARAM lparam);

	//按动出牌按钮函数
	//LRESULT	OnHitOutCard(WPARAM wparam, LPARAM lparam);
	//按动上轮按钮函数
	//LRESULT	OnHitLastTurn(WPARAM wparam, LPARAM lparam);
	//按动看底牌按钮函数
	//LRESULT	OnHitLookBack(WPARAM wparam, LPARAM lparam);
	//按动有事按钮函数
	LRESULT	OnHitHaveThing(WPARAM wparam, LPARAM lparam);
	//发送离开请求函数
	LRESULT	OnSendHaveThing(WPARAM wparam, LPARAM lparam);
	//用户请求离开
	LRESULT	OnArgeeUserLeft(WPARAM wparam, LPARAM lparam);
	//右键用牌
	//LRESULT	OnRightHitCard(WPARAM wparam, LPARAM lparam);
	//提前结束按钮
	LRESULT	OnStop(WPARAM wparam, LPARAM lparam);
	//发送提前结束
	LRESULT	OnStopThing(WPARAM wparam, LPARAM lparam);
	//同意提前结束
	LRESULT	OnAgreeStop(WPARAM wparam, LPARAM lparam);
	//不出按钮
	//LRESULT OnHitPass(WPARAM wparam, LPARAM lparam);
	//用户处理结果
	LRESULT OnHitActiveResult(WPARAM wparam, LPARAM lparam);
	//托管
	LRESULT OnHitAuto(WPARAM wparam,LPARAM lparam);
	//显示用户下注界面
	LRESULT OnShowNote(WPARAM wparam,LPARAM lparam);
	//用户下注消息
	LRESULT OnSelectNote(WPARAM wparam,LPARAM lparam);	
	//NT 按钮函数
	LRESULT	OnHitNt(WPARAM wparam, LPARAM lparam);
	//叫分
	LRESULT	OnCallScore(WPARAM wparam, LPARAM lparam);

	//发牌动画完成后显示各家牌
	LRESULT SendCardShowCard(WPARAM wparam,LPARAM lparam);
	//更新下注列表
	BOOL UpdateNtList();

	void ResetGameStation(int iGameStation);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT nIDEvent);
	//	afx_msg void OnClose();
protected:
	virtual void OnCancel();
	virtual BYTE ViewStation(BYTE bDeskStation);	//zxj 2009-11-21 打开注释
	//显示下注按钮,iAddNote表示本轮最大下注数.bTimes表示下注次数
	//	BOOL ShowHandAddNote(int iNowBigNote=0,BYTE bTimes=1,BYTE iNowBigNoteStyle=0,BOOL bExtVal=false);
	//设置声音
	//BOOL SetPlaySound(BYTE bSoundStyle,BOOL bExtVal=false);
	//函数声明
	BOOL CheckVersion(BYTE iVersion,BYTE iVersion2);
	//修改用户押注类型
	BOOL ModifyNote(BYTE iViewStation,int iCurNote,BOOL bExtVal=false);
	//设置押注声音
	//BOOL SetNoteSound(BYTE bNoteStyle,BOOL bIsBoy = true);
	//代替断线玩家下注
	BOOL UserSupersedeNote(BYTE bDeskStation);
	////出牌牌型声音設置
	//BOOL SetOutCardTypeSound(BYTE iCardList[],int iCardCount,BOOL IsBoy = true);
	////播放mp3声音
	//BOOL PlayOutCardType(TCHAR FileName[],HWND hmciwnd);
	////播入场景声音
	//BOOL SetSenceSound(BYTE iSenceSound = 0,BOOL IsBoy = TRUE,int iVal = -1);
public:
	//超級客戶端換底牌
	LRESULT ChangeBackCard();
	//換底牌結果
	BOOL ChangeBackCardResult(BYTE bDeskStation,BYTE bSourceBackCard,BYTE bResultCard,BOOL bExtVal=false);
	//換系統牌
	BOOL ReplaceCard(BYTE iTotalCard[],int iSendCardPos,int iEndPos,BYTE bSourceCard,BYTE bResultCard);
public:
	
	//去掉所有指示牌标示
	void DelShowThis();
	//隐藏叫庄按钮
	BOOL HideButton();
	//叫分
	void ShowCallScoreBt(int CallScore,BOOL bExtVol=false);
};
