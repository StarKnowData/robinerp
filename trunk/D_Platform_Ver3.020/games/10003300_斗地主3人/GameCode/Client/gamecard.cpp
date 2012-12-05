#include "Stdafx.h"
#include "Resource.h"
#include "GameCard.h"
#include "ClientGameDlg.h"
//静态变量
CGameImage				CUpGradeGameCard::m_CardPic[6];								//所用牌

BEGIN_MESSAGE_MAP(CUpGradeGameCard, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()
#define IDC_HAND            MAKEINTRESOURCE(32649)

//构造函数
CUpGradeGameCard::CUpGradeGameCard(BYTE bCardStyle)
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	//c++ test
	m_iCardHight = 0;
	m_iCardWidth = 0;
	m_iCardHSpace = 0;
	m_iCardVSpace = 0;
	m_iCardUpSpace = 0;
	m_bMove = false;
	m_CurCardIndex = 0;

	m_bCardCount=0;
	SetCardStyle(bCardStyle);
	SetCardParameter(17,18,20);
	m_pHandleWnd=NULL;
	m_bHorzLook=true;
	m_bShowCard=false;
	m_bUseMouse=false;
	m_bHotHitCard=255;
	m_bSelect=false;
	m_PtBasePoint.SetPoint(0,0);
	m_bFriendCardCount=0;			//友牌总数
	m_bShowNum = 0;
	m_XShowMode=XShowMode::SWX_MODE_CENTER;
	m_YShowMode=YShowMode::SWY_MODE_CENTER;
	m_iSourcePoint = 0 ;
	m_iBackPoint = 0;
	m_iBackMultiple = 1;
	//	m_bLButtonDown = FALSE;
	m_ptLeftHit = CPoint(0,0);
	m_bCanMove = FALSE;
	m_bMultiSel = false;
	m_bMoveSel = false;

	//AfxSetResourceHandle(GetModuleHandle(NULL));
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
	FixCardControl();
	return;
}

void CUpGradeGameCard::GetCardWindthAndHeight(int &wt, int &ht)
{
	wt = m_CardPic[1].GetWidth()/3;
	ht = m_CardPic[1].GetHeight();
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
	FixCardControl();
	return;
}

//设置显示扑克
void CUpGradeGameCard::SetShowCard(bool bShow)
{
	m_bShowCard=bShow;
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

	if(bCardList == NULL)
	{
		m_iSourcePoint = 0;
		m_iBackPoint = 0; 
		m_iBackMultiple = 1;
	}

	m_CardArray.SetSize(bCardCount);
	m_CardUpArray.SetSize(bCardCount);
	if (bCardList!=NULL) CopyMemory(m_CardArray.GetData(),bCardList,sizeof(BYTE)*bCardCount);
	if (bUpList!=NULL) CopyMemory(m_CardUpArray.GetData(),bUpList,sizeof(BYTE)*bCardCount);
	else memset(m_CardUpArray.GetData(),0,sizeof(BYTE)*bCardCount);
	if(m_MoveSelectCardArray.GetSize()!=bCardCount)
	{
		m_MoveSelectCardArray.SetSize(bCardCount);
		memset(m_MoveSelectCardArray.GetData(),0,sizeof(BYTE)*bCardCount);
	}
	m_bCardCount=bCardCount;
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
			if (bCardList!=NULL)
				bCardList[bUpCount]=m_CardArray.GetAt(i);
			bUpCount++;
		}
	}
	return bUpCount;
}

//获取扑克信息
BYTE CUpGradeGameCard::GetCard(BYTE bCardList[], BYTE bUpList[])
{
	if (bCardList!=NULL)
		CopyMemory(bCardList,m_CardArray.GetData(),m_bCardCount*sizeof(BYTE));
	if (bUpList!=NULL)
		CopyMemory(bUpList,m_CardUpArray.GetData(),m_bCardCount*sizeof(BYTE));
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
		if ((bCardUp==TRUE)&&(Point.y>m_iCardHight)) 
			bHitThisCard=false;
		if ((bCardUp==FALSE)&&(Point.y<m_iCardUpSpace))
			bHitThisCard=false;

		//寻找前面的张扑克
		if (bHitThisCard==false)
		{
			BYTE bFindCount=m_iCardWidth/m_iCardHSpace+1;
			for (BYTE i=1;i<bFindCount;i++)
			{
				if (bCardIndex==0)
					break;
				if(bCardIndex-i < 0)
					break;
				bCardUp=m_CardUpArray.GetAt(bCardIndex-i);
				if ((bCardUp==FALSE)&&(Point.y>m_iCardWidth)) 
					return bCardIndex-i;
				if ((bCardUp==TRUE)&&(Point.y<m_iCardUpSpace))
					return bCardIndex-i;
			}
			return 255;
		}
		return bCardIndex;
	}
	return 255;
}

