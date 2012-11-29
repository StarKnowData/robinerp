<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_JpPrices" Codebehind="JpPrices.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
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
				<td class="title_03" colspan="11">
					<strong><font color="red">道具列表</font></strong></td>
			</tr>
			<tr align="center" style="font-weight:bold;">
				<td style="display: none" width="1%">
				</td>
				<td>
					ID号</td>
				<td>
					道具名称</td>
				<td>
					普通会员价格</td>
				<td>
					VIP会员价格</td>
				<td>
					操作</td>
			</tr>
			<asp:Repeater ID="ProList" runat="server">
				<ItemTemplate>
					<tr>
						<%
							if( ( TableID ) % 2 == 0 )
							{
								Response.Write( "  <tr align='center' bgcolor='#E1E1E1' height='25px' >" );
							}
							else
							{
								Response.Write( "  <tr align='center' bgcolor='#ffffff' height='25px'>" );
							}       
						%>
						<td style="display: none">
							<%=TableID = TableID + 1%>
						</td>
						<td>
							<%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 )%>
						</td>
						<td>
							<%# Eval("PropName")%>
						</td>
						<td>
							金币:<%# Eval("Price") %></td>
						<td>
							金币:<%# Eval("VipPrice") %></td>
						<td>
							<a href='JpProicesE.aspx?id=<%# Eval("PropID") %>'>修改价格</a>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label runat="server" Text="暂无任何记录！" ID="NoProList" Visible="false"></asp:Label>
			<tr>
				<td colspan='11' align='right'>
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
