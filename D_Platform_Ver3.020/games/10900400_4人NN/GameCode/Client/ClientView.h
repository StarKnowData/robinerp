#pragma once

#include "StdAfx.h"
#include "Resource.h"
//#include "StationView.h"
//#include "GameNoteWnd.h"
//#include "PlaySetDlg.h"
//#include "GameInfoDlg.h"
//#include "GameEndInfoDlg.h"
//#include "BackCardDlg.h"
//#include "HaveThing.h"
//#include "LeaveMessage.h"
#include "GameCard.h"
//#include "Stop.h"
//#include "StopMessage.h"
#include "ShowNoteBtn.h"
#include "GameFinishDlg.h"
#include "BeginAnimal.h"
//#include "EndAnimal.h"
#include "NoteAnimal.h"
#include "CeasyNtList.h"
#include "GameNoteWnd.h"
#include "CardShape.h"


class CUpGradeDlg;
class CUpGradeView;

#define ID_BEGIN_ANIMAL					10001			//开始动画
#define ID_NOTE_ANIMAL_ZERO				10002			//下注动画
#define ID_NOTE_ANIMAL_ONE				10003			//下注动画
#define ID_NOTE_ANIMAL_TWO				10004			//下注动画
#define ID_NOTE_ANIMAL_THREE			10005			//下注动画
#define ID_SEND_CARD_ANIMAL				10006			//发牌动画
#define ID_COLLECT_JETON_ANIMAL			10007			//收集筹码
#define WM_SETMESSAGE					10008			//动画信息
#define WM_SENDCARD_SHOWCARD			10009			//发牌后显示各家牌

//控件 ID
#define IDC_CONTINUE					124				//继续按钮
#define IDC_LEAVE						125				//离开
//#define IDC_LAST_CARD					125				//上轮按钮
//#define IDC_BACK_CARD					126				//底牌按钮
#define IDC_HAVE_THING					127				//有事要走
#define IDC_STOP						128				//停止本局
#define IDC_AUTO						129				//托管
#define IDC_SHUTTLE						135				//梭了按钮
#define IDC_NOTADD						137				//不加按钮
#define IDC_CALL_SCORE_PASS				140				//叫分类型
#define IDC_CALL_SCORE_1				141				//叫分类型
#define IDC_CANSOUND					142				//用户设置声音
#define IDC_BGSOUND						143				//背景音乐
#define MAX_JETON						16				//最大筹码数
#define MAX_NOTEJEONT					50				//最多支持50个筹码显示在桌面正中
#define NOTEVIEW						150				//等待中

//梭哈视图类
class CClientPlayView : public CUsingSkinClass//CGDIPlayView
{
//程序变量
public:
	BOOL						m_bIsNote[PLAY_COUNT];				//是否有下注动画
	bool                        m_bDraw;                            //是否绘下注
	bool						m_bIsSendCard[PLAY_COUNT];			//谁有发牌
	int						    m_bOpenCard[PLAY_COUNT];			//摊牌
	int							m_flag;								//记发牌中的玩家
	int                         m_iGetPoint[PLAY_COUNT];            //玩家明牌得分
	int                         m_iShape[PLAY_COUNT];
	int                         m_iGetPointSplit[PLAY_COUNT];       //玩家明牌得分 
	//int							m_iThisTurnAddNote;				//本次要在玩家手中添加数
	int							m_iNoteJeontTimes;					//用户下注筹码计数
	int							m_NoteStart;						//下注位置
	BYTE                        m_GameType;							//游戏种类。0为普通。1为同喜乐
	BYTE                        m_iGameNoteSetType;                 //游戏筹码设置类型

