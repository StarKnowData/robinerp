#pragma once

#include "StdAfx.h"

//声明名字空间
//using namespace AFC::AFCImage;

//消息定义
#define	IDM_LEFT_HITCARD			WM_USER+110						//左击扑克
#define	IDM_RIGHT_HITCARD			WM_USER+111						//右击扑克
//#define IDM_MOUSE_OUT				WM_USER+112
#define IDM_MOUSE_UP				WM_USER+113

//操作掩码
#define	UG_HUA_MASK					0xF0							//花色掩码
#define	UG_VALUE_MASK				0x0F							//数字掩码

//牌型
#define IMAGE_1024_768				0x00							//牌
#define IMAGE_800_600				0x00							//牌
#define IMAGE_SMALL					0x01							//牌
#define IMAGE_VERY_SMALL			0x03							//牌

//扑克控制类
class CUpGradeGameCard : public CWnd
{
	//枚举定义
public:
	enum XShowMode { SWX_MODE_LEFT, SWX_MODE_CENTER, SWX_MODE_RIGHT };
	enum YShowMode { SWY_MODE_TOP,  SWY_MODE_CENTER, SWY_MODE_BOTTOM }; 
	//CByteArray						m_MoveSelectCardArray;					//移动选择扑克数组


	//变量定义
protected:
	int								m_iCardHight;					//扑克高度
	int								m_iCardWidth;					//扑克宽度
	int								m_iCardHSpace;					//扑克间隔
	int								m_iCardVSpace;					//扑克间隔
	int								m_iCardUpSpace;					//跳起高度
	CRgn							m_CardViewRgn;					//扑克区域
	CWnd							* m_pHandleWnd;					//处理窗口

//{{ qy 牌控件修改20091109
	void DisplayInfo();  // 绘制框选
	CRect m_RectDis;     // 框选范围
	CPoint m_stPoint;    // 起始坐标
	BOOL m_bSelectOK;    // 是否选择状态
//}} qy 牌控件修改20091109

	//信息变量
protected:
	bool							m_bShowCard;					//显示扑克
	bool							m_bHorzLook;					//是否横放
	bool							m_bUseMouse;					//响应鼠标
	BYTE							m_bHotHitCard;					//焦点扑克
	BYTE							m_bCardCount;					//扑克数目
	CPoint							m_PtBasePoint;					//基准坐标
	XShowMode						m_XShowMode;					//显示模式
	YShowMode						m_YShowMode;					//显示模式
	CByteArray						m_CardArray;					//扑克数组
	CByteArray						m_CardUpArray;					//扑克数组
	BYTE							m_bShowNum;						//是否显示数量	
	BYTE							m_bCardStyle;					//使用牌是否为小牌true表示使用小牌,false表示使用默认牌
	BOOL							m_bSelect;						//是否在某张牌上
	CByteArray						m_CardFriendArray;				//扑克数组(如果牌数大多分二组显示)
	BYTE							m_bFriendCardCount;				//友牌总数
//	BOOL							m_bLButtonDown;					//左键被按下
	BYTE							m_iFirstCard;					//
	CPoint							m_ptLeftHit;					//左键被按下的坐标
	CPoint							m_ptLeftHitMove;				//左键按下移动所到的坐标
	CPoint							m_ptMovePoint;					//移动鼠标当前的坐标
	BOOL							m_bCanMove;						//是否为移动
	BYTE							m_bMoveFirstCard;				//移动的第一张牌即单击的那张牌
	bool							m_bMoveSel;					
	CPoint                          m_pMovePos;                     //按下左键位置
	BYTE                            m_bCanUp;                       //是否升起备份
	bool							m_bMove;
	int								m_CurCardIndex;					// 鼠标当前所在card index
	BYTE							m_StartIndex;					// 开始移动的位置
	BYTE							m_EndIndex;						// 开始移动的位置
	CPoint							m_pStartPos;					// 开始鼠标位置
	bool							m_bMultiSel;
	CPoint							m_pEndPos;						// 结束位置
	///赖子牌代替牌
	BYTE                            m_ReplaceCardList[4];  
	///赖子代替牌数
	BYTE                        	m_iReplaceCount;

	//主动设置分数
	int								m_iSourcePoint;						//原来分数
	int								m_iBackPoint;						//设置捞底分数
	int								m_iBackMultiple;					//设置底倍数
	//图片变量
protected:
//	CAFCImage						m_CardPic[2];					//扑克控件
	static		CGameImage			m_CardPic[7];//[4];					//扑克控件
	CGameImage						m_Num;								//数字
	//函数定义
public:
	//构造函数
	CUpGradeGameCard(BYTE bCardStyle=0);
	//析构函数
	virtual ~CUpGradeGameCard();

