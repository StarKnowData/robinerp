<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameTypes" Codebehind="GameTypes.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
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
                    <strong>游戏类别管理</strong></td>
            </tr>
            <tr>
                <td>
                    序号</td>
                <td>
                    类别名称</td>
                <td>
                    类别号</td>
                 <td>隶属类别</td>
                <td>
                    排列号</td>
                <td>
                    是否激活</td>
                <td>
                    操作</td>
            </tr>
            <asp:Repeater ID="GameTypesList" runat="server">
                <ItemTemplate>
                    <tr>
                        <td>
                            <%=tableids=tableids+1 %>
                        </td>
                        <td>
                            <%# Eval("KindName") %></td>
                        <td>
                            <%# Eval("KindID") %></td>
                            <td><%#Eval("KindParentName")%></td>
                        <td>
                            <%# Eval("IDSort")%></td>
                        <td>
                            <%# Eval("Enable").ToString().ToLower() == "1" ? "<font color=\"red\">已激活</font>" : "未激活"%></td>
                        <td>
                            <a href='GameTypesEdit.aspx?id=<%# Eval("KindID") %>'>修改</a>&nbsp;&nbsp; <a href='GameTypesDel.aspx?id=<%# Eval("KindID") %>' onclick="javascript:return confirm('确定删除该游戏名称吗？删除后将不能恢复!');">
                                删除</a></td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
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
                <td align="left">
                    <div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
