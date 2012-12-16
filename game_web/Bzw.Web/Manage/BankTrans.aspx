<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_BankTrans" %>

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
<script type="text/javascript" src="/Public/Js/jquery.js"></script>
<script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

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
                    用户转账</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 用户转账</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <form id="Form1" runat="server" onsubmit="return onFormSubmit(this)" class="democss">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0">
                     
                        <tr>
                            <th width="24%" height="35" align="right" scope="row">
                                游戏帐号：
                            </th>
                            <td width="76%">
                                <%=UiCommon.UserLoginInfo.UserName %>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                银行存款：
                            </th>
                            <td>
                                <%=UiCommon.StringConfig.AddZeros( new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID)) %>
                                <%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                钱包余款：
                            </th>
                            <td>
                                <%= UiCommon.StringConfig.AddZeros(new BLL.Member().GetWalletMoney(UiCommon.UserLoginInfo.UserID))%>
                                <%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                银行密码：
                            </th>
                            <td>
                                <asp:TextBox ID="txtPassword" runat="server" CssClass="pro_input" TextMode="password"
                                    MaxLength="20"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                转入帐号：
                            </th>
                            <td>
                                <asp:TextBox ID="txtInputUserName" runat="server" CssClass="pro_input" MaxLength="20"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                确定转入帐号：
                            </th>
                            <td>
                                <asp:TextBox ID="txtInputUserName2" runat="server" CssClass="pro_input" MaxLength="20"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                转账金额：
                            </th>
                            <td>
                                <asp:TextBox ID="txtMoney" runat="server" CssClass="pro_input" MaxLength="18"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="50" scope="row">
                                &nbsp;
                            </th>
                            <td>
                                <input class="but_011" type="submit" name="button5" id="button5" value="确认转账" onserverclick="button5_ServerClick"
                                    runat="server" /><input class="but_022" type="button" name="button5" id="Submit1"
                                        value="清空重写" onclick="ClearInfo()" />
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

                        function ClearInfo() {
                            document.getElementById('txtPassword').value = '';
                            document.getElementById('txtInputUserName').value = '';
                            document.getElementById('txtInputUserName2').value = '';
                            document.getElementById('txtMoney').value = '';
                        }

                        function onFormSubmit(f) {

                            //登录密码----------
                            var password = document.getElementById('txtPassword');
                            if (!alertNull(password, '请输入银行密码！')) {
                                return false;
                            }

                            //转入帐号-----------
                            var txtInputUserName = document.getElementById('txtInputUserName');
                            var txtInputUserName2 = document.getElementById('txtInputUserName2');
                            if (!alertNull(txtInputUserName, '请输入转入帐号！（对方在游戏或网站中登录的用户名）')) {
                                return false;
                            }

                            if (txtInputUserName.value.trim() != txtInputUserName2.value.trim()) {
                                alert('两次输入转入帐号不一致！');
                                txtInputUserName2.focus();
                                return false;
                            }

                            //转账金额----------
                            var txtMoney = document.getElementById('txtMoney');
                            if (!alertNonNegativeNumber(txtMoney, '转账金额必须是大于零，并且小于2100亿的数字！')) {
                                return false;
                            } else if (parseInt(txtMoney.value.trim()) <= 0 || parseInt(txtMoney.value.trim()) >= 210000000000) {
                                alert('转账金额必须是大于零，并且小于2100亿的数字！');
                                txtMoney.focus();
                                return false;
                            }

                            return true;
                        }
 //-->
                    </script>

                    <br />
                    <br />
                    <strong><b>转账条件：</b></strong><br />
                    1、您的账户余款（银行存款+钱包余款）必须大于<%=UiCommon.StringConfig.AddZeros(TransferLessAllMoney)%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%><br />
                    2、转账的金额必须是<%=TransferMultiple%>的倍数，而且单笔转账不得少于<%=UiCommon.StringConfig.AddZeros(TransferLessMoney) %><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>。<br />
                    <b>注意：</b><br />
                    请一定要正确的填写转入帐号，转账是从银行存款中转出，如果银行存款不够，请到先到游戏中把钱包余款存入银行账户中，再来转账。 普通用户转账需要扣除万分之<%=TransferTax%>的手续费，VIP用户转账需要扣除万分之<%=VipTransferTax %>的手续费，但单笔转账最高扣出的手续费为<%=UiCommon.StringConfig.AddZeros(MaxTransTax)%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>，这笔费用将从转账的金额中扣出。
                </div>
            </div><p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
