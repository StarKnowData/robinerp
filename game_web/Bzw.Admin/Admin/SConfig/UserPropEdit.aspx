<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_UserPropEdit" Codebehind="UserPropEdit.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

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
				<th class="title_03">
					玩家<asp:Literal runat="server" ID="ltUserName"></asp:Literal>道具修改
				</th>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td height="5">&nbsp;
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<asp:PlaceHolder runat="server" ID="phPropList"></asp:PlaceHolder>
		</table>
		<br />
		<table width="100%" border="0" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" class="admin_table">
			<tr>
				<td class="title_03" align="center">
					<asp:Button runat="server" ID="btnSubmit" Text=" 修 改 " CssClass="put" OnClick="btnSubmit_Click" />&nbsp;&nbsp;&nbsp;&nbsp;<input type="button"  value="返 回" onclick="javascript:history.back()" class="put" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
