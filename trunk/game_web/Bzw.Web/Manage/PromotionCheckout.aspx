<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_PromotionCheckout" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <script type="text/javascript" src="/Public/Js/public.js"></script>

    <script type="text/javascript" src="/Public/Js/password_check.js"></script>

    <script type="text/javascript" src="/Public/Js/District.js"></script>

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
                    游戏推广结算</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 游戏推广结算</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <div class="cz">
                    <form id="Form1" runat="server" onsubmit="return onFormSubmit(this)">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab03">
                      
                       
                        <tr>
                            <th width="24%" height="35" align="right" scope="row">
                                真实姓名：
                            </th>
                            <td width="76%">
                                <asp:Literal ID="lteTrueName" runat="server"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                用户名：
                            </th>
                            <td>
                                <%=UiCommon.UserLoginInfo.UserName %>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                银行存款：
                            </th>
                            <td>
                                <%=UiCommon.StringConfig.AddZeros(new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID))%>
                                <%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                推广收入：
                            </th>
                            <td>
                                <asp:Literal ID="lteTgMoney" runat="server"></asp:Literal><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                结账<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>：
                            </th>
                            <td>
                                <asp:TextBox ID="txtMoney"   CssClass="input" runat="server"
                                    MaxLength="9"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td height="50" scope="row">
                                &nbsp;
                            </td>
                            <td>
                                <input type="submit" name="button5" id="button5" class="but_011" value="我要结账" onserverclick="button5_ServerClick"
                                    runat="server" />
                            </td>
                        </tr>
                         <tr>
                            <td colspan="2">
                                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                            </td>
                        </tr>
                    </table>
                    </form>

                    <script type="text/javascript">
    <!--
                        function onFormSubmit(f) {

                            var txtMoney = document.getElementById('txtMoney');
                            if (!alertNonNegativeNumber(txtMoney, '结账<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>必须是大于零的数字！')) {
                                return false;
                            } else if (parseInt(txtMoney.value.trim()) <= 0) {
                                alert('结账<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>必须是大于零的数字！');
                                txtMoney.focus();
                                return false;
                            }

                            return true;
                        }
     //-->
                    </script>

                    <br />
                    <br />
                    <strong><b>备注：</b></strong><br />
                    1、只有推广收入大于等于<asp:Literal ID="lteCon_MinClearingMoney" runat="server"></asp:Literal><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>才能结账<br />
                    2、结账方式：把您推广的收入转入到您的银行中<br />
                </div>
                <div class="clear">
                </div>
            </div>
            <!--right End-->
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <!--content End-->
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
