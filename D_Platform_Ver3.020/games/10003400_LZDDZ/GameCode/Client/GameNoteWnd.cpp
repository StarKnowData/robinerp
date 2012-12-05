#include "StdAfx.h"
#include "GameNoteWnd.h"
#include "Resource.h"
#include "ClientGameDlg.h"
#define IDC_LOGO_IN 1005
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include <GdiPlus.h> 
using namespace Gdiplus; 
#pragma comment(lib,"gdiplus.lib") 


BEGIN_MESSAGE_MAP(CGameNoteWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

//构造函数
CGameNoteWnd::CGameNoteWnd(void)
{
	//AfxSetResourceHandle(GetModuleHandle(GET_CLIENT_DLL_NAME(szTempStr))));

	TCHAR szName[MAX_PATH];
	wsprintf(szName,TEXT(".\\image\\%s\\waiting.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_bk.SetLoadInfo(szName,true);

	m_iFlag=0;
//	m_Font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	//AfxSetResourceHandle(GetModuleHandle(NULL));
	m_dwUserID = 0;
}

//析构函数
CGameNoteWnd::~CGameNoteWnd(void)
{
}
//创建
int CGameNoteWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//m_btContinue.Create(TEXT(""),WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,56,26),this,IDC_CONTINUE_2);
	//m_btLogo.Create(TEXT(""),WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS,CRect(0,0,56,26),this,IDC_LOGO_IN);
	return CWnd::OnCreate(lpCreateStruct);
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
//	Graphics graphics(dc.GetSafeHdc()); // Create a GDI+ graphics object
//	WCHAR buf[MAX_PATH+MAX_PATH+4];
	//wsprintfW(buf, L"%s", m_szName);
//	wsprintfW(buf, L"image\\dbddz\\waiting%d.png",m_iFlag);

//	Image image(buf);

//	graphics.DrawImage(&image,REAL(0), REAL(0), image.GetWidth(), image.GetHeight());

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
void CGameNoteWnd::AutoSize(int xValue,int yValue)
{
//	BITMAP BmpInfo;
//	m_BackBmp.GetBitmap(&BmpInfo);
//	MoveWindow(0,0,BmpInfo.bmWidth,BmpInfo.bmHeight);
	MoveWindow(xValue,yValue,m_bk.GetWidth(),m_bk.GetHeight());
	
//	CRect rect;
//	m_btLogo.GetClientRect(&rect);
//	int width=rect.Width();
//	int height=rect.Height();
////	m_btContinue.MoveWindow(128,210,width,height);
//	m_btLogo.MoveWindow(190,44,width,height);

	Invalidate();
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
	else ShowWindow(SW_HIDE);
		return;
}
//设置当前状态
void CGameNoteWnd::SetGameStateFlag(int iStateFlag)
{
	m_iFlag= iStateFlag;
	TCHAR buf[MAX_PATH];

	wsprintf(buf, TEXT("image\\%s\\waiting.bmp"), GET_SKIN_FOLDER(szTempStr));
	m_bk.SetLoadInfo(buf,CGameImageLink::m_bAutoLock);
	CGameImageHelper ImageHandle(&m_bk);
	HRGN hRgn=AFCBmpToRgn(ImageHandle,RGB(255,0,255),RGB(1,1,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
	}
	
	//CGameImage			m_bk2;
	//if(m_iFlag == 4)
	//{
	//	TCHAR szName[MAX_PATH];
	//	wsprintf(szName,TEXT(".\\image\\%s\\login_bt.bmp"),GET_SKIN_FOLDER(szTempStr));	//开始按钮
	//	m_btLogo.LoadButtonBitmap(szName,false);	
	//	m_bk2.SetLoadInfo(szName,true);
	//	hRgn=AFCBmpToRgn(m_bk2,RGB(255,0,255),RGB(1,1,1));
	//	if(hRgn)
	//		m_btLogo.SetWindowRgn(hRgn,true);
	//}
	//if(m_iFlag == 4)
	//	m_btLogo.ShowWindow(SW_SHOW);
	//else
	//	m_btLogo.ShowWindow(SW_HIDE);

	AutoSize(0,0);
	Invalidate();
}

