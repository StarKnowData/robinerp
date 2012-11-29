<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_UserIp_Top" Codebehind="UserIp_Top.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
<!--
body {
	background-color: #ffffff;
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
            <%--<tr>
                <td class="title_05">
                    <a href="?action=search">搜索用户</a> <a href="?action=list">所有用户列表</a> <a href="?action=dayreg">
                        今日注册用户</a> <a href="?action=24reg">24小时内注册</a> <a href="?action=24login">24小时内登录</a>
                    <a href="?action=regip">注册IP查询</a> <a href="?action=regip100" style='color: red'>注册IP（TOP100）排行榜</a>
                </td>
            </tr>--%>
        </table>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td style="height: 5px">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>注册IP排列榜(TOP100)</strong></td>
            </tr>
            <asp:Repeater ID="UserRegIp" runat="server">
                <ItemTemplate>
                    <tr>
                        <td align='left' width='200'>
                            &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; IP：<%# Eval("RegisterIP")%></td>
                        <td align='left'>
                            <font color="red"><%# Eval("ipcount") %></font>个</td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
        </table>
          
    </form>
</body>
</html>
