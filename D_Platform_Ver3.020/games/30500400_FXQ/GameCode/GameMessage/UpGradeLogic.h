#pragma once

#include <vector>

const  int  SPACE_WIDE    = 40 ;
const  int  SPACE_HEIGHT  = 40 ; 

///得到玩家的相对视图位置
inline BYTE  GetUserRelativePos(BYTE  iMyStation ,BYTE iStation ) 
{
	return  (iStation - iMyStation + 2 + PLAY_COUNT )%PLAY_COUNT  ;
}
// 通过飞机相对于我的位置和我的enSide得出飞机在公共路线上的绝对位置   
inline int GetPublicStepIndex(enumSide enMySide,int nMyStep)
{
	if(enMySide == emInvalidate || nMyStep == 255) 
		return 255;

	if(enMySide == emGreen) 
		return nMyStep;

	if (enMySide == emRed) 
	{
		if(nMyStep >= 0 && nMyStep <= 38) 
			return nMyStep + 13;

		if(nMyStep >= 39 && nMyStep < 52) 
			return nMyStep - 39;
	}

	if (enMySide == emYellow)
	{
		if(nMyStep >= 0 && nMyStep <= 25) 
			return nMyStep + 26;

		if(nMyStep >= 26 && nMyStep < 52) 
			return nMyStep - 26;
	}
	if (enMySide == emBlue)
	{
		if(nMyStep >= 0 && nMyStep <= 12) 
			return nMyStep + 39;

		if(nMyStep >= 13 && nMyStep < 52) 
			return nMyStep - 13;
	}

	return 255;
}

// 通过飞机在公共路线上的绝对位置得出飞机相对于我的enSide的位置
inline int GetMyStepIndex(enumSide enMySide,int nPubStep)
{
	if(enMySide == emInvalidate || nPubStep == 255) 
		return 255;

	return  (nPubStep + 13 *enMySide )%52 ; 
}
///整个棋盘的位置
struct PATH	// 保存整个棋盘的坐标(根据我的颜色方生成)
{
	int     PathWidth ;
	int     PathHeight ; 
	CPoint  ptBasePos ; 
	// 公用路线的坐标
	STEP PubPath[PUBLIC_PATH_STEP];	
	// 停机坪的坐标
	struct PRVPATH
	{
		STEP Park[PLAYER_PLANE_NUM];	// 四架飞机停放的格子
		STEP TakeOff;					// 起飞的格子
		STEP Landing[PRIVATE_PATH_STEP]; // 着陆的格子
		STEP DashedS;					// 飞棋的开始格子
		STEP DashedE;					// 飞棋的结束格子
	}PrvPath[PLAY_COUNT]; 

	///设置坐标基准点
	void  SetBasePt(int iWidth , int iHeight , CPoint pt)
	{
		PathWidth  = iWidth ; 
		PathHeight = iHeight ; 
		ptBasePos = pt ;
	}
	// 根据我的颜色方生成以我为主的坐标系,包括每个棋格，飞机停放位置，飞棋位置
	void IniCoordinate(enumSide enMySide)		
	{
		for(int i = 0; i < PUBLIC_PATH_STEP; i += 4)
		{
			PubPath[i].cbSide   = emBlue;
			PubPath[i+1].cbSide = emGreen ;
			PubPath[i+2].cbSide = emRed;
			PubPath[i+3].cbSide = emYellow;
		}

		int nStartStepX = 0,nStartStepY = 0,nStepSize = 0;
		int i = 0 ; 
		// 首先生成一个临时的坐标
		STEP tPubPath[PUBLIC_PATH_STEP]; 
		for(i = 0; i <= 3; i++)		
		{
			tPubPath[i].enPlaneDt = emUp;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x - 3*PathWidth ,ptBasePos.y + (7 -i)*PathHeight) ;
		}

