<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_AlbumWrite" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/public/js/jquery.js"></script>

    <script src="/public/js/public.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <Left:Control ID="leftOne" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    创建相册</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 创建相册</p>
            </div>
            <div id="sub_nr" style="margin-top: 15px;">
                <div class="frie_pro">
                    <a href="Album.aspx" id="current">
                        <img src="/images/fhphoto.gif" width="12" height="12" />
                        返回相册列表</a> &nbsp;&nbsp;| &nbsp;&nbsp;<a href="PicListWrite.aspx"><img src="/images/scphoto.gif"
                            width="12" height="12" />
                            上传相片</a>
                </div>
                <form runat="server" id="form1">
                <table width="90%" border="0" cellspacing="0" cellpadding="0">
                    <tr>
                        <th height="43" colspan="2" scope="row">
                            &nbsp;
                        </th>
                    </tr>
                    <tr>
                        <th width="42%" height="45" align="right" scope="row">
                            相册名称：
                        </th>
                        <td width="58%">
                            <asp:TextBox ID="txtAlbumName" runat="server" CssClass="pro_input" MaxLength="12"></asp:TextBox>
                            <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtAlbumName"
                                Display="Dynamic" ErrorMessage="请填写相册名称"></asp:RequiredFieldValidator>
                        </td>
                    </tr>
                    <tr>
                        <th height="45" align="right" scope="row">
                            浏览权限：
                        </th>
                        <td>
                            <asp:RadioButtonList ID="rdoIsPublic" runat="server" RepeatDirection="Horizontal"
                                RepeatLayout="Flow">
                            </asp:RadioButtonList>
                        </td>
                    </tr>
                    <tr>
                        <th height="74" scope="row">
                            &nbsp;
                        </th>
                        <td>
                            <asp:Button ID="btnSubmit" runat="server" CssClass="but_011" Text="新建相册" OnClick="btnSubmit_Click" />&nbsp;
                            <input type="button" class="but_back" onclick="javascript:history.back();" value="  " />
                        </td>
                    </tr>
                </table>
                </form>
            </div>    <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <div class="clear">
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
