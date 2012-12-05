#include "StdAfx.h"
#include "UpGradeLogic.h"

//构造函数
CUpGradeGameLogic::CUpGradeGameLogic(void)
{
	memset(m_iPlayerfight , 0 , sizeof(m_iPlayerfight)) ; 
	
}
//析造函数
CUpGradeGameLogic::~CUpGradeGameLogic()
{

}
///初始化数据
void CUpGradeGameLogic::InitServerData(void)
{
	///规定逻辑0号位置为绿方
	for (int i = 0 ; i<PLAY_COUNT ; i++)
	{
		m_PlayerSerInfo[i].Reset() ;

		m_PlayerSerInfo[i].cbSide = i; 
		for(int  j = 0 ; j< PLAYER_PLANE_NUM ; j++)
		{
			m_PlayerSerInfo[i].Plane[j].emSide = i;   
			m_PlayerSerInfo[i].Plane[j].emPlaneState =  emStandby ; 
			m_PlayerSerInfo[i].Plane[j].cbStep = STEP_HOME ; 
			m_PlayerSerInfo[i].Plane[j].cbAirPortPos  = i; 
			m_PlayerSerInfo[i].Plane[j].cbLandPos = j ; 
		}

		for(int j = 0 ; j<MAX_MAGIC_NUM ; j++)
		{
			m_PlayerSerInfo[i].Magic[j].cbMagic = j+1 ;  ///魔法类别
			m_PlayerSerInfo[i].Magic[j].cbCount = 1; ///魔法个数
		}
	}

	memset(m_iPlayerfight , 0 , sizeof(m_iPlayerfight)) ; 

	return ; 
}
///判断玩家是否有可以活动的飞机（同时返回飞机是否能否活动）
int  CUpGradeGameLogic::FindActivePlaneCount(BYTE iDeskStation)
{
	if(iDeskStation>=PLAY_COUNT)
	{
		return  0; 
	}
	int  iCount = 0 ; 
	for(int i = 0 ; i<PLAYER_PLANE_NUM ; i++)
	{
		if(m_PlayerSerInfo[iDeskStation].Plane[i].emPlaneState>emStandby 
			&& m_PlayerSerInfo[iDeskStation].Plane[i].emPlaneState<emStop)
		{
			iCount ++ ; 
		}
	}

	return iCount ; 
}
///玩家有几架飞机完成飞行任务
int  CUpGradeGameLogic::FindPlaneFinishCount(BYTE iDeskStation) 
{
	if(iDeskStation>=PLAY_COUNT)
	{
		return  0; 
	}
	int  iCount = 0 ; 

	for(int i = 0 ; i<PLAYER_PLANE_NUM ; i++)
	{
		if(m_PlayerSerInfo[iDeskStation].Plane[i].emPlaneState == emStop) 
		{
			iCount ++ ; 
		}
	}
	return iCount ; 
}
///找到一个可以飞行的飞机
int CUpGradeGameLogic::FindOnePlaneToFly(BYTE  bDeskStation , BYTE cbDiceValue) 
{
	for(int i = 0 ; i<PLAYER_PLANE_NUM ; i++)
	{
		if(cbDiceValue == 6)
		{
			if(m_PlayerSerInfo[bDeskStation].Plane[i].emPlaneState == emStandby) ///为6点的找在飞机场的飞机
			{
				return i ;
			}
			else
			{
				if(m_PlayerSerInfo[bDeskStation].Plane[i].emPlaneState != emStop)
				{
					return i ; 
				}
			}
		}
		else
		{
			if(m_PlayerSerInfo[bDeskStation].Plane[i].emPlaneState>emStandby 
				&& m_PlayerSerInfo[bDeskStation].Plane[i].emPlaneState<emStop)
			{
				return i ; 
			}
		}
	}
	return  -1 ; 
}
///找到一个可以飞行的飞机
int CUpGradeGameLogic::FindOnePlaneToFly(BYTE  bDeskStation , BYTE cbDiceValue ,GameScence ScenceData) 
{
	for(int i = 0 ; i<PLAYER_PLANE_NUM ; i++)
	{
		if(cbDiceValue == 6)
		{
			if(ScenceData.PlaneIndex[bDeskStation][i].emPlaneState == emStandby) ///为6点的找在飞机场的飞机
			{
				return i ;
			}
			else
			{
				if(ScenceData.PlaneIndex[bDeskStation][i].emPlaneState != emStop)
				{
					return i ; 
				}
			}
		}
		else
		{
			if(ScenceData.PlaneIndex[bDeskStation][i].emPlaneState>emStandby 
				&& ScenceData.PlaneIndex[bDeskStation][i].emPlaneState<emStop)
			{
				return i ; 
			}
		}
	}
	return  -1 ; 
}
///获取改点有多少个自己的棋子
int CUpGradeGameLogic::GetMyselfInStepCount(BYTE  cbSide , BYTE cbStep , PLANE Plane[]) 
{
	if(cbSide == emInvalidate )
	{
		return 0 ;  ///
	}

	int  iPlaneCount = 0 ;

	for(int  j = 0 ; j<PLAY_COUNT ; j++)
	{
		if(m_PlayerSerInfo[cbSide].Plane[j].emPlaneState == emFlying ||m_PlayerSerInfo[cbSide].Plane[j].emPlaneState== emLanding)
		{
			if(m_PlayerSerInfo[cbSide].Plane[j].cbStep == cbStep)
			{
				Plane[iPlaneCount] = m_PlayerSerInfo[cbSide].Plane[j] ; 
				iPlaneCount ++ ;
			}
		}
	}
	return iPlaneCount ;

}
///获取改点有多少个自己的棋子
int CUpGradeGameLogic::GetMyselfInStepCount(BYTE cbSide , BYTE cbStep , GameScence ScenceData) 
{
	if(cbSide == emInvalidate )
	{
		return 0 ;  ///
	}

	int  iPlaneCount = 0 ;

	for(int  j = 0 ; j<PLAY_COUNT ; j++)
	{
		if(ScenceData.PlaneIndex[cbSide][j].emPlaneState == emFlying || ScenceData.PlaneIndex[cbSide][j].emPlaneState== emLanding)
		{
			if(ScenceData.PlaneIndex[cbSide][j].cbStep == cbStep)
			{
				iPlaneCount ++ ;
			}
		}
	}
	return iPlaneCount ;
}
///获取该点有多少个敌方的棋子
int  CUpGradeGameLogic::GetEnemyInStepCount(BYTE cbSide, BYTE cbStep ,PLANE Plane[]) 
{
	if(cbSide == emInvalidate )
	{
		return 0 ;  ///
	}

	if(cbStep >49)  ///在此处是不可能有敌方的飞机的
	{
		return 0 ; 
	}

	int  iPlaneCount = 0 ; 

	for(int  i = 0 ; i<PLAY_COUNT ; i++)
	{
		if((PLAY_COUNT + cbSide - i)%2 == 0 ) ///自己方的飞机
		{
			continue;
		}

		for(int  j = 0 ; j<PLAY_COUNT ; j++)
		{
			if(m_PlayerSerInfo[i].Plane[j].emPlaneState != emFlying) ///非在公共线路的飞机
			{
				continue; 
			}

			if(GetMyStepIndex((enumSide)i ,m_PlayerSerInfo[i].Plane[j].cbStep) == GetMyStepIndex((enumSide)cbSide,cbStep))
			{
				Plane[iPlaneCount ++ ] = m_PlayerSerInfo[i].Plane[j] ; 
			}
		}
	}

	return iPlaneCount ; 
}
///以下供客户端使用
///获取该点有多少个敌方的棋子
int  CUpGradeGameLogic::GetEnemyInStepCount(BYTE cbSide, BYTE cbStep ,GameScence ScenceData ) 
{
	if(cbSide == emInvalidate )
	{
		return 0 ;  ///
	}
	if(cbStep >49)  ///在此处是不可能有敌方的飞机的
	{
		return 0 ; 
	}

	int  iPlaneCount = 0 ; 

	for(int  i = 0 ; i<PLAY_COUNT ; i++)
	{
		if((PLAY_COUNT + cbSide - i)%2 == 0 ) ///自己方的飞机
		{
			continue;
		}

		for(int  j = 0 ; j<PLAY_COUNT ; j++)
		{
			if(ScenceData.PlaneIndex[i][j].emPlaneState != emFlying) ///非在公共线路的飞机
			{
				continue; 
			}

			if(GetMyStepIndex((enumSide)i ,ScenceData.PlaneIndex[i][j].cbStep) == GetMyStepIndex((enumSide)cbSide,cbStep))
			{
				iPlaneCount ++ ;
			}
		}
	}

	return iPlaneCount ; 
}
///检测该玩家是否完成飞行任务
bool CUpGradeGameLogic::CheckGameFinish(BYTE bDeskStation)
{
	return (FindPlaneFinishCount(bDeskStation) == PLAYER_PLANE_NUM) ; 
}
///获取在该点我是否能飞行
bool CUpGradeGameLogic::IsCanFly(BYTE cbSide , BYTE cbStep) 
{
	if(cbSide == emInvalidate )
	{
		return false ;  ///
	}
	if(cbStep <1 ||cbStep >=49) ///到了自己的位置就不能飞了
	{
		return false ; 
	}
	if((cbStep + 3 )%PLAY_COUNT == 0 ) ///是自己的格子
	{
		return true ; 
	}

	return false ; 
}
///判断玩家是否可以走捷径
bool   CUpGradeGameLogic::IsCanShortCut(BYTE cbSide , BYTE cbStep )
{
	if(cbStep == emInvalidate)
	{
		return false ; 
	}
	if(cbStep != SHORTCUT_STEP_VALUE)
	{
		return false ; 
	}

	PLANE planeIndex[8] ; 
	if(GetEnemyInStepCount(cbSide ,SHORTCUT_STEP_VALUE ,planeIndex)>1)
	{
		return false ; 
	}
	return true ;  

}
///判断一个飞机是否能飞行
bool  CUpGradeGameLogic::IsCanMove(BYTE bDeskStation , BYTE inDex ,BYTE cbDiceValue)
{
	if(bDeskStation >=PLAY_COUNT)
	{
		return false ;
	}

	if(m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState == emStop)
	{
		return false ; 
	}

	if(cbDiceValue == 6)
	{
		return true ; 
	}
	else
	{
		if(m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState<emTakeoff 
			||m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState>emLanding)
		{
			return false ; 
		}
	}

	return true ; 
}
///玩家走棋判断
int  CUpGradeGameLogic::PlayerPlaneFly(BYTE bDeskStation ,BYTE cbDiceValue ,int inDex ,PlaneFlyStruct PlaneActiveTrack[])
{
	if(bDeskStation <0 ||bDeskStation >=PLAY_COUNT)
	{
		return 0 ; 
	}

	int iActivePlaneCount = 0 ; //需要激活的飞机的数量 0号为指定的自己的飞机

	if(inDex < 0 ||inDex >=PLAYER_PLANE_NUM )
	{
		return 0 ; 
	}
	switch(m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState)
	{
	case  emStandby:
		{
			int  iComeByCount = 0 ;       ///需要移动的步数

			if(cbDiceValue == 6 ) ///只有6点可以起飞
			{
				PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME ;
				PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_TAKEOFF ;
				PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

				PlaneActiveTrack[iActivePlaneCount].cbSide   = bDeskStation ;
				PlaneActiveTrack[iActivePlaneCount].cbIndex   = inDex ;  
				PlaneActiveTrack[iActivePlaneCount].cbOperateType = emTakeOfFActive ; 
				iActivePlaneCount ++ ; 
				m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emTakeoff ;
				m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = STEP_TAKEOFF ; 
			}
			return iActivePlaneCount ; 
		}
	case  emTakeoff :
	case  emFlying:
		{
			bool   bNeedBack  = false ;     ///是否需要回退  
			bool   bCanFly    = false ;        ///是否可以飞行
			int    iComeByCount = 0 ;       ///需要移动的步数
			int    cbTempStep = -1 ;       ///有迭子的位置
			int    cbStartPos ;         ///起始位置

			int    iMyselfCount = 0 ;

			PLANE  planeIndex[8] ;
			PLANE  mySelfIndex[4] ; //自己的飞机架数
			memset(planeIndex , 0 , sizeof(planeIndex)) ; 
			memset(mySelfIndex , 0 , sizeof(mySelfIndex)) ; 

			if(m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState == emTakeoff)
			{
				cbStartPos     = -1 ;
				iMyselfCount   = 1 ;
				mySelfIndex[0] = m_PlayerSerInfo[bDeskStation].Plane[inDex] ;

				PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_TAKEOFF ; 
			}
			else
			{
				cbStartPos = m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep ; 
				PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbStartPos ; 

				iMyselfCount = GetMyselfInStepCount(bDeskStation ,cbStartPos ,mySelfIndex) ; 
			}

			PlaneActiveTrack[iActivePlaneCount].cbSide = bDeskStation ; 
			PlaneActiveTrack[iActivePlaneCount].cbIndex = inDex ; 

			for(int i = cbStartPos + 1 ; i < cbStartPos + cbDiceValue  ; i++) ///暂不考虑走最后一步(最后一步可能有飞棋)
			{
				PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = i ;

				if(GetEnemyInStepCount(bDeskStation,i ,planeIndex) >iMyselfCount)  ///1点时不会到这里来
				{
					bNeedBack = true ; 
					cbTempStep = i ;                ///到这里就不能再走了
					break;
				}
			}

			if(bNeedBack == true) ///敌方有迭子的情况(这种状况下没有撞机的)
			{
				int iEndPos = 2*cbTempStep - cbDiceValue - cbStartPos; 

				if( iEndPos >=0)
				{
					for(int j = cbTempStep - 1 ; j >= iEndPos ; j-- )
					{
						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] =  j ;
					}

					PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

					m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = iEndPos ;
					m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ; 
				}
				else
				{
					for(int j = cbTempStep - 1 ; j>=0 ; j-- )
					{
						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] =  j ;
					}

					PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_TAKEOFF ;
					PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

					m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = STEP_TAKEOFF ;
					m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emTakeoff ;  ///重新回到起飞位置
				}

				PlaneActiveTrack[iActivePlaneCount].cbOperateType = emBackActive ; 
				iActivePlaneCount ++ ;
				
			}
			else  ///走棋过程中没有迭子,检测最后一步
			{
				int  iEnemyPlaneCount =  GetEnemyInStepCount(bDeskStation ,cbDiceValue + cbStartPos ,planeIndex) ;
				Msg("wysoutfxqlogic开始检测飞机的最后一步检测的步cbDiceValue==%d ,cbStartPos==%d ,%d ,敌方飞机的个数==%d",cbDiceValue , cbStartPos ,cbDiceValue + cbStartPos ,iEnemyPlaneCount); 
			
				if(iEnemyPlaneCount >0 ) ///最后一步有敌机不会再走了
				{
					if(iEnemyPlaneCount <=iMyselfCount) ///如果自己的飞机大于等于敌方的飞机
					{
						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbDiceValue + cbStartPos;
						PlaneActiveTrack[iActivePlaneCount].cbOperateType = emFlyingActive ; 

						m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = cbDiceValue + cbStartPos ;
						m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;

						m_iPlayerfight[bDeskStation%2] += iEnemyPlaneCount ;
					}
					else
					{
						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbDiceValue + cbStartPos;
						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME;
						PlaneActiveTrack[iActivePlaneCount].cbOperateType = emHomeActive ; 

						m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = STEP_HOME ;
						m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emStandby  ; ///回家了

						//m_iPlayerfight[(bDeskStation+1)%2] += iMyselfCount ; 
					}

					PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

					for(int i = 0 ; i <iEnemyPlaneCount ; i++) ///处理敌方的飞机
					{
						iActivePlaneCount ++ ;
						iComeByCount = 0 ;  ///后面是其他飞机的处理
						int   bOtherDesk  = planeIndex[i].emSide ;
						int   bOtherIndex = planeIndex[i].cbLandPos ;  
						BYTE  cbStartStep =planeIndex[i].cbStep; 

						PlaneActiveTrack[iActivePlaneCount].cbSide = bOtherDesk ; 
						PlaneActiveTrack[iActivePlaneCount].cbIndex = bOtherIndex ; 

						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbStartStep ; 
						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME ;
						PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
						PlaneActiveTrack[iActivePlaneCount].cbOperateType = emHomeActive ; 

						m_PlayerSerInfo[bOtherDesk].Plane[bOtherIndex].cbStep = STEP_HOME ;
						m_PlayerSerInfo[bOtherDesk].Plane[bOtherIndex].emPlaneState = emStandby ; 

						//m_iPlayerfight[bDeskStation%2] ++ ; 
					}

					iActivePlaneCount ++ ; 

				}
				else ///最后一步没有敌方的飞机
				{
					if(IsCanShortCut(bDeskStation ,cbDiceValue + cbStartPos))  ///是否可以飞翔
					{
						int  iOtherStepCount = GetEnemyInStepCount(bDeskStation ,SHORTCUT_OTHER_STEP ,planeIndex) ;  

						if( iOtherStepCount== iMyselfCount)  //相等的情况下打掉敌方的飞机
						{
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbDiceValue + cbStartPos ;
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_OTHER_STEP;

							PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
							PlaneActiveTrack[iActivePlaneCount].cbOperateType = emShortCutActive ; 

							m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = SHORTCUT_OTHER_STEP ;
							m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ; 

							iActivePlaneCount ++ ; 

							for(int  i = 0 ; i < iOtherStepCount ; i++)
							{
								iComeByCount = 0 ; 

								PlaneActiveTrack[iActivePlaneCount].cbSide = planeIndex[i].emSide ; 
								PlaneActiveTrack[iActivePlaneCount].cbIndex = planeIndex[i].cbLandPos ; 

								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_OTHER_STEP ; 
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME ; 

								PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

								m_PlayerSerInfo[planeIndex[i].emSide].Plane[planeIndex[i].cbLandPos].cbStep = STEP_HOME ;
								m_PlayerSerInfo[planeIndex[i].emSide].Plane[planeIndex[i].cbLandPos].emPlaneState = emStandby ; 

								m_iPlayerfight[bDeskStation%2] ++ ; 

								iActivePlaneCount ++ ; 
							}
						}
						else if(iOtherStepCount <iMyselfCount)
						{
							bCanFly = true ; 
							int inDexEnemy = 0 ; 
							for(int  i = SHORTCUT_OTHER_STEP;i<SHORTCUT_OTHER_STEP +4 ; i++ )
							{
								if(GetEnemyInStepCount(bDeskStation ,i,planeIndex) >iMyselfCount)
								{
									bCanFly = false ;
									i = inDexEnemy ; 
									break;
								}
							}

							if(bCanFly == true) ///可以再飞一次
							{
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_STEP_VALUE ;
								for(int  i = SHORTCUT_OTHER_STEP;i<SHORTCUT_OTHER_STEP +5 ; i++ )
								{
									PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = i ;
								}
								PlaneActiveTrack[iActivePlaneCount].cbOperateType = emShortCutActive ; 
								PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

								m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = SHORTCUT_OTHER_STEP +4 ;
								m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;

								iActivePlaneCount ++ ; 
								
							}
							else  //不再飞行
							{
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_STEP_VALUE ;
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_OTHER_STEP ;

								PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount  ; 

								m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = SHORTCUT_OTHER_STEP ;
								m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;

								iActivePlaneCount ++ ; 
							}
						}

						if(iOtherStepCount <=iMyselfCount)  ///这两种情况先考虑完
						{
							BYTE  iSpecifySide    = m_PlayerSerInfo[bDeskStation].Plane[inDex].emSide ; 
							BYTE  iSpecifyStation = m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState ; 
							BYTE  iSpecifyStep    =  m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep ; 

							///看一下自己的飞机有多少架
							for(int  i = 0 ; i <iMyselfCount ; i++)   ///拷贝本玩家同一位置飞机的路径
							{
								BYTE  cbMyTempside = mySelfIndex[i].emSide ; 
								BYTE  cbMyInDex    = mySelfIndex[i].cbLandPos ;

								if(cbMyInDex == inDex)
								{
									continue;
								}

								PlaneActiveTrack[iActivePlaneCount] = PlaneActiveTrack[0] ; 

								PlaneActiveTrack[iActivePlaneCount].cbSide  = cbMyTempside ;
								PlaneActiveTrack[iActivePlaneCount].cbIndex = cbMyInDex ; 

								m_PlayerSerInfo[cbMyTempside].Plane[cbMyInDex].cbStep = iSpecifyStep ;
								m_PlayerSerInfo[cbMyTempside].Plane[cbMyInDex].emPlaneState = iSpecifyStation ; 

								iActivePlaneCount ++ ; 
							}

							return iActivePlaneCount ; 
						}
					}

					if(IsCanFly(bDeskStation , cbDiceValue + cbStartPos )) ///（到了自己的格子）
					{
						bCanFly = true ; 
						for(int  i = cbDiceValue + cbStartPos;i<cbDiceValue + cbStartPos +4 ; i++ )
						{
							if(GetEnemyInStepCount(bDeskStation ,i,planeIndex) >iMyselfCount)
							{
								bCanFly = false ; 
								break;
							}
						}
					}

					if(bCanFly == true) ///需要再走4步 加上最后一步
					{
						for(int  i = 0 ; i<5 ; i++)
						{
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbDiceValue + i + cbStartPos ;
						}

						PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
						PlaneActiveTrack[iActivePlaneCount].cbOperateType = emFlyingActive ;

						m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = cbDiceValue + cbStartPos + 4 ;
						m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;
					}
					else  ///断定这里不可能有回退的可能
					{
						PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbDiceValue + cbStartPos ;
						
						PlaneActiveTrack[iActivePlaneCount].cbOperateType = emFlyingActive ; 

						m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = cbDiceValue + cbStartPos ;

						if((cbDiceValue + cbStartPos) >=50 && (cbDiceValue + cbStartPos) < (FINISH_PATH_STEP - 1))
						{
							m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emLanding ;
						}
						else if(cbDiceValue + cbStartPos == FINISH_PATH_STEP - 1)
						{
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME ;

							PlaneActiveTrack[iActivePlaneCount].cbOperateType = emArriveHome ; 

							m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emStop ;
							m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep  = STEP_HOME ; 
						}
						else
						{
							m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;
						}

						PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
						
					}

					if(IsCanShortCut(bDeskStation ,m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep)) //可以走捷径
					{
						memset(planeIndex , 0 , sizeof(planeIndex)) ; 

						int  iLastStepEnemyCount = GetEnemyInStepCount(bDeskStation ,SHORTCUT_OTHER_STEP ,planeIndex) ; 

						if( iLastStepEnemyCount <iMyselfCount)
						{
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_STEP_VALUE ;
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_OTHER_STEP ;

							PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount  ;
							PlaneActiveTrack[iActivePlaneCount].cbOperateType = emShortCutActive ; 

							m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = SHORTCUT_OTHER_STEP ;
							m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;

						}
						else if(iLastStepEnemyCount == iMyselfCount)
						{
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_STEP_VALUE ;
							PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_OTHER_STEP ;

							PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount  ; 
							PlaneActiveTrack[iActivePlaneCount].cbOperateType = emShortCutActive ; 

							m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = SHORTCUT_OTHER_STEP ;
							m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;
							
							iActivePlaneCount ++ ; 

							for(int  i = 0 ; i < iLastStepEnemyCount ; i++)
							{
								iComeByCount = 0 ; 

								PlaneActiveTrack[iActivePlaneCount].cbSide = planeIndex[i].emSide ; 
								PlaneActiveTrack[iActivePlaneCount].cbIndex = planeIndex[i].cbLandPos ; 

								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = SHORTCUT_OTHER_STEP ; 
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME ; 

								PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

								m_PlayerSerInfo[planeIndex[i].emSide].Plane[planeIndex[i].cbLandPos].cbStep = STEP_HOME ;
								m_PlayerSerInfo[planeIndex[i].emSide].Plane[planeIndex[i].cbLandPos].emPlaneState = emStandby ; 

								m_iPlayerfight[bDeskStation%2] ++ ; 

								iActivePlaneCount ++ ; 
							}
						}
					}

					BYTE cbTermalStep = m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep ; 

					if(cbTermalStep>=0 &&cbTermalStep<50)
					{
						///检测真实的最后一步是否有飞机
						memset(planeIndex , 0 ,sizeof(planeIndex)) ; 

						Msg("wysoutfxqlogic开始检测飞机的最后一步检测的步cbDiceValue==%d ,cbStartPos==%d ",cbDiceValue , cbStartPos); 

						int  iEnemyPlaneCount =  GetEnemyInStepCount(bDeskStation ,cbTermalStep ,planeIndex) ;

						if(iEnemyPlaneCount >0 ) ///最后一步有敌机不会再走了
						{
							if(iEnemyPlaneCount <=iMyselfCount) ///打了一架飞机回家了
							{
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] =  cbTermalStep;
								PlaneActiveTrack[iActivePlaneCount].cbOperateType = emFlyingActive ; 

								m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = cbTermalStep ;
								m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emFlying ;
								m_iPlayerfight[bDeskStation%2]+= iEnemyPlaneCount ;
							}
							else
							{
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME;
								PlaneActiveTrack[iActivePlaneCount].cbOperateType = emHomeActive ; 

								m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = STEP_HOME ;
								m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emStandby  ; ///回家了

								//m_iPlayerfight[(bDeskStation + 1)%2] += iMyselfCount;
							}

							PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 

							for(int i = 0 ; i <iEnemyPlaneCount ; i++) ///处理敌方的飞机
							{
								iActivePlaneCount ++ ;
								iComeByCount = 0 ;  ///后面是其他飞机的处理
								int   bOtherDesk  = planeIndex[i].emSide ;
								int   bOtherIndex = planeIndex[i].cbLandPos ;  
								BYTE  cbStartStep =planeIndex[i].cbStep; 

								PlaneActiveTrack[iActivePlaneCount].cbSide = bOtherDesk ; 
								PlaneActiveTrack[iActivePlaneCount].cbIndex = bOtherIndex ; 

								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbTermalStep ; 
								PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = STEP_HOME ;
								PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
								PlaneActiveTrack[iActivePlaneCount].cbOperateType = emHomeActive ; 

								m_PlayerSerInfo[bOtherDesk].Plane[bOtherIndex].cbStep = STEP_HOME ;
								m_PlayerSerInfo[bOtherDesk].Plane[bOtherIndex].emPlaneState = emStandby ;

								//m_iPlayerfight[bDeskStation%2] ++ ;
							}
						}
					}

					iActivePlaneCount ++ ; 
				}
			}

			BYTE  iSpecifySide    = m_PlayerSerInfo[bDeskStation].Plane[inDex].emSide ; 
			BYTE  iSpecifyStation = m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState ; 
			BYTE  iSpecifyStep    =  m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep ; 

			///看一下自己的飞机有多少架
			for(int  i = 0 ; i <iMyselfCount ; i++)   ///拷贝本玩家同一位置飞机的路径
			{
				BYTE  cbMyTempside = mySelfIndex[i].emSide ; 
				BYTE  cbMyInDex    = mySelfIndex[i].cbLandPos ;

				if(cbMyInDex == inDex)
				{
					continue;
				}

				PlaneActiveTrack[iActivePlaneCount] = PlaneActiveTrack[0] ; 

				PlaneActiveTrack[iActivePlaneCount].cbSide  = cbMyTempside ;
				PlaneActiveTrack[iActivePlaneCount].cbIndex = cbMyInDex ; 

				m_PlayerSerInfo[cbMyTempside].Plane[cbMyInDex].cbStep = iSpecifyStep ;
				m_PlayerSerInfo[cbMyTempside].Plane[cbMyInDex].emPlaneState = iSpecifyStation ; 

				iActivePlaneCount ++ ; 
			}
			return iActivePlaneCount ; 
		}
	case  emLanding:
		{
			int    iComeByCount = 0 ;       ///需要移动的步数
			int   cbStartPos = m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep ; 

			PLANE   mySelfIndex[PLAY_COUNT] ;
			memset(mySelfIndex , 0 , sizeof(mySelfIndex)) ; 

			int  iMyselfCount = GetMyselfInStepCount(bDeskStation ,cbStartPos ,mySelfIndex) ; 

			PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = cbStartPos ; 
			PlaneActiveTrack[iActivePlaneCount].cbSide = bDeskStation ; 
			PlaneActiveTrack[iActivePlaneCount].cbIndex = inDex ; 

			if(cbStartPos + cbDiceValue == FINISH_PATH_STEP -1) ///飞机完成飞行任务
			{
				for(int i = cbStartPos + 1; i<= cbStartPos + cbDiceValue  ; i++)
				{
					PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = i;
				}

				PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++]  = STEP_HOME ;
				PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
				PlaneActiveTrack[iActivePlaneCount].cbOperateType = emArriveHome ; 

				m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = STEP_HOME ; 
				m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState = emStop ; 
				
			}
			else if(cbStartPos + cbDiceValue >FINISH_PATH_STEP -1) ///需要后退
			{
				for(int i = cbStartPos + 1; i<  FINISH_PATH_STEP   ; i++)
				{
					PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = i;
				}
				for(int i =  FINISH_PATH_STEP - 2 ; i>= 2*(FINISH_PATH_STEP-1) - cbStartPos- cbDiceValue ; i--)
				{
					PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = i;
				}

				PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
				PlaneActiveTrack[iActivePlaneCount].cbOperateType = emBackActive ; 

				m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = 2*(FINISH_PATH_STEP-1) - cbStartPos- cbDiceValue;
			}
			else
			{
				for(int i = cbStartPos + 1; i<=  cbStartPos + cbDiceValue   ; i++)
				{
					PlaneActiveTrack[iActivePlaneCount].cbComeByStepIndex[iComeByCount ++] = i;
				}

				PlaneActiveTrack[iActivePlaneCount].cbStepCount = iComeByCount ; 
				PlaneActiveTrack[iActivePlaneCount].cbOperateType = emFlyingActive ; 

				m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep = cbStartPos + cbDiceValue;
			}

			iActivePlaneCount ++ ; 

			BYTE  iSpecifySide    = m_PlayerSerInfo[bDeskStation].Plane[inDex].emSide ; 
			BYTE  iSpecifyStation = m_PlayerSerInfo[bDeskStation].Plane[inDex].emPlaneState ; 
			BYTE  iSpecifyStep    =  m_PlayerSerInfo[bDeskStation].Plane[inDex].cbStep ; 

			///看一下自己的飞机有多少架
			for(int  i = 0 ; i <iMyselfCount ; i++)   ///拷贝本玩家同一位置飞机的路径
			{
				BYTE  cbMyTempside = mySelfIndex[i].emSide ; 
				BYTE  cbMyInDex    = mySelfIndex[i].cbLandPos ;

				if(cbMyInDex == inDex)
				{
					continue;
				}

				PlaneActiveTrack[iActivePlaneCount] = PlaneActiveTrack[0] ; 

				PlaneActiveTrack[iActivePlaneCount].cbSide  = cbMyTempside ;
				PlaneActiveTrack[iActivePlaneCount].cbIndex = cbMyInDex ; 

				m_PlayerSerInfo[cbMyTempside].Plane[cbMyInDex].cbStep = iSpecifyStep ;
				m_PlayerSerInfo[cbMyTempside].Plane[cbMyInDex].emPlaneState = iSpecifyStation ; 

				iActivePlaneCount ++ ; 
			}

			return iActivePlaneCount ; 
		}
		break ;
	case  emStop:
	case  emError:
		{
			return  0; 
		}
	}
	return  iActivePlaneCount ;
}



