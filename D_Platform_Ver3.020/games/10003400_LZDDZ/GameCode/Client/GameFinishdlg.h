#pragma once

#include "StdAfx.h"
#include "Resource.h"
//游戏信息类
class CGameFinishDlg : public CWnd
{
	//变量定义
protected:
	//CFont				m_Font;						//显示字体
//	CString				m_strMessage;				//字符信息
//	CBitmap				m_BackBmp;					//背景
	GameFinishNotify	m_iFinish;
	CGameImage			m_bk;
	CGameImage			m_Flag;						//标记
	BYTE				m_iViewStation;				//是否为本玩家
//	enum					{ IDD = IDD_GAME_END };			//对话框数据
	//函数定义
public:
	CWnd *m_pParnet;
	//构造函数
	CGameFinishDlg();
	//析构函数
	virtual ~CGameFinishDlg();
	//自动调整大小
	void AutoSize(int x,int y);
	//设置信息
//	void SetMessage(TCHAR * szMessage);
	void SetMessage(GameFinishNotify finishnotify,BYTE iViewStation=0);
	//void SetShow(BOOL bShow = TRUE);
	//消息函数
public:
	//重画函数
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void SetIntToCharLjl(CString  &str, __int64 iMoney, int iSet);

	int m_iPower; 
	void SetPower(int iPower=0)
	{
		m_iPower = iPower;
	}
};
