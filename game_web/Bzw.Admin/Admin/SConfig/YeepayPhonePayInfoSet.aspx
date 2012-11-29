<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_YeepayPhonePayInfoSet" Codebehind="YeepayPhonePayInfoSet.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

	<script type="text/javascript" src="/Public/Js/jquery.js"></script>

	<script type="text/javascript" src="/Public/Js/public.js"></script>

	<style type="text/css">
    <!--
    .imeclose{ime-mode:disabled;}
    -->
    </style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03">
					<strong>易宝短信充值说明设置</strong></td>
			</tr>
			<tr>
				<td align="center">
					<FCKeditorV2:FCKeditor ID="fckContent" runat="server" BasePath="/Public/Js/fckeditor/" Height="500px">
					</FCKeditorV2:FCKeditor>
				</td>
			</tr>
			<tr>
				<td align="center">
					<asp:Button ID="Button1" runat="server" Text="提交修改" class="put" OnClick="Button1_Click" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