		for(i = 4; i <= 6; i++)
		{
			tPubPath[i].enPlaneDt = emLeft;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x - i*PathWidth ,ptBasePos.y + 3*PathHeight) ;
		}
		for(i = 7; i <= 12; i++)
		{
			tPubPath[i].enPlaneDt = emUp;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x - 7*PathWidth ,ptBasePos.y + (10 -i)*PathHeight) ;
		}

		for(i = 13; i <= 16; i++)	
		{
			tPubPath[i].enPlaneDt = emRight;	
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x + (i -20 )*PathWidth ,ptBasePos.y -3*PathHeight) ;
		}

		for(i = 17; i <= 19; i++)	
		{
			tPubPath[i].enPlaneDt = emUp;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x - 3*PathWidth ,ptBasePos.y +(13-i)*PathHeight) ;
		}

		for(i = 20; i <= 25; i++)	
		{
			tPubPath[i].enPlaneDt = emRight;	
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x +(i -23 )*PathWidth ,ptBasePos.y -7*PathHeight) ;
		}

		for (i = 26; i <= 29; i++)
		{
			tPubPath[i].enPlaneDt = emDown;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x +3*PathWidth ,ptBasePos.y + (i - 33)*PathHeight) ;
		}

		for(i = 30; i <= 32; i++)	
		{
			tPubPath[i].enPlaneDt = emRight;	
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x + (i - 26)*PathWidth ,ptBasePos.y -3*PathHeight) ;
		}
		for(i = 33; i <= 38; i++)	
		{
			tPubPath[i].enPlaneDt = emDown;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x + 7*PathWidth ,ptBasePos.y + (i - 36)*PathHeight) ;
		}
		for(i = 39; i <= 42; i++)	
		{
			tPubPath[i].enPlaneDt = emLeft;	
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x + ( 46-i)*PathWidth ,ptBasePos.y + 3*PathHeight) ;
		}
		for(i = 43; i <= 45; i++)	
		{
			tPubPath[i].enPlaneDt = emDown;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x + 3*PathWidth ,ptBasePos.y + (i - 39)*PathHeight) ;
		}

		for(i = 46; i <= 51; i++)	
		{
			tPubPath[i].enPlaneDt = emLeft;
			tPubPath[i].ptPathPos.SetPoint(ptBasePos.x + ( 49- i)*PathWidth ,ptBasePos.y + 7*PathHeight) ;
		}
		tPubPath[3].enPlaneDt  = emLeftUp;
		tPubPath[16].enPlaneDt = emUpRight;
		tPubPath[29].enPlaneDt = emRightDown;
		tPubPath[42].enPlaneDt = emDownLeft;

		//// 根据我的颜色方，生成我的坐标系
		for(i = 0; i < PUBLIC_PATH_STEP; i++)
		{
			// 这句话可以这样理解:对于我来说的位置0,实际是公共路径的位置GetPublicStepIndex(enMySide,i)
			PubPath[GetPublicStepIndex(enMySide, i)].ptPathPos = tPubPath[i].ptPathPos;
			PubPath[GetPublicStepIndex(enMySide, i)].enPlaneDt = tPubPath[i].enPlaneDt;
		}

		for(int i = 0 ; i<PLAY_COUNT ; i++)
		{
			int  xSign  ;
			int  ySign  ; 

			int  iViewPos = GetUserRelativePos(enMySide , i) ; 

			for(int  j = 0 ; j< PLAYER_PLANE_NUM ; j++)
			{
				 xSign = ((j%2 == 0)?-1 : 1) ;
				 ySign =  ((j>1)?1 : -1) ;

				if(iViewPos%2 == 0)
				{
					PrvPath[i].Park[j].ptPathPos.x = (PubPath[i*13 + 6].ptPathPos.x + PubPath[i*13 + 7].ptPathPos.x)/2 + xSign*SPACE_WIDE ; 
					PrvPath[i].Park[j].ptPathPos.y = (PubPath[i*13].ptPathPos.y + PubPath[i*13 + 1].ptPathPos.y)/2  + ySign*SPACE_WIDE; 
				}
				else
				{
					PrvPath[i].Park[j].ptPathPos.x = (PubPath[i*13].ptPathPos.x + PubPath[i*13 + 1].ptPathPos.x)/2 + xSign*SPACE_WIDE ; 
					PrvPath[i].Park[j].ptPathPos.y = (PubPath[i*13 + 6].ptPathPos.y + PubPath[i*13 + 7].ptPathPos.y)/2 + ySign*SPACE_WIDE;
				}

				if(iViewPos == 0 )
				{
					PrvPath[i].Park[j].enPlaneDt = emLeft ; 
				}
				else if(iViewPos == 1)
				{
					PrvPath[i].Park[j].enPlaneDt = emUp ; 
				}
				else if(iViewPos == 2 )
				{
					PrvPath[i].Park[j].enPlaneDt = emRight ; 
 				}
				else if(iViewPos == 3 )
				{
					PrvPath[i].Park[j].enPlaneDt = emDown ; 
				}
				else 
				{
					PrvPath[i].Park[j].enPlaneDt = emErrorDir ; 
				}
			}
    
			xSign = ((iViewPos>1)?-1:1);
		    ySign = ((iViewPos == 0 || iViewPos == 3 )?-1:1) ; 

			PrvPath[i].TakeOff.ptPathPos.x = PubPath[i*13].ptPathPos.x + xSign *PathWidth ; 
			PrvPath[i].TakeOff.ptPathPos.y = PubPath[i*13].ptPathPos.y + ySign *PathHeight ; 

			if(iViewPos == 0 )
			{
				PrvPath[i].TakeOff.enPlaneDt = emDownLeft ; 
			}
			else if(iViewPos == 1)
			{
				PrvPath[i].TakeOff.enPlaneDt = emLeftUp ; 
			}
			else if(iViewPos == 2 )
			{
				PrvPath[i].TakeOff.enPlaneDt = emUpRight ; 
			}
			else if(iViewPos == 3 )
			{
				PrvPath[i].TakeOff.enPlaneDt = emRightDown ; 
			}
			else 
			{
				PrvPath[i].TakeOff.enPlaneDt = emErrorDir ; 
			}

			if(iViewPos%2 ==  0)
			{
				xSign = 0 ; 
				ySign = ((iViewPos == 2)?-1:1); 
			}
			else
			{
				xSign = ((iViewPos == 1)?-1:1) ; 
				ySign = 0 ;
			}

			for(int  j = 0 ; j<PRIVATE_PATH_STEP ; j++)
			{
				PrvPath[i].Landing[j].ptPathPos.x =  PubPath[(i+3)%PLAY_COUNT *13 +10].ptPathPos.x + xSign *(j + 1)*PathWidth ;
				PrvPath[i].Landing[j].ptPathPos.y =  PubPath[(i+3)%PLAY_COUNT *13 +10].ptPathPos.y + ySign *(j + 1) *PathHeight ;

				if(iViewPos == 0 )
				{
					PrvPath[i].Landing[j].enPlaneDt = emDown ; 
				}
				else if(iViewPos == 1)
				{
					PrvPath[i].Landing[j].enPlaneDt = emLeft ; 
				}
				else if(iViewPos == 2 )
				{
					PrvPath[i].Landing[j].enPlaneDt = emUp ; 
				}
				else if(iViewPos == 3 )
				{
					PrvPath[i].Landing[j].enPlaneDt = emRight ; 
				}
				else 
				{
					PrvPath[i].Landing[j].enPlaneDt = emErrorDir ; 
				}
			}
		}
	}
};


