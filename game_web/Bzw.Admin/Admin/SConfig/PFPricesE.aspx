<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_PFPricesE" Codebehind="PFPricesE.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
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
<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
  <tr><td colspan="2" class="title_03"><strong>修改魅力值清零道具信息</strong></td></tr>
  <tr><td width="17%" align="right">道具名称：</td>
      <td width="83%" align="left"><input type="text" name="PropName" id="PropName" value="<%=PropName %>" readonly class="put" /></td>
  </tr>

  <tr><td width="17%" align="right">价格：</td>
      <td width="83%" align="left"><input type="text" name="Price" id="Price" value="<%=Price %>" maxlength="9" class="put" /></td>
  </tr>
    <tr><td width="17%" align="right">清零魅力值（最大能清除多少魅力值）：</td>
      <td width="83%" align="left"><input type="text" name="VipPrice" id="VipPrice" value="<%=VipPrice %>" maxlength="9" class="put" /></td>
  </tr>
   <tr><td width="17%" align="right" valign="top">道具描述：</td>
      <td width="83%" align="left"><input type="text" name="Descript" id="Descript" value="<%=Descript %>" class="put" style="width: 338px" />限25个字符
      </td>
  </tr>
  <tr>
    <td width="17%" align="right">&nbsp;</td>
    <td width="83%" align="left">
        <asp:Button ID="Button1" runat="server" Text="提交修改" class="put" OnClick="EditJpPro" />
    </td>
  </tr>
  </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';
                
                /*
                if(!alertNull(document.getElementById("Award_Name"),'温馨提示：\n\n请输入奖品名称！')){
                    return false;
                }*/
                
                //----------
                if(!alertNonNegativeNumber($('#Price')[0], msgfix+'价格'+msgend)){
                    return false;
                }
                
                //------document.getElementById('Award_OnLineTime') = $('#Award_OnLineTime')[0]
                if(!alertNonNegativeNumber($('#VipPrice')[0], msgfix+'清零魅力值'+msgend)){
                    return false;
                }
                
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
