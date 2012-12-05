// CenterServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainServer.h"
#include "MainServerDlg.h"
#include "BuildTime.h"
#define IDM_TRAY_NOTIFY_MSG (WM_USER +17)

//#include "DlgSetup.h"

// CCenterServerDlg 对话框

void CMainServerDlg::CheckBanBen()
{
	return ;
	CString sn ="20071030";////截止日期

	long in=atol(sn.GetBuffer (sn.GetLength ()));
	if(in<=0)return ;
	int y1=atoi(sn.Mid (0,4)),
		m1   =atoi(sn.Mid (4,2)),
		d1=atoi(sn.Mid (6,2));

	CTime t1(y1,m1,d1,0,0,0);
	time_t ct;  
	time( &ct ) ;

	CTime t2(ct);

	CTimeSpan tsp;
	tsp=t2-t1;//// 当前日期  - 截止日期

	LONGLONG dd=tsp.GetDays ();

	if(t2>t1)//dd > 0)
	{
		//KillTimer(1);
		//KillTimer(2);
		//KillTimer(3);
		m_GameLogon.StoptService();
		AfxMessageBox("本软件生命周期到期，请重新联系www.bzw.cn获取升级版本。（此提示并非时间限制，而是说明程序寿命已到，获取升级版本是免费的。）");
		CDialog::OnOK ();//theApp.m_pMainWnd->DestroyWindow ();
		return ;
	}
}


void CMainServerDlg::OnBnClickedSetup()
{
	//	CDlgSetup dlg;
	/*	dlg.m_pmsgSendToClient = &this->server.m_msgSendToClient ;
	if(dlg.DoModal () == IDOK)
	{
	server.m_msgSendToClient.m_iMainserverPort = atol(dlg.m_iMainserverPort);
	#define get_string(ss) ( (ss).GetBuffer((ss).GetLength ())   )
	memcpy(server.m_msgSendToClient.m_strGameSerialNO,get_string(dlg.m_strGameSerialNO),20);
	memcpy(server.m_msgSendToClient.m_strMainserverIPAddr,get_string(dlg.m_strMainserverIPAddr),20);
	memcpy(server.m_msgSendToClient.m_strHomeADDR,get_string(dlg.m_strHomeADDR),50);
	memcpy(server.m_msgSendToClient.m_strLoginNewUserADDR,get_string(dlg.m_strLoginNewUserADDR),50);
	memcpy(server.m_msgSendToClient.m_strHelpADDR,get_string(dlg.m_strHelpADDR),50);
	memcpy(server.m_msgSendToClient.m_strBBSADDR,get_string(dlg.m_strBBSADDR),50);
	memcpy(server.m_msgSendToClient.m_strHuaZhangADDR,get_string(dlg.m_strHuaZhangADDR),50);
	memcpy(server.m_msgSendToClient.m_strDownLoadSetupADDR,get_string(dlg.m_strDownLoadSetupADDR),50);
	memcpy(server.m_msgSendToClient.m_strDownLoadUpdatepADDR,get_string(dlg.m_strDownLoadUpdatepADDR),50);
	server.WriteINIFile();

	}*/
}



void OutputFun(char* message)
{
	CString s=message;
	CMainServerDlg* p=(CMainServerDlg*)AfxGetApp()->m_pMainWnd ;
	p->OutputFun(s);

}


void CMainServerDlg::OutputFun(const CString & message)
{
	m_listSysRunInfo.DisplayMsg(COutputDisplay::Message,message);
}

CMainServerDlg::CMainServerDlg(CWnd* pParent /*=NULL*/)
: CDialog(IDD_MAINSERVER_DIALOG, pParent),m_TrayIcon(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SYS_RUN_INFO, m_listSysRunInfo);
	DDX_Control(pDX, IDC_STATIC_STATUSBAR, m_strStatusBar);
}

