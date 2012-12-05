#pragma once

#include "StdAfx.h"

//游戏信息类
class CGameNoteWnd : public CWnd
{
	//变量定义
protected:
//	CFont				m_Font;						//显示字体
//	CString				m_strMessage;				//字符信息
//	CBitmap				m_BackBmp;					//背景
	CNormalBitmapButtonEx			m_btLogo;		//登陆
	CGameImage			m_bk;
	int					m_iFlag;									
	unsigned long m_dwUserID;
	//函数定义
public:
	//构造函数
	CGameNoteWnd();
	//析构函数
	virtual ~CGameNoteWnd();
	//自动调整大小
	void AutoSize(int xValue,int yValue);
	//设置信息
	void SetMessage(TCHAR * szMessage);

	//消息函数
public:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	//重画函数
	afx_msg void OnPaint();
	void SetGameStateFlag(int iStateFlag = 0);
	DECLARE_MESSAGE_MAP()
};
