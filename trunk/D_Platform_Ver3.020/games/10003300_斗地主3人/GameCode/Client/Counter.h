#pragma once


// CCounter

class CCounter : public CWnd
{
	DECLARE_DYNAMIC(CCounter)

public:
	CCounter();
	virtual ~CCounter();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLookClose();

	afx_msg void OnLeaveNum() ; 
	afx_msg void OnHaveNum() ; 

	void  DrawHistoryInfo(CDC *pDC);    
	void  ReSetDlg();

public:
	CGameImage			          m_bglook;
	CNormalBitmapButtonEx         m_btnLookclose;  //关闭按钮
	CNormalBitmapButtonEx         m_btnleaveNum;  //关闭按钮
	CNormalBitmapButtonEx         m_btnHaveNum;  //关闭按钮
		
	BOOL                          m_bShowLeaveNum;  //是否显示剩余张数
	
	int                           m_iHistoryCard[20] ; //记录每种牌出的张数
	
};