	//全部筹码视图
	//CNoteAnimal					m_NoteAll[MAX_NOTEJEONT];		//用户下注筹码总视图
	//CNoteAnimal					m_NoteAnimal;					//用户下注动画
	//CNoteAnimal					m_NoteTotal[PLAY_COUNT];	
	CPoint						m_NoteAllPoint[MAX_NOTEJEONT];
	//CUpGradeGameCard			m_SendCardAnimal[PLAY_COUNT];		//发牌动画使用的牌
	//CBeginAnimal				m_BeginAnimal;						//开始动画
	//CUpGradeGameCard			m_FlashCard;						//发扑克动画效果
	CGameNoteWnd			    m_GameNoteView;						//游戏信息

	
protected:
	CPoint				m_PtAuto[PLAY_COUNT];							//用户拖管
	CPoint				m_PtNote[PLAY_COUNT];							//用户押注位置
	CPoint				m_PtNoteTotal[PLAY_COUNT];						//用户总注
	CPoint				m_PtNoteLimit[PLAY_COUNT];						//本轮下注上限
	CPoint				m_PtFace[PLAY_COUNT];							//玩家闲像显示位置
	CPoint				m_PtScore[PLAY_COUNT];							//用户筹码数
	CPoint				m_PtPass[PLAY_COUNT];							//放弃
	CPoint				m_PtJeton[PLAY_COUNT];							//下注筹码位置
	CPoint				m_PtShowLimit;									//显示用户下注极限
	CPoint				m_PtNoteAll;									//用户下注全部筹码所在位置
	CPoint				m_PtBeginAnimalStart;							//开始动画起点
	CPoint				m_PtBeginAnimalEnd;								//开始动画终点
	CPoint				m_PtGameTitle;									//游戏标题logo坐标
	CPoint              m_PtPeopleBk[PLAY_COUNT];						//人物背景图坐标
	CPoint              m_PtNt[PLAY_COUNT];								//明牌标志坐标
	CPoint				m_PtGetPoint[PLAY_COUNT];						//抓分显示坐标
    CPoint              m_PtShape[PLAY_COUNT];							//牌型标志
	CRect				m_BtnRect0,m_BtnRect1,m_BtnRect2,m_BtnRect3;	//矩形框
	CPoint              m_PtGif[PLAY_COUNT];							//动画
	CPoint				m_PtOpenCard[PLAY_COUNT];						//摊牌
public:
	//下注动画静态坐标系
	CPoint				m_PtNoteAnimalStart[PLAY_COUNT];				//开家开始下注动画视图坐标
	CPoint				m_PtNoteAnimalEnd[PLAY_COUNT];					//下注动画结束坐标
	//用户信息
//	int					m_iHuaKind;						//主牌花色
//	int					m_iShowStation;					//报主位置
	int					m_iNtStation;					//庄家位置
	int                 m_nPowerOfGold;             	//金币倍率

	//控件变量
public:
	CGameImage				m_Jeton;					//标志图标
	//图片
	CGameImage				m_bit_background;			//背景填充小图
	CGameImage				m_Background;				//背景贴图(大贴图)
	CGameImage				m_GameTitleLogo;			//游戏名称logo
	CGameImage				m_Pass;						//pass图示
	CGameImage              m_PeopleBk1;				//人物背景1
	CGameImage              m_PeopleBk2;				//人物背景2
	CGameImage              m_PeopleBk3;				//人物背景3

	CGameImage              m_Ming;						//明牌标志
	CGameImage				m_HuangGuan;				//皇冠
	CGameImage				m_PicGreenNum;				//绿色数字
	CGameImage              m_NoteKuan;					//筹码框
	CGameImage				m_PicNum;					//时间数字
	CGameImage				m_PicSmallNum;				//小时间数字
	CeasyNtList			    m_NtList;
	CShowNote			    m_ShowNote;					//显示按钮
	
	CUpGradeGameCard		m_UserCard[PLAY_COUNT];		//用户扑克
    CUpGradeGameCard        m_UserBull[PLAY_COUNT];
	//CUpGradeGameCard		m_SysBackCard;				//系统牌显示

	CGameFinishDlg			m_Result;					//游戏结束信息

