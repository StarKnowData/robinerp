#include "StdAfx.h"
#include "ServerManage.h"
#include "writelog.h"
#include <math.h>
//游戏配置

bool CServerGameDesk:: m_bHaveKing;
bool CServerGameDesk:: m_bRobnt;
bool CServerGameDesk:: m_bAdddouble;
bool CServerGameDesk:: m_bShowcard;
UINT CServerGameDesk:: m_iPlayCard;
UINT CServerGameDesk:: m_iPlayCount;
UINT CServerGameDesk:: m_iSendCount;
UINT CServerGameDesk:: m_iBackCount;
UINT CServerGameDesk:: m_iUserCount;

BYTE CServerGameDesk:: m_iLimitUpGrade;
BOOL CServerGameDesk:: m_bKingCanReplace;
DWORD CServerGameDesk::m_iCardShape;
//游戏扩展配置
BYTE CServerGameDesk:: m_iThinkTime;
BYTE CServerGameDesk:: m_iBeginTime;
BYTE CServerGameDesk:: m_iGiveBackTime;
BYTE CServerGameDesk:: m_iCallScoreTime;
BYTE CServerGameDesk:: m_iAddDoubleTime;
BOOL CServerGameDesk:: m_bTurnRule;		//顺时针还是逆时针
int  CServerGameDesk:: m_iHammerMoney;		//加锤时扣的钱


void DebugPrintf(const char *p, ...)
{
	char szFilename[256];
	sprintf( szFilename, "E:\\bzw\\DebugInfo\\%dServer.txt", NAME_ID);
	FILE *fp = fopen( szFilename, "a" );
	if (NULL == fp)
	{
		return;
	}
	va_list arg;
	va_start( arg, p );
	vfprintf(fp, p, arg );
	fprintf(fp,"\n");
	fclose(fp);
}

void MyMsgBox(const char *lpszFormat, ...)
{
	va_list pArg;
	va_start(pArg, lpszFormat);
	char szMessage[1024] = { 0 };
#ifdef WIN32
	_vsnprintf(szMessage, 1023, lpszFormat, pArg);
#else
	vsnprintf(szMessage, 1023, lpszFormat, pArg);
#endif
	va_end(pArg);
	AfxMessageBox(szMessage);
}

//构造函数
CServerGameDesk::CServerGameDesk(void):CGameDesk(FULL_BEGIN)
{
	//c++ test
	::ZeroMemory(m_iUserCardCount,sizeof(m_iUserCardCount));
	::ZeroMemory(m_iUserCard,sizeof(m_iUserCard));
	::ZeroMemory(m_iBackCard,sizeof(m_iBackCard));
	::ZeroMemory(m_iDeskCard,sizeof(m_iDeskCard));
	//已初始化
	//m_iDeskCardCount  m_iRobNT m_iPeopleMul m_iAIStation m_bAuto m_iCallScore

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		m_iLastCardCount[i] = 0;
		m_iAwardPoint[i] = 0;
		m_iWinPoint[i] = 0;
	}
	::ZeroMemory(m_iLastOutCard, 0, PLAY_COUNT*45);
	m_iRecvMsg = 0;
	m_iBase = 0;
	m_iRobMul = 0;
	m_iBombMul = 0;
	m_iGameFlag = GS_FLAG_NORMAL;
	m_iUpGradePeople = -1;
	m_iLeaveArgee = 0;
	m_iNtFirstCount = 0;		//第一首牌清零
	//	m_iNowCallScorePeople = -1;		//
	m_iBaseOutCount = 0;
	m_iNtPeople = -1;
	m_iDealPeople = -1;
	m_iUpGradePeople = -1;
	m_iFirstOutPeople = -1;
	m_iNowBigPeople = -1;
	m_iOutCardPeople = -1;
	m_iBeenPlayGame = 0;
	m_bGameStation = GS_WAIT_ARGEE;
	m_bThrowoutCard = 0x00;
	m_bFirstCallScore = 255;
	m_iPrepareNT = 255;		//预备庄家
	m_bHaveSendBack = false;
	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));	
	::memset(m_iRobNT,0,sizeof(m_iRobNT));				//抢地主亮牌变量
	::memset(m_iPeopleMul,1,sizeof(m_iPeopleMul));		//加棒变量
	::memset(m_iAIStation,0,sizeof(m_iAIStation));		//智能托管
	::memset(m_bAuto,0,sizeof(m_bAuto));				//托管
	::memset(m_iCallScore,-1,sizeof(m_iCallScore));		//叫分
	::memset(m_bCanleave,1,sizeof(m_bCanleave));
	::memset(m_iHistroyData , 0 , sizeof(m_iHistroyData)) ; 
	
	m_iFirstCutPeople = 255;
	m_icountleave = 0;
	LoadIni();
	//加载局数限制
//	LoadExtIni();

	InitThisGame();
#ifdef SUPER_VERSION
	for(int i = 0; i < 8; i++)
	{
		m_iSuperCardCount[i] = 0;
		::memset(m_bSuperCardList[i],0,sizeof(m_bSuperCardList[i]));
	}
	m_bSuperStation = -1;
#endif

	::memset(m_byUserChui,255,sizeof(m_byUserChui));				//记录玩家是否加锤
}

//析构函数
CServerGameDesk::~CServerGameDesk(void)
{
}

//加载ini配置文件
BOOL CServerGameDesk::LoadIni()
{
	CString nid;
	nid.Format("%d",NAME_ID);
	CString s = CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s +nid +"_s.ini");
	CString key = TEXT("game");
	m_bHaveKing = f.GetKeyVal(key,"haveking",1);
	m_iPlayCard = f.GetKeyVal(key,"card",1);
	m_iPlayCount = f.GetKeyVal(key,"cardcount",54);

	m_iSendCount = f.GetKeyVal(key,"sendcard",51);

	m_iBackCount = f.GetKeyVal(key,"backcard",3);
	m_iUserCount = f.GetKeyVal(key,"usercount",17);

	m_iLimitUpGrade = f.GetKeyVal(key,"limitupgrade",5);
	m_bKingCanReplace = f.GetKeyVal(key,"kingcanreplace",0);
	m_iHammerMoney = f.GetKeyVal(key,"iHammerMoney",0);
	key=TEXT("other");
	m_iBeginTime = f.GetKeyVal(key,"begintime",30);
	m_iThinkTime = f.GetKeyVal(key,"thinktime",30);
	m_iGiveBackTime = f.GetKeyVal(key,"givebacktime",30);
	m_iCallScoreTime = f.GetKeyVal(key,"CallScoretime",15);
	m_iAddDoubleTime = f.GetKeyVal(key,"adddoubletime",5);
	key = TEXT("cardshape");
	m_iCardShape &=0x00000000;
	m_iCardShape |= (f.GetKeyVal(key,"one",1)&0xFFFFFFFF);//单张
	m_iCardShape |= ((f.GetKeyVal(key,"two",1)<<1)&0xFFFFFFFF);//对
	m_iCardShape |= ((f.GetKeyVal(key,"three",1)<<2)&0xFFFFFFFF);//三条
	m_iCardShape |= ((f.GetKeyVal(key,"threeandone",1)<<3)&0xFFFFFFFF);//三带单
	m_iCardShape |= ((f.GetKeyVal(key,"threeandtwo",0)<<4)&0xFFFFFFFF);//三带二单
	m_iCardShape |= ((f.GetKeyVal(key,"threeanddouble",1)<<5)&0xFFFFFFFF);//三带对

	m_iCardShape |= ((f.GetKeyVal(key,"traight",1)<<6)&0xFFFFFFFF);//单顺
	m_iCardShape |= ((f.GetKeyVal(key,"traightflush",0)<<7)&0xFFFFFFFF);//同花顺
	m_iCardShape |= ((f.GetKeyVal(key,"twosequence",1)<<8)&0xFFFFFFFF);//双顺
	m_iCardShape |= ((f.GetKeyVal(key,"threesequence",1)<<9)&0xFFFFFFFF);//三顺
	m_iCardShape |= ((f.GetKeyVal(key,"threeandonesequence",1)<<10)&0xFFFFFFFF);//三带带单
	m_iCardShape |= ((f.GetKeyVal(key,"threeandtwosequence",0)<<11)&0xFFFFFFFF);//三带二单顺
	m_iCardShape |= ((f.GetKeyVal(key,"threeanddublesequence",1)<<12)&0xFFFFFFFF);//三带对顺

	m_iCardShape |= ((f.GetKeyVal(key,"fourandone",0)<<13)&0xFFFFFFFF);//四带一
	m_iCardShape |= ((f.GetKeyVal(key,"fourandtwo",1)<<14)&0xFFFFFFFF);//四带二单
	m_iCardShape |= ((f.GetKeyVal(key,"fourandonedouble",0)<<15)&0xFFFFFFFF);//四带一对
	m_iCardShape |= ((f.GetKeyVal(key,"fourandtwodouble",1)<<16)&0xFFFFFFFF);//四带二对

	m_iCardShape |= ((f.GetKeyVal(key,"510k",0)<<17)&0xFFFFFFFF);			//510k
	m_iCardShape |= ((f.GetKeyVal(key,"master510k",0)<<18)&0xFFFFFFFF);		//同花510k
	m_iCardShape |= ((f.GetKeyVal(key,"bomb",1)<<19)&0xFFFFFFFF);			//炸弹
	m_iCardShape |= ((f.GetKeyVal(key,"kingbomb",1)<<20)&0xFFFFFFFF);		//王炸
	return true;
}

//加载局数限制
BOOL CServerGameDesk::LoadExtIni()
{
	CString s = CINIFile::GetAppPath ();/////本地路径
	CString nid;
	nid.Format("%d",NAME_ID);
	CINIFile f( s +nid +"_s.ini");

	TCHAR szKey[20];
	wsprintf(szKey,"%s",nid);
	CString key = szKey;
	m_bTurnRule = f.GetKeyVal(key,"TurnRule",0);
	m_iLimitPlayGame = f.GetKeyVal(key,"limitplay",1);
	m_bRobnt = f.GetKeyVal(key,"robnt",0);
	m_bAdddouble=f.GetKeyVal(key,"adddouble",1);
	m_bShowcard=f.GetKeyVal(key,"showcard",0);
	m_iHammerMoney = f.GetKeyVal(key,"iHammerMoney",0);
	return TRUE;
}

//根据房间ID加载配置文件
BOOL CServerGameDesk::LoadExtIni(int iRoomID)
{
	TCHAR szKey[20];
	CString nid;
	nid.Format("%d",NAME_ID);
	wsprintf(szKey,"%s_%d",nid,iRoomID);
	CString key = szKey;
	CString s = CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s +nid +"_s.ini");
	m_bTurnRule = f.GetKeyVal(key,"TurnRule",m_bTurnRule);
	m_iLimitPlayGame = f.GetKeyVal(key,"limitplay",m_iLimitPlayGame);
	m_bRobnt = f.GetKeyVal(key,"robnt",m_bRobnt);
	m_bAdddouble=f.GetKeyVal(key,"adddouble",m_bAdddouble);
	m_bShowcard=f.GetKeyVal(key,"showcard",m_bShowcard);
	m_iHammerMoney = f.GetKeyVal(key,"iHammerMoney",0);
	
	return TRUE;
}

//拦截玩家强退消息
bool CServerGameDesk::HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	ASSERT(pNetHead->bMainID==MDM_GM_GAME_FRAME);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_FORCE_QUIT:
		{
			char cKey[10];
			CString sPath=CBcfFile::GetAppPath();
			int iResult = 1;
			if (CBcfFile::IsFileExist(sPath + "SpecialRule.bcf"))
			{
				CBcfFile fsr( sPath + "SpecialRule.bcf");
				sprintf(cKey, "%d", NAME_ID);
				iResult = fsr.GetKeyVal (_T("ForceQuitAsAuto"), cKey, 1);
			}

			if (iResult == 0)
			{
				return __super::HandleFrameMessage( bDeskStation,  pNetHead,  pData,  uSize,  uSocketID,  bWatchUser); 
			}
			return true;
		}
		break;
	default:
		break;
	}
	return __super::HandleFrameMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}

