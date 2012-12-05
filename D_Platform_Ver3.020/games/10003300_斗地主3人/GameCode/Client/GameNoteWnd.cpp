#include "StdAfx.h"
#include "GameNoteWnd.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CGameNoteWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//构造函数
CGameNoteWnd::CGameNoteWnd(void)
{
	AfxSetResourceHandle(GetModuleHandle(GET_CLIENT_DLL_NAME(szTempStr)));

	TCHAR path[MAX_PATH];
	wsprintf(path, TEXT(".\\image\\waiting.bmp"));
	m_bk.SetLoadInfo(path, true);

	AfxSetResourceHandle(GetModuleHandle(NULL));
}

//析构函数
CGameNoteWnd::~CGameNoteWnd(void)
{
}

//重画函数
void CGameNoteWnd::OnPaint() 
{
	CPaintDC dc(this); 
	CRect ClientRect;
	GetClientRect(&ClientRect);
	this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	help.BitBlt(dc.GetSafeHdc(),0,0);
/*
	//绘画背景
	CDC BackDC;
	BITMAP BmpInfo;
	m_BackBmp.GetBitmap(&BmpInfo);
	BackDC.CreateCompatibleDC(&dc);
	BackDC.SelectObject(&m_BackBmp);
	dc.BitBlt(0,0,BmpInfo.bmWidth,BmpInfo.bmHeight,&BackDC,0,0,SRCCOPY);

	//绘画字体
	RECT ClientRect;
	GetClientRect(&ClientRect);
	dc.SelectObject(m_Font);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));
	dc.DrawText(m_strMessage,&ClientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	*/
}

//自动调整大小
void CGameNoteWnd::AutoSize()
{
//	BITMAP BmpInfo;
//	m_BackBmp.GetBitmap(&BmpInfo);
//	MoveWindow(0,0,BmpInfo.bmWidth,BmpInfo.bmHeight);
	MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight());

}

//设置信息
void CGameNoteWnd::SetMessage(TCHAR * szMessage)
{
//	m_strMessage.Empty();
	if (szMessage!=NULL)
	{
//		m_strMessage=szMessage;
		Invalidate();
		UpdateWindow();
		ShowWindow(SW_SHOW);
	}
	else if (this->GetSafeHwnd() != NULL)
	{
		ShowWindow(SW_HIDE);
	}
		
	return;
}

// ----------------------------------------------------------------------------
// PengJiLin, 2011-4-19, 在线时长、局数送金币图像提示
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CGetMoneyWnd, CWnd)
    ON_WM_PAINT()
END_MESSAGE_MAP()


CGetMoneyWnd::CGetMoneyWnd(void)
{
	AfxSetResourceHandle(GetModuleHandle(GET_CLIENT_DLL_NAME(szTempStr)));

    m_strGetInfo = "";
    m_strTimeInfo = "";
    m_strCountInfo = "";

    m_iStartX = 0;
    m_iStartY = 0;
    m_iStartSpace = 0;
    m_iFlagX = 0;
    m_iFlagY = 0;
    m_cColor = RGB(0,0,0);

	TCHAR path[MAX_PATH];
	wsprintf(path, TEXT(".\\image\\getmoney.bmp"));
	m_bk.SetLoadInfo(path, true);

    wsprintf(path, TEXT(".\\image\\gongxi.bmp"));
    m_Flag.SetLoadInfo(path, true);

	AfxSetResourceHandle(GetModuleHandle(NULL));
}

CGetMoneyWnd::~CGetMoneyWnd(void)
{
}

