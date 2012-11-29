<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage_Pay_Baofoo_Default" %>

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

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script src="/Public/Js/public.js" type="text/javascript"></script>

    <style type="text/css">
        .tbradio input
        {
            border: 0;
            vertical-align: middle;
        }
    </style>
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
                    宝付支付</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 宝付在线支付</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
        
                    <h6>
                        您选择了宝付支付方式</h6>
                    <form id="form1" action="pay_post.aspx" class="democss" method="post" onsubmit="return onFormSubmit(this)">
                    <input type="hidden" name="Type" value="bank" />

                    <script type="text/javascript">

                        function ChoosePayment() {
                            if (document.getElementById("bank").checked) {
                                document.getElementById("selbank").style.display = "";
                                document.getElementById("selcard").style.display = "none";
                            }
                            else {
                                document.getElementById("selbank").style.display = "none";
                                document.getElementById("selcard").style.display = "";
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
                                                <input type="radio" name="pay_type" value="1" id="bank" checked="checked" onclick="ChoosePayment();" />&nbsp;银行支付</label>
                                            &nbsp;
                                            <label>
                                                <input type="radio" name="pay_type" value="2" id="gamecard" onclick="ChoosePayment();" />&nbsp;点卡充值</label>
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
                                    <tr id="tr7">
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1002" checked="checked" />&nbsp;工商银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1005" />&nbsp;农业银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1001" />&nbsp;招商银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1003" />&nbsp;建设银行</label>
                                        </td>
                                    </tr>
                                    <tr id="tr8">
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1020" />&nbsp;交通银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1006" />&nbsp;民生银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1004" />&nbsp;浦发银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1026" />&nbsp;中国银行</label>
                                        </td>
                                    </tr>
                                    <tr id="tr9">
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1039" />&nbsp;中信银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1009" />&nbsp;兴业银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1032" />&nbsp;北京银行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1022" />&nbsp;光大银行</label>
                                        </td>
                                    </tr>
                                    <tr id="tr3">
                                        <td>
                                            <label>
                                                <input type="radio" name="bankid" value="1000" />&nbsp;全部网银支付</label>
                                        </td>
                                        <td>
                                            &nbsp;
                                        </td>
                                        <td>
                                            &nbsp;
                                        </td>
                                        <td>
                                            &nbsp;
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
                                    <tr id="tr1">
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="1" checked="checked" />&nbsp;神州行</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="2" />&nbsp;联通卡</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="3" />&nbsp;电信卡</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="11" />&nbsp;盛大卡</label>
                                        </td>
                                    </tr>
                                    <tr id="tr2">
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="12" />&nbsp;完美卡</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="14" />&nbsp;征途卡</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="15" />&nbsp;骏网一卡通</label>
                                        </td>
                                        <td>
                                            <label>
                                                <input type="radio" name="cardid" value="16" />&nbsp;网易卡</label>
                                        </td>
                                    </tr>
                                </table>
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

                        <script type="text/javascript">
<!--
			function CalculationMoney() {
			
				KeyPressNum(this,$("#PayMoney").val());
				
				if(isNaN($("#PayMoney").val())){
					$("#ExchangeMoney").val("0");
					return false;
				}else{
					$("#ExchangeMoney").val($("#PayMoney").val()*<%= UiCommon.StringConfig.AddZeros(MoneyRate) %>);
				}	
			}
 

		  
 //-->
                        </script>

                        <tr>
                            <th height="30" scope="row">
                                <span class="red">*</span>充值金额：
                            </th>
                            <td>
                                <input type="text" id="PayMoney" name="PayMoney" maxlength="9" class="input" onkeypress="return KeyPressNum(this,event);"
                                    onkeyup="CalculationMoney()" />
                                * 金额请输入大于零的整数,点卡为点卡面值
                            </td>
                        </tr>
                        <tr>
                            <th height="65" scope="row">
                                &nbsp;
                            </th>
                            <td>
                                <input type="submit" name="button" id="button" value="  " class="but_01" />
                                <input type="reset" name="button" id="reset1" value="  " class="but_02" />
                            </td>
                        </tr>
                    </table>
                    </form>
                    <div id="warning">
                        请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。</div>
                </div><p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
            </div>
        </div>
        <!--right End-->
        <div class="clear">
        </div>
    
    <!--content End-->
  
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
            var txtUserNameVal = document.getElementById('txtUserName2');
            if (!alertNull(txtUserName, '请输入游戏帐号！（用户名）')) {
                return false;
            }
            var urlData = '/Public/XmlHttpUser.aspx?type=nameexist&username=' + escape(txtUserName.value.trim());
            var strReturn = AjaxCall(urlData);
            if (strReturn == "0") {
                alert('对不起，您输入的游戏帐号！（用户名）不存在。');
                txtUserName.focus();
                return false;
            }
            //strReturn=="1" 存在    

            if (txtUserNameVal != txtUserNameVal) {
                alert('两次输入游戏帐号不一致！');
                return false;
            }

            if (isNaN($("#PayMoney").val())) {
                alert('充值金额请输入整数！');
                return false;
            }

            return true;
        }

                         //-->
    </script>

</body>
</html>
