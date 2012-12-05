#pragma once

#include "../GameMessage\JqLogic0.h"


/// class CServerGameDesk;
class CJqLogic:public CJqLogic0 
{ 
protected:
	
public :
	CPtrList mLoseStationList;
	void CountFen(int fen[]);
	int GetNextStation(int station);

	///CServerGameDesk *m_pServer;

	void UserMove(tagMove &move,    tagMoveResult&   result);
	int m_maxPeople;

	bool m_bBuzhen[4];
	void UserBuZhen(tagBuZhen& bz);

	void Init()
	{
		while(!mLoseStationList.IsEmpty ())
		{
			int *p=(int *)mLoseStationList.RemoveHead ();
			if(p)delete p;
		}
		mLoseStationList.RemoveAll ();
		
		m_iStartI =m_iStartJ= m_iEndI = m_iEndJ = -1;
		
		for(int i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
	        mBoard[i][j]=JQ_TYPE_NONE;
		for(int i=0;i<4;i++)
			m_bBuzhen[i]=false;
		m_iPlayerCount=0;
	}

	bool IsStationLose(int station)
	{
		for(POSITION pos=mLoseStationList.GetHeadPosition ();pos != NULL;)
		{
			int *p=(int *)mLoseStationList.GetNext (pos);
			if(!p)continue;
			if(*p == station)return true;
		}
		return false;
	}
	bool IsFinish();
	CJqLogic();
	~CJqLogic(void);
public:
	int GetBaseFen(int fen);
	int GetBuzhenCount();
	bool UserLeft(BYTE bDeskStation);
};


