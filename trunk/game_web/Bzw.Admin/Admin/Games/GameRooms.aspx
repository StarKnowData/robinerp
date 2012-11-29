<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameRooms" Codebehind="GameRooms.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
<script src="/Public/Js/public.js" type="text/javascript"></script>
<script src="/Public/Js/jquery.js" type="text/javascript"></script>
<script src="/Public/Js/admin.js" type="text/javascript"></script>
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td class="title_03">
                    <strong>游戏房间管理</strong></td>
            </tr>
            <!--<tr><td class="title_05">
<a href="?action=roominfo" style='color:red'>显示房间信息</a>&nbsp;&nbsp;
<a href="?action=roomadd" >添加游戏房间</a>

<a href="admin_gameType.asp?action=list">游戏类别管理</a>
<a href="admin_gameName.asp?action=list">游戏名称管理</a>

</td></tr>-->
        </table>
        <table>
            <tr>
                <td height="5">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td align="left">
                    <strong>游戏大类</strong>
                    <asp:DataList ID="GameBigList" runat="server" RepeatColumns="8">
                        <ItemTemplate>
                            &nbsp;&nbsp;&nbsp; <a href='GameRooms.aspx?bid=<%# Eval("Kindid") %>'>
                                <%# Eval("KindName") %>
                            </a>&nbsp;&nbsp;&nbsp;|
                        </ItemTemplate>
                    </asp:DataList>
                    <asp:Label ID="NoGameBigList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
                </td>
            </tr>
            <tr>
                <td align="left">
                    <strong>游戏小类 </strong>
                    <asp:DataList ID="GameSmallList" runat="server" RepeatColumns="8">
                        <ItemTemplate>
                            &nbsp;&nbsp;&nbsp; <a href='GameRooms.aspx?bid=<%=RoomBigID %>&sid=<%# Eval("Nameid") %>'>
                                <%# Eval("ComName") %>
                            </a>&nbsp;&nbsp;&nbsp;
                        </ItemTemplate>
                    </asp:DataList>
                    <asp:Label ID="NoGameSmallList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
                </td>
            </tr>
        </table>
        <table>
            <tr>
                <td height="5">
                </td>
            </tr>
        </table>
        <asp:Repeater ID="RoomListInfos" runat="server">
            <HeaderTemplate>
                <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
                    bgcolor="F2F8FF" class="admin_table">
                    <tr>
                        <td class="title_03" colspan="11">
                            <strong>房间信息显示</strong></td>
                    </tr>
                    <tr>
                        <td>
                            序号</td>
                        <td>
                            房间ID</td>
                        <td>
                            游戏性质</td>
                        <td>
                            游戏名称</td>
                        <td>
                            排列ID</td>
                        <td>
                            名称ID</td>
                        <td>
                            在线人数</td>
                        <td>
                            是否激活</td>
                        <td>
                            版本号</td>
                        <td>
                            房间规则</td>
                        <td>
                            操作</td>
                    </tr>
            </HeaderTemplate>
            <ItemTemplate>
                <tr>
                    <td>
                        <%=tableids = tableids+1%>
                    </td>
                    <td>
                        <%# Eval("id") %>
                    </td>
                    <td>
                        <%# GetGameRooms(Convert.ToInt32(Eval("GameTypeID")))%>
                    </td>
                    <td>
                        <%# Eval("RoomName")%>
                    </td>
                    <td>
                        <%# Eval("idsort") %>
                    </td>
                    <td>
                        <%# Eval("RoomID") %>
                    </td>
                    <td>
                        <%# Eval("OnLineCount") %>
                    </td>
                    <td>
                <%# Eval("EnableRoom").ToString().ToLower() == "0" ? "未激活" : "已激活"%>
                    </td>
                    <td>
                        <%# Eval("version")%>
                    </td>
                    <td>
                       <a href="#" onclick="openRoomRuleDiv('RoomRule.aspx?RoomRule=<%# Eval("RoomRule")%>',350,320)" title="点击查看规则明细"><%# Eval("RoomRule")%></a>
                    </td>
                    <td>
                        <a href='GameRoomsEdit.aspx?sid=<%# Eval("id") %>'>修改</a>&nbsp;&nbsp;<a href='GameRoomsDel.aspx?sid=<%# Eval("id") %>'
                            onclick="javascript:return confirm('您确定要删除该房间吗？');">删除</a></td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Label ID="NoRoomListInfos" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
        
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td style="height: 5px" style="background-color: White">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td align="left">
                    <div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
