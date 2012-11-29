<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Prizes_PrizesAdd" Codebehind="PrizesAdd.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
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
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>添加奖品资料</strong></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品名称：</td>
                <td width="83%" align="left">
                    <input type="text" id="Award_Name" name="Award_Name" value="" class="put" maxlength="20" /></td>
            </tr>
            <tr style="display:none;">
                <td height="17%" align="right">
                    奖品分类：</td>
                <td align="left">
                    <select name="leitype">
                        <option value="1">虚拟类</option>
                        <option value="2" selected="selected">实物类</option>
                        <option value="3">现金类</option>
                    </select>
                </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品所需<%=UiCommon.StringConfig.GoldName %>数：</td>
                <td width="83%" align="left">
                    <input type="text" id="Award_MoneyCost" name="Award_MoneyCost" value="1" maxlength="18" class="put" /></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品所需游戏时长数：</td>
                <td width="83%" align="left">
                    <input type="text" id="Award_OnLineTime" name="Award_OnLineTime" value="0" maxlength="5" class="put" />小时</td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品数量：</td>
                <td width="83%" align="left">
                    <input type="text" id="Award_Num" name="Award_Num" value="1" maxlength="7" class="put" /></td>
            </tr>
            <%--<tr>
                <td align="right">
                    图片地址：</td>
                <td align="left">
                    <input name="picture" type="text" id="picture" value="/UpLoad/Prizes/NoPic.Jpg"
                        size="50" maxlength="100" class="put" /></td>
            </tr>--%>
            <tr>
                <td align="right">
                    奖品图片：</td>
                <td align="left">
					<asp:FileUpload runat="server" ID="fuImageUrl" />(300K以内，允许的类型：jpg,jpeg,gif)
                    <%--<iframe src='../inc/Pupload.inc.aspx' frameborder='0' style='height: 25px; width: 90%;'
                        scrolling='no'></iframe>--%>
                </td>
            </tr>
            <tr>
                <td align="right" valign="top">
                    奖品介绍：</td>
                <td align="left" valign="top">
                    <FCKeditorV2:FCKeditor ID="Award_Info" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/">
                    </FCKeditorV2:FCKeditor>
                </td>
            </tr>
            <tr style="display:none;">
                <td width="17%" align="right">
                    是否热换奖品：</td>
                <td width="83%" align="left">
                    <input type="radio" name="Award_hot" value="1" class="put" />
                    热换
                    <input name="Award_hot" type="radio" value="0" checked="checked" class="put" />
                    非热换</td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    &nbsp;</td>
                <td width="83%" align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 添 加 " class="put" OnClick="Prizes_Add" />
                </td>
            </tr>
        </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';
                
                if(!alertNull(document.getElementById("Award_Name"),'温馨提示：\n\n请输入奖品名称！')){
                    return false;
                }
                
                //----------
                if(!alertNonNegativeNumber($('#Award_MoneyCost')[0], msgfix+'奖品所需金币数'+msgend)){
                    return false;
                }
                
                //------document.getElementById('Award_OnLineTime') = $('#Award_OnLineTime')[0]
                if(!alertNonNegativeNumber($('#Award_OnLineTime')[0], msgfix+'奖品所需游戏时长数'+msgend)){
                    return false;
                }
                
                if(!alertNonNegativeNumber( $('#Award_Num')[0], msgfix+'奖品数量'+msgend)){
                    return false;
                }
                
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
