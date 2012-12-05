#include "Stdafx.h"
#include "Resource.h"
#include "GameCard.h"
#include "ClientGameDlg.h"
//静态变量
CGameImage				CUpGradeGameCard::m_CardPic[4];								//所用牌
#define ID_TIMER_MOVE_CARD        2008    // 移动ID
#define MOVE_CARD_TIME_INTERVAL   10     // 时间间隔

BEGIN_MESSAGE_MAP(CUpGradeGameCard, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//构造函数
CUpGradeGameCard::CUpGradeGameCard(BYTE bCardStyle)
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	m_bCardCount=0;
	SetCardStyle(bCardStyle);
	SetCardParameter(15,13,20);
	m_pHandleWnd=NULL;
	m_bHorzLook=true;
	m_bShowCard=false;
	m_bUseMouse=false;
	m_bShowNum = 0;
	m_bHotHitCard=255;
	m_bSelect=false;
	m_PtBasePoint.SetPoint(0,0);
	m_bFriendCardCount=0;			//友牌总数
	m_XShowMode=XShowMode::SWX_MODE_CENTER;
	m_YShowMode=YShowMode::SWY_MODE_CENTER;
	//AfxSetResourceHandle(GetModuleHandle(NULL));
	TCHAR path[MAX_PATH];
	wsprintf(path,".\\image\\this.bmp");
	m_NowThis.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
}

//析构函数
CUpGradeGameCard::~CUpGradeGameCard()
{
}

//初始化函数
bool CUpGradeGameCard::InitGameCard(CWnd * pHandleWnd)
{
	m_pHandleWnd=pHandleWnd;
	return true;
}

//设置扑克参数
void CUpGradeGameCard::SetCardParameter(int iHSpace, int iVSpace, int iUpSpace)
{
	m_iCardHSpace=iHSpace;
	m_iCardVSpace=iVSpace;
	m_iCardUpSpace=iUpSpace;
	FixCardControl(false);
	return;
}

//获取大小函数
bool CUpGradeGameCard::GetCardSize(CSize & Size)
{
	if (m_bCardCount>0)
	{
		if (m_bHorzLook==true)
		{
			Size.cx=m_iCardWidth+(m_bCardCount-1)*m_iCardHSpace;
			Size.cy=m_iCardHight+m_iCardUpSpace;
		}
		else
		{
			Size.cx=m_iCardWidth;
			Size.cy=m_iCardHight+(m_bCardCount-1)*m_iCardVSpace;
		}
	}
	else
	{
		Size.cx=0;
		Size.cy=0;
	}
	return true;
}

//设置基准点函数
void CUpGradeGameCard::SetBasePoint(CPoint & BasePoint, XShowMode XShowMode, YShowMode YShowMode)
{
	m_XShowMode=XShowMode;
	m_YShowMode=YShowMode;
	m_PtBasePoint=BasePoint;
	if(this->m_hWnd)
		FixCardControl();
	return;
}

//设置显示扑克
void CUpGradeGameCard::SetShowCard(bool bShow)
{
	m_bShowCard=bShow;
	if(this->m_hWnd)
		Invalidate(FALSE);
	return;
}

//设置使用鼠标
void CUpGradeGameCard::SetUseMouse(bool bUserMouse)
{
	m_bUseMouse=bUserMouse;
	return;
}

//设置显示方式
void CUpGradeGameCard::SetLookMode(bool bHorzLook)
{
	m_bHorzLook=bHorzLook;
	return;
}

//设置扑克
bool CUpGradeGameCard::SetCard(BYTE bCardList[], BYTE bUpList[], BYTE bCardCount)
{
	if (bCardCount>m_CardArray.GetSize()) m_CardArray.SetSize(bCardCount);
	if (bCardCount>m_CardUpArray.GetSize()) m_CardUpArray.SetSize(bCardCount);
	if (bCardList!=NULL) CopyMemory(m_CardArray.GetData(),bCardList,sizeof(BYTE)*bCardCount);
	if (bUpList!=NULL) CopyMemory(m_CardUpArray.GetData(),bUpList,sizeof(BYTE)*bCardCount);
	else memset(m_CardUpArray.GetData(),0,sizeof(BYTE)*bCardCount);
	m_bCardCount=bCardCount;
	if(((CClientGameDlg*)m_pHandleWnd)->GetGameStatus()==0)
		FixCardControl(false);
	else
		FixCardControl();

	return true;
}

