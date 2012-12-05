#pragma once

#include "StdAfx.h"
#include "Resource.h"
class CShowNote : public CDialog
{
	//控件变量
public:	
	CGameImage			m_bk;								//背景图
//	CBitmapButton		m_BmShow;							//按钮
//	CBitmapButton		m_BmNote;							//按钮
//	CBitmapButton		m_BmAdd;							//按钮
//	CBitmapButton		m_BmFollow;							//按钮
//	CBitmapButton		m_BmGiveup;							//按钮
	CNormalBitmapButtonEx       m_BmShow;							//开按钮
	CNormalBitmapButtonEx		m_BmNote;							//下按钮
	CNormalBitmapButtonEx		m_BmAdd;							//加按钮
	CNormalBitmapButtonEx		m_BmFollow;							//跟按钮
	CNormalBitmapButtonEx		m_BmGiveup;	                        //弃
	CNormalBitmapButtonEx	    m_BmLook;                           //看
	CWnd				*m_pParent;
	
	enum				{ IDD = IDD_SHOW_NOTE };			//ID 号码

	//函数定义
public:
	//构造函数
	CShowNote(CWnd * pParent = NULL);
	//更新列表
	void UpdateShowNoteBtn(BOOL show=false,BOOL note=false,BOOL add=false,BOOL follow=false,BOOL giveup=false,BOOL look=true);
	//设置下注
	void SetShowNoteBtn(BOOL show=false,BOOL note=false,BOOL add=false,BOOL follow=false,BOOL giveup=false,BOOL look=true);
protected:
	//DDX 支持
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//消息函数
protected:
	//初始化函数
	virtual BOOL OnInitDialog();
	//按钮消息
	afx_msg void OnNote();
	//按钮消息
	afx_msg void OnShow();
	//按钮消息
	afx_msg void OnFollow();
	//按钮消息
	afx_msg void OnGiveup();
	//按钮消息
	afx_msg void OnAdd();
	afx_msg void OnLook();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void DrawBk(CDC * pDC, int x, int y);
	DECLARE_MESSAGE_MAP()
};

