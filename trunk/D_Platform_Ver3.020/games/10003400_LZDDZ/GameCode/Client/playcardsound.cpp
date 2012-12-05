#include"stdafx.h"
#include "playcardsound.h"
#include "..\GameMessage\upgradelogic.h"
#pragma comment(lib,"vfw32.lib")

CUpGradeGameLogic		m_Logic;					//升级逻辑

//播放Mp3音乐
HWND PlayCardMusic(TCHAR FileName[],HWND hParent)
{	
	HWND hmciwnd;
	//hmciwnd = MCIWndCreate(this->m_hWnd,AfxGetInstanceHandle(),WS_CHILD,FileName);
	hmciwnd=MCIWndCreate(hParent,AfxGetInstanceHandle(),WS_CHILD|MCIWNDF_NOMENU|MCIWNDF_NOOPEN|MCIWNDF_NOPLAYBAR|MCIWNDF_NOERRORDLG,FileName);
	if(hmciwnd)
		MCIWndPlay(hmciwnd);	
	return hmciwnd;
}
/*
播放场景声音
parameter iSenceSound 场景声音
parameter isBoy		性别
parameter hParent    父窗口
parameter iVal		播放指定背景音乐(未设置此值,随机播放)
*/
//播放场景声音
HWND SetSceneSound(BYTE iSceneSound,HWND hParent,BOOL IsBoy,int iVal)
{
	TCHAR str[100]="";
	TCHAR filename[MAX_PATH];//path[MAX_PATH];
	CString s=CBcfFile::GetAppPath ();/////本地路径
	CBcfFile f( s + "cardsound.bcf");
	CString key = TEXT("cardscene");
	//	TCHAR path[MAX_PATH];
	CString folder,extendname,name;
	folder=f.GetKeyVal(key,"folder","music\\cardwav\\scene\\");
	extendname=f.GetKeyVal(key,"extendname",".mp3");

	//	TCHAR filename[MAX_PATH],str[100]="";
	srand(GetCurrentTime());
	int count;
	switch(iSceneSound)
	{
	case SOUND_WIN://胜利
		if(IsBoy)
		{	
			count = f.GetKeyVal(key,"bwincount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"b(win%d)",rand()%count);
		}
		else
		{
			count = f.GetKeyVal(key,"gwincount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"g(win%d)",rand()%count);
		}
		break;
	case SOUND_LOSE://失败
		if(IsBoy)
		{
			count = f.GetKeyVal(key,"blosecount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"b(lose%d)",rand()%count);
		}
		else
		{
			count = f.GetKeyVal(key,"glosecount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"g(lose%d)",rand()%count);
		}
		break;
	case SOUND_WAITING://等待
		if(IsBoy)
		{
			count = f.GetKeyVal(key,"bwaitcount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"b(wait%d)",rand()%count);
		}
		else
		{
			count = f.GetKeyVal(key,"gwaitcount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"g(wait%d)",rand()%count);
		}
		break;
	case SOUND_ERROR://出牌出错了
		if(IsBoy)
		{
			count = f.GetKeyVal(key,"berrorcount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"b(error%d)",rand()%count);
		}
		else
		{
			count = f.GetKeyVal(key,"gerrorcount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"g(error%d)",rand()%count);
		}
		break;
	case SOUND_READY://单人准备
		if(IsBoy)
		{
			count = f.GetKeyVal(key,"breadycount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"b(ready%d)",rand()%count);
		}
		else
		{
			count = f.GetKeyVal(key,"greadycount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"g(ready%d)",rand()%count);
		}
		break;
	case SOUND_START://四家准备开始
		{
			if(IsBoy)
			{
				count = f.GetKeyVal(key,"bstartcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"b(start%d)",rand()%count);
			}
			else
			{
				count = f.GetKeyVal(key,"gstartcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"g(start%d)",rand()%count);
			}
			break;
		}
	case SOUND_START_OUT_CARD://开始游戏(随机)
		if(IsBoy)
		{
			count = f.GetKeyVal(key,"bstartoutcardcount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"b(startoutcard%d)",rand()%count);
		}
		else
		{
			count = f.GetKeyVal(key,"gstartcount",10);
			if(count == 0)
				return NULL;
			wsprintf(str,"g(start%d)",rand()%count);
		}
		break;
	case SOUND_CALL_SCORE://叫分
		{
			
			if(IsBoy)
			{
				wsprintf(str,"b(jiaofen%d)",iVal);
			}
			else
			{
				wsprintf(str,"g(jiaofen%d)",iVal);
			}
			if ( iVal == 30 )
			{
				extendname=f.GetKeyVal(key,"extendname",".wav");
				name=f.GetKeyVal(key,str,str);
				wsprintf(filename,"%s%s%s",folder,name,extendname);

	
				return 	PlayCardMusic(filename,hParent);

			}
			
			break;
		}
	case SOUND_OUT_CARD_FINISH://出完牌
		{
			if(IsBoy)
			{
				count = f.GetKeyVal(key,"boutcardfinishcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"b(outcardfinish%d)",rand()%count);
			}
			else
			{
				count = f.GetKeyVal(key,"goutcardfinishcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"g(outcardfinish%d)",rand()%count);
			}
			break;
		}
	case SOUND_FRIEND_APPEAR://盟友出現
		{
			if(IsBoy)
			{
				count = f.GetKeyVal(key,"bfriendcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"b(friend%d)",rand()%count);
			}
			else
			{
				count = f.GetKeyVal(key,"gfriendcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"g(friend%d)",rand()%count);
			}
			break;
		}
	case SOUND_USER_RUNAWARY:	//逃跑
		{
			if(IsBoy)
			{
				count = f.GetKeyVal(key,"brunawarycount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"b(runawary%d)",rand()%count);
			}
			else
			{
				count = f.GetKeyVal(key,"grunawarycount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"g(runawary%d)",rand()%count);
			}
			break;
		}
	case SOUND_USER_LEFT:	//有人离开
		{
			if(IsBoy)
			{
				count = f.GetKeyVal(key,"bleftcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"b(left%d)",rand()%count);
			}
			else
			{
				count = f.GetKeyVal(key,"gleftcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"g(left%d)",rand()%count);
			}
			break;
		}
	case SOUND_GIVE_BACK://埋底
		{
			if(IsBoy)
			{
				count = f.GetKeyVal(key,"bgivebackcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"b(giveback%d)",rand()%count);
			}
			else
			{
				count = f.GetKeyVal(key,"ggivebackcount",10);
				if(count == 0)
					return NULL;
				wsprintf(str,"g(giveback%d)",rand()%count);
			}
			break;
		}
	default:
		if(IsBoy)
			wsprintf(str,"b(sence_0)");
		else
			wsprintf(str,"g(sence_0)");
		break;
	}
	name=f.GetKeyVal(key,str,str);
	wsprintf(filename,"%s%s%s",folder,name,extendname);
	return 	PlayCardMusic(filename,hParent);
}

/*
设置通用声音
时间警告
提示无效
发牌
*/
//游戏声音
BOOL SetPlaySound(BYTE bSoundType)
{
	CString s=CBcfFile::GetAppPath ();/////本地路径
	CBcfFile f( s + "cardsound.bcf");
	CString key = TEXT("system");
	CString folder,filename;
	folder=f.GetKeyVal(key,"folder","music\\cardwav\\");
	TCHAR fi[MAX_PATH+1];
	switch(bSoundType)
	{
	case SOUND_WARNING://警告
		{
			filename = f.GetKeyVal(key,"warning","warning");
			break;
		}
	case SOUND_INVALIDATE://无效
		{
			filename = f.GetKeyVal(key,"invalidate","invalidate");
			break;
		}
	case SOUND_SEND_CARD://发牌
		{
			filename = f.GetKeyVal(key,"sendcard","sendcard");
			break;
		}
	case  SOUND_OUT_CARD_DEF://出牌
		{
			filename = f.GetKeyVal(key,"outcarddef","outcarddef");
			break;
		}
	case SOUND_OUT_CARD_BOMB://炸弹
		{
			filename = f.GetKeyVal(key,"bomb","bomb");
			break;
		}
	case SOUND_OUT_CARD_PASS://不要
		{
			filename = f.GetKeyVal(key,"pass","pass");
			break;
		}
	case SOUND_START_DEF://开始
		{
			filename = f.GetKeyVal(key,"startdef","startdef");
			break;
		}
	case SOUND_GAME_OVER://游戏结束
		{
			filename = f.GetKeyVal(key,"gameover","gameover");
			break;
		}
	case SOUND_ADD_DOUBLE://加棒
		{
			filename = f.GetKeyVal(key,"adddouble","adddouble");
			break;
		}
	case SOUND_ROB_NT://抢地主
		{
			filename = f.GetKeyVal(key,"robnt","robnt");
			break;
		}

	case SOUND_WIN:
		{
			filename = f.GetKeyVal(key,"win","win");
			break;
		
		}
	case SOUND_LOSE:
		{
			filename = f.GetKeyVal(key,"lost","lost");
			break;
			
		}
	}
	wsprintf(fi,"%s%s%s",folder,filename,".wav");
	::PlaySound(fi,NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP|SND_NOWAIT|SND_NODEFAULT);
	return true;
}

//斗地主播放mp3声音 (090402b1 JJ)
HWND SetDdzSound(BYTE bSoundType, HWND hParent, BOOL IsBoy)
{
	if (hParent == NULL)
	{
		return NULL;
	}
	CString s=CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s + "cardsound.ini");
	CString key = TEXT("ddz");
	CString folder, filename;
	CString strRandnum, extendname;

	folder = f.GetKeyVal(key,"folder","music\\cardwav\\ddz\\");
	extendname = f.GetKeyVal(key,"externname",".mp3");
	if (IsBoy)
	{
		folder += "boy\\";
	}
	else
	{
		folder += "girl\\";
	}
	strRandnum.Format("%d", rand()%2);
	TCHAR fi[MAX_PATH+1]={0};
	switch(bSoundType)
	{
	case SOUND_OUT_CARD_BOMB://炸弹
		{
			filename = f.GetKeyVal(key,"bomb","bomb");
			break;
		}
	case SOUND_OUT_CARD_KINGBOMB://王炸
		{
			filename = f.GetKeyVal(key,"kingbomb","kingbomb");
			break;
		}
	case SOUND_OUT_CARD_SAN://三张
		{
			filename = f.GetKeyVal(key,"san","san");
			break;
		}
	case SOUND_OUT_CARD_SANDAIY://三带一
		{
			filename = f.GetKeyVal(key,"sandaiy","sandaiy");
			break;
		}
	case SOUND_OUT_CARD_SANDAID://三带一对
		{
			filename = f.GetKeyVal(key,"sandaid","sandaid");
			break;
		}
	case SOUND_OUT_CARD_SIDAIE://四带二
		{
			filename = f.GetKeyVal(key,"sidaie","sidaie");
			break;
		}
	case SOUND_OUT_CARD_SIDAID://四带2对
		{
			filename = f.GetKeyVal(key,"sidaid","sidaid");
			break;
		}
	case SOUND_OUT_CARD_PLANE://飞机
		{
			filename = f.GetKeyVal(key,"plane","plane");
			break;
		}
	case SOUND_OUT_CARD_LIANDUI://连对
		{
			filename = f.GetKeyVal(key,"liandui","liandui");
			break;
		}
	case SOUND_OUT_CARD_SHUNZI://顺子
		{
			filename = f.GetKeyVal(key,"shunzi","shunzi");
			break;
		}
	case SOUND_OUT_CARD_PASS://不出
		{
			filename = f.GetKeyVal(key,"pass","pass");
			strRandnum.Format("%d", rand()%3);
			filename += strRandnum;
			break;
		}
	case SOUND_OUT_CARD:	//管上
		{
			filename = f.GetKeyVal(key,"yao","yao");
			strRandnum.Format("%d", rand()%3);
			filename += strRandnum;
			break;
		}
	case SOUND_ADD_DOUBLE: //加倍
		{
			filename = f.GetKeyVal(key,"double","double");
			break;
		}
	case SOUND_ADD_DOUBLE_NOT: //不加倍
		{
			filename = f.GetKeyVal(key,"doublenot","doublenot");
			break;
		}
	case SOUND_ROB_NT: //抢地主
		{
			filename = f.GetKeyVal(key,"rob","rob");
			strRandnum.Format("%d", rand()%3);
			filename += strRandnum;
			break;
		}
	case SOUND_ROB_NT_NOT: //不抢地主
		{
			filename = f.GetKeyVal(key,"robnot","robnot");
			break;
		}
	case SOUND_SHOW_CARD: //明牌
		{
			filename = f.GetKeyVal(key,"showcard","showcard");
			break;
		}
	}

	wsprintf(fi,"%s%s%s",folder,filename,extendname);
	if (!CINIFile::IsFileExist(fi))
	{
		return NULL;
	}
	return 	PlayCardMusic(fi,hParent);
}
//斗地主播放单张和对子声音 (090402b1 JJ)
HWND SetDdzCardSound(BYTE cardNum, HWND hParent, BYTE count, BOOL bFirstOut, BOOL IsBoy)
{
	if (hParent == NULL || count > 2 || count < 0)
	{
		return NULL;
	}
	CString s=CINIFile::GetAppPath ();/////本地路径
	CINIFile f( s + "cardsound.ini");
	CString key = TEXT("cardtype");
	CString folder, filename;
	CString strCardnum, extendname;
	srand(GetTickCount());
	int nSayYao = rand()%2; //根据随机值随机说管上啊大你什么的 定个50%的几率
	folder = f.GetKeyVal(key,"folder","music\\cardwav\\cardtype\\");
	extendname = f.GetKeyVal(key,"externname",".mp3");
	if (IsBoy)
	{
		folder += "boy\\";
	}
	else
	{
		folder += "girl\\";
	}

	TCHAR fi[MAX_PATH+1]={0};

	if (nSayYao == 0 && bFirstOut == FALSE)
	{
		filename.Format("yao%d", rand()%3);
		wsprintf(fi, _T("%s%s%s"), folder, filename, extendname);
		return 	PlayCardMusic(fi,hParent);
	}

	if (cardNum == 0x4E)
	{
		filename = "sKing";
	} 
	else if (cardNum == 0x4F)
	{
		filename = "bKing";
	} 
	else
	{
		strCardnum.Format("%d", cardNum);
		if (count == 1)
		{	
			filename = strCardnum;
		}
		else if (count == 2)
		{
			filename = strCardnum + strCardnum;
		}
	}

	wsprintf(fi,"%s%s%s",folder,filename,extendname);
	if (!CINIFile::IsFileExist(fi))
	{
		return NULL;
	}
	return 	PlayCardMusic(fi,hParent);
}

//用户押注声音(专为梭哈准备)
BOOL SetNoteSound(BYTE bNoteStyle,BOOL bIsBoy)
{
	TCHAR str[MAX_PATH+1]="";
	TCHAR filename[MAX_PATH];//path[MAX_PATH];
	CString s=CBcfFile::GetAppPath ();/////本地路径
	CBcfFile f( s + "cardsound.bcf");
	CString key = TEXT("shnote");
	//	TCHAR path[MAX_PATH];
	CString folder,extendname,name;
	folder=f.GetKeyVal(key,"folder","music\\cardwav\\sh\\");
	extendname=f.GetKeyVal(key,"extendname",".wav");
	TCHAR Val[50];
	srand(GetCurrentTime());
	int count =1;//f.GetKeyVal(key,"count",1);
	switch(bNoteStyle)
	{
	case TYPE_SHUTTLE:
		{	
			wsprintf(Val,"%c(show%d)",bIsBoy?'b':'g',rand()%count);
			name = f.GetKeyVal(key,Val,Val);
			break;
		}
	case TYPE_FOLLOW:
		{
			wsprintf(Val,"%c(follow%d)",bIsBoy?'b':'g',rand()%count);
			name = f.GetKeyVal(key,Val,Val);
			break;
		}
	case TYPE_ADD:
		{
			wsprintf(Val,"%c(add%d)",bIsBoy?'b':'g',rand()%count);
			name = f.GetKeyVal(key,Val,Val);
			break;
		}
	case TYPE_NOTE:
		{
			wsprintf(Val,"%c(note%d)",bIsBoy?'b':'g',rand()%count);
			name = f.GetKeyVal(key,Val,Val);
			break;
		}
	case TYPE_GIVE_UP:
		{
			wsprintf(Val,"%c(pass%d)",bIsBoy?'b':'g',rand()%count);
			name = f.GetKeyVal(key,Val,Val);
			break;
		}	
	default:
		{
			wsprintf(str,"%c(def)",bIsBoy?'b':'g');
			name = f.GetKeyVal(key,Val,Val);
			break;
		}	
	}
	wsprintf(filename,"%s%s%s",folder,name,extendname);

	::PlaySound(filename,NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP|SND_NOWAIT|SND_NODEFAULT);
	return true;
}

/*
parameter iCardList 出牌队例
parameter iCardCount 出牌数量
parameter IsBoy		性别
parameter IsFirst	是否第一个出(如不支持牌数字,后面所出的全部调用默认的声音如管上,大上)
*/
//设置出牌牌型声音(专为四冲准备
HWND SetOutCardTypeSound(BYTE iCardList[],int iCardCount,HWND hParent,BOOL IsBoy,BOOL IsFirest )
{
/*	//int cardshape = m_Logic.GetCardShape(iCardList,iCardCount);
	int cardstart,cardend;
	int bSuperNum = 0;
	TCHAR str[100]="";
	TCHAR filename[MAX_PATH];
	CString s=CINIFile::GetAppPath ();/////本地路径
	CBcfFile f( s + "cardsound.bcf");
	CString key = TEXT("sysc");
	TCHAR Val[50];
	CString folder,extendname,name;
	folder=f.GetKeyVal(key,"folder","music\\cardwav\\sysc\\");
	extendname=f.GetKeyVal(key,"extendname",".mp3");

	switch(iCardCount)
	{
	case 0://pass
		{
			wsprintf(str,"%c(pass)",IsBoy?'b':'g');	
			break;
		}
	case 1://单张至16张
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		{
			wsprintf(Val,"%c(%d_supernum)",IsBoy?'b':'g',iCardCount);
			bSuperNum=f.GetKeyVal(key,Val,0);
			if(!bSuperNum)
				cardstart = 0;
			else
				cardstart = m_Logic.SearchMinCardNum(iCardList,iCardCount);
			wsprintf(str,"%c(%d_%d)",IsBoy?'b':'g',iCardCount,(cardstart)?cardstart:(cardstart+IsFirest));
			break;
		}
	default:
		wsprintf(str,"%c(def)",IsBoy?'b':'g');
		break;
	}
	name=f.GetKeyVal(key,str,str);
	wsprintf(filename,"%s%s%s",folder,name,extendname);

	return 	PlayCardMusic(filename,hParent);*/
	return NULL;
}

//设置出牌类型(专为斗地主准备)
/*
parameter iCardList 出牌队例
parameter iCardCount 出牌数量
parameter IsBoy		性别
parameter IsFirst	是否第一个出(如不支持牌数字,后面所出的全部调用默认的声音如管上,大上)
*/
/*
//设置出牌牌型声音
HWND SetOutCardTypeSound(BYTE iCardList[],int iCardCount,HWND hParent,BOOL IsBoy,BOOL IsFirest )
{
	int cardshape = m_Logic.GetCardShape(iCardList,iCardCount);
	int cardstart,cardend;
	//	TCHAR filename[MAX_PATH],
	TCHAR str[100]="";
	TCHAR filename[MAX_PATH];//path[MAX_PATH];
	CString s=CINIFile::GetAppPath ();/////本地路径
	CBcfFile f( s + "cardsound.bcf");
	CString key = TEXT("type0");
	//	TCHAR path[MAX_PATH];
	CString folder,extendname,name;
	folder=f.GetKeyVal(key,"folder","music\\cardwav\\type0\\");
	extendname=f.GetKeyVal(key,"extendname",".mp3");

	switch(cardshape)
	{
	case UG_ERROR_KIND://pass
		{
			if(IsBoy)
				wsprintf(str,"b(pass)");
			else
				wsprintf(str,"g(pass)");
			break;
		}
	case UG_ONLY_ONE:
		{
			cardstart = m_Logic.GetCardNum(iCardList[0]);
			if(IsBoy)
			{
				wsprintf(str,"b(1_%d)",cardstart);
			}
			else
				wsprintf(str,"g(1_%d)",cardstart);
			break;
		}
	case UG_DOUBLE:
		{
			cardstart = m_Logic.GetCardNum(iCardList[0]);
			if(IsBoy)
			{
				wsprintf(str,"b(2_%d)",cardstart);
			}
			else
				wsprintf(str,"g(2_%d)",cardstart);
			break;
		}
	case UG_THREE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(three)");
				//wsprintf(str,"b(2_%d)",cardstart);//預留
			}
			else
				wsprintf(str,"g(three)");
			break;
		}
	case UG_THREE_ONE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(three_one)");
			}
			else
				wsprintf(str,"g(three_one)");
			break;
		}
	case UG_THREE_TWO:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(three_two)");
			}
			else
				wsprintf(str,"g(three_two)");
			break;
		}
	case UG_THREE_DOUBLE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(three_double)");
			}
			else
				wsprintf(str,"g(three_double)");
			break;
		}
	case UG_FOUR_ONE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(four_one)");
			}
			else
				wsprintf(str,"g(four_one)");
			break;
		}
	case UG_FOUR_TWO:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(four_two)");
			}
			else
				wsprintf(str,"g(four_two)");
			break;
		}
	case UG_FOUR_ONE_DOUBLE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(four_one_double)");
			}
			else
				wsprintf(str,"g(four_one_double)");
			break;
		}
	case UG_FOUR_TWO_DOUBLE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(four_two_double)");
			}
			else
				wsprintf(str,"g(four_two_double)");
			break;
		}
	case UG_STRAIGHT:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(one_sequence)");
			}
			else
				wsprintf(str,"g(one_sequence)");
			break;
		}
	case UG_STRAIGHT_FLUSH:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(straight_flush)");
			}
			else
				wsprintf(str,"g(straight_flush)");
			break;
		}
	case UG_DOUBLE_SEQUENCE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(two_sequence)");
			}
			else
				wsprintf(str,"g(two_sequence)");
			break;
		}
	case UG_THREE_SEQUENCE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(three_sequence)");
			}
			else
				wsprintf(str,"g(three_sequence)");
			break;
		}
	case UG_FOUR_SEQUENCE:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(four_sequence)");
			}
			else
				wsprintf(str,"g(four_sequence)");
			break;
		}
	case UG_BOMB:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(bomb)");
			}
			else
				wsprintf(str,"g(bomb)");
			break;
		}
	case UG_KING_BOMB:
		{
			if(IsBoy)
			{
				wsprintf(str,"b(king_bomb)");
			}
			else
				wsprintf(str,"g(king_bomb)");
			break;
		}
	default:
		if(IsBoy)
		{
			wsprintf(str,"b(def)");
		}
		else
			wsprintf(str,"g(def)");
		break;
	}
	name=f.GetKeyVal(key,str,str);
	wsprintf(filename,"%s%s%s",folder,name,extendname);

	return 	PlayCardMusic(filename,hParent);
}*/