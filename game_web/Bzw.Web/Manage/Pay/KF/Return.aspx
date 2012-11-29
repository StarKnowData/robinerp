<%@ Page Language="C#" AutoEventWireup="true"   Inherits="Bzw.Inhersits.Manage.Pay.KF.Manage_Pay_KF_Return" %>

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
      <h1>花旗充值</h1></div>
      <div class="rightbox" >
        <div class="prize_detail">
       
 
				 <form id="form2" runat="server" >
								<div class="newsCont">
									<div style=" text-align:center "><table border="0" cellpadding="2" cellspacing="0" >
										<tr>
											<th align="right">
												支付结果：</th>
											<td align="left">
												<%=PayResult %>
												<asp:Literal id="Lab_msg" RunAt="Server"/>
											</td>
										</tr>
										<tr>
											<th align="right">
												订单号：</th>
											<td align="left">
												<%=PayOrderID %>
											</td>
										</tr>
										<tr>
											<th align="right">
												充值金额：</th>
											<td align="left">
												<%=PayMoney %>
											</td>
										</tr>
										<tr><td>&nbsp;</td></tr>
										 <tr>                                       
                                            <td colspan="2" align="center">
                                                <a href="/Manage/" title="返回会员中心">返回会员中心</a>
                                            </td>
                                        </tr>
									</table></div>
                                   
									
								
								</div>
						 
        </form>
        <div id="warning">	请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。</div>
                      <div class="clear"></div>
      </div>  
    </div>
   
      </div><!--right End-->
          <div class="clear"></div>
    </div><!--content End-->
</div>
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
 
</body>
</html>
