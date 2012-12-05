#include"stdafx.h"
//声音类型设置
#define SOUND_WIN					0x01				//胜利
#define SOUND_LOSE					0x02				//输
#define SOUND_WAITING				0x03				//等待
#define SOUND_ERROR					0x04				//出牌出错了
#define SOUND_READY					0x05				//游戏开始
#define SOUND_START					0x06				//准备出第一手牌
#define SOUND_START_OUT_CARD		0x07				//出第一手牌
#define SOUND_JIAO_FEN				0x08				//叫分
#define SOUND_OUT_CARD_FINISH		0x09				//某玩家出牌結束
#define SOUND_GAME_PASS				0x0A				//不出
#define SOUND_FRIEND_APPEAR			0x0B				//盟友出現
#define SOUND_USER_RUNAWARY			0x0C				//有人逃跑
#define SOUND_USER_LEFT				0x0D				//有人离开
#define SOUND_GIVE_BACK				0x0E				//埋底
#define SOUND_HIT_CARD              0x11                //点击牌的声音
#define	SOUND_HIT_BEGIN             0x12                //点击开始按钮声音

#define SOUND_OUT_CARD				0x13				//出牌声音
#define SOUND_WARNING_5				0x14				//警告 5
#define SOUND_WARNING_4				0x15				//警告 4
#define SOUND_WARNING_3				0x16				//警告 3
#define SOUND_WARNING_2				0x17				//警告 2
#define SOUND_WARNING_1				0x18				//警告 1
#define SOUND_WARNING_0				0x19				//警告 0
#define SOUND_SEND_CARD				0x1A				//发牌声音
#define SOUND_OUT_CARD_DEF			0x1B				//默认出牌声音
#define SOUND_OUT_CARD_BOMB			0x1C				//出炸彈
#define SOUND_OUT_CARD_PASS			0x1D				//不出
#define SOUND_INVALIDATE			0x1E				//提示失败
#define SOUND_START_DEF				0x20				//四个人开始游戏后
#define SOUND_GAME_OVER				0x21				//游戏结束


#define SOUND_NO_POINT				   0x22			   //无点牌
#define SOUND_BULL_ONE                 0x23            //牛一
#define SOUND_BULL_TWO                 0x24            //牛二
#define SOUND_BULL_THREE               0x25            //牛三
#define SOUND_BULL_FOUR                0x26            //牛四
#define SOUND_BULL_FIVE                0x27            //牛五
#define SOUND_BULL_SIX                 0x28            //牛六
#define SOUND_BULL_SEVEN               0x29            //牛七
#define SOUND_BULL_EIGHT               0x2A            //牛八
#define SOUND_BULL_NINE                0x2B            //牛九
#define SOUND_BULL_BULL				   0x2C				//牛牛
#define SOUND_BULL_SILVER              0X2D            //银牛
#define SOUND_BULL_GOLD                0X2E            //金牛
#define SOUND_FIVE_SMALL               0X30            //五小
#define SOUND_BULL_BOMB                0X31            //炸弹

//add by xyh 2011-12-13
#define SOUND_GIVEUP_NT				   0X40				//放弃叫庄
#define SOUND_CALL_NT				   0X41				//叫庄
#define SOUND_USER_CHIP				   0X42				//玩家下注
#define SOUND_CHONG_PAI				   0X43				//重排
#define SOUND_TAN_PAI				   0X44				//摊牌
#define SOUND_USER_LEAVE			   0X45				//离开
#define SOUND_USER_CUE				   0X46				//提示


//按注类型(梭哈备用)
#define TYPE_GIVE_UP					0x00			//放弃
//#define TYPE_NOTE						0x01			//下注
#define TYPE_ADD						0x02			//加注
#define TYPE_FOLLOW						0x03			//跟注
#define TYPE_SHUTTLE					0x04			//梭哈
#define TYPE_NN                         0x05            //牛牛

//设置下注声音(专为梭哈准备)
BOOL SetNoteSound(BYTE bNoteStyle,BOOL bIsBoy);
//声音通用设置
BOOL SetPlaySound(BYTE bSoundType);
//出牌牌型声音設置
HWND SetOutCardTypeSound(BYTE iCardList[],int iCardCount,HWND hParent,BOOL IsBoy = true,BOOL IsFirest = TRUE);
//播放mp3声音
HWND PlayCardMusic(TCHAR FileName[],HWND hParent);
//播入场景声音
HWND SetSceneSound(BYTE iSceneSound,HWND hParent,BOOL IsBoy = TRUE,int iVal = -1);
