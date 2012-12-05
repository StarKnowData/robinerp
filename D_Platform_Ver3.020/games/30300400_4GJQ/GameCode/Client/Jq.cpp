#include "StdAfx.h"
#include "Jq.h"
#include "resource.h"




void TransparentBlt2( HDC hdcDest,      // 目标DC
					int nXOriginDest,   // 目标X偏移
					int nYOriginDest,   // 目标Y偏移
					int nWidthDest,     // 目标宽度
					int nHeightDest,    // 目标高度
					HDC hdcSrc,         // 源DC
					int nXOriginSrc,    // 源X起点
					int nYOriginSrc,    // 源Y起点
					int nWidthSrc,      // 源宽度
					int nHeightSrc,     // 源高度
					UINT crTransparent  // 透明色,COLORREF类型
					)
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);

	// 将源DC中的位图拷贝到临时DC中
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);

	// 设置透明色
	SetBkColor(hImageDC, crTransparent);

	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(255,255,255));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	// 清理、恢复	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
}


void  CStaticGlbJq::ShowACross(CDC* pDC,CPoint& destCenterPt,int angle)
{
	CRect  rc;
	if(angle == 0 || angle == 180)
	{
		rc.left = rc.top = 0;
		rc.right = rc.left + mSzSrcQiZi.cx + 4;
		rc.bottom = rc.top + mSzSrcQiZi.cy + 4;
	}
	else
	{
		rc.left = 0;
		rc.top = mSzSrcQiZi.cy + 4;
		rc.right = rc.left + mSzSrcQiZi.cy + 4;
		rc.bottom = rc.top + mSzSrcQiZi.cx + 4;
	}
	CRect destrc;
	destrc.left = destCenterPt.x - rc.Width () / 2;
	destrc.top= destCenterPt.y - rc.Height () / 2;
	destrc.right = destrc.left + rc.Width ();
	destrc.bottom = destrc.top + rc.Height ();


	/*

	if(p_hp_AllOther)
	{
		//p_hp_AllOther->StretchBlt (
		     //                   pDC->GetSafeHdc(),
			//					destrc.left ,destrc.top,destrc.Width () ,destrc.Height (),
			//					rc.left ,rc.top,rc.Width () ,rc.Height ()
			//					);

	  if(!p_hp_AllOther->GetImage())return;

	  HDC hdc=p_hp_AllOther->GetImage()->GetDC ();
	   if(hdc == NULL || pDC->GetSafeHdc  () == NULL)return;

	   TransparentBlt2( 
		            pDC->GetSafeHdc  (),//HDC hdcDest,      // 目标DC

					destrc.left ,destrc.top,destrc.Width () ,destrc.Height (),
								
					//int nXOriginDest,   // 目标X偏移
					//int nYOriginDest,   // 目标Y偏移
					//int nWidthDest,     // 目标宽度
					//int nHeightDest,    // 目标高度
					hdc,//HDC hdcSrc,         // 源DC
					rc.left ,rc.top,rc.Width () ,rc.Height (),
					//int nXOriginSrc,    // 源X起点
					//int nYOriginSrc,    // 源Y起点
					//int nWidthSrc,      // 源宽度
					//int nHeightSrc,     // 源高度
					RGB(255,255,255)//UINT crTransparent  // 透明色,COLORREF类型
					);

	  
	}*/

	
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CGameImageHelper handle(&m_btOther);
	CBitmap * pOldBmp = memDC.SelectObject(handle);

	TransparentBlt2( 
		            pDC->GetSafeHdc  (),//HDC hdcDest,      // 目标DC
					destrc.left ,destrc.top,destrc.Width () ,destrc.Height (),
					memDC.GetSafeHdc  (),//HDC hdcSrc,         // 源DC
					rc.left ,rc.top,rc.Width () ,rc.Height (),
					RGB(255,255,255)//UINT crTransparent  // 透明色,COLORREF类型
					);
	
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
}

/**
 * 绘画路径
 */
