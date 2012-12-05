#pragma once

#include "StdAfx.h"
#include "Resource.h"
//#include "StationView.h"
//#include "NtList.h"
#include "GameNoteWnd.h"
#include "PlaySetDlg.h"
#include "GameInfoDlg.h"
//#include "GameEndInfoDlg.h"
//#include "BackCardDlg.h"
#include "HaveThing.h"
#include "LeaveMessage.h"
#include "GameCard.h"
#include "Stop.h"
#include "StopMessage.h"
#include "ChessManual.h"
#include "AdmitDefeat.h"
#include "RegretChess.h"
#include "DianMu.h"
#include "MsgBox.h"
#include "GameFinishDlg.h"
#include "GameSet.h"

class CUpGradeDlg;
class CUpGradeView;

//梭哈视图类
class CClientPlayView : public CUsingSkinClass
{

#ifdef	VIDEO
	public:
		CRect				m_RtVideo[2];				//用户的视频窗口位置
#endif

		//用于动画显示
	CPoint                          m_PtGif[PLAY_COUNT];


	//控件变量
public:
	CUpGradeGameCard			m_MeCard;					//棋盘

	CGameSet					m_GameSetDlg;
	CPlaySetDlg					m_GameSet;					//游戏设置
	CGameInfoDlg				m_GameInfo;					//游戏信息
	CGameNoteWnd				m_GameNoteView;				//游戏信息
//	CStationView				m_StationView;				//状态窗口
	CMsgBox						m_msgbox;					//显示消息框
	CLeaveMessage				m_ThingMessage;				//离开消息
	CHaveThing					m_HaveThing;				//有事离开
	CStop						m_StopThing;				//求和
	CStopMessage				m_StopMessage;				//求和对应
	CAdmitDefeat				m_AdmitDefeat;				//认输
	CChessManual				m_ChessManual;				//棋谱
	CRegretChess				m_RegretChess;				//悔棋
	CDianMu						m_DianMu;					//点目
	CGameFinishDlg				m_Result;					//游戏结束信息

	CNormalBitmapButtonEx		m_btContinue;				//继续按钮
	CNormalBitmapButtonEx		m_btLeave;					//离开
	CNormalBitmapButtonEx		m_btStop;					//求和
	CNormalBitmapButtonEx		m_btAdmitDefeat;			//认输
	CNormalBitmapButtonEx		m_btRegretChess;			//悔棋
	CNormalBitmapButtonEx		m_btChessManual;			//点目
	CNormalBitmapButtonEx		m_btFinishDianMu;			//完成点目
	CNormalBitmapButtonEx		m_btThing;					//有事要走
	//函数定义
public:
	//构造函数
	CClientPlayView();
	//析构函数
	virtual ~CClientPlayView();

	//重载函数
public:
	//重置界面函数
	virtual void ResetGameView();
	//绘画界面函数
	virtual void DrawViewFace(CDC * pDC, int iWidth, int iHeight);
	//更新用户资料
	virtual void UpdateUserInfo(BYTE bViewStation);
	
	virtual void FixControlSize(int,int);
	//功能函数
public:
	void TransparentBlt2( HDC hdcDest,      // 目标DC
					int nXOriginDest,   // 目标X偏移
					int nYOriginDest,   // 目标Y偏移
					int nWidthDest,     // 目标宽度
					int nHeightDest,    // 目标高度
					HDC hdcSrc,         // 源DC
					int nXOriginSrc,    // 源X起点
					int nYOriginSrc,    // 源Y起点
					int nWidthSrc,      // 源宽度
					int nHeightSrc,     // 源高度
					UINT crTransparent  // 透明色,COLORREF类型
					);
	//消息函数
protected:
	//建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	DECLARE_MESSAGE_MAP()
	//按钮消息函数
public:
	//按钮消息
	void OnHitButton(UINT uID);

public:
#ifdef	VIDEO
	BOOL						m_bWatch;    ///自己是否为观战
	CGameImage					m_pVideoFrame;	//视频背景
	///将此昵称的玩家视频窗口矩形写入参数rect,并返回TRUE;没找到返回falst
	BOOL						GetVideoRect(CString  strNickname, RECT& rect, CString& pic);
#endif

};
