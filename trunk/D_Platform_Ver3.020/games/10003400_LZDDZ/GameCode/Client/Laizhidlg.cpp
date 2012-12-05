#include "StdAfx.h"
#include "LaiZhiDlg.h"
#include "Resource.h"
#include "ClientView.h"
#include ".\clientgamedlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CLaiZhiDlg, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_NEXT_GAME, OnHitNext)
	ON_BN_CLICKED(IDC_CANCEL_GAME, OnHitCancel)
END_MESSAGE_MAP()

//构造函数
CLaiZhiDlg::CLaiZhiDlg(void)// :CGameFaceGo(CLaiZhiDlg::IDD)
{
	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));


	//AfxSetResourceHandle(GetModuleHandle(NULL));
}
//
int CLaiZhiDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	TCHAR szName[MAX_PATH];

	wsprintf(szName,TEXT(".\\image\\%s\\laizi2.bmp"),GET_SKIN_FOLDER(szTempStr));
	m_bk.SetLoadInfo(szName,TRUE);

	wsprintf(szName, TEXT(".\\image\\%s\\GAME_CARD.bmp"), SKIN_CARD);//扑克牌
	m_OptionalCardsType.SetLoadInfo(szName, TRUE);

	wsprintf(szName, TEXT(".\\image\\%s\\GAME_CARD_LaiZi.bmp"), SKIN_CARD);//癞子牌
	m_LaiZiCard.SetLoadInfo(szName, TRUE);

	m_btNext.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW|WS_VISIBLE,CRect(0,0,0,0),this,IDC_NEXT_GAME);
	m_btCancel.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_DISABLED|BS_OWNERDRAW|WS_VISIBLE,CRect(0,0,0,0),this,IDC_CANCEL_GAME);

	CGameImage bk;
	HRGN hRgn;
	wsprintf(szName,TEXT(".\\image\\%s\\xiayiye_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//下一页按钮
	m_btNext.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btNext.SetWindowRgn(hRgn,true);

	wsprintf(szName,TEXT(".\\image\\%s\\cancel_bt.bmp"),GET_SKIN_FOLDER(szTempStr));			//取消按钮
	m_btCancel.LoadButtonBitmap(szName,false);	
	bk.SetLoadInfo(szName,true);
	hRgn=AFCBmpToRgn(bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
		m_btCancel.SetWindowRgn(hRgn,true);

	CRect ContronRect;
	m_btNext.GetClientRect(&ContronRect);
	
	m_btNext.MoveWindow(50,170,ContronRect.Width(),ContronRect.Height());
	m_btCancel.MoveWindow(180,170,ContronRect.Width(),ContronRect.Height());
	m_btNext.ShowWindow(1);
	m_btNext.EnableWindow(1);
	m_btCancel.EnableWindow(1);
	

	m_BtnRect0,m_BtnRect1,m_BtnRect2,m_BtnRect3;	//矩形框
	m_BtnRect0.left = 24;
	m_BtnRect0.right = 270;
	m_BtnRect0.top=50;
	m_BtnRect0.bottom =73;

	m_BtnRect1.left = 24;
	m_BtnRect1.right = 270;
	m_BtnRect1.top=80;
	m_BtnRect1.bottom =103;

	m_BtnRect2.left = 24;
	m_BtnRect2.right = 270;
	m_BtnRect2.top=110;
	m_BtnRect2.bottom =133;

	m_BtnRect3.left = 24;
	m_BtnRect3.right = 270;
	m_BtnRect3.top=140;
	m_BtnRect3.bottom =163;

	CRect ClientRect;
	GetClientRect(&ClientRect);
	CGameImageHelper	help(&m_bk);
	this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	hRgn=AFCBmpToRgn(help,RGB(255,0,255),RGB(1,0,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,help.GetWidth(),help.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
	}


	return 0;
}
//析构函数
CLaiZhiDlg::~CLaiZhiDlg(void)
{
}

//重画函数
void CLaiZhiDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect ClientRect;
	GetClientRect(&ClientRect);

	CGameImageHelper	help(&m_bk);//画背景
	help.BitBlt(dc.GetSafeHdc(),0,0);
	CGameImageHelper helpOptionalCardsType(&m_OptionalCardsType);//画可供选择的牌型
	CGameImageHelper helpOptionalCardsTypeForLaiZi(&m_LaiZiCard);//画可供选择的牌型(专画癞子)
	int x=24;
	int y=ClientRect.Height()/2 - 28;

	CRect rect;
	CFont Font;
	//Font.CreateFont(10,10,0,300,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	Font.CreateFont(14,0,0,0,0,0,0,0,134,3,2,1,2,TEXT("宋体"));
	CFont *OldFont=dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255,255,255));
	dc.SetBkMode(TRANSPARENT);
    CString StrBuf;


	for (int i=m_ThisCount; i<m_Replace.ListCount&&i<(m_ThisCount+4); i++)
	{
		StrBuf = "";
		GetString(m_Replace.ReplaceList[i], m_Replace.CardCount, StrBuf);
		rect.left=ClientRect.Width() - 80;
		rect.right=rect.left+70;
		rect.top=50+(i-m_ThisCount)*28;
		rect.bottom=rect.top+33;
		dc.DrawText(StrBuf,lstrlen(StrBuf),&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		
		
		for (int j=0; j<m_Replace.CardCount; j++)//画可供选择的牌型
		{
			if (GetCardNum(m_Replace.ReplaceList[i][j]) == GetCardNum(((CClientPlayView*)GetParent())->m_bLaiCardList[0]))//当是癞子牌
			{
				helpOptionalCardsTypeForLaiZi.BitBlt(dc.GetSafeHdc(), 25+j*15, rect.top, 15, 
					25,GetCardXPos(m_Replace.ReplaceList[i][j])*70, GetCardYPos(m_Replace.ReplaceList[i][j])*95, SRCCOPY);
			}
			else
			{
				helpOptionalCardsType.BitBlt(dc.GetSafeHdc(), 25+j*15, rect.top, 15, 
					25,GetCardXPos(m_Replace.ReplaceList[i][j])*70, GetCardYPos(m_Replace.ReplaceList[i][j])*95, SRCCOPY);
				if (4 == m_Replace.CardCount && 3 == j)
				{
					helpOptionalCardsTypeForLaiZi.BitBlt(dc.GetSafeHdc(), 25+j*15, rect.top, 15, 
						25,GetCardXPos(m_Replace.ReplaceList[i][j])*70, GetCardYPos(m_Replace.ReplaceList[i][j])*95, SRCCOPY);//将最后一个标为软炸
				}
			}

		}
	}
	dc.DeleteDC();
	return ;
}

//自动调整大小
void CLaiZhiDlg::AutoSize(int xValue,int yValue)
{
	MoveWindow(xValue,yValue,m_bk.GetWidth(),m_bk.GetHeight());
	Invalidate();
	UpdateWindow();
}


void CLaiZhiDlg::SetMessage(ReplaceStruct replace, bool PassShow, bool bFlag)
{
	
	m_Replace=replace;
	m_ThisCount = 0;
	m_bPassShow = !PassShow;
	m_btNext.EnableWindow(1);
	m_btCancel.EnableWindow(1);
	if (4 > m_Replace.ListCount)
	{
		m_btNext.EnableWindow(FALSE);
	}
	if (bFlag)
		OnSelect(0);
	UpdateWindow();
	return;
}

void CLaiZhiDlg::OnLButtonDown(UINT nFags,CPoint point)
{
	if(PtInRect(&m_BtnRect0,point))
	{
		OnSelect(0);
		return ;
	}
	if(PtInRect(&m_BtnRect1,point))
	{
		if (m_Replace.ListCount <= 1) 
			return;
		OnSelect(1);
		return ;
	}
	if(PtInRect(&m_BtnRect2,point))
	{
		if (m_Replace.ListCount <= 2) 
			return;
		OnSelect(2);
		return ;
	}
	if(PtInRect(&m_BtnRect3,point))
	{
		if (m_Replace.ListCount <= 3) 
			return;
		OnSelect(3);
		return ;
	}
	//PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	return ;
}
//得到字符
BOOL CLaiZhiDlg::GetString(BYTE CardList[], int CardCount, CString & str)
{
	CString strTemp;
	BYTE tempUpCard[20] = {0};
	BYTE iCount = ((CClientPlayView*)GetParent())->m_MeCard.GetUpCard(tempUpCard);
	BYTE byteTempLaiZiValue = GetCardNum(((CClientPlayView*)GetParent())->m_bLaiCardList[0]);//癞子的牌点值
	
	CString temp;
	temp= "三带一";
	int iTemp;//临时的数组下标
	if (4 == CardCount)
	{
			BYTE byteTempArr[20] = {0};
			for (int i=0; i<CardCount; i++)
			{
				BYTE byteValue = GetCardNum(CardList[i]);//临时的牌点值
				for (int k=0; k<20; k++)
				{
					if (0 != tempUpCard[k])
					{
						if ((byteTempLaiZiValue == GetCardNum(tempUpCard[k])) && (byteValue == byteTempLaiZiValue))
						{
							CardList[i] = tempUpCard[k];
						}
					}
				}
				strTemp.Format("GetHuaKind:%d, CardList[i]:%d", GetHuaKind(CardList[i]), CardList[i]);
				//OutputDebugString(strTemp);

				byteTempArr[GetCardNum(CardList[i])]++;  //记录相同牌点的牌有几个
			}

			//OutputDebugString("-------------------------");				 

			for (int i=0; i<20; i++)
			{
				if (byteTempArr[i] == 4)//软炸
				{
					temp= "软炸";
                    CardList[0] = 48 - GetHuaKind(CardList[0]) + CardList[0];
                    CardList[1] = CardList[0] - 16;
					CardList[2] = CardList[1] - 16;
					CardList[3] = CardList[2] - 16;
				}
				if (byteTempArr[i] == 3)//三带一
				{
                     for (int j=0; j<4; j++)
                     {
						 if (GetCardNum(CardList[j]) != i)
						 {
							 CardList[3] = CardList[j];
						 }
						 else
						 {
                              iTemp = j;
						 }
                     }
                     CardList[0] = 48 - GetHuaKind(CardList[iTemp]) + CardList[iTemp];
					 CardList[1] = CardList[0] - 16;
					 CardList[2] = CardList[1] - 16;
				}
			}
	}
	else
	{
		temp = "非炸牌型";
	}
	
	str += temp;
 
	return TRUE;
}


//下一页
void CLaiZhiDlg::OnHitNext()
{
	
	m_ThisCount+=4;
	Invalidate();
	if ((m_ThisCount+4) >= m_Replace.ListCount)
	{
		m_btNext.EnableWindow(0);
	}
}
//取消
void CLaiZhiDlg::OnHitCancel()
{
	ShowWindow(SW_HIDE);
	/*((CClientPlayView*)GetParent())->m_btOutCard.ShowWindow(SW_SHOW);
	((CClientPlayView*)GetParent())->m_btPass.ShowWindow(m_bPassShow);
	((CClientPlayView*)GetParent())->m_btCue.ShowWindow(SW_SHOW);
	*/
	
	
}

void CLaiZhiDlg::OnSelect(int Id)
{
	ShowWindow(SW_HIDE);
	int Index = Id + m_ThisCount;

	((CClientGameDlg*)GetParent()->GetParent())->SendMessage(IDM_SELECT_NUM,Index,Index);
	((CClientPlayView*)GetParent())->m_btOutCard.ShowWindow(SW_HIDE);
	((CClientPlayView*)GetParent())->m_btPass.ShowWindow(SW_HIDE);
	((CClientPlayView*)GetParent())->m_btCue.ShowWindow(SW_HIDE);
	
}
