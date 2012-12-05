#pragma once

#include "StdAfx.h"
#include "Resource.h"
//#include "StationView.h"
//#include "NtList.h"
#include "GameNoteWnd.h"
//#include "PlaySetDlg.h"
//#include "GameInfoDlg.h"
//#include "GameEndInfoDlg.h"
//#include "BackCardDlg.h"
#include "HaveThing.h"
#include "LeaveMessage.h"
#include "GameCard.h"
#include "LaiZhiDlg.h"
//#include "Stop.h"
//#include "StopMessage.h"
#include "GameFinishDlg.h"
#include "DisplayTalkDialog.h"	//聊天框
#include "Animal.h"
#include "CardAnimal.h"
#include "CombineAnimal.h"

class CUpGradeDlg;
class CUpGradeView;

//控件 ID
#define IDC_OUT_CARD				121				//出牌按钮
#define IDC_CONTINUE				124				//继续按钮
#define IDC_LAST_CARD				125				//上轮按钮
#define IDC_HAVE_THING				127				//有事要走
#define IDC_AUTOCARD				130				//托管
#define IDC_PASS					132				//不出
#define IDC_SORT_CARD				133				//排序
#define IDC_CUE						134				//提示
#define IDC_CALL_SCORE_PASS			140				//叫分类型
#define IDC_CALL_SCORE_1			141				//叫分类型
#define IDC_CALL_SCORE_2			142				//叫分类型
#define IDC_CALL_SCORE_3			143				//叫分类型
#define IDC_LEAVE					144				//离开类型
#define IDC_ROB_NT					145				//抢地主
#define IDC_ROB_NT_2				146				//不抢
#define IDC_ADD_DOUBLE				147				//加棒
#define IDC_ADD_DOUBLE_2			148				//不加棒
#define IDC_SHOW_CARD				149				//亮牌
#define	IDC_SHOW_CARD_2				150				//不亮
#define IDC_STARTDISPLAY			151				//明牌开始按钮

//梭哈视图类
class CClientPlayView : public CUsingSkinClass//CGDIPlayView
{
	bool							m_bInit;
	//程序变量
protected:
	CPoint							m_PtNt[PLAY_COUNT];							//庄家和盟友位置
	CPoint							m_PtAuto[PLAY_COUNT];						//托管坐标
	CPoint							m_PtAwardPoint[PLAY_COUNT];					//奖分情况
	CPoint							m_PtSequence[PLAY_COUNT];					//出牌先后顺序
	CPoint							m_PtPass[PLAY_COUNT];						//放弃
	CPoint							m_PtLastCardFlag[PLAY_COUNT];				//最后一手牌标记
	CPoint							m_PtGetPoint[PLAY_COUNT];					//抓分显示坐标
	CPoint							m_PtDeskTempPoint;					//桌面临时分
	CPoint							m_PtDeskMultiple;					//桌子倍数
	CPoint							m_PtRoomMultiple;					//房间倍数
	CPoint							m_PtGameMultiple;					//房间倍数
	CPoint							m_PtCallScore[PLAY_COUNT];						//叫分坐标
	CPoint							m_PtCallScoreResult;					//叫分结果(斗地主等游戏中会出现)
	CPoint							m_PtCallScoreNT;						//叫分庄家
	CPoint							m_PtGameTitle;						//游戏标题logo坐标
	CPoint							m_PtBottomCue;						//游戏提示
	CPoint							m_PtPeopleMul[PLAY_COUNT];					//玩家加棒显示位置
	CPoint							m_PtShowMsg;						//
	CPoint                          m_PtGif[PLAY_COUNT];
	CPoint                          m_PtLaiZhi;                         //赖子坐标
	//当前出牌者方向坐标
	CPoint							m_PtCurOrientation[PLAY_COUNT];						//游戏标题logo坐标
	//当前桌面提示坐标
	CPoint							m_PtDeskCue;								//桌面提示坐标
	//扑克索引
	POINT							ptCardPoint[PLAY_COUNT];
	POINT							ptHandCard[PLAY_COUNT];
	POINT							ptBackCard;							//底牌
	int								m_Bt1WidthSpace;					//右边按钮坐标
	int								m_Bt1HeightSpace;
	int								m_Bt2WidthSpace;					//叫分按钮
	int								m_Bt2HeightSpace;