//获取升起的扑克
BYTE CUpGradeGameCard::GetUpCard(BYTE bCardList[])
{
	BYTE bUpCount=0;
	for (BYTE i=0;i<m_bCardCount;i++)
	{
		if (m_CardUpArray.GetAt(i)==TRUE)
		{
			if (bCardList!=NULL) bCardList[bUpCount]=m_CardArray.GetAt(i);
			bUpCount++;
		}
	}
	return bUpCount;
}

//获取扑克信息
BYTE CUpGradeGameCard::GetCard(BYTE bCardList[], BYTE bUpList[])
{
	if (bCardList!=NULL) CopyMemory(bCardList,m_CardArray.GetData(),m_bCardCount*sizeof(BYTE));
	if (bUpList!=NULL) CopyMemory(bUpList,m_CardUpArray.GetData(),m_bCardCount*sizeof(BYTE));
	return m_bCardCount;
}

//按键测试
BYTE CUpGradeGameCard::HitCardTest(CPoint & Point)
{
	if (m_bHorzLook==true)
	{
		//寻找按键扑克
		BYTE bCardIndex=(BYTE)(Point.x/m_iCardHSpace);
		if (bCardIndex>=m_bCardCount)
			bCardIndex=m_bCardCount-1;

		//判断按键位置
		bool bHitThisCard=true;
		BYTE bCardUp=m_CardUpArray.GetAt(bCardIndex);
		if ((bCardUp==TRUE)&&(Point.y>m_iCardHight)) bHitThisCard=false;
		if ((bCardUp==FALSE)&&(Point.y<m_iCardUpSpace)) bHitThisCard=false;

		//寻找前面的张扑克
		if (bHitThisCard==false)
		{
			BYTE bFindCount=m_iCardWidth/m_iCardHSpace+1;
			for (BYTE i=1;i<bFindCount;i++)
			{
				if (bCardIndex==0) break;
				bCardUp=m_CardUpArray.GetAt(bCardIndex-i);
				if ((bCardUp==FALSE)&&(Point.y>m_iCardWidth)) return bCardIndex-i;
				if ((bCardUp==TRUE)&&(Point.y<20)) return bCardIndex-i;
			}
			return 255;
		}
		return bCardIndex;
	}
	return 255;
}

//删除升起的扑克
BYTE CUpGradeGameCard::RemoveUpCard()
{
	for (BYTE i=0;i<m_bCardCount;i++)
	{
		if (m_CardUpArray.GetAt(i)==TRUE)
		{
			m_bCardCount--;
			m_CardArray.RemoveAt(i);
			m_CardUpArray.RemoveAt(i);
			i--;
		}
	}
	FixCardControl();
	return m_bCardCount;
}

