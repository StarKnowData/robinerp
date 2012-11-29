<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GMAwardTypeSetEdit.aspx.cs" Inherits="Bzw.Web.Admin.SConfig.GMAwardTypeSetEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>

    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <script src="/Public/Js/ColorPicker.js"></script>
</head>
<body>
    <form id="Login" runat="server">
	 <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td style="text-align:left; font-weight:bold; height:5px">
                   GM赠送方案管理</td>
            </tr>
        </table>
         <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td style="height:5px;"></td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td style="width:30%; text-align:right;">赠送金币数：</td>
                <td  align="left">
					<asp:TextBox ID="txtMoney" runat="server"></asp:TextBox>
                &nbsp;<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtMoney" Display="Dynamic" ErrorMessage="赠送金币数不能为空"></asp:RequiredFieldValidator>
					<asp:RangeValidator ID="RangeValidator1" runat="server" ControlToValidate="txtMoney" ErrorMessage="需为0-9亿内数字" MaximumValue="900000000" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
            </tr>
            <tr>
                <td align="right" valign="top">
                    赠送道具1：</td>
                <td style="text-align:left;">
					道具：<asp:DropDownList ID="ddlProp1" runat="server">
						<asp:ListItem Value="0" Text="不选"></asp:ListItem>
					</asp:DropDownList> 
				    数量：<asp:TextBox ID="txtCount1" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator2" runat="server" ControlToValidate="txtCount1" ErrorMessage="需为0-999内数字" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
              
            </tr>
            <tr>
                <td align="right" valign="top">
                    赠送道具2：</td>
                <td align="left">
                 道具：<asp:DropDownList ID="ddlProp2" runat="server">
						<asp:ListItem Value="0" Text="不选"></asp:ListItem>
					</asp:DropDownList>
				 数量：<asp:TextBox ID="txtCount2" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator3" runat="server" ControlToValidate="txtCount2" ErrorMessage="需为0-999内数字" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
                
            </tr>
             <tr>
                <td align="right" valign="top">
                    赠送道具3：</td>
                <td align="left">
				 道具：<asp:DropDownList ID="ddlProp3" runat="server">
						<asp:ListItem Value="0" Text="不选"></asp:ListItem>
					</asp:DropDownList>
				 数量：<asp:TextBox ID="txtCount3" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator4" runat="server" ControlToValidate="txtCount3" ErrorMessage="需为0-999内数字" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
               
            </tr>
             <tr>
                <td align="right" valign="top">
                    赠送道具4：</td>
                <td align="left">
                 道具：<asp:DropDownList ID="ddlProp4" runat="server">
						<asp:ListItem Value="0" Text="不选"></asp:ListItem>
					</asp:DropDownList>
				 数量：<asp:TextBox ID="txtCount4" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator5" runat="server" ControlToValidate="txtCount4" ErrorMessage="需为0-999内数字" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
              
            </tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 添 加 " class="put" onclick="Button1_Click"/>
                    <input type="button" name="Submit2" value=" 返 回 " class="put" onclick="javascript:location.href='GMAwardTypeSet.aspx';"/>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
