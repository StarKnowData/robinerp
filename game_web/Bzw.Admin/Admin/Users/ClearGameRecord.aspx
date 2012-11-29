<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_ClearGameRecord" Codebehind="ClearGameRecord.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #ffffff;
	margin-top: 0px;
}
-->
</style>

	<script type="text/javascript" src="/Public/Js/jquery.js"></script>

	<script type="text/javascript" src="/Public/Js/public.js"></script>

	<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>清理游戏记录</strong></td>
			</tr>
			<tr>
				<td class="title_03">
					可按时间段删除游戏记录，以减少数据量，提高查询速度；如果在下面的日期选择框中只输入开始时间或结束时间，则将删除指定时间点前面或后面的数据。<br />
					<strong style="color:Red;">注意：操作不可恢复，请谨慎使用！</strong>
				</td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td height="5px">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					按时间段从<asp:TextBox runat="server" ID="txtBeginTime" CssClass="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndTime\')}',dateFmt:'yyyy-MM-dd'})"></asp:TextBox>到<asp:TextBox runat="server" ID="txtEndTime" CssClass="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginTime\')}',dateFmt:'yyyy-MM-dd'})"></asp:TextBox>
					<asp:CustomValidator ID="CustomValidator1" runat="server" ClientValidationFunction="ValiTime" Display="Dynamic" ErrorMessage="请选择起止时间段！"></asp:CustomValidator>
					<script>
						function ValiTime(source,arguments)
						{
							var bt = $("#<%=txtBeginTime.ClientID %>");
							var et = $("#<%=txtEndTime.ClientID %>");
							if(bt.val().Trim() && et.val().Trim())
							{
								arguments.IsValid = false;
								return;
							}
							arguments.IsValid = true;
						}
					</script>
				</td>
			</tr>
			<tr>
				<td align="left">
					<asp:Button runat="server" ID="btnSubmit" Text=" 删 除 " OnClientClick="return confirm('您确认要删除吗？\r\n注意：此操作不可恢复！')" CssClass="put" OnClick="btnSubmit_Click" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
