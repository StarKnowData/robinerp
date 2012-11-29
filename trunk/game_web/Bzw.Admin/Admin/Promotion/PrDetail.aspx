<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_PrDetail" Codebehind="PrDetail.aspx.cs" %>

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
				<td colspan="7" align="center" class="title_03">
					<strong>推广员推广记录明细</strong></td>
			</tr>
			<tr>
				<td colspan="7" align="left" class="title_03" style="margin-left: 15px;">
					共计：<%=ShouYi%>金币
				</td>
			</tr>
			<tr align="center" bgcolor="#f4f4f4">
				<td>
					序号</td>
				<td>
					被推广用户</td>
				<td>
					充值金额</td>
				<td>
					充值类型</td>
				<td>
					充值时间</td>
				<td>
					推广员收益</td>
			</tr>
			<asp:Repeater ID="PrListinfos" runat="server">
				<ItemTemplate>
					<tr align="center">
						<td>
							<%# Container.ItemIndex + 1 + anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 )%>
						</td>
						<td title="游戏时长：<%# Eval("PlayTimeHourCount") %>小时&#13;注册时间：<%# Eval("RegisterTM") %>">
							<%# Eval("UserName")%>
						</td>
						<td>
							<%# Eval("PayMoney") %>
						</td>
						<td>
							<%# Eval("PayType") %>
						</td>
						<td>
							<%# Eval("AddTime","{0:yyyy-MM-dd HH:mm:ss}") %>
						</td>
						<td>
							<%# Eval("GetMoney")%>
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
						UrlPaging="True" PageSize="20">
					</webdiyer:AspNetPager>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
