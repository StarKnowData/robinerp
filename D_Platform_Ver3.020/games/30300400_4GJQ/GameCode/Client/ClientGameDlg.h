#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "ClientView.h"
#include "GameSet.h"
//#include "PlaySound.h"
#include "LoveSendClassInExe.h"

/// 消息定义
#define IDM_BEGIN			WM_USER+120					///< 开始按钮消息
#define IDM_USER_NT			WM_USER+121					///< 用户反牌
//#define IDM_GIVE_BACK		WM_USER+123					///< 留底牌按钮

#define IDM_OUT_CARD_PASS		WM_USER+123				///< 用户出牌
#define IDM_OUT_CARD		WM_USER+124					///< 用户出牌
#define IDM_LOOK_LAST		WM_USER+125					///< 看上轮扑克
///#define IDM_BACK_CARD		WM_USER+126				///< 底牌信息
#define IDM_HAVE_THING		WM_USER+127					///< 有事要走
#define IDM_SEND_THING		WM_USER+128					///< 发送离开请求
#define IDM_ARGEE_LEAVE		WM_USER+129					///< 同意离开消息
#define IDM_STOP			WM_USER+130					///< 提前结束按钮
#define IDM_STOP_THING		WM_USER+131					///< 发送提前结束
#define IDM_ARGEE_STOP		WM_USER+132					///< 同意提前结束
#define IDM_SET_FLASH_CHESS WM_USER+122					///< 设置棋子闪烁

/// 定时器 ID
#define ID_BEGIN_TIME				100					///< 开始定时器
///#define ID_WAIT_ROB					101				///< 等待抢底牌
///#define ID_GIVE_BACK				102					///< 等待留底牌
#define ID_OUT_CARD					103					///< 出牌等待时间
#define ID_SHOW_LAST				104					///< 查看上轮扑克
///#define ID_SHOW_CARD				105					///< 甩牌定时器
///#define ID_LOOK_BACK				106					///< 查看底牌
#define ID_SHOW_PATH				107					///< 显示轨迹
#define ID_FLASH_CHESS				108					///< 闪烁棋子

/// 重置函数参数
#define RS_ALL_VIEW					1					///< 重置所有参数
#define RS_GAME_CUT					2					///< 用户离开重置
#define RS_GAME_END					3					///< 游戏结束重置
#define RS_GAME_BEGIN				4					///< 游戏开始重置

/// 游戏框架类    AFC::界面库::IDD_GAME_FRAME 
class CClientGameDlg : public CLoveSendClassInExe//CGameFrameDlg
{	
bool H041_UserLose(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H0011_UserBuZhen(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H085_DuiJiaHaveThingResult(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H084_DuiJiaHaveThing(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H083_UserHaveThingResult(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H082_UserHaveThing(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H081_UserContinueEnd(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H080_UserLeftOrGameAnQuanFinish(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H040_UserOutCard(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);

	bool H030_NextStep(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H010_GameBegin(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	bool H000_UserSetGameJu(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);

protected:
	/// 用户进入
	virtual bool GameUserCome(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);
	
public:
	bool  IsWatcher( ){return m_bWatchMode;}
	/// 固定信息
	BYTE					m_iLessCount;				///< 最少游戏盘数
	BYTE						m_bTimeOutCount;		///< 超时

	/// 控件变量
public:
	CClientPlayView			m_PlayView;					///< 游戏视图
	CGameSet				* m_GameSet;
	_PathMsg				m_MResultPath;				///< 轨迹数据

	int						m_iVersion;
	int						m_iVersion2;
	int						uRunPublish;				///< 扣分
	int						basepoint;					///< 倍数
	BYTE					m_iAfterWaitAction;  		///< 开始倒计时结束后的动作 1 自动开始 2 自动离开
	/// 函数定义
public:
	/// 构造函数
	CClientGameDlg();
	/// 析构函数
	virtual ~CClientGameDlg();

protected:
	/// 初始化函数
	virtual BOOL OnInitDialog();
	/// 数据绑定函数
	virtual void DoDataExchange(CDataExchange * pDX);
	virtual void OnWatchSetChange(void);
	virtual void OnGameSetting();	
	bool	AFCCloseFrame();

	CPlaySound				m_playsound;
	CPlaySound				m_playsound2;

	/// 重载函数
public:
	int GetPlayerCount();
	/// 设置游戏状态
	virtual bool SetGameStation(void * pStationData, UINT uDataSize);
	/// 游戏消息处理函数
	virtual bool HandleGameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/);
	/// 重新设置界面
	virtual void ResetGameFrame();
	/// 定时器消息
	virtual bool OnGameTimer(BYTE bDeskStation, UINT uTimeID, UINT uTimeCount);
	/// 清除所有定时器
	void KillAllTimer();
	/// 同意开始游戏 
	virtual bool OnControlHitBegin();
	/// 安全结束游戏
	virtual bool OnControlSafeFinish(){return false;};
	/// 用户离开
	virtual bool GameUserLeft(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);
	/// view
	virtual BYTE ViewStation(BYTE bDeskStation);
	/// 消息函数
public:
	/// 开始按钮函数
	LRESULT	OnHitBegin(WPARAM wparam, LPARAM lparam);
	/// 按动扑克按钮函数
	/// /LRESULT	OnHitCard(WPARAM wparam, LPARAM lparam);

	/// 按动上轮按钮函数
	/// LRESULT	OnHitLastTurn(WPARAM wparam, LPARAM lparam);
	/// 按动有事按钮函数
	LRESULT	OnHitHaveThing(WPARAM wparam, LPARAM lparam);
	/// 发送离开请求函数
	LRESULT	OnSendHaveThing(WPARAM wparam, LPARAM lparam);
	/// 用户请求离开
	LRESULT	OnArgeeUserLeft(WPARAM wparam, LPARAM lparam);
	/// 右键用牌
	/// /LRESULT	OnRightHitCard(WPARAM wparam, LPARAM lparam);
	/// 提前结束按钮
	LRESULT	OnStop(WPARAM wparam, LPARAM lparam);
	/// 发送提前结束
	LRESULT	OnStopThing(WPARAM wparam, LPARAM lparam);
	/// 同意提前结束
	LRESULT	OnAgreeStop(WPARAM wparam, LPARAM lparam);
	/// 设置闪烁棋子
	LRESULT	OnFlashChess(WPARAM wparam, LPARAM lparam);

	void ResetGameStation(int iGameStation);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT nIDEvent);
protected:
	virtual void OnCancel();
};

extern int  GetStation( int viewStation);
extern CClientGameDlg * g_pCClientGameDlg;
extern  bool  IsWatcher( );
extern int GetStationParameter();