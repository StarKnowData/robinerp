#include "StdAfx.h"
#include "jqboard.h"
#include "A_Star.h"
#include "clientgamedlg.h"

#define BACK_COLOR   RGB(0,128,0)
#define __ABS(a) ( (a) >= 0 ? (a) : -(a))
static int Have_Checked=-5000;
extern void Msg(const char *lpszFormat, ...);

void CJqBoard::SetAQiZi(int ii,int jj,CDC* MemDC,bool showfront)
{
	if(!bIsInBoard(ii,jj))return;
	int qi=mBoard[ii][jj];
	CPoint p;
	int iTempX, iTempY;//临时x,y位置
	p.x=m_ptBoardStartCenter.x + jj*g_CStaticGlbMj.mSzGrade.cx;
	iTempX = p.x;
	p.y=m_ptBoardStartCenter.y + ii*g_CStaticGlbMj.mSzGrade.cy;
	iTempY = p.y;
	
	//CString str;
	//str.Format("--------------p.x:%d,  p.y:%d", p.x, p.y);
	//OutputDebugString(str);

	int ang=0;bool bb=false;
	
	if(( ii == m_iStartI && jj == m_iStartJ)&&m_startqi!=JQ_TYPE_NONE)
	{
		//开始棋子角度
		int station=GetStationFromColor(GetAJqCol(m_startqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==0)
			ang=180;
		else if(station==1)
			ang=90;
		else if(station==3)
			ang=270;
		else
			ang=0;
	}	
	if(( ii == m_iEndI && jj == m_iEndJ)&&m_endqi!=JQ_TYPE_NONE)
	{
		//目标棋子角度
		int station=GetStationFromColor(GetAJqCol(m_endqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==0)
			ang=180;
		else if(station==1)
			ang=90;
		else if(station==3)
			ang=270;
		else
			ang=0;
	}	
	if(qi!=JQ_TYPE_NONE)
	{
		int station=GetStationFromColor(GetAJqCol(qi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==0)
			ang=180;
		else if(station==1)
			ang=90;
		else if(station==3)
			ang=270;
		else
			ang=0;
	}

	bb= ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10;///上
	if(bb)
	{
		if (8 <= jj)//从第8列开始
		{
			p.x = iTempX + 2;
		}
		if (10 == jj)//第10列
		{
			p.x = iTempX + 3;
		}

		p.y = iTempY + 1;//微调

		ang=180;
	}

	bb= ii >= 11 && ii <= 16 && jj >= 6 && jj <= 10;///下
	if(bb)
	{
        if (8 <= jj)//从第8列开始
        {
			p.x = iTempX + 2;
        }
		if (10 == jj)//第10列
		{
			p.x = iTempX + 3;
		}

		p.y = iTempY - 1;//微调

/*
		CString str;
		str.Format("下--------------ii:%d,jj:%d",ii,jj);
		OutputDebugString(str);
*/
		ang=0;
	}

	
	bb= ii >= 6 && ii <= 10 && jj >= 0 && jj <= 5;///左
	if(bb)
	{
		p.y = iTempY - 1;

		if (8 <= ii)//从第8列开始
		{
			p.y = p.y + 2;
		}
		if (10 == ii)//第10列
		{
			p.y = p.y + 1;
		}
        p.x =  iTempX + 3;
		ang=270;
	}

	bb= ii >= 6 && ii <= 10 && jj >= 11 && jj <= 16;///右
	if(bb)
	{
		p.y = iTempY - 1;

		if (8 <= ii)//从第8列开始
		{
			p.y = p.y + 2;
		}
		if (10 == ii)//第10列
		{
			p.y = p.y + 1;
		}

		ang=90;
	}

	if(//((ii==m_iStartI&&jj==m_iStartJ) && (-1 == m_iEndI||-1 == m_iEndJ))    ||   
		(ii==m_iEndI&&jj==m_iEndJ))
	  g_CStaticGlbMj.ShowACross (MemDC,p,ang);

	if(( ii == m_iStartI && jj == m_iStartJ)&&m_startqi!=JQ_TYPE_NONE)
	{
		//开始棋子角度
		int station=GetStationFromColor(GetAJqCol(m_startqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==2 && ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10)
			ang=0;
	}	
	
	if(( ii == m_iEndI && jj == m_iEndJ)&&m_endqi!=JQ_TYPE_NONE)
	{
		//目标棋子角度
		int station=GetStationFromColor(GetAJqCol(m_endqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==2 && ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10)
			ang=0;
	}	
	if(qi!=JQ_TYPE_NONE)
	{
		int station=GetStationFromColor(GetAJqCol(qi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==2 && ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10)
			ang=0;
	}

	if(qi == JQ_TYPE_NONE)return; 

	bool bDrawChess=true;
	bb=GetAJqCol(qi) == m_MyColor&&(!IsWatcher()||m_bWatchOther);
	bb= !bb;

	if(showfront) 
		bb= false;	
	if (ii==m_iStartI&&jj==m_iStartJ&&(-1==m_iEndI||-1==m_iEndJ)&&m_bShowStartChess)
		bDrawChess = false;

	g_CStaticGlbMj.ShowAPisa(qi,MemDC,p,ang,bb,bDrawChess);
}


void CJqBoard::ShowAllJunQiFlag(CDC *pdc)
{
	int i;////Microsoft VisualC++2005/MFC8.0
	int II[4]={-1,-1,-1,-1},JJ[4]={-1,-1,-1,-1};///旗位
	bool SLIsIn[4] ={false,false,false,false};

	for(i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
		{
			int ff=mBoard[i][j];
			int col=GET_A_JQ_COLOR(ff);
			int name=GET_A_JQ_NAME(ff);
			if(name == JQ_TYPE_NAME_SL)SLIsIn[col]=true;
			if(name == JQ_TYPE_NAME_JQ)
			{
				II[col]=i;
				JJ[col]=j;
				
			}
		}

		for(i=0;i<4;i++)
		{
			if(!SLIsIn[i])
			{
				int ii=II[i],jj=JJ[i];
				if(ii < 0 || jj < 0)continue;
				SetAQiZi(ii,jj,pdc,true);
			}
		}
}

/**
 * 是否完成布阵
 */
bool CJqBoard::bFinishBuzhen()
{
	return m_bFinishBuzhen;
}

void CJqBoard::Init()
{
	
	for(int i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
	        mBoard[i][j]=JQ_TYPE_NONE;

	m_bFinishBuzhen=false;
	m_iJingQiI=m_iJingQiJ=m_iStartI =m_iStartJ= m_iEndI = m_iEndJ = -1;
	
	m_bShowStartChess = true;
	m_bICanMove=false;
	m_iNowOutPeople=-1;
	m_viewstation = 2;
	m_startqi=m_endqi=JQ_TYPE_NONE;
	m_station=GetStation(m_viewstation);

	 m_MyColor= GetColorFromStation(m_station);
	 if(m_MyColor< 0)return;

	 mBoard[11][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_YZ);
	 mBoard[11][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_GB);
	 mBoard[11][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_JZ);
	 mBoard[11][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_GB);
	 mBoard[11][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_YZ);

	 mBoard[12][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_PZ);
	 mBoard[12][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIANZ);
	 mBoard[12][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_PZ);

	 mBoard[13][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_SZ);
	 mBoard[13][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_ZD);
	 mBoard[13][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_ZD);
	 mBoard[13][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_SZ);

	 mBoard[14][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_TZ);
	 mBoard[14][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIANZ);
	 mBoard[14][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_TZ);

	 mBoard[15][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIZ);
	 mBoard[15][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_SL);
	 mBoard[15][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_GB);
	 mBoard[15][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIZ);
	 mBoard[15][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL);

	 mBoard[16][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL);
	 mBoard[16][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_JQ);
	 mBoard[16][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL);
	 mBoard[16][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_PZ);
	 mBoard[16][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIANZ);
}

bool CJqBoard::MoveQiZi1(int iTo,int jTo,int iFrom,int jFrom)
{
	Msg("Test:Step a iTo %d, jTo %d, iFrom %d jFrom %d",iTo, jTo, iFrom, jFrom);
	if( !bIsInBoard(iTo,jTo) || !bIsInBoard(iFrom,jFrom))return false;
	g_startqi=mBoard[iFrom][jFrom];
	///都在盘内
	int di=__ABS(iTo - iFrom), dj=__ABS(jTo - jFrom);
	if( di == 0 && dj == 0)return false;
	///两子不在同一位置

	int fQi=mBoard[iFrom][jFrom],tQi=mBoard[iTo][jTo];
	if(!IsCanMove2Qi(tQi,fQi))///子不能吃或移动
		return false;

	Msg("Test:Step: o empty EmptyStepLine");
	EmptyStepLine();
	g_StepLine.Push (iFrom, jFrom);//add
	bool f=bIsInJuYin(iFrom,jFrom),t=bIsInJuYin(iTo,jTo);
	
	if(f || t)///有一方或双方都在军营
	{
		if(t && tQi != JQ_TYPE_NONE)return false;///在军营里的子不能吃		
		if( di > 1 || dj > 1)return false;

		g_StepLine.Push (iTo, jTo);//add
		return true;
	}

	///都不在军营
	Msg("Test:Step: p empty EmptyStepLine");
	EmptyStepLine();
	g_StepLine.Push (iFrom, jFrom);//add
	f=bIsInRailway(iFrom,jFrom);t=bIsInRailway(iTo,jTo);

	if(!f || !t)///有一方或双方都不在铁道线
	{
		if( di > 1 || dj > 1)return false;
		bool bb= di == 0 || dj == 0;
		if(bb)
		{
			g_StepLine.Push (iTo, jTo);//add
			return true;
		}
		
	}

	///都在铁道线
	Msg("Test:Step: q empty EmptyStepLine");
	EmptyStepLine();

	////走直线
	if(di == 0)
	{
		Msg("Test:Step: b [%d,%d]", iFrom, jFrom);
		g_StepLine.Push (iFrom, jFrom);
		if( CanGoJ(jFrom,jTo,iFrom))
		{
			g_StepLine.Push (iTo, jTo);//add
			return true;
		}
		if(GET_A_JQ_NAME( fQi) != JQ_TYPE_NAME_GB)
			return false;
	}

	Msg("Test:Step: r empty EmptyStepLine");
	EmptyStepLine();
	if(dj == 0)
	{
		Msg("Test:Step: c [%d,%d]", iFrom, jFrom);
		g_StepLine.Push (iFrom, jFrom);//add
		if( CanGoI(iFrom,iTo,jFrom))
		{
			g_StepLine.Push (iTo, jTo);//add
			return true;
		}
		
		if(GET_A_JQ_NAME(fQi) != JQ_TYPE_NAME_GB)
			return false;
	}

	Msg("Test:Step: s empty EmptyStepLine");
	EmptyStepLine();
	g_StepLine.Push (iFrom, jFrom);//add

	////走弯线
	if(CanGoCircle(iTo,jTo,iFrom,jFrom))
	{
		g_StepLine.Push (iTo, jTo);//add
		return true;
	}

	Msg("Test:Step: t empty EmptyStepLine");
	EmptyStepLine();

	g_StepLine.Push (iTo, jTo);//add
	//bool bResult = bGBGoRailway(iTo,jTo,iFrom,jFrom);
	bool bResult = bCanArrival(iTo,jTo,iFrom,jFrom);
	g_StepLine.Push (iFrom, jFrom);//add

	return bResult;
}

bool CJqBoard::bCanGoThrough(int iTo,int jTo,int ii,int jj)
{
	int DI[4]={0,-1,0,1};
	int DJ[4]={-1,0,1,0};
	if(jj == 6 )
	{
		if(ii == 6){DJ[2] = 2;DI[3]=2;}
		if(ii == 8){DJ[2] = 2;DI[1]=-2;DI[3]=2;}
		if(ii == 10){DJ[2] = 2;DI[1]=-2;}
	}
	if(jj == 8 )
	{
		if(ii == 6){DJ[0] = -2;DJ[2]=2;DI[3]=2;}
		if(ii == 8){DJ[0] = -2;DJ[2] = 2;DI[1]=-2;DI[3]=2;}
		if(ii == 10){DJ[0] = -2;DJ[2] = 2;DI[1]=-2;}
	}
	if(jj == 10 )
	{
		if(ii == 6){DJ[0] = -2;DI[3]=2;}
		if(ii == 8){DJ[0] =-2;DI[3]=2;DI[1]=-2;}
		if(ii == 10){DJ[0] =-2;DI[1]=-2;}
	}
	bool bbb=false;

	for(int i=0;i<4;i++)
	{
		int di=ii+DI[i],dj=jj+DJ[i];
		if(di==iTo && dj == jTo)
		{
			mBoard[di][dj]=Have_Checked;
			Msg("Test:Step: d [%d,%d]", di,dj);
			g_StepLine.Push (di,dj);
			return true;
		}
		if(mBoard[di][dj] != JQ_TYPE_NONE)continue;
		if(mBoard[di][dj] == Have_Checked)continue;
		if(bIsInRailway(di,dj))
		{
			mBoard[di][dj]=Have_Checked;
			Msg("Test:Step: e [%d,%d]", di,dj);
			g_StepLine.Push (di,dj);
			return true;
		}

	}

	return false;

}

void CJqBoard::UserMove(tagMoveResult&   result)
{
	m_iStartI=	result.m_iStartI;
	m_iStartJ =result.m_iStartJ;
	m_iEndI = result.m_iEndI;
	m_iEndJ =result.m_iEndJ;
	m_startqi=mBoard[m_iStartI][m_iStartJ];
	m_endqi=mBoard[m_iEndI][m_iEndJ];
	ToMyCord(result.station,m_iStartI,m_iStartJ,m_iStartI,m_iStartJ);
	ToMyCord(result.station,m_iEndI,m_iEndJ,m_iEndI,m_iEndJ);

	if(m_iStartI < 0 || m_iStartJ < 0 ||
		m_iEndI < 0 || m_iEndJ < 0  )return;

	mBoard[m_iEndI][m_iEndJ] = result.ToJq;
	mBoard[m_iStartI][m_iStartJ] = result.FromJq;
}

/**
 * 初始化轨迹
 */
void CJqBoard::InitPath()
{
	memset(m_Path, 255, sizeof(m_Path));
}

/**
 * 设置每步轨迹
 */
void CJqBoard::UserPath(int station, int x, int y, POINT start, POINT end)
{
	// 得到视图位置
	int viewstation=g_pCClientGameDlg->ViewStation (station);
	int iStartX, iStartY, iEndX, iEndY;
	iStartX = start.x;
	iStartY = start.y;
	iEndX	= end.x;
	iEndY	= end.y;

	ToMyCord(station,x,y,x,y);

	if (255!=iStartX || 255!=iStartY)
		ToMyCord(station, iStartX, iStartY, iStartX, iStartY);
	if (255!=iEndX || 255!=iEndY)
		ToMyCord(station, iEndX, iEndY, iEndX, iEndY);

	if ((255==iStartX || 255==iStartY) && (255==iEndX || 255==iEndY))
	{
		// 所有点必须在一条线上，不能出现无连续的轨迹位置
		__asm{int 3}
	}

	// 先计算视图位置为2的数据，再进行调整
	if (255!=iEndX && 255!=iEndY)
	{
		if (iEndY == y)
		{
			m_Path[x][y] = (iEndX>x) ? _down : _up;
		}
		else if (iEndY < y)
		{
			m_Path[x][y] = (iEndX==x) ? _left : (iEndX<x) ? _LUp: _LDown;
		}
		else if (iEndY > y)
		{
			m_Path[x][y] = (iEndX==x) ? _right: (iEndX<x) ? _RUp: _RDown;
		}
	}
	else
	{
		if (iStartY == y)
		{
			m_Path[x][y] = (iStartX>x) ? _up : _down;
		}
		else if (iStartY < y)
		{
			m_Path[x][y] = (iStartX==x) ? _right : (iStartX<x) ? _RDown: _RUp;
		}
		else if (iStartY > y)
		{
			m_Path[x][y] = (iStartX==x) ? _left: (iStartX<x) ? _LDown: _LUp;
		}
	}
}

/**
 * 设置移动轨迹中的棋子
 */
void CJqBoard::UserMovePathCheen(int station, POINT ptFront, POINT ptStart, POINT ptEnd, int iFinalEndX, int iFinalEndY)
{
	int iFrontX,iFrontY,iStartX,iStartY,iEndX,iEndY,iTmp;
	iFrontX = ptFront.x;
	iFrontY = ptFront.y;
	iStartX = ptStart.x;
	iStartY = ptStart.y;
	iEndX = ptEnd.x;
	iEndY = ptEnd.y;

	ToMyCord(station, iFrontX, iFrontY, iFrontX, iFrontY);
	ToMyCord(station, iStartX, iStartY, iStartX, iStartY);
	ToMyCord(station, iEndX, iEndY, iEndX, iEndY);
	ToMyCord(station, iFinalEndX, iFinalEndY, iFinalEndX, iFinalEndY);

	if (iEndX==iFinalEndX && iEndY==iFinalEndY)
	{
		mBoard[iStartX][iStartY] = JQ_TYPE_NONE;
	}
	else if (iStartX==iFinalEndX && iStartY==iFinalEndY)
	{
		;
	}
	else
	{
		iTmp = mBoard[iStartX][iStartY];
		mBoard[iStartX][iStartY] = mBoard[iEndX][iEndY];
		mBoard[iEndX][iEndY] = iTmp;
	}
	
	if(bIsInBoard(iFrontX,iFrontY))
		mBoard[iFrontX][iFrontY]=JQ_TYPE_NONE;
}

/**
 * 设置刷新区域
 */
void CJqBoard::GetRefurbishRECT(RECT & rc, POINT start)
{
	int ii = start.x;
	int jj = start.y;
	int qi=mBoard[ii][jj];
	memset(&rc, 0, sizeof(rc));

	POINT p;
	int iTempX, iTempY;//临时x,y位置
	int ang=0;bool bb=false;
	p.x=m_ptBoardStartCenter.x + jj*g_CStaticGlbMj.mSzGrade.cx;
	iTempX = p.x;
	p.y=m_ptBoardStartCenter.y + ii*g_CStaticGlbMj.mSzGrade.cy;
	iTempY = p.y;	
	
	if(( ii == m_iStartI && jj == m_iStartJ)&&m_startqi!=JQ_TYPE_NONE)
	{
		//开始棋子角度
		int station=GetStationFromColor(GetAJqCol(m_startqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==0)
			ang=180;
		else if(station==1)
			ang=90;
		else if(station==3)
			ang=270;
		else
			ang=0;
	}	
	if(( ii == m_iEndI && jj == m_iEndJ)&&m_endqi!=JQ_TYPE_NONE)
	{
		//目标棋子角度
		int station=GetStationFromColor(GetAJqCol(m_endqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==0)
			ang=180;
		else if(station==1)
			ang=90;
		else if(station==3)
			ang=270;
		else
			ang=0;
	}	

	if(qi!=JQ_TYPE_NONE)
	{
		int station=GetStationFromColor(GetAJqCol(qi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==0)
			ang=180;
		else if(station==1)
			ang=90;
		else if(station==3)
			ang=270;
		else
			ang=0;
	}

	bb= ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10;///上
	if(bb)
	{
		if (8 <= jj)//从第8列开始
		{
			p.x = iTempX + 2;
		}
		if (10 == jj)//第10列
		{
			p.x = iTempX + 3;
		}

		p.y = iTempY + 1;//微调

		ang=180;
	}

	bb= ii >= 11 && ii <= 16 && jj >= 6 && jj <= 10;///下
	if(bb)
	{
        if (8 <= jj)//从第8列开始
        {
			p.x = iTempX + 2;
        }
		if (10 == jj)//第10列
		{
			p.x = iTempX + 3;
		}

		p.y = iTempY - 1;//微调
		ang=0;
	}

	
	bb= ii >= 6 && ii <= 10 && jj >= 0 && jj <= 5;///左
	if(bb)
	{
		p.y = iTempY - 1;

		if (8 <= ii)//从第8列开始
		{
			p.y = p.y + 2;
		}
		if (10 == ii)//第10列
		{
			p.y = p.y + 1;
		}
        p.x =  iTempX + 3;
		ang=270;
	}

	bb= ii >= 6 && ii <= 10 && jj >= 11 && jj <= 16;///右
	if(bb)
	{
		p.y = iTempY - 1;

		if (8 <= ii)//从第8列开始
		{
			p.y = p.y + 2;
		}
		if (10 == ii)//第10列
		{
			p.y = p.y + 1;
		}

		ang=90;
	}

	if(( ii == m_iStartI && jj == m_iStartJ)&&m_startqi!=JQ_TYPE_NONE)
	{
		//开始棋子角度
		int station=GetStationFromColor(GetAJqCol(m_startqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==2 && ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10)
			ang=0;
	}	
	
	if(( ii == m_iEndI && jj == m_iEndJ)&&m_endqi!=JQ_TYPE_NONE)
	{
		//目标棋子角度
		int station=GetStationFromColor(GetAJqCol(m_endqi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==2 && ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10)
			ang=0;
	}	
	if(qi!=JQ_TYPE_NONE)
	{
		int station=GetStationFromColor(GetAJqCol(qi));
		station=::g_pCClientGameDlg->ViewStation(station);
		if(station==2 && ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10)
			ang=0;
	}

	bb=GetAJqCol(qi) == m_MyColor&&(!IsWatcher()||m_bWatchOther);
	bb= !bb;
	//if(showfront) bb= false;
	
	CRect rcTmp=g_CStaticGlbMj.GetJqSrcRect(qi,ang,bb);
	rc.left = p.x - rcTmp.Width () / 2;
	rc.top= p.y - rcTmp.Height () / 2;
	rc.right = rc.left + rcTmp.Width ();
	rc.bottom = rc.top + rcTmp.Height ();	
}

int CJqBoard::GetJq(int station,int i,int j)
{
	int i1=-1,j1=-1;
	ToMyCord(station,i1,j1,i,j);
	return mBoard[i1][j1];
}

void  CJqBoard::ToMyCord(int station,int& toi,int& toj,int fi,int fj)
{
	toi=toj=-1;
	int viewstation=g_pCClientGameDlg->ViewStation (station );
	int ang=0;
	if(viewstation  == 2)ang =0;
	else if(viewstation  == 0)ang =180;
	else if(viewstation  == 1)ang =270;
	else if(viewstation  == 3)ang =90;
	Rotate(toi,toj,fi,fj,ang);
}

void CJqBoard::CopyOtherBuZhen(tagBuZhen& bz)//CPtrList & from,int DevSite)
{
	for(int i=0;i<bz.Count;i++)
	{
		int ii=i / 5 + 11 ,jj=i % 5 + 6, i1=-1 ,j1=-1;

		ToMyCord(bz.station,i1,j1,ii,jj);
		if(i1 < 0 || j1 < 0)continue;
		mBoard[i1][j1]=bz.CardArr[i];
	}
}

void  CJqBoard::FinishBuZhen ()
{
	m_bICanMove= false;
	m_iStartI =m_iStartJ= m_iEndI = m_iEndJ = -1;
	tagBuZhen bz;
	bz.Count = 0;
	bz.station = this->m_station;
	for(int i=11;i<= 16;i++)
		for(int j=6;j<=10;j++)
		{
			bz.CardArr[bz.Count ]=mBoard[i][j];
			bz.Count ++;
		}
	m_bFinishBuzhen=true;
	g_pCClientGameDlg->SendGameData(&bz,sizeof(bz),MDM_GM_GAME_NOTIFY,ASS_BUZHEN,0);
}

void CJqBoard::OnLBUp(CPoint& pt)
{
	if(IsWatcher( ))return;
	int ii=-1,jj=-1;
	CPoint p;  
	int dd2=g_CStaticGlbMj.mSzSrcQiZi.cx * g_CStaticGlbMj.mSzSrcQiZi.cx +g_CStaticGlbMj.mSzSrcQiZi.cy * g_CStaticGlbMj.mSzSrcQiZi.cy;
		dd2 /= 4;
	for(int i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
		{
			p.x=m_ptBoardStartCenter.x + j*g_CStaticGlbMj.mSzGrade.cx;
			p.y=m_ptBoardStartCenter.y + i*g_CStaticGlbMj.mSzGrade.cy ;
			int dd=(p.x - pt.x) * (p.x - pt.x) +(p.y - pt.y)* (p.y - pt.y);

			if(dd <= dd2)
			{
				ii =i;
				jj= j;
				break;
			}			
		}

	if(ii < 0 || jj < 0)
		return;
	if( GetStationParameter() == GS_BUZHEN||GetStationParameter() == GS_WAIT_ARGEE)
	{
		if(!m_bICanMove)return ;
		if(mBoard[ii][jj] == JQ_TYPE_NONE)return;
		
		if(!bIsInMyBuZhenArea(ii,jj))return;

		if(GetAJqCol(mBoard[ii][jj]) != m_MyColor)return;
		if(m_iStartI < 0 || m_iStartJ < 0)
		{
			m_iStartI =ii;
			m_iStartJ= jj;
			return;
		}

		if(m_iEndI < 0 || m_iEndJ < 0)
		{
			m_iEndI =ii;
			m_iEndJ= jj;
			Exchang2QiZiInBuZhen(m_iEndI,m_iEndJ,m_iStartI,m_iStartJ);
			return;
		}

		
		m_iStartI =m_iStartJ= m_iEndI = m_iEndJ = -1;

		m_iStartI =ii;
		m_iStartJ= jj;

		return;
	}


	if( GetStationParameter() == GS_PLAY_GAME)
	{
		if(!m_bICanMove)return;
		if(m_iNowOutPeople != m_station)return;
		if(!bIsInBoard(ii,jj))return;
		if(m_iStartI < 0 || m_iStartJ < 0)goto ret;
		
		if((0==m_iStartI&&7==m_iStartJ)||(0==m_iStartI&&9==m_iStartJ)||
			(7==m_iStartI&&0==m_iStartJ)||(9==m_iStartI&&0==m_iStartJ)||
			(7==m_iStartI&&16==m_iStartJ)||(9==m_iStartI&&16==m_iStartJ)||
			(16==m_iStartI&&7==m_iStartJ)||(16==m_iStartI&&9==m_iStartJ))
		{
			//大本营内的棋子不能走
			m_iStartI=m_iStartJ=-1;
			return ;
		}

		if(m_iStartI==m_iJingQiI&&m_iStartJ==m_iJingQiJ)
		{
			m_iStartI=m_iStartJ=-1;
			return ;
		}

		if(m_iEndI < 0 || m_iEndJ < 0)
		{
			m_iEndI =ii;
			m_iEndJ= jj;
			
			bool bb=MoveQiZi(m_iEndI,m_iEndJ,m_iStartI,m_iStartJ,true);			
			if(!bb)
			{
			  m_iEndI = m_iEndJ = -1;
			  Msg("Test:DDDD %d==%d__start%d,%d end%d,%d__ %d",GetAJqCol(mBoard[m_iEndI][m_iEndJ]),m_MyColor,m_iStartI,m_iStartJ,m_iEndI,m_iEndJ,bb);
			  
			  if (mBoard[ii][jj]==MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL))return;
			  if (mBoard[ii][jj]==MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_JQ))return;

			  if (mBoard[ii][jj]!=JQ_TYPE_NONE && GetAJqCol(mBoard[ii][jj])==m_MyColor)
			  {				  
				  m_iStartI = ii;
				  m_iStartJ = jj;
				  m_iEndI = m_iEndJ = -1;
			  }

			  Msg("Test:DDDD start%d,%d end%d,%d",m_iStartI,m_iStartJ,m_iEndI,m_iEndJ);
			  return;
			}
			m_bICanMove=false;


			tagMove  m;
			memset(m.cPath, 255, sizeof(m.cPath));
			m.m_iStartI=m_iStartI;
			m.m_iStartJ=m_iStartJ;
			m.m_iEndI=m_iEndI;
			m.m_iEndJ=m_iEndJ;			

			// 获得刚走棋的步子，传给服务器
			CPoint * pPt=NULL;
			POSITION pTrList=g_StepLine.List.GetTailPosition();
			UINT k=0;
			POINT ptLast,ptCurrent;
			ptLast.x = ptLast.y = 255;

			while (NULL!=pTrList)
			{
				pPt = (CPoint *)(g_StepLine.List.GetPrev(pTrList));

				if (NULL!=pPt)
				{
					//不要相信K的顺序就是真正走棋顺序，原本我也这样想。结果往往理想与现实差距甚远
					//K值只要不为255，算法就会认为是合法的路径
					Msg("Test:Step:  前位置(%d,%d)， 后位置（%d,%d)",ptLast.x,ptLast.y,pPt->x,pPt->y);
					if (0<=pPt->x && MAX_I>pPt->x && 0<=pPt->y && MAX_J>pPt->y)
					{
						ptCurrent.x = pPt->x;
						ptCurrent.y = pPt->y;

						//如果两位置都在‘田’字位置则需要插入它们之间跳过的位置，这样方便于显示轨迹
						if (GetCenterFarmWordPath(ptCurrent) && GetCenterFarmWordPath(ptLast))
						{
							POINT pTmp;
							pTmp.x = ptLast.x + (ptLast.x-ptCurrent.x)/2*(-1);
							pTmp.y = ptLast.y + (ptLast.y-ptCurrent.y)/2*(-1);
							m.cPath[pTmp.x][pTmp.y] = ++k;
						}

						m.cPath[pPt->x][pPt->y] = ++k;
						ptLast.x = pPt->x;
						ptLast.y = pPt->y;
					}
				}
			}

			m.iStep = k;
			g_pCClientGameDlg->SendGameData(&m,sizeof(m),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);
			g_pCClientGameDlg->KillAllTimer();
			Msg("Test:Step f Send ASS_OUT_CARD");
		
			/////////////////
			for (BYTE i=0;i<17;i++)
				for(BYTE j=0;j<17;j++)
					if (m.cPath[i][j]!=255)
						Msg("Test:Step:  g (%d %d)", i, j);

			///////////////////////

			return;
		}
ret:
		if (mBoard[ii][jj] == JQ_TYPE_NONE)return;
		if (GetAJqCol(mBoard[ii][jj]) != m_MyColor)return;
		if (mBoard[ii][jj]==MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL))return;
		if (mBoard[ii][jj]==MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_JQ))return;

		m_iStartI =m_iStartJ= m_iEndI = m_iEndJ = -1;

		m_iStartI =ii;
		m_iStartJ= jj;
		return;
	}
}

void CJqBoard::OnPaint(CDC *pdc)
{
	// 绘制路径
	DrawPath(pdc);

	for(int i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
			SetAQiZi(i,j,pdc);

	ShowAllJunQiFlag(pdc);
}

void CJqBoard::DrawPath(CDC * pDC)
{
	for (int ii=0; ii<MAX_I; ii++)
	{
		for (int jj=0; jj<MAX_J; jj++)
		{
			if(255==m_Path[ii][jj] || !bIsInBoard(ii,jj))
				continue;
			
			int qi=m_Path[ii][jj];
			CPoint p;
			int iTempX, iTempY;//临时x,y位置
			p.x=m_ptBoardStartCenter.x + jj*g_CStaticGlbMj.mSzGrade.cx;
			iTempX = p.x;
			p.y=m_ptBoardStartCenter.y + ii*g_CStaticGlbMj.mSzGrade.cy;
			iTempY = p.y;
			int ang=0;bool bb=false;

			if(( ii == m_iStartI && jj == m_iStartJ)&&m_startqi!=JQ_TYPE_NONE)
			{
				//开始棋子角度
				int station=GetStationFromColor(GetAJqCol(m_startqi));
				station=::g_pCClientGameDlg->ViewStation(station);
				if(station==0)
					ang=180;
				else if(station==1)
					ang=90;
				else if(station==3)
					ang=270;
				else
					ang=0;
			}	

			if(( ii == m_iEndI && jj == m_iEndJ)&&m_endqi!=JQ_TYPE_NONE)
			{
				//目标棋子角度
				int station=GetStationFromColor(GetAJqCol(m_endqi));
				station=::g_pCClientGameDlg->ViewStation(station);
				if(station==0)
					ang=180;
				else if(station==1)
					ang=90;
				else if(station==3)
					ang=270;
				else
					ang=0;
			}	

			if(qi!=JQ_TYPE_NONE)
			{
				int station=GetStationFromColor(GetAJqCol(qi));
				station=::g_pCClientGameDlg->ViewStation(station);
				if(station==0)
					ang=180;
				else if(station==1)
					ang=90;
				else if(station==3)
					ang=270;
				else
					ang=0;
			}

			bb= ii >= 0 && ii <= 5 && jj >= 6 && jj <= 10;///上
			if(bb)
			{
				if (8 <= jj)//从第8列开始
				{
					p.x = iTempX + 2;
				}
				if (10 == jj)//第10列
				{
					p.x = iTempX + 3;
				}

				p.y = iTempY + 1;//微调
				ang=180;
			}

			bb= ii >= 11 && ii <= 16 && jj >= 6 && jj <= 10;///下
			if(bb)
			{
				if (8 <= jj)//从第8列开始
				{
					p.x = iTempX + 2;
				}
				if (10 == jj)//第10列
				{
					p.x = iTempX + 3;
				}

				p.y = iTempY - 1;//微调
				ang=0;
			}


			bb= ii >= 6 && ii <= 10 && jj >= 0 && jj <= 5;///左
			if(bb)
			{
				p.y = iTempY - 1;

				if (8 <= ii)//从第8列开始
				{
					p.y = p.y + 2;
				}
				if (10 == ii)//第10列
				{
					p.y = p.y + 1;
				}
				p.x =  iTempX + 3;
				ang=270;
			}

			bb= ii >= 6 && ii <= 10 && jj >= 11 && jj <= 16;///右
			if(bb)
			{
				p.y = iTempY - 1;

				if (8 <= ii)//从第8列开始
				{
					p.y = p.y + 2;
				}
				if (10 == ii)//第10列
				{
					p.y = p.y + 1;
				}

				ang=90;
			}

			g_CStaticGlbMj.ShowPath(pDC,p,m_Path[ii][jj],ang,ii,jj);
		}
	}
}

void  CJqBoard::EmptyStepLine()
{
	g_CurI = g_CurJ = -1;
	g_StepLine.Empty();
}


bool CJqBoard::MoveQiZi(int iTo,int jTo,int iFrom,int jFrom,bool IsIPut)
{
	 if(!MoveQiZi1(iTo, jTo, iFrom, jFrom))
		 return false;
	return true;
}

bool CJqBoard::bGBGoRailway1(int iTo,int jTo,int iFrom,int jFrom)
{
	bool bb=false;
	if(bIsInRailway(iFrom,jFrom))
	{
		Msg("Test:Step: h [%d,%d]", iFrom,jFrom);
		g_StepLine.Push (iFrom,jFrom);
		mBoard[iFrom][jFrom]=Have_Checked;
		
	}

	while(!g_StepLine.IsEmpty ())
	{
		int ii,jj;
		if(!g_StepLine.GetTop (ii,jj))return false;
		if(ii==iTo && jj == jTo)
		{
			Msg("Test:Step: i Pop[%d,%d]", ii, jj);
			g_StepLine.Pop (ii, jj);
			return true;
		}
		bool b=bCanGoThrough(iTo, jTo,ii,jj);
		if(!b)b=bPushChaXian(iTo,jTo,ii,jj,g_StepLine);
        if(!b)
		{
			Msg("Test:Step: j Pop[%d,%d]", ii, jj);
			g_StepLine.Pop (ii, jj);
		}
	}
	return false;
}

bool CJqBoard::bPushChaXian(int iTo,int jTo,int ii,int jj,CPStack& s)
{
	int ip=-1,jp=-1;
	if(ii == 5 && jj == 6){ip=6;jp=5;}
	if(ii == 5 && jj ==10){ip=6;jp=11;}
	if(ii == 6 && jj == 5){ip=5;jp=6;}
	if(ii == 6 && jj == 11){ip=5;jp=10;}
	
	if(ii == 10 && jj == 5){ip=11;jp=6;}
	if(ii == 10 && jj == 11){ip=11;jp=10;}
	if(ii == 11 && jj == 6){ip=10;jp=5;}
	if(ii == 11 && jj == 10){ip=10;jp=11;}

	if(ip < 0 || jp < 0)return false;

	if(ip==iTo && jp == jTo)
	{
		mBoard[ip][jp]=Have_Checked;
		s.Push (ip,jp);   
		return true;
	}
	if(mBoard[ip][jp] != JQ_TYPE_NONE)return false;
	if(mBoard[ip][jp] == Have_Checked)return false;

	if(bIsInRailway(ip,jp) )// && bCanGoThrough(ip,jp))
	{
		mBoard[ip][jp]=Have_Checked;
		s.Push (ip,jp);
		return true;
	}

	return false;
}

bool CJqBoard::bGBGoRailway(int iTo,int jTo,int iFrom,int jFrom)
{
	int i;////Microsoft VisualC++2005/MFC8.0
	if(GET_A_JQ_NAME( mBoard[iFrom][jFrom]) != JQ_TYPE_NAME_GB)return false;
	int tmpbd[MAX_I][MAX_J];
	for(i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
	      tmpbd[i][j]=  mBoard[i][j];
	bool bb= bGBGoRailway1(iTo,jTo,iFrom,jFrom);


	for( i=0;i<MAX_I;i++)
		for( int j=0;j<MAX_J;j++)
	      mBoard[i][j]=  tmpbd[i][j];

	return bb;

}

bool CJqBoard::CanGoJ(int fromj,int toj,int ii)
{
	int startj=fromj,endj=toj;
	if(startj >= endj)
	{
		for(int j=fromj - 1;j > endj;j--)
		{
			int ff=mBoard[ii][j];
			if(ff != JQ_TYPE_NONE)return false;
			Msg("Test:Step: k [%d,%d]", ii, j);
			g_StepLine.Push (ii, j);
		}
	}
	else
	{
	
		for(int j=startj + 1;j<endj;j++)
		{
			int ff=mBoard[ii][j];
			if(ff != JQ_TYPE_NONE)return false;
			Msg("Test:Step: l [%d,%d]", ii, j);
			g_StepLine.Push (ii, j);
		}
	}
	return true;
}

bool CJqBoard::CanGoI(int fromi,int toi,int jj)
{

	int starti=fromi,endi=toi;
	if(starti >= endi)
	{
		for(int i=starti - 1;i > endi;i--)
		{
			int ff=mBoard[i][jj];
			if(ff != JQ_TYPE_NONE)return false;
			Msg("Test:Step: m [%d,%d]", i, jj);
			g_StepLine.Push (i, jj);
		}
	}
	else
	{
		for(int i=starti + 1;i<endi;i++)
		{
			int ff=mBoard[i][jj];
			if(ff != JQ_TYPE_NONE)return false;
			Msg("Test:Step: n [%d,%d]", i, jj);
			g_StepLine.Push (i, jj);
		}
	}
	return true;
}

bool CJqBoard::CanGoCircle(int iTo,int jTo,int iFrom,int jFrom)
{
	////走弯线	

	if(jFrom == 6)
	{
		if(jTo > 5)return false;
		if(iTo == 6)
		{
			if(iFrom > 5)return false;
			
			if(!CanGoI(iFrom,6,jFrom))return false;
			return CanGoJ(6,jTo,6);
		}
		if(iTo == 10)
		{
			if(iFrom < 11)return false;
			if(!CanGoI(iFrom,10,jFrom))return false;
			return CanGoJ(6,jTo,10);
		}
		return false;
	}
	if(jFrom == 10)
	{
		if(jTo < 11)return false;
		if(iTo == 6)
		{
			if(iFrom > 5)return false;
			if(!CanGoI(iFrom,6,jFrom))return false;
			return CanGoJ(10,jTo,6);
		}
		if(iTo == 10)
		{
			if(iFrom < 11)return false;
			if(!CanGoI(iFrom,10,jFrom))return false;
			return CanGoJ(10,jTo,10);
		}
		return false;
	}

	if(iFrom == 6)
	{
		if(iTo > 5)return false;
		if(jTo == 6)
		{
			if(jFrom > 5)return false;
			if(!CanGoJ(jFrom,6,iFrom))return false;
			return CanGoI(6,iTo,6);
		}
		if(jTo == 10)
		{
			if(jFrom  < 11)return false;
			if(!CanGoJ(jFrom,10,iFrom))return false;
			return CanGoI(6,iTo,10);
		}
		return false;
	}
	if(iFrom == 10)
	{
		if(iTo < 11)return false;
		if(jTo == 6)
		{
			if(jFrom > 5)return false;
			if(!CanGoJ(jFrom,6,iFrom))return false;
			return CanGoI(10,iTo,6);
		}
		if(jTo == 10)
		{
			if(jFrom  < 11)return false;
			if(!CanGoJ(jFrom,10,iFrom))return false;
			return CanGoI(10,iTo,10);
		}
		return false;
	}
	return false;
}

bool CJqBoard::IsCanMove2Qi(int toQi,int fromQi)///子能吃或移动
{
	if( fromQi == JQ_TYPE_NONE )return false;

	///地雷和军旗不能移动

	if( 
		GET_A_JQ_NAME(fromQi) == JQ_TYPE_NAME_JQ || 
		GET_A_JQ_NAME(fromQi) == JQ_TYPE_NAME_DL
		)return false;

	if( toQi == JQ_TYPE_NONE )return true;

	int fCol=GET_A_JQ_COLOR(fromQi),tCol=GET_A_JQ_COLOR(toQi);
	if(2==m_iPlayerCount)
	{
		return fCol!=tCol;
	}
	if(fCol == JQ_TYPE_COLOR_RED || fCol == JQ_TYPE_COLOR_BLACK)
		return tCol == JQ_TYPE_COLOR_BLUE || tCol == JQ_TYPE_COLOR_GRAY;

	if(fCol == JQ_TYPE_COLOR_GRAY || fCol == JQ_TYPE_COLOR_BLUE)
		return tCol == JQ_TYPE_COLOR_RED || tCol == JQ_TYPE_COLOR_BLACK;

	return false;
}


bool CJqBoard::bIsInBoard(int i,int j)
{
	bool NotIn =
        (i< 6 && j <6) || 
		(i> 10 && j <6) || 
		(i< 6 && j > 10) || 
		(i> 10 && j > 10) ||

		( (i==7 || i==9 )&& (j >= 6 && j <= 10) )||
		( (j==7 || j==9 )&& (i >= 6 && i <= 10) );

		return !NotIn;
}

bool CJqBoard::bIsInJuYin(int i,int j)////在军营
{
	return
        
		((i==2 || i==4 || i==12 || i==14)&& ( j == 7 || j == 9)) ||
		((j==2 || j==4 || j==12 || j==14)&& ( i == 7 || i == 9)) ||
		((i == 3 || i == 13) && j == 8) ||
		((j == 3 || j == 13) && i == 8);
}

bool CJqBoard::bIsInDaBenYin(int i,int j)////在大本营
{
	return( i == 7 || i == 9) && ( j == 0 || j == 16) ||
		( j == 7 || j == 9) && ( i == 0 || i == 16);
}

///////update////////////////////////////////
bool  CJqBoard::Exchang2QiZiInBuZhen(int iTo,int jTo,int iFrom,int jFrom)
{
	if(!bIsInBoard(iTo,jTo))return false;
	if(!bIsInBoard(iFrom,jFrom))return false;
	if(!bIsInBoard(iTo,jTo))return false;
	int tQi=mBoard[iTo][jTo],fQi=  mBoard[iFrom][jFrom];
	if(fQi == JQ_TYPE_NONE)return false;
	if(tQi == JQ_TYPE_NONE)return false;

	int fName = GET_A_JQ_NAME(fQi),tName = GET_A_JQ_NAME(tQi);

	if(
		iTo == 11 && fName== JQ_TYPE_NAME_ZD ||
		iFrom == 11 && tName== JQ_TYPE_NAME_ZD
		)return false;

	if( 
		fName== JQ_TYPE_NAME_DL && !(iTo == 15 || iTo == 16 )||
		tName== JQ_TYPE_NAME_DL && !(iFrom == 15 || iFrom == 16)
		)return false;

	if( 
		fName== JQ_TYPE_NAME_JQ && !bIsInDaBenYin(iTo,jTo) ||
		tName== JQ_TYPE_NAME_JQ && !bIsInDaBenYin(iFrom,jFrom)
		)return false;
	

	mBoard[iTo][jTo] = fQi;//SetAQiZi(iTo,jTo);
	mBoard[iFrom][jFrom] = tQi;//SetAQiZi(iFrom,jFrom);
	return true;
}


CJqBoard::~CJqBoard(void)
{
	Msg("Test:Step: u empty EmptyStepLine");
	EmptyStepLine();
}

///static fun
bool CJqBoard::bIsInMyBuZhenArea(int i,int j)////在我的布子范围
{
	bool NotIn=
			i>16  || j>10 || 
			i < 11  || j < 6 ||
			( i==12 || i==14 ) && ( j == 7 || j == 9) ||
			i==13 && j == 8 
		;
	return !NotIn;
}

bool CJqBoard::bIsInRailway(int i,int j)////在铁道线
{
	bool In =
        ( (i > 0 && i< 16 && i != 7 && i != 9 ) && (j == 6 ||  j == 10)) || 
		( (j > 0 && j< 16 && j != 7 && j != 9 ) && (i == 6 ||  i == 10)) || 
		( (j > 5 && j< 11  ) && (i == 1 ||  i == 5 || i == 11 ||  i == 15) )|| 
		( (i > 5 && i< 11  ) && (j == 1 ||  j == 5 || j == 11 ||  j == 15) )|| 
		(i==8 && j == 8 );
	return In;
}

void CJqBoard::LoadBuZhen()
{
   	TCHAR path[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH,path);
	
	CFileDialog FileDlg(TRUE,"bzjq",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"军棋布局文件(*.bzjq)|*.bzjq||",&::g_pCClientGameDlg->m_PlayView);
	FileDlg.m_ofn.lpstrTitle=TEXT("调入布局");
	FileDlg.m_ofn.lpstrInitialDir=path;
	if (FileDlg.DoModal()!=IDOK)
	{
		return ;
	}
	::SetCurrentDirectory(path);

   CFile file;
   if(!file.Open (FileDlg.GetPathName(),CFile::modeRead ))return;


   BuZhenNode nd;

   while(1)
   {
	   int len=file.Read (&nd,sizeof(nd));
	   if(len != sizeof(nd))break;

	    mBoard[nd.i][nd.j]=MakeAJq(this->m_MyColor ,nd.jqname) ;
   }

   file.Close ();
}

void CJqBoard::SaveBuZhen()
{
	TCHAR path[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH,path);

	CFileDialog FileDlg(FALSE,"bzjq",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"军棋布局文件(*.bzjq)|*.bzjq||",&::g_pCClientGameDlg->m_PlayView);
	FileDlg.m_ofn.lpstrTitle=TEXT("保存布局");
	FileDlg.m_ofn.lpstrInitialDir=path;
	if (FileDlg.DoModal()!=IDOK)
	{
		return ;
	}

	::SetCurrentDirectory(path);
	CFile file;
	BuZhenNode nd;

	if(!file.Open (FileDlg.GetPathName(),CFile::modeWrite | CFile::modeCreate ))
		return;

	for(int i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
		{
			if(!bIsInMyBuZhenArea(i,j))continue;

			nd.i=i;nd.j=j;
			nd.jqname =GetAJqName(mBoard[i][j]);
			file.Write (&nd,sizeof(nd));
		}

   file.Close ();
}

bool CJqBoard::bCanIMove(void)
{
	int jq=JQ_TYPE_NONE;
	int fCol=-1;
	for(int i=0;i<17;i++)
	{
		for(int j=0;j<17;j++)
		{
			if((0==i&&7==j) || (0==i&&9==j)
				||(7==i&&0==j) || (9==i&&0==j)
				||(7==i&&16==j) || (9==i&&16==j)
				||(16==i&&7==j) || (16==i&&9==j))
			{
				//大本营内的棋子不能走
				continue;
			}
			jq=mBoard[i][j];
			if(jq==JQ_TYPE_NONE)
				continue;
			fCol=GET_A_JQ_COLOR(jq);
			if(fCol!=m_MyColor)
				continue;
			if(16==i)
			{
				int jqn=GET_A_JQ_NAME(mBoard[i-1][j]);
				if(JQ_TYPE_NAME_JQ==jqn || JQ_TYPE_NAME_DL==jqn)
					continue;
			}
			if(	GET_A_JQ_NAME(jq) == JQ_TYPE_NAME_JQ 
				|| GET_A_JQ_NAME(jq) == JQ_TYPE_NAME_DL)
				continue;
			return true;
		}
	}
	return false;
}

CJqBoard::CJqBoard(void)//:IGameUI()
{
	m_station=m_viewstation=m_MyColor=-1;
	for(int i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
	        mBoard[i][j]=JQ_TYPE_NONE;	
}
void CJqBoard::StartBuzhen()
{
	m_bICanMove = true;
	mBoard[11][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_YZ);
	mBoard[11][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_GB);
	mBoard[11][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_JZ);
	mBoard[11][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_GB);
	mBoard[11][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_YZ);

	mBoard[12][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_PZ);
	mBoard[12][7]=JQ_TYPE_NONE;
	mBoard[12][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIANZ);
	mBoard[12][9]=JQ_TYPE_NONE;
	mBoard[12][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_PZ);

	mBoard[13][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_SZ);
	mBoard[13][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_ZD);
	mBoard[13][8]=JQ_TYPE_NONE;
	mBoard[13][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_ZD);
	mBoard[13][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_SZ);

	mBoard[14][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_TZ);
	mBoard[14][7]=JQ_TYPE_NONE;
	mBoard[14][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIANZ);
	mBoard[14][9]=JQ_TYPE_NONE;
	mBoard[14][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_TZ);

	mBoard[15][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIZ);
	mBoard[15][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_SL);
	mBoard[15][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_GB);
	mBoard[15][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIZ);
	mBoard[15][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL);

	mBoard[16][6]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL);
	mBoard[16][7]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_JQ);
	mBoard[16][8]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_DL);
	mBoard[16][9]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_PZ);
	mBoard[16][10]=MAKE_A_JQ(m_MyColor,JQ_TYPE_NAME_LIANZ);
}


