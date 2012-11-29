<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LotterLog.aspx.cs" Inherits="Admin_Lotter_LotterLog" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
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
					<strong><font color="red">抽奖记录列表</font></strong></td>
			</tr>
			<tr>
				<td>
					序号</td>
				<td>玩家名称</td>
				<td>
					奖品名称</td>
				<td>
					花费金币数</td>
			 
				<td>
					抽奖时间</td>
					<td>状态</td>
				<td>
					修改</td>
				<td>
					删除</td>
			</tr>
			<asp:Repeater ID="PrizesList" runat="server">
				<ItemTemplate>
					<tr>
						<td>
							<%=TableIds=TableIds+1 %>
						</td>
						<td>
							<%# Eval("UserName") %>
						</td>
						<td>
							 <%# Eval("LotteryAwardName")%></td>
						<td>
							<%# Eval("ChangeMoney") %>
							 </td>
						<td>
							<%# Eval("AddDate")%>
						</td>
						<td>
							<%# Eval("Status").ToString() == "1" ? "<font color=\"red\">已发货</font>" : "未发货"%>
						</td>
						<td>
							<a href='LotterLog.aspx?act=edit&id=<%# Eval("ID") %>&sta=<%#Eval("Status") %>'>修改状态</a></td>
						<td>
							<a href='LotterLog.aspx?act=del&id=<%# Eval("ID") %>' onclick="javascript:return confirm('您确定要删除当前记录吗？删除后将不能恢复!!');"><font color="red">删除</font></a>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoPrizesList" runat="server" Text="<tr><td colspan='8' align='center'>暂无任何记录！</td></tr>" Visible="false"></asp:Label>
			<tr>
				<td colspan="8" align="right">
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
