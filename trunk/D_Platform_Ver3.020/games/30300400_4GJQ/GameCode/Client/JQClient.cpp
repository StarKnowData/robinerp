#include "Stdafx.h"
#include <afxdllx.h>
#include "Resource.h"
#include "ClientGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE GameClientDLL = { NULL, NULL };

/**
 * DLL 入口函数
 */
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

/**
 * 等级判断函数（梭哈游戏）
 */
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
		TEXT("工兵"),TEXT("副班长"),TEXT("正班长"),TEXT("副排长"),
		TEXT("正排长"),	TEXT("副连长"),	TEXT("正连长"),TEXT("副营长"),
		TEXT("正营长"),TEXT("副团长"),TEXT("正团长"),TEXT("副旅长"),
		TEXT("正旅长"),	TEXT("副师长"),TEXT("正师长"),TEXT("副军长"),
		TEXT("正军长"),TEXT("副司令"),TEXT("司令"),TEXT("军区司令"),
		TEXT("三军总司令")
	};
	for (int i=0;i<21;i++)	
		if (dwPoint<uBasePoint[i]) 
			return szOrderName[i];
	return TEXT("军委主席");
}

/********************************************************************************************/
/**
 * 启动游戏客户端
 * 客户端引出函数
 */
GETCLIENTINFO;
GETGAMEICON(NAME_ID);
GETFRAMEINTERFACE(CClientGameDlg)
GETORDERFUNCTION(GetGameOrderName);

/********************************************************************************************/
