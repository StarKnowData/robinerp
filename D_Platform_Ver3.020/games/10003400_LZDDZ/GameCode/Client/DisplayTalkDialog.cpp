// DisplayTalkDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DisplayTalkDialog.h"
#include "ClientGameDlg.h"

// CDisplayTalkDialog dialog

IMPLEMENT_DYNAMIC(CDisplayTalkDialog, CDialog)

CDisplayTalkDialog::CDisplayTalkDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayTalkDialog::IDD, pParent)
{
	m_strCurrentText.Empty();

    m_nJianGe = 20;
	m_bPreIsText = FALSE;
	m_bIsFirst = FALSE;
	m_nLineJianGe = 2;
	m_nTextToImage = 4;
	m_bWriteDC = TRUE;
}

CDisplayTalkDialog::~CDisplayTalkDialog()
{
}

void CDisplayTalkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
 }


BEGIN_MESSAGE_MAP(CDisplayTalkDialog, CDialog)
  	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()
 
BOOL CDisplayTalkDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR name[MAX_PATH];
	wsprintf(name,TEXT(".\\image\\%s\\usertalk%d.bmp"),GET_SKIN_FOLDER(szTempStr),m_viewid); //囧
	m_img.SetLoadInfo(name,true);
	CGameImageHelper ImageHandle(&m_img);
	HRGN hRgn=AFCBmpToRgn(ImageHandle,RGB(255,0,255),RGB(1,1,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),SWP_NOMOVE);
 		SetWindowRgn(hRgn,TRUE);
	}
	::SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	GetClientRect(&m_rectClient);

 	m_font.CreateFont(-13,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));  //------本对话框专用字体
	m_crFont = RGB(255,255,128);                                               //------字体的颜色    
	
	TCHAR* pMsg = TEXT("测试");
	GetDC()->SelectObject(&m_font);
	m_fontHeight = GetDC()->GetTextExtent(pMsg,lstrlen(pMsg)).cy; 

 	return FALSE;  // return TRUE unless you set the focus to a control
 }

void CDisplayTalkDialog::DisplayTalkText(TCHAR * szCharString)
{ 
 	//-------------------------窗体透明----------------------
	HINSTANCE hInst = LoadLibrary(TEXT("User32.DLL"));
	if(hInst != NULL) 
	{ 
	typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		fun=(MYFUNC)GetProcAddress(hInst, TEXT("SetLayeredWindowAttributes"));
		m_Tran=160;
		if(fun)fun(this->GetSafeHwnd(),0,m_Tran,2); 
		FreeLibrary(hInst); 
	}
	m_msg=szCharString;
	KillTimer(1);
	KillTimer(2);
	SetTimer(1,3000,NULL);
	m_bWriteDC=true;
	ShowWindow(SW_SHOW);
}

BOOL CDisplayTalkDialog::OnEraseBkgnd(CDC* pDC)
{
	//return CDialog::OnEraseBkgnd(pDC);
	if(m_viewid==-1)
		return true;
 	CGameImageHelper help(&m_img);
	CDC srcdc;
	srcdc.CreateCompatibleDC(pDC);
	srcdc.SelectObject(help);
	::TransparentBlt(pDC->GetSafeHdc(),0,0,help.GetWidth(),help.GetHeight(),srcdc,0,0,help.GetWidth(),help.GetHeight(),srcdc.GetPixel(0,0));
	srcdc.DeleteDC();
	return TRUE;
 }

CTrueItem * CDisplayTalkDialog::TranslateChar(TCHAR * szCharString, int iCharLength, int & iPassCharCount)
{
	CTrueItem * pItem=NULL;
	int iItemLength=0,iInputLenth=0;
	CGameTalkText gameTalk;
 	for (int i=0;i<iCharLength-2;i++)
	{
		if ((szCharString[i]==TEXT('/'))&&(szCharString[i+1]==TEXT(':')))
		{
			for (int j=0;j<MAX_EXPRESS_ITEM;j++)
			{
 				pItem = &gameTalk.m_ExpreesionItem[j];
				iInputLenth=iCharLength-i;
				iItemLength=pItem->m_uTranceLength;  //解释长度
				if (iItemLength>iInputLenth) return NULL;
				int k=2;
				for (k=2;k<iItemLength;k++)
				{
					if ((szCharString[i+k]!=pItem->m_szTrancelate[k])&&(szCharString[i+k]!=(pItem->m_szTrancelate[k]+32))) 
						break;
				}
				if (k==iItemLength) 
				{
					iPassCharCount=i;
					return pItem;
				}
			}
			i++;
		}
	}
	return NULL;
}

