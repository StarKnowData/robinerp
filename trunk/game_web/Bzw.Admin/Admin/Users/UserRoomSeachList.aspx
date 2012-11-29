<%@ Page Language="C#" AutoEventWireup="true"
	Inherits="Admin_Users_UserRoomSeachList" Codebehind="UserRoomSeachList.aspx.cs" %>

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
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03">
					<strong>查询[&nbsp;<font color="red"><%=usernames %></font>&nbsp;]的房间记录</strong></td>
			</tr>
			<tr>
				<td>
					<a href="UserGameSeach.aspx?id=<%=seachids %>">1、查询游戏记录</a>
					<a href="UserMoneySeach.aspx?id=<%=seachids%>">2、查询游戏房间里的存取记录</a>
					<a href="UserRoomSeach.aspx?id=<%=seachids%>">3、查询房间记录</a><%-- <a href="UserAboutSeach.aspx?id=<%=seachids %>">
                            4、用户资料修改记录</a>--%>
				</td>
			</tr>
		</table>
		<table>
			<tr>
				<td style="height: 5px">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="11">
					<font color="red"><strong>查询到&nbsp;[&nbsp;<%=RoomName %>&nbsp;]&nbsp;房间的玩家游戏记录列表</strong></font></td>
			</tr>
			<tr>
				<td>
					序号</td>
				<td>
					用户名</td>
				<td>
					积分</td>
				<td>
					金币</td>
				<td>
					税值</td>
				<td>
					赢</td>
				<td>
					输</td>
				<td>
					平</td>
				<td>
					玩的时间</td>
				<td>
					在线时间</td>
				<td>
					时间</td>
			</tr>
			<asp:Repeater ID="RoomSeachList" runat="server">
				<HeaderTemplate>
				</HeaderTemplate>
				<ItemTemplate>
					<tr>
						<td>
							<%=TableID=TableID+1 %>
						</td>
						<td>
							<%# Eval("UserName").ToString() %>
							&nbsp;
						</td>
						<td>
							<%# Eval("Point")%>
						</td>
						<td>
							<%# Eval("Money")%>
						</td>
						<td>
							<%# Eval("TaxCom")%>
						</td>
						<td>
							<%# Eval("Win")%>
						</td>
						<td>
							<%# Eval("Lost") %>
						</td>
						<td>
							<%# Eval("Mid") %>
						</td>
						<td>
							<%# Eval("PlayTimeCount") %>&nbsp:秒
						</td>
						<td>
							<%# Eval("OnLineTimeCount") %>&nbsp:秒
						</td>
						<td>
							<%# Eval("LogonDate")%>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			
			<table>
				<tr>
					<td style="height: 5px">
					<asp:Label ID="NoUserRoom" runat="server" Text="暂无房间记录！" Visible="false"></asp:Label>
					</td>
				</tr>
			</table>
			<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
				bgcolor="F2F8FF" class="admin_table">
			 
				<tr>
				 
					<td align="left">税值总数：<%=sum %>
						<div id="page_link" class="page_link">
							<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True"
								CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条"
								FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left"
								ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到"
								UrlPaging="True">
							</webdiyer:AspNetPager>
						</div>
					</td>
				</tr>
			</table>
	</form>
</body>
</html>
