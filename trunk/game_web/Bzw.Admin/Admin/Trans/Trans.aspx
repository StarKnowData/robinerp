<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Trans_Trans" Codebehind="Trans.aspx.cs" %>

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
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="15">
					<font color="red"><strong>
						<%=titlenames %>
					</strong></font>
				</td>
			</tr>
			<tr>
				<td>
					序号</td>
				<td>
					转账人</td>
				<td>
					转账前</td>
				<td>
					转账后</td>
				<td>
					接受人</td>
				<td>
					转账前</td>
				<td>
					转账后</td>
				<td>
					转账金币</td>
				<td>
					实际到账金额
				</td>
				<td>
					手续费</td>
				<td>
					转账时间</td>				
				<td>
					操作</td>
			</tr>
			<asp:Repeater ID="TransList" runat="server">
				<ItemTemplate>
					<tr>
						<td>
							<%=tableids=tableids+1 %>
						</td>
						<td>
							<font color="red">
								<%# Eval("UserName") %>
							</font>
						</td>
						<td>
							<%# Eval("TransBefore")%>
						</td>
						<td>
							<%# Eval("TransAfter") %>
						</td>
						<td>
							<font color="red">
								<%# Eval("UserNameZZ") %>
							</font>
						</td>
						<td>
							<%# Eval("ZZ_TransBefore") %>
						</td>
						<td>
							<%# Eval("ZZ_TransAfter")%>
						</td>
						<td>
							<%# Eval("Money") %>
						</td>
						<td>
							<%# Convert.ToInt64( Eval( "Money" ).ToString())-Convert.ToInt64(Eval("Tax").ToString())%>
						</td>
						<td>
							<%# Eval("Tax") %>
						</td>						
						<td>
							<%# Eval("TransTime") %>
						</td>
						<td>
							<a href='TransDel.aspx?id=<%# Eval("id") %>' onclick="javascript:return confirm('您确定要删除当前记录吗？删除后将不能恢复!!');">删除</a></td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoTransList" runat="server" Text=" <tr><td colspan='16' align='center'>暂无任何记录！</td></tr>" Visible="false"></asp:Label>
			<tr>
				<td colspan='16' align='right'>
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
