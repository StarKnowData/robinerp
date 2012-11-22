//会员  订单  留言   棋牌室

var toptabmenu = [
{ 'id': '1', 'title': '会    员', 'mainmenulist': '1', 'mainmenuidlist': '1010', 'defaulturl': '../AdminControl/UserInfo.aspx', 'system': '1' },
{ 'id': '2', 'title': '订    单', 'mainmenulist': '2', 'mainmenuidlist': '2010', 'defaulturl': '../AdminControl/DingDan.aspx', 'system': '1' },
{ 'id': '3', 'title': '棋牌室', 'mainmenulist': '3', 'mainmenuidlist': '3010', 'defaulturl': '../AdminControl/Qps.aspx', 'system': '1' },
{ 'id': '4', 'title': '留    言', 'mainmenulist': '4', 'mainmenuidlist': '4010', 'defaulturl': '../AdminControl/LeaveWord.aspx', 'system': '1' },
//{'id': '5', 'title': '首页幻灯片', 'mainmenulist': '6', 'mainmenuidlist': '6010', 'defaulturl': '../AdminControl/ImagesList.aspx', 'system': '1' },
//{ 'id': '6', 'title': '友情链接', 'mainmenulist': '7', 'mainmenuidlist': '7010', 'defaulturl': '../AdminControl/LinkList.aspx', 'system': '1' }
];
var mainmenu = [
{ 'id': '1', 'menuid': '1010', 'menutitle': '会    员' },
{ 'id': '2', 'menuid': '2010', 'menutitle': '订    单' },
{ 'id': '3', 'menuid': '3010', 'menutitle': '棋牌室' },
{ 'id': '4', 'menuid': '4010', 'menutitle': '留    言' }
//{ 'id': '5', 'menuid': '5010', 'menutitle': '院友注册' }
//{ 'id': '6', 'menuid': '6010', 'menutitle': '首页幻灯片' },
//{ 'id': '7', 'menuid': '7010', 'menutitle': '友情链接' }
];
var submenu = [
{ 'menuparentid': '1010', 'menutitle': '会    员', 'link': '../AdminControl/UserInfo.aspx', 'frameid': 'main' },
{ 'menuparentid': '2010', 'menutitle': '订    单', 'link': '../AdminControl/DingDan.aspx', 'frameid': 'main' },
{ 'menuparentid': '3010', 'menutitle': '棋牌室', 'link': '../AdminControl/Qps.aspx', 'frameid': 'main' },
{ 'menuparentid': '4010', 'menutitle': '留    言', 'link': '../AdminControl/LeaveWord.aspx', 'frameid': 'main' }


//{ 'menuparentid': '5010', 'menutitle': '注册成员', 'link': '../AdminControl/PartReg.aspx', 'frameid': 'main' }
//{ 'menuparentid': '6010', 'menutitle': '幻灯片列表', 'link': '../AdminControl/ImagesList.aspx', 'frameid': 'main' },
//{ 'menuparentid': '7010', 'menutitle': '友情链接列表', 'link': '../AdminControl/LinkList.aspx', 'frameid': 'main' }


];
var shortcut = []