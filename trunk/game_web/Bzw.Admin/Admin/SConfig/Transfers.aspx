<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_Transfers" Codebehind="Transfers.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

	<script type="text/javascript" src="/Public/Js/jquery.js"></script>

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
		<table border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="#F2F8FF" class="admin_table2" width="100%">
			<tr>
				<td class="title_03">
					<strong>设置用户转账参数</strong></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td height="5">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="right" width="33%">
					账户余款（银行存款+钱包余款）必须大于&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<td align="left">
						<input type="text" id="TransferLessAllMoney" name="TransferLessAllMoney" value="<%=TransferLessAllMoney %>" maxlength="18" class="put" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
			</tr>
			<tr>
				<td align="right" width="33%">
					转账的金额必须是&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<td align="left">
						<input type="text" id="TransferMultiple" name="TransferMultiple" value="<%=TransferMultiple %>" maxlength="9" class="put" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;倍数</td>
			</tr>
			<tr>
				<td align="right" width="33%">
					单笔转账不得少于&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<td align="left">
						<input type="text" id="TransferLessMoney" name="TransferLessMoney" value="<%=TransferLessMoney %>" maxlength="18" class="put" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
			</tr>
			<tr>
				<td align="right" width="33%">
					普通用户转账需要扣除&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;万分之<td align="left">
						<input type="text" id="TransferTax" name="TransferTax" value="<%=TransferTax %>" maxlength="4" class="put" />&nbsp;&nbsp;&nbsp;的手续费</td>
			</tr>
			<tr>
				<td align="right" width="33%">
					VIP用户转账需要扣除&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;万分之<td align="left">
						<input type="text" id="VipTransferTax" name="VipTransferTax" value="<%=VipTransferTax %>" maxlength="4" class="put" />&nbsp;&nbsp;&nbsp;的手续费</td>
			</tr>
			<tr>
				<td align="right" width="33%">
					单笔转账最高扣除&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
				<td align="left">
					<input type="text" id="MaxTransTax" name="MaxTransTax" value="<%=MaxTransTax %>" maxlength="9" class="put" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;的手续费</td>
			</tr>
			<tr>
				<td>
					&nbsp;</td>
				<td align="left">
					<asp:Button ID="Button1" runat="server" Text=" 修 改 " class="put" OnClick="TranEdit" />
				</td>
			</tr>
		</table>

		<script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';
            
                //----------
                if(!alertNonNegativeNumber($('#TransferLessAllMoney')[0], msgfix+'账户余款（银行存款+钱包余款）'+msgend)){
                    return false;
                }
                
                //------document.getElementById('Award_OnLineTime') = $('#Award_OnLineTime')[0]
                if(!alertNonNegativeNumber($('#TransferMultiple')[0], msgfix+'转账金额的倍数] 请输入大于零的数字！')){
                    return false;
                }
                
                if(!alertNonNegativeNumber($('#TransferLessMoney')[0], msgfix+'单笔转账最少金额'+msgend)){
                    return false;
                }
                
                if(!alertNonNegativeNumber($('#TransferTax')[0], msgfix+'普通用户转账需要扣除的手续费'+msgend)){
                    return false;
                }
                if(!alertNonNegativeNumber($('#VipTransferTax')[0], msgfix+'VIP用户转账需要扣除的手续费'+msgend)){
                    return false;
                }
                
                if(!alertNonNegativeNumber($('#MaxTransTax')[0], msgfix+'单笔转账最高扣除的最高手续费'+msgend)){
                    return false;
                }
                 
                return true;
            }
         //-->
		</script>

	</form>
</body>
</html>
