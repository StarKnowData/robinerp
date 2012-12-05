#include "Stdafx.h"
#include "PlaySetDlg.h"
#include "ClientGameDlg.h"
#include "Resource.h"


BEGIN_MESSAGE_MAP(CPlaySetDlg, CCoolView)
END_MESSAGE_MAP()

/**
 * 构造函数
 */
CPlaySetDlg::CPlaySetDlg(CWnd * pParent) : CCoolView(CPlaySetDlg::IDD,pParent)
{
	m_pPP=pParent;
//	m_GameSetInfo.iBeginStation=2;
//	m_GameSetInfo.iEndStation=14;
	m_GameSetInfo.iPlayCount=30;		//思考时间
}

/**
 * 析够函数
 */
CPlaySetDlg::~CPlaySetDlg()
{
}

/**
 * DDX/DDV 支持
 */
void CPlaySetDlg::DoDataExchange(CDataExchange* pDX)
{
	CCoolView::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_SPIN, m_SpinCtrl);
}

/**
 * 初始化函数
 */
BOOL CPlaySetDlg::OnInitDialog()
{
	CCoolView::OnInitDialog();
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));
	//LoadDialogBitmap(GetModuleHandle(CLIENT_DLL_NAME),IDB_MODE_BMP,RGB(255,0,255),RGB(1,1,1));
	AfxSetResourceHandle(GetModuleHandle(NULL));
	
	//设置控件
	((CEdit *)GetDlgItem(IDC_COUNT))->LimitText(2);
	m_SpinCtrl.SetBuddy(GetDlgItem(IDC_COUNT));
	m_SpinCtrl.SetRange(10,60);

	return TRUE;
}

/**
 * 取消按钮
 */
void CPlaySetDlg::OnCancel()
{
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_GameSet);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	CCoolView::OnClose();
	::PostMessage(pp->GetSafeHwnd(),WM_CLOSE,0,0); 
}

/**
 * 确定按钮
 */
void CPlaySetDlg::OnOK()
{
	//读取数据
	BOOL bTrancelate=FALSE;
//	m_GameSetInfo.iBeginStation=((CComboBox *)GetDlgItem(IDC_BEGIN_STATION))->GetCurSel()+2;
//	m_GameSetInfo.iEndStation=((CComboBox *)GetDlgItem(IDC_END_STATION))->GetCurSel()+2;
	m_GameSetInfo.iCardCount=1;//(((CButton *)GetDlgItem(IDC_TWO))->GetCheck()==BST_CHECKED)?1:2;
	m_GameSetInfo.iPlayCount=GetDlgItemInt(IDC_COUNT,&bTrancelate);

	//效验数据
	if (bTrancelate==FALSE || m_GameSetInfo.iPlayCount==0)
	{
		AfxMessageBox(TEXT(" 请设置游戏的思考时间（10-60）！"),MB_ICONQUESTION);
		GetDlgItem(IDC_COUNT)->SetFocus();
		return;
	}
/*	if (m_GameSetInfo.iBeginStation>m_GameSetInfo.iEndStation)
	{
		AfxMessageBox(TEXT(" 开打的级数不能比结束的级数大！"),MB_ICONQUESTION);
		GetDlgItem(IDC_BEGIN_STATION)->SetFocus();
		return;
	}*/

	//发送消息
	CClientPlayView *p=CONTAINING_RECORD(this,CClientPlayView,m_GameSet);
	CClientGameDlg *pp=CONTAINING_RECORD(p,CClientGameDlg,m_PlayView);
	pp->PostMessage(IDM_BEGIN,0,0);
	CCoolView::OnClose();
	return;
}

/**
 * 设置游戏设置
 */
void CPlaySetDlg::SetGameSetInfo(int iCardCount)
{
	//设置变量
	m_GameSetInfo.iCardCount=iCardCount;
	if (GetSafeHwnd()==NULL) 
		Create(IDD_SET_PLAY,m_pPP);

	//设置控件
//	GetDlgItem(IDC_TWO)->EnableWindow(iCardCount&1);
//	GetDlgItem(IDC_THREE)->EnableWindow(iCardCount&2);
//	if (iCardCount&1) ((CButton *)GetDlgItem(IDC_TWO))->SetCheck(BST_CHECKED);
	//else if (iCardCount&2) ((CButton *)GetDlgItem(IDC_THREE))->SetCheck(BST_CHECKED);
	SetDlgItemInt(IDC_COUNT,m_GameSetInfo.iPlayCount);
//	((CComboBox *)GetDlgItem(IDC_BEGIN_STATION))->SetCurSel(m_GameSetInfo.iBeginStation-2);
	//((CComboBox *)GetDlgItem(IDC_END_STATION))->SetCurSel(m_GameSetInfo.iEndStation-2);

	CRect rect;
	m_pPP->GetClientRect(rect);
	int cx=rect.Width();
	int cy=rect.Height();
	GetClientRect(rect);
	MoveWindow((cx-rect.Width())/2,(cy-rect.Height())/2,rect.Width(),rect.Height());

	ShowWindow(SW_SHOW);

	return;
}

/**
 * 获取游戏设置
 */
tagGameSetInfo * CPlaySetDlg::GetGameSetInfo()
{
//	if (GetSafeHwnd()) return NULL;
	return &m_GameSetInfo;
}