//按键测试(是否在某张牌上方)
BYTE CUpGradeGameCard::HitCardTestAbove(CPoint &Point)
{
	//	AfxMessageBox("3");
	if (m_bHorzLook==true)
	{
		//寻找按键扑克
		BYTE bCardIndex=(BYTE)(Point.x/m_iCardHSpace);
		if (bCardIndex>=m_bCardCount)
			bCardIndex=m_bCardCount-1;

		//判断按键位置
		bool bHitThisCard=true;
		BYTE bCardUp=m_CardUpArray.GetAt(bCardIndex);
		if ((bCardUp==TRUE)&&(Point.y>m_iCardHight)) 
			bHitThisCard=false;
		if ((bCardUp==FALSE)&&(Point.y>m_iCardHight))
			bHitThisCard=false;

		//寻找前面的张扑克
		if (bHitThisCard==false)
		{
			BYTE bFindCount=m_iCardWidth/m_iCardHSpace+1;
			for (BYTE i=1;i<bFindCount;i++)
			{
				if (bCardIndex==0) break;
				if(bCardIndex-i < 0)
					break;
				bCardUp=m_CardUpArray.GetAt(bCardIndex-i);
				if ((bCardUp==FALSE)&&(Point.y>m_iCardWidth)) return bCardIndex-i;
				if ((bCardUp==TRUE)&&(Point.y<m_iCardUpSpace)) return bCardIndex-i;
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
void CUpGradeGameCard::FixCardControl()
{
	if (!m_hWnd)
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
	Invalidate(FALSE);
	//设置区域
	CRgn AllRgn,SignedRgn;
	AllRgn.CreateRectRgn(0,0,0,0);
	for (BYTE i=0;i<m_bCardCount;i++)
	{
		if (m_bHorzLook==true)
		{
			BYTE bUpCard=m_CardUpArray.GetAt(i);
			/*if(m_bUseMouse)
			{
				SignedRgn.CreateRoundRectRgn(i*m_iCardHSpace,0,
					i*m_iCardHSpace+m_iCardWidth+1,m_iCardUpSpace+m_iCardHight+1,2,2);
				AllRgn.CombineRgn(&AllRgn,&SignedRgn,RGN_OR);

			}
			else
			{*/
			SignedRgn.CreateRoundRectRgn(i*m_iCardHSpace,(bUpCard==TRUE)?0:m_iCardUpSpace,
				i*m_iCardHSpace+m_iCardWidth+1,(bUpCard==TRUE)?m_iCardHight+1:m_iCardUpSpace+m_iCardHight+1,2,2);
			AllRgn.CombineRgn(&AllRgn,&SignedRgn,RGN_OR);

			//}
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
	//	m_CardViewRgn.CopyRgn(&AllRgn);
	SetWindowRgn(AllRgn,TRUE);
	AllRgn.DeleteObject();
	//	m_CardViewRgn.DeleteObject();
	//	m_CardViewRgn.Attach(AllRgn.Detach());
	//重画界面
	Invalidate(TRUE);
	return;
}

//建立消息
int CUpGradeGameCard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct)==-1) return -1;
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime(1000);
	SetCardImage();
	SetCardWidthHeight(0,0);

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
	//填充
	CGameImageHelper CardHandle(&m_CardPic[0]);
	CGameImageHelper BackHandle(&m_CardPic[1]);
	CGameImageHelper SmallHandle(&m_CardPic[2]);		//小牌
	CGameImageHelper SmallBackHandle(&m_CardPic[3]);	//小牌大小猫
	CGameImageHelper BkHandle(&m_bk);
	CGameImageHelper MoveSelectCardHandle(&m_CardPic[4]);
	CGameImageHelper MoveSelectBackHandle(&m_CardPic[5]);

	//绘画扑克
	int iXPos=0,iYPos=0;
	CGameImageHelper * pActiveHandle=NULL;

	for(int i = 0; i < CardSize.cy; i += m_bk.GetHeight())
	{
		for(int j = 0; j < CardSize.cx; j += m_bk.GetWidth())
		{	
			BkHandle.BitBlt(BufferDC, j ,i);	
		}	
	}
	for (BYTE i=0;i<m_bCardCount;i++)
	{
		BYTE bCard=m_CardArray.GetAt(i);
		BYTE bUpCard=m_CardUpArray.GetAt(i);
		BYTE bMoveSelect =m_MoveSelectCardArray.GetAt(i);

		if ((m_bShowCard==true)&&bCard != 0)//(m_CardArray.GetAt(i)!=0))
		{
			if ((bCard==0x4E)||(bCard==0x4F))
			{
				if(bMoveSelect==1)
				{
					iXPos=(bCard-0x4D)*m_iCardWidth;
					iYPos=0;
					pActiveHandle=&MoveSelectBackHandle;	
				}
				else if(IMAGE_SMALL == GetCardStyle() )
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
				if(bMoveSelect==1)
				{
					pActiveHandle=&MoveSelectCardHandle;
					iXPos=GetCardXPos(bCard)*m_iCardWidth;
					iYPos=GetCardYPos(bCard)*m_iCardHight;
				}
				else if(IMAGE_SMALL == GetCardStyle() )
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
			if(bMoveSelect==1)
			{
				pActiveHandle=&MoveSelectBackHandle;
			}
			else if(IMAGE_SMALL == GetCardStyle() )
				pActiveHandle=&SmallBackHandle;
			else
				pActiveHandle=&BackHandle;
		}

		if (m_bHorzLook==true) 
			pActiveHandle->BitBlt(BufferDC,i*m_iCardHSpace,bUpCard?0:m_iCardUpSpace,m_iCardWidth,m_iCardHight,iXPos,iYPos);
		else 
			pActiveHandle->BitBlt(BufferDC,0,i*m_iCardVSpace,m_iCardWidth,m_iCardHight,iXPos,iYPos);
		//鼠标选择牌
		/*
		if(m_bMoveSel && i==m_CurCardIndex && !(m_CurCardIndex>= m_StartIndex && m_CurCardIndex<=m_EndIndex))
		{
		CRect rc;
		rc.left = i*m_iCardHSpace+4;
		rc.top = bUpCard?0:m_iCardUpSpace;
		rc.right = i*m_iCardHSpace+m_iCardHSpace;
		rc.bottom = rc.top+m_iCardHight;
		DrawTransparent(BufferDC.GetSafeHdc(), rc, RGB(125, 0, 125), 200);
		}*/
	}

	//刷新界面
	dc.BitBlt(0,0,CardSize.cx,CardSize.cy,&BufferDC,0,0,SRCCOPY);
	//透明处理

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
	int iNumWidth = 25,iNumHeight = 28;

	CDC NumDC;
	NumDC.CreateCompatibleDC(&dc);

	CGameImageHelper Num(&m_Num);

	NumDC.SelectObject(Num);
	int xoffset =(rect1.Width()-( m_bCardCount >=10?2:1)*iNumWidth)/2;
	int yoffset = (rect1.Height()-iNumHeight)/2;
	int num1 =m_bCardCount/10 ,num2 = m_bCardCount%10;
	if (m_bShowNum)
	{
		if(m_bCardCount >= 10)
		{
			dc.TransparentBlt(rect1.left+xoffset,rect1.top+yoffset,iNumWidth,iNumHeight,&NumDC,num1*iNumWidth,0,iNumWidth,iNumHeight,RGB(255,0,255));
			dc.TransparentBlt(rect1.left+xoffset+iNumWidth,rect1.top+yoffset,iNumWidth,iNumHeight,&NumDC,num2*iNumWidth,0,iNumWidth,iNumHeight,RGB(255,0,255));
		}else
		{
			dc.TransparentBlt(rect1.left+xoffset,rect1.top+yoffset,iNumWidth,iNumHeight,&NumDC,num2*iNumWidth,0,iNumWidth,iNumHeight,RGB(255,0,255));
		}
	}
	

	//鼠标选择牌
	//刷新界面
	//if(m_bMultiSel)
	//{
	//	CRect rc(m_pStartPos.x, m_pStartPos.y, m_pEndPos.x, m_pEndPos.y);
	//	if(abs(rc.top -rc.bottom) < 2)
	//		rc.bottom = rc.top+2;
	//	DrawTransparent(dc.GetSafeHdc(), rc, RGB(125, 0, 125), 200);
	//	//dc.FillSolidRect(&rc, RGB(255, 0, 0));
	//}
	//清理资源
	BufferDC.SelectObject(pOldBmp);
	BufferDC.DeleteDC();
	BufferBmp.DeleteObject();
	return;
}

//分牌
int CUpGradeGameCard::GetPoint()
{
	if(m_iSourcePoint && m_iBackPoint && m_iBackMultiple)
		return m_iSourcePoint +m_iBackPoint * m_iBackMultiple;
	int score = 0;
	for (BYTE i=0;i<m_bCardCount;i++)
	{
		BYTE bCard=m_CardArray.GetAt(i);
		if(GetCardValue(bCard) == 5 )
			score +=5;
		if(GetCardValue(bCard) == 10||GetCardValue( bCard ) == 13 )
			score +=10;
	}
	return score;
}
//鼠标消息
void CUpGradeGameCard::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags, Point);
	if (m_bUseMouse==true)
	{
		m_ToolTip.AddTool(this,"在牌面上点击左键收牌，在牌面外点击右键出牌");
		m_ToolTip.Activate(TRUE);

		if (m_bHorzLook==true)
		{
			m_bHotHitCard=HitCardTest(Point);
			if(m_bHotHitCard == 255)
				return ;
			//寻找按键扑克
			BYTE bCardUp=m_CardUpArray.GetAt(m_bHotHitCard);
			bool AllUp = true;
			for(int i=0; i<m_CardUpArray.GetCount(); i++)
			{
				if(!m_CardUpArray.GetAt(i))
				{
					AllUp = false;
					break;
				}
			}
			if(!AllUp && bCardUp && Point.y<m_iCardUpSpace+m_iCardHight)//2008-08-20加上m_iCardHight
			{
				m_bMoveSel = true;
				//			m_bLDown = true;
				m_pMovePos = Point;

				m_bCanUp = bCardUp;
				if (!bCardUp)
				{
					m_bMoveFirstCard = m_bHotHitCard;
					m_CardUpArray.SetAt(m_bHotHitCard,1);
				}
				m_bMove = false;
				m_CurCardIndex = -1;
				m_StartIndex = m_bHotHitCard;
				for(int i=m_bHotHitCard; i>=0; i--)
				{
					if(m_CardUpArray.GetAt(i))
					{
						m_StartIndex = i;
						continue;
					}
				}
				m_EndIndex = m_bHotHitCard;
				for(int i=m_bHotHitCard+1; i<m_bCardCount; i++)
				{
					if(m_CardUpArray.GetAt(i))
					{
						m_EndIndex = i;
						continue;
					}
				}
			}
			else
			{
				m_pStartPos = Point;
				m_bMultiSel = true;
			}
			SetCapture();
		}
	}
	return;
}
//paramenter iSourcePoint 源分数
//paramenter iBackPoint		底分数
//paramenter iBackMultiple	捞底倍数
//主动设置分牌数
BOOL CUpGradeGameCard::SetBackPointAndMultiple(int iSourcePoint,int iBackPoint,int iBackMultiple)
{
	m_iSourcePoint = iSourcePoint;
	m_iBackPoint = iBackPoint;
	m_iBackMultiple = iBackMultiple;
	return true;
}
//鼠标消息
void CUpGradeGameCard::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags, Point);

	//m_MouseMove = false;
	//	m_bLDown = false;
	if (m_bUseMouse==true)
	{
		/*int iIndexStart = GetCardIndex(m_pStartPos);
		int iIndexEnd   = GetCardIndex(Point);
		if(iIndexStart== iIndexEnd)
		{
		if(255 != iIndexStart)
		{
		bool bUp = m_CardUpArray.GetAt(iIndexStart);
		m_CardUpArray.SetAt(iIndexStart,!bUp);
		m_bMultiSel = false;
		m_bMoveSel = false;
		ReleaseCapture();
		for(int i=0; i<m_bCardCount; i++)
		{
		m_MoveSelectCardArray.SetAt(i,false);
		}
		m_bHotHitCard=255;
		m_EndIndex = 255;
		m_StartIndex = 255;
		m_CurCardIndex = 255;
		FixCardControl();
		goto end;
		}
		}*/
		//add begin
		int iIndexStart = 255;
		if(m_bMultiSel)
		{
			iIndexStart = GetCardIndex(m_pStartPos);
		}
		else
		{
			iIndexStart = GetCardIndex(m_pMovePos);			
		}
		int iIndexEnd   = GetCardIndex(Point);
		if(iIndexStart== iIndexEnd)
		{
			if(255 != iIndexStart)
			{
				bool bUp = m_CardUpArray.GetAt(iIndexStart);
				m_CardUpArray.SetAt(iIndexStart,!bUp);
				m_bMultiSel = false;
				m_bMoveSel = false;
				ReleaseCapture();
				for(int i=0; i<m_bCardCount; i++)
				{
					m_MoveSelectCardArray.SetAt(i,false);
				}
				FixCardControl();
			}
			else if(m_bHotHitCard==HitCardTest(Point) && m_CurCardIndex!=255)
			{
				m_CardUpArray.SetAt(m_bHotHitCard, !m_CardUpArray.GetAt(m_bHotHitCard));
			}

			goto end;
		}
		//add end


		if(m_bMultiSel)
		{
			m_bMultiSel = false;
			ReleaseCapture();
			m_pEndPos = Point;
			if(m_pEndPos.x < 0)
				m_pEndPos.x = 0;
			int sindex = GetCardIndex(m_pStartPos);
			int eindex = GetCardIndex(m_pEndPos);
			bool bDiffer = false;
			bool bUp = m_CardUpArray.GetAt(sindex);
			if(sindex > eindex)
			{
				int temp = sindex;
				sindex = eindex;
				eindex = temp;
			}
			/*
			for(int i=sindex; i<=eindex; i++)
			{
			if(bUp != m_CardUpArray.GetAt(i))
			{
			bDiffer = true;
			break;
			}
			}
			if(!bDiffer)
			bUp = !bUp;
			*/
			for(int i=sindex; i<=eindex; i++)
			{
				//m_CardUpArray.SetAt(i, bUp?TRUE:FALSE);
				m_CardUpArray.SetAt(i, TRUE);
			}

			for(int i=0; i<m_bCardCount; i++)
			{
				m_MoveSelectCardArray.SetAt(i,false);
			}

			FixCardControl();
		}
		else if(m_bMoveSel)
		{
			m_bMoveSel = false;
			if (!m_bCanUp)
				m_CardUpArray.SetAt(m_bMoveFirstCard,0);
			ReleaseCapture();
			CRect rc;
			GetClientRect(&rc);
			if(Point.x < -40)
				m_CurCardIndex = 255;
			else if(Point.x <0)
			{
				Point.x = 0;
				m_CurCardIndex = -1;
			}
			else
			{
				m_CurCardIndex = Point.x/m_iCardHSpace;
			}

			if(Point.x > (rc.right+20))
				m_CurCardIndex = 255;
			if(Point.y < -20)
				m_CurCardIndex = 255;
			if(Point.y > (rc.bottom+/*20*/m_iCardHight))//2008-08-20
				m_CurCardIndex = 255;

			if (m_CurCardIndex!=255 && m_CurCardIndex >= m_bCardCount)
			{
				m_CurCardIndex = m_bCardCount-1;
			}
			if(!m_bMove && m_bHotHitCard==HitCardTest(Point) && m_CurCardIndex!=255)
			{
				m_CardUpArray.SetAt(m_bHotHitCard, !m_CardUpArray.GetAt(m_bHotHitCard));
			}	
			//拖牌结束后恢复正常状态
			if(m_bMove)
			{
				for(int i=0; i<m_bCardCount; i++)
				{
					//m_CardUpArray.SetAt(i, bUp?TRUE:FALSE);
					m_CardUpArray.SetAt(i, false);
				}
			}
			/*			else if(m_CurCardIndex!=255)
			{
			BYTE card[100];
			BYTE up[100];
			bool bUp = false;
			if(m_CurCardIndex == -1)
			bUp = m_CardUpArray.GetAt(0);
			else
			{
			bUp = m_CardUpArray.GetAt(m_CurCardIndex);
			}
			int cur = 0;

			if(m_CurCardIndex < m_StartIndex)//左移
			{

			for(int i=0; i<=m_CurCardIndex; i++)//移动块之前未动数据
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = m_CardUpArray.GetAt(i);
			cur++;
			}

			for(int i = m_CurCardIndex+1; i < m_StartIndex; i ++)//保存之前间隔升起来的牌
			{
			if(m_CardUpArray.GetAt(i))
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = bUp;
			cur++;
			}
			}

			for(int i=m_StartIndex; i<=m_EndIndex; i++)//保存升起来数据
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = bUp;
			cur++;
			}
			for(int i=m_EndIndex+1; i<m_bCardCount; i++)//移动块之后升起来的数据
			{
			if(m_CardUpArray.GetAt(i))
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = bUp;
			cur++;
			}
			}
			for(int i=m_CurCardIndex+1; i<m_StartIndex; i++)//还原移动数据之后补充数据
			{	
			if(m_CardUpArray.GetAt(i))
			continue;
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = m_CardUpArray.GetAt(i);
			cur++;
			}
			for(int i=m_EndIndex+1; i<m_bCardCount; i++)//移动块之后未动数据
			{
			if(m_CardUpArray.GetAt(i))
			continue;
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = m_CardUpArray.GetAt(i);
			cur++;
			}
			}
			else if(m_CurCardIndex > m_EndIndex)//右移
			{
			for(int i=0; i<m_StartIndex; i++)//移动块之前未升起来的数据
			{
			if(m_CardUpArray.GetAt(i))
			continue;
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = m_CardUpArray.GetAt(i);
			cur++;
			}
			for(int i=m_EndIndex+1; i<=m_CurCardIndex; i++)//移动块之后未升起来数据
			{
			if(m_CardUpArray.GetAt(i))
			continue;
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = m_CardUpArray.GetAt(i);
			cur++;
			}
			for(int i=0; i<m_StartIndex; i++)//移动块之前升起来的数据
			{
			if(m_CardUpArray.GetAt(i))
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = bUp;
			cur++;
			}
			}

			for(int i=m_StartIndex; i<=m_EndIndex; i++)//移动升起来的整块
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = bUp;
			cur++;
			}
			for(int i=m_EndIndex+1; i<=m_CurCardIndex; i++)//移动块之后升起来数据
			{
			if(m_CardUpArray.GetAt(i))
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = bUp;
			cur++;
			}
			}
			for(int i=m_CurCardIndex+1; i<m_bCardCount; i++)//移动块后未动数据
			{
			card[cur] = m_CardArray.GetAt(i);
			up[cur] = m_CardUpArray.GetAt(i);
			cur++;
			}
			}
			else
			{
			goto end;//return ;
			}
			CopyMemory(m_CardArray.GetData(),card,sizeof(BYTE)*m_bCardCount);
			CopyMemory(m_CardUpArray.GetData(),up,sizeof(BYTE)*m_bCardCount);
			}*/
			FixCardControl();
		}
	}
end:
	//BYTE bHitCard=HitCardTest(Point);
	if ((m_bUseMouse==true /*&& bHitCard != 255*/)&&(m_pHandleWnd!=NULL)) 
		m_pHandleWnd->SendMessage(IDM_LEFT_HITCARD,0,0);
	if ((m_bUseMouse==true) &&(m_pHandleWnd!=NULL))
		m_pHandleWnd->SendMessage(IDM_MOUSE_UP,0,0);
	return;
}
//鼠标消息
void CUpGradeGameCard::OnRButtonUp(UINT nFlags, CPoint point)
{
	//	if(!((CClientGameDlg*)m_pHandleWnd)->m_PlayView.m_bRightPower)
	//	{
	//		//右击出牌
	//AfxMessageBox("1");
	//		if ((m_bUseMouse==true)&&(m_pHandleWnd!=NULL)) 
	//			m_pHandleWnd->SendMessage(IDM_RIGHT_HITCARD,0,0);

	//	CClientGameDlg *p=CONTAINING_RECORD(this,CClientGameDlg,m_PlayView);
	if (NULL != m_pHandleWnd)
	{
		m_pHandleWnd->SendMessage(IDM_OUT_CARD,1,2);
	}
	//
	//右击收回功能屏蔽改为右击出牌
	/*   if (NULL != m_pHandleWnd)
	{
	((CClientGameDlg*)m_pHandleWnd)->m_PlayView.m_btOutCard.EnableWindow(0);
	if (m_bUseMouse) 
	{
	for(int i=0; i<m_bCardCount; i++)
	{
	m_CardUpArray.SetAt(i,false);
	}
	}
	FixCardControl();
	}
	*/
	//
	//	}
	//	else
	//	{
	//AfxMessageBox("1");
	//	if ((m_bUseMouse==true)&&(m_pHandleWnd!=NULL))
	//	{
	//		//AfxMessageBox("1");
	//		BYTE bHitCard=HitCardTest(point);
	//		if ((bHitCard==255))
	//		{
	//			m_bHotHitCard=255;
	//			return;
	//		}
	//		BYTE bUpCard=m_CardUpArray.GetAt(bHitCard);
	//		//发现了点击的扑克
	//		//if(bHitCard)
	//		//{
	//		//	//AfxMessageBox("1");
	//		//	BYTE HuaSe=GetCardNum(m_CardArray.GetAt(bHitCard));
	//		//	for(int i=0;i<m_bCardCount;i++)
	//		//	{
	//		//		if ((m_bShowCard==true)&&(m_CardArray.GetAt(i)!=0))
	//		//		{
	//		//			BYTE ttt=GetCardNum(m_CardArray.GetAt(i));
	//		//			if(HuaSe==ttt)
	//		//			{
	//		//				m_CardUpArray.SetAt(i,(bUpCard==TRUE)?FALSE:TRUE);
	//		//			}
	//		//		}
	//		//	}
	//			FixCardControl();
	//			/*CRect Rect;
	//			Rect.SetRect(0,0,33*m_iCardHSpace+m_iCardWidth,m_iCardHight+m_iCardUpSpace);
	//			InvalidateRect(Rect,FALSE);*/
	//			m_pHandleWnd->SendMessage(IDM_RIGHT_HITCARD,1,1);
	//		//}
	//	}
	////}
	return;
}
void CUpGradeGameCard::UnUpAllCard()
{
	if (NULL != m_pHandleWnd)
	{
		((CClientGameDlg*)m_pHandleWnd)->m_PlayView.m_btOutCard.EnableWindow(0);
		if (m_bUseMouse) 
		{
			for(int i=0; i<m_bCardCount; i++)
			{
				m_CardUpArray.SetAt(i,false);
			}
		}
		FixCardControl();
	}

}
//光标消息
BOOL CUpGradeGameCard::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message)
{
	if (m_bUseMouse==true)
	{
		SetCursor(LoadCursor(NULL, IDC_HAND));
		return TRUE;
	}
	return __super::OnSetCursor(pWnd,nHitTest,message);
}

