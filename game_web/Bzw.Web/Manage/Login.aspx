<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_Login" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript">
        function onFormSubmit(f) {
            if (!alertNull(f.txtAccount, '请输入用户名！')) {
                return false;
            }

            if (!alertNull(f.txtPwd, '请输入登录密码！')) {
                return false;
            }

            var txtValidCode = document.getElementById('txtValidCode');
            if (!alertNull(txtValidCode, '请输入验证码！')) {
                return false;
            }

            return true;
        }
    </script>

</head>
<body>
    <form id="form1" runat="server" onsubmit="return onFormSubmit(this);">
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
            
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    用户登录</h3>
                <p class="dqwz">
                    当前位置：首页 > 用户登录</p>
            </div>
            <div id="sub_nr">
                <div id="login01">
                    <ul>
                        <li>
                            <img src="/Images/id02.jpg" alt="" />
                            <asp:TextBox ID="txtAccount" runat="server" CssClass="in"></asp:TextBox>
                        </li>
                        <li>
                            <img src="/Images/pw01.jpg" alt="" />
                            <asp:TextBox ID="txtPwd" runat="server" TextMode="Password" CssClass="in"></asp:TextBox>
                        </li>
                        <li>
                            <img src="/Images/yzm01.jpg" alt="" />
                            <asp:TextBox ID="txtValidCode" runat="server" Width="41px" MaxLength="4" CssClass="in"></asp:TextBox>&nbsp;<img
                                src="/Public/Getcode.aspx" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
                                alt="点击换一张图片" style="  cursor: pointer; width: 50px;
                                height: 17px ; line-height:17px;" />
                        </li>
                        
                    </ul>
                    <p>
                    <asp:Button  ID="imageField" runat="server"  OnClick="btnSubmit_Click"  Text=" " CssClass="but_Reg"  />
                        
                    </p>
                    <p class="login_btn01">
                        <a href="/Manage/Reg.aspx">
                            <img src="/Images/cont_btn13.jpg" alt="" /></a><a href="/Manage/GetPass.aspx"><img
                                src="/Images/cont_btn14.jpg" alt="" /></a></p>
                                <p style=" text-align:center; width:300px;"><asp:Label ID="lbMsg" ForeColor="red" runat="server"></asp:Label></p>
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--right End-->
    </div><!--content End-->
     
    <!--footer-->
    <WebFooter:Control ID="webfooter1" runat="server" />
    </form>
</body>
</html>
