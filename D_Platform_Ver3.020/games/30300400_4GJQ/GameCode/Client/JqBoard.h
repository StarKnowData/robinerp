#pragma once

#include "StdAfx.h"
#include <vector>
#include "../GameMessage/JqLogic0.h"

/**
 * A星结构
 */
typedef struct tagAStarStruct
{
	UINT FVal;	//F值（G+H）
	UINT GVal;	//G值（从起点沿着已生成的路径到一个位置的移动距离,假定两结点之间移动的距离为10包括斜角）
	UINT HVal;	//H值（从给定位置到目的位置的估计移动距离）
	POINT ptParent;	//父结点位置
	POINT ptPos;	//自己位置
}AStarStruct;

class CJqBoard :public CJqLogic0
{
protected:	
	 CPStack g_StepLine;
	 CPStack m_StepLine;
     int g_CurI,g_CurJ,g_startqi;
	 int m_startqi,m_endqi;
	 bool m_bShowStartChess;

private:
	 /// 所有处理列表
	 std::vector<AStarStruct> m_AllList;
	 /// 开启列表
	 std::vector<AStarStruct> m_OpenList;
	 /// 关闭列表
	 std::vector<POINT> m_CloseList;
	 /// 当前位置
	 AStarStruct m_CurrentPos;

public :
	bool bFinishBuzhen();
	bool bCanIMove(void);
	void  ToMyCord(int station,int& toi,int& toj,int fi,int fj);
	void UserMove(tagMoveResult&   result);
	bool m_bICanMove;
	int GetJq(int station,int i,int j);
	void CopyOtherBuZhen(tagBuZhen& bz);//CPtrList & from,int DevSite);
	void FinishBuZhen ();
	void StartBuzhen();
	void Init();
	void LoadBuZhen();
	void SaveBuZhen();
	void OnLBUp(CPoint& pt);
	void OnPaint(CDC *pdc);
	void DrawPath(CDC * pDC);
	bool m_bFinishBuzhen;
	CPoint m_ptBoardStartCenter;
    bool MoveQiZi(int iTo,int jTo,int iFrom,int jFrom,bool IsIPut=true);
	CJqBoard(void);
	~CJqBoard(void);
	/// 清空选择坐标（自己不能下棋时，设置）
	void SetStartEndXY(){ m_iStartI =m_iStartJ= m_iEndI = m_iEndJ = -1; }
	/// 初始化轨迹
	void InitPath();
	/// 设置每步轨迹
	void UserPath(int station, int x, int y, POINT start, POINT end);
	/// 设置移动轨迹中的棋子
	void UserMovePathCheen(int station, POINT ptFront, POINT ptStart, POINT ptEnd, int iFinalEndX, int iFinalEndY);
	/// 设置刷新区域
	void GetRefurbishRECT(RECT & rc, POINT start);
	/// 设置闪烁
	void SetFlashChess(int &iX, int &iJ, bool bFlash);
	/// 获得是否闪烁
	bool GetFlashChess() const{ return m_bShowStartChess; }
	
protected:
	
	void SetAQiZi(int ii,int jj,CDC* MemDC,bool showfront = false);
	bool  Exchang2QiZiInBuZhen(int iTo,int jTo,int iFrom,int jFrom);
	void ShowAllJunQiFlag(CDC *pdc);
	/// 在我的布子范围
	static bool bIsInMyBuZhenArea(int i,int j);
	/// 在铁道线
	static bool bIsInRailway(int i,int j);
	/// 在棋盘有效位置
	static bool bIsInBoard(int i,int j);
	/// 在军营
    static bool bIsInJuYin(int i,int j);
	/// 在大本营
    static bool bIsInDaBenYin(int i,int j);

private:
	bool bPushChaXian(int iTo,int jTo,int ii,int jj,CPStack& s);
	bool CanGoCircle(int iTo,int jTo,int iFrom,int jFrom);

	bool bGBGoRailway(int iTo,int jTo,int iFrom,int jFrom);
	bool bGBGoRailway1(int iTo,int jTo,int iFrom,int jFrom);

	bool CanGoI(int fromi,int toi,int jj);
	bool CanGoJ(int fromj,int toj,int ii);

	bool IsCanMove2Qi(int toQi,int fromQi);
	bool MoveQiZi1(int iTo,int jTo,int iFrom,int jFrom);
	
	int m_station,m_viewstation,m_MyColor;
	void  EmptyStepLine();
    bool bCanGoThrough(int iTo,int jTo,int ii,int jj);
		
private:
	/// 计算G值
	UINT CountGVal();
	/// 计算H值
	UINT CountHVal(int x, int y, int iToX, int iToY);
	/// 计算F值
	bool SetFVal(AStarStruct & POS);
	/// 查找该位置是否在关闭位置
	bool FindCloseList(POINT pt);
	/// 获得最小F值
	AStarStruct GetMinFVal();
	/// 查找该位置是否可以走斜
	bool GetGoTiltPath(POINT pt);
	/// 查找是否在中间田子格位置
	bool GetCenterFarmWordPath(POINT pt);
	/// 加入开启列表
	void AddOpenList(int iTo,int jTo, POINT ptParent);
	/// 工兵走棋
	bool bCanArrival(int iTo,int jTo,int iFrom,int jFrom);
};

struct BuZhenNode
{
	int i,j,jqname;
};