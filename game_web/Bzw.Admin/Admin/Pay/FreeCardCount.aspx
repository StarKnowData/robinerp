<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Pay_FreeCardCount" Codebehind="FreeCardCount.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

	<script type="text/javascript" src="/Public/Js/jquery.js"></script>

	<script type="text/javascript" src="/Public/Js/public.js"></script>

	<style type="text/css">
    <!--
    body {
	    background-color: #FFFFFF;
	    margin-top: 0px;
    }
    .imeclose{ime-mode:disabled;}
    -->
    </style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="2" class="title_03">
					<strong>赠送免费卡数量设置</strong></td>
			</tr>
			<tr>
				<td align="right" width="25%">
					免费卡 </td>
				<td align="left">
					<input id="txt1Yuan" name="txt1Yuan" maxlength="12" runat="server" class="imeclose" onkeypress="return KeyPressNum(this,event);" />张
					<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txt1Yuan" Display="Dynamic" ErrorMessage="请输入免费卡数"></asp:RequiredFieldValidator>
					<asp:CompareValidator ID="CompareValidator1" runat="server" ControlToValidate="txt1Yuan" Display="Dynamic" ErrorMessage="只能输入大于0的整数！" Operator="GreaterThan" Type="Integer" ValueToCompare="0"></asp:CompareValidator></td>
			</tr>
			
			<tr>
				<td>
					&nbsp;
				</td>
				<td>
					<asp:Button ID="Button1" runat="server" Text="提交修改" class="put" OnClick="EditFilt" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
