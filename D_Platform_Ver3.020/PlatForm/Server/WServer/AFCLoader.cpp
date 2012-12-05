#include "StdAfx.h"
#include "AFCLoader.h"
#include "MainFrm.h"

BEGIN_MESSAGE_MAP(CAFCLoaderApp, CWinApp)
END_MESSAGE_MAP()

//应用程序对象
CAFCLoaderApp theApp;

//构造函数
CAFCLoaderApp::CAFCLoaderApp()
{
}

bool CAFCLoaderApp::CheckBanBen()
{
	return true;
	CString sn ="20071030";////截止日期
	
	long in=atol(sn.GetBuffer (sn.GetLength ()));
	if(in<=0) return false;
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
		//m_GameLogon.StoptService();
		AfxMessageBox("本软件生命周期到期，请重新联系www.bzw.cn获取升级版本。（此提示并非时间限制，而是说明程序寿命已到，获取升级版本是免费的。）");
		//CDialog::OnOK ();//theApp.m_pMainWnd->DestroyWindow ();
		return false;
	}
	return true;
}

//初始化函数
BOOL CAFCLoaderApp::InitInstance()
{
	if(!CheckBanBen()) return true;
	//初始化
	InitCommonControls();
	CWinApp::InitInstance();

	//初始化
	if (!AfxOleInit()||!AfxSocketInit()) return FALSE;
	AfxEnableControlContainer();
	SetRegistryKey(_T("子分布服务器控制系统"));

	//设置程序路径
	TCHAR szModuleName[MAX_PATH];
	DWORD dwLength=GetModuleFileName(AfxGetInstanceHandle(),szModuleName,sizeof(szModuleName));
	szModuleName[dwLength-lstrlen(m_pszExeName)-lstrlen(TEXT(".EXE"))-1]=0;
	SetCurrentDirectory(szModuleName);


	//建立窗口
	
	CMainFrame * pFrame=new CMainFrame;
	m_pMainWnd=pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW,NULL,NULL);
	//pFrame->SetWindowTextA("hepengyu");//SetWindowTitle(TMLcopyright);
	//pFrame->SetTitle(TMLcopyright);
	return TRUE;
}
