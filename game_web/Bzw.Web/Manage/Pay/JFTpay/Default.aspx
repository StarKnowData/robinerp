<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="Bzw.Inhersits.Manage_Pay_JFTpay_Default" %>

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
    <link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
    <style type="text/css">
        .tbradio input
        {
            border: 0;
            vertical-align: middle;
        }
        .fr_input02
        {
            height: 18px;
            padding: 1px;
        }
    </style>
</head>
<body>
    <div id="wrap">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="4" />
        <!--content-->
        <div id="content">
            <div id="left1">
                <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
                <WebService:Control ID="webservice1" runat="server" />
            </div>
            <div id="right">
                <div class="right_con_title">
                    <span>当前位置：<a href="/Default.aspx" title="首页">首页</a> > <a href="/Manage/Pay/Default.aspx"
                        title="充值">充值</a> > <a href="/Manage/Pay/JFTpay/Default.aspx" title="聚付通支付">聚付通支付</a></span>
                    <h1>
                        <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>聚付通在线支付</h1>
                </div>
                <div class="rightbox">
                    <div class="prize_detail">
                        <h6>
                            您选择了聚付通支付方式</h6>
                        <form id="form1" action="Send.aspx" class="democss" method="post" onsubmit="return onFormSubmit(this)">
                        <input type="hidden" name="Type" value="bank" />
                        <script type="text/javascript">
	
    	function CalculationMoney() {
			    var couponNum;
				KeyPressNum(this,$("#PayMoney").val());
				
				if(isNaN($("#PayMoney").val())){
                    $("#CouponNum").val("0");
					return false;
				}else{
                    couponNum=parseInt($("#PayMoney").val()*<%= CouponRate %>);
                    if(couponNum<0)
                    {
                        couponNum=0;
                    }
                    $("#CouponNum").val(couponNum);
				}	
			}

        function ChoosePayment()
        {
            if(document.getElementById("bank").checked)
            {
                document.getElementById("selbank").style.display="";
                document.getElementById("selcard").style.display="none";
                document.getElementById("selcardno").style.display="none";
                document.getElementById("selcardpass").style.display="none";
                document.getElementById("diankatishi").style.display="none";
            }
            else
            {
                document.getElementById("selbank").style.display="none";
                document.getElementById("selcard").style.display="";
                document.getElementById("selcardno").style.display="";
                document.getElementById("selcardpass").style.display="";
                document.getElementById("diankatishi").style.display="";
            }
        } 

	
                        </script>
                        <table width="99%" border="0" cellpadding="0" cellspacing="0" class="democss">
                            <tr id="Tr4">
                                <td width="29%" height="10">
                                </td>
                                <td width="71%">
                                </td>
                            </tr>
                            <tr>
                                <th width="29%" height="40" scope="row">
                                    <span class="red">*</span>选择充值方式：
                                </th>
                                <td width="71%">
                                    <table width="100%" border="0" class="tbradio">
                                        <tr>
                                            <td>
                                                <label>
                                                    <input type="radio" name="pay_type" value="1" id="bank" checked="checked" onclick="ChoosePayment();" />&nbsp;银行充值</label>
                                                &nbsp;
                                                <label>
                                                    <input type="radio" name="pay_type" value="2" id="gamecard" onclick="ChoosePayment();" />&nbsp;游戏点卡充值</label>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                            </tr>
                            <tr id="selbank">
                                <th width="29%" height="30" scope="row">
                                    <span class="red">*</span>选择充值银行：
                                </th>
                                <td width="71%">
                                    <table width="100%" border="0" cellspacing="0" cellpadiving="0" class="tbradio">
                                        <tr id="tr1">
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="967" checked="checked" />&nbsp;工商银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="964" />&nbsp;农业银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="970" />&nbsp;招商银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="965" />&nbsp;建设银行</label>
                                            </td>
                                        </tr>
                                        <tr id="tr2">
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="981" />&nbsp;交通银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="980" />&nbsp;民生银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="974" />&nbsp;深圳发展银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="963" />&nbsp;中国银行</label>
                                            </td>
                                        </tr>
                                        <tr id="tr3">
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="962" />&nbsp;中信银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="972" />&nbsp;兴业银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="977" />&nbsp;浦发银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="986" />&nbsp;光大银行</label>
                                            </td>
                                        </tr>
                                        <tr id="tr4">
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="989" />&nbsp;北京银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="988" />&nbsp;渤海银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="985" />&nbsp;广东发展银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="984" />&nbsp;广州市农信社</label>
                                            </td>
                                        </tr>
                                        <tr id="tr5">
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="984" />&nbsp;广州市商业银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="976" />&nbsp;上海农商银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="979" />&nbsp;南京银行</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="rtype" value="982" />&nbsp;华夏银行</label>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                            </tr>
                            <tr id="selcard" style="display: none;">
                                <th width="29%" height="30" scope="row">
                                    <span class="red">*</span>选择点卡类型：
                                </th>
                                <td width="71%">
                                    <table width="100%" border="0" cellspacing="0" cellpadiving="0" class="tbradio">
                                        <tr id="tr6">
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="1" checked="checked" />&nbsp;腾讯QB卡</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="2" />&nbsp;盛大一卡通</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="3" />&nbsp;骏网一卡通</label>
                                            </td>
                                        </tr>
                                        <tr id="tr7">
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="4" />&nbsp;聚付通</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="5" />&nbsp;完美一卡通</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="6" />&nbsp;搜狐一卡通</label>
                                            </td>
                                        </tr>
                                        <tr id="tr8">
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="7" />&nbsp;征途游戏卡</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="8" />&nbsp;久游一卡通</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="9" />&nbsp;网易一卡通</label>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="12" />&nbsp;中国电信充值卡</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="13" />&nbsp;中国电信充值卡</label>
                                            </td>
                                            <td>
                                                <label>
                                                    <input type="radio" name="cardid" value="14" />&nbsp;神州行全国充值卡</label>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                            </tr>
                            <tr id="selcardno" style="display: none;">
                                <th width="29%" height="30" scope="row">
                                    <span class="red">*</span>卡号：
                                </th>
                                <td width="71%">
                                    <input name="txtCardNo" type="text" id="txtCardNo" size="20" class="fr_input02" />
                                </td>
                            </tr>
                            <tr id="selcardpass" style="display: none;">
                                <th width="29%" height="30" scope="row">
                                    <span class="red">*</span>卡密：
                                </th>
                                <td width="71%">
                                    <input name="txtCardPass" type="text" id="txtCardPass" size="20" class="fr_input02" />
                                </td>
                            </tr>
                            <tr>
                                <th width="29%" height="30" scope="row">
                                    <span class="red">*</span>您的充值帐号：
                                </th>
                                <td width="71%">
                                    <input name="txtUserName" type="text" id="txtUserName" size="20" value="<%=UiCommon.UserLoginInfo.UserName %>"
                                        class="fr_input02" />
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    <span class="red">*</span>确认充值帐号：
                                </th>
                                <td>
                                    <input name="txtUserName2" type="text" id="txtUserName2" size="20" value="<%=UiCommon.UserLoginInfo.UserName %>"
                                        class="fr_input02" />
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    <span class="red">*</span>充值金额：
                                </th>
                                <td>
                                    <input type="text" id="PayMoney" name="PayMoney" maxlength="9" class="fr_input02"
                                        onkeyup="CalculationMoney()" />
                                    * 金额请输入大于零的整数,点卡为点卡面值
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    赠送奖劵
                                </th>
                                <td>
                                    <input id="CouponNum" name="CouponNum" readonly="readonly" value="0" />张
                                </td>
                            </tr>
                            <tr>
                                <th height="65" scope="row">
                                    &nbsp;
                                </th>
                                <td>
                                    <input type="submit" name="button" id="button" value="提 交" class="but_01" />
                                    <input type="reset" name="button" id="reset1" value="重 填" class="but_02" />
                                </td>
                            </tr>
                        </table>
                        </form>
                        <div id="warning">
                            <center id="diankatishi" style="display: none;">
                                <b>
                                    <label style="color: red;">
                                        游戏点卡充值： 玩家充值自付20%手续费 ( 如：100充值卡得到实际面值为80 )</label></b>
                            </center>
                            请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。
                        </div>
                    </div>
                </div>
            </div>
            <!--right End-->
            <div class="clear">
            </div>
        </div>
        <!--content End-->
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

            var txtUserName = $("#txtUserName").val();
            var txtUserNameVal = $("#txtUserName2").val();

            if (txtUserName == "") {
                alert('请输入游戏帐号！（用户名）');
                return false;
            }

            var urlData = '/Public/XmlHttpUser.aspx?type=nameexist&username=' + escape(txtUserName);
            var strReturn = AjaxCall(urlData);
            if (strReturn == "0") {
                alert('对不起，您输入的游戏帐号！（用户名）不存在。');
                txtUserName.focus();
                return false;
            }

            //strReturn=="1" 存在    
            if (txtUserName != txtUserNameVal) {
                alert('两次输入游戏帐号不一致！');
                return false;
            }


            if ($("input[@type=radio][name=pay_type][checked]").val() == "2") {
                var cardno = $("#txtCardNo").val().trim();
                var cardpass = $("#txtCardPass").val().trim();
                if (cardno == "") {
                    alert('请输入卡号！（点卡号码）')
                    return false;
                }
                if (cardpass == "") {
                    alert('请输入卡密！（点卡密码）')
                    return false;
                }

            }

            var paymoney = $("#PayMoney").val().trim()

            if (paymoney == "") {
                alert('请输入充值金额！');
                return false;
            }


            if (isNaN(paymoney) || paymoney == 0 || paymoney < 0) {
                alert('充值金额为大于0的正整数！');
                return false;
            }


            return true;
        }

                         //-->
    </script>
</body>
</html>
