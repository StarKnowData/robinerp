#pragma once
#include "StdAfx.h"

#define CARD_WIDTH	80		//牌宽
#define CARD_HEIGHT	105		//牌高
#define CARD_SPACE	15		//牌间隔

//牌动画类(090330a1 JJ)
class CCardAnimal 
{
public:
	CCardAnimal(void);

	~CCardAnimal(void);
private:
	CPoint	m_ptBegin;						//起点位置

	CPoint	m_ptEnd;						//终点位置

	BYTE	m_nCard[10];					//牌数组,最高支持10位

	int		m_nCardCount;					//此时有多少张牌

	int		m_nTime;						//总时间(ms)

	int		m_nNowTime;					//剩余时间(ms)

	int		m_nElapse;						//时间间隔

	CGameImage	*m_pImgNormalCard;			//普通的42张牌

	CGameImage	*m_pImgBackCard;			//牌背和大小王
public:
	//函数
	LRESULT Create(IN CGameImage * pNormalCard, IN CGameImage * pBackCard);	//设置动画 (动画图片指针)

	LRESULT Begin(IN int nTime, IN int nElapse, IN CPoint ptBegin, IN CPoint ptEnd, IN BYTE card[], IN int count);	//开始播放动画(播放多久(ms) 时间间隔 动画位置起始和结束坐标) 牌 牌数

	void End();																//结束播放动画

	LRESULT DrawAnimal(IN CDC *pDC, IN int xPos, IN int yPos);				//画动画,放在指定窗口OnPaint函数内

	LRESULT OnTimer();														//放在指定窗口OnTime内,返回值用于控制是否动画结束

	bool IsValid();															//是否是可使用的对象

	bool IsOnShow();														//是否正在播放

	bool CanShow();															//当前对象是否可用
	
	static BYTE GetCardXPos(BYTE bCard)										//获取牌在牌图中X位置
	{ 
		BYTE bkk=(bCard&0x0F)+1;
		if (bkk==14) bkk=1;
		return bkk-1; 
	}

	static BYTE GetCardYPos(BYTE bCard) { return (bCard&0xF0)>>4; }			//获取牌在牌图中Y位置
protected:
	void Init();															//初始化,内部使用
};
