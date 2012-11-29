<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameBattleRoomsWrite" Codebehind="GameBattleRoomsWrite.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="2" class="title_03">
					<strong>添加混战房间</strong></td>
			</tr>
			<tr>
				<td align="right">
					房间名称：</td>
				<td align="left">
					<asp:TextBox ID="txtRoomName" runat="server" CssClass="put"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtRoomName" Display="Dynamic" ErrorMessage="请输入房间名称"></asp:RequiredFieldValidator></td>
			</tr>
			<tr>
				<td align="right">
					开始时间：</td>
				<td align="left">
					<asp:TextBox ID="txtBeginTime" runat="server" CssClass="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndTime\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtBeginTime" Display="Dynamic" ErrorMessage="请输入起始时间"></asp:RequiredFieldValidator></td>
			</tr>
			<tr>
				<td align="right">
					结束时间：</td>
				<td align="left">
					<asp:TextBox ID="txtEndTime" runat="server" CssClass="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginTime\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate="txtEndTime" Display="Dynamic" ErrorMessage="请输入结束时间"></asp:RequiredFieldValidator></td>
			</tr>
			<tr>
				<td>
					&nbsp;</td>
				<td align="left">
					<asp:Button ID="btnSubmit" runat="server" Text="填好提交" Class="put" OnClick="btnSubmit_Click" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
