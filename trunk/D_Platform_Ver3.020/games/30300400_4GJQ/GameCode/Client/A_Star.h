/**
 *	功能： A-Star算法 查找工兵最短路径
 *  作者： Wolf.Li
 *  日期： 2010.02.04
 *  关键字： H值、G值、F值、开启列表、关闭列表
 *  备注： 关键字请参照A星算法
 */

extern void Msg(const char *lpszFormat, ...);

/**
 * 计算G值
 */
UINT CJqBoard::CountGVal()
{
	return m_CurrentPos.GVal+10;
}

/**
 * 计算H值
 * @param x,y 处理的位置坐标
 * @param iToX, iToY 目的位置坐标
 */
UINT CJqBoard::CountHVal(int x, int y, int iToX, int iToY)
{
	int iUxy=0;
	POINT pt;
	pt.x = x;
	pt.y = y;

	if (GetCenterFarmWordPath(pt))
	{
		int iCount=2;
		int iMin = x<iToX ? x : iToX;
		int iMax = x>iToX ? x : iToX;

		while (iCount--)
		{
			//先传值再减，所以while表达式为1，while里面为0
			if (0==iCount)
			{
				iMin = y<iToY ? y : iToY;
				iMax = y>iToY ? y : iToY;
			}

			for (int i=iMin; i<=iMax; i++)
			{
				//统计两条路径中有多少两位置之间空格的，找到最优的H值（针对'田'字）
				if ( (6==i || 8==i || 10==i)  &&  (6==i-2 || 8==i-2 || 10==i-2) )
				{
					iUxy++;
				}
			}
		}
	}

	Msg("Test:Step 计算（%d,%d）H值%d ",x,y,(abs(x-iToX) + abs(y-iToY) - iUxy)*10);
	return (abs(x-iToX) + abs(y-iToY) - iUxy)*10;
}

/**
 * 计算F值
 * @param POS 设置POS的F值
 */
bool CJqBoard::SetFVal(AStarStruct & POS)
{
	bool bFind = false;
	for (std::vector<AStarStruct>::iterator i=m_OpenList.begin(); i<m_OpenList.end(); ++i)
	{
		if ((*i).ptPos.x==POS.ptPos.x && (*i).ptPos.y==POS.ptPos.y)
		{
			//当前这条路径不是最短
			if ((*i).FVal > POS.GVal+POS.HVal)
			{
				POS.FVal = POS.GVal+POS.HVal;
				*i = POS;

				for (std::vector<AStarStruct>::iterator iAll=m_AllList.begin(); iAll<m_AllList.end(); ++iAll)
				{
					if ((*iAll).ptPos.x==POS.ptPos.x && (*iAll).ptPos.y==POS.ptPos.y)
					{
						*iAll = POS;
						break;
					}
				}
			}
			
			Msg("Test:DDDD 父位置 > %d,%d  相邻位置%d,%d (f%d, h%d, g%d)",POS.ptParent.x, POS.ptParent.y,POS.ptPos.x, POS.ptPos.y,\
				POS.FVal,POS.HVal,POS.GVal);
			bFind = true;
			break;
		}
	}

	//没找到则计算参照G值与H值
	if ( !bFind )
		POS.FVal = POS.GVal+POS.HVal;

	return bFind;
}

/**
 * 查找该位置是否在关闭位置
 */
bool CJqBoard::FindCloseList(POINT pt)
{
	for (std::vector<POINT>::iterator i=m_CloseList.begin(); i<m_CloseList.end(); ++i)
	{
		if (pt.x==(*i).x && pt.y==(*i).y)
		{
			return true;
		}
	}

	return false;
}

/**
 * 获得最小F值
 */
