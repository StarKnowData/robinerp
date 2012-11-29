<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PrEdit.aspx.cs" Inherits="Admin_Lotter_PrEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/public.js"></script>
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
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>添加抽奖的奖品信息</strong></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品名称：</td>
                <td width="83%" align="left">
                    <input type="text" id="LotteryAwardName" name="LotteryAwardName" value="<%=strName %>" class="put" maxlength="20" /></td>
            </tr>
            <tr>
                <td align="right">
                    奖品图片：</td>
                <td align="left">
					<asp:PlaceHolder runat="server" ID="phImageUrl">
						<asp:TextBox runat="server" ID="txtImageUrl" CssClass="put"></asp:TextBox>&nbsp;
						<input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageUrl.Text.Trim() %>',0,0);" />&nbsp;
						<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />
					</asp:PlaceHolder>
					<asp:PlaceHolder runat="server" ID="phFileImage">
						<asp:FileUpload runat="server" ID="fuImage" />(300K以内，允许的类型：jpg,jpeg,gif)
					</asp:PlaceHolder>
                    
                </td>
            </tr>
            
            <tr>
                <td width="17%" align="right">
                    金的概率：</td>
                <td width="83%" align="left">
                    <input type="text" id="GoldRate" name="GoldRate" value="<%=strGoldRate %>" maxlength="2" class="put" />%</td>
            </tr>
            
                 <tr>
                <td align="right">
                    玉的概率：</td>
                <td align="left">
                    <input type="text" id="JadeRate" name="JadeRate" value="<%=strJadeRate %>" maxlength="2" class="put" />%
                   </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    银的概率：</td>
                <td width="83%" align="left">
                    <input type="text" id="SilverRate" name="SilverRate" value="<%=strSilverRate %>" maxlength="2" class="put" />% </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品数量：</td>
                <td width="83%" align="left">
                    <input type="text" id="Num" name="Num" value="<%=strNum %>" maxlength="5" class="put" /></td>
            </tr>
        
            <tr>
                <td width="17%" align="right">
                    &nbsp;</td>
                <td width="83%" align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 " class="put" OnClick="Prizes_Edit" />
                </td>
            </tr>
        </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';

                if (!alertNull(document.getElementById("LotteryAwardName"), '温馨提示：\n\n请输入奖品名称！')) {
                    return false;
                }
                
 
                if (!alertNonNegativeNumber($('#GoldRate')[0], msgfix + '金的概率' + msgend)) {
                    return false;
                }
                 
                if(!alertNonNegativeNumber($('#SilverRate')[0], msgfix+'银的概率'+msgend)){
                    return false;
                }
                if (!alertNonNegativeNumber($('#JadeRate')[0], msgfix + '玉的概率' + msgend)) {
                    return false;
                }
                if(!alertNonNegativeNumber( $('#Num')[0], msgfix+'奖品数量'+msgend)){
                    return false;
                }
                
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
