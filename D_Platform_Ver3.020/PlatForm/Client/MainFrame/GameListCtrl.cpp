#include "StdAfx.h"
#include "GamePlace.h"
#include "GameListCtrl.h"
#include "PlaceResource.h"
#include "GamePlaceMessage.h"
#include "AppealDlg.h"
#include "GameListTip.h"
#include "MainRoomEx.h"

extern void DebugPrintf(const char *p, ...);


BEGIN_MESSAGE_MAP(CGameListCtrl, CTreeCtrl)

	//{{AFX_MSG_MAP(CTreeCtrlEx) 
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CGameListCtrl::OnNMCustomdraw)
	//ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, &CGameListCtrl::OnTvnItemexpanding)
 	ON_NOTIFY_REFLECT_EX(NM_CLICK, &CGameListCtrl::OnNMClick)
	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, &CGameListCtrl::OnNMDlbClick)
	ON_BN_CLICKED(IDC_BTN_Rule,&CGameListCtrl::OnClickReadRule)
	ON_WM_MOUSEMOVE()
// 	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CGameListCtrl::OnTvnItemexpanded)
	//}}AFX_MSG_MAP 


END_MESSAGE_MAP()

#define SET_LINE_COLOR          (TV_FIRST+40)		//设置颜色消息						
#define LS_TIME_OUT				60L		//列表超时数									

//树控件指针
CGameListCtrl					* CAFCGameListItem::m_pTreeCtrl=NULL;
std::map<UINT,CGameListCtrl::Color_Font>  CGameListCtrl::m_mapStatusColor;
std::map<void*,UINT> CGameListCtrl::m_mapHitemRoomID;
void CGameListCtrl::IEnterARoomOrLeave(UINT uRoomID,bool bEnter)//进入或离开一个房间。计算各个子服务器的在线人数和名称
{
	CAFCRoomItem * pGameRoomItem = FindRoomItem(uRoomID);//获得房间的列表的指针
	if (!pGameRoomItem)
		return;
	int dd = 0;
	if (bEnter) 
		dd = 1;//pGameRoomItem->m_RoomInfo.uPeopleCount ++;
	else 
		dd = -1;//pGameRoomItem->m_RoomInfo.uPeopleCount --;

	pGameRoomItem->m_RoomInfo.uPeopleCount += dd;
	
	if (pGameRoomItem->m_RoomInfo.uPeopleCount < 0 || pGameRoomItem->m_RoomInfo.uPeopleCount>0x7fffffff)
		pGameRoomItem->m_RoomInfo.uPeopleCount = 0;
	
	TCHAR szBuffer[100];
	memset(szBuffer,0,sizeof(szBuffer));
    //各个服务器的在线人数和名称

    // PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
	//wsprintf(szBuffer,TEXT("(%3d)%s"),pGameRoomItem->m_RoomInfo.uPeopleCount,pGameRoomItem->m_RoomInfo.szGameRoomName);
    COLORREF statuscolor = RGB(0,0,0);
	CString strStatusText = "";
	RoomOnLineShow(szBuffer, &pGameRoomItem->m_RoomInfo,statuscolor,strStatusText);

	SetItemText(pGameRoomItem->m_hCurrentItem,szBuffer);
	SetItemStatusColor(pGameRoomItem->m_hCurrentItem,pGameRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);
	CAFCNameItem *p = FindNameItem(pGameRoomItem->m_RoomInfo.uNameID);
	if(p)
	{
		p->m_NameInfo.m_uOnLineCount += dd;
		if (p->m_NameInfo.m_uOnLineCount < 0 || p->m_NameInfo.m_uOnLineCount>0x7FFFFFFF)
			p->m_NameInfo.m_uOnLineCount = 0;
		///p->UpdateOnLineCount();
		UpdateOnLineCount();
		//ExpandItem(2);
		///////////////////////////////////////////////////////////
		///Kylin 20090107  添加最近游戏列表
		bool canadd;

		canadd=true;
		for(int i=0;i<Glb().m_baFavorSave.GetCount();i++)
		{
			if(p->m_NameInfo.uNameID==Glb().m_baFavorSave[i])
			{
				canadd=false;
				break;
			}			
		}
		if(canadd)
			Glb().m_baFavorSave.Add(p->m_NameInfo.uNameID);

		///////////////////////////////////////////////////////////

	}
}

//更新总在线人数
bool CGameListCtrl::UpdateOnLineCount()
{
	//统计人数
	UINT uOnLineCount = 0L;
	CAFCGameListItem * pGameKindItem = GetKindParentItem();//获取根项
	for (INT_PTR i=0; i<pGameKindItem->m_ItemPtrArray.GetCount(); i++)
	{
		CAFCKindItem * pKindItem = (CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (NULL == pKindItem)
			continue;

		UINT kd = 0;

		// duanxiaohui 20111107 add
		for (INT_PTR j = 0; j < pKindItem->m_ItemPtrArray.GetCount(); j++)
		{
			CAFCKindItem * pKindItem2 = (CAFCKindItem *)pKindItem->m_ItemPtrArray.GetAt(j);

			// 判断是游戏类型还是游戏名称
			if (pKindItem2->m_uDataType == GLK_GAME_KIND)
			{
				UINT kd2 = 0;

				// 是游戏类型, 则这层目录为二级目录, 子目录下还有游戏
				for (INT_PTR k = 0; k < pKindItem2->m_ItemPtrArray.GetCount(); k++)
				{
					CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem2->m_ItemPtrArray.GetAt(k);
					if (NULL != pNameItem)
					{
						if (pNameItem->m_NameInfo.m_uOnLineCount < 0 || pNameItem->m_NameInfo.m_uOnLineCount > 0x7fffffff)
						{	
							pNameItem->m_NameInfo.m_uOnLineCount = 0;
						}

						pNameItem->UpdateOnLineCount();
						kd2 += pNameItem->m_NameInfo.m_uOnLineCount;
					}
				}

				uOnLineCount += kd;

				if (kd < 0)
				{	
					kd = 0;
				}

				TCHAR szBuffer[100];
				ZeroMemory(szBuffer,sizeof(szBuffer));

				KindOnLineShow(szBuffer, pKindItem2->m_KindInfo.szKindName, kd2);

				SetItemText(pKindItem2->m_hCurrentItem, szBuffer);
			}
			else
			{
				CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
				if (NULL != pNameItem)
				{
					if (pNameItem->m_NameInfo.m_uOnLineCount < 0 || pNameItem->m_NameInfo.m_uOnLineCount>0x7fffffff)
					{	
						pNameItem->m_NameInfo.m_uOnLineCount = 0;
					}

					pNameItem->UpdateOnLineCount();
					kd += pNameItem->m_NameInfo.m_uOnLineCount;
				}
			}
		}

		//for (INT_PTR j=0; j<pKindItem->m_ItemPtrArray.GetCount(); j++)
		//{
		//	CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
		//	if (NULL != pNameItem)
		//	{
		//		if (pNameItem->m_NameInfo.m_uOnLineCount < 0 || pNameItem->m_NameInfo.m_uOnLineCount>0x7fffffff)
		//			pNameItem->m_NameInfo.m_uOnLineCount = 0;
		//		pNameItem->UpdateOnLineCount();
		//		///uOnLineCount += pNameItem->m_uOnLineCount;
		//		kd += pNameItem->m_NameInfo.m_uOnLineCount;
		//	}
		//}

		// end duanxiaohui

		uOnLineCount += kd;
		if(kd<0)
			kd=0;
		
		TCHAR szBuffer[100];
		ZeroMemory(szBuffer,sizeof(szBuffer));
		
        // PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
        //wsprintf(szBuffer,TEXT("%s(%d)"),pKindItem->m_KindInfo.szKindName,kd);//m_RoomInfo.szGameRoomName);
        KindOnLineShow(szBuffer, pKindItem->m_KindInfo.szKindName,kd);

		SetItemText(pKindItem->m_hCurrentItem,szBuffer);
	}
	
	
	//更新显示
	TCHAR szBuffer[100];
	ZeroMemory(szBuffer,sizeof(szBuffer));
	//if(Glb().m_baFavor.GetCount())
	//	wsprintf(szBuffer,TEXT(Glb().m_Tree[1]),uOnLineCount);//第一个树。多少人在线
	/*else*/ 
    
    // PengJiLin, 2011-7-20, 如果不显示数字，则只显示名称
    //wsprintf(szBuffer,TEXT(Glb().m_Tree[0]),uOnLineCount);//第一个树。多少人在线
    RootOnLineShow(szBuffer, TEXT(Glb().m_Tree[0].GetBuffer()),uOnLineCount);
	SetItemText(pGameKindItem->m_hCurrentItem,szBuffer);
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表
	if(Glb().m_baFavor.GetCount())
	{
		UINT uOnLineCount=0L;
		CAFCGameListItem * pGameKindItem=(CAFCGameListItem *)m_InsideArray.GetAt(0);//获取根项
		for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
		{
			CAFCNameItem * pNameItem=(CAFCNameItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
			if (pNameItem!=NULL)
			{
				if(pNameItem->m_NameInfo.m_uOnLineCount < 0 || pNameItem->m_NameInfo.m_uOnLineCount>0x7fffffff)
					pNameItem->m_NameInfo.m_uOnLineCount=0;
				pNameItem->UpdateOnLineCount();
			}
		}

	}	
	///////////////////////////////////////////////////////////

	return true;
}


//处理数据
bool CGameListCtrl::HandleNameOnLineData(DL_GP_RoomListPeoCountStruct * pOnLineCountPtr, UINT uCount)
{
	
	for (UINT i=0;i<uCount;i++) 
	{
		CAFCNameItem * pNameItem=FindNameItem((pOnLineCountPtr+i)->uID);
		if (pNameItem!=NULL)
		{
			pNameItem->m_NameInfo.m_uOnLineCount=(pOnLineCountPtr+i)->uOnLineCount;
            pNameItem->UpdateOnLineCount();
			//pNameItem->ExpandItem (1);    // yjj 2008-12-23
		}

		pNameItem=FindNameItem((pOnLineCountPtr+i)->uID, 999);
		if (pNameItem!=NULL)
		{
			pNameItem->m_NameInfo.m_uOnLineCount=(pOnLineCountPtr+i)->uOnLineCount;
			pNameItem->UpdateOnLineCount();
			//pNameItem->ExpandItem (1);    // yjj 2008-12-23
		}
	}
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表
	if(Glb().m_baFavor.GetCount())
	{
		for (UINT i=0;i<uCount;i++) 
		{
			CAFCNameItem * pNameItem=FindNameItem((CAFCGameListItem *)m_InsideArray.GetAt(0),(pOnLineCountPtr+i)->uID);
			if (pNameItem!=NULL)
			{
				pNameItem->m_NameInfo.m_uOnLineCount=(pOnLineCountPtr+i)->uOnLineCount;
				pNameItem->UpdateOnLineCount();
				//pNameItem->ExpandItem (1);    // yjj 2008-12-23
			}
		}
	}	
	///////////////////////////////////////////////////////////
    UpdateOnLineCount();

	return true;
}

CAFCNameItem *CGameListCtrl::FindNameItem(UINT uID, UINT uKind)
{
	//统计人数
	UINT uOnLineCount = 0L;
	CAFCGameListItem * pGameKindItem = GetKindParentItem();//获取根项

	if (uKind == 999)
	{
		CAFCKindItem *pKind = FindKindItem(uKind);
		if (pKind != NULL)
		{
			CAFCNameItem * pNameItem = FindNameItem(pKind, uID);
			if (pNameItem != NULL)
				return pNameItem;
		}
		return NULL;
	}

	for (INT_PTR i=0; i<pGameKindItem->m_ItemPtrArray.GetCount(); i++)
	{
		CAFCKindItem * pKindItem = (CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (NULL != pKindItem && pKindItem->m_KindInfo.uKindID != 999)
		{
			for (INT_PTR j=0; j<pKindItem->m_ItemPtrArray.GetCount(); j++)
			{
				CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
				if (NULL != pNameItem)
				{
					if(pNameItem->m_NameInfo.uNameID == uID)
						return pNameItem;
				}
			}
		}
	}
	return NULL;
}

//处理数据
bool CGameListCtrl::HandleIOnLineData(MSG_GP_SR_OnLineStruct * pOnLineCountPtr, UINT uCount)
{
	for (UINT i=0;i<uCount;i++) 
	{
//		CAFCNameItem * pNameItem=FindNameItem(FindKindItem((pOnLineCountPtr+i)->uKindID),(pOnLineCountPtr+i)->uNameID);
		//if (pNameItem!=NULL) pNameItem->m_uOnLineCount=(pOnLineCountPtr+i)->uOnLineCount;
	}
	return true;
}

//展开数据
bool CGameListCtrl::ExpandItemFirstRoom()
{
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项

	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (pKindItem!=NULL)
		{
			for (INT_PTR j=0;j<pKindItem->m_ItemPtrArray.GetCount();j++)
			{
				CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
				if (pNameItem!=NULL)
				{
					pNameItem->ExpandItem (4);
					return true;
				}
			}
		}
	}
	return true;
}

/*******************************************************************************************************/
CAFCRoomItem *CGameListCtrl::FindRoomItem(UINT uRoomID)
{
	//统计人数
	UINT uOnLineCount=0L;
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (pKindItem!=NULL)
		{
			for (INT_PTR j=0;j<pKindItem->m_ItemPtrArray.GetCount();j++)
			{
				CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
				if (pNameItem!=NULL)
				{
					for (INT_PTR rr=0;rr<pNameItem->m_ItemPtrArray.GetCount();rr++)
					{
						CAFCRoomItem * proomItem=(CAFCRoomItem *)pNameItem->m_ItemPtrArray.GetAt (rr);
						if(proomItem != NULL && proomItem->m_RoomInfo.uRoomID == uRoomID)return proomItem;
					
					}
				}
			}
		}
	}
	return NULL;
}

CAFCRoomItem *CGameListCtrl::FindRoomItemEx(UINT uRoomID, UINT uKind)
{
	//统计人数
	UINT uOnLineCount=0L;
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (pKindItem!=NULL && (uKind == -1 || (uKind == 999 && pKindItem->m_KindInfo.uKindID == uKind)))
		{
			for (INT_PTR j=0;j<pKindItem->m_ItemPtrArray.GetCount();j++)
			{
				CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
				if (pNameItem!=NULL)
				{
					for (INT_PTR rr=0;rr<pNameItem->m_ItemPtrArray.GetCount();rr++)
					{
						CAFCRoomItem * proomItem=(CAFCRoomItem *)pNameItem->m_ItemPtrArray.GetAt (rr);
						if (proomItem->m_bIsContest)
						{
							for (int k = 0; k < proomItem->m_RoomContest.size(); k++)
							{
								if (proomItem->m_RoomContest[k].uRoomID == uRoomID)
									return proomItem;
							}
						}
						else
						{
							if(proomItem->m_RoomInfo.uRoomID == uRoomID)return proomItem;
						}
					}
				}
			}
		}
	}
	return NULL;
}

// PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
bool CGameListCtrl::m_bUseNumShow = false;
void CGameListCtrl::KindOnLineShow(TCHAR* pchDest, TCHAR* pchName, UINT uNum)
{
    // 使用数字显示
    if(true == m_bUseNumShow)
    {
        wsprintf(pchDest,TEXT("%s(%d)"),pchName,uNum);
        return;
    }

    wsprintf(pchDest,TEXT("%s"),pchName);
    //if(uNum >= KIND_NUM_TO_FULL)
    //    wsprintf(pchDest,TEXT("%s")/*TEXT("%s(爆满)")*/,pchName);
    //else if(uNum >= KIND_NUM_TO_BUSY)
    //    wsprintf(pchDest,TEXT("%s")/*TEXT("%s(繁忙)")*/,pchName);
    //else
    //    wsprintf(pchDest,TEXT("%s")/*TEXT("%s(空闲)")*/,pchName);
}
void CGameListCtrl::RoomOnLineShow(TCHAR* pchDest, ComRoomInfo* pRoomInfo,COLORREF& statusColor,CString& statusText)
{
    UINT uPeopleCount = pRoomInfo->uPeopleCount;
    if(uPeopleCount > 0xFFFF) uPeopleCount = 0;

    // 使用数字显示
    if(true == m_bUseNumShow)
    {
        wsprintf(pchDest,TEXT("(%3d)%s"),uPeopleCount,pRoomInfo->szGameRoomName);
        return;
    }
	
	CBcfFile fOrder(CBcfFile::GetAppPath()+"Order.bcf");
	UINT uLevel1 = fOrder.GetKeyVal("CrowdedShow", "Level1Count", 30);
	UINT uLevel2 = fOrder.GetKeyVal("CrowdedShow", "Level2Count", 80);
	UINT uLevel3 = fOrder.GetKeyVal("CrowdedShow", "Level3Count", 100);
	UINT uLevel4 = fOrder.GetKeyVal("CrowdedShow", "Level4Count", 100);

	UINT uFull = pRoomInfo->uDeskCount * pRoomInfo->uDeskPeople;
    if(0 == uFull) uFull = 1;

    float fRate = 0.0f;
    fRate = (float)uPeopleCount/uFull*100;

	if(fRate <= uLevel1)
	{
		statusColor = (COLORREF)fOrder.GetKeyVal("CrowdedShow", "Level1Color", 4227200);
		statusText = fOrder.GetKeyVal("CrowdedShow", "Level1Text", "空闲");
	}
	else if(fRate <= uLevel2)
	{
		statusColor = (COLORREF)fOrder.GetKeyVal("CrowdedShow", "Level2Color", 33023);
		statusText = fOrder.GetKeyVal("CrowdedShow", "Level2Text", "繁忙");
	}
	else if(fRate <= uLevel3)
	{
		statusColor = (COLORREF)fOrder.GetKeyVal("CrowdedShow", "Level3Color", 255);
		statusText = fOrder.GetKeyVal("CrowdedShow", "Level3Text", "拥挤");
	}
	else if(fRate <= uLevel4)
	{
		statusColor = (COLORREF)fOrder.GetKeyVal("CrowdedShow", "Level4Color", 4194432);
		statusText = fOrder.GetKeyVal("CrowdedShow", "Level4Text", "爆满");
	}
	else
	{
		statusColor = (COLORREF)fOrder.GetKeyVal("CrowdedShow", "Level4Color", 4194432);
		statusText = fOrder.GetKeyVal("CrowdedShow", "Level4Text", "爆满");
	}
	wsprintf(pchDest,TEXT("%s"), pRoomInfo->szGameRoomName);
}
void CGameListCtrl::RootOnLineShow(TCHAR* pchDest, TCHAR* pchFormat, UINT uNum)
{
    // 使用数字显示
    if(true == m_bUseNumShow)
    {
        CString strFormat;
		strFormat.Format(pchFormat);
		if (strFormat.Compare("游戏大厅") >= 0)
		{
			strcpy(pchDest,TEXT("游戏大厅"));
		}
		else
		{
			wsprintf(pchDest,pchFormat,uNum);
		}

        return;
    }

    // 不显示数字
    TCHAR chBuffer[100] = {0};
    TCHAR* ptr = NULL;
    ptr = strstr(pchFormat, "(");
    if(NULL != ptr)
    {
        memcpy(chBuffer, pchFormat, (int)(ptr) - (int)pchFormat);
        strcpy(pchDest, chBuffer);
    }
    else
    {
        strcpy(pchDest,TEXT("游戏大厅"));
    }
}

// 检测并确定显示方式
void CGameListCtrl::CheckIfUseNumShow()
{
    CBcfFile fOrder(CBcfFile::GetAppPath()+"Order.bcf");
    UINT uShow = fOrder.GetKeyVal("CrowdedShow", "PeopleCountShow", 1);
    m_bUseNumShow = uShow;
}

