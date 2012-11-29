<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_FlashAd_FlashEdit" Codebehind="FlashEdit.aspx.cs" %>

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
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>修改幻灯片图片</strong></td>
            </tr>
            <tr>
                <td align="right">
                    显示标题：</td>
                <td align="left">
                    <input name="title" type="text" id="title" size="50" value="<%=title %>" maxlength="50"
                        class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    图片地址：</td>
                <td align="left">
      
                         <asp:FileUpload ID="FileUpload1" runat="server" size="50" class ="put"  Style="position: relative" />
                        （图片格式必须为jpg格式）
                        </td>
            </tr>
            <tr>
                <td align="right">
                    链接地址：</td>
                <td align="left">
                    <input name="url" type="text" id="url" size="50" value="<%=url %>" maxlength="50"
                        class="put" /></td>
            </tr>

            <tr>
                <td align="right">
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 " class="put" OnClick="FlashEdits" />
                    <input type="reset" name="Submit2" value="清除重写" class="put" /></td>
            </tr>
        </table>
        <div>
        <%--<img id="Image1"  style="position: relative; display:none " width="520" height="160" src="" />--%>
        <img id="Image2"  style="position: relative" width="520" height="160" src="<%= picture %>" /></div>
    </form>
</body>
</html>
