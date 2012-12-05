#pragma once

#include "StdAfx.h"

//声明名字空间
//using namespace AFC::AFCImage;

//扑克控制类
class CNoteAnimal : public CWnd
{
	//枚举定义
public:
CPoint							m_PtBasePoint;					//基准坐标
	//变量定义
protected:
	CRgn							m_CardViewRgn;					//扑克区域
	CWnd							* m_pHandleWnd;					//处理窗口

	int								m_iTotalJeton;					//面值
	int								m_iArrayJeton[16];		//筹码分析数组

	BYTE							m_bJetonCount;					//分析出来所用筹码个数数目
	//筹码坐标系
	int								m_iWidth;				//宽
	int								m_iHeight;				//高
	int								m_iXoffset;				//x轴偏离量
	int								m_iYoffset;				//y轴偏离量
	
	//筹码重叠方式
	BOOL							m_bOverlap;				//默认为假即全部显示
	//信息变量
protected:
	bool							m_bHorzLook;					//是否横放
	
	BOOL							m_bCardStyle;					//使用牌是否为小牌true表示使用小牌,false表示使用默认牌
	
	//图片变量
protected:
	CGameImage						m_CardPic;					//扑克控件
	CGameImageHelper*				m_pMoveCard;					//牌移动

	BOOL							m_bSelect;						//是否选择牌
	//函数定义
public:
	//构造函数
	CNoteAnimal(BOOL bOverlap=false);//是否叠在一起
	//析构函数
	virtual ~CNoteAnimal();

	//设置函数
public:
	//初始化函数
	bool InitGameCard(CWnd * pHandleWnd);
	//设置扑克参数
	void SetCardParameter(int iWidth,int iHeight,int iXoffset,int iYoffset);
	//设置基准点函数
	void SetBasePoint(CPoint & BasePoint);
	//设置筹码面值
	void SetTotalJeton(int iTotal);
	//获取筹码面值
	int  GetJeton(){return m_iTotalJeton;}
	//增加用户所下注情况
	void AddJeton(int iTotal);
	//分析筹码
	int AnalyseJeton(int iTotalJeton,int iArrayJeton[],BYTE iJetonCount,BYTE bJeton[]);
	//设置显示方式
	void SetLookMode(bool bHorzLook=true);
	//获取显示方式
	BOOL GetLookMode();
	//设置重叠方式
	void SetOverlap(BOOL bOverlap){m_bOverlap=bOverlap;}
	//获取重叠方式
	BOOL GetOverlap(){return m_bOverlap;}
public:
	//内联函数
public:
	//获取扑克数目
	BYTE GetCardCount() { return m_bJetonCount; }
	//获取扑克位置
	BYTE GetCardXPos(BYTE bCard) { return bCard; };
	//获取扑克位置
	BYTE GetCardYPos(BYTE bCard) { return bCard; };

	//内部函数
protected:
	//调整窗口位置
	void FixCardControl();
	//获取大小函数
	bool GetCardSize(CSize & Size);

	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//重画函数
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
};

