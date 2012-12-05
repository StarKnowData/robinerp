#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "ClientView.h"
#include "UpGradeLogic.h"
#include "GameSet.h"

#include "LoveSendClassInExe.h"

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
#define IDM_BEGIN					WM_USER+120					//开始按钮消息
#define IDM_HAVE_THING				WM_USER+127					//有事要走
#define IDM_SEND_THING				WM_USER+128					//发送离开请求
#define IDM_ARGEE_LEAVE				WM_USER+129					//同意离开消息
#define IDM_STOP					WM_USER+130					//提前结束按钮
#define IDM_STOP_THING				WM_USER+131					//发送提前结束
#define IDM_ARGEE_STOP				WM_USER+132					//同意提前结束
#define IDM_ADMIT_DEFEAT			WM_USER+133					//认输
#define IDM_REGRET_CHESS			WM_USER+134					//悔棋
#define IDM_CHESS_MANUAL			WM_USER+135					//棋谱
#define IDM_SEND_REN_SHU			WM_USER+136					//发送认输
#define IDM_AGREE_REGRET			WM_USER+137					//同意悔棋
#define IDM_FINISH_DIAN_MU			WM_USER+138
#define IDM_ASSURANCE_DIAN_MU		WM_USER+139					//确定点目
#define IDM_AGREE_DIAN_MU			WM_USER+140					//同意点目
#define	IDM_NUMBER_ZI				WM_USER+141					//强制数子
#define IDM_ASSURANCE_NUM_ZI		WM_USER+142					//确定强制数子

#define IDM_GAMESETTING_OK				WM_USER+143					//确定强制数子

//定时器 ID
#define ID_BEGIN_TIME				100							//开始定时器
#define ID_OUT_CARD					103							//出牌等待时间

//重置函数参数
#define RS_ALL_VIEW					1							//重置所有参数
#define RS_GAME_CUT					2							//用户离开重置
#define RS_GAME_END					3							//游戏结束重置
#define RS_GAME_BEGIN				4							//游戏开始重置

//游戏框架类 
class CClientGameDlg : public CLoveSendClassInExe//CGameFrameDlg
{
	//变量定义
public:
	int							m_iVersion;							//高版本号
	int							m_iVersion2;						//低版本号

	//倍数设置	
	int							m_iRoomBasePoint;					//房间倍数
	int							m_iRunPublish;						//逃跑扣分
	int							m_iRunPublishMoney;					//逃跑扣分

	BYTE						m_iBeginTime;						//开始时间
	//运行信息
	BYTE						m_iNowOutPeople;					//现在出牌者
	int							m_Qiflag[2];						//双方的黑白
	CString						m_finishMsg;						//数目信息
//	BYTE						m_bTimeOutCount;					//超时
	//int							m_nJiaoZu;
	
	int							m_iStartI,							//走子起点
								m_iStartJ,
								m_iEndI,							//走子终点
								m_iEndJ;


	int							m_iMeBoard[21][21];					//本方棋局
	int							m_iMeChessFlag;						//本方标志
	int							m_iCurPlayFlag;						//当前走子者

	int							m_iJuTimeMinute,					//局时分
								m_iJuTimeSecond,					//局时秒
								m_iBuTimeMinute,					//步时分
								m_iBuTimeSecond,					//步时秒
								m_iDuMiaoMinute,					//读秒分
								m_iDuMiaoSecond;					//读秒秒

	bool						m_bIsInDianZi;
	bool						m_bCanPlay;
	int							m_iDianMuQiZi[21][21];
	TCHAR						m_szMSG[MAX_PATH];					//消息字符数组
	bool                        m_bNoHaveAgreeRegret;                //是否点击了同意悔棋会不同意悔棋
	//控件变量
public:
	CUpGradeGameLogic			m_Logic;						//升级逻辑
	CClientPlayView				m_PlayView;						//游戏视图
	CGameSet					* m_GameSet;
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

	//消息函数
public:
	//开始按钮函数
	LRESULT	OnHitBegin(WPARAM wparam, LPARAM lparam);
	//按动扑克按钮函数
	LRESULT	OnHitCard(WPARAM wparam, LPARAM lparam);
	//按动有事按钮函数
	LRESULT	OnHitHaveThing(WPARAM wparam, LPARAM lparam);
	//发送离开请求函数
	LRESULT	OnSendHaveThing(WPARAM wparam, LPARAM lparam);
	//用户请求离开
	LRESULT	OnArgeeUserLeft(WPARAM wparam, LPARAM lparam);
	//右键用牌
	LRESULT	OnRightHitCard(WPARAM wparam, LPARAM lparam);
	//提前结束按钮
	LRESULT	OnStop(WPARAM wparam, LPARAM lparam);
	//发送提前结束
	LRESULT	OnStopThing(WPARAM wparam, LPARAM lparam);
	//同意提前结束
	LRESULT	OnAgreeStop(WPARAM wparam, LPARAM lparam);
	//认输
	LRESULT OnAdmitDefeat(WPARAM wparam, LPARAM lparam);
	//悔棋
	LRESULT OnRegretChess(WPARAM wparam, LPARAM lparam);
	//棋谱
	LRESULT OnChessManual(WPARAM wparam, LPARAM lparam);
	//超时处理
	LRESULT OnSuperTimer(WPARAM wparam, LPARAM lparam);
	//确认认输
	LRESULT OnSendAdmitDefeat(WPARAM wparam, LPARAM lparam);
	//同意悔棋
	LRESULT OnAgreeRegret(WPARAM wparam, LPARAM lparam);
	//完成点目
	LRESULT OnFinishDianMu(WPARAM wparam, LPARAM lparam);

	//同意点目
	LRESULT OnAgreeDianMu(WPARAM wParam, LPARAM lParam);
	
	//强制数子
	LRESULT	OnNumberZi(WPARAM wParam, LPARAM lParam);
	
	//确定强制数子
	LRESULT OnAssuranceNumZi(WPARAM wParam, LPARAM lParam);

	//鼠标移动到棋子上（点目用）
	LRESULT OnMouseMoveCard(WPARAM wparam, LPARAM lParam);

	//确定点目
	LRESULT OnAssuranceDianMu(WPARAM wParam, LPARAM lParam);

	LRESULT OnGameSettingOK(WPARAM wParam, LPARAM lParam);


	void ResetGameStation(int iGameStation);

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

protected:
	virtual void OnCancel();
	virtual bool	AFCCloseFrame(bool bNotifyServer = true);
	virtual void FixControlStation(int iWidth, int iHeight);
public:
	//版本核对
	BOOL CheckVersion(BYTE iVersion,BYTE iVersion2);
	//是否可以中途离开
	virtual BOOL CanLeftDesk(BYTE bDeskStation);
	//用户进入
	virtual bool GameUserCome(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);

};
