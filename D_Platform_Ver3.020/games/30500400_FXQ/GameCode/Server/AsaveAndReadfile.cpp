#include "StdAfx.h"
#include "AsaveAndReadfile.h"



/** 
* 默认的构造函数, 初始化数据
* 
*/
CAsaveAndReadfile::CAsaveAndReadfile(void)
{
	m_iCountMove = 0;
	memset(m_iWeyByte,0,sizeof(m_iWeyByte));
	m_firsttime = 0;
	m_lastlongtime = 0;
}

/** 
* 默认的构造函数
* 
*/
CAsaveAndReadfile::~CAsaveAndReadfile(void)
{
}



/** 
* 存储服务端发送的数据包
*
* @param pNetHead网络数据包结构头
*
* @param pNetData 数据包
*
* @pararm uDataSize数据包的大小
*/
void CAsaveAndReadfile::SaveFileMessage( NetMessageHead * pNetHead, void * pNetData, UINT uDataSize )
{
	CFile  file; 
	CFileFind   finder;
	long ltime = 0;
	bool bfindfile = false;
	if ( finder.FindFile(m_strFile))
	{
		if( file.Open(m_strFile,CFile::modeWrite | CFile::typeBinary) )  
		{
			bfindfile = true;
		}
	}
	else
	{
		if( file.Open(m_strFile,CFile::modeWrite | CFile::modeCreate | CFile::typeBinary) )  
		{
			bfindfile = true;
		}
	}
	if( bfindfile )  
	{  
		//追加模式
		file.SeekToEnd();
		m_lastlongtime = GetTickCount();
		
		if ( m_firsttime == 0 )
		{
			ltime = 1000;
		}
		else
		{
			ltime = m_lastlongtime - m_firsttime;
		}
		file.Write(&ltime,sizeof(long));
		m_firsttime = m_lastlongtime;
		file.Write(pNetHead,sizeof(NetMessageHead));
		UINT  length = uDataSize;
 
		file.Write(&length,sizeof(length));
		if ( length != 0 )
		{
			file.Write(pNetData,uDataSize);
		}
		file.Close();
		
	}
	
}

/** 
* 存储玩家信息
*
* @param pNetPlayMessage玩家信息
*
* @param strfile 存盘的目录
*
*/
void CAsaveAndReadfile::SavePlayMessage(SaveData_t *pNetPlayMessage,CString strfile)
{
	m_strFile = strfile;
	CFile  file; 
	CFileFind   finder;
	bool bfindfile = false;
	if ( finder.FindFile(strfile))
	{
		if( file.Open(strfile,CFile::modeWrite | CFile::typeBinary) )  
		{
			bfindfile = true;
		}
	}
	else
	{
		if( file.Open(strfile,CFile::modeWrite | CFile::modeCreate | CFile::typeBinary) )  
		{
			bfindfile = true;
		}
	}
	if( bfindfile )  
	{  
		//追加模式
		file.SeekToEnd();
		file.Write(pNetPlayMessage,sizeof(SaveData_t));
		file.Close();
	}
}