//调整窗口位置
void CUpGradeGameCard::FixCardControl(bool bInvalide)
{
	if(!this->m_hWnd)
		return;
	//获取位置
	CSize Size;
	GetCardSize(Size);

	//调整位置
	CRect CardRect;
	switch (m_XShowMode)
	{
	case SWX_MODE_LEFT: { CardRect.left=m_PtBasePoint.x; break; }
	case SWX_MODE_CENTER: {	CardRect.left=m_PtBasePoint.x-Size.cx/2; break; }
	case SWX_MODE_RIGHT: { CardRect.left=m_PtBasePoint.x-Size.cx; break; }
	}

	switch (m_YShowMode)
	{
	case SWY_MODE_TOP: { CardRect.top=m_PtBasePoint.y; break; }
	case SWY_MODE_CENTER: {	CardRect.top=m_PtBasePoint.y-Size.cy/2;	break; }
	case SWY_MODE_BOTTOM: { CardRect.top=m_PtBasePoint.y-Size.cy; break; }
	}

	//移动位置
	CardRect.right=CardRect.left+Size.cx;
	CardRect.bottom=CardRect.top+Size.cy;
	MoveWindow(&CardRect);

	//设置区域
	CRgn AllRgn,SignedRgn;
	AllRgn.CreateRectRgn(0,0,0,0);
	for (BYTE i=0;i<m_bCardCount;i++)
	{
		if (m_bHorzLook==true)
		{
			BYTE bUpCard=m_CardUpArray.GetAt(i);
			SignedRgn.CreateRoundRectRgn(i*m_iCardHSpace,(bUpCard==TRUE)?0:m_iCardUpSpace,
				i*m_iCardHSpace+m_iCardWidth+1,(bUpCard==TRUE)?m_iCardHight+1:m_iCardUpSpace+m_iCardHight+1,2,2);
			AllRgn.CombineRgn(&AllRgn,&SignedRgn,RGN_OR);
			SignedRgn.DeleteObject();
		}
		else 
		{
			SignedRgn.CreateRoundRectRgn(0,i*m_iCardVSpace,m_iCardWidth+1,i*m_iCardVSpace+m_iCardHight+1,2,2);
			AllRgn.CombineRgn(&AllRgn,&SignedRgn,RGN_OR);
			SignedRgn.DeleteObject();
		}
	}

	//设置区域
	SetWindowRgn(AllRgn,TRUE);
	AllRgn.DeleteObject();
	Invalidate(FALSE);

	return;
}

//建立消息
int CUpGradeGameCard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct)==-1) return -1;
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime(10);

	SetCardImage();
	SetCardWidthHeight(0,0);
	/*	if (GetSystemMetrics(SM_CXSCREEN)>=1024)
	{
	m_iCardHSpace=16;
	m_iCardVSpace=10;
	if(GetCardStyle())//调用小牌
	{
	m_iCardHight=57;
	m_iCardWidth=42;		
	}
	else
	{
	m_iCardHight=95;
	m_iCardWidth=70;	
	}
	//		m_CardPic[0].SetLoadInfo(".\\image\\card\\game_card.bmp",CGameImageLink::m_bAutoLock);
	//		m_CardPic[1].SetLoadInfo(".\\image\\card\\game_card_back.bmp",CGameImageLink::m_bAutoLock);
	//		m_CardPic[2].SetLoadInfo(".\\image\\card\\game_card_small.bmp",CGameImageLink::m_bAutoLock);
	//		m_CardPic[3].SetLoadInfo(".\\image\\card\\game_card_small_back.bmp",CGameImageLink::m_bAutoLock);

	//		m_CardPic[0].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_GAME_CARD,CGameImageLink::m_bAutoLock);
	//		m_CardPic[1].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_CARD_BACK,CGameImageLink::m_bAutoLock);
	//		m_CardPic[2].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_GAME_CARD_SMALL,CGameImageLink::m_bAutoLock);	
	//		m_CardPic[3].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_GAME_CARD_SMALL_BACK,CGameImageLink::m_bAutoLock);	
	}
	else
	{
	m_iCardHSpace=11;
	m_iCardVSpace=11;
	if(GetCardStyle())//调用小牌
	{
	m_iCardHight=57;
	m_iCardWidth=42;
	}
	else
	{		
	m_iCardHight=73;
	m_iCardWidth=54;
	}
	//====m_CardPic[0]牌正面视图.m_CardPic[1]牌背面视图
	//	m_CardPic[0].SetLoadInfo(".\\image\\card\\game_card_800.bmp",CGameImageLink::m_bAutoLock);
	//	m_CardPic[1].SetLoadInfo(".\\image\\card\\game_card_800_back.bmp",CGameImageLink::m_bAutoLock);
	//	m_CardPic[2].SetLoadInfo(".\\image\\card\\game_card_small.bmp",CGameImageLink::m_bAutoLock);
	//	m_CardPic[3].SetLoadInfo(".\\image\\card\\game_card_small_back.bmp",CGameImageLink::m_bAutoLock);

	//		m_CardPic[0].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_GAME_CARD_800,CGameImageLink::m_bAutoLock);
	//		m_CardPic[1].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_CARD_BACK_800,CGameImageLink::m_bAutoLock);
	//		m_CardPic[2].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_GAME_CARD_SMALL,CGameImageLink::m_bAutoLock);
	//		m_CardPic[3].SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_GAME_CARD_SMALL_BACK,CGameImageLink::m_bAutoLock);
	}*/
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);
	return 0;
}