///玩家的数据(供服务端保存数据)
struct   PLAYER
{
	BYTE            cbSide;		               //玩家的颜色
	PLANE           Plane[PLAYER_PLANE_NUM];   //玩家的飞机
	MAGIC           Magic[MAX_MAGIC_NUM] ;     //玩家拥有的魔法（当前只有巧借东风）
	
	PLAYER()
	{
		cbSide = 255 ; 
		memset(Plane , 0 , sizeof(Plane)) ; 
		memset(Magic , 0 , sizeof(Magic)) ;
	}
	void Reset()
	{
		cbSide = 255 ; 
		memset(Plane , 0 , sizeof(Plane)) ; 
		memset(Magic , 0 , sizeof(Magic)) ;
	}
} ;
///游戏场景(供客户端使用)
struct  GameScence
{
	BYTE          cbMySide ;                                   ///我自己的方位
	BYTE          cbGameStation[PLAY_COUNT] ;                  ///游戏状态
	PLANE         PlaneIndex[PLAY_COUNT][PLAYER_PLANE_NUM] ;   ///当前每个人飞机的状况
	MAGIC         MagicIndex[PLAY_COUNT][MAX_MAGIC_NUM] ;      ///玩家拥有的魔法（当前只有巧借东风）
	
	GameScence()
	{
		cbMySide = 255 ; 
		memset(cbGameStation , 0 , sizeof(cbGameStation)) ; 
		memset(MagicIndex , 0 , sizeof(MagicIndex)) ; 
		for(int i = 0 ; i<PLAY_COUNT ; i++)
		{
		  for (int j = 0 ; j<PLAYER_PLANE_NUM ; j++)
		  {
			  PlaneIndex[i][j].Reset() ; 
		  }
		}
	}
	void Reset()
	{
		cbMySide = 255 ; 
		memset(cbGameStation , 0 , sizeof(cbGameStation)) ; 
		memset(MagicIndex , 0 , sizeof(MagicIndex)) ; 
		for(int i = 0 ; i<PLAY_COUNT ; i++)
		{
			for (int j = 0 ; j<PLAYER_PLANE_NUM ; j++)
			{
				PlaneIndex[i][j].Reset() ; 
			}
		}
	}
};
///飞行棋逻辑
class CUpGradeGameLogic
{
public:
	///构造函数		
	CUpGradeGameLogic(void);
	///析构函数
	virtual ~CUpGradeGameLogic();

public:
	///玩家信息
	PLAYER   m_PlayerSerInfo[PLAY_COUNT] ;    ///四个人的飞机信息（玩家在服务端的信息都是从0开始）

