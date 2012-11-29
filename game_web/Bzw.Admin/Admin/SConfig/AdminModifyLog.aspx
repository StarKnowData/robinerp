<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Sconfig_AdminModifyLog" Codebehind="AdminModifyLog.aspx.cs" %>

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
                    <strong><font color="red">系统日志列表</font></strong></td>
            </tr>
            <tr>
                <td>
                    序号</td>
                <td>
                    用户名</td>
                <td>
                    描述</td>
                <td>
                    IP</td>
                <td>
                    操作系统</td>
                <td>
                    时间</td>
                <td>
                    状态</td>
            </tr>
            <asp:Repeater ID="PrizesHList" runat="server">
                <ItemTemplate>
                    <tr>
                        <td>
                            <%=TableId=TableId+1 %>
                        </td>
                        <td>
                            <%# Eval("AdminName")%></td>
                        <td>
                            <%# Eval("Description")%></td>
                        <td>
                            <%# Eval("IP")%></td>
                        <td>
                            <%# Eval("System") %></td>
                        <td>
                            <%# Eval("AddTime")%></td>
                        <td>
                            <%# Eval("State").ToString().ToLower() == "true" ? "<font color=\"red\">成功</font>" : "失败"%></td>
                       </tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Label ID="NoPrizesHList" runat="server" Text="暂无任何数据！" Visible="false"></asp:Label>
            <tr>
                <td colspan='11' align='right'>
                <div id="page_link" class="page_link">
                <webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True" OnPageChanging="WebPager1_PageChanging">
					</webdiyer:AspNetPager>
                          <%--  <asp:Literal ID="pageList" runat="server"></asp:Literal>--%>
                </div>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