/*
BOOL CUpGradeGameCard::PreTranslateMessage(MSG* pMsg)
{
//	m_ToolTip.RelayEvent(pMsg);
return CWnd::PreTranslateMessage(pMsg);
}*/
//鼠标消息(按左键拖动,可以将升起来的牌移动到右边)
void CUpGradeGameCard::OnMouseMove(UINT nFlags, CPoint Point)
{
	//__super::OnMouseMove(nFlags, Point);
	if (m_bUseMouse==true)
	{
		if(m_bMultiSel)
		{
			//最后一张牌是当前点的那张牌，就不接着处理zht20100518
			if (GetCardIndex(m_pEndPos) == GetCardIndex(Point))
			{
				return;
			}

			m_pEndPos = Point;
			if(m_pEndPos.x < 0)
				m_pEndPos.x = 0;

			int sindex = GetCardIndex(m_pStartPos);
			int eindex = GetCardIndex(m_pEndPos);

			if(sindex > eindex)
			{
				int temp = sindex;
				sindex = eindex;
				eindex = temp;
			}			

			for(int i=0; i<m_bCardCount; i++)
			{
				m_MoveSelectCardArray.SetAt(i,false);
			}

			for(int i=sindex; i<=eindex; i++)
			{
				m_MoveSelectCardArray.SetAt(i,true);
			}

			SetCursor(LoadCursor(NULL, IDC_CROSS));
			//Invalidate();
			FixCardControl();
			UpdateWindow();
		}
		else if(m_bMoveSel)
		{
			//			if (m_bLDown &&(abs(m_pMovePos.x - Point.x)>2 || abs(m_pMovePos.y - Point.y)>2))
			//			{
			//				//AfxMessageBox("");
			////				if (!m_MouseMove) 
			//				{
			////					m_MouseMove = true;
			////					FixCardControl();
			//				}
			////				m_pHandleWnd->SendMessage(IDM_MOVE_CARD,0,0);
			//			}
			//			else 
			//				m_MouseMove = false;
			CRect rc;
			GetClientRect(&rc);
			if(Point.x < -40)
				m_CurCardIndex = 255;
			else if(Point.x <0)
			{
				Point.x = 0;
				m_CurCardIndex = -1;
			}
			else
			{
				m_CurCardIndex = Point.x/m_iCardHSpace;
			}

			if(Point.x > (rc.right+20))
				m_CurCardIndex = 255;

			if(Point.y < -20)
				m_CurCardIndex = 255;
			if(Point.y > (rc.bottom+/*20*/m_iCardHight))//2008-08-20
				m_CurCardIndex = 255;

			if (m_CurCardIndex!=255 && m_CurCardIndex >= m_bCardCount)
			{
				m_CurCardIndex = m_bCardCount-1;
			}

			//if(m_CurCardIndex>= m_StartIndex && m_CurCardIndex<=m_EndIndex)
			//	m_CurCardIndex = 255;

			if(m_CurCardIndex == 255)
			{
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
			}
			else
			{
				m_bMove = true;
				SetCursor(LoadCursor(NULL, IDC_HAND));
				MouseMoveAjust(Point);
			}		
			Invalidate();
		}
		else if(nFlags&MK_LBUTTON)
		{
			m_bMultiSel = true;
			m_pStartPos = Point;
			BYTE bCardIndex=(BYTE)(Point.x/m_iCardHSpace);
			if(bCardIndex >=m_bCardCount)
				bCardIndex = m_bCardCount-1;
			if (bCardIndex == m_bCardCount-1)
			{
				CRect rc;
				GetClientRect(&rc);
				m_pStartPos.x = rc.right-2;
			}

			if(bCardIndex == 0)
				m_pStartPos.x = 2;

			// duanxiaohu 2010-07-15 下面判断会引起，从右到左第二张牌开始，玩家双击时会将该牌的左侧所有牌都弹起。在此注释掉
			/*if ((bCardIndex>0 && bCardIndex<m_bCardCount-1) && m_pStartPos.y>20)
			{
			m_pStartPos.x = 2;
			}*/

			SetCapture();
		}
		else
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}
	CWnd::OnMouseMove(nFlags, Point);

}

