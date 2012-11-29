<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_UserAnaly_Edit_Users" Codebehind="Edit_Users.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>修改管理员密码 </title>
    <link href="../css/Inc_style.css" rel="stylesheet" type="text/css"/>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/ecmascript" language="javascript">
    <!--
    function CheckForm(){    
        var userName = document.getElementById('txtUserName');
        if(!alertNull(userName,'请输入用户名！'))
        {
          return false;
        }        
        
        var AdminPwd1 = document.getElementById('AdminPwd1');
        if(!alertNull(AdminPwd1,'请输入新密码！'))
        {
          return false;
        } 
        
        if(AdminPwd1.value.trim() != AdminPwd2.value.trim()) {
            alert('对不起，两次输入的新密码不一致，请重新输入！');
            AdminPwd2.focus();
            return false;
        }  
        
        return true;
    }

    //-->
    </script>
</head>
<body>
<form id="form1" runat="server" onsubmit="return CheckForm()">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
                <strong>修改运营系统用户密码</strong></td>
        </tr>
        <tr>
            <td colspan="2" align="center">
                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
        </tr>
        <tr>
            <td align="right" width="25%">
                用户名：</td>
            <td align="left">
                <asp:TextBox ID="txtUserName" runat="server" class="put" MaxLength="20"></asp:TextBox></td>
        </tr>
        <tr>
            <td align="right" width="25%">
                新密码：</td>
            <td align="left">
                <asp:TextBox ID="txtPass" TextMode="Password" runat="server" class="put" MaxLength="20"></asp:TextBox>
                </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                确认新密码：</td>
            <td align="left">
                <asp:TextBox ID="txtPass2" TextMode="Password" runat="server" class="put" MaxLength="20"></asp:TextBox></td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
            <td>
                <asp:Button ID="Button2" runat="server" OnClick="EditAdminUsers" Text="确定修改" class="put" />
            </td>
        </tr>
    </table>
</form>
</body>
</html>

