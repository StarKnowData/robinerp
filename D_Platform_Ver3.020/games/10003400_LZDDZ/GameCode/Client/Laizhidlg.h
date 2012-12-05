#pragma once

#include "StdAfx.h"
#include "Resource.h"
#define    IDC_NEXT_GAME   12345
#define    IDC_CANCEL_GAME 12346

//操作掩码
#define	UG_HUA_MASK					0xF0							//花色掩码
#define	UG_VALUE_MASK				0x0F							//数字掩码
//游戏信息类
class CLaiZhiDlg : public CWnd
{
	//变量定义
protected:
	//CFont				m_Font;						//显示字体
//	CString				m_strMessage;				//字符信息
//	CBitmap				m_BackBmp;					//背景
	ReplaceStruct	    m_Replace;
	int                 m_ThisCount;                //当前显示的为第几个用来记录当前页
	bool                m_bPassShow;                //是否绘不出按钮.
	CGameImage			m_bk;
	CGameImage          m_OptionalCardsType;          //在对话显示的可选择牌型
	CGameImage          m_LaiZiCard;                  //癞子牌
	CGameImage			m_Flag;						//标记
	BYTE				m_iViewStation;				//是否为本玩家
	CRect				m_BtnRect0,m_BtnRect1,m_BtnRect2,m_BtnRect3;	//矩形框
//	enum					{ IDD = IDD_GAME_END };			//对话框数据
	//函数定义
public:
	CNormalBitmapButtonEx   m_btNext;       //下一页
	CNormalBitmapButtonEx   m_btCancel;     //取消
	CWnd *m_pParnet;
	//构造函数
	CLaiZhiDlg();
	//析构函数
	virtual ~CLaiZhiDlg();
	//自动调整大小
	void AutoSize(int x,int y);
	//设置信息
	void SetMessage(ReplaceStruct Replace, bool PassShow, bool bFlag = false);
	//下一页
	void OnHitNext();
	//取消
	void OnHitCancel();
	//得到字符
	BOOL GetString(BYTE CardList[], int CardCount,  CString & str);
	int GetCardNum(BYTE iCard) { return (iCard&0x0F)+1; }
	void OnSelect(int Id);
	//消息函数
public:
	//重画函数
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	//获取扑克数值
	BYTE GetCardValue(BYTE bCard) 
	{ 
		//return (bCard&UG_VALUE_MASK);
		BYTE bkk=(bCard&UG_VALUE_MASK)+1;
		if (bkk==14) bkk=1;
		return bkk; 
	}
	//获取扑克花色
	BYTE GetHuaKind(BYTE bCard) { return bCard&UG_HUA_MASK; };
	//获取扑克位置
	BYTE GetCardXPos(BYTE bCard) { return GetCardValue(bCard)-1; };
	//获取扑克位置
	BYTE GetCardYPos(BYTE bCard) { return GetHuaKind(bCard)>>4; };

};
