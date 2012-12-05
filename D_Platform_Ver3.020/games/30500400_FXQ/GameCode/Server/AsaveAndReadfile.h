#pragma once


///存储玩家信息
struct playStrData_t
{
	UINT uUserID[PLAY_COUNT];             //玩家id号
	UINT uUserMoney[PLAY_COUNT];         //< 玩家i 剩余钱数
	char nickName[PLAY_COUNT][61];           //玩家昵称
	ULONG dwUserIP[PLAY_COUNT];             //玩家ip地址   
	UINT  iRoomBasePoint;                   //房间倍数
	playStrData_t()
	{
		memset(uUserID,0,sizeof(uUserID));
		memset(uUserMoney,0,sizeof(uUserMoney));
		memset(nickName,0,sizeof(nickName));
	}
};

///封装玩家信息
struct SaveData_t
{
	WORD wTag;
	UINT uTime;
	UINT uLen;
	playStrData_t buffer;
};

///存盘类
class CAsaveAndReadfile
{
public:
	CAsaveAndReadfile(void);
public:
	~CAsaveAndReadfile(void);
	void  Serialize(CArchive&ar);  
	
	void  SaveFileMessage(NetMessageHead * pNetHead, void * pNetData,UINT uDataSize );

	//存储玩家信
	void SavePlayMessage(SaveData_t *pNetPlayMessage,CString strfile);
	int  m_iWeyByte[100];         //每一个数据包的大小
	int  m_iCountMove;            //记录一共有多少个数据包

	//从服务端得到的数据包
	
    //初始时间
	LONG m_firsttime;
	//结束时间
	LONG m_lastlongtime;
	
	CString m_strFile;

};