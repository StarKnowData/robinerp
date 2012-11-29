<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_CountIp" Codebehind="CountIp.aspx.cs" %>

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
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td class="title_03">
                    <strong>会员管理</strong></td>
            </tr>
        </table>
        <table width="100%" border="0" cellspacing="0" cellpadding="0" style="background-color: White">
            <tr>
                <td style="height: 5px">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>统计每日该注册IP,机器码的统计</strong></td>
            </tr>
            <asp:Repeater ID="IpCount" runat="server">
                <ItemTemplate>
                    <tr>
                        <td align='right' width='200'>
                            <%#Convert.ToDateTime( Eval("ddr")).ToString("yyyy/MM/dd") %>
                        </td>
                        <td align='left'>
                            <font color="red">
                                <%# Eval("bbr")%>
                            </font>个注册用户</td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Label ID="NoIpCount" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
        </table>
    </form>
</body>
</html>
