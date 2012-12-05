#pragma once

#include "Resource.h"
// CBeginAnimal 对话框

class CBeginAnimal : public CDialog
{
	DECLARE_DYNAMIC(CBeginAnimal)
private:
	CGameImage			m_bk;								//背景图
	
public:
	CBeginAnimal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBeginAnimal();

// 对话框数据
	enum { IDD = IDD_BEGIN_ANIMAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//初始化函数
	virtual BOOL OnInitDialog();

protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	void FixCardControl(int x,int y);
};
