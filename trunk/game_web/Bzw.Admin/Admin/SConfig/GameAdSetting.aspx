<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_GameAdSetting" Codebehind="GameAdSetting.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
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
                    <strong>游戏广告位管理</strong></td>
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
                <td>
                    ID</td>
                <td>
                    标题</td>
                <td>
                    内容</td>
                
                <td>
                    操作</td>
            </tr>
                <asp:Repeater ID="FlashAdlist" runat="server">
               <ItemTemplate>
            <tr>
                <td align='center'>
                    <%=TableID=TableID+1 %></td>
                <td>
                    <%# Eval("title")%></td>
                <td>
                    <%# Eval("content")%></td>
             
                <td>
                    <a href="GameADEdit.aspx?id=<%# Eval("id") %>">修改</a></td>
            </tr>
            </ItemTemplate>
             </asp:Repeater>
            
        </table>
    </form>
</body>
</html>
