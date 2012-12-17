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
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

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
              
                    <li>
                        <div style="padding-right: 14px;  " class="fl"><img src="/Images/taobao.jpg" width="110" height="100" alt="淘宝充值"/></div>
                        <strong class="text05">淘宝官网充值</strong><br />
                        由八棋赢官方开通的官方淘宝充值
                        <p style="padding-top: 15px; ">
                            <a href="http://shop100262618.taobao.com/shop/view_shop.htm?tracelog=twddp">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <li>
                        <div style="padding-right: 14px;  " class="fl">
                            <img src="/Images/dianhua.jpg" width="110" height="100"/></div>
                        <strong class="text05">易宝固话短信充值</strong><br />
                        固话或短信购买易宝一卡通，在线进行支付和充值
                        <p style="padding-top: 15px; ">
                            <a href="/Manage/Pay/Yeepay/NotePay.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <li>
                        <div style="padding-right: 14px;  " class="fl">
                            <img src="/Images/pay_06.jpg" width="110" height="100"/></div>
                        <strong class="text05">联通充值卡</strong><br />
                        联通用户，用联通充值卡面额进行充值
                        <p style="padding-top: 15px; ">
                            <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=UNICOM-NET">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>
                    <li>
                        <div style="padding-right: 14px;  " class="fl"><img src="/Images/pay_05.jpg" width="110" height="100"/></div>
                        <strong class="text05">神州行充值卡</strong><br />
                        仅限移动用户，用神州行充值卡面额进行充值<br />
                        
                        <p style="padding-top: 15px; ">
                            <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=SZX-NET">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>

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
                    <%}%>
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
