<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_ServiceContent" Codebehind="ServiceContent.aspx.cs" %>

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
                    <strong>客服中心内容设置</strong></td>
            </tr>
            <tr>
                <td align="right" style="width: 170px">
                    内容：</td>
                <td align="left">
                    <asp:TextBox ID="txtKey" runat="server" Height="497px" TextMode="MultiLine" Width="708px"></asp:TextBox>
                    </td>
            </tr>
            <tr>
                <td style="width: 170px">
                    &nbsp;
                </td>
                <td>
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"   OnClick="EditFilt"/>
                    &nbsp;&nbsp;<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                </td>
            </tr>
            
        </table>
    </form>
</body>
</html>