//处理数据
bool CGameListCtrl::HandleRoomOnLineData(DL_GP_RoomListPeoCountStruct * pOnLineCountPtr, UINT uCount)
{
	for (UINT i=0;i<uCount;i++) 
	{
		CAFCRoomItem * pRoomItem=FindRoomItemEx((pOnLineCountPtr+i)->uID);
		if (pRoomItem!=NULL)
		{
			if (!pRoomItem->m_bIsContest)
			{
				pRoomItem->m_RoomInfo.uPeopleCount=(pOnLineCountPtr+i)->uOnLineCount;

				{
					TCHAR szBuffer[100];
					memset(szBuffer,0,sizeof(szBuffer));
					if(pRoomItem->m_RoomInfo.uPeopleCount<0 || pRoomItem->m_RoomInfo.uPeopleCount>0x7fffffff)
						pRoomItem->m_RoomInfo.uPeopleCount=0;
				
					// PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
					//wsprintf(szBuffer,TEXT("(%3d)%s"),pRoomItem->m_RoomInfo.uPeopleCount,pRoomItem->m_RoomInfo.szGameRoomName);
					COLORREF statuscolor = RGB(0,0,0);
					CString strStatusText = "";
					RoomOnLineShow(szBuffer, &pRoomItem->m_RoomInfo,statuscolor,strStatusText);

					SetItemText(pRoomItem->m_hCurrentItem,szBuffer);
					SetItemStatusColor(pRoomItem->m_hCurrentItem,pRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);
				}
			}
			else
			{
				ComRoomInfo* _p = FindContestRoomItem(pRoomItem, (pOnLineCountPtr+i)->uID);
				if (_p != NULL)
				{
					_p->uPeopleCount = (pOnLineCountPtr+i)->uOnLineCount;
					int _pcount = 0;
					for (int k = 0; k < pRoomItem->m_RoomContest.size(); k++)
					{
						_pcount += pRoomItem->m_RoomContest[k].uPeopleCount;
					}
					pRoomItem->m_iContestPeopleCount = _pcount;
				}
			}
		}


		pRoomItem=FindRoomItemEx((pOnLineCountPtr+i)->uID, 999);
		if (pRoomItem!=NULL)
		{
			if (!pRoomItem->m_bIsContest)
			{
				pRoomItem->m_RoomInfo.uPeopleCount=(pOnLineCountPtr+i)->uOnLineCount;

				{
					TCHAR szBuffer[100];
					memset(szBuffer,0,sizeof(szBuffer));
					if(pRoomItem->m_RoomInfo.uPeopleCount<0 || pRoomItem->m_RoomInfo.uPeopleCount>0x7fffffff)
						pRoomItem->m_RoomInfo.uPeopleCount=0;

					// PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
					//wsprintf(szBuffer,TEXT("(%3d)%s"),pRoomItem->m_RoomInfo.uPeopleCount,pRoomItem->m_RoomInfo.szGameRoomName);
					COLORREF statuscolor = RGB(0,0,0);
					CString strStatusText = "";
					RoomOnLineShow(szBuffer, &pRoomItem->m_RoomInfo,statuscolor,strStatusText);

					SetItemText(pRoomItem->m_hCurrentItem,szBuffer);
					SetItemStatusColor(pRoomItem->m_hCurrentItem,pRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);
				}
			}
			else
			{
				ComRoomInfo* _p = FindContestRoomItem(pRoomItem, (pOnLineCountPtr+i)->uID);
				if (_p != NULL)
				{
					_p->uPeopleCount = (pOnLineCountPtr+i)->uOnLineCount;
					int _pcount = 0;
					for (int k = 0; k < pRoomItem->m_RoomContest.size(); k++)
					{
						_pcount += pRoomItem->m_RoomContest[k].uPeopleCount;
					}
					pRoomItem->m_iContestPeopleCount = _pcount;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	if(Glb().m_baFavor.GetCount())
	{
		CAFCGameListItem * pGameKindItem=(CAFCGameListItem *)m_InsideArray.GetAt(0);//获取根项
		for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
		{
			CAFCNameItem * pNameItem=(CAFCNameItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
			if (pNameItem!=NULL) 
			{
				CAFCRoomItem * pRoomItem=FindRoomItem(pNameItem,(pOnLineCountPtr+i)->uID);
				if (pRoomItem!=NULL)
				{
					pRoomItem->m_RoomInfo.uPeopleCount=(pOnLineCountPtr+i)->uOnLineCount;

					{
						TCHAR szBuffer[100];
						memset(szBuffer,0,sizeof(szBuffer));
						if(pRoomItem->m_RoomInfo.uPeopleCount<0 || pRoomItem->m_RoomInfo.uPeopleCount>0x7fffffff)
							pRoomItem->m_RoomInfo.uPeopleCount=0;
						
                        // PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
                        //wsprintf(szBuffer,TEXT("(%3d)%s"),pRoomItem->m_RoomInfo.uPeopleCount,pRoomItem->m_RoomInfo.szGameRoomName);
						COLORREF statuscolor = RGB(0,0,0);
						CString strStatusText = "";
						RoomOnLineShow(szBuffer, &pRoomItem->m_RoomInfo,statuscolor,strStatusText);

						SetItemText(pRoomItem->m_hCurrentItem,szBuffer);
						SetItemStatusColor(pRoomItem->m_hCurrentItem,pRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);
					}
				}
			}
		}
	}
	///////////////////////////////////////////////////////////

	return true;
}
//析构函数
CAFCGameListItem::CAFCGameListItem()
{
	m_uUpdateTime=0;
	m_hCurrentItem=NULL;
	m_pParentItem=NULL;
	m_uDataType=GLK_NO_DATA;
	return;
}

//析构函数
CAFCGameListItem::~CAFCGameListItem()
{
	for (int i=0;i<m_ItemPtrArray.GetCount();i++)
	{
		delete (CAFCGameListItem *)m_ItemPtrArray.GetAt(i);
		m_ItemPtrArray.SetAt(i,NULL);
	}
	return;
}

//初始化项
bool CAFCGameListItem::Init(CAFCGameListItem * pParentItem)
{
	m_pParentItem=pParentItem;
	return true;
}

//在树上插入一个叶子接点数据
HTREEITEM CAFCGameListItem::AddTreeData(TCHAR * szText, UINT uIconIndex, LPARAM lParam)
{
	TV_INSERTSTRUCT InsertInf;
	memset(&InsertInf,0,sizeof(InsertInf));
	InsertInf.item.cchTextMax=100;
	InsertInf.hParent=m_hCurrentItem; // 父节点
	InsertInf.hInsertAfter=TVI_LAST;
	InsertInf.item.iImage=uIconIndex;
	InsertInf.item.iSelectedImage=uIconIndex;
	InsertInf.item.pszText=szText;
	InsertInf.item.lParam=lParam;
	InsertInf.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;

	return m_pTreeCtrl->InsertItem(&InsertInf);
}

//展开项数据
bool CAFCGameListItem::ExpandItem(int iExpendCount)
{
	if ((iExpendCount==-1)||(iExpendCount>0))//如果项序号等于-1或者项序号大于0（即项序号不等于0）
	{
		if (m_hCurrentItem!=NULL) m_pTreeCtrl->Expand(m_hCurrentItem,TVE_EXPAND);//如果当前项不为空，那么展开当前项
		if ((iExpendCount>1)||(iExpendCount==-1))//如果项序号等于-1或者项序号大于1（即项序号不等于1，不等于0）
		{
			if (iExpendCount>0) iExpendCount--;//如果项序号大于0，那么项序号减1
			for (int i=0;i<m_ItemPtrArray.GetCount();i++)//子项数组总数
			{
				CAFCGameListItem * pListItem=(CAFCGameListItem *)m_ItemPtrArray.GetAt(i);//////////得到 游戏列表子项
				//if (pListItem!=NULL) pListItem->ExpandItem(iExpendCount);//如果游戏列表子项不为空，那么展开游戏列表子项
				//2008-12-23
			}
		}
		return true;
	}
	return false;
}
//加入从服务器获取的类型
bool CAFCGameListItem::UpdateGetListItem()//////////更新列表AddTreeData
{
	CBcfFile fMsg(CBcfFile::GetAppPath()+"ClientMessage.bcf");
	CString str;
	
	if (m_uDataType == GLK_GAME_NAME)/////////////如果数据类型是游戏名字
	{
		if (m_ItemPtrArray.GetCount()==0)////无子项
		{
			TCHAR szBuffer[100];
			memset(szBuffer,0,sizeof(szBuffer));
			if ((m_uUpdateTime+LS_TIME_OUT) <= (LONG)time(NULL)) 
			{
				str = fMsg.GetKeyVal("MainRoom","ReadingInfor","读取信息...");
				wsprintf(szBuffer,str.GetBuffer());//如果更新时间+列表超时数小于当前时间，那么就读取信息
			}
			else
			{
				str = fMsg.GetKeyVal("MainRoom","NoRooms","没有房间");
				wsprintf(szBuffer,str.GetBuffer());//否则就算超时，显示没有实例
			}
			TCHAR sz[200];
			wsprintf(sz,"%d,%d",m_uUpdateTime,(LONG)time(NULL));
			//Writelog(sz);
			if (m_hUpdateItem==NULL) 
				m_hUpdateItem=AddTreeData(szBuffer,IND_NO_ROOM,NULL);///如果获取索引等于空，那么获取索引=增加项，显示//没有房间的图标
			else
			{
				m_pTreeCtrl->SetItemText(m_hUpdateItem,szBuffer);//树控件指针设置显示文字
			}
		}
		else if (m_hUpdateItem!=NULL) ///有子项
		{
			for (INT_PTR i=0;i<m_ItemPtrArray.GetCount();i++)//循环所有子项
			{
				CAFCRoomItem * pRoomItem=(CAFCRoomItem *)m_ItemPtrArray.GetAt(i);///游戏房间子项等于树子项
				pRoomItem->m_uUpdateTime=(LONG)time(NULL);//更新时间=当前时间
			}
			m_pTreeCtrl->DeleteItem(m_hUpdateItem);//删除获取索引
			m_hUpdateItem=NULL;////////获取索引为空
		}
	}
	return true;
}
//是否需要更新 
bool CAFCGameListItem::IsNeedUpdate()//是否需要更新
{
	if ((m_uDataType==GLK_GAME_NAME)&&((m_uUpdateTime+LS_TIME_OUT)<=time(NULL))) return true;////////如果数据类型是游戏名字，并且更新时间+列表超时数小于当前时间
	return false;
}
//删除过时房间
bool CAFCGameListItem::DeleteOutTimeItem()
{
	
	if (m_uDataType==GLK_GAME_NAME)//如果数据类型是游戏名字
	{
		for (INT_PTR i=0;i<m_ItemPtrArray.GetCount();i++)//////////循环所有子项
		{
			CAFCRoomItem * pRoomItem=(CAFCRoomItem *)m_ItemPtrArray.GetAt(i);//游戏房间子项等于树子项
			if ((pRoomItem!=NULL)&&((pRoomItem->m_uUpdateTime+LS_TIME_OUT)<=(LONG)time(NULL)))//如果游戏房间子项不为空，并且且更新时间+列表超时数小于当前时间
			{
				m_ItemPtrArray.RemoveAt(i--);///////删除子项数组
				m_pTreeCtrl->DeleteItem(pRoomItem->m_hCurrentItem);/////删除树子项
				delete pRoomItem;////删除游戏房间子项
			}
		}
		UpdateGetListItem();/////更新列表
	}
	return true;
}
//加入游戏类型AddTreeData
bool CAFCGameListItem::AddGameKind(ComKindInfo * pGameKind,int initType)
{
	try
	{
		CAFCKindItem * pGameKindItem = new CAFCKindItem; // 新游戏类型子项
		if (pGameKindItem != NULL) // 如果游戏类型子项不为空
		{
			pGameKindItem->Init(this); 

			pGameKindItem->m_KindInfo = *pGameKind; // 类型数据

			pGameKindItem->m_uDataType = initType;

			/*
			TCHAR szBuffer[100];
			wsprintf(szBuffer,TEXT("%d"),pGameKindItem->m_KindInfo.Head.bDataType); // 第一个树。多少人在线
			AfxMessageBox(szBuffer);
			AfxMessageBox(pGameKindItem->m_KindInfo.szKindName);
			*/

			// 增加子项
			m_ItemPtrArray.Add(pGameKindItem); 
			
			// duanxiaohui 2011-11-21 二级目录加载外部图标
			if (pGameKind->uParentKindID != 0)
			{
				CString strPath;
				strPath.Format("%s\\icon\\%s.ico",m_skinmgr.GetKeyVal(m_skinmgr.GetSkinBcfFileName()), pGameKind->szKindName);
				int nIconIndex = CPlaceResource::LoadExtendIcon(strPath);
				if (nIconIndex == 0)
				{
					nIconIndex = IND_KIND2_ICON;  // 默认二级目录图标
				}

				pGameKindItem->m_hCurrentItem = AddTreeData(pGameKindItem->m_KindInfo.szKindName, nIconIndex, (LPARAM)pGameKindItem); 
			}
			else
			{
				pGameKindItem->m_hCurrentItem = AddTreeData(pGameKindItem->m_KindInfo.szKindName, IND_KIND_ICON, (LPARAM)pGameKindItem); 
			}

			//pGameKindItem->m_hCurrentItem = AddTreeData(pGameKindItem->m_KindInfo.szKindName, IND_KIND_ICON, (LPARAM)pGameKindItem); 

			// end duanxiaohui 

			return true;
		}
	}
	catch (...) {}
	return false;
}

//加入游戏名字
CAFCNameItem* CAFCGameListItem::AddGameName(ComNameInfo * pGameName,int initType)
{
	try
	{
		CAFCNameItem * pGameNameItem=new CAFCNameItem;
		
		if (pGameNameItem!=NULL)
		{
			//设置数据
			pGameNameItem->Init(this);
			pGameNameItem->m_NameInfo=*pGameName;
			pGameNameItem->m_NameInfo.Head.bDataType = initType;
			pGameNameItem->m_uDataType = initType;
			m_ItemPtrArray.Add(pGameNameItem);
			pGameNameItem->m_hCurrentItem=AddTreeData(pGameNameItem->m_NameInfo.szGameName,CPlaceResource::GetListIconIndex(pGameName),(LPARAM)pGameNameItem);
			return pGameNameItem;
		}
	}
	catch (...) {}
	return NULL;
}

//加入游戏房间
bool CAFCGameListItem::AddGameRoom(ComRoomInfo * pGameRoom)
{
	try
	{
		CAFCRoomItem * pGameRoomItem=new CAFCRoomItem;
		if (pGameRoomItem!=NULL)
		{
			//设置数据		
			pGameRoomItem->Init(this);
			pGameRoomItem->m_RoomInfo=*pGameRoom;
			pGameRoomItem->m_uUpdateTime=(LONG)time(NULL);
			m_ItemPtrArray.Add(pGameRoomItem);
			TCHAR szBuffer[100];
			memset(szBuffer,0,sizeof(szBuffer));
			
            // PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
            //wsprintf(szBuffer,TEXT("(%3d)%s"),pGameRoom->uPeopleCount,pGameRoom->szGameRoomName);
			COLORREF statuscolor = RGB(0,0,0);
			CString strStatusText = "";
			CGameListCtrl::RoomOnLineShow(szBuffer, pGameRoom,statuscolor,strStatusText);
			
			if (pGameRoom->bVIPRoom)
				pGameRoomItem->m_hCurrentItem=AddTreeData(szBuffer,7,(LPARAM)pGameRoomItem); ///< 金葫芦2代是VIP房间
			else
				pGameRoomItem->m_hCurrentItem=AddTreeData(szBuffer,IND_ROOM_ICON,(LPARAM)pGameRoomItem);
			
			if (m_pTreeCtrl != NULL)
				m_pTreeCtrl->SetItemStatusColor(pGameRoomItem->m_hCurrentItem,pGameRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);

			return true;
		}
	}
	catch (...) {}
	return false;
}

//加入比赛房间
bool CAFCGameListItem::AddContestItem(ComRoomInfo * pGameRoom)
{
		try
	{
		CAFCRoomItem * pGameRoomItem=new CAFCRoomItem;
		if (pGameRoomItem!=NULL)
		{
			//设置数据		
			pGameRoomItem->Init(this);
			pGameRoomItem->m_RoomInfo=*pGameRoom;
			pGameRoomItem->m_uUpdateTime=(LONG)time(NULL);
			m_ItemPtrArray.Add(pGameRoomItem);
			TCHAR szBuffer[100];
			memset(szBuffer,0,sizeof(szBuffer));

			pGameRoomItem->m_bIsContest = true;
			pGameRoomItem->m_RoomContest.push_back(*pGameRoom);
			
            // PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
            //wsprintf(szBuffer,TEXT("(%3d)%s"),pGameRoom->uPeopleCount,pGameRoom->szGameRoomName);
			COLORREF statuscolor = RGB(0,0,0);
			CString strStatusText = "";
			CGameListCtrl::RoomOnLineShow(szBuffer, pGameRoom,statuscolor,strStatusText);

			if (pGameRoom->bVIPRoom)
				pGameRoomItem->m_hCurrentItem=AddTreeData(szBuffer,7,(LPARAM)pGameRoomItem); ///< 金葫芦2代是VIP房间
			else
				pGameRoomItem->m_hCurrentItem=AddTreeData(szBuffer,IND_ROOM_ICON,(LPARAM)pGameRoomItem);

			if (m_pTreeCtrl != NULL)
				m_pTreeCtrl->SetItemStatusColor(pGameRoomItem->m_hCurrentItem,pGameRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);

			return true;
		}
	}
	catch (...) {}
	return false;
}

//加入内部数据
bool CAFCGameListItem::AddInsideData(GameInsideInfo * pInsideData, UINT uIconIndex)
{
	try
	{
		CAFCInsideItem * pInsideItem=new CAFCInsideItem;
		if (pInsideItem!=NULL)
		{
			//设置数据
			pInsideItem->Init(this);
			pInsideItem->m_InsideInfo=*pInsideData;
			m_ItemPtrArray.Add(pInsideItem);
			pInsideItem->m_hCurrentItem=AddTreeData(pInsideItem->m_InsideInfo.szDisplayName,uIconIndex,(LPARAM)pInsideItem);
			return true;
		}
	}
	catch (...) {}
	return false;
}
	
/*******************************************************************************************************/

//设置单个游戏的总在线人数
bool CAFCNameItem::UpdateOnLineCount()
{
	TCHAR szBuffer[100];
	memset(szBuffer,0,sizeof(szBuffer));
	if(m_NameInfo.m_uOnLineCount<0 || m_NameInfo.m_uOnLineCount>0x7fffffff)
		m_NameInfo.m_uOnLineCount=0;
	
    // PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
    //wsprintf(szBuffer,TEXT("%s(%d)"),m_NameInfo.szGameName,m_NameInfo.m_uOnLineCount);
    CGameListCtrl::KindOnLineShow(szBuffer, m_NameInfo.szGameName,m_NameInfo.m_uOnLineCount);
	
	m_pTreeCtrl->SetItemText(m_hCurrentItem,szBuffer);
	return true;
}

/*******************************************************************************************************/

//构造函数
CGameListCtrl::CGameListCtrl()
{
	m_hLastMMItem = NULL;
	m_mapStatusColor.clear();
	m_mapHitemRoomID.clear();
}

//析构函数
CGameListCtrl::~CGameListCtrl()
{
	for (int i=0;i<m_InsideArray.GetCount();i++)
	{
		delete (CAFCGameListItem *)m_InsideArray.GetAt(i);
		m_InsideArray.SetAt(i,NULL);
	}
	m_mapStatusColor.clear();
	m_mapHitemRoomID.clear();
	return;
}

//初始化函数,同时增加根接点
bool CGameListCtrl::Init()
{
	//设置控件
	//SendMessage(SET_LINE_COLOR,0,(LPARAM)CGameImageLink::m_ColorResource.m_crListTxColor);

	//设置游戏列表数据
	UINT uIconIndex[]=
	{
		IND_LIST_ROOT,IND_ROOM_NO_ICON,IND_LIST_ROOT,IND_LIST_NO_INSTALL,
		IND_LIST_ROOT,IND_LIST_ROOT,IND_LIST_ROOT,
	};
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表
	if(Glb().m_baFavor.GetCount())
	{
		CBcfFile fMsg(CBcfFile::GetAppPath()+"ClientMessage.bcf");
		CString str = fMsg.GetKeyVal("MainRoom","RecentGameList","最近玩过的游戏列表");

		GameInsideInfo InsideInfo;
		InsideInfo.Head.uSize=sizeof(InsideInfo);
		InsideInfo.Head.bDataType=GLK_GAME_USE;
		InsideInfo.uTrunID=1000;
		lstrcpy(InsideInfo.szDisplayName,str.GetBuffer());
		bool bAddExtendIcon=false;
		CString s=CBcfFile::GetAppPath();/////本地路径
		CBcfFile f( s + "bzgame.bcf");

		CString strICO=f.GetKeyVal(Glb().m_key,"FavorICO","");
		//DebugPrintf("strICO = [%s]", strICO);
		if(strICO!="")
		{
			UINT uIconExtendIndex=CPlaceResource::LoadExtendIcon(strICO);
			//DebugPrintf("CPlaceResource::LoadExtendIcon(strICO) = [%d]", uIconExtendIndex);
			if(uIconExtendIndex>0)
			{
				if(AddRootItem(&InsideInfo,uIconExtendIndex))
					bAddExtendIcon=true;
			}
		}
		if(!bAddExtendIcon)
			AddRootItem(&InsideInfo,uIconIndex[0]);
	}	
	///////////////////////////////////////////////////////////

	//在树上插入根数据
	CAFCGameListItem::m_pTreeCtrl=this;

	for (int i=0;i<1;i++)                                                        //游戏大厅树列表初始化 Tree2，Tree3已用销售列表
	{	
		GameInsideInfo InsideInfo;
		InsideInfo.Head.uSize=sizeof(InsideInfo);
		InsideInfo.Head.bDataType=GLK_GAME_USE;
		InsideInfo.uTrunID=1000+i;
		lstrcpy(InsideInfo.szDisplayName,Glb().m_Tree[i]);
		bool bAddExtendIcon=false;
		if(Glb().m_Tree[i+20]!="")
		{
			UINT uIconExtendIndex=CPlaceResource::LoadExtendIcon(Glb().m_Tree[i+20]);
			if(uIconExtendIndex>0)
			{
				if(AddRootItem(&InsideInfo,uIconExtendIndex))
					bAddExtendIcon=true;
			}
		}
		if(!bAddExtendIcon)
			AddRootItem(&InsideInfo,uIconIndex[0]);
	}

	//加载网络线条的颜色
	CString s = CBcfFile::GetAppPath();/////本地路径
	CString strSkin = m_skinmgr.GetSkinBcfFileName();
	CBcfFile f( s + strSkin);
	CString key= TEXT("GameListWnd");

	m_crGridLine = f.GetKeyVal(key,"list_itemline_color",(__int64)RGB(230,230,230));
	m_crGridHotBk1 = f.GetKeyVal(key,"list_itemhot_bkcolor1",(__int64)RGB(17,142,206));
	m_crGridHotBk2 = f.GetKeyVal(key,"list_itemhot_bkcolor2",(__int64)RGB(161,217,245));
	m_crGridHotTxt1 = f.GetKeyVal(key,"list_itemhot_textcolor1",(__int64)RGB(255,255,255));
	m_crGridHotTxt2 = f.GetKeyVal(key,"list_itemhot_textcolor2",(__int64)RGB(0,0,0));

	TCHAR path[MAX_PATH];
	CString skinfolder;
	if ("skin0.bcf" == strSkin)
		skinfolder=f.GetKeyVal("skin0","skinfolder",m_skinmgr.GetSkinPath());
	else
		skinfolder=f.GetKeyVal("skin1","skinfolder",m_skinmgr.GetSkinPath());

	//加载列表根结点logo
	wsprintf(path,"%sleft\\list_logo_game.bmp",skinfolder);
	m_imgLogo.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	//加载列表折叠/反折叠logo
	wsprintf(path,"%sleft\\list_bn_fold.bmp",skinfolder);
	m_imgFold.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	wsprintf(path,"%sleft\\list_bn_unfold.bmp",skinfolder);
	m_imgUnFold.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,"%sleft\\set_bt.bmp",skinfolder);
	m_imgAD.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	//加载鼠标手势
	m_curHand  = LoadCursor(NULL,MAKEINTRESOURCE(32649));
	m_curArrow = LoadCursor(NULL,IDC_ARROW);

	SetItemHeight(24);


    // PengJiLin, 2011-7-20, 人数是否以数字形式显示
    CheckIfUseNumShow();

	//查看规则按钮
	m_btRule.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BTN_Rule);

	wsprintf(path,"%sleft\\rule.bmp",skinfolder);
	m_btRule.LoadButtonBitmap(path,false);
	m_btRule.ShowWindow(SW_HIDE);



	CBcfFile fMsg(CBcfFile::GetAppPath()+"ClientMessage.bcf");
	bool bShow = fMsg.GetKeyVal("MainRoom","ShowLastLoginGame", 0);
	if (bShow)
	{
		ComKindInfo p;
		ZeroMemory(&p, sizeof(p));
		p.Head.bDataType = 1;
		p.Head.bDataType = 80;

		CString str = fMsg.GetKeyVal("MainRoom","ShowLastLoginGameText", "最近常登录的游戏");
		strcpy(p.szKindName, str);

		p.uKindID = 999;

		HandleKindData(&p, 1);
	}


	return true;
}

void CGameListCtrl::LoadSkin()
{
	//设置游戏列表数据
	//UINT uIconIndex[]=
	//{
	//	IND_LIST_ROOT,IND_ROOM_NO_ICON,IND_LIST_ROOT,IND_LIST_NO_INSTALL,
	//	IND_LIST_ROOT,IND_LIST_ROOT,IND_LIST_ROOT,
	//};
	/////////////////////////////////////////////////////////////
	/////Kylin 20090107  添加最近游戏列表
	//if(Glb().m_baFavor.GetCount())
	//{
	//	CBcfFile fMsg(CBcfFile::GetAppPath()+"ClientMessage.bcf");
	//	CString str = fMsg.GetKeyVal("MainRoom","RecentGameList","最近玩过的游戏列表");

	//	GameInsideInfo InsideInfo;
	//	InsideInfo.Head.uSize=sizeof(InsideInfo);
	//	InsideInfo.Head.bDataType=GLK_GAME_USE;
	//	InsideInfo.uTrunID=1000;
	//	lstrcpy(InsideInfo.szDisplayName,str.GetBuffer());
	//	bool bAddExtendIcon=false;
	//	CString s=CBcfFile::GetAppPath();/////本地路径
	//	CBcfFile f( s + "bzgame.bcf");

	//	CString strICO=f.GetKeyVal(Glb().m_key,"FavorICO","");
	//	//DebugPrintf("strICO = [%s]", strICO);
	//	if(strICO!="")
	//	{
	//		UINT uIconExtendIndex=CPlaceResource::LoadExtendIcon(strICO);
	//		//DebugPrintf("CPlaceResource::LoadExtendIcon(strICO) = [%d]", uIconExtendIndex);
	//		if(uIconExtendIndex>0)
	//		{
	//			if(AddRootItem(&InsideInfo,uIconExtendIndex))
	//				bAddExtendIcon=true;
	//		}
	//	}
	//	if(!bAddExtendIcon)
	//		AddRootItem(&InsideInfo,uIconIndex[0]);
	//}	
	/////////////////////////////////////////////////////////////

	////在树上插入根数据
	//CAFCGameListItem::m_pTreeCtrl=this;

	//for (int i=0;i<1;i++)                                                        //游戏大厅树列表初始化 Tree2，Tree3已用销售列表
	//{	
	//	GameInsideInfo InsideInfo;
	//	InsideInfo.Head.uSize=sizeof(InsideInfo);
	//	InsideInfo.Head.bDataType=GLK_GAME_USE;
	//	InsideInfo.uTrunID=1000+i;
	//	lstrcpy(InsideInfo.szDisplayName,Glb().m_Tree[i]);
	//	bool bAddExtendIcon=false;
	//	if(Glb().m_Tree[i+20]!="")
	//	{
	//		UINT uIconExtendIndex=CPlaceResource::LoadExtendIcon(Glb().m_Tree[i+20]);
	//		if(uIconExtendIndex>0)
	//		{
	//			if(AddRootItem(&InsideInfo,uIconExtendIndex))
	//				bAddExtendIcon=true;
	//		}
	//	}
	//	if(!bAddExtendIcon)
	//		AddRootItem(&InsideInfo,uIconIndex[0]);
	//}

	//加载网络线条的颜色
	CString s = CBcfFile::GetAppPath();/////本地路径
	CString strSkin = m_skinmgr.GetSkinBcfFileName();
	CBcfFile f( s + strSkin);
	CString key= TEXT("GameListWnd");

	m_crGridLine = f.GetKeyVal(key,"list_itemline_color",(__int64)RGB(230,230,230));
	m_crGridHotBk1 = f.GetKeyVal(key,"list_itemhot_bkcolor1",(__int64)RGB(17,142,206));
	m_crGridHotBk2 = f.GetKeyVal(key,"list_itemhot_bkcolor2",(__int64)RGB(161,217,245));
	m_crGridHotTxt1 = f.GetKeyVal(key,"list_itemhot_textcolor1",(__int64)RGB(255,255,255));
	m_crGridHotTxt2 = f.GetKeyVal(key,"list_itemhot_textcolor2",(__int64)RGB(0,0,0));

	TCHAR path[MAX_PATH];
	CString skinfolder;
	if ("skin0.bcf" == strSkin)
		skinfolder=f.GetKeyVal("skin0","skinfolder",m_skinmgr.GetSkinPath());
	else
		skinfolder=f.GetKeyVal("skin1","skinfolder",m_skinmgr.GetSkinPath());

	//加载列表根结点logo
	wsprintf(path,"%sleft\\list_logo_game.bmp",skinfolder);
	m_imgLogo.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	//加载列表折叠/反折叠logo
	wsprintf(path,"%sleft\\list_bn_fold.bmp",skinfolder);
	m_imgFold.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	wsprintf(path,"%sleft\\list_bn_unfold.bmp",skinfolder);
	m_imgUnFold.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	wsprintf(path,"%sleft\\set_bt.bmp",skinfolder);
	m_imgAD.SetLoadInfo(path,CGameImageLink::m_bAutoLock);

	//加载鼠标手势
	//m_curHand  = LoadCursor(NULL,MAKEINTRESOURCE(32649));
	//m_curArrow = LoadCursor(NULL,IDC_ARROW);

	//SetItemHeight(24);

	// PengJiLin, 2011-7-20, 人数是否以数字形式显示
	//CheckIfUseNumShow();

	//查看规则按钮
	//m_btRule.Create(TEXT(""),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BTN_Rule);

	wsprintf(path,"%sleft\\rule.bmp",skinfolder);
	m_btRule.LoadButtonBitmap(path,false);
	m_btRule.ShowWindow(SW_HIDE);

	//CBcfFile fMsg(CBcfFile::GetAppPath()+"ClientMessage.bcf");
	//bool bShow = fMsg.GetKeyVal("MainRoom","ShowLastLoginGame", 0);
	//if (bShow)
	//{
	//	ComKindInfo p;
	//	ZeroMemory(&p, sizeof(p));
	//	p.Head.bDataType = 1;
	//	p.Head.bDataType = 80;

	//	CString str = fMsg.GetKeyVal("MainRoom","ShowLastLoginGameText", "最近常登录的游戏");
	//	strcpy(p.szKindName, str);

	//	p.uKindID = 999;

	//	HandleKindData(&p, 1);
	//}
}
//换肤
LRESULT CGameListCtrl::OnExchangeSkin(WPARAM wpara,LPARAM lpara)
{
	LoadSkin();
	//OnPaint();
	Invalidate();
	return LRESULT(0);
}
//初始化函数,同时增加根接点
bool CGameListCtrl::Init2()
{
	//设置控件
	//SendMessage(SET_LINE_COLOR,0,(LPARAM)CGameImageLink::m_ColorResource.m_crListTxColor);
	
	//设置游戏列表数据
	UINT uIconIndex[]=
	{
		IND_LIST_ROOT,IND_ROOM_NO_ICON,IND_LIST_ROOT,IND_LIST_NO_INSTALL,
		IND_LIST_ROOT,IND_LIST_ROOT,IND_LIST_ROOT,
	};
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	CAFCGameListItem::m_pTreeCtrl=this;
	if(Glb().m_baFavor.GetCount())
	{
		CBcfFile fMsg(CBcfFile::GetAppPath()+"ClientMessage.bcf");
		CString str = fMsg.GetKeyVal("MainRoom","RecentGameList","最近玩过的游戏列表");

		GameInsideInfo InsideInfo;
		InsideInfo.Head.uSize=sizeof(InsideInfo);
		InsideInfo.Head.bDataType=GLK_GAME_USE;
		InsideInfo.uTrunID=1000;
		lstrcpy(InsideInfo.szDisplayName,str.GetBuffer());
		AddRootItem(&InsideInfo,uIconIndex[0]);
	}	
	///////////////////////////////////////////////////////////

	//在树上插入根数据
	for (int i=0;i<Glb().m_TreeCount2;i++)
	{	
		GameInsideInfo InsideInfo;
		InsideInfo.Head.uSize=sizeof(InsideInfo);
		InsideInfo.Head.bDataType=GLK_GAME_USE;
		InsideInfo.uTrunID=1000+i;
		lstrcpy(InsideInfo.szDisplayName,Glb().m_Tree2[i]);
		if (!AddRootItem(&InsideInfo,uIconIndex[0])) return false;
	}

    // PengJiLin, 2011-7-20, 人数是否以数字形式显示
    CheckIfUseNumShow();

	return true;
}
//插入根项
bool CGameListCtrl::AddRootItem(GameInsideInfo * pInsideData, UINT uIconIndex)
{
	try
	{
		bool haveAddress = false;
		if (pInsideData->Head.bDataType == GLK_GAME_ADD)
		{
			haveAddress =true;
		}

		CAFCInsideItem * pInsideItem=new CAFCInsideItem();
		if (haveAddress)
		{
			pInsideItem->m_uDataType = GLK_GAME_ADD;
		}
		if (pInsideItem!=NULL)
		{
			//设置数据
			pInsideItem->Init(NULL);
			pInsideItem->m_InsideInfo=*pInsideData;
			m_InsideArray.Add(pInsideItem);

			//插入数据
			TV_INSERTSTRUCT InsertInf;
			memset(&InsertInf,0,sizeof(InsertInf));
			InsertInf.item.cchTextMax=100;
			InsertInf.hInsertAfter=TVI_LAST;
			InsertInf.itemex.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM|TVIF_INTEGRAL;
			InsertInf.itemex.iImage=uIconIndex;
			InsertInf.itemex.iSelectedImage=uIconIndex;//选择根图标
			InsertInf.itemex.iIntegral = 1;
			InsertInf.itemex.pszText=pInsideData->szDisplayName;
			InsertInf.itemex.lParam=(LPARAM)pInsideItem;

			pInsideItem->m_hCurrentItem=InsertItem(&InsertInf);

			if (pInsideData->Head.bDataType == GLK_GAME_ADD)
			{
				SetItemColor(pInsideItem->m_hCurrentItem,RGB(255,0,0));
			}
			return true;
		}
	}
	catch (...) {}
	return false;
}


//处理数据//在树上加入游戏类型AddTreeData
bool CGameListCtrl::HandleKindData(ComKindInfo * pKindInfoPtr, UINT uKindCount)
{
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (UINT i=0;i<uKindCount;i++) 
	{
		// duanxiaohui 20111107 add
		if ((pKindInfoPtr + i)->uParentKindID != 0)
		{
			// 检测是否存在父游戏ID类型
			CAFCKindItem * pGameParentKindItem = FindKindItem((pKindInfoPtr + i)->uParentKindID);
			if (pGameParentKindItem != NULL)
			{
				if (FindKindItem((pKindInfoPtr+i)->uKindID) == NULL)
				{
					pGameParentKindItem->AddGameKind(pKindInfoPtr + i); // 在树上加入子游戏类型AddTreeData
				}

				continue ;
			}
		}
		// end duanxiaohui

		if (FindKindItem((pKindInfoPtr+i)->uKindID)==NULL)
				pGameKindItem->AddGameKind(pKindInfoPtr+i);//在树上加入游戏类型AddTreeData
	}
	return true;
}

bool CGameListCtrl::HandleUrlData(CAFCGameUrlItem * pUrlInfoPtr, UINT uDatatype)
{

	HTREEITEM root = GetKindParentItem()->m_hCurrentItem;
	for (int i = 0; i < m_GameUrl.GetCount(); i++)
	{
		CAFCGameUrlItem* p = (CAFCGameUrlItem *)m_GameUrl.GetAt(i);
		if (p->m_uDataType == uDatatype) 
		{
			root = p->m_hCurrentItem;
		}
	}
	try
	{
		CAFCGameUrlItem* p = new CAFCGameUrlItem();
		if (p!=NULL)
		{ 
			//设置数据
			//*p = *pUrlInfoPtr;
			p->m_uDataType = pUrlInfoPtr->m_uDataType;
			p->m_stName = pUrlInfoPtr->m_stName;
			p->m_stUrl = pUrlInfoPtr->m_stUrl;

			m_GameUrl.Add(p);

			//插入数据
			TV_INSERTSTRUCT InsertInf;
			memset(&InsertInf,0,sizeof(InsertInf));
			InsertInf.hParent = root;
			InsertInf.item.cchTextMax = 100;
			InsertInf.hInsertAfter = TVI_LAST;
			InsertInf.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;

			// duanxiaohui 2011-11-21 加载外部icon
			CString strPath;
			strPath.Format("%s\\icon\\%s.ico", m_skinmgr.GetKeyVal(m_skinmgr.GetSkinBcfFileName()), pUrlInfoPtr->m_stName);
			int nIconIndex = CPlaceResource::LoadExtendIcon(strPath);
			if (nIconIndex == 0)
			{
				nIconIndex = IND_KIND_ICON;  // 默认Icon图标
			}
			// end duanxiaohui

			InsertInf.item.iImage =  nIconIndex;
			InsertInf.item.iSelectedImage =  nIconIndex; //选择根图标
			InsertInf.item.pszText = p->m_stName.GetBuffer();
			InsertInf.item.lParam = (LPARAM)p;
			p->m_hCurrentItem = InsertItem(&InsertInf);
			return true;
		}
	}
	catch (...) {}
}


bool CGameListCtrl::HandleLoginGame(int iGameID)
{
	for (int i = 0; i < m_LoginGameInfo.size(); i++)
	{
		if (m_LoginGameInfo[i].iGameID == iGameID)
		{
			CAFCNameItem* _pName = FindNameItem(iGameID);
			CAFCKindItem* _pKind = FindKindItem(999);
			if (_pName == NULL || _pKind == NULL) return false;

			CAFCNameItem* _pNameAdd = FindNameItem(_pKind, iGameID);
			if (_pNameAdd != NULL) delete _pNameAdd;
			_pNameAdd = _pKind->AddGameName(&_pName->m_NameInfo);

			for (int i = 0; i < _pName->m_ItemPtrArray.GetCount(); i++)
			{
				CAFCRoomItem* _pRoom = (CAFCRoomItem*)_pName->m_ItemPtrArray.GetAt(i);
				if (_pRoom != NULL)
					_pNameAdd->AddGameRoom(&_pRoom->m_RoomInfo);
			}
		}
	}

	return true;
	//pGameNameItem->m_hCurrentItem=AddTreeData(pGameNameItem->m_NameInfo.szGameName,CPlaceResource::GetListIconIndex(pGameName),(LPARAM)pGameNameItem);
}

bool CGameListCtrl::HandleLoginGameName(ComNameInfo * pNameInfoPtr)
{
	CAFCKindItem* _pKind = FindKindItem(999);
	if (_pKind == NULL || pNameInfoPtr == NULL) return false;
	if (FindNameItem(_pKind, pNameInfoPtr->uNameID)==NULL) 
		_pKind->AddGameName(pNameInfoPtr);
}

void CGameListCtrl::ClearLoginGameName()
{
	CAFCKindItem* _pKind = FindKindItem(999);

	for (INT_PTR i=0;i< _pKind->m_ItemPtrArray.GetCount();i++)//////////循环所有子项
	{
		CAFCNameItem * pName = (CAFCNameItem *)_pKind->m_ItemPtrArray.GetAt(i);//游戏房间子项等于树子项
		if (pName!=NULL)//如果游戏房间子项不为空，并且且更新时间+列表超时数小于当前时间
		{
			_pKind->m_ItemPtrArray.RemoveAt(i--);///////删除子项数组
			DeleteItem(pName->m_hCurrentItem);/////删除树子项
			delete pName;////删除游戏房间子项
		}
	}
}
 
//处理数据/////在树上加入游戏名字
bool CGameListCtrl::HandleNameData(ComNameInfo * pNameInfoPtr, UINT uNameCount)
{
	static bool FirstInit = false;
	int iCount = 0;
	int iDeleteCount = 0;
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项

	for (UINT i=0;i<uNameCount;i++)                      //删除销售列表中重复的项   add by wyl   11-5-16
	{
		for ( SELLLISTINFO::iterator it = m_SellListVec.begin(); it != m_SellListVec.end(); it++ )
		{
			iCount ++;
			if ((*it).NameID == (pNameInfoPtr+i)->uNameID)
			{
				(*it).NameID = 0;
				iDeleteCount++;
			}
		}

		//记录游戏房间和游戏房间名字   yjj 090310
		CAppealDlg::WriteGameInfoFile((pNameInfoPtr+i)->szGameName,(pNameInfoPtr+i)->uNameID);

		CAFCKindItem * pKindItem=FindKindItem((pNameInfoPtr+i)->uKindID);
		if ((pKindItem!=NULL)&&(FindNameItem(pKindItem,(pNameInfoPtr+i)->uNameID)==NULL)) pKindItem->AddGameName(pNameInfoPtr+i);///////在树上加入游戏名字
		///////////////////////////////////////////////////////////
		///Kylin 20090107  添加最近游戏列表
		if(Glb().m_baFavor.GetCount())
		{
			bool canadd;

			canadd=false;
			for(int j=0;j<Glb().m_baFavor.GetCount();j++)
			{
				if(Glb().m_baFavor[j]==(pNameInfoPtr+i)->uNameID)
				{
					canadd=true;
					break;
				}
			}
			if(canadd)
			{
				CAFCGameListItem * pKindItem;
				pKindItem=(CAFCGameListItem *)m_InsideArray.GetAt(0);
				if ((pKindItem!=NULL)&&(FindNameItem(pKindItem,(pNameInfoPtr+i)->uNameID)==NULL)) pKindItem->AddGameName(pNameInfoPtr+i);///////在树上加入游戏名字
			}
		}
		///////////////////////////////////////////////////////////
	}

	//增加销售列表				add by wyl    11-5-16
	CString s=CBcfFile::GetAppPath (false);
	CBcfFile f( s + "bzgame.bcf");

	int TreeCount=f.GetKeyVal ("BZW","TreeCount",1);

	if ( 2 <= TreeCount && ((CMainRoomEx*)GetMainRoom())->m_HaveSellList && !FirstInit)
	{
		FirstInit = true;
		UINT uIconIndex[]=
		{
			IND_LIST_ROOT,IND_ROOM_NO_ICON,IND_LIST_ROOT,IND_LIST_NO_INSTALL,
			IND_LIST_ROOT,IND_LIST_ROOT,IND_LIST_ROOT,
		};

		for (int i=1;i<3;i++)
		{	
			GameInsideInfo InsideInfo;
			InsideInfo.Head.uSize=sizeof(InsideInfo);
			if (i != 2)
			{
				InsideInfo.Head.bDataType=GLK_GAME_USE;
			}
			else
			{
				InsideInfo.Head.bDataType=GLK_GAME_ADD;
			}

			InsideInfo.uTrunID=1000+i;
			lstrcpy(InsideInfo.szDisplayName,Glb().m_Tree[i]);
			bool bAddExtendIcon=false;
			if(Glb().m_Tree[i+20]!="")
			{
				UINT uIconExtendIndex=CPlaceResource::LoadExtendIcon(Glb().m_Tree[i+20]);
				if(uIconExtendIndex>0)
				{
					if(AddRootItem(&InsideInfo,uIconExtendIndex))
						bAddExtendIcon=true;
				}
			}
			if(!bAddExtendIcon)
				AddRootItem(&InsideInfo,uIconIndex[0]);
		}
		//////////////////////////////////////////////////////////////////////////
		ComKindInfo *pSellInfo = new ComKindInfo;

		for ( SELLLISTINFO::iterator it = m_SellListVec.begin(); it != m_SellListVec.end(); it++ )
		{
			if ((*it).NameID == 0)
				continue;
			
			memcpy(pSellInfo->szKindName,(*it).szKindName,61);
			pSellInfo->uKindID = (*it).KindID;
			CAFCGameListItem * pGameKindItem=(CAFCGameListItem *)GetSellListParentItem();	//获取根项 
			if (FindSellKindItem((*it).KindID) == NULL)
			{
				pGameKindItem->AddGameKind(pSellInfo);

				pGameKindItem->m_pTreeCtrl->SetItemColor(pGameKindItem->m_hCurrentItem,RGB(0,0,255));

				if (pGameKindItem->m_pTreeCtrl->ItemHasChildren(pGameKindItem->m_hCurrentItem))
				{
					HTREEITEM hItem = pGameKindItem->m_pTreeCtrl->GetChildItem(pGameKindItem->m_hCurrentItem);
					pGameKindItem->m_pTreeCtrl->SetItemColor(hItem,RGB(0,0,255));

					while (hItem != NULL)
					{
						hItem = pGameKindItem->m_pTreeCtrl->GetNextSiblingItem(hItem);
						pGameKindItem->m_pTreeCtrl->SetItemColor(hItem,RGB(0,0,255));
						CString buffer;
						buffer.Format("更多地方特色游戏(%d)",iCount/uNameCount - iDeleteCount);
						pGameKindItem->m_pTreeCtrl->SetItemText(pGameKindItem->m_hCurrentItem,buffer);
					}
				}
				pGameKindItem->ExpandItem(2);
			}

			// 加游戏名称
			pGameKindItem = FindSellKindItem((*it).KindID);
			ComNameInfo *pNameInfoPtrSellList = new ComNameInfo;
			pNameInfoPtrSellList->Head.bDataType = 10;
			pNameInfoPtrSellList->uKindID = (*it).KindID;
			memcpy(pNameInfoPtrSellList->szGameName,(*it).szGameName,60);
			char precessName[61]={0};
			wsprintf(precessName,"%d.exe",(*it).NameID);
			memcpy(pNameInfoPtrSellList->szGameProcess,precessName,60);
			pNameInfoPtrSellList->uNameID = (*it).NameID;
			pGameKindItem->AddGameName(pNameInfoPtrSellList,(*it).ParamID + 100);
			

			//所有游戏名 颜色控制
			if (pGameKindItem->m_pTreeCtrl->ItemHasChildren(pGameKindItem->m_hCurrentItem))
			{
				HTREEITEM hItem = pGameKindItem->m_pTreeCtrl->GetChildItem(pGameKindItem->m_hCurrentItem);
				pGameKindItem->m_pTreeCtrl->SetItemColor(hItem,RGB(0,0,255));

				while (hItem != NULL)
				{
					hItem = pGameKindItem->m_pTreeCtrl->GetNextSiblingItem(hItem);
					pGameKindItem->m_pTreeCtrl->SetItemColor(hItem,RGB(0,0,255));
				}
			}
		}
	}

	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	if(Glb().m_baFavor.GetCount())
	{
		CAFCGameListItem * pGameKindItem=(CAFCGameListItem *)m_InsideArray.GetAt(0);//获取根项
		bool bdeal;
		do
		{
			bdeal=false;
			for(int j=0;j<Glb().m_baFavor.GetCount();j++)
			{
				if(FindNameItem(Glb().m_baFavor[j])==NULL)
				{
					Glb().m_baFavor.RemoveAt(j);
					bdeal=true;
					break;
				}
			}
			for(int j=0;j<Glb().m_baFavorSave.GetCount();j++)
			{
				if(FindNameItem(Glb().m_baFavorSave[j])==NULL)
				{
					Glb().m_baFavorSave.RemoveAt(j);
					bdeal=true;
					break;
				}
			}
			
		}
		while(bdeal);

	}
	///////////////////////////////////////////////////////////

	return true;
}
//处理数据
bool CGameListCtrl::HandleRoomData(ComRoomInfo * pRoomInfoPtr, UINT uRoomCount, UINT uKindID, UINT uNameID)
{
	CAFCKindItem* pKind = FindKindItem(uKindID);
	CAFCNameItem * pNameItem=FindNameItem(pKind,uNameID);///查找游戏名称
	if (pNameItem!=NULL)
	{
		for (UINT i=0;i<uRoomCount;i++)
		{

			CAFCRoomItem * pRoomItem = NULL;

			if ((pRoomInfoPtr+i)->dwRoomRule & GRR_CONTEST)
			{
				pRoomItem = FindRoomItemByContest(pNameItem, pRoomInfoPtr+i);
				if (pRoomItem != NULL)
				{
					ComRoomInfo* _p = FindContestRoomItem(pRoomItem, (pRoomInfoPtr+i)->uRoomID);
					if (_p != NULL)
					{
						pRoomItem->m_uUpdateTime=(LONG)time(NULL);
						lstrcpy(pRoomItem->m_RoomInfo.szGameRoomName,(pRoomInfoPtr+i)->szGameRoomName);
					}
					else
					{
						pRoomItem->m_RoomContest.push_back(*(pRoomInfoPtr+i));
					}
				}
				else
				{
					pNameItem->AddContestItem(pRoomInfoPtr+i);
				}
			}
			else
			{
				pRoomItem=FindRoomItem(pNameItem,(pRoomInfoPtr+i)->uRoomID);/////////在这个游戏名称下面再查找房间ID

				if (pRoomItem!=NULL)
				{
					TCHAR szBuffer[100];
					memset(szBuffer,0,sizeof(szBuffer));
					pRoomItem->m_uUpdateTime=(LONG)time(NULL);
					lstrcpy(pRoomItem->m_RoomInfo.szGameRoomName,(pRoomInfoPtr+i)->szGameRoomName);
					////////////////////////////////////////////
					///Kylin 20090204 防止负人数
				
					// PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
					//wsprintf(szBuffer,TEXT("(%3d)%s"),(pRoomInfoPtr+i)->uPeopleCount<0?0:(pRoomInfoPtr+i)->uPeopleCount,(pRoomInfoPtr+i)->szGameRoomName);

					////////////////////////////////////////////
					COLORREF statuscolor = RGB(0,0,0);
					CString strStatusText = "";
					RoomOnLineShow(szBuffer, (pRoomInfoPtr+i),statuscolor,strStatusText);

					SetItemText(pRoomItem->m_hCurrentItem,szBuffer);
					SetItemStatusColor(pRoomItem->m_hCurrentItem,pRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);
				}
				else pNameItem->AddGameRoom(pRoomInfoPtr+i);////////在这个游戏名称下面增加查找房间ID
			}
		}
	}
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	if(Glb().m_baFavor.GetCount())
	{
		CAFCNameItem * pNameItem=FindNameItem((CAFCGameListItem *)m_InsideArray.GetAt(0),uNameID);///查找游戏名称
		if (pNameItem!=NULL)
		{
			for (UINT i=0;i<uRoomCount;i++)
			{
				CAFCRoomItem * pRoomItem=FindRoomItem(pNameItem,(pRoomInfoPtr+i)->uRoomID);/////////在这个游戏名称下面再查找房间ID

				if (pRoomItem!=NULL)
				{
					TCHAR szBuffer[100];
					memset(szBuffer,0,sizeof(szBuffer));
					pRoomItem->m_uUpdateTime=(LONG)time(NULL);
					lstrcpy(pRoomItem->m_RoomInfo.szGameRoomName,(pRoomInfoPtr+i)->szGameRoomName);
					////////////////////////////////////////////
					///Kylin 20090204 防止负人数
					
                    // PengJiLin, 2011-7-20, 游戏树形列表，支持显示在线人数数字显示、说明显示(空闲、繁忙)
                    //wsprintf(szBuffer,TEXT("(%3d)%s"),(pRoomInfoPtr+i)->uPeopleCount<0?0:(pRoomInfoPtr+i)->uPeopleCount,(pRoomInfoPtr+i)->szGameRoomName);

					COLORREF statuscolor = RGB(0,0,0);
					CString strStatusText = "";
					RoomOnLineShow(szBuffer, (pRoomInfoPtr+i),statuscolor,strStatusText);

					SetItemText(pRoomItem->m_hCurrentItem,szBuffer);
					SetItemStatusColor(pRoomItem->m_hCurrentItem,pRoomItem->m_RoomInfo.uRoomID,RGB(0,0,0),statuscolor,strStatusText);
				}
				else pNameItem->AddGameRoom(pRoomInfoPtr+i);////////在这个游戏名称下面增加查找房间ID
			}
		}
	}
	///////////////////////////////////////////////////////////

	return true;
}
//查找类型子项
CAFCKindItem * CGameListCtrl::FindKindItem(UINT uKindID)
{
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);

		// duanxiaohui 20111107 add
		//if ((pKindItem!=NULL)&&(pKindItem->m_KindInfo.uKindID==uKindID)) return pKindItem;

		if (pKindItem != NULL)
		{
			if (pKindItem->m_KindInfo.uKindID == uKindID)
			{
				return pKindItem;
			}
			else if (pKindItem->m_KindInfo.uKindID != 999)
			{
				for (INT_PTR j = 0; j < pKindItem->m_ItemPtrArray.GetCount(); j++)
				{
					CAFCKindItem * pKindItem2 = (CAFCKindItem *)pKindItem->m_ItemPtrArray.GetAt(j);
					if ((pKindItem2 != NULL) && (pKindItem2->m_KindInfo.uKindID==uKindID))
					{
						return pKindItem2;
					}
				}
			}
		}
		// end duanxiaohui
	}

	return NULL;
}

CAFCKindItem * CGameListCtrl::FindSellKindItem(UINT uKindID)                         
{
	CAFCGameListItem * pGameKindItem=GetSellListParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		
		// duanxiaohui 20111107 add
		/*if ((pKindItem!=NULL)&&(pKindItem->m_KindInfo.uKindID==uKindID))
		return pKindItem;*/

		if (pKindItem != NULL)
		{
			if (pKindItem->m_KindInfo.uKindID == uKindID)
			{
				return pKindItem;
			}
			else
			{
				for (INT_PTR j = 0; j < pKindItem->m_ItemPtrArray.GetCount(); j++)
				{
					CAFCKindItem * pKindItem2 = (CAFCKindItem *)pKindItem->m_ItemPtrArray.GetAt(j);
					if ((pKindItem2 != NULL) && (pKindItem2->m_KindInfo.uKindID==uKindID))
					{
						return pKindItem2;
					}
				}
			}
		}
		// end duanxiaohui
	}
	return NULL;
}
//查找名字子项
CAFCNameItem * CGameListCtrl::FindNameItem(CAFCKindItem * pKindItem, UINT uNameID)
{
	if (pKindItem!=NULL)
	{
		for (INT_PTR i=0;i<pKindItem->m_ItemPtrArray.GetCount();i++)
		{
			CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(i);
			if ((pNameItem!=NULL)&&(pNameItem->m_NameInfo.uNameID==uNameID)) return pNameItem;
		}
	}
	return NULL;
}