AStarStruct CJqBoard::GetMinFVal()
{
	AStarStruct ptTmp;
	memset(&ptTmp, 0, sizeof(ptTmp));
	UINT uMinFVal=65536; 
	
	for (std::vector<AStarStruct>::size_type i=0; i<m_OpenList.size(); ++i)
	{
		if (FindCloseList(m_OpenList.at(i).ptPos))
			continue;

		if (uMinFVal>m_OpenList.at(i).FVal)
		{
			uMinFVal = m_OpenList.at(i).FVal;
			ptTmp = m_OpenList.at(i);
		}
	}

	return ptTmp;
}

/**
 * 查找该位置是否可以走斜
 * @param pt 查找的位置
 */
bool CJqBoard::GetGoTiltPath(POINT pt)
{
	//下面位置都可以走斜
	return (	(pt.x ==  6  && pt.y ==  5)	||  \
				(pt.x ==  5  && pt.y ==  6)	||  \
				(pt.x ==  5  && pt.y == 10)	||  \
				(pt.x ==  6  && pt.y == 11)	||  \
				(pt.x == 10  && pt.y == 11)	||  \
				(pt.x == 11  && pt.y == 10)	||  \
				(pt.x == 10  && pt.y ==  5)	||  \
				(pt.x == 11  && pt.y ==  6)
				);
}

/**
 * 查找是否在中间田子格位置
 * @param pt 查找的位置
 */
bool CJqBoard::GetCenterFarmWordPath(POINT pt)
{
	//下面位置都在中间‘田’字位置
	return (	(pt.x ==  6  && pt.y ==  6)	||  \
				(pt.x ==  6  && pt.y ==  8)	||  \
				(pt.x ==  6  && pt.y == 10)	||  \
				(pt.x ==  8  && pt.y ==  6)	||  \
				(pt.x ==  8  && pt.y ==  8)	||  \
				(pt.x ==  8  && pt.y == 10)	||  \
				(pt.x == 10  && pt.y ==  6)	||  \
				(pt.x == 10  && pt.y ==  8)	||  \
				(pt.x == 10  && pt.y == 10)
				);
}

/**
 * 加入开启列表
 * @param ptParent 父结点位置坐标
 * @param iToX, iToY 目的位置坐标
 */
void CJqBoard::AddOpenList(int iTo,int jTo, POINT ptParent)
{
	AStarStruct tmpPOS;
	memset(&tmpPOS, 0, sizeof(tmpPOS));
	char cAboutPos=4;
	//前四个控件上下左右，后四个控制斜角 X坐标
	int iNumX[]={0, 1,  0, -1,   1, -1, -1,  1};
	//前四个控件上下左右，后四个控制斜角 Y坐标
	int iNumY[]={1, 0, -1,  0,   1, -1,  1, -1};
	tmpPOS.ptParent.x = ptParent.x;
	tmpPOS.ptParent.y = ptParent.y;
	
	// 该父亲位置不可以走斜
	if (GetGoTiltPath(ptParent))
		cAboutPos = 8;

	for (char i=0; i<cAboutPos; i++)
	{
		tmpPOS.ptPos.x = ptParent.x+iNumX[i];
		tmpPOS.ptPos.y = ptParent.y+iNumY[i];
		
		//如果不在棋盘内
		if ( !bIsInBoard(tmpPOS.ptPos.x,tmpPOS.ptPos.y) )
		{
			//中间田字格位置的四周相邻部分空了一格所以需要再补一格（路线图处少了一格但路是通的）
			if (GetCenterFarmWordPath(ptParent))
			{
				tmpPOS.ptPos.x += iNumX[i];
				tmpPOS.ptPos.y += iNumY[i];
			}
			else
				continue;
		}

		//该位置有棋 并且不是目的坐标
		if ( mBoard[tmpPOS.ptPos.x][tmpPOS.ptPos.y]!=JQ_TYPE_NONE && (tmpPOS.ptPos.x!=iTo || tmpPOS.ptPos.y!=jTo))
			continue;

		//如果不在铁路上(超过一步的必须在铁道上)
		if (!bIsInRailway(tmpPOS.ptPos.x, tmpPOS.ptPos.y))
		{
			Msg("Test:DDDD 如果不在铁路上");
			continue;
		}

		//如果该位置在关闭列表已存在返回
		if (FindCloseList(tmpPOS.ptPos))
			continue;

		tmpPOS.GVal = CountGVal();
		tmpPOS.HVal = CountHVal(tmpPOS.ptPos.x, tmpPOS.ptPos.y, iTo, jTo);
		
		if ( !SetFVal(tmpPOS) )
		{
			Msg("Test:DDDD 支持走弯 %d 父位置%d,%d  相邻位置%d,%d (f%d, h%d, g%d)",cAboutPos,ptParent.x, ptParent.y,tmpPOS.ptPos.x, tmpPOS.ptPos.y,\
				tmpPOS.FVal,tmpPOS.HVal,tmpPOS.GVal);
			m_OpenList.push_back(tmpPOS);
			m_AllList.push_back(tmpPOS);
		}
	}
}