//机器人托管
BOOL CServerGameDesk::UseAI(BYTE bDeskStation)
{
	m_iAIStation[bDeskStation] = 1;

	int count = 0;
	for(int i = 0; i < PLAY_COUNT ; i ++)
		if(m_iAIStation[i])
			count ++;

	if(count >= PLAY_COUNT)
	{
		GameFinish(255,/*GFF_SAFE_FINISH*/GFF_FORCE_FINISH);
		return true;
	}
	SetAIMachine(bDeskStation,TRUE);
	return true;
}

//游戏数据包处理函数
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	switch (pNetHead->bAssistantID)
	{
#ifdef SUPER_VERSION
		case 79://超级客户端
			{
				if(bWatchUser)
					return FALSE;
				if(m_bGameStation == GS_PLAY_GAME)
					return true;
				SetCardStruct * pCard = (SetCardStruct*)pData;
				//默认方式(当前设置玩家)
				m_bSuperStation = bDeskStation ;
				if(pCard->paicount[0] > 0)//仅设置自家
				{
					m_iSuperCardCount[m_bSuperStation] = pCard->paicount[0];
					::CopyMemory(m_bSuperCardList[m_bSuperStation],pCard->pai[0],m_iSuperCardCount[m_bSuperStation]);

				}else//设置多家0位置给默认
				{
					for(int i = 1; i < 8; i ++)
					{
						m_iSuperCardCount[i-1] = pCard->paicount[i];
						::CopyMemory(m_bSuperCardList[i-1],pCard->pai[i],sizeof(BYTE)*m_iSuperCardCount[i-1]);
					} 
				}
				return TRUE;
			}
#endif
		case ASS_GM_AGREE_GAME:		//用户同意游戏
			{
				if (bWatchUser) 
					return FALSE;
				if(m_bGameStation != GS_WAIT_NEXT)
					m_bGameStation = GS_WAIT_ARGEE;

				////第一玩家同意后,每隔一段时间开始扫描是否可以开始游戏 
				//if(TY_MATCH_GAME == m_pDataManage->m_InitData.uComType)
				//	SetTimer(TIME_START_GAME,m_iBeginTime*1000);

				return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
			}
		case ASS_REPLACE_GM_AGREE_GAME:		//代替玩家同意游戏 
			{
				if ((bWatchUser)
					||(uSize!=sizeof(ReplaceAgreeStruct))) 
					return FALSE;
				ReplaceAgreeStruct *agree = (ReplaceAgreeStruct*)pData;
				//断线用户代替开始
				if(m_pUserInfo[agree->bDeskStation] != NULL
					&&m_pUserInfo[agree->bDeskStation]->m_UserData.bUserState == USER_ARGEE)
					return true;
				m_pUserInfo[agree->bDeskStation]->m_UserData.bUserState = USER_ARGEE;

				return true;
			}
		case ASS_CALL_SCORE:
			{
				if ((bWatchUser)
					||(uSize!=sizeof(CallScoreStruct))) 
					return FALSE;
				CallScoreStruct * pCallScore=(CallScoreStruct *)pData;
				UserCallScore(bDeskStation,pCallScore->iValue);
				return true;
			}
		case ASS_REPLACE_CALL_SCORE:
			{
				return true;//不再接受客户端代处理zht20100324
				if (uSize!=sizeof(ReplaceCallScoreStruct)) 
					return FALSE;
				ReplaceCallScoreStruct * pReplace=(ReplaceCallScoreStruct *)pData;
				UserCallScore(pReplace->bDeskStation,pReplace->CallScore);
				return true;
			}
		case ASS_ROB_NT:						//抢地主
			{
				
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				RobNTStruct * pRobNT=(RobNTStruct *)pData;
				UserRobNT(pRobNT->bDeskStation,pRobNT->iValue);
				return TRUE;
			}
		case ASS_REPLACE_ROB_NT:			//代替抢地主
			{
				return true;///不再接受客户端代处理zht20100324
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				RobNTStruct * pRobNT=(RobNTStruct *)pData;
				UserRobNT(pRobNT->bDeskStation,pRobNT->iValue);
				return true;
			}
		case ASS_SHOW_CARD:	//亮牌
			{
		
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				ShowCardStruct * pShowCard=(ShowCardStruct *)pData;
				UserShowCard(pShowCard->bDeskStation,pShowCard->iValue);
				return true;
			}
		case ASS_REPLACE_SHOW_CARD://代替亮牌
			{
				return true;//不再接受客户端代处理zht20100324
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				ReplaceShowCardStruct * pShowCard=(ReplaceShowCardStruct *)pData;
				UserShowCard(pShowCard->bRepDeskStation,pShowCard->iValue);
				return true;
			}
		case ASS_ADD_DOUBLE:					//加棒
			{
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				AddDoubleStruct * pAddDouble=(AddDoubleStruct *)pData;
				UserAddDouble(pAddDouble->bDeskStation,pAddDouble->iValue);
				return TRUE;
			}
		case ASS_REPLACE_ADD_DOUBLE:			//代替加棒
			{
				return true;//不再接受客户端代处理zht20100324
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				AddDoubleStruct * pAddDouble=(AddDoubleStruct *)pData;
				UserAddDouble(pAddDouble->bDeskStation,pAddDouble->iValue);
				return true;
			}	
		case ASS_OUT_CARD:		//用户出牌
			{
				if(bWatchUser)
					return false;
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				OutCardStruct * pOutCard=(OutCardStruct *)pData;
				if ((uSize<(sizeof(OutCardStruct)-sizeof(pOutCard->iCardList)))
					||(uSize>sizeof(OutCardStruct))||bWatchUser) return FALSE;
				if (uSize!=(sizeof(OutCardStruct)-sizeof(pOutCard->iCardList)+sizeof(BYTE)*pOutCard->iCardCount))
					return FALSE;
				UserOutCard(bDeskStation,pOutCard->iCardList,pOutCard->iCardCount);
				OutputDebugString("zhtlog:用户出牌");
				return true;
			}
		case ASS_REPLACE_OUT_CARD://代替出牌
			{
				return true;//不再接受客户端代处理zht20100324
				if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
					return true;
				ReplaceOutCardStruct * pOutCard=(ReplaceOutCardStruct *)pData;
				if ((uSize<(sizeof(ReplaceOutCardStruct)-sizeof(pOutCard->iCardList)))
					||(uSize>sizeof(ReplaceOutCardStruct))||bWatchUser) return FALSE;
				if (uSize!=(sizeof(ReplaceOutCardStruct)-sizeof(pOutCard->iCardList)+sizeof(BYTE)*pOutCard->iCardCount))
					return FALSE;
				UserOutCard(pOutCard->bDeskStation,pOutCard->iCardList,pOutCard->iCardCount);
				return true;
			}
			//辅助消息
		case ASS_HAVE_THING:	//有事请求离开
			{
				if(bWatchUser)
					return false;
				HaveThingStruct * pThing=(HaveThingStruct *)pData;
				UserHaveThing(bDeskStation,pThing->szMessage);
				return true;
			}
		case ASS_LEFT_RESULT: //同意用户离开
			{
				if(bWatchUser)
					return false;
				LeaveResultStruct * pLeave=(LeaveResultStruct *)pData;
				ArgeeUserLeft(bDeskStation,pLeave->bArgeeLeave);
				return true;
			}
		case ASS_AUTO:			//托管
			{
				if ((bWatchUser)
					||(uSize!=sizeof(AutoStruct))) 
					return FALSE;
				AutoStruct * pAuto = (AutoStruct*)pData;
				UserSetAuto(bDeskStation,pAuto->bAuto);
				return true;
			}
		case ASS_USER_VIP_VERTIFY:
			{
				if(bWatchUser)
				{
					return TRUE ; 
				}

				UserVipVertify(bDeskStation) ;

				return TRUE ; 
			}
		case ASS_CHUI:	//锤消息
			{
				if((bWatchUser)||(uSize!=sizeof(ChuiStruct)))
				{
					return FALSE;
				}

				ChuiStruct *pChui = (ChuiStruct*)pData;

				HandleChuiAction(pChui->bDeskStation,pChui->bIsChui);

				return TRUE ; 
			}
		default:
			{
				break ; 
			}

	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}


//設置游戲狀態
BOOL CServerGameDesk::InitThisGame()
{
	m_Logic.SetKingCanReplace(m_bKingCanReplace);
	m_Logic.SetCardShape(m_iCardShape);
	return true;
}
bool CServerGameDesk::InitDeskGameStation()
{
	LoadExtIni();
	LoadExtIni(m_pDataManage->m_InitData.uRoomID);
	return true;
}


#define IDT_USER_CUT				1L										//断线定时器 ID
//定时器消息
bool CServerGameDesk::OnTimer(UINT uTimerID)
{
	//JAdd-20090113-//取消1M倒计时退出
	if ((uTimerID>=IDT_USER_CUT)&&(uTimerID<(UINT)(IDT_USER_CUT+m_bMaxPeople)))
	{
		if (m_bGameStation>=20&&m_bGameStation<23)
		{
			return true;
		}
	}
	switch(uTimerID)
	{
	case TIME_START_GAME:
		{
			if(m_bGameStation == GS_WAIT_NEXT ||m_bGameStation == GS_WAIT_ARGEE)
			{
				StartGame();
			}else
			{
				KillTimer(TIME_START_GAME);
			}
			break;
		}
	case TIME_SEND_CARD:				//發牌
		{
			if (m_bGameStation == GS_SEND_CARD)
				SendCard();
			else KillTimer(TIME_SEND_CARD);
			break;
		}
	case TIME_SEND_ALL_CARD:
		{
			if (m_bGameStation == GS_SEND_CARD)
			{
				SendAllCard();
			}
			else 
			{
				KillTimer(TIME_SEND_ALL_CARD);
			}
			break;
		}
	case TIME_JIAO_FEN:                // 叫分定时器
		{
			KillTimer(TIME_JIAO_FEN);

			if (GS_WAIT_BACK == m_bGameStation && GS_FLAG_CALL_SCORE == m_iGameFlag)
			{
				// 自动不叫分
				UserCallScore(m_bCurrentCallScore, 0);
			}

			break;
		}
	case TIME_WAIT_NEWTURN:				//新一輪
		{
			KillTimer(TIME_WAIT_NEWTURN);
			if (m_bGameStation == GS_PLAY_GAME)
				NewPlayTurn(m_iNowBigPeople);
			break;
		}	
	case TIME_ADD_DOUBLE:
		{
			if (m_bGameStation == GS_WAIT_BACK)
				AddDoubleResult();
			else KillTimer(TIME_ADD_DOUBLE);
			break;
		}
	case TIME_ROB_NT:
		{
			if (m_bGameStation == GS_WAIT_BACK)
			{
				//OutputDebugString("zhtout:11111");
				UserRobNT(m_bCurrentCallScore,0);
			}
			else KillTimer(TIME_ROB_NT);
			break;
		}
	case TIME_WAIT_CALL:					//反牌(升级)
		{
			break;
		}	
	case TIME_OUT_CARD:
		{
			KillTimer(TIME_OUT_CARD);
			if (m_bGameStation == GS_PLAY_GAME) 
				UserAutoOutCard(m_iOutCardPeople);
			break;
		}
	case TIME_GAME_FINISH:				//結束
		{
			KillTimer(TIME_GAME_FINISH);
			if (m_bGameStation == GS_PLAY_GAME) 
				GameFinish(0,GF_NORMAL);
			break;
		}	
	case TIME_SHOW_CARD:
		{
			KillTimer(TIME_SHOW_CARD);
			if (m_bGameStation == GS_WAIT_BACK)
			{
				OutputDebugString("zhtout:11111");
				UserShowCard(m_iUpGradePeople,0);
			}
		}
	case TIME_CHUI:
		{
			KillTimer(TIME_CHUI);

			//超时的玩家为不锤
			for(int i = 0; i < PLAY_COUNT; ++i)
			{
				if(m_byUserChui[i] == 255)
				{
					m_byUserChui[i] = 0;
				}
			}

			GamePrepare();	//游戏准备

			break;
		}
	}
	return __super::OnTimer(uTimerID);
}

