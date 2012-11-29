<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_JpProicesE" Codebehind="JpProicesE.aspx.cs" %>

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
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="2" class="title_03">
					<strong>修改道具价格</strong></td>
			</tr>
			<tr>
				<td width="17%" align="right">
					道具名称：</td>
				<td width="83%" align="left">
					<%--<input type="text" name="PropName" id="PropName" value="<%=PropName %>" readonly class="put" />--%>
					<%=PropName %></td>
			</tr>
			<tr>
				<td width="17%" align="right">
					普通用户价格：</td>
				<td width="83%" align="left">
					<input type="text" name="Price" id="Price" value="<%=Price %>" maxlength="7" class="put" /></td>
			</tr>
			<tr>
				<td width="17%" align="right">
					VIP价格：</td>
				<td width="83%" align="left">
					<input type="text" name="VipPrice" id="VipPrice" value="<%=VipPrice %>" maxlength="7" class="put" />
					
					</td>
			</tr>
			<tr>
				<td width="17%" align="right" valign="top">
					变化魅力值：</td>
				<td width="83%" align="left">
					<input type="text" name="Fasic" id="Fasic" value="<%=Fasic %>" class="put"  maxlength="25" />魅力值大小：0-255
					<input type="hidden" name="hidv" id="hidv" value="<%=HidFasic %>" />
				</td>
			</tr>
			<tr>
				<td width="17%" align="right" valign="top">
					道具说明：</td>
				<td width="83%" align="left">
					<input type="text" name="Descript" id="Descript" value="<%=Descript %>" class="put" style="width: 338px" maxlength="25" />限25个字符
				</td>
			</tr>
			
			<tr>
				<td width="17%" align="right">
					&nbsp;</td>
				<td width="83%" align="left">
					<asp:Button ID="Button1" runat="server" Text="提交修改" class="put" OnClick="EditJpPro" />&nbsp;&nbsp;&nbsp;&nbsp;<input type="button"  value="返   回" onclick="javascript:history.back()" class="put" />
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
                if(!alertNonNegativeNumber($('#Price')[0], msgfix+'普通用户价格'+msgend)){
                    return false;
                }
                
                //------document.getElementById('Award_OnLineTime') = $('#Award_OnLineTime')[0]
                if(!alertNonNegativeNumber($('#VipPrice')[0], msgfix+'VIP价格'+msgend)){
                    return false;
                }
                
                return true;
            }
         //-->
		</script>

	</form>
</body>
</html>
