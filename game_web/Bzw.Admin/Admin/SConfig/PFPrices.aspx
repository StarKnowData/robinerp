<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_PFPrices" Codebehind="PFPrices.aspx.cs" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
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
                <td class="title_03" colspan="5">
                    <strong><font color="red">魅力值清零道具列表</font></strong></td>
            </tr>
            <tr style="text-align:center; font-weight:bold;"> 
                <td>
                    ID号</td>
                <td>
                    道具名称</td>
                <td>
                    价格</td>
                <td>
                    清零魅力值</td>
                <td>
                    操作</td>
            </tr>
            <asp:Repeater ID="ProList" runat="server">
                <ItemTemplate>
                    <tr>
     <%
         if ((TableID) % 2 == 0)
        {
            Response.Write("  <tr align='center' bgcolor='#E1E1E1' height='25px' >");
        }
        else
        {
            Response.Write("  <tr align='center' bgcolor='#ffffff' height='25px'>"); 
        }       
     %>
                    <td style="display:none"><%=TableID = TableID + 1%></td>
                        <td>
                            <%# Eval("ID")%>
                        </td>
                        <td>
                            <%# Eval("Title")%></td>
                        <td>
                            金币:<%# Eval("Price")%></td>
                        <td>
                            <%# Eval("DecFasci")%></td>
                        <td>
                            <a href='PFPricesE.aspx?id=<%# Eval("ID") %>'>修改</a>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Label runat="server" Text="暂无任何记录！" ID="NoProList" Visible="false"></asp:Label>
            <tr>
                <td colspan='11' align='right'>
                    <div id="page_link" class="page_link">
                     	<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
					</webdiyer:AspNetPager>
                     </div>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
