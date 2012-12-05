#pragma once
#include"Resource.h"


// CDialect 对话框

class CDialect : public CDialog
{
	DECLARE_DYNAMIC(CDialect)

public:
	CDialect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialect();

// 对话框数据
	enum { IDD = IDD_DIALECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//初始化对话框
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	

public:

	CGameImage				  m_bk;			//背景图
	CNormalBitmapButtonEx     m_btOk ;          //确定按钮

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
};
