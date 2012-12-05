#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "GameNoteWnd.h"
#include "HaveThing.h"
#include "LeaveMessage.h"
#include "GameCard.h"
#include "GameFinishDlg.h"
#include "DisplayTalkDialog.h"	//聊天框
#include "FlashModule\shockwaveflash1.h"
#include "Counter.h"
#include "Dialect.h"

class CUpGradeDlg;
class CUpGradeView;

extern DWORD      g_bucFileHandle;  //buc文件句柄
extern CGameImage g_gameImage;      //游戏图片文件


//控件 ID
#define IDC_OUT_CARD				121				///< 出牌按钮
#define IDC_CONTINUE				124				///< 继续按钮
#define IDC_LAST_CARD				125				///< 上轮按钮
#define IDC_HAVE_THING				127				///< 有事要走
#define IDC_AUTOCARD				130				///< 托管
#define IDC_PASS					132				///< 不出
#define IDC_SORT_CARD				133				///< 排序
#define IDC_CUE						134				///< 提示
#define IDC_COUNTER                 135             ///<记牌器
#define IDC_DIALECT                 136             ///<方音
#define IDC_CALL_SCORE_PASS			140				///< 叫分类型
#define IDC_CALL_SCORE_1			141				///< 叫分类型
#define IDC_CALL_SCORE_2			142				///< 叫分类型
#define IDC_CALL_SCORE_3			143				///< 叫分类型
#define IDC_LEAVE					144				///< 离开类型
#define IDC_ROB_NT					145				///< 抢地主
#define IDC_ROB_NT_2				146				///< 不抢
#define IDC_ADD_DOUBLE				147				///< 加棒
#define IDC_ADD_DOUBLE_2			148				///< 不加棒
#define IDC_SHOW_CARD				149				///< 亮牌
#define	IDC_SHOW_CARD_2				150				///< 不亮
#define IDC_CHANGE_SHIN				151				///<换肤
#define IDC_CHUI_YES				152				///<锤
#define IDC_CHUI_NO					153				///<不锤

const  int VIDEO_WIDTH  = 180;
const  int VIDEO_HEIGHT = 150;
const  int VIDEO_WIDTH_MYSELF = 215;
const  int VIDEO_HEIGHT_MYSELF = 150;

//梭哈视图类
class CClientPlayView : public CUsingSkinClass//CGDIPlayView
{
	bool							m_bInit;
	//程序变量
protected:
	CPoint							m_PtNt[PLAY_COUNT];				///< 庄家和盟友位置
	CPoint							m_PtAuto[PLAY_COUNT];			///< 托管坐标
	CPoint							m_PtAwardPoint[PLAY_COUNT];		///< 奖分情况
	CPoint							m_PtSequence[PLAY_COUNT];		///< 出牌先后顺序
	CPoint							m_PtPass[PLAY_COUNT];			///< 放弃
	CPoint							m_PtLastCardFlag[PLAY_COUNT];	///< 最后一手牌标记
	CPoint							m_PtGetPoint[PLAY_COUNT];		///< 抓分显示坐标
	CPoint							m_PtDeskTempPoint;				///< 桌面临时分
	CPoint							m_PtDeskMultiple;				///< 桌子倍数
	CPoint							m_PtRoomMultiple;				///< 房间倍数
	CPoint							m_PtGameMultiple;				///< 房间倍数
	CPoint							m_PtCallScore[PLAY_COUNT];		///< 叫分坐标
	CPoint							m_PtCallScoreResult;			///< 叫分结果(斗地主等游戏中会出现)
	CPoint							m_PtCallScoreNT;				///< 叫分庄家
	CPoint							m_PtGameTitle;					///< 游戏标题logo坐标
	CPoint							m_PtBottomCue;					///< 游戏提示
	CPoint							m_PtPeopleMul[PLAY_COUNT];		///< 玩家加棒显示位置
	CPoint							m_PtShowMsg;					///< 
	CPoint                          m_PtGif[PLAY_COUNT];
	CPoint							m_PtResultTime;					
	CPoint							m_PtCurOrientation[PLAY_COUNT];	///< 当前出牌者方向坐标
	CPoint							m_PtDeskCue;					///< 桌面提示坐标	
	//扑克索引
	POINT							ptCardPoint[PLAY_COUNT];
	POINT							ptHandCard[PLAY_COUNT];
	POINT							ptBackCard;						///< 底牌
	int								m_Bt1WidthSpace;				///< 右边按钮坐标
	int								m_Bt1HeightSpace;
	int								m_Bt2WidthSpace;				///< 叫分按钮
	int								m_Bt2HeightSpace;
public:
	CPoint                          m_ptVideoPos[PLAY_COUNT];        ///玩家的视频位置
	int								m_iDeskTempPoint;				///< 桌面上的分数(临时分)
	__int64							m_iDeskMultiple;				///< 桌子倍数
	__int64							m_iRoomMultiple;				///< 房间倍数
	__int64							m_iGameMultiple;				///< 游戏倍数
	
