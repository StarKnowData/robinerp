<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_PrEdit" Codebehind="PrEdit.aspx.cs" %>

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
                    <strong>修改推广员资料</strong></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    用户名：</td>
                <td width="83%" align="left">
                    <font color="red"><%=TGUserName %></font></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    真实姓名：</td>
                <td width="83%" align="left">
                    <input type="text" name="Truename" value="<%=Truename %>" class="put" maxlength="10"/></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    联系电话：</td>
                <td width="83%" align="left">
                    <input type="text" name="Phone" value="<%=Phone %>" class="put" maxlength="20" /></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    联系地址：</td>
                <td width="83%" align="left">
                    <input type="text" name="Address" value="<%=Address %>" class="put"  maxlength="50"/></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    总收入：</td>
                <td width="83%" align="left">
                    <font color="red"><%= MoneyCount%></font>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                    统计时间：<%=CountTime%></td>
            </tr>
            <tr>
                <td align="right">
                    是否审核：</td>
                <td align="left">
                    <input type="radio" name="Pass" value="1" class="put" <%= (Pass.ToString().ToLower()=="true" ? "CHECKED" : "") %> />审核
                    <input type="radio" name="Pass" value="0" class="put" <%= (Pass.ToString().ToLower()=="false" ? "CHECKED" : "") %>/>未审核
                </td>
            </tr>
            <tr>
                <td align="right">
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="确认修改" class="put" OnClick="PrEd" />
                    <input type="reset" name="Submit2" value="还原设置" class="put" />
                    <input type="button" name="Submit2" onclick="javascript:history.back();" value="返回上一页"
                        class="put" />
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
