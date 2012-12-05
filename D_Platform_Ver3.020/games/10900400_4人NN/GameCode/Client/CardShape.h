#pragma once


// CCardShape

class CCardShape : public CWnd
{
	DECLARE_DYNAMIC(CCardShape)

private:
	BYTE			m_byShape;   /**< 牌型 */
	CGameImage      m_imgShape;  /**< 牌图片 */
	CPoint          m_pt;        /**< 窗口位置 */
	Image         * m_pImage;
public:
	CCardShape();
	virtual ~CCardShape();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

public:
	/// 设置显示位置
	void SetPoint(int x, int y);

	/// 显示牌型
	void ShowCardShape(BYTE byShape);

	//<创建区域
	void CreateRgn();
};


