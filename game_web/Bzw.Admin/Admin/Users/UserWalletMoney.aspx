<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserWalletMoney.aspx.cs" Inherits="Admin_Users_UserWalletMoney" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>玩家游戏中金币</title>
</head>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/public.js" type="text/javascript"></script>
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/admin.js" type="text/javascript"></script>
 

<body>
	<table width="100%" border="1" align="center" cellpadding="1" cellspacing="0" bordercolor="A4B6D7" class="admin_table">
			<tr>
				<td class="title_03" colspan="11">
					<strong><font color="red">玩家ID:<%=UserID %>的游戏金币列表</font></strong></td>
			</tr>
			<tr>
				<td>
					游戏ID</td>
				<td>
					游戏名称</td> 
				<td>
					金币</td>
				 
			</tr>
			<asp:Repeater ID="PrizesList" runat="server">
				<ItemTemplate>
					<tr>
						 
						<td>
							<%# Eval("GameID") %>
						</td>
						<td>
							金币:<%# Eval("ComName")%></td>
						<td>
							<%# Eval("WalletMoney") %>
							 </td>
					 
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoPrizesList" runat="server" Text="<tr><td colspan='8' align='center'>暂无任何记录！</td></tr>" Visible="false"></asp:Label>
			<tr>
				<td colspan="8" align="right">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="10">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
		
</body>
</html>

