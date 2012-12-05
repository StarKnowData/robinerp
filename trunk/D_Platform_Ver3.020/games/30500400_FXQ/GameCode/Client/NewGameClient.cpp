#include "stdafx.h"
#include "NewGameClient.h"
#include "IGameFrame.h"
#include "UI_ForLogic/IUserInterface.h"
#include "UI_ForLogic/GameIDDefines.h"
#include "UIControlsDefine.h"
#include "Common/UIMessageDefines.h"
#include "LoveSendClassInExe.h"

const    int   AIRPORT_WIDTH  = 37 ; 
const    int   AIRPORT_HEIGHT = 37 ; 
 
void MsgPrint(const char *lpszFormat, ...)
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

IGameImpl *CreateNewGameImpl(IGameFrame* pIBase, IUserInterface *pIUI)
{
    return dynamic_cast<IGameImpl*>(new CNewGameClient(pIBase, pIUI));
}
void DestroyNewGameImpl(IGameImpl **ppImp)
{
    delete *ppImp;
    *ppImp = NULL;
}

CNewGameClient::CNewGameClient(IGameFrame *pGameFrame, IUserInterface *pUI)
{
    m_pGameFrame = pGameFrame;
    m_pUI = pUI;

	m_iMyDeskStation = -1 ;
	m_cbOperater   = 255 ; 

	m_cbCurrentStation = 0 ; 
	m_cbDiceFrame    = 0 ; 

	m_iBeginTime   = 10 ;   
    m_iDiceTime    = 10 ; 
	m_iThinkTime   = 15 ; 
	m_cbDiceValue = 0 ;
	m_iAniPlaneCount = 0 ;

	m_bAutoOutTime = 0 ;

	m_bWatchStation = false ;

	memset(m_iPlayerfight , 0 , sizeof(m_iPlayerfight))  ; 

	memset(m_iPropCount , 0 , sizeof(m_iPropCount)) ;

	memset(m_bReady , 0 , sizeof(m_bReady)) ; 

	memset(m_bAutoOutCard,0,sizeof(m_bAutoOutCard)) ; 

	for(int  i = 0 ; i<MAX_ANI_PLANE ; i++)
	{
		m_planeAni[i].IniData() ;
	}

	m_bombAni.IniData() ;

	m_SoundEngine = createIrrKlangDevice();

	m_SoundEnginBg = createIrrKlangDevice() ; 

}

