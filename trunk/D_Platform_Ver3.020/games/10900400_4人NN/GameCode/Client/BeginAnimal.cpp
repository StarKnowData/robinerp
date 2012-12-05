// BeginAnimal.cpp : 实现文件
//

#include "stdafx.h"
#include "BeginAnimal.h"


// CBeginAnimal 对话框

IMPLEMENT_DYNAMIC(CBeginAnimal, CDialog)

CBeginAnimal::CBeginAnimal(CWnd* pParent /*=NULL*/)
	: CDialog(CBeginAnimal::IDD, pParent)
{
	TCHAR path[200];
	wsprintf(path,TEXT(".\\image\\begin.bmp"));
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

}

CBeginAnimal::~CBeginAnimal()
{
}

void CBeginAnimal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BOOL CBeginAnimal::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CGameImageHelper ImageHandle(&m_bk);
	HRGN hRgn=AFCBmpToRgn(ImageHandle,RGB(255,255,255),RGB(1,0,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
		return true;
	}
	
	MoveWindow(0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight());
	//AfxSetResourceHandle(GetModuleHandle(NULL));
	
	return TRUE;
}
void CBeginAnimal::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper ImageHandle(&m_bk);
	ImageHandle.BitBlt(dc.GetSafeHdc(),0,0);
		return;
}
void CBeginAnimal::FixCardControl(int x,int y)
{
	MoveWindow(x,y,m_bk.GetWidth(),m_bk.GetHeight());
}
BEGIN_MESSAGE_MAP(CBeginAnimal, CDialog)
	ON_WM_PAINT()	
END_MESSAGE_MAP()


// CBeginAnimal 消息处理程序
