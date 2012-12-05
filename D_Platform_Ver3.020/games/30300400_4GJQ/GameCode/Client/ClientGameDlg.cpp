#include "StdAfx.h"
#include "ClientGameDlg.h"
#include "GameSet.h"
#include ".\clientgamedlg.h"
#include "Platform\bzsound.h"

void Msg(const char *lpszFormat, ...)
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
	OutputDebugString(szMessage);
}

///判断是否为空闲状态
///@param a 返回值
#define IsStation(a); \
if (GetStationParameter()==GS_WAIT_SETGAME || GetStationParameter()==GS_WAIT_ARGEE || GetStationParameter()==GS_WAIT_NEXT) \
{ \
	return a; \
}

/**
 * 设置游戏状态
 */
bool CClientGameDlg::SetGameStation(void * pStationData, UINT uDataSize)
{
	Msg("Test:Data 当前状态 %d  __id %d", GetStationParameter(),GetMeUserInfo()->bDeskStation); 
//	g_bIsWatcher = m_bWatchMode;
	if(m_bWatchMode)
	{
		m_PlayView.m_btContinue.ShowWindow(false);
		//m_PlayView.m_btleave.ShowWindow(false);
		m_PlayView.m_Logic.m_bWatchOther=m_bWatchOther;
		m_PlayView.m_btFinishDiaoDu.ShowWindow(false);
		m_PlayView.m_btLoadBuZhen.ShowWindow(false);
		m_PlayView.m_btSaveBuZhen.ShowWindow(false);
	}
	else
	{
		m_PlayView.m_Logic.m_bWatchOther=false;
	}

	switch (GetStationParameter())
	{
	case GS_WAIT_SETGAME:	//游戏没有开始状态
		{
			if(uDataSize!=sizeof(GameStation_1))
			{
				MessageBox("您需要下载新的客户端","系统提示",0);
				OnCancel();
				return true;
			}
			GameStation_1 * pGameStation=(GameStation_1 *)pStationData;
			if(pGameStation->iMainVersion!=MAIN_VERSION||pGameStation->iLessVersion!=ASS_VERSION)
			{
				MessageBox("您需要下载新的客户端","系统提示",0);
				OnCancel();
				return true;
			}
			uRunPublish = pGameStation->uRunPublish;
			basepoint	= pGameStation->basepoint;
			
			if (!IsQueueGameRoom()) 
			{
				if(!m_bWatchMode)
				{
					m_PlayView.m_btContinue.ShowWindow(true);
					//m_PlayView.m_btleave.ShowWindow(true);
				}
			}
			else
			{
				m_PlayView.m_btContinue.ShowWindow(SW_HIDE);
				KillAllTimer();
				m_PlayView.m_btFinishDiaoDu.ShowWindow (SW_SHOW);
				m_PlayView.m_btLoadBuZhen.ShowWindow (SW_SHOW);
				m_PlayView.m_btSaveBuZhen.ShowWindow (SW_SHOW);

				m_PlayView.m_btFinishDiaoDu.EnableWindow (true);
				m_PlayView.m_btLoadBuZhen.EnableWindow (true);
				m_PlayView.m_btSaveBuZhen.EnableWindow (true);

				m_PlayView.m_Logic.StartBuzhen();
				ResetGameStation(RS_GAME_BEGIN);
			}
			return TRUE;
		}
	case GS_WAIT_ARGEE:	//等待同意状态
		{
			if(uDataSize!=sizeof(GameStation_2))
			{
				MessageBox("您需要下载新的客户端","系统提示",0);
				OnCancel();
				return true;
			}
			GameStation_2 * pGameStation=(GameStation_2 *)pStationData;
			if(pGameStation->iMainVersion!=MAIN_VERSION||pGameStation->iLessVersion!=ASS_VERSION)
			{
				MessageBox("您需要下载新的客户端","系统提示",0);
				OnCancel();
				return true;
			}
			
			uRunPublish = pGameStation->uRunPublish;
			basepoint	= pGameStation->basepoint;
			ResetGameStation(RS_GAME_BEGIN);
			m_PlayView.m_Logic.Init();
			m_iLessCount=pGameStation->iPlayCount;
			
			for(int i=0;i<MAX_I;i++)
			{
				for(int j=0;j<MAX_J;j++)
				{
					int ii=-1,jj=-1;
					if(m_pGameInfo->uDeskPeople == 4)
						m_PlayView.m_Logic.ToMyCord (2,ii,jj,i,j);
					else
						m_PlayView.m_Logic.ToMyCord (0,ii,jj,i,j);
					if(ii < 0 || jj < 0)continue;
					m_PlayView.m_Logic.mBoard[ii][jj] = pGameStation->mBoard[i][j];
				}
			}

			if (!IsQueueGameRoom()) 
			{
				if(!m_bWatchMode)
				{
					m_PlayView.m_btContinue.ShowWindow(true);
					SetGameTimer(GetMeUserInfo()->bDeskStation,20,ID_BEGIN_TIME);
					//m_PlayView.m_btleave.ShowWindow(true);
				}
			}
			else
			{
				KillAllTimer();
				m_PlayView.m_btFinishDiaoDu.ShowWindow (SW_SHOW);
				m_PlayView.m_btLoadBuZhen.ShowWindow (SW_SHOW);
				m_PlayView.m_btSaveBuZhen.ShowWindow (SW_SHOW);

				m_PlayView.m_btFinishDiaoDu.EnableWindow (true);
				m_PlayView.m_btLoadBuZhen.EnableWindow (true);
				m_PlayView.m_btSaveBuZhen.EnableWindow (true);

				m_PlayView.m_Logic.StartBuzhen();
			}


			m_PlayView.UpdateViewFace(NULL);
			/*

			CString strResult = "this is the result";//5.18 2009
			GameResult gameResult;
			for (int i=0; i<PLAY_COUNT; i++)
			{
			gameResult.iMoney[i] = 5;
			gameResult.iWardPoint[i] = 5;
			strcpy(gameResult.name[i], "nickname");
			}
			m_PlayView.m_Result.ShowMsg(TEXT(""),20,true,gameResult, Glb().m_nPowerOfGold);
			//m_PlayView.m_msgbox.ShowMsg(TEXT("\n\n\n\n\n您已覆灭!"),10, false, gameResult);

			*/
			return TRUE;
		}
	
	case GS_BUZHEN:	//发牌状态
	case GS_PLAY_GAME:	//游戏进行中
		{
			//清理是否是新进桌子
			m_PlayView.m_bFirstGame = false;

			int st=0;
			if(m_pGameInfo->uDeskPeople == 4)
				st=2;
			m_PlayView.m_Logic.Init();
			m_PlayView.m_Logic.m_iPlayerCount=GetPlayerCount();
			m_PlayView.UpdateViewFace(NULL);
			GameStation_3 * pGameStation=(GameStation_3 *)pStationData;

			m_iLessCount=pGameStation->iPlayCount;
			uRunPublish = pGameStation->uRunPublish;
			basepoint	= pGameStation->basepoint;
			m_PlayView.m_btThing.EnableWindow(!m_bWatchMode);
			m_PlayView.m_btStop.EnableWindow(!m_bWatchMode);

			m_PlayView.m_Logic.m_iNowOutPeople = pGameStation->m_iNowOutPeople;	

			m_PlayView.m_Logic.ToMyCord (st,
				m_PlayView.m_Logic.m_iStartI,m_PlayView.m_Logic.m_iStartJ,
				 pGameStation->m_iStartI,pGameStation->m_iStartJ
				);

			m_PlayView.m_Logic.ToMyCord (st,
				m_PlayView.m_Logic.m_iEndI,m_PlayView.m_Logic.m_iEndJ,
				 pGameStation->m_iEndI,pGameStation->m_iEndJ
				);

			//m_PlayView.m_Logic.m_iStartI = pGameStation->m_iStartI;
			//m_PlayView.m_Logic.m_iStartJ = pGameStation->m_iStartJ;
			//m_PlayView.m_Logic.m_iEndI = pGameStation->m_iEndI;
			//m_PlayView.m_Logic.m_iEndJ = pGameStation->m_iEndJ;

			for(int i=0;i<MAX_I;i++)
		      for(int j=0;j<MAX_J;j++)
			  {
				  int ii=-1,jj=-1;
				  m_PlayView.m_Logic.ToMyCord (st,ii,jj,i,j);
				  if(ii < 0 || jj < 0)continue;
	              m_PlayView.m_Logic.mBoard[ii][jj] = pGameStation->mBoard[i][j];
			  }
			  if(m_PlayView.m_Logic.m_iNowOutPeople==GetMeUserInfo()->bDeskStation)
				  m_PlayView.m_Logic.m_bICanMove=true;
			if (m_PlayView.m_Logic.m_iNowOutPeople!=-1) 
			{
				SetGameTimer(m_PlayView.m_Logic.m_iNowOutPeople,pGameStation->iTimerCount - 3,ID_OUT_CARD);
				//SetGameTimer(m_PlayView.m_Logic.m_iNowOutPeople,m_iLessCount,ID_OUT_CARD);

			}
				

			m_PlayView.UpdateViewFace(NULL);
			return TRUE;
		}
	case GS_WAIT_NEXT:		//等待下一盘开始
		{
			//清理是否是新进桌子
			m_PlayView.m_bFirstGame = false;

			//g_bIsWatcher=m_bWatchMode;
			GameStation_5 * pGameStation=(GameStation_5 *)pStationData;

			//设置数据
			m_iLessCount=pGameStation->iPlayCount;
			uRunPublish = pGameStation->uRunPublish;
			basepoint	= pGameStation->basepoint;
			if (!IsQueueGameRoom()) 
			{
				//显示开始按钮 
				if (GetMeUserInfo()->bUserState!=USER_ARGEE)
				{
					if (m_bWatchMode==false)
					{
						m_PlayView.m_btContinue.ShowWindow(SW_SHOW);
						//m_PlayView.m_btleave.ShowWindow(true);
						m_PlayView.m_btContinue.SetFocus();
					}
					SetGameTimer(GetMeUserInfo()->bDeskStation,20,ID_BEGIN_TIME);
				}
			}
			else
			{
				KillAllTimer();
				m_PlayView.m_btFinishDiaoDu.ShowWindow (SW_SHOW);
				m_PlayView.m_btLoadBuZhen.ShowWindow (SW_SHOW);
				m_PlayView.m_btSaveBuZhen.ShowWindow (SW_SHOW);

				m_PlayView.m_btFinishDiaoDu.EnableWindow (true);
				m_PlayView.m_btLoadBuZhen.EnableWindow (true);
				m_PlayView.m_btSaveBuZhen.EnableWindow (true);

				m_PlayView.m_Logic.StartBuzhen();
			}

			
			return TRUE;
		}
	}


	return false;
}

