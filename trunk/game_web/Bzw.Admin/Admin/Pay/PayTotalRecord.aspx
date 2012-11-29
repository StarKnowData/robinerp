<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Pay_PayTotalRecord" Codebehind="PayTotalRecord.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>充值记录汇总</title>
 	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body style="text-align: center; font-size: 12px;">
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03" align="left">
					<strong>玩家[&nbsp;<asp:Literal runat="server" ID="ltUserName"></asp:Literal>&nbsp;]充值记录汇总</strong></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0" style="background-color: White">
			<tr>
				<td style="background-color: White; height: 5px">
				</td>
			</tr>
		</table>
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="1" bordercolor="A4B6D7" bgcolor="#A4B6D7" class="admin_table">
			<tr bgcolor="#ffffff">
				<td class="title_03" style="padding-top: 5px; padding-bottom: 5px; text-align: left">
				</td>
			</tr>
			<tr>
				<td>
					<asp:Repeater ID="rptPayBankList" runat="server">
						<HeaderTemplate>
							<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
								<tr>
									<td class="title_03" colspan="11" align="left">
									</td>
								</tr>
								<tr>
									<td>
										序号</td>
									<td>
										用户名</td>
									<td>
										充值金额</td>
									<td>
										充值卡号或定单号</td>
									<td>
										充值类型</td>
									<td>
										充值时间</td>
								</tr>
						</HeaderTemplate>
						<ItemTemplate>
							<%
								if( ( Userids ) % 2 == 0 )
								{
									Response.Write( "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" );
								}
								else
								{
									Response.Write( "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" );
								}       
							%>
							<td>
								<%# Container.ItemIndex+1 %>
							</td>
							<td>
								<%# Eval("UserName") %>
							</td>
							<td>
								<%# Eval("Account")%>
							</td>
							<td>
								<%# Eval("OperationNum")%>
							</td>
							<td>
								<%# Eval("TypeInfo")%>
							</td>
							<td>
								<%# Eval("AddTime")%>
							</td>
							</tr>
						</ItemTemplate>
						<FooterTemplate>
							</table>
						</FooterTemplate>
					</asp:Repeater>
					<asp:Literal ID="ltNoRecord" runat="server" Text="暂无任何记录!" Visible="false"></asp:Literal>
				</td>
			</tr>
			
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="background-color: White; height: 5px">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="right">
					<webdiyer:AspNetPager Style="margin-top: 5px;" runat="server" ID="WebPager1" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True" PageSize="20" OnPageChanging="WebPager1_PageChanging">
					</webdiyer:AspNetPager>
				</td>
			</tr>
			
		</table>
		<input type="button"  value="返   回" onclick="javascript:history.back()" class="put" />
	</form>
</body>
</html>
