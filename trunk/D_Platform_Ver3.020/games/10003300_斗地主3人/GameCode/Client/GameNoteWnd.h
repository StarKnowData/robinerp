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
	CGameImage			m_bk;
	//函数定义
public:
	//构造函数
	CGameNoteWnd();
	//析构函数
	virtual ~CGameNoteWnd();
	//自动调整大小
	void AutoSize();
	//设置信息
	void SetMessage(TCHAR * szMessage);

	//消息函数
public:
	//重画函数
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

// ----------------------------------------------------------------------------
// PengJiLin, 2011-4-19, 在线时长、局数送金币图像提示
// ----------------------------------------------------------------------------
class CGetMoneyWnd: public CWnd
{
protected:
    CGameImage			m_bk;
    CGameImage			m_Flag;     // 恭喜 标志

    CString             m_strGetInfo;
    CString             m_strTimeInfo;
    CString             m_strCountInfo;

    int                 m_iStartX;
    int                 m_iStartY;
    int                 m_iStartSpace;
    int                 m_iFlagX;
    int                 m_iFlagY;
    COLORREF            m_cColor;

public:
    CGetMoneyWnd();
    virtual ~CGetMoneyWnd();
    void AutoSize();
    void SetShow(BOOL bShow);

    void SetMessage(CString& strGet, CString& strTime, CString& strCount, bool bInVideoRoom);

public:
    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()
};