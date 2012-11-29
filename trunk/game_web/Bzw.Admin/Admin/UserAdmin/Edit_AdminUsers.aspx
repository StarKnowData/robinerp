<%@ Page Language="C#" AutoEventWireup="true"
	Inherits="Admin_Edit_AdminUsers" Codebehind="Edit_AdminUsers.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>修改管理员密码 </title>
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
//  if(document.Login.AdminName.value == '') {
//    alert('温馨提示：\n\n请输入用户名！');
//    document.Login.AdminName.focus();
//    return false;
//  }
  if(document.Login.AdminPwd.value == '') {
    alert('温馨提示：\n\n请输入原始密码！');
    document.Login.AdminPwd.focus();
    return false;
  }
  if(document.Login.AdminPwd1.value == '') {
    alert('温馨提示：\n\n请输入新密码！');
    document.Login.AdminPwd1.focus();
    return false;
  }
   if(document.Login.AdminPwd2.value == '') {
    alert('温馨提示：\n\n请输入新密码！');
    document.Login.AdminPwd2.focus();
    return false;
  }
  
   if(document.Login("AdminPwd1").value!=document.Login("AdminPwd2").value )
		{
		   alert("温馨提示：\n\n对不起，两次密码不一样，请确认您输入的新密码！");
		   document.Login("AdminPwd1").focus();
		   return false;
		}
		else
		{
		    return true;
		}
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
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
                <strong>修改个人密码</strong></td>
        </tr>
        <tr>
            <td colspan="2" align="center">
                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
        </tr>
        <tr>
            <td align="right" width="25%">
                用户名：</td>
            <td align="left">
                <asp:Literal ID="ltUserName" runat="server"></asp:Literal></td>
        </tr>
        <tr>
            <td align="right" width="25%">
                旧密码：</td>
            <td align="left">
                <asp:TextBox ID="AdminPwd" TextMode="Password" runat="server" class="put" MaxLength="20"></asp:TextBox></td>
        </tr>
        <tr>
            <td align="right" width="25%">
                新密码：</td>
            <td align="left">
                <asp:TextBox ID="AdminPwd1" TextMode="Password" runat="server" class="put" MaxLength="20"></asp:TextBox>
                </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                确认新密码：</td>
            <td align="left">
                <asp:TextBox ID="AdminPwd2" TextMode="Password" runat="server" class="put" MaxLength="20"></asp:TextBox></td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
            <td align="left">
                <asp:Button ID="Button2" runat="server" OnClick="EditAdminUsers" Text="确定修改" class="put" />
            </td>
        </tr>
    </table>
			<%--<center>
				<table width="68%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolorlight="#335078"
					bordercolordark="#FFFFFF" bgcolor="#C5D5E4" style="font-size: 12px; letter-spacing: 1px;">
					<tr bgcolor="#B6EBC4">
						<td bgcolor="#C5D5E4" height="25" style="width: 615px">
							<p align="center">
								<b>修改密码</b>
						</td>
					</tr>
					<tr>
						<td height="21" align="middle" bgcolor="#DFE8F0" style="border-bottom: medium none;
							width: 615px;">
							<div align="center">
								<br>
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;用户名：&nbsp;<asp:TextBox ID="AdminName" runat="server" MaxLength="15" BackColor="ControlLightLight"
									class="put"></asp:TextBox>
								<asp:Literal ID="ltUserName" runat="server"></asp:Literal>
							</div>
						</td>
					</tr>
					<tr>
						<td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;
							border-bottom: medium none; width: 615px;">
							<div align="center">
								原始密码：
								<asp:TextBox ID="AdminPwd" TextMode="Password" runat="server" class="put"></asp:TextBox>
							</div>
						</td>
					</tr>
					<tr>
						<td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;
							border-bottom: medium none; width: 615px;">
							<div align="center">
								&nbsp;&nbsp;&nbsp;&nbsp;新密码：
								<asp:TextBox ID="AdminPwd1" TextMode="Password" runat="server" class="put"></asp:TextBox>
							</div>
						</td>
					</tr>
					<tr>
						<td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;
							border-bottom: medium none; width: 615px;">
							<div align="center">
								确认密码：
								<asp:TextBox ID="AdminPwd2" TextMode="Password" runat="server" class="put"></asp:TextBox>
							</div>
						</td>
					</tr>
					<tr>
						<td height="25" bgcolor="#DFE8F0" style="border-top: medium none; width: 615px;">
							<p align="center">
								<asp:Button ID="Button1" runat="server" Text="确定修改" class="put" name="B1" OnClick="EditAdminUsers" />
						</td>
					</tr>
				</table>
			</center>--%>
		</form>
	</div>
</body>
</html>
