<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_GameADEdit" Codebehind="GameADEdit.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
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

    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <script src="/Public/Js/ColorPicker.js"></script>
</head>
<body>
    <form method="POST" name='Login' id="Login" action="" runat="server" >
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <b>修改广告内容页面</b></td>
            </tr>
            <tr>
                <td  align="right">广告标题：</td>
                <td  align="left">
                   <%=title %>

                </td>
            </tr>

       
            <tr>
                <td align="right" valign="top">
                    广告内容：</td>
                <td align="left">
                    <FCKeditorV2:FCKeditor ID="content" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/" ToolbarSet="GameAdBasic">
                    </FCKeditorV2:FCKeditor>
                </td>
            </tr>
           
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 " OnClick="GameADEd" class="put"/>
                    <input type="button" name="Submit2" value=" 返 回 " class="put" onclick="javascript:history.back();"/>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