//将牌反转
BOOL CUpGradeGameCard::Convert(BYTE CardList[],int iCardCount)
{
	for(int i = 0; i< iCardCount/2 ;i++)
	{
		BYTE Card = CardList[i];
		CardList[i] = CardList[iCardCount-1];
		CardList[iCardCount-1] = Card;
	}
	return TRUE;
}

//移动牌位置,由源位置移动到目的位置
BOOL CUpGradeGameCard::ChangeIndexArray(BYTE DestIndex ,BYTE SrcIndex)
{
	BYTE MoveBlock[100]={0};
	int k = 0;
	int index = -1;						 //第一张的位置
	//绑定升起来的牌
	for(int i = SrcIndex - 1;i > 0; i --)//源左边坚起来的牌加入在前面
	{	//将升起来的牌全部保存
		if(m_CardUpArray.GetAt(i) == TRUE)
		{
			if(index == -1)
				index = i;
			MoveBlock[k++] = m_CardArray.GetAt(i);
		}
		else 
			break;
	}
	//前面无
	if(index == -1)
		index = SrcIndex;
	else
	{
		//反转
		Convert(MoveBlock,k);
	}

	MoveBlock[k++] = m_CardArray.GetAt(SrcIndex);

	for(int i = SrcIndex+1;i < m_bCardCount; i ++)//源右边坚起来的牌加入在后面
	{	//将升起来的牌全部保存
		if(m_CardUpArray.GetAt(i) == TRUE)
		{
			MoveBlock[k++] = m_CardArray.GetAt(i);
		}
		else 
			break;
	}

	//char s[100];
	//AfxMessageBox(" ");
	//for (int i=0; i< k; i++)
	//{
	//	sprintf(s,"%d:%d",i,MoveBlock[i]);
	//	WriteLog(s,1);
	//}
	//源和目的之间的值进行整块移动
	if(DestIndex > SrcIndex)//右移
	{
		for(int i = index ; i < index + k; i ++)					//空出位置
		{
			if(i + k  >= m_bCardCount) 
				break;
			m_CardArray.SetAt(i,m_CardArray.GetAt(i + k ));
			m_CardUpArray.SetAt(i,m_CardUpArray.GetAt(i + k ));
		}
		for(int i = DestIndex - k + 1; i <= DestIndex; i ++)				//将升起来的牌加入
		{
			if(i - (DestIndex - k + 1) < 0 ) 
				break;
			m_CardArray.SetAt(i,MoveBlock[i - (DestIndex - k + 1)]);
			m_CardUpArray.SetAt(i,1);
		}
	}
	else if (DestIndex < SrcIndex)//左移
	{
		for(int i = index + k - 1 ; i > index - 1 ;i--)				//空出位置
		{
			if( i - k < 0)
				break;
			m_CardArray.SetAt(i,m_CardArray.GetAt(i - k));
			m_CardUpArray.SetAt(i,m_CardUpArray.GetAt(i - k));
		}
		for(int i = DestIndex; i < DestIndex + k ; i ++)			//将升起来的牌加入
		{
			if(i - DestIndex < 0)
				break;
			m_CardArray.SetAt(i,MoveBlock[i - DestIndex]);
			m_CardUpArray.SetAt(i,1);
		}
	}
	//重绘
	FixCardControl();
	if ((m_bUseMouse==true /*&& bHitCard != 255*/)&&(m_pHandleWnd!=NULL)) 
		m_pHandleWnd->SendMessage(IDM_LEFT_HITCARD,0,0);
	return TRUE;
}

