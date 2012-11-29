<%@ Page Language="C#" AutoEventWireup="true" ValidateRequest="false" EnableEventValidation="false" Inherits="Admin_Users_Edit_User" Codebehind="Edit_User.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
		<script src="/Public/Js/public.js" type="text/javascript"></script>
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/admin.js" type="text/javascript"></script>
	<style type="text/css">
 
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
 
</style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>会员管理</strong></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0" bgcolor="#FFFFFF">
			<tr>
				<td height="5">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="2" class="title_03">
					<strong>修改用户[&nbsp;<asp:Literal runat="server" ID="ltUserName"></asp:Literal>&nbsp;]资料</strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='../SConfig/UserPropEdit.aspx?params=<%=userName %>'>查看该用户的道具数量</a>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='../Pay/PayTotalRecord.aspx?params=<%=userName %>'>查看该用户的充值记录</a>
					<%if (UiCommon.StringConfig.BankVersion == "2")
       { %>	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='GameMoneyList.aspx?params=<%=UserID %>'>查看该用户的游戏金币记录</a><%} %>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					用户名：</td>
				<td width="83%" align="left">
				<asp:Literal runat="server" ID="LiteralUserName"></asp:Literal>
					<%--<asp:TextBox ID="txtUserNames" runat="server" Enabled="false" Class="put" MaxLength="20"></asp:TextBox>--%></td>
			</tr>
			<tr>
				<td width="17%" align="right">
					用户真实姓名：</td>
				<td width="83%" align="left">
				<asp:TextBox ID="txtUserRealName" runat="server" Class="put" MaxLength="9"></asp:TextBox><br/>
				</td>
			</tr>
			<tr>
				<td align="right">
					用户密码：</td>
				<td align="left">
					<asp:TextBox ID="txtPassWord" runat="server" Class="put" TextMode="password" MaxLength="20"></asp:TextBox>
					（无需修改时请留空）
				</td>
			</tr>
			<tr style="display:none;">
				<td align="right">
					用户原始密码：</td>
				<td align="left">
					<asp:Literal runat="Server" ID="ltSourcePwd"></asp:Literal>
					（这是MD5字符串，修改请用正常密码）
				</td>
			</tr>
			<tr>
				<td align="right">
					银行密码：</td>
				<td align="left">
					<asp:TextBox ID="txtTwoPassWord" runat="server" Class="put" TextMode="password" MaxLength="20"></asp:TextBox>（不修改密码，请留空）</td>
			</tr>
			<tr style="display:none;">
				<td align="right">
					原始银行密码：</td>
				<td align="left">
					<asp:Literal runat="server" ID="ltSourceTwoPwd"></asp:Literal>
					（这是MD5字符串，修改请用正常密码）
				</td>
			</tr>
			<tr style="display:none;">
				<td align="right">
					证件类型：</td>
				<td align="left">
					<asp:DropDownList runat="server" ID="ddlZJ_Type">
						<asp:ListItem Text="身份证" Value="1" Selected="true"></asp:ListItem>
						<asp:ListItem Text="军人证" Value="2"></asp:ListItem>
						<asp:ListItem Text="护照" Value="3"></asp:ListItem>
						<asp:ListItem Text="电话号码" Value="4"></asp:ListItem>
						<asp:ListItem Text="其他证件" Value="5"></asp:ListItem>
					</asp:DropDownList>
				</td>
			</tr>
			<tr>
				<td align="right">
					身份证号：</td>
				<td align="left">
					<asp:TextBox ID="txtZJ_Number" runat="server" Class="put" MaxLength="18"></asp:TextBox></td>
			</tr>
			<tr>
				<td align="right">
					提示问题：</td>
				<td align="left">
					
					<asp:Literal runat="server" ID="ltPwd_ques"></asp:Literal>
					</td>
			</tr>
			<tr>
				<td align="right">
					提示问题答案：</td>
				<td align="left">
					<asp:TextBox ID="txtPwd_anw" runat="server" Class="put" MaxLength="30"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="right">
					用户昵称：</td>
				<td align="left">
						 <asp:TextBox ID="txtNickName" runat="server"  Class="put"></asp:TextBox> 
				<%--	<asp:Literal runat="server" ID="LiteralNickName"></asp:Literal>--%>
				</td>
			</tr>
			<tr>
				<td align="right">
					头像：</td>
				<td align="left">
					<asp:Literal runat="server" ID="ltHeadImg"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td align="right">
					性别：</td>
				<td align="left">
					<asp:RadioButtonList runat="server" ID="rdolSex" RepeatDirection="Horizontal" RepeatLayout="flow">
						<asp:ListItem Text="男" Value="1"></asp:ListItem>
						<asp:ListItem Text="女" Value="0"></asp:ListItem>
					</asp:RadioButtonList>
				</td>
			</tr>
			<tr style="display:none;">
				<td align="right">
					用户组：</td>
				<td align="left">
					<asp:DropDownList runat="server" ID="ddlMember">
						<asp:ListItem Value="0" Text="一般玩家"></asp:ListItem>
						<asp:ListItem Value="1" Text="普通用户"></asp:ListItem>
						<asp:ListItem Value="2" Text="高级会员"></asp:ListItem>
						<asp:ListItem Value="3" Text="特邀嘉宾"></asp:ListItem>
						<asp:ListItem Value="4" Text="永久会员"></asp:ListItem>
						<asp:ListItem Value="5" Text="元老玩家"></asp:ListItem>
					</asp:DropDownList>
				</td>
			</tr>
			<tr style="display:none;">
				<td align="right">
					用户类型：</td>
				<td align="left">
					<asp:DropDownList runat="server" ID="ddlUserType">
						<asp:ListItem Text="普通玩家" Value="0" Selected="true"></asp:ListItem>
						<asp:ListItem Text="电视比赛玩家" Value="1"></asp:ListItem>
						<asp:ListItem Text="VIP玩家" Value="2"></asp:ListItem>
						<asp:ListItem Text="电视比赛VIP玩家" Value="3"></asp:ListItem>
					</asp:DropDownList>
				</td>
			</tr>
			<tr>
				<td align="right">
					游戏管理员等级：</td>
				<td align="left">
					<asp:DropDownList runat="server" ID="ddlMaster">
						<asp:ListItem Value="0" Text="非管理员" Selected="true"></asp:ListItem>
						<asp:ListItem Value="3" Text="超级管理员"></asp:ListItem>
					</asp:DropDownList>
				</td>
			</tr>
			<tr>
				<td align="right">
					钱包金币：</td>
				<td align="left">
					<asp:TextBox ID="txtWalletMoney" runat="server" Class="put" MaxLength="18"></asp:TextBox>
				 <%if (UiCommon.StringConfig.BankVersion == "2")
       { %>   <a href="#" onclick="openRoomRuleDiv('UserWalletMoney.aspx?UserID=<%=UserID %>',550,320);">点此查看</a>	<%} %>
				</td>
			</tr>
			<tr>
				<td align="right">
					银行金币：</td>
				<td align="left">
					<asp:TextBox ID="txtBankMoney" runat="server" Class="put" MaxLength="18"></asp:TextBox></td>
			</tr>
			<tr>
			    <td align="right"><%=UiCommon.StringConfig.GoldName %>：</td>
			    <td align="left"><asp:TextBox ID="txtLotteries" runat="server" CssClass="put" MaxLength="9"></asp:TextBox></td>
			</tr>
			<tr>
				<td align="right">
					魅力：</td>
				<td align="left">
					<asp:TextBox ID="txtFascination" runat="server" Class="put" MaxLength="7"></asp:TextBox></td>
			</tr>
			<tr runat="server" id="trIsTrader">
				<td align="right">
					是否是超级玩家：</td>
				<td align="left">
					<asp:RadioButtonList runat="server" ID="rdoIsTrader" RepeatDirection="horizontal" RepeatLayout="flow">
						<asp:ListItem Value="1" Text="是"></asp:ListItem>
						<asp:ListItem Value="0" Text="否"></asp:ListItem>
					</asp:RadioButtonList>
				</td>
			</tr>
			<tr>
				<td align="right">
					当前VIP时间：</td>
				<td align="left">
					<asp:Literal runat="server" ID="ltCurrentVIPTime"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td align="right">
					添加VIP时间：</td>
				<td align="left">
					<asp:RadioButtonList runat="server" ID="rdolVip" RepeatDirection="horizontal" RepeatLayout="Flow">
						<asp:ListItem Value="0" Text="取消VIP"></asp:ListItem>
						<asp:ListItem Value="604800" Text="一周VIP"></asp:ListItem>
						<asp:ListItem Value="2592000" Text="一月VIP"></asp:ListItem>
						<asp:ListItem Value="15552000" Text="半年VIP"></asp:ListItem>
						<asp:ListItem Value="31104000" Text="一年VIP"></asp:ListItem>
					</asp:RadioButtonList>
					&nbsp;自定义天数：<asp:TextBox ID="txtCustomVIP" runat="server" Width="50px" MaxLength="3" CssClass="put"></asp:TextBox>天
				</td>
			</tr>
			
			
			<tr>
				<td align="right">
					帐号是否锁定机器：</td>
				<td align="left">
					<asp:Label ID="LockLabel" runat="server"></asp:Label>