/**
 * 游戏结束
 */
bool CClientGameDlg::H081_UserContinueEnd(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	if (uDataSize!=sizeof(GameEndStruct)) 
		return FALSE;

	IsStation(true);
	GameEndStruct * pGameEnd=(GameEndStruct *)pNetData;
	KillGameTimer(0);
	CString stime;//*shingo*
	stime.Format("%d",CTime::GetCurrentTime());
	int curtime=atoi(stime);

    GameResult  gameResult;
	if(pGameEnd->iTurePoint[0]==0)
	{
		if(m_PlayView.m_bRightPower)
		{
			TCHAR path[MAX_PATH] = {0};
			wsprintf(path,TEXT("sound\\he.mp3"));
			m_playsound2.PlayMusic(m_hWnd,path,1);
		}
	}

	//在聊天框里显示成绩
	CString str="\n";
	if(GetPlayerCount()==2)
		str+="\n";

	str+="本局游戏结果：\n";
	str+="－－－－－－- - - - - -";
	m_MessageHandle.InsertNormalMessage(str.GetBuffer(MAX_PATH));

	str = "";
	BYTE iDoublePointEffect = 0;
	__int64 nMoneyTemp = 1;
	for(int i=0; i<Glb().m_nPowerOfGold; i++)
	{
		nMoneyTemp*=10;
	}

	
	CString s = "..\\";// CBcfFile::GetAppPath ();/////本地路径	

#ifdef	VIDEO
	CBcfFile f( "30300405.bcf");
#else
	CBcfFile f( "30300400.bcf");
#endif	

	CString key=TEXT("config");	

	CString sec = _T("");

	CString strtemp;
	
	for (int i=0;i<4&&i<m_pGameInfo->uDeskPeople;i++)
	{		
		if (m_pUserInfo[i]!=NULL)
		{

			//if(m_pUserInfo[i]->GameUserInfo.iDoublePointTime>curtime && pGameEnd->iTurePoint[i]>0)
			//20081125 双倍积分卡效果
			iDoublePointEffect = (1<<i);
			if((iDoublePointEffect & pGameEnd->iDoublePointEffect)
				&& pGameEnd->iTurePoint[i] >0)
			{
				pGameEnd->iTurePoint[i]*=2;
				sec.Format("ResultTipDouble%d", m_pGameInfo->uComType);
				str.Format(f.GetKeyVal(key, sec, ""),
					m_pUserInfo[i]->GameUserInfo.nickName,pGameEnd->iTurePoint[i]);

				if (m_pGameInfo->uComType != 1)
				{
					strtemp.Format("%I64d",nMoneyTemp*pGameEnd->iChangeMoney[i]);
					str+=strtemp;
				}				

//#ifdef TWENTY
//				str.Format("%s%s 得分 %d（双倍积分卡效果） 铜板%I64d\n",str.GetBuffer(), m_pUserInfo[i]->GameUserInfo.nickName, \
//					pGameEnd->iTurePoint[i], nMoneyTemp*pGameEnd->iChangeMoney[i]);
//#else
//				if(GetComType()!=TY_MONEY_GAME)
//					str.Format("%s%s 得分 %d（双倍积分卡效果）\n",str.GetBuffer(),m_pUserInfo[i]->GameUserInfo.nickName, \
//					pGameEnd->iTurePoint[i]);
//				else
//					str.Format("%s%s 得分 %d（双倍积分卡效果） 金币%I64d\n",str.GetBuffer(), m_pUserInfo[i]->GameUserInfo.nickName, \
//					pGameEnd->iTurePoint[i], nMoneyTemp*pGameEnd->iChangeMoney[i]);
//#endif
			}
			else
			{				
				sec.Format("ResultTip%d", m_pGameInfo->uComType);
				str.Format(f.GetKeyVal(key, sec, ""),
					m_pUserInfo[i]->GameUserInfo.nickName,pGameEnd->iTurePoint[i]);

				if (m_pGameInfo->uComType != 1)
				{
					strtemp.Format("%I64d",nMoneyTemp*pGameEnd->iChangeMoney[i]);
					str+=strtemp;
				}			

//#ifdef TWENTY
//				str.Format("%s%s  得分 %d  铜板%I64d\n",str.GetBuffer(),m_pUserInfo[i]->GameUserInfo.nickName, \
//					pGameEnd->iTurePoint[i], nMoneyTemp*pGameEnd->iChangeMoney[i]);
//#else
//				if(GetComType()!=TY_MONEY_GAME)
//				{
//					str.Format("%s%s  得分 %d\n",str.GetBuffer(), m_pUserInfo[i]->GameUserInfo.nickName, pGameEnd->iTurePoint[i]);
//				}
//				else
//				{
//					str.Format("%s%s  得分 %d  金币%I64d\n",str.GetBuffer(),m_pUserInfo[i]->GameUserInfo.nickName, \
//						pGameEnd->iTurePoint[i], nMoneyTemp*pGameEnd->iChangeMoney[i]);
//				}
//#endif
			}
	
			m_MessageHandle.InsertNormalMessage(str.GetBuffer(MAX_PATH));
			//设置结束显示信息
			_stprintf_s(gameResult.name[i],sizeof(gameResult.name[i]), _T("%s"),m_pUserInfo[i]->GameUserInfo.nickName);
			gameResult.iMoney[i]=pGameEnd->iChangeMoney[i];
			gameResult.iWardPoint[i]=pGameEnd->iTurePoint[i];

			m_PlayView.m_showcoredlg.SetUserScore(ViewStation(i),pGameEnd->iTurePoint[i],pGameEnd->iChangeMoney[i]);
			
		}
	}	
	m_MessageHandle.InsertNormalMessage(str.GetBuffer(MAX_PATH));//游戏结果
	str="－－－－－－- - - - - -\n";
	m_MessageHandle.InsertNormalMessage(str.GetBuffer(MAX_PATH));//游戏结果

	m_PlayView.m_Result.ShowMsg(TEXT(""), 20, /*true*/false, gameResult, Glb().m_nPowerOfGold);

	/*
	m_MessageHandle.InsertNormalMessage("本局游戏结果：");
	m_MessageHandle.InsertNormalMessage("－－－－－－");
	CString str;
	for (int i=0;i<4&&i<m_pGameInfo->uDeskPeople;i++)
	{
	if (m_pUserInfo[i]!=NULL)
	{
	if(GetComType()!=TY_MONEY_GAME)
		str.Format("%s 得分 %d",m_pUserInfo[i]->GameUserInfo.szName,pGameEnd->iTurePoint[i]);
	else
		str.Format("%s 得分 %d 金币 %d",m_pUserInfo[i]->GameUserInfo.szName,pGameEnd->iTurePoint[i],pGameEnd->iChangeMoney[i]);
	m_MessageHandle.InsertNormalMessage(str.GetBuffer(MAX_PATH));
	}
	}
	m_MessageHandle.InsertNormalMessage("－－－－－－");
	*/
	if (m_bWatchMode==FALSE)
	{
		m_PlayView.m_btContinue.ShowWindow(SW_SHOW);
		//m_PlayView.m_btleave.ShowWindow(true);
		m_PlayView.m_btContinue.SetFocus();
	}
	m_PlayView.m_btThing.EnableWindow(SW_HIDE);			///< 有事要走
	m_PlayView.m_btStop.EnableWindow(SW_HIDE);				///< 停止本局
	SetGameTimer(GetMeUserInfo()->bDeskStation,20,ID_BEGIN_TIME);

	//设置数据
	if(m_pGameInfo->bEnableSound)
		PlaySound(TEXT("GAME_OVER"),GetModuleHandle(CLIENT_DLL_NAME),SND_RESOURCE|SND_NOSTOP|SND_ASYNC|SND_NODEFAULT|SND_NOWAIT);
	SetStationParameter(GS_WAIT_NEXT);
	ResetGameStation(RS_GAME_END);
	return TRUE;

}

