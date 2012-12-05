#include "StdAfx.h"
#include "GameFinishDlg.h"
#include "Resource.h"
#include "ClientGameDlg.h"
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
CGameFinishDlg::CGameFinishDlg(void) //:CGameFaceGo(CGameFinishDlg::IDD)
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	m_pParnet=NULL;
	//AfxSetResourceHandle(GetModuleHandle(NULL));
	m_iCx=0;
	m_iCy=0;
	m_nPowerOfGold=0;
}

//析构函数
CGameFinishDlg::~CGameFinishDlg(void)
{
}

//重画函数
void CGameFinishDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC srcdc;
	CGameImageHelper help(&m_bk);
	help.BitBlt(dc.GetSafeHdc(),0,0);
	
	CGameImageHelper	win(&m_win);
	CGameImageHelper	lost(&m_lost);
	CGameImageHelper	equal(&m_equal);
	srcdc.CreateCompatibleDC(&dc);
	srcdc.SelectObject(help);

	CFont Font;
	CRect rect;
	TCHAR szMsg[50]="";
	Font.CreateFont(14,0,0,0,600,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));

	CFont *OldFont=dc.SelectObject(&Font);
	CString str;
	dc.SetTextColor(RGB(0,255,30));
	int x = 15;
	int y = 107;
	int YAdd = 34;
	int winX=240;
	int winY=97;

	dc.SetBkMode(TRANSPARENT);
	
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(m_iFinish.iCardShape[i] == 100)
			continue;
		if(m_iViewStation == i)
		{
			dc.SetTextColor(RGB(255,0,0));
		}
		else
		{
			dc.SetTextColor(RGB(0,0,0));
		}

		wsprintf(szMsg,"%s",m_iFinish.name[i]);//名字
		rect.left=x+7;
		rect.right=rect.left+90;
		rect.top=y+YAdd*i-5;
		rect.bottom=rect.top+18;
		dc.DrawText(szMsg,lstrlen(szMsg),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		wsprintf(szMsg,m_ShapeName[m_iFinish.iCardShape[i]]);
		rect.left=122;
		rect.right=rect.left+80;
		rect.top=y+YAdd*i-5;
		rect.bottom=rect.top+18;
		dc.DrawText(szMsg,lstrlen(szMsg),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		
		wsprintf(szMsg,"%I64d",m_iFinish.iWardPoint[i]);//得分
		rect.left=282;
		rect.right=rect.left+110 + 40;
		rect.top=y+YAdd*i-5;
		rect.bottom=rect.top+18;   
		dc.DrawText(szMsg,lstrlen(szMsg),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		if (m_iFinish.iWardPoint[i] > 0||m_iFinish.iMoney[i]>0)
		{
			srcdc.SelectObject(win);
			::TransparentBlt(dc.GetSafeHdc(),winX,winY+i*34,48,26,srcdc,0,0,win.GetWidth(),win.GetHeight(),srcdc.GetPixel(0,0));
		}
		else if(m_iFinish.iWardPoint[i] ==0&&m_iFinish.iMoney[i] ==0 )
		{
			srcdc.SelectObject(equal);
			::TransparentBlt(dc.GetSafeHdc(),winX,winY+i*34,48,26,srcdc,0,0,equal.GetWidth(),equal.GetHeight(),srcdc.GetPixel(0,0));
		}
		else
		{
			srcdc.SelectObject(lost);
			::TransparentBlt(dc.GetSafeHdc(),winX,winY+i*34,48,26,srcdc,0,0,lost.GetWidth(),lost.GetHeight(),srcdc.GetPixel(0,0));
			
		}

		CString strMoney;
		GetNumString(m_iFinish.iMoney[i],strMoney,m_nPowerOfGold);
		wsprintf(szMsg,"%s",strMoney);//银子
		rect.left=380;
		rect.right=rect.left+110 + 40;
		rect.top=y+YAdd*i-5;
		rect.bottom=rect.top+18;
		dc.DrawText(szMsg,lstrlen(szMsg),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}

	srcdc.DeleteDC();
	dc.SelectObject(OldFont);
}

void CGameFinishDlg::SetMessage(GameFinishNotify finishnotify,BYTE iViewStation, int nPowerOfGold)
{
	m_iFinish=finishnotify;
	m_iViewStation=iViewStation;
	m_nPowerOfGold = nPowerOfGold;
	return;
}

void CGameFinishDlg::OnLButtonDown(UINT nFags,CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	return ;
}

int CGameFinishDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	TCHAR szName[MAX_PATH];
	wsprintf(szName,".\\image\\result.bmp");
	m_bk.SetLoadInfo(szName,false);


	wsprintf(szName,".\\image\\win.bmp");
	m_win.SetLoadInfo(szName,false);

	wsprintf(szName,".\\image\\lost.bmp");
	m_lost.SetLoadInfo(szName,false);

	wsprintf(szName,".\\image\\equal.bmp");
	m_equal.SetLoadInfo(szName,false);


	m_ShapeName[0] = TEXT("牛破");
	m_ShapeName[1] = TEXT("牛一");
	m_ShapeName[2] = TEXT("牛二");
	m_ShapeName[3] = TEXT("牛三");
	m_ShapeName[4] = TEXT("牛四");
	m_ShapeName[5] = TEXT("牛五");
	m_ShapeName[6] = TEXT("牛六");
	m_ShapeName[7] = TEXT("牛七");
	m_ShapeName[8] = TEXT("牛八");
	m_ShapeName[9] = TEXT("牛九");
	m_ShapeName[10] = TEXT("牛牛");
	m_ShapeName[11] = TEXT("银牛");
	m_ShapeName[12] = TEXT("金牛");
	m_ShapeName[13] = TEXT("五小");
	m_ShapeName[14] = TEXT("炸弹");

	// TODO:  在此添加您专用的创建代码
	CGameImageHelper help(&m_bk);
	HRGN hRgn=AFCBmpToRgn(help,RGB(255,0,255),RGB(1,1,1));     //过滤掉RGB(255,0,255)的颜色区域
	if (hRgn!=NULL)
	{
		SetWindowRgn(hRgn,TRUE);        //设置为没有过滤掉的区域
	}
	CRect rect;
	GetClientRect(&rect);
	this->MoveWindow(0,0,help.GetWidth(),help.GetHeight());

	return 0;
}
///
///依当前金币倍率得到字符串
///@param [int] int nNum 要显示的数字
///@param [out] CString &Str 返回的字符串
///@param [int] int nPower 金币倍率
///@return void
///
void CGameFinishDlg::GetNumString(__int64 nNum, CString &Str, int nPower)
{
	if (0 == nNum)
	{
		Str.Format("0");
		return;
	}
	/// 暂存结果
	TCHAR strTmp[64];
    TCHAR str[50];
	/// 目前只处理大于0的情况，在正常字符串后面要加至少一个0
	wsprintf( strTmp, TEXT("%I64d"), nNum);
	for (int i=0; i<nPower; ++i)
	{
		_tcscat( strTmp, TEXT("0"));
	}
	/// 按位数每三位空一格显示
	int nLen = _tcslen(strTmp);	// 字符串长度
	int nTimes = nLen % 3;	// 这个字符串可以分成的节数，至少是1节
	
	int nSrc = 0;
	int nDes = 0;

	for (int i=0; i<nLen; ++i)
	{
		//if ((i>0)&&(i%3==nTimes))
		//{
			//str[nDes++] = TEXT(' ');///牛牛不加空格
		//}
		str[nDes++] = strTmp[nSrc++];
	}
	str[nDes] = TEXT('\0');
	Str.Format("%s",str);
	return ;
}
