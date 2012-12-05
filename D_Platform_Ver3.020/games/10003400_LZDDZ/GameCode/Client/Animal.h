#pragma once
#include "StdAfx.h"

//播放动画类(非组合型动画)(090329a1 JJ)
class CAnimal
{
public:
	CAnimal(void);

	~CAnimal(void);
//变量
private:
	CPoint	m_ptBasepoint;			//播放位置

	int		m_nFrame;				//总帧数

	int		m_nNowFrame;			//当前正在播放的帧

	int		m_nTime;				//总时间(ms)

	int		m_nLeftTime;			//剩余时间(ms)

	int		m_nElapse;				//时间间隔

	CGameImage * m_pImage;			//使用的图像
//函数
public:
	LRESULT Create(IN CGameImage *pImage, IN int nFrame);					//设置动画 (动画图片指针 图片帧数)

	LRESULT Begin(IN int nTime, IN int nElapse, IN int xPos, IN int yPos);	//开始播放动画(播放多久(ms)  动画位置x,y坐标)
	
	void End();																//结束播放动画

	LRESULT DrawAnimal(IN CDC *pDC, IN int iMidx, IN int iMidy);			//画动画,放在指定窗口OnPaint函数内

	LRESULT OnTimer();														//放在指定窗口OnTime内,返回值用于控制是否动画结束

	bool IsValid();															//是否是可使用的对象

	bool IsOnShow();														//是否正在播放

	bool CanShow();															//当前对象是否可用
protected:
	void Init();															//初始化,内部使用
};