//获取游戏状态信息
bool CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{
	/// 玩家重连，表示不在托管状态，因此在这里设置为不托管
	if (!bWatchUser)
		m_bAuto[bDeskStation] = false;
	switch (m_bGameStation)
	{
	case GS_WAIT_SETGAME:		//游戏没有开始状态
	case GS_WAIT_ARGEE:			//等待玩家开始状态
		{
			GameStation_2 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;			//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;			//低版本
			//游戏内容设置
			GameStation.iPlayCard = m_iPlayCard;				//扑克副数
			GameStation.iPlayCount = m_iPlayCount;				//扑克总数
			GameStation.bKingCanReplace = m_bKingCanReplace;				//是否有王
			GameStation.iCardShape = m_iCardShape;						//牌型设置
			//辅助时间
			GameStation.iBeginTime = m_iBeginTime;				//游戏开始时间设置
			GameStation.iThinkTime = m_iThinkTime;				//游戏思考时间
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iAddDoubleTime = m_iAddDoubleTime;			//叫分时间
			//游戏轮数
			GameStation.iPlayLimit = m_iLimitPlayGame;
			
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();	//桌子倍数
			GameStation.iRoomBasePoint = GetRoomMul();	//房间倍数
			GameStation.iRunPublish = GetRunPublish();			//逃跑扣分
			GameStation.bTurnRule = m_bTurnRule;		//顺时针还是逆时针	
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	case GS_SEND_CARD:		//发牌状态
	case GS_WAIT_BACK:		//等待埋底牌状态
		{
			//发送取消机器人托管
			if(!bWatchUser)
				SetAIMachine(bDeskStation,false);

			GameStation_3 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;			//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;			//低版本
			//游戏轮数
			GameStation.iPlayLimit = m_iLimitPlayGame;
			//游戏内容设置
			GameStation.iPlayCard = m_iPlayCard;				//扑克副数
			GameStation.iPlayCount = m_iPlayCount;				//扑克总数
			GameStation.bKingCanReplace = m_bKingCanReplace;				//是否有王
			GameStation.iCardShape = m_iCardShape;						//牌型设置
			//辅助时间
			GameStation.iBeginTime = m_iBeginTime;				//游戏开始时间设置
			GameStation.iThinkTime = m_iThinkTime;				//游戏思考时间
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iAddDoubleTime = m_iAddDoubleTime;			//叫分时间
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();	//桌子倍数
			GameStation.iRoomBasePoint = GetRoomMul();	//房间倍数
			GameStation.iRunPublish = GetRunPublish();			//逃跑扣分
			GameStation.iBase = m_iBase;								//游戏倍数	

			GameStation.iUpGradePeople = m_iUpGradePeople;		
			GameStation.iBeenPlayGame = m_iBeenPlayGame;
			GameStation.iGameFlag = m_iGameFlag;				//m_iGameFlag分为叫分状态

			GameStation.iCallScoreResult = (m_iNtPeople == -1)?-1:m_iCallScore[m_iNtPeople];	//当前所叫的分
			GameStation.iCallScorePeople = m_bCurrentCallScore;
			memcpy(GameStation.bCanleave, m_bCanleave, sizeof(m_bCanleave));
			::CopyMemory(GameStation.byUserChui,m_byUserChui,sizeof(m_byUserChui));	//锤一锤数据
			GameStation.bTurnRule = m_bTurnRule;		//顺时针还是逆时针	

			//几家托管状态保存
			for(int i = 0; i < PLAY_COUNT; i ++)
			{
				GameStation.bAuto[i] = m_bAuto[i];
				GameStation.iCallScore[i] = m_iCallScore[i];	//当前几个人所叫分
				GameStation.iRobNT[i] = m_iRobNT[i];
			}

			int iPos = 0;
			ZeroMemory(&GameStation.iUserCardList, sizeof(GameStation.iUserCardList));
			for(int i = 0; i < PLAY_COUNT; i ++)
			{
				GameStation.iUserCardCount[i] = m_iUserCardCount[i];
				/// 只发自己的手牌，Modified by zxd 20100314
				if (bDeskStation == i)
				{
					::CopyMemory(&GameStation.iUserCardList[iPos],m_iUserCard[i],sizeof(BYTE)*m_iUserCardCount[i]);
				}
				iPos += m_iUserCardCount[i];
			}
			//发送数据
			int iSendSize = sizeof(GameStation);
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,iSendSize);
			return TRUE;
		}

	case GS_PLAY_GAME:	//游戏中状态
		{
			//发送取消机器人托管
			if(!bWatchUser)
				SetAIMachine(bDeskStation,false);
		
			GameStation_4 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;			//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;			//低版本
			//游戏内容设置
			GameStation.iPlayCard = m_iPlayCard;				//扑克副数
			GameStation.iPlayCount = m_iPlayCount;				//扑克总数
			GameStation.bKingCanReplace = m_bKingCanReplace;				//是否有王
			GameStation.iCardShape = m_iCardShape;						//牌型设置
			//辅助时间
			GameStation.iBeginTime = m_iBeginTime;				//游戏开始时间设置
			GameStation.iThinkTime = m_iThinkTime;				//游戏思考时间
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iAddDoubleTime = m_iAddDoubleTime;			//叫分时间
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();	//桌子倍数
			GameStation.iRoomBasePoint = GetRoomMul();	//房间倍数
			GameStation.iRunPublish = GetRunPublish();			//逃跑扣分
			//游戏轮数
			GameStation.iPlayLimit = m_iLimitPlayGame;

			//底牌
			//::memcpy(GameStation.iBackCard,m_iBackCard,sizeof(BYTE)*m_iBackCount);
			GameStation.iUpGradePeople = m_iUpGradePeople;		
			GameStation.iBeenPlayGame = m_iBeenPlayGame;		
			GameStation.iCallScoreResult = m_iCallScore[m_iUpGradePeople];	//当前叫分
			GameStation.iOutCardPeople = m_iOutCardPeople;	
			GameStation.iFirstOutPeople = m_iFirstOutPeople;	
			GameStation.iBigOutPeople = m_iNowBigPeople;	
			GameStation.iBaseOutCount = m_iBaseOutCount;	
			GameStation.iBase = m_iBase;							//游戏倍数	
			memcpy(GameStation.bCanleave, m_bCanleave, sizeof(m_bCanleave));
			memcpy(GameStation.iHistroyInfoData , m_iHistroyData, sizeof(GameStation.iHistroyInfoData)) ;
			::CopyMemory(GameStation.byUserChui,m_byUserChui,sizeof(m_byUserChui));	//锤一锤数据
			GameStation.bTurnRule = m_bTurnRule;		//顺时针还是逆时针	
			
			//托管状态
			for(int i = 0; i < PLAY_COUNT; i ++)
			{
				GameStation.bAuto[i] = m_bAuto[i];
				GameStation.iAwardPoint[i] = m_iAwardPoint[i];	//各家奖分
				GameStation.iPeopleBase[i] = m_iPeopleMul[i];	//加棒
				GameStation.iRobNT[i] = m_iRobNT[i];
			}	
			
			//设置各家手中牌
			int iPos = 0;
			ZeroMemory(&GameStation.iUserCardList, sizeof(GameStation.iUserCardList));
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				//设置用户手中牌
				GameStation.iUserCardCount[i] = m_iUserCardCount[i];
				/// 只发自己的手牌，Modified by zxd 20100314 地主亮明牌
				if (i==bDeskStation||(i==m_iUpGradePeople&&m_iRobNT[m_iUpGradePeople]>=2))
				{
					::CopyMemory(&GameStation.iUserCardList[iPos],m_iUserCard[i],sizeof(BYTE)*m_iUserCardCount[i]);
				}
				iPos += m_iUserCardCount[i];
				//设置用户桌面牌牌
				GameStation.iDeskCardCount[i] = m_iDeskCardCount[i];
				::CopyMemory(&GameStation.iUserCardList[iPos],m_iDeskCard[i],sizeof(BYTE)*m_iDeskCardCount[i]);
				iPos += m_iDeskCardCount[i];
				//设置上一轮扑克 
				GameStation.bIsLastCard = m_bIsLastCard;
				::CopyMemory(&GameStation.iLastCardCount, m_iLastCardCount, sizeof(BYTE)*PLAY_COUNT );
				::CopyMemory(GameStation.iLastOutCard[i], m_iLastOutCard[i], sizeof(BYTE)*m_iLastCardCount[i] );
			}
			//是否不出
			GameStation.bIsPass = m_byteHitPass;
			//当前最大牌
			GameStation.iBaseOutCount = m_iBaseOutCount;
			::CopyMemory(&GameStation.iUserCardList[iPos],m_iDeskCard[m_iNowBigPeople],sizeof(BYTE)*m_iBaseOutCount);
			iPos += m_iBaseOutCount;
			//底牌
			int iBackCount = m_iBackCount;
			GameStation.iBackCardCount = iBackCount;
			::CopyMemory(&GameStation.iUserCardList[iPos],m_iBackCard,sizeof(BYTE)*m_iBackCount);
			iPos += m_iBackCount;

			//发送数据
			int iSendSize = sizeof(GameStation);
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,iSendSize);
			return TRUE;
		}
	case GS_WAIT_NEXT:		//等待下一盘游戏开始
		{
			//发送取消机器人托管
			//SetAIMachine(bDeskStation,false);
			GameStation_5 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//游戏版本核对
			GameStation.iVersion = DEV_HEIGHT_VERSION;			//游戏高版本
			GameStation.iVersion2 = DEV_LOW_VERSION;			//低版本
			//游戏内容设置
			GameStation.iPlayCard = m_iPlayCard;				//扑克副数
			GameStation.iPlayCount = m_iPlayCount;				//扑克总数
			GameStation.iCardShape = m_iCardShape;				//牌型设置
			//辅助时间
			GameStation.iBeginTime = m_iBeginTime;				//游戏开始时间设置
			GameStation.iThinkTime = m_iThinkTime;				//游戏思考时间
			GameStation.iCallScoreTime = m_iCallScoreTime;			//叫分时间
			GameStation.iAddDoubleTime = m_iAddDoubleTime;			//叫分时间
			//游戏轮数
			GameStation.iPlayLimit = m_iLimitPlayGame;
			//房间倍数
			GameStation.iDeskBasePoint = GetDeskBasePoint();	//桌子倍数
			GameStation.iRoomBasePoint = GetRoomMul();	//房间倍数
			GameStation.iRunPublish = GetRunPublish();			//逃跑扣分
			GameStation.bTurnRule = m_bTurnRule;		//顺时针还是逆时针	
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	}
	return false;
}

//清所有计时器
void CServerGameDesk::KillAllTimer()
{
	KillTimer(TIME_SEND_CARD);
	KillTimer(TIME_SEND_ALL_CARD);
	KillTimer(TIME_WAIT_CALL);
	KillTimer(TIME_GAME_FINISH);
	KillTimer(TIME_WAIT_NEWTURN);
	KillTimer(TIME_OUT_CARD);
	KillTimer(TIME_START_GAME);
	KillTimer(TIME_ADD_DOUBLE);
	KillTimer(TIME_ROB_NT);
	KillTimer(TIME_SHOW_CARD);
}

