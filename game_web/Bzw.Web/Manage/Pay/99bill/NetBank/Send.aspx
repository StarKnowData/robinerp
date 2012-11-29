<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay._99bill.NetBank.Manage_Pay_99bill_NetBank_Send" %>

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
              &gt; 快钱网上银行转帐充值</span>
      <h1>快钱网银转帐</h1></div>
      <div class="rightbox" >
        <div class="prize_detail">
       
 
				 <form id="form2" runat="server" >
								<div class="newsCont">
									<div style=" text-align:center "><table border="0" cellpadding="2" cellspacing="0" >
										<tr>
											<th align="right">
												商品名称：</th>
											<td align="left">
												<label><asp:Literal id="Lab_productName" RunAt="Server"/>
          </label>
											</td>
										</tr>
										<tr>
											<th align="right">
												支付方式：</th>
											<td align="left">
												<label>快钱网上银行转帐支付
          </label>
											</td>
										</tr>
										<tr>
											<th align="right">
												订单编号：</th>
											<td align="left">
											<label><asp:Literal id="Lab_orderId" RunAt="Server"/>
          </label>
											</td>
										</tr>
										<tr>
											<th align="left">
												支付人：</th>
											<td align="left">
											  <label><asp:Literal id="Lab_payerName" RunAt="Server"/>
          </label>
											</td>
										</tr>
										<tr>
											<th align="right">
												支付金额：</th>
											<td align="left">
											 
        <asp:Literal id="Lab_orderAmount" RunAt="Server"/>元
          </label>
											</td>
										</tr>
										<tr><td>&nbsp;</td></tr>
									 
									</table></div> 
								</div>
						 
        </form>
        <div id="submit">
        <!--form name="kqPay" method="post" action="https://www.99bill.com/gateway/recvMerchantInfoAction.htm" target="_blank"-->
      <form name="kqPay" method="post" action="https://www.99bill.com/gateway/recvMerchantInfoAction.htm" >
		    <input type="hidden" id="inputCharset" name="inputCharset" runat="server"/>
		    <input type="hidden" id="bgUrl" name="bgUrl" runat="server"/>
		    <input type="hidden" id="pageUrl" name="pageUrl" runat="server"/>
		    <input type="hidden" id="version" name="version" runat="server"/>
		    <input type="hidden" id="language" name="language" runat="server"/>
		    <input type="hidden" id="signType" name="signType" runat="server"/>
		    <input type="hidden" id="merchantAcctId" name="merchantAcctId" runat="server"/>
		    <input type="hidden" id="payerName" name="payerName" runat="server"/>
		    <input type="hidden" id="payerContactType" name="payerContactType" runat="server"/>
		    <input type="hidden" id="payerContact" name="payerContact" runat="server"/>
		    <input type="hidden" id="orderId" name="orderId" runat="server"/>
		    <input type="hidden" id="orderAmount" name="orderAmount" runat="server"/>
		    <input type="hidden" id="payType" name="payType" runat="server"/>
		    <input type="hidden" id="orderTime" name="orderTime" runat="server"/>
		    <input type="hidden" id="productName" name="productName" runat="server"/>
		    <input type="hidden" id="productNum" name="productNum" runat="server"/>
		    <input type="hidden" id="productId" name="productId" runat="server"/>
		    <input type="hidden" id="productDesc" name="productDesc" runat="server"/>
		    <input type="hidden" id="ext1" name="ext1" runat="server"/>
		    <input type="hidden" id="ext2" name="ext2" runat="server"/>
		    <input type="hidden" id="signMsg" name="signMsg" runat="server"/>
		    
		    <input type="hidden" id="bankId" name="bankId" runat="server" />
            <input type="hidden" id="redoFlag" name="redoFlag" runat="server" />
            <input type="hidden" id="pid" name="pid" runat="server" />
            
		    <input type="submit" id="submit2" value="提交到快钱" class="but_01">
	    </form>	
</div> 
        
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
