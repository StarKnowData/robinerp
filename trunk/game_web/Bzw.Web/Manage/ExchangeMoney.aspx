<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_ExchangeMoney"  %>

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

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

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
						>
						<a href="default.aspx">会员中心</a>
						><span class="title"> <%=ConfigurationManager.AppSettings["moneyName"].ToString()%>兑换</span></div>
				</div>
				<!--manage-->
				<form id="Form1" runat="server" class="democss">
					<div id="mem_content">
						<dl>
							<dt>用户名：</dt>
							<dd>
								<%=UiCommon.UserLoginInfo.UserName %>
							</dd>
							<dt>银行存款：</dt>
							<dd>
								<%= new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID).ToString()=="0"?"0":new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID).ToString()+UiCommon.StringConfig.AddZero() %>
								<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
							</dd>
							<dt>钱包余款：</dt>
							<dd>
								<%= new BLL.Member().GetWalletMoney(UiCommon.UserLoginInfo.UserID).ToString() == "0" ? "0" : new BLL.Member().GetWalletMoney(UiCommon.UserLoginInfo.UserID).ToString()+UiCommon.StringConfig.AddZero()%>
								<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
							</dd>
							<dt>登录密码：</dt>
							<dd>
								<label>
									<asp:TextBox ID="txtPassword" runat="server" CssClass="input" TextMode="password" MaxLength="50"></asp:TextBox>
								</label>
								<font class="red">*</font>
								<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtPassword" Display="Dynamic" ErrorMessage="请输入登录密码"></asp:RequiredFieldValidator>
								<asp:CustomValidator ID="CustomValidator1" runat="server" ClientValidationFunction="CheckPassword" ControlToValidate="txtPassword" Display="Dynamic" ErrorMessage="登录密码不正确" SetFocusOnError="True"></asp:CustomValidator>
							</dd>
							<dt>代理商帐号：</dt>
							<dd>
								<label>
									<asp:TextBox ID="txtAgent" runat="server" CssClass="input" MaxLength="50"></asp:TextBox>
								</label>
								<font class="red">*</font>（您要跟哪个代理商申请兑换<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>）<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtAgent" Display="Dynamic" ErrorMessage="请输入代理商帐号"></asp:RequiredFieldValidator>
							</dd>
							<dt>确认代理商帐号：</dt>
							<dd>
								<label>
									<asp:TextBox ID="txtAgent2" runat="server" CssClass="input" MaxLength="50"></asp:TextBox>
								</label>
								<font class="red">*</font>（请重复上面输入的代理商帐号）<asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate="txtAgent2" Display="Dynamic" ErrorMessage="请再次输入代理商帐号"></asp:RequiredFieldValidator>
								<asp:CompareValidator ID="CompareValidator1" runat="server" ControlToCompare="txtAgent" ControlToValidate="txtAgent2" Display="Dynamic" ErrorMessage="两次输入的代理商帐号不一致"></asp:CompareValidator>
								<asp:CustomValidator ID="CustomValidator2" runat="server" ClientValidationFunction="CheckAgentAccount" ControlToValidate="txtAgent2" Display="Dynamic" ErrorMessage="找不到您输入的代理商，请重新核对！" SetFocusOnError="True"></asp:CustomValidator>

								<script>
									//检查密码
									function CheckPassword(source, arguments)
									{
										var url = "UsersForm.aspx?params=checkcurrentpass&pass=" + arguments.Value + "&x=" + Math.random();
										var rc = $.ajax({url:url,async:false}).responseText;
										//alert(rc);
										arguments.IsValid = (rc == "success");
									}
									//检查代理商帐号
									function CheckAgentAccount(source, arguments)
									{
										var url = "UsersForm.aspx?params=checkagentaccount&account=" + encodeURIComponent( arguments.Value.Trim() ) + "&x=" + Math.random();
										var rc = $.ajax({url:url,async:false}).responseText;
										arguments.IsValid = (rc == "success");
									}
								</script>

							</dd>
							<dt>转账金额：</dt>
							<dd>
								<label>
									<asp:TextBox ID="txtMoney" runat="server" style="text-align:right" CssClass="input" MaxLength="10"></asp:TextBox>00
								</label>
								<font class="red">*</font>
								<asp:RequiredFieldValidator ID="RequiredFieldValidator4" runat="server" ControlToValidate="txtMoney" Display="Dynamic" ErrorMessage="请填写转帐金额"></asp:RequiredFieldValidator>
								<asp:CompareValidator ID="CompareValidator2" runat="server" ControlToValidate="txtMoney" Display="Dynamic" ErrorMessage="只能输入大于0的整数" Operator="GreaterThan" Type="Integer" ValueToCompare="0"></asp:CompareValidator>
							</dd>
						</dl>
						<div id="submit2">
							<label>
								<asp:Button runat="server" ID="btnSubmit" CssClass="btn_ok" Text="确认转帐" OnClick="btnSubmit_Click" />
							</label>
						</div>
						<hr />
						<div class="tips1">
							<b>兑换注意事项：</b><br />
							1、每次最低兑换<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>数为<%=MinMoney %>00<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>。<br />
							2、每笔转帐将按<%=ChangeType %>收取手续费，每笔收取<%=ProcedureFee %>00<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>。<br />
							<b>注意：</b><br />
							请一定要正确的填写转账游戏帐号，转账是从银行存款中转，如果银行存款不够，请到先到游戏中把钱包余款存入银行账户中，再来转账。
						</div>
					</div>
				</form>
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
