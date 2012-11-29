<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Books_BookInfo" Codebehind="BookInfo.aspx.cs" %>

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
    <asp:Repeater ID="BookInfos" runat="server">
        <ItemTemplate>
            <table width="100%"  border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
                bgcolor="F2F8FF" class="admin_table" style=" table-layout:fixed;word-wrap:break-word; overflow:hidden;">
                <tr>
                    <td width="10%" align="right">
                        标题：</td>
                    <td width="90%" align="left">
                        <%# Eval("MsgTitle") %>
                        （<font color="red"><%# Eval("MsgTime") %></font>）</td>
                </tr>
                <tr>
                    <td align="right">
                        内容：</td>
                    <td align="left">
                        <p>
                            <span style="color: #ff0000;"><strong>
                                <%# Eval("MsgName") %>
                            </strong></span>&nbsp; 在留言中说：
                            <br />
                            <br>
                            <%# Eval("MsgText") %>
                            <br />
                        </p>
                        <div style="border: 1px solid #aaaaaa; background: #f4f4f4; padding: 5px; width:90%;word-wrap:break-word;">
                            <%# Eval("MsgReply") %>
                            <br />
                            <br>
                            回复时间：
                            <%# Eval("MsgReplyTime") %>
                        </div>
                    </td>
                </tr>
            </table>
        </ItemTemplate>
    </asp:Repeater>
    <form id="form1" runat="server">
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="17%" align="right">
                    是否通过审核：</td>
                <td width="83%" align="left">
                    <input name="inp" type="radio" value="1" class="put" <%=IsPass.ToString().ToLower()=="true"  ? "checked" : "" %>/>是
                    <input name="inp" type="radio" value="0" class="put" <%=IsPass.ToString().ToLower() =="false"  ? "checked" : ""  %>/>否
                </td>
            </tr>
    </table>
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td width="16%">
                    &nbsp;</td>
                <td width="84%">
                    <textarea cols="50" rows="5" name="Reply" class="put"></textarea>
                 （此项为空即不回复   ）
                 </td>
            </tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td>
                    <asp:Button ID="Button1" runat="server" Text="修改审核回复留言" OnClick="HFBook" class="put" />
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