	CCardShape             m_CardShape[PLAY_COUNT]; // 四个玩家的牌型

	CNormalBitmapButtonEx			m_btContinue;		//继续按钮
	CNormalBitmapButtonEx			m_btLeave;			//离开
	CNormalBitmapButtonEx           m_btReset;          //要牌
	CNormalBitmapButtonEx           m_btOpen;           //不要牌
	CNormalBitmapButtonEx           m_btBull;           //加倍
	CNormalBitmapButtonEx           m_btChangeShin;     //换肤

			//====叫分情况
	CNormalBitmapButtonEx			m_btCallScorePass;					//不叫
	CNormalBitmapButtonEx			m_btCallScore1;						//不叫
	CGameImage						m_PicLeftLogo;						//顶端贴图
	CGameImage						m_PicLogoface;						//头像贴图
    CGameImage                      m_Waiting;                          //等待贴图
	CGameImage						m_PicScore;							//用户当下注分
	CGameImage                      m_Nt;                               //庄
	CGameImage                      m_WinFen;                           //赢分
	CGameImage                      m_LossFen;                          //输分
	CGameImage                      m_Niu;                              //牛
	CGameImage                      m_Niu_n;                            //无牛
	CGameImage                      m_Nn;                               //牛牛
	CGameImage                      m_ImgJn;                            //金牛
	CGameImage                      m_ImgYn;                            //银牛
	CGameImage                      m_ImgBomb;                          //炸弹
	CGameImage                      m_ImgFive;                          //五小
	CGameImage                      m_Num;                              //牛数字
	CGameImage						m_imgOpenCard;						//摊牌
	CGameImage                      m_imgScoreRule;                     //积分规则示意图
	__int64							m_iNotePoint[PLAY_COUNT];			//用户押注数
	__int64							m_iNoteTotalPoint;					//总注
	__int64							m_iNoteLimit;						//本轮上限
	__int64                         m_iMingLImit;                       //明注最大
	int                             m_iAnLImit;
	__int64                         m_iBaseNote;                        //底注
	int								m_iThisTurnNote[PLAY_COUNT];		//本轮玩家押注总数
	int								m_iPass[PLAY_COUNT];				
	BOOL                            m_bMing[PLAY_COUNT];                //明牌
	BOOL                            m_bWait;                            //画等待图片
	
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
	bool		m_bClass3DInfo;

	CString     m_strMoneyType;									//金币名称

	CUpGradeGameCard				m_SendCardAnimal[4];		//发牌动画使用的牌
	CUpGradeGameCard				m_FlashCard;				//发扑克动画效果