//重置游戏状态
bool CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	KillAllTimer();
	if ((bLastStation == GFF_FORCE_FINISH)||( bLastStation== GF_SAFE))
	{
		::memset(m_iWinPoint,0,sizeof(m_iWinPoint));
		::memset(m_iAIStation,0,sizeof(m_iAIStation));
		m_iBeenPlayGame=0;
		m_iNtPeople=-1;
		m_iDealPeople=-1;
	}
	m_iPrepareNT = 255;		//预备庄家
	m_iUpGradePeople = -1;
	m_iBase = 0;
	m_iRobMul = 0;
	m_iBombMul = 0;
	m_iFirstCutPeople = 255;

	for(int i = 0;i < PLAY_COUNT; i ++)
	{
		m_iAwardPoint[i]=0;
	}
	m_iGameFlag = GS_FLAG_NORMAL;
	m_bCurrentCallScore = 255;
	m_iNtFirstCount=0;		//庄家出的第一手牌数量
	m_iLeaveArgee=0;
	m_iBaseOutCount=0;
	m_iNowBigPeople=-1;
	m_iOutCardPeople=-1;
	m_iSendCardPos=0;
	m_bFirstCallScore = 255;
	m_bHaveSendBack = false;
	memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));
	memset(m_iUserCardCount,0,sizeof(m_iUserCardCount));

	::memset(m_iRobNT,0,sizeof(m_iRobNT));				//抢地主亮牌变量
	::memset(m_iPeopleMul,1,sizeof(m_iPeopleMul));		//加棒变量
	::memset(m_iAIStation,0,sizeof(m_iAIStation));		//智能托管
	::memset(m_bAuto,0,sizeof(m_bAuto));				//托管
	::memset(m_iCallScore,-1,sizeof(m_iCallScore));		//叫分
	::memset(m_iHistroyData , 0 , sizeof(m_iHistroyData)) ; 

#ifdef SUPER_VERSION
	for(int i = 0; i < 8; i++)
	{
		m_iSuperCardCount[i] = 0;
		::memset(m_bSuperCardList[i],0,sizeof(m_bSuperCardList[i]));
	}
	m_bSuperStation = -1;
#endif
	::memset(m_byUserChui,255,sizeof(m_byUserChui));				//记录玩家是否加锤
	return TRUE;
}

//服务端自动开始游戏
BOOL CServerGameDesk::StartGame()
{
	for(int i = 0; i < PLAY_COUNT ;i++)
	{
		if(m_pUserInfo[i] == NULL)
			UseAI(i);
	}
	if(GameBegin(ALL_ARGEE))
		KillTimer(TIME_START_GAME);
	return TRUE;
}

//游戏开始
bool CServerGameDesk::GameBegin(BYTE bBeginFlag)
{
	if (__super::GameBegin(bBeginFlag)==false)
	{
		GameFinish(0,GF_SAFE);
		return false;
	}

	::ZeroMemory(m_iAIStation,sizeof(m_iAIStation));//清空代打情况；20090218 By Shao

	m_icountleave = 0;

	m_iSendCardPos = 0;
	m_iBeenPlayGame ++;
	m_bGameStation = GS_SEND_CARD;
	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));
	::memset(m_iUserCardCount,0,sizeof(m_iUserCardCount));
	::memset(m_bCanleave,1,sizeof(m_bCanleave));
	
	//发送开始消息
	BeginUpgradeStruct BeginMessage;
	BeginMessage.iUpgradeStation = m_iUpGradePeople;
	BeginMessage.iBeenPlayGame = m_iBeenPlayGame;
	BeginMessage.iPlayLimit = m_iLimitPlayGame;

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		m_iLastCardCount[i] = 0;
	}
	::ZeroMemory(m_iLastOutCard, 0, PLAY_COUNT*45);
	m_bIsLastCard = false;
	m_byteHitPass = 0;

	for (int i = 0; i < PLAY_COUNT; i ++)
		SendGameData(i,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_GAME_BEGIN,0);
	SendWatchData(m_bMaxPeople,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_GAME_BEGIN,0);

	//分发扑克
	BYTE iCardArray[162];
	m_Logic.RandCard(iCardArray,m_iPlayCount,m_bHaveKing);

#ifdef SUPER_VERSION
	for(int j = 0; j < PLAY_COUNT; j++)
	{
		for(int i = 0; i < m_iSuperCardCount[j]; i ++)
		{
			//仅适应一副牌
			int temp = m_Logic.GetSerialBySpecifyCard(iCardArray,0,m_iPlayCount,m_bSuperCardList[j][i]);

			if(temp != -1)
			{	
				BYTE t = iCardArray[i + j * m_iUserCount];
				iCardArray[i + j * m_iUserCount] = iCardArray[temp];
				iCardArray[temp] = t;
			}
		}
	}
#endif
	//明牌
	srand(GetTickCount());
	m_bThrowoutCard = iCardArray[rand() % (m_iSendCount/*m_iPlayCount - 3*/)];

	for (int i = 0; i < PLAY_COUNT; i ++)
	{
		::CopyMemory(m_iUserCard[i],&iCardArray[m_iUserCount*i],sizeof(BYTE)*m_iUserCount);
	}
	::CopyMemory(m_iBackCard,&iCardArray[m_iSendCount],sizeof(BYTE)*m_iBackCount);


#ifdef	SHAO_YANG
	SetTimer(TIME_CHUI,15*1000);	//设置加锤计时器
	ChuiStruct s_Chui;
	s_Chui.iFee = m_iHammerMoney;

	//发送锤一锤消息
	for(int i = 0; i < PLAY_COUNT; ++i)
	{
		s_Chui.bDeskStation = i;
		SendGameData(i,&s_Chui,sizeof(ChuiStruct),MDM_GM_GAME_NOTIFY,ASS_CHUI,0);
	}
	SendWatchData(m_bMaxPeople,&s_Chui,sizeof(ChuiStruct),MDM_GM_GAME_NOTIFY,ASS_CHUI,0);
#else
	GamePrepare();
#endif


	return TRUE;
}

//准备发牌
BOOL CServerGameDesk::GamePrepare()
{
	srand((unsigned int )time(0));

	m_iDealPeople = rand() % PLAY_COUNT;

	PrepareStruct Prepare;
	Prepare.bCard = m_bThrowoutCard;
	
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		Prepare.bUserVip = IsVipUser(i) ;
	
		SendGameData(i,&Prepare,sizeof(Prepare),MDM_GM_GAME_NOTIFY,ASS_GAME_PREPARE,0);
	}

	SendWatchData(m_bMaxPeople,&Prepare,sizeof(Prepare),MDM_GM_GAME_NOTIFY,ASS_GAME_PREPARE,0);

	SetTimer(TIME_SEND_ALL_CARD,1000);

	return TRUE;
}

