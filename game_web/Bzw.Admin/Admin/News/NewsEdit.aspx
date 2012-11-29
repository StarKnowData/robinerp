<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_News_NewsEdit" Codebehind="NewsEdit.aspx.cs" %>

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
    <script src="/Public/Js/jquery2.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js"></script>
    <script src="/Public/Js/ColorPicker.js"></script>
</head>
<body>
    <form method="POST" name='Login' id="Login" action="" runat="server" onSubmit='return CheckForm();'>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <b>修改新闻页面</b></td>
            </tr>
            <tr>
                <td  align="right">新闻标题：</td>
                <td width="643" align="left">
                    <input name="title" type="text" id="title" size="50" maxlength="50" class="put" value="<%=title %>" />&nbsp;<span id="spcol"><img src="/Images/System/colorpicker.gif" width="21" height="18" onclick="$(this).colorPicker({ setColor:'input[@id=title]',setValue:$('#hidTitleColor') })" align="absmiddle" alt="设置标题颜色" /></span>
					<asp:HiddenField ID="hidTitleColor" runat="server" />
                    
                    <script>
                        $(document).ready(
							function() {

							    if ($("#hidTitleColor").val().toLowerCase() != "black" && $("#hidTitleColor").val().toLowerCase() != "") {
							        $("#title").css("color", $("#hidTitleColor").val());
							        $("#spcol").css("background", $("#hidTitleColor").val());
							    }
							}
						);
						 $("#spcol").css("background","black");
                    </script>
                </td>
            </tr>
            <tr>
                <td align="right">新闻类别：</td>
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
                    <input name="keywords" type="text" id="keywords" size="50" maxlength="50" class="put"  value="<%=keywords %>"/></td>
            </tr>
            <tr>
                <td align="right">
                    资讯出处：</td>
                <td align="left">
                    <input name="news_from" type="text" id="news_from" size="20" maxlength="20" class="put" value="<%=news_from %>"/></td>
            </tr>
            <tr>
                <td align="right">
                    作者：</td>
                <td align="left">
                    <input name="author" type="text" id="author" size="20" maxlength="20" class="put" value="<%=author %>"/></td>
            </tr>
            <tr>
                <td align="right">
                    发布人：</td>
                <td align="left">
                    <input name="issuer" type="text" id="issuer" size="20" maxlength="20" class="put" value="<%=issuer %>"/></td>
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
					<asp:PlaceHolder runat="server" ID="phImageUrl">
						<asp:TextBox runat="server" ID="txtImageUrl" CssClass="put"></asp:TextBox>&nbsp;
						<input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageUrl.Text.Trim() %>',0,0);" />&nbsp;
						<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />
					</asp:PlaceHolder>
					<asp:PlaceHolder runat="server" ID="phFileImage">
						<asp:FileUpload runat="server" ID="fuImage" />(300K以内，允许的类型：jpg,jpeg,gif)
					</asp:PlaceHolder>
                 <%--<iframe src='../Inc/Nupload.inc.aspx' frameborder='0' style='height:25px;width:100%;' scrolling='no'></iframe> --%>
                </td>
            </tr>
            <tr style="display:none">
                <td align="right">
                    是否通过：</td>
                <td align="left">
                    <input name="through" type="radio" value="1" <%= (through.ToString().ToLower()=="true" ? "CHECKED" : "") %>  class="put"/>
                    是
                    <input type="radio" name="through" value="0" <%= (through.ToString().ToLower()=="false" ? "CHECKED" : "") %> class="put"/>
                    否</td>
            </tr>
            <tr>
                <td align="right">
                    是否推荐：</td>
                <td align="left">
                    <input type="radio" name="recommendation" value="1"  <%= (recommendation.ToString().ToLower()=="true" ? "CHECKED" : "") %> class="put"/>
                    是
                    <input name="recommendation" type="radio" value="0"  <%= (recommendation.ToString().ToLower()=="false" ? "CHECKED" : "") %> class="put"/>
                    否</td>
            </tr>
            <tr>
                <td align="right">
                    是否置顶：</td>
                <td align="left">
                    <input type="radio" name="Istop" value="1" <%= (Istop.ToString().ToLower()=="true" ? "CHECKED" : "") %> class="put"/>
                    是
                    <input name="Istop" type="radio" value="0" <%= (Istop.ToString().ToLower()=="false" ? "CHECKED" : "") %> class="put"/>
                    否</td>
            </tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 " OnClick="NewsEd" class="put"/>
                    <input type="button" name="Submit2" value=" 返 回 " class="put" onclick="javascript:history.back();"/>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