	int								m_iDeskTempPoint;					//桌面上的分数(临时分)
	int								m_iDeskMultiple;					//桌子倍数
	int								m_iRoomMultiple;					//房间倍数
	int								m_iGameMultiple;					//游戏倍数
	

	int								m_iPass[PLAY_COUNT];							//本轮玩家押注总数

	int								m_iCallScore[PLAY_COUNT];				//各家叫分
	int								m_iCueType;								//提示方式


	CString                         m_strCoinName ;                      ///玩家金币名称

	bool                            m_bShowLogo ;                        ///是否显示玩家头像
	bool                            m_bShowMoney ;                       ///是否显示玩家金币

public:
	CToolTipCtrl					m_ToolTip;					//提示文字
	CPoint							m_PtSBomb[3];				//小炸弹位置
//	CDisplayTalkDialog				m_dlgDisTalk[PLAY_COUNT];	//聊天框
	BYTE							m_iCurOrientation;			//当前出牌者方向
	bool							m_bFirstGame;				//是否新进入桌子
	//图片
	BYTE                            m_bLaiCardList[4];          //赖子
	CGameImage						m_bit_background;			//背景填充小图
	CGameImage						m_Background;	//背景贴图(大贴图)
	CGameImage						m_GameTitleLogo;//游戏名称logo
	CGameImage						m_NT;			//庄家标识	
	CGameImage						m_NT2;		//庄家标识	
	CGameImage						m_AwardPint;	//奖分情况
	CGameImage						m_CallScore;		//叫分图片
	CGameImage						m_AutoLogo;		//托管标识
	CGameImage						m_Pass;			//pass图示
	CGameImage						m_LastCardFlag;	//最后一手牌提示图标
	CGameImage						m_PicSequence;	//出牌先后顺序提示图标
	CGameImage						m_PicBottomCue;	//出牌先后顺序提示图标
	CGameImage						m_PeopleMul;	//出牌先后顺序提示图标
	CGameImage						m_ShowMsg;	    //出牌先后顺序提示图标
	CGameImage						m_ImgFangXiang;		//方向图片	
    CGameImage                      m_Num;
	CGameImage                      m_LaiZhi;          //赖子
	CGameImage                      m_ImgCard;         //赖子牌
	CGameImage						m_ImgSmlLaiz;	   //小癞子显示在左上角
	//动画图片(090329a1 JJ)
	CGameImage						m_ImgAnimalDZWin;			//地主赢
	CGameImage						m_ImgAnimalDZLose;			//地主输
	CGameImage						m_ImgAnimalSmallBomb;		//小炸弹
	CGameImage						m_ImgAnimalBBFire;			//大炸弹火焰
	CGameImage						m_ImgAnimalBBCardNormal;	//大炸弹普通牌
	CGameImage						m_ImgAnimalBBCardBack;		//大炸弹牌背和大小王
	CGameImage						m_ImgAnimalBBStar;			//大炸弹星星

	CUpGradeGameCard				m_MeCard;					//自己的扑克
	CUpGradeGameCard				m_MeBackCard;				//底牌
	CUpGradeGameCard				m_UserCard[PLAY_COUNT];		//用户扑克
	CUpGradeGameCard				m_HandCard[3];				//用户手中扑克
	CUpGradeGameCard                m_ThreeCard;                //二人斗地主中不发人的扑克 

	CLeaveMessage					m_ThingMessage;				//离开消息
	CGameNoteWnd					m_GameNoteView;				//游戏信息
	CGameFinishDlg					m_Result;				//游戏结束信息
	CLaiZhiDlg                      m_SelectLaiZhi;            //赖子选择框

//	CStationView					m_StationView;				//状态窗口
	CNormalBitmapButtonEx			m_btOutCard;				//出牌按钮
	CNormalBitmapButtonEx			m_btPass;					//不出
	CNormalBitmapButtonEx			m_btCue;					//提示

	CNormalBitmapButtonEx			m_btContinue;				//继续按钮
	//CNormalBitmapButtonEx			m_btStartDisplayCards;		//明牌开始按钮 无用 
	CNormalBitmapButtonEx			m_btLeave;				    //离开按钮
	CNormalBitmapButtonEx			m_btAuto;					//托管按钮
	CNormalBitmapButtonEx			m_btThing;					//有事要走
	CNormalBitmapButtonEx			m_btSortCard;				//排序

