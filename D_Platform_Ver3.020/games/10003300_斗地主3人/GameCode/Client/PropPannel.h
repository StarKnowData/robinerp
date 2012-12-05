#pragma once
#include "afxwin.h"
#include "resource.h"
#include "Platform/explorer1.h"
#include "CommonDefine.h"

using namespace Gdiplus;


// CPropPannel 对话框

class CPropPannel : public CDialog
{
	DECLARE_DYNAMIC(CPropPannel)

	CWnd		*m_pParent;
	GameInfoStructInExe	*m_pGameInfo;			//游戏信息指针，从父窗口传来，需要得到玩家信息
	Image		*imgDialog;
	COLORREF	m_bkcolor;
	CString		m_strPropUrl;

	int			curPropID;
	int			curPropPrice;
	int			curPropVipPrice;

	int			m_nOpenFrom;

public:
	CPropPannel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPropPannel();

// 对话框数据
	//enum { IDD = IDD_PROPPANNEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctlTip;
public:
	virtual BOOL OnInitDialog();
	void setSkinIndex(int sk);
public:
	CNormalBitmapButtonEx m_bnClose;
public:
	afx_msg void OnPaint();
public:
	void drawSkin(void);
public:
	afx_msg void OnBnClickedClose();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	void openPannel(int openFrom,CString strGiveUser=TEXT(""));
	void ResetData(void);
public:
	CExplorer2 m_ie;
public:
	DECLARE_EVENTSINK_MAP()
public:
	void BeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
public:
	void NavigateErrorExplorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Frame, VARIANT* StatusCode, BOOL* Cancel);
public:
	void processLocalProp();
public:
	CString GetUrlValue(CString szUrl, CString szField);

public:
	int m_nHoldCount;
public:
	int m_nBuyCount;
public:
	CString m_strBuyMoney;
public:
	CEdit m_ctlGiveUser;
public:
	CNormalBitmapButtonEx  m_bnUse;
public:
	CNormalBitmapButtonEx  m_bnBuy;
public:
	CNormalBitmapButtonEx  m_bnGive;
	CNormalBitmapButtonEx  m_cancelBtn;
public:
	afx_msg void OnEnChangeBuycount();
public:
	CEdit m_ctlBuyCount;
public:
	CString m_sGiveUser;
public:
	CEdit m_ctlGiveCount;
public:
	int m_nGiveCount;
public:
	afx_msg void OnEnChangeGiveuser();
public:
	afx_msg void OnEnChangeGivecount();
public:
	afx_msg void OnBnClickedBuy();
public:
	void OnGetPropInformation(_TAG_USERPROP* userProp);
public:
	afx_msg void OnBnClickedUse();
public:
	afx_msg void OnBnClickedGive();
public:
	void OnGivenProp(_TAG_PROP_GIVE_FOR * propGiveFor);
public:
	void OnNetMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize);
};