//发送扑克给用户
BOOL CServerGameDesk::SendCard()
{
	if (m_iSendCardPos == m_iSendCount)
	{
		
		KillTimer(TIME_SEND_CARD);
		SendCardFinish();
		return TRUE;
	}
	//继续发送扑克(1次发两张)
	for(int i = 0; i < 2; i ++)
	{
		BYTE bDeskStation = (m_iDealPeople + m_iSendCardPos) % PLAY_COUNT;
		SendCardStruct SendCard;
		SendCard.bDeskStation = bDeskStation;
		SendCard.bCard = m_iUserCard[bDeskStation][m_iSendCardPos/PLAY_COUNT];

		for(int i = 0; i < PLAY_COUNT; i ++)
			SendGameData(i,&SendCard,sizeof(SendCard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD,0);
		SendWatchData(m_bMaxPeople,&SendCard,sizeof(SendCard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD,0);

		SendCardMsg(bDeskStation,SendCard.bCard);

		m_iUserCardCount[bDeskStation] ++;
		m_iSendCardPos ++;
		if(m_iSendCardPos == m_iSendCount)
			break;
	}

	return TRUE;
}

//发牌消息
BOOL CServerGameDesk::SendCardMsg(BYTE bDeskStation,BYTE bCard)
{
	if(m_bFirstCallScore != 255)
		return TRUE;
	if(bCard == m_bThrowoutCard)
	{
		m_bFirstCallScore = bDeskStation;
		SendCardStruct sendcard;
		sendcard.bDeskStation = bDeskStation;
		sendcard.bCard = m_bThrowoutCard;
		for(int i = 0; i < PLAY_COUNT; i ++)
			SendGameData(i,&sendcard,sizeof(sendcard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD_MSG,0);

		SendWatchData(m_bMaxPeople,&sendcard,sizeof(sendcard),MDM_GM_GAME_NOTIFY,ASS_SEND_CARD_MSG,0);
	}
	return TRUE;
}

///一次發所有牌
/// 为防止外挂看牌器存在，只发自己的手牌，他人的手牌清空。
/// 旁观玩家不发任何牌，以免作弊现象
/// 由ZXD修改于20100314

BOOL CServerGameDesk::SendAllCard()
{
	SendAllStruct SendAll;
	::memset(&SendAll,0,sizeof(SendAll));

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		m_iUserCardCount[i] = m_iUserCount;		
		SendAll.iUserCardCount[i] = m_iUserCardCount[i];
	}

	//发送数据
	int iPos = 0;
	for(int i = 0;i < PLAY_COUNT; i ++)
	{
		//memset(SendAll.iUserCardList,0,sizeof(SendAll.iUserCardList));
		::CopyMemory(&SendAll.iUserCardList[iPos],m_iUserCard[i],sizeof(BYTE)*m_iUserCardCount[i]);
		iPos += m_iUserCardCount[i];
		SendGameData(i,&SendAll,sizeof(SendAll),MDM_GM_GAME_NOTIFY,ASS_SEND_ALL_CARD,0);
		SendWatchData(i,&SendAll,sizeof(SendAll),MDM_GM_GAME_NOTIFY,ASS_SEND_ALL_CARD,0);
		::ZeroMemory(&SendAll.iUserCardList, sizeof(SendAll.iUserCardList));
	}
	
	m_iSendCardPos++;
	if(m_iSendCardPos == 1)
	{
		KillTimer(TIME_SEND_ALL_CARD);
		SendCardFinish();
		return FALSE;
	}

	return 0;
}

//发牌结束
BOOL CServerGameDesk::SendCardFinish()
{

	SendCardFinishStruct sendcardfinish;

	//发送发牌结束
	for(int i = 0; i < PLAY_COUNT; i ++)
		SendGameData(i,&sendcardfinish,sizeof(sendcardfinish),MDM_GM_GAME_NOTIFY,ASS_SEND_FINISH,0);
	SendWatchData(m_bMaxPeople,&sendcardfinish,sizeof(sendcardfinish),MDM_GM_GAME_NOTIFY,ASS_SEND_FINISH,0);

	if (m_bFirstCallScore == 255)
	{
		srand(GetTickCount());
		m_bFirstCallScore = rand()%PLAY_COUNT;
	}
	SendCallScore(m_bFirstCallScore);
	return true;
}

//发送给第一个叫分
BOOL CServerGameDesk::SendCallScore(BYTE bDeskStation)
{
	m_bGameStation = GS_WAIT_BACK;
	m_iGameFlag = GS_FLAG_CALL_SCORE;																	

	CallScoreStruct CallScore;
	CallScore.iValue = (m_iPrepareNT == 255) ? -1 : m_iCallScore[m_iPrepareNT];
	CallScore.bDeskStation = bDeskStation;						
	CallScore.bCallScoreflag = true;						

	m_bCurrentCallScore = bDeskStation ;

	for(int i = 0; i < PLAY_COUNT; i ++)
		SendGameData(i,&CallScore,sizeof(CallScore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE,0);

	SendWatchData(m_bMaxPeople,&CallScore,sizeof(CallScore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE,0);

	// 设置定时器 20秒内，叫分无响应，则服务器自动处理叫分 20100319 duanxiaohui 添加
	SetTimer(TIME_JIAO_FEN, (m_iCallScoreTime+5) * 1000);  

	return TRUE;
}

//叫分
BOOL CServerGameDesk::UserCallScore(BYTE bDeskStation, int iVal)
{
	if (bDeskStation != m_bCurrentCallScore)
	{
		return true;
	}

	// 结束叫分定时器
	KillTimer(TIME_JIAO_FEN);

	if(iVal == 0)
	{	
		m_iCallScore[bDeskStation] = 0;		//====某位置不叫分
	}
	else
	{
		m_iCallScore[bDeskStation] = iVal;	//叫分类型

		m_iPrepareNT = bDeskStation;				//最后叫分者

		if( iVal == 3)						//有人直接叫3分
		{
			CallScoreStruct callscore;
			callscore.bDeskStation = bDeskStation;
			callscore.bCallScoreflag = FALSE;					
			callscore.iValue = m_iCallScore[bDeskStation];		//当前叫分类型保存

			for(int i = 0; i < PLAY_COUNT; i ++)
				SendGameData(i,&callscore,sizeof(callscore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_RESULT,0);		//将叫分情况发给其他用户

			goto NT;
		}
	}
	CallScoreStruct callscore;
	callscore.bDeskStation = bDeskStation;
	callscore.bCallScoreflag = FALSE;					
	callscore.iValue = m_iCallScore[bDeskStation];		//当前叫分类型保存

	for(int i = 0; i < PLAY_COUNT; i ++)
		SendGameData(i,&callscore,sizeof(callscore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_RESULT,0);		//将叫分情况发给其他用户

	SendWatchData(m_bMaxPeople,&callscore,sizeof(callscore),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_RESULT,0);

	int iNextPeople = GetNextDeskStation(bDeskStation);

	if(m_iCallScore[iNextPeople] == 0)
		goto NT;

	if(m_iCallScore[iNextPeople] == -1)
	{
		SendCallScore(iNextPeople);
		return TRUE;
	}

NT:		
	CallScoreFinish();
	return true;
}

//叫分结束
BOOL CServerGameDesk::CallScoreFinish()
{
	if (m_iPrepareNT == 255 )	//没有人叫分.重新发牌
	{
		GameFinish(0,GF_NO_CALL_SCORE);
		return true;
	}
	if (m_iCallScore[m_iPrepareNT] == 0 )	//没有人叫分.重新发牌
	{
		GameFinish(0,GF_NO_CALL_SCORE);
		return true;
	}
	//用于抢地主位置结束控制
	m_iNtPeople = m_iPrepareNT;

	CallScoreStruct scoreresult;
	scoreresult.iValue = m_iCallScore[m_iPrepareNT];
	scoreresult.bDeskStation  = m_iPrepareNT;
	scoreresult.bCallScoreflag = false;
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&scoreresult,sizeof(scoreresult),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_FINISH,0);		//将叫分情况发给其他用户
	}

	SendWatchData(m_bMaxPeople,&scoreresult,sizeof(scoreresult),MDM_GM_GAME_NOTIFY,ASS_CALL_SCORE_FINISH,0);

	BYTE bDeskStation = GetRobNtDeskStation(m_iPrepareNT);
	if(bDeskStation == m_iPrepareNT || !m_bRobnt)
		RobNTFinish();
	else
		SendRobNT(bDeskStation);

	//直接进入游戏
	//SendBackCard();
	return TRUE;
}

//发送抢地主消息
BOOL CServerGameDesk::SendRobNT(BYTE bDeskStation)
{
	m_iGameFlag = GS_FLAG_ROB_NT;				//抢地主																
	//抢地主情况
	RobNTStruct  robnt;
	m_bCurrentCallScore = bDeskStation; ///当前抢地主玩家
	robnt.bDeskStation = bDeskStation;
	robnt.iValue = -1;

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&robnt,sizeof(robnt),MDM_GM_GAME_NOTIFY,ASS_ROB_NT,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&robnt,sizeof(robnt),MDM_GM_GAME_NOTIFY,ASS_ROB_NT,0);

	SetTimer(TIME_ROB_NT, (m_iCallScoreTime+5) * 1000); 
	return TRUE;
}

//玩家抢地主消息
BOOL CServerGameDesk::UserRobNT(BYTE bDeskStation, int iValue)
{
	KillTimer(TIME_ROB_NT);
	//抢地主结果情况
	if(iValue)
	{
		m_iRobNT[bDeskStation] += 1;				//抢地主
		m_iBase += 1;
		m_iRobMul += 1;
		AwardPointStruct awardpoint;
		::memset(&awardpoint,0,sizeof(awardpoint));
		awardpoint.iBase = m_iBase;
		//游戏统一倍数
		for(int i = 0 ; i < PLAY_COUNT;i++)
		{
			SendGameData(i,&awardpoint,sizeof(awardpoint),MDM_GM_GAME_NOTIFY,ASS_GAME_MULTIPLE,0);		//将叫分情况发给其他用户
		}
		m_iPrepareNT = bDeskStation;																	//新一预备庄家
	}
	RobNTStruct  robnt;
	robnt.bDeskStation = bDeskStation;
	robnt.iValue = iValue;
	for(int i = 0;i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&robnt,sizeof(robnt),MDM_GM_GAME_NOTIFY,ASS_ROB_NT_RESULT,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&robnt,sizeof(robnt),MDM_GM_GAME_NOTIFY,ASS_ROB_NT_RESULT,0);
	//地主最后抢
	if(bDeskStation == m_iNtPeople)
	{
		RobNTFinish();
		return TRUE;
	}

	BYTE bDesk = GetRobNtDeskStation(bDeskStation);
	//两农民未抢地主
	if(bDesk == m_iNtPeople 
		&&m_iRobNT[(m_iNtPeople + 1 )%PLAY_COUNT] == 0
		 &&m_iRobNT[(m_iNtPeople + 2 )%PLAY_COUNT] == 0)
	{
		RobNTFinish();
	}else
	{
		SendRobNT(bDesk);
	}
	return TRUE;
}

//获取下一个玩家位置
BYTE CServerGameDesk::GetNextDeskStation(BYTE bDeskStation)
{
	if(!m_bTurnRule)//顺时针
		return (bDeskStation + 1 ) % PLAY_COUNT;
	//逆时针
	return 	(bDeskStation + (PLAY_COUNT - 1)) % PLAY_COUNT;
}

//获取一个抢地主玩家
BYTE CServerGameDesk::GetRobNtDeskStation(BYTE bDeskStation)
{
	for(int i = GetNextDeskStation(bDeskStation); ; i = GetNextDeskStation(i))
	{
		if(m_iCallScore[i] != 0)
			return i;
	}
	return bDeskStation;
}

//抢地主结束
BOOL CServerGameDesk::RobNTFinish()
{
	//抢地主是否成功
	if(m_iPrepareNT != m_iNtPeople)
	{
		RobNTStruct  robresult;
		robresult.bDeskStation = m_iPrepareNT;
		robresult.iValue = -1;
		for (int i = 0; i < PLAY_COUNT; i ++) 
			SendGameData(i,&robresult,sizeof(robresult),MDM_GM_GAME_NOTIFY,ASS_ROB_NT_FINISH,0);
		SendWatchData(m_bMaxPeople,&robresult,sizeof(robresult),MDM_GM_GAME_NOTIFY,ASS_ROB_NT_FINISH,0);
	}

	//抢地主结束发底牌
	SendBackCard();
	return TRUE;
}

//发送底牌
BOOL CServerGameDesk::SendBackCard()
{
	//转庄家
//	m_iNtPeople = m_iPrepareNT;					// 20081027 zht 修改 抢地主时胜负判断错误的问题 
	if (m_bHaveSendBack)
	{
		return TRUE;
	}
	m_bHaveSendBack = true;

	m_iUpGradePeople = m_iPrepareNT;

	BackCardExStruct BackCard;
	BackCard.iGiveBackPeople = m_iUpGradePeople;
	BYTE byBackCount = m_iBackCount;
	BackCard.iBackCardCount = byBackCount;

	::CopyMemory(&m_iUserCard[m_iUpGradePeople][m_iUserCardCount[m_iUpGradePeople]],m_iBackCard,sizeof(BYTE)*BackCard.iBackCardCount);
	m_iUserCardCount[m_iUpGradePeople] += BackCard.iBackCardCount;

	::CopyMemory(BackCard.iBackCard,m_iBackCard,sizeof(BYTE)*BackCard.iBackCardCount);

	for (int i = 0; i < PLAY_COUNT; i ++) 
		SendGameData(i,&BackCard,sizeof(BackCard),MDM_GM_GAME_NOTIFY,ASS_BACK_CARD_EX,0);
	SendWatchData(m_bMaxPeople,&BackCard,sizeof(BackCard),MDM_GM_GAME_NOTIFY,ASS_BACK_CARD_EX,0);

	if(m_bAdddouble)
		SendAddDouble();
	else
		AddDoubleFinish();
	//直接进入游戏
	//BeginPlay();
	return TRUE;
}

//发送加棒消息
BOOL CServerGameDesk::SendAddDouble()
{
	m_iGameFlag = GS_FLAG_ADD_DOUBLE;				//加棒																
	m_iRecvMsg = 0;

	SetTimer(TIME_ADD_DOUBLE,m_iAddDoubleTime+5 * 1000);
	//抢地主情况
	AddDoubleStruct  adddouble;
	adddouble.bDeskStation = m_iUpGradePeople;
	adddouble.iValue = -1;

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&adddouble,sizeof(adddouble),MDM_GM_GAME_NOTIFY,ASS_ADD_DOUBLE,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&adddouble,sizeof(adddouble),MDM_GM_GAME_NOTIFY,ASS_ADD_DOUBLE,0);
	return  TRUE;
}

//玩家加棒
BOOL CServerGameDesk::UserAddDouble(BYTE bDeskStation, int iVal)
{
	m_iRecvMsg ++ ;

	if(iVal)
	{//玩家加棒
		m_iPeopleMul[bDeskStation] = 2;
	}

	if(m_iRecvMsg >= 2)
		AddDoubleResult();
	return TRUE;
}

//加棒结果
BOOL CServerGameDesk::AddDoubleResult()
{
	KillTimer(TIME_ADD_DOUBLE);

	for(int j = 0; j < PLAY_COUNT ;j++)
	{
		//抢地主结果情况
		AddDoubleStruct  adddouble;
		adddouble.bDeskStation = j;
		adddouble.iValue = m_iPeopleMul[j];

		for(int i = 0; i < PLAY_COUNT; i ++)
		{
			SendGameData(i,&adddouble,sizeof(adddouble),MDM_GM_GAME_NOTIFY,ASS_ADD_DOUBLE_RESULT,0);		//将叫分情况发给其他用户
		}
		SendWatchData(m_bMaxPeople,&adddouble,sizeof(adddouble),MDM_GM_GAME_NOTIFY,ASS_ADD_DOUBLE_RESULT,0);
	}
	AddDoubleFinish();

	return TRUE;
}

//加棒结束
BOOL CServerGameDesk::AddDoubleFinish()
{
	//抢地主结果情况
	AddDoubleStruct  adddouble;
	::memset(&adddouble,0,sizeof(adddouble));
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&adddouble,sizeof(adddouble),MDM_GM_GAME_NOTIFY,ASS_ADD_DOUBLE_FINISH,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&adddouble,sizeof(adddouble),MDM_GM_GAME_NOTIFY,ASS_ADD_DOUBLE_FINISH,0);

	if(m_bShowcard)
		SendShowCard();
	else
		ShowCardFinish();
	return true;
}

//亮牌
BOOL CServerGameDesk::SendShowCard()
{
	m_iGameFlag = GS_FLAG_SHOW_CARD;				//亮牌																
	ShowCardStruct show;
	show.bDeskStation = m_iUpGradePeople;

	SetTimer(TIME_SHOW_CARD, (m_iAddDoubleTime+5) * 1000); 

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&show,sizeof(show),MDM_GM_GAME_NOTIFY,ASS_SHOW_CARD,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&show,sizeof(show),MDM_GM_GAME_NOTIFY,ASS_SHOW_CARD,0);
	return TRUE;
}

//明牌消息
BOOL CServerGameDesk::UserShowCard(BYTE bDeskStation,int iValue)
{
	KillTimer(TIME_SHOW_CARD);
	if(iValue)
	{
		m_iBase += 1;
		m_iRobMul += 1;

		m_iRobNT[bDeskStation] += 2;				//亮牌
	}

	ShowCardStruct showresult;
	::ZeroMemory(&showresult, sizeof(showresult));
	showresult.bDeskStation = bDeskStation;
	showresult.iValue = iValue;
	showresult.iBase = m_iBase;//20081204
	showresult.iCardCount = m_iUserCardCount[bDeskStation];
	memcpy(showresult.iCardList,m_iUserCard[bDeskStation],sizeof(BYTE)*m_iUserCardCount[bDeskStation]);
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&showresult,sizeof(showresult),MDM_GM_GAME_NOTIFY,ASS_SHOW_CARD_RESULT,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&showresult,sizeof(showresult),MDM_GM_GAME_NOTIFY,ASS_SHOW_CARD_RESULT,0);

	ShowCardFinish();
	return TRUE;
}

