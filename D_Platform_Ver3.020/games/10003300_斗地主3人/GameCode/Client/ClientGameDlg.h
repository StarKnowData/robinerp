#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "ClientView.h"
#include "LoveSendClassInExe.h"
#include "../GameMessage/UpGradeLogic.h"
#ifdef _USE_VIDEO
#include "BRGameVideoSDK.h"
/**
* 游戏视频结构
*/
struct MyGameVideo
{
	MyGameVideo()
		: VideoServerPort(0)
	{
	}
	MyGameVideo(const char *serverip,int port)
		: VideoServerPort(port)
	{
		if(serverip) strcpy(VideoServerIP,serverip);
	}
	char VideoServerIP[256];                 // 视频服务器IP
	int VideoServerPort;                     // 视频服务器端口
};
#endif

//消息定义
#define IDM_BEGIN			WM_USER+120					//开始按钮消息
#define IDM_OUT_CARD		WM_USER+124					//用户出牌
#define IDM_HAVE_THING		WM_USER+127					//有事要走
#define IDM_SEND_THING		WM_USER+128					//发送离开请求
#define IDM_ARGEE_LEAVE		WM_USER+129					//同意离开消息
#define IDM_STOP			WM_USER+130					//提前结束按钮
#define IDM_STOP_THING		WM_USER+131					//发送提前结束
#define IDM_ARGEE_STOP		WM_USER+132					//同意提前结束
#define IDM_AUTOCARD		WM_USER+134					//托管
#define IDM_CALL_SCORE		WM_USER+135					//叫分

#define IDM_SORT			WM_USER+137					//排序
#define IDM_PASS			WM_USER+138					//过
#define IDM_CUE				WM_USER+139					//提示

#define IDM_ADD_DOUBLE		WM_USER+140					//加棒
#define IDM_ROB_NT			WM_USER+141					//抢地主
#define IDM_LOOK_LAST		WM_USER+142					//看上轮扑克
#define IDM_SHOW_CARD		WM_USER+143				    //亮牌
#define IDM_COUNTER         WM_USER+144                 //记牌器
#define IDM_DIALECT         WM_USER+145                 ///方音
#define IDM_CHUIYES         WM_USER+146                 ///锤
#define IDM_CHUINO          WM_USER+147                 ///不锤
//定时器 ID
#define ID_BEGIN_TIME				100					//开始定时器
#define ID_LEAVE_TIME				101					//离开定时器
#define ID_OUT_CARD					103					//出牌等待时间
#define ID_CALL_SCORE_TIME			107					//叫分定时器
#define ID_ROB_NT_TIME				108					//抢地主计时器
#define ID_ADD_DOUBLE_TIME			109					//加棒
#define ID_SHOW_LAST				110					//查看上轮扑克
#define ID_SHOW_CARD				111					//亮牌


#define ID_CONNECT_FLASH_TIME       112                 //连接视频播放器
#define ID_REMOVE_VIDEO_COLOR       113                  //去掉视频底色定时器
#define ID_ANIM_TIME				114					//动画计时器
#define TIME_CHUI					115					//锤
//重置函数参数
#define RS_ALL_VIEW					1					//重置所有参数
#define RS_GAME_CUT					2					//用户离开重置
#define RS_GAME_END					3					//游戏结束重置
#define RS_GAME_BEGIN				4					//游戏开始重置

#define GAME_AUTO_TIME				1					//自動出牌時間設置
#define GAME_RAND_TIME				2					//智能时间

//游戏框架类 
class CClientGameDlg : public CLoveSendClassInExe//CGameFrameDlg
{
	int						m_iVersion;					//内部开发版本号
	int						m_iVersion2;				//内部开发版本号
	BYTE					m_iPalyCard;				//游戏扑克副数
	int						m_iPlayCount;				//游戏扑克总数
	__int64					m_iRoomBasePoint;			//房间倍数
	__int64					m_iRunPublish;				//逃跑扣分
	BYTE					m_iAfterWaitAction;  	//开始倒计时结束后的动作 1 自动开始 2 自动离开 0900311a1 JJ

//	BYTE					m_iBeginNt;					//开始位置
//	BYTE					m_iEndNt;					//结束位置 
	//=====================时间表信息===================
	BYTE					m_iThinkTime;				//最少游戏盘数
	BYTE					m_iGiveBackTime;			//留底时间
	BYTE					m_iBeginTime;				//游戏开始时间
	BYTE					m_iCallScoreTime;				//游戏开始时间
	BYTE					m_iAddDoubleTime;				//游戏开始时间

