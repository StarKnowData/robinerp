#pragma once
#include "StdAfx.h"
#include "Resource.h"

// CControlWin 对话框

class CControlWin : public CDialog
{
	DECLARE_DYNAMIC(CControlWin)

public:
	CControlWin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CControlWin();

// 对话框数据IDD_CONTROLWIN
	enum { IDD = IDD_CONTROLWIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	void SetParentWnd(CWnd* pWnd);
};