	int								m_iNtStation;					///< 庄家位置
	int								m_iPass[PLAY_COUNT];			///< 本轮玩家押注总数

	int								m_iCallScore[PLAY_COUNT];		///< 各家叫分
	int								m_iCueType;						///< 提示方式

	bool							m_bFirstGame;					///< 是否新进入桌子
	bool							m_bCanLeave;					///< 能否点击退出

	CToolTipCtrl					m_ToolTip;						///< 提示文字
	CDisplayTalkDialog				m_dlgDisTalk[PLAY_COUNT];		///< 聊天框
	BYTE							m_iCurOrientation;				///< 当前出牌者方向
	//图片
	CGameImage						m_bit_background;				///< 背景填充小图
	CGameImage						m_Background;					///< 背景贴图(大贴图)
	CGameImage						m_GameTitleLogo;				///< 游戏名称logo
	CGameImage						m_NT;							///< 庄家标识	
	CGameImage						m_NT2;							///< 庄家标识	
	CGameImage						m_AwardPint;					///< 奖分情况
	CGameImage						m_CallScore;					///< 叫分图片
	CGameImage						m_AutoLogo;						///< 托管标识
	CGameImage						m_Pass;							///< pass图示
	CGameImage						m_LastCardFlag;					///< 最后一手牌提示图标
	CGameImage						m_PicSequence;					///< 出牌先后顺序提示图标
	CGameImage						m_PicBottomCue;					///< 出牌先后顺序提示图标
	CGameImage						m_PeopleMul;					///< 出牌先后顺序提示图标
	CGameImage						m_ShowMsg;						///< 出牌先后顺序提示图标
	CGameImage						m_ImgFangXiang;					///< 方向图片	
	CGameImage						m_imgLogoFrame;					///< 头像底图 20090516
    CGameImage                      m_Num;
	Image*							m_ImgBackground[4];				//背景图片数组
	int								m_iCurrentBG;					//当前背景图片
	Image							*m_ImageAnim[5];				//动画图片
	int								m_iCurrentStitch;				//动画当前针数
	Image*							m_pChuiSign;					//锤一锤标志
	CPoint							m_PtChui[PLAY_COUNT];			//锤一锤标志坐标
	BYTE 							m_iChui[PLAY_COUNT];			//是否锤一锤 1:未知状态，0:不锤，2:锤

	CUpGradeGameCard				m_MeCard;						///< 自己的扑克
	CUpGradeGameCard				m_MeBackCard;					///< 自己的底牌
	CUpGradeGameCard				m_UserCard[PLAY_COUNT];			///< 用户扑克
	CUpGradeGameCard				m_HandCard[3];					///< 用户手中扑克
	CUpGradeGameCard                m_ThreeCard;            	    ///< 二人斗地主中不发人的扑克 

	CShockwaveflash1 m_FlashPlayer[PLAY_COUNT];	

	/// 根据配置文件设置，是否显示人物头像
	bool 		m_bShowLogo;
	bool        m_bShowMoney ;  ///是否显示玩家金币

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

	CString     m_strCoinName ;    //货币名称

	CLeaveMessage					m_ThingMessage;					///< 离开消息
	CGameNoteWnd					m_GameNoteView;					///< 游戏信息
	CGameFinishDlg					m_Result;						///< 游戏结束信息
	CCounter                        m_CounterDlg ;                  ///点击记牌器按钮
	CDialect                        m_DialectDlg ; 

    // PengJiLin, 2011-4-19, 在线时长、局数送金币图像提示
    CGetMoneyWnd                    m_GetMoneyImageView;

//	CStationView					m_StationView;					///< 状态窗口
	CNormalBitmapButtonEx			m_btOutCard;					///< 出牌按钮
	CNormalBitmapButtonEx			m_btPass;						///< 不出
	CNormalBitmapButtonEx			m_btCue;						///< 提示

