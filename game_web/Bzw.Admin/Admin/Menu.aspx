1<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Menu" CodeBehind="Menu.aspx.cs" %>

<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>后台管理</title>

    <script type="text/ecmascript" language="javascript1.2">
        function showsubmenu(sid) {
            whichEl = eval('submenu' + sid);
            if (whichEl.style.display == 'none') {
                eval("submenu" + sid + ".style.display='';");
            }
            else {
                eval("submenu" + sid + ".style.display='none';");
            }
        }
        
    </script>

    <link href="css/left_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        .STYLE1
        {
            color: #FF0000;
        }
    </style>
</head>
<body>
    <table width="158" border='0' align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td height="50" valign="top">
                <img src='Images/title.gif'>
            </td>
        </tr>
    </table>
    <table cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/title_bg_quit.gif' id='menuTitle0'>
                <a href='Serverinfo.aspx' target='main'><b><span class='glow'>管理首页</span></b></a><span
                    class='glow'> | </span>&nbsp;<a href='Admin_Logout.aspx' target='_top' onclick='{if(confirm("确定要退出吗?")){return true;}return false;}'><b><span
                        class='glow'>退出</span></b></a>
            </td>
        </tr>
        <tr>
            <td style='display: ' id='submenu0'>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                欢迎您，<b><%=AdminInfo["UserName"].ToString() %></b>
                            </td>
                        </tr>
                        <%=(GetSession != "2" ? string.Empty : "<tr><td height=20><font color='#FF0000'><a href='UserAdmin/Add_AdminUser.aspx' target='main'>◆&nbsp;管理员管理 </a></font></td></tr>")%>
                        <%=(GetSession != "2" ? string.Empty : "<tr><td height=20><font color='#FF0000'><a href='UserAdmin/UpdateLoginName.aspx' target='main'>◆&nbsp;修改默认登录名 </a></font></td></tr>")%>
                        <%=(GetSession!="2"?string.Empty:"<tr><td height=20><font color='#FF0000'><a href='UserAnaly/Add_AnalyUser.aspx' target='main'>◆&nbsp;运营系统用户管理</a></font></td></tr>") %>
                        <%=(GetSession!="2"?string.Empty:"<tr><td height=20><a href='UserAdmin/ConfigEncryption.aspx' target='main'>◆&nbsp;加密/解密数据库链接 </a></td></tr>" )%>
                        <tr>
                            <td height="20">
                                <font color='#FF0000'><a href="SConfig/AdminModifyLog.aspx" target="main">◆&nbsp;系统日志</a></font>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <table cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_02.gif' id="menuTitle203" onclick='showsubmenu(203)'
                style='cursor: hand;'>
                <span class="glow">网站信息管理</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu203'>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr id="Tr1">
                            <td height="20">
                                <a href="SConfig/SEO_Opera.aspx" target="main">◆&nbsp;SEO内容设置 </a>
                            </td>
                        </tr>
                        <tr id="table_01">
                            <td height="20">
                                <font color='#FF0000'><a href='FlashAd/FlashAd.aspx' target='main'>◆&nbsp;首页Flash管理
                                </a></font>
                            </td>
                        </tr>
                        <tr id="table_02">
                            <td height="20">
                                <a href='Books/Book.aspx' target='main'>◆&nbsp;玩家留言管理 </a>
                            </td>
                        </tr>
                        <tr id="table_03">
                            <td height="20">
                                <a href="SConfig/systems.aspx" target="main">◆&nbsp;网站参数设置 </a>
                            </td>
                        </tr>
                        <tr id="Tr3">
                            <td height="20">
                                <a href="SConfig/Accept.aspx" target="main">◆&nbsp;服务条款设置 </a>
                            </td>
                        </tr>
                        <tr id="Tr4">
                            <td height="20">
                                <a href="SConfig/ServiceContent.aspx" target="main">◆&nbsp;客服中心内容设置 </a>
                            </td>
                        </tr>
                        <tr id="Tr2">
                            <td height="20">
                                <a href="SConfig/GameAdSetting.aspx" target="main">◆&nbsp;游戏广告位管理 </a>
                            </td>
                        </tr>
                        <%-- <tr><td height="20"><a href="FasciExchange/FasciExchange.aspx" target="main">◆&nbsp;魅力兑换管理 </a></td></tr>--%>
                        <tr>
                            <td height="20">
                                <a href="SConfig/AdminMsgList.aspx" target="main">◆&nbsp;系统信息发送管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="News/News.aspx" target="main">◆&nbsp;新闻管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="serverinfo.aspx" target="main">◆&nbsp;服务器信息</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/SystemStatEveryDay.aspx" target="main">◆&nbsp;今日系统信息统计</a>
                            </td>
                        </tr>
                        <%--<tr id="Tr2"><td height="20"><a href="Friend/Default.aspx" target="main">◆&nbsp;友情链接管理 </a></td></tr>--%>
                        <%--<tr id="Tr5"><td height="20"><a href="SConfig/YeepayPhonePayInfoSet.aspx" target="main">◆&nbsp;易宝短信充值说明 </a></td></tr>--%>
                        <tr>
                            <td height="20">
                                <a href='SConfig/ClearList.aspx' target='main'>◆&nbsp;清理表数据 </a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <!--用户管理中心-->
    <table id="table_04" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_03.gif' id="menuTitle206" onclick='showsubmenu(206)'
                style='cursor: hand;'>
                <span class="glow">用户管理中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu206'>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                <a href="FineryID/FineryID.aspx" target="main">◆&nbsp;靓号管理 </a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/CreateUser.aspx" target="main">◆&nbsp;新增用户</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/Users_Seach.aspx" target="main">◆&nbsp;搜索站内会员</a>
                            </td>
                        </tr>
                         <tr>
            <td height="20"><a href="Users/UserPointList.aspx" target="main">◆&nbsp;用户积分管理</a></td>
          </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/User_List.aspx?id=1" target="main">◆&nbsp;今日注册用户</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/UserIp_Seach.aspx" target="main">◆&nbsp;注册IP查询</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/UserIP_top.aspx" target="main">◆&nbsp;注册IP（Top100）</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/UserLoginSearch.aspx" target="main">◆&nbsp;游戏登录记录查询</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/Pictures.aspx" target="main">◆&nbsp;用户照片审核</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/ClearLoginInfo.aspx" target="main">◆&nbsp;解除用户登录限制</a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <!--充值管理中心-->
    <table id="table_05" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_4.gif' id="menuTitle202" onclick='showsubmenu(202)'
                style='cursor: hand;'>
                <span class="glow">充值管理中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu202'>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                <a href="Pay/Rate.aspx" target="main">◆&nbsp;金币兑换比例设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Pay/Pay.aspx?pay=1" target="main">◆&nbsp;点卡充值管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Pay/PayBank.aspx" target="main">◆&nbsp;网上支付充值记录</a>
                            </td>
                        </tr>
                        <%if (ConfigurationManager.AppSettings["IsPayToPoint"] == "1")
                          { %>
                        
                        <tr>
                            <td height="20">
                                <a href="Pay/PayToPoint.aspx" target="main">◆&nbsp;充值积分记录</a>
                            </td>
                        </tr>
                        <%} %>
                        <tr>
                            <td height="20">
                                <a href="Pay/FreeCardCount.aspx" target="main">◆&nbsp;赠送免费卡数量设置</a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <!--游戏管理中心-->
    <table id="table_06" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_9.gif' id="menuTitle301" onclick='showsubmenu(301)'
                style='cursor: hand;'>
                <span class="glow">游戏管理中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu301'>
                <div class="sec_menu" style='width: 158'>
                    <table width="130" align="center" cellpadding="0" cellspacing="0">
                        <tr>
                            <td height="20">
                                <a href="Games/GameTypes.aspx" target="main">◆&nbsp;游戏类别管理 </a><a href="Games/GameTypesAdd.aspx"
                                    target="main" class="menu">添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Games/GameNames.aspx" target="main">◆&nbsp;游戏信息管理 </a><a href="Games/GameNamesAdd.aspx"
                                    target="main">添加</a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td>
                                <a href="Games/GameRooms.aspx" target="main" class="menu" style="color: #000000">◆&nbsp;游戏房间管理
                                </a><a href="Games/GameRoomsAdd.aspx" target="main" class="menu">添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a class="menu" href="Games/GameBattleRooms.aspx" style="color: #000000" target="main">
                                    ◆&nbsp;混战房间管理 </a><a class="menu" href="Games/GameBattleRoomsWrite.aspx" target="main">
                                        添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a class="menu" href="Games/GameContestRooms.aspx" style="color: #000000" target="main">
                                    ◆&nbsp;比赛房间管理 </a><a class="menu" href="Games/GameContestRoomsWrite.aspx" target="main">
                                        添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20px">
                                <a target="main" href="Games/ApplyRoomList.aspx">◆&nbsp;租赁房间列表</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="GameInfo/GameBigTing.aspx" target="main">◆&nbsp;游戏大厅管理</a>
                            </td>
                        </tr>
                        <%--<tr>
          <td height="20"><a href="GameInfo/GameType.aspx" target="main">◆&nbsp;类别管理</a> <a href="GameInfo/GameType_Add.aspx" target="main"> 添加</a></td>
        </tr>--%>
                        <tr>
                            <td height="20">
                                <a href="GameInfo/GameMain.aspx" target="main">◆&nbsp;游戏规则</a> <a href="GameInfo/GameMain_Add.aspx"
                                    target="main">添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/FilterGameName.aspx" target="main">◆&nbsp;累积游戏时长设置</a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <!--比赛管理中心-->
    <table id="table_18" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_9.gif' id='Td2' onclick='showsubmenu(305)' style='cursor: hand;'>
                <span class="glow">比赛管理中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu305'>
                <div class="sec_menu" style='width: 158'>
                    <table width="130" align="center" cellpadding="0" cellspacing="0">
                        <tr>
                            <td height="20">
                                <a href="SConfig/MatchSendType.aspx" target="main">◆&nbsp;奖励方案名设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/MatchSendLotteries.aspx" target="main">◆&nbsp;赠送奖券设置</a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <!--代理商帐号管理-->
    <table id="table_17" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_9.gif' id='menuTitle304' onclick='showsubmenu(304)'
                style='cursor: hand;'>
                <span class="glow">代理商帐号管理</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu304'>
                <div class="sec_menu" style='width: 158'>
                    <table width="130" align="center" cellpadding="0" cellspacing="0">
                        <tr>
                            <td height="20">
                                <a href="Agency/AgencyView.aspx" target="main">◆&nbsp;代理商帐号管理</a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <!--转账管理中心-->
    <table id="table_08" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height='25' class='menu_title' onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_4.gif' id='menuTitle2002' onclick='showsubmenu(2002)'
                style='cursor: hand;'>
                <span class="glow">转账管理中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu2002'>
                <div class="sec_menu" style="width: 158">
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                <a href="SConfig/Transfers.aspx" target="main">◆&nbsp;转账参数设置 </a>
                            </td>
                        </tr>
                        <%--  <tr>
          <td height="20"><a href="Trans/Trans.aspx" target="main">◆&nbsp;所有记录列表</a></td>
        </tr>--%>
                        <tr>
                            <td height="20">
                                <a href="Trans/TransSeach.aspx" target="main">◆&nbsp;转账记录搜索</a>
                            </td>
                        </tr>
                        <%-- <tr>
          <td height="20"><a href="Trans/Trans.aspx?time=24" target="main">◆&nbsp;24小时转账记录</a></td>
        </tr>--%>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <%--记录查询中心--%>
    <table id="table_09" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_9.gif' id="menuTitle3030" onclick='showsubmenu(3003)'
                style='cursor: hand;'>
                <span class="glow">记录查询中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu3003'>
                <div class="sec_menu" style='width: 158'>
                    <table width="130" align="center" cellpadding="0" cellspacing="0">
                        <tr>
                            <td height="20">
                                <a href="Users/UserGameSeach.aspx" target="main">◆&nbsp;游戏记录查询</a>
                            </td>
                        </tr>
                        <!--tr height="20">
            <td height="20"><a href="Users/UserMoneySeach.aspx" target="main">◆&nbsp;转帐记录查询</a></td>
          </tr-->
                        <tr>
                            <td height="20">
                                <a href="Users/UserRoomSeach.aspx" target="main">◆&nbsp;房间记录查询</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/ClearGameRecord.aspx" target="main">◆&nbsp;清理游戏记录</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/MoneyStatiEveryday.aspx" target="main">◆&nbsp;每天金币统计</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/TaxStatiEveryday.aspx" target="main">◆&nbsp;游戏<%=UiCommon.StringConfig.RoomTaxName %>统计</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/SystemStat.aspx" target="main">◆&nbsp;系统信息统计</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/SystemStatEveryDay.aspx" target="main">◆&nbsp;今日系统信息统计</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/UsersMoneyChangeLog.aspx" target="main">◆&nbsp;金币变化日志</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/UserReceiveMoneyList.aspx" target="main">◆&nbsp;领取金币日志</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/UserSendMoneyLog.aspx" target="main">◆&nbsp;时长,局数金币日志</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Users/UserGameMoneyLog.aspx" target="main">◆&nbsp;玩家游戏输赢统计</a>
                            </td>
                        </tr>
                        <%if (UiCommon.StringConfig.BankVersion == "2")
                          { %>
                        <tr>
                            <td height="20">
                                <a href="Users/UserBankDeposit.aspx" target="main">◆&nbsp;用户存单记录</a>
                            </td>
                        </tr>
                        <%} %>
                        <tr>
                            <td height="20">
                                <a href="Users/UserLoterriesLog.aspx" target="main">◆&nbsp;用户<%=UiCommon.StringConfig.GoldName %>变化日志</a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <%--新闻管理中心--%>
    <%--<table id="table_10" cellpadding="0" cellspacing="0" width="158" align="center">
  <tr>
    <td height="25" class="menu_title" onmouseover=this.className='menu_title2'; onmouseout=this.className='menu_title'; background='Images/Admin_left_9.gif' id=menuTitle3002 onclick='showsubmenu(3002)' style='cursor:hand;'><span class=glow>新闻管理中心</span></td>
  </tr>
  <tr>
    <td style='display:none' id='submenu3002'>
    <div class=sec_menu style='width:158'>
        <table width=130 align="center" cellpadding="0" cellspacing="0">
           <tr height="20">
            <td><a href="News/NewsType.aspx" target="main" class="menu" style="color: #000000">◆&nbsp;新闻类别管理</a> <a href="News/NewsTypeAdd.aspx" target="main"> 添加 </a>  </td>
          </tr>
          <tr height="20">
            <td><a href="News/News.aspx" target="main" class="menu" style="color: #000000">◆&nbsp;新闻管理</a>  <a href="News/News_Add.aspx" target="main" >  添加  </a></td>
          </tr>
         
		
        </table>
      </div>
        <div  style='width:158'>
          <table cellpadding="0" cellspacing="0" align="center" width=130>
            <tr>
              <td height="2"></td>
            </tr>
          </table>
      </div></td>
  </tr>