//查找名字子项
CAFCNameItem * CGameListCtrl::FindNameItem(CAFCGameListItem * pKindItem, UINT uNameID)
{
	if (pKindItem!=NULL)
	{
		for (INT_PTR i=0;i<pKindItem->m_ItemPtrArray.GetCount();i++)
		{
			CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(i);
			if ((pNameItem!=NULL)&&(pNameItem->m_NameInfo.uNameID==uNameID)) return pNameItem;
		}
	}
	return NULL;
}
//查找房间子项
CAFCRoomItem * CGameListCtrl::FindRoomItem(CAFCNameItem * pNameItem, UINT uRoomID, ComRoomInfo* pRoomInfo)
{
	if (pNameItem!=NULL)
	{
		//if (pRoomInfo->dwRoomRule & GRR_CONTEST)
		//{
		//	for (INT_PTR i=0;i<pNameItem->m_ItemPtrArray.GetCount();i++)
		//	{
		//		CAFCRoomItem * pRoomItem=(CAFCRoomItem *)pNameItem->m_ItemPtrArray.GetAt(i);
		//		if (pRoomItem != NULL && pRoomItem->m_bIsContest)
		//		{
		//			for (int k = 0; k < pRoomItem->m_RoomContest.size(); k++)
		//			{
		//				if (pRoomItem->m_RoomContest[k].uRoomID == uRoomID) return pRoomItem;
		//			}
		//		}
		//	}
		//}
		//else
		//{
			for (INT_PTR i=0;i<pNameItem->m_ItemPtrArray.GetCount();i++)
			{
				CAFCRoomItem * pRoomItem=(CAFCRoomItem *)pNameItem->m_ItemPtrArray.GetAt(i);
				if (pRoomItem!=NULL)
				{
					if (pRoomItem->m_RoomInfo.uRoomID==uRoomID) return pRoomItem;
				}
			}
		//}
	}
	return NULL;
}


