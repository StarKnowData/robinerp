#pragma once

#include "StdAfx.h"
#include "Resource.h"
//#include "ResultListCtrl.h"
#include "afxcmn.h"

//#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment(lib, "gdiplus.lib")

//#include "gameframedlg.h"
//游戏信息类
class CGameFinishDlg : public CWnd
{
	//变量定义
protected:
	GameFinishNotify	m_iFinish;
	CGameImage			m_bk;
	CGameImage          m_win;
	CGameImage          m_lost;
    CGameImage          m_equal;
	int                 m_iCx;
	int                 m_iCy;
	BYTE				m_iViewStation;				//是否为本玩家
	UserItemStruct					* m_pUserItem[MAX_PEOPLE];
	CString             m_ShapeName[15];
	//enum					{ IDD = IDD_GAME_END };			//对话框数据
	int                 m_nPowerOfGold;   ///金币倍率

	//函数定义
public:
	CWnd *m_pParnet;
	//构造函数
	CGameFinishDlg();
	//析构函数
	virtual ~CGameFinishDlg();

	void SetMessage(GameFinishNotify finishnotify,BYTE iViewStation=0,int nPowerOfGold =0);
	
protected:
public:
	//重画函数
	afx_msg void OnPaint();

	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	/// 依当前金币倍率得到显示字符串
	void GetNumString(__int64 nNum, CString &Str, int nPower);
};
