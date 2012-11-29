<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LastLoginGameCount.aspx.cs" Inherits="Admin_SConfig_LastLoginGameCount" %>

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
                    <strong>平台大厅左栏显示登录过的游戏个数设置</strong></td>
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
                    游戏个数设置：</td>
               <td align="left">
                    <input type="text" id="LastLoginGameCount" name="LastLoginGameCount" value="<%=LastLoginGameCount%>" maxlength="9" class="put"/>个</td>
            </tr>
             <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"    OnClick="EditConfig" />
                    
                </td>
            </tr>
        </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';
                
                //----------
                var LastLoginGameCount = document.getElementById('LastLoginGameCount');
                if(!alertNonNegativeNumber(MoneyToViptimeWeek, msgfix+'游戏个数'+msgend)){
                    return false;
                } 
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
