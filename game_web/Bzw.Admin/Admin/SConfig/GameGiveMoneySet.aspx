<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GameGiveMoneySet.aspx.cs" Inherits="Bzw.Web.Admin.SConfig.GameGiveMoneySet" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>
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
                    <strong>在线送金币设置</strong></td>
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
                   活动开始时间：</td>
                <td align="left">
                    <input type="text" id="txtBeginDate" name="txtBeginDate"  class="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})" value="<%=StartPresent%>" readonly/></td>
            </tr>
            <tr>
                <td align="right" width="25%">
                   活动结束时间：</td>
                <td align="left">
                    <input type="text" id="txtEndDate" name="txtEndDate" class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})" value="<%=EndPresent%>" readonly/></td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    每次送：</td>
                <td align="left">
                    <input type="text" id="CoinNum" name="CoinNum" value="<%= CoinNum %>" maxlength="9" class="put" maxlength="10">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;金币</td>
            </tr>
              <tr>
                <td align="right" width="25%">
                    每：</td>
                <td align="left">
                    <input type="text" id="TimeLength" name="TimeLength" value="<%=TimeLength %>" maxlength="9" class="put" maxlength="10">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;分钟送一次</td>
            </tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"    OnClick="EditPric" />
                </td>
            </tr>
            <tr><td colspan="2">如要取消在线赠送金币功能,请将活动结束时间设置为过期时间(如:1900-01-01 00:00:00)</td></tr>
        </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';

                var TxtBeginDate = document.getElementById('txtBeginDate');

                var txtEndDate = document.getElementById('txtEndDate');

                var CoinNum = document.getElementById('CoinNum');
                reg = /^[1-9]{1}[0-9]*$|^(0){1}$/;
                if (!reg.test(CoinNum.value)) {
                	alert("金币数只能为正整数");
                	return false;
                }
                return true;
                /*if(!alertNonNegativeNumber(MoneyToViptimeHYear, msgfix+'半年VIP价格'+msgend)){
                    return false;
                }*/

                var TimeLength = document.getElementById('TimeLength');
                reg = /^[1,9]{1}[0,9]*$|^(0){1}$/
                if (!reg.test(TimeLength.value)) {
                	alert("分钟只能设置正整数");
                	return false;
                }
                /*if(!alertNonNegativeNumber(MoneyToViptimeYear, msgfix+'一年VIP价格'+msgend)){
                    return false;
                }*/
                
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