/**
 * 定时器消息
 * @param bDeskStation 玩家ID
 * @param uTimeID 时间ID
 * @param uTimeCount 计时器值
 */
bool CClientGameDlg::OnGameTimer(BYTE bDeskStation, UINT uTimeID, UINT uTimeCount)
{
	switch (uTimeID)
	{
	case ID_BEGIN_TIME:	//继续游戏定时器
		{
			if (uTimeCount<=1)
			{
				//时间到了
				if (m_iAfterWaitAction == 1)
				{
					OnHitBegin(0,0);
				}
				else
				{
					SendMessage(WM_CLOSE,0,0);
				}
				
				//SetStationParameter(GS_BUZHEN);
				return true;
			}
			if (uTimeCount<=10) 
			{
				if(m_pGameInfo->bEnableSound)
				{
					//PlaySound(TEXT("WARNING"),GetModuleHandle(CLIENT_DLL_NAME),SND_RESOURCE|SND_NOSTOP|SND_ASYNC|SND_NODEFAULT|SND_NOWAIT);
					TCHAR path[MAX_PATH] = {0};
					wsprintf(path,TEXT("sound\\timeout.mp3"));
					m_playsound2.PlayMusic(m_hWnd,path);
				}
			}

			return true;
		}
	case ID_OUT_CARD:	//出牌
		{
			int iViewStation=ViewStation(bDeskStation);
			if (uTimeCount<=1)	//时间到了
			{
				//判断超时
				if((m_PlayView.m_Logic.m_iNowOutPeople==GetMeUserInfo()->bDeskStation) && (m_bWatchMode==FALSE))
					m_bTimeOutCount++;
				if (m_bTimeOutCount>=5 && (m_PlayView.m_Logic.m_iNowOutPeople==GetMeUserInfo()->bDeskStation) && (m_bWatchMode==FALSE))
				{
					KillGameTimer(0);
					SendGameData(MDM_GM_GAME_FRAME,ASS_GM_FORCE_QUIT,0);
					SendGameData(MDM_GR_USER_ACTION,ASS_GR_USER_UP,0);
					PostMessage(WM_CLOSE,0,0);
					AFCMessageBox(TEXT("超时次数太多，游戏结束！"),m_pGameInfo->szGameName,AFC_CONFIRM); //,this);
					return false;
				}
				else if(m_PlayView.m_Logic.m_iNowOutPeople==GetMeUserInfo()->bDeskStation && !m_bWatchMode)
				{
					CString str;
					str.Format("请注意，您已经超时 %d 次了，超时五次会当做逃跑处理。",m_bTimeOutCount);
					m_MessageHandle.InsertNormalMessage(str.GetBuffer());
					//
					m_PlayView.m_btStop.EnableWindow(FALSE);//5.18 2009
					m_PlayView.m_btThing.EnableWindow(FALSE);
					m_PlayView.m_Logic.SetStartEndXY();
				}

				if ((m_PlayView.m_Logic.m_iNowOutPeople==GetMeUserInfo()->bDeskStation)&&(m_bWatchMode==FALSE))
				{
					tagNextStep m;
		             m.station=m_PlayView.m_Logic.m_iNowOutPeople;
					 SendGameData(&m,sizeof(m),MDM_GM_GAME_NOTIFY,ASS_PASS,0);
					//m_PlayView.m_Logic.AutoOutCard();
				}
				return true;
			}
			if ((uTimeCount<=6)&&(m_bWatchMode==FALSE)&&(iViewStation==2)) 
			{
				if(m_pGameInfo->bEnableSound)
					PlaySound(TEXT("WARNING"),GetModuleHandle(CLIENT_DLL_NAME),SND_RESOURCE|SND_NOSTOP|SND_ASYNC|SND_NODEFAULT|SND_NOWAIT);
			}
			return true;
		}
	}
	return true;
}

bool CClientGameDlg::H041_UserLose(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	KillTimer(ID_FLASH_CHESS);
	tagNextStep* p= (tagNextStep*)pNetData;
	m_PlayView.m_Logic.ClearColorAllQiZi(m_PlayView.m_Logic.GetColorFromStation (p->station) );
	m_PlayView.m_Logic.ClearColorAllQiZi(m_PlayView.m_Logic.GetColorFromStation (p->station2) );
	m_PlayView.UpdateViewFace(NULL);

	GameResult gameResult;
	if(p->station == GetMeUserInfo()->bDeskStation&&!m_bWatchMode)
		m_PlayView.m_msgbox.ShowMsg(TEXT("\n\n\n\n\n您已覆灭!"),10, false, gameResult);
	if(p->station2 == GetMeUserInfo()->bDeskStation&&!m_bWatchMode)
		m_PlayView.m_msgbox.ShowMsg(TEXT("\n\n\n\n\n您已覆灭!"),10,false, gameResult);
	return true;
}

/**
 * 用户出牌
 * @param pNetData 网络数据包
 * @param uDataSize 数据包大小
 */
bool CClientGameDlg::H040_UserOutCard(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	tagMoveResult *p=(tagMoveResult *)pNetData;

	if(p->station==GetMeUserInfo()->bDeskStation&&p->loseColor>=0)
	{
		if(p->FromJq==JQ_TYPE_NAME_JQ)
		{//如果吃的是军旗,则这个子,以后都不能走了.
			m_PlayView.m_Logic.m_iJingQiI=p->m_iEndI;
			m_PlayView.m_Logic.m_iJingQiJ=p->m_iEndJ;
		}
	}

	if(m_PlayView.m_bRightPower)
	{
		int mystation=GetMeUserInfo()->bDeskStation;
		int s=m_PlayView.m_Logic.GetJq(p->station,p->m_iStartI,p->m_iStartJ);
		int e=m_PlayView.m_Logic.GetJq(p->station,p->m_iEndI,p->m_iEndJ);
		int sn,en;
		sn=GET_A_JQ_NAME(s);
		en=GET_A_JQ_NAME(e);
		int ton=GET_A_JQ_NAME(p->ToJq);
		int fromn=GET_A_JQ_NAME(p->FromJq);
		//TCHAR sz[100];
		//wsprintf(sz,"ms:%d ton%d sn%d en%d",GetMeUserInfo()->bDeskStation,ton,sn,en);
		//MessageBox(sz);

		TCHAR path[MAX_PATH] = {0};
		if(p->FromJq==JQ_TYPE_NAME_JQ)
		{
			int losestation=m_PlayView.m_Logic.GetStationFromColor(p->loseColor);
			
			if((mystation==losestation || (mystation+2)%4==losestation)
				&&p->loseColor2==-1)
			{
				wsprintf(path,TEXT("sound\\shu.mp3"));
				m_playsound2.PlayMusic(m_hWnd,path,1);
			}
			else
			{
				wsprintf(path,TEXT("sound\\win.mp3"));
				m_playsound2.PlayMusic(m_hWnd,path,1);
			}
		}
		else
		{
			if(en==JQ_TYPE_NAME_NONE)
			{//走棋
				wsprintf(path,TEXT("sound\\zuoqi.mp3"));
				m_playsound2.PlayMusic(m_hWnd,path,1);
			}
			else
			{
				if(JQ_TYPE_NAME_DL==en&&sn==JQ_TYPE_NAME_GB)
				{
					//挖地雷音
					wsprintf(path,TEXT("sound\\walei.mp3"));
					m_playsound2.PlayMusic(m_hWnd,path,1);
				}
				else if(JQ_TYPE_NAME_ZD==sn||JQ_TYPE_NAME_ZD==en)
				{
					wsprintf(path,TEXT("sound\\zadan.mp3"));
					m_playsound2.PlayMusic(m_hWnd,path,1);
				}
				else if(JQ_TYPE_NAME_NONE==ton)
				{
					wsprintf(path,TEXT("sound\\etoe.mp3"));
					m_playsound2.PlayMusic(m_hWnd,path,1);
				}
				else if(ton==en)
				{
					wsprintf(path,TEXT("sound\\stob.mp3"));
					m_playsound2.PlayMusic(m_hWnd,path,1);
				}
				else if(ton==sn)
				{
					wsprintf(path,TEXT("sound\\btos.mp3"));
					m_playsound2.PlayMusic(m_hWnd,path,1);
				}
			}
		}
	}

	if(p->FromJq==JQ_TYPE_NAME_JQ)
		p->FromJq=JQ_TYPE_NONE;

	if(p->m_iStartI!=-1)
	{
		m_MResultPath.Init();
		m_MResultPath.PathMsg = *p;
		m_PlayView.m_Logic.InitPath();

		// 寻找第一个位置
		for (int j=0; j<MAX_I; j++)
		{
			for (int k=0; k<MAX_J; k++)
			{
				// 因为是第一个位置
				if (255!=m_MResultPath.PathMsg.cPath[j][k] && 0==abs(j-p->m_iStartI) && 0==abs(k-p->m_iStartJ))
				{
					m_MResultPath.CurPath.x = j;
					m_MResultPath.CurPath.y = k;
					m_MResultPath.bContinueInsertPos[j][k] = TRUE;

					j = MAX_I;
					k = MAX_J;
					break;
				}
			}
		}

		m_MResultPath.iCurStep = 1;
		SetTimer(ID_SHOW_PATH, 1*p->iStep, NULL);
	}

	CString AllResult,TmpResult;
	AllResult.Format("Test:DDDD %d",p->iStep);
	for (int i=0;i<17; i++)
		for (int j=0;j<17; j++)
			if (m_MResultPath.PathMsg.cPath[i][j]!=255)
			{
				TmpResult.Format("  (%d,%d)",i,j);
				AllResult+=TmpResult;
			}
			Msg(AllResult);

		
	m_PlayView.m_Logic.m_iNowOutPeople= p->nextstation;

	if ((m_bWatchMode==FALSE)&&(GetMeUserInfo()->bDeskStation==m_PlayView.m_Logic.m_iNowOutPeople))
	{
		/*if(!m_PlayView.m_Logic.bCanIMove())
		{//无子可以走了
			tagMove  m;
			m.m_iStartI=-1;
			m.m_iStartJ=-1;
			m.m_iEndI=-1;
			m.m_iEndJ=-1;
			SendGameData(&m,sizeof(m),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);	
			return true;
		}*/
		
		//wushuqun 2008.8.20
		//修改“有事离开” "提前结束“按钮不能用

		m_PlayView.m_btStop.EnableWindow(true);
		m_PlayView.m_btThing.EnableWindow(true);
	    m_PlayView.m_Logic.m_bICanMove=true;
		KillTimer(ID_FLASH_CHESS);
	}
	else
	{
		//修改“有事离开” "提前结束“按钮不能用
		m_PlayView.m_btStop.EnableWindow(FALSE);
		m_PlayView.m_btThing.EnableWindow(false);
	}
	if (m_PlayView.m_Logic.m_iNowOutPeople!=-1) 
			 SetGameTimer(m_PlayView.m_Logic.m_iNowOutPeople,m_iLessCount,ID_OUT_CARD);
	else
		KillAllTimer();
	
	m_PlayView.UpdateViewFace(NULL);
	return TRUE;
}

