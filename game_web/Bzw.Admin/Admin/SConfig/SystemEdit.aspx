<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_SystemEdit" Codebehind="SystemEdit.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
    <title><%= SiteConfig.GetParaValue("Title")%></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="2">
                    <strong>网站参数维护</strong></td>
            </tr>
            <tr>
                <td align="right">
                    参数名称：</td>
                <td align="left"><asp:TextBox ID="txtParaName" ReadOnly=true runat="server" ></asp:TextBox></td>
            </tr>
            <tr>
                <td align="right">
                    参数值：</td>
                <td align="left">
                    <asp:TextBox ID="txtParaValue" runat="server" CssClass="put" Width="500" MaxLength="30"></asp:TextBox></td>
            </tr>
             <tr>
                <td align="right">
                    描述：</td>
                <td align="left">
                    <asp:TextBox ID="txtParaDesc" runat="server" CssClass="put" Width="500" MaxLength="50"></asp:TextBox></td>
            </tr>
           <td align="right">
              &nbsp;
            </td>
            <td align="left">
                <asp:Button ID="btnSubmit" runat="server" Text="保 存" OnClick="On_btnSubmit" CssClass="put" />
                <input name="reback" type="button" value="返回上一页" onclick="javascript:history.back();" class="put"/>
            </td>
            </tr>
        </table>
    </form>
</body>
</html>