//移动牌位置,由源位置移动到目的位置
BOOL CUpGradeGameCard::ChangeIndex(BYTE DestIndex ,BYTE SrcIndex)
{
	BYTE temp = m_CardArray.GetAt(SrcIndex);
	BYTE tempup = m_CardUpArray.GetAt(SrcIndex);

	//源和目的之间的值进行整块移动
	if(DestIndex > SrcIndex)								//右移
	{
		for(int i = SrcIndex ; i < DestIndex ;i++)
		{
			if(i + 1 >= m_bCardCount )
				break;
			m_CardArray.SetAt(i,m_CardArray.GetAt(i + 1));
			m_CardUpArray.SetAt(i,m_CardUpArray.GetAt(i + 1));
		}
	}else if (DestIndex < SrcIndex)							//左移
	{
		for(int i = SrcIndex ; i > DestIndex ;i--)
		{
			if(i - 1 < 0)
				break;
			m_CardArray.SetAt(i,m_CardArray.GetAt(i - 1));
			m_CardUpArray.SetAt(i,m_CardUpArray.GetAt(i - 1));
		}
	}
	m_CardArray.SetAt(DestIndex,temp);
	m_CardUpArray.SetAt(DestIndex,tempup);

	//重绘
	FixCardControl();
	return TRUE;
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
	return FriendCount;
}
//设置调用图片
void CUpGradeGameCard::SetCardImage()
{
	TCHAR path[MAX_PATH]={0};
	switch(GetCardStyle())
	{
	case 2:
	case IMAGE_SMALL:
	//	wsprintf(path,TEXT("%s\\game_Card_SMALL.bmp"), SKIN_CARD);
	//	m_CardPic[2].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	//	wsprintf(path,TEXT("%s\\game_Card_SMALL_back.bmp"), SKIN_CARD);
	//	m_CardPic[3].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	//	//m_CardPic[2].SetLoadInfo("image\\card\\CardSkin\\game_Card_SMALL.bmp",CGameImageLink::m_bAutoLock);
	//	//m_CardPic[3].SetLoadInfo("image\\card\\CardSkin\\game_Card_SMALL_back.bmp",CGameImageLink::m_bAutoLock);
	//	break;
	//case IMAGE_VERY_SMALL:
	//	wsprintf(path,TEXT("%s\\very_small.bmp"), SKIN_CARD);
	//	m_CardPic[0].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	//	//m_CardPic[0].SetLoadInfo("image\\card\\very_small.bmp",CGameImageLink::m_bAutoLock);
	//	//m_CardPic[1].SetLoadInfo("image\\card\\very_small.bmp",CGameImageLink::m_bAutoLock);
	//	break;
	default:
		if(1)//GetSystemMetrics(SM_CXSCREEN)>=1024)
		{
			wsprintf(path,TEXT("%s\\game_Card.bmp"), SKIN_CARD);
			m_CardPic[0].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

			wsprintf(path,TEXT("%s\\game_Card_back.bmp"), SKIN_CARD);
			m_CardPic[1].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
			//m_CardPic[0].SetLoadInfo("image\\card\\CardSkin\\game_Card.bmp",CGameImageLink::m_bAutoLock);
			//m_CardPic[1].SetLoadInfo("image\\card\\CardSkin\\game_Card_back.bmp",CGameImageLink::m_bAutoLock);
			//选择的牌图
			wsprintf(path,TEXT("%s\\game_Card_SELECT.bmp"), SKIN_CARD);
			m_CardPic[4].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

			wsprintf(path,TEXT("%s\\game_CARD_BACK_SELECT.bmp"), SKIN_CARD);
			m_CardPic[5].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
		}
		//else
		//{
		//	wsprintf(path,TEXT("%s\\game_Card_800.bmp"), SKIN_CARD);
		//	m_CardPic[0].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

		//	wsprintf(path,TEXT("%s\\game_Card_800_back.bmp"), SKIN_CARD);
		//	m_CardPic[1].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

		//	//选择的牌图
		//	wsprintf(path,TEXT("%s\\game_Card_800_SELECT.bmp"), SKIN_CARD);
		//	m_CardPic[4].SetLoadInfo(path,CGameImageLink::m_bAutoLock);

		//	wsprintf(path,TEXT("%s\\game_Card_800_back_SELECT.bmp"), SKIN_CARD);
		//	m_CardPic[5].SetLoadInfo(path,CGameImageLink::m_bAutoLock);
		//}
		break;
	}
	wsprintf(path,TEXT(".\\image\\cardnum.bmp"));
	m_Num.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,TEXT(".\\image\\BackColorOnly.bmp"));
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

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
			m_iCardHight=m_CardPic[1].GetHeight();
			m_iCardWidth=m_CardPic[1].GetWidth()/3;	
			m_iCardHSpace=m_iCardWidth/5;
		}
		else
		{
			m_iCardHight=73;
			m_iCardWidth=54;
		}
	}
	return ;
}

