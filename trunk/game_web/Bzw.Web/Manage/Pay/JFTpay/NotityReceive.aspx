<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="NotityReceive.aspx.cs" Inherits="Bzw.Inhersits.Manage_Pay_JFTpay_NotityReceive" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>聚付通支付</title>
    <meta name="description" content="">
    <meta http-equiv="Content-Type" content="text/html; charset=uft-8" />
    <style type="text/css">
        body
        {
            font-size: 12px;
            margin-left: 0px;
            margin-top: 0px;
            margin-right: 0px;
            margin-bottom: 0px;
        }
        .Sy1
        {
            color: #2179DD;
        }
        .Sy2
        {
            color: #FFFFFF;
            font-size: 16px;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <form id="Form1" runat="server">
    <table width="100%" height="34" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td width="34">
                <img src="img/pic_1.gif" width="69" height="60" />
            </td>
            <td width="204" background="img/pic_3.gif" bgcolor="#2179DD">
                <a href="http://www.jftpay.net/">
                    <img src="img/Logo.png" alt="jftpay" width="204" height="55" border="0" /></a>
            </td>
            <td background="img/pic_3.gif" bgcolor="#2179DD">
                <span class="Sy2">聚付通支付，支付结果</span>
            </td>
            <td width="13" height="34">
                <img src="img/pic_2.gif" width="69" height="60" />
            </td>
        </tr>
    </table>
    <p>
        <br />
    </p>
    <table width="50%" border="0" align="center" cellpadding="0" cellspacing="0" style="border: solid 1px #107929">
        <tr>
            <td height="35">
                <table width="100%" border="0" align="center" cellpadding="5" cellspacing="1">
                    <tr>
                        <td height="30" colspan="2" bgcolor="#6BBE18">
                            <span style="color: #FFFFFF">感谢您使用聚付通支付平台</span>
                        </td>
                    </tr>
                    <tr>
                        <td colspan="2" bgcolor="#CEE7BD">
                        </td>
                    </tr>
                    <tr>
                        <td align="left" width="30%" class="Sy1">
                            &nbsp;&nbsp;商户订单号
                        </td>
                        <td align="left">
                            &nbsp;&nbsp;<label id="id" runat="server"></label>
                        </td>
                    </tr>
                    <tr>
                        <td align="left">
                            &nbsp;&nbsp;支付结果
                        </td>
                        <td align="left">
                            &nbsp;&nbsp;<label id="state" runat="server"></label>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