//查找房间子项
CAFCRoomItem * CGameListCtrl::FindRoomItemByContest(CAFCNameItem * pNameItem, ComRoomInfo* pRoomInfo)
{
	if (pNameItem!=NULL)
	{
		if (pRoomInfo->dwRoomRule & GRR_CONTEST)
		{
			for (INT_PTR i=0;i<pNameItem->m_ItemPtrArray.GetCount();i++)
			{
				CAFCRoomItem * pRoomItem=(CAFCRoomItem *)pNameItem->m_ItemPtrArray.GetAt(i);
				if (pRoomItem != NULL && pRoomItem->m_bIsContest && pRoomInfo->iContestID == pRoomItem->m_RoomInfo.iContestID)
				{
					return pRoomItem;
				}
			}
		}
	}
	return NULL;
}


//查找比赛房间子项
ComRoomInfo * CGameListCtrl::FindContestRoomItem(CAFCRoomItem * pRoomItem, int iRoomID)
{
	if (pRoomItem != NULL && pRoomItem->m_bIsContest)
	{
		for (int i = 0; i < pRoomItem->m_RoomContest.size(); i++)
		{
			if (pRoomItem->m_RoomContest[i].uRoomID == iRoomID)
				return &(pRoomItem->m_RoomContest[i]);
		}
	}
	return NULL;
}