void  CStaticGlbJq::ShowPath(CDC* pDC, CPoint& destCenterPt, int iDirection, int angle,int x, int y)
{
	CRect  rc,destrc;
	int iDirectionWidth = 14;	// 小箭头宽
	int iDirectionHeight = 14;	// 小箭头高	
	rc.left = iDirection*iDirectionWidth;

	rc.top = 0;
	rc.right = rc.left + iDirectionWidth;
	rc.bottom = rc.top + iDirectionHeight;

	destrc.left = destCenterPt.x - rc.Width () / 2;
	destrc.top= destCenterPt.y - rc.Height () / 2;
	destrc.right = destrc.left + rc.Width ();
	destrc.bottom = destrc.top + rc.Height ();

	if (6==x && 6==y)
		destrc.OffsetRect(-1, -2);
	if (8==x && 6==y)
		destrc.OffsetRect(-1, 0);
	else if (10==x && 6==y)
		destrc.OffsetRect(-1, 2);
	else if (6==x && 8==y)
		destrc.OffsetRect(1, -2);
	else if (8==x && 8==y)
		destrc.OffsetRect(1, 0);
	else if (10==x && 8==y)
		destrc.OffsetRect(1, 2);
	else if (6==x && 10==y)
		destrc.OffsetRect(3, -2);
	else if (8==x && 10==y)
		destrc.OffsetRect(3, 0);
	else if (10==x && 10==y)
		destrc.OffsetRect(3, 2);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CGameImageHelper handle(&m_bit_Path);
	CBitmap * pOldBmp = memDC.SelectObject(handle);

	TransparentBlt2( 
		            pDC->GetSafeHdc  (),//HDC hdcDest,      // 目标DC
					destrc.left ,destrc.top,destrc.Width () ,destrc.Height (),
					memDC.GetSafeHdc  (),//HDC hdcSrc,         // 源DC
					rc.left ,rc.top,rc.Width () ,rc.Height (),
					RGB(255,0,255)//UINT crTransparent  // 透明色,COLORREF类型
					);
	
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
}

/**
 * 给画棋子
 */
void  CStaticGlbJq::ShowAPisa(int ps,CDC* pDC,CPoint& destCenterPt,int angle,bool showback,bool bDraw)
{
	if (!bDraw)
		return;

	CRect  rc=GetJqSrcRect(ps,angle,showback);
	CRect destrc;
	destrc.left = destCenterPt.x - rc.Width () / 2;
	destrc.top= destCenterPt.y - rc.Height () / 2;
	destrc.right = destrc.left + rc.Width ();
	destrc.bottom = destrc.top + rc.Height ();


	//CString str;
	//str.Format("================destrc.left:%d,destCenterPt.x:%d",  destrc.left, destCenterPt.x);
	//OutputDebugString(str);

	if(p_hp_AllQiZi)
		p_hp_AllQiZi->StretchBlt (
		                        pDC->GetSafeHdc(),
								destrc.left ,destrc.top,destrc.Width () ,destrc.Height (),
								rc.left ,rc.top,rc.Width () ,rc.Height ()
								);
}

