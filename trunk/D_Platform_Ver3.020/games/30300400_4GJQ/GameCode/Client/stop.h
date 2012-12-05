#pragma once

#include "Stdafx.h"
#include "Resource.h"

//有事离开对话框类
class CStop : public CGameFaceGo
{
//	DECLARE_DYNAMIC(CHaveThing)

	//变量定义
public:
	CNormalBitmapButtonEx				m_btOk;							//确定按钮
	CNormalBitmapButtonEx				m_btCancel;						//取消按钮
	enum					{ IDD = IDD_STOP };			//对话框数据
	CWnd				*m_pParnet;
	CGameImage			m_bk;			                //背景图


	//函数定义
public:
	//构造函数
	CStop(CWnd * pParent=NULL);   
	//析构函数
	virtual ~CStop();
	//初始化函数
	virtual BOOL OnInitDialog();

protected:
	//取消函数
	virtual void OnCancel();
	//确定函数
	virtual void OnOK();
	// DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);   
	void AutoSize();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
};
