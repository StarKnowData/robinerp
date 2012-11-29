<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_SEO" Codebehind="SEO.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
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
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>SEO内容设置</strong></td>
            </tr>
            <tr>
                <td align="right" width="20%">
                    META-KEYWORDS：</td>
                <td align="left" width="80%">
                    <asp:TextBox ID="txtKey" runat="server" Height="45px" TextMode="MultiLine"　Width="550px"></asp:TextBox>限500个字符
                    </td>
            </tr>
            <tr>
                <td align="right">
                    META-DESCRIPTION：</td>
                <td align="left">
                    <asp:TextBox ID="txtDesc" runat="server" Height="45px" TextMode="MultiLine"　Width="550px"></asp:TextBox>限500个字符
                    </td>
            </tr>
            <tr>
                <td>
                    &nbsp;
                </td>
                <td>
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"   OnClick="EditFilt"/>
                    &nbsp;&nbsp;<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                </td>
            </tr>
            <tr>
                <td colspan="2" style="padding-left:20px;">
                    例如：<br />META-KEYWORDS：网络棋牌游戏，麻将，斗地主，双扣,休闲游戏,电子竞技,游戏下载<br />
                            META-DESCRIPTION：提供网络棋牌，对战，休闲等在线游戏的综合网络休闲娱乐平台.包括游戏下载</td>
            </tr>
            
        </table>
    </form>
</body>
</html>
