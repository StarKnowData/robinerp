#include "StdAfx.h"
#include "BClientSocket.h"
#include "gameplacemessage.h"
#include "ZClientSocket.h"

#include "cfgEngine.h"
#include "wCore2.h"

ifstream inf("IP.txt");
CBClientSocket::CBClientSocket(void): m_ClientSocket(this)
{
	inf>>m_IP;
	if (m_IP == "") m_IP = "127.0.0.1";
}

CBClientSocket::~CBClientSocket(void)
{
	m_ClientSocket.CloseSocket(true);
}
 

//网络读取消息
bool CBClientSocket::OnSocketReadEvent(NetMessageHead* pNetHead, void* pNetData, UINT uDataSize, CTCPClientSocket* pClientSocket)
{
	switch (pNetHead->bMainID)
	{
		case MDM_CONNECT:	//连接消息 
		{
			return OnConnect(pNetHead, pNetData, uDataSize, pClientSocket);
		}
		case MDM_GP_REQURE_GAME_PARA:
		{
			return OnRequreGamePara(pNetHead, pNetData, uDataSize, pClientSocket);
		}
	}
	return true;
}

//网络连接消息
bool CBClientSocket::OnSocketConnectEvent(UINT uErrorCode, CTCPClientSocket* pClientSocket)
{
	if (uErrorCode!=0)	//连接出现错误
	{
		ConnectToServer();
		return true;
	}
	return true;//连接成功
}

//网络关闭消息
bool CBClientSocket::OnSocketCloseEvent()
{
	return true;
}

//连接到服务器
bool CBClientSocket::ConnectToServer()
{
	//授权检测
	long timeStamp=coreGetTimeStamp();

	long licExpires=coreGetLicenseExpires();

	if(timeStamp>licExpires)
	{
		PostQuitMessage(0);
		return false;
	}

	int static iConnect = 0;
	iConnect++;
	if (iConnect > 3)
	{
		AfxMessageBox("连接中心服务器不成功,程序将退出,请稍后再试!");
		PostQuitMessage(0);
		return false;
	}
	if (m_ClientSocket.Connect(m_IP.c_str(), CENTER_SERVER_PORT) == false)
		ConnectToServer();
	return true;
}


bool CBClientSocket::OnConnect(NetMessageHead* pNetHead, void* pNetData, UINT uDataSize, CTCPClientSocket* pClientSocket)
{
	if (pNetHead->bAssistantID == ASS_NET_TEST)	//网络测试信息
	{
		pClientSocket->SendData(MDM_CONNECT,ASS_NET_TEST,0);//连接消息类型
		return true;
	}
	else if ((pNetHead->bAssistantID == 2)||(pNetHead->bAssistantID == 3))	//连接成功
	{
		MSG_S_ConnectSuccess * _p = (MSG_S_ConnectSuccess *)pNetData;
		if (_p != NULL)
		{
			pClientSocket->SetCheckCode(_p->i64CheckCode, SECRET_KEY);
		}

 		 m_ClientSocket.SendData(0, 0, MDM_GP_REQURE_GAME_PARA, 0, 0);
		 return true;
	}
}

bool CBClientSocket::OnRequreGamePara(NetMessageHead* pNetHead, void* pNetData, UINT uDataSize, CTCPClientSocket* pClientSocket)
{
	CenterServerMsg* msg=(CenterServerMsg*)pNetData;
	if (msg)
	{
		m_par.m_iMainserverPort=msg->m_iMainserverPort;
		m_par.m_nHallInfoShowClass=msg->m_nHallInfoShowClass;
		memcpy(m_par.m_strGameSerialNO, msg->m_strGameSerialNO, 20);
		memcpy(m_par.m_strMainserverIPAddr, msg->m_strMainserverIPAddr, 20);
		memcpy(m_par.m_strHomeADDR, msg->m_strHomeADDR, 50);
		memcpy(m_par.m_strWebRootADDR, msg->m_strWebRootADDR, 50);
		memcpy(m_par.m_strHelpADDR, msg->m_strHelpADDR, 50);
		memcpy(m_par.m_strDownLoadSetupADDR, msg->m_strDownLoadSetupADDR, 50);
		memcpy(m_par.m_strDownLoadUpdatepADDR, msg->m_strDownLoadUpdatepADDR, 50);
		memcpy(m_par.m_strRallAddvtisFlashADDR, msg->m_strRallAddvtisFlashADDR, 50);
		memcpy(m_par.m_strRoomRollADDR, msg->m_strRoomRollADDR, 100);
		m_par.m_nEncryptType = msg->m_nEncryptType;		//平台加密方式
		m_par.m_nFunction = msg->m_nFunction;
		m_par.m_lNomalIDFrom = msg->m_lNomalIDFrom;
		m_par.m_lNomalIDEnd = msg->m_lNomalIDEnd;


		AfxGetMainWnd()->PostMessage(MSG_CMD_GET_GAMEPARA, (WPARAM)(&m_par), 0);
	}
	return true;
}