</table>--%>
    <%--道具管理中心--%>
    <table id="table_15" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_9.gif' id="Td1" onclick='showsubmenu(3022)' style='cursor: hand;'>
                <span class="glow">道具管理中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu3022'>
                <div class="sec_menu" style='width: 158'>
                    <table width="130" align="center" cellpadding="0" cellspacing="0">
                        <tr>
                            <td height="20">
                                <a href="SConfig/JpPrices.aspx" target="main">◆&nbsp;道具价格设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/DaoJuLog.aspx" target="main">◆&nbsp;道具购买记录</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/PropStatistic.aspx" target="main">◆&nbsp;道具每日消耗统计</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/Prices.aspx" target="main">◆&nbsp;VIP购买价格设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/PFPrices.aspx" target="main">◆&nbsp;魅力值清零道具设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/DaoJuFasciLog.aspx" target="main">◆&nbsp;魅力值清零道具记录</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Cloth/ClothesList.aspx" target="main">◆&nbsp;服装列表 </a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <!--魅力兑换管理中心-->
    <table id="table_16" align="center" cellpadding="0" cellspacing="0" width="158">
        <tr>
            <td id="menuTitle329" background='Images/Admin_left_9.gif' class="menu_title" height="25"
                onclick='showsubmenu(329)' style='cursor: pointer;'>
                <span class="glow">魅力兑换管理中心</span>
            </td>
        </tr>
        <tr>
            <td id='submenu329' style='display: none'>
                <div class="sec_menu" style='width: 158'>
                    <table align="center" cellpadding="0" cellspacing="0" width="130">
                        <tr height="20">
                            <td>
                                <a class="menu" href="FasciExchange/FasciPropAdd.aspx" style="color: #000000" target="main">
                                    ◆&nbsp;添加魅力兑换金币道具</a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td>
                                <a class="menu" href="FasciExchange/FasciExchange.aspx" style="color: #000000" target="main">
                                    ◆&nbsp;魅力兑换管理 </a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td>
                                <a href="FasciExchange/FasciExchangeLog.aspx" target="main">◆&nbsp;魅力兑换记录 </a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table align="center" cellpadding="0" cellspacing="0" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <%-- 靓号管理中心 --%>
    <%--<table id="table2" cellpadding="0" cellspacing="0" width="158" align="center">
  <tr>
    <td height="25" class="menu_title" onmouseover=this.className='menu_title2'; onmouseout=this.className='menu_title'; background='Images/Admin_left_9.gif' id=Td3 onclick='showsubmenu(303)' style='cursor:hand;'><span class=glow>靓号管理中心</span></td>
  </tr>
  <tr>
    <td style='display:none' id='submenu303'><div class=sec_menu style='width:158'>
      <table width=130 align="center" cellpadding="0" cellspacing="0">
    
        
           </table>
    </div>
        <div  style='width:158'>
          <table cellpadding="0" cellspacing="0" align="center" width=130>
            <tr>
              <td height="2"></td>
            </tr>
          </table>
        </div></td>
  </tr>
