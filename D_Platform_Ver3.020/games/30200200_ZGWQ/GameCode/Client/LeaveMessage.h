#pragma once

#include "stdafx.h"
#include "Resource.h"

//玩家请求离开消息
class CLeaveMessage : public CGameFaceGo
{

	//变量定义
protected:
	CNormalBitmapButtonEx				m_btOk;							//确定按钮
	CNormalBitmapButtonEx				m_btCancel;						//取消按钮
	enum					{ IDD = IDD_THING_MESSAGE };
	CGameImage					m_bk;
	//函数定义
public:
	//构造函数
	CLeaveMessage();
	//析构函数
	virtual ~CLeaveMessage();
	//设置信息
	void SetLeaveMessage(TCHAR * szMessage, TCHAR * szUserName);
	CWnd *m_pParent;

protected:
	//取消函数
	virtual void OnCancel();
	//确定函数
	virtual void OnOK();
	//DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	virtual BOOL OnInitDialog();
};
