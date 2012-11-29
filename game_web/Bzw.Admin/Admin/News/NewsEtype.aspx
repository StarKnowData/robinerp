<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_News_NewsEtype" Codebehind="NewsEtype.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
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
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="2">
                    <strong>修改新闻类别</strong></td>
            </tr>
            <tr>
                <td align="right">
                    类别名称：</td>
                <td align="left">
                    <input type="text" name="TypeName" value="<%=TypeName %>" class="put" maxlength="15"/></td>
            </tr>
            <tr>
                <td align="right">
                    排列号：</td>
                <td align="left">
                    <input type="text" name="TypeSort" value="<%=TypeSort %>" class="put" maxlength="4"/></td>
            </tr>
            <td align="right">
&nbsp;
            </td>
            <td align="left">
                <asp:Button ID="Button1" runat="server" Text=" 修 改 " OnClick="TypeEd" class="put"/>
                <input name="reback" type="button" value="返回上一页" onclick="javascript:history.back();" class="put"/>
            </td>
            </tr>
        </table>
    </form>
</body>
</html>
