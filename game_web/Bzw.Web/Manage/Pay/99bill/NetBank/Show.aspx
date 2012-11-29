<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay._99bill.NetBank.Manage_Pay_99bill_NetBank_Show"  %>

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
            &gt; <a href="/Manage/Pay/Default.aspx" title="充值">帐户充值</a>  
              &gt; 返回支付结果</span>
      <h1>快钱网上银行转帐充值</h1></div>
      <div class="rightbox" >
        <div class="prize_detail">
       
 
				 <form id="form2" runat="server" class="democss" >
  <dl>
    <dt>支付方式：</dt>
    <dd>
      <label>快钱网上银行转帐充值
          </label>
    </dd>
    <dt>订单编号：</dt>
    <dd>
      <label><asp:Literal ID="Lab_orderId" runat="Server" />
          </label>
    </dd>
    <dt>订单金额：</dt>
    <dd>
      <label><asp:Literal ID="Lab_orderAmount" runat="Server" />元
          </label>
    </dd>
    <dt>支付结果：</dt>
    <dd>
      <label><asp:Literal id="Lab_msg" RunAt="Server"/>
          </label>
    </dd>   
</dl>
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
