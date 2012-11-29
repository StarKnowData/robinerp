<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="CreateBankTax.aspx.cs" Inherits="Admin_SConfig_CreateBankTax" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
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
                    <strong>玩家生成存单的税率设置</strong></td>
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
                <td align="right" width="25%">
                    税率设置：</td>
               <td align="left">
                    <input type="text" id="BankTax" name="BankTax" value="<%=BankTax%>" maxlength="9" class="put" />%&nbsp;&nbsp;请输入整数</td>
            </tr>
             <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"    OnClick="EditPric" />
                    
                </td>
            </tr>
        </table>
       
    </form>
</body>
</html>
