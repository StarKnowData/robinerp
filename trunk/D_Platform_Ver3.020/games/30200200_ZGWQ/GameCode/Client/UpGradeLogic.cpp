#include "StdAfx.h"
#include "UpGradeLogic.h"


static int ADDI[4] = {0,-1,0,1};
static int ADDJ[4] = {-1,0,1,0}; //每个子直线紧邻的四的方向


//构造函数
CUpGradeGameLogic::CUpGradeGameLogic(void)
{
		::memset(m_shizi,0,sizeof(m_shizi));
}

BOOL CUpGradeGameLogic::CanAddQiZi(int curI, int curJ, int myFlag, int qi[][21])
{
	if (qi[curI][curJ] != WQ_FLAG_NONE) return FALSE;
	int flag = WQ_FLAG_BLACK;
	if (myFlag == WQ_PLAY_FLAG_WHITE) flag = WQ_FLAG_WHITE;
	qi[curI][curJ] = flag;
		
	int n = AddNewQiZi(curI,curJ,myFlag,qi);

	if (n < 0)
	{
		qi[curI][curJ] = WQ_FLAG_NONE;
		return FALSE;
	}
	for (int i = 1;i < 20;i++)
		for (int j = 1;j < 20;j++)
		{
			if (qi[i][j] == WQ_FLAG_CUR_BLACK || qi[i][j] == WQ_FLAG_CUR_WHITE) qi[i][j] -= 10;
		}
		
	qi[curI][curJ] = flag + 10;
	
	return TRUE;
}


int CUpGradeGameLogic::AddNewQiZi(int pi, int pj, int iFlag, int qi[][21])
{
	if (pi >= WQ_MAX_I - 1 || pj >= WQ_MAX_J -1 || pi < 1 || pj < 1) return -1;

	int totalKilledZi = 0;

	m_iDJCurPutI = pi;
	m_iDJCurPutJ = pj;

	int killedI,killedJ;
	
	if (iFlag == WQ_PLAY_FLAG_WHITE) //add white
	{
		int n = KillAllQiZi(&killedI,&killedJ,WQ_FLAG_BLACK,qi);
		if (n < 0) return -1;
		if (n == 1)
		{
			///AfxMessageBox("n == 1");
			if (m_iDJCurPutI == m_iDJLastKilledI && m_iDJCurPutJ == m_iDJLastKilledJ)//打劫
			{
				qi[pi][pj] = WQ_FLAG_NONE;
				qi[killedI][killedJ] = WQ_FLAG_CUR_BLACK;
				//AfxMessageBox("打劫");
				return -1;
			}
			if (!(killedI == pi && killedJ == pj))
			{
				m_iDJLastKilledI = killedI;
				m_iDJLastKilledJ = killedJ;
			}
		}
		else
		{
			m_iDJLastKilledI = -1;
			m_iDJLastKilledJ = -1;
		}

		totalKilledZi += n;
		n = KillAllQiZi(&killedI,&killedJ,WQ_FLAG_WHITE,qi);
		if (n < 0) return -1;
		totalKilledZi += n;
	}
	else if (iFlag == WQ_PLAY_FLAG_BLACK)//add black
	{
		
		int n = KillAllQiZi(&killedI,&killedJ,WQ_FLAG_WHITE,qi);
		if (n < 0) return -1;
		if (n == 1)
		{	
			if (m_iDJCurPutI == m_iDJLastKilledI && m_iDJCurPutJ == m_iDJLastKilledJ)
			{
				qi[pi][pj] = WQ_FLAG_NONE;
				qi[killedI][killedJ] = WQ_FLAG_CUR_WHITE;
				
				return -1;
			}
			if (!(killedI == pi && killedJ == pj))
			{
				m_iDJLastKilledI = killedI;
				m_iDJLastKilledJ = killedJ;
			}
		}
		else
		{
			m_iDJLastKilledI = -1;
			m_iDJLastKilledJ = -1;
		}

		totalKilledZi += n;
		n = KillAllQiZi(&killedI,&killedJ,WQ_FLAG_BLACK,qi);
		if (n < 0) return -1;
		totalKilledZi += n;
	}

	return totalKilledZi;
	return 0;
}


