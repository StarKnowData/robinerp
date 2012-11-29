<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_PrCs" Codebehind="PrCs.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

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
	<form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
			bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>设置推广提成参数</strong></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td height="5">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="right" width="25%">
					推广有效期&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<td width="15%" align="left">
						<input type="text" name="Con_ValidDay" id="Con_ValidDay" value="<%=Con_ValidDay %>"
							maxlength="4" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;天</td>
				<td width="60%">说明：从被推广玩家的注册时间算起，在有效期内推广人才能从被推广人得到提成，超过此有效期推广人不能再从此被推广人获得提成</td>
			</tr>
			<tr>
				<td align="right">
					推广游戏时长&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<td align="left">
						<input type="text" name="Con_OnlineTime" id="Con_OnlineTime" value="<%=Con_OnlineTime %>"
							maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;小时</td>
							<td align="left">说明：被推广玩家的游戏时间必须大于这个时长，才是一个有效的推广，否则这个推广无效</td>
			</tr>
			<tr>
				<td align="right">
					一个有效推广给推广员的奖励&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<td align="left">
						<input type="text" name="Con_ValidUserAddMoney" id="Con_ValidUserAddMoney" value="<%=Con_ValidUserAddMoney %>"
							maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
			<td align="left">说明：推广员推广了一个有效的推广后，一次性给推广员的奖励</td>
			</tr>
			<tr>
				<td align="right">
					被推广玩家达到有效推广后的奖励&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
				<td align="left">
					<input type="text" name="Con_ValidUserMoney" id="Con_ValidUserMoney" value="<%=Con_ValidUserMoney %>"
						maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
				<td align="left">说明：被推广员成为了一个有效的推广后，一次性给被推广员的奖励</td>
			</tr>
			<tr>
				<td align="right">
					被推广玩家每充值1元，推广员所得到的金币数&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<td align="left">
						<input type="text" name="Con_CardInPercent" id="Con_CardInPercent" value="<%=Con_CardInPercent %>"
							maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
							<td align="left">说明：在推广有效期内，并且是一个有效的推广，被推广玩家每充值1元，推广员应获得的提成(金币数)</td>
			</tr>
			<tr style="display: none;">
				<td align="right">
					抽取下级推广员的总业绩的百分比&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
				<td align="left">
					<input type="text" name="Con_GetMoneyPercent" id="Con_GetMoneyPercent" value="<%=Con_GetMoneyPercent %>"
						maxlength="3" class="put">%&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
				<td align="left"></td>
			</tr>
			<tr>
				<td align="right">
					推广收入结账最低金币数&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
				<td align="left">
					<input type="text" name="Con_MinClearingMoney" id="Con_MinClearingMoney" value="<%=Con_MinClearingMoney %>"
						maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
				<td align="left">说明：推广员推广收入只有累积到一定金额时才能结账，结账之后推广收入才转入推广员的账户</td>
			</tr>
			<tr>
				<td align="right">
					推荐人的奖励&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
				<td align="left">
					<input type="text" name="Con_RegMoney" id="Con_RegMoney" value="<%=Con_RegMoney %>"
						maxlength="9" class="put" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
				<td align="left">说明：新玩家注册时，他的推荐人获得的一次性奖励</td>
			</tr>
			<tr style="display: none;">
				<td align="right">
					兑换金币时，1元钱兑换多少金币&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
				<td align="left">
					<input type="text" name="Con_MoneyChangeRate" id="Con_MoneyChangeRate" value="<%=Con_MoneyChangeRate %>"
						maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
				<td align="left">说明：1人民币值多少金币</td>
			</tr>
			<tr>
				<td align="left" colspan="3" align="center">
					<asp:Button ID="Button1" runat="server" Text=" 修 改 " OnClick="PrCsEdit" class="put" Width="100"/>
				</td>
			</tr>
		</table>

		<script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的整数！';
                
                //----------
                var Con_ValidDay = document.getElementById('Con_ValidDay');
                if(!alertNonNegativeNumber(Con_ValidDay, msgfix+'推广收入结账的有效时间'+msgend)){
                    return false;
                }
                var Con_MinClearingMoney = document.getElementById('Con_MinClearingMoney');
                if(!alertNonNegativeNumber(Con_MinClearingMoney, msgfix+'推广收入结账最低要达到的金币数'+msgend)){
                    return false;
                }
                
                var Con_OnlineTime = document.getElementById('Con_OnlineTime');
                if(!alertNonNegativeNumber(Con_OnlineTime, msgfix+'一个有效的推广是被推广玩家的游戏时长必须达到'+msgend)){
                    return false;
                }
                
                var Con_ValidUserAddMoney = document.getElementById('Con_ValidUserAddMoney');
                if(!alertNonNegativeNumber(Con_ValidUserAddMoney, msgfix+'一个有效推广给推广员的提成'+msgend)){
                    return false;
                }
                
                var Con_CardInPercent = document.getElementById('Con_CardInPercent');
                if(!alertNonNegativeNumber(Con_CardInPercent, msgfix+'被推广玩家每充值1元，推广员所得到的金币数'+msgend)){
                    return false;
                }
                
                var Con_RegMoney = document.getElementById('Con_RegMoney');
                if(!alertNonNegativeNumber(Con_RegMoney, msgfix+'玩家注册时填入推荐人即可获得的金币数'+msgend)){
                    return false;
                }
                
                var Con_ValidUserMoney = document.getElementById('Con_ValidUserMoney');
                if(!alertNonNegativeNumber(Con_ValidUserMoney, msgfix+'被推广玩家成为有效推广员后的奖励金币数'+msgend)){
                    return false;
                } 
                return true;
            }
         //-->
		</script>

	</form>
</body>
</html>