// 画半透明框
void CUpGradeGameCard::DrawTransparent(HDC destdc, CRect &rc, COLORREF color, int Alpha)
{
	int temp;
	if(rc.left > rc.right)
	{
		temp = rc.left;
		rc.left = rc.right;
		rc.right = temp;
	}
	if(rc.top > rc.bottom)
	{
		temp = rc.top;
		rc.top = rc.bottom;
		rc.bottom = temp;
	}
	int cx = rc.Width();
	int cy = rc.Height();
	int dx = rc.left;
	int dy = rc.top;
	HDC dc;
	dc = CreateCompatibleDC(destdc);
	HBRUSH brush = CreateSolidBrush(TRANSPARENT);
	HBITMAP bitmap;
	bitmap = CreateCompatibleBitmap(destdc,cx,cy);
	SelectObject(dc,bitmap);
	//StretchBlt(dc,0,0,cx,cy,destdc,dx,dy,cx,cy,SRCCOPY);
	//::TransparentBlt(dc,0,0,cx,cy,srcdc,sx,sy,cx,cy,crTransparent);
	CRect rect(0, 0, cx, cy);
	::FillRect(dc, &rect, brush);

	BLENDFUNCTION bl;
	bl.BlendOp = AC_SRC_OVER;
	bl.BlendFlags = 0;
	bl.SourceConstantAlpha = Alpha;
	bl.AlphaFormat = 0; 
	AlphaBlend(destdc,dx,dy,cx,cy,dc,0,0,cx,cy,bl);
	DeleteObject(bitmap);
	DeleteDC(dc);
	DeleteObject(brush);
}

