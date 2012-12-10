<%@ Page Language="C#" AutoEventWireup="true"   Inherits="Bzw.Inhersits.Manage.Pay.IPS.Manage_Pay_IPS_OrderPay" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>



<body onload="document.getElementById('frmPay').submit();">
    <!-- 
    [modify for debug] jeffery
    <form id="frmPay" method="post" action="https://pay.ips.com.cn/ipayment.aspx">
    -->
    <form id="frmPay" method="post" action="https://pay.ips.net.cn/ipayment.aspx">
    <input type="hidden" id="Mer_code" runat="server" />
    <input type="hidden" id="Billno" runat="server" />
    <input type="hidden" id="Amount" runat="server" />
    <input type="hidden" id="Date" runat="server" />
    <input type="hidden" id="Currency_Type" runat="server" />
    <input type="hidden" id="Gateway_Type" value="01" runat="server" />
    <input type="hidden" id="Lang" value="GB" runat="server"/>
    <input type="hidden" id="MerchantUrl" runat="server" />
    <input type="hidden" id="failUrl" runat="server" />
    <input type="hidden" id="ErrorUrl" runat="server" />
    <input type="hidden" id="Attach" runat="server"/>
    <input type="hidden" id="OrderEncodeType" value="5"  runat="server"/>
    <input type="hidden" id="RetEncodeType" value="17" runat="server" />
    <input type="hidden" id="Rettype" value="0" runat="server"/>
    <input type="hidden" id="ServerUrl" runat="server" />
    <input type="hidden" id="signMD5" runat="server" />
    <input type="hidden" id="DoCredit" runat="server" value="" />
    <input type="hidden" id="Bankco" runat="server" value="" />
    </form>
</body>
</html>
