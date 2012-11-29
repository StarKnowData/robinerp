<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_systems" Codebehind="systems.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		<%= SiteConfig.GetParaValue("Title")%>
	</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>网站参数设置</strong></td>
			</tr>
		</table>
		<asp:Repeater ID="sysList" runat="server">
			<HeaderTemplate>
				<table width="100%" border="0" cellspacing="0" cellpadding="0" style="background-color: White" >
					<tr>
						<td style="height: 5px"  >
						</td>
					</tr>
				</table>
				<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
					<tr align="center" >
						<td width="3%">
							序号</td>
						<td width="8%">
							参数名称</td>
						<td width="*">
							参数值</td>
						<td width="40%">
							描述</td>
						<td width="16%">
							操作</td>
					</tr>
			</HeaderTemplate>
			<ItemTemplate>
				<tr align='center' height='25px' onmouseout="this.style.backgroundColor='#ffffff'" onmouseover="this.style.backgroundColor='#E1E1E1'">
					<td>
						<%# Eval("ID") %>
					</td>
					<td>
						<%# Eval("ParaName")%>
					</td>
					<td>
						<%# Eval("ParaValue")%>
					</td>
					<td>
						<%# Eval("Descript")%>
					</td>
					<td>
						<a href='SystemEdit.aspx?id=<%# Eval("ID") %>'><%# Eval("ID").ToString()=="8"?"上传":"修改" %></a></td>
				</tr>
			</ItemTemplate>
			<FooterTemplate>
				</table>
			</FooterTemplate>
		</asp:Repeater>
		<asp:Label ID="NoUserList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height: 5px" style="background-color: White">
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