//插入获取数据
bool CGameListCtrl::FillGetListItem()
{
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (pKindItem!=NULL)
		{
			// duanxiaohui 20111107 add
			for (INT_PTR j = 0; j < pKindItem->m_ItemPtrArray.GetCount(); j++)
			{
				CAFCKindItem * pKindItem2 = (CAFCKindItem *)pKindItem->m_ItemPtrArray.GetAt(j);

				// 判断是游戏类型还是游戏名称
				if (pKindItem2->m_uDataType == GLK_GAME_KIND)
				{
					// 是游戏类型, 则这层目录为二级目录, 子目录下还有游戏
					for (INT_PTR k = 0; k < pKindItem2->m_ItemPtrArray.GetCount(); k++)
					{
						CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem2->m_ItemPtrArray.GetAt(k);
						if (pNameItem != NULL) 
						{
							pNameItem->m_uUpdateTime=0;
							pNameItem->UpdateGetListItem();
						}
					}
				}
				else
				{
					CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
					if (pNameItem != NULL) 
					{
						pNameItem->m_uUpdateTime = 0;
						pNameItem->UpdateGetListItem();
					}
				}
			}

			/*for (INT_PTR j=0;j<pKindItem->m_ItemPtrArray.GetCount();j++)
			{
			CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
			if (pNameItem!=NULL) 
			{
			pNameItem->m_uUpdateTime=0;
			pNameItem->UpdateGetListItem();
			}
			}*/

			// end duanxiaohui
		}			
	}
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	if(Glb().m_baFavor.GetCount())
	{
		CAFCGameListItem * pGameKindItem=(CAFCGameListItem *)m_InsideArray.GetAt(0);//获取根项
		for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
		{
			CAFCNameItem * pNameItem=(CAFCNameItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
			if (pNameItem!=NULL) 
			{
				pNameItem->m_uUpdateTime=0;
				pNameItem->UpdateGetListItem();
			}
		}
	}
	///////////////////////////////////////////////////////////
	return true;
}
//删除过时房间 
bool CGameListCtrl::DeleteOutTimeRoom(UINT uKindID, UINT uNameID)
{
	CAFCNameItem * pNameItem=FindNameItem(FindKindItem(uKindID),uNameID);
	if (pNameItem!=NULL) pNameItem->DeleteOutTimeItem();
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	if(Glb().m_baFavor.GetCount())
	{
		CAFCNameItem * pNameItem=FindNameItem((CAFCGameListItem *)m_InsideArray.GetAt(0),uNameID);
		if (pNameItem!=NULL) pNameItem->DeleteOutTimeItem();
	}
	///////////////////////////////////////////////////////////

	return true;
}
//获取进程名字
bool CGameListCtrl::GetProcessName(CAFCRoomItem * pGameRoomItem, TCHAR * szProcessName, UINT uBufferSize)
{
	if ((pGameRoomItem->m_pParentItem!=NULL)&&(pGameRoomItem->m_pParentItem->m_uDataType==GLK_GAME_NAME))
	{
		CAFCNameItem * pGameName=(CAFCNameItem *)pGameRoomItem->m_pParentItem;
		CopyMemory(szProcessName,pGameName->m_NameInfo.szGameProcess,__min(uBufferSize,sizeof(pGameName->m_NameInfo.szGameProcess)));
		szProcessName[uBufferSize/sizeof(TCHAR)-1]=0;
		return true;
	}
	return false;
}
//获取游戏名字
bool CGameListCtrl::GetGameName(CAFCRoomItem * pGameRoomItem, TCHAR * szGameName, UINT uBufferSize)
{
	if ((pGameRoomItem->m_pParentItem!=NULL)&&(pGameRoomItem->m_pParentItem->m_uDataType==GLK_GAME_NAME))
	{
		CAFCNameItem * pGameName=(CAFCNameItem *)pGameRoomItem->m_pParentItem;
		CopyMemory(szGameName,pGameName->m_NameInfo.szGameName,__min(uBufferSize,sizeof(pGameName->m_NameInfo.szGameName)));
		szGameName[uBufferSize/sizeof(TCHAR)-1]=0;
		return true;
	}
	return false;
}



//展开数据
bool CGameListCtrl::ExpandItem(int iExpendCount)
{
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	pGameKindItem->ExpandItem(iExpendCount);
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	if(Glb().m_baFavor.GetCount())
	{
		CAFCGameListItem * pGameKindItem=(CAFCGameListItem *)m_InsideArray.GetAt(0);//获取根项
		pGameKindItem->ExpandItem(iExpendCount);
	}
	///////////////////////////////////////////////////////////

	return true;
}

void CGameListCtrl::UpdataItem(CAFCGameListItem* pItem)
{
	CAFCNameItem * pNameItem;
	int i;
	for(i=0;i<=pItem->m_pParentItem->m_ItemPtrArray.GetCount();i++)
	{
		pNameItem = (CAFCNameItem *)(pItem->m_pParentItem->m_ItemPtrArray.GetAt(i));
		if(pNameItem->m_hCurrentItem==pItem->m_hCurrentItem)
			break;
	}
	int selimage=CPlaceResource::GetListIconIndex(&(pNameItem->m_NameInfo));
	TVITEM item;
	item.hItem=pItem->m_hCurrentItem;
	item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	item.iImage=selimage;
	item.iSelectedImage=selimage;
	TreeView_SetItem(m_hWnd,&item);
}

//获取Item的层次值
int CGameListCtrl::GetItemLevel(HTREEITEM hItem)
{
	int iLevel = 0;

	HTREEITEM hNext = GetParentItem(hItem);

	while (hNext)
	{
		iLevel++;
		hNext = GetParentItem(hNext);
	}

	return iLevel;
}