// 得到牌index
BYTE CUpGradeGameCard::GetCardIndex(CPoint &Point)
{
	BYTE index = HitCardTest(Point);
	if(index == 255)
	{
		index=(BYTE)(Point.x/m_iCardHSpace);
		if (index!=255 && index>=m_bCardCount)
			index=m_bCardCount-1;
	}
	return index;
}
////处理移动牌
void CUpGradeGameCard::MouseMoveAjust(CPoint Point)
{
	if(m_bMoveSel && m_CurCardIndex>=0 && m_CurCardIndex<m_bCardCount && m_CurCardIndex>=0 && m_CurCardIndex!=m_bHotHitCard)
	{

		BYTE card[100];
		BYTE up[100];

		int cur = 0;

		if(m_CurCardIndex==0)//鼠标在第一个牌位置时的处理
		{

			//构造中间部分
			for(int i=0;i<m_bCardCount;i++)
			{
				if(m_CardUpArray.GetAt(i))
				{
					card[cur] = m_CardArray.GetAt(i);
					up[cur] = m_CardUpArray.GetAt(i);
					cur++;
				}
			}
			//构造后面部分
			for(int i=0;i<m_bCardCount;i++)
			{
				if(!m_CardUpArray.GetAt(i))
				{
					card[cur] = m_CardArray.GetAt(i);
					up[cur] = m_CardUpArray.GetAt(i);
					cur++;
				}
			}

		}
		else if(m_CurCardIndex==(m_bCardCount-1))//鼠标在最后一个牌位置时的处理
		{

			//构造后面部分
			for(int i=0;i<m_bCardCount;i++)
			{
				if(!m_CardUpArray.GetAt(i))
				{
					card[cur] = m_CardArray.GetAt(i);
					up[cur] = m_CardUpArray.GetAt(i);
					cur++;
				}
			}
			//构造中间部分
			for(int i=0;i<m_bCardCount;i++)
			{
				if(m_CardUpArray.GetAt(i))
				{
					card[cur] = m_CardArray.GetAt(i);
					up[cur] = m_CardUpArray.GetAt(i);
					cur++;
				}
			}
		}
		else //鼠标在一般位置时的处理
		{


			if(m_CurCardIndex>m_bHotHitCard)
			{
				//左移动
				//构造前部分
				for(int i=0;i<=m_CurCardIndex;i++)
				{
					if(!m_CardUpArray.GetAt(i))
					{
						card[cur] = m_CardArray.GetAt(i);
						up[cur] = m_CardUpArray.GetAt(i);
						cur++;
					}
				}
				//构造中间部分
				for(int i=0;i<m_bCardCount;i++)
				{
					if(m_CardUpArray.GetAt(i))
					{
						card[cur] = m_CardArray.GetAt(i);
						up[cur] = m_CardUpArray.GetAt(i);
						cur++;
					}
				}
				//构造后面部分
				for(int i=m_CurCardIndex+1;i<m_bCardCount;i++)
				{
					if(!m_CardUpArray.GetAt(i))
					{
						card[cur] = m_CardArray.GetAt(i);
						up[cur] = m_CardUpArray.GetAt(i);
						cur++;
					}
				}
			}
			else if(m_CurCardIndex<m_bHotHitCard)
			{
				//右移动
				//构造前部分
				for(int i=0;i<m_CurCardIndex;i++)
				{
					if(!m_CardUpArray.GetAt(i))
					{
						card[cur] = m_CardArray.GetAt(i);
						up[cur] = m_CardUpArray.GetAt(i);
						cur++;
					}
				}
				//构造中间部分
				for(int i=0;i<m_bCardCount;i++)
				{
					if(m_CardUpArray.GetAt(i))
					{
						card[cur] = m_CardArray.GetAt(i);
						up[cur] = m_CardUpArray.GetAt(i);
						cur++;
					}
				}
				//构造后面部分
				for(int i=m_CurCardIndex;i<m_bCardCount;i++)
				{
					if(!m_CardUpArray.GetAt(i))
					{
						card[cur] = m_CardArray.GetAt(i);
						up[cur] = m_CardUpArray.GetAt(i);
						cur++;
					}
				}
			}
		}

		//计算升牌开始位置
		m_StartIndex=m_bHotHitCard;
		for(int i=0; i<m_bCardCount; i++)
		{
			if(up[i])
			{
				m_StartIndex = i;
				break;
			}
		}

		//计算升牌结束位置
		for(int i=m_StartIndex+1; i<m_bCardCount; i++)
		{
			if(up[i])
			{
				m_EndIndex = i;
				continue;
			}
		}

		//设置激活的牌，更新牌数据，刷新显示
		m_bHotHitCard=m_CurCardIndex;
		CopyMemory(m_CardArray.GetData(),card,sizeof(BYTE)*m_bCardCount);
		CopyMemory(m_CardUpArray.GetData(),up,sizeof(BYTE)*m_bCardCount);
		FixCardControl();
		UpdateWindow();
	}	
	else
	{
		return ;
	}

	return;
}

BOOL CUpGradeGameCard::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_ToolTip.RelayEvent(pMsg);
	return CWnd::PreTranslateMessage(pMsg);
}