CNewGameClient::~CNewGameClient()
{
	if(m_SoundEngine)
	{
		m_SoundEngine->drop();
	}

	if(m_SoundEnginBg)
	{
		m_SoundEnginBg->drop() ; 
	} 

}
/// 初始化
int CNewGameClient::Initial()
{
    // 载入UI
    m_pUI->LoadData(L"UIData_FXQ.dat");

    return 0;
}
/// 初始化UI
int CNewGameClient::InitUI()
{
	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		GetControlNode(pExtAni , IExAnimate , (i+EX_ANI_HIGTLIGHT)) ; 
		pExtAni->SetPlayState(false) ; 
		pExtAni->SetControlVisible(false) ; 
		pExtAni->SetMouseThough(true) ;
	}

	GetControlNode(pImage  , IImage , IMG_BASE_POINT) ; 
	m_ptBasePoint.SetPoint(pImage->GetGameX() -27, pImage->GetGameY()- 25 ) ; 

	m_BasePath.SetBasePt(AIRPORT_WIDTH , AIRPORT_HEIGHT ,m_ptBasePoint) ;


	CString filepath = CBcfFile::GetAppPath() ; 
	CString strfileName ;
	strfileName.Format("%d.bcf",NAME_ID) ; 
	CBcfFile file(filepath + strfileName) ;
	m_bSoundPlay = file.GetKeyVal("config","PlaySound",m_bSoundPlay) ; 
	m_bSoundBgPlay = file.GetKeyVal("config", "PlayBgSound" , m_bSoundBgPlay) ;
	m_bAllowWatch = file.GetKeyVal("config","AllowWatch",m_bAllowWatch) ; 
	m_strCoinName = file.GetKeyVal("config","CoinName","乐豆") ;

    UserSetGameInfo(m_bSoundPlay,m_bSoundBgPlay, m_bAllowWatch,false);
	
    return 0;
}
///初始化
void CNewGameClient::ResetScenceData(void) 
{
	m_GameScene.cbMySide = m_iMyDeskStation ; 
	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		for(int  j = 0 ; j<PLAYER_PLANE_NUM  ; j ++)
		{
			m_GameScene.PlaneIndex[i][j].emSide = i ; 
			m_GameScene.PlaneIndex[i][j].emPlaneState = emStandby ; 
			m_GameScene.PlaneIndex[i][j].cbStep = STEP_HOME ; 
			m_GameScene.PlaneIndex[i][j].cbAirPortPos = i ;
			m_GameScene.PlaneIndex[i][j].cbLandPos  = j ;  
		}
	}

}
/// 设置游戏的当前状态
void CNewGameClient::SetGameStation(void * pBuffer,int nLen)
{
	m_bWatchStation = m_pGameFrame->GetIsWatching() ; 

	m_iMyDeskStation = m_pGameFrame->GetMyDeskStation() ; 

	m_BasePath.IniCoordinate((enumSide)m_iMyDeskStation) ; ///根据自己的位置产生一个坐标系
	
	SetBaseImage() ;
	ResetScenceData() ;

	switch(GetStationParameter())
	{
	case GS_WAIT_SETGAME:
	case GS_WAIT_ARGEE:
		{
			m_pGameFrame->SetTimer(TIME_GAME_BEGIN , 10 * 1000 ) ; 
			ShowOrHideUserTime(m_iMyDeskStation , 10 ,0 , true) ;

			GetControlNode(pBtn , IButton ,BN_START_GAME) ; 

			if(NULL != pBtn)
			{
				pBtn->SetControlVisible(!m_bWatchStation) ; 
				pBtn->SetEnable(true) ; 
			}

			memset(m_bAutoOutCard , 0 , sizeof(m_bAutoOutCard)) ; 

			ShowGameFinish(false) ; 

			PlayDiceAni(0,false , false) ; 

			ShowFightScore(false) ;

			ShowPlayerPropLogo(false) ;
					
			break;
		}
	case GS_SEND_CARD:
		{
			break;
		}
	case GS_PLAY_GAME:
		{
			PlayingGameStation  *PlayingData = (PlayingGameStation *)pBuffer; 

			memcpy(m_iPropCount ,PlayingData->cbPropCount ,sizeof(m_iPropCount)) ; 

			memcpy(m_iPlayerfight ,PlayingData->iPlayerfight , sizeof(m_iPlayerfight)) ;

			ShowFightScore(true) ;

			ShowPlayerPropLogo(true) ;

			for(int i = 0 ; i<PLAY_COUNT ; i++)
			{
				for(int  j = 0 ; j<PLAY_COUNT ; j++)
				{
					m_GameScene.PlaneIndex[i][j] = PlayingData->PlaneData[i][j]; 
				}
			}

			break ; 
		}
	case GS_WAIT_NEXT:
		{			
			break;
		}
	default:
		{
			break;
		}
	}	

	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		DrawPlayerPlane(i , true) ; 
	}

	return  ; 
}
/// 游戏消息 
int CNewGameClient::HandleGameMessage(WORD nMainID,WORD nSubId,BYTE * buffer,int nLen)
{
    switch(nSubId)
    {
    case ASS_GM_GAME_STATION:   ///<设置状态
        {
			GameBaseStation *pBaseData  =(GameBaseStation *)buffer ; 

			m_iBeginTime = pBaseData->cbBeginTime ; 
			m_iDiceTime  = pBaseData->cbDiceTime ; 
			m_iThinkTime = pBaseData->cbThinkTime ; 

			memcpy(m_bReady , pBaseData->bUserReady , sizeof(m_bReady)) ; 
			memcpy(m_bAutoOutCard , pBaseData->bUserAuto , sizeof(m_bAutoOutCard)) ; 
			
			SetGameStation(buffer, nLen); 

			ShowAutoOutCard(true) ;

			ShowReadyLogo(true) ;
			break;
        }
	case ASS_GM_AGREE_GAME:
		{		
			if(nLen!=sizeof(MSG_GR_R_UserAgree))
			{
				return 0;
			}				

			MSG_GR_R_UserAgree * pUser=(MSG_GR_R_UserAgree *)buffer;

			if(pUser->bDeskStation == m_iMyDeskStation)
			{
				HideAllTime() ; 
				m_pGameFrame->KillTimer(TIME_GAME_BEGIN);
				
				GetControlNode(pBtn ,IButton , BN_START_GAME)->SetControlVisible(false) ; 
				pBtn->SetEnable(false) ;

				PlayHihtLightAni(false ,false) ; 

				PlayDiceAni(0,false ,false) ; 

				ShowGameFinish(false) ; 

			}
			m_bReady[pUser->bDeskStation] = true ;

			ShowReadyLogo(true) ; 

			break;
		}
	case ASS_GAME_BEGIN:
		{
			if(nLen != sizeof(BeginUpgradeStruct))
			{
				return 0 ; 
    		}

			SetStationParameter(GS_PLAY_GAME) ; 

			OnSCBeginMessage((BeginUpgradeStruct *)buffer) ; 

			break;
		}
	case ASS_APPLY_DICE:
		{
			if(nLen != sizeof(WaitDiceStruct))
			{
				return 0 ; 
			}

			OnSCWaitDiceMessage((WaitDiceStruct *)buffer ) ; 

			break; 
		}
	case  ASS_NOTIFY_DICE:
		{
			if(nLen != sizeof(NotifyDiceStruct))
			{
				return 0 ; 
			}
			OnSCDiceMessage((NotifyDiceStruct *)buffer) ; 
			break; 
		}
	case  ASS_NOTIFY_CHOISE_PLANE:
		{
			if(nLen != sizeof(NotifyChoisePlane))
			{
				return 0 ; 
			}

			OnSCChoisePlaneMessage((NotifyChoisePlane *)buffer) ;

			break;
		}
	case  ASS_PLANE_FLY_ANI:
		{
			if(nLen != sizeof(PlayerActiveStruct))
			{
				return 0 ; 
			}

			OnSCPlaneFlyMessage((PlayerActiveStruct *)buffer) ; 
	
			break;
		}
	case  ASS_PLANE_FLY_FINISH:
		{
			if(nLen != sizeof(ScenceChangeStruct))
			{
				return 0 ; 
			}

			OnSCPlaneFlyFinish((ScenceChangeStruct *)buffer) ;

			break;
		}
	case  ASS_NO_CONTINUE_END:
		{
			if(nLen != sizeof(GameEndStruct))
			{
				return 0 ; 
			}

			SetStationParameter(GS_WAIT_ARGEE) ; 

			OnSCGameFinish((GameEndStruct *)buffer) ;
			break;
		}
	case  ASS_CUT_END:
		{
			if(nLen != sizeof(GameCutStruct))
			{
				return 0 ; 
			}
			SetStationParameter(GS_WAIT_ARGEE) ; 

			OnSCGameCutFinish((GameCutStruct *)buffer) ; 

			break;
		}
	case  ASS_AUTO:
		{
			if(sizeof(AutoStruct) != nLen)
			{
				return 0 ; 
			}
			AutoStruct *pAutodata = (AutoStruct *)buffer ; 
			SetAutoStation(pAutodata->bDeskStation,pAutodata->bAuto) ; 

			ShowAutoOutCard(true) ; 

			break; 
		}
    default:
        break;
    }
    return 0;
}
/// 界面消息
int CNewGameClient::OnUIMessage(TUIMessage* pMessage)
{
	if(pMessage->_uMessageType == UI_LBUTTONUP)
	{
		switch(pMessage->_uControlID)
		{
		case  BN_RESET_FRAME:
		case  BN_SET_FRAME:
			{
				CPoint ptTemp = m_ptBasePoint ; 
				GetControlNode(pImage  , IImage , IMG_BASE_POINT) ; 
				m_ptBasePoint.SetPoint(pImage->GetGameX() -27, pImage->GetGameY()- 25 ) ; 
				m_BasePath.SetBasePt(AIRPORT_WIDTH , AIRPORT_HEIGHT ,m_ptBasePoint) ;

				m_BasePath.IniCoordinate((enumSide)m_iMyDeskStation) ; ///根据自己的位置产生一个坐标系

				for(int i = 0 ; i<m_iAniPlaneCount ; i++)
				{
					m_planeAni[i].ResetPlanePoint(m_ptBasePoint - ptTemp) ;
					m_planeAni[i].m_ptCurrentPos.Offset(m_ptBasePoint - ptTemp) ; 
				}

				m_bombAni.ResetPlanePoint(m_ptBasePoint - ptTemp) ; 
				m_bombAni.m_ptCurrentPos.Offset(m_ptBasePoint - ptTemp) ; 

				return 0 ;
			}
		case  BTN_SET_GAME_INFO:
			{
				UserSetGameInfo(m_bSoundPlay,m_bSoundBgPlay ,m_bAllowWatch,true);
				return 0; 
			}
		case BTN_SET_GAME_OK:
			{
				IRadioButton *pRadioBtnVoice = dynamic_cast<IRadioButton *>(m_pUI->GetIControlbyID(BTN_SET_VOICE)) ;
				IRadioButton *pRadioBtnVoicebg = dynamic_cast<IRadioButton *>(m_pUI->GetIControlbyID(BTN_SET_BG_VOICE)) ;
				IRadioButton *pRadioBtnWatch = dynamic_cast<IRadioButton *>(m_pUI->GetIControlbyID(BTN_SET_WATCH)) ; 
				if(NULL != pRadioBtnVoice && NULL!= pRadioBtnWatch &&NULL != pRadioBtnVoicebg)
				{
					m_bSoundPlay =pRadioBtnVoice->GetIsSelect() ; 
					m_bSoundBgPlay = pRadioBtnVoicebg->GetIsSelect() ; 
					m_bAllowWatch = pRadioBtnWatch->GetIsSelect() ; 

					CString strCfgName;
					strCfgName.Format("%s%d.bcf",CINIFile::GetAppPath(),NAME_ID);
					DWORD dwCfgFile = ::cfgOpenFile(strCfgName);

					if(dwCfgFile >=0x10) //文件打开成功
					{
						//声音开关配置
						::cfgSetValue(dwCfgFile,"config","PlaySound",m_bSoundPlay);

						//声音开关配置
						::cfgSetValue(dwCfgFile,"config","PlayBgSound",m_bSoundBgPlay);

						//允许旁观开关配置
						::cfgSetValue(dwCfgFile,"config","AllowWatch",m_bAllowWatch);

						::cfgClose(dwCfgFile);						
					}
				}

				UserSetGameInfo(m_bSoundPlay,m_bSoundBgPlay ,m_bAllowWatch,false);

				if(!m_SoundEngine || !m_SoundEnginBg)
				{
					return 0 ; 
				}

				if(m_bSoundBgPlay)
				{
					m_SoundEnginBg->setAllSoundsPaused(false) ; 

					if(GetStationParameter() == GS_SEND_CARD ||GetStationParameter() == GS_PLAY_GAME)
					{
						SetGameBgSound(GAME_BG_SOUND ,true) ;
					}
				}
				else
				{
					m_SoundEnginBg->setAllSoundsPaused(true) ; 
					m_SoundEnginBg->stopAllSounds() ; 
				}

				if(m_bSoundPlay)
				{
					m_SoundEngine->setAllSoundsPaused(false);	
				}
				else
				{
					m_SoundEngine->setAllSoundsPaused(true);
					m_SoundEngine->stopAllSounds();		
				}
				return 0;

			}
		case  BTN_TRUSTEE:
		case  BTN_TRUSTEE_CANCEL:
			{
				AutoStruct TrustData ; 
				TrustData.bAuto = !m_bAutoOutCard[m_iMyDeskStation] ; 
				TrustData.bDeskStation = m_pGameFrame->GetMyDeskStation() ; 

				m_pGameFrame->SendGameData(&TrustData,sizeof(TrustData),MDM_GM_GAME_NOTIFY,ASS_AUTO,0);

				break; 
			}
		case  BTN_SET_GAME_CANCEL:
			{
				UserSetGameInfo(m_bSoundPlay,m_bSoundBgPlay ,m_bAllowWatch,false);
				return 0;
			}
		case  IMG_PLANE_2:
		case  IMG_PLANE_2 +1:
		case  IMG_PLANE_2+2:
		case  IMG_PLANE_2+3:
			{
				if(m_iMyDeskStation != m_cbOperater)
				{
					return 0 ; 
				}
				if(m_cbCurrentStation != WAIT_PLAYER_CHOISE)
				{
					return 0 ; 
				}
				if(m_bWatchStation)
				{
					return 0 ; 
				}

				PlayerChoiseStruct ChoiseData ; 
				ChoiseData.cbDeskStation = m_iMyDeskStation ; 
				ChoiseData.inDexPlane =  pMessage->_uControlID - IMG_PLANE_2; 
				m_pGameFrame->SendGameData(&ChoiseData ,sizeof(ChoiseData) ,MDM_GM_GAME_NOTIFY ,ASS_PLAYER_CHOISE_PLANE ,0) ;

				return 0 ;
			}
		default:
			break;
		}

		if(m_cbCurrentStation == WAIT_PLAYER_DICE)
		{
			GetControlNode(pContain , IContain ,CTN_PROP) ; 

			if(pMessage->_uControlID  == BTN_PROP1)
			{
				GetControlNode(pBtn , IButton , BTN_PROP1)->SetControlVisible(false) ; 
				pContain->SetControlVisible(true) ; 
				return 0 ;
			}
			if(pMessage->_uControlID >=BTN_SICE &&pMessage->_uControlID <BTN_SICE + 6)
			{
				pContain->SetControlVisible(false) ; 

				PropDiceStruct DiceData ;
				DiceData.cbDeskStaion = m_iMyDeskStation ; 
				DiceData.cbIndex   =  pMessage->_uControlID - BTN_SICE + 1 ; 

				m_pGameFrame->SendGameData(&DiceData , sizeof(DiceData) ,MDM_GM_GAME_NOTIFY ,ASS_DICE_PROP ,0) ;
				return 0 ; 
			}

			if(m_iMyDeskStation != m_cbOperater)
			{
				return 0 ; 
			}

			if(m_bWatchStation)
			{
				return 0 ; 
			}

			pContain->SetControlVisible(false) ; 

			m_pGameFrame->SendGameData(ASS_APPLY_DICE ,NULL , 0 ) ; 
			return 0; 
		}
	}

	if(pMessage->_uMessageType == UI_CATOONFINISH)
	{
		if(pMessage->_uControlID == EXT_ANI_DICE)
		{
			PlayDiceAni(0,false , true) ; 
			return 0  ; 
		}
	}

	if(pMessage->_uMessageType == UI_MOUSEENTER ||pMessage->_uMessageType == UI_MOUSEMOVE)
	{
		if(m_iMyDeskStation != m_cbOperater ||m_cbCurrentStation != WAIT_PLAYER_CHOISE)
		{
			ShowDestineImg(0 ,pMessage->_uControlID - IMG_PLANE_2,false) ;
			return  0 ; 
		}
		if(pMessage->_uControlID>=IMG_PLANE_2 && pMessage->_uControlID <IMG_PLANE_2+4 )
		{
			int iStep = m_ClientLogic.GetPlaneFlyPos(m_iMyDeskStation ,pMessage->_uControlID - IMG_PLANE_2 ,m_cbDiceValue, m_GameScene) ;

			//MsgPrint("wysoutfxqinfo::当前检测到飞机飞到的位置 iStep ==%d" , iStep) ;
			ShowDestineImg(iStep ,pMessage->_uControlID - IMG_PLANE_2,true) ; 
		}
	}
	else
	{
		ShowDestineImg(0 ,pMessage->_uControlID - IMG_PLANE_2, false) ; 
	
	}
    return 0;
}

