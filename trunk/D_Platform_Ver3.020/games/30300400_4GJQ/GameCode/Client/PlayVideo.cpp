#include "stdafx.h"
#include "PlayVideo.h"
#include "ClientView.h"
 
CPlayVideo*  CPlayVideo::m_pPlayVideo=NULL;

CPlayVideo::CPlayVideo()
{
	m_pPlayVideo=this;
}
CPlayVideo::~CPlayVideo()
{  if( NULL != m_pPlayVideo )
	Video_Release();
	m_pPlayVideo = NULL;
};

CPlayVideo*  CPlayVideo::CreatePlayVideo()
{
	 
	if(NULL != m_pPlayVideo)
		return m_pPlayVideo;
	else
	{
		 return NULL;
	}
}

bool  CPlayVideo::Video_Initialize( ST_INITVIDEO& stInitVideo)
{
	return __super::Video_Initialize( stInitVideo);
}

void	CPlayVideo::Video_Release()
{
	__super::Video_Release();   

}
 

/**
 * @param name, 玩家昵称;
 * @param rect, 此玩家视频窗口坐标;
 * @result 当成功输出　rect时，返回true,否则false;
 */

#ifdef	VIDEO
bool	CPlayVideo::GetVideoRectByName( CString name, RECT& rect, CString& pic)
{
	CClientPlayView *pPlayView=(CClientPlayView*)m_pParentWnd;
	ASSERT(pPlayView);
	if(pPlayView)
	{
	 
		return pPlayView->GetVideoRect( name, rect, pic);
		
	}
	else
		return false;
	 
}
#endif