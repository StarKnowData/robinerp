<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_UserList_Seach_UserGameSeach" Codebehind="UserGameSeach.aspx.cs" %>

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
.STYLE1{color:red;}
-->
</style>
</head>
<body>
  <form id="form1" runat="server" method="post">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td class="title_03">
                <strong>查询[&nbsp;<font color="red"><%=usernames %></font>&nbsp;]的游戏记录</strong></td>
        </tr>
        <asp:Panel ID="YesGameSeach" runat="server"  Width="100%" Visible="true"> <tr>
            <td>
                <a href="UserGameSeach.aspx?id=<%=seachids %>">1、查询游戏记录</a> <a href="UserMoneySeach.aspx?id=<%=seachids%>">
                    2、查询游戏房间里的存取记录</a> <a href="UserRoomSeach.aspx?id=<%=seachids%>">3、查询房间记录</a> <%--<a href="UserAboutSeach.aspx?id=<%=seachids %>">
                        4、用户资料修改记录</a>--%></td>
        </tr> </asp:Panel>
    </table>
    <table>
            <tr>
                <td style="height: 5px">
                </td>
            </tr>
        </table>
  
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>查询游戏记录</strong></td>
            </tr>
            <tr>
                <td align="right" valign="baseline">
                    <strong>提示说明：</strong></td>
                <td align="left">
                    <strong>尽量的缩小搜索的范围，把一次大的搜索分多次查询；当记录很多时，系统会很慢。</strong></td>
            </tr>
            <tr>
                <td width="14%" align="right" valign="baseline">
                    <span class="STYLE1">*</span> 房间类型：</td>
                <td width="86%" align="left">
                    <select name="tt" id="tt">
                        <option value="0" selected="selected" Class="put">不限</option>
                        <option value="1">普通场</option>
                        <option value="2">比赛场</option>
                        <option value="3">金币场</option>
                    </select>
                </td>
            </tr>
            <tr>
                <td align="right">
                    <span class="STYLE1">* </span>游戏房间：</td>
                <td align="left">
                    <asp:DropDownList ID="rr" runat="server" Class="put">
                     <asp:ListItem Value="0">不限</asp:ListItem>
                    </asp:DropDownList>
                   
                </td>
            </tr>
            <tr>
                <td align="right">
                    <span class="STYLE1">  </span>玩家用户名：</td>
                <td align="left">
                    <input name="uu" type="text" id="uu" value="<%=usernamess %>" Class="put"/>
                    <input name="ids" type="text" id="ids" value="<%=seachids %>" style="display: none;" />
                    <input name="us" type="text" id="us" value="<%=usernames %>" style="display: none;" />
                    （必须是全名，不支持模糊查询）</td>
            </tr>
            <tr>
                <td align="right">
                    <span class="STYLE1">* </span>结束时间：</td>
                <td align="left" >
                    <input name="d1" type="text" id="d1" value="0" size="5" maxlength="5" Class="put"/>
                    小时前到
                    <input name="d2" type="text" id="d2" value="24" size="5" maxlength="5" Class="put"/>
                    小时前（前面输入的数比后面的数小，比如：0到24表示从现在算起24小时以前的记录）
                </td>
            </tr>
            <tr>
                <td style="height: 31px">&nbsp;
                    <input type="hidden" name="action" value="search" /></td>
                <td align="left" style="height: 31px">   
                     <input id="Button2" type="button" runat="server" onserverclick="SearchPage" value=" 查 询 " Class="put"/>
                </td>
            </tr>
        </table>
    </form>
    

</body>
</html>
