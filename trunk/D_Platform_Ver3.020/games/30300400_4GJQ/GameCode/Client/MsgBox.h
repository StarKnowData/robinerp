#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <afxwin.h>


#define IDR_HIDE		1
/// CMsgBox 对话框
class CMsgBox : public CDialog
{
	DECLARE_DYNAMIC(CMsgBox)

public:
	/// 标准构造函数
	CMsgBox(CWnd* pParent = NULL);   
	virtual ~CMsgBox();

	/// 对话框数据
	enum { IDD = IDD_MSGBOX };
	CString m_msg;
	int		m_Time;
	CGameImage		m_bkImg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	/// 自动调整大小
	void AutoSize(int x,int y);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
public:
	CNormalBitmapButtonEx m_btcancel;
	CNormalBitmapButtonEx m_btleave;
	void ShowMsg(TCHAR  szMsg[], int time, bool Showleave, GameResult gameResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
private:
	GameResult	m_iFinish;              ///< 结束信息
	CGameImage	m_Flag;					///< 标记


};
