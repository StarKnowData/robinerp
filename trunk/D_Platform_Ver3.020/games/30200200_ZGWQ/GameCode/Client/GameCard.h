#pragma once

#include "StdAfx.h"

//声明名字空间
//using namespace AFC::AFCImage;

//消息定义
#define	IDM_LEFT_HITCARD			WM_USER+110						//左击扑克
#define	IDM_RIGHT_HITCARD			WM_USER+111						//右击扑克
#define IDM_SUPER_TIMER				WM_USER+113						//超时
#define IDM_MOVE_ONCARD				WM_USER+115						

//操作掩码
#define	UG_HUA_MASK					0xF0							//花色掩码
#define	UG_VALUE_MASK				0x0F							//数字掩码
void  Testlog(TCHAR *pMessage);
//扑克控制类
class CUpGradeGameCard : public CWnd
{
	//枚举定义
public:
	enum XShowMode { SWX_MODE_LEFT, SWX_MODE_CENTER, SWX_MODE_RIGHT };
	enum YShowMode { SWY_MODE_TOP,  SWY_MODE_CENTER, SWY_MODE_BOTTOM }; 
	
	CDC userDC;
	//变量定义
protected:
//	int								m_iCardHight;					//扑克高度
//	int								m_iCardWidth;					//扑克宽度
//	int								m_iCardHSpace;					//扑克间隔
//	int								m_iCardVSpace;					//扑克间隔
//	int								m_iCardUpSpace;					//跳起高度
//	CRgn							m_CardViewRgn;					//扑克区域
	CWnd							* m_pHandleWnd;					//处理窗口
	
	int								initFlag;			//初始化棋盘
	int								m_iQZiWidth;
	int								m_iBoard[21][21];	//棋局
	int								m_iMeFlag;			//我方标志
	int								m_iCurPlay;			//当前走子方;
	BOOL							m_bInitBoard;		//初始化棋盘
	int								m_iBoardWidth;		//棋盘宽度
	int								m_iBoardHeight;		//棋盘高度
	
	int								m_iStartI,			//走子起始点
									m_iStartJ,
									m_iEndI,			//走子终点
									m_iEndJ;
	BOOL							m_bIsPlay;			//是否走子
public:
	int								m_iJuMin;			//局时
	int								m_iJuSec;
	int								m_iBuMin;
	int								m_iBuSec;
	int								m_iDuMin;
	int								m_iDuSec;

	int								m_iTopJuUseTime;//上方用时
	int								m_iTopBuUseTime;
	int								m_iTopDuUseTime;
	int								m_iBotJuUseTime;//下方用时
	int								m_iBotBuUseTime;
	int								m_iBotDuUseTime;
	
	UserItemStruct					*m_pUserInfo[2];//用户信息


	int								m_iFocusX;
	int								m_iFocusY;

	int								m_iTiZiNum[2];		//提子数
	bool							m_bUseMouseFlag;	//使用鼠标标志

	CString							m_strFinishMessage;	//结束信息
	bool							m_bIsFinish;		//是否结束
public:
	int								m_iQiZiNum[2];		//目数已下棋子数

#ifdef	VIDEO
	public:
		CPoint							m_PtVideo[2];					//用户视频窗口位置
	public:
		CGameImage						m_pVideoFrame;					//视频背景
#endif

	//信息变量
protected:
	//bool							m_bShowCard;					//显示扑克
//	bool							m_bHorzLook;					//是否横放
	bool							m_bUseMouse;					//响应鼠标
	//BYTE							m_bHotHitCard;					//焦点扑克
	//BYTE							m_bCardCount;					//扑克数目
	CPoint							m_PtBasePoint;					//基准坐标
	XShowMode						m_XShowMode;					//显示模式
	YShowMode						m_YShowMode;					//显示模式
	//CByteArray						m_CardArray;					//扑克数组
//	CByteArray						m_CardUpArray;					//扑克数组

	//图片变量
protected:
//	CAFCImage						m_CardPic[2];					//扑克控件
	//CGameImage						m_CardPic[2];					//扑克控件
	
