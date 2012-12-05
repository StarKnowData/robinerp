#pragma once

const  int   MAX_NODE     = 52 ; 
///每步移动的大小
const  int   STEP_WIDE  = 6 ; 

class CPlaneMoveAni
{
public:
	CPlaneMoveAni(void);
public:
	~CPlaneMoveAni(void);

public: 
	BYTE     m_cbMySide ;        ///当前自己的位置
	BYTE     m_cbMoveSide  ;     ///移动的棋子属于哪一方的棋子
	BYTE     m_inDex ;          ///移动的飞机的索引


	int      m_iNeedByNodeCount;  ///需要经历的点的个数
	int      m_iHaveByNodeCount ;  //已经经历了的节点
	BYTE     m_cbDestInDex[MAX_NODE] ;  ///玩家需要经历的点
	BYTE     m_cbDirect[MAX_NODE] ;      ///改点方向

	CPoint   m_ptDestPoint[MAX_NODE] ;  ///玩家经历的点的位置
	
	CPoint   m_ptCurrentPos ;        ///当前的棋盘位置

	BYTE    m_iActiveTyple ;   ///动作类型

	bool     m_bRun;              ///是否正在播放动画
	bool     m_bFinish ;          ///是否结束

	int      m_iXstep ;           //x方向上的移动速度
	int      m_iYStep ;           //y方向上的移动速度

public:
	 ///初始化数据
	 void   IniData(void) ;
	 ///获取两点之间的符号
	 inline  int  GetsignByTwoNum(long iNum1, long iNum2) 
	 {
		 if(abs(iNum1 - iNum2) < 5)
		 {
			 return 0 ; 
		 }
		 return iNum1 >iNum2?1:-1 ; 
	 }

public:
	 ///获取当前是否正在播放动画
	bool   GetPlayState(void) { return m_bRun ; }
	///获取当前走到的位置
	CPoint GetCurrentPos(void ) { return  m_ptCurrentPos ;}
	///获取当前飞机的方向
	BYTE   GetCurrentDirect(void){return m_cbDirect[m_iHaveByNodeCount -1] ;}
	///获取当前飞机的颜色
	BYTE   GetPlaneColor(void) { return  m_cbMoveSide ; }
     ///动画执行中
	void   RunAni(void) ; 
	///飞行玩家的数据
	void   SetPlaneData(BYTE cbMySide , BYTE cbMoveSide , BYTE  inDex) ; 
	 ///设置当前的数据
    void   SetPlaneFlyData(int iNeedByNode , BYTE cbPathIndex[] ,CPoint ptDest[] , BYTE cbDirect[]) ;
	///重新设置游戏中移动飞机的坐标
	void   ResetPlanePoint(CPoint  ptPix) ;
	
};
