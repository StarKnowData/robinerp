<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_GameInfo_AgencyGameDown" Codebehind="AgencyGameDown.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
	<form id="form1" runat="server">
		<tr>
			<td class="title_03" colspan="2">
				<strong>代理商游戏大厅下载管理</strong></td>
		</tr>
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<th>
					序号</th>
				<th>
					代理商二级域名</th>
				<th>
					电信下载地址</th>
				<th>
					网通下载地址</th>
				<th>
					操作</th>
			</tr>
			<asp:Repeater runat="server" ID="rptDataList">
				<ItemTemplate>
					<tr>
						<td align="center">
							<%=RowNum++%>
						</td>
						<td align="center">
							<%# Eval( "twodomain" )%>
						</td>
						<td align="center">
							<%# Eval("dianxindown") %>
						</td>
						<td align="center">
							<%# Eval( "wangtongdown" )%>
						</td>
						<td align="center">
							<a href="AgencyGameDown.aspx?action=edit&params=<%# Eval("ID") %>">修改</a>&nbsp;&nbsp;
							<a href="AgencyGameDown.aspx?action=del&params=<%# Eval("ID") %>" onclick="javascript:return confirm('确定要删除吗？\r\n注意：删除后将不会恢复!');">
								刪除</a>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
		</table>
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table" style="margin-top: 25px;">
			<tr>
				<th colspan="25">
					添加/修改下载地址&nbsp;&nbsp;&nbsp;&nbsp;<a href="AgencyGameDown.aspx" style="color: Blue;">添加</a></th>
			</tr>
			<tr>
				<th align="right">
					代理商二级域名：</th>
				<td align="left">
					<asp:TextBox runat="server" ID="txtTwoDomain" CssClass="put" MaxLength="50" ValidationGroup="DownloadAddress"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtTwoDomain"
						Display="Dynamic" ErrorMessage="请填写代理商二级域名" ValidationGroup="DownloadAddress"></asp:RequiredFieldValidator></td>
			</tr>
			<tr>
				<th align="right">
					电信下载地址：</th>
				<td align="left">
					<asp:TextBox runat="server" ID="txtDXUrl" CssClass="put" MaxLength="1000" ValidationGroup="DownloadAddress" Width="251px"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtDXUrl"
						Display="Dynamic" ErrorMessage="请填写电信下载地址" ValidationGroup="DownloadAddress"></asp:RequiredFieldValidator></td>
			</tr>
			<tr>
				<th align="right">
					网通下载地址：</th>
				<td align="left">
					<asp:TextBox runat="server" ID="txtWTUrl" CssClass="put" MaxLength="1000" ValidationGroup="DownloadAddress" Width="251px"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate="txtWTUrl"
						Display="Dynamic" ErrorMessage="请填写网通下载地址" ValidationGroup="DownloadAddress"></asp:RequiredFieldValidator></td>
			</tr>
			<tr>
				<th align="right">
					&nbsp;</th>
				<td align="left">
					<asp:Button runat="server" ID="btnSubmit" CssClass="put" Text=" 保 存 " ValidationGroup="DownloadAddress"
						OnClick="btnSubmit_Click" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
