<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Default" Codebehind="Default.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>登录管理中心</title>
	<link rel="stylesheet" href="css/Style.css" />
<script type="text/javascript" language="javascript"> 
function TopLocationToMe() 
{ 
document.getElementById("<%=txtUserName.ClientID %>").focus(); 
if(parent != null && parent.location.href != location.href) 
top.location.href = location.href; 
} 
</script>
<script type="text/ecmascript" language="javascript">
<!--

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
<body onload="TopLocationToMe()" >
	<p>
		&nbsp;
	</p>
	<p>
		&nbsp;
	</p>
	<form name='Login' id="Login" target='_parent' runat="server">
		<table width='600' border='0' align='center' cellpadding='0' cellspacing='0'>
			<tr>
				<td colspan='2'>
					<img src='Images/Admin_Login1.gif' width='600' height='126'></td>
			</tr>
			<tr>
				<td width='508' valign='top' background='Images/Admin_Login2.gif'>
					<table width='508' border='0' cellspacing='0' cellpadding='0'>
						<tr style="height: 20px; line-height: 20px;">
							<td width="70">
							</td>
							<td>
							</td>
							<td width="30">
							</td>
							<td>
							</td>
							<td colspan="1" width="35">
							</td>
							<td colspan='2'>
							</td>
						</tr>
						<tr>
							<td>
							</td>
							<td>
								<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtUserName">请填写用户名</asp:RequiredFieldValidator></td>
							<td>
							</td>
							<td>
								<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtPassword">请填写密码</asp:RequiredFieldValidator></td>
							<td colspan="1">
							</td>
							<td colspan='2'>
								<asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate="txtCode">请填写验证码</asp:RequiredFieldValidator></td>
						</tr>
						<tr>
							<td>
							</td>
							<td>
								<font color='#043BC9'>用户名：</font></td>
							<td>
							</td>
							<td>
								<font color='#043BC9'>密&nbsp;&nbsp;&nbsp;&nbsp;码：</font></td>
							<td colspan="1">
							</td>
							<td colspan='2'>
								<font color='#043BC9'>验证码：</font></td>
						</tr>
						<tr>
							<td>
							</td>
							<td>
								<asp:TextBox ID='txtUserName' type='text' MaxLength='20' Style='width: 110px; border-right: 0px;
									border-top: 0px; border-left: 0px; border-bottom: #c0c0c0 1px solid; background-color: #F7F7F7'
									onMouseOver="this.style.background='#ffffff';" onMouseOut="this.style.background='#F7F7F7'"
									onFocus='this.select();' runat="server"></asp:TextBox>&nbsp;
							</td>
							<td>
							</td>
							<td>
								<asp:TextBox ID='txtPassword' runat='server' TextMode="Password" MaxLength='20' Style='width: 110px;
									border-right: 0px; border-top: 0px; border-left: 0px; border-bottom: #c0c0c0 1px solid;
									background-color: #F7F7F7' onMouseOver="this.style.background='#ffffff';" onMouseOut="this.style.background='#F7F7F7'"
									onFocus='this.select();'></asp:TextBox>&nbsp;
							</td>
							<td>
							</td>
							<td>
								<asp:TextBox ID='txtCode' runat='server' size='6' MaxLength='4' Style='width: 50px;
									border-right: 0px; border-top: 0px; border-left: 0px; border-bottom: #c0c0c0 1px solid;
									background-color: #F7F7F7' onMouseOver="this.style.background='#ffffff';" onMouseOut="this.style.background='#F7F7F7'"
									onFocus='this.select();'></asp:TextBox>&nbsp;
							</td>
							<td>
								<img src="/Public/Getcode.aspx" height="18" onclick="javascript:this.src='/Public/Getcode.aspx?x=' + Math.random();"
									alt="验证码,看不清楚?请点击刷新验证码" style="cursor: pointer;" />&nbsp;</td>
						</tr>
						<tr>
							<td colspan="9" style="text-align: center; padding-top: 4px;">
								Design By： 深圳市正易龙科技有限公司</td>
						</tr>
					</table>
				</td>
				<td>
					<asp:ImageButton ID="ImageButton1" runat="server" src='Images/Admin_Login3.gif' Style='width: 92px;
						height: 126px;' OnClick="AddAdminLogin" />
				</td>
			</tr>
		</table>

		<script type="text/ecmascript" language="javascript">
        <!--
            try{
                document.getElementById('AdminName').focus();
            }catch(e){}
        //-->
		</script>

	</form>
</body>
</html>