</table>--%>
    <%--奖品管理中心--%>
    <table id="table_11" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_9.gif' id="menuTitle302" onclick='showsubmenu(302)'
                style='cursor: hand;'>
                <span class="glow">奖品管理中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu302'>
                <div class="sec_menu" style='width: 158'>
                    <table width="130" align="center" cellpadding="0" cellspacing="0">
                        <tr height="20">
                            <td>
                                <a href="Prizes/Prizes.aspx" target="main" class="menu" style="color: #000000">◆&nbsp;奖品管理
                                </a><a href="Prizes/PrizesAdd.aspx" target="main">添加</a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td>
                                <a href="Prizes/PrizesH.aspx" target="main">◆&nbsp;兑奖记录管理 </a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <%--系统配置中心--%>
    <table id="table_12" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_05.gif' id="menuTitle210" onclick='showsubmenu(210)'
                style='cursor: hand;'>
                <span class="glow">系统配置中心</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu210'>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                <a href="SConfig/Filtering.aspx" target="main">◆&nbsp;注册过滤设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/ReceiveMoneySettings.aspx" target="main">◆&nbsp;领取金币设置 </a><a href="SConfig/ReceiveMoneyConfig.aspx"
                                    target="main">添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/Prices.aspx" target="main">◆&nbsp;注册送金币设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/LastLoginGameCount.aspx" target="main">◆&nbsp;平台显示最近登录游戏个数</a>
                            </td>
                        </tr>
                        <tr style="display: none;">
                            <td height="20">
                                <a href="SConfig/MoneyRankingViewSet.aspx" target="main">◆&nbsp;财富排行榜显示设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/CreateRanking.aspx" target="main">◆&nbsp;排行榜静态页设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="SConfig/GMAwardTypeSet.aspx" target="main">◆&nbsp;GM奖励方案设置</a>
                            </td>
                        </tr>
                        <%if (UiCommon.StringConfig.BankVersion == "2")
                          { %>
                        <tr>
                            <td height="20">
                                <a href="SConfig/CreateBankTax.aspx" target="main">◆&nbsp;生成存单税率设置</a>
                            </td>
                        </tr>
                        <%} %>
                        <!--<tr>
          <td height="20"><a href="SConfig/CompanyInfo.aspx" target="main">◆&nbsp;公司信息管理 </a></td>
        </tr>
       <tr>
          <td height="20"><a href="SConfig/Jinbi.aspx" target="main">◆&nbsp;基础金币设定 </a></td>
        </tr>-->
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <%--推广系统管理--%>
    <table id="table_13" cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_01.gif' id="menuTitle201" onclick='showsubmenu(201)'
                style='cursor: hand;'>
                <span class="glow">推广系统管理</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu201'>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                <a href="Promotion/PrCs.aspx" target="main">◆&nbsp;推广相关参数设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Promotion/PrList.aspx" target="main">◆&nbsp;推广管理 </a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <table id="table_14" cellpadding="0" cellspacing="0" width="158" align="center" style="display:none;">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_01.gif' id="menuTitle217" onclick='showsubmenu(217)'
                style='cursor: hand;'>
                <span class="glow">抽奖系统管理</span>
            </td>
        </tr>
        <tr>
            <td style='display: none' id='submenu217'>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                <a href="Lotter/LotterConfig.aspx" target="main">◆&nbsp;抽奖相关参数设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Lotter/PrList.aspx" target="main">◆&nbsp;抽奖奖品管理 </a><a href="Lotter/PrAdd.aspx"
                                    target="main">添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Lotter/PrUserList.aspx" target="main">◆&nbsp;指定玩家管理 </a><a href="Lotter/PrUserAdd.aspx"
                                    target="main">添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td height="20">
                                <a href="Lotter/LotterLog.aspx" target="main">◆&nbsp;抽奖记录查询 </a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="2">
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
    <%--网管处理信息