void CDisplayTalkDialog::InsertCharToDC(const TCHAR * szMsg)
{  
	CDC* pDC = GetDC();
 	if(m_bWriteDC)
	{
		pDC->SetTextColor( m_crFont );
		pDC->SelectObject(&m_font);
		int xOffset = pDC->GetTextExtent(szMsg,lstrlen(szMsg)).cx; 
		if( IsNewLine(szMsg) )
		{
            int numCanDisplay = ThisLineContainChar(szMsg);
		    if(numCanDisplay != -1)  //返回值有效,则先显示前N个字符
			{
				//------------先显示前   numCanDisplay  能显出来的
				TCHAR szTemp[500];
				TCHAR* pTemp=szTemp;
				CopyNumChar(szMsg,1,numCanDisplay,pTemp);
 				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextAlign(TA_LEFT);
				CRect rectTemp;
				rectTemp = m_rectCurrentLine;
				rectTemp.left = m_ptCurrent.x;
				//if(m_bIsFirst) m_bIsFirst = FALSE;
   				pDC->DrawText(pTemp,numCanDisplay,&rectTemp,DT_LEFT|DT_VCENTER|DT_NOCLIP);  
				//------------换行重置坐标，然后将第 numCanDisplay 个字符显后的再显示出来
                CopyNumChar(szMsg,numCanDisplay+1,lstrlen(szMsg),pTemp);
				m_ptCurrent.x = m_rectCurrentLine.left;
				m_rectCurrentLine.top = m_rectCurrentLine.top+m_fontHeight+m_nLineJianGe;	//距上一行的行距为2
				m_rectCurrentLine.bottom = m_rectCurrentLine.top+m_fontHeight;

				if( m_rectCurrentLine.top > m_rectClient.bottom-m_nJianGe-m_fontHeight)
				{
				//	DisplayOmit();           //显示省略号
					m_bWriteDC = FALSE;
					return;
				}
 				InsertCharToDC(pTemp);
                return;

			}
		}
		if( m_rectCurrentLine.top > m_rectClient.bottom-m_nJianGe-m_fontHeight)
		{
			//DisplayOmit();           //显示省略号
			m_bWriteDC = FALSE;
			return;
		}

		CRect rectTemp;
		rectTemp = m_rectCurrentLine;
		rectTemp.left = m_ptCurrent.x; 
 		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextAlign(TA_LEFT);
  		pDC->DrawText(szMsg,lstrlen(szMsg),&rectTemp,DT_LEFT|DT_VCENTER|DT_NOCLIP); 
		m_ptCurrent.x = m_ptCurrent.x + xOffset;

		if(m_bIsFirst) m_bIsFirst = FALSE;
		m_bPreIsText = TRUE;       //表示已经输出过文字
		return;
	}
 }

void CDisplayTalkDialog::InsertBitmapToDC(HBITMAP hBitmap)
{
	CDC* pDC = GetDC();
	if(m_bWriteDC)
	{
 		BITMAP infoBmp;
 		::GetObject(hBitmap,sizeof(BITMAP),&infoBmp);

		CDC memDC,*pDC;
		pDC = GetDC();
		memDC.CreateCompatibleDC(pDC);
 
	   if(m_ptCurrent.x + infoBmp.bmWidth > m_rectCurrentLine.right)  //宽度如果容不了,另起一行
		{
			m_ptCurrent.x = m_rectCurrentLine.left;
			m_rectCurrentLine.top =  m_rectCurrentLine.top+m_fontHeight+m_nLineJianGe;
			m_rectCurrentLine.bottom = m_rectCurrentLine.top + m_fontHeight;
		}
		if(m_rectCurrentLine.top > m_rectClient.bottom-m_nJianGe-m_fontHeight)  //若到达最底端，则不显示
		{
			//DisplayOmit();           //显示省略号
			m_bWriteDC = FALSE;
			return;
		}
		
		if((m_bPreIsText)&&(!m_bIsFirst))
 			m_ptCurrent.x += m_nTextToImage;          //若前面是文字，则图片挪动一段距离
		if((!m_bPreIsText)&&(!m_bIsFirst))
			m_ptCurrent.x -= m_nTextToImage;          //若前面是图片，且本次输出不为第一次，回退多余的坐标
		if(m_bIsFirst)
			m_bIsFirst = FALSE;
 		m_ptCurrent.y = m_rectCurrentLine.top-4;     //定位y点为行rect的top值,此"4"值可调
        TransparentBltBitmap(hBitmap,m_ptCurrent,RGB(255,0,255));
        
  		m_ptCurrent.x += infoBmp.bmWidth+m_nTextToImage;  //先假设其后的输入为文字，于是将当前点坐标挪动一段距离
		m_bPreIsText = FALSE;   //表示曾经输入过图片
		memDC.DeleteDC();
	}
}

