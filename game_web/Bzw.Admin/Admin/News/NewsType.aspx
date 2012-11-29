<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_News_NewsType" Codebehind="NewsType.aspx.cs" %>

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
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="11">
                    <strong>新闻类别管理</strong></td>
            </tr>
            <tr>
                <td>
                    序号</td>
                <td>
                    类别名称</td>
                <td>
                    排列号</td>
                <td>
                    操作</td>
            </tr>
            <asp:Repeater ID="News_TypeList" runat="server">
                <ItemTemplate>
                    <tr>
                        <td>
                            <%=TableId = TableId+1%>
                        </td>
                        <td>
                            <%# Eval("typename") %></td>
                        <td>
                            <%# Eval("typesort") %></td>
                        <td>
                            <a href='NewsEtype.aspx?id=<%# Eval("typeid") %>'>修改</a>&nbsp;&nbsp;|&nbsp;&nbsp;<a href='NewsDtype.aspx?id=<%# Eval("typeid") %>'
                                onclick="javascript:return confirm('确定删除该新闻分类吗？删除后将不能恢复!');">删除</a></td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Label ID="NoNews_TypeList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
        </table>
    </form>
</body>
</html>
