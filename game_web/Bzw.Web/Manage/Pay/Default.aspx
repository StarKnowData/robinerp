<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay.Manage_Pay_Default" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

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
                    账户充值</h3>
                <p class="dqwz">
                    当前位置：首页 > 账户充值</p>
            </div>
            <div id="sub_nr">
                <ul class="zhcz">
                    <li>
                        <div style="padding-right: 14px;  " class="fl">
                            <img src="/Images/cont_tbl_img20.jpg" alt="" /></div>
                        <strong class="text05">点卡充值</strong><br />
                        使用点卡充值卡，在官网上进行<br />
                        充值。
                        <p style="padding-top: 15px; ">
                            <a href="/Manage/Pay/PointCard.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <%  if (UiCommon.StringConfig.IPS_Mer_code != "")
                        { %>
                    <li>
                        <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/cont_tbl_img21.jpg" alt="" /></div>
                        <strong class="text05">环迅在线充值</strong><br />
                        支持工商、招商、农业、建设、中<br />
                        国银行等国内27家银行及信用卡。
                        <p style="padding-top: 15px;">
                            <a href="/Manage/Pay/IPS/Default.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <%} %>
                    <%  if (UiCommon.StringConfig.YeepayMerID != "")
                        { %>
                    <li>
                        <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/pay/pay_01.jpg" alt="" width="106px" height="84px" /></div>
                        <strong class="text05">易宝在线支付</strong><br />
                        支持工商、招商、农业、建设、等<br />
                        国内27家银行和信用卡，游戏点卡
                        <p style="padding-top: 15px;">
                            <a href="/Manage/Pay/Yeepay/Default.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <%} if (UiCommon.StringConfig.BaofooMerchantID != "")
                        { %>
                    <li>
                        <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/pay/pay_01.jpg" alt="" width="106px" height="84px" /></div>
                        <strong class="text05">宝付在线支付</strong><br />
                        支持工商、招商、农业、建设、等<br />
                        国内27家银行和信用卡，游戏点卡
                        <p style="padding-top: 15px;">
                            <a href="/Manage/Pay/Baofoo/Default.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <%} if (UiCommon.StringConfig.AlipayPartnerID != "")
                        { %>
                    <li>
                        <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/pay/zfb.jpg" alt="" width="106px" height="84px" /></div>
                        <strong class="text05">支付宝在线支付</strong><br />
                        支持工商、招商、农业、建设、等<br />
                        国内27家银行和信用卡
                        <p style="padding-top: 15px;">
                            <a href="/Manage/Pay/AliPay/Default.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <%} if (UiCommon.StringConfig.JFTpay_MemberID != "")
                        { %>
                    <li>
                        <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/pay/pay_01.jpg" alt="" width="106px" height="84px" /></div>
                        <strong class="text05">聚付通在线支付</strong><br />
                        支持工商、招商、农业、建设等<br />
                        国内20家银行卡充值
                        <p style="padding-top: 15px;">
                            <a href="/Manage/Pay/JFTpay/Default.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <%} %>
                </ul>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <!--right End-->
    </div>
    <!--content End-->
    <div class="clear">
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
