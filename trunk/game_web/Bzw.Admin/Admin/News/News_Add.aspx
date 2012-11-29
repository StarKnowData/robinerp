<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_News_News_Add" Codebehind="News_Add.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
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
<script type="text/javascript" language="javascript">
<!--
function CheckForm() {
  if(document.Login.title.value == '') {
    alert('温馨提示：\n\n新闻标题不能为空！');
    document.Login.title.select();
    return false;
  }  
}

function CheckBrowser() {
  var app=navigator.appName;
  var verStr=navigator.appVersion;
  if(app.indexOf('Netscape') != -1) {
    alert('友情提示：\n    您使用的是Netscape浏览器，可能会导致无法使用后台的部分功能。建议您使用 IE6.0 或以上版本。');
  } else if(app.indexOf('Microsoft') != -1) {
    if (verStr.indexOf('MSIE 3.0')!=-1 || verStr.indexOf('MSIE 4.0') != -1 || verStr.indexOf('MSIE 5.0') != -1 || verStr.indexOf('MSIE 5.1') != -1)
      alert('友情提示：\n    您的浏览器版本太低，可能会导致无法使用后台的部分功能。建议您使用 IE6.0 或以上版本。');
  }
}
//-->
    </script>
    <script src="/Public/Js/jquery2.js"></script>
    <script src="/Public/Js/ColorPicker.js"></script>
</head>
<body>
    <form method="POST" name='Login' id="Login" action="" runat="server" onSubmit='return CheckForm();'>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <b>添加新闻页面</b></td>
            </tr>
            <tr>
                <td  align="right">
                    新闻标题：</td>
                <td  align="left">
                    <input name="title" type="text" id="title" size="50" maxlength="50" class="put" />&nbsp;<span style="background:#000;"><img src="/Images/System/colorpicker.gif" width="21" height="18" onclick="$(this).colorPicker({ setColor:'input[@id=title]',setValue:$('#hidTitleColor') })" align="absmiddle" alt="设置标题颜色" /></span>
					<asp:HiddenField ID="hidTitleColor" runat="server" />
                    <asp:TextBox ID="picture" runat="server" Width="0" Height="0" style="visibility:hidden;"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td align="right">
                    新闻类别：</td>
                <td align="left">
                    <asp:DropDownList ID="news_type" runat="server">
                    </asp:DropDownList>
                    
                    <a href="NewsTypeAdd.aspx">添加新闻分类</a>
                </td>
            </tr>
            <tr>
                <td align="right">
                    关键字：</td>
                <td align="left">
                    <input name="keywords" type="text" id="keywords" size="50" maxlength="50" class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    资讯出处：</td>
                <td align="left">
                    <input name="news_from" type="text" id="news_from" size="20" maxlength="20" class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    作者：</td>
                <td align="left">
                    <input name="author" type="text" id="author" size="20" maxlength="20" class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    发布人：</td>
                <td align="left">
                    <input name="issuer" type="text" id="issuer" size="20" maxlength="20" class="put" /></td>
            </tr>
            <tr>
                <td align="right" valign="top">
                    新闻内容：</td>
                <td align="left">
                    <FCKeditorV2:FCKeditor ID="content" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/">
                    </FCKeditorV2:FCKeditor>
                </td>
            </tr>
           
            <tr style="display:none;">
                <td align="right">
                    上传图片：</td>
                <td align="left">
					<asp:FileUpload runat="server" ID="fuImage" />(300K以内，允许的类型：jpg,jpeg,gif)
                 <%--<iframe src='../Inc/Nupload.inc.aspx' frameborder='0' style='height:25px;width:100%;' scrolling='no'></iframe> --%>
                </td>
            </tr>
            <tr style="display:none">
                <td align="right">
                    是否通过：</td>
                <td align="left">
                    <input name="through" type="radio" value="1" checked="checked" class="put"/>
                    是
                    <input type="radio" name="through" value="0" class="put"/>
                    否</td>
            </tr>
            <tr>
                <td align="right">
                    是否推荐：</td>
                <td align="left">
                    <input type="radio" name="recommendation" value="1" class="put"/>
                    是
                    <input name="recommendation" type="radio" value="0" checked="checked" class="put" />
                    否</td>
            </tr>
            <tr>
                <td align="right">
                    是否置顶：</td>
                <td align="left">
                    <input type="radio" name="Istop" value="1" class="put" />
                    是
                    <input name="Istop" type="radio" value="0" checked="checked" class="put"/>
                    否</td>
            </tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 提 交 " OnClick="NewsAd" class="put" />
                    <input type="reset" name="Submit2" value=" 清 除 " class="put"/>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
