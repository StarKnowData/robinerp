<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_ExchangeMoneyLog"  %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebService.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		
	</title>
	
	<link href="/css/style.css" rel="stylesheet" type="text/css" />
	<link href="/css/css.css" rel="stylesheet" type="text/css" />
	<link href="/css/cssPage.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
	<div id="layout">
		<!--header-->
		<WebTop:Control ID="webtop1" runat="server" />

		<script type="text/javascript">SetNav(8);</script>

		<!--main-->
		<div id="main">
			<!--left-->
			<div id="left">
				<div class="left_t">
				</div>
				<div class="left_m">
					<!--l_manage-->
					<Left:Control ID="Left1" runat="server" />
				</div>
				<div class="left_b">
				</div>
			</div>
			<!--right-->
			<div id="right">
				<div id="r_top">
					<div id="local_A">
						<img src="/images/local_mem.jpg" /></div>
					<div id="local_B">
						<a href="/Default.aspx">首页</a>
						> 会员中心 > 交易记录</div>
				</div>
				<!--manage-->
				<div id="pic_header">
					<a href="/Manage/Pay/PointCardLog.aspx">点卡充值记录</a>&nbsp;&nbsp;|&nbsp;&nbsp;
					<a href="/Manage/BankTransLog.aspx">转帐记录</a>&nbsp;&nbsp;|&nbsp;&nbsp;
					<a href="/Manage/ExchangeMoneyLog.aspx"><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>兑换记录</a>
				</div>
				<div id="mem_content">
					<table width="100%" border="0" cellspacing="0" cellpadding="0" class="banklsit">
						<thead>
							<tr>
								<th colspan="8" scope="col">
									<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>兑换记录</th>
							</tr>
						</thead>
						<tr>
							<th>
								序号</th>
							<th>
								兑换时间</th>
							<th>
								交易<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></th>
							<th>
								实际<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></th>
							<th>
								手续费</th>
							<th>
								代理商</th>
						</tr>
						<asp:Repeater ID="rpList" runat="server">
							<ItemTemplate>
								<tr>
									<td>
										<%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 )%>
									</td>
									<td>
										<%#Eval( Bzw.E.Web_VAgentMoneyLog._.InputDate.Name, "{0:yyyy-MM-dd HH:mm:ss}" )%>
									</td>
									<td>
										<%#Eval(Bzw.E.Web_VAgentMoneyLog._.Money.Name).ToString() == "0" ? "0" : Eval(Bzw.E.Web_VAgentMoneyLog._.Money.Name).ToString()+UiCommon.StringConfig.AddZero()%>
									</td>
									<td>
										<%#Eval(Bzw.E.Web_VAgentMoneyLog._.ActuallyMoney.Name).ToString() == "0" ? "0" : Eval(Bzw.E.Web_VAgentMoneyLog._.ActuallyMoney.Name).ToString()+UiCommon.StringConfig.AddZero()%>
									</td>
									<td>
										<%#Eval(Bzw.E.Web_VAgentMoneyLog._.ProcedureFee.Name).ToString() == "0" ? "0" : Eval(Bzw.E.Web_VAgentMoneyLog._.ProcedureFee.Name).ToString()+UiCommon.StringConfig.AddZero()%>
									</td>
									<td>
										<%#Eval( Bzw.E.Web_VAgentMoneyLog._.AgentLoginName.Name )%>
									</td>
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='20'>暂无数据...</td></tr>"></asp:Literal>
					</table>
					<webdiyer:AspNetPager PageSize="30" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" NumericButtonCount="5" UrlPaging="True">
					</webdiyer:AspNetPager>
				</div>
				<div id="r_bottom">
				</div>
				<div class="clear">
				</div>
			</div>
		</div>
		<!--footer-->
		<WebFooter:Control ID="webfooter1" runat="server" />
	</div>
</body>
</html>
