#pragma once

#include "StdAfx.h"
#include "Resource.h"
#define JETON_W 31
#define JETON_H 30
class CeasyNtList : public CDialog
{
	//控件变量
public:
	CGameImage				m_bk;								//背景图
	CGameImage				m_PicNum;							//时间数字
	//CNormalBitmapButtonEx    m_Bm4;						//按钮
	//CNormalBitmapButtonEx    m_Bm3;						//按钮
	//CNormalBitmapButtonEx    m_Bm2;						//按钮
	//CNormalBitmapButtonEx    m_Bm1;						//按钮
	//CNormalBitmapButtonEx    m_Bm5;						//按钮
	//CNormalBitmapButtonEx    m_Bm6;						//按钮
	CNormalBitmapButtonEx    m_BmMax;					//按钮
	CNormalBitmapButtonEx    m_BmCancel;				//按钮
	CNormalBitmapButtonEx    m_BmOk;				     //按钮
	CRect					m_BtnRect0,m_BtnRect1,m_BtnRect2;	//矩形框
	int						m_BtnIndex0,m_BtnIndex1,m_BtnIndex2;//索引
	int						m_iStart0,m_iStart1,m_iStart2,m_iEnd;//三个下注筹码显示和最大加注
	//CNormalBitmapButtonEx	m_BmOk;
//CNormalBitmapButtonEx	m_BmCancel;
//	CBitmapButton		m_Bmmp;							//按钮
//	CBitmapButton		m_Bmnt;							//按钮
	int					m_Num;							//当前下注数
	int				m_iMinNote;				    	//最小注
	int				m_iThisLimit;					    //当前极限注数
	enum			{ IDD = IDD_EASY_LIST };		     	//ID 号码

	//函数定义
public:
	//构造函数
	CeasyNtList(CWnd * pParent = NULL);
	//更新列表
	void UpdateNumList(int b1=0,int b2=0,int b3=0,int b4=0,int b5=0,int b6=0);
	//设置下注
	void SetNumList(int iThisTurnLimit,int MinNote);
	//更新选择按钮
	void UpdateBtnList(BOOL up1=false,BOOL up2=false,BOOL up3=false,BOOL max=false,BOOL cancel=false);
	//绘画数字
	void DrawNum(CDC * pDC);
	//绘画数字
	void DrawNum(CDC * pDC, int iXPos, int iYPos, UINT uNum);

protected:
	//DDX 支持
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//消息函数
protected:
	//确定函数
	virtual void OnOK();
	//取消函数
	virtual void OnCancel();
	//初始化函数
	virtual BOOL OnInitDialog();
	//下注1消息
	afx_msg void OnNote1();
	//下注2消息
	afx_msg void OnNote2();
	//下注3消息
	afx_msg void OnNote3();
	//最大消息
	afx_msg void OnMax();	
	//取消消息
	afx_msg void OnResetCancel();
   //确定消息
	afx_msg void OnResetOk();
	afx_msg void OnPaint();

	//afx_msg void OnNT()   ;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
	public:
	afx_msg void OnBnClicked7();
public:
	afx_msg void OnBnClicked13();
	//设置起点筹码
	void CeasyNtList::SetJetonStart(int iStart1,int iStart2 = 0,int iStart3 = 0,int iEnd = 0);
	//获取索引值
	int GetIndex(int iScore);

};