	CGameImage						m_BoardPic;//棋盘
	
	CGameImage						m_bitFocus;//走子标志
	CGameImage						m_bitBlack,//黑子
									m_bitWhite,//白子
									m_bitCurBlack,//当前黑子
									m_bitCurWhite,//当前白子
									m_bitHeiGuan,//黑棋罐
									m_bitBaiGuan,//白棋罐
									m_bitBCross,//
									m_bitWCross;//


	//函数定义
public:
	//构造函数
	CUpGradeGameCard();
	//析构函数
	virtual ~CUpGradeGameCard();

	//设置函数
public:
	//初始化函数
	bool InitGameCard(CWnd * pHandleWnd);
	//设置扑克参数
	void SetCardParameter(int iHSpace, int iVSpace, int iUpSpace);
	//设置基准点函数
	void SetBasePoint(CPoint & BasePoint, XShowMode XShowMode, YShowMode YShowMode);
	//设置显示扑克
	//void SetShowCard(bool bShow);
	//设置使用鼠标
	void SetUseMouse(bool bUserMouse);
	//设置显示方式
	//void SetLookMode(bool bHorzLook);

	//功能函数
public:

	//设置棋局
	void SetChess(int iMeFlag, int iCurPlay, int qi[][21], BOOL initBoard = FALSE);
	//设置走棋标志
	void SetPlayFlag(int iStartI, int iStartJ, int iEndI, int iEndJ, BOOL bIsPlay = FALSE);
	//设置时间
	void SetPlayTime(int iJuMin, int iJuSec, int iBuMin, int iBuSec, int iDuMin, int iDuSec);
	//启动定时器
	void SetTimerCount();
	//设置结束信息
	void SetFinishMessage(CString strMessage, bool bIsFinish);
	//设置用户信息
	void SetUserInfo(UserItemStruct *m_UserInfo, int iStation);
	//设置提子
	void SetTiZiNum(int iNum[]);
	//设置扑克
	//bool SetCard(BYTE bCardList[], BYTE bUpList[], BYTE bCardCount);
	//删除升起的扑克
	//BYTE RemoveUpCard();
	//获取升起的扑克
	//BYTE GetUpCard(BYTE bCardList[]);
	//获取扑克信息
	//BYTE GetCard(BYTE bCardList[], BYTE bUpList[]);

	//内联函数
public:
	//获取扑克数目
//	BYTE GetCardCount() { return m_bCardCount; }
	
	//内部函数
protected:
	//按键测试
	BYTE HitCardTest(CPoint & Point);
	//调整窗口位置
	void FixCardControl();
	//获取大小函数
	bool GetCardSize(CSize & Size);
	

	//设置棋盘
	void SetBoard(CDC &memDC);
	//设置棋子
	void SetQiZi(int i, int j, int type, CDC *memDC);
	//显示棋子
	void ShowQiZi(int iDestX, int iDestY,int type, CDC *memDC);
	//显示走子标志
	void ShowPlayFlag(CDC *memDC);
	//get init time string
	void GetInitTimeString(int iMinute, int iSec,CString &str);
	//get time string 
	void GetTimeString(int iSec, CString &str);
	//显示提子数
	void ShowTiZiNum(CDC *memDC);
	//set display time
	void SetTimeDisplay(int iDestX, int iDestY,CString &str, CDC *memDC, COLORREF crColor);
	//显示该谁走标志
	void ShowGeneralFlag(CDC *memDC);
	//初始化信息
	void SetInitInfo(CDC *memDC, bool bFlag = false); 
	//显示完成信息
	void ShowFinishMessage(CDC *memDC);

	//透明贴图
	void TransparentBlt(CDC *pDestDC,int iDestX, int iDestY, int iDestWidth, int iDestHeight,
						CDC *pSrcDC, int iSrcX, int iSrcY, int iSrcWidth, int iSrcHeight, COLORREF transparentColor);
	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//重画函数
	afx_msg void OnPaint();
	//鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//光标消息
	afx_msg BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	void Init(void);
};