	CNormalBitmapButtonEx			m_btRobNT;				//抢地主
	CNormalBitmapButtonEx			m_btRobNT2;				//不抢
	CNormalBitmapButtonEx			m_btAddDouble;			//加棒
	CNormalBitmapButtonEx			m_btAddDouble2;			//不加棒

	CNormalBitmapButtonEx			m_btShowCard;			//亮牌
	CNormalBitmapButtonEx			m_btShowCard2;			//不亮

	CNormalBitmapButtonEx			m_btLastTurn;				//上一轮

	//动画类(090329a1 JJ)
	CAnimal							m_AnimalResult;			//结束后动画(地主输,地主赢)
	CAnimal							m_AnimalBomb[3];		//3位玩家小炸弹动画
	//CCardAnimal						m_AnimalCard;		//牌动画
	CCombineAnimal					m_AnimalBigBomb;		//3位玩家大炸弹动画

	CHaveThing						m_HaveThing;						//有事离开
	BYTE							m_iAwardPoint[PLAY_COUNT];			//四家奖分情况
	bool							m_bAuto[PLAY_COUNT];				//托管标记
	int								m_iPeopleMul[PLAY_COUNT];			//玩家是否加棒
	int								m_iNtStation;						//庄家位置

	BOOL                            m_bIsFakeBomb;                      //是否为软炸
 public:
		//====叫分情况
	CNormalBitmapButtonEx			m_btCallScorePass;		//不叫
	CNormalBitmapButtonEx			m_btCallScore1;			//不叫
	CNormalBitmapButtonEx			m_btCallScore2;			//不叫
	CNormalBitmapButtonEx			m_btCallScore3;			//不叫

private:
	COLORREF			m_NameColor;						//显示用户颜色
#ifdef VIDEO
public :
	BOOL					m_bWatch;    ///自己是否为观战
	CGameImage				m_pVideoFrame;    ///视频背景
	CRect					m_rectVideoFrame[MAX_PEOPLE];  ///视频背景坐标
	BOOL					GetVideoRect(CString  strNickname, RECT& rect, CString& pic);
	CPlayVideo		         m_PlayVideo;
#endif
public:
	void SetNameColor(COLORREF rgb)	{m_NameColor=rgb;	}
	//函数定义
public:
	//构造函数
	CClientPlayView();
	//析构函数
	virtual ~CClientPlayView();
	
	int x;
	//重载函数
public:
	//重置界面函数
	virtual void ResetGameView();
	//绘画界面函数
	virtual void DrawViewFace(CDC * pDC, int iWidth, int iHeight);
	//更新用户资料
	virtual void UpdateUserInfo(BYTE bViewStation);

