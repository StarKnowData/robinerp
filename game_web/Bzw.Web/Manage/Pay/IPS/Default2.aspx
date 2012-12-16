<%@ Page Language="C#" AutoEventWireup="true"  Inherits="Bzw.Inhersits.Manage.Pay.IPS.Manage_Pay_IPS_Default2" %>

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
	
	<link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script src="/Public/Js/public.js" type="text/javascript"></script>
</head>
<body>
<div id="wrap">
<!--header-->
    <WebTop:Control ID="webTopOne" runat="server" pageType="4"/> 

<!--content-->
    <div id="content">
      <div id="left1">
        <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
		<WebService:Control ID="webservice1" runat="server" />
      </div>
 <div id="right">
        <div class="right_con_title">  <span>当前位置：<a href="/Default.aspx" title="首页">首页</a> > <a href="/Manage/Pay/Default.aspx" title="充值">充值</a> > <a href="/Manage/Pay/IPS/Default.aspx" title="环迅充值">环迅充值</a></span>
      <h1><asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>环迅充值</h1></div>
      <div class="rightbox" >
        <div class="prize_detail">
        <h6>您选择了环迅神州行充值方式</h6>        
        <form id="Form1" action="OrderPay.aspx" class="democss" method="post"   onsubmit="return onFormSubmit(this)">
        
         <input type="hidden" name="Type" id="Type" value="phone" />
         
				<table border="0" cellpadding="2" cellspacing="0" class="tab03">
					<tr>
						<td colspan="2">
							&nbsp;
						</td>
					</tr>
					<tr>
						<th align="right"  height="35">
							游戏帐号(用户名)：</th>
						<td align="left">
							 
							<input type="text" id="txtUserName" name="txtUserName" value="<%=username %>" maxlength="20" class="input" />
							*
						</td>
					</tr>
					<tr>
						<th align="right"  height="35">
							确认帐号：</th>
						<td align="left">
						 
						<input type="text" id="txtUserName2" name="txtUserName2"  value="<%=username %>"  maxlength="20" class="input" />
							*
						</td>
					</tr>
				
					<tr>
						<th align="right"  height="35">
							金额：</th>
						<td align="left">
						<input type="text" id="PayMoney" name="PayMoney" maxlength="9" class="input" onkeypress="return KeyPressNum(this,event);" onkeyup="CalculationMoney()" />
						   * 金额请输入大于零的整数
						</td>
					</tr>
					<tr>
						<th align="right"  height="35">兑换成<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>：</th>
						<td><input id="ExchangeMoney" readonly="readonly" value="0"/></td>
					</tr>
				 	<tr>
					<th align="right" height="35">充值类型：</th>
					<td align="left">神舟卡充值</td>
					</tr>
					<tr>
						<th height="65" scope="row"  height="35">
							&nbsp;</th>
						<td>
							<input type="submit" name="imageField2" id="imageField2" class="but_01" value="填好提交"  />
							<input type="reset" name="imageField3" id="imageField3" class="but_02" value="清空重写" onclick="ClearInfo()"/>
						</td>
					</tr>
				</table>
        </form>
        <div id="warning">	请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。</div>
                     
      </div>  
    </div>
     
      </div><!--right End-->
        <div class="clear"></div>
    </div><!--content End-->
</div>
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
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
