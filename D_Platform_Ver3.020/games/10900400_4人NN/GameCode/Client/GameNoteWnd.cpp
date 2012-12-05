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
	TCHAR szTempStr[255] = {0};
	

	TCHAR path[MAX_PATH];
	wsprintf(path, TEXT(".\\image\\waiting.bmp"));
	m_bk.SetLoadInfo(path, true);


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
	//this->MapWindowPoints(this->GetParent(),&ClientRect);
	//CGameImageHelper	help(&m_bk);
	//this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	//help.BitBlt(dc.GetSafeHdc(),0,0);

	CDC BufferDc;
	CGameImageHelper	help(&m_bk);
	BufferDc.CreateCompatibleDC(&dc);
	BufferDc.SelectObject(help);
	::TransparentBlt(dc.GetSafeHdc(),0,0,help.GetWidth(),help.GetHeight(),BufferDc.GetSafeHdc(),\
		0,0,help.GetWidth(),help.GetHeight(),RGB(255,0,255));
	ReleaseDC(&BufferDc);
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
	CenterWindow(GetParent());
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