CRect  CStaticGlbJq::GetJqSrcRect(int ps,int angle,bool showback)
{
	CRect rc;
	int w=mSzSrcQiZi.cx ,
		h=mSzSrcQiZi.cy;

	int col = GET_A_JQ_COLOR(ps),jq=GET_A_JQ_NAME(ps);

	switch(angle)
	{
	case 0:
		{
			switch(col)
			{
				case JQ_TYPE_COLOR_RED:
				{
					rc.left = (JQ_TYPE_NAME_SL - jq  ) * w;
					rc.top = 0 * h;
					
				}
				break;
				case JQ_TYPE_COLOR_BLUE:
				{
					rc.left = (JQ_TYPE_NAME_SL - jq  ) * w;
					rc.top = 1 * h;
				}
					break;
				case JQ_TYPE_COLOR_BLACK:
				{
					rc.left = (JQ_TYPE_NAME_SL - jq  ) * w;
					rc.top = 2 * h;
				}
					break;
				case JQ_TYPE_COLOR_GRAY:
				{
					rc.left = (JQ_TYPE_NAME_SL - jq  ) * w;
					rc.top = 3 * h;
				}
				break;
			
			}
			if(showback)rc.left = 12 * w;
			rc.right = rc.left + w;
			rc.bottom = rc.top + h;
		}
		break;
	case 180:
		{
			switch(col)
			{
				case JQ_TYPE_COLOR_RED:
				{
					rc.left = (jq - JQ_TYPE_NAME_ZD  + 1) * w;
					rc.top = 3 * h;
				}
				break;
				case JQ_TYPE_COLOR_BLUE:
				{
					rc.left = (jq - JQ_TYPE_NAME_ZD  + 1) * w;
					rc.top = 2 * h;
				}
					break;
				case JQ_TYPE_COLOR_BLACK:
				{
					rc.left = (jq - JQ_TYPE_NAME_ZD  + 1) * w;
					rc.top = 1 * h;
				}
					break;
				case JQ_TYPE_COLOR_GRAY:
				{
					rc.left = (jq - JQ_TYPE_NAME_ZD  + 1) * w;
					rc.top = 0 * h;
				}
				break;
			
			}
			if(showback)rc.left = 0 * w;
			rc.top += 4 * h;
			rc.right = rc.left + w;
			rc.bottom = rc.top + h;
		}
		break;
	case 90:
		{
			w=mSzSrcQiZi.cy;
		    h=mSzSrcQiZi.cx;
			switch(col)
			{
				case JQ_TYPE_COLOR_RED:
				{
					rc.left = 0 * w;
					rc.top =( jq - JQ_TYPE_NAME_ZD  + 1) * h;
				}
				break;
				case JQ_TYPE_COLOR_BLUE:
				{
					rc.left = 1 * w;
					rc.top =( jq - JQ_TYPE_NAME_ZD  + 1) * h;
				}
					break;
				case JQ_TYPE_COLOR_BLACK:
				{
					rc.left = 2 * w;
					rc.top =( jq - JQ_TYPE_NAME_ZD  + 1) * h;
				}
					break;
				case JQ_TYPE_COLOR_GRAY:
				{
					rc.left = 3 * w;
					rc.top =( jq - JQ_TYPE_NAME_ZD  + 1) * h;
				}
				break;
			
			}
			if(showback)rc.top = 0 * h;
			rc.top +=  8 * mSzSrcQiZi.cy;
			rc.right = rc.left + w;
			rc.bottom = rc.top + h;
		}
		break;
	case 270:
		{
			w=mSzSrcQiZi.cy;
		    h=mSzSrcQiZi.cx;
			switch(col)
			{
				case JQ_TYPE_COLOR_RED:
				{
					rc.left = 3 * w;
					rc.top =(JQ_TYPE_NAME_SL - jq  ) * h;
				}
				break;
				case JQ_TYPE_COLOR_BLUE:
				{
					rc.left = 2 * w;
					rc.top =(JQ_TYPE_NAME_SL - jq  ) * h;
				}
					break;
				case JQ_TYPE_COLOR_BLACK:
				{
					rc.left = 1 * w;
					rc.top =(JQ_TYPE_NAME_SL - jq  ) * h;
				}
					break;
				case JQ_TYPE_COLOR_GRAY:
				{
					rc.left = 0 * w;
					rc.top =(JQ_TYPE_NAME_SL - jq  ) * h;
				}
				break;
			
			}
			if(showback)rc.top = 12 * h;
			rc.top +=  8 * mSzSrcQiZi.cy;
			rc.left += 4 * w;
			rc.right = rc.left + w;
			rc.bottom = rc.top + h;
		}
		break;
	}
	return rc;
}

