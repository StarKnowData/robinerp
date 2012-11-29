<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_CreateRanking" Codebehind="CreateRanking.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>无标题页</title>
     <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
   <form id="form1" runat="server" >
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td class="title_03">
                    <strong>生成排行榜Html页</strong></td>
            </tr>
        </table>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td height="5">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">

            <tr>
                
                <td align="center">
                    <asp:Button ID="Button1" runat="server"  Text="点击生成"  OnClick="CreateHtml" />
                    <asp:Label ID="msg" runat="server" ForeColor="red"></asp:Label>
                </td>
            </tr>
        </table>
 
    </form>
</body>
</html>
