#ifndef _CONTROLID_FOR_LOGIC_UIGameCommNew_
#define _CONTROLID_FOR_LOGIC_UIGameCommNew_
///这是给逻辑用的控件信息，程序员可以按自己的习惯改里面的宏
///文件名格式为：生成的相应的控件信息文件名+ “_”+ControlDefines 
///宏    +    ID    +  控件名字  + 控件类型  + 资源路径

const int CTN_450 = 450;  ///<排队机  容器 
const int CTN_450_BTN_451 = 451;  ///<按钮返回大厅  按扭 resources\image\Bn_fhdt.png
const int CTN_450_ExAnimate_452 = 452;  ///<等待动画  外部动画控件 
const int CTN_450_IMG_1000031 = 1000031;  ///<防作弊背景  图片 resources\image\paohuzhibj_03.png

const int CTN_2 = 2;  ///<上边框  容器 
const int CTN_2_BTN_10 = 10;  ///<最小化按钮  按扭 resources\image\Bn_zhuixiaohua.png
const int CTN_2_BTN_11 = 11;  ///<关闭按钮  按扭 resources\image\Bn_close.png
const int NET_CONTROL = 1002443; ///网页空间
const int CTN_2_IMG_1002444 = 1002444;  ///<网络品质  图片 resources\image\Image_wlpz.png
const int CTN_2_Sudoku_1 = 1;  ///<边框  边框 
const int CTN_2_TEXT_1002440 = 1002440;  ///<欢迎文字  静态文本 

const int CTN_1000000 = 1000000;  ///<游戏  容器 

///游戏背景
const  int   IMG_BASE     = 1000001 ; 

///游戏设置相关
const   int      CONTAIN_GAME_SET             = 1000380 ; 
const   int      BTN_SET_VOICE                = 1000300 ; 
const   int      BTN_SET_BG_VOICE             = 1000310 ; 
const   int      BTN_SET_WATCH                = 1000320 ; 
const   int      BTN_SET_GAME_OK              = 1000330 ; 
const   int      BTN_SET_GAME_CANCEL          = 1000340 ; 
const   int      BTN_SET_GAME_INFO            = 1003500 ;


const int BTN_TRUSTEE = 1300051;  ///<托管  按扭 resources\image\Bn_tuoguan.png
const int BTN_TRUSTEE_CANCEL = 1300052;  ///<取消托管  按扭 resources\image\Bn_qxtg.png


const  int IMG_TRUSTEE1 = 1300060 ; 

///机场飞机
const  int   IMG_PLANE_0  = 1200000 ; 
const  int   IMG_PLANE_1  = 1200100 ; 
const  int   IMG_PLANE_2  = 1200200 ; 
const  int   IMG_PLANE_3  = 1200300 ; 

///中心基准图 
const  int   IMG_BASE_POINT = 1200400 ; 	     

///1200400 - 1200900留为克隆用
///巧借东风
const  int   BTN_PROP1    = 1200310 ; 
///桥接东风容器
const  int   CTN_PROP     = 1200330 ; 
///按钮0 - 5  
const  int	 BTN_SICE    = 1200311 ; 
///闹钟0-3
const  int   TIME_FRAME_0  = 1200340 ; 
///飞机克隆副本
const  int   IMG_PLANE0   = 1200000 ;
const  int   IMG_PLANE1   = 1200100 ; 
const  int   IMG_PLANE2   = 1200200 ; 
const  int   IMG_PLANE3   = 1200300 ;
///巧借东风标识0-3
const  int	 IMG_PROP_FLAG = 1200306 ; 
///准备标识0-3
const  int   IMG_READY_FLAG = 1200317 ; 
///	指示玩家下一步位置图标
const  int   IMG_NEXT_STEP  = 1300000 ; 
///移动色子动画
const  int	 MOVE_DICE_ANI  = 1300005 ; 
///色子动画
const  int   EXT_ANI_DICE   = 1300010 ;
///闪烁动画1300011 -1300014
const  int   EX_ANI_HIGTLIGHT = 1300011 ; 

const  int	 EX_PLANE_BOMB   = 1300030 ; 

///玩家击落飞机记录
const  int   STATIC_TEXT_NAME_0    = 1300032 ; 
const  int   STATIC_TEXT_NAME_1    = 1300033 ; 
const  int   STATIC_TEXT_NAME_2    = 1300034 ; 
const  int   STATIC_TEXT_NAME_3    = 1300035 ;
///击落
const  int   STATIC_TEXT_SCORE_0   = 1300036 ;
const  int   STATIC_TEXT_SCORE_1   = 1300037 ;

///游戏结束图片标识
const  int   IMAGE_GAME_OVER       = 1300040 ;  ///游戏结束

///游戏中的瞄准图片
const  int   IMAGE_AIM_PLANE       =  1300050  ; ///瞄准


#endif ///< _CONTROLID_FOR_LOGIC
