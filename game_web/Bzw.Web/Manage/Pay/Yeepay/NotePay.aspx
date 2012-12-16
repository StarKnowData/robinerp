<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay.Yeepay.Manage_Pay_Yeepay_NotePay" %>

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
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/Public/Js/public.js" type="text/javascript"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="4" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    易宝固话短信充值</h3>
                <p class="dqwz">
                    当前位置：首页 > 账户充值</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <h6>
                        您选择了易宝固话短信充值方式</h6>
                    <form id="Form1" action="" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab03">
                        <tr>
                            <td valign="middle" colspan="2" align="center">
                               <%-- <iframe src="http://www.52yxly.com/ypcard/buydesc.html" frameborder="0" scrolling="no"
                                    width="585" height="410"></iframe>--%>
                            </td>
                        </tr>
                        <tr>
                            <td valign="middle" colspan="2" align="center">
                                已拥有易宝一卡通卡密，填写下面的表单立即充值：
                            </td>
                        </tr>
                        <tr>
                            <th width="35%" height="30" align="right" scope="row">
                                游戏帐号(用户名)：
                            </th>
                            <td width="65%" valign="middle">
                                <asp:TextBox ID="txtUserName" runat="server" MaxLength="20" CssClass="input"></asp:TextBox>
                                *
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                确认帐号：
                            </th>
                            <td valign="middle">
                                <asp:TextBox ID="txtUserName2" runat="server" MaxLength="20" CssClass="input"></asp:TextBox>
                                *
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                金额：
                            </th>
                            <td valign="middle">
                                <asp:DropDownList ID="PayMoney" runat="server">
                                    <asp:ListItem Value="2">2元</asp:ListItem>
                                    <asp:ListItem Value="5">5元</asp:ListItem>
                                    <asp:ListItem Value="10" Selected="true">10元
                                    </asp:ListItem>
                                    <asp:ListItem Value="15">15元</asp:ListItem>
                                    <asp:ListItem Value="20">20元</asp:ListItem>
                                    <asp:ListItem Value="25">25元</asp:ListItem>
                                    <asp:ListItem Value="30">30元</asp:ListItem>
                                    <asp:ListItem Value="50">50元</asp:ListItem>
                                    <asp:ListItem Value="100">100元</asp:ListItem>
                                </asp:DropDownList>
                            </td>
                        </tr>
                        <tr>
                            <th height="65" scope="row">
                                &nbsp;
                            </th>
                            <td>
                                <%--<input type="submit" name="button2" id="button2" value="提交" class="submit" />
									<input type="submit" name="button2" id="Submit1" value="重填" class="reset" />--%>
                                <input type="submit" name="imageField2" id="Button1" class="but_01" value="  "
                                    onserverclick="Button1_Click" runat="server" />
                                <input type="button" name="button5" id="Button2"  class="but_02" value="  "  onclick="ClearInfo()" />
                            </td>
                        </tr>
                    </table>
                    </form>
                    <div id="warning">
                        请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。</div>
                    <div class="clear">
                    </div>
                </div>
            </div><p><img src="/Images/cont_img01.jpg" alt="" /></p>
          
        </div>
        <!--right End-->
    </div>
    <!--content End-->
   <div class="clear">
            </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />

    <script type="text/javascript">
<!--
        function ClearInfo() {
            document.getElementById('txtUserName').value = '';
            document.getElementById('txtUserName2').value = '';
        }


        function onFormSubmit(f) {

            var txtUserName = document.getElementById('txtUserName');
            var txtUserName2 = document.getElementById('txtUserName2');
            if (!alertNull(txtUserName, '请输入游戏帐号！（用户名）')) {
                return false;
            }

            var urlData = '/Public/XmlHttpUser.aspx?type=nameexist&username=' + escape(txtUserName.value.trim());
            //alert(urlData);
            var strReturn = AjaxCall(urlData);
            //alert(strReturn);
            if (strReturn == "0") {
                alert('对不起，您输入的游戏帐号！（用户名）不存在。');
                txtUserName.focus();
                return false;
            }
            //strReturn=="1" 存在

            if (txtUserName.value.trim() != txtUserName2.value.trim()) {
                alert('两次输入游戏帐号不一致！');
                txtUserName2.focus();
                return false;
            }

            var pmsg = '金额请输入大于零的整数！';
            var PayMoney = document.getElementById('PayMoney');
            if (!alertNonNegativeNumber(PayMoney, pmsg)) {
                return false;
            } else if (parseInt(PayMoney.value.trim()) <= 0) {
                alert(pmsg);
                PayMoney.focus();
                return false;
            }

            return true;
        }
 //-->
    </script>

</body>
</html>