/// 定时器消息（游戏中的定时器处理）
void CNewGameClient::OnTimer(int nTimerID)
{
	switch(nTimerID)
	{
	case  TIME_GAME_BEGIN :
		{
			m_pGameFrame->KillTimer(TIME_GAME_BEGIN);
			m_pGameFrame->ClickContinue();
			break ; 
		}
	case  TIME_AIM_AT_PLANE:
		{
			m_bombAni.RunAni() ; 

			if(m_bombAni.m_bFinish)
			{
				m_pGameFrame->KillTimer(TIME_AIM_AT_PLANE) ;
				m_pGameFrame->SetTimer(TIME_PLANE_FLY , 200) ;
				DrawAimBombAni(false) ; 
				DrawBmobAni(true) ;
				SetPlaySound(m_iMyDeskStation , BOMB_SOUND ,false) ;
			}
			else
			{
				DrawAimBombAni(true) ; 
				SetPlaySound(m_iMyDeskStation , AIM_AT_PLANE ,false) ;
			}
			break;
		}
	case  TIME_PLANE_FLY:  //飞机飞行动画
		{
			m_pGameFrame->KillTimer(TIME_PLANE_FLY) ;

			for(int i = 0 ; i<m_iAniPlaneCount ; i++)
			{
				m_planeAni[i].RunAni() ; 
			}

			bool  bAllFinish = true ; 

			for(int  i = 0 ; i<m_iAniPlaneCount ; i++)
			{
				if(m_planeAni[i].m_bFinish == false)
				{
					bAllFinish = false ;               ///有玩家的动画飞机还没飞完
					break;
				}
			}

			if(bAllFinish == true )
			{
				m_pGameFrame->SendGameData(ASS_PLANE_FLY_FINISH , 0 , 0) ;

				if(m_planeAni[0].m_iActiveTyple == emArriveHome)
				{
					SetPlaySound(m_iMyDeskStation , ARRIVE_HOME ,false) ;
				}
				else
				{
					SetPlaySound(m_iMyDeskStation , PLANE_ARRIVE ,false) ;
				}

				ShowFightScore(true) ; 
			}
			else
			{
				m_pGameFrame->SetTimer(TIME_PLANE_FLY , 10) ;
			}

			DrawPlaneAni() ; 
	
			break; 
		}
	case  TIME_PLAYER_DICE:
		{
			HideAllTime() ; 
			m_pGameFrame->KillTimer(TIME_PLAYER_DICE) ; 
			m_pGameFrame->KillTimer(TIME_CURSOR_ANI) ; 
			SetCurrentCursor(-1) ; 

			//UserAutoDice() ; 
			m_pGameFrame->SendGameData(ASS_APPLY_DICE ,NULL , 0 ) ; 

			break;
		}
	case  TIME_DICE_FINISH:  ///通知服务端色子动画完成
		{
			m_pGameFrame->KillTimer(TIME_DICE_FINISH) ; 
			m_pGameFrame->SendGameData(ASS_NOTIFY_DICE_FINISH , NULL ,0) ;
			break; ; 
		}
	case  TIME_CURSOR_ANI:
		{
			m_cbDiceFrame = (m_cbDiceFrame + 1)%8 ; 
			SetCurrentCursor(m_cbDiceFrame) ; 
			break;
		}
	case  TIME_PLAYER_CHOISE: ///玩家选择飞机
		{
			m_pGameFrame->KillTimer(TIME_PLAYER_CHOISE) ; 

			if(m_bAutoOutCard[m_iMyDeskStation])
			{
				UserAutoChoisePlane() ; 
				return ; 
			}

			if(m_bAutoOutCard[m_iMyDeskStation] == false &&m_bAutoOutTime<3)
			{
				m_bAutoOutTime ++;
				CString strInfo ; 
				strInfo.Format("注意，您已超时%d次 ,超时3次将自动设为托管!" , m_bAutoOutTime);
				m_pGameFrame->InsertNormalMessage(strInfo.GetBuffer()) ;

				UserAutoChoisePlane() ; 
			}
			else
			{
				AutoStruct TrustData ; 
				TrustData.bAuto = true ; 
				TrustData.bDeskStation = m_iMyDeskStation ; 
				m_pGameFrame->SendGameData(&TrustData,sizeof(TrustData),MDM_GM_GAME_NOTIFY,ASS_AUTO,0);
			}
			break;
		}
	default:
		{
			break ; 
		}
	}
	return ; 

}
///玩家退出游戏
bool CNewGameClient::OnGameQuiting()
{
	if(m_pGameFrame->GetIsWatching())
	{
		return true ; 
	}

	CString szAppPath = CINIFile::GetAppPath();
	szAppPath.SetAt(szAppPath.GetLength()-1, TCHAR('\0'));
	int nPosOfSlash = szAppPath.ReverseFind(TCHAR('\\'));
	CString szAppPathParent = szAppPath.Left(nPosOfSlash);

	CString strKeyName  ; 
	strKeyName.Format("%d" ,NAME_ID) ; 
	CBcfFile File(szAppPathParent + "\\SpecialRule.bcf") ; 

	bool   bForceQuitAsAuto = File.GetKeyVal("ForceQuitAsAuto",strKeyName ,1) ; 

	if( GetStationParameter() ==GS_PLAY_GAME)
	{
		if(bForceQuitAsAuto)
		{
			if(IDOK != AFCMessageBox("您正在游戏中, 现在离开游戏将会托管处理 ，是否要离开？", "提示",AFC_YESNO)) 
			{
				return false ; 
			}
		}
		else
		{
			if(IDOK != AFCMessageBox("您正在游戏中, 现在离开将会被扣罚，是否真的要离开？", "提示",AFC_YESNO)) 
			{
				return false ; 
			}
		}
		m_pGameFrame->SendGameData(NULL , 0 ,MDM_GM_GAME_FRAME,ASS_GM_FORCE_QUIT,0);
	}

	return true;
}
///杀掉所有定时器
void CNewGameClient::KillAllGameTime(void)
{
	m_pGameFrame->KillTimer(TIME_GAME_BEGIN) ; 
	m_pGameFrame->KillTimer(TIME_PLAYER_DICE) ; 
	m_pGameFrame->KillTimer(TIME_DICE_FINISH) ; 
	m_pGameFrame->KillTimer(TIME_PLAYER_CHOISE) ;
	m_pGameFrame->KillTimer(TIME_AIM_AT_PLANE) ;
	m_pGameFrame->KillTimer(TIME_PLANE_FLY) ; 
	m_pGameFrame->KillTimer(TIME_CURSOR_ANI) ;

	return ; 
}
///显示和隐藏事件控件
void CNewGameClient::ShowOrHideUserTime(BYTE bDeskStation,int nShowMaxNum,int nShowMinNum,bool bFlag)
{	
	BYTE iView = m_pGameFrame->DeskStation2View(bDeskStation) ; 
	ITime *pTime = NULL ;
	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		pTime = dynamic_cast<ITime *>(m_pUI->GetIControlbyID(TIME_FRAME_0 +i));
		if( NULL != pTime)
		{
			pTime->SetPLay(false) ;
			pTime->SetControlVisible(false);
		}
	}
	pTime  = dynamic_cast<ITime *>(m_pUI->GetIControlbyID(TIME_FRAME_0 +iView));
	if(NULL != pTime )
	{		
		if(bFlag)
		{
			pTime->SetShowMaxNum(nShowMaxNum);
			pTime->SetShowMinNum(nShowMinNum);
			pTime->SetPLay(true);
		}
		pTime->SetControlVisible(bFlag);
	}
}
///隐藏所有定时器
void  CNewGameClient::HideAllTime()
{
	ITime *pTime = NULL ;
	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		pTime = dynamic_cast<ITime *>(m_pUI->GetIControlbyID(TIME_FRAME_0 +i));
		if(NULL != pTime)
		{
			pTime->SetPLay(false) ;
			pTime->SetControlVisible(false);
		}
	}
	return ; 
}

