<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Sconfig_SystemStat" Codebehind="SystemStat.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
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
</head>
<body>
    <form id="form1" runat="server">
    
    <asp:Repeater ID="PrizesHList" runat="server">
                <ItemTemplate>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
            <tr><td colspan="2" class="title_03" align="center" ><strong>系统统计列表</strong></td></tr>
            <tr>
                <td align="right" width="40%">
                    玩家银行总存款&nbsp;&nbsp;&nbsp;
                    <td width="60%" align="left">
                        &nbsp;&nbsp;<%# Eval("UserBankMoney")%>金币
                    </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    玩家钱包总余额&nbsp;&nbsp;&nbsp;
                    <td align="left">
                        &nbsp;&nbsp;<%# Eval("UserWalletMoney")%>金币
                    </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                   玩家所有金币数&nbsp;&nbsp;&nbsp;
                    <td align="left">
                        &nbsp;&nbsp;<%# Eval("UserAllMoney")%>金币
                        </td>
            </tr>
            <tr>
                <td align="right" width="40%">
                    机器人银行总存款&nbsp;&nbsp;&nbsp;
                    <td width="60%" align="left">
                        &nbsp;&nbsp;<%# Eval("RobotBankMoney")%>金币
                    </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    机器人钱包总余额&nbsp;&nbsp;&nbsp;
                    <td align="left">
                        &nbsp;&nbsp;<%# Eval("RobotWalletMoney")%>金币
                    </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                   机器人所有金币数&nbsp;&nbsp;&nbsp;
                    <td align="left">
                        &nbsp;&nbsp;<%# Eval("RobotAllMoney")%>金币
                        </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    交税总数&nbsp;&nbsp;&nbsp;
                    <td align="left">
                        &nbsp;&nbsp;<%# Eval("AllTax")%>金币
                        </td>
            </tr>
            <tr >
                <td align="right" width="34%">
                    最高交税数&nbsp;&nbsp;&nbsp;</td>
                <td align="left">
                    &nbsp;&nbsp;<%# Eval("MaxTax")%>金币
                    </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    最低交税数&nbsp;&nbsp;&nbsp;</td>
                <td align="left">
                    &nbsp;&nbsp;<%# Eval("MinTax")%>金币
                    </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    充值金币总数&nbsp;&nbsp;&nbsp;</td>
                <td align="left">
                   &nbsp;&nbsp;<%# Eval("AllPayMoney")%>金币
                    </td>
            </tr>
             <tr><td colspan="2" class="title_03" align="center" ><strong>注册人数统计列表</strong></td></tr>
            <tr>
                <td align="right" width="34%">
                    总注册人数&nbsp;&nbsp;&nbsp;</td>
                <td align="left">
                   &nbsp;&nbsp;<%# Eval("AllRegUserCount")%>人
                    </td>
            </tr>
            <tr>
                <td align="right" width="34%">
                    被推广人数&nbsp;&nbsp;&nbsp;</td>
                <td align="left">
                    &nbsp;&nbsp;<%# Eval("AllTGUserCount")%>人
                    </td>
            </tr>
            <tr >
                <td align="right" width="34%">
                    总赠送金币数&nbsp;&nbsp;&nbsp;</td>
                <td align="left">
                    &nbsp;&nbsp;<%# Eval("AllPresentMoney")%>金币
                    </td>
            </tr>
            
           
        </table>
        </ItemTemplate>
        </asp:Repeater>
    </form>
</body>
</html>
