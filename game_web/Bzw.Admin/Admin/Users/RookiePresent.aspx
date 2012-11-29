<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_RookiePresent" Codebehind="RookiePresent.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>

	<style type="text/css">
	.imeclose{ime-mode:disabled;}
	.redtext{color:red;font-family:Arial,"宋体";}
	</style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>新手大礼包配置</strong></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td height="5">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="right">
					活动是否有效：</td>
				<td align="left">
					<asp:CheckBox runat="server" ID="cbxIsEnable" Text="有效" Checked="true" />
				</td>
			</tr>
			<tr>
				<td align="right">
					活动开始时间：</td>
				<td align="left">
					<asp:TextBox runat="server" ID="txtBeginDate" CssClass="put imeclose" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd'})"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="right">
					活动自动结束时间：</td>
				<td align="left">
					<asp:TextBox runat="server" ID="txtEndDate" CssClass="put imeclose" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'})"></asp:TextBox>
				</td>
			</tr>
			<tr style="display:none ">
				<td align="right">
					每次赠送金币数量：</td>
				<td align="left">
					<asp:TextBox runat="server" ID="txtMoney" CssClass="put imeclose" onkeypress="return KeyPressNum(this,event);"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="right" valign="top">
					赠送的道具数量设置：</td>
				<td align="left" style="padding:5px;">
					<asp:PlaceHolder runat="server" ID="phPropPresent"></asp:PlaceHolder>
				</td>
			</tr>
			<tr>
				<td>
					&nbsp;
				</td>
				<td align="left">
					<asp:Button ID="btnSubmit" runat="server" Text="提交修改" class="put" OnClick="btnSubmit_Click" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
