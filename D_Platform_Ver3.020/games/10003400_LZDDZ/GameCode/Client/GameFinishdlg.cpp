#include "StdAfx.h"
#include "GameFinishDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CGameFinishDlg, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()

//构造函数
CGameFinishDlg::CGameFinishDlg(void)// :CGameFaceGo(CGameFinishDlg::IDD)
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));


	//AfxSetResourceHandle(GetModuleHandle(NULL));
}
//
int CGameFinishDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	TCHAR szName[MAX_PATH];
	wsprintf(szName,TEXT(".\\image\\%s\\result.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_bk.SetLoadInfo(szName,TRUE);
	
	/*wsprintf(szName,".\\image\\%s\\win.bmp",GET_SKIN_FOLDER(szTempStr));
	m_Flag.SetLoadInfo(szName,false);*/

	CRect ClientRect;
	GetClientRect(&ClientRect);
	//this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	HRGN hRgn=AFCBmpToRgn(help,RGB(255,0,255),RGB(1,0,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,help.GetWidth(),help.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
	}
	m_iPower = 0;

	return 0;
}
//析构函数
CGameFinishDlg::~CGameFinishDlg(void)
{
}

//重画函数
void CGameFinishDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CGameImageHelper	help(&m_bk);
	help.BitBlt(dc.GetSafeHdc(),0,0);

	GetClientRect(&ClientRect);
	int x=24;//ClientRect.left+20;
	int y=ClientRect.Height()/2 + 40;

	CRect rect;
	TCHAR sz[100];
	CFont Font;
	Font.CreateFont(14,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	CFont *OldFont=dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255,0,0));
	dc.SetBkMode(TRANSPARENT);

	wsprintf(sz,"%d%%",m_iFinish.iTax);
	rect.left=345;
	rect.right=365;
	rect.top=52+14;
	rect.bottom=rect.top+20;
	dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
    int TempW = 0;
	int TempH = 0;
	dc.SetTextColor(RGB(0,0,0));
	for (int i=0; i<PLAY_COUNT; i++)
	{
		for (int j=0; j<10; j++)
		{
			if (m_iFinish.iBombCard[i][j] > 0)
			{
				CString str;
				switch(m_iFinish.iBombCard[i][j])
				{
				case 11:
					str = "J";
					break;
				case 12:
					str = "Q";
					break;
				case 13:
					str = "K";
					break;
				case 14:
					str = "A";
					break;
				default:
					str.Format("%d",m_iFinish.iBombCard[i][j]);
					break;
				}
				
				switch(i)
				{
				case 0:
					wsprintf(sz,"春天:x2");
					break;
				case 1:
					wsprintf(sz,"火箭:x4");
					break;
				case 2:
					wsprintf(sz,"%s硬炸:x4",str);
					break;
				case 3:
					wsprintf(sz,"%s软炸:x2",str);
					break;
				}

				rect.left=30 + TempW*120;
				rect.right=rect.left + 90;
				rect.top=80 + TempH *40+14;
				rect.bottom=rect.top+20;
				dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
				TempW ++;
				if (TempW > 3)
				{
					TempW = 0;
					TempH ++;
				}
			}			
		}
	}

	wsprintf(sz,"%d",m_iFinish.iCallScore);
	rect.left=235;
	rect.right=265;
	rect.top=52+14;
	rect.bottom=rect.top+20;
	dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

	wsprintf(sz,"%d",m_iFinish.iBasePoint);
	rect.left=95;
	rect.right=120;
	rect.top=52+14;
	rect.bottom=rect.top+20;
	dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

	int StartX = 229;
	int StartY = 106;

	CString strMoney;
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		if(strlen(m_iFinish.name[i]) <= 0)
			continue;
		/*if(m_iViewStation==i)
			dc.SetTextColor(RGB(255,0,0));
		else
			dc.SetTextColor(RGB(0,0,0));*/
		if(m_iFinish.iWardPoint[i] > 0 || m_iFinish.iMoney[i] > 0)
		{
			dc.SetTextColor(RGB(255,0,0));
		}
		else
		{
			dc.SetTextColor(RGB(0,0,0));
		}

		wsprintf(sz, "%s", m_iFinish.name[i]);
		rect.left=x + 8;
		rect.right=rect.left+80;
		rect.top=y+25*i+14;
		rect.bottom=rect.top+33;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	
		wsprintf(sz, "%I64d", m_iFinish.iWardPoint[i]);
		rect.left=150;
		rect.right=rect.left+110;
		rect.top=y+25*i+14;
		rect.bottom=rect.top+33;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		SetIntToCharLjl(strMoney, m_iFinish.iMoney[i], m_iPower);
		wsprintf(sz, "%s", strMoney/*m_iFinish.iMoney[i]*/);
		rect.left=280;
		rect.right=rect.left+110;
		rect.top=y+25*i+14;
		rect.bottom=rect.top+33;
		dc.DrawText(sz,lstrlen(sz),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);		
	}
	return ;
}

//自动调整大小
void CGameFinishDlg::AutoSize(int xValue,int yValue)
{
	MoveWindow(xValue,yValue,m_bk.GetWidth(),m_bk.GetHeight());
	Invalidate();
	UpdateWindow();
}


void CGameFinishDlg::SetMessage(GameFinishNotify finishnotify,BYTE iViewStation)
{

	m_iFinish=finishnotify;
	m_iViewStation=iViewStation;
	Invalidate(TRUE);
	UpdateWindow();
	return;
}

void CGameFinishDlg::OnLButtonDown(UINT nFags,CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	return ;
}

void CGameFinishDlg::SetIntToCharLjl(CString  &str, __int64 iMoney, int iSet)
{
	CString strTmpe("0");
	str.Format("%I64d",iMoney);
	for ( int i=0; i<iSet; i++  )
	{
		str+= strTmpe;
	}
}

