#pragma once
#include "StdAfx.h"
#include "Animal.h"
#include "CardAnimal.h"

//子动画对象属性设置结构体
struct AnimalStruct 
{
	CGameImage *pImage;
	int	nFrame;
};
//子动画对象播放属性结构体
struct AnimalShowAttriStruct
{
	int nTime;
	int nElapse;
	int xPos;
	int yPos;
};

//组合动画类(最高支持3层组合,待扩展成n层版本 090329a1 JJ)
class CCombineAnimal
{
public:
	CCombineAnimal(void);

	~CCombineAnimal(void);
public:
	LRESULT Create(IN AnimalStruct * pAniStruct, IN int count);				//设置count个子动画(子动画属性, 个数)

	LRESULT Begin(IN AnimalShowAttriStruct * pAniShowAttri, IN int *nBegin, IN int *nEnd, IN int count);	//开始播放动画(播放属性, 开始时间, 结束时间, 个数)
		
	LRESULT BeginCard(IN int beginCardTime, IN int endCardTime, IN CPoint ptBegin, IN CPoint ptEnd, IN int zPos, BYTE card[], int count);	//设置牌动画对象,开始结束时间,z轴位置, 牌数组, 牌数目 

	void End();

	LRESULT DrawAnimal(IN CDC *pDC, IN int xPos, IN int yPos);				//画动画,放在指定窗口OnPaint函数内

	LRESULT OnTimer();														//放在指定窗口OnTime内,返回值用于控制是否动画结束

	bool IsValid();															//是否是可使用的对象

	bool IsOnShow();														//是否正在播放
private:
	void Init();															//初始化,内部使用

	bool CanShow();															//当前所有对象是否都可用
public:
	CCardAnimal	m_CardAnimal;	//牌动画对象(待解耦)
private:
	CAnimal m_childAnimal[3];	//3个子动画对象

	int	m_nCardBeginTime;		//牌动画开始时间

	int m_nCardEndTime;			//牌动画结束时间
	
	int m_nCardZpos;			//牌动画Z轴位置

	int m_nTime;				//总时间(100ms的倍数,  = 3个子动画对象中最大帧数*100ms)

	int m_nNowTime;				//已经播放过的时间(100ms的倍数)

	int m_nElapse[3];			//子动画自己的间隔时间(100ms的倍数)

	int m_nChildOnUse;			//此对象有几个子动画对象正在使用

	int m_nBeginTime[3];		//子动画对象开始时间(100ms的倍数)

	int m_nEndTime[3];			//子动画对象结束时间(100ms的倍数)
};
