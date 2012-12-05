#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "GameNoteWnd.h"
#include "PlaySetDlg.h"
#include "GameInfoDlg.h"
#include "HaveThing.h"
#include "LeaveMessage.h"
#include "Stop.h"
#include "StopMessage.h"
#include "jqboard.h"
#include "MsgBox.h"
#include "Result.h"

class CUpGradeDlg;
class CUpGradeView;

/// 控件 ID
#define IDC_GAME_BEGIN				120				///< 开始按钮
#define IDC_CONTINUE				124				///< 继续按钮
#define IDC_HAVE_THING				127				///< 有事要走
#define IDC_STOP					128				///< 停止本局
#define IDC_FINISH_DIAODU			130				///< 底牌按钮
#define IDC_SAVE_BUZHEN				131				///< 有事要走
#define IDC_LOAD_BUZHEN				132				///< 停止本局
#define IDC_LEAVE					133				///< 停止本局
/// 梭哈视图类
class CClientPlayView : public CUsingSkinClass//CGDIPlayView
{
	///CRect m_rcMjDesk; ////麻将显示总区域
	void DrawUserMj(CDC * pDC, int iClientWidth, int iClientHeight);
	void DrawNt(CDC * pDC, int x, int y);
	/// 程序变量
protected:
	UINT m_imaxelaspse;
	
	CPoint				m_PtNt[PLAY_COUNT];					///< 用户反牌位置
	CPoint              m_PtGif[PLAY_COUNT];        ///< 道具动画
	/// 控件变量
public:
	int			m_widthVideo;
	int			m_heightVideo;
	void SetCheckTimer(int maxelaspse);

	void KillCheckTimer();
	CJqBoard m_Logic;
	void Init();
	
	CBitmap				m_NT;						///< NT 图标
	CGameInfoDlg		m_GameInfo;					///< 游戏信息
	CPlaySetDlg			m_GameSet;					///< 游戏设置
	CGameNoteWnd		m_GameNoteView;				///< 游戏信息
	CNormalBitmapButtonEx		m_btContinue;		///< 继续按钮
	//CNormalBitmapButtonEx		m_btleave;			///< 离开
	CNormalBitmapButtonEx		m_btThing;			///< 有事要走
	CNormalBitmapButtonEx		m_btStop;			///< 停止本局

	CNormalBitmapButtonEx m_btFinishDiaoDu;//.Create(TEXT("完成调度"),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_FINISH_DIAODU);
	CNormalBitmapButtonEx m_btLoadBuZhen;//.Create(TEXT("调入布局"),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_DISABLED|BS_OWNERDRAW,CRect(0,0,25,25),this,IDC_LOAD_BUZHEN);
	CNormalBitmapButtonEx m_btSaveBuZhen;

	/// 根据配置文件设置，是否显示人物头像
	BOOL		m_bShowLogo;
	int			m_NameFont_Height;
	int			m_NameFont_Width;
	int			m_NameTextOffset_Height;
	int			m_NameTextOffset_Width;
	int			m_JinBiFont_Height;
	int			m_JinBiFont_Width;
	int			m_JinBiTextOffset_Height;
	int			m_JinBiTextOffset_Width;
	int			m_UserNameOffset_x[PLAY_COUNT];
	int			m_UserNameOffset_y[PLAY_COUNT];
	int			m_JinBiOffset_x[PLAY_COUNT];
	int			m_JinBiOffset_y[PLAY_COUNT];

	bool		m_bFirstGame;						///第一次进入桌子

	CLeaveMessage		m_ThingMessage;				///< 离开消息
	CHaveThing			m_HaveThing;				///< 有事离开
	CStop				m_StopThing;
	CStopMessage		m_StopMessage;
	CMsgBox				m_msgbox;					///< 显示消息框
	CMsgBoxResult       m_Result;                   ///< 游戏结算框
	CGameImage			m_PicTopBar;				///< 顶端贴图
	CGameImage			m_PicTopBarLeft;			///< 顶端贴图
	CGameImage			m_PicTopBarRight;			///< 顶端贴图


	bool							m_bUpdateScoreboard;			///< 更新积分榜
	/// 函数定义
public:
	/// 构造函数
	CClientPlayView();
	/// 析构函数
	virtual ~CClientPlayView();
public:
	/// /将此昵称的玩家视频窗口矩形写入参数rect,并返回TRUE;没找到返回falst
	BOOL	GetVideoRect(CString  strNickname, RECT& rect, CString& pic);

	/// 重载函数
public:
	/// 重置界面函数
	virtual void ResetGameView();
	/// 绘画界面函数
	virtual void DrawViewFace(CDC * pDC, int iWidth, int iHeight);
	/// 更新用户资料
	virtual void UpdateUserInfo(BYTE bViewStation);
	virtual void FixControlSize(int,int);


	/// 功能函数
public:
	void DrawInfo(CDC *pDC);	
	/// 提示文字
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	/// 消息函数
protected:
	/// 建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	/// 设置背景色
	void SetBackBmp(UINT uResourceID, TCHAR * szFileName=NULL, BOOL bResource=TRUE);
	/// 设置庄家位置
	void SetNTStation(int iViewStation=-1);
	/// 设置游戏分数
	void SetGamePoint(int iGamePoint=0, int bMeSide=-1);
	
	DECLARE_MESSAGE_MAP()
	/// 按钮消息函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	/// 开始按钮
	void OnHitBegin();
	void OnHitFinishDiaoDu();
	void OnHitSaveBuZhen();
	void OnHitLoadBuZhen();	
	/// 继续按钮
	void OnHitContinue();
	void OnHitLeave();
	/// 有事要走
	void OnHitThing();
	/// 提前停止
	void OnHitStop();
public:
	static CBitmap				m_Bitmap_Num;
	BOOL						m_bRightPower;
	afx_msg void OnTimer(UINT nIDEvent);

public :

#ifdef	VIDEO
	BOOL					m_bWatch;						///< 自己是否为观战
	CGameImage				m_pVideoFrame;					///< 视频背景
	CRect					m_rectVideoFrame[MAX_PEOPLE];   ///< 视频背景坐标
	BOOL					GetVideoRect(CString  strNickname, CRect& rect);
	CPlayVideo				m_pPlayVideo;
#endif
};