&nbsp;<asp:LinkButton ID="lockLB" runat="server" onclick="LinkButton1_Click" Visible="False">解除机器锁定</asp:LinkButton>
					
				</td>
			</tr>
			<tr>
				<td align="right">
					玩家帐号启用禁用：</td>
				<td align="left">
					<asp:RadioButtonList runat="server" ID="rdolDisabled" RepeatDirection="horizontal" RepeatLayout="flow">
						<asp:ListItem Value="0" Text="启用"></asp:ListItem>
						<asp:ListItem Value="1" Text="禁用"></asp:ListItem>
					</asp:RadioButtonList>
				</td>
			</tr>
			<tr>
				<td align="right" style="height: 27px">
					电子邮箱：</td>
				<td align="left" style="height: 27px">
					<asp:Literal runat="server" ID="ltEmail"></asp:Literal>
				</td>
			</tr>
			<% if(needqq=="1"){%>
			<tr>
				<td align="right" style="height: 27px">
					QQ：</td>
				<td align="left" style="height: 27px">
					<asp:Literal runat="server" ID="ltqqnum"></asp:Literal>
				</td>
			</tr>
			<% }%>
			<tr>
				<td align="right" style="height: 27px">
					电话号码：</td>
				<td align="left" style="height: 27px">
					<asp:Literal runat="server" ID="ltPhoneNum"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td align="right" style="height: 27px">
					个性签名：</td>
				<td align="left" style="height: 27px">
					<asp:Literal runat="server" ID="ltSignDesc"></asp:Literal>
				</td>
			</tr>
		 <tr>
				<td align="right" style="height: 27px">
					联系地址：</td>
				<td align="left" style="height: 27px">
					<asp:Literal runat="server" ID="ltAddress"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					固定电话：</td>
				<td width="83%" align="left">
					<asp:Literal runat="server" ID="ltTelNo"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					交税总额：</td>
				<td width="83%" align="left">
					<asp:Literal runat="server" ID="ltAllTax"></asp:Literal>
				</td>
			</tr>
			
			<tr>
				<td width="17%" align="right">
					注册IP：</td>
				<td width="83%" align="left">
					<asp:Literal runat="server" ID="ltRegisterIP"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					注册时间：</td>
				<td width="83%" align="left">
					<asp:Literal runat="server" ID="ltRegisterTM"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					最后登录IP：</td>
				<td width="83%" align="left">
					<asp:Literal runat="server" ID="ltLastLoginIP"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					最后登录时间：</td>
				<td width="83%" align="left">
					<asp:Literal runat="server" ID="ltLastLoginTM"></asp:Literal>
				</td>
			</tr>
			<tr>
				<td align="right">
					登录次数：</td>
				<td align="left">
					<asp:Literal runat="server" ID="ltAllLoginTime"></asp:Literal>
				</td>
			</tr>
		<%--	<tr>
				<td align="right">
					网站登录次数：</td>
				<td align="left">
					<asp:Literal runat="server" ID="ltWebLoginTime"></asp:Literal>
				</td>
			</tr>--%>
			<tr>
				<td align="right">
					&nbsp;
				</td>
				<td align="left">
					<asp:Button ID="Button1" runat="server" Text="确认修改" Class="put"  OnClick="Edit_Users" />
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