	//设置函数
public:
	//初始化函数
	bool InitGameCard(CWnd * pHandleWnd);
	//设置扑克参数
	void SetCardParameter(int iHSpace, int iVSpace, int iUpSpace);
	//设置牌宽和高
	void SetCardWidthHeight(int iWidth,int iHeight);
	//设置基准点函数
	void SetBasePoint(CPoint & BasePoint, XShowMode XShowMode, YShowMode YShowMode);
	//设置显示扑克
	void SetShowCard(bool bShow);
	//设置使用鼠标
	void SetUseMouse(bool bUserMouse=false);
	//设置显示方式
	void SetLookMode(bool bHorzLook);
	//设置调用牌模式
	void SetCardStyle(BYTE bCardStyle=0){m_bCardStyle=bCardStyle;}
	//调用牌模式
	BYTE GetCardStyle(){return m_bCardStyle;}
	//设置调用牌模式
	void SetCardShowNum(BYTE bShowNum = 0){m_bShowNum = bShowNum;}
	//调用牌模式
	BYTE GetCardShowNum(){return m_bShowNum;}
	///某张牌是否属于牌队列里
	BOOL IsInside(BYTE bCardList[], int iCount, BYTE bCard, BYTE TempCard[], int TempCount);
	//功能函数
public:
	//设置扑克
	bool SetCard(BYTE bCardList[], BYTE bUpList[], BYTE bCardCount, BYTE ReplaceCardList[]=NULL, BYTE ReplaceCount=0);
	//删除升起的扑克
	BYTE RemoveUpCard();
	//获取升起的扑克
	BYTE GetUpCard(BYTE bCardList[]);
	//获取扑克信息
	BYTE GetCard(BYTE bCardList[], BYTE bUpList[]);
	//分牌总数
	int GetPoint();
	//主动设置分数
	BOOL SetBackPointAndMultiple(int iSourcePoint = 0,int iBackPoint = 0,int iBackMultiple = 1);
	//内联函数

	//lym1111使弹起的牌落下
	void DownCard();

public:
	//获取扑克数目
	BYTE GetCardCount() { return m_bCardCount; }
	//获取扑克数值
	BYTE GetCardValue(BYTE bCard) 
	{ 
		//return (bCard&UG_VALUE_MASK);
		BYTE bkk=(bCard&UG_VALUE_MASK)+1;
		if (bkk==14) bkk=1;
		return bkk; 
	}
	//获取扑克花色
	BYTE GetHuaKind(BYTE bCard) { return bCard&UG_HUA_MASK; }
	//获取扑克大小
	BYTE GetCardNum(BYTE bCard) { return bCard&UG_VALUE_MASK; }	
	//获取扑克位置
	BYTE GetCardXPos(BYTE bCard) { return GetCardValue(bCard)-1; };
	//获取扑克位置
	BYTE GetCardYPos(BYTE bCard) { return GetHuaKind(bCard)>>4; };

	//内部函数
protected:
	//按键测试
	BYTE HitCardTest(CPoint & Point);
	//按键测试
	BYTE HitCardTestAbove(CPoint &Point);
	//调整窗口位置
	void FixCardControl(bool bInvalide=true);
	//获取大小函数
	bool GetCardSize(CSize & Size);

	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//重画函数
	afx_msg void OnPaint();
	//鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//光标消息
	afx_msg BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message);
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags,CPoint Point);
	
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	//设置友牌数组
	BOOL SetFriendArray(BYTE bCardList[], BYTE bUpList[], BYTE bCardCount);

	//{{ qy 牌控件修改20091109
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	int GetCardsIndex(CRect &rect);	               // 获取区域的牌
	void GetCardRect(BYTE byIndex, CRgn &rgnCard); // 获取索引牌的区域
	CByteArray  m_aSelIndex;                       // 选中牌的所有索引
	COLORREF m_SelecColor;                         // 框选颜色
	//}} qy 牌控件修改20091109

protected:
	//查找友牌数组中某一个牌的个数
	BYTE FindACardNumInFriendList(BYTE iCardNum);
	//设置图片
	void SetCardImage();
	//交换二张牌位置
	BOOL ChangeIndex(BYTE DestIndex ,BYTE SrcIndex);

	BYTE GetCardIndex(CPoint &Point);

	//交换多张
	BOOL ChangeIndexArray(BYTE DestIndex,BYTE SrcIndex);
	//将牌反转
	BOOL Convert(BYTE CardList[],int iCardCount);
	DECLARE_MESSAGE_MAP()


	CByteArray						m_MoveSelectCardArray;					//移动选择扑克数组
};