//明牌结束
BOOL CServerGameDesk::ShowCardFinish()
{
	ShowCardStruct showresult;
	::memset(&showresult,0,sizeof(showresult));

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		SendGameData(i,&showresult,sizeof(showresult),MDM_GM_GAME_NOTIFY,ASS_SHOW_CARD_FINISH,0);		//将叫分情况发给其他用户
	}
	SendWatchData(m_bMaxPeople,&showresult,sizeof(showresult),MDM_GM_GAME_NOTIFY,ASS_SHOW_CARD_FINISH,0);

	BeginPlay();

	return TRUE;
}

//游戏开始
BOOL CServerGameDesk::BeginPlay()
{
	//设置数据
	m_bGameStation = GS_PLAY_GAME;
	m_iBaseOutCount = 0;
	m_iNowBigPeople = m_iOutCardPeople = m_iFirstOutPeople = m_iUpGradePeople;

	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));

	//排列扑克
	for (int i = 0; i < PLAY_COUNT; i ++) 
		m_Logic.SortCard(m_iUserCard[i],NULL,m_iUserCardCount[i]);

	//发送游戏开始消息
	BeginPlayStruct Begin;
	Begin.iOutDeskStation = m_iOutCardPeople;
	for (int i = 0;i < PLAY_COUNT; i ++)
		SendGameData(i,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);
	SendWatchData(m_bMaxPeople,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);

	if (m_pUserInfo[m_iOutCardPeople] != NULL)
	{
		// 判断该断线玩家是否掉线
		if (USER_CUT_GAME == m_pUserInfo[m_iOutCardPeople]->m_UserData.bUserState)
		{
			// 自动出牌
			SetTimer(TIME_OUT_CARD, 1000);
		}
		else
		{
			SetTimer(TIME_OUT_CARD,(m_iThinkTime + 8)*1000);
		}
	}

	return TRUE;
}

//用户出牌
BOOL CServerGameDesk::UserOutCard(BYTE bDeskStation,  BYTE iOutCard[],  int iCardCount)
{
	//GameFinish(bDeskStation,GF_NORMAL);
	//return true;
	CSingleLock singleLock(&m_Mutex);
	singleLock.Lock();

	if (bDeskStation != m_iOutCardPeople) 
		return true;
	

	//处理服务器牌
	if(iCardCount > 0)					
	{
		if(0 == m_iNtFirstCount)		//地主出的第一手牌
			m_iNtFirstCount = iCardCount;

		
		//增加出牌逻辑合法性判断zht 2010-03-23
		if (!m_Logic.CanOutCard(iOutCard,iCardCount,m_iDeskCard[m_iNowBigPeople],m_iDeskCardCount[m_iNowBigPeople],\
		                   m_iUserCard[bDeskStation],m_iUserCardCount[bDeskStation],bDeskStation == m_iNowBigPeople))
		{
			return TRUE;
		}
		if (m_Logic.RemoveCard(iOutCard,iCardCount,m_iUserCard[bDeskStation],m_iUserCardCount[bDeskStation]) == 0)
			return FALSE;


		KillTimer(TIME_OUT_CARD);
		m_iNowBigPeople = bDeskStation;
		m_iBaseOutCount = iCardCount;

		m_iUserCardCount[bDeskStation] -= iCardCount;
		//记录出牌信息
		m_iDeskCardCount[bDeskStation] = iCardCount;
		::CopyMemory(m_iDeskCard[bDeskStation],iOutCard,sizeof(BYTE)*iCardCount);

		for(int i = 0 ; i<iCardCount  ; i++)
		{
			m_iHistroyData[m_Logic.GetCardBulk(iOutCard[i],false)] ++ ; 
		}
	}
	else
	{
		KillTimer(TIME_OUT_CARD);
		//某一位置什麼牌也不出
		m_iDeskCardCount[bDeskStation] = iCardCount;

		m_byteHitPass |= (1<<bDeskStation);	//记录PASS
	}
	//发送玩家出牌结果
	OutCardMsg UserOutResult;
	UserOutResult.bDeskStation = bDeskStation;
	UserOutResult.iCardCount = iCardCount;
	::CopyMemory(UserOutResult.iCardList,iOutCard,sizeof(BYTE)*iCardCount);

	int iSendSizeReslut = sizeof(UserOutResult) - sizeof(UserOutResult.iCardList) + sizeof(BYTE) * iCardCount;

	for (int i = 0;i < PLAY_COUNT; i ++) 
		SendGameData(i,&UserOutResult,iSendSizeReslut,MDM_GM_GAME_NOTIFY,ASS_OUT_CARD_RESULT,0);

	SendWatchData(m_bMaxPeople,&UserOutResult,iSendSizeReslut,MDM_GM_GAME_NOTIFY,ASS_OUT_CARD_RESULT,0);

	//是否为加分牌型
	IsAwardPoin(iOutCard,iCardCount,bDeskStation);

	//====判断是否这个玩家是否出完牌
	if (m_iUserCardCount[bDeskStation] <= 0)
	{
		m_iDealPeople = bDeskStation;
		//出完牌各參數設置
		//OutCardFinish(bDeskStation);

		//检查是否结束
		//if(CheckFinish())
		{
			SetTimer(TIME_GAME_FINISH,1000);
			return true;
		}
	}
	//所出的牌最大,重新开始新一轮
	if(m_Logic.IsKingBomb(iOutCard,iCardCount))
	{	
		m_iNowBigPeople = m_iFirstOutPeople = m_iOutCardPeople = bDeskStation;
		IsNewTurn();
		return true;
	}

	//计算下一轮出牌者
	m_iOutCardPeople = GetNextDeskStation(bDeskStation);//(bDeskStation+1)%PLAY_COUNT;

	for(int i = m_iOutCardPeople ;;i = GetNextDeskStation(i))
	{
		m_iOutCardPeople = i;				//当前出牌者
		if(IsNewTurn())
			return true;
		//当前出牌者有牌未出
		if(m_iUserCardCount[i]>0)
			break;
	}

	OutCardMsg UserOut;
	UserOut.iNextDeskStation = m_iOutCardPeople;
	UserOut.iCardCount = 0;
	int iSendSize = sizeof(UserOut)-sizeof(UserOut.iCardList)+sizeof(BYTE)*iCardCount;

	for (int i=0;i<m_bMaxPeople;i++) 
		SendGameData(i,&UserOut,iSendSize,MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);

	SendWatchData(m_bMaxPeople,&UserOut,iSendSize,MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);

	// qy 20090804 增加8秒做延时
	//SetTimer(TIME_OUT_CARD,(m_iThinkTime + 8)*1000);

	// duanxiaohui 增加 20100319
	if (m_pUserInfo[m_iOutCardPeople] != NULL)
	{
		// 判断该断线玩家是否掉线
		if (USER_CUT_GAME == m_pUserInfo[m_iOutCardPeople]->m_UserData.bUserState)
		{
			// 自动出牌
			SetTimer(TIME_OUT_CARD, 1000);
		}
		else
		{
			SetTimer(TIME_OUT_CARD,(m_iThinkTime + 8)*1000);
		}
	}
	return TRUE;
}

//是否為新一輪
BOOL CServerGameDesk::IsNewTurn()
{
	if(m_iOutCardPeople == m_iFirstOutPeople)
	{
		for(int i = 0; i < PLAY_COUNT; i ++)
			SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_ONE_TURN_OVER,0);

		SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_ONE_TURN_OVER,0);
	}	

	if (m_iOutCardPeople == m_iNowBigPeople)			//最先出牌者
	{
		//m_iOutCardPeople = -1;

		SetTimer(TIME_WAIT_NEWTURN,1000);
		return true;
	}
	return false;
}
//新一轮开始
BOOL CServerGameDesk::NewPlayTurn(BYTE bDeskStation)
{
	m_iBaseOutCount = 0;
	m_iOutCardPeople = m_iFirstOutPeople = m_iNowBigPeople = bDeskStation;

	//保存上一轮出牌情况
	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		m_bIsLastCard = true;
		m_byteHitPass = 0;
		m_iLastCardCount[i] = m_iDeskCardCount[i];
		::CopyMemory(m_iLastOutCard[i],m_iDeskCard[i],sizeof(BYTE)*m_iLastCardCount[i]);
	}

	::memset(m_iDeskCardCount,0,sizeof(m_iDeskCardCount));

	NewTurnStruct turn;
	turn.bDeskStation = bDeskStation ;

	for (int i = 0; i < PLAY_COUNT; i ++) 
		SendGameData(i,&turn,sizeof(turn),MDM_GM_GAME_NOTIFY,ASS_NEW_TURN,0);
	SendWatchData(m_bMaxPeople,&turn,sizeof(turn),MDM_GM_GAME_NOTIFY,ASS_NEW_TURN,0);

	//SetTimer(TIME_OUT_CARD,(m_iThinkTime + 8)*1000);

	// duanxiaohui 增加 20100319
	if (m_pUserInfo[m_iOutCardPeople] != NULL)
	{
		// 判断该断线玩家是否掉线
		if (USER_CUT_GAME == m_pUserInfo[m_iOutCardPeople]->m_UserData.bUserState)
		{
			// 自动出牌
			SetTimer(TIME_OUT_CARD, 1000);
		}
		else
		{
			SetTimer(TIME_OUT_CARD,(m_iThinkTime + 8)*1000);
		}
	}
	return TRUE;
}

//所出牌中讨赏设置
BOOL CServerGameDesk::IsAwardPoin(BYTE iOutCard[],int iCardCount,BYTE bDeskStation)
{
	if(m_Logic.IsKingBomb(iOutCard,iCardCount) || m_Logic.IsBomb(iOutCard,iCardCount))
	{
		m_iBase += 1;
		m_iBombMul += 1;
		m_iAwardPoint[bDeskStation] += 1;							

		AwardPointStruct award;
		award.iAwardPoint = m_iAwardPoint[bDeskStation];
		award.bDeskStation = bDeskStation;
		award.iBase = m_iBase;
		//发送奖分情况
		for (int i = 0;i < PLAY_COUNT; i++) 
			SendGameData(i,&award,sizeof(award),MDM_GM_GAME_NOTIFY,ASS_AWARD_POINT,0);
		SendWatchData(m_bMaxPeople,&award,sizeof(award),MDM_GM_GAME_NOTIFY,ASS_AWARD_POINT,0);
	}
	return true;
}

