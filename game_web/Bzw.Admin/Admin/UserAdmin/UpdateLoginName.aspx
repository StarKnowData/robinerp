<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_UserAdmin_UpdateLoginName" Codebehind="UpdateLoginName.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>修改登录名</strong></td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    网站后台默认管理员登录名：</td>
                <td align="left">
                    <asp:TextBox ID="txtAdminName" runat="server"　Width="100px" MaxLength="20"></asp:TextBox><font color="red">*</font>限20个字符之内
                    </td>
            </tr>            
            <tr>
                <td>
                    &nbsp;
                </td>
                <td>
                    <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text=" 提 交 " class="put" />
                    &nbsp;&nbsp;<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                </td>
            </tr>
            
        </table>
    </form>
</body>
</html>
