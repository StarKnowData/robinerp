<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="QPS.Web.Default" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>后台管理系统</title>
    <link href="Css/login.css" rel="stylesheet" type="text/css">
</link>
    		<style type="text/css">
BODY { BACKGROUND-IMAGE: url(imgs/login_01.jpg) }
		</style>
		
				<script language="javascript">
<!--
function SetFocus()
{
if (document.Form1.txtAdminname.value=="")
	document.Form1.txtAdminname.focus();
else
	document.Form1.UserName.select();
}
function CheckForm()
{
	if (document.Form1.CheckCode.value==""){
       alert ("请输入您的验证码！");
       document.Form1.CheckCode.focus();
       return(false);
    }
}

//-->
		</script>
</head>
<body style="margin:auto;">
		<form id="Form1" method="post" runat="server" target="_top">
			<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="center" valign="middle"><br>
						<br>
						<br>
						<table width="638" height="474" border="0" align="center" cellpadding="0" cellspacing="0"
							id="__01">
							<tr>
								<td width="638" height="38"><img src="imgs/loginpic_01.jpg" width="638" height="38" alt=""></td>
							</tr>
							<tr>
								<td height="40"><img src="imgs/loginpic_02.jpg" width="638" height="40" alt=""></td>
							</tr>
							<tr>
								<td height="38"><img src="imgs/loginpic_03.jpg" width="638" height="38" alt=""></td>
							</tr>
							<tr>
								<td height="42"><img src="imgs/loginpic_04.jpg" width="638" height="42" alt=""></td>
							</tr>
							<tr>
								<td height="32"><img src="imgs/loginpic_05.jpg" width="638" height="32" alt=""></td>
							</tr>
							<tr>
								<td height="47"><img src="imgs/loginpic_06.jpg" width="638" height="47" alt=""></td>
							</tr>
							<tr>
								<td height="29"><img src="imgs/loginpic_07.jpg" width="638" height="29" alt=""></td>
							</tr>
							<tr>
								<td height="56" background="imgs/loginpic_08.jpg">
									<table width="100%" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="180">&nbsp;</td>
											<td width="60">用户名：</td>
											<td width="110">
												<asp:TextBox id="txtAdminname" runat="server" Width="100px" MaxLength="20" onMouseOver="this.style.background='#E1F4EE';"
													onMouseOut="this.style.background='#FFFFFF'">admin</asp:TextBox></td>
											<td width="48">密&nbsp;&nbsp;码：</td>
											<td width="110"><asp:TextBox id="txtAdminPW" runat="server" Width="100px" MaxLength="20" TextMode="Password"
													onMouseOver="this.style.background='#E1F4EE';" onMouseOut="this.style.background='#FFFFFF'">123654</asp:TextBox>
											</td>
											<td width="106"><asp:ImageButton Runat="server" ID="imgbtn" ImageUrl="imgs/login_04.jpg" Border="0" width="92" height="30" OnClick="imgbtn_Click"></asp:ImageButton></td>
										</tr>
										<tr>
											<td width="220"></td>
											<td>验证码：</td>
											<td width="147" align="left" valign="middle"><input name="CheckCode" runat="server" id="checkcode" size="6" maxlength="4" onMouseOver="this.style.background='#E1F4EE';" onMouseOut="this.style.background='#FFFFFF'" onFocus="this.select(); " onblur="return checkcode_onblur()">&nbsp;<img src="gif.aspx" border="0" onclick="this.src='gif.aspx?time='+Math.random();"></td>
											<td colspan="3" align="center">&nbsp;</td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="50" background="imgs/loginpic_09.jpg"><asp:requiredfieldvalidator id="Requiredfieldvalidator2" Runat="server" ControlToValidate="txtAdminname" Display="Static"
										ErrorMessage="用户名不能为空"></asp:requiredfieldvalidator>
								<%--	<asp:regularexpressionvalidator id="RegularExpressionValidator2" runat="server" ControlToValidate="txtAdminname"
										ErrorMessage="用户名4-20位英文数字" ValidationExpression="\w{4,20}"></asp:regularexpressionvalidator>--%>
									<asp:requiredfieldvalidator id="Requiredfieldvalidator1" Runat="server" ControlToValidate="txtAdminPW" Display="Static"
										ErrorMessage="密码不能为空"></asp:requiredfieldvalidator>
									<asp:regularexpressionvalidator id="Regularexpressionvalidator1" runat="server" ControlToValidate="txtAdminPW" ErrorMessage="密码4-20位英文数字"
										ValidationExpression="\w{4,20}"></asp:regularexpressionvalidator></td>
							</tr>
							<tr>
								<td height="47" style="HEIGHT: 47px"><img src="imgs/loginpic_10.jpg" width="638" height="46" alt=""></td>
							</tr>
							<tr>
								<td height="56"><img src="imgs/loginpic_11.jpg" width="638" height="56" alt=""></td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</form>
	</body>
<%--<body>
    <form id="form1" runat="server">
    <div>
    <table>
        <tr>
            <td>用户名：</td>
            <td>
                <asp:TextBox ID="txtName" runat="server"></asp:TextBox>
            </td>
            <td></td>
        </tr>
         <tr>
            <td>密码：</td>
            <td>
                <asp:TextBox ID="txtPwd" runat="server"></asp:TextBox>
            </td>
            <td></td>
        </tr>
         <tr>
            <td></td>
            <td>
            <asp:Button ID="Button1" runat="server" Text="登陆" onclick="Button1_Click" />
            <asp:Button ID="Button2" runat="server" Text="取消" onclick="Button2_Click" />
                <asp:LinkButton ID="LinkButton1" runat="server" onclick="LinkButton1_Click">注册</asp:LinkButton>
            </td>
            <td></td>
        </tr>
    
    </table>       
    </div>
    </form>
</body>--%>
</html>
