<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_UserAdmin_ConfigEncryption" Codebehind="ConfigEncryption.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server" >
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>加密/解密web.config的数据库链接</strong></td>
            </tr>
            <tr>
                <td align="right" style="width: 300px">
					当前web.config的数据库链接是否已经加密：</td>
                <td align="left">
                    <font color="red">
						<%=IsEncry?"是":"否" %></font></td>
            </tr>
            <tr>
                <td style="width: 241px">
                    &nbsp;
                </td>
                <td>
                    <asp:Button ID="Button1" runat="server" Text=" 加 密 " class="put" OnClick="Button1_Click" />
                    &nbsp;&nbsp;<asp:Button ID="Button2" runat="server" Text=" 解 密 " class="put" OnClick="Button2_Click" />&nbsp;
                </td>
            </tr>
            
        </table>
    </form>
</body>
</html>
