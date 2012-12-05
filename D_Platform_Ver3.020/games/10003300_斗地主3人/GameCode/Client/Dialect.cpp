// Dialect.cpp : 实现文件
//

#include "stdafx.h"
#include "Dialect.h"
#include "ClientGameDlg.h"


// CDialect 对话框

IMPLEMENT_DYNAMIC(CDialect, CDialog)

CDialect::CDialect(CWnd* pParent /*=NULL*/)
	: CDialog(CDialect::IDD, pParent)
{

}

CDialect::~CDialect()
{
}

void CDialect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, DIALECT_BT, m_btOk);
}


BEGIN_MESSAGE_MAP(CDialect, CDialog)
	ON_BN_CLICKED(DIALECT_BT, &CDialect::OnBnClickedOk)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()



int CDialect::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码

	TCHAR path[MAX_PATH];
	wsprintf(path,TEXT(".\\image\\game_set.bmp"));
	m_bk.SetLoadInfo(path,true);

	wsprintf(path,TEXT(".\\image\\ok.bmp"));
	m_btOk.LoadButtonBitmap(path,true);

	return 0;
}
BOOL CDialect::OnInitDialog()
{
	CDialog::OnInitDialog() ; 

	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);

	CRect iRect ; 
	if(m_btOk.GetSafeHwnd())
	{
		m_btOk.GetClientRect(&iRect) ; 
		m_btOk.MoveWindow(80,125,iRect.right - iRect.left,iRect.bottom - iRect.top,false);
	}

	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(true) ;

	return  TRUE ;
}
HBRUSH CDialect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	return hbr;
}
void CDialect::OnLButtonDown(UINT nFlags,CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}
void CDialect::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CGameImageHelper	help(&m_bk);	
	help.BitBlt(dc.GetSafeHdc(),0,0);
}
void CDialect::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int iTemp = 0 ; 

	for(int i = 0 ; i < 4 ; i++ )
	{
		if(((CButton *)GetDlgItem(IDC_RADIO2 + i))->GetCheck() > 0)
		{
			iTemp = i ; 
			break ; 
		}
	}

	GetParent()->SendMessage(IDM_DIALECT,(WPARAM)iTemp,0);

	OnOK();
}
