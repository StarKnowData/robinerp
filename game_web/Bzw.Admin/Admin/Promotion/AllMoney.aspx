<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_AllMoney" Codebehind="AllMoney.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="7" align="center" class="title_03">
					<strong>推广员收入明细</strong></td>
			</tr>
			<tr>
				<td width="30%" align="right">
					用户名：</td>
				<td width="83%" align="left">
					<font color="red">
						<%=TGUserName %>
					</font>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					推广员总收入：</td>
				<td width="83%" align="left">
					<font color="red">
						<%=Convert.ToInt32(TGIncome) + Convert.ToInt32(TGPayIncome)%>
					</font>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					有效推广的收入（被推广玩家的推广度达到100%后得到金币数）：</td>
				<td width="83%" align="left">
					<font color="red">
						<%=TGIncome%>
					</font>
				</td>
			</tr>
			
			<tr>
				<td width="17%" align="right">
					推广员抽取被推广玩家的充值提成：</td>
				<td width="83%" align="left">
					<font color="red">
						<%=TGPayIncome%>
					</font>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					推广员未结账的推广收入总数：</td>
				<td width="83%" align="left">
					<font color="red">
						<%=TGMoneyCount%>
					</font>
				</td>
			</tr>
			<tr>
				<td width="17%" align="right">
					推广员已结账金币总数：</td>
				<td width="83%" align="left">
					<font color="red">
						<%=TGBalanceMoney %>
					</font>
				</td>
			</tr>
			<tr>
			<td colspan="2" align="center" ><input id="back" type="button" value="返回" class="put" onclick="javascript:history.back();" /></td>
			</tr>
		</table>
		<%--<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="7" align="center" class="title_03">
                    <strong>推广员总金额详细</strong></td>
            </tr>  
            <tr>
                <td width="30%" align="right">
                    用户名：</td>
                <td width="83%" align="left">
                    <font color="red"><%=TGUserName %></font></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                   推广用户申请结算总金额：</td>
                <td width="83%" align="left">
                    <font color="red"><%=a %></font></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    被推广用户到达时间后得到金币数：</td>
                <td width="83%" align="left">
                    <font color="red"><%=b %></font></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    推广员结算后抽水金币数：</td>
                <td width="83%" align="left">
                    <font color="red"><%=c %></font></td>
            </tr>  
              <tr>
                <td width="17%" align="right">
                    被推广用户充值得到金币数：</td>
                <td width="83%" align="left">
                    <font color="red"><%=d %></font></td>
            </tr>                              
        </table>--%>
	</form>
</body>
</html>
