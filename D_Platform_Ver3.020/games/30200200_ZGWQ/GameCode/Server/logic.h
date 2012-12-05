#include "stdafx.h"
////////////////////////////////////////////////wq//////////////////////////
#define WQ_FLAG_NONE				0
#define WQ_FLAG_BLACK				1
#define WQ_FLAG_WHITE				2
#define WQ_FLAG_SIDE				3
#define WQ_FLAG_CUR_BLACK			(WQ_FLAG_BLACK + 10)
#define WQ_FLAG_CUR_WHITE			(WQ_FLAG_WHITE + 10)
#define WQ_FLAG_BLACK_CROSS			4
#define WQ_FLAG_WHITE_CROSS			5

#define WQ_MAX_I					21
#define WQ_MAX_J					21

#define WQ_BLACK_TIE_MU				(3.75) //黑帖目3又3/4子

enum WQ_PLAY_FLAG
{
	WQ_PLAY_FLAG_BLACK = 0,
	WQ_PLAY_FLAG_WHITE = 1
};

///////////////////////////////////////////////////////////////////

/******************************************************************************************************/

enum XQ_PLAY_FLAG
{
	XQ_PLAY_FLAG_RED = 0,
	XQ_PLAY_FLAG_BLACK = 1
};


//象棋
#define XQ_FLAG_NONE				0
#define XQ_FLAG_RED					1
#define XQ_FLAG_BLACK				-1

#define XQ_QIZI_NONE				0
#define XQ_CROSS					8

//红方
#define XQ_RED_JU					1
#define XQ_RED_MA					2
#define XQ_RED_PAO					3
#define XQ_RED_JIANG				6
#define XQ_RED_SHI					4
#define XQ_RED_XIANG				5
#define XQ_RED_BIN					7

//黑方
#define XQ_BLACK_JU					-1
#define XQ_BLACK_MA					-2
#define XQ_BLACK_PAO				-3
#define XQ_BLACK_JIANG				-6
#define XQ_BLACK_SHI				-4
#define XQ_BLACK_XIANG				-5
#define XQ_BLACK_BIN				-7

#define XQ_MAX_I					(10)
#define XQ_MAX_J					(9)

/******************************************************************************************************/
/******************************************************************************************************/

class CUpGradeGameLogic
{
	//变量定义
private:
	
	//函数定义
public:
	//构造函数
	CUpGradeGameLogic(void);
	~CUpGradeGameLogic(void);
	//功能函数（公共函数）
public:
	void NumQiZi(float *totalBlack, float *totalWhite, int qi[][21]);
	
private:
	int GetEmptyFlag(int pi,int pj,int qi[][21]);
};
