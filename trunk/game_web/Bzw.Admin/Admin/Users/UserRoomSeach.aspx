<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_UserList_Seach_UserRoomSeach" Codebehind="UserRoomSeach.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
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
    <form id="form1" runat="server">
    
<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
 <tr><td class="title_03"><strong>查询[&nbsp;<font color=red><%=usernames %></font>&nbsp;]的房间记录</strong></td></tr>
 
 <asp:Panel ID="YesRoomSeach" runat="server"  Width="100%">
 <tr><td>
 <a href="UserGameSeach.aspx?id=<%=seachids %>">1、查询游戏记录</a>
 <a href="UserMoneySeach.aspx?id=<%=seachids%>">2、查询游戏房间里的存取记录</a>
 <a href="UserRoomSeach.aspx?id=<%=seachids%>">3、查询房间记录</a>
 <%--<a href="UserAboutSeach.aspx?id=<%=seachids %>">4、用户资料修改记录</a>--%>
 </td></tr>
 </asp:Panel>
</table>

<table>
<tr>
<Td style="height:5px"></Td>
</tr>
</table>
<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
<tr>
<td colspan="2" class="title_03"><strong>查询房间记录</strong></td>
</tr>
<tr>
  <td align="right" valign="baseline"><strong>提示说明：</strong></td>
  <td align="left"><strong>尽量的缩小搜索的范围，把一次大的搜索分多次查询；当记录很多时，系统会很慢。</strong></td>
</tr>
<tr>
  <td align="right"><span class="STYLE1">* </span>游戏房间：</td>
  <td align="left">

      <asp:DropDownList ID="rr" runat="server">
      </asp:DropDownList>
  </td>
</tr>
<tr>
  <td align="right"><span class="STYLE1">  </span>玩家用户名：</td>
  <td align="left"><input name="uu" type="text" id="uu" value="<%=usernamess %>" Class="put"/>
  <input name="ids" type="text" id="Text1" value="<%=seachids %>" style="display:none" />
  <input name="us" type="text" id="Text2" value="<%=usernames %>" style="display:none"/>
    （必须是全名，不支持模糊查询）</td>
</tr>
<tr>
  <td align="right"><span class="STYLE1">* </span>结束时间：</td>
  <td align="left"><input name="d1" type="text" id="d1" value="0" size="5" maxlength="5" Class="put"/>
    小时前到 
    <input name="d2" type="text" id="d2" value="24" size="5" maxlength="5" Class="put"/>
    小时前（前面输入的数比后面的数小，比如：0到24表示从现在算起24小时以前的记录）	 </td>
</tr>
<%--<tr>
  <td align="right"><span class="STYLE1">*</span>显示条数：</td>
  <td align="left"><input name="nn" type="text" id="nn" value="0" Class="put"/>
    （结果中显示的最多记录数，0为显示所有的）</td>
</tr>--%>
<tr>
  <td align="right"><span class="STYLE1">*</span>排列项：</td>
  <td align="left"><select name="ss" id="ss">
    <option value="0" selected="selected">按积分</option>
    <option value="1">按金币</option>
    <option value="2">按交税</option>
    <option value="3">按赢的局数</option>
    <option value="4">按输的局数</option>
    <option value="5">按平的局数</option>
    <option value="6">按玩游戏时间</option>
    <option value="7">按在线时间</option>
    <option value="8">按时间</option>
  </select>
    <input name="s1" type="checkbox" id="s1" value="1" checked="checked" Class="put"/>
    降序（显示结果的排列顺序项，选定降序即按排序项的降序方式排列，不选即表示升序。）</td>
</tr>
<tr>
<td><input type="hidden" name="action" value="search" />&nbsp;</td>
<td align="left">
  <input id="Button1" type="button" runat="server" onserverclick="SearchPage" value=" 查 询 " Class="put" />
</td>
</tr>
</table>
<table>
<tr>
<Td style="height:5px"></Td>
</tr>
</table>

</form>
</body>
</html>
