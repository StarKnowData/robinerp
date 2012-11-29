<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_PrListInfo" Codebehind="PrListInfo.aspx.cs" %>

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

	<script >
								function getTGstate (flg){
									
									 if(flg=='1')
										{
											document.write('<font color="red">已结算</font>');
										}
										else if(flg=='2')
										{
											document.write ('<font color="red">已过期</font>');
										}
										else
										{
											document.write ('未结算');
										}
									}
	</script>

</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="7" align="center" class="title_03">
					<strong>推广员推广记录</strong></td>
			</tr>
			<tr>
				<td colspan="7">
					已结算：<%=TGCount %>人 &nbsp;&nbsp;共收入：<%=TGIncome%>金币
				</td>
			</tr>
			<tr align="center">
				<td bgcolor="#f4f4f4">
					序号</td>
				<td bgcolor="#f4f4f4">
					用户名</td>
				<td bgcolor="#f4f4f4">
					被推广用户</td>
				<td bgcolor="#f4f4f4">
					有效推广完成度</td>
				<td bgcolor="#f4f4f4">
					推荐时间</td>
				<td bgcolor="#f4f4f4">
					结算</td>
				<td bgcolor="#f4f4f4">
					结算时间</td>
			</tr>
			<asp:Repeater ID="PrListinfos" runat="server">
				<ItemTemplate>
					<tr align="center">
						<td>
							<%=TableID=TableID+1 %>
						</td>
						<td>
							<%# Eval("TGUserName")%>
						</td>
						<td>
							<%# Eval("UserName").ToString()%>
						</td>
						<td>
							<%# GetUserPercent(Eval("Userid").ToString())%>
						</td>
						<td>
							<%# Eval("RegTime") %>
						</td>
						<td>
						<script>
							getTGstate('<%#Eval("IsRegAward") %>');
						</script>
						</td>
						<td>
							<%# Eval("CalTime") %>
							&nbsp;
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<tr>
				<td colspan="7" align="center">
					<asp:Label ID="NoPrListinfos" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