void CGameListCtrl::UpdateAllIcon(void)
{
	int selimage;
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (pKindItem!=NULL)
		{
			// duanxiaohui 20111107 add
			for (INT_PTR j = 0; j < pKindItem->m_ItemPtrArray.GetCount(); j++)
			{
				CAFCKindItem * pKindItem2 = (CAFCKindItem *)pKindItem->m_ItemPtrArray.GetAt(j);

				// 判断是游戏类型还是游戏名称
				if (pKindItem2->m_uDataType == GLK_GAME_KIND)
				{
					// 是游戏类型, 则这层目录为二级目录, 子目录下还有游戏
					for (INT_PTR k = 0; k < pKindItem2->m_ItemPtrArray.GetCount(); k++)
					{
						CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem2->m_ItemPtrArray.GetAt(k);
						if (pNameItem != NULL) 
						{
							selimage = CPlaceResource::GetListIconIndex(&(pNameItem->m_NameInfo));
							TVITEM item;
							item.hItem = pNameItem->m_hCurrentItem;
							item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
							item.iImage = selimage;
							item.iSelectedImage = selimage;
							TreeView_SetItem(m_hWnd, &item);
						}
					}
				}
				else
				{
					CAFCNameItem * pNameItem = (CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(j);
					if (pNameItem != NULL) 
					{
						selimage = CPlaceResource::GetListIconIndex(&(pNameItem->m_NameInfo));
						TVITEM item;
						item.hItem = pNameItem->m_hCurrentItem;
						item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
						item.iImage = selimage;
						item.iSelectedImage = selimage;
						TreeView_SetItem(m_hWnd, &item);
					}
				}
			}

			//for (INT_PTR i=0;i<pKindItem->m_ItemPtrArray.GetCount();i++)
			//{
			//	CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(i);
			//	if (pNameItem!=NULL)
			//	{
			//		selimage=CPlaceResource::GetListIconIndex(&(pNameItem->m_NameInfo));
			//		TVITEM item;
			//		item.hItem=pNameItem->m_hCurrentItem;
			//		item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE;
			//		item.iImage=selimage;
			//		item.iSelectedImage=selimage;
			//		TreeView_SetItem(m_hWnd,&item);
			//	}
			//}

			// end duanxiaohui
		}
	}
}
void CGameListCtrl::JoinAllItem(void)
{
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{

			CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
			if (pKindItem!=NULL)
			{
				for (INT_PTR i=0;i<pKindItem->m_ItemPtrArray.GetCount();i++)
				{
					CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(i);
					if (pNameItem!=NULL)
					{
						pNameItem->m_pTreeCtrl->Expand(pNameItem->m_hCurrentItem,TVE_COLLAPSE);
					}
				}
				pKindItem->m_pTreeCtrl->Expand(pKindItem->m_hCurrentItem,TVE_COLLAPSE);
			}
	}
	for (INT_PTR i=0;i< m_GameUrl.GetCount();i++)
	{
		CAFCGameUrlItem *q = (CAFCGameUrlItem *)m_GameUrl.GetAt(i);
		this->Expand(q->m_hCurrentItem, TVE_COLLAPSE);
	}
}
bool CGameListCtrl::ExpandAll(bool ExpName)
{
	CAFCGameListItem * pGameKindItem=GetKindParentItem();//获取根项
	for (INT_PTR i=0;i<pGameKindItem->m_ItemPtrArray.GetCount();i++)
	{
		CAFCKindItem * pKindItem=(CAFCKindItem *)pGameKindItem->m_ItemPtrArray.GetAt(i);
		if (pKindItem!=NULL)
		{
			for (INT_PTR i=0;i<pKindItem->m_ItemPtrArray.GetCount()&&ExpName;i++)
			{
				CAFCNameItem * pNameItem=(CAFCNameItem *)pKindItem->m_ItemPtrArray.GetAt(i);
				if (pNameItem!=NULL)
				{
					pNameItem->m_pTreeCtrl->Expand(pNameItem->m_hCurrentItem,TVE_EXPAND);
				}
			}
			pKindItem->m_pTreeCtrl->Expand(pKindItem->m_hCurrentItem,TVE_EXPAND);
		}
	}

	for (INT_PTR i=0;i< m_GameUrl.GetCount();i++)
	{
		CAFCGameUrlItem *q = (CAFCGameUrlItem *)m_GameUrl.GetAt(i);
		this->Expand(q->m_hCurrentItem, TVE_EXPAND);
	}
	///////////////////////////////////////////////////////////
	///Kylin 20090107  添加最近游戏列表

	if(Glb().m_baFavor.GetCount())
	{
		CAFCGameListItem * pGameKindItem=(CAFCGameListItem *)m_InsideArray.GetAt(0);//获取根项
		pGameKindItem->m_pTreeCtrl->Expand(pGameKindItem->m_hCurrentItem,TVE_EXPAND);
	}
	///////////////////////////////////////////////////////////

	return true;
}
BEGIN_MESSAGE_MAP(CFunListCtrl, CTreeCtrl)
END_MESSAGE_MAP()

//构造函数
CFunListCtrl::CFunListCtrl()
{
}

//析构函数
CFunListCtrl::~CFunListCtrl()
{
	return;
}
void CFunListCtrl::LoadSkin()
{
	//设置游戏列表数据
	UINT uIconIndex[]=
	{
		IND_LIST_ROOT,IND_ROOM_NO_ICON,IND_LIST_ROOT,IND_LIST_NO_INSTALL,
		IND_LIST_ROOT,IND_LIST_ROOT,IND_LIST_ROOT,
	};
	CString s=CBcfFile::GetAppPath();/////本地路径
	int nCount;
	CBcfFile f( s + "bzgame.bcf");
	CBcfFile fs(s + m_skinmgr.GetSkinBcfFileName());
	CString key=TEXT("GameListControl");

	int r,g,b;
	r=fs.GetKeyVal(key,"gamelbr",0);
	g=fs.GetKeyVal(key,"gamelbg",255);
	b=fs.GetKeyVal(key,"gamelbb",0);
	this->SetBkColor(RGB(r,g,b));

	nCount=f.GetKeyVal (Glb().m_key,"TreeCount3",0);
	for (int i=0;i<nCount;i++)
	{	
		CString msg,strIcon;
		UINT uTempIconIndex;

		msg.Format("Tree3Icon%d",i);
		strIcon=f.GetKeyVal(Glb().m_key,msg,"");
		uTempIconIndex=IND_LIST_ROOT;
		if(strIcon!="")
		{
			uTempIconIndex=CPlaceResource::LoadExtendIcon(strIcon);
			if(uTempIconIndex<1)
				uTempIconIndex=IND_LIST_ROOT;
		}
		//插入数据
		TV_INSERTSTRUCT InsertInf;
		memset(&InsertInf,0,sizeof(InsertInf));
		InsertInf.item.cchTextMax=100;
		InsertInf.hInsertAfter=TVI_LAST;
		InsertInf.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
		InsertInf.item.iImage=uTempIconIndex;
		InsertInf.item.iSelectedImage=uTempIconIndex;//选择根图标
		msg.Format("3Tree%d",i);
		CString temp=f.GetKeyVal (Glb().m_key,msg,"");
		//strncpy(InsertInf.item.pszText,strIcon,strIcon.GetLength());
		InsertInf.item.pszText=temp.GetBuffer();
		msg.Format("Tree3URLid%d",i);
		//CString temp2=f.GetKeyVal (Glb().m_key,msg,"");
		m_saUrl.Add(f.GetKeyVal (Glb().m_key,msg,""));
		InsertInf.item.lParam=(LPARAM)i;
		InsertItem(&InsertInf);
	}
}
bool CFunListCtrl::Init()
{
	//设置控件
	//SendMessage(SET_LINE_COLOR,0,(LPARAM)CGameImageLink::m_ColorResource.m_crListTxColor);

	//设置游戏列表数据
	UINT uIconIndex[]=
	{
		IND_LIST_ROOT,IND_ROOM_NO_ICON,IND_LIST_ROOT,IND_LIST_NO_INSTALL,
		IND_LIST_ROOT,IND_LIST_ROOT,IND_LIST_ROOT,
	};
	CString s=CBcfFile::GetAppPath();/////本地路径
	int nCount;
	CBcfFile f( s + "bzgame.bcf");

	CBcfFile fs(s + m_skinmgr.GetSkinBcfFileName());
	CString key=TEXT("GameListControl");

	int r,g,b;
	r=fs.GetKeyVal(key,"gamelbr",0);
	g=fs.GetKeyVal(key,"gamelbg",255);
	b=fs.GetKeyVal(key,"gamelbb",0);
	this->SetBkColor(RGB(r,g,b));

	nCount=f.GetKeyVal (Glb().m_key,"TreeCount3",0);
	for (int i=0;i<nCount;i++)
	{	
		CString msg,strIcon;
		UINT uTempIconIndex;

		msg.Format("Tree3Icon%d",i);
		strIcon=f.GetKeyVal(Glb().m_key,msg,"");
		uTempIconIndex=IND_LIST_ROOT;
		if(strIcon!="")
		{
			uTempIconIndex=CPlaceResource::LoadExtendIcon(strIcon);
			if(uTempIconIndex<1)
				uTempIconIndex=IND_LIST_ROOT;
		}
		//插入数据
		TV_INSERTSTRUCT InsertInf;
		memset(&InsertInf,0,sizeof(InsertInf));
		InsertInf.item.cchTextMax=100;
		InsertInf.hInsertAfter=TVI_LAST;
		InsertInf.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
		InsertInf.item.iImage=uTempIconIndex;
		InsertInf.item.iSelectedImage=uTempIconIndex;//选择根图标
		msg.Format("3Tree%d",i);
		CString temp=f.GetKeyVal (Glb().m_key,msg,"");
		//strncpy(InsertInf.item.pszText,strIcon,strIcon.GetLength());
		InsertInf.item.pszText=temp.GetBuffer();
		msg.Format("Tree3URLid%d",i);
		//CString temp2=f.GetKeyVal (Glb().m_key,msg,"");
		m_saUrl.Add(f.GetKeyVal (Glb().m_key,msg,""));
		InsertInf.item.lParam=(LPARAM)i;
		InsertItem(&InsertInf);
	}
	return true;
}

//树控件颜色控制
void   CGameListCtrl::SetItemFont(HTREEITEM   hItem,   LOGFONT&   logfont) 
{ 
	Color_Font   cf; 
	if(   !m_mapColorFont.Lookup(   hItem,   cf   )   ) 
		cf.color   =   (COLORREF)-1; 
	cf.logfont   =   logfont; 
	m_mapColorFont[hItem]   =   cf; 
} 

////////////////////////////////////////////////////////////////////// 
void   CGameListCtrl::SetItemBold(HTREEITEM   hItem,   BOOL   bBold) 
{ 
	SetItemState(hItem,   bBold   ?   TVIS_BOLD:   0,   TVIS_BOLD); 
} 

////////////////////////////////////////////////////////////////////// 
void   CGameListCtrl::SetItemColor(HTREEITEM   hItem,   COLORREF   color) 
{ 
	Color_Font   cf; 
	if(!m_mapColorFont.Lookup(hItem,   cf)) 
		cf.logfont.lfFaceName[0]   =   '\0 '; 
	cf.color   =   color; 
	m_mapColorFont[hItem]   =   cf; 
} 

void  CGameListCtrl::SetItemStatusColor(HTREEITEM hItem,UINT roomID,const COLORREF& color,const COLORREF& statusColor,const CString& strStatusText) 
{ 
	Color_Font   cf;
	cf.color = color;
	cf.logfont.lfFaceName[0]   = '\0';
	cf.statusfont.lfFaceName[0] = '\0';
	cf.statuscolor = statusColor;
	wsprintf(cf.statusfont.lfFaceName,"%s",strStatusText);
	
	m_mapHitemRoomID[hItem] = roomID;
	m_mapStatusColor[roomID] = cf;
}
////////////////////////////////////////////////////////////////////// 
BOOL   CGameListCtrl::GetItemFont(HTREEITEM   hItem,   LOGFONT   *   plogfont) 
{ 
	Color_Font   cf; 
	if(!m_mapColorFont.Lookup(hItem,   cf)) 
		return   FALSE; 
	if(cf.logfont.lfFaceName[0]   ==   '\0 ')   
		return   FALSE; 
	*plogfont   =   cf.logfont; 
	return   TRUE; 

} 

////////////////////////////////////////////////////////////////////// 
BOOL   CGameListCtrl::GetItemBold(HTREEITEM   hItem) 
{ 
	return   GetItemState(hItem,   TVIS_BOLD)   &   TVIS_BOLD; 
} 

////////////////////////////////////////////////////////////////////// 
COLORREF   CGameListCtrl::GetItemColor(HTREEITEM   hItem) 
{ 
	//   Returns   (COLORREF)-1   if   color   was   not   set 
	Color_Font   cf; 
	if(!m_mapColorFont.Lookup(hItem,   cf)) 
		return   (COLORREF)   -   1; 
	return   cf.color; 

} 

////////////////////////////////////////////////////////////////////// 
void CGameListCtrl::OnPaint() 
{ 
	CPaintDC dc(this); 

	// Create a memory DC compatible with the paint DC 
	CDC memDC; 
	memDC.CreateCompatibleDC(&dc); 

	CRect rcClip, rcClient; 
	dc.GetClipBox( &rcClip ); 
	GetClientRect(&rcClient); 

	// Select a compatible bitmap into the memory DC 
	CBitmap bitmap; 
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() ); 
	memDC.SelectObject( &bitmap ); 

	//dc.SetBkMode(TRANSPARENT);

	// Set clip region to be same as that in paint DC 
	CRgn rgn; 
	rgn.CreateRectRgnIndirect( &rcClip ); 
	memDC.SelectClipRgn(&rgn); 
	rgn.DeleteObject(); 

	// First let the control do its default drawing. 
	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0); 

	HTREEITEM hItem = GetFirstVisibleItem(); 

	int iItemCount = GetVisibleCount() + 1; 
	while(hItem && iItemCount--) 
	{ 
		CRect rect; 

		// Do not meddle with selected items or drop highlighted items 
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED; 
		Color_Font cf; 


		if ((GetItemState(hItem, selflag) & selflag) 
			&& ::GetFocus() == m_hWnd) 
			; 
		else if (m_mapColorFont.Lookup(hItem, cf)) 
		{ 
			CFont *pFontDC; 
			CFont fontDC; 
			LOGFONT logfont; 

			if(cf.logfont.lfFaceName[0] != '\0 ') 
				logfont = cf.logfont; 
			else { 
				// No font specified, so use window font 
				CFont *pFont = GetFont();
				pFont-> GetLogFont( &logfont ); 
			} 

			if(GetItemBold(hItem)) 
				logfont.lfWeight = 700; 

			fontDC.CreateFontIndirect(&logfont); 
			pFontDC = memDC.SelectObject(&fontDC ); 

			if(cf.color != (COLORREF) - 1) 
				memDC.SetTextColor(cf.color); 
			else 
				memDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT)); 


			CString sItem = GetItemText(hItem); 

			GetItemRect(hItem, &rect, TRUE); 
			//memDC.SetBkColor( GetSysColor(COLOR_WINDOW )); 
			memDC.SetBkMode(TRANSPARENT);
			memDC.TextOut(rect.left + 2, rect.top + 5, sItem); 

			memDC.SelectObject(pFontDC); 
		} 

		hItem = GetNextVisibleItem(hItem); 
	} 


	dc.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC, 
		rcClip.left, rcClip.top, SRCCOPY); 

	memDC.DeleteDC(); 
} 

