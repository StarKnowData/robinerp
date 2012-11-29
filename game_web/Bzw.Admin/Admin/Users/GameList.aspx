<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GameList.aspx.cs" Inherits="Admin_Games_GameList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	 
	  <script src="/Public/Js/DatePicker/WdatePicker.js"></script>
	<style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03">
					<strong>查询[&nbsp;<font color="red"><%=usernames %></font>&nbsp;]的游戏记录</strong></td>
			</tr>
			<tr>
				<td>
				  
                   &nbsp;&nbsp;&nbsp;&nbsp; 游戏类型：<asp:DropDownList ID="ddlNameID" runat="server" style="width:80px;"/>
                &nbsp;&nbsp;&nbsp;&nbsp;结束时间：从<asp:TextBox ID="txtBegin" runat ="server" style="width:120px;"></asp:TextBox> 至
                <asp:TextBox ID="txtEnd" runat ="server" style="width:120px;"></asp:TextBox>
                &nbsp;&nbsp;&nbsp;&nbsp;<asp:Button ID="btnSearch" runat="server" Text=" 查 询 " OnClick="btnSearch_Click"/>
                &nbsp;&nbsp;&nbsp;&nbsp;<input type="button" value=" 返 回 " onclick="document.location.href='<%=Utility.Common.UrlValue %>'" />
                </td> 
			 
			</tr>
		</table>
		<table>
			<tr>
				<td style="height: 5px; width: 3px;">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="11">
					<font color="red"><strong>查询到的玩家游戏记录列表</strong></font></td>
			</tr>
			<tr>
				<td>
					序号</td>
				<td>
					房间名</td>
				<td>
					桌子</td>
				<td>
					当局用时</td>
				<td>
					当局结束时间</td>
				<td>
					交的税值</td>
				<td>
					玩家</td>
				<td>
					相关玩家</td>
			</tr>
			<asp:Repeater ID="GameSeachList" runat="server" OnItemDataBound="GameSeachList_ItemDataBound">
				<ItemTemplate>
					<tr>
						<td>
							<%=listids=listids+1 %>
						</td>
						<td>
							<%# Eval("RoomName")%>
						</td>
						<td>
							<%# Eval("Deskindex") %>
							号</font>
						</td>
						<td>
							<%# Eval("GameTime") %>
							秒</td>
						<td>
							<%# Eval("EndTime") %>
						</td>
						<td>
							<%# Eval("Tax") %>
						</td>
						<td>
							<a href="Edit_User.aspx?id=<%# Eval("UserID").ToString() %>" title="结束时总分：<%# Eval("SrcPoint").ToString() %>
改变分数：<%# Eval("ChangePoint").ToString() %>
结束时金币：<%# Eval("SrcMoney").ToString() %>
改变金币：<%# Eval("ChangeMoney").ToString() %>
税：<%# Eval("ChangeTax").ToString() %>" onclick="javscript:return confirm('是否转到用户管理查看当前用户的信息？');">
								<%# GetName(Eval("UserID"))%>
							</a>
						</td>
						<td>
							<asp:Literal runat="server" ID="ltRelateUser"></asp:Literal>
							<%--<a href="UserGameSeachList_xg.aspx?id=<%# Eval("RecordIndex")%>">相关玩家</a>--%>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
		</table>
		<table>
			<tr>
				<td style="height: 5px; text-align: center;">
					<asp:Label ID="NoUserGame" runat="server" Text="暂无游戏记录！" Visible="false"></asp:Label>
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					<div id="page_link" class="page_link">
						<%--<asp:Literal ID="pageList" runat="server"></asp:Literal>--%>
						<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
							FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
							PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go"
							TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
