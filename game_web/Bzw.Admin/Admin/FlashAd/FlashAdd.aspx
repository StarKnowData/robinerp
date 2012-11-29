<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_FlashAd_FlashAdd" Codebehind="FlashAdd.aspx.cs" %>

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
                    <strong>添加幻灯片</strong></td>
            </tr>
            <tr>
                <td align="right">
                    显示标题：</td>
                <td align="left">
                    <input name="title" type="text" id="title" size="50" value="" maxlength="50" class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    图片地址：</td>
                <td align="left">
                    <%--<input name="picture" type="text" id="picture" value="" size="50" maxlength="50"
                        class="put" />--%>
                         <!--图片上传预览start-->
<%--
                        <script language="javascript" type="text/javascript">
                        function PreviewImg(imgFile)
                        {    
                             var newPreview = document.getElementById("Image1");
                             alert(imgFile.value);
                             newPreview.src = imgFile.value;
                             newPreview.style.width = "477px";
                             newPreview.style.height = "196px";
                         }
                        </script>
--%>
                        <!--预览end-->
                        <asp:FileUpload ID="FileUpload1" size="50" class ="put" runat="server"/>
                         （图片格式必须为jpg格式,图片规格：477*224）
                        </td>
            </tr>
            <tr>
                <td align="right">
                    链接地址：</td>
                <td align="left">
                    <input name="url" type="text" id="url" size="50" value="" maxlength="50" class="put" />
                    填写网站目录下的相对地址</td>
            </tr>


            <tr>
                <td align="right">
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="填好提交" class="put"   OnClick="FlashAdds"/>
                    <input type="reset" name="Submit2" value="清除重写" class="put"/></td>
            </tr>
        </table>
       <%-- <div > <img id="Image1" src ="" /></div>--%>
    </form>
</body>
</html>