	BYTE					m_iBeenPlayGame;				//已游戏局数
	//自己扑克数据
	BYTE					m_iMeCardCount;				//自己扑克的数目
	BYTE					m_iMeCardList[45];			//自己扑克列表
	BYTE					m_Card[PLAY_COUNT][45];				//各家手中的扑克数组
	BYTE					m_CardCount[PLAY_COUNT];				//各家手中的牌数
	bool                    m_bIsFirstOne[PLAY_COUNT];
	bool                    m_bIsFirstTow[PLAY_COUNT];

	//主牌信息
	BYTE					m_iNtPeople;				//亮主的游戏者
	BYTE					m_iBackCard[12];				//底牌扑克
	BYTE					m_iBackCount;				//底牌数

	//运行信息
	BYTE					m_iDeskCardCount[PLAY_COUNT];		//每人桌面扑克的数目
	BYTE					m_DeskCard[PLAY_COUNT][45];			//每人桌面的扑克

	//运行信息
	BYTE					m_bCurrentOperationStation;		//現在叫分者
	BYTE					m_iNowOutPeople;			//现在出牌者
	BYTE					m_iBaseCount;				//第一个出牌者牌数目
	BYTE					m_iFirstOutPeople;			//第一个出牌者
	BYTE					m_iBigOutPeople;			//当前最大出牌者

	BYTE					m_iBaseCard[45];			//第一个出牌者的扑克

	//上轮显示数据
	BYTE					m_bShowLast;				//是否可以显示上轮扑克
	BYTE					m_bShowIngLast;				//是否正显示上轮扑克
	BYTE					m_iLastCardCount[PLAY_COUNT];		//上轮扑克的数目
	BYTE					m_iLastOutCard[PLAY_COUNT][45];		//上轮的扑克
	BYTE					m_byteHitPass;						//是否不出

	BYTE					m_iAIStation[PLAY_COUNT];			//机器人托管
	////定时器计数
	BYTE						m_bTimeOutCount;		//超时
	int							m_btAutoTime;
	BYTE						m_bSortCard;				//排序方式

	void SetColor();
	CAFCColorResource			colorresource;		//聊天,系统颜色结构
	void ShowCallScoreBt(int CallScore,BOOL bExtVol=false);
	//控件变量
public:
	CUpGradeGameLogic		m_Logic;					//升级逻辑
	CClientPlayView			m_PlayView;					//游戏视图

	//	bool					m_iToux;					//是否正在请求投降
//	bool					m_bisexit;
	bool					m_bAutoCard;				//是否托管
	int						m_ResultCallScore;			//叫分结果
//	int						m_TotalScore;				//总分

	HWND					m_hMciWnd1;						//背景音乐(出牌)
	HWND					m_hMciWnd2;						//背景音乐(场景)
	HWND					m_hMciWnd3;						//背景音乐(背景)
	BOOL					m_bPlay;						//播放

	TCHAR					m_CueMessage[MAX_PATH];			//提示
	BOOL					m_bRightPower;					//顺时针出牌

	BOOL                    bInitFinish;
	bool                    m_bPlayFlashVideo;                       //是否启用视频

	bool                    m_bConnectFlash[PLAY_COUNT];
	char                    m_strFlash[PLAY_COUNT][256];	    //记录玩家的视频信息

	bool                    m_LastOneCard;               

    int                     m_iDialectType ;                 ///方音方式

#ifdef _USE_VIDEO
	CBRGameVideoSDK         *m_pBRGameVideoSDK;             /// 视频控件
	MyGameVideo             m_GameVideoSet;                 /// 游戏视频设置
	std::map<std::string,int>   m_VideoUserInfo;             /// 3个视频用户
#endif

	//函数定义
public:
	//构造函数
	CClientGameDlg();
	//析构函数
	virtual ~CClientGameDlg();

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
	virtual bool HandleGameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize);
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
	//聊天消息
	virtual void ShowUserTalk(MSG_GR_RS_NormalTalk *pNormalTalk);
	//取得游戏状态

	/// 为视频模块重载此函数
	virtual bool GameUserCome(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);
	
	virtual bool AFCCloseFrame();

		///从数值转换成String
	void GetNumString(__int64 nNum, CString &Str, int nPower);

    // PengJiLin, 2011-4-19, 在线时长、局数送金币图像提示
    virtual void ShowGetMoneyImage();

	//消息函数
