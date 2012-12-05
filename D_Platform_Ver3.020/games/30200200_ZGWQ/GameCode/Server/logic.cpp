#include "stdafx.h"
#include "logic.h"
//构造函数
CUpGradeGameLogic::CUpGradeGameLogic(void)
{

}
//析造函数
CUpGradeGameLogic::~CUpGradeGameLogic()
{

}

void CUpGradeGameLogic::NumQiZi(float *totalBlack, float *totalWhite, int qi[][21])
{
	*totalBlack = 0;
	*totalWhite = 0;

	int black = 0,white = 0;

	for (int i = 1;i < WQ_MAX_I - 1;i++)
		for (int j = 1;j < WQ_MAX_J - 1;j++)
		{
			if (qi[i][j]>10)
			{	
				qi[i][j] -=10;
			}
			if (qi[i][j] == WQ_FLAG_WHITE) white++;
			else if (qi[i][j] == WQ_FLAG_BLACK) black++;
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