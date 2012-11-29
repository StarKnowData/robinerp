<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ReceiveMoneyConfig.aspx.cs" Inherits="Admin_SConfig_ReceiveMoneyConfig" %>

 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title></title>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	
	<style type="text/css">
		<!
		-- body { background-color: #FFFFFF; margin-top: 0px; }
		-- ></style>
</head>
<body>
 
    <form id="form1" runat="server" >
    <div>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03">
				<strong>设置领取金币参数</strong>
			</td>
		</tr>
	</table>
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td height="5">
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		<%--<tr>
		<td align="right">
				ID：&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtID" MaxLength="9" CssClass="put" runat="server"></asp:TextBox>  领取排序ID，请勿重复
				</td>
		</tr>--%>
		<tr>
			<td align="right">
				领取金币数：&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtReceiveMoney" MaxLength="9" CssClass="put" runat="server"></asp:TextBox>
	  
					设置每次玩家领取金币时的金币数
				</td>
		</tr> 
		<tr>
			<td align="right">领取金币时的底线金币&nbsp;&nbsp;</td>
			<td align="left">
				<asp:TextBox ID="txtMinMoney" MaxLength="9" runat="server" CssClass="put"></asp:TextBox>  
					 玩家只有在金币数低于这个时才能领取金币
					 
			</td>
		</tr>
    	<tr>
			<td align="right">
				领取的时间间隔&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtSpaceTime" MaxLength="9" runat="server" CssClass="put"></asp:TextBox> 间隔多少分钟才可以领取
				</td>
			 
		</tr>
		<tr>
			<td align="center" colspan="2">
				<asp:Button ID="Button1" runat="server" Text=" 添 加 " OnClick="ReceiveMoneyEdit" class="put" />
			</td>
		</tr>
	</table>
    </div>
    </form>
</body>
</html>