public:
	//开始按钮函数
	LRESULT	OnHitBegin(WPARAM wparam, LPARAM lparam);

	//按动扑克按钮函数
	LRESULT	OnHitCard(WPARAM wparam, LPARAM lparam);

	//按动出牌按钮函数
	LRESULT	OnHitOutCard(WPARAM wparam, LPARAM lparam);

	//按动有事按钮函数
	LRESULT	OnHitHaveThing(WPARAM wparam, LPARAM lparam);
	//发送离开请求函数
	LRESULT	OnSendHaveThing(WPARAM wparam, LPARAM lparam);
	//用户请求离开
	LRESULT	OnArgeeUserLeft(WPARAM wparam, LPARAM lparam);
	//右键用牌
	LRESULT	OnRightHitCard(WPARAM wparam, LPARAM lparam);
	//托管
	LRESULT	OnAuto(WPARAM wparam, LPARAM lparam);
		//托管
	LRESULT	OnCounter(WPARAM wparam, LPARAM lparam);
	///方音
	LRESULT	OnDialect(WPARAM wparam, LPARAM lparam);
	//叫分
	LRESULT	OnCallScore(WPARAM wparam, LPARAM lparam);
	//不出
	LRESULT OnHitPassCard(WPARAM wparam,LPARAM lparam);
	//提示
	LRESULT OnCue(WPARAM wparam,LPARAM lparam);
	//排序
	LRESULT OnHitSortCard(WPARAM wparam,LPARAM lparam);
	//抢地主
	LRESULT OnRobNT(WPARAM wparam,LPARAM lparam);
	//加棒
	LRESULT OnAddDouble(WPARAM wparam,LPARAM lparam);
	//加棒
	LRESULT OnShowCard(WPARAM wparam,LPARAM lparam);
	//锤
	LRESULT OnChuiYes(WPARAM wparam,LPARAM lparam);
	//不锤
	LRESULT OnChuiNo(WPARAM wparam,LPARAM lparam);
	//重新设置游戏数据
	virtual void ResetGameStation(int iGameStation);
	//录影接口函数lc090226
	virtual void SetRecordView();

	virtual void FixControlStation(int iWidth, int iHeight);
	//取得游戏状态
	int	GetGameStatus()
	{
		if(this)
			return GetStationParameter();
		else
			return 0;
	};
	DECLARE_MESSAGE_MAP()

	afx_msg void OnTimer(UINT nIDEvent);

#ifdef _USE_VIDEO
	afx_msg LRESULT OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam);
	/// 刷新所有的视频面板
public:
	void RefreshAllVideoPanel(void);
#endif

//	afx_msg void OnClose();
protected:
	virtual void OnCancel();
	//视图转换
	virtual BYTE ViewStation(BYTE bDeskStation);
	//版本核对
	BOOL CheckVersion(BYTE iVersion,BYTE iVersion2);
	//设置提示牌弹起来
	void SetCueCardList(BYTE CueCardList[],BYTE iMeCardList[],int iMeCardCount,BYTE ResultCard[],int iResultCardCount);
	//播放背景声音
	BOOL PlayBackgroundMusic(){return TRUE;};
	//用戶出牌
	BOOL UserOutCard();
	//桌面提示
	BOOL SetNoteFlag(int iFlag = 0);
	//玩家断线,并判断是否为当前出牌者
	virtual BOOL UserCut(BYTE bDeskStation);
	//代替玩家开始
	BOOL ReplaceBegin(BYTE bDeskStation);
	//代替用戶叫分
	BOOL ReplaceCallScore(BYTE bDeskStation);
	//代替用戶出牌
	BOOL ReplaceOutCard(BYTE bDeskStation);
	//代替加棒
	BOOL ReplaceAddDouble(BYTE bDeskStation);
	//代替抢主
	BOOL ReplaceRobNT(BYTE bDeskStation);
	//按动上轮按钮函数
	LRESULT	OnLastTurn(WPARAM wparam, LPARAM lparam);
	//隐藏按钮
	BOOL HideButton();

	//add by ljl
	//播放声音
	BOOL VoiceOut(BYTE bDeskStation, LPCSTR pszSound);
public:
	/// 播放视频 
	void PlayFlashVideo(BYTE bDeskStation,UserItemStruct * pUserItem,bool byMySelf);
    ///停止视频
	void StopFlashVideo(BYTE iView);
	///
	void CreateTrustTxt(void);
};
