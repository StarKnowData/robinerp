<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ClothEdit.aspx.cs" Inherits="Admin_Cloth_ClothEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <style type="text/css">
        <!
        -- body
        {
            background-color: #FFFFFF;
            margin-top: 0px;
        }
        -- ></style>
</head>
<body>
    <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
                <strong>修改服装信息</strong>
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                服装名称：
            </td>
            <td width="83%" align="left">
                <input type="text" name="LogName" id="LogName" value="<%=LogName %>"  
                    class="put" />
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                头像图片：
            </td>
             <td width="83%" align="left">
             <img src="<%=ImgSrc %>" width="55px" height="55px" />
             </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                价格：
            </td>
            <td width="83%" align="left">
                <input type="text" name="Price" id="Price" value="<%=Price %>" maxlength="13" class="put" /><%=UiCommon.StringConfig.MoneyName %>
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                赠送<%=UiCommon.StringConfig.GoldName %>：
            </td>
            <td width="83%" align="left">
                <input type="text" name="SendLotteries" id="SendLotteries" value="<%=SendLotteries %>" maxlength="9"
                    class="put" />
            </td>
        </tr>
        <tr>
            <td width="17%" align="right" valign="top">
                描述：
            </td>
            <td width="83%" align="left">
            <textarea name="Descript" id="Descript" style=" width:300px; height:100px;"  ><%=Descript %></textarea>500字以内
              
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                &nbsp;
            </td>
            <td width="83%" align="left">
                <asp:Button ID="btnSumbit" runat="server" Text="提交修改" class="put" 
                    onclick="btnSumbit_Click"   /> &nbsp;&nbsp;&nbsp;<input type="button" class="put" onclick="location.href='ClothesList.aspx';" value="返回列表" />
            </td>
        </tr>
    </table>

    <script type="text/javascript">
        <!--
        function onFormSubmit(f) {

            var msgfix = '温馨提示：\n\n[';
            var msgend = '] 请输入大于或等于零的数字！';

            
            if(!alertNull(document.getElementById("LogName"),'温馨提示：\n\n请输入服装名称！')){
            return false;
            } 

            //----------
            if (!alertNonNegativeNumber($('#Price')[0], msgfix + '价格' + msgend)) {
                return false;
            }
            if (!alertNonNegativeNumber($('#SendLotteries')[0], msgfix + '赠送数' + msgend)) {
                return false;
            }

            

            return true;
        }
         //-->
    </script>

    </form>
</body>
</html>
