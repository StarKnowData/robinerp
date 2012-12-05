#include "Stdafx.h"
#include "CeasyNtList.h"
#include "ClientGameDlg.h"
#include "Resource.h"

#define NUM_WIDTH	30//19				//押注数
#define NUM_HEIGHT	30//27				//押注数高
//按钮消息
/*void CNtList::OnNT()   
{	
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_NtList);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
//	pp->SendMessage(IDM_USER_NT,UG_NT_CARD,UG_NT_CARD); 
}*/

BEGIN_MESSAGE_MAP(CeasyNtList, CDialog)
	/*ON_BN_CLICKED(IDC_1, On1)
	ON_BN_CLICKED(IDC_2, On2)
	ON_BN_CLICKED(IDC_3, On3)*/
//	ON_BN_CLICKED(IDC_4, On4)
//	ON_BN_CLICKED(IDC_5, On5)
//	ON_BN_CLICKED(IDC_6, On6)
	ON_BN_CLICKED(IDC_MAX, OnMax)
	ON_BN_CLICKED(IDC_CANCEL, OnResetCancel)
    ON_BN_CLICKED(IDC_OK, OnResetOk)
	ON_WM_PAINT()	
	ON_WM_LBUTTONDOWN()
	//	ON_BN_CLICKED(IDC_NT, OnNT)
END_MESSAGE_MAP()

//构造函数
CeasyNtList::CeasyNtList(CWnd* pParent /*=NULL*/): CDialog(CeasyNtList::IDD, pParent)
{

	TCHAR path[200];
//	wsprintf(path,TEXT(".\\image\\normal_num.bmp"));
//	m_PicNum.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,TEXT(".\\image\\eNoteList.bmp"));
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,TEXT(".\\image\\jeton.bmp"));
	m_PicNum.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	
	m_BtnIndex0 = m_BtnIndex1 = m_BtnIndex2 = 0;
	m_iStart0 = m_iStart1 = m_iStart2 = 50;
	m_Num=0;
}
//DDX 支持
void CeasyNtList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_4, m_Bm4);*/
	/*DDX_Control(pDX, IDC_3, m_Bm3);
	DDX_Control(pDX, IDC_2, m_Bm2);
	DDX_Control(pDX, IDC_1, m_Bm1);*/
//	DDX_Control(pDX, IDC_5, m_Bm5);
	DDX_Control(pDX, IDC_OK, m_BmOk);
	DDX_Control(pDX, IDC_MAX, m_BmMax);
	DDX_Control(pDX, IDC_CANCEL, m_BmCancel);
}

//确定函数
void CeasyNtList::OnOK() 
{
	return;
}

//取消函数
void CeasyNtList::OnCancel() 
{
	return;
}

