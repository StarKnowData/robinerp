<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_GameInfo_GameType_Add" Codebehind="GameType_Add.aspx.cs" %>

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

	<script language="javascript" type="text/javascript">

function CheckForm() {
  if(document.getElementById("TypeName").value == '') {
    alert('温馨提示：\n\n请输入游戏分类名称！');
    document.getElementById("TypeName").focus();
    return false;
  }  
}
	</script>

</head>
<body>
	<form id="form1" runat="server" onsubmit='return CheckForm();'>
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="2">
					<strong>添加游戏分类</strong></td>
			</tr>
			<tr>
				<td width="20%" align="right" >
					分类名称：
				</td>
				<td>
					<input name="TypeName" type="text" value="" id="TypeName" class="put" maxlength="15" />
				</td>
			</tr>
			<tr>
				<td align="right">
					分类排序：</td>
				<td>
					<input name="TypeSort" type="text" id="TypeSort" value="0" size="5" maxlength="4"	class="put" />
				</td>
			</tr>
			<tr>
				<td align="center" colspan="2">
					<asp:Button ID="Button1" runat="server" Text=" 添 加 " class="put" OnClick="TypeAdd" />
					<input type="hidden" name="action2" value="add" />
					<input type="hidden" name="action" value="add" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
