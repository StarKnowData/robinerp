#include "StdAfx.h"
#include ".\chessmanual.h"
#include "ClientGameDlg.h"

CChessManual::CChessManual():CGameFaceGo(CChessManual::IDD)
, m_strQiPu(_T(""))
{
	m_pParnet=NULL;
	m_iBuCount = 1;
	m_iFlag = 0;
	m_szString.Empty();
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\renshu.bmp"),SKIN_FOLDER);
	m_bk.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
}

CChessManual::~CChessManual(void)
{
}

BOOL CChessManual::OnInitDialog()
{
	CGameFaceGo::OnInitDialog();
	SetWindowPos(&wndBottom,0,0,m_bk.GetWidth(),m_bk.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	
	TCHAR path[MAX_PATH] = {0};
	wsprintf(path,TEXT("image\\%s\\agree_bt.bmp"),SKIN_FOLDER);
	m_btOk.LoadButtonBitmap(path,false);
	wsprintf(path,TEXT("image\\%s\\oppose.bmp"),SKIN_FOLDER);
	m_btCancel.LoadButtonBitmap(path,false);
	if(m_btOk.GetSafeHwnd())
	{
		m_btOk.MoveWindow(54,100,46,20,false);
		m_btCancel.MoveWindow(143,100,46,20,false);
	}
	return TRUE;
}
BEGIN_MESSAGE_MAP(CChessManual, CGameFaceGo)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CChessManual::OnPaint()
{
	CPaintDC dc(this);
	CGameImageHelper handle(&m_bk);
	handle.BitBlt(dc,0,0);

	LPCTSTR pstr = m_szString.GetBuffer();
	if (pstr != NULL) pstr += TEXT('\0');
	m_szString.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_QIPU)->SetWindowText(pstr);
}


void CChessManual::ClearAll()
{
	m_iBuCount = 1;
	m_iFlag = 0;
	m_szString.Empty();
}

void CChessManual::GetCharSet(int iOrder, CString &str)
{
	str.Empty();
	switch (iOrder)
	{
	case 1:
		str = TEXT("一");
		break;

	case 2:
		str = TEXT("二");
		break;

	case 3:
		str = TEXT("三");
		break;

	case 4:
		str = TEXT("四");
		break;

	case 5:
		str = TEXT("五");
		break;

	case 6:
		str = TEXT("六");
		break;

	case 7:
		str = TEXT("七");
		break;

	case 8:
		str = TEXT("八");
		break;

	case 9:
		str = TEXT("九");
		break;
	}
}



