#pragma once
///#include "e:\20050611_pmbgame\newgame\客户端组件\界面库.2003\afcdialog.h"

#include "Stdafx.h"
#include "Resource.h"

class CRegretChess :
	public CGameFaceGo
{
public:
	CNormalBitmapButtonEx				m_btOk;							//同意按钮
	CNormalBitmapButtonEx				m_btCancel;						//不同意按钮
	enum					{ IDD = IDD_DLG_HUI_QI };			//对话框数据
	CWnd *m_pParnet;
	CGameImage							m_bk;
public:
	CRegretChess(void);
	~CRegretChess(void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
