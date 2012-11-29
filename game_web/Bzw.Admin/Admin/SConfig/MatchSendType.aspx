<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MatchSendType.aspx.cs" Inherits="Admin_SConfig_MatchSendType" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title></title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
	<form id="form1" runat="server">
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		<caption>
			<font color='red'><strong>比赛赠送奖券方案列表</strong></font></caption>
		<tr>
			<th>
				ID
			</th>
			<th>
				方案名
			</th>
			<th>
				操作
			</th>
		</tr>
		<asp:Repeater runat="server" ID="rptDataList">
			<ItemTemplate>
				<tr>
					<td align="center">
						<%# Eval( "ID" )%>
					</td>
					<td align="center">
						<%# Eval( "Name" ).ToString()%>
					</td>
					<td align="center">
						<a href="MatchSendType.aspx?action=edit&params=<%# Eval("ID") %>&reurl=<%=Server.UrlEncode(Request.Url.AbsoluteUri) %>">修改</a>&nbsp;&nbsp; <a href="MatchSendType.aspx?action=del&params=<%# Eval("ID") %>&reurl=<%=Server.UrlEncode(Request.Url.AbsoluteUri) %>" onclick="javascript:return confirm('确定要删除吗？\r\n注意：删除后将不会恢复!');">刪除</a>
					</td>
				</tr>
			</ItemTemplate>
		</asp:Repeater>
		<asp:Label ID="ltNonData" runat="server" Text="<tr><td colspan='3'>暂无任何数据！</td></tr>"></asp:Label>
		<tr>
			<td align="left" colspan="3">
				<webdiyer:aspnetpager runat="server" id="anpPageIndex" custominfohtml="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" firstpagetext="首页" lastpagetext="尾页" nextpagetext="下一页" numericbuttoncount="5" pageindexboxtype="DropDownList" prevpagetext="上一页" showcustominfosection="Left" showpageindexbox="Never" submitbuttontext="Go" textafterpageindexbox="" textbeforepageindexbox="" urlpaging="True" alwaysshow="True" pagesize="20">
					</webdiyer:aspnetpager>
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table" style="margin-top: 25px;">
		<tr>
			<th colspan="2">
				添加/修改比赛赠送奖券方案名&nbsp;&nbsp;&nbsp;<a href="MatchSendType.aspx">添加</a>
			</th>
		</tr>
		<tr>
			<th align="right">
				方案名：
			</th>
			<td align="left">
				<asp:TextBox runat="server" ID="txtName" CssClass="put" ></asp:TextBox>
				<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtName" Display="Dynamic" ErrorMessage="请输入排名名次" ></asp:RequiredFieldValidator>
				 
			</td>
		</tr>
	 
		<tr>
			<th align="right">
				&nbsp;
			</th>
			<td align="left">
				<asp:Button runat="server" ID="btnSubmit" CssClass="put" Text=" 添 加 " OnClick="btnSubmit_Click"  />
			</td>
		</tr>
	</table>
	</form>
</body>
</html>