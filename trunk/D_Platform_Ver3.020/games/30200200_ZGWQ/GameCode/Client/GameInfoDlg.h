#pragma once

#include "Stdafx.h"
#include "Resource.h"

//游戏设置信息类
class CGameInfoDlg : public CCoolView//CGameFaceGo
{
	//变量定义
public:
	enum				{ IDD = IDD_GAME_INFO };			// 对话框数据

	//控件变量
public:	
	CNormalBitmapButtonEx			m_btOk;								//确定按钮
	CNormalBitmapButtonEx			m_btCancel;							//取消按钮
	CWnd*							m_pPP;

	//函数定义
public:
	//构造函数
	CGameInfoDlg(CWnd * pParent=NULL);
	//析够函数
	virtual ~CGameInfoDlg();
	//取消按钮
	virtual void OnCancel();
	//确定按钮
	virtual void OnOK();
	//设置游戏设置
	void SetGameSetInfo(int iJUMinute, int iJuSecond, int iBuMinute, int iBuSecond, int iDuMinute, int iDuSecond);

protected:
	// DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