HBITMAP CDisplayTalkDialog::CopyBitmap(HBITMAP hSourceHbitmap)
{
	  CDC sourceDC;   
	  CDC destDC;   
	  sourceDC.CreateCompatibleDC(NULL);   
	  destDC.CreateCompatibleDC(NULL);   
	  //The   bitmap   information.   
	  BITMAP   bm = {0};   
	  //Get   the   bitmap   information.   
	  ::GetObject(hSourceHbitmap,   sizeof(bm),   &bm);   
	  //   Create   a   bitmap   to   hold   the   result   
	  HBITMAP   hbmResult   =   ::CreateCompatibleBitmap(CClientDC(NULL),   bm.bmWidth,   bm.bmHeight);   	    
	  HBITMAP   hbmOldSource   =   (HBITMAP)::SelectObject(   sourceDC.m_hDC,   hSourceHbitmap);   
	  HBITMAP   hbmOldDest   =   (HBITMAP)::SelectObject(   destDC.m_hDC,   hbmResult   );   
	  destDC.BitBlt(0,0,bm.bmWidth,   bm.bmHeight,   &sourceDC,   0,   0,   SRCCOPY   );   
	    
	  //Restore   DCs   
	  ::SelectObject(   sourceDC.m_hDC,   hbmOldSource   );   
	  ::SelectObject(   destDC.m_hDC,   hbmOldDest   );   
	  ::DeleteObject(sourceDC.m_hDC);   
	  ::DeleteObject(destDC.m_hDC);   	    
	  return   hbmResult;   
}

