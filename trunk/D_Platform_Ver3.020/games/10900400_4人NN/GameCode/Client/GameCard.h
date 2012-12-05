#pragma once

#include "StdAfx.h"

//声明名字空间
//using namespace AFC::AFCImage;

//消息定义
#define	IDM_LEFT_HITCARD			WM_USER+110						//左击扑克
#define	IDM_RIGHT_HITCARD			WM_USER+111						//右击扑克
#define IDM_MOUSE_MOVE				WM_USER+112						//鼠标移动到牌上
#define	IDM_MOUSE_LEFT				WM_USER+113						//鼠标移开

//操作掩码
#define	UG_HUA_MASK					0xF0							//花色掩码
#define	UG_VALUE_MASK				0x0F							//数字掩码

//牌型
#define IMAGE_1024_768				0x00							//牌
#define IMAGE_800_600				0x01							//牌
#define IMAGE_SMALL					0x02							//牌
#define IMAGE_VERY_SMALL			0x03							//牌

//扑克控制类
class CUpGradeGameCard : public CWnd
{
	//枚举定义
public:
	enum XShowMode { SWX_MODE_LEFT, SWX_MODE_CENTER, SWX_MODE_RIGHT };
	enum YShowMode { SWY_MODE_TOP,  SWY_MODE_CENTER, SWY_MODE_BOTTOM }; 

	//变量定义
protected:
	int								m_iCardHight;					//扑克高度
	int								m_iCardWidth;					//扑克宽度
	int								m_iCardHSpace;					//扑克间隔
	int								m_iCardVSpace;					//扑克间隔
	int								m_iCardUpSpace;					//跳起高度
//	CRgn							m_CardViewRgn;					//扑克区域
	CWnd							* m_pHandleWnd;					//处理窗口

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
	BYTE							m_bCardStyle;					//使用牌是否为小牌true表示使用小牌,false表示使用默认牌
	BOOL							m_bSelect;						//是否在某张牌上
	CByteArray						m_CardFriendArray;				//扑克数组(如果牌数大多分二组显示)
	BYTE							m_bFriendCardCount;				//友牌总数
	BYTE							m_bShowNum;	
		//图片变量
	CGameImage                      m_NowThis;                             //现在动的牌
protected:
//	CAFCImage						m_CardPic[2];					//扑克控件
	static		CGameImage				m_CardPic[4];//[4];					//扑克控件
	CToolTipCtrl					m_ToolTip;						//工具提示

	//colin09041发牌动画
	CPoint                     m_ptStart;    // 移动的开始坐标
	CPoint                     m_ptEnd;      // 移动目标坐标
	long                       m_lMoveCount;   // 移动次数
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
	void SetCardShowNum(BYTE bShowNum = 0){m_bShowNum = bShowNum; Invalidate(FALSE);}
	//设置调用牌模式
	void SetCardStyle(BYTE bCardStyle=0){m_bCardStyle=bCardStyle;}
	//调用牌模式
	BYTE GetCardStyle(){return m_bCardStyle;}
	//功能函数
public:
	//设置扑克
	bool SetCard(BYTE bCardList[], BYTE bUpList[], BYTE bCardCount);
	//删除升起的扑克
	BYTE RemoveUpCard();
	//获取升起的扑克
	BYTE GetUpCard(BYTE bCardList[]);
	//获取扑克信息
	BYTE GetCard(BYTE bCardList[], BYTE bUpList[]);

	//内联函数
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

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	//设置友牌数组
	BOOL SetFriendArray(BYTE bCardList[], BYTE bUpList[], BYTE bCardCount);

		// 获取当前位置
	void GetBasePoint(CPoint &ptBasePoint);

	/****************************************************************
	* 函数名: void MoveAnimal(CPoint &ptStart, CPoint &ptEnd, long lTime)
	* 功能: 开始移动筹码，设置移动起始、终点、总时间
	* 参数: CPoint &ptStart    [in]  起始位置
	*       CPoint &ptEnd      [in]  终点
	*       long lTime         [in]  移动总时间 (ms)
	* 返回: N/A
	****************************************************************/
	void MoveAnimal(CPoint &ptStart, CPoint &ptEnd, long lTime);

	// 停止移动
	void StopMove(void);
protected:
	//查找友牌数组中某一个牌的个数
	BYTE FindACardNumInFriendList(BYTE iCardNum);
	//设置图片
	void SetCardImage();
	DECLARE_MESSAGE_MAP()
};