///设置游戏背景图标(根据自己的颜色设置背景)
void CNewGameClient::SetBaseImage(void) 
{
	///设置背景图片
	CString strBaseImage ;
	strBaseImage.Format(".\\resources\\image\\ChessBoard%d.png" ,m_iMyDeskStation) ; 
	GetControlNode(pImage ,IImage ,IMG_BASE) ;
	pImage->LoadPic(CA2W(strBaseImage)) ; 
	pImage->SetControlVisible(true) ; 

	return ; 
}
///绘制玩家的飞机情况
void CNewGameClient::DrawPlayerPlane(BYTE bDeskStation , bool bShow)
{
	UserInfoForGame UserInfo ; 
	bool bRet = m_pGameFrame->GetUserInfo(bDeskStation , UserInfo) ; 
	if(bRet == false )
	{
		return ; 
	}

	BYTE  iViewStation = GetUserRelativePos(m_iMyDeskStation , bDeskStation) ;
	MsgPrint("wysoutloginfo::自己的位置===%d , 玩家的位置%d , 得到的视图位置%d" , m_iMyDeskStation , bDeskStation ,iViewStation ) ;
	for(int  j = 0 ; j < PLAYER_PLANE_NUM  ; j++)
	{
		GetControlNode(pImg , IImage , (IMG_PLANE_0 +  iViewStation*100 + j)) ; 

		if(NULL == pImg)
		{
			return ; 
		}

		if(iViewStation != 2 )
		{
			pImg->SetMouseThough(true) ; 
		}
		else
		{
			GetControlNode(pConTrol , IImage , IMG_PLANE_2 + j) ; 
			if(NULL != pConTrol)
			{
				pImg->SetMouseMove(true) ; 
				pConTrol->SetIsHandCursor(true) ; 
			}
		}

		int  iWide   =  pImg->GetGameW() ; 
		int  iHeight =  pImg->GetGameH() ;

		int  iDirection ; 

		CPoint ptStep ; 

		BYTE  cbStep =  m_GameScene.PlaneIndex[bDeskStation][j].cbStep ; 

		int inDexCount= m_ClientLogic.GetPlanePixIndex(bDeskStation ,j ,cbStep ,m_GameScene) ;

		if(m_GameScene.PlaneIndex[bDeskStation][j].emPlaneState == emStandby)
		{
			iDirection = m_BasePath.PrvPath[bDeskStation].Park[j].enPlaneDt ; 
			ptStep = m_BasePath.PrvPath[bDeskStation].Park[j].ptPathPos  ; 
		}
		else if(m_GameScene.PlaneIndex[bDeskStation][j].emPlaneState == emTakeoff)
		{
			 iDirection = m_BasePath.PrvPath[bDeskStation].TakeOff.enPlaneDt ; 
			ptStep = m_BasePath.PrvPath[bDeskStation].TakeOff.ptPathPos ; 
		}
		else if(m_GameScene.PlaneIndex[bDeskStation][j].emPlaneState == emFlying)
		{
			iDirection =  m_BasePath.PubPath[GetMyStepIndex(enumSide(bDeskStation) ,cbStep )].enPlaneDt ; 

			ptStep  = m_BasePath.PubPath[GetMyStepIndex(enumSide(bDeskStation) ,cbStep )].ptPathPos ; 

			if(m_GameScene.PlaneIndex[bDeskStation][j].cbStep == 49)
			{
				BYTE iViewStation = GetUserRelativePos(m_iMyDeskStation ,bDeskStation) ; 

				if(0 == iViewStation)
				{
					iDirection = emDown ; 
				}
				else if(1 == iViewStation)
				{
					iDirection = emLeft ; 
				}
				else if(2 == iViewStation)
				{
					iDirection = emUp ;  
				}
				else 
				{
					iDirection = emRight ; 
				}
			}
		}
		else if(m_GameScene.PlaneIndex[bDeskStation][j].emPlaneState  == emLanding || (cbStep >= 50 &&cbStep <FINISH_PATH_STEP))
		{
			iDirection = m_BasePath.PrvPath[bDeskStation].Landing[cbStep - 50].enPlaneDt ; 
			ptStep  = m_BasePath.PrvPath[bDeskStation].Landing[cbStep - 50].ptPathPos ; 
		}
		else if(m_GameScene.PlaneIndex[bDeskStation][j].emPlaneState  == emStop)
		{
			iDirection = 8 ; 
			ptStep = m_BasePath.PrvPath[bDeskStation].Park[j].ptPathPos ;
		}
		else
		{
			///bug了
		}
		MsgPrint("wysoutinfoUI ::inDexCount==%d ,cbStep==%d", inDexCount , cbStep) ;

		ptStep.Offset(inDexCount*2 , inDexCount*2) ; 

		pImg->SetGameXY(ptStep.x , ptStep.y) ;
		pImg->SetSrcX(iDirection *iWide) ;
		pImg->SetSrcY(bDeskStation *iHeight) ;
		pImg->SetControlVisible(bShow) ; 
	}
}
///绘制飞机动画
void CNewGameClient:: DrawAimBombAni(bool bShow) 
{
	GetControlNode(pImg, IImage ,IMAGE_AIM_PLANE); 

	if(NULL  == pImg)
	{
		return ; 
	}
	pImg->SetControlVisible(bShow) ; 

	CPoint ptGetCurrentPos ; 

	ptGetCurrentPos = m_bombAni.GetCurrentPos() ; 

	pImg->SetMouseThough(true) ; 

	pImg->SetGameXY(ptGetCurrentPos.x ,ptGetCurrentPos.y ) ; 


	return ; 
}
//播放炸弹动画
void  CNewGameClient::DrawBmobAni(bool bPlay) 
{
	GetControlNode(pExAni , IExAnimate ,EX_PLANE_BOMB ) ; 
	if(NULL != pExAni)
	{
		pExAni->SetPlayState(bPlay) ; 
		pExAni->SetGameXY(m_bombAni.m_ptCurrentPos.x  - 25,m_bombAni.m_ptCurrentPos.y - 20) ;
		pExAni->SetControlVisible(bPlay) ; 
	}

	return ; 
}
///绘制飞机动画
void CNewGameClient:: DrawPlaneAni(void) 
{
	for(int i = 0 ; i<m_iAniPlaneCount ; i++)
	{
		BYTE cbDirect  = m_planeAni[i].GetCurrentDirect() ; 
		BYTE cbColor   = m_planeAni[i].GetPlaneColor() ; 

		int  IControlID = IMG_PLANE0 + GetUserRelativePos(m_planeAni[i].m_cbMySide, m_planeAni[i].m_cbMoveSide)*100 + m_planeAni[i].m_inDex ; 

		GetControlNode(pImg, IImage ,IControlID); 

		if(NULL  == pImg)
		{
			return ; 
		}
		pImg->SetControlVisible(true) ; 

		int xWide    = pImg->GetPicWidth() /9 ; 
		int yHeight  = pImg->GetPicHeight() /4 ; 

		pImg->SetSrcX(xWide *cbDirect) ; 
		pImg->SetSrcY(yHeight *cbColor) ; 

		MsgPrint("wysoutinfo::m_cbDirect==%d ,cbColor==%d ,%d ,%d" , cbDirect , cbColor ,xWide ,yHeight) ;

		CPoint ptGetCurrentPos ; 

		ptGetCurrentPos = m_planeAni[i].GetCurrentPos() ; 

		pImg->SetGameXY(ptGetCurrentPos.x ,ptGetCurrentPos.y) ; 
	}

	return ; 
}
/// 置状态
void CNewGameClient::SetStationParameter(BYTE bGameStation)
{
	m_bGameStation = bGameStation ; 
}
///获取游戏状态
BYTE CNewGameClient::GetStationParameter()
{
	return m_bGameStation;
}
/// 重设游戏状态
int CNewGameClient::ResetGameFrame(void)
{
	return 0;
}
/// 玩家进入
int CNewGameClient::GameUserCome(void)
{
	m_iMyDeskStation = m_pGameFrame->GetMyDeskStation() ; 

	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		DrawPlayerPlane(i , true) ; 
 	}

	ShowReadyLogo(true) ;

	return 0;
}
/// 玩家离开
int CNewGameClient::GameUserLeft(int nIndex)
{
	m_bReady[nIndex] = false ;

	ShowReadyLogo(true) ; 
	return 0;
}
/// 玩家断线
int CNewGameClient::GameUserOffLine(void)
{
	return 0;
}
// 是否正在游戏，由游戏实现
// 旁观玩家返回false，游戏玩家正在游戏中返回true，其它状态返回false
bool CNewGameClient::IsPlayingGame()
{
	return true;
}
///设置当前的光标显示
void  CNewGameClient::SetCurrentCursor(int iSrcPos)
{
	IXUICursor *pCursorMouse = m_pUI->GetICursor() ;
	pCursorMouse->SetCursorImage(L".\\resources\\image\\CursorDice.png");

	if(iSrcPos<0 ||iSrcPos>7)
	{		
		m_pUI->SetUICursor(32512);
		pCursorMouse->SetControlVisible(false);
	}
	else
	{		
		int iWidth  = pCursorMouse->GetCursorImageWidth()/8;
		int iHeight = pCursorMouse->GetCursorImageHeight(); 
		m_pUI->SetUICursor(32512);
		pCursorMouse->SetPointMode(1);
		//pCursorMouse->SetHideCursor(true) ; //隐藏后无法显示
		
		pCursorMouse->SetSrcX(iWidth*iSrcPos);
		pCursorMouse->SetSrcY(0);
		pCursorMouse->SetSrcW(iWidth);
		pCursorMouse->SetSrcH(iHeight);
		pCursorMouse->SetControlVisible(true);
	}
}
///处理服务端发过来的开始消息
bool CNewGameClient::OnSCBeginMessage(BeginUpgradeStruct *pBeginData)
{
	KillAllGameTime() ; 

	ResetScenceData() ; 

	m_bAutoOutTime = 0 ; 

	memset(m_iPlayerfight , 0 , sizeof(m_iPlayerfight))  ; 

	memset(m_bReady , 0 , sizeof(m_bReady))  ; 

	memset(m_bAutoOutCard,0,sizeof(m_bAutoOutCard)) ; 

	ShowReadyLogo(false) ; 

	ShowGameFinish(false) ; 

	PlayDiceAni(0,false ,false) ; 

	PlayHihtLightAni(false ,false) ; 

	ShowAutoOutCard(true) ; 

	GetControlNode(pBtn , IButton ,BN_START_GAME)->SetControlVisible(false) ;

	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		m_iPropCount[i] = 1 ; 
	}
	///更新一次所有玩家的信息
	for(int  i = 0 ; i<PLAY_COUNT ; i++)
	{
		DrawPlayerPlane(i , true) ; 
	}

	ShowFightScore(true) ; 

	ShowPlayerPropLogo(true) ;

	if(m_SoundEnginBg)
	{
		m_SoundEnginBg->setAllSoundsPaused(false) ; 

		SetGameBgSound(GAME_BG_SOUND ,true) ; 
	}



	return true ; 
}
///更新玩家界面
bool CNewGameClient::OnSCWaitDiceMessage(WaitDiceStruct *pWaiData) 
{
    KillAllGameTime() ; 

	m_cbOperater = pWaiData->cbDeskStation ; 

	m_cbCurrentStation  = WAIT_PLAYER_DICE ; 

	PlayDiceAni(0,false , false) ; 

	PlayHihtLightAni(true ,true) ; 

	if(m_iMyDeskStation == m_cbOperater)
	{
		m_pGameFrame->SetTimer(TIME_CURSOR_ANI , 200) ; 

		GetControlNode(pPropBtn , IButton , BTN_PROP1) ; 
		pPropBtn->SetControlVisible(m_iPropCount[m_cbOperater] >0 &&!m_bWatchStation) ;
		pPropBtn->SetEnable(m_iPropCount[m_cbOperater] >0) ; 

		if(m_bAutoOutCard[m_cbOperater])
		{
			m_pGameFrame->SetTimer(TIME_PLAYER_DICE ,300) ; 
		}
		else
		{
			m_pGameFrame->SetTimer(TIME_PLAYER_DICE ,m_iDiceTime*1000) ; 
		}

	}
	else
	{
		m_pGameFrame->KillTimer(TIME_CURSOR_ANI) ; 
		SetCurrentCursor(-1) ; 

		GetControlNode(pPropBtn , IButton , BTN_PROP1)->SetControlVisible(false) ; 
		pPropBtn->SetEnable(false) ;
	}

	ShowOrHideUserTime(m_cbOperater , m_iDiceTime ,0 , true) ; 

	return true ; 
}
///玩家打色子动画
bool  CNewGameClient::OnSCDiceMessage(NotifyDiceStruct *pDiceDate)
{
	KillAllGameTime() ; 
	m_pGameFrame->KillTimer(TIME_CURSOR_ANI) ; 

	if(pDiceDate->cbDeskStation == m_iMyDeskStation)
	{
	    m_pGameFrame->SetTimer(TIME_DICE_FINISH , 1100) ; 
	}

	GetControlNode(A , IButton , BTN_PROP1)->SetControlVisible(false) ;
	GetControlNode(B ,IContain , CTN_PROP)->SetControlVisible(false) ;

	m_cbDiceValue = pDiceDate->cbDiceValue ; 

	m_iPropCount[pDiceDate->cbDeskStation] = pDiceDate->cbPropCount ; 

	m_cbCurrentStation = WAIT_DICE_ANI ;
	
	if(m_iMyDeskStation == pDiceDate->cbDeskStation)
	{
		SetCurrentCursor(-1) ; 
	}

	PlayDiceAni(pDiceDate->cbDeskStation , true , true) ; 

	SetPlaySound(m_iMyDeskStation , DICE_ROLL ,false) ;

	ShowPlayerPropLogo(true) ;

	return true ; 
}
///通知客户端选择起飞的飞机
bool  CNewGameClient::OnSCChoisePlaneMessage(NotifyChoisePlane *pChoiseData) 
{
	KillAllGameTime() ; 
	m_pGameFrame->KillTimer(TIME_CURSOR_ANI) ; 

	m_cbCurrentStation = WAIT_PLAYER_CHOISE ;

	m_cbOperater = pChoiseData->cbDeskStation ; 

	
	if(m_iMyDeskStation == pChoiseData->cbDeskStation)
	{
		if(m_bAutoOutCard[m_cbOperater])
		{
			m_pGameFrame->SetTimer(TIME_PLAYER_CHOISE , 300) ; 
		}
		else
		{
			m_pGameFrame->SetTimer(TIME_PLAYER_CHOISE , m_iThinkTime *1000) ; 
		}
	}

	ShowOrHideUserTime(pChoiseData->cbDeskStation ,m_iThinkTime ,0 ,true) ; 

	return true ; 
}
///处理服务端发来的飞机飞行消息
bool CNewGameClient::OnSCPlaneFlyMessage(PlayerActiveStruct *pActiveData) 
{
    KillAllGameTime() ; 

	m_cbCurrentStation = WAIT_PLANE_FLY_ANI ;

	m_iAniPlaneCount = pActiveData->iPlaneCount ; 

	memcpy(m_iPlayerfight , pActiveData->iPlayerfight , sizeof(m_iPlayerfight)) ; 


	for(int  i = 0 ; i< m_iAniPlaneCount ; i++)
	{
		m_planeAni[i].IniData() ;
		m_planeAni[i].m_iActiveTyple =  pActiveData->PlaneActive[i].cbOperateType ; 

		BYTE   cbStepPath[52]  ;
		BYTE   cbDirect[52] ; 
		CPoint pt[52] ;

		memset(cbStepPath , 0 ,sizeof(cbStepPath)) ; 
		memset(cbDirect , 0  , sizeof(cbDirect)) ; 

		int  bDeskStation = pActiveData->PlaneActive[i].cbSide ; 
		int  iPtCount     = pActiveData->PlaneActive[i].cbStepCount ; 
		BYTE  iPlaneIndex = pActiveData->PlaneActive[i].cbIndex ; 

		for(int j = 0 ; j<iPtCount ; j++)
		{
			cbStepPath[j] = pActiveData->PlaneActive[i].cbComeByStepIndex[j] ;

			if(cbStepPath[j] == STEP_HOME)
			{
				pt[j] = m_BasePath.PrvPath[bDeskStation].Park[iPlaneIndex].ptPathPos ; 
				cbDirect[j] = m_BasePath.PrvPath[bDeskStation].Park[iPlaneIndex].enPlaneDt;
			}
			else if(cbStepPath[j] == STEP_TAKEOFF)
			{
				pt[j] = m_BasePath.PrvPath[bDeskStation].TakeOff.ptPathPos ;
				cbDirect[j] = m_BasePath.PrvPath[bDeskStation].TakeOff.enPlaneDt;
			}
			else if(cbStepPath[j] >= 50 && cbStepPath[j] <FINISH_PATH_STEP )
			{
				pt[j] = m_BasePath.PrvPath[bDeskStation].Landing[cbStepPath[j] - 50].ptPathPos ; 
				cbDirect[j] = m_BasePath.PrvPath[bDeskStation].Landing[cbStepPath[j] - 50].enPlaneDt ;

			}
			else
			{
				pt[j] = m_BasePath.PubPath[GetMyStepIndex(enumSide(bDeskStation) ,cbStepPath[j])].ptPathPos ; 
				cbDirect[j] = m_BasePath.PubPath[GetMyStepIndex(enumSide(bDeskStation) ,cbStepPath[j] )].enPlaneDt;

				if(cbStepPath[j] == 49)
				{
					BYTE iViewStation = GetUserRelativePos(m_iMyDeskStation ,bDeskStation) ; 

					if(0 == iViewStation)
					{
						cbDirect[j] = emDown ; 
					}
					else if(1 == iViewStation)
					{
						cbDirect[j] = emLeft ; 
					}
					else if(2 == iViewStation)
					{
						cbDirect[j] = emUp ;  
					}
					else 
					{
						cbDirect[j] = emRight ; 
					}
				}
				if(j<iPtCount - 1 && (cbStepPath[j]== SHORTCUT_STEP_VALUE) && (pActiveData->PlaneActive[i].cbComeByStepIndex[j+1] == SHORTCUT_OTHER_STEP))
				{
					cbDirect[j] = m_BasePath.PubPath[GetMyStepIndex(enumSide(bDeskStation) ,SHORTCUT_OTHER_STEP + 2)].enPlaneDt;
				}

			}
			MsgPrint("wysoutfxqinfo::bDeskStation ==%d ,iPtCount==%d ,cbStepPath[%d]== %d",bDeskStation , iPtCount , i,cbStepPath[i]) ; 
		}

		if(iPtCount >1) //1个点是不能飞行的
		{
			m_planeAni[i].SetPlaneData(m_iMyDeskStation , bDeskStation ,iPlaneIndex) ; 
			m_planeAni[i].SetPlaneFlyData(iPtCount, cbStepPath ,pt ,cbDirect) ;
			
		}
		else
		{
			MsgPrint("wysoutfxqinfo::不能飞行原因==点不够%d ，飞机的索引不对%d" , iPtCount,iPlaneIndex) ; 
		}
	}

	MsgPrint("wysoutfxqinfoClient::需要飞行的飞机个数%d" , m_iAniPlaneCount) ; 


	if(m_iAniPlaneCount>1)  ///检查是否有撞击的动作
	{
		if(pActiveData->PlaneActive[0].cbSide !=  pActiveData->PlaneActive[1].cbSide)  //写算法时已规定0号位置为指定飞机的索引
		{
			int  iPassPtCount = m_planeAni[0].m_iNeedByNodeCount ; 

			if(m_planeAni[0].m_cbDestInDex[m_planeAni[0].m_iNeedByNodeCount - 1]  == STEP_HOME)
			{
				iPassPtCount = m_planeAni[0].m_iNeedByNodeCount - 1 ;
			}
			m_bombAni.SetPlaneData(255 , 255 ,255) ; 
			m_bombAni.SetPlaneFlyData(iPassPtCount ,m_planeAni[0].m_cbDestInDex ,m_planeAni[0].m_ptDestPoint ,m_planeAni[0].m_cbDirect ) ;

			m_pGameFrame->SetTimer(TIME_AIM_AT_PLANE , 15) ; 
		}
		else
		{
			m_pGameFrame->SetTimer(TIME_PLANE_FLY , 15) ; 
		}
		
	}
	else if(m_iAniPlaneCount == 1 )
	{
		if(pActiveData->PlaneActive[0].cbOperateType == emShortCutActive)
		{
			SetPlaySound(m_iMyDeskStation ,PLANE_FLY ,false) ; 
		}
		m_pGameFrame->SetTimer(TIME_PLANE_FLY , 15) ; 
	}

	return true ; 
}
///飞行棋飞行任务结束
bool CNewGameClient::OnSCPlaneFlyFinish(ScenceChangeStruct *pScenceChange) 
{
	if(NULL == pScenceChange)
	{
		return false ; 
	}

	m_pGameFrame->KillTimer(TIME_PLANE_FLY) ; 

	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		for(int  j = 0 ; j<PLAY_COUNT ; j++)
		{
			m_GameScene.PlaneIndex[i][j] = pScenceChange->PlaneData[i][j]; 
		}

		DrawPlayerPlane(i ,true) ; 
	}

	return true ; 
}
///玩家游戏结束(不显示结算框)
bool CNewGameClient:: OnSCGameFinish(GameEndStruct *pGameEnd)
{
	KillAllGameTime() ; 
	memset(m_bAutoOutCard , 0 , sizeof(m_bAutoOutCard)) ; 

	CString strInfo ; 
	strInfo.Format("本局游戏结果") ;
	m_pGameFrame->InsertNormalMessage(strInfo.GetBuffer()) ; 

	for(int  i  = 0 ; i<PLAY_COUNT ; i ++)
	{
		UserInfoForGame  UserInfo ; 
		memset(&UserInfo , 0 , sizeof(UserInfo)) ;

		bool  bExist = m_pGameFrame->GetUserInfo(i , UserInfo) ; 

		if(bExist == false)
		{
			continue;
		}

		strInfo.Format("%s:得分%I64d , %s%I64d" , UserInfo.szNickName , pGameEnd->iTurePoint[i] ,m_strCoinName , pGameEnd->iChangeMoney[i]) ; 
		m_pGameFrame->InsertNormalMessage(strInfo.GetBuffer()) ; 
	}

	m_pGameFrame->SetTimer(TIME_GAME_BEGIN , 10 * 1000 ) ; 
	ShowOrHideUserTime(m_iMyDeskStation , 10 ,0 , true) ;

	GetControlNode(pBtn , IButton ,BN_START_GAME) ; 

	if(NULL != pBtn)
	{
		pBtn->SetControlVisible(!m_bWatchStation) ; 
		pBtn->SetEnable(true) ; 
	}

	if(pGameEnd->iTurePoint[m_iMyDeskStation] >0 ||pGameEnd->iChangeMoney[m_iMyDeskStation]>0)
	{
		SetPlaySound(m_iMyDeskStation ,SOUND_WIN ,false) ; 
	}
	else if(pGameEnd->iTurePoint[m_iMyDeskStation] <0||pGameEnd->iChangeMoney[m_iMyDeskStation]<0)
	{
		SetPlaySound(m_iMyDeskStation , SOUND_LOST , false) ; 
	}

	if(m_SoundEnginBg)
	{
		m_SoundEnginBg->setAllSoundsPaused(true) ; 
		m_SoundEnginBg->stopAllSounds() ; 
	}



	SetCurrentCursor(-1) ; 

	PlayHihtLightAni(false ,false) ; 

	PlayDiceAni(0 , false ,false) ; 

	ShowGameFinish(true) ; 

	ShowAutoOutCard(true) ; 

	return true ; 
}
///玩家强退结束
bool CNewGameClient:: OnSCGameCutFinish(GameCutStruct *pCutEnd)
{
	KillAllGameTime() ; 

	memset(m_bAutoOutCard , 0 , sizeof(m_bAutoOutCard)) ; 

	CString strInfo ; 

	strInfo.Format("由于玩家强退 ，游戏结束！") ;
	m_pGameFrame->InsertNormalMessage(strInfo.GetBuffer()) ; 

	strInfo.Format("本局游戏结果") ;
	m_pGameFrame->InsertNormalMessage(strInfo.GetBuffer()) ; 

	for(int  i  = 0 ; i<PLAY_COUNT ; i ++)
	{
		UserInfoForGame  UserInfo ; 
		memset(&UserInfo , 0 , sizeof(UserInfo)) ;

		bool  bExist = m_pGameFrame->GetUserInfo(i , UserInfo) ; 

		if(bExist == false)
		{
			continue;
		}

		strInfo.Format("%s:得分%I64d , %s%I64d" , UserInfo.szNickName , pCutEnd->iTurePoint[i] ,m_strCoinName ,  pCutEnd->iChangeMoney[i]) ; 
		m_pGameFrame->InsertNormalMessage(strInfo.GetBuffer()) ; 
	}

	if(m_SoundEnginBg)
	{
		m_SoundEnginBg->setAllSoundsPaused(true) ;
		m_SoundEnginBg->stopAllSounds() ; 
	}

	m_pGameFrame->SetTimer(TIME_GAME_BEGIN , 10 * 1000 ) ; 
	ShowOrHideUserTime(m_iMyDeskStation , 10 ,0 , true) ;

	GetControlNode(pBtn , IButton ,BN_START_GAME) ; 

	if(NULL != pBtn)
	{
		pBtn->SetControlVisible(!m_bWatchStation) ; 
		pBtn->SetEnable(true) ; 
	}

	SetCurrentCursor(-1) ; 

	PlayHihtLightAni(false ,false) ; 

	PlayDiceAni(0 ,false ,false) ; 

	ShowGameFinish(true) ; 

	ShowAutoOutCard(true) ; 

	return true ; 
}