void CDisplayTalkDialog::OnTimer(UINT_PTR nIDEvent)
{
	if(1==nIDEvent)
	{//开始隐藏窗口
		KillTimer(nIDEvent);
		SetTimer(2,50,NULL);
	}
	else if(2==nIDEvent)
	{//慢慢淡化
		m_Tran-=10;
		if(m_Tran<=0)
		{
			KillTimer(2);
			ShowWindow(SW_HIDE);
			return ;
		}
		HINSTANCE hInst = LoadLibrary(TEXT("User32.DLL"));
		if(hInst != NULL) 
		{ 
			typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
			MYFUNC fun = NULL;
			//取得SetLayeredWindowAttributes函数指针 
			fun=(MYFUNC)GetProcAddress(hInst,TEXT( "SetLayeredWindowAttributes"));
			if(fun)fun(this->GetSafeHwnd(),0,m_Tran,2); 
			FreeLibrary(hInst); 
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void  CDisplayTalkDialog::TransparentBltBitmap(HBITMAP hBitmap,CPoint ptCurrent,COLORREF crTrans)
{
	HBITMAP  hNewBitmap;
	hNewBitmap = CopyBitmap(hBitmap);

	CDC*  pActiveDC,*pMaskDC,*pDC;
 	pDC = GetDC();
 	BITMAP infoBmp;
	::GetObject(hNewBitmap,sizeof(BITMAP),&infoBmp);

	 pActiveDC = new CDC();//装载了位图的DC
	 pActiveDC->CreateCompatibleDC(pDC);
	 pActiveDC->SelectObject(hNewBitmap);
	 pActiveDC->SetBkColor( crTrans );

	 pMaskDC = new CDC();  //掩码DC
	 pMaskDC->CreateCompatibleDC(pDC);
	 CBitmap bmpMask;
	 bmpMask.CreateBitmap(infoBmp.bmWidth,infoBmp.bmHeight, 1, 1, NULL);     //单色位图
	 CBitmap * pOldMaskBmp = pMaskDC->SelectObject(&bmpMask);
	 pMaskDC->BitBlt(0,0,infoBmp.bmWidth,infoBmp.bmHeight,pActiveDC,0,0,SRCCOPY);

 	 //-----------------------(2)透明化处理-----------------------------------
	 pDC->BitBlt(ptCurrent.x,ptCurrent.y,infoBmp.bmWidth,infoBmp.bmHeight,pActiveDC,0, 0, SRCINVERT);
	 pDC->BitBlt(ptCurrent.x,ptCurrent.y,infoBmp.bmWidth,infoBmp.bmHeight, pMaskDC,0, 0, SRCAND);
	 pDC->BitBlt(ptCurrent.x,ptCurrent.y,infoBmp.bmWidth,infoBmp.bmHeight, pActiveDC, 0, 0, SRCINVERT);
	 //-------------------------指针回收-------------------------
	 ReleaseDC(pDC);
	 delete pActiveDC;
	 delete pMaskDC;
}

void CDisplayTalkDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	m_pDC = &dc;  

	if(m_viewid==-1)
		return ;

	//::BitBlt(dc.GetSafeHdc(),0,0,r.Width(),r.Height(),playviewdc->GetSafeHdc(),0,0,SRCCOPY);
 	
	CGameImageHelper help(&m_img);
	CDC srcdc;
	srcdc.CreateCompatibleDC(&dc);
	srcdc.SelectObject(help);
	::TransparentBlt(dc.GetSafeHdc(),0,0,help.GetWidth(),help.GetHeight(),srcdc,0,0,help.GetWidth(),help.GetHeight(),srcdc.GetPixel(0,0));

	m_rectCurrentLine = m_rectClient;
	m_rectCurrentLine.top += 8;
	m_rectCurrentLine.bottom =m_rectCurrentLine.top+m_fontHeight;
	m_rectCurrentLine.left += 8;
	m_rectCurrentLine.right -= 8;
	m_ptCurrent.x = m_rectCurrentLine.left;
	if(m_viewid==0)
		m_rectCurrentLine.top += 20;
	if(m_viewid==1)
		m_rectCurrentLine.top += 0;
	if(m_viewid==2)
		m_rectCurrentLine.top += 0;
	if(m_viewid==3)
		m_rectCurrentLine.top += 20;

	TCHAR szCharString[1000];
	lstrcpyn(szCharString,m_msg,200);
	szCharString[200]='\0';

    CTrueItem * pItem=NULL;
	m_bIsFirst = TRUE;
	int iCharLength=lstrlen(szCharString),iHandleLength=0;
 	do
	{
		int iPassCharCount=0;
		pItem=TranslateChar(szCharString+iHandleLength,iCharLength-iHandleLength,iPassCharCount);
		if (pItem!=NULL)
		{
			szCharString[iHandleLength+iPassCharCount]=0;
  			InsertCharToDC(szCharString+iHandleLength);
			iHandleLength+=iPassCharCount+pItem->m_uTranceLength;                      
 			InsertBitmapToDC(pItem->m_ExpPicImage);
 		}
		else 
		{
  			InsertCharToDC(szCharString+iHandleLength);			
 			break;
		}
	} while (pItem!=NULL);  
	srcdc.DeleteDC();
}

void CDisplayTalkDialog::CopyNumChar(const TCHAR *pSrc, int iStart,int iEnd, TCHAR* pDst)
{
	int i=iStart-1;
	int j=0;
	while(i<=iEnd-1)
	{
 		*(pDst+j) =  *(pSrc+i);
		i++;j++;
	}
	*(pDst+j)=TEXT('\0');
 }

int CDisplayTalkDialog::ThisLineContainChar(const TCHAR* szMsg)
{
    TCHAR szTemp[500];
    TCHAR* pTemp=szTemp;
	byte j=0;
	byte a=szMsg[0];
	byte b=szMsg[1];
	//判断是否汉字
	if((a>=176&&a<=247&&b>=160&&b<=254)||//GB2312
		(((a>=129&&a<=255)||(a>=64&&a<=126))&&b>=161&&b<=254)||///GB5
		(a>=129&&a<=254&&b>=64&&b<=254))//GBK
		j=2;
	else
		j=1;
	for(int i=lstrlen(szMsg);i>0;)
	{
		CopyNumChar(szMsg,j,i,pTemp);
        if( !IsNewLine(pTemp) )
			return i;
		a=szMsg[i-2];
		b=szMsg[i-1];
		//判断是否汉字
		if((a>=176&&a<=247&&b>=160&&b<=254)||//GB2312
			(((a>=129&&a<=255)||(a>=64&&a<=126))&&b>=161&&b<=254)||///GB5
			(a>=129&&a<=254&&b>=64&&b<=254))//GBK
			i-=2;
		else
			i-=1;
	}
	return -1;
}

BOOL CDisplayTalkDialog::IsNewLine(const TCHAR* szMsg)
{
	CRect rectTemp;
	CDC* pDC = GetDC();
	pDC->SelectObject(&m_font);
	int xOffset = pDC->GetTextExtent( szMsg,lstrlen(szMsg)).cx; 
	if(xOffset > (m_rectCurrentLine.right-m_ptCurrent.x))  //宽度如果容不了,另起一行
		return TRUE;
	return FALSE;
}

void CDisplayTalkDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
}

void CDisplayTalkDialog::DisplayOmit()
{
	TCHAR* pMsg = _T(".....");
    CDC* pDC = GetDC();
	pDC->SelectObject(&m_font);
	int len = pDC->GetTextExtent(pMsg,lstrlen(pMsg)).cx;

	m_rectCurrentLine.left = m_rectCurrentLine.right-len;
	m_rectCurrentLine.right = m_rectClient.right;
	m_rectCurrentLine.top -= (m_fontHeight+m_nLineJianGe);
	m_rectCurrentLine.bottom = m_rectCurrentLine.top + m_fontHeight;
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_LEFT);
	pDC->DrawText(pMsg,lstrlen(pMsg),m_rectCurrentLine,DT_LEFT|DT_VCENTER);
}