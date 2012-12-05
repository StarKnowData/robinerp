#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "afxcmn.h"

//扑克设置信息
struct tagGameSetInfo
{
	int			iJuTimeMinute;//局时分
	int			iJuTimeSecond;//局时秒
	int			iBuTimeMinute;//步时分
	int			iBuTimeSecond;//步时秒
	int			iDuMiaoMinute;//读秒分
	int			iDuMiaoSecond;//读秒秒
	
	tagGameSetInfo()
	{
		iJuTimeMinute = 10;
		iJuTimeSecond = 15;
		iBuTimeMinute = 3;
		iBuTimeSecond = 15;
		iDuMiaoMinute = 5;
		iDuMiaoSecond = 25;
	
	}
};

//牌局设置类
class CPlaySetDlg : public CCoolView//CGameFaceGo//CAFCBaseDialog
{
	//变量定义
public:
	tagGameSetInfo		m_GameSetInfo;					//游戏设置信息
	enum				{ IDD = IDD_SET_PLAY };			//对话框数据

	//控件变量
public:
	CNormalBitmapButtonEx			m_btOk;							//确定按钮
	CNormalBitmapButtonEx			m_btCancel;						//取消按钮
	CWnd*							m_pPP;
	//函数定义
public:
	//构造函数
	CPlaySetDlg(CWnd * pParent=NULL);
	//析够函数
	virtual ~CPlaySetDlg();
	//初始化函数
	virtual BOOL OnInitDialog();
	//取消按钮
	virtual void OnCancel();
	//确定按钮
	virtual void OnOK();
	//设置游戏设置
	void SetGameSetInfo(int iCardCount = 0);
	//获取游戏设置
	tagGameSetInfo * GetGameSetInfo();

protected:
	// DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