void CGetMoneyWnd::OnPaint() 
{
	CPaintDC dc(this); 
	CRect ClientRect;
	GetClientRect(&ClientRect);

	CGameImageHelper	help(&m_bk);

    CDC srcDC;
    srcDC.CreateCompatibleDC(&dc);
    CBitmap *pOldBmp = srcDC.SelectObject(help);
    ::TransparentBlt(dc.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),
                    srcDC.GetSafeHdc(),0,0,m_bk.GetWidth(),m_bk.GetHeight(),srcDC.GetPixel(0,0));
    srcDC.SelectObject(pOldBmp);

    CRect rect;
    TCHAR sz[100];
    CFont Font;
    Font.CreateFont(14,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
    CFont *OldFont=dc.SelectObject(&Font);
    dc.SetTextColor(RGB(255,255,255));
    dc.SetBkMode(TRANSPARENT);

    int iIndex = 0;
    if(m_strGetInfo.GetLength() > 0)
    {
        CGameImageHelper flag(&m_Flag);
        srcDC.CreateCompatibleDC(&dc);
        pOldBmp = srcDC.SelectObject(flag);

        ::TransparentBlt(dc.GetSafeHdc(), m_iFlagX+5, m_iFlagY, flag.GetWidth(), flag.GetHeight(),
                   srcDC.GetSafeHdc(),0,0,m_Flag.GetWidth(),m_Flag.GetHeight(),srcDC.GetPixel(0,0));
        srcDC.SelectObject(pOldBmp);
        srcDC.DeleteDC();

        dc.SetTextColor(m_cColor);
        rect.left = m_iStartX + m_Flag.GetWidth() + 10;
        rect.right = rect.left + m_bk.GetWidth();
        rect.top = m_iStartY + m_iStartSpace * iIndex;
        rect.bottom = rect.top + 35;
        dc.DrawText(m_strGetInfo,m_strGetInfo.GetLength(),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
    }
    
    iIndex++;
    dc.SetTextColor(RGB(0,0,0));
    if(m_strTimeInfo.GetLength() > 0)
    {
        rect.left = m_iStartX;
        rect.right = rect.left + m_bk.GetWidth();
        rect.top = m_iStartY + m_iStartSpace * iIndex++;
        rect.bottom = rect.top + 35;
        dc.DrawText(m_strTimeInfo,m_strTimeInfo.GetLength(),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
    }

    if(m_strCountInfo.GetLength() > 0)
    {
        rect.left = m_iStartX;
        rect.right = rect.left + m_bk.GetWidth();
        rect.top = m_iStartY + m_iStartSpace * iIndex++;
        rect.bottom = rect.top + 35;
        dc.DrawText(m_strCountInfo,m_strCountInfo.GetLength(),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
    }

    __super::OnPaint();
}

void CGetMoneyWnd::AutoSize()
{
	MoveWindow(0,0,m_bk.GetWidth(),m_bk.GetHeight());
}

void CGetMoneyWnd::SetShow(BOOL bShow)
{
	if(TRUE == bShow)
	{
		Invalidate();
		UpdateWindow();
		ShowWindow(SW_SHOW);
	}
	else if (this->GetSafeHwnd() != NULL)
	{
		ShowWindow(SW_HIDE);
	}

	return;
}

void CGetMoneyWnd::SetMessage(CString& strGet, CString& strTime, CString& strCount, bool bInVideoRoom)
{
    m_strGetInfo = strGet;
    m_strTimeInfo = strTime;
    m_strCountInfo = strCount;

    CBcfFile f(GET_CLIENT_BCF_NAME(szTempStr));

    CString key = TEXT("UISet");
    if(bInVideoRoom) key="VideoUISet";

    m_iStartX = f.GetKeyVal(key,TEXT("GetMoneyX"), 25);
    m_iStartY = f.GetKeyVal(key,TEXT("GetMoneyY"), 25);
    m_iStartSpace = f.GetKeyVal(key,TEXT("GetMoneyLineSpace"), 35);
    //m_cColor = f.GetKeyVal(key,TEXT("GetMoneyColor"), RGB(0,0,0));

    m_iFlagX = f.GetKeyVal(key,TEXT("GetMoneyFlagX"), 25);
    m_iFlagY = f.GetKeyVal(key,TEXT("GetMoneyFlagY"), 30);
}