BEGIN_MESSAGE_MAP(CMainServerDlg, CDialog)
	ON_WM_CREATE()////////////
	ON_WM_SIZE()//////////
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNSTART, OnBnClickedSetup)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_MESSAGE(IDM_TRAY_NOTIFY_MSG,OnTrayIconNotify)///////////
	ON_BN_CLICKED(IDC_BTNNEWS, &CMainServerDlg::OnBnClickedBtnnews)
	ON_REGISTERED_MESSAGE(WM_CREATETRAYBAR, OnCreateTray)
END_MESSAGE_MAP()




//建立函数
int CMainServerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
#define APP_TITLEe "主服务MainServer"
	//系统内部建立
	if (CDialog::OnCreate(lpCreateStruct)==-1) return -1;
	//if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,CRect(0,0,0,0),this,AFX_IDW_PANE_FIRST,NULL))	return -1;

	//建立任务栏图标
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TrayIcon.SetNotifyWnd(this,IDM_TRAY_NOTIFY_MSG);
	m_TrayIcon.SetIcon(hIcon,APP_TITLEe);
	//m_TrayIcon.ShowBalloonTip("正在启动MainServer主服务系统，请稍后...   ",APP_TITLEe);
	SetIcon(hIcon,FALSE);
	DestroyIcon(hIcon);

	m_TrayIcon.ShowBalloonTip("启动MainServer主服务系统成功",APP_TITLEe);
	ShowWindow(SW_SHOW);

	return 0;
}
//任务栏图标消息
LRESULT CMainServerDlg::OnTrayIconNotify(WPARAM wID, LPARAM lEvent)
{
	switch (lEvent)
	{
	case WM_LBUTTONDBLCLK:	//双击事件
		{
			ShowWindow(SW_SHOW);
			//PostQuitMessage(0);
			return 1;
		}
	}
	return 0;
}
//位置消息
void CMainServerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (nType==SIZE_MINIMIZED)	ShowWindow(SW_HIDE);
}

// CCenterServerDlg 消息处理程序