void CStaticGlbJq::Init()
{	
	static bool g_bGlb_Mj_Is_Inited=false;
	if(g_bGlb_Mj_Is_Inited)return;

	//AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	CString s = CINIFile::GetAppPath ();/////本地路径
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("%simage/Other1024.bmp"), s.GetBuffer());
	s.ReleaseBuffer();
	m_btOther.SetLoadInfo(path, true);
//	m_bit_AllOther_1024.SetLoadInfo(GetModuleHandle(CLIENT_DLL_NAME),IDB_ALLOTHER_1024,CGameImageLink::m_bAutoLock);

	wsprintf(path,TEXT("%s/image/AllQiZi1024.bmp"), s.GetBuffer());
	s.ReleaseBuffer();
	m_bit_AllQiZi_1024.SetLoadInfo(path,true);

	wsprintf(path,TEXT("%s/image/path.bmp"), s.GetBuffer());
	s.ReleaseBuffer();
	m_bit_Path.SetLoadInfo(path,true);
	//AfxSetResourceHandle(GetModuleHandle(NULL));

	if(p_hp_AllQiZi)delete p_hp_AllQiZi;
	p_hp_AllQiZi=NULL;

	//if (GetSystemMetrics(SM_CXSCREEN)>=1024)
	{
		p_hp_AllQiZi = new CGameImageHelper(&m_bit_AllQiZi_1024);
//		p_hp_AllOther = new CGameImageHelper(&m_bit_AllOther_1024);
		mSzSrcQiZi.cx = 36;
		mSzSrcQiZi.cy  = 27;
		mSzGrade.cx = 39;
		mSzGrade.cy  = 39;
	}
//	else
	{
	}

	g_bGlb_Mj_Is_Inited=true;
}

CStaticGlbJq   g_CStaticGlbMj;

/*
void CStaticGlbJq::ShowAPisa(int ps,CDC* pDC,CRect& rc)
{
	if(!pDC)return;

	Init();
    int startX=rc.left ,startY=rc.top ;;

	

	if(ps == JQ_TYPE_NONE)   ////erase
	{
		return;
	}

	CBitmap* bit=NULL;//GetAPisa(ps);
	
	if(!bit)return;

}


void CJq::ShowAJq(CDC* pDC,CPoint ptStart)
{
	CRect rc(
		       ptStart.x ,
			   ptStart.y ,
			   ptStart.x+ JQ_SHOW_SCAL_WEIGHT,
			   ptStart.y+JQ_SHOW_SCAL_HEIGHT
			   );
	
	
	g_CStaticGlbMj.ShowAPisa ( m_iPs, pDC, rc );
}

*/

CJq::CJq(void)
{
	g_CStaticGlbMj.Init ();
	m_iPs=JQ_TYPE_NONE;

}

CJq::~CJq(void)
{
}



CJq::CJq(int ps)
{
	m_iPs=ps;
	g_CStaticGlbMj.Init ();

}



CJq::CJq(int hs,int pd)
{
	m_iPs=MAKE_A_JQ(hs,pd);
}














































