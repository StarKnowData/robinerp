
#include "StdAfx.h"
#include "UpGradeLogic.h"


CUpGradeGameLogic::CStack::CStack()
{

}


CUpGradeGameLogic::CStack::CStack(CUpGradeGameLogic::CStack &s)
{
	for (POSITION pos = s.m_list.GetHeadPosition();pos;)
	{
		tagPointNode *p = (tagPointNode *) s.m_list.GetNext(pos);
		if (!p) return;
		tagPointNode *pn = new tagPointNode(p->i,p->j);
		m_list.AddTail(pn);
	}
	

	/*for (int pos = s.m_list.GetHeadPosition();pos >= 0;)
	{
		tagPointNode *p = s.m_list.GetNext(&pos);
		if (!p) return;
		tagPointNode *pn = new tagPointNode(p->i,p->j);
		m_list.AddTail(pn);
	}*/
}


/*CWQGameLogic::CStack & operator =(CWQGameLogic::CStack &s)
{
	for (int pos = s.m_list.GetHeadPosition();pos >= 0;)
	{
		tagPointNode *p = s.m_list.GetNext(&pos);
		///if (!p) return *this;
		tagPointNode *pn = new tagPointNode(p->i,p->j);
		//m_list.AddTail(pn);
	}

	//return *this;
}*/


bool CUpGradeGameLogic::CStack::bPop(int *piRet, int *pjRet)
{
	if (bIsEmpty()) return false;
	tagPointNode *p = (tagPointNode *) m_list.GetHead();
	if (!p) return false;

	*piRet = p->i;
	*pjRet = p->j;
	m_list.RemoveHead();
	
	///delete p;
	//p = NULL;
	return true;
}


bool CUpGradeGameLogic::CStack::bGetTop(int *piRet, int *pjRet)
{
	if (bIsEmpty()) return false;
	tagPointNode *p = (tagPointNode *) m_list.GetHead();
	if (!p) return false;

	*piRet = p->i;
	*pjRet = p->j;
	
	//delete p;
	//p = NULL;
	return true;
}


bool CUpGradeGameLogic::CStack::bIsEmpty()
{
	return m_list.IsEmpty();
}



bool CUpGradeGameLogic::CStack::bIsInQ(int iIn, int jIn)
{	

	for (POSITION pos = m_list.GetHeadPosition();pos;)
	{
		tagPointNode *p = (tagPointNode *) m_list.GetNext(pos);
		if (!p) return false;
		if (p->i == iIn && p->j == jIn) 
			return true;
	}

	
	/*do
	//for (int pos = m_list.GetHeadPosition();;)//pos >= 0;)
	{	 pos = m_list.GetHeadPosition();
		tagPointNode *p = m_list.GetNext(&pos);
		//CString s;
		//s.Format("%d,%d,%d",p->i,p->j,pos);
		//AfxMessageBox(s);
		if (!p) return false;
		if (p->i == iIn && p->j == jIn) return true;
	}while(pos >= 0);*/

	return false;
}


void CUpGradeGameLogic::CStack::Push(int iIn, int jIn)
{
	tagPointNode *p = new tagPointNode();
	p->i = iIn;
	p->j = jIn;

	m_list.AddHead(p);
	
	//delete p;
	///p = NULL;
	return;
}


CUpGradeGameLogic::CStack::~CStack()
{
	while (!bIsEmpty())
	{
		tagPointNode *p = (tagPointNode *) m_list.RemoveHead();
		delete p;
		p = NULL;
	}
	m_list.RemoveAll();
}