	virtual void FixControlSize(int,int);
	//功能函数
public:
	void DrawInfo(CDC *pDC);
	void TransparentBlt2( HDC hdcDest,      // 目标DC
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
	//建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

public:
	//设置背景色
	void SetBackBmp(UINT uResourceID, TCHAR * szFileName=NULL, BOOL bResource=TRUE);
	//绘制背景填充小图
	void DrawBk(CDC *pDC,int iWidth, int iHeight);
	//绘制游戏logo
	void DrawGameTitle(CDC *pDC);
	//设置庄家位置
	void SetNTStation(int iViewStation=-1);
	//绘画 NT 标志
	void DrawNt(CDC * pDC, int x, int y);
	//绘画农民标志
	void DrawFarmer(CDC * pDC, int x, int y);
	//绘画 NT 图标
	void DrawNtLogo(CDC * pDC, int x, int y, int iHuaKind);
	DECLARE_MESSAGE_MAP()
	//按钮消息函数
protected:
	//开始按钮
	void OnHitBegin();
	//明牌开始按钮
	void OnHitBeginDisplayCards();
	//离开
	void OnHitLeave();	
	//出牌按钮
	void OnHitOutCard();
	//继续按钮
	void OnHitContinue();

	//有事要走
	void OnHitThing();
	//投降
	void OnHitTuoxiang();
public:
	//比赛场设置
	void DrawFen(CDC * pDC);
public:
	void OnHitAuto(void);

	void SetCallScoreValue(BYTE bViewStation,int iCallScore);
	
	int m_iCallScoreResult;

	void SetCallScoreResult(int iCardCount = 0);		//叫分结果
	//托管
	void SetAuto(int bDeskStation,bool bAuto);
	//绘制托管
	BOOL DrawAuto(CDC * pDC);
	//设置奖分
	void SetAwardPoint(BYTE iViewStation,BYTE iAwardPoint);
	//繪製將分
	void DrawAwardPoint(CDC *pDC);
	//
	void OnHitCallScore(UINT uID);
	//
	void OnCue();	//提示
	//
	void OnHitPass();
	//
	void OnHitSort();
	//設置房间倍数
	BOOL SetRoomMultiple(int iRoomMultiple = 0);
	//绘制房间倍数
	BOOL DrawRoomMultiple(CDC *pDC);
	//设置游戏倍数
	BOOL SetGameMultiple(int iGameMultiple = 0);
	//绘制游戏倍数
	BOOL DrawGameMultiple(CDC *pDC);
	//绘制叫分结果
	BOOL DrawCallScoreResult(CDC *pDC);
	//设置桌面倍数
	BOOL SetDeskMultiple(int iDeskMultiple= 0);
	//绘制桌面倍数
	BOOL DrawDeskMultiple(CDC *pDC);
	//设置桌面临时分
	void SetDeskTempPoint(int iDeskTempPoint = 0);
	//增加桌面临时分
	void AddDeskTempPoint(int iDeskTempPoint);
	//绘制桌面临时分
	BOOL DrawDeskTempPoint(CDC *pDC);
	//绘制底部提示
	BOOL DrawBottom(CDC * pDC);
	//放弃
	void DrawPass(CDC *pDC);
	//设置放弃
	void SetPass(BYTE iViewStation,int iGiveup);
	//获取扑克数值
	BYTE GetCardValue(BYTE bCard) 
	{ 
		//return (bCard&UG_VALUE_MASK);
		BYTE bkk=(bCard&UG_VALUE_MASK)+1;
		if (bkk==14) bkk=1;
		return bkk; 
	}
	//获取扑克花色
	BYTE GetHuaKind(BYTE bCard) { return bCard&UG_HUA_MASK; };
	//获取扑克位置
	BYTE GetCardXPos(BYTE bCard) { return GetCardValue(bCard)-1; };
	//获取扑克位置
	BYTE GetCardYPos(BYTE bCard) { return GetHuaKind(bCard)>>4; };
///////////////////////////////////////////////////////////////////////////
	CUpGradeGameCard		m_DeskCard;		//桌面上牌(用来显示发牌动画)
	CUpGradeGameCard		m_SendCard[PLAY_COUNT];		//桌面上牌(用来显示发牌动画)

	BOOL				m_bHaveSendCardAnimal[PLAY_COUNT];					//发牌动画控制变量
	CPoint				m_PtStart[PLAY_COUNT];								//发牌动画活动坐标
	CPoint				m_PtSendCardEnd[PLAY_COUNT];							//发牌动画结束点坐标
	CPoint				m_PtSendCardStart[PLAY_COUNT];						//发牌动画起始点坐标

	void				SetSendCardPointStart(BYTE iViewStation);	//设置发牌动画起始坐标
	void				SendCardAnimal();							//发牌动画函数

///////////////////////////////////////////////////////////////////////////
	//聊天框
	void DisplayTalkMsg(int Viewstation,TCHAR * szCharString);
	//提示文字
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//方向
	void SetOrientation(BYTE bDeskStation);
	//绘制方向
	BOOL DrawOrientation(CDC *pDC);
	//聊天框初始化
	void Init();
	//根据游戏加载坐标
	void LoadSkinIni(int cx,int cy);
	//根据坐标重新移动
	void MoveScreen(int cx,int cy);
	//抢地主
	void OnHitRobNT();
	//不抢地主
	void OnHitRobNT2();
	//加棒
	void OnHitAddDouble();
	//不加棒
	void OnHitAddDouble2();
	//加棒
	void OnHitShowCard();
	//不加棒
	void OnHitShowCard2();
	//上一轮
	void OnHitLastTurn();
	//设置玩家倍数
	void SetPeopleMultiple(BYTE bViewStation,int iVal = 1);
	//绘制玩家倍数
	void DrawPeopleMultiple(CDC *pDC);
	//绘制玩家叫分结果和倍率背景图
	void DrawShowMsg(CDC *pDC);
	//设置赖子
	void SetLai(BYTE iCard);
	//画赖子
	void DrawLai(CDC *pDC);
};
