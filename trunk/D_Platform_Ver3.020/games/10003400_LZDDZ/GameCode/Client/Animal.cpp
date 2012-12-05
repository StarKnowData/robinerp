#include "StdAfx.h"
#include "Animal.h"

extern void MyMsgBox(const char *lpszFormat, ...);

CAnimal::CAnimal(void)
{
	Init();
}

CAnimal::~CAnimal(void)
{
	Init();
}

void CAnimal::Init()
{
	m_ptBasepoint.x = 0;
	m_ptBasepoint.y = 0;
	m_nFrame = 0;
	m_nNowFrame = 0;
	m_nTime = 0;
	m_nLeftTime = 0;
	m_nElapse = 0;
	m_pImage = NULL;
}

LRESULT	CAnimal::Create(IN CGameImage *pImage, IN int nFrame)
{
	if (pImage == NULL || nFrame <= 0)
	{
		Init();
		return ER_ERROR;
	}

	Init();
	m_pImage = pImage;
	m_nFrame = nFrame;
	return ER_OK;
}

LRESULT CAnimal::Begin(IN int nTime, IN int nElapse, IN int xPos, IN int yPos)
{
	m_nNowFrame = 0;
	m_nTime = nTime;
	m_nElapse = nElapse;
	m_nLeftTime = nTime;
	m_ptBasepoint.x = xPos;
	m_ptBasepoint.y = yPos;
	return ER_OK;
}

void CAnimal::End()
{
	m_ptBasepoint.x = 0;
	m_ptBasepoint.y = 0;
	m_nNowFrame = 0;
	m_nTime = 0;
	m_nLeftTime = 0;
	m_nElapse = 0;
}

LRESULT CAnimal::DrawAnimal(IN CDC *pDC, IN int iMidx, IN int iMidy)
{
	if (!CanShow() || pDC == NULL)
	{
		return ER_ERROR;
	}

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CGameImageHelper img(m_pImage);

	int nOneWidth  = img.GetWidth() / m_nFrame;		//Ã¿Ö¡¿í
	int nOneHeight = img.GetHeight();				//Ã¿Ö¡¸ß

	dc.SelectObject(img);
	TransparentBlt(pDC->GetSafeHdc(), iMidx-nOneWidth/2+m_ptBasepoint.x, iMidy-nOneHeight/2+m_ptBasepoint.y,
				nOneWidth, nOneHeight, 
				dc.GetSafeHdc(), 
				nOneWidth*m_nNowFrame,  0,
				nOneWidth, nOneHeight, RGB(255,0,255));
	dc.DeleteDC();
	return	ER_OK;
}

LRESULT CAnimal::OnTimer()
{
	if (m_nTime <= 0 || m_nFrame <= 0 || m_nElapse <= 0)
	{
		End();
		return ER_ERROR;
	}

	m_nLeftTime -= m_nElapse;
	m_nNowFrame++;
	m_nNowFrame = m_nNowFrame%m_nFrame;
	if ( m_nLeftTime < m_nElapse)
	{
		End();
		return ER_END;
	}
	return ER_OK;
}

bool CAnimal::IsValid()
{
	if (m_nFrame != 0 && m_pImage != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CAnimal::IsOnShow()
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

bool CAnimal::CanShow()
{
	if (m_nFrame < 0 || m_nNowFrame < 0 || m_nElapse <= 0 ||
		m_nNowFrame > m_nFrame-1 || m_nTime <= 0 || m_nLeftTime <= 0 || m_pImage == NULL)
	{
		return false;
	}
	return true;
}
