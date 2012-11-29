<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PrList.aspx.cs" Inherits="Admin_Lotter_PrList" %>

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
                    <strong>奖品管理</strong></td>
            </tr>
            <tr>
                <td class="title_05">
                    <a href="PrList.aspx">所有奖品列表</a> <a href="PrAdd.aspx">添加奖品 </a>
                </td>
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
                <td class="title_03" colspan="11">
                    <strong><font color="red">奖品列表</font></strong></td>
            </tr>
            <tr>
                <td>
                    序号</td>
                <td>
                    奖品名</td>
                <td>
                    图片地址</td>
                <td>
                    金概率</td>
                    <td>玉概率</td><td>银概率</td>
                    <td>添加时间</td>
                <td>
                    操作</td>
            </tr>
                <asp:Repeater ID="PrAdlist" runat="server">
               <ItemTemplate>
            <tr>
                <td align='center'>
                    <%=TableID=TableID+1 %></td>
                <td>
                    <%# Eval("LotteryAwardName")%></td>
                    <td align="center"><%#Eval("PicName")%></td>
                <td>
                    <%# Eval("GoldRate")%></td>
                   
                    <td><%#Eval("JadeRate") %></td> <td><%#Eval("SilverRate")%></td>
                    <td><%#Eval("AddDate") %></td> 
                <td>
                    <a href="PrEdit.aspx?id=<%# Eval("id") %>">修改</a>&nbsp;&nbsp;&nbsp;&nbsp;<a href='PrList.aspx?id=<%# Eval("id") %>' onclick="javacript:return confirm('是否确定要删除吗?删除后不能恢复!');">
                        删除</a></td>
            </tr>
            </ItemTemplate>
             </asp:Repeater>
            
        </table>
    </form>
</body>
</html>

