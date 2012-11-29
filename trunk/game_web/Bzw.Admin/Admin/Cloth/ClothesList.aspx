<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ClothesList.aspx.cs" Inherits="Admin_Cloth_ClothesList" %>

 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
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
					<strong><font color="red">服装列表</font></strong></td>
			</tr>
			<tr align="center" style="font-weight:bold;">
			 
				<td>
					ID</td>
				<td>
					道具名称</td>
					<td>头像等级</td>
					<td>性别</td>
					<td>图片</td>
				<td>
					 价格</td>
				<td>
					赠送<%=UiCommon.StringConfig.GoldName %></td>
				<td>
					操作</td>
			</tr>
			<asp:Repeater ID="rptClothesList" runat="server">
				<ItemTemplate>
					 
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
						<td  >
							<%=TableID = TableID + 1%>
						</td>
						 
						<td>
							<%# Eval("LogName")%>
						</td>
						<td><%#Eval("LogID") %></td>
						<td><%#(Eval("Sex").ToString()=="True")?"男":"女" %></td>
						<td><img src='/Image/Users/<%#Eval("Sex").ToString() == "True" ? "b_" +( Convert.ToInt32(Eval("LogID").ToString())+1) + ".png" : "g_" + (Convert.ToInt32(Eval("LogID").ToString())+1) + ".png"%>' alt="" width="55" height="55" onerror="this.src='/Images/NoPicture/no_pic.gif';this.onerror='';" /></td>
						<td>
							<%=UiCommon.StringConfig.MoneyName %>:<%# Eval("Price") %></td>
						<td>
							 <%# Eval("SendLotteries") %></td>
						<td>
							<a href='ClothEdit.aspx?id=<%# Eval("ID") %>'>修改价格</a></td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label runat="server" Text="暂无任何记录！" ID="NoProList" Visible="false"></asp:Label>
			 
		</table>
	</form>
</body>
</html>
