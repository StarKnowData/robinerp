#pragma once
#include "VideoWndStyle.h"


class CVideoWnd :
	public CWnd
{
public:
	CVideoWnd(void);
public:
	~CVideoWnd(void);
protected:
	DECLARE_DYNCREATE(CVideoWnd)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xf53b5b07, 0xdf60, 0x4df5, { 0x80, 0x35, 0x3a, 0x63, 0xd0, 0x1d, 0x83, 0xca } };
		return clsid;
	};
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL);
	 

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)	;
	 
	virtual BOOL  OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnWndMsg(
		UINT message,
		WPARAM wParam,
		LPARAM lParam,
		LRESULT* pResult 
	);


	// Attributes
public:

	// Operations 	 
public:
	void	LeaveRoom(long roomid);
	void	ActiveVideoClient(LPCTSTR authCode, short codeEncType);
	void	StartVideoClient(LPCTSTR videoserveripaddr, short videoserverport);
	void	SetMessageNotifyHandle(long* phWnd);
	short	SetFortuneImage(LPCTSTR lpImageFile);
	void	SetSnapShotSavePath(LPCTSTR PathStr);
	void    SetRecordFileSavePath(LPCTSTR PathStr);
	short   SetVideoToolBarStyle(long* lpStyle);
	short   SetVideoFrameStyle(long* lpStyle)  ;
	void	RegisterUser(short isVisitor, long userid, LPCTSTR username, LPCTSTR password, short passEncType);
	void	UnRegisterUser(long userid);
	void	EnterRoom(long roomid, LPCTSTR roompass, short passEncType);
	void    AppendFortuneMenuItem(long userid, LPCTSTR menuText, LPCTSTR toolTip, short menuTag, short imageIndex);
	void    ResetFortuneMenu(long userid);
	void    ShowUserPanel(long userid, short bShow, short left, short top, short right, short bottom);
	void	ShowUserPanelEx(long userid, short bShow, short left, short top, short right, short bottom, short style, long* pParentWnd);
	void	UserCameraControl(long userid, short bOpen, long* phWnd, short left, short top, short right, short bottom);
	void    PrepaGetUserList();
	long    FetchNextUserID();
	void	SetUserPicture(long userid, LPCTSTR pathname);
	void	CVideoWnd::Release();
	CString GetUserNameByUserID(long userid);

};