	ULONG_PTR						m_gdiplusToken;				/**< GDI+*/
	Image*							m_pImgBackground[4];		//背景图片数组
	int								m_iCurrentBG;				//当前背景图片
	GameFinishNotify				m_ViFinish;					//结算数据
	bool							m_bShowResult;				//是否显示结算;
	CString							m_ShapeName[15];

private:
	COLORREF						m_NameColor;				//显示用户颜色
	int								m_iJetonCount;				//筹码总数
#ifdef VIDEO
public :
	BOOL					m_bWatch;    ///自己是否为观战
	CGameImage				m_pVideoFrame;    ///视频背景
	CRect					m_rectVideoFrame[MAX_PEOPLE];  ///视频背景坐标
	BOOL					GetVideoRect(CString  strNickname, RECT& rect, CString& pic);
	CPlayVideo				m_PlayVideo;
#endif
public:
	void SetNameColor(COLORREF rgb)	{m_NameColor=rgb;}
	//函数定义
public:
	//构造函数
	CClientPlayView();
	//析构函数
	virtual ~CClientPlayView();
	//重载函数
public:
	//重置界面函数
	virtual void ResetGameView();
	//绘画界面函数
	virtual void DrawViewFace(CDC * pDC, int iWidth, int iHeight);
	//更新用户资料
	virtual void UpdateUserInfo(BYTE bViewStation);
	//位置调整
	virtual void FixControlSize(int,int);
	//重新绘用户头像
//	virtual void DrawLogo(CDC *pDC,BYTE iViewStation,int iXPos,int iYPos,BOOL bBoy,BOOL bCut=false);
	//功能函数
public:
	//绘制背景填充小图
	void DrawBk(CDC *pDC,Image *pImage,int iWidth, int iHeight);
	//绘制游戏logo
	void DrawGameTitle(CDC *pDC,int iWidth,int iHeight);
	void DrawInfo(CDC *pDC);
	void TransparentBlt2( HDC hdcDest,        // 目标DC
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

public:
	//设置背景色
	void SetBackBmp(UINT uResourceID, TCHAR * szFileName=NULL, BOOL bResource=TRUE);
	//设置庄家位置
//	void SetNTStation(int iViewStation=-1);
	//设置报主位置
	void SetShowNtStation(int iViewStation=-1, int iHuaKind=0);
	//设置游戏分数
	void SetGamePoint(int iGamePoint=0, int bMeSide=-1);
	//绘画 NT 标志
	//void DrawNt(CDC * pDC, int x, int y);
	//绘画 NT 图标
	//void DrawNtLogo(CDC * pDC, int x, int y, int iHuaKind);
	//绘画明牌标志
	void SetMing(BYTE iViewStation,BOOL iGiveup);
     //设置是否绘等待图片 
	void SetWait(BOOL wait=0);

	DECLARE_MESSAGE_MAP()
	//按钮消息函数
protected:
	//开始按钮
	void OnHitBegin();
	//继续按钮
	void OnHitContinue();
	//托管
	void OnHitAuto();
	//提前停止
	void OnHitLeave();
	//上轮扑克
	//void OnHitLastTurn();
	//底牌按钮
	//void OnHitLookBack();
	//有事要走
	void OnHitThing();
	//提前停止
	void OnHitStop();
	//下注
	void OnNote();
	////弃
    void OnOver();
	//要牌
	void OnReset();
	//不要
	void OnBull();
	//加倍
	void OnOpen();
	//
	void OnHitCallScore(UINT uID);

	//换肤
	void OnChangeShin();

	void SetAuto(int bDeskStation,bool bAuto);
	//画托管图标
	void DrawAutoLogo(CDC * pDC, int x, int y);
public:
//	static CBitmap				m_Back_Center;
//	static BITMAP				m_Back_Center_Info;
//	static CBitmap				m_Bitmap_Num;
	BOOL						m_bRightPower;
	BOOL						m_bMeSide;					//是否本方得分
	int							m_iGamePoint;				//游戏分数
	BOOL						m_bAuto[PLAY_COUNT];		//托管状态
	//设置押注分
	void SetNotePoint(BYTE iViewStation,__int64 iNotePoint=0);
	//设置本轮下注分
	//void SetThisTurnNotePoint(BYTE iViewStation,int iThisTurnPoint=0);
	//增加本轮下注数
	//void AddThisTurnNotePoint(BYTE iViewStation,int iThisTurnPoint);
	//加注
	void AddNotePoint(BYTE iViewStation,__int64 iNotePoint);
	//总注
	//void AddTotalNote(BYTE iViewStation,int iNoteTotal);
	//设置总注
	//void SetTotalNote(BYTE iViewStation,int iNoteTotal);
	//设置最大注
	void SetMingLImit(int limit,int an=0);
	//绘制押注分
	//void DrawNote(CDC *pDC);
	//设置本轮押注上限
	void SetLimitNote(BYTE iViewStation,__int64 iNoteLimit,__int64 iBaseNote);
	//画分
	void DrawNum(CDC * pDC, int iXPos, int iYPos, UINT Num,int offset,BOOL bThousand=false);
	//画分
	void DrawSmallNum(CDC * pDC, int iXPos, int iYPos, int Num,int offset,BOOL bIsFourOrSix=FALSE/*显示四位还是六位*/,BOOL bIsPlus=TRUE,/*是否为正数*/BOOL bThousand=FALSE/*是否用到K*/);	
	//画头像上下注框
	void DrawScore(CDC * pDC, int x, int y);
	//放弃
	void DrawPass(CDC *pDC);
	//画明牌
	void DrawMing(CDC *pDC);
   //画等待
	void  DrawWait(CDC *pDC, int iWidth,int iHeight);
	//
	//画分
	void DrawGreenNum(CDC * pDC, int iXPos, int iYPos, int Num,int offset,BOOL bIsFourOrSix=FALSE/*显示四位还是六位*/,BOOL bIsPlus=TRUE,/*是否为正数*/BOOL bThousand=FALSE/*是否用到K*/);
	//画分
	BOOL DrawGetPoint(CDC *pDC);

	//设置放弃
	void SetPass(BYTE iViewStation,int iGiveup);
	//设置庄家
	void SetNTStation(int iViewStation = -1);
	//画庄家
	void  DrawNt(CDC *pDC);
public:
	//开始动画
	void BeginAnimal(void);
	//下注动画,iViewStation位置
	void NoteAnimal(BYTE iViewStation);
	//绘制背景图
	void DrawBackPic(CDC* pDC,int iWidth,int iHeight);
	//初始化某位置动画起始坐标
	void SetNoteAnimalPoint(BYTE iViewStation);
	//设置本次添加数
	//void SetAddNote(int iAddNote){m_iThisTurnAddNote=iAddNote;}
	//起始动画坐标
	CPoint m_iNoteAnimalPointStart[PLAY_COUNT];
	//收集筹码起始坐标
	CPoint m_PtCollectJetonStart[PLAY_COUNT];
	//设置起始坐标动画
	void SetNotePointStart(BYTE iViewStation);
	//发牌动画
	void SendCardAnimal(BYTE iViewStation, bool split = false);
	//发牌动画牌开始位置
	CPoint m_iSendCardAnimalPointStart[PLAY_COUNT];
	//发牌各位置起始坐标
	CPoint m_PtSendCardAnimalStart[PLAY_COUNT];
	//发牌动画中各位置终点坐标;		
	CPoint	m_PtSendCardAnimalEnd[PLAY_COUNT];
	//分牌位置的发牌动画终点
	CPoint	m_PtSendCardAnimalEndSplit[PLAY_COUNT];
	//设置发牌动画起始位置
	void SetSendCardPointStart(BYTE iViewStation);
	//设置收集筹码起始坐标
	void SetCollectJetonStart();
	//收集筹码动画
	void CollectJetonAnimal();
	//设置加筹码数
	void SetAddJeton(int iBaseNote);
	//显示中间一堆筹码
	void ShowAllNote();
	//设置筹码堆数
	void SetAddTimes(int iTimes);
	//设置开始动画位置
	void SetBeginAnimalPos();
	//开始动画可变坐标
	CPoint m_PtBeginAnimal;
	//设置牌面点
	void SetGetPoint(BYTE iViewStation,int iGetPoint);
	//设置牌分牌面点
	void SetGetPointSplit(BYTE iViewStation,int iGetPoint);
	//画牌型
	void  DrawShape(CDC *pDC,int x,int y,int shape);
	//设置牌型
	void SetShape(BYTE iViewStation,int Shape);
	//画下注按钮
	void CClientPlayView::DrawNoteBt(CDC *pDC);
	//画摊牌标识
	void DrawOpenCard(CDC *pDC);
	void SetDrawNote(bool draw = false);
	void OnNote(int type);
	void DrawMoney(CDC *pDC);
	/// 依当前金币倍率得到显示字符串
	void GetNumString(__int64 nNum, CString &Str, int nPower);
	// 发牌动画
	void SendCard(BYTE byViewSeat, int iTime);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//绘制头像框
	void DrawLogoBJ(int iView,CDC *pDC,int iXPos,int iYPos);
};