int CUpGradeGameLogic::KillAllQiZi(int *killedI, int *killedJ, int myFlag, int qi[][21])
{
	if (!(myFlag == WQ_FLAG_BLACK || myFlag == WQ_FLAG_WHITE)) return -1;
	int myChessFlag = myFlag;//WQ_FLAG_BLACK;
	int enemyChessFlag = WQ_FLAG_BLACK;
	if (myFlag == WQ_FLAG_BLACK) enemyChessFlag = WQ_FLAG_WHITE;

	int bdChk[WQ_MAX_I][WQ_MAX_J];
	::CopyMemory(bdChk,qi,sizeof(bdChk));

	for (int i = 0;i < WQ_MAX_I;i++)
		for (int j = 0;j < WQ_MAX_J;j++)
		{
			if (i == 0 || i == WQ_MAX_I - 1 || j == 0 || j == WQ_MAX_J - 1)
			{
				bdChk[i][j] = enemyChessFlag;
				continue;
			}

			if (bdChk[i][j] == WQ_FLAG_CUR_BLACK || bdChk[i][j] == WQ_FLAG_CUR_WHITE)
			{
				bdChk[i][j] -= 10;
				continue;
			}
		}

	int totalKilledZi = 0;
	int cii,cjj;

	for (int i = 1;i < WQ_MAX_I - 1;i++)
		for (int j = 1;j < WQ_MAX_J - 1;j++)
		{
			int ff = bdChk[i][j];
			if (!(ff == myChessFlag)) continue;
			CStack sChk,sDieZi;
			sChk.Push(i,j);
			bdChk[i][j] = WQ_FLAG_HASCHECKED_QIZI;
			bool bHasDie = true;
				//int ii,jj;
			while (!sChk.bIsEmpty())
			{
				int ii,jj;
				if (!sChk.bPop(&ii,&jj)) return totalKilledZi;
				sDieZi.Push(ii,jj);

				for (int iii = 0;iii < 4;iii++)
				{
					int pi = ii + ADDI[iii],
						pj = jj + ADDJ[iii];
					int f1 = bdChk[pi][pj];
					if (f1 == WQ_FLAG_NONE)
					{
						bHasDie = false;
						continue;
					}
					if (f1 == enemyChessFlag) continue;
					if (f1 == myChessFlag || f1 == myChessFlag + 10)
					{
						bdChk[pi][pj] = WQ_FLAG_HASCHECKED_QIZI;
						sChk.Push(pi,pj);
						continue;
					}

				}//end for
			}//end while
			
			if (!bHasDie) continue;
			
			if (sDieZi.bIsInQ(m_iDJCurPutI,m_iDJCurPutJ)) {return -1;}

			while (!sDieZi.bIsEmpty())
			{
				if (!sDieZi.bPop(&cii,&cjj)) return totalKilledZi;
				*killedI = cii;
				*killedJ = cjj;
				totalKilledZi++;
				qi[cii][cjj] = WQ_FLAG_NONE;
			}

		}//end for

	return totalKilledZi;
	return 0;
}