//初始化函数
BOOL CeasyNtList::OnInitDialog() 
{

	CDialog::OnInitDialog();
	CGameImageHelper ImageHandle(&m_bk);
	HRGN hRgn=AFCBmpToRgn(ImageHandle,RGB(255,0,255),RGB(1,0,1));

	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
	}
	//加载按钮
	int iWidth=40,iHide=40;
	CGameImage m_tempbk;
	HRGN hRgn2;
	TCHAR szName[MAX_PATH];

	int x=27;
	int y=43;
	int i=46;
	m_BtnRect0.left = x;
	m_BtnRect0.top = y;
	m_BtnRect0.right = m_BtnRect0.left + JETON_W;
	m_BtnRect0.bottom = m_BtnRect0.top + JETON_H;
	//wsprintf(szName,".\\image\\50_bt.bmp");	//开始按钮
	//m_Bm1.LoadButtonBitmap(szName,false);	
	//m_tempbk.SetLoadInfo(szName,true);
	//hRgn2=AFCBmpToRgn(m_tempbk,RGB(255,0,255),RGB(1,1,1));
	//if(hRgn2)
	//	m_Bm1.SetWindowRgn(hRgn2,true);
	//m_Bm1.MoveWindow(x,y,iWidth,iHide);
	x+=i;

	//wsprintf(szName,".\\image\\100_bt.bmp");	//开始按钮
	//m_Bm2.LoadButtonBitmap(szName,false);	
	//m_tempbk.SetLoadInfo(szName,true);
	//hRgn2=AFCBmpToRgn(m_tempbk,RGB(255,0,255),RGB(1,1,1));
	//if(hRgn2)
	//	m_Bm2.SetWindowRgn(hRgn2,true);
	//m_Bm2.MoveWindow(x,y,iWidth,iHide);
	m_BtnRect1.left = x;
	m_BtnRect1.top = y;
	m_BtnRect1.right = m_BtnRect1.left + JETON_W;
	m_BtnRect1.bottom = m_BtnRect1.top + JETON_H;
	x+=i;

	//wsprintf(szName,".\\image\\200_bt.bmp");	//开始按钮
	//m_Bm3.LoadButtonBitmap(szName,false);	
	//m_tempbk.SetLoadInfo(szName,true);
	//hRgn2=AFCBmpToRgn(m_tempbk,RGB(255,0,255),RGB(1,1,1));
	//if(hRgn2)
	//	m_Bm3.SetWindowRgn(hRgn2,true);
	//m_Bm3.MoveWindow(x,y,iWidth,iHide);
	m_BtnRect2.left = x;
	m_BtnRect2.top = y;
	m_BtnRect2.right = m_BtnRect2.left + JETON_W;
	m_BtnRect2.bottom = m_BtnRect2.top + JETON_H;
	x += i;
		
	wsprintf(szName,".\\image\\max_bt.bmp");	//开始按钮
	m_BmMax.LoadButtonBitmap(szName,false);	
	m_tempbk.SetLoadInfo(szName,true);
	hRgn2=AFCBmpToRgn(m_tempbk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn2)
		m_BmMax.SetWindowRgn(hRgn2,true);
	m_BmMax.MoveWindow(14,86,52,22);
	
	wsprintf(szName,".\\image\\cancel_bt.bmp");	//开始按钮
	m_BmCancel.LoadButtonBitmap(szName,false);	
	m_tempbk.SetLoadInfo(szName,true);
	hRgn2=AFCBmpToRgn(m_tempbk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn2)
		m_BmCancel.SetWindowRgn(hRgn2,true);
	m_BmCancel.MoveWindow(118,86,52,22);

	wsprintf(szName,".\\image\\ok_bt.bmp");	//确定按钮
	m_BmOk.LoadButtonBitmap(szName,false);	
	m_tempbk.SetLoadInfo(szName,true);
	hRgn2=AFCBmpToRgn(m_tempbk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn2)
		m_BmOk.SetWindowRgn(hRgn2,true);
	m_BmOk.MoveWindow(66,86,52,22);

	CRect ClientRect;
	GetClientRect(&ClientRect);

	this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());

	UpdateBtnList(1,1,1,1,1);		//更新下注按钮

	//AfxSetResourceHandle(GetModuleHandle(NULL));
	return TRUE;
}

//更新按钮可用状态
void CeasyNtList::UpdateBtnList(BOOL up1,BOOL up2,BOOL up3,BOOL max,BOOL cancel)
{
	m_BmMax.EnableWindow(max);
    m_BmOk.EnableWindow(true);
	m_BmCancel.EnableWindow(cancel);
	return ;
}
//设置起点筹码
void CeasyNtList::SetJetonStart(int iStart0,int iStart1,int iStart2,int iEnd)
{
	m_iStart0 = iStart0;
	m_iStart1 = (iStart1 == 0 ? iStart0*5 : iStart1);
	m_iStart2 = (iStart2 == 0 ? iStart0*10 : iStart2 );
	m_iEnd = (iEnd == 0) ? iStart0*5 : iEnd;
	
	//设置下注索引
	m_BtnIndex0 = GetIndex(m_iStart0);
	m_BtnIndex1 = GetIndex(m_iStart0 * 5);
	m_BtnIndex2 = GetIndex(m_iStart0 * 10);
	return ;
}
//获取索引值
int CeasyNtList::GetIndex(int iScore)
{
	int iArray[18] = {1,		2,		5,
					10,			20,		50,		
					100,		200,	500,
					1000,		2000,	5000,
					10000,		20000,	50000,
					100000,      200000,500000};
	for(int i = 0; i < 18; i++)
		if(iScore <= iArray[i])
		{
			return i;
		}
	return 0;
}
//设置下注数
void CeasyNtList::SetNumList(int iThisTurnLimit,int MinNote)
{
	//押注数清零
	m_Num=0;
	//底注
	m_iMinNote=MinNote;
	//本轮最大押注数
	m_iThisLimit=iThisTurnLimit;

	SetJetonStart(MinNote);
	
}
void CeasyNtList::OnMax()  
{		
	m_Num=m_iThisLimit;
	/*CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_NtList);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_SELECT_NOTE_NUM,m_Num,7);*/ 
	Invalidate();
}

