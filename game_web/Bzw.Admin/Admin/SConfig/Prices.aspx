<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_Prices" Codebehind="Prices.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
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
    <form id="form1" runat="server"  onsubmit="return onFormSubmit(this)">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td class="title_03">
                    <strong>金币数设置</strong></td>
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
				<td colspan="2" style="height:25px;font-weight:bold" >
					VIP价格设置
				</td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    一周VIP价格：</td>
                <td align="left">
                    <input type="text" id="MoneyToViptimeWeek" name="MoneyToViptimeWeek" value="<%=MoneyToViptimeWeek %>" maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    一个月VIP价格：</td>
                <td align="left">
                    <input type="text" id="MoneyToViptimeMonth" name="MoneyToViptimeMonth" value="<%=MoneyToViptimeMonth %>" maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    半年VIP价格：</td>
                <td align="left">
                    <input type="text" id="MoneyToViptimeHYear" name="MoneyToViptimeHYear" value="<%=MoneyToViptimeHYear %>" maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
            </tr>
              <tr>
                <td align="right" width="25%">
                    一年VIP价格：</td>
                <td align="left">
                    <input type="text" id="MoneyToViptimeYear" name="MoneyToViptimeYear" value="<%=MoneyToViptimeYear %>" maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
            </tr>
            <tr>
				<td colspan="2" style="height:25px;font-weight:bold" >
					注册送金币设置
				</td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    注册送金币数设置：</td>
               <td align="left">
                    <input type="text" id="RegMoney" name="RegMoney" value="<%=RegMoney%>" maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
            </tr>
             <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"    OnClick="EditPric" />
                    
                </td>
            </tr>
        </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';
                
                //----------
                var MoneyToViptimeWeek = document.getElementById('MoneyToViptimeWeek');
                if(!alertNonNegativeNumber(MoneyToViptimeWeek, msgfix+'一周VIP价格'+msgend)){
                    return false;
                }
                
                var MoneyToViptimeMonth = document.getElementById('MoneyToViptimeMonth');
                if(!alertNonNegativeNumber(MoneyToViptimeMonth, msgfix+'一个月VIP价格'+msgend)){
                    return false;
                }
                
                var MoneyToViptimeHYear = document.getElementById('MoneyToViptimeHYear');
                if(!alertNonNegativeNumber(MoneyToViptimeHYear, msgfix+'半年VIP价格'+msgend)){
                    return false;
                }
                
                var MoneyToViptimeYear = document.getElementById('MoneyToViptimeYear');
                if(!alertNonNegativeNumber(MoneyToViptimeYear, msgfix+'一年VIP价格'+msgend)){
                    return false;
                }
                
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