int CUpGradeGameLogic::GetEmptyFlag(int pi, int pj, int qi[][21])
{
	int flag = WQ_FLAG_NONE;

	for (int i = pi + 1;i < WQ_MAX_I - 1;i++)//bottom
	{
		int f = qi[i][pj];
		if (f == WQ_FLAG_BLACK)
		{
			flag = WQ_FLAG_BLACK;
			break;
		}
		else if (f == WQ_FLAG_WHITE)
		{
			flag = WQ_FLAG_WHITE;
			break;
		}
	}

	for (int i = pi - 1;i > 0;i--)//bottom
	{
		int f = qi[i][pj];
		if (f == WQ_FLAG_BLACK)
		{
			if (flag == WQ_FLAG_WHITE) return WQ_FLAG_NONE;
			flag = WQ_FLAG_BLACK;
			break;
		}
		else if (f == WQ_FLAG_WHITE)
		{
			if (flag == WQ_FLAG_BLACK) return WQ_FLAG_NONE;
			flag = WQ_FLAG_WHITE;
			break;
		}
	}

	for (int j = pj + 1;j < WQ_MAX_J - 1;j++)//left
	{
		int f = qi[pi][j];
		if (f == WQ_FLAG_BLACK)
		{
			if (flag == WQ_FLAG_WHITE) return WQ_FLAG_NONE;
			flag = WQ_FLAG_BLACK;
			break;
		}
		else if (f == WQ_FLAG_WHITE)
		{
			if (flag == WQ_FLAG_BLACK) return WQ_FLAG_NONE;
			flag = WQ_FLAG_WHITE;
			break;
		}
	}

	for (int j = pj - 1;j > 0;j--)//right
	{
		int f = qi[pi][j];
		if (f == WQ_FLAG_BLACK)
		{
			if (flag == WQ_FLAG_WHITE) return WQ_FLAG_NONE;
			flag = WQ_FLAG_BLACK;
			break;
		}
		else if (f == WQ_FLAG_WHITE)
		{
			if (flag == WQ_FLAG_BLACK) return WQ_FLAG_NONE;
			flag = WQ_FLAG_WHITE;
			break;
		}
	}

	return flag;
}


void CUpGradeGameLogic::NumQiZi(float *totalBlack, float *totalWhite, int qi[][21])
{
	*totalBlack = 0;
	*totalWhite = 0;
	
	int black = 0,white = 0;

	for (int i = 1;i < WQ_MAX_I - 1;i++)
		for (int j = 1;j < WQ_MAX_J - 1;j++)
		{
			if(qi[i][j]>10)
				qi[i][j]-=10;
			if (qi[i][j] == WQ_FLAG_WHITE) white++;
			else if (qi[i][j] == WQ_FLAG_BLACK) black++;
			else qi[i][j] = WQ_FLAG_NONE;
		}

	for (int i = 1;i < WQ_MAX_I - 1;i++)
		for (int j = 1;j < WQ_MAX_J - 1;j++)
		{
			if (qi[i][j] != WQ_FLAG_NONE) continue;
			int ff = GetEmptyFlag(i,j,qi);
			if (ff == WQ_FLAG_WHITE)
			{
				white++;
				qi[i][j] = WQ_FLAG_WHITE_CROSS;
			}
			else if (ff == WQ_FLAG_BLACK)
			{
				black++;
				qi[i][j] = WQ_FLAG_BLACK_CROSS;
			}
		}

	*totalBlack = (float) black;
	*totalWhite = (float) white;

	int remainEmpty = 0;

	for (int i = 1;i < WQ_MAX_I - 1;i++)
		for(int j = 1;j < WQ_MAX_J - 1;j++)
		{
			if (qi[i][j] == WQ_FLAG_NONE) remainEmpty++;
		}

	(*totalBlack) += (float) remainEmpty / 2;
	(*totalWhite) += (float) remainEmpty / 2;
	return;
}


BOOL CUpGradeGameLogic::IsIllegalDianMu(int curI, int curJ, int myFlag, int qi[][21])
{
	if (curI < 1 || curI > WQ_MAX_I - 2 || curJ < 1 || curJ > WQ_MAX_J - 2) return FALSE;
	int f = qi[curI][curJ];
	if (f > 10) f -= 10;
	if (f != myFlag + 1) return FALSE;
	if (qi[curI][curJ] > 10) qi[curI][curJ] -= 10;
	qi[curI][curJ]=WQ_FLAG_NONE;
	m_shizi[curI][curJ]=3;
	float fw,fb;
	NumQiZi(&fw,&fb,qi);
	return TRUE;
}