/**
 * 开始升级游戏
 * @param pNetData 网络数据包
 * @param uDataSize 数据包大小
 */
bool CClientGameDlg::H030_NextStep(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	if(GS_BUZHEN==GetStationParameter()&&m_pGameInfo->bEnableSound)
	{
		TCHAR path[MAX_PATH] = {0};
		wsprintf(path,TEXT("sound\\finishbuzhen.mp3"));
		m_playsound2.PlayMusic(m_hWnd,path,1);
		wsprintf(path,TEXT("sound\\backsound.mp3"));
		m_playsound.PlayMusic(m_hWnd,path);
	}
	SetStationParameter(GS_PLAY_GAME);

	tagNextStep *s =(tagNextStep *)pNetData;

	m_PlayView.m_Logic.m_iNowOutPeople= s->station;
	if ((m_bWatchMode==FALSE)&&(GetMeUserInfo()->bDeskStation==m_PlayView.m_Logic.m_iNowOutPeople))
	{
		//修改“有事离开” "提前结束“按钮不能用
        //wushuqun 2008.8.20
		m_PlayView.m_btStop.EnableWindow(true);
		m_PlayView.m_btThing.EnableWindow(true);

	    m_PlayView.m_Logic.m_bICanMove=true;		
	}
	if (m_PlayView.m_Logic.m_iNowOutPeople!=-1) 
	{

		SetGameTimer(m_PlayView.m_Logic.m_iNowOutPeople,m_iLessCount,ID_OUT_CARD);
	}

	m_PlayView.UpdateViewFace(NULL);

	return TRUE;
}

/**
 * 同意用户离开
 * @param pNetData 网络数据包
 * @param uDataSize 数据包大小
 */
bool CClientGameDlg::H0011_UserBuZhen(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	tagBuZhen * bz=(tagBuZhen *)pNetData;

	m_PlayView.m_Logic.CopyOtherBuZhen (*bz);

	m_PlayView.UpdateViewFace(NULL);
	return true;
}

int CClientGameDlg::GetPlayerCount()
{
	int count=0;
	for(int i=0;i<4;i++)
	{
		if(m_pUserInfo[i])
			count++;
	}
	return count;
}

/**
 * 游戏开始
 * @param pNetData 网络数据包
 * @param uDataSize 数据包大小
 */
bool CClientGameDlg::H010_GameBegin(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	m_bTimeOutCount=0;
	//m_PlayView.Init();
	if (uDataSize!=sizeof(BeginGameStruct)) return FALSE;
	BeginGameStruct * pBegin=(BeginGameStruct *)pNetData;
	m_bTimeOutCount=0;
	SetStationParameter(GS_BUZHEN);
	m_PlayView.m_Logic.m_iPlayerCount=GetPlayerCount();
	if(m_PlayView.m_Logic.bFinishBuzhen())
		return true;

	for(int i = 0; i < PLAY_COUNT; i ++)
	{
		if(m_pUserInfo[i] == NULL)
			continue;
		m_pUserInfo[i]->GameUserInfo.bUserState = USER_PLAY_GAME;
	}

	if(!IsWatcher( ))
	{
		if(m_pGameInfo->bEnableSound)
		{
			TCHAR path[MAX_PATH] = {0};
			wsprintf(path,TEXT("sound\\buzhen.mp3"));
			m_playsound.PlayMusic(m_hWnd,path);
		}

		m_PlayView.m_Logic.m_bICanMove = true;
		m_PlayView.m_btFinishDiaoDu.ShowWindow (SW_SHOW);
		m_PlayView.m_btLoadBuZhen.ShowWindow (SW_SHOW);
		m_PlayView.m_btSaveBuZhen.ShowWindow (SW_SHOW);

		m_PlayView.m_btFinishDiaoDu.EnableWindow (true);
		m_PlayView.m_btLoadBuZhen.EnableWindow (true);
		m_PlayView.m_btSaveBuZhen.EnableWindow (true);

	}
	else
	{
		m_PlayView.m_Logic.m_bICanMove = false;
		m_PlayView.m_btFinishDiaoDu.ShowWindow (SW_HIDE);
		m_PlayView.m_btLoadBuZhen.ShowWindow (SW_HIDE);
		m_PlayView.m_btSaveBuZhen.ShowWindow (SW_HIDE);
	}

	m_PlayView.m_GameNoteView.SetMessage(NULL);
	if(!IsWatcher( ))
	{
		m_PlayView.m_btStop.EnableWindow(FALSE);//5.18 2009
		m_PlayView.m_btThing.EnableWindow(FALSE);
	}
	if (m_bWatchMode==TRUE) 
	{
		KillAllTimer();
		//ResetGameStation(RS_GAME_BEGIN);
	}
	else
	{
		/*m_PlayView.m_btStop.EnableWindow(true);
		m_PlayView.m_btThing.EnableWindow(true);*/
		
	}

	KillAllTimer();
	m_PlayView.KillCheckTimer ();
	if(!IsWatcher( ))
		m_PlayView.SetCheckTimer(90 * 1000);
	m_PlayView.UpdateViewFace(NULL);
	return TRUE;
}

/**
 * 清除所有定时器
 */
void CClientGameDlg::KillAllTimer()
{
	memset(m_PlayView.m_uTime,0,sizeof(m_PlayView.m_uTime));
	KillGameTimer(ID_BEGIN_TIME);
	KillGameTimer(ID_OUT_CARD);
	KillTimer(ID_FLASH_CHESS);
	
	return;
}

bool CClientGameDlg::H000_UserSetGameJu(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
//	g_bIsWatcher = m_bWatchMode;
	if (uDataSize!=sizeof(UserArgeeGame)) return FALSE;
	SetStationParameter(GS_WAIT_ARGEE);
	UserArgeeGame * pGameSet=(UserArgeeGame *)pNetData;
				
	//设置数据
	m_iLessCount=pGameSet->iPlayCount;
//	m_iPalyCardCount=pGameSet->iCardCount;

	if ((m_bWatchMode==FALSE)&&(GetMeUserInfo()->bDeskStation!=0))
	{
		m_PlayView.m_GameNoteView.SetMessage(NULL);
		//m_PlayView.m_GameInfo.SetGameSetInfo(1,1,1,1);
		m_PlayView.m_GameInfo.SetGameSetInfo(pGameSet->iCardCount,pGameSet->iPlayCount,
							3,5);
	}
	else m_PlayView.m_GameNoteView.SetMessage(TEXT("正在等待其他玩家开始游戏"));
	return TRUE;
}

int GetStationParameter()
{
	if(!g_pCClientGameDlg)return -1;


    return g_pCClientGameDlg->GetStationParameter();
}

bool  IsWatcher( )
{
	return g_pCClientGameDlg->IsWatcher( );
}

int  GetStation( int viewStation)
{//绘画界面函数   m_rcMjDesk
	for (int i=0;i<4;i++)
	{
		if(g_pCClientGameDlg->ViewStation(i) == viewStation)return i;
	}
	return -1;
}

/**
 * 游戏消息处理函数
 */
