<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay._99bill.NetBank.Manage_Pay_99bill_NetBank_Default" %>
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
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/public.js" type="text/javascript"></script>
    <style type="text/css">
        .style1
        {
            height: 35px;
        }
    </style>
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
        <div class="right_con_title">  <span>当前位置：<a href="/Default.aspx" title="首页">首页</a> 
            &gt; <a href="/Manage/Pay/Default.aspx" title="充值">充值</a> &gt; <a href="/Manage/Pay/99bill/NetBank/Default.aspx" title="快钱网上银行转帐充值">
            快钱网上银行转帐充值</a></span>
      <h1><asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
          快钱网上银行转帐充值</h1></div>
      <div class="rightbox" >
        <div class="prize_detail">
        <h6>您选择了快钱网上银行转帐充值方式</h6>        
        <form id="form1" action="Send.aspx" method="post" class="democss" onsubmit="return onFormSubmit(this)">
        <table border="0" cellpadding="2" cellspacing="0" class="tab03">
					<tr>
					<th align="right"  height="35">
							商户名称：</th>
						<td align="left">
							 
							 <label><%= UiCommon.StringConfig.CompanyNameOfPay%>
          </label>
						</td>
					</tr>
					<tr>
						<th align="right"  height="35">
							游戏帐号(用户名)：</th>
						<td align="left">
							 
							 <label>
        <input name="txtUserName" type="text" id="txtUserName" size="20" value="<%=UiCommon.UserLoginInfo.UserName %>" class="input" />
          </label>*
						</td>
					</tr>
					<tr>
						<th align="right"  height="35">
							确认帐号：</th>
						<td align="left">
						 
						  <input name="txtUserName2" type="text" id="txtUserName2" size="20" value="<%=UiCommon.UserLoginInfo.UserName %>" class="input" />
							*
						</td>
					</tr>
					<tr>
						<th align="right" class="style1">
							神州行充值卡面额：</th>
						<td align="left" class="style1">
						 <select id="PayMoney" name="PayMoney">
            <option value="50" selected>50元充值卡</option>
            <option value="100" >100元充值卡</option>
            <option value="300" >300元充值卡</option>
            <option value="500" >500元充值卡</option>
        </select>
						   * 金额请输入大于零的整数
						</td>
					</tr>
					 
				 
					<tr>
						<th height="65" scope="row"  height="35">
							&nbsp;</th>
						<td>
							<input type="submit" name="imageField2" id="imageField2" class="but_01" value="填好提交"  />
							<input type="reset" name="imageField3" id="imageField3" class="but_02" value="清空重写" onclick="ClearInfo()"/>
							
						</td>
					</tr>
					<tr><td  colspan="2" style="text-align:center"> <br /><br />
      <asp:Label ID="Label1" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td></tr>
				</table>
   
  
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

        return true;
    }
 //-->
</script>
</form>
        <div id="warning">	请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。</div>
                      <div class="clear"></div>
      </div>  
    </div>
     <div class="clear"></div>
      </div><!--right End-->
        
    </div><!--content End-->
</div>
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
		 
</body>
</html>