<table style="display:none;" id="table_14" cellpadding="0" cellspacing="0" width="158" align="center">
  <tr>
    <td height="25" class="menu_title" onmouseover=this.className='menu_title2'; onmouseout=this.className='menu_title'; background='Images/Admin_left_01.gif' id=menuTitle217 onclick='showsubmenu(217)' style='cursor:hand;'><span class=glow>网管处理信息</span></td>
  </tr>
  <tr>
    <td style='display:none' id='submenu217'><div class=sec_menu style='width:158'>
      <table cellpadding="0" cellspacing="0" align="center" width=130>
        <tr>
          <td height="20"><a href="GameISSUE/UserGMNo.aspx" target="main">◆&nbsp;网管信息处理 </a></td>
        </tr>
      </table>
    </div>
        <div style='width:158'>
          <table cellpadding="0" cellspacing="0" align="center" width=130>
            <tr>
              <td height="2"></td>
            </tr>
          </table>
        </div></td>
  </tr>
</table>--%>
    <table cellpadding="0" cellspacing="0" width="158" align="center">
        <tr>
            <td height="25" class="menu_title" onmouseover="this.className='menu_title2';" onmouseout="this.className='menu_title';"
                background='Images/Admin_left_04.gif' id="menuTitle208">
                <span>系统信息</span>
            </td>
        </tr>
        <tr>
            <td>
                <div class="sec_menu" style='width: 158'>
                    <table cellpadding="0" cellspacing="0" align="center" width="130">
                        <tr>
                            <td height="20">
                                <br />
                                版权所有：<a href="" title="深圳市正易龙科技有限公司" onclick="openUrl();">深圳市正易龙科技有限公司</a><br />
                                <br />
                                <br />
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>

    <script type="text/ecmascript">

        //杨大胜 2009-4-1
        var gde = '<%=GetSession %>'
        if (gde != '2') {
            //先把所有的模块面板隐藏起来
            document.getElementById('table_01').style.display = "none";
            document.getElementById('table_02').style.display = "none";
            document.getElementById('table_03').style.display = "none";
            var tabs = document.body.getElementsByTagName("TABLE");
            //   alert(tabs.length);
            for (var i = 0; i < tabs.length; i++) //table_04 to table_15    display=none
            {
                if (tabs[i].id.indexOf('table_') != -1) {
                    //alert(tabs[i].id);
                    tabs[i].style.display = 'none';
                }
            }

            //---------------------
            var ids = '<%=ids%>';

            if (ids != '') {
                ids = ids.split(',');

                for (var i = 0; i < ids.length; i++) { //table_01 to table_15   display=block
                    if (document.getElementById('table_' + ids[i]) != null) {
                        document.getElementById('table_' + ids[i]).style.display = 'block';
                    }
                }
            }
        }
        function openUrl() {
            window.open("http://www.kfgame.com");
        }
    </script>

</body>
</html>
