<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_MoneyRankingViewSet" Codebehind="MoneyRankingViewSet.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
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
                    <strong>财富排行榜显示设置</strong></td>
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
                <td align="right" width="25%">
                    显示方式：</td>
                <td align="left">
                   <input type="radio" name="yes" value="0"  id="radio1" runat="server" />钱包+银行&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="radio2" name="yes" value="1" runat="server"/>钱包
                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; <span style="font-family:color:Gray;">说明：钱包+银行表示网站前台财富排行榜用的是钱包金币和银行金币总数来排行的</span>
                   </td>
               
            </tr>

            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"  OnClick="EditPric" />
                    <asp:Label ID="msg"  runat="server" ForeColor="red" Text=""></asp:Label>
                </td>
            </tr>
        </table>

    </form>
</body>
</html>