//重画函数
void CUpGradeGameCard::OnPaint()
{
	CPaintDC dc(this);
	if (m_bCardCount==0) return;

	//建立缓冲
	CDC BufferDC;
	CSize CardSize;
	CBitmap BufferBmp;
	GetCardSize(CardSize);
	BufferDC.CreateCompatibleDC(&dc);
	BufferBmp.CreateCompatibleBitmap(&dc,CardSize.cx,CardSize.cy);
	CBitmap * pOldBmp=BufferDC.SelectObject(&BufferBmp);

	//加载位图
	//	CAFCImageHandle CardHandle(&m_CardPic[0]);
	CGameImageHelper CardHandle(&m_CardPic[0]);
	//	CGameImageHelper CardHandle(&m_CardPic[0]);
	CGameImageHelper BackHandle(&m_CardPic[1]);
	CGameImageHelper SmallHandle(&m_CardPic[2]);		//小牌
	CGameImageHelper SmallBackHandle(&m_CardPic[3]);	//小牌大小猫

	//绘画扑克
	int iXPos=0,iYPos=0;
	CGameImageHelper * pActiveHandle=NULL;
	for (BYTE i=0;i<m_bCardCount;i++)
	{
		BYTE bCard=m_CardArray.GetAt(i);
		BYTE bUpCard=m_CardUpArray.GetAt(i);
		if ((m_bShowCard==true)&&(m_CardArray.GetAt(i)!=0))
		{
			if ((bCard==0x4E)||(bCard==0x4F))
			{
				if(IMAGE_SMALL == GetCardStyle() )
				{
					iXPos=(bCard-0x4D)*m_iCardWidth;
					iYPos=0;
					pActiveHandle=&SmallBackHandle;		
				}else
				{
					iXPos=(bCard-0x4D)*m_iCardWidth;
					iYPos=0;
					pActiveHandle=&BackHandle;		
				}
			}
			else
			{
				if(IMAGE_SMALL == GetCardStyle() )
				{
					pActiveHandle=&SmallHandle;
					iXPos=GetCardXPos(bCard)*m_iCardWidth;
					iYPos=GetCardYPos(bCard)*m_iCardHight;
				}else
				{
					pActiveHandle=&CardHandle;
					iXPos=GetCardXPos(bCard)*m_iCardWidth;
					iYPos=GetCardYPos(bCard)*m_iCardHight;
				}

			}
		}
		else
		{
			iXPos=0;
			iYPos=0;
			if(IMAGE_SMALL == GetCardStyle() )
				pActiveHandle=&SmallBackHandle;
			else
				pActiveHandle=&BackHandle;
		}

		if (m_bHorzLook==true) 
			pActiveHandle->BitBlt(BufferDC,i*m_iCardHSpace,bUpCard?0:m_iCardUpSpace,m_iCardWidth,m_iCardHight,iXPos,iYPos);
		else pActiveHandle->BitBlt(BufferDC,0,i*m_iCardVSpace,m_iCardWidth,m_iCardHight,iXPos,iYPos);
	}

	//刷新界面
	dc.BitBlt(0,0,CardSize.cx,CardSize.cy,&BufferDC,0,0,SRCCOPY);

	CRect rect,rect1;
	//牌区大矩形
	rect.left=0;
	rect.right=CardSize.cx;
	if(m_bHorzLook)
		rect.top = CardSize.cy - m_iCardHight;
	else 
		rect.top =0;
	rect.bottom=CardSize.cy;

	switch(m_bShowNum)
	{
	case 1:
		if (m_bHorzLook==true) 		//小矩形
		{
			rect1.left =  rect.right - m_iCardWidth;
			rect1.top =  rect.top;
			rect1.bottom = rect.bottom;
			rect1.right = rect.right;
		}else
		{
			rect1.left =  rect.left ;
			rect1.top =  rect.bottom - m_iCardHight;
			rect1.bottom = rect.bottom ;
			rect1.right = rect.right;;
		}
		break;	
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
	int iNumWidth = 36,iNumHeight = 41;

	CDC NumDC;
	NumDC.CreateCompatibleDC(&dc);

	CGameImageHelper Num(&m_NowThis);

	NumDC.SelectObject(Num);
	int xoffset =(rect1.Width()-( m_bCardCount >=10?2:1)*iNumWidth)/2;
	int yoffset = (rect1.Height()-iNumHeight)/2;
	if (m_bShowNum)
		dc.TransparentBlt(rect1.left+xoffset,rect1.top+yoffset,Num.GetWidth(),Num.GetHeight(),&NumDC,0,0,Num.GetWidth(),Num.GetHeight(),RGB(255,0,255));

	//清理资源
	BufferDC.SelectObject(pOldBmp);
	BufferDC.DeleteDC();
	NumDC.DeleteDC();
	BufferBmp.DeleteObject();

	return;
}

//鼠标消息
void CUpGradeGameCard::OnLButtonDown(UINT nFlags, CPoint Point)
{
	if ((m_bHorzLook==true)&&(m_bUseMouse==true))
		m_bHotHitCard=HitCardTest(Point);
	return;
}

//鼠标消息
void CUpGradeGameCard::OnLButtonUp(UINT nFlags, CPoint Point)
{
	if ((m_bUseMouse==true)&&(m_bHotHitCard!=255))
	{
		BYTE bHitCard=HitCardTest(Point);
		if ((bHitCard==255)||(m_bHotHitCard!=bHitCard))
		{
			m_bHotHitCard=255;
			return;
		}
		BYTE bUpCard=m_CardUpArray.GetAt(bHitCard);
		m_CardUpArray.SetAt(bHitCard,(bUpCard==TRUE)?FALSE:TRUE);
		FixCardControl();

		//重画失效部分
		CRect Rect;
		Rect.SetRect(bHitCard*m_iCardHSpace,0,bHitCard*m_iCardHSpace+m_iCardWidth,m_iCardHight+m_iCardUpSpace);
		InvalidateRect(Rect,FALSE);
		if (m_pHandleWnd!=NULL) m_pHandleWnd->SendMessage(IDM_LEFT_HITCARD,m_CardArray.GetAt(bHitCard)/*牌值*/,bUpCard/*是否为升起来牌*/);
	}
	return;
}

//鼠标消息
void CUpGradeGameCard::OnRButtonUp(UINT nFlags, CPoint point)
{
	/*	if(!((CClientGameDlg*)m_pHandleWnd)->m_PlayView.m_bRightPower)
	{
	if ((m_bUseMouse==true)&&(m_pHandleWnd!=NULL)) 
	m_pHandleWnd->SendMessage(IDM_RIGHT_HITCARD,0,0);
	}
	else
	{
	if ((m_bUseMouse==true)&&(m_pHandleWnd!=NULL))
	{
	BYTE bHitCard=HitCardTest(point);
	if ((bHitCard==255))
	{
	m_bHotHitCard=255;
	return;
	}
	BYTE bUpCard=m_CardUpArray.GetAt(bHitCard);
	//发现了点击的扑克
	if(bHitCard)
	{
	BYTE HuaSe=GetCardNum(m_CardArray.GetAt(bHitCard));
	for(int i=0;i<m_bCardCount;i++)
	{
	if ((m_bShowCard==true)&&(m_CardArray.GetAt(i)!=0))
	{
	BYTE ttt=GetCardNum(m_CardArray.GetAt(i));
	if(HuaSe==ttt)
	{
	m_CardUpArray.SetAt(i,(bUpCard==TRUE)?FALSE:TRUE);
	}
	}
	}
	FixCardControl();
	CRect Rect;
	Rect.SetRect(0,0,33*m_iCardHSpace+m_iCardWidth,m_iCardHight+m_iCardUpSpace);
	InvalidateRect(Rect,FALSE);
	m_pHandleWnd->SendMessage(IDM_RIGHT_HITCARD,0,0);
	}
	}
	}*/
	return;
}

//光标消息
BOOL CUpGradeGameCard::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message)
{
	/*if (m_bUseMouse==true)
	{
		SetCursor(CGameImageLink::m_hHandCursor);
		return TRUE;
	}*/
	return __super::OnSetCursor(pWnd,nHitTest,message);
}


