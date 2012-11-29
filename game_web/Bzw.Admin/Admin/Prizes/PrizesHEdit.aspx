<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Prizes_PrizesHEdit" Codebehind="PrizesHEdit.aspx.cs" %>

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
                <td colspan="2" class="title_03">
                    <strong>修改兑奖记录资料</strong></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品名称：</td>
                <td width="83%" align="left">
                    <%=PName %></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    兑奖用户：</td>
                <td width="83%" align="left">
                    <%=PUser%></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    兑奖时间：</td>
                <td width="83%" align="left">
                    <%=Ptime %></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    收货人姓名：</td>
                <td width="83%" align="left"><%=PNameUser %>
                </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    收货人电话：</td>
                <td width="83%" align="left"><%=Ptel %>
                </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    收货人地址：</td>
                <td width="83%" align="left"><%=Paddress %>
                </td>
            </tr>
             <tr>
                <td width="17%" align="right">
                   用户填写的备注：</td>
                <td width="83%" align="left"><%=PUserRemark%>
                </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    是否发货：</td>
                <td width="83%" align="left">
                    <input name="IsCash" type="radio" value="1" class="put" <%=PIsCash.ToString().ToLower()=="true"  ? "checked" : "" %>/>是
                    <input name="IsCash" type="radio" value="0" class="put" <%=PIsCash.ToString().ToLower() =="false"  ? "checked" : ""  %>/>否
                </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    <input type="hidden" name="action2" value="edit" /></td>
                <td width="83%" align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 "  OnClick="Prizes_Edit" class="put"/>
                    <input id="button" type="button" value="返 回" onclick="javascript:history.back();" class="put" />
                    </td>
            </tr>
        </table>
    </form>
</body>
</html>