// void CGameListCtrl::OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
// 	// TODO: Add your control notification handler code here
// 
// 	POINT pt = GetCurrentMessage()->pt; 
// 	ScreenToClient(&pt); 
// 
// 	TVHITTESTINFO tvht;
// 	tvht.pt = pt;
// 	HitTest(&tvht);
// 
// 	if (!GetParentItem(tvht.hItem))
// 	{
// 		*pResult = 0;
// 	}
// }

void CGameListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

  /*不同控件消息不同，如TreeView控件发送NM_CUSTOMDRAW通知码时，lParam指向的
    是NMTVCUSTOMDRAW结构体，这个结构体的第一个成员是NMCUSTOMDRAW结构体*/
    NMCUSTOMDRAW* pNMCustomDraw = (NMCUSTOMDRAW*)pNMHDR;
    NMTVCUSTOMDRAW* pNMTVCustomDraw = (NMTVCUSTOMDRAW*)pNMHDR;

	switch(pNMCustomDraw->dwDrawStage)
	{
	case CDDS_PREPAINT: //绘制循环开始时
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
		}
		break;

    case CDDS_ITEMPREPAINT :  //绘制item前，可绘制背景
        {
			//自己画，不发送NM_CUSTOMDRAW,绘制item后发送NM_CUSTOMDRAW
            HTREEITEM hItem = (HTREEITEM)pNMCustomDraw->dwItemSpec;
            //CRect rcItem = pNMCustomDraw->rc;

            CRect rtemp;
            GetItemRect(hItem,&rtemp,TRUE);

            if (rtemp.IsRectEmpty())
            {        
				//不需要重绘
                *pResult = CDRF_DODEFAULT;
                break;
            }
             *pResult = (CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT);
        }
        break;

	case CDDS_ITEMPOSTPAINT: //绘制item后
		{
			HTREEITEM hItem = (HTREEITEM)pNMCustomDraw->dwItemSpec;

			CDC dc;
			dc.Attach(pNMCustomDraw->hdc);

			CRect rcItem;
			int nImage,nImageSel;
			UINT uItemState;

			GetItemRect(hItem,&rcItem,FALSE);
			GetItemImage(hItem,nImage,nImageSel);
			uItemState = GetItemState(hItem,TVIS_EXPANDED);

			CPen pen;

			pen.CreatePen(PS_SOLID,1,m_crGridLine);
			CPen* pOldPen = dc.SelectObject(&pen);

			if (GetNextItem(hItem,TVGN_NEXTVISIBLE))
			{
				dc.MoveTo(rcItem.left,rcItem.bottom - 1);
				dc.LineTo(rcItem.right + 5,rcItem.bottom - 1);
			}

			dc.SelectObject(pOldPen);

			CRect rcDraw = rcItem;

			rcDraw.left = pNMTVCustomDraw->iLevel * 16 - 6;

			CFont* pFont = NULL;
			pFont = GetFont();
			LOGFONT lf;
			pFont->GetLogFont(&lf);

			if (pNMTVCustomDraw->iLevel == 0)
			{
				lf.lfHeight = 14;
				strcpy(lf.lfFaceName,_TEXT("黑体"));
				lf.lfWeight = 900;
			}
			else if (pNMTVCustomDraw->iLevel == 1)
			{
				lf.lfWeight = 900;
			}

			//鼠标在Item上方时
			if(pNMCustomDraw->uItemState & CDIS_HOT)
			{
				if (pNMTVCustomDraw->iLevel == 0)
				{
					dc.FillSolidRect(&rcItem,RGB(255,255,255));
					m_btRule.ShowWindow(SW_HIDE);
				}
				else
				{
					if (pNMTVCustomDraw->iLevel == 1)
					{
						dc.FillSolidRect(rcItem.left,rcItem.top,rcItem.right,rcItem.Height() - 1,m_crGridHotBk1);
						dc.SetTextColor(m_crGridHotTxt1);
						m_btRule.ShowWindow(SW_HIDE);
					}
					else
					{
						//遇到游戏名，显示阅读规则的按钮
						CAFCGameListItem * pGameItem=(CAFCGameListItem *)GetItemData(hItem);
						if (pGameItem != NULL && pGameItem->m_uDataType != GLK_GAME_NAME)
						{
							dc.FillSolidRect(rcItem.left,rcItem.top,rcItem.right,rcItem.Height() - 1,m_crGridHotBk1);
							dc.SetTextColor(m_crGridHotTxt1);
							m_btRule.ShowWindow(SW_HIDE);
						}
						else
						{
							dc.FillSolidRect(rcItem.left,rcItem.top,rcItem.right,rcItem.Height() - 1,m_crGridHotBk2);
							dc.SetTextColor(m_crGridHotTxt2);
							m_btRule.MoveWindow(rcItem.left + 200,rcItem.top + 2,60,18,TRUE);
							m_btRule.ShowWindow(SW_SHOW);
						}
					}
				}
			}
			else
			{
				if (pNMTVCustomDraw->iLevel == 0)
				{
					dc.FillSolidRect(rcItem.left,rcItem.top,rcItem.right,rcItem.Height(),RGB(255,255,255));
				}
				else
				{
					dc.FillSolidRect(rcItem.left,rcItem.top,rcItem.right,rcItem.Height() - 1,RGB(255,255,255));
				}
				
				dc.SetTextColor(RGB(0,0,0));
			}

			//画+-按钮
			if (ItemHasChildren(hItem) && pNMTVCustomDraw->iLevel > 0)
			{
				CGameImage* pImage = NULL;
				if (uItemState & TVIS_EXPANDED)
				{
					pImage = &m_imgFold;
				}
				else
				{
					pImage = &m_imgUnFold;
				}
				CGameImageHelper imgHelper(pImage);
				rcDraw.left;
				imgHelper.BitBlt(dc.GetSafeHdc(),rcDraw.left,rcDraw.top + 6);
			}

			//画Item Logo
 			rcDraw.left += 18;

			if (pNMTVCustomDraw->iLevel == 0)
			{
				CGameImageHelper heperRoot(&m_imgLogo);
				heperRoot.BitBlt(dc.GetSafeHdc(),rcDraw.left - 4,/*rcDraw.top + 1*/1);
			}
			else
			{
				CPoint pt(rcDraw.left,rcDraw.top + 4);
				CImageList* pImageList = CPlaceResource::GetGameListIcon();
				pImageList->Draw(&dc,nImage,pt,ILD_TRANSPARENT);
			}

			//画文字
			rcDraw.left += 20;
			CString strText = GetItemText(hItem);
			int nOldBkMode = dc.SetBkMode(TRANSPARENT);

			CFont newFont;
			newFont.CreateFontIndirect(&lf);
			CFont* pOldFont = dc.SelectObject(&newFont);

			if (pNMTVCustomDraw->iLevel == 0)
			{
				CRect rcDrawRoot(rcDraw);
				rcDrawRoot.top = 7;

				if (strText.Compare("游戏大厅") >= 0)
				{
					if(1 == CGamePlaceApp::GetModuleStatus(_T("GameList"),_T("IsShowOnLineCount"),0))
					{
						CString strOnLineUser;
						strOnLineUser.Format("[%d人]",GetMainRoom()->GetonlineUserCount());
						strText.Append(strOnLineUser);
						dc.DrawText(strText, &rcDrawRoot,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
					}
					else
					{
						dc.DrawText(strText, &rcDrawRoot,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
					}
				}
			}
			else
			{
				dc.DrawText(strText, &rcDraw,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
				std::map<void*,UINT>::iterator mapRoomIDIter =  m_mapHitemRoomID.find(hItem);
				if (mapRoomIDIter != m_mapHitemRoomID.end())
				{
					dc.SetTextColor(m_mapStatusColor[mapRoomIDIter->second].statuscolor);
					dc.DrawText(m_mapStatusColor[mapRoomIDIter->second].statusfont.lfFaceName, &rcDraw,DT_VCENTER|DT_SINGLELINE|DT_RIGHT|DT_END_ELLIPSIS);
				}
			}

			dc.SelectObject(pOldFont);
			dc.SetBkMode(nOldBkMode);

			//CGameImageHelper heperRoot(&m_imgAD);
			//heperRoot.BitBlt(dc.GetSafeHdc(),rcDraw.left,/*rcDraw.top + 1*/1);

			dc.Detach();

			*pResult = CDRF_NOTIFYITEMDRAW;
		}
		break;

	default:
		{
			*pResult = CDRF_DODEFAULT;      
		}
		break;
	}
}

BOOL CGameListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	// JianGuankun 2011.11.19
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	POINT pt = GetCurrentMessage()->pt; 
	ScreenToClient(&pt);

	TVHITTESTINFO tvht;
	tvht.pt = pt;
	HitTest(&tvht); 

	if(GetItemLevel(tvht.hItem) == 0) //列表标题不能点击
	{
		*pResult = 0;
		return FALSE;
	}

	if(!(tvht.flags & (TVHT_NOWHERE | TVHT_ONITEMBUTTON))) 
	{
// 		CString str;
// 		str.Format("UIClient:OnNMClick TVHT_ABOVE Text = %s tvht.flags = 0x%08x",GetItemText(tvht.hItem),tvht.flags);
// 		OutputDebugString(str);
		if (tvht.hItem)
		{
			Expand(tvht.hItem,TVE_TOGGLE);
		}
	}

	*pResult = 0;

	return FALSE;
}

BOOL CGameListCtrl::OnNMDlbClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	// JianGuankun 2011.11.19

	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	POINT pt = GetCurrentMessage()->pt; 
	ScreenToClient(&pt);

	TVHITTESTINFO tvht;
	tvht.pt = pt;
	HitTest(&tvht); 

	if(GetItemLevel(tvht.hItem) == 0) //列表标题不能点击
	{
		*pResult = 1;
		return FALSE;
	}

	*pResult = 0;

	return FALSE;
}

void CGameListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;

	//ScreenToClient(&pt); 

	TVHITTESTINFO tvht;
	tvht.pt = pt;
	HitTest(&tvht); 

	if (!(tvht.flags & TVHT_NOWHERE) && GetParentItem(tvht.hItem))
	{
		::SetCursor(m_curHand);
	}
	else
	{
		::SetCursor(m_curArrow);
		return;
	}

	if (tvht.hItem != m_hLastMMItem && m_hLastMMItem)
	{
		//if(!(tvht.flags & TVHT_ONITEM)) 
		{
			NMTVCUSTOMDRAW* ptvDraw = new NMTVCUSTOMDRAW();
			ptvDraw->nmcd.hdc = GetDC()->GetSafeHdc();
			ptvDraw->nmcd.dwDrawStage = CDDS_ITEMPOSTPAINT;
			ptvDraw->nmcd.uItemState |= CDIS_HOT;
			ptvDraw->nmcd.dwItemSpec = (DWORD_PTR)tvht.hItem;
			ptvDraw->iLevel = GetItemLevel(tvht.hItem);

			LRESULT lResult = 0;

			OnNMCustomdraw((NMHDR*)ptvDraw,&lResult);

			ptvDraw->nmcd.uItemState &= (~CDIS_HOT);
			ptvDraw->nmcd.dwItemSpec = (DWORD_PTR)m_hLastMMItem;
			ptvDraw->iLevel = GetItemLevel(m_hLastMMItem);

			lResult = 0;
			OnNMCustomdraw((NMHDR*)ptvDraw,&lResult);
		
			//::SendMessage(GetParent()->m_hWnd,NM_CUSTOMDRAW,IDC_GAME_LIST,(LPARAM)ptvDraw);

			//SendMessage(NM_CUSTOMDRAW,IDC_GAME_LIST,(LPARAM)ptvDraw);

			delete ptvDraw;

// 			CString str;
// 			str.Format("UIClient:OnNMClick OnMouseMove Text = %s tvht.flags = 0x%08x",GetItemText(tvht.hItem),tvht.flags);
// 			OutputDebugString(str);
		}
	}

	m_hLastMMItem = tvht.hItem;

	__super::OnMouseMove(nFlags, point);
}


void CGameListCtrl::OnClickReadRule()
{
	CPoint Point;
	GetCursorPos(&Point);
	ScreenToClient(&Point);
	HTREEITEM hItemHit = HitTest(Point);
	HTREEITEM hItemSel = GetSelectedItem();

	CAFCNameItem* pNameItem = (CAFCNameItem*)GetItemData(hItemHit);
	if (pNameItem != NULL)
	{
		CString strURL;
		if (pNameItem->m_NameInfo.uNameID!=0)
		{
			strURL.Format(TEXT("/app/showgame.%s?id=%d"),Glb().m_urlpostfix,pNameItem->m_NameInfo.uNameID);
			GetMainRoom()->IE(Glb().m_CenterServerPara.m_strWebRootADDR + strURL);
		}
	}
}

// void CGameListCtrl::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
// 	// TODO: Add your control notification handler code here
// 
// 	OutputDebugString("UIClient:OnTvnItemexpanded");
// 
// 	*pResult = 0;
// }
// 


