#pragma once
#include "Stdafx.h"
#include "Resource.h"
#include "afxcmn.h"

// CDisplayTalkDialog dialog

class CDisplayTalkDialog : public CDialog
{
	DECLARE_DYNAMIC(CDisplayTalkDialog)

public:
	CDisplayTalkDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDisplayTalkDialog();

// Dialog Data
	enum { IDD = IDD_DISPLAY_TALK };
private:
	CString m_strCurrentText;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//---------------对话框中的一些参数--------------------
	CFont  m_font;
	CString m_msg;
	COLORREF  m_crFont;
	CGameImage m_img;
	int		m_Tran;	//透明程度
 	//-------------以下2变量联合起来使用-------------------
	CRect m_rectCurrentLine; //当前行的范围,通常只用y值
	CPoint m_ptCurrent;      //当前行的输出位置，只有x有效

	CRect  m_rectClient;
	BOOL   m_bWriteDC;  //是否还可以向DC输出文字
	CDC*   m_pDC;       //为OnPaint重绘中统一的DC.
    int    m_fontHeight;  //选进DC中字体的高度
	int		m_viewid;
	int    m_nJianGe;  //聊天框与图片bottom的间隔
	BOOL   m_bPreIsText; //在输入图片之前是否是文字
	BOOL   m_bIsFirst;   //表示本次输出图片或者文字是否为第一次，若为第一次则无需调整坐标
	int    m_nLineJianGe;  //行与行之间的之隔
	int    m_nTextToImage;  //文字与图片之间的间隔,也是图片与图片间的间隔
public:
	virtual BOOL OnInitDialog();
	void DisplayTalkText(TCHAR* szCharString);   //设定聊天内容------外部接口

    CTrueItem* TranslateChar(TCHAR * szCharString, int iCharLength, int & iPassCharCount);
    void InsertBitmapToDC(HBITMAP hBitmap);
    HBITMAP CopyBitmap(HBITMAP hSourceHbitmap);
    void TransparentBltBitmap(HBITMAP hBitmap,CPoint ptCurrent,COLORREF crTrans);  //透明化传输位图到DC

    void InsertCharToDC(const TCHAR * szCharString);
 	BOOL IsNewLine(const TCHAR* szMsg);            //判断显示szMsg时是否需要换行
	int  ThisLineContainChar(const TCHAR* szMsg);  //判断本行可容纳的字符数
	void CopyNumChar(const TCHAR* pSrc,int iStart,int iEnd,TCHAR* pDst);   //将pSrc自第iStart到第iEnd个字符复制到pDst中,加'\0'

	void DisplayOmit();        //显示省略号
public:
 	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnPaint();
 public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