BOOL CUpGradeGameCard::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	return CWnd::PreTranslateMessage(pMsg);
}

//鼠标消息
void CUpGradeGameCard::OnMouseMove(UINT nFlags, CPoint Point)
{
	m_bHotHitCard=HitCardTest(Point);
	if ((m_bUseMouse==true)&&(m_bHotHitCard!=255)&&!m_bSelect)
	{
//		if ((bHitCard==255)||(m_bHotHitCard!=bHitCard))
//		{
//			m_bHotHitCard=255;
//			return;
//		}
//		BYTE bHitCard=HitCardTest(Point);
//		BYTE bUpCard=m_CardUpArray.GetAt(bHitCard);
//		m_CardUpArray.SetAt(bHitCard,(bUpCard==TRUE)?FALSE:TRUE);
//		FixCardControl();

		//重画失效部分
//		CRect Rect;
//		Rect.SetRect(bHitCard*m_iCardHSpace,0,bHitCard*m_iCardHSpace+m_iCardWidth,m_iCardHight+m_iCardUpSpace);
//		InvalidateRect(Rect,FALSE);

		m_bSelect=true;
		//if (m_pHandleWnd!=NULL)	m_pHandleWnd->SendMessage(IDM_LEFT_HITCARD);
	}
	else
	{		//重画失效部分
//		CRect Rect;
//		Rect.SetRect(bHitCard*m_iCardHSpace,0,bHitCard*m_iCardHSpace+m_iCardWidth,m_iCardHight+m_iCardUpSpace);
//		InvalidateRect(Rect,FALSE);
		m_bSelect=false;
//		if (m_pHandleWnd!=NULL) m_pHandleWnd->SendMessage(IDM_MOUSE_LEFT);
	}
	return;
	CWnd::OnMouseMove(nFlags, Point);
}
//设置友牌
BOOL CUpGradeGameCard::SetFriendArray(BYTE bCardList[], BYTE bUpList[], BYTE bCardCount)
{
	/*if (bCardCount>m_CardFriendArray.GetSize())*/ m_CardFriendArray.SetSize(bCardCount);
	//if (bCardCount>m_CardUpArray.GetSize()) m_CardUpArray.SetSize(bCardCount);
	if (bCardList!=NULL) CopyMemory(m_CardFriendArray.GetData(),bCardList,sizeof(BYTE)*bCardCount);
	//if (bUpList!=NULL) CopyMemory(m_CardUpArray.GetData(),bUpList,sizeof(BYTE)*bCardCount);
	//else memset(m_CardUpArray.GetData(),0,sizeof(BYTE)*bCardCount);
	m_bFriendCardCount=bCardCount;
	return TRUE;
	//m_CardFriendArray
}
//在友牌数例中查找某张牌的数目
BYTE CUpGradeGameCard::FindACardNumInFriendList(BYTE iCardNum)
{
	int FriendCount=0;
	if(m_bFriendCardCount>0&&m_bCardCount>0)
	{
		for(int i=0;i<m_bFriendCardCount;i++)
		{
			if(GetCardNum(m_CardFriendArray.GetAt(i))==iCardNum)
				FriendCount++;
		}	
	}
	//	TCHAR sz[200];
	//	wsprintf(sz,"FriendCount=%d,m_bFriendCardCount=%d",FriendCount,m_bFriendCardCount);
	//	WriteStr(sz);
	return FriendCount;
}
//设置调用图片
void CUpGradeGameCard::SetCardImage()
{
	TCHAR path[MAX_PATH]={0};
	switch(GetCardStyle())
	{
	case IMAGE_SMALL:
			wsprintf(path,TEXT("image\\CardSkin\\game_CARD_SMALL.bmp"));
			m_CardPic[2].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
			
			wsprintf(path,TEXT("image\\CardSkin\\game_CARD_SMALL_back.bmp"));
			m_CardPic[3].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

		break;
	case IMAGE_VERY_SMALL:
			wsprintf(path,TEXT("image\\CardSkin\\very_small.bmp"));
			m_CardPic[0].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

		//m_CardPic[1].SetLoadInfo(".\\image\\card\\very_small.bmp",CGameImageLink::m_bAutoLock);
		break;
	default:
		if(GetSystemMetrics(SM_CXSCREEN)>=1024)
		{
			wsprintf(path,TEXT("image\\CardSkin\\game_CARD.bmp"));
			m_CardPic[0].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
			wsprintf(path,TEXT("image\\CardSkin\\game_CARD_back.bmp"));
			m_CardPic[1].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
		}
		else
		{
			wsprintf(path,TEXT("image\\CardSkin\\game_CARD_800.bmp"));
			m_CardPic[0].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
			wsprintf(path,TEXT("image\\CardSkin\\game_CARD_800_back.bmp"));
			m_CardPic[1].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
		}
		break;
	}
	return ;
}
//设置扑克高和宽
void  CUpGradeGameCard::SetCardWidthHeight(int iWidth,int iHeight)
{
	switch(GetCardStyle())
	{
	case IMAGE_SMALL:
		m_iCardHight=57;
		m_iCardWidth=42;
		break;
	case IMAGE_VERY_SMALL:
		m_iCardHight=12;
		m_iCardWidth=25;
		break;
	default:
		if(GetSystemMetrics(SM_CXSCREEN)>=1024)
		{	
			/*m_iCardHight=94;
			m_iCardWidth=123;	*/
			m_iCardHight=m_CardPic[1].GetHeight();
			m_iCardWidth=m_CardPic[1].GetWidth()/3;	
			m_iCardHSpace=m_iCardWidth / 5;
		}
		else
		{
			m_iCardHight=73;
			m_iCardWidth=54;
		}
	}
	return ;
}
void CUpGradeGameCard::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (ID_TIMER_MOVE_CARD == nIDEvent)
	{
		// 算出坐标进行移动
		if (NULL == m_hWnd)
		{
			return ;
		}
		CRect rect;
		GetClientRect(&rect);
		m_lMoveCount --;
		CPoint ptMoveTo(0,0);
		if (m_lMoveCount < 1)
		{
			m_ptStart = m_ptEnd;
		}
		else
		{
			ptMoveTo = m_ptEnd - m_ptStart;
			if (0 != ptMoveTo.x)
			{
				long lTmp = ptMoveTo.x/m_lMoveCount;
				if (0 == lTmp)
				{
					lTmp = (ptMoveTo.x>0)?1:-1;
				}
				else
				{
					ptMoveTo.x = lTmp;
				}
			}
			if (0 != ptMoveTo.y)
			{
				long lTmp = ptMoveTo.y/m_lMoveCount;
				if (0 == lTmp)
				{
					lTmp = (ptMoveTo.y>0)?1:-1;
				}
				else
				{
					ptMoveTo.y = lTmp;
				}
			}
			m_ptStart += ptMoveTo;			
		}
		if (m_ptStart == m_ptEnd)
		{
              ShowWindow(SW_HIDE);
			KillTimer(ID_TIMER_MOVE_CARD);
		}
		SetBasePoint(m_ptStart, m_XShowMode, m_YShowMode);
	}

	CWnd::OnTimer(nIDEvent);
}

// 移动
void CUpGradeGameCard::MoveAnimal(CPoint &ptStart, CPoint &ptEnd, long lTime)
{
	if (NULL == m_hWnd)
	{
		return ;
	}
	KillTimer(ID_TIMER_MOVE_CARD);
	ShowWindow(SW_SHOW);
	SetBasePoint(ptStart, m_XShowMode, m_YShowMode);
	m_ptStart = ptStart;         // 起点
	m_ptEnd = ptEnd;             // 终点
	m_lMoveCount = lTime/MOVE_CARD_TIME_INTERVAL; // 移动次数
	if (0 == m_lMoveCount)
	{
		m_lMoveCount = 1;
	}
	SetTimer(ID_TIMER_MOVE_CARD, MOVE_CARD_TIME_INTERVAL, NULL);
}
void CUpGradeGameCard::StopMove(void)
{
    ShowWindow(SW_HIDE);
	KillTimer(ID_TIMER_MOVE_CARD);
}
void CUpGradeGameCard::GetBasePoint(CPoint &ptBasePoint)
{
	ptBasePoint = m_PtBasePoint;
}