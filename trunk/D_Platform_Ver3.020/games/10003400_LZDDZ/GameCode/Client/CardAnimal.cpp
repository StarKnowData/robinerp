#include "StdAfx.h"
#include "CardAnimal.h"

extern void MyMsgBox(const char *lpszFormat, ...);

CCardAnimal::CCardAnimal(void)
{
	Init();
}

CCardAnimal::~CCardAnimal(void)
{
	Init();
}

void CCardAnimal::Init()
{
	::memset(&m_ptBegin, 0, sizeof(m_ptBegin));
	::memset(&m_ptEnd, 0, sizeof(m_ptEnd));
	::memset(m_nCard, 0, sizeof(m_nCard));
	m_nCardCount = 0;
	m_nTime = 0;
	m_nNowTime = 0;
	m_nElapse = 0;
	m_pImgNormalCard = NULL;
	m_pImgBackCard = NULL;
}

LRESULT CCardAnimal::Create(IN CGameImage * pNormalCard, IN CGameImage * pBackCard)
{
	if (pNormalCard == NULL || pBackCard == NULL)
	{
		Init();
		return ER_ERROR;
	}
	Init();
	m_pImgNormalCard = pNormalCard;
	m_pImgBackCard = pBackCard;
	return ER_OK;
}

LRESULT CCardAnimal::Begin(IN int nTime, IN int nElapse, IN CPoint ptBegin, IN CPoint ptEnd, IN BYTE card[], IN int count)//少入口控制,自己注意
{
	m_nTime = nTime;
	m_nNowTime = 0;
	m_nElapse = nElapse;
	::memcpy(&m_ptBegin, &ptBegin, sizeof(m_ptBegin));
	::memcpy(&m_ptEnd, &ptEnd, sizeof(m_ptEnd));
	m_nCardCount = count;
	for (int i = 0; i < count; i++)
	{
		m_nCard[i] = card[i];
	}
	return ER_OK;
}

void CCardAnimal::End()
{
	::memset(&m_ptBegin, 0, sizeof(m_ptBegin));
	::memset(&m_ptEnd, 0, sizeof(m_ptEnd));
	::memset(m_nCard, 0, sizeof(m_nCard));
	m_nCardCount = 0;
	m_nTime = 0;
	m_nNowTime = 0;
	m_nElapse = 0;
}

LRESULT CCardAnimal::DrawAnimal(IN CDC *pDC, IN int xPos, IN int yPos)
{
	if (pDC == NULL || !CanShow())
	{
		return ER_ERROR;
	}

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CGameImageHelper imgNormal(m_pImgNormalCard);
	CGameImageHelper imgBack(m_pImgBackCard);

	CPoint ptNow;
	CPoint ptReal;
	ptNow.x = m_ptBegin.x + (m_ptEnd.x-m_ptBegin.x)*m_nNowTime/m_nTime+xPos;
	ptNow.y = m_ptBegin.y + (m_ptEnd.y-m_ptBegin.y)*m_nNowTime/m_nTime+yPos;
	ptReal.x = ptNow.x - (CARD_WIDTH + (m_nCardCount-1)*CARD_SPACE)/2;
	ptReal.y = ptNow.y - CARD_HEIGHT/2;

	for (int i = 0; i < m_nCardCount; i++)
	{
		int iXPos = 0;
		int iYPos = 0;
		if (m_nCard[i] == 0x4E || m_nCard[i] == 0x4F) //大小王
		{
			iXPos = (m_nCard[i]-0x4D)*CARD_WIDTH;
			iYPos = 0;
			dc.SelectObject(imgBack);
		}
		else
		{
			iXPos = GetCardXPos(m_nCard[i])*CARD_WIDTH;
			iYPos = GetCardYPos(m_nCard[i])*CARD_HEIGHT;
			dc.SelectObject(imgNormal);
		}
		TransparentBlt(pDC->GetSafeHdc(), ptReal.x+i*CARD_SPACE, ptReal.y,
			CARD_WIDTH, CARD_HEIGHT, 
			dc.GetSafeHdc(), 
			iXPos, iYPos,
			CARD_WIDTH, CARD_HEIGHT, RGB(255,0,255));
	}
	dc.DeleteDC();
	return	ER_OK;
}

LRESULT CCardAnimal::OnTimer()
{
	if (m_nTime <= 0 || m_nElapse <= 0)
	{
		End();
		return ER_ERROR;
	}
	m_nNowTime += m_nElapse;
	if ( m_nNowTime >= m_nTime)
	{
		End();
		return ER_END;
	}
	return ER_OK;
}

bool CCardAnimal::IsValid()
{
	if (m_pImgNormalCard != NULL && m_pImgBackCard != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCardAnimal::IsOnShow()
{
	if (m_nTime != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCardAnimal::CanShow()
{
	if (m_nElapse <= 0 || m_nTime <= 0 || m_nNowTime < 0 || 
		m_nNowTime > m_nTime || m_pImgBackCard == NULL || m_pImgNormalCard == NULL)
	{
		return false;
	}
	return true;
}