	int      m_iPlayerfight[2] ;           ///双方的战绩


public:
	///初始化数据
	void  InitServerData(void) ;
	///将服务端的数据转化为客户端的数据
	void  ChangeDate(BYTE  iDeskStation) ; 
	///查找玩家是否有活动的飞机，返回活动飞机的数量
	int   FindActivePlaneCount(BYTE iDeskStation ) ; 
	///查找有几架飞机已经完成飞行任务
	int   FindPlaneFinishCount(BYTE iDeskStation) ; 
	///找到一个可以飞的飞机
	int   FindOnePlaneToFly(BYTE  bDeskStation , BYTE cbDiceValue) ; 
	///获取该点有多少个敌方的棋子
	int   GetEnemyInStepCount(BYTE cbSide, BYTE cbStep ,PLANE Plane[])  ;
	///获取该点有多少个敌方的棋子
	int   GetEnemyInStepCount(BYTE cbSide, BYTE cbStep ,GameScence ScenceData ) ;
	///获取改点有多少个自己的棋子
	int   GetMyselfInStepCount(BYTE  cbSide , BYTE cbStep , PLANE Plane[]) ; 
	///获取改点有多少个自己的棋子
	int   GetMyselfInStepCount(BYTE cbSide , BYTE cbStep , GameScence ScenceData) ;
	///获取在该点我是否能飞行
	bool  IsCanFly(BYTE cbSide , BYTE cbStep ) ; 
	///是否可以走捷径
	bool  IsCanShortCut(BYTE  cbSide , BYTE cbStep ) ; 
	///判断玩家是否可以走捷径
	bool  IsCanShortCut(BYTE cbSide , BYTE cbStep ,GameScence ScenceData ) ;
	///判断指定的飞机是否能够飞行
	bool  IsCanMove(BYTE bDeskStation , BYTE inDex ,BYTE cbDiceValue) ;
	///玩家服务端走棋客户端是根据服务端走棋而改变的
	int   PlayerPlaneFly(BYTE  bDeskStation , BYTE cbDiceValue , int inDex , PlaneFlyStruct  PlaneActiveTrack[]) ; 
	///检测游戏是否结束
	bool  CheckGameFinish(BYTE bDeskStation ) ; 
	///找到一个可以飞的飞机
	int   FindOnePlaneToFly(BYTE  bDeskStation , BYTE cbDiceValue ,GameScence ScenceData) ; 
	/// 获取飞机飞行的位置
	int  GetPlaneFlyPos(BYTE bDeskStation , int inDex ,int cbDiceValue , GameScence ScenceData) ;
	///获取飞机的偏移索引
	int  GetPlanePixIndex(BYTE bDeskStation ,int inDex ,  BYTE  cbStep , GameScence ScenceData ) ;

};