#include "StdAfx.h"
#include "ClientGameDlg.h"
#include ".\dianmu.h"

CDianMu::CDianMu(void):CGameFaceGo(CDianMu::IDD)
{
	m_pParent = NULL;
}

CDianMu::~CDianMu(void)
{
}


BOOL CDianMu::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	MoveWindow(0,0,242,137);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BEGIN_MESSAGE_MAP(CDianMu, CGameFaceGo)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, OnHitContinueChess)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CDianMu::OnPaint()
{
	CPaintDC dc(this); 
	//SetWindowPos(&wndBottom,0,0,242,137,SWP_NOZORDER);
	CGameImageHelper handle(&m_bk);
	handle.BitBlt(dc,0,0);
	dc.SetBkMode(TRANSPARENT);

	CFont font; //JMod-字体格式修改-20090631
	font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	CFont *pOldFont = dc.SelectObject(&font);	
	dc.TextOut(m_iDestX,m_iDestY,m_strMessage);
	dc.SelectObject(pOldFont);
	font.DeleteObject();

	//jph 100127
	HRGN hRgn;
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
	{
		SetWindowRgn(hRgn,true);
	}

}

void CDianMu::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pParent = GetParent();
	if (m_pParent)
	{
		CString str;
		this->GetWindowText(str);
		if (str == TEXT("点目结果"))///TEXT("强制数子"))
		{
			//同意点目结果	
			m_pParent->SendMessage(IDM_ASSURANCE_NUM_ZI,1,1);
		}
		else if (str == TEXT("点目"))
		{
			if (m_strMessage == TEXT("您确定要开始点目吗?"))
			{
				m_pParent->SendMessage(IDM_ASSURANCE_DIAN_MU,0,0);
			}
			else if (m_strMessage == TEXT("对家请求点目，您同意吗?"))
			{
				m_pParent->SendMessage(IDM_AGREE_DIAN_MU,1,1);
			}
		}
	}

	CGameFaceGo::OnOK();
}

void CDianMu::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pParent = GetParent();
	if (m_pParent)
	{
		CString str;
		this->GetWindowText(str);
		if (str == TEXT("点目结果"))
		{
			//继续点目
			m_pParent->SendMessage(IDM_ASSURANCE_NUM_ZI,2,2);
		}
		else if (str == TEXT("点目"))
		{
			if (m_strMessage == TEXT("对家请求点目，您同意吗?"))
				m_pParent->SendMessage(IDM_AGREE_DIAN_MU,0,0);
		}
	}

	CGameFaceGo::OnCancel();
}

void CDianMu::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CGameFaceGo::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX,IDC_BUTTON_CONTINUE,m_btContinueChess);
	CGameFaceGo::DoDataExchange(pDX);
}


void CDianMu::SetMessage(TCHAR *szMessage, int iDestX, int iDestY)
{
	m_strMessage.Empty();

	if (szMessage != NULL)
	{
		m_strMessage = szMessage;
		m_iDestX = iDestX;
		m_iDestY = iDestY;
		Invalidate(FALSE);
	}

	return;

}
void CDianMu::OnHitContinueChess()
{
	m_pParent->SendMessage(IDM_ASSURANCE_NUM_ZI,3,3);
	CGameFaceGo::OnCancel();
}

void CDianMu::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(point.y<22)
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CGameFaceGo::OnLButtonDown(nFlags, point);
}
