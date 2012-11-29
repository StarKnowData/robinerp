<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_PrBalanceLog" Codebehind="PrBalanceLog.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>推广收入结账</title>
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
				<td colspan="7" align="center" class="title_03">
					<strong>推广员推广收入结账日志</strong></td>
			</tr>
			<tr>
				<td colspan="7" align="left" class="title_03" style="margin-left: 15px;">
				共计：<%=BalanceMoney%>金币</td>
			</tr>
			<tr align="center" bgcolor="#f4f4f4">
				<td>
					序号</td>
				<td>
					用户名</td>
				<td>
					用户昵称</td>
				<td>
					结账金额</td>
				<td>
					IP</td>
				<td>
					结账时间</td>
			</tr>
			<asp:Repeater ID="PrBalanceLog" runat="server">
				<ItemTemplate>
					<tr align="center">
						<td>
							<%# Container.ItemIndex + 1 + anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 )%>
						</td>
						<td>
							<%# Eval("UserName")%>
						</td>
							<td>
							<%# Eval("NickName")%>
						</td>
						<td>
							<%# Eval("Money") %>金币
						</td>
						<td>
							<%# Eval("IP") %>
						</td>
						<td>
							<%# Eval("ClearingTime","{0:yyyy-MM-dd HH:mm:ss}") %>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoPrListinfos" runat="server" Text="<tr><td colspan='7' align='center'>暂无记录</td></tr>"
				Visible="false"></asp:Label>
			<tr>
				<td colspan="7" align="right">
					<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条"
						FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
						PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
						ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
						UrlPaging="True" PageSize="30">
					</webdiyer:AspNetPager>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
