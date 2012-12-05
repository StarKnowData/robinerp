#include "StdAfx.h"
#include <stdio.h>

#include "EntinfoSmsImp.h"

//PJY SMS 通讯实现类//////////////////////////////////////////////////////////////////////////////////

CEntinfoSmsImp::CEntinfoSmsImp(void)
{
}

CEntinfoSmsImp::~CEntinfoSmsImp(void)
{
}

//接口实现////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT CEntinfoSmsImp::SendMessage(char* szPhoneNo,char* szMessage)
{
	CComBSTR bstPhoneNo(szPhoneNo);
	CComBSTR bstMessage(szMessage);
	CComBSTR bstSN("SDK-WSS-010-01736");
	CComBSTR bstPwd("0C6C7B645C7BC0153487CBB7C57B8ABC");
	CComBSTR bstExt("");
	CComBSTR bstDateTime("");
	CComBSTR bstRRID("");
	CComBSTR bstResult;

// 	SYSTEMTIME sys_t;
// 	char szTime[32] = {0};
// 	::GetLocalTime(&sys_t);
// 	_stprintf(szTime,"%02d:%02d:%02d",sys_t.wHour,sys_t.wMinute,sys_t.wSecond);
// 	CComBSTR bstDateTime(szTime);

// 	CString str;
// 	str.Format("DServer:CEntinfoSmsImp::SendMessagePhone = %s Message = %s",szPhoneNo,szMessage);
// 	OutputDebugString(str);

	HRESULT hr = CWebServiceT::mt(bstSN,bstPwd,bstPhoneNo,bstMessage,bstExt,bstDateTime,bstRRID,&bstResult);

	wchar_t wszBuf[256] = {0};
	swprintf(wszBuf,L"DSms:Phone = %s Message = %s Result = %s     mt return = 0x%08x",
		bstPhoneNo.m_str,bstMessage.m_str,bstResult.m_str,hr);
	OutputDebugString(CW2A(wszBuf));

	return hr;
}

void CEntinfoSmsImp::ReleaseObject()
{
	OutputTraceStr("Sms: CEntinfoSmsImp::ReleaseObject");
	delete this;
}