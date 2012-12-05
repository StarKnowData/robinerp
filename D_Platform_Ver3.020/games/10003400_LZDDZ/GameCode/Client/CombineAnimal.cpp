#include "StdAfx.h"
#include "CombineAnimal.h"

extern void MyMsgBox(const char *lpszFormat, ...);

CCombineAnimal::CCombineAnimal(void)
{
	Init();
}

CCombineAnimal::~CCombineAnimal(void)
{
	Init();
}

void CCombineAnimal::Init()
{
	for (int i = 0; i < 3; i++)
	{
		m_childAnimal[i].Create(NULL, 0);
		m_CardAnimal.Create(NULL, NULL);
		m_nElapse[i] = 0;
		m_nBeginTime[i] = 0;
		m_nEndTime[i] = 0;
	}
	m_nTime = 0;
	m_nNowTime = 0;
	m_nChildOnUse = 0;

	m_nCardBeginTime = 0;
	m_nCardEndTime = 0;
}

LRESULT CCombineAnimal::Create(IN AnimalStruct * pAniStruct, IN int count)
{
	if (pAniStruct == NULL || count > 3 || count < 0)
	{
		Init();
		return ER_ERROR;
	}

	Init();
	for (int i = 0; i < count; i++)
	{
		m_childAnimal[i].Create(pAniStruct[i].pImage, pAniStruct[i].nFrame);
	}	
	m_nChildOnUse = count;
	return ER_OK;
}

LRESULT CCombineAnimal::Begin(IN AnimalShowAttriStruct * pAniShowAttri, IN int *nBegin, IN int *nEnd, IN int count)
{
	if (pAniShowAttri == NULL || nBegin == NULL || nEnd == NULL || count > m_nChildOnUse || count < 0)
	{
		return ER_ERROR;
	}
	for (int i = 0; i < count; i++)
	{
		m_childAnimal[i].Begin(pAniShowAttri[i].nTime, pAniShowAttri[i].nElapse, pAniShowAttri[i].xPos, pAniShowAttri[i].yPos);
		m_nElapse[i] = pAniShowAttri[i].nElapse;
		m_nBeginTime[i] = nBegin[i];
		m_nEndTime[i] = nEnd[i];
		if (nEnd[i] > m_nTime)
		{
			m_nTime = nEnd[i];
		}
	}	
	return m_nTime;
}

void CCombineAnimal::End()
{
	for (int i = 0; i < 3; i++)
	{
		m_childAnimal[i].End();
		m_nEndTime[i] = 0;
		m_nBeginTime[i] = 0;
		m_nElapse[i] = 0;
	}
	m_nTime = 0;
	m_nNowTime = 0;

	m_CardAnimal.End();
	m_nCardBeginTime = 0;
	m_nCardEndTime = 0;
}

LRESULT CCombineAnimal::DrawAnimal(IN CDC *pDC, IN int xPos, IN int yPos)
{
	if (pDC == NULL || !CanShow())
	{
		return ER_ERROR;
	}
	for (int i = 0; i < m_nChildOnUse; i++)
	{
		if (i == m_nCardZpos)
		{	
			if (m_nNowTime >= m_nCardBeginTime && m_nNowTime < m_nCardEndTime)
			{
				m_CardAnimal.DrawAnimal(pDC, xPos, yPos);
			}
		}
		if (m_nNowTime >= m_nBeginTime[i] && m_nNowTime < m_nEndTime[i])
		{
			m_childAnimal[i].DrawAnimal(pDC, xPos, yPos);
		}
	}
	return ER_OK;
}

LRESULT CCombineAnimal::OnTimer()
{
	if (!IsValid())
	{
		return ER_ERROR;
	}
	m_nNowTime += 100;
	if (m_nNowTime >= m_nTime)
	{
		End();
		return ER_END;
	}
	int state = ER_OK;
	//∆’Õ®∂Øª≠
	for (int i = 0; i < m_nChildOnUse; i++)
	{
		if (m_nBeginTime[i] <= m_nNowTime && m_nEndTime[i] > m_nNowTime )
		{
			int n = m_nNowTime - m_nBeginTime[i];
			if (n % m_nElapse[i] == 0)
			{
				m_childAnimal[i].OnTimer();
				state = ER_UPDATE;
			}
			
		}
		else if (m_nEndTime[i] == m_nNowTime)
		{
			m_childAnimal[i].End();
			state = ER_UPDATE;
		}
	}
	//≈∆∂Øª≠
	if ( m_nCardBeginTime <= m_nNowTime && m_nCardEndTime > m_nNowTime )
	{
		m_CardAnimal.OnTimer();
	}
	else if (m_nCardEndTime == m_nNowTime)
	{
		m_CardAnimal.End();
		state = ER_UPDATE;
	}
	return state+m_nNowTime*100+m_nBeginTime[0]+m_nEndTime[0]*10;
}

bool CCombineAnimal::IsValid()
{
	if (m_nChildOnUse <= 0)
	{
		return false;
	}
	if (!m_CardAnimal.IsValid())
	{
		return false;
	}
	for (int i = 0; i < m_nChildOnUse; i++)
	{
		if (!m_childAnimal[i].IsValid())
		{
			return false;
		}
	}
	return true;
}

bool CCombineAnimal::CanShow()
{
	if (m_nChildOnUse <= 0)
	{
		return false;
	}
	return true;
}

bool CCombineAnimal::IsOnShow()
{
	if (m_nTime > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

LRESULT CCombineAnimal::BeginCard(IN int beginCardTime, IN int endCardTime, IN CPoint ptBegin, IN CPoint ptEnd, IN int zPos, BYTE card[], int count)
{
	m_nCardBeginTime = beginCardTime;
	m_nCardEndTime = endCardTime;
	m_nCardZpos = zPos;
	m_CardAnimal.Begin(endCardTime-beginCardTime, 100, ptBegin, ptEnd, card, count);
	return ER_OK;
}