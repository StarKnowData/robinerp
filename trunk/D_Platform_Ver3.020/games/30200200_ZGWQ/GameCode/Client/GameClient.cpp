#include "Stdafx.h"
#include <afxdllx.h>
#include "Resource.h"
#include "ClientGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE GameClientDLL = { NULL, NULL };

//DLL 入口函数
extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (!AfxInitExtensionModule(GameClientDLL, hInstance)) return 0;
		new CDynLinkLibrary(GameClientDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		AfxTermExtensionModule(GameClientDLL);
	}
	return 1;
}

/********************************************************************************************/

//等级判断函数（梭哈游戏）
extern "C" __declspec(dllexport) TCHAR * GetGameOrderName(__int64 dwPoint)
{
	static __int64 uBasePoint[21]=
	{
		30,100,200,500,
		1000,1600,3000,5000,
		10000,20000,50000,80000,
		120000,200000,300000,400000,
		500000,600000,800000,1000000,
		1500000
	};
	static TCHAR * szOrderName[21]=
	{
		TEXT("初学者"),TEXT("初学者"),TEXT("刚入门"),TEXT("会一点"),
		TEXT("纯业余"),	TEXT("不入流"),	TEXT("不入段"),TEXT("业余初段"),
		TEXT("业余三段"),TEXT("业余五段"),TEXT("专业一段"),TEXT("专业二段"),
		TEXT("专业三段"),	TEXT("专业四段"),TEXT("专业五段"),TEXT("专业六段"),
		TEXT("专业七段"),TEXT("专业八段"),TEXT("专业九段"),TEXT("超级九段"),
		TEXT("棋圣")
	};
	for (int i=0;i<21;i++)	
		if (dwPoint<uBasePoint[i]) 
			return szOrderName[i];
	return TEXT("棋神");
}

/********************************************************************************************/

//启动游戏客户端
//客户端引出函数
GETCLIENTINFO;
GETGAMEICON(NAME_ID);
GETFRAMEINTERFACE(CClientGameDlg)
GETORDERFUNCTION(GetGameOrderName);

/********************************************************************************************/