//按钮消息
void CeasyNtList::OnNote1()   
{	m_Num+=m_iStart0;
    if(m_Num>=m_iThisLimit)
		m_Num=m_iThisLimit;
    Invalidate();
/*    CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_NtList);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_SELECT_NOTE_NUM,m_Num,1);*/ 
}

void CeasyNtList::OnNote2()   
{
	m_Num+=m_iStart1;
    if(m_Num>=m_iThisLimit)
		m_Num=m_iThisLimit;
    Invalidate();
	/*CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_NtList);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_SELECT_NOTE_NUM,m_Num,2); */
}

void CeasyNtList::OnNote3()   
{
    m_Num+=m_iStart2;
	if(m_Num>=m_iThisLimit)
		m_Num=m_iThisLimit;
	//CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_NtList);
	//CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	//pp->SendMessage(IDM_SELECT_NOTE_NUM,m_Num,3); 
	Invalidate();
}

void CeasyNtList::OnResetCancel()  
{	
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_NtList);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_SELECT_NOTE_NUM,m_Num,15); 
}
void CeasyNtList::OnResetOk()  
{
	if ( m_Num <= 0 )
		return;
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_NtList);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->SendMessage(IDM_SELECT_NOTE_NUM,m_Num,TYPE_NOTE); 
}
void CeasyNtList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		
	CGameImageHelper	help(&m_bk);
	help.BitBlt(dc.GetSafeHdc(),0,0);
	
	CGameImageHelper jeton(&m_PicNum);
	CDC destdc;

	destdc.CreateCompatibleDC(&dc);
	destdc.SelectObject(jeton);
	::TransparentBlt(dc.GetSafeHdc(),m_BtnRect0.left,m_BtnRect0.top,JETON_W,JETON_H,destdc.GetSafeHdc(),
		m_BtnIndex0 * JETON_W,0,JETON_W,JETON_H,RGB(255,0,255));

	::TransparentBlt(dc.GetSafeHdc(),m_BtnRect1.left,m_BtnRect1.top,JETON_W,JETON_H,destdc.GetSafeHdc(),
		m_BtnIndex1 * JETON_W,0,JETON_W,JETON_H,RGB(255,0,255));

	::TransparentBlt(dc.GetSafeHdc(),m_BtnRect2.left,m_BtnRect2.top,JETON_W,JETON_H,destdc.GetSafeHdc(),
		m_BtnIndex2 * JETON_W,0,JETON_W,JETON_H,RGB(255,0,255));

	DrawNum(&dc);
	destdc.DeleteDC();

}
//鼠标按下下注消息
void CeasyNtList::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(PtInRect(&m_BtnRect0,point))
	{
		OnNote1();
		return ;
	}
	if(PtInRect(&m_BtnRect1,point))
	{
		OnNote2();
		return ;
	}
	if(PtInRect(&m_BtnRect2,point))
	{
		OnNote3();
		return ;
	}
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	return ;
}
//写下注量
void CeasyNtList::DrawNum(CDC * pDC)
{
	{
		CFont Font, *OldFont;
		CRect rect;
		TCHAR PointMsg[200];
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkMode(TRANSPARENT);
		wsprintf(PointMsg,"%d",m_Num);
		Font.CreateFont(18,10,0,0,0,0,0,0,700,4,2,1,5,TEXT("宋体"));
		OldFont=pDC->SelectObject(&Font);
		rect.left = 20;
		rect.right = rect.left + 140;
		rect.top = 13;
		rect.bottom = rect.top + 20;
		pDC->DrawText(PointMsg,lstrlen(PointMsg),&rect,DT_RIGHT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		pDC->SelectObject(OldFont);
	}
	return;
}


