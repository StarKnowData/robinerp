#include "StdAfx.h"
#include "jqlogic0.h"


void  Testlog(TCHAR *pMessage)
{
	try
	{
		char FileName[50];
		wsprintf(FileName,"e:\\syslog%d.txt\0",GetCurrentProcessId());
		//AfxMessageBox(FileName);
		CFile syslog;
		syslog.Open(FileName,CFile::modeNoTruncate| CFile::modeCreate |CFile::modeReadWrite);
		syslog.SeekToEnd();
		syslog.Write(pMessage,strlen(pMessage));

		syslog.SeekToEnd();
		TCHAR nextLine[] = "\r\n";
		syslog.Write(nextLine,strlen(nextLine));

		syslog.Close();
	}
	catch(CException *e)
	{
		//AfxMessageBox("some exception!");
		e->Delete();
		return ; 
	}
}

void CJqLogic0::Rotate(int& iTo,int& jTo,int ifrom,int jfrom ,int angle)
{
	int ii=ifrom,jj=jfrom;
	switch(angle)//DevSite)
	{
	case 90://DESK_PEOPLE_SITE_LEFT:
			{
				int i=ii;
				ii=jj;
				jj=-i;
				jj += 16;
			}
			break;
	case 180://DESK_PEOPLE_SITE_TOP:
			ii=-ii + 16;
			jj=-jj + 16;
			break;
	case 270://DESK_PEOPLE_SITE_RIGHT:
			{
				int i=ii;
				ii=-jj;
				jj=i;

				ii+=16;
			}
			break;
		case 0://DESK_PEOPLE_SITE_BOTTOM:
			break;

        default:
			return;

		}///switch

	iTo=ii;jTo=jj;

	
}

int CJqLogic0::Compare(int q1,int q2)
{
	if(q1 == JQ_TYPE_NONE && q2 == JQ_TYPE_NONE)return 0;
	if( q1 == JQ_TYPE_NONE )return -1;
	if( q2 == JQ_TYPE_NONE )return 1;
	int n1=GET_A_JQ_NAME(q1),n2=GET_A_JQ_NAME(q2);
	if(n1 == n2)return 0;
	///棋子名不同
	if(n1 == JQ_TYPE_NAME_ZD || n2 == JQ_TYPE_NAME_ZD)return 0;
	if(n1 == JQ_TYPE_NAME_JQ )return -1;
	if(n2 == JQ_TYPE_NAME_JQ )return 1;
	
	if(n1 == JQ_TYPE_NAME_DL )
	{
		if(n2 == JQ_TYPE_NAME_GB)return -1;
		return 1;
		
	}
	if(n2 == JQ_TYPE_NAME_DL )
	{
		if(n1 == JQ_TYPE_NAME_GB)return 1;
		return -1;
	}
	return n1 > n2 ? 1 : -1;
}

/*	
void CJqLogic0::InitJq(bool bStart)
{
	for(int i=0;i<MAX_I;i++)
		for(int j=0;j<MAX_J;j++)
	        mBoard[i][j]=JQ_TYPE_NONE;
	if(!bStart)return;
if(m_iMyColor < 0 )return;

	 mBoard[11][6]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_YZ);
	 mBoard[11][7]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_GB);
	 mBoard[11][8]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_JZ);
	 mBoard[11][9]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_GB);
	 mBoard[11][10]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_YZ);

	 mBoard[12][6]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_PZ);
	 mBoard[12][8]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_LIANZ);
	 mBoard[12][10]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_PZ);

	 mBoard[13][6]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_SZ);
	 mBoard[13][7]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_ZD);
	 mBoard[13][9]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_ZD);
	 mBoard[13][10]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_SZ);

	 mBoard[14][6]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_TZ);
	 mBoard[14][8]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_LIANZ);
	 mBoard[14][10]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_TZ);

	 mBoard[15][6]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_LIZ);
	 mBoard[15][7]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_SL);
	 mBoard[15][8]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_GB);
	 mBoard[15][9]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_LIZ);
	 mBoard[15][10]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_DL);

	 mBoard[16][6]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_DL);
	 mBoard[16][7]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_JQ);
	 mBoard[16][8]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_DL);
	 mBoard[16][9]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_PZ);
	 mBoard[16][10]=MAKE_A_JQ(m_iMyColor,JQ_TYPE_NAME_LIANZ);

	 
}

*/

/*i
void CJqLogic0::LogicCordToDevCord(int DevSite,int& iTo,int& jTo,int ifrom,int jfrom )
{
	nt ii=ifrom,jj=jfrom;
	switch(DevSite)
	{
		case DESK_PEOPLE_SITE_LEFT:
			{
				int i=ii;
				ii=jj;
				jj=-i;
				jj += 16;
			}
			break;
		case DESK_PEOPLE_SITE_TOP:
			ii=-ii + 16;
			jj=-jj + 16;
			break;
		case DESK_PEOPLE_SITE_RIGHT:
			{
				int i=ii;
				ii=-jj;
				jj=i;

				ii+=16;
			}
			break;
		case DESK_PEOPLE_SITE_BOTTOM:
			break;

        default:
			return;

		}///switch

	iTo=ii;jTo=jj;

	
}

*/













