BOOL CMainServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CheckBanBen();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	///RegOutPutFun(::OutputFun);
	SetStatusBar();

	SetTimer(1,1000 ,NULL);
	SetTimer(2,2000 ,NULL);



	ManageInfoStruct Init;
	memset(&Init,0,sizeof(Init));

	//远程数据库
	//DWORD dwIP=0;
	//if (m_SQLIP.GetAddress(dwIP)!=4)
	//{
	//	AfxMessageBox(TEXT("请填写远程数据库 IP！"));
	//	m_SQLIP.SetFocus();
	//	return;
	//}
	lstrcpy(Init.szLogonSQLName,TEXT("sa"));
	//	GetDlgItemText(IDC_SQL_PASS,Init.szLogonSQLPass,sizeof(Init.szLogonSQLPass));
	//wsprintf(Init.szLogonSQLIP,TEXT("%d.%d.%d.%d"),FIRST_IPADDRESS(dwIP),SECOND_IPADDRESS(dwIP),THIRD_IPADDRESS(dwIP),FOURTH_IPADDRESS(dwIP));

	//本地数据库
	//if (m_NativeIP.GetAddress(dwIP)!=4)
	//{
	//	AfxMessageBox(TEXT("请填写本地数据库 IP！"));
	//	m_NativeIP.SetFocus();
	//	return;
	//}
	//lstrcpy(Init.szNativeSQLName,TEXT("sa"));
	//GetDlgItemText(IDC_SQL_PASS2,Init.szNativeSQLPass,sizeof(Init.szNativeSQLPass));
	//wsprintf(Init.szNativeSQLIP,TEXT("%d.%d.%d.%d"),FIRST_IPADDRESS(dwIP),SECOND_IPADDRESS(dwIP),THIRD_IPADDRESS(dwIP),FOURTH_IPADDRESS(dwIP));
	wsprintf(Init.szLogonSQLIP,TEXT("%d.%d.%d.%d"),127,0,0,1);
	wsprintf(Init.szNativeSQLIP,TEXT("%d.%d.%d.%d"),127,0,0,1);
	//启动服务
	if (!m_GameLogon.InitService(&Init))
	{
		OutputFun("初始化服务器失败！");
		AfxMessageBox("InitService Error !");
		return false;
	}
	UINT	errCode;
	if (!m_GameLogon.StartService(errCode))
	{
		CString stip;
		stip.Format("Start Service Failed ,Error Code:%X",errCode);
		OutputFun(stip);
		AfxMessageBox(stip);
		return false;
	}

	//	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	////////////////////////////////////
	////Kylin 20090316添加防止账户同时登陆

	HANDLE hDatabase=m_GameLogon.m_LogonManage.m_SQLDataManage.hDBLogon;
	HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ClearLoginRecord");
	if(hRecord<(HANDLE)0x1000)
		return false;
	sqlSPAddPara(hDatabase,hRecord,"@ZID",m_GameLogon.m_LogonManage.m_ID);
	sqlSPExec(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	////////////////////////////////////

	CString s;
	s.Format("MainServer启动成功 支持最大人数:%d Port:%d   Spe:110 Tec:29001  普通规则  允许进入 ",
		m_GameLogon.m_LogonManage.m_uMaxPeople,m_GameLogon.m_LogonManage.m_nPort );

	OutputFun(s);

	//GetDlgItem(IDC_EDIT3)->SetWindowText(s);//"启动成功\r\nPort:5050\r\nSpe:110 Tec:29001\r\n普通规则\r\n允许进入\r\n");

	CString scaption;
	GetWindowText(s);
	scaption.Format("%s v%d.%d.%d %s",s,VER_MAIN,VER_MIDDLE,VER_RESVERSE,VER_BUILDTIME);
	SetWindowText(scaption);


	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	///版权版权版权版权版权版权版权版权版权版权版权版权
		CPaintDC dc(this); // 用于绘制的设备上下文
		dc.SetBkMode(TRANSPARENT);//透明的, 显然的, 明晰的背景颜色
		dc.SetTextColor(RGB(255, 255, 255));//黄色
		dc.DrawText(TMLcopyright,lstrlen(TMLcopyright),CRect(2,457,720,836),DT_TOP|DT_RIGHT|DT_NOCLIP|DT_SINGLELINE);
		dc.SetTextColor(RGB(200, 200, 200));//黄色
		dc.DrawText(TMLcopyright,lstrlen(TMLcopyright),CRect(1,456,720,836),DT_TOP|DT_RIGHT|DT_NOCLIP|DT_SINGLELINE);
		dc.SetTextColor(RGB(0, 0, 0));//黄色
		dc.DrawText(TMLcopyright,lstrlen(TMLcopyright),CRect(0,455,720,836),DT_TOP|DT_RIGHT|DT_NOCLIP|DT_SINGLELINE);
		CDialog::OnPaint();
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMainServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainServerDlg::OnDestroy()
{
	m_GameLogon.UnInitService();
	CDialog::OnDestroy();

	// TODO: 在此添加消息处理程序代码
}

void CMainServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nID)
	{
	case SC_CLOSE:
		//		server.Stop();
		KillTimer(1);
		CDialog::OnSysCommand(nID, lParam);
		return;;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CMainServerDlg::SetStatusBar()
{
	CString s1;
	//	s1.Format (" 总联结数:%d",server.GetClientCount ());
	m_strStatusBar.SetWindowText (s1);

}

void CMainServerDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1)
		SetStatusBar();

	if(nIDEvent == 2)
	{
		KillTimer(2);
		ShowWindow(SW_HIDE);
	}

	CDialog::OnTimer(nIDEvent);
}


void CMainServerDlg::OnBnClickedOk()
{
	//	server.Stop();
	KillTimer(1);
	OnOK();
}


void CMainServerDlg::OnBnClickedBtnnews()
{
	m_GameLogon.m_LogonManage.m_TCPSocket.SendDataBatch(NULL,0,MDM_GP_MESSAGE,ASS_GP_NEWS_SYSMSG,0);
	return;
}

LRESULT CMainServerDlg::OnCreateTray(WPARAM wp, LPARAM lp)
{
#define APP_TITLE "主服务MainServer"
	m_TrayIcon.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),APP_TITLE,TRUE);
	return 0;
}