	CNormalBitmapButtonEx			m_btContinue;					///< 继续按钮
	CNormalBitmapButtonEx			m_btLeave;						///< 继续按钮
	CNormalBitmapButtonEx			m_btAuto;						///< 托管按钮
	CNormalBitmapButtonEx			m_btThing;						///< 有事要走
	CNormalBitmapButtonEx			m_btSortCard;					///< 排序
	CNormalBitmapButtonEx			m_btRobNT;						///< 抢地主
	CNormalBitmapButtonEx			m_btRobNT2;						///< 不抢
	CNormalBitmapButtonEx			m_btAddDouble;					///< 加棒
	CNormalBitmapButtonEx			m_btAddDouble2;					///< 不加棒
	CNormalBitmapButtonEx			m_btShowCard;					///< 亮牌
	CNormalBitmapButtonEx			m_btShowCard2;					///< 不亮
	CNormalBitmapButtonEx			m_btLastTurn;					///< 上一轮
	CNormalBitmapButtonEx			m_btCounter;					///< 记牌器
	CNormalBitmapButtonEx           m_btdialect ;                   ///方音按钮
	CNormalBitmapButtonEx           m_btChangeShin;					///<换肤
	CNormalBitmapButtonEx           m_btChuiYes;					///<锤
	CNormalBitmapButtonEx           m_btChuiNo;						///<不锤

	CHaveThing						m_HaveThing;					///< 有事离开
	BYTE							m_iAwardPoint[PLAY_COUNT];		///< 四家奖分情况
	bool							m_bAuto[PLAY_COUNT];			///< 托管标记
	bool							m_bUpdateScoreboard;			///< 更新积分榜
	int								m_iPeopleMul[PLAY_COUNT];		///< 玩家是否加棒

	bool                            m_bAIChooseCard ; 
public:
		//====叫分情况
	CNormalBitmapButtonEx			m_btCallScorePass;				///< 不叫
	CNormalBitmapButtonEx			m_btCallScore1;					///< 不叫
	CNormalBitmapButtonEx			m_btCallScore2;					///< 不叫
	CNormalBitmapButtonEx			m_btCallScore3;					///< 不叫

private:
	COLORREF			m_NameColor;								///< 显示用户颜色

public :
	BOOL					m_bWatch;								///< 自己是否为观战
	CGameImage				m_pVideoFrame;							///< 视频背景
	CRect					m_rectVideoFrame[MAX_PEOPLE];			///< 视频背景坐标
	BOOL					GetVideoRect(CString  strNickname, RECT& rect, CString& pic);

public:
	void SetNameColor(COLORREF rgb)	{m_NameColor=rgb;	}
	/// 函数定义
public:
	/// 构造函数
	CClientPlayView();
	/// 析构函数
	virtual ~CClientPlayView();
	
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
	void TransparentBlt2( HDC hdcDest,  // 目标DC
					int nXOriginDest,   // 目标X偏移
					int nYOriginDest,   // 目标Y偏移
					int nWidthDest,     // 目标宽度
					int nHeightDest,    // 目标高度
					HDC hdcSrc,         // 源DC
					int nXOriginSrc,    // 源X起点
					int nYOriginSrc,    // 源Y起点
					int nWidthSrc,      // 源宽度
					int nHeightSrc,     // 源高度
					UINT crTransparent  // 透明色,COLORREF类型
					);

	//消息函数
protected:
	/// 建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	/// 设置背景色
	void SetBackBmp(UINT uResourceID, TCHAR * szFileName=NULL, BOOL bResource=TRUE);
	/// 绘制背景填充小图
	void DrawBk(CDC *pDC, int iWidth, int iHeight);
	/// 绘制游戏logo
	void DrawGameTitle(CDC *pDC);
	/// 设置庄家位置
	void SetNTStation(int iViewStation=-1);
	/// 绘画 NT 标志
	void DrawNt(CDC * pDC, int x, int y);
	/// 绘画 NT 图标
	void DrawNtLogo(CDC * pDC, int x, int y, int iHuaKind);
	DECLARE_MESSAGE_MAP()
	/// 按钮消息函数
protected:
	/// 开始按钮
	void OnHitBegin();
	/// 离开
	void OnHitLeave();	
	/// 出牌按钮
	void OnHitOutCard();
	/// 继续按钮
	void OnHitContinue();
	/// 有事要走
	void OnHitThing();
	/// 投降
	void OnHitTuoxiang();
public:
	/// 比赛场设置
	void DrawFen(CDC * pDC);
public:
	void OnHitAuto(void);

	void SetCallScoreValue(BYTE bViewStation,int iCallScore);
	