/*CBitmap* CStaticGlbJq::GetAPisa(int ps)
{
	CBitmap* bit=NULL;

    if(ps == JQ_TYPE_R_SL)bit=&m_bit_jq_r_sl;
	if(ps == JQ_TYPE_R_JZ)bit=&m_bit_jq_r_jz;
	if(ps == JQ_TYPE_R_SZ)bit=&m_bit_jq_r_sz;
	if(ps == JQ_TYPE_R_LIZ)bit=&m_bit_jq_r_liz;
	if(ps == JQ_TYPE_R_TZ)bit=&m_bit_jq_r_tz;
	if(ps == JQ_TYPE_R_YZ)bit=&m_bit_jq_r_yz;
	if(ps == JQ_TYPE_R_LIANZ)bit=&m_bit_jq_r_lianz;
	if(ps == JQ_TYPE_R_PZ)bit=&m_bit_jq_r_pz;
	if(ps == JQ_TYPE_R_GB)bit=&m_bit_jq_r_gb;
    if(ps == JQ_TYPE_R_DL)bit=&m_bit_jq_r_dl;
	if(ps == JQ_TYPE_R_JQ)bit=&m_bit_jq_r_jq;
	if(ps == JQ_TYPE_R_ZD)bit=&m_bit_jq_r_zd;

	
    if(ps == JQ_TYPE_G_SL)bit=&m_bit_jq_g_sl;
	if(ps == JQ_TYPE_G_JZ)bit=&m_bit_jq_g_jz;
	if(ps == JQ_TYPE_G_SZ)bit=&m_bit_jq_g_sz;
	if(ps == JQ_TYPE_G_LIZ)bit=&m_bit_jq_g_liz;
	if(ps == JQ_TYPE_G_TZ)bit=&m_bit_jq_g_tz;
	if(ps == JQ_TYPE_G_YZ)bit=&m_bit_jq_g_yz;
	if(ps == JQ_TYPE_G_LIANZ)bit=&m_bit_jq_g_lianz;
	if(ps == JQ_TYPE_G_PZ)bit=&m_bit_jq_g_pz;
	if(ps == JQ_TYPE_G_GB)bit=&m_bit_jq_g_gb;
    if(ps == JQ_TYPE_G_DL)bit=&m_bit_jq_g_dl;
	if(ps == JQ_TYPE_G_JQ)bit=&m_bit_jq_g_jq;
	if(ps == JQ_TYPE_G_ZD)bit=&m_bit_jq_g_zd;


	if(ps == JQ_TYPE_B_SL)bit=&m_bit_jq_b_sl;
	if(ps == JQ_TYPE_B_JZ)bit=&m_bit_jq_b_jz;
	if(ps == JQ_TYPE_B_SZ)bit=&m_bit_jq_b_sz;
	if(ps == JQ_TYPE_B_LIZ)bit=&m_bit_jq_b_liz;
	if(ps == JQ_TYPE_B_TZ)bit=&m_bit_jq_b_tz;
	if(ps == JQ_TYPE_B_YZ)bit=&m_bit_jq_b_yz;
	if(ps == JQ_TYPE_B_LIANZ)bit=&m_bit_jq_b_lianz;
	if(ps == JQ_TYPE_B_PZ)bit=&m_bit_jq_b_pz;
	if(ps == JQ_TYPE_B_GB)bit=&m_bit_jq_b_gb;
    if(ps == JQ_TYPE_B_DL)bit=&m_bit_jq_b_dl;
	if(ps == JQ_TYPE_B_JQ)bit=&m_bit_jq_b_jq;
	if(ps == JQ_TYPE_B_ZD)bit=&m_bit_jq_b_zd;

	
    if(ps == JQ_TYPE_K_SL)bit=&m_bit_jq_k_sl;
	if(ps == JQ_TYPE_K_JZ)bit=&m_bit_jq_k_jz;
	if(ps == JQ_TYPE_K_SZ)bit=&m_bit_jq_k_sz;
	if(ps == JQ_TYPE_K_LIZ)bit=&m_bit_jq_k_liz;
	if(ps == JQ_TYPE_K_TZ)bit=&m_bit_jq_k_tz;
	if(ps == JQ_TYPE_K_YZ)bit=&m_bit_jq_k_yz;
	if(ps == JQ_TYPE_K_LIANZ)bit=&m_bit_jq_k_lianz;
	if(ps == JQ_TYPE_K_PZ)bit=&m_bit_jq_k_pz;
	if(ps == JQ_TYPE_K_GB)bit=&m_bit_jq_k_gb;
    if(ps == JQ_TYPE_K_DL)bit=&m_bit_jq_k_dl;
	if(ps == JQ_TYPE_K_JQ)bit=&m_bit_jq_k_jq;
	if(ps == JQ_TYPE_K_ZD)bit=&m_bit_jq_k_zd;

	
	return bit;

}*/
