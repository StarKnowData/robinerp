<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Pay_Rate" CodeBehind="Rate.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <%--<script type="text/javascript" src="/Public/Js/Global.js"></script>--%>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <script type="text/javascript" src="/Public/Js/public.js"></script>

    <style type="text/css">
        <!
        -- body
        {
            background-color: #FFFFFF;
            margin-top: 0px;
        }
        .imeclose
        {
            ime-mode: disabled;
        }
        -- ></style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
                <strong>用户充值人民币金币兑换比例设置</strong>
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                充值1元 =
            </td>
            <td align="left">
                <input id="txt1Yuan" name="txt1Yuan" maxlength="7" runat="server" class="imeclose"
                    onkeypress="return KeyPressNum(this,event);" /><%=UiCommon.StringConfig.MoneyName %>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txt1Yuan"
                    Display="Dynamic" ErrorMessage="请输入每1元点卡可兑换金币数"></asp:RequiredFieldValidator>
                <asp:CompareValidator ID="CompareValidator1" runat="server" ControlToValidate="txt1Yuan"
                    Display="Dynamic" ErrorMessage="只能输入大于0的整数！" Operator="GreaterThan" Type="Integer"
                    ValueToCompare="0"></asp:CompareValidator>
            </td>
        </tr>
        <tr style='<%=ConfigurationManager.AppSettings["IsPayToPoint"]=="1"?"":"display:none;" %>'>
            <td align="right" width="25%">
             充值1元 =
            </td>
            <td align="left">
            <asp:TextBox ID="txtPointChangeRate" runat="server" Text="0" MaxLength="19"></asp:TextBox>
              <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtPointChangeRate"
                    Display="Dynamic" ErrorMessage="请输入每1元可兑换积分数"></asp:RequiredFieldValidator>
                <asp:CompareValidator ID="CompareValidator2" runat="server" ControlToValidate="txtPointChangeRate"
                    Display="Dynamic" ErrorMessage="只能输入大于等于0的整数！" Operator="GreaterThanEqual" Type="Double"
                    ValueToCompare="0"></asp:CompareValidator>
            积分
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                玩家每日充值金额限制
            </td>
            <td align="left">
                <asp:TextBox ID="txtUserMaxPayMoney" runat="server" CssClass="imeclose" MaxLength="7"
                    onkeypress="return KeyPressNum(this,event);"></asp:TextBox>元
            </td>
        </tr>
        <%--<tr style="display:none ;">
				<td align="right" width="25%">
					易宝网银充值1元 = </td>
				<td align="left">
					<input id="txtNetBank" name="txtNetBank" maxlength="12" runat="server"  class="imeclose" onkeypress="return KeyPressNum(this,event);" />金币
					<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtNetBank" Display="Dynamic" ErrorMessage="请输入易宝网银充值1元可兑换金币数"></asp:RequiredFieldValidator>
					<asp:CompareValidator ID="CompareValidator2" runat="server" ControlToValidate="txtNetBank" Display="Dynamic" ErrorMessage="只能输入大于0的整数！" Operator="GreaterThan" Type="Integer" ValueToCompare="0"></asp:CompareValidator></td>
			</tr>
			<tr style="display:none ;">
				<td align="right" width="25%">
					易宝骏网一卡通充值1元 = </td>
				<td align="left">
					<input id="txtJunnet" name="txtJunnet" maxlength="12" runat="server" class="imeclose" onkeypress="return KeyPressNum(this,event);" />金币
					<asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate="txtJunnet" Display="Dynamic" ErrorMessage="请输入易宝骏网一卡通充值1元可兑换金币数"></asp:RequiredFieldValidator>
					<asp:CompareValidator ID="CompareValidator3" runat="server" ControlToValidate="txtJunnet" Display="Dynamic" ErrorMessage="只能输入大于0的整数！" Operator="GreaterThan" Type="Integer" ValueToCompare="0"></asp:CompareValidator></td>
			</tr>
			<tr style="display:none ;">
				<td align="right" width="25%">
					易宝中移动神州行充值1元 = </td>
				<td align="left">
					<input id="txtSzx" name="txtSzx" maxlength="12" runat="server" class="imeclose" onkeypress="return KeyPressNum(this,event);" />金币
					<asp:RequiredFieldValidator ID="RequiredFieldValidator4" runat="server" ControlToValidate="txtSzx" Display="Dynamic" ErrorMessage="请输入易宝神州行充值1元可兑换金币数"></asp:RequiredFieldValidator>
					<asp:CompareValidator ID="CompareValidator4" runat="server" ControlToValidate="txtSzx" Display="Dynamic" ErrorMessage="只能输入大于0的整数！" Operator="GreaterThan" Type="Integer" ValueToCompare="0"></asp:CompareValidator></td>
			</tr>
			<tr style="display:none ;">
				<td align="right" width="25%">
					易宝联通充值卡充值1元 = </td>
				<td align="left">
					<input id="txtUnicom" name="txtUnicom" maxlength="12" runat="server" class="imeclose" onkeypress="return KeyPressNum(this,event);" />金币
					<asp:RequiredFieldValidator ID="RequiredFieldValidator5" runat="server" ControlToValidate="txtUnicom" Display="Dynamic" ErrorMessage="请输入易宝联通充值卡充值1元可兑换金币数"></asp:RequiredFieldValidator>
					<asp:CompareValidator ID="CompareValidator5" runat="server" ControlToValidate="txtUnicom" Display="Dynamic" ErrorMessage="只能输入大于0的整数！" Operator="GreaterThan" Type="Integer" ValueToCompare="0"></asp:CompareValidator></td>
			</tr>
			<tr style="display:none ;">
				<td align="right" width="25%">
					易宝一卡通充值1元 = </td>
				<td align="left">
					<input id="txtYPCard" name="txtYPCard" maxlength="12" runat="server" class="imeclose" onkeypress="return KeyPressNum(this,event);" />金币
					<asp:RequiredFieldValidator ID="RequiredFieldValidator6" runat="server" ControlToValidate="txtYPCard" Display="Dynamic" ErrorMessage="请输入易宝一卡通充值1元可兑换金币数"></asp:RequiredFieldValidator>
					<asp:CompareValidator ID="CompareValidator6" runat="server" ControlToValidate="txtYPCard" Display="Dynamic" ErrorMessage="只能输入大于0的整数！" Operator="GreaterThan" Type="Integer" ValueToCompare="0"></asp:CompareValidator></td>
			</tr>--%>
        <tr>
            <td>
                &nbsp;
            </td>
            <td>
                <asp:Button ID="Button1" runat="server" Text="提交修改" class="put" OnClick="EditFilt" />
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
