#include "Stdafx.h"
#include <afxdllx.h>
#include "Resource.h"

#define IDI_CLIENT_LIST                 1000
#define IDI_CLIENT_ROOM                 1001

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE GameClientDLL = { NULL, NULL };
DWORD      g_bucFileHandle;  //buc�ļ����

//DLL ��ں���
extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (!AfxInitExtensionModule(GameClientDLL, hInstance)) return 0;
		//::BZInit();
		new CDynLinkLibrary(GameClientDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		AfxTermExtensionModule(GameClientDLL);
	}
	return 1;
}

/********************************************************************************************/

//�ȼ��жϺ����������Ϸ��
extern "C" __declspec(dllexport) TCHAR * GetGameOrderName(__int64 dwPoint)
{
	static __int64 uBasePoint[18]=
	{
		0,100,200,400,
		800,1600,3200,6400,		
		12800,25600,51200,102400,
		204800,409600,819200,1638400,
		3276800,6553600
	};
	static TCHAR * szOrderName[18]=
	{
		TEXT("�̹�"),TEXT("����"),TEXT("ƶũ"),TEXT("��ũ"),
		TEXT("��ũ"),TEXT("�ƹ�"),TEXT("����"),TEXT("����"),
		TEXT("С����"),TEXT("�����"),TEXT("С����"),TEXT("�����"),
		TEXT("֪��"),TEXT("֪��"),TEXT("�ܶ�"),TEXT("Ѳ��"),
		TEXT("ة��"),TEXT("����")
	};
	for (int i=0;i<18;i++)	if (dwPoint<uBasePoint[i]) return szOrderName[i];
	return TEXT("�����");
}

/********************************************************************************************/

//������Ϸ�ͻ���
//�ͻ�����������
GETCLIENTINFO;
GETGAMEICON(NAME_ID);
//GETFRAMEINTERFACE(CClientGameDlg)
GETORDERFUNCTION(GetGameOrderName);

/********************************************************************************************/