void CChessManual::SetQiPu(int iStartI, int iStartJ, int iEndI, int iEndJ, int iQiZi, int type,int iMeFlag)
{
	/*CString str;
	CString s;
	m_iFlag++;
	if (m_iFlag % 3 == 0) 
	{
		m_iBuCount++;
		m_iFlag = 0;
		m_iFlag++;
	}
	
	if (m_iBuCount < 10) s.Format("  %d",m_iBuCount);
	else s.Format("%d",m_iBuCount);

	str = s;
	if (type == XQ_FLAG_RED)
		{	
			if (iMeFlag == XQ_FLAG_BLACK)
			{
				iStartI = 9 - iStartI;
				iEndI = 9 - iEndI;
				iStartJ = 9 - iStartJ -1 ;//+	1;
				iEndJ = 9 - iEndJ - 1;//+ 1;
			}
			str += TEXT("红：");
			switch (iQiZi)
			{
			case XQ_RED_JU:
				str += TEXT("车");
				
				GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI == iEndI)
				{
					str += TEXT("平");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				else
				{
					if (iStartI > iEndI)
					{
						str += TEXT("进");
						GetCharSet(iStartI-iEndI,s);
						str += s;
					}
					else
					{
						str += TEXT("退");
						GetCharSet(iEndI-iStartI,s);
						str += s;
					}
				}
				break;
				
			case XQ_RED_MA:
				str += TEXT("马");
			///	CString s;
				GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI > iEndI)
				{
					str += TEXT("进");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				else
				{
					str += TEXT("退");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				break;

			case XQ_RED_PAO:
				str += TEXT("炮");
			///	CString s;
				GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI == iEndI)
				{
					str += TEXT("平");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				else
				{
					if (iStartI > iEndI)
					{
						str += TEXT("进");
						GetCharSet(iStartI-iEndI,s);
						str += s;
					}
					else
					{
						str += TEXT("退");
						GetCharSet(iEndI-iStartI,s);
						str += s;
					}
				}
				break;

			case XQ_RED_BIN:
				str += TEXT("兵");
		//		CString s;
				GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI > 4)//未过河
				{
					str += TEXT("进一");
				}
				else //过河
				{
					if (iStartI == iEndI)
					{
						str += TEXT("平");
						GetCharSet(9-iEndJ,s);
						str += s;
					}
					else
					{
						str += TEXT("进一");
					}
				}
				break;

			case XQ_RED_JIANG:
				str += TEXT("帅");
	//			CString s;
				GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI == iEndI)
				{
					str += TEXT("平");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				else
				{
					if (iStartI > iEndI)
					{
						str += TEXT("进一");
					}
					else
					{
						str += TEXT("退一");
					}
				}
				break;

			case XQ_RED_SHI:
				str += TEXT("士");
	//			CString s;
				GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI > iEndI)
				{
					str += TEXT("进");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				else
				{
					str += TEXT("退");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				break;

			case XQ_RED_XIANG:
				str += TEXT("相");
	//			CString s;
				GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI > iEndI)
				{
					str += TEXT("进");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				else
				{
					str += TEXT("退");
					GetCharSet(9-iEndJ,s);
					str += s;
				}
				break;
			}
		}

	if (type == XQ_FLAG_BLACK)
		{
			if (iMeFlag == XQ_FLAG_RED)
			{
				iStartI = 9 - iStartI;
				iEndI = 9 - iEndI;
				iStartJ = 9 - iStartJ - 1;//+ 1;
				iEndJ = 9 - iEndJ - 1;//+ 1;
			}
			str += TEXT("黑：");
			switch (iQiZi)
			{
			case XQ_BLACK_JU:
				str += TEXT("车");
				//CString s;
				s.Format(" %d ",9-iStartJ);
				str += s;
				if (iStartI == iEndI)
				{
					str += TEXT("平");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				else
				{
					if (iStartI > iEndI)
					{
						str += TEXT("进");
						s.Format(" %d ",iStartI-iEndI);
						str += s;
					}
					else
					{
						str += TEXT("退");
						s.Format(" %d ",iEndI-iStartI);
						str += s;
					}
				}
				break;
					
			case XQ_BLACK_MA:
				str += TEXT("马");
	//			CString s;
				s.Format(" %d ",9-iStartJ);
				str += s;
				if (iStartI > iEndI)
				{
					str += TEXT("进");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				else
				{
					str += TEXT("退");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				break;

			case XQ_BLACK_PAO:
				str += TEXT("炮");
	//			CString s;
				s.Format(" %d ",9-iStartJ);
				str += s;
				if (iStartI == iEndI)
				{
					str += TEXT("平");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				else
				{
					if (iStartI > iEndI)
					{
						str += TEXT("进");
						s.Format(" %d ",iStartI-iEndI);
						str += s;
					}
					else
					{
						str += TEXT("退");
						s.Format(" %d ",iEndI-iStartI);
						str += s;
					}
				}
				break;

			case XQ_BLACK_BIN:
				str += TEXT("卒");
	//			CString s;
				s.Format(" %d ",9-iStartJ);
				str += s;
				if (iStartI > 4)//未过河
				{
					str += TEXT("进 1");
				}
				else //过河
				{
					if (iStartI == iEndI)
					{
						str += TEXT("平");
						s.Format(" %d ",9-iEndJ);
						str += s;
					}
					else
					{
						str += TEXT("进 1");
					}
				}
				break;

			case XQ_BLACK_JIANG:
				str += TEXT("将");
	//			CString s;
				s.Format(" %d ",9-iStartJ);
				str += s;
				if (iStartI == iEndI)
				{
					str += TEXT("平");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				else
				{
					if (iStartI > iEndI)
					{
						str += TEXT("进 1");
					}
					else
					{
						str += TEXT("退 1");
					}
				}
				break;

			case XQ_BLACK_SHI:
				str += TEXT("士");
	//			CString s;
				s.Format(" %d ",9-iStartJ);//GetCharSet(9-iStartJ,s);
				str += s;
				if (iStartI > iEndI)
				{
					str += TEXT("进");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				else
				{
					str += TEXT("退");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				break;

			case XQ_BLACK_XIANG:
				str += TEXT("象");
	//			CString s;
				s.Format(" %d ",9-iStartJ);
				str += s;
				if (iStartI > iEndI)
				{
					str += TEXT("进");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				else
				{
					str += TEXT("退");
					s.Format(" %d ",9-iEndJ);
					str += s;
				}
				break;
			}

		}

	str += TEXT("\r\n");
	m_szString += str;*/
	///m_strQiPu = m_szString;
	///UpdateData();
	return;
}


void CChessManual::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CGameFaceGo::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_QIPU, m_strQiPu);
}
