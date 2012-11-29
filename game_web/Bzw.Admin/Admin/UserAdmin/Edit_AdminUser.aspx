<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Edit_AdminUser" Codebehind="Edit_AdminUser.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>修改管理员 </title>
	<link href="../css/Inc_style.css" rel="stylesheet" type="text/css">
	<style type="text/css">
<!--
body {
	background-color: #E7EEF5;
	margin-left: 0px;
	margin-top: 0px;
	margin-right: 0px;
	margin-bottom: 0px;
}
-->
</style>

	<script type="text/ecmascript" language="javascript">
<!--
function SetFocus() {
if(document.Login.AdminName.value == '')
  document.Login.AdminName.focus();
else
  document.Login.AdminName.select();
}

function CheckForm() {
  if(document.Login.AdminName.value == '') {
    alert('请输入用户名！');
    document.Login.AdminName.focus();
    return false;
  }
//  if(document.Login.AdminPwd.value == '') {
//    alert('请输入密码！');
//    document.Login.AdminPwd.focus();
//    return false;
//  }
}

function CheckBrowser() {
  var app=navigator.appName;
  var verStr=navigator.appVersion;
  if(app.indexOf('Netscape') != -1) {
    alert('友情提示：\n    您使用的是Netscape浏览器，可能会导致无法使用后台的部分功能。建议您使用 IE6.0 或以上版本。');
  } else if(app.indexOf('Microsoft') != -1) {
    if (verStr.indexOf('MSIE 3.0')!=-1 || verStr.indexOf('MSIE 4.0') != -1 || verStr.indexOf('MSIE 5.0') != -1 || verStr.indexOf('MSIE 5.1') != -1)
      alert('友情提示：\n    您的浏览器版本太低，可能会导致无法使用后台的部分功能。建议您使用 IE6.0 或以上版本。');
  }
}
//-->
	</script>

</head>
<body>
	<div align="center">
		<form method="POST" name='Login' id="Login" action="" runat="server" onsubmit='return CheckForm();'>
			<center>
				<table width="68%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolorlight="#335078"
					bordercolordark="#FFFFFF" bgcolor="#C5D5E4" style="font-size: 12px; letter-spacing: 1px;">
					<tr bgcolor="#B6EBC4">
						<td bgcolor="#C5D5E4" height="25" style="width: 615px">
							<p align="center">
								<b>修改管理员</b>
						</td>
					</tr>
					<tr>
						<td height="21" align="middle" bgcolor="#DFE8F0" style="border-bottom: medium none;
							width: 615px;">
							<div align="center">
								<br>
								用户名：
								<asp:TextBox ID="AdminName" runat="server" ReadOnly="true"  MaxLength="15" class="put"></asp:TextBox>
							</div>
						</td>
					</tr>
					<tr>
						<td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;
							border-bottom: medium none; width: 615px;">
							<div align="center">
								密&nbsp; 码：
								<asp:TextBox ID="AdminPwd" TextMode="Password" runat="server" class="put"></asp:TextBox>
							</div>
						</td>
					</tr>
					<tr id="trPopedom" runat="server">
						<td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;
							border-bottom: medium none;">
							<div align="left">
								分配权限：<br /><div style="padding-left:20px;line-height:30px;">
								<asp:CheckBoxList ID="chkListModels" runat="server" RepeatColumns="5" RepeatDirection="Horizontal"
									RepeatLayout="Flow">
								</asp:CheckBoxList></div>
							</div>
						</td>
					</tr>
					<tr>
						<td height="25" bgcolor="#DFE8F0" style="border-top: medium none; width: 615px;">
							<p align="center">
								<asp:Button ID="Button1" runat="server" Text="确定修改" name="B1" class="put" OnClick="EditAdminUser" />
								<input name="reback" type="button" value="返回上一页" onclick="javascript:history.back();"
									class="put" />
						</td>
					</tr>
				</table>
			</center>
		</form>
	</div>
</body>
</html>