bool CClientGameDlg::HandleGameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	Msg("Test:Data 当前消息 %d  __id %d", pNetHead->bAssistantID,GetMeUserInfo()->bDeskStation);

	if (pNetHead->bMainID==MDM_GM_GAME_NOTIFY)
	{
		switch (pNetHead->bAssistantID)
		{
		case ASS_LOSE:
			{
				return H041_UserLose(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		case ASS_BUZHEN:
			{
				return H0011_UserBuZhen(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}		
		case ASS_CONTINUE_END:	//游戏结束
		case ASS_NO_CONTINUE_END:
			{
				return H081_UserContinueEnd(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		case ASS_HAVE_THING:	//用户请求离开
			{
				return H082_UserHaveThing(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		case ASS_LEFT_RESULT:	//请求离开结果 
			{
				return H083_UserHaveThingResult(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		case ASS_MESSAGE:
			{
				if (uDataSize!=sizeof(MessageStruct))
				{
					
					return FALSE;
				}
				MessageStruct *pMessage=(MessageStruct*)pNetData;
				m_MessageHandle.InsertSystemMessage(pMessage->Message);
				return true;
			}
		case ASS_STOP_THING://对家请求提前结束
			{
				return H084_DuiJiaHaveThing(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		case ASS_AGREE_STOP://请求提前结束结果
			{
				return H085_DuiJiaHaveThingResult(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}

		case ASS_NEXT_STEP://ASS_GAME_PLAY:		//开始升级游戏
			{
				return H030_NextStep(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		case ASS_OUT_CARD:		//用户出牌
			{
				return H040_UserOutCard(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}		
		
		case ASS_GAME_POINT:	//用户分数
			{
//				return H043_UserFen(pNetHead, pNetData,  uDataSize, pClientSocket);
			}		
		case ASS_SALE_END:	//游戏安全结束
		case ASS_CUT_END:	//用户强行离开
			{
				return H080_UserLeftOrGameAnQuanFinish(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
			
		case ASS_UG_USER_SET:		//用户设置牌局
			{
				return H000_UserSetGameJu(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		case ASS_BEGIN_UPGRADE:		//游戏开始
			{
				m_PlayView.m_Result.ShowWindow(SW_HIDE);
				 return H010_GameBegin(pNetHead, pNetData,  uDataSize/*, pClientSocket*/);
			}
		

		}
	}
	
	return __super::HandleGameMessage(pNetHead,pNetData,uDataSize/*,pClientSocket*/);
}

/**
 * 游戏安全结束,用户强行离开
 */
bool CClientGameDlg::H080_UserLeftOrGameAnQuanFinish(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
    if (uDataSize!=sizeof(GameCutStruct)) 
		return FALSE;

	IsStation(true);
	GameCutStruct * pGameEnd=(GameCutStruct *)pNetData;
	KillGameTimer(0);

	if(pGameEnd->bDeskStation != GetMeUserInfo()->bDeskStation&&m_pUserInfo[pGameEnd->bDeskStation]!=NULL)
	{
		//显示信息
		TCHAR szMessage[100];
		if (pNetHead->bAssistantID==ASS_CUT_END)
			wsprintf(szMessage,TEXT("由于〖 %s 〗强行退出，游戏结束。"),m_pUserInfo[pGameEnd->bDeskStation]->GameUserInfo.nickName);
		else 
			wsprintf(szMessage,TEXT("由于〖 %s 〗离开，游戏结束。"),m_pUserInfo[pGameEnd->bDeskStation]->GameUserInfo.nickName);
		//	m_PlayView.m_StationView.CleanAllInfo(TRUE);
		m_MessageHandle.InsertNormalMessage(szMessage);
	}
	if(m_pGameInfo->bEnableSound)
		PlaySound(TEXT("GAME_OVER"),GetModuleHandle(CLIENT_DLL_NAME),SND_RESOURCE|SND_NOSTOP|SND_ASYNC|SND_NODEFAULT|SND_NOWAIT);
	SetStationParameter(GS_WAIT_ARGEE);
	m_PlayView.KillCheckTimer();
	m_PlayView.m_btFinishDiaoDu.ShowWindow(false);
	m_PlayView.m_btLoadBuZhen.ShowWindow(false);
	m_PlayView.m_btSaveBuZhen.ShowWindow(false);
	m_PlayView.m_btThing.EnableWindow(SW_HIDE);			///< 有事要走
	m_PlayView.m_btStop.EnableWindow(SW_HIDE);				///< 停止本局
	KillAllTimer();

	//上一轮数据
/*	if (m_bShowIngLast)
	{
		m_bShowIngLast=FALSE;
		KillTimer(ID_SHOW_LAST);
		//for (int i=0;i<4;i++)
//			m_PlayView.m_UserCard[ViewStation(i)].SetCard(m_DeskCard[i],NULL,m_iDeskCardCount[i]);
	}
	m_bShowLast=FALSE;
	m_iLastCardCount=0;*/
	ResetGameStation(RS_GAME_CUT);

	//设置牌局
	//if ((GetMeUserInfo()->bDeskStation==0)&&(m_bWatchMode==FALSE))
	//	m_PlayView.m_GameSet.SetGameSetInfo(1);//m_iCardCount);
	//else
	//	m_PlayView.m_GameNoteView.SetMessage(TEXT("正在等待东家设置牌局"));
	if(!m_bWatchMode)
	{
		m_PlayView.m_btContinue.ShowWindow(true);
		SetGameTimer(GetMeUserInfo()->bDeskStation,20,ID_BEGIN_TIME);
		//m_PlayView.m_btleave.ShowWindow(true);
	}
	if(pGameEnd->bDeskStation==GetMeUserInfo()->bDeskStation&&pNetHead->bAssistantID==ASS_SALE_END)
		OnCancel();
	return TRUE;
}

/**
 * 用户请求离开
 */
bool CClientGameDlg::H082_UserHaveThing(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	HaveThingStruct * pThing=(HaveThingStruct *)pNetData;
	if (m_PlayView.m_ThingMessage.GetSafeHwnd()==NULL) 
	{
		m_PlayView.m_ThingMessage.Create(IDD_THING_MESSAGE, &m_PlayView);
		m_PlayView.m_ThingMessage.m_pParent = &m_PlayView;
	}	
	m_PlayView.m_ThingMessage.SetLeaveMessage(pThing->szMessage,m_pUserInfo[pThing->pos]->GameUserInfo.nickName);
	m_PlayView.m_ThingMessage.CenterWindow(&m_PlayView);
	m_PlayView.m_ThingMessage.ShowWindow(SW_SHOW);
	return TRUE;
}

/**
 * 请求离开结果
 */
bool CClientGameDlg::H083_UserHaveThingResult(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	if (uDataSize!=sizeof(LeaveResultStruct)) return FALSE;
	LeaveResultStruct * pLeftResult=(LeaveResultStruct *)pNetData;
	CString strBuffer;
	if (!pLeftResult->bArgeeLeave) 
//	strBuffer.Format(TEXT("玩家 %s 同意游戏结束。"),m_UserInfo[pLeftResult->bDeskStation].szName);
//	else 
	{
		strBuffer.Format(TEXT("玩家 %s 不同意游戏结束。但本局结束后，申请离开者可以离开。"),m_pUserInfo[pLeftResult->bDeskStation]->GameUserInfo.nickName);
		m_MessageHandle.InsertNormalMessage(strBuffer.GetBuffer(MAX_PATH));
	}
	return TRUE;
}

/**
 * 对家请求提前结束
 */
bool CClientGameDlg::H084_DuiJiaHaveThing(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	/*
	if (m_PlayView.m_StopMessage.GetSafeHwnd()==NULL) 
	{
		m_PlayView.m_StopMessage.Create(IDD_STOP_MESSAGE,this);
		m_PlayView.m_StopMessage.m_pParent=this;
	}
	*/
	m_PlayView.m_StopMessage.CenterWindow(&m_PlayView);
	m_PlayView.m_StopMessage.ShowWindow(SW_SHOW);
	return true;
}

/**
 * 对家请求提前结束结果
 */
bool CClientGameDlg::H085_DuiJiaHaveThingResult(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize/*, CTCPClientSocket * pClientSocket*/)
{
	if (uDataSize!=sizeof(StopResultStruct))return FALSE;
	StopResultStruct *pStop=(StopResultStruct*)pNetData;
	if (pStop->bArgee) 
	{
		m_MessageHandle.InsertNormalMessage("对家同意提前结束。");
	}
	else 
	{
		m_MessageHandle.InsertNormalMessage("对家认为还有再升级的机会。");
	}
	return true;
}

BEGIN_MESSAGE_MAP(CClientGameDlg, CLoveSendClassInExe)
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(IDM_BEGIN,OnHitBegin)
//	ON_MESSAGE(IDM_LOOK_LAST,OnHitLastTurn)
	ON_MESSAGE(IDM_HAVE_THING,OnHitHaveThing)
	ON_MESSAGE(IDM_SEND_THING,OnSendHaveThing)
	ON_MESSAGE(IDM_ARGEE_LEAVE,OnArgeeUserLeft)
	ON_MESSAGE(IDM_STOP,OnStop)
	ON_MESSAGE(IDM_STOP_THING,OnStopThing)			//发送提前结束事件
	ON_MESSAGE(IDM_ARGEE_STOP,OnAgreeStop)			//同意提前结束事件
	ON_MESSAGE(IDM_SET_FLASH_CHESS,OnFlashChess)
	
	ON_WM_TIMER()
END_MESSAGE_MAP()

CClientGameDlg * g_pCClientGameDlg=NULL;

/**
 * 构造函数
 */
CClientGameDlg::CClientGameDlg() : CLoveSendClassInExe(&m_PlayView)
{
	g_pCClientGameDlg=this;
	m_GameSet=NULL;
	m_iVersion=7;
	m_iVersion2=0;
	m_iLessCount=0;

	m_bTimeOutCount=0;
	m_iAfterWaitAction = 2;
}

/**
 * 析构函数
 */
CClientGameDlg::~CClientGameDlg()
{
}

/**
 * 数据绑定函数
 */
void CClientGameDlg::DoDataExchange(CDataExchange * pDX)
{
	CLoveSendClassInExe::DoDataExchange(pDX);
	DoDataExchangeWebVirFace(pDX);
}

/**
 * 初始化函数
 */
BOOL CClientGameDlg::OnInitDialog()
{
	m_PlayView.m_showcoredlg.m_ucomtype=GetComType();
	CLoveSendClassInExe::OnInitDialog();
	//更新标题
	SetDialogIcon(LoadIcon(GetModuleHandle(CLIENT_DLL_NAME),MAKEINTRESOURCE(IDI_CLIENT_ROOM)),TRUE);
	
	m_PlayView.m_bRightPower=GetProfileInt(TEXT("RightPower"),TRUE);

	m_playsound.Create(_T("STATIC"), "", WS_CHILD|WS_VISIBLE,  CRect(0, 0, 20, 20), this, 1234);
	m_playsound2.Create(_T("STATIC"), "", WS_CHILD | WS_VISIBLE, CRect(0, 0, 20, 20), this, 1235);
	m_playsound.ShowWindow(false);
	m_playsound2.ShowWindow(false);
	m_PlayView.m_Logic.InitPath();

	//CString s = _T("GameOption.bcf");	//本地路径
	CString s;
#ifdef	VIDEO
	s = _T("30300405.bcf");	//本地路径
#else
	s = _T("30300400.bcf");	//本地路径
#endif		
	if (CBcfFile::IsFileExist(s))
	{
		CBcfFile f(s);
		m_iAfterWaitAction = f.GetKeyVal(_T("config"), _T("AfterWaitAction"), 2);
		if (m_iAfterWaitAction != 1 && m_iAfterWaitAction != 2)
		{
			m_iAfterWaitAction = 1;
		}
	}

	return TRUE;
}

/**
 * 重新设置界面
 */
void CClientGameDlg::ResetGameFrame()
{
	m_playsound.StopMusic();
	m_playsound2.StopMusic();
	m_bTimeOutCount=0;
	
	m_PlayView.SetGamePoint();
	m_PlayView.SetNTStation(-1);
	m_PlayView.m_GameNoteView.SetMessage(NULL);
	for (int i=0;i<4;i++)
	{
	}
	if (m_PlayView.m_GameInfo.GetSafeHwnd()) m_PlayView.m_GameInfo.DestroyWindow();
	if (m_PlayView.m_HaveThing.GetSafeHwnd()) m_PlayView.m_HaveThing.DestroyWindow();
	if (m_PlayView.m_ThingMessage.GetSafeHwnd()) m_PlayView.m_ThingMessage.DestroyWindow();
	if (m_PlayView.m_GameSet.GetSafeHwnd()) m_PlayView.m_GameSet.DestroyWindow();
//	if(m_GameSet->GetSafeHwnd())	m_GameSet->EndDialog(0);
	return __super::ResetGameFrame();
}

/**
 * 开始按钮函数
 */
LRESULT	CClientGameDlg::OnHitBegin(WPARAM wparam, LPARAM lparam)
{
	//memset(m_PlayView.m_Logic.m_Path, 1, sizeof(m_PlayView.m_Logic.m_Path));//del
	//m_PlayView.m_Logic.m_Path[0][0]=1;//右方
	//m_PlayView.m_Logic.m_Path[0][1]=2;//左方
	//m_PlayView.m_Logic.m_Path[0][2]=3;//上方
	//m_PlayView.m_Logic.m_Path[0][3]=4;//下方
	//m_PlayView.m_Logic.m_Path[0][4]=5;//右上
	//m_PlayView.m_Logic.m_Path[0][5]=6;//左上
	//m_PlayView.m_Logic.m_Path[0][6]=7;//右下
	//m_PlayView.m_Logic.m_Path[0][7]=8;//左下

	//m_PlayView.UpdateViewFace(NULL);
	//return 0;//del
	OnControlHitBegin();
	return 0;
}

bool CClientGameDlg::OnControlHitBegin()
{
	if ((GetStationParameter()==GS_WAIT_SETGAME)&&(GetMeUserInfo()->bDeskStation==0))
	{
		tagGameSetInfo * pGameSet=m_PlayView.m_GameSet.GetGameSetInfo();
		if (pGameSet!=NULL)
		{
			UserArgeeGame Agree;
//			Agree.iBeginStation=pGameSet->iBeginStation;
//			Agree.iEndStation=pGameSet->iEndStation;
			Agree.iPlayCount=pGameSet->iPlayCount;
			Agree.iCardCount=pGameSet->iCardCount;
			SendGameData(&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_GM_AGREE_GAME,0);
		}
		m_PlayView.m_btContinue.ShowWindow(SW_HIDE);
		//m_PlayView.m_btleave.ShowWindow(SW_HIDE);

	}
	else if ((GetStationParameter()==GS_WAIT_NEXT)||(GetStationParameter()==GS_WAIT_ARGEE))
	{
		m_PlayView.m_btContinue.ShowWindow(SW_HIDE);
		//m_PlayView.m_btleave.ShowWindow(SW_HIDE);
		SendGameData(MDM_GM_GAME_NOTIFY,ASS_GM_AGREE_GAME,0);
	}
	KillAllTimer();
//	m_PlayView.m_StationView.CleanAllInfo(FALSE);
//	m_PlayView.m_StationView.m_iTurePoint=0;
	//ResetGameStation(RS_GAME_BEGIN);
	m_PlayView.m_btFinishDiaoDu.ShowWindow (SW_SHOW);
	m_PlayView.m_btLoadBuZhen.ShowWindow (SW_SHOW);
	m_PlayView.m_btSaveBuZhen.ShowWindow (SW_SHOW);

	m_PlayView.m_btFinishDiaoDu.EnableWindow (true);
	m_PlayView.m_btLoadBuZhen.EnableWindow (true);
	m_PlayView.m_btSaveBuZhen.EnableWindow (true);

	m_PlayView.m_Logic.StartBuzhen();
	m_PlayView.UpdateViewFace(NULL);
	m_PlayView.m_Result.ShowWindow(false);
	m_PlayView.m_Result.KillTimer(IDR_HIDE);
	return true;
}

/**
 * 按动有事按钮函数
 */
LRESULT	CClientGameDlg::OnHitHaveThing(WPARAM wparam, LPARAM lparam)
{
	if (m_PlayView.m_HaveThing.GetSafeHwnd()==NULL) 
	{
		AfxSetResourceHandle(GetModuleHandle(GET_CLIENT_DLL_NAME(szTempStr)));
		m_PlayView.m_HaveThing.Create(IDD_THING,&m_PlayView);
		m_PlayView.m_HaveThing.m_pParnet=&m_PlayView;
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}
	m_PlayView.m_HaveThing.CenterWindow(&m_PlayView);
	m_PlayView.m_HaveThing.ShowWindow(SW_SHOW);
	m_PlayView.m_HaveThing.SetFocus();
	return 0;
}

/**
 * 提前结束
 */
LRESULT	CClientGameDlg::OnStop(WPARAM wparam, LPARAM lparam)
{
//	if(m_PlayView.m_bMeSide && m_PlayView.m_iGamePoint>=80 && !m_bWatchMode)
	{
		/*
		if (m_PlayView.m_StopThing.GetSafeHwnd()==NULL) 
		{
			m_PlayView.m_StopThing.Create(IDD_STOP,this);
			m_PlayView.m_StopThing.m_pParnet=this;
		}
		*/
		m_PlayView.m_StopThing.CenterWindow(&m_PlayView);
		m_PlayView.m_StopThing.ShowWindow(SW_SHOW);
		m_PlayView.m_StopThing.SetFocus();
		
	}
	return 0;
}

/**
 * 发送提前结束
 */
LRESULT	CClientGameDlg::OnStopThing(WPARAM wparam, LPARAM lparam)
{
//	if(!m_bWatchMode && GetStationParameter()!=GS_WAIT_SETGAME && m_PlayView.m_bMeSide && m_PlayView.m_iGamePoint>=80)
	{
		
		SendGameData(MDM_GM_GAME_NOTIFY,ASS_STOP_THING,0);
	}
	return 0;
}

/**
 * 同意提前结束
 */
LRESULT	CClientGameDlg::OnAgreeStop(WPARAM wparam, LPARAM lparam)
{
	if(!m_bWatchMode && GetStationParameter()!=GS_WAIT_SETGAME)
	{
		StopResultStruct Stop;
		Stop.bArgee=(BYTE)wparam;
		SendGameData(&Stop,sizeof(Stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);
	}
	return 0;
}


/**
 * 设置闪烁棋子
 */
LRESULT	CClientGameDlg::OnFlashChess(WPARAM wparam, LPARAM lparam)
{
	if ((m_bWatchMode==FALSE)&&(GetMeUserInfo()->bDeskStation==m_PlayView.m_Logic.m_iNowOutPeople))
	{
		CRect rcEnd;
		int ix, iy;
		POINT ptTmp;
		m_PlayView.m_Logic.SetFlashChess(ix, iy, true);
		
		ptTmp.x = ix;
		ptTmp.y = iy;
		m_PlayView.m_Logic.GetRefurbishRECT(rcEnd, ptTmp);
		m_PlayView.UpdateViewFace(&rcEnd);

		SetTimer(ID_FLASH_CHESS, 500, NULL);
	}

	return 0;
}

/**
 * 发送离开请求函数
 */
LRESULT	CClientGameDlg::OnSendHaveThing(WPARAM wparam, LPARAM lparam)
{
	if(!m_bWatchMode && GetStationParameter()>GS_WAIT_ARGEE)
	{
		m_PlayView.m_btThing.EnableWindow(FALSE);
		HaveThingStruct HaveThing;
		HaveThing.pos=0;
		::lstrcpy(HaveThing.szMessage,(char *)wparam);
		SendGameData(&HaveThing,sizeof(HaveThing),MDM_GM_GAME_NOTIFY,ASS_HAVE_THING,0);
	}

	return 0;
}

/**
 * 用户请求离开
 */
LRESULT	CClientGameDlg::OnArgeeUserLeft(WPARAM wparam, LPARAM lparam)
{
	LeaveResultStruct Leave;
	Leave.bDeskStation=GetMeUserInfo()->bDeskStation;
	Leave.bArgeeLeave=(BYTE)wparam;
	SendGameData(&Leave,sizeof(Leave),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	return 0;
}

/**
 * 重置游戏
 */
void CClientGameDlg::ResetGameStation(int iGameStation)
{
	m_PlayView.m_btFinishDiaoDu.EnableWindow (false);
	m_PlayView.m_btFinishDiaoDu.ShowWindow (false);
	m_PlayView.m_btLoadBuZhen.EnableWindow (false);
	m_PlayView.m_btLoadBuZhen.ShowWindow (false);
	m_PlayView.m_btSaveBuZhen.EnableWindow (false);
	m_PlayView.m_btSaveBuZhen.ShowWindow (false);
	m_PlayView.m_StopThing.ShowWindow(false);
	m_PlayView.m_StopMessage.ShowWindow(false);
	
	if (m_PlayView.m_GameInfo.GetSafeHwnd()) m_PlayView.m_GameInfo.DestroyWindow();
	if (m_PlayView.m_HaveThing.GetSafeHwnd()) m_PlayView.m_HaveThing.DestroyWindow();
	if (m_PlayView.m_ThingMessage.GetSafeHwnd()) m_PlayView.m_ThingMessage.DestroyWindow();	
		
	switch (iGameStation)
	{
	case RS_ALL_VIEW:
	case RS_GAME_CUT:
		{
			//清理是否是新进桌子
			m_PlayView.m_bFirstGame = false;

			m_PlayView.Init();
			m_PlayView.SetGamePoint();
			m_PlayView.SetNTStation(-1);
			if (m_PlayView.m_GameSet.GetSafeHwnd()) m_PlayView.m_GameSet.DestroyWindow();
			m_playsound.StopMusic();
			m_playsound2.StopMusic();
			break;
		}
	case RS_GAME_BEGIN:
		{
			m_PlayView.m_Result.ShowWindow(false);
			m_PlayView.Init();
			m_PlayView.SetGamePoint();
			m_PlayView.SetNTStation(-1);
			if (m_PlayView.m_GameSet.GetSafeHwnd()) m_PlayView.m_GameSet.DestroyWindow();
			break;
		}
	case RS_GAME_END:
		m_PlayView.m_Logic.Init ();
		KillTimer(ID_FLASH_CHESS);
		break;
	}
	
	return;
}

void CClientGameDlg::OnGameSetting()
{
	AfxSetResourceHandle(GetModuleHandle(CLIENT_DLL_NAME));

	CGameSet GameSetDlg(this);
	m_GameSet=&GameSetDlg;
	GameSetDlg.m_bSound=m_pGameInfo->bEnableSound;
	GameSetDlg.m_bShowUser=m_pGameInfo->bShowUserInfo;	
	GameSetDlg.m_bEnableWatch=m_pGameInfo->bEnableWatch;
	GameSetDlg.m_bRightPower=GetProfileInt(TEXT("RightPower"),TRUE);

	if (GameSetDlg.DoModal()==IDOK)
	{
		m_GameSet=NULL;
		//定义参数
		bool bSendWatch=((m_bWatchMode==false)&&(m_pGameInfo->bEnableWatch!=GameSetDlg.m_bEnableWatch));

		//保存数据
		m_pGameInfo->bShowUserInfo=GameSetDlg.m_bShowUser;
		m_pGameInfo->bEnableWatch=GameSetDlg.m_bEnableWatch;
		m_pGameInfo->bEnableSound=GameSetDlg.m_bSound;
		WriteProfileInt(TEXT("RightPower"),GameSetDlg.m_bRightPower?1:0);
		m_PlayView.m_bRightPower=GameSetDlg.m_bRightPower;//棋子音效

		//发送数据
		if (bSendWatch==true)
		{
			MSG_GM_WatchSet WatchSet;			
			memset(&WatchSet,0,sizeof(WatchSet));
			WatchSet.dwUserID=0;
			SendGameData(&WatchSet,sizeof(WatchSet),MDM_GM_GAME_FRAME,ASS_GM_WATCH_SET,GameSetDlg.m_bEnableWatch?TRUE:FALSE);
		}
		if(!m_bWatchMode)
		{
			if(m_pGameInfo->bEnableSound)
			{
				TCHAR path[MAX_PATH] = {0};

				if(GS_BUZHEN==GetStationParameter())
				{
					wsprintf(path,TEXT("sound\\buzhen.mp3"));
					m_playsound.PlayMusic(m_hWnd,path);
				}
				else if(GS_BUZHEN<GetStationParameter())
				{
					wsprintf(path,TEXT("sound\\backsound.mp3"));
					m_playsound.PlayMusic(m_hWnd,path);
				}
			}
			else
			{
				m_playsound.StopMusic();
				m_playsound2.StopMusic();
			}
		}
	}
	m_GameSet=NULL;

	AfxSetResourceHandle(GetModuleHandle(NULL));

	return;
}

void CClientGameDlg::OnWatchSetChange(void)
{
	if (m_bWatchMode==true)
	{
		if (m_bWatchOther)
			m_MessageHandle.InsertNormalMessage(TEXT("玩家允许您旁观他游戏"));
		else
			m_MessageHandle.InsertNormalMessage(TEXT("玩家不允许您旁观他游戏"));
		m_PlayView.m_Logic.m_bWatchOther=m_bWatchOther;
		m_PlayView.Invalidate(true);
	}
}

/**
 * 用户离开
 */
bool CClientGameDlg::GameUserLeft(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser)
{
	if ((bWatchUser==false)&&(pUserItem!=NULL))
	{
		if (GetStationParameter()==GS_WAIT_ARGEE)
		{
			/*for (int i=0;i<4;i++)
			{
				if (m_pUserInfo[i]!=NULL) 
				{
					m_pUserInfo[i]->GameUserInfo.bUserState=USER_SITTING;
					m_UserListDlg.UpdateGameUser(m_pUserInfo[i]);
				}
			}
			if (m_PlayView.m_GameInfo.GetSafeHwnd()) m_PlayView.m_GameInfo.DestroyWindow();
			m_PlayView.m_GameNoteView.SetMessage(TEXT("正在等待东家设置牌局"));
			m_PlayView.UpdateViewFace(NULL);*/
			tagBuZhen  bz;
			bz.station=bDeskStation;
			bz.Count=30;
			for(int i=0;i<bz.Count;i++)
			{
				bz.CardArr[i]=JQ_TYPE_NONE;
			}			
			m_PlayView.m_Logic.CopyOtherBuZhen(bz);
		}
	}
	//旁观者也离开游戏桌
	if(GetMeUserInfo()->bDeskStation==bDeskStation&&!bWatchUser==TRUE)
	{
		OnCancel();
	}
	return __super::GameUserLeft(bDeskStation,pUserItem,bWatchUser);
	
}

void CClientGameDlg::OnTimer(UINT nIDEvent)
{

	if (nIDEvent==ID_FLASH_CHESS)
	{
		CRect rcEnd;
		int ix, iy;
		POINT ptTmp;
		m_PlayView.m_Logic.SetFlashChess(ix, iy, !m_PlayView.m_Logic.GetFlashChess());
		
		ptTmp.x = ix;
		ptTmp.y = iy;
		m_PlayView.m_Logic.GetRefurbishRECT(rcEnd, ptTmp);
		m_PlayView.UpdateViewFace(&rcEnd);
	}
	else if (nIDEvent==ID_SHOW_PATH)
	{
		// [tmpX,tmpY]需要设置箭头的位置，
		// 因为需要确定方向，所以才会有FrontPath, BackPath
		// FrontPath表示设置位置的前一位置，BackPath表示设置位置的后一位置
		for (int j=0; j<MAX_I; j++)
		{
			for (int k=0; k<MAX_J; k++)
			{
				// 位置不能为空，前后位置x,y需要有一个绝对值为1
				//（为什么只需要一个，有时另一个可能为0，但肯定有一个为1）
				// bContinueInsertPosition 该位置是否已经插入
				if ( 255!=m_MResultPath.PathMsg.cPath[j][k]    &&    \
					(1==abs(j-m_MResultPath.CurPath.x)||1==abs(k-m_MResultPath.CurPath.y))    &&    \
					!m_MResultPath.bContinueInsertPos[j][k] )
				{
					// cPath 保存每个位置的索引，且这索引是连续的。如果两位置之间索引没有连续
					// 可以判定它们是不相连的
					if (255!=m_MResultPath.CurPath.x && 255!=m_MResultPath.CurPath.y   &&   \
						1!=abs(m_MResultPath.PathMsg.cPath[j][k] - \
						m_MResultPath.PathMsg.cPath[m_MResultPath.CurPath.x][m_MResultPath.CurPath.y]))
					{
						continue;
					}

					// 确定下一个位置
					m_MResultPath.BackPath.x = j;
					m_MResultPath.BackPath.y = k;
					//设置轨迹
					m_PlayView.m_Logic.UserPath(m_MResultPath.PathMsg.station, m_MResultPath.CurPath.x, \
						m_MResultPath.CurPath.y, m_MResultPath.FrontPath, m_MResultPath.BackPath);
					//设置移动过程中棋子（但不是最终结果）
					m_PlayView.m_Logic.UserMovePathCheen(m_MResultPath.PathMsg.station, m_MResultPath.FrontPath, \
						m_MResultPath.CurPath, m_MResultPath.BackPath,m_MResultPath.PathMsg.m_iEndI, m_MResultPath.PathMsg.m_iEndJ);
					//获得刷新区域
					CRect rcCurrent,rcFront,rcEnd;
					m_PlayView.m_Logic.GetRefurbishRECT(rcFront, m_MResultPath.FrontPath);
					m_PlayView.UpdateViewFace(&rcFront);
					m_PlayView.m_Logic.GetRefurbishRECT(rcCurrent, m_MResultPath.CurPath);
					m_PlayView.UpdateViewFace(&rcCurrent);
					m_PlayView.m_Logic.GetRefurbishRECT(rcEnd, m_MResultPath.BackPath);
					m_PlayView.UpdateViewFace(&rcEnd);
					//rcCurrent.UnionRect(rcCurrent, rcFront);
					//rcCurrent.UnionRect(rcCurrent, rcEnd);
					//m_PlayView.UpdateViewFace(&rcCurrent);
					Msg("Test:DDDD 当前步数%d rcFront(%d,%d,%d,%d) rcCurrent(%d,%d,%d,%d) rcEnd(%d,%d,%d,%d)",rcCurrent.left,rcCurrent.top,rcCurrent.right,rcCurrent.bottom,\
						rcCurrent.left,rcCurrent.top,rcCurrent.right,rcCurrent.bottom, rcEnd.left, rcEnd.top, rcEnd.right, rcEnd.bottom);

					// 保存位置信息，准备下一位置设置
					m_MResultPath.FrontPath.x = m_MResultPath.CurPath.x;
					m_MResultPath.FrontPath.y = m_MResultPath.CurPath.y;
					m_MResultPath.CurPath.x = m_MResultPath.BackPath.x;
					m_MResultPath.CurPath.y = m_MResultPath.BackPath.y;
					m_MResultPath.BackPath.x = 255;
					m_MResultPath.BackPath.y = 255;
					m_MResultPath.bContinueInsertPos[j][k] = TRUE;
				}
			}
		}

		if (m_MResultPath.iCurStep++ >= m_MResultPath.PathMsg.iStep)
		{
			KillTimer(ID_SHOW_PATH);
			m_PlayView.m_Logic.UserMove(m_MResultPath.PathMsg);
			m_PlayView.UpdateViewFace(NULL);
		}
	}
	CLoveSendClassInExe::OnTimer(nIDEvent);
}

void CClientGameDlg::OnCancel()
{
	//查询状态
	if (!m_bWatchMode && GetStationParameter()>=GS_BUZHEN&&GetStationParameter()<GS_WAIT_NEXT)
	{
		TCHAR sz[200];
		CString s = CBcfFile::GetAppPath ();/////本地路径	

#ifdef	VIDEO
		CBcfFile f( "30300405.bcf");
#else
		CBcfFile f( "30300400.bcf");
#endif	
		
		CString key=TEXT("config");		
		CString sec;

		sec.Format("FouceQuitTip%d", m_pGameInfo->uComType);

		int nMoneyTemp = 1;
		for(int i=0; i<Glb().m_nPowerOfGold; i++)
		{
			nMoneyTemp*=10;
		}
		if (GetComType() == TY_MONEY_GAME)
		{
			wsprintf(sz,f.GetKeyVal(key, sec, ""),basepoint*uRunPublish*nMoneyTemp);
		}
		else
		{
			wsprintf(sz,f.GetKeyVal(key, sec, ""),uRunPublish,basepoint*uRunPublish*nMoneyTemp);
		}
		
		
		if (IDOK!=AFCMessageBox(sz,m_pGameInfo->szGameName,AFC_YESNO)) //|MB_DEFBUTTON2|MB_ICONINFORMATION,this)) 
			return;
		
		SendGameData(150,3,0);
	}

	/////释放视频资源  
	//if( NULL != CPlayVideo::CreatePlayVideo())
	//	CPlayVideo::CreatePlayVideo()->Video_Release();

	m_PlayView.m_bFirstGame = true;

	AFCCloseFrame();

	__super::OnCancel();
}

BYTE CClientGameDlg::ViewStation(BYTE bDeskStation)
{
	if(m_pGameInfo->uDeskPeople==2)
	{
		if(bDeskStation==GetMeUserInfo()->bDeskStation)
			return 2;
		else
			return 0;
	}
	BYTE bViewStation=(bDeskStation+m_pGameInfo->uDeskPeople-GetMeUserInfo()->bDeskStation);
	switch (m_pGameInfo->uDeskPeople)
	{
	case 1: { bViewStation+=1; break; }
	case 2: { bViewStation+=1; break; }
	case 3: { bViewStation+=1; break; }
	case 4: { bViewStation+=2; break; }
	case 5: { bViewStation+=2; break; }
	case 6: { bViewStation+=3; break; }
	case 7: { bViewStation+=3; break; }
	case 8: { bViewStation+=4; break; }
	}
	return bViewStation%m_pGameInfo->uDeskPeople;
}

/**
 * 为视频模块重载此函数
 */
bool CClientGameDlg::GameUserCome(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser)
{
	if (! __super::GameUserCome(bDeskStation, pUserItem, bWatchUser))
	{
		return FALSE;
	}

#ifdef	VIDEO
	if( GetMeUserInfo()->dwUserID == pUserItem->GameUserInfo.dwUserID && bWatchUser )
	{
		 m_PlayView.m_bWatch=bWatchUser;
	}
	 if( GetMeUserInfo()->dwUserID == pUserItem->GameUserInfo.dwUserID && (!bWatchUser) )
	{    
		CPlayVideo *pPlayVideo=CPlayVideo::CreatePlayVideo();
		if(NULL!=pPlayVideo)
		{ 
			CString NickName=TEXT("");
			int    byteDeskNO=0;
			UserInfoStruct &UInfo=	pUserItem->GameUserInfo;
			NickName+=UInfo.nickName;
			byteDeskNO=UInfo.bDeskNO;
			UINT	uiRoomID = m_pGameInfo->uRoomID;
			UINT	uiBRRoomID =   uiRoomID * 1000 + byteDeskNO; 

			ST_INITVIDEO stInitVideo;
			stInitVideo.iRoomPassType = 0;
			stInitVideo.nRoomID		  = uiBRRoomID;
			stInitVideo.pParentWnd    = &m_PlayView;
			stInitVideo.strRoomPass   = _T("");
			stInitVideo.strUserName	  = NickName;
			stInitVideo.strUserPass   = _T("");
			if( pPlayVideo->Video_Initialize(stInitVideo) )
			{
				//AppendLog("视频初始化成功!");
				//连接视频服务器
				pPlayVideo->Connect();
			}
			else
			{
				//pPlayVideo->Video_Release();
				//AppendLog("视频初始化失败!");
				return 0;
			}

		} 
		 

	}
#endif 
	return TRUE;
}

bool	CClientGameDlg::AFCCloseFrame()
{
#ifdef	VIDEO
		///释放视频资源  
	if( NULL != CPlayVideo::CreatePlayVideo())
		CPlayVideo::CreatePlayVideo()->Video_Release();
#endif

	return __super::AFCCloseFrame();
}

///
///依当前金币倍率得到字符串
///@param [in] int nNum 要显示的数字
///@param [out] CString &Str 返回的字符串
///@param [in] int nPower 金币倍率
///@param [in] bool bIsBlank 返回是否加空格
///@return void
///

void GetNumString(int nNum, CString &Str, int nPower,bool bIsBlank)
{
	if (0 == nNum)
	{
		Str.Format("0");
		return;
	}
	/// 暂存结果
	TCHAR strTmp[50];
    TCHAR str[50];
	/// 目前只处理大于0的情况，在正常字符串后面要加至少一个0
	wsprintf( strTmp, TEXT("%d"), nNum);
	for (int i=0; i<nPower; ++i)
	{
		_tcscat( strTmp, TEXT("0"));
	}
	/// 按位数每三位空一格显示
	int nLen = _tcslen(strTmp);	// 字符串长度
	int nTimes = nLen % 3;	// 这个字符串可以分成的节数，至少是1节
	
	int nSrc = 0;
	int nDes = 0;

	for (int i=0; i<nLen; ++i)
	{
		if ((i>0)&&(i%3==nTimes)&&bIsBlank)
		{
			str[nDes++] = TEXT(' ');
		}
		str[nDes++] = strTmp[nSrc++];
	}
	str[nDes] = TEXT('\0');
	Str.Format("%s",str);
	return ;
}