#include "StdAfx.h"
#include "jqlogic.h"
#include "ServerManage.h"

void  CJqLogic::CountFen(int fen[])
{
	int win=-1;
	for(int i=0;i<4;i++)fen[i] = 0;
	for(int i=0;i<m_maxPeople;i++)
	{
		if(!IsStationLose(i))
		{
			win =i;
			break;
		}
	} 
	TCHAR sz[100];
	wsprintf(sz,"win %d",win);
	Testlog(sz);
	if(win < 0)return;
	int f=1;
	if(mLoseStationList.GetCount () <= 2)f=2;
	for(int i=0;i<4;i++)fen[i] = -f;
	fen[win] = f;
	if(4 == m_iPlayerCount)
		fen[(win + 2) % 4] = f;
	if(mLoseStationList.GetCount () == m_iPlayerCount)
	{
		memset(fen,0,sizeof(fen));
	}
}

int CJqLogic::GetNextStation(int station)
{
	if(mLoseStationList.GetCount () >= m_iPlayerCount)return -1;
	int ns=station;
	while(1)
	{
		int n=3;
		if(2==m_iPlayerCount && m_maxPeople==4)//如果是两个在玩,则
			n=2;
		ns=(ns + n) % m_maxPeople;
		if(!IsStationLose(ns))return ns;
	}
	return 0;
}

void CJqLogic::UserMove(tagMove &move,    tagMoveResult&   result)
{
	int ang=0;
	if(m_maxPeople==2)
	{
		if(result.station  == 0)ang =0;
		else if(result.station  == 1)ang =180;
	}
	else
	{
		if(result.station  == 2)ang =0;
		else if(result.station  == 0)ang =180;
		else if(result.station  == 1)ang =270;
		else if(result.station  == 3)ang =90;
		else return;
	}
	int si=-1,sj=-1;
	Rotate(si,sj,move.m_iStartI,move.m_iStartJ,ang);

	if(si <0 || sj < 0)return;
	int sqi=mBoard[si][sj];
	int ei=-1,ej=-1;
	Rotate(ei,ej,move.m_iEndI,move.m_iEndJ,ang);

	if(ei <0 || ej < 0)return;
	int eqi=mBoard[ei][ej];

	int loseColor=-1;
	

	int c=Compare(eqi,sqi);
	
	if(c < 0)
	{//sqi大
		if(GetAJqName(eqi) == JQ_TYPE_NAME_JQ)
		{
			loseColor=GetAJqCol(eqi);
			eqi=sqi;
			sqi=JQ_TYPE_NAME_JQ;
		}
		else
		{
			eqi=sqi;
			sqi=JQ_TYPE_NONE;
		}
	}
	else if(c == 0)
	{//平
		if(GetAJqName(eqi) == JQ_TYPE_NAME_JQ)
			loseColor=GetAJqCol(eqi);
		eqi=JQ_TYPE_NONE;
		sqi=JQ_TYPE_NONE;
	}
	else
	{
		sqi=JQ_TYPE_NONE;
	}

	result.m_iStartI=move.m_iStartI;
	result.m_iStartJ=move.m_iStartJ;
	result.m_iEndI=move.m_iEndI;
	result.m_iEndJ=move.m_iEndJ;
	result.ToJq=eqi;
	result.FromJq=sqi;



	mBoard[si][sj]= (result.FromJq==JQ_TYPE_NAME_JQ)?JQ_TYPE_NONE:result.FromJq;
	mBoard[ei][ej]=result.ToJq;

	m_iStartI =si;
	m_iStartJ=sj;
	m_iEndI =ei;
	m_iEndJ = ej;

	result.loseColor=-1;
	result.loseColor2=-1;
	if(loseColor >= 0) 
	{
		ClearColorAllQiZi(loseColor);
		int *p=new int;
		*p=GetStationFromColor(loseColor);//result.station;
		mLoseStationList.AddTail (p);
		result.loseColor=loseColor;
	}
	if(JQ_TYPE_NONE==result.ToJq)
	{//计算哪些玩家已经无子可下
		bool cor[4];
		GetDeadPeople(cor);
		for(int i=0; i<4; i++)
		{
			if(cor[i])
				continue;			
			int station=GetStationFromColor(i);
			if(station!=m_iStation && station!=(m_iStation+2)%4 && 2==m_iPlayerCount&&m_maxPeople==4)//如果这两个位置是没人的
				continue;
			if(station>=m_maxPeople)
				continue;
			if(IsStationLose(station))
				continue;
			TCHAR sz[100];
			wsprintf(sz,"lose station %d",station);
			Testlog(sz);
			if(-1 == result.loseColor)
				result.loseColor = i;
			else
				result.loseColor2 = i;
			ClearColorAllQiZi(i);
			int *p=new int;
			*p=station;
			mLoseStationList.AddTail (p);
		}
	}
	result.nextstation=GetNextStation(result.station);//ns;
}