	int m_iCallScoreResult;
	/// 叫分结果
	void SetCallScoreResult(int iCardCount = 0);		
	/// 托管
	void SetAuto(int bDeskStation,bool bAuto);
	/// 绘制托管
	BOOL DrawAuto(CDC * pDC);
	/// 设置奖分
	void SetAwardPoint(BYTE iViewStation,BYTE iAwardPoint);
	/// 繪製將分
	void DrawAwardPoint(CDC *pDC);
	///点击叫分
	void OnHitCallScore(UINT uID);
	/// 提示
	void OnCue();	
	/// 点击不出
	void OnHitPass();
	///添加记牌器功能
	void OnHitCounter() ; 
	///方音
	void OnHitDialect() ;
	/// 排序
	void OnHitSort();
	/// 設置房间倍数
	BOOL SetRoomMultiple(int iRoomMultiple = 0);
	/// 绘制房间倍数
	BOOL DrawRoomMultiple(CDC *pDC);
	/// 设置游戏倍数
	BOOL SetGameMultiple(int iGameMultiple = 0);
	/// 绘制游戏倍数
	BOOL DrawGameMultiple(CDC *pDC);
	/// 绘制叫分结果
	BOOL DrawCallScoreResult(CDC *pDC);
	/// 设置桌面倍数
	BOOL SetDeskMultiple(int iDeskMultiple= 0);
	/// 绘制桌面倍数
	BOOL DrawDeskMultiple(CDC *pDC);
	/// 设置桌面临时分
	void SetDeskTempPoint(int iDeskTempPoint = 0);
	/// 增加桌面临时分
	void AddDeskTempPoint(int iDeskTempPoint);
	/// 绘制桌面临时分
	BOOL DrawDeskTempPoint(CDC *pDC);
	/// 绘制底部提示
	BOOL DrawBottom(CDC * pDC);
	/// 放弃
	void DrawPass(CDC *pDC);
	/// 设置放弃
	void SetPass(BYTE iViewStation,int iGiveup);
///////////////////////////////////////////////////////////////////////////
	CUpGradeGameCard		m_DeskCard;								///< 桌面上牌(用来显示发牌动画)
	CUpGradeGameCard		m_SendCard[PLAY_COUNT];					///< 桌面上牌(用来显示发牌动画)

	BOOL				m_bHaveSendCardAnimal[PLAY_COUNT];			///< 发牌动画控制变量
	CPoint				m_PtStart[PLAY_COUNT];						///< 发牌动画活动坐标
	CPoint				m_PtSendCardEnd[PLAY_COUNT];				///< 发牌动画结束点坐标
	CPoint				m_PtSendCardStart[PLAY_COUNT];				///< 发牌动画起始点坐标

	void				SetSendCardPointStart(BYTE iViewStation);	///< 设置发牌动画起始坐标
	void				SendCardAnimal();							///< 发牌动画函数

///////////////////////////////////////////////////////////////////////////
	/// 聊天框
	void DisplayTalkMsg(int Viewstation,TCHAR * szCharString);
	/// 提示文字
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	/// 方向
	void SetOrientation(BYTE bDeskStation);
	/// 绘制方向
	BOOL DrawOrientation(CDC *pDC);
	/// 聊天框初始化
	void Init();
	/// 根据游戏加载坐标
	void LoadSkinIni(int cx,int cy);
	/// 根据坐标重新移动
	void MoveScreen(int cx,int cy);
	/// 抢地主
	void OnHitRobNT();
	/// 不抢地主
	void OnHitRobNT2();
	/// 加棒
	void OnHitAddDouble();
	/// 不加棒
	void OnHitAddDouble2();
	/// 加棒
	void OnHitShowCard();
	/// 不加棒
	void OnHitShowCard2();
	/// 上一轮
	void OnHitLastTurn();
	//换肤
	void OnChangeShin();
	/// 锤
	void OnHitChuiYes();
	/// 不锤
	void OnHitChuiNo();
	/// 设置玩家倍数
	void SetPeopleMultiple(BYTE bViewStation,int iVal = 1);
	/// 绘制玩家倍数
	void DrawPeopleMultiple(CDC *pDC);
	/// 绘制玩家叫分结果和倍率背景图
	void DrawShowMsg(CDC *pDC);

public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
     //创建不规则区域
	 HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
     //去掉视频底色
     void RemoveVideoBaseColor(void);

	 void SetVideoRgn(BYTE iView);

	 void DarwCardImage(CDC *pDC);	//画2.5D牌背

	 void SetAnimStitch(int iStitch);	//设置动画针数

	 void DarwChuiAnim(CDC *pDC,int iW,int iH);	//画动画图片

	 void SetChuiData(BYTE byStation, BYTE iFlag);	//设置锤一锤数据

	 void DarwChuiSign(CDC *pDC);			//绘制锤一锤标志
};