//游戏结束
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	//编写代码
	switch (bCloseFlag)
	{
	case GF_NORMAL:		//游戏正常结束
		{
			//设置数据 
			m_bGameStation = GS_WAIT_NEXT;
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}

			BOOL bOutCard = GetNoOutCard();

			double t = pow((double)2.0,(int)m_iBase);

			__int64 iTurePoint = m_iCallScore[m_iNtPeople];

			//是谁胜
			if(m_iUserCardCount[m_iUpGradePeople] == 0)		
			{
				iTurePoint = iTurePoint;
			}
			else 
			{
				iTurePoint = - iTurePoint;
			}

			//游戏结束
			GameEndStruct GameEnd;
			::memset(&GameEnd,0,sizeof(GameEnd));
			GameEnd.iCallScore = m_iCallScore[m_iNtPeople];							//底分
			GameEnd.iRobMul = m_iRobMul;											//抢地主;
			GameEnd.iBombMul = m_iBombMul;											//炸弹;
			GameEnd.iOutCardMul = (bOutCard?1:0);
			GameEnd.iTotalMul = m_iBase;											//总倍数
			GameEnd.iUpGradeStation = m_iUpGradePeople;
			GameEnd.iBasePoint = GetRoomMul();
			memset(GameEnd.iTurePoint,0,sizeof(GameEnd.iTurePoint));
			memset(GameEnd.iInitScore,0,sizeof(GameEnd.iInitScore));

			memcpy(&GameEnd.iUserCard,&m_iUserCard,sizeof(GameEnd.iUserCard));
			memcpy(&GameEnd.iUserCardCount,&m_iUserCardCount,sizeof(m_iUserCardCount));

			//各家得分
			int iBaseCount = 0;						//加棒数
			for(int i = 0; i < PLAY_COUNT; i++)
			{
				if(m_iPeopleMul[i] == 2)
					iBaseCount ++;
			}

			for(int i = 0; i < PLAY_COUNT; i++)
			{
				if(i == m_iUpGradePeople)//庄家
				{
					GameEnd.iInitScore[i] = (2 + iBaseCount) * iTurePoint * t *( bOutCard ? 2 : 1);
					GameEnd.iTurePoint[i] = GameEnd.iInitScore[i];
				}
				else
				{
					//真实得分
					GameEnd.iInitScore[i] = - iTurePoint * (int)t * (bOutCard ? 2 : 1) * m_iPeopleMul[i];//加棒
					bool add =((m_iUserCardCount[i] == 0) && m_pDataManage->m_InitData.uComType == TY_MATCH_GAME);
					GameEnd.iTurePoint[i] = GameEnd.iInitScore[i] + (add ? 1 : 0) ;//先出完牌的农民加一分
				}
			}

#ifdef SHAO_YANG	//计算加锤
			int iTempChui = 0;
			GameEnd.iInitScore[m_iUpGradePeople] = 0;
			for(int i = 0; i < PLAY_COUNT; ++i)
			{
				if(i == m_iUpGradePeople)
					continue;

				int iChuiResult = (m_byUserChui[i]+m_byUserChui[m_iUpGradePeople])?(m_byUserChui[i]+m_byUserChui[m_iUpGradePeople]):1;
				GameEnd.iInitScore[i] = GameEnd.iInitScore[i]*iChuiResult;
				GameEnd.iTurePoint[i] =  GameEnd.iInitScore[i];

				GameEnd.iInitScore[m_iUpGradePeople] += -GameEnd.iInitScore[i];	//计算庄家的分数
			}

			GameEnd.iTurePoint[m_iUpGradePeople] =  GameEnd.iInitScore[m_iUpGradePeople];
#endif	
			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));


			ChangeUserPointint64(GameEnd.iTurePoint,temp_cut);
			__super::RecoderGameInfo(GameEnd.iChangeMoney);

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// 金币场不扣积分    add by wys 2010-11-1
			if (true == bNotCostPoint)
			{
				memset(GameEnd.iTurePoint,0,sizeof(GameEnd.iTurePoint));
			}
			//继续
			if(m_iBeenPlayGame >= m_iLimitPlayGame || TY_MATCH_GAME != m_pDataManage->m_InitData.uComType)//本轮结束
			{
				m_bGameStation = GS_WAIT_ARGEE;
				//DebugPrintf("GameEnd--iInitScore[%d][%d][%d]iChangeMoney[%d][%d][%d][%d][%d][%d][%d][%d]",
				//	GameEnd.iInitScore[0],
				//	GameEnd.iInitScore[1],
				//	GameEnd.iInitScore[2],
				//	GameEnd.iChangeMoney[0],
				//	GameEnd.iChangeMoney[1],
				//	GameEnd.iChangeMoney[2],
				//	GameEnd.iChangeMoney[3],
				//	GameEnd.iChangeMoney[4],
				//	GameEnd.iChangeMoney[5],
				//	GameEnd.iChangeMoney[6],
				//	GameEnd.iChangeMoney[7]
				//);

				for (int i = 0; i < PLAY_COUNT; i ++) 
					SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_NO_CONTINUE_END,0);
				SendWatchData(m_bMaxPeople,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_NO_CONTINUE_END,0);


				bCloseFlag = GFF_FORCE_FINISH;
				ReSetGameState(bCloseFlag);
				__super::GameFinish(bDeskStation,bCloseFlag);
				return TRUE;
			}
			else//下一局开始
			{
				for (int i = 0; i < PLAY_COUNT; i ++) 
					SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);
				SendWatchData(m_bMaxPeople,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);
				//设置数据 
				m_bGameStation = GS_WAIT_NEXT;
			}

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GF_NO_CALL_SCORE:
		{
			//设置数据 
			m_bGameStation = GS_WAIT_NEXT;

			BOOL bhavecut = false;
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
				{
					if(m_pUserInfo[i]->m_UserData.bUserState == USER_CUT_GAME)
					{
						bhavecut = true;
						break;
					}
					m_pUserInfo[i]->m_UserData.bUserState = USER_ARGEE;
				}
			}
			if(bhavecut)
			{
				GameFinish(255,GF_SAFE);
				return true;
			}
			//游戏结束
			GameEndStruct GameEnd;
			::memset(&GameEnd,0,sizeof(GameEnd));
			//发送数据
			for (int i = 0; i < PLAY_COUNT; i ++) 
				SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_NO_CALL_SCORE_END,0);
			SendWatchData(m_bMaxPeople,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_NO_CALL_SCORE_END,0);

			ReSetGameState(GF_NORMAL);

			GameBegin(ALL_ARGEE);
			return true;
		}
	case GFF_SAFE_FINISH:
	case GF_SAFE:			//游戏安全结束
		{
			//////////////////////////////////////////////////////////////////////////
			if (m_bGameStation >= GS_SEND_CARD && m_bGameStation < GS_WAIT_NEXT && bDeskStation != 255)
			{
				//MyMsgBox("SAFE %d", bDeskStation);
				m_iFirstCutPeople = bDeskStation;
				SetAIMachine(bDeskStation, true);
				return true;
			}
			if (bDeskStation == 255)
			{
				bDeskStation = 0;
			}
			//////////////////////////////////////////////////////////////////////////
			//设置数据
			m_bGameStation = GS_WAIT_ARGEE;//GS_WAIT_SETGAME;

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			GameCutStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));

			for (int i = 0; i < PLAY_COUNT; i ++) 
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SAFE_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SAFE_END,0);

			bCloseFlag = GFF_FORCE_FINISH;

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GFF_FORCE_FINISH:		//用户断线离开
		{
			//////////////////////////////////////////////////////////////////////////090514JJa1 添加斷線管理
			//if (m_bGameStation >= GS_SEND_CARD && m_bGameStation < GS_WAIT_NEXT && (bDeskStation>=0&&bDeskStation<PLAY_COUNT))
			//{
			//	//MyMsgBox("FORCE %d", bDeskStation);
			//	m_iFirstCutPeople = bDeskStation;
			//	SetAIMachine(bDeskStation, true);
			//	return true;
			//}
			if (m_iFirstCutPeople != 255)
			{
				bDeskStation = m_iFirstCutPeople;
			}
			
			//////////////////////////////////////////////////////////////////////////
			m_bGameStation = GS_WAIT_ARGEE;

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			GameCutStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));
			CutEnd.bDeskStation = bDeskStation;

			CutEnd.iTurePoint[bDeskStation] = - GetRunPublish();
			CutEnd.iTurePoint[(bDeskStation + 1)%PLAY_COUNT] = GetRunAwayOtherGetPoint((bDeskStation + 1)%PLAY_COUNT,bDeskStation);
			CutEnd.iTurePoint[(bDeskStation + 2)%PLAY_COUNT] = GetRunAwayOtherGetPoint((bDeskStation + 2)%PLAY_COUNT,bDeskStation);
			//CutEnd.iTurePoint[(bDeskStation+3)%4] = GetRunAwayOtherGetPoint((bDeskStation+3)%4,bDeskStation);


			bool temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				temp_cut[i] = (bDeskStation == i && CutEnd.iTurePoint[i] < 0);
			}

			ChangeUserPointint64(CutEnd.iTurePoint, temp_cut);//,CutEnd.iChangeMoney,false);

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// 金币场不扣积分  add by wys 2010-11-1
			if (true == bNotCostPoint)
			{
				memset(CutEnd.iTurePoint,0,sizeof(CutEnd.iTurePoint));
			}

			__super::RecoderGameInfo(CutEnd.iChangeMoney);
			/*DebugPrintf("CutEnd.iTurePoint[i] =[%d][%d][%d]",
				CutEnd.iTurePoint[0],
				CutEnd.iTurePoint[1],
				CutEnd.iTurePoint[2]);
			DebugPrintf("CutEnd.iChangeMoney[i] =[%d][%d][%d][%d][%d][%d][%d][%d]",
				CutEnd.iChangeMoney[0],
				CutEnd.iChangeMoney[1],
				CutEnd.iChangeMoney[2],
				CutEnd.iChangeMoney[3],
				CutEnd.iChangeMoney[4],
				CutEnd.iChangeMoney[5],
				CutEnd.iChangeMoney[6],
				CutEnd.iChangeMoney[7]
				);*/

			for (int i = 0; i < PLAY_COUNT; i ++)
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_CUT_END,0);

			bCloseFlag = GFF_FORCE_FINISH;

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);

			return TRUE;
		}
	case GF_TERMINATE://意外停止游戏
		{
			//设置数据 
			m_bGameStation = GS_WAIT_ARGEE;

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			GameCutStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));
			for (int i = 0; i < PLAY_COUNT; i ++)
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_TERMINATE_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_TERMINATE_END,0);

			bCloseFlag = GFF_FORCE_FINISH;

			ReSetGameState(bCloseFlag);
			__super::GameFinish(0,bCloseFlag);
			return true;
		}
	case GF_AHEAD_END://提前结束
		{
			//设置数据 
			m_bGameStation = GS_WAIT_ARGEE;

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}

			GameCutStruct CutEnd;
			::memset(&CutEnd,0,sizeof(CutEnd));

			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_AHEAD_END,0);
			}
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_AHEAD_END,0);

			bCloseFlag = GFF_FORCE_FINISH;

			ReSetGameState(bCloseFlag);
			__super::GameFinish(0,bCloseFlag);
			return true;
		}
	}

	//重置数据
	ReSetGameState(bCloseFlag);
	__super::GameFinish(bDeskStation,bCloseFlag);

	return true;
}

//玩家逃跑其他玩家得分
int CServerGameDesk::GetRunAwayOtherGetPoint(BYTE bDeskStation,BYTE bRunDeskStation )
{
	return 0;
}

//逃跑扣分
int CServerGameDesk::GetRunPublish()
{
	return m_pDataManage->m_InitData.uRunPublish;
}
//逃跑扣分
int CServerGameDesk::GetRunPublish(BYTE bDeskStation)
{
	return m_pDataManage->m_InitData.uRunPublish;
}

//游戲基礎倍數
int CServerGameDesk::GetRoomMul()
{
	return m_pDataManage->m_InitData.uBasePoint; // 倍数
}

//桌子倍数
int CServerGameDesk::GetDeskBasePoint()
{
	return 1;
	//return GetTableBasePoint();
}
//统计倍数
int CServerGameDesk::GetHumanBasePoint()
{
	return 1;
	int minval = m_pUserInfo[0]->m_UserData.dwPoint;
	for(int i = 1; i < PLAY_COUNT;i ++)
	{
		minval = min(minval,m_pUserInfo[i]->m_UserData.dwPoint);
	}
	return minval;
}

//设置下一个庄家,即下一个发牌位置,叫分位置
BOOL CServerGameDesk::SetNextBanker(BYTE bGameFinishState)
{
	switch(bGameFinishState)
	{
	case GF_NORMAL://正常结束本局胜者下一局优先叫分
		for (int i = 0; i < PLAY_COUNT; i++)
		{
			if(m_iUserCardCount[i] == 0)
			{
				m_iDealPeople = m_iUpGradePeople = i;
				break;
			}
		}
		break;
	case GF_NO_CALL_SCORE://无人叫分
#ifdef TWO
		m_iDealPeople = m_iUpGradePeople =  (m_iUpGradePeople +1)%PLAY_COUNT;
#else
		m_iDealPeople = m_iUpGradePeople =  (m_iUpGradePeople +2)%PLAY_COUNT;
#endif
		break;
	default:
		m_iDealPeople = m_iUpGradePeople = -1;
	}
	return TRUE;
}

