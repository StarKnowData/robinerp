<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FasciExchangeEdit.aspx.cs" Inherits="Admin_FasciExchange_FasciExchangeEdit" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
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
                <td class="title_03" colspan="2">
                    <strong>魅力兑换修改</strong></td>
            </tr>
      
            <tr>
            <td  align="right" width="34%">兑换名称&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
            <td align="left"><input type="text" id="PrizeName" name="PrizeName"  runat="server" readonly="readonly"/>不能修改</td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    魅力值数&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
                    <td align="left">
                        <input type="text" name="FasciNum" id="FasciNum" value="" runat="server" maxlength="9" class="put"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    此魅力值数可兑换的奖品数&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
                    <td align="left">
                        <input type="text" name="PropCount" id="PropCount" value="" maxlength="9" runat="server" class="put"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;个</td>
            </tr>
            
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 " OnClick="PrCsEdit" class="put"/>
                    
                </td>
            </tr>
        </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的整数！';

                //----------
                var PrizeName = document.getElementById("PrizeName");
                if (PrizeName.value == "") {
                    alert('奖品名称不能为空!');
                    return false;
                }
                var FasciNum = document.getElementById('FasciNum');
                if (!alertNonNegativeNumber(FasciNum, msgfix + '魅力值数' + msgend)) {
                    return false;
                }

                var PropCount = document.getElementById('PropCount');
                if (!alertNonNegativeNumber(PropCount, msgfix + '魅力值必须大于XX才能兑换' + msgend)) {
                    return false;
                }
                
              
                
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