///判断玩家是否可以走捷径
bool   CUpGradeGameLogic::IsCanShortCut(BYTE cbSide , BYTE cbStep ,GameScence ScenceData )
{
	if(cbStep == emInvalidate)
	{
		return false ; 
	}
	if(cbStep != SHORTCUT_STEP_VALUE)
	{
		return false ; 
	}

	if(GetEnemyInStepCount(cbSide ,SHORTCUT_STEP_VALUE ,ScenceData)>1)
	{
		return false ; 
	}
	return true ;  

}


///根据当前的场景和玩家飞机的索引点数确定玩家的飞机能飞到的位置
int  CUpGradeGameLogic::GetPlaneFlyPos(BYTE bDeskStation , int inDex ,int cbDiceValue , GameScence  ScenceData)
{
	if(bDeskStation >=PLAY_COUNT)
	{
		return -1 ; 
	}
	if(inDex <0 ||inDex>=PLAYER_PLANE_NUM)
	{
		return -1 ; 
	}
	int  iDestineStep  = -1 ;  
	switch(ScenceData.PlaneIndex[bDeskStation][inDex].emPlaneState)
	{
	case  emStandby:
		{
			if(cbDiceValue != 6)
			{
				return -1 ; 
			}
			else
			{
				return STEP_TAKEOFF ; 
			}
			break;
		}
	case  emTakeoff:
	case  emFlying:
		{
			bool   bNeedBack  = false ;     ///是否需要回退  
			bool   bCanFly  = false ;        ///是否可以飞行
			int    iComeByCount = 0 ;       ///需要移动的步数
			int    cbTempStep = -1 ;       ///有迭子的位置
			int    cbStartPos ;         ///起始位置

			int    iMyselfCount = 0 ;

			if(ScenceData.PlaneIndex[bDeskStation][inDex].emPlaneState == emTakeoff)
			{
				iMyselfCount   = 1 ;
				cbStartPos = -1 ;
			}
			else
			{
				cbStartPos = ScenceData.PlaneIndex[bDeskStation][inDex].cbStep ; 
				iMyselfCount = GetMyselfInStepCount(bDeskStation ,cbStartPos ,ScenceData) ; 
			}

			for(int i = cbStartPos +1 ; i < cbStartPos + cbDiceValue  ; i++) ///暂不考虑走最后一步(最后一步可能有飞棋)
			{
				if(GetEnemyInStepCount(bDeskStation,i,ScenceData) >iMyselfCount)  ///1点时不会到这里来
				{
					bNeedBack = true ; 
					cbTempStep = i ;                ///到这里就不能再走了
					break;
				}
			}

			if(bNeedBack == true) ///敌方有迭子的情况(这种状况下没有撞机的)
			{
				int iEndPos = 2*cbTempStep - cbDiceValue - cbStartPos; 
				iDestineStep = (iEndPos >0 ?iEndPos:STEP_TAKEOFF) ; 
			}
			else  ///走棋过程中没有迭子
			{
				int  iEnemyPlaneCount =  GetEnemyInStepCount(bDeskStation ,cbDiceValue + cbStartPos ,ScenceData) ;

				if(iEnemyPlaneCount >0 ) ///最后一步有敌机
				{
					if(iEnemyPlaneCount <=iMyselfCount) ///打了一架飞机回家了
					{
						iDestineStep = cbDiceValue + cbStartPos ; 
					}
					else
					{
						iDestineStep = STEP_HOME ; 
					}
				}
				else ///最后一步没有敌方的飞机
				{
					if(IsCanShortCut(bDeskStation ,cbDiceValue + cbStartPos))  ///是否可以飞翔
					{
						if(GetEnemyInStepCount(bDeskStation ,SHORTCUT_OTHER_STEP ,ScenceData) == iMyselfCount)
						{
							iDestineStep = SHORTCUT_STEP_VALUE  ; 
						}
						else if( GetEnemyInStepCount(bDeskStation ,SHORTCUT_OTHER_STEP ,ScenceData) <iMyselfCount)
						{
							bCanFly = true ; 
							
							for(int  i = SHORTCUT_OTHER_STEP;i<SHORTCUT_OTHER_STEP +4 ; i++ )
							{
								if(GetEnemyInStepCount(bDeskStation ,i,ScenceData) >iMyselfCount)
								{
									bCanFly = false ;
									break;
								}
							}

							if(bCanFly == true) ///可以再飞一次
							{
								iDestineStep = SHORTCUT_OTHER_STEP +4 ;
							}
							else  //不再飞行
							{
								iDestineStep = SHORTCUT_OTHER_STEP ; 
							}
						}

						return iDestineStep ; 
					}

					if(IsCanFly(bDeskStation , cbDiceValue + cbStartPos)) ///可以飞行
					{
						bCanFly = true ; 
						for(int  i = cbDiceValue + cbStartPos ; i<cbDiceValue + cbStartPos +4 ; i++ )
						{
							if(GetEnemyInStepCount(bDeskStation ,i,ScenceData) >iMyselfCount)
							{
								bCanFly = false ; 
								break;
							}
						}
					}

					iDestineStep = (bCanFly?(cbDiceValue + cbStartPos + 4):(cbDiceValue + cbStartPos)); 

					if(IsCanShortCut(bDeskStation ,iDestineStep)) //可以走捷径
					{
						if(GetEnemyInStepCount(bDeskStation ,SHORTCUT_OTHER_STEP ,ScenceData)  < iMyselfCount +1)
						{
							iDestineStep = SHORTCUT_OTHER_STEP ;
						}
					}
				}
			}
			break;
		}
	case  emLanding:
		{
			int  cbStartPos = ScenceData.PlaneIndex[bDeskStation][inDex].cbStep ; 

			if(cbStartPos + cbDiceValue > FINISH_PATH_STEP -1) ///飞机完成飞行任务
			{
				iDestineStep = 2*(FINISH_PATH_STEP-1) - cbStartPos- cbDiceValue;
			}
			else
			{
				iDestineStep = cbStartPos + cbDiceValue ; 
			}

			break;
		}
	default:
		{
			break;
		}
	}
	return  iDestineStep ; 
}
/// 返回飞机的索引(算我下面有多少架飞机)
int CUpGradeGameLogic::GetPlanePixIndex(BYTE bDeskStation ,int inDex , BYTE  cbStep ,GameScence ScenceData ) 
{
	int inDexCount = 0 ; 

	if(cbStep == STEP_TAKEOFF)
	{
		for(int i = 0 ; i<inDex ; i++)
		{
			if(ScenceData.PlaneIndex[bDeskStation][i].emPlaneState == emTakeoff)
			{
				inDexCount ++ ; 
			}
		}
	}
	else if(cbStep>49 && cbStep <55)
	{
		for(int i = 0 ; i<inDex ; i++)
		{
			if(ScenceData.PlaneIndex[bDeskStation][i].cbStep == cbStep)
			{
				inDexCount ++ ; 
			}
		}
	}
	else if(cbStep>=0 &&cbStep<50)
	{
		for(int i = 0 ; i<bDeskStation ; i++)
		{
			for(int j = 0 ; j<PLAYER_PLANE_NUM ; j++)
			{
				if(ScenceData.PlaneIndex[i][j].emPlaneState != emFlying)
				{
					continue;
				}
				
				if((GetMyStepIndex((enumSide)bDeskStation , cbStep) == GetMyStepIndex((enumSide)i ,ScenceData.PlaneIndex[i][j].cbStep)))
				{
					inDexCount ++  ; 
				}
			}
		}

		for(int j = 0 ; j<inDex ; j ++)
		{
			if(ScenceData.PlaneIndex[bDeskStation][j].emPlaneState != emFlying)
			{
				continue;
			}
			if(ScenceData.PlaneIndex[bDeskStation][j].cbStep == cbStep)
			{
				inDexCount ++ ; 
			}
		}
	}
	return inDexCount ; 
}