//本轮胜者
BYTE CServerGameDesk::GetGameWiner(BOOL &bCut)
{
	int winer = 0;
	for(int i = 1;i < PLAY_COUNT ; i ++)
	{
		if(m_pUserInfo[i] == NULL)
			continue;
		if(m_iWinPoint[i] > m_iWinPoint[winer])
		{
			winer = i;
		}
	}
	//断线玩家,找一个非断线玩家代替
	if(m_pUserInfo[winer]!=NULL&&m_pUserInfo[winer]->m_UserData.bUserState  == USER_CUT_GAME || m_iAIStation[winer])
	{
		bCut = TRUE;
		if(m_iWinPoint[(winer+1)%PLAY_COUNT] > m_iWinPoint[(winer+2)%PLAY_COUNT])
			if(m_pUserInfo[(winer+1)%PLAY_COUNT] != NULL&&m_pUserInfo[(winer+1)%PLAY_COUNT]->m_UserData.bUserState  != USER_CUT_GAME  && !m_iAIStation[(winer+1)%PLAY_COUNT])
				return (winer+1)%PLAY_COUNT;

		if(m_pUserInfo[(winer+2)%PLAY_COUNT] != NULL&&m_pUserInfo[(winer+2)%PLAY_COUNT]->m_UserData.bUserState  != USER_CUT_GAME)
			return (winer+2)%PLAY_COUNT;
	}

	return winer;
}

//获取真实分(每一个玩家真实分
int CServerGameDesk::GetTruePoint(BYTE bDeskStation)
{
	return 0;
}


//判断是否正在游戏
bool CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	if((m_bGameStation >= GS_SEND_CARD && m_bGameStation < GS_WAIT_NEXT))
		return true;
	return false;
}

//判断是否正在游戏
bool CServerGameDesk::IsPlayGameEx(BYTE bDeskStation)
{
	return true;
}

//用户离开游戏桌
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	OutputDebugString("wyslog Server UserLeftDesk");
	//JAdd-20090116
	if (m_bGameStation>=20&&m_bGameStation<23)  //在游戏中，
	{
		//return false;
		return __super::UserLeftDesk(bDeskStation,pUserInfo);
	}
	else
	{
		return __super::UserLeftDesk(bDeskStation,pUserInfo);
	}
	////if(m_bGameStation > GS_WAIT_ARGEE && m_pDataManage->m_InitData.uComType != TY_MATCH_GAME)
	////{
	////	GameFinish(bDeskStation,GF_SAFE);
	////	//		m_bGameStation=GS_WAIT_ARGEE;
	////}
	//return __super::UserLeftDesk(bDeskStation,pUserInfo);
}


//用户设置游戏
BOOL CServerGameDesk::UserSetGame(UserArgeeGame * pGameSet)
{
	return TRUE;
}

//用来改变用户断线条件的函数
bool CServerGameDesk::CanNetCut(BYTE bDeskStation)
{
	return true;
}

//用户请求离开
BOOL CServerGameDesk::UserHaveThing(BYTE bDeskStation, char * szMessage)
{
	// 已经点过退出按钮(一局只能单击一次)
	if (!m_bCanleave[bDeskStation])
		return TRUE;

	if (m_bGameStation < GS_SEND_CARD) 
		return TRUE;

	if (m_iHaveThingPeople != bDeskStation)
	{
		m_iLeaveArgee = 0;
	}

	m_icountleave = 0;
	m_iHaveThingPeople = bDeskStation;
	m_iLeaveArgee|= 1<<bDeskStation;
	m_bCanleave[bDeskStation]=false;

	if (m_iLeaveArgee != 7)
	{
		HaveThingStruct HaveThing;
		HaveThing.pos = bDeskStation;
		::CopyMemory(HaveThing.szMessage,szMessage,60*sizeof(char));

		for (int i = 0; i < PLAY_COUNT; i ++)
			if (i != bDeskStation)
				SendGameData(i,&HaveThing,sizeof(HaveThing),MDM_GM_GAME_NOTIFY,ASS_HAVE_THING,0);
	}
	else 
		GameFinish(255,GF_SAFE);
	return TRUE;
}

//同意用户离开
BOOL CServerGameDesk::ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee)
{
	m_icountleave++;
	if (bArgee) m_iLeaveArgee|= 1<<bDeskStation;
	else 
		m_iLeaveArgee = 0;
	if (m_iLeaveArgee != 7)				//3个人游戏
	{
		LeaveResultStruct Leave;
		Leave.bDeskStation = bDeskStation;
		Leave.bArgeeLeave = bArgee;
		for (int i = 0; i < PLAY_COUNT; i ++) 
			if (i != bDeskStation) 
				SendGameData(i,&Leave,sizeof(Leave),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}
	else
	{
		GameFinish(255,GF_SAFE);
		LeaveResultStruct Leave1;
		Leave1.bDeskStation = m_iHaveThingPeople;
		Leave1.bArgeeLeave = true;
		SendGameData(m_iHaveThingPeople,&Leave1,sizeof(Leave1),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}
	if (m_icountleave>=2)
	{
		m_iLeaveArgee=0;
	}

	return TRUE;
}

//托管设置
bool CServerGameDesk::UserSetAuto(BYTE bDeskStation,bool bAutoCard)
{
	m_bAuto[bDeskStation] = bAutoCard;
	AutoStruct autoset;
	autoset.bAuto = bAutoCard;
	autoset.bDeskStation = bDeskStation;

	for(int i = 0; i < PLAY_COUNT; i ++)
		SendGameData(i,&autoset,sizeof(autoset),MDM_GM_GAME_NOTIFY,ASS_AUTO,0);
	SendWatchData(m_bMaxPeople,&autoset,sizeof(autoset),MDM_GM_GAME_NOTIFY,ASS_AUTO,0);
	return true;
}
///检测用户是否为Vip用户
BOOL CServerGameDesk::UserVipVertify(BYTE bDeskStation) 
{
	if(bDeskStation <0 ||bDeskStation>=PLAY_COUNT)
	{
		return TRUE ; 
	}

	VipDataStruct VipData ; 
	memset(&VipData , 0 , sizeof(VipData));

	VipData.bDeskStation = bDeskStation ; 
	VipData.bVipUser = IsVipUser(bDeskStation) ;

	SendGameData(bDeskStation , &VipData ,sizeof(VipData),MDM_GM_GAME_NOTIFY , ASS_USER_VIP_VERTIFY ,0 );

	return TRUE ;
}

//自动出牌
BOOL CServerGameDesk::UserAutoOutCard(BYTE bDeskStation)
{
	if (bDeskStation >= PLAY_COUNT)
	{
		return FALSE;
	}

	BYTE bCardList[54];
	int iCardCount = 0;
	//if(bDeskStation == m_iFirstOutPeople)   // duanxiaohui alter 20100319
	{
		m_Logic.AutoOutCard(m_iUserCard[bDeskStation],m_iUserCardCount[bDeskStation],
			m_iDeskCard[m_iNowBigPeople],m_iDeskCardCount[m_iNowBigPeople],
			bCardList,iCardCount,bDeskStation == m_iNowBigPeople);
	}
	//else
	//{
	//	iCardCount = 0;
	//}
	return UserOutCard(bDeskStation,bCardList,iCardCount);
}


//发送取消机器人托管
BOOL CServerGameDesk::SetAIMachine(BYTE bDeskStation,BOOL bState)
{
	m_iAIStation[bDeskStation] = bState;

	UseAIStation ai;
	ai.bDeskStation = bDeskStation;
	ai.bState = bState;
	for(int i = 0; i < PLAY_COUNT ;i++)
	{
		if(i != bDeskStation &&m_pUserInfo[i] != NULL)		
			SendGameData(i,&ai,sizeof(ai),MDM_GM_GAME_NOTIFY,ASS_AI_STATION,0);	
	}
	SendWatchData(m_bMaxPeople,&ai,sizeof(ai),MDM_GM_GAME_NOTIFY,ASS_AI_STATION,0);

	return TRUE;
}


//用户断线离开
bool CServerGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	__super::UserNetCut(bDeskStation,  pLostUserInfo);

	UserleftDesk  bagUserleft;
	bagUserleft.bDeskStation = bDeskStation;
	for (int i = 0;i<PLAY_COUNT;i++)
	{
		if (NULL == m_pUserInfo[i])
		{
			continue;
		}
		SendGameData(i,&bagUserleft,sizeof(bagUserleft),MDM_GM_GAME_NOTIFY,ASS_USER_LEFTDESK,0);
	}
	
	return UseAI(bDeskStation);
}


//是否为未出过牌
BYTE CServerGameDesk::GetNoOutCard()
{
	BOOL bOutCard = FALSE;
	//两闲家没有出过牌
	if(m_iUserCardCount[(m_iUpGradePeople + 1) % PLAY_COUNT] == m_iUserCardCount[(m_iUpGradePeople + 2) % PLAY_COUNT]
	&&m_iUserCardCount[(m_iUpGradePeople + 2) % PLAY_COUNT] == 17)
	{
		bOutCard = true;
	}
#ifdef TWO
		if(m_iUserCardCount[(m_iUpGradePeople + 1) % PLAY_COUNT] == 17)
	{
		bOutCard = true;
	}
#endif
	//庄家仅出了第一首牌
	if(m_iUserCardCount[m_iUpGradePeople] == 20 - m_iNtFirstCount)		
	{
		bOutCard = true;
	}
	return bOutCard;
}
//检查机器人是否能双倍下注
BOOL  CServerGameDesk::IsVipUser(BYTE bDeskStation)
{
	//是否非法参数传入
	if (bDeskStation >= PLAY_COUNT||bDeskStation<0)
		return FALSE;

	if (NULL == m_pUserInfo[bDeskStation])
	{
		return FALSE;
	}

	CString stime;
	stime.Format("%d",CTime::GetCurrentTime());
	int curtime=atoi(stime);

	return curtime < m_pUserInfo[bDeskStation]->m_UserData.iVipTime?TRUE:FALSE;
}

///处理锤动画
void CServerGameDesk::HandleChuiAction(BYTE bDeskStation, bool bType)
{
	if(bDeskStation > PLAY_COUNT || m_byUserChui[bDeskStation]!=255 ||	//玩家位置异常 玩家已点选择锤一锤
	   m_pUserInfo[bDeskStation]->m_UserData.i64Money <= m_iHammerMoney)//玩家身上金币不够锤一锤
	{
		return;
	}

	//加锤
	if(bType)
	{
		UpdateUserDB(m_pUserInfo[bDeskStation]->m_UserData.dwUserID, -m_iHammerMoney);	//玩家选取锤一锤时要扣钱

		m_byUserChui[bDeskStation] = 2;
	}
	else	//不加锤
	{
		m_byUserChui[bDeskStation] = 0;
	}

	ChuiStruct s_Chui;
	s_Chui.bIsChui = bType;
	s_Chui.iFee = m_iHammerMoney;

	//发送消息
	for (int i = 0; i < PLAY_COUNT; ++i)
	{
		s_Chui.bDeskStation = bDeskStation;
		SendGameData(i, &s_Chui, sizeof(s_Chui), MDM_GM_GAME_NOTIFY, ASS_CHUI_RESULT, 0);
	}
	SendWatchData(m_bMaxPeople, &s_Chui, sizeof(s_Chui), MDM_GM_GAME_NOTIFY, ASS_CHUI_RESULT, 0);

	int iTemp = 0;
	for(int i = 0; i < PLAY_COUNT; ++i)
	{
		if(255 != m_byUserChui[i])
		{	
			iTemp++;
		}
	}

	if (iTemp >= 3)
	{
		iTemp = 0;
		KillTimer(TIME_CHUI);
		GamePrepare();	
	}
}