/**
 * 工兵走棋
 * @param iToX, iToY 目的位置坐标
 * @param iFrom, jFrom 源位置坐标
 */
bool CJqBoard::bCanArrival(int iTo,int jTo,int iFrom,int jFrom)
{
	if(GET_A_JQ_NAME( mBoard[iFrom][jFrom]) != JQ_TYPE_NAME_GB)
		return false;

	bool bFind = false;
	AStarStruct tmpPOS;
	tmpPOS.ptPos.x = iFrom;
	tmpPOS.ptPos.y = jFrom;
	tmpPOS.FVal = 0;
	tmpPOS.GVal = 0;
	tmpPOS.HVal = 0;
	m_CurrentPos = tmpPOS;

	m_OpenList.clear();
	m_AllList.clear();
	m_CloseList.clear();
	m_OpenList.push_back(tmpPOS);
	m_AllList.push_back(tmpPOS);

	while (1)
	{
		if (m_OpenList.empty())
			break;

		for (std::vector<AStarStruct>::iterator it=m_OpenList.begin(); it<m_OpenList.end(); ++it)
		{
			if ((*it).ptPos.x==m_CurrentPos.ptPos.x && (*it).ptPos.y==m_CurrentPos.ptPos.y)
			{
				m_CloseList.push_back((*it).ptPos);	//加入到关闭列表中不再操作该位置
				m_OpenList.erase(it);	//从开启列表中删除
				break;
			}
		}

		//设置单前位置的相邻位置
		AddOpenList(iTo, jTo, m_CurrentPos.ptPos);
		//找最小F值
		m_CurrentPos = GetMinFVal();
		
		//找到目的地
		if (iTo==m_CurrentPos.ptPos.x && jTo==m_CurrentPos.ptPos.y)
		{
			bFind = true;
			break;
		}
	}

	//得到路径
	POINT ptOperator = m_CurrentPos.ptParent;
	
	//考虑到步骤不多，且原有思路是这样
	//查找路径时直接循环回搠查找，不改变整体结构
	while (bFind)
	{
		//已经得到路径所有位置 跳出
		if (ptOperator.x==iFrom && ptOperator.y==jFrom)
			break;

		for (std::vector<AStarStruct>::size_type i=0; i<m_AllList.size(); ++i)
		{
			if (m_AllList.at(i).ptPos.x==ptOperator.x && m_AllList.at(i).ptPos.y==ptOperator.y)
			{
				g_StepLine.Push(ptOperator.x, ptOperator.y);
				ptOperator = m_AllList.at(i).ptParent;
				break;
			}
		}
	}

	return bFind;
}

/// 设置闪烁
void CJqBoard::SetFlashChess(int &iX, int &iJ, bool bFlash)
{ 
	m_bShowStartChess = bFlash; 
	iX = m_iStartI;
	iJ = m_iStartJ;
}