bool CJqLogic::IsFinish()
{
	int cot=mLoseStationList.GetCount ();
	if(cot >=m_maxPeople-1)
		return true;
	if(cot>=m_iPlayerCount-1)
		return true;
	if(cot >= 3)return true;
	
	if(cot == 2)
	{
		int *p1=(int *)mLoseStationList.GetHead ();
		if(!p1)return false;
		int *p2=(int *)mLoseStationList.GetTail ();
		if(!p2)return false;	

		if(( *p1 + *p2 )== 2)//0,1
			return true;
		if( (*p1 + *p2) == 4)//2,3
			return true;	
	}
	return false;
}

/**
 * 得到已布阵的人数
 */
int CJqLogic::GetBuzhenCount()
{
	int count=0;
	for(int i=0; i<4; i++)
	{
		if(m_bBuzhen[i])
			count++;
	}
	return count;
}

bool CJqLogic::UserLeft(BYTE bDeskStation)
{
	m_bBuzhen[bDeskStation]=false;
	tagBuZhen  bz;
	bz.station=bDeskStation;
	bz.Count=30;
	for(int i=0;i<bz.Count;i++)
	{
		bz.CardArr[i]=JQ_TYPE_NONE;
	}
	
	int ang=0;
	if(m_maxPeople==2)
	{
		if(bz.station  == 0)ang =0;
		else if(bz.station  == 1)ang =180;
	}
	else
	{
		if(bz.station  == 2)ang =0;
		else if(bz.station  == 0)ang =180;
		else if(bz.station  == 1)ang =270;
		else if(bz.station  == 3)ang =90;
		else return true;
	}

	for(int i=0;i<bz.Count;i++)
	{
		int ii=i / 5 + 11 ,jj=i % 5 + 6, i1=-1 ,j1=-1;
		Rotate(i1,j1,ii,jj,ang);
		if(i1 < 0 || j1 < 0)continue;
		mBoard[i1][j1]=bz.CardArr[i];
	}
	return true;
}

void CJqLogic::UserBuZhen(tagBuZhen& bz)
{
	m_bBuzhen[bz.station]=true;
	if(GetBuzhenCount() == 1)m_iNowOutPeople = bz.station;
	
	int ang=0;
	if(m_maxPeople==2)
	{
		if(bz.station  == 0)ang =0;
		else if(bz.station  == 1)ang =180;
	}
	else
	{
		if(bz.station  == 2)ang =0;
		else if(bz.station  == 0)ang =180;
		else if(bz.station  == 1)ang =270;
		else if(bz.station  == 3)ang =90;
		else return;
	}

	for(int i=0;i<bz.Count;i++)
	{
		int ii=i / 5 + 11 ,jj=i % 5 + 6, i1=-1 ,j1=-1;
		Rotate(i1,j1,ii,jj,ang);
		if(i1 < 0 || j1 < 0)continue;
		mBoard[i1][j1]=bz.CardArr[i];
	}

	
}

CJqLogic::CJqLogic()
{
	m_iNowOutPeople=-1;
	m_maxPeople=PLAY_COUNT;
	Init();
}
CJqLogic::~CJqLogic(void)
{
}
int CJqLogic::GetBaseFen(int f)
{
	__int64 uBasePoint[20]=
	{
		0, 10, 30,
		60, 100, 200,
		400, 640, 920,
		1240, 2140, 4640,
		7390, 10390, 13640,
		20640, 35640, 51640,
		68640, 86640
	};
	int fen[20]=
	{
		1, 2, 3, 4, 5,
		10, 12, 14, 16, 18,
		50,	55, 60, 65, 70,
		150,160, 170, 180, 190
	};
	for(int i=0;i<20;i++)
		if (f<uBasePoint[i])
			return fen[i];
	return fen[19];
}