///播放色子动画
void CNewGameClient::PlayDiceAni(BYTE bDeskStation , bool bPlay , bool bShow)
{
	CString strPath ; 
	strPath.Format(".\\resources\\anim\\diceAni\\DiceAnimal_%d.bani" , m_cbDiceValue) ; 
	
	GetControlNode(pExtAni , IExAnimate ,EXT_ANI_DICE) ; 
	GetControlNode(pMoveAni , IMoveAction , MOVE_DICE_ANI) ; 
	if(NULL == pExtAni || NULL == pMoveAni)
	{
		return ; 
	}

	if(bPlay == true)
	{
		srand((unsigned) time(NULL) ) ; 

		int  iRandPos1 = rand()%2 +1 ; 
		int  iRandPos2 = rand()%4 +1;

		pMoveAni->SetPlayState(true) ; 
		pMoveAni->SetControlVisible(true) ; 

		pMoveAni->SetStartP(m_BasePath.PubPath[GetMyStepIndex(enumSide(bDeskStation) ,iRandPos1)].ptPathPos ) ; 
		pMoveAni->SetEndP(m_BasePath.PubPath[GetMyStepIndex(enumSide((bDeskStation + 2)%PLAY_COUNT) ,iRandPos2)].ptPathPos) ; 
		pMoveAni->SetTotalMoveTime(800) ; 

		pExtAni->SetExtFilePath(CA2W(strPath)) ; 
		pExtAni->LoadFromFile();
		pExtAni->SetControlVisible(bShow);
		pExtAni->SetPlayState(true);				
		pExtAni->SetIsLoop(false);
		pExtAni->SetMouseThough(true) ; 
		pExtAni->SetPlayTotalTime(750) ; 
	}
	else
	{
		if(bShow == true)
		{
			pExtAni->SetShowFrame(pExtAni->GetFrameNum()-1);	
		}
		pExtAni->SetPlayState(false);	
		pExtAni->SetControlVisible(bShow);
		pExtAni->SetMouseThough(true) ;
	}
}
///高亮状态
void CNewGameClient::PlayHihtLightAni(bool bPlay ,bool bShow)
{
	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		GetControlNode(pExtAni , IExAnimate , (i+EX_ANI_HIGTLIGHT)) ; 
		pExtAni->SetPlayState(false) ; 
		pExtAni->SetControlVisible(false) ; 
	}
	if(255 == m_cbOperater)
	{
		return ; 
	}

	BYTE iViewStation = m_pGameFrame->DeskStation2View(m_cbOperater) ; 

	GetControlNode(pExtAnimal,IExAnimate,(EX_ANI_HIGTLIGHT + iViewStation))->SetControlVisible(bShow) ; 
	pExtAnimal->SetPlayState(bPlay) ; 
	pExtAnimal->SetIsLoop(true) ; 
	pExtAnimal->SetMouseThough(true) ;
}

