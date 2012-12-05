#pragma once

#include "StdAfx.h"

//操作掩码
#define	UG_HUA_MASK					0xF0			//1111 0000
#define	UG_VALUE_MASK				0x0F			//0000 1111

//扑克花色
#define UG_FANG_KUAI				0x00			//方块	0000 0000
#define UG_MEI_HUA					0x10			//梅花	0001 0000
#define UG_HONG_TAO					0x20			//红桃	0010 0000
#define UG_HEI_TAO					0x30			//黑桃	0011 0000
#define UG_NT_CARD					0x40			//主牌	0100 0000
#define UG_ERROR_HUA				0xF0			//错误  1111 0000

//扑克出牌类型
#define UG_ERROR_KIND				0				//错误
#define UG_ONLY_ONE					1				//单牌
#define UG_DOUBLE					2				//对牌
#define UG_THREE					3				//三条
#define UG_DOUBLE_TRACKOR			4				//两条拖拉机
#define UG_THREE_TARCKOR			5				//三条拖拉机
#define	UG_SHOW_CARD				6				//甩牌





///////////////////////////////////////////////////////////////

//用户昵称//相差18
#define XQ_UPPEOPLE_X				(40)
#define XQ_UPPEOPLE_Y				(185)
#define XQ_DOWNPEOPLE_X				(40)
#define XQ_DOWNPEOPLE_Y				(500)

//用户头像
#define XQ_UPPEOPLE_LOG_X			(25)
#define XQ_UPPEOPLE_LOG_Y			(67)
#define XQ_DOWNPEOPLE_LOG_X			(25)
#define XQ_DOWNPEOPLE_LOG_Y			(381)

#define XQ_UP_RANGZI_Y				(XQ_UPPEOPLE_Y+18)//让子
#define XQ_UP_TIZI_Y				(XQ_UPPEOPLE_Y+18*2)//提子
#define XQ_UP_MUSU_Y				(XQ_UPPEOPLE_Y+18*3)//目数
#define XQ_SET_TOP_JU_TIME_Y		(XQ_UPPEOPLE_Y+18*4)//用时
#define XQ_SET_TOP_BU_TIME_Y		(XQ_UPPEOPLE_Y+18*5)//倒计时

#define XQ_DOWN_RANGZI_Y			(XQ_DOWNPEOPLE_Y+18)//让子
#define XQ_DOWN_TIZI_Y				(XQ_DOWNPEOPLE_Y+18*2)//提子
#define XQ_DOWN_MUSU_Y				(XQ_DOWNPEOPLE_Y+18*3)//目数
#define XQ_SET_BOT_JU_TIME_Y		(XQ_DOWNPEOPLE_Y+18*4)//用时
#define XQ_SET_BOT_BU_TIME_Y		(XQ_DOWNPEOPLE_Y+18*5)//倒计时

//显示时间设置坐标
//中间显示
#define XQ_INIT_SET_JU_TIME_X		(XQ_UPPEOPLE_X)
#define XQ_INIT_SET_JU_TIME_Y		(325)
#define XQ_INIT_SET_BU_TIME_X		(XQ_UPPEOPLE_X)
#define XQ_INIT_SET_BU_TIME_Y		(350)
#define XQ_INIT_SET_DU_TIME_X		(85)
#define XQ_INIT_SET_DU_TIME_Y		(418)

//上方显示用时
#define XQ_SET_TOP_JU_TIME_X		(XQ_UPPEOPLE_X)
#define XQ_SET_TOP_BU_TIME_X		(XQ_UPPEOPLE_X)

#define XQ_SET_TOP_DU_TIME_X		(XQ_UPPEOPLE_X)
#define XQ_SET_TOP_DU_TIME_Y		(341)

//下方显示用时
#define XQ_SET_BOT_JU_TIME_X		(XQ_DOWNPEOPLE_X)
#define XQ_SET_BOT_BU_TIME_X		(XQ_DOWNPEOPLE_X)

#define XQ_SET_BOT_DU_TIME_X		(XQ_DOWNPEOPLE_X)//
#define XQ_SET_BOT_DU_TIME_Y		((XQ_UPPEOPLE_Y+18))//



