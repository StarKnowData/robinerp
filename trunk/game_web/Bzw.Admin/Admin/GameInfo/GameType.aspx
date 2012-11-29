<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_GameInfo_GameType" Codebehind="GameType.aspx.cs" %>

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
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td class="title_03">
                    <strong>游戏分类管理</strong></td>
            </tr>
        </table>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td height="5">
                </td>
            </tr>
        </table>
        <asp:Repeater ID="TypeListInfo" runat="server">
            <HeaderTemplate>
                <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
                    bgcolor="F2F8FF" class="admin_table">
                    <tr>
                        <td width="13%">
                            序号</td>
                        <td width="22%">
                            分类ID号</td>
                        <td width="26%">
                            分类名称</td>
                        <td width="22%">
                            分类排序</td>
                        <td width="8%">
                            修改</td>
                        <td width="9%">
                            删除</td>
                    </tr>
            </HeaderTemplate>
            <ItemTemplate>
                <tr>
                    <td>
                        <%=tableids=tableids+1 %>
                    </td>
                    <td>
                        <%# Eval("TypeID") %>
                    </td>
                    <td>
                        <a href='?action=edit&TypeID=1'>
                            <%# Eval("TypeName") %>
                        </a>
                    </td>
                    <td>
                        <%# Eval("TypeSort") %>
                    </td>
                    <td>
                        <a href="GameTypeEdit.aspx?id=<%# Eval("TypeID") %>" >修改</a></td>
                    <td>
                        <a href='GameTypeDel.aspx?id=<%# Eval("TypeID") %>' onclick='javascript:return confirm("删除分类将影响游戏的分类，您确定要删除吗？");'>
                            删除</a></td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Label runat="server" Text="暂无任何记录！" ID="NoTypeList" Visible="false"> </asp:Label>
        </table>
    </form>
</body>
</html>
