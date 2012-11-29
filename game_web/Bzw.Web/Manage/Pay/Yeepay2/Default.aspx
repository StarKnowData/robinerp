<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay.Yeepay2.Manage_Pay_Yeepay2_Default" %>

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

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

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
                    在线充值</h3>
                <p class="dqwz">
                    当前位置：首页 > 充值</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <ul class="zhcz">
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/Images/cont_tbl_img20.jpg" alt="" /></div>
                            <strong class="text05">点卡充值</strong><br />
                            使用点卡充值卡，在官网上进行<br />
                            充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/PointCard.aspx">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <%if (UiCommon.StringConfig.YeepayMerID != "")
                          { %>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/Pay/pay_01.jpg" alt="" width="106px" height="84px" /></div>
                            <strong class="text05">银行卡充值</strong><br />
                            使用点卡充值卡，在官网上进行<br />
                            充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=Bank">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/Images/pay/pay_05.jpg" alt="" width="106px" height="84px" /></div>
                            <strong class="text05">神州行充值卡充值</strong><br />
                            仅限移动用户，用神州行充值<br />
                            卡面额进行充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=SZX-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/Images/pay/czk.jpg" alt="" width="106px" height="84px" /></div>
                            <strong class="text05">联通卡充值</strong><br />
                            用联通卡充值卡面额进行充值。<br />
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=UNICOM-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/pay/zt.jpg" alt="征途游戏卡充值" width="106px" height="84px" /></div>
                            <strong class="text05">征途游戏卡充值</strong><br />
                            用征途游戏卡充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=ZHENGTU-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/pay/sd.jpg" alt="盛大游戏卡充值" width="106px" height="84px" /></div>
                            <strong class="text05">盛大游戏卡充值</strong><br />
                            盛大游戏卡充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=SNDACARD-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/pay/qq.jpg" alt="Q币支付充值" width="106px" height="84px" /></div>
                            <strong class="text05">Q币支付充值</strong><br />
                            Q币支付充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=QQCARD-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/Pay/jw.jpg" alt="全国骏网一卡通充值" width="106px" height="84px" /></div>
                            <strong class="text05">全国骏网一卡通充值</strong><br />
                            全国骏网一卡通充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=JUNNET-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/Pay/ybykt.jpg" alt="易宝一卡通充值" width="106px" height="84px" /></div>
                            <strong class="text05">易宝一卡通充值</strong><br />
                            易宝一卡通充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=YPCARD-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <%} %>
                    </ul>
                </div>
                <div class="clear">
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>    <!--right End-->
    </div>

    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