#define XQ_UP_FLAG_X				(75)//下棋标志
#define XQ_UP_FLAG_Y				(262)
#define XQ_DOWN_FLAG_X				(75)
#define XQ_DOWN_FLAG_Y				(580)

//////////////////////////////////////////////////wq//////////////
#define WQ_USE_TIME_LEFT_X				(70)//左边用时
#define WQ_USE_TIME_LEFT_Y				(392)
#define WQ_DAO_TIME_LEFT_X				(70)//左边到计时
#define	WQ_DAO_TIME_LEFT_Y				(412)

#define WQ_USE_TIME_RIGHT_X				(901)//右边
#define WQ_USE_TIME_RIGHT_Y				(390)
#define WQ_DAO_TIME_RIGHT_X				(901)
#define WQ_DAO_TIME_RIGHT_Y				(413)

#define WQ_BOARD_ORG_X					(150)//棋盘左上角在整个客户区中的坐标
#define WQ_BOARD_ORG_Y					(29)//棋盘左上角在整个客户区中的坐标
#define WQ_BOARD_X						(150)//棋盘在整个棋盘图中的坐标
#define WQ_BOARD_Y						(29)//棋盘在整个棋盘图中的坐标
#define WQ_RECT_W						(32)//棋盘中每个格子的宽度
#define WQ_QIZI_R						(29)//棋子直径

#define WQ_MAX_I						(21)//19 行加2边界
#define WQ_MAX_J						(21)//19 列加2边界

#define WQ_FLAG_NONE					0
#define WQ_FLAG_BLACK					1
#define WQ_FLAG_WHITE					2
#define WQ_FLAG_SIDE					3	//2边界
#define WQ_FLAG_CUR_BLACK				(WQ_FLAG_BLACK + 10)
#define WQ_FLAG_CUR_WHITE				(WQ_FLAG_WHITE + 10)

#define WQ_FLAG_BLACK_CROSS				4
#define WQ_FLAG_WHITE_CROSS				5


#define WQ_FLAG_HASCHECKED_QIZI			(-10)

#define WQ_BLACK_TIE_MU					(3.75)//黑贴目3又3/4子


enum WQ_PLAY_FLAG
{
	WQ_PLAY_FLAG_BLACK = 0,
	WQ_PLAY_FLAG_WHITE = 1
};


//棋盘坐标
struct tagPointNode
{
	int i;
	int j;

	tagPointNode()
	{
		i = -1;
		j = -1;
	}

	tagPointNode(tagPointNode &pn)
	{
		i = pn.i;
		j = pn.j;
	}

	tagPointNode(int ii, int jj)
	{
		i = ii;
		j = jj;
	}

};

/////////////////////////////////////////////////////

//围棋逻辑类 
class CUpGradeGameLogic
{
	//变量定义
private:

	int							m_iQiZi[21][21];	//棋子
	//打劫
	int							m_iDJCurPutI,
								m_iDJCurPutJ;

	int							m_iDJLastKilledI,
								m_iDJLastKilledJ;

	//函数定义
public:
	int								m_shizi[21][21];
	//构造函数
	CUpGradeGameLogic(void);
public:
	//能否下棋子
	BOOL  CanAddQiZi(int curI, int curJ,int myFlag, int qi[][21]);
	//点目
	BOOL IsIllegalDianMu(int curI, int curJ, int myFlag, int qi[][21]);

	void NumQiZi(float *totalBlack, float *totalWhite, int qi[][21]);
	//内部函数
private:
	
	int KillAllQiZi(int *killedI, int *killedJ, int myFlag, int qi[][21]);
	int AddNewQiZi(int pi, int pj, int iFlag, int qi[][21]);
	int GetEmptyFlag(int pi,int pj,int qi[][21]);
	//堆栈类
protected:
	class CStack
	{
	public:
		///CTList <tagPointNode *> m_list;
		CPtrList	m_list;

		bool bPop(int *piRet, int *pjRet);
		bool bGetTop(int *piRet, int *pjRet);

		void Push(int iIn, int jIn);
		bool bIsInQ(int iIn, int jIn);
		bool bIsEmpty();

		CStack & operator =(CStack &s);
		CStack();
		CStack(CStack &s);
		virtual ~CStack();
	};
};
