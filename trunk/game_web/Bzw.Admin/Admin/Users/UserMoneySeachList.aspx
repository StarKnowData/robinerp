<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_UserMoneySeachList" Codebehind="UserMoneySeachList.aspx.cs" %>

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
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03">
					<strong>查询[&nbsp;<font color="red"><%=usernames %></font>&nbsp;]的游戏房间里的存取记录</strong></td>
			</tr>
			<tr>
				<td>
					<a href="UserGameSeach.aspx?id=<%=seachids %>">1、查询游戏记录</a>
					<a href="UserMoneySeach.aspx?id=<%=seachids%>">2、查询游戏房间里的存取记录</a>
					<a href="UserRoomSeach.aspx?id=<%=seachids%>">3、查询房间记录</a>
					<%--<a href="UserAboutSeach.aspx?id=<%=seachids %>">
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
		
				<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
					<tr>
						<td class="title_03" colspan="11">
							<font color="red"><strong>查询游戏房间里的存取记录列表</strong></font></td>
					</tr>
					<tr>
						<td>
							序号</td>
						<td>
							用户名</td>
						<td>
							房间ID</td>
						<td>
							操作时间</td>
						<td>
							操作前银行金币</td>
					   
						<td>
							操作前钱包金币</td>
					
						<td>
							存进金币</td>
						<td>
							取出金币</td>
						
					</tr>
					<asp:Repeater ID="MoneySeachList" runat="server">
			<HeaderTemplate>
			</HeaderTemplate>
			<ItemTemplate>
				<tr>
					<td>
						<%=tableids=tableids+1 %>
					</td>
					<td>
						<%# Eval("UserName").ToString() %>
					</td>
					<td>
						<%# Convert.ToInt32(Eval("RoomID"))==0?"网站中":Eval("RoomId").ToString()%>
					</td>
					<td>
						<%# Eval("TimeEx")%>
					</td>
					<td>
						<%# Eval("MoneyInBank") %>
					</td>
					<td>
						<%# Eval("MoneyInRoom") %>
					</td>
					
					<td>
						<%# Eval("OutMoney") %>
					</td>
					<td>
						<%# Eval("InMoney")%>
					</td>
					
				</tr>
			</ItemTemplate>
		</asp:Repeater>
		
		</table>
		<table>
			<tr>
				<td style="height: 5px">
				<asp:Label ID="NoUserGame" runat="server" Text="暂无划帐记录！" Visible="false"></asp:Label>
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
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
