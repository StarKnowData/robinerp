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

/**
 * 构造函数
 */
CGameNoteWnd::CGameNoteWnd(void)
{
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT(".\\image\\waiting.bmp"));
	m_BackBmp.SetLoadInfo(path,true);
	m_Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	AfxSetResourceHandle(GetModuleHandle(NULL));
}

/**
 * 析构函数
 */
CGameNoteWnd::~CGameNoteWnd(void)
{
}

/**
 * 重画函数
 */
void CGameNoteWnd::OnPaint() 
{
	CPaintDC dc(this); 

	//绘画背景
	CDC BackDC;
	//BITMAP BmpInfo;
	//m_BackBmp.GetBitmap(&BmpInfo);
	BackDC.CreateCompatibleDC(&dc);
	BackDC.SelectObject(m_BackBmp);
	dc.BitBlt(0,0,m_BackBmp.GetWidth(),m_BackBmp.GetHeight(),&BackDC,0,0,SRCCOPY);

	//绘画字体
	RECT ClientRect;
	GetClientRect(&ClientRect);
	dc.SelectObject(m_Font);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));
	//dc.DrawText(m_strMessage,&ClientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

/**
 * 自动调整大小
 */
void CGameNoteWnd::AutoSize()
{
//	BITMAP BmpInfo;
	//m_BackBmp.GetBitmap(&BmpInfo);
	MoveWindow(0,0,m_BackBmp.GetWidth(),m_BackBmp.GetHeight());
}

/**
 * 设置信息
 */
void CGameNoteWnd::SetMessage(TCHAR * szMessage)
{
	m_strMessage.Empty();
	if (szMessage!=NULL)
	{
		m_strMessage=szMessage;
		Invalidate();
		UpdateWindow();
		ShowWindow(SW_SHOW);
	}
	else ShowWindow(SW_HIDE);
	return;
}
