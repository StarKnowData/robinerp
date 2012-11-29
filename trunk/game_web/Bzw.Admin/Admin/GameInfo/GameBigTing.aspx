<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_GameInfo_GameBigTing" Codebehind="GameBigTing.aspx.cs" %>

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
        
                <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
                    bgcolor="F2F8FF" class="admin_table">
                    <asp:Repeater ID="GameBig" runat="server">
            <ItemTemplate>
                    <tr>
                        <td class="title_03" colspan="2">
                            <strong>游戏大厅信息管理</strong></td>
                    </tr>
                    <tr>
                        <td width="20%" align="right">
                            版本号：</td>
                        <td width="80%" align="left">
                            <input name="Main_copy" type="text" id="Main_copy" value="<%# Eval("main_copy") %>" size="50" maxlength="50"
                                class="put" /></td>
                    </tr>
                    <tr>
                        <td align="right">
                            应用平台：</td>
                        <td align="left">
                            <input name="Main_use" type="text" id="Main_use" value="<%# Eval("main_use") %>" size="50"
                                maxlength="100" class="put" /></td>
                    </tr>
                     <tr>
                        <td align="right">
                            简洁版下载地址：</td>
                        <td align="left">
                            <input name="Down_saddress" type="text" id="Down_saddress" value="<%# Eval("down_saddress") %>"
                                size="50" maxlength="100" class="put" /></td>
                    </tr>
                    <tr>
                        <td align="right">
                            完整版下载地址：</td>
                        <td align="left">
                            <input name="Down_address" type="text" id="Down_address" value="<%# Eval("down_address") %>"
                                size="50" maxlength="100" class="put" /></td>
                    </tr>
                    <tr style="display:none"> 
                        <td align="right">
                            下载次数：</td>
                        <td align="left">
                            <input name="Down_num" type="text" id="Down_num" value="<%# Eval("down_num") %>" size="50" maxlength="50"
                                class="put" />（必须输入一个数字!）</td>
                    </tr>
                    <tr>
                        <td align="right">
                            文件大小：</td>
                        <td align="left">
                            <input name="FileSize" type="text" id="FileSize" value="<%# Eval("filesize") %>" size="50" maxlength="9"
                                class="put" />（单位为KB,请不要加单位）</td>
                    </tr>
                    <tr>
                        <td align="right">
                            图片地址：</td>
                        <td align="left">
                            <input name="Image_URL" type="text" id="Image_URL" value="<%# Eval("image_url") %>" size="50"
                                maxlength="50" class="put" /></td>
                    </tr>
                    <tr>
                        <td align="right" valign="top">
                            大厅介绍：</td>
                        <td align="left">
                            <textarea name="Main_info" cols="50" rows="10" id="Main_info" class="put"><%# Eval("main_info") %></textarea>
                            限500字符</td>
                    </tr> 
                    </ItemTemplate>
        </asp:Repeater>
                    <tr>
                        <td>
                            &nbsp;</td>
                        <td align="left">
                            <asp:Button ID="Button1" runat="server" Text="修改信息"  class="put" OnClick="GameBigEdit"/>
                            <input type="hidden" name="action" value="edit" /></td>
                    </tr>
                </table>
           
    </form>
</body>
</html>
