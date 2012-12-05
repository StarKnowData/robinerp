// CardShape.cpp : 实现文件
//

#include "stdafx.h"
#include "CardShape.h"


// CCardShape

IMPLEMENT_DYNAMIC(CCardShape, CWnd)

CCardShape::CCardShape()
{
	m_byShape = -1;
	m_pt.x = 0;
	m_pt.y = 0;
}

CCardShape::~CCardShape()
{

}


BEGIN_MESSAGE_MAP(CCardShape, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CCardShape 消息处理程序

int CCardShape::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

BOOL CCardShape::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CCardShape::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
#ifdef	SAO_YANG
	Graphics g(GetDC()->m_hDC);
	g.DrawImage(m_pImage, Rect(8,5,m_pImage->GetWidth(),m_pImage->GetHeight()));
#else
	CGameImageHelper help(&m_imgShape);
	help.BitBlt(dc, 0, 0);
#endif

}

/// 设置显示位置
void CCardShape::SetPoint(int x, int y)
{	
	m_pt.x = x;
	m_pt.y = y;
	
	ShowCardShape(m_byShape);
}

/// 显示牌型
void CCardShape::ShowCardShape(BYTE byShape)
{	
	m_byShape = byShape;

	if(m_byShape > 10)
	{
		return;
	}

#ifdef	SAO_YANG
	CString strTemp;
	strTemp.Format(".\\image\\%dNum.png",m_byShape);

	m_pImage = Image::FromFile(CA2W(strTemp));
	CreateRgn();

	MoveWindow(m_pt.x+10, m_pt.y, m_pImage->GetWidth(), m_pImage->GetHeight());
#else
	TCHAR szPath[MAX_PATH];
	wsprintf(szPath, ".\\image\\%dNum.bmp", m_byShape);
	m_imgShape.SetLoadInfo(szPath, CGameImageLink::m_bAutoLock);

	CGameImageHelper help(&m_imgShape);
	HRGN hRgn = AFCBmpToRgn(help, RGB(255, 0, 255), RGB(1, 1, 1));     // 过滤掉RGB(255,0,255)的颜色区域
	if (hRgn != NULL)
	{
		SetWindowRgn(hRgn,TRUE);        // 设置为没有过滤掉的区域
	}

	MoveWindow(m_pt.x, m_pt.y, help.GetWidth(), help.GetHeight());
#endif
	
	Invalidate(FALSE);

	ShowWindow(SW_SHOW);
}

//<创建区域
void CCardShape::CreateRgn()
{
	HRGN hRgn = NULL;

	Image * pImage = m_pImage;
	if (pImage == NULL)
	{
		return ;
	}

	// 进行透明色过滤
	Region* _rgn = NULL;
	int nW = pImage->GetWidth();
	int nH = pImage->GetHeight();

	///////////////////////  进行透明色过滤 /////////////////////
	Bitmap* bmp = new Bitmap(nW, nH);   
	Graphics* g = Graphics::FromImage(bmp);  

	RectF rect;
	rect.X = 8;
	rect.Y = 5;
	rect.Width = nW;
	rect.Height = nH;
	g->DrawImage(pImage, rect, 0, 0, nW, nH, UnitPixel, NULL, NULL, NULL);

	GraphicsPath gp;   
	for (int i = 0; i < nW; i ++)   
	{   
		for (int j = 0; j < nH; j++)   
		{   
			Color cl;   
			bmp->GetPixel(i, j, &cl);   
			if (cl.GetA() != 0)   
			{
				gp.AddRectangle(Rect(i, j, 1, 1));   
			}
		}  
	}   

	delete g;
	delete bmp;   
	_rgn = new Region(&gp);  
	///////////////////////////////////////////////////////////////

	if (_rgn != NULL)
	{
		Graphics g(GetDC()->m_hDC);   
		hRgn = ::CreateRectRgn(0, 0, 0, 0);    
		CombineRgn(hRgn, _rgn->GetHRGN(&g), NULL, RGN_COPY);    
		delete _rgn;

		SetWindowRgn(hRgn, FALSE);
	}
}