///显示玩家准备图标
void CNewGameClient::ShowReadyLogo(bool bShow) 
{
	for(int  i = 0 ; i <PLAY_COUNT ; i++)
	{
		UserInfoForGame UserInfo ; 
		bool bExist = m_pGameFrame->GetUserInfo(i , UserInfo) ; 
		
		int  iView = GetUserRelativePos(m_iMyDeskStation , i) ; 
		
		GetControlNode(pImage , IImage ,IMG_READY_FLAG + iView) ; 
		if(NULL != pImage)
		{
			pImage->SetControlVisible(bShow &&m_bReady[i] &&bExist) ; 
		}
	}
}
///显示玩家道具图标
void CNewGameClient::ShowPlayerPropLogo(bool bshow)
{
	for(int  i = 0 ; i <PLAY_COUNT ; i++)
	{
		int  iView = GetUserRelativePos(m_iMyDeskStation , i) ; 
		GetControlNode(pImage , IImage ,IMG_PROP_FLAG + iView) ; 
		if(NULL != pImage)
		{
			pImage->SetControlVisible(bshow &&m_iPropCount[i]) ; 
		}
	}

}
///显示目的地图片
void CNewGameClient::ShowDestineImg(int  cbStep  ,BYTE inDex , bool bShow) 
{
	GetControlNode(pImage , IImage , IMG_NEXT_STEP) ; 
	if(NULL == pImage)
	{
		return ; 
	}
	CPoint ptPoint; 
	enumDirection iDirection ; 

	if(cbStep == STEP_HOME)
	{
		ptPoint = m_BasePath.PrvPath[m_iMyDeskStation].Park[inDex].ptPathPos ; 
		iDirection = m_BasePath.PrvPath[m_iMyDeskStation].Park[inDex].enPlaneDt;
	}
	else if(cbStep == STEP_TAKEOFF)
	{
		ptPoint = m_BasePath.PrvPath[m_iMyDeskStation].TakeOff.ptPathPos ;
		iDirection = m_BasePath.PrvPath[m_iMyDeskStation].TakeOff.enPlaneDt;
	}
	else if(cbStep >= 50 && cbStep <FINISH_PATH_STEP )
	{
		ptPoint = m_BasePath.PrvPath[m_iMyDeskStation].Landing[cbStep - 50].ptPathPos ; 
		iDirection = m_BasePath.PrvPath[m_iMyDeskStation].Landing[cbStep - 50].enPlaneDt ;

	}
	else
	{
		ptPoint = m_BasePath.PubPath[GetMyStepIndex(enumSide(m_iMyDeskStation) ,cbStep)].ptPathPos ; 
		iDirection = m_BasePath.PubPath[GetMyStepIndex(enumSide(m_iMyDeskStation), cbStep)].enPlaneDt;
	}

	int xSrc =  pImage->GetPicWidth() /8 ; 
	int ySrc = pImage->GetPicHeight() ; 

	pImage->SetControlVisible(bShow &&cbStep >=0) ; 
	pImage->SetGameXY(ptPoint.x +10, ptPoint.y +10) ;
	pImage->SetSrcX(xSrc *iDirection) ; 
	pImage->SetMouseThough(true) ;
}
///显示玩家的战绩
void CNewGameClient::ShowFightScore(bool bShow) 
{
	for(int i = 0 ; i<PLAY_COUNT ; i++)
	{
		UserInfoForGame UserInfo ; 
		memset(&UserInfo , 0 , sizeof(UserInfo)) ; 
		bool bExist = m_pGameFrame->GetUserInfo( i  , UserInfo) ;  
		if(false == bExist)
		{
			continue; 
		}

		int  iView = GetUserRelativePos(m_iMyDeskStation  , i); 
		GetControlNode(pText , IText , STATIC_TEXT_NAME_0  + iView) ; 

		if(NULL == pText)
		{
			break; 
		}
		pText->SetControlVisible(bShow) ;  
		pText->SetText(CA2W(UserInfo.szNickName)) ;
	}

	GetControlNode(pText0 , IText , STATIC_TEXT_SCORE_0) ; 
	if(NULL == pText0)
	{
		return ; 
	}

	int  iFightCount = ((m_iMyDeskStation%2 == 0)?m_iPlayerfight[0]:m_iPlayerfight[1]) ;

	CString strInfo ; 
	strInfo.Format("击落飞机:%d架",iFightCount ) ; 
	pText0->SetText(CA2W(strInfo)) ; 
	pText0->SetControlVisible(bShow) ; 

	GetControlNode(pText1 , IText , STATIC_TEXT_SCORE_1) ; 
	if(NULL == pText1)
	{
		return ; 
	}

	iFightCount = ((m_iMyDeskStation%2 != 0)?m_iPlayerfight[0]:m_iPlayerfight[1]) ;

	strInfo.Format("击落飞机:%d架",iFightCount) ; 
	pText1->SetText(CA2W(strInfo)) ;
	pText1->SetControlVisible(bShow) ; 

	return ;
}
///显示游戏结束标识
void CNewGameClient::ShowGameFinish(bool  bShow) 
{
	GetControlNode(pImage , IImage , IMAGE_GAME_OVER) ; 
	if(NULL != pImage)
	{
		pImage->SetControlVisible(bShow) ; 
	}
}
///玩家设置游戏信息
int  CNewGameClient::UserSetGameInfo(bool bSoundEnable,bool bSoundBgEnable,bool bWatchEnable,bool bShow)
{
	IContain  *pConTain = dynamic_cast<IContain *>(m_pUI->GetIControlbyID(CONTAIN_GAME_SET));
	if(NULL!=pConTain )
	{
		OutputDebugString("11900800 ::UserSetGameInfo") ; 
		pConTain->SetControlVisible(bShow); 
	}

	IRadioButton *pRadioBtnVoice = dynamic_cast<IRadioButton *>(m_pUI->GetIControlbyID(BTN_SET_VOICE)) ;
	IRadioButton *pRadioBtnVoicebg = dynamic_cast<IRadioButton *>(m_pUI->GetIControlbyID(BTN_SET_BG_VOICE)) ;
	IRadioButton *pRadioBtnWatch = dynamic_cast<IRadioButton *>(m_pUI->GetIControlbyID(BTN_SET_WATCH)) ; 
	if(NULL != pRadioBtnVoice && NULL!= pRadioBtnWatch && NULL != pRadioBtnVoicebg)
	{
		pRadioBtnVoice->SetIsSelect(bSoundEnable) ; 
		pRadioBtnVoice->SetControlVisible(bShow);

		pRadioBtnVoicebg->SetIsSelect(bSoundBgEnable) ; 
		pRadioBtnVoicebg->SetControlVisible(bShow);

		pRadioBtnWatch->SetIsSelect(bWatchEnable) ; 
		pRadioBtnWatch->SetControlVisible(bShow);
	}	
	return 0 ;
}
///设置托管方式
void CNewGameClient::SetAutoStation(BYTE bDeskStation,bool bAtuoOrCancel) 
{	
	m_bAutoOutCard[bDeskStation] = bAtuoOrCancel ; 

	if(bAtuoOrCancel == true)
	{
		if(bDeskStation == m_cbOperater && m_cbCurrentStation == WAIT_PLAYER_DICE)
		{
			UserAutoDice(); 
		}
		else if(bDeskStation == m_cbOperater && m_cbCurrentStation == WAIT_PLAYER_CHOISE)
		{
			UserAutoChoisePlane() ; 
		}
	}
	return ; 
}
///显示托管标志
void CNewGameClient::ShowAutoOutCard(bool bShow)
{
	BYTE iMyDeskStation = m_pGameFrame->GetMyDeskStation() ; 
	IButton *pBtnAtuo       = dynamic_cast<IButton *>(m_pUI->GetIControlbyID(BTN_TRUSTEE)) ; 
	IButton *pBtnAtuoCancel = dynamic_cast<IButton *>(m_pUI->GetIControlbyID(BTN_TRUSTEE_CANCEL)) ; 
	if(NULL !=pBtnAtuo && NULL != pBtnAtuoCancel)
	{
		if(true == m_bAutoOutCard[iMyDeskStation])
		{
			pBtnAtuo->SetControlVisible(false) ; 
			pBtnAtuoCancel->SetControlVisible(!m_bWatchStation) ;
		}
		else
		{
			pBtnAtuo->SetControlVisible(!m_bWatchStation) ; 
			pBtnAtuoCancel->SetControlVisible(false) ;
		}
	}
	for (int i = 0 ; i<PLAY_COUNT ; i++)
	{
		BYTE iView = m_pGameFrame->DeskStation2View(i) ; 
		IImage *pImage = dynamic_cast<IImage *>(m_pUI->GetIControlbyID(IMG_TRUSTEE1 + iView)) ; 
		if(NULL != pImage)
		{
			if(true == m_bAutoOutCard[i])
			{
				pImage->SetControlVisible(bShow) ; 
			}
			else
			{
				pImage->SetControlVisible(false) ; 
			}			
		}
	}
}
///用户托管打色子
void CNewGameClient::UserAutoDice(void) 
{
	m_pGameFrame->KillTimer(TIME_PLAYER_DICE) ; 

	if(m_cbCurrentStation != WAIT_PLAYER_DICE)
	{
		return ; 
	}
	if(m_iMyDeskStation != m_cbOperater)
	{
		return  ; 
	}

	GetControlNode(pContain , IContain ,CTN_PROP) ; 
	if(NULL != pContain)
	{
		return  ; 
	}

	pContain->SetControlVisible(false) ; 

	m_pGameFrame->SendGameData(ASS_APPLY_DICE ,NULL , 0 ) ; 

	return ; 
}
///用户托管选择棋子
void  CNewGameClient::UserAutoChoisePlane(void)
{
	if(m_cbCurrentStation != WAIT_PLAYER_CHOISE)
	{
		return ; 
	}

	if(m_iMyDeskStation != m_cbOperater)
	{
		return  ; 
	}

	m_pGameFrame->KillTimer(TIME_PLAYER_CHOISE) ; 

	PlayerChoiseStruct ChoiseData ; 
	ChoiseData.cbDeskStation = m_iMyDeskStation ; 
	ChoiseData.inDexPlane = m_ClientLogic.FindOnePlaneToFly(m_iMyDeskStation , m_cbDiceValue , m_GameScene) ; 
	m_pGameFrame->SendGameData(&ChoiseData ,sizeof(ChoiseData) ,MDM_GM_GAME_NOTIFY ,ASS_PLAYER_CHOISE_PLANE ,0) ; 
	return ; 
}
///  播放音效
void CNewGameClient::SetPlaySound(BYTE iDeskStation,int SoundID, bool bISLoop)
{
	if(!m_SoundEngine)
	{
		return ;
	}
	if(!m_bSoundPlay)
	{
		return ;
	}

	CString  folder ;
	CString  filename;
	char szFileName[MAX_PATH];
	memset(szFileName,0,sizeof(szFileName)) ; 

	folder.Format("sound/Gamesound/") ; 

	switch(SoundID)
	{
	case  PLANE_ARRIVE:
		{
			filename.Format("Arrive") ; 
			break;
		}
	case BOMB_SOUND:
		{
			filename.Format("Bomb") ;
			break;
		}
	case DICE_ROLL:
		{
			filename.Format("diceroll") ;
			break;
		}
	case PLANE_FLY:
		{
			filename.Format("fly") ;
			break;
		}
	case PLANE_TAKEOFF:
		{
			filename.Format("takeoff") ;
			break;
		}
	case TIME_OUT:
		{
			filename.Format("timeout") ;
			break;
		}
	case WIND_SOUND:
		{
			filename.Format("wind");
			break;
		}
	case AIM_AT_PLANE:
		{
			filename.Format("AimAtPlane") ; 
			break;
		}
	case  ARRIVE_HOME:
		{
			filename.Format("ArriveHome") ; 
			break;
		}
	case  SOUND_WIN:
		{
			filename.Format("win") ; 
			break;
		}
	case  SOUND_LOST:
		{
			filename.Format("lost") ; 
			break;
		}
	default:
		{
			return ;
		}
	}

	wsprintf(szFileName,"%s%s%s",folder,filename,".ogg");

	m_SoundEngine->play2D(szFileName,bISLoop);

	return ; 
}
///  播放音效
void CNewGameClient::SetGameBgSound(int SoundID, bool bISLoop)
{
	if(!m_SoundEnginBg)
	{
		return ;
	}
	if(!m_bSoundBgPlay)
	{
		return ;
	}

	CString  folder ;
	CString  filename;
	char szFileName[MAX_PATH];
	memset(szFileName,0,sizeof(szFileName)) ; 

	folder.Format("sound/Gamesound/") ; 

	switch(SoundID)
	{
	case  GAME_BG_SOUND:
		{
			filename.Format("BgSound") ; 
			break;
		}
	default:
		{
			return ;
		}
	}

	wsprintf(szFileName,"%s%s%s",folder,filename,".ogg");

	m_SoundEnginBg->play2D(szFileName,bISLoop);

	return ; 
}
