<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_Filtering" Codebehind="Filtering.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

	<script type="text/javascript" src="/Public/Js/public.js"></script>

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
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>注册过滤设置</strong></td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    用户名中禁止包含的关键字：<br />
                    （多个关键字请用“|”分隔）</td>
                <td align="left">
					<asp:TextBox ID="txtBadUserName" CssClass="put" TextMode="MultiLine" Rows="5" Columns="50" runat="server"></asp:TextBox>
                    最多8000个字符（4000个汉字）</td>
            </tr>
            <tr>
                <td align="right">
                    昵称中禁止包含的关键字：<br />
                    （多个关键字请用“|”分隔）</td>
                <td align="left">
                    <asp:TextBox runat="server" ID="txtBadNickName" CssClass="put" TextMode="multiLine" Rows="5" Columns="50"></asp:TextBox>
                    最多8000个字符（4000个汉字）</td>
            </tr>
            <tr>
                <td colspan="2">
                    说明：禁止包含的关键字。即如果您禁止包含关键字"admin"，那么"admin2"或"adminGG"都不能注册。</td>
            </tr>
            <tr>
                <td align="right">
					限制IP注册：
                </td>
                <td align="left">
					<asp:TextBox runat="server" ID="txtIPDisabled" CssClass="put" TextMode="MultiLine" Rows="5" Columns="50"></asp:TextBox>
					如：192.168.*.*，127.*.*.*，不能是*.168.168.168的形式。多个用半角逗号（,）间隔，最多2000个字符（包括逗号）。
                </td>
            </tr>
             
            <tr>
                <td align="right">
					重复注册间隔时间：
                </td>
                <td align="left">
					<asp:TextBox runat="server" ID="txtReRegTimeSpan" CssClass="put" style="ime-mode:disabled;" MaxLength="3" Width="25px"></asp:TextBox>
					分钟，填写0表示不限制，只能填写大于或等于0的整数。
					<asp:CompareValidator ID="CompareValidator1" runat="server" ControlToValidate="txtReRegTimeSpan" Display="Dynamic" ErrorMessage="重复注册间隔时间只能是大于等于0的整数！" Operator="GreaterThanEqual" Type="Integer" ValueToCompare="0"></asp:CompareValidator></td>
            </tr>
            <tr>
                <td align="right">
					不在财富排行榜中显示的用户名关键字：
                </td>
               <td align="left">
					<asp:TextBox runat="server" ID="txtSpecialUser" CssClass="put"  MaxLength="6" Width="100px"></asp:TextBox>
					例如：关键字为game，所有帐户为game*的账户都不会显示在财富排行榜中。请将该关键字也设置为用户名中禁止包含的关键字，防止玩家注册到。
					</td>
            </tr>
            <tr>
                <td align="right">同一IP每日注册帐号数量限制：</td>
                <td align="left"><asp:TextBox ID="txtSameIPRegCount" runat="server" MaxLength="6" Width="25px" Text="0" onkeypress="return KeyPressNum(this,event);"></asp:TextBox>填写0则不限制</td>
            </tr>
            <tr>
                <td align="right">同一身份证注册帐号数量限制：</td>
                <td align="left"><asp:TextBox ID="txtSameCardNoRegCount" runat="server" MaxLength="6" Width="25px" Text="0" onkeypress="return KeyPressNum(this,event);"></asp:TextBox>填写0则不限制</td>
            </tr>
            <tr>
                <td>
                    &nbsp;
                </td>
                <td>
                    <asp:Button ID="Button1" runat="server" Text="提交修改" class="put"   OnClick="EditFilt"/>
                </td>
            </tr>
        </table>
    </form>
    

</body>
</html>
