<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Sconfig_SystemStatEveryDay" Codebehind="SystemStatEveryDay.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

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
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03" align="left">
					&nbsp;&nbsp;&nbsp;&nbsp;<a href="SystemStatEveryDay.aspx?Date=<%= DateTime.Now .ToShortDateString() %>">今天统计</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<strong> 统计日期：</strong><asp:TextBox ID="txtDate" runat="server"></asp:TextBox>
					<asp:Button ID="btnStat" runat="server" Text="统计" class="put" OnClick="btnStat_Click" />
				</td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0" style="background-color: White">
			<tr>
				<td style="background-color: White; height: 5px">
				</td>
			</tr>
		</table>
		<asp:Repeater ID="PrizesHList" runat="server">
			<ItemTemplate>
				<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
					<tr>
						<td colspan="2" class="title_03" align="center">
							<strong>游戏记录统计［<%=strDateTime%>］</strong></td>
					</tr>
					<tr>
						<td align="right" width="40%">
							当天所玩局数&nbsp;&nbsp;&nbsp;
							<td width="60%" align="left">
								&nbsp;&nbsp;<%# Eval("JiShu")%>局
							</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天游戏时间总数&nbsp;&nbsp;&nbsp;
							<td align="left">
								&nbsp;&nbsp;<%# Eval("GameTimes")%>秒
							</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天平均每局时间&nbsp;&nbsp;&nbsp;
							<td align="left">
								&nbsp;&nbsp;<%# Eval("AvgTime")%>秒
							</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天所交税总数&nbsp;&nbsp;&nbsp;
							<td align="left">
								&nbsp;&nbsp;<%# Eval("GameTax")%>金币
							</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天平均每局交税数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("AvgGameTax")%>金币
						</td>
					</tr>
					<tr>
						<td colspan="2" class="title_03" align="center">
							<strong>划账记录每日统计［<%=strDateTime%>］</strong></td>
					</tr>
					<tr>
						<td align="right" width="34%">
							划账总数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("TransCount")%>金币
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							手续费总数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("TransTax")%>金币
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							最高划账手续费&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("MaxTransTax")%>金币
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							最底划账手续费&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("MinTransTax")%>金币
						</td>
					</tr>
					<tr>
						<td colspan="2" class="title_03" align="center">
							<strong>今日用户注册统计［<%=strDateTime%>］</strong></td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天注册人数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("T_RegUserCount")%>人
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天被推广人数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("T_TGUserCount")%>人
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天总赠送金币数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("T_PresentMoney")%>金币
						</td>
					</tr>
					<tr>
						<td colspan="2" class="title_03" align="center">
							<strong>用户充值每日统计［<%=strDateTime%>］</strong></td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天点卡充值数量&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("T_PointCardCont")%>张
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天点卡充值总金币数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("T_PointCardMoney")%>金币
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天银行充值次数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("T_BankPayCont")%>次
						</td>
					</tr>
					<tr>
						<td align="right" width="34%">
							当天银行充值总金币数&nbsp;&nbsp;&nbsp;</td>
						<td align="left">
							&nbsp;&nbsp;<%# Eval("T_BankPayMoney")%>金币
						</td>
					</tr>
					<tr>
						<td colspan="2" class="title_03" align="center">
							<strong>后台急需处理［<%=strDateTime%>］</strong></td>
					</tr>
					<tr><td align="right" width="34%">
					未审核的留言数&nbsp;&nbsp;&nbsp;
					</td>
					<td align="left">&nbsp;&nbsp;<%#Eval("T_UndoMsg")%>个&nbsp;&nbsp;<a href="../Books/Book.aspx">查看</a></td>
					</tr>
					<tr><td align="right" width="34%">
					未审核的照片数&nbsp;&nbsp;&nbsp;
					</td>
					<td align="left">&nbsp;&nbsp;<%#Eval("T_UndoPhoto")%>张&nbsp;&nbsp;<a href="../Users/Pictures.aspx">查看</a></td>
					</tr>
					<tr><td align="right" width="34%">
					未审核的奖品兑换记录数&nbsp;&nbsp;&nbsp;
					</td>
					<td align="left">&nbsp;&nbsp;<%#Eval("T_UndoPrizeExchange")%>条&nbsp;&nbsp;<a href="../Prizes/PrizesH.aspx">查看</a></td>
					</tr>
				</table>
			</ItemTemplate>
		</asp:Repeater>
	</form>
</body>
</html>
