<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_UserTop" Codebehind="UserTop.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #ffffff;
}
-->
</style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="2" class="title_03">
					<strong>活跃在前30名的用户信息</strong></td>
			</tr>
			<tr>
				<td width="27%" valign="top">
					<div id="gamelist">
						<ul>
							<asp:Repeater ID="GameLists" runat="server">
								<ItemTemplate>
									<li>
										<a href='UserTop.aspx?id=<%# Eval("NameID") %>'>
											<%# Eval("ComName")%>
										</a>
									</li>
								</ItemTemplate>
							</asp:Repeater>
							<asp:Label ID="NoGameList" runat="server" Text="暂无任何数据记录！" Visible="false"></asp:Label>
						</ul>
					</div>
				</td>
				<td width="73%" align="center" valign="top">
					<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
						<tr>
							<td height="27" align="center">
								序号</td>
							<td align="center">
								用户名</td>
							<td align="center">
								赢</td>
							<td align="center">
								输</td>
							<td align="center">
								断线</td>
							<td align="center">
								游戏时间</td>
							<td align="center">
								在线时间</td>
							<td align="center">
								积分</td>
						</tr>
						<asp:Repeater ID="ListsInfo" runat="server">
							<ItemTemplate>
								<tr>
									<td>
										<%=listids = listids+1%>
									</td>
									<td>
										<%# Eval("UserName") %>
									</td>
									<td>
										<%# Eval("win") %>
									</td>
									<td>
										<%# Eval("lost") %>
									</td>
									<td>
										<%# Eval("cut") %>
									</td>
									<td>
										<%# Eval("PlayTimeCount") %>
									</td>
									<td>
										<%# Eval("OnLineTimeCount") %>
									</td>
									<td>
										<%# Eval("Point") %>
									</td>
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<tr>
							<td colspan="8">
								<asp:Label ID="NoList" runat="server" Text="暂无任何数据记录！" Visible="false"></asp:Label>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
