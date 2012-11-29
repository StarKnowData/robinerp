<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Alipay_Return2.aspx.cs" Inherits="Bzw.Web.Manage.Pay.AlipayTest.Alipay_Return2" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebService.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebMeta" Src="~/Public/WebMeta.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		<%= SiteConfig.GetParaValue("Title")%>
	</title>
	<WebMeta:Control ID="webmeta1" runat="server" />
	<link href="/css/main.css" rel="stylesheet" type="text/css" />

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
	<table width="1002" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td width="25" valign="top">
				<img src="/images/top_left.jpg" width="25" height="336" /></td>
			<td width="280" valign="top">
				<!--login-->
				<WebUserLogin:Control ID="webuserlogin1" runat="server" />
				<br />
				<!--l_service-->
				<WebService:Control ID="webservice1" runat="server" />
			</td>
			<td width="10" valign="top">
				<img src="/images/top_mid.jpg" width="10" height="336" /></td>
			<td width="660" valign="top">
				<!--header-->
				<WebTop:Control ID="webtop1" runat="server" />
				<table width="660" border="0" cellpadding="0" cellspacing="0" background="/images/main_bg1.jpg">
					<tr>
						<td height="25" background="/images/main_top.jpg">
							&nbsp;</td>
					</tr>
					<tr>
						<td>
							<div class="nav">
								当前位置：<a href="/">首页</a> > <a href="/Manage/Pay/Default.aspx">帐户充值</a> > 返回支付结果
							</div>
							<div class="titles t6">
							</div>
							<form id="form2" runat="server" onsubmit="return onFormSubmit(this)">
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
						</td>
					</tr>
					<tr>
						<td>
							<img src="/images/main_bottom.jpg" width="660" height="18" /></td>
					</tr>
				</table>
			</td>
			<td width="27" valign="top">
				<img src="/images/top_right.jpg" width="27" height="336" /></td>
		</tr>
	</table>
	<!--footer-->
	<WebFooter:Control ID="Control1" runat="server" />	